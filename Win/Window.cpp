////////////////////////////////////////////////////////////////////////////////
//     _______                       ____________________________________     //
//     \\ .   \            _________/ . . . . . . . . . . . . . . . .   /     //
//      \\ .   \       ___/ . . . . .    ______________________________/      //
//       \\ .   \   __/. . .   _________/     /    // .  __________/          //
//        \\ .   \_//      ___/ .  _____     /    // .  /______               //
//         \\ .   \/     _/ // .  /    \\    |    \\  .        \              //
//          \\ .        /   || .  |    ||    |     \\______     \             //
//           \\ .      /    || .  \____//    |  _________//     /             //
//            \\ .    /     //  .            / // . . . .      /              //
//             \\____/     //_______________/ //______________/               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//   This is free and unencumbered software released into the public domain.  //
//                                                                            //
//   Anyone is free to copy, modify, publish, use, compile, sell, or          //
//   distribute this software, either in source code form or as a compiled    //
//   binary, for any purpose, commercial or non-commercial, and by any        //
//   means.                                                                   //
//                                                                            //
//   In jurisdictions that recognize copyright laws, the author or authors    //
//   of this software dedicate any and all copyright interest in the          //
//   software to the public domain. We make this dedication for the benefit   //
//   of the public at large and to the detriment of our heirs and             //
//   successors. We intend this dedication to be an overt act of              //
//   relinquishment in perpetuity of all present and future rights to this    //
//   software under copyright law.                                            //
//                                                                            //
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,          //
//   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF       //
//   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   //
//   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR        //
//   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,    //
//   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR    //
//   OTHER DEALINGS IN THE SOFTWARE.                                          //
//                                                                            //
//   For more information, please refer to <http://unlicense.org>             //
////////////////////////////////////////////////////////////////////////////////
//    VOS : Virtual Operating System                                          //
//     Win/Window.cpp : Window management for Windows                         //
////////////////////////////////////////////////////////////////////////////////
#include "Window.h"

Window* VOSGlobalWindow = 0;


