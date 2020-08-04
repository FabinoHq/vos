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
//     System/Win/SysWindow.cpp : Window management for Windows               //
////////////////////////////////////////////////////////////////////////////////
#include "SysWindow.h"

SysWindow* VOSGlobalWindow = 0;


////////////////////////////////////////////////////////////////////////////////
//  SysWindow default constructor                                             //
////////////////////////////////////////////////////////////////////////////////
SysWindow::SysWindow() :
m_instance(0),
m_handle(0)
{
    if (!VOSGlobalWindow)
    {
        // Set global window pointer
        VOSGlobalWindow = this;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  SysWindow destructor                                                      //
////////////////////////////////////////////////////////////////////////////////
SysWindow::~SysWindow()
{
    // Close the window
    close();
}


////////////////////////////////////////////////////////////////////////////////
//  Create the window                                                         //
//  return : True if the window is successfully created                       //
////////////////////////////////////////////////////////////////////////////////
bool SysWindow::create()
{
    // Get the software instance
    m_instance = GetModuleHandle(0);

    // Get the system display mode
    SysDisplayMode displayMode;
    if (!displayMode.getSystemMode())
    {
        // Invalid system mode
        return false;
    }

    // Register the window class
    WNDCLASS windowClass = { 0 };
    windowClass.style = 0;
    windowClass.lpfnWndProc = &SysWindow::OnEvent;
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
    DWORD windowStyle = (WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_SIZEBOX);
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
        // Unable to create the system window
        return false;
    }

    // Enable the window
    UpdateWindow(m_handle);
    ShowCursor(TRUE);
    SetActiveWindow(m_handle);
    SetFocus(m_handle);
    ShowWindow(m_handle, SW_SHOW);

    // System window successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Close the window                                                          //
////////////////////////////////////////////////////////////////////////////////
void SysWindow::close()
{
    if (m_handle)
    {
        // Delete the window
        DestroyWindow(m_handle);
        UnregisterClass(VOSWindowClassName, m_instance);
    }
    
    m_instance = 0;
    m_handle = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Get window event                                                          //
//  return : True if an event occurred, false otherwise                       //
////////////////////////////////////////////////////////////////////////////////
bool SysWindow::getEvent(Event& event)
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
//  Get window instance                                                       //
//  return : Reference to the window instance                                 //
////////////////////////////////////////////////////////////////////////////////
HINSTANCE& SysWindow::getInstance()
{
    return m_instance;
}

////////////////////////////////////////////////////////////////////////////////
//  Get window handle                                                         //
//  return : Reference to the window handle                                   //
////////////////////////////////////////////////////////////////////////////////
HWND& SysWindow::getHandle()
{
    return m_handle;
}


////////////////////////////////////////////////////////////////////////////////
//  Window static event callback function                                     //
////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK SysWindow::OnEvent(
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
void SysWindow::processEvent(UINT msg, WPARAM wparam, LPARAM lparam)
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
                m_events.push(event);
                break;

            // Close window events
            case WM_CLOSE:
                event.type = EVENT_CLOSED;
                m_events.push(event);
                break;

            case WM_QUIT:
                event.type = EVENT_CLOSED;
                m_events.push(event);
                break;

            // Resize window event
            case WM_SIZE:
                event.type = EVENT_RESIZED;
                m_events.push(event);
                break;

            // Keys events
            case WM_KEYDOWN:
                event.type = EVENT_KEYPRESSED;
                event.key = transcriptKey(wparam);
                m_events.push(event);
                break;

            case WM_KEYUP:
                event.type = EVENT_KEYRELEASED;
                event.key = transcriptKey(wparam);
                m_events.push(event);
                break;

            default:
                break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Transcript key event                                                      //
////////////////////////////////////////////////////////////////////////////////
EventKey SysWindow::transcriptKey(WPARAM key)
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
