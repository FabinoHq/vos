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


////////////////////////////////////////////////////////////////////////////////
//  Window default constructor                                                //
////////////////////////////////////////////////////////////////////////////////
Window::Window() :
m_instance(0),
m_handle(0),
m_device(0),
m_context(0)
{

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
void Window::udpate()
{

}

////////////////////////////////////////////////////////////////////////////////
//  Close the window                                                          //
////////////////////////////////////////////////////////////////////////////////
void Window::close()
{
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

    // Context successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Window static event callback function                                     //
////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK Window::OnEvent(
    HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam
)
{
    // Default windows events
    return DefWindowProc(hwnd, msg, wparam, lparam);
}
