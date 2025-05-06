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
//   For more information, please refer to <https://unlicense.org>            //
////////////////////////////////////////////////////////////////////////////////
//    VOS : Virtual Operating System                                          //
//     System/Win/SysWindow.cpp : Window management for Windows               //
////////////////////////////////////////////////////////////////////////////////
#include "SysWindow.h"


////////////////////////////////////////////////////////////////////////////////
//  SysWindow global instance                                                 //
////////////////////////////////////////////////////////////////////////////////
SysWindow GSysWindow = SysWindow();


////////////////////////////////////////////////////////////////////////////////
//  SysWindow default constructor                                             //
////////////////////////////////////////////////////////////////////////////////
SysWindow::SysWindow() :
m_instance(0),
m_handle(0),
m_hasFocus(false),
m_systemMode(),
m_width(0),
m_height(0),
m_cursors(0),
m_events()
{

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
    if (!m_systemMode.getSystemMode())
    {
        // Invalid system mode
        GSysMessage << "[0x2001] Invalid system display mode\n";
        GSysMessage << "Current system display mode must be valid";
        return false;
    }

    // Allocate system cursors
    m_cursors = GSysMemory.alloc<HCURSOR>(
        SYSCURSOR_CURSORSCOUNT, SYSMEMORY_WINDOW
    );
    if (!m_cursors) { return false; }

    // Load system cursors
    for (int i = 0; i < SYSCURSOR_CURSORSCOUNT; ++i) { m_cursors[i] = 0; }
    m_cursors[SYSCURSOR_NONE] = 0;
    m_cursors[SYSCURSOR_DEFAULT] = LoadCursor(0, IDC_ARROW);
    if (!m_cursors[SYSCURSOR_DEFAULT]) { return false; }
    #if (VOS_POINTERLOCK == 0)
        m_cursors[SYSCURSOR_TOPRESIZE] = LoadCursor(0, IDC_SIZENS);
        if (!m_cursors[SYSCURSOR_TOPRESIZE]) { return false; }
        m_cursors[SYSCURSOR_BOTTOMRESIZE] = LoadCursor(0, IDC_SIZENS);
        if (!m_cursors[SYSCURSOR_BOTTOMRESIZE]) { return false; }
        m_cursors[SYSCURSOR_LEFTRESIZE] = LoadCursor(0, IDC_SIZEWE);
        if (!m_cursors[SYSCURSOR_LEFTRESIZE]) { return false; }
        m_cursors[SYSCURSOR_RIGHTRESIZE] = LoadCursor(0, IDC_SIZEWE);
        if (!m_cursors[SYSCURSOR_RIGHTRESIZE]) { return false; }
        m_cursors[SYSCURSOR_TOPLEFTRESIZE] = LoadCursor(0, IDC_SIZENWSE);
        if (!m_cursors[SYSCURSOR_TOPLEFTRESIZE]) { return false; }
        m_cursors[SYSCURSOR_TOPRIGHTRESIZE] = LoadCursor(0, IDC_SIZENESW);
        if (!m_cursors[SYSCURSOR_TOPRIGHTRESIZE]) { return false; }
        m_cursors[SYSCURSOR_BOTTOMLEFTRESIZE] = LoadCursor(0, IDC_SIZENESW);
        if (!m_cursors[SYSCURSOR_BOTTOMLEFTRESIZE]) { return false; }
        m_cursors[SYSCURSOR_BOTTOMRIGHTRESIZE] = LoadCursor(0, IDC_SIZENWSE);
        if (!m_cursors[SYSCURSOR_BOTTOMRIGHTRESIZE]) { return false; }
    #endif // VOS_POINTERLOCK

    // Register the window class
    WNDCLASS windowClass = { 0 };
    windowClass.style = 0;
    windowClass.lpfnWndProc = &SysWindow::OnEvent;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = m_instance;
    windowClass.hIcon = LoadIcon(0, IDI_APPLICATION);
    windowClass.hCursor = m_cursors[SYSCURSOR_DEFAULT];
    windowClass.hbrBackground = 0;
    windowClass.lpszMenuName = 0;
    windowClass.lpszClassName = VOSWindowClassName;
    if (!RegisterClass(&windowClass))
    {
        // Unable to register the window class
        GSysMessage << "[0x2002] Unable to register the window class\n";
        GSysMessage << "Window class must be registrable";
        return false;
    }

    // Window size
    m_width = 1760;
    m_height = 990;

    // Define the window settings
    DWORD windowStyle = (
        WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_OVERLAPPED | WS_CAPTION |
        WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX
    );
    LONG windowWidth = m_width;
    LONG windowHeight = m_height;

    // Center the window
    int centerX = (m_systemMode.getWidth() / 2) - (m_width / 2);
    int centerY = (m_systemMode.getHeight() / 2) - (m_height / 2);

    // Create the window
    m_handle = CreateWindow(
        VOSWindowClassName, L"VOS", windowStyle, centerX, centerY,
        windowWidth, windowHeight, 0, 0, m_instance, this
    );
    if (!m_handle)
    {
        // Unable to create the system window
        GSysMessage << "[0x2003] Unable to create the system window\n";
        GSysMessage << "System window must be creatable";
        return false;
    }

    // Register raw mouse input
    RAWINPUTDEVICE rawmouse;
    rawmouse.usUsagePage = HID_USAGE_PAGE_GENERIC;
    rawmouse.usUsage = HID_USAGE_GENERIC_MOUSE;
    rawmouse.dwFlags = RIDEV_INPUTSINK;
    rawmouse.hwndTarget = m_handle;
    RegisterRawInputDevices(&rawmouse, 1, sizeof(rawmouse));

    // Center mouse
    SetCursorPos(m_systemMode.getWidth()/2, m_systemMode.getHeight()/2);

    // Enable the window
    UpdateWindow(m_handle);
    #if (VOS_POINTERLOCK == 1)
        ShowCursor(FALSE);
    #else
        ShowCursor(TRUE);
    #endif // VOS_POINTERLOCK
    SetActiveWindow(m_handle);
    SetFocus(m_handle);
    ShowWindow(m_handle, SW_SHOW);
    m_hasFocus = true;

    // Fullscreen
    /*DEVMODE devMode;
    devMode.dmSize = sizeof(DEVMODE);
    devMode.dmPelsWidth = 1920;
    devMode.dmPelsHeight = 1080;
    devMode.dmBitsPerPel = 32;
    devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
    if (ChangeDisplaySettings(
        &devMode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
    {
        return false;
    }
    SetWindowLong(
        m_handle, GWL_STYLE, WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN
    );
    SetWindowLong(m_handle, GWL_EXSTYLE, WS_EX_APPWINDOW);
    SetWindowPos(m_handle, HWND_TOP, 0, 0, 1920, 1080, SWP_FRAMECHANGED);
    ShowWindow(m_handle, SW_SHOWNORMAL);*/

    // System window successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Close the window                                                          //
////////////////////////////////////////////////////////////////////////////////
void SysWindow::close()
{
    // Destroy the window
    if (m_handle)
    {
        DestroyWindow(m_handle);
    }
    m_handle = 0;

    // Destroy the instance
    if (m_instance)
    {
        UnregisterClass(VOSWindowClassName, m_instance);
    }
    m_instance = 0;

    // Destroy system cursors
    if (m_cursors)
    {
        for (int i = 0; i < SYSCURSOR_CURSORSCOUNT; ++i)
        {
            if (m_cursors[i]) { /*DestroyCursor(m_cursors[i]);*/ }
        }
    }
    m_cursors = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Get window event                                                          //
//  return : True if an event occurred, false otherwise                       //
////////////////////////////////////////////////////////////////////////////////
bool SysWindow::getEvent(SysEvent& event)
{
    // Events processing
    MSG msg;
    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Get event in the FIFO queue
    event.type = SYSEVENT_NONE;
    if (!m_events.empty())
    {
        event = m_events.front();
        m_events.pop();
        return true;
    }

    return false;
}


////////////////////////////////////////////////////////////////////////////////
//  Window static event callback function                                     //
////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK SysWindow::OnEvent(
    HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    // Process event
    GSysWindow.processEvent(msg, wparam, lparam);

    // System cursor event
    if (msg == WM_SETCURSOR)
    {
        if (LOWORD(lparam) == HTCLIENT) { return 0; }
    }

    // System menu event
    if ((msg == WM_SYSCOMMAND) && (wparam == SC_KEYMENU))
    {
        return 0;
    }

    // System close event
    if (msg == WM_CLOSE)
    {
        return 0;
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
        SysEvent event;
        event.type = SYSEVENT_NONE;

        // Event type
        switch (msg)
        {
            // Create window event
            case WM_CREATE:
                event.type = SYSEVENT_CREATED;
                m_events.push(event);
                break;

            // Close window events
            case WM_CLOSE:
                event.type = SYSEVENT_CLOSED;
                m_events.push(event);
                break;

            case WM_QUIT:
                event.type = SYSEVENT_CLOSED;
                m_events.push(event);
                break;

            // Focus events
            case WM_SETFOCUS:
                m_hasFocus = true;
                #if (VOS_POINTERLOCK == 1)
                    ShowCursor(FALSE);
                #endif // VOS_POINTERLOCK
                break;

            case WM_KILLFOCUS:
                m_hasFocus = false;
                #if (VOS_POINTERLOCK == 1)
                    ShowCursor(TRUE);
                #endif // VOS_POINTERLOCK
                break;

            // Keys events
            case WM_KEYDOWN:
            case WM_SYSKEYDOWN:
                event.type = SYSEVENT_KEYPRESSED;
                event.key = transcriptKey(wparam, lparam);
                m_events.push(event);
                break;

            case WM_KEYUP:
            case WM_SYSKEYUP:
                event.type = SYSEVENT_KEYRELEASED;
                event.key = transcriptKey(wparam, lparam);
                m_events.push(event);
                break;

            // Mouse events
            #if (VOS_POINTERLOCK == 0)
                case WM_MOUSEMOVE:
                    event.type = SYSEVENT_MOUSEMOVED;
                    event.mouse.x = GET_X_LPARAM(lparam);
                    event.mouse.y = GET_Y_LPARAM(lparam);
                    m_events.push(event);
                    break;
            #endif // VOS_POINTERLOCK

            // Raw inputs
            case WM_INPUT:
                if (m_hasFocus)
                {
                    UINT dwsize = sizeof(RAWINPUT);
                    static BYTE lpb[sizeof(RAWINPUT)];
                    GetRawInputData(
                        (HRAWINPUT)lparam, RID_INPUT, lpb,
                        &dwsize, sizeof(RAWINPUTHEADER)
                    );
                    RAWINPUT* raw = (RAWINPUT*)lpb;

                    switch (raw->header.dwType)
                    {
                        // Mouse events
                        case RIM_TYPEMOUSE:
                        {
                            // Mouse move event
                            #if (VOS_POINTERLOCK == 1)
                                event.type = SYSEVENT_MOUSEMOVED;
                                event.mouse.x = raw->data.mouse.lLastX;
                                event.mouse.y = raw->data.mouse.lLastY;
                                m_events.push(event);
                                SetCursorPos(
                                    m_systemMode.getWidth()/2,
                                    m_systemMode.getHeight()/2
                                );
                            #endif // VOS_POINTERLOCK

                            // Mouse pressed events
                            if (raw->data.mouse.usButtonFlags &
                                RI_MOUSE_LEFT_BUTTON_DOWN)
                            {
                                event.type = SYSEVENT_MOUSEPRESSED;
                                event.mouse.button = SYSEVENT_MOUSE_LEFT;
                                event.mouse.x = raw->data.mouse.lLastX;
                                event.mouse.y = raw->data.mouse.lLastY;
                                m_events.push(event);
                            }
                            if (raw->data.mouse.usButtonFlags &
                                RI_MOUSE_RIGHT_BUTTON_DOWN)
                            {
                                event.type = SYSEVENT_MOUSEPRESSED;
                                event.mouse.button = SYSEVENT_MOUSE_RIGHT;
                                event.mouse.x = raw->data.mouse.lLastX;
                                event.mouse.y = raw->data.mouse.lLastY;
                                m_events.push(event);
                            }

                            // Mouse released events
                            if (raw->data.mouse.usButtonFlags &
                                RI_MOUSE_LEFT_BUTTON_UP)
                            {
                                event.type = SYSEVENT_MOUSERELEASED;
                                event.mouse.button = SYSEVENT_MOUSE_LEFT;
                                event.mouse.x = raw->data.mouse.lLastX;
                                event.mouse.y = raw->data.mouse.lLastY;
                                m_events.push(event);
                            }
                            if (raw->data.mouse.usButtonFlags &
                                RI_MOUSE_RIGHT_BUTTON_UP)
                            {
                                event.type = SYSEVENT_MOUSERELEASED;
                                event.mouse.button = SYSEVENT_MOUSE_RIGHT;
                                event.mouse.x = raw->data.mouse.lLastX;
                                event.mouse.y = raw->data.mouse.lLastY;
                                m_events.push(event);
                            }

                            // Mouse wheel event
                            if (raw->data.mouse.usButtonFlags & RI_MOUSE_WHEEL)
                            {
                                event.type = SYSEVENT_MOUSEWHEEL;
                                event.mouse.wheel =
                                    (short)raw->data.mouse.usButtonData;
                                m_events.push(event);
                            }
                            break;
                        }

                        default:
                            break;
                    }
                }
                break;

            default:
                break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Transcript key event                                                      //
////////////////////////////////////////////////////////////////////////////////
SysEventKey SysWindow::transcriptKey(WPARAM wparam, LPARAM lparam)
{
    switch (wparam)
    {
        case VK_ESCAPE: return SYSEVENT_KEY_ESCAPE;
        case VK_RETURN: return SYSEVENT_KEY_RETURN;
        case VK_SPACE: return SYSEVENT_KEY_SPACE;
        case VK_BACK: return SYSEVENT_KEY_BACKSPACE;

        case VK_UP: return SYSEVENT_KEY_UP;
        case VK_DOWN: return SYSEVENT_KEY_DOWN;
        case VK_LEFT: return SYSEVENT_KEY_LEFT;
        case VK_RIGHT: return SYSEVENT_KEY_RIGHT;

        case VK_RWIN: return SYSEVENT_KEY_RSYS;
        case VK_LWIN: return SYSEVENT_KEY_LSYS;
        case VK_CONTROL:
        {
            return ((HIWORD(lparam)&KF_EXTENDED) ?
                SYSEVENT_KEY_RCTRL : SYSEVENT_KEY_LCTRL);
        }
        case VK_MENU:
        {
            return ((HIWORD(lparam)&KF_EXTENDED) ?
                SYSEVENT_KEY_RALT : SYSEVENT_KEY_LALT);
        }
        case VK_SHIFT:
        {
            static UINT rshift = MapVirtualKeyW(VK_RSHIFT, MAPVK_VK_TO_VSC);
            return ((((lparam & 0x00FF0000) >> 16) == rshift) ?
                SYSEVENT_KEY_RSHIFT : SYSEVENT_KEY_LSHIFT);
        }
        case VK_TAB: return SYSEVENT_KEY_TAB;

        case VK_F1: return SYSEVENT_KEY_F1;
        case VK_F2: return SYSEVENT_KEY_F2;
        case VK_F3: return SYSEVENT_KEY_F3;
        case VK_F4: return SYSEVENT_KEY_F4;
        case VK_F5: return SYSEVENT_KEY_F5;
        case VK_F6: return SYSEVENT_KEY_F6;
        case VK_F7: return SYSEVENT_KEY_F7;
        case VK_F8: return SYSEVENT_KEY_F8;
        case VK_F9: return SYSEVENT_KEY_F9;
        case VK_F10: return SYSEVENT_KEY_F10;
        case VK_F11: return SYSEVENT_KEY_F11;
        case VK_F12: return SYSEVENT_KEY_F12;
        case VK_F13: return SYSEVENT_KEY_F13;
        case VK_F14: return SYSEVENT_KEY_F14;
        case VK_F15: return SYSEVENT_KEY_F15;

        case 'A': return SYSEVENT_KEY_A;
        case 'B': return SYSEVENT_KEY_B;
        case 'C': return SYSEVENT_KEY_C;
        case 'D': return SYSEVENT_KEY_D;
        case 'E': return SYSEVENT_KEY_E;
        case 'F': return SYSEVENT_KEY_F;
        case 'G': return SYSEVENT_KEY_G;
        case 'H': return SYSEVENT_KEY_H;
        case 'I': return SYSEVENT_KEY_I;
        case 'J': return SYSEVENT_KEY_J;
        case 'K': return SYSEVENT_KEY_K;
        case 'L': return SYSEVENT_KEY_L;
        case 'M': return SYSEVENT_KEY_M;
        case 'N': return SYSEVENT_KEY_N;
        case 'O': return SYSEVENT_KEY_O;
        case 'P': return SYSEVENT_KEY_P;
        case 'Q': return SYSEVENT_KEY_Q;
        case 'R': return SYSEVENT_KEY_R;
        case 'S': return SYSEVENT_KEY_S;
        case 'T': return SYSEVENT_KEY_T;
        case 'U': return SYSEVENT_KEY_U;
        case 'V': return SYSEVENT_KEY_V;
        case 'W': return SYSEVENT_KEY_W;
        case 'X': return SYSEVENT_KEY_X;
        case 'Y': return SYSEVENT_KEY_Y;
        case 'Z': return SYSEVENT_KEY_Z;

        case '0': return SYSEVENT_KEY_0;
        case '1': return SYSEVENT_KEY_1;
        case '2': return SYSEVENT_KEY_2;
        case '3': return SYSEVENT_KEY_3;
        case '4': return SYSEVENT_KEY_4;
        case '5': return SYSEVENT_KEY_5;
        case '6': return SYSEVENT_KEY_6;
        case '7': return SYSEVENT_KEY_7;
        case '8': return SYSEVENT_KEY_8;
        case '9': return SYSEVENT_KEY_9;

        default: return SYSEVENT_KEY_NONE;
    }
}
