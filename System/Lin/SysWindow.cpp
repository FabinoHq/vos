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
//     System/Lin/SysWindow.cpp : Window management for Linux                 //
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
m_display(0),
m_handle(0),
m_screen(0),
m_closeMsg(0),
m_hasFocus(false),
m_width(0),
m_height(0),
m_lastMouseX(0),
m_lastMouseY(0),
m_lastMouseLeft(false),
m_lastMouseRight(false),
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
    // Window close message
    Atom wmCloseMsg = 0;

    // Window default colors
    unsigned long black = 0;
    unsigned long white = 0;

    // Get the system display
    m_display = XOpenDisplay((char*)0);
    if (!m_display)
    {
        // Unable to open the display
        SysMessage::box() << "[0x2101] Unable to open the system display\n";
        SysMessage::box() << "System display must be openable";
        return false;
    }

    // Get the default screen
    m_screen = DefaultScreen(m_display);

    // Get the default colors
    black = BlackPixel(m_display, m_screen);
    white = WhitePixel(m_display, m_screen);

    // Window size
    m_width = 1760;
    m_height = 990;

    // Create the window
    m_handle = XCreateSimpleWindow(
        m_display, DefaultRootWindow(m_display),
        0, 0, m_width, m_height, 5, white, black
    );
    if (!m_handle)
    {
        // Unable to create the system window
        SysMessage::box() << "[0x2102] Unable create the system window\n";
        SysMessage::box() << "System window must be creatable";
        return false;
    }

    // Set window properties
    XSetStandardProperties(m_display, m_handle, "VOS", "VOS", None, 0, 0, 0);

    // Select window inputs
    XSelectInput(
        m_display, m_handle,
        ExposureMask | FocusChangeMask | ButtonPressMask | ButtonReleaseMask |
        KeyPressMask | KeyReleaseMask | StructureNotifyMask
    );

    // Set window delete message
    wmCloseMsg = XInternAtom(m_display, "WM_DELETE_WINDOW", false);
    XSetWMProtocols(m_display, m_handle, &wmCloseMsg, 1);
    m_closeMsg = static_cast<long int>(wmCloseMsg);

    // Enable the window
    XClearWindow(m_display, m_handle);
    XMapRaised(m_display, m_handle);
    XFlush(m_display);
    m_hasFocus = true;

    // Grab mouse pointer
    #if (VOS_POINTERLOCK == 1)
        for (unsigned int i = 0; i < SysWindowGrabPointerAttempts; ++i)
        {
            if (XGrabPointer(m_display, m_handle, True, None, GrabModeAsync,
                GrabModeAsync, m_handle, None, CurrentTime) == GrabSuccess)
            {
                break;
            }
            else
            {
                SysSleep(0.01);
            }
        }
    #endif // VOS_POINTERLOCK

    // Get window center position
    XWindowAttributes xwa;
    XGetWindowAttributes(m_display, m_handle, &xwa);
    int centerX = (xwa.width/2)-xwa.x;
    int centerY = (xwa.height/2)-xwa.y;

    // Center mouse
    XWarpPointer(m_display, None, m_handle, 0, 0, 0, 0, centerX, centerY);

    // Raw mouse initial state
    Window root;
    int rootMouseX = 0;
    int rootMouseY = 0;
    int mouseX = 0;
    int mouseY = 0;
    unsigned int mask = 0;
    XQueryPointer(
        m_display, m_handle, &root, &root,
        &rootMouseX, &rootMouseY, &mouseX, &mouseY, &mask
    );
    m_lastMouseX = mouseX;
    m_lastMouseY = mouseY;
    m_lastMouseLeft = (mask & Button1Mask);
    m_lastMouseRight = (mask & Button3Mask);

    // Allocate system cursors
    m_cursors = new(std::nothrow) Cursor[SYSCURSOR_CURSORSCOUNT];
    if (!m_cursors)
    {
        // Could not allocate system cursors
        return false;
    }

    // Load system cursors
    for (int i = 0; i < SYSCURSOR_CURSORSCOUNT; ++i) { m_cursors[i] = 0; }
    Pixmap cursorPixmap = XCreatePixmap(m_display, m_handle, 1, 1, 1);
    GC graphicsContext = XCreateGC(m_display, cursorPixmap, 0, 0);
    XDrawPoint(m_display, cursorPixmap, graphicsContext, 0, 0);
    XFreeGC(m_display, graphicsContext);
    XColor color;
    color.flags = (DoRed | DoGreen | DoBlue);
    color.red = 0;
    color.blue = 0;
    color.green = 0;
    m_cursors[SYSCURSOR_NONE] = XCreatePixmapCursor(
        m_display, cursorPixmap, cursorPixmap, &color, &color, 0, 0
    );
    XFreePixmap(m_display, cursorPixmap);
    if (!m_cursors[SYSCURSOR_NONE]) { return false; }
    m_cursors[SYSCURSOR_DEFAULT] = None;
    #if (VOS_POINTERLOCK == 0)
        m_cursors[SYSCURSOR_TOPRESIZE] =
            XCreateFontCursor(m_display, XC_top_side);
        if (!m_cursors[SYSCURSOR_TOPRESIZE]) { return false; }
        m_cursors[SYSCURSOR_BOTTOMRESIZE] =
            XCreateFontCursor(m_display, XC_bottom_side);
        if (!m_cursors[SYSCURSOR_BOTTOMRESIZE]) { return false; }
        m_cursors[SYSCURSOR_LEFTRESIZE] =
            XCreateFontCursor(m_display, XC_left_side);
        if (!m_cursors[SYSCURSOR_LEFTRESIZE]) { return false; }
        m_cursors[SYSCURSOR_RIGHTRESIZE] =
            XCreateFontCursor(m_display, XC_right_side);
        if (!m_cursors[SYSCURSOR_RIGHTRESIZE]) { return false; }
        m_cursors[SYSCURSOR_TOPLEFTRESIZE] =
            XCreateFontCursor(m_display, XC_top_left_corner);
        if (!m_cursors[SYSCURSOR_TOPLEFTRESIZE]) { return false; }
        m_cursors[SYSCURSOR_TOPRIGHTRESIZE] =
            XCreateFontCursor(m_display, XC_top_right_corner);
        if (!m_cursors[SYSCURSOR_TOPRIGHTRESIZE]) { return false; }
        m_cursors[SYSCURSOR_BOTTOMLEFTRESIZE] =
            XCreateFontCursor(m_display, XC_bottom_left_corner);
        if (!m_cursors[SYSCURSOR_BOTTOMLEFTRESIZE]) { return false; }
        m_cursors[SYSCURSOR_BOTTOMRIGHTRESIZE] =
            XCreateFontCursor(m_display, XC_bottom_right_corner);
        if (!m_cursors[SYSCURSOR_BOTTOMRIGHTRESIZE]) { return false; }
    #endif // VOS_POINTERLOCK

    // Hide mouse cursor
    #if (VOS_POINTERLOCK == 1)
        XDefineCursor(m_display, m_handle, m_cursors[SYSCURSOR_NONE]);
    #endif // VOS_POINTERLOCK

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
        XDestroyWindow(m_display, m_handle);
    }
    m_handle = 0;

    if (m_display)
    {
        // Destroy system cursors
        if (m_cursors)
        {
            for (int i = 0; i < SYSCURSOR_CURSORSCOUNT; ++i)
            {
                if (m_cursors[i]) { XFreeCursor(m_display, m_cursors[i]); }
            }
            delete[] m_cursors;
        }
        m_cursors = 0;

        // Release the display
        XCloseDisplay(m_display);
    }
    m_display = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Get window event                                                          //