////////////////////////////////////////////////////////////////////////////////
//  Window default constructor                                                //
////////////////////////////////////////////////////////////////////////////////
Window::Window() :
m_instance(0),
m_handle(0),
m_device(0),
m_context(0)
{
    if (!VOSGlobalWindow)
    {
        // Set global window pointer
        VOSGlobalWindow = this;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Window destructor                                                         //
////////////////////////////////////////////////////////////////////////////////
Window::~Window()
{
    // Close the window
    close();
}


////////////////////////////////////////////////////////////////////////////////
//  Create the window                                                         //
//  return : True if the window is successfully created                       //
////////////////////////////////////////////////////////////////////////////////
bool Window::create()
{
    // Get the software instance
    m_instance = GetModuleHandle(0);

    // Get the system display mode
    DisplayMode displayMode;
    if (!displayMode.getSystemMode())
    {
        // Invalid system mode
        return false;
    }

    // Register the window class
    WNDCLASS windowClass = { 0 };
    windowClass.style = 0;
    windowClass.lpfnWndProc = &Window::OnEvent;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = m_instance;
    windowClass.hIcon = LoadIcon(0, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(0, IDC_ARROW);
    windowClass.hbrBackground = 0;
    windowClass.lpszMenuName = 0;
    windowClass.lpszClassName = VOSWindowClassName;
    if (!RegisterClass(&windowClass))
    {
        // Unable to register the window class
        return false;
    }

    // Define the window settings
    DWORD windowStyle = (WS_VISIBLE | WS_CAPTION | WS_SYSMENU);
    LONG windowWidth = 1024;
    LONG windowHeight = 768;

    // Center the window
    int centerX = (displayMode.getWidth() / 2) - (windowWidth / 2);
    int centerY = (displayMode.getHeight() / 2) - (windowHeight / 2);

    // Create the window
    m_handle = CreateWindow(
        VOSWindowClassName, L"VOS", windowStyle, centerX, centerY,
        windowWidth, windowHeight, 0, 0, m_instance, this
    );
    if (!m_handle)
    {
        // Unable to create the window
        return false;
    }

    // Set focus to the window
    UpdateWindow(m_handle);
    ShowCursor(TRUE);
    SetActiveWindow(m_handle);
    SetFocus(m_handle);
    ShowWindow(m_handle, SW_SHOW);

    // Create the window context
    return createContext();
}

////////////////////////////////////////////////////////////////////////////////
//  Update the window (swap front and back buffers)                           //
////////////////////////////////////////////////////////////////////////////////
void Window::update()
{
    if (m_device)
    {
        // Swap front and back buffers
        SwapBuffers(m_device);
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Close the window                                                          //
////////////////////////////////////////////////////////////////////////////////
void Window::close()
{
    if (m_context)
    {
        // Delete context
        wglMakeCurrent(m_device, 0);
        wglDeleteContext(m_context);
        m_context = 0;
    }

    if (m_device)
    {
        // Release device
        ReleaseDC(m_handle, m_device);
        m_device = 0;
    }

    if (m_handle)
    {
        // Delete the window
        DestroyWindow(m_handle);
        UnregisterClass(VOSWindowClassName, m_instance);
        m_handle = 0;
    }
}


////////////////////////////////////////////////////////////////////////////////
//  Get window event                                                          //
//  return : True if an event occurred, false otherwise                       //
////////////////////////////////////////////////////////////////////////////////
bool Window::getEvent(Event& event)
{
    // Events processing
    MSG msg;
    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Get event in the FIFO queue
    event.type = EVENT_NONE;
    if (!m_events.empty())
    {
        event = m_events.front();
        m_events.pop();
        return true;
    }

    return false;
}


////////////////////////////////////////////////////////////////////////////////
//  Create window context                                                     //
//  return : True if the window context is successfully created               //
////////////////////////////////////////////////////////////////////////////////
bool Window::createContext()
{
    if (!m_handle)
    {
        // Invalid window handle
        return false;
    }

    // Get the device context
    m_device = GetDC(m_handle);
    if (!m_device)
    {
        // Invalid device context
        return false;
    }

    // Set the pixel format descriptor
    PIXELFORMATDESCRIPTOR pfd = { 0 };
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = (PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER);
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cRedBits = 0;
    pfd.cRedShift = 0;
    pfd.cGreenBits = 0;
    pfd.cGreenShift = 0;
    pfd.cBlueBits = 0;
    pfd.cBlueShift = 0;
    pfd.cAlphaBits = 0;
    pfd.cAlphaShift = 0;
    pfd.cAccumBits = 0;
    pfd.cAccumRedBits = 0;
    pfd.cAccumGreenBits = 0;
    pfd.cAccumBlueBits = 0;
    pfd.cAccumAlphaBits = 0;
    pfd.cDepthBits = 8;
    pfd.cStencilBits = 24;
    pfd.cAuxBuffers = 0;
    pfd.bReserved = PFD_MAIN_PLANE;
    pfd.dwVisibleMask = 0;

    int pixelFormat = ChoosePixelFormat(m_device, &pfd);
    if (!pixelFormat)
    {
        // Invalid pixel format
        return false;
    }

    if (!SetPixelFormat(m_device, pixelFormat, &pfd))
    {
        // Unable to set the pixel format
        return false;
    }

    // Create the graphics context
    m_context = wglCreateContext(m_device);
    if (!m_context)
    {
        // Unable to create the graphics context
        return false;
    }

    // Context successfully created
    wglMakeCurrent(m_device, m_context);
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Window static event callback function                                     //
////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK Window::OnEvent(
    HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam
)
{
    // Process event
    if (VOSGlobalWindow)
    {
        VOSGlobalWindow->processEvent(msg, wparam, lparam);
    }

    // System destroy event
    if (msg == WM_DESTROY)
    {
        PostQuitMessage(0);
    }

    // Default window events
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

////////////////////////////////////////////////////////////////////////////////
//  Process window events                                                     //
////////////////////////////////////////////////////////////////////////////////
void Window::processEvent(UINT msg, WPARAM wparam, LPARAM lparam)
{
    if (m_handle)
    {
        Event event;
        event.type = EVENT_NONE;

        // Event type
        switch (msg)
        {
            // Create window event
            case WM_CREATE:
                event.type = EVENT_CREATED;
                break;

            // Close window events
            case WM_CLOSE:
                event.type = EVENT_CLOSED;
                break;

            case WM_QUIT:
                event.type = EVENT_CLOSED;
                break;

            // Keys events
            case WM_KEYDOWN:
                event.type = EVENT_KEYPRESSED;
                event.key = transcriptKey(wparam);
                break;

            case WM_KEYUP:
                event.type = EVENT_KEYRELEASED;
                event.key = transcriptKey(wparam);
                break;

            default:
                event.type = EVENT_NONE;
                break;
        }

        // Add new event
        m_events.push(event);
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Transcript key event                                                      //
////////////////////////////////////////////////////////////////////////////////
EventKey Window::transcriptKey(WPARAM key)
{
    switch (key)
    {
        case VK_ESCAPE:
            return EVENT_KEY_ESCAPE;

        case VK_RETURN:
            return EVENT_KEY_RETURN;

        default:
            return EVENT_KEY_NONE;
    }
}
