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
        SysMessage::box() << "[0x2001] Invalid system display mode\n";
        SysMessage::box() << "Current system display mode must be valid";
        return false;
    }

    // Allocate system cursors
    m_cursors = new (std::nothrow) HCURSOR[SYSCURSOR_CURSORSCOUNT];
    if (!m_cursors)
    {
        // Could not allocate system cursors
        return false;
    }

    // Load system cursors
    m_cursors[SYSCURSOR_NONE] = 0;
    m_cursors[SYSCURSOR_DEFAULT] = LoadCursor(0, IDC_ARROW);
    if (!m_cursors[SYSCURSOR_DEFAULT]) { return false; }
    m_cursors[SYSCURSOR_NS] = LoadCursor(0, IDC_SIZENS);
    if (!m_cursors[SYSCURSOR_NS]) { return false; }
    m_cursors[SYSCURSOR_EW] = LoadCursor(0, IDC_SIZEWE);
    if (!m_cursors[SYSCURSOR_EW]) { return false; }
    m_cursors[SYSCURSOR_NESW] = LoadCursor(0, IDC_SIZENESW);
    if (!m_cursors[SYSCURSOR_NESW]) { return false; }
    m_cursors[SYSCURSOR_NWSE] = LoadCursor(0, IDC_SIZENWSE);
    if (!m_cursors[SYSCURSOR_NWSE]) { return false; }

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
        SysMessage::box() << "[0x2002] Unable to register the window class\n";
        SysMessage::box() << "Window class must be registrable";
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
        SysMessage::box() << "[0x2003] Unable to create the system window\n";
        SysMessage::box() << "System window must be creatable";
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
    for (int i = 0; i < SYSCURSOR_CURSORSCOUNT; ++i)
    {
        if (m_cursors[i]) { /*DestroyCursor(m_cursors[i]);*/ }
    }
    if (m_cursors) { delete[] m_cursors; }
    m_cursors = 0;
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
//  Window static event callback function                                     //
////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK SysWindow::OnEvent(
    HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    // Process event
    GSysWindow.processEvent(msg, wparam, lparam);

    // System cursor event
    #if (VOS_POINTERLOCK == 0)
        if (msg == WM_SETCURSOR)
        {
            // Todo : Side window resize ?
            return 0;
        }
    #endif // VOS_POINTERLOCK

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
                event.type = EVENT_KEYPRESSED;
                event.key = transcriptKey(wparam, lparam);
                m_events.push(event);
                break;

            case WM_KEYUP:
            case WM_SYSKEYUP:
                event.type = EVENT_KEYRELEASED;
                event.key = transcriptKey(wparam, lparam);
                m_events.push(event);
                break;

            // Mouse events
            #if (VOS_POINTERLOCK == 0)
                case WM_MOUSEMOVE:
                    event.type = EVENT_MOUSEMOVED;
                    event.mouse.x = LOWORD(lparam);
                    event.mouse.y = HIWORD(lparam);
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
                                event.type = EVENT_MOUSEMOVED;
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
                                event.type = EVENT_MOUSEPRESSED;
                                event.mouse.button = EVENT_MOUSE_LEFT;
                                event.mouse.x = raw->data.mouse.lLastX;
                                event.mouse.y = raw->data.mouse.lLastY;
                                m_events.push(event);
                            }
                            if (raw->data.mouse.usButtonFlags &
                                RI_MOUSE_RIGHT_BUTTON_DOWN)
                            {
                                event.type = EVENT_MOUSEPRESSED;
                                event.mouse.button = EVENT_MOUSE_RIGHT;
                                event.mouse.x = raw->data.mouse.lLastX;
                                event.mouse.y = raw->data.mouse.lLastY;
                                m_events.push(event);
                            }

                            // Mouse released events
                            if (raw->data.mouse.usButtonFlags &
                                RI_MOUSE_LEFT_BUTTON_UP)
                            {
                                event.type = EVENT_MOUSERELEASED;
                                event.mouse.button = EVENT_MOUSE_LEFT;
                                event.mouse.x = raw->data.mouse.lLastX;
                                event.mouse.y = raw->data.mouse.lLastY;
                                m_events.push(event);
                            }
                            if (raw->data.mouse.usButtonFlags &
                                RI_MOUSE_RIGHT_BUTTON_UP)
                            {
                                event.type = EVENT_MOUSERELEASED;
                                event.mouse.button = EVENT_MOUSE_RIGHT;
                                event.mouse.x = raw->data.mouse.lLastX;
                                event.mouse.y = raw->data.mouse.lLastY;
                                m_events.push(event);
                            }

                            // Mouse wheel event
                            if (raw->data.mouse.usButtonFlags & RI_MOUSE_WHEEL)
                            {
                                event.type = EVENT_MOUSEWHEEL;
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
EventKey SysWindow::transcriptKey(WPARAM wparam, LPARAM lparam)
{
    switch (wparam)
    {
        case VK_ESCAPE: return EVENT_KEY_ESCAPE;
        case VK_RETURN: return EVENT_KEY_RETURN;
        case VK_SPACE: return EVENT_KEY_SPACE;
        case VK_BACK: return EVENT_KEY_BACKSPACE;

        case VK_UP: return EVENT_KEY_UP;
        case VK_DOWN: return EVENT_KEY_DOWN;
        case VK_LEFT: return EVENT_KEY_LEFT;
        case VK_RIGHT: return EVENT_KEY_RIGHT;

        case VK_RWIN: return EVENT_KEY_RSYS;
        case VK_LWIN: return EVENT_KEY_LSYS;
        case VK_CONTROL:
        {
            return ((HIWORD(lparam)&KF_EXTENDED) ?
                EVENT_KEY_RCTRL : EVENT_KEY_LCTRL);
        }
        case VK_MENU:
        {
            return ((HIWORD(lparam)&KF_EXTENDED) ?
                EVENT_KEY_RALT : EVENT_KEY_LALT);
        }
        case VK_SHIFT:
        {
            static UINT rshift = MapVirtualKeyW(VK_RSHIFT, MAPVK_VK_TO_VSC);
            return ((((lparam & 0x00FF0000) >> 16) == rshift) ?
                EVENT_KEY_RSHIFT : EVENT_KEY_LSHIFT);
        }
        case VK_TAB: return EVENT_KEY_TAB;

        case VK_F1: return EVENT_KEY_F1;
        case VK_F2: return EVENT_KEY_F2;
        case VK_F3: return EVENT_KEY_F3;
        case VK_F4: return EVENT_KEY_F4;
        case VK_F5: return EVENT_KEY_F5;
        case VK_F6: return EVENT_KEY_F6;
        case VK_F7: return EVENT_KEY_F7;
        case VK_F8: return EVENT_KEY_F8;
        case VK_F9: return EVENT_KEY_F9;
        case VK_F10: return EVENT_KEY_F10;
        case VK_F11: return EVENT_KEY_F11;
        case VK_F12: return EVENT_KEY_F12;
        case VK_F13: return EVENT_KEY_F13;
        case VK_F14: return EVENT_KEY_F14;
        case VK_F15: return EVENT_KEY_F15;

        case 'A': return EVENT_KEY_A;
        case 'B': return EVENT_KEY_B;
        case 'C': return EVENT_KEY_C;
        case 'D': return EVENT_KEY_D;
        case 'E': return EVENT_KEY_E;
        case 'F': return EVENT_KEY_F;
        case 'G': return EVENT_KEY_G;
        case 'H': return EVENT_KEY_H;
        case 'I': return EVENT_KEY_I;
        case 'J': return EVENT_KEY_J;
        case 'K': return EVENT_KEY_K;
        case 'L': return EVENT_KEY_L;
        case 'M': return EVENT_KEY_M;
        case 'N': return EVENT_KEY_N;
        case 'O': return EVENT_KEY_O;
        case 'P': return EVENT_KEY_P;
        case 'Q': return EVENT_KEY_Q;
        case 'R': return EVENT_KEY_R;
        case 'S': return EVENT_KEY_S;
        case 'T': return EVENT_KEY_T;
        case 'U': return EVENT_KEY_U;
        case 'V': return EVENT_KEY_V;
        case 'W': return EVENT_KEY_W;
        case 'X': return EVENT_KEY_X;
        case 'Y': return EVENT_KEY_Y;
        case 'Z': return EVENT_KEY_Z;

        case '0': return EVENT_KEY_0;
        case '1': return EVENT_KEY_1;
        case '2': return EVENT_KEY_2;
        case '3': return EVENT_KEY_3;
        case '4': return EVENT_KEY_4;
        case '5': return EVENT_KEY_5;
        case '6': return EVENT_KEY_6;
        case '7': return EVENT_KEY_7;
        case '8': return EVENT_KEY_8;
        case '9': return EVENT_KEY_9;

        default: return EVENT_KEY_NONE;
    }
}