//  return : True if an event occurred, false otherwise                       //
////////////////////////////////////////////////////////////////////////////////
bool SysWindow::getEvent(SysEvent& event)
{
    // Events processing
    XEvent msg;
    while (XPending(m_display))
    {
        XNextEvent(m_display, &msg);
        processEvent(msg);
    }

    if (m_hasFocus)
    {
        // Raw mouse input
        SysEvent event;
        Window root;
        int rootMouseX = 0;
        int rootMouseY = 0;
        int mouseX = 0;
        int mouseY = 0;
        unsigned int mask = 0;
        XQueryPointer(
            m_display, m_handle, &root, &root,
            &rootMouseX, &rootMouseY, &mouseX, &mouseY, &mask
        );

        #if (VOS_POINTERLOCK == 1)
            // Get window center position
            XWindowAttributes xwa;
            XGetWindowAttributes(m_display, m_handle, &xwa);
            int centerX = (xwa.width/2)-xwa.x;
            int centerY = (xwa.height/2)-xwa.y;

            if ((mouseX != centerX) || (mouseY != centerY))
            {
                // Mouse move event
                event.type = EVENT_MOUSEMOVED;
                event.mouse.x = mouseX-centerX;
                event.mouse.y = mouseY-centerY;
                m_events.push(event);

                // Center mouse
                XWarpPointer(
                    m_display, None, m_handle, 0, 0, 0, 0, centerX, centerY
                );
                XFlush(m_display);
            }
        #else
            // Mouse move event
            if ((mouseX != m_lastMouseX) || (mouseY != m_lastMouseY))
            {
                event.type = EVENT_MOUSEMOVED;
                event.mouse.x = mouseX;
                event.mouse.y = mouseY;
                m_events.push(event);

                m_lastMouseX = mouseX;
                m_lastMouseY = mouseY;
                XFlush(m_display);
            }
        #endif // VOS_POINTERLOCK

        // Mouse buttons
        if (mask & Button1Mask)
        {
            if (!m_lastMouseLeft)
            {
                // Left mouse button pressed
                event.type = EVENT_MOUSEPRESSED;
                event.mouse.button = EVENT_MOUSE_LEFT;
                event.mouse.x = mouseX;
                event.mouse.y = mouseY;
                m_events.push(event);
                m_lastMouseLeft = true;
            }
        }
        else
        {
            if (m_lastMouseLeft)
            {
                // Left mouse button released
                event.type = EVENT_MOUSERELEASED;
                event.mouse.button = EVENT_MOUSE_LEFT;
                event.mouse.x = mouseX;
                event.mouse.y = mouseY;
                m_events.push(event);
                m_lastMouseLeft = false;
            }
        }
        if (mask & Button3Mask)
        {
            if (!m_lastMouseRight)
            {
                // Right mouse button pressed
                event.type = EVENT_MOUSEPRESSED;
                event.mouse.button = EVENT_MOUSE_RIGHT;
                event.mouse.x = mouseX;
                event.mouse.y = mouseY;
                m_events.push(event);
                m_lastMouseRight = true;
            }
        }
        else
        {
            if (m_lastMouseRight)
            {
                // Right mouse button released
                event.type = EVENT_MOUSERELEASED;
                event.mouse.button = EVENT_MOUSE_RIGHT;
                event.mouse.x = mouseX;
                event.mouse.y = mouseY;
                m_events.push(event);
                m_lastMouseRight = false;
            }
        }
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
//  Process window events                                                     //
////////////////////////////////////////////////////////////////////////////////
void SysWindow::processEvent(XEvent msg)
{
    if (m_handle)
    {
        SysEvent event;
        event.type = EVENT_NONE;

        // Event type
        switch (msg.type)
        {
            // Close window events
            case ClientMessage:
                if (msg.xclient.data.l[0] == m_closeMsg)
                {
                    event.type = EVENT_CLOSED;
                    m_events.push(event);
                }
                break;

            case DestroyNotify:
                event.type = EVENT_CLOSED;
                m_events.push(event);
                break;

            // Resize window event
            case ConfigureNotify:
                if ((msg.xconfigure.width != m_width) ||
                    (msg.xconfigure.height != m_height))
                {
                    m_width = msg.xconfigure.width;
                    m_height = msg.xconfigure.height;
                }
                break;

            // Focus events
            case FocusIn:
            {
                m_hasFocus = true;
                #if (VOS_POINTERLOCK == 1)
                    XDefineCursor(
                        m_display, m_handle, m_cursors[SYSCURSOR_NONE]
                    );
                    for (unsigned int i = 0;
                        i < SysWindowGrabPointerAttempts; ++i)
                    {
                        if (XGrabPointer(m_display, m_handle, True, None,
                            GrabModeAsync, GrabModeAsync, m_handle,
                            None, CurrentTime) == GrabSuccess)
                        {
                            break;
                        }
                        else
                        {
                            SysSleep(0.01);
                        }
                    }

                    // Get window center position
                    XWindowAttributes xwa;
                    XGetWindowAttributes(m_display, m_handle, &xwa);
                    int centerX = (xwa.width/2)-xwa.x;
                    int centerY = (xwa.height/2)-xwa.y;

                    // Center mouse
                    XWarpPointer(
                        m_display, None, m_handle, 0, 0, 0, 0, centerX, centerY
                    );
                    XFlush(m_display);
                #endif // VOS_POINTERLOCK
                break;
            }

            case FocusOut:
                m_hasFocus = false;
                #if (VOS_POINTERLOCK == 1)
                    XDefineCursor(m_display, m_handle, None);
                    XUngrabPointer(m_display, CurrentTime);
                #endif // VOS_POINTERLOCK
                break;

            // Keys events
            case KeyPress:
            {
                event.type = EVENT_KEYPRESSED;
                for (int i = 0; i < 4; ++i)
                {
                    event.key = transcriptKey(XLookupKeysym(&msg.xkey, i));
                    if (event.key != EVENT_KEY_NONE) break;
                }
                m_events.push(event);
                break;
            }

            case KeyRelease:
            {
                event.type = EVENT_KEYRELEASED;
                for (int i = 0; i < 4; ++i)
                {
                    event.key = transcriptKey(XLookupKeysym(&msg.xkey, i));
                    if (event.key != EVENT_KEY_NONE) break;
                }
                m_events.push(event);
                break;
            }

            // Mouse wheel events
            case ButtonPress:
                switch (msg.xbutton.button)
                {
                    // Mouse wheel up
                    case Button4:
                        event.type = EVENT_MOUSEWHEEL;
                        event.mouse.wheel = 127;
                        m_events.push(event);
                        break;

                    // Mouse wheel down
                    case Button5:
                        event.type = EVENT_MOUSEWHEEL;
                        event.mouse.wheel = -127;
                        m_events.push(event);
                        break;

                    default:
                        break;
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
SysEventKey SysWindow::transcriptKey(KeySym key)
{
    switch (key)
    {
        case XK_Escape: return EVENT_KEY_ESCAPE;
        case XK_Return: case XK_KP_Enter: return EVENT_KEY_RETURN;
        case XK_space: return EVENT_KEY_SPACE;
        case XK_BackSpace: return EVENT_KEY_BACKSPACE;

        case XK_Super_R: return EVENT_KEY_RSYS;
        case XK_Super_L: return EVENT_KEY_LSYS;
        case XK_Control_R: return EVENT_KEY_RCTRL;
        case XK_Control_L: return EVENT_KEY_LCTRL;
        case XK_Alt_R: return EVENT_KEY_RALT;
        case XK_Alt_L: return EVENT_KEY_LALT;
        case XK_Shift_R: return EVENT_KEY_RSHIFT;
        case XK_Shift_L: return EVENT_KEY_LSHIFT;
        case XK_Tab: return EVENT_KEY_TAB;

        case XK_Up: return EVENT_KEY_UP;
        case XK_Down: return EVENT_KEY_DOWN;
        case XK_Left: return EVENT_KEY_LEFT;
        case XK_Right: return EVENT_KEY_RIGHT;

        case XK_F1: return EVENT_KEY_F1;
        case XK_F2: return EVENT_KEY_F2;
        case XK_F3: return EVENT_KEY_F3;
        case XK_F4: return EVENT_KEY_F4;
        case XK_F5: return EVENT_KEY_F5;
        case XK_F6: return EVENT_KEY_F6;
        case XK_F7: return EVENT_KEY_F7;
        case XK_F8: return EVENT_KEY_F8;
        case XK_F9: return EVENT_KEY_F9;
        case XK_F10: return EVENT_KEY_F10;
        case XK_F11: return EVENT_KEY_F11;
        case XK_F12: return EVENT_KEY_F12;
        case XK_F13: return EVENT_KEY_F13;
        case XK_F14: return EVENT_KEY_F14;
        case XK_F15: return EVENT_KEY_F15;

        case XK_A: case XK_a: return EVENT_KEY_A;
        case XK_B: case XK_b: return EVENT_KEY_B;
        case XK_C: case XK_c: return EVENT_KEY_C;
        case XK_D: case XK_d: return EVENT_KEY_D;
        case XK_E: case XK_e: return EVENT_KEY_E;
        case XK_F: case XK_f: return EVENT_KEY_F;
        case XK_G: case XK_g: return EVENT_KEY_G;
        case XK_H: case XK_h: return EVENT_KEY_H;
        case XK_I: case XK_i: return EVENT_KEY_I;
        case XK_J: case XK_j: return EVENT_KEY_J;
        case XK_K: case XK_k: return EVENT_KEY_K;
        case XK_L: case XK_l: return EVENT_KEY_L;
        case XK_M: case XK_m: return EVENT_KEY_M;
        case XK_N: case XK_n: return EVENT_KEY_N;
        case XK_O: case XK_o: return EVENT_KEY_O;
        case XK_P: case XK_p: return EVENT_KEY_P;
        case XK_Q: case XK_q: return EVENT_KEY_Q;
        case XK_R: case XK_r: return EVENT_KEY_R;
        case XK_S: case XK_s: return EVENT_KEY_S;
        case XK_T: case XK_t: return EVENT_KEY_T;
        case XK_U: case XK_u: return EVENT_KEY_U;
        case XK_V: case XK_v: return EVENT_KEY_V;
        case XK_W: case XK_w: return EVENT_KEY_W;
        case XK_X: case XK_x: return EVENT_KEY_X;
        case XK_Y: case XK_y: return EVENT_KEY_Y;
        case XK_Z: case XK_z: return EVENT_KEY_Z;

        case XK_0: return EVENT_KEY_0;
        case XK_1: return EVENT_KEY_1;
        case XK_2: return EVENT_KEY_2;
        case XK_3: return EVENT_KEY_3;
        case XK_4: return EVENT_KEY_4;
        case XK_5: return EVENT_KEY_5;
        case XK_6: return EVENT_KEY_6;
        case XK_7: return EVENT_KEY_7;
        case XK_8: return EVENT_KEY_8;
        case XK_9: return EVENT_KEY_9;

        default: return EVENT_KEY_NONE;
    }
}
