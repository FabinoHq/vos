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
//     System/Lin/SysWindow.cpp : Window management for Linux                 //
////////////////////////////////////////////////////////////////////////////////
#include "SysWindow.h"


////////////////////////////////////////////////////////////////////////////////
//  SysWindow default constructor                                             //
////////////////////////////////////////////////////////////////////////////////
SysWindow::SysWindow() :
m_display(0),
m_handle(0),
m_screen(0),
m_closeMsg(0),
m_width(0),
m_height(0),
m_lastMouseX(0),
m_lastMouseY(0),
m_hiddenCursor(0)
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
        ExposureMask | ButtonPressMask | ButtonReleaseMask |
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

    // Grab mouse pointer
    bool pointerGrabbed = false;
    for (unsigned int i = 0; i < 1000; ++i)
    {
        if (XGrabPointer(m_display, m_handle, True, None, GrabModeAsync,
            GrabModeAsync, m_handle, None, CurrentTime) == GrabSuccess)
        {
            pointerGrabbed = true;
            break;
        }
        else
        {
            SysSleep(0.01);
        }
    }

    if (!pointerGrabbed)
    {
        // Unable to grab the mouse pointer
        SysMessage::box() << "[0x2103] Unable to grab the mouse pointer\n";
        SysMessage::box() << "Mouse pointer must be grabbed";
        return false;
    }

    // Get window center position
    XWindowAttributes xwa;
    XGetWindowAttributes(m_display, m_handle, &xwa);
    int centerX = (xwa.width/2)-xwa.x;
    int centerY = (xwa.height/2)-xwa.y;

    // Center mouse
    XWarpPointer(m_display, m_handle, m_handle, 0, 0, 0, 0, centerX, centerY);

    // Raw mouse initial position
    Window root;
    int mouseX = 0;
    int mouseY = 0;
    unsigned int mask = 0;
    XQueryPointer(
        m_display, m_handle, &root, &root,
        &mouseX, &mouseY, &mouseX, &mouseY, &mask
    );
    m_lastMouseX = mouseX;
    m_lastMouseY = mouseY;

    // Hide mouse cursor
    Pixmap cursorPixmap = XCreatePixmap(m_display, m_handle, 1, 1, 1);
    GC graphicsContext = XCreateGC(m_display, cursorPixmap, 0, 0);
    XDrawPoint(m_display, cursorPixmap, graphicsContext, 0, 0);
    XFreeGC(m_display, graphicsContext);
    XColor color;
    color.flags = DoRed | DoGreen | DoBlue;
    color.red = 0;
    color.blue = 0;
    color.green = 0;
    m_hiddenCursor = XCreatePixmapCursor(
        m_display, cursorPixmap, cursorPixmap, &color, &color, 0, 0
    );
    XDefineCursor(m_display, m_handle, m_hiddenCursor);
    XFreePixmap(m_display, cursorPixmap);

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
        XDestroyWindow(m_display, m_handle);
    }

    if (m_display)
    {
        // Destroy hidden cursor
        XFreeCursor(m_display, m_hiddenCursor);

        // Release the display
        XCloseDisplay(m_display);
    }

    m_handle = 0;
    m_display = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Get window width                                                          //
//  return : Window width                                                     //
////////////////////////////////////////////////////////////////////////////////
int SysWindow::getWidth()
{
    return m_width;
}

////////////////////////////////////////////////////////////////////////////////
//  Get window height                                                         //
//  return : Window height                                                    //
////////////////////////////////////////////////////////////////////////////////
int SysWindow::getHeight()
{
    return m_height;
}

////////////////////////////////////////////////////////////////////////////////
//  Get window event                                                          //
//  return : True if an event occurred, false otherwise                       //
////////////////////////////////////////////////////////////////////////////////
bool SysWindow::getEvent(Event& event)
{
    // Events processing
    XEvent msg;
    while (XPending(m_display))
    {
        XNextEvent(m_display, &msg);
        processEvent(msg);
    }

    // Raw mouse input
    Window root;
    int mouseX = 0;
    int mouseY = 0;
    unsigned int mask = 0;
    XQueryPointer(
        m_display, m_handle, &root, &root,
        &mouseX, &mouseY, &mouseX, &mouseY, &mask
    );

    if ((mouseX != m_lastMouseX) || (mouseY != m_lastMouseY))
    {
        Event rawMouse;
        rawMouse.type = EVENT_MOUSEMOVED;
        rawMouse.mouse.x = mouseX-m_lastMouseX;
        rawMouse.mouse.y = mouseY-m_lastMouseY;
        m_events.push(rawMouse);
    }
    m_lastMouseX = mouseX;
    m_lastMouseY = mouseY;

    // Get window center position
    XWindowAttributes xwa;
    XGetWindowAttributes(m_display, m_handle, &xwa);
    int centerX = (xwa.width/2)-xwa.x;
    int centerY = (xwa.height/2)-xwa.y;

    // Center mouse
    XWarpPointer(m_display, m_handle, m_handle, 0, 0, 0, 0, centerX, centerY);
    XQueryPointer(
        m_display, m_handle, &root, &root,
        &mouseX, &mouseY, &mouseX, &mouseY, &mask
    );
    m_lastMouseX = mouseX;
    m_lastMouseY = mouseY;

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
//  Get window display                                                        //
//  return : Pointer to the window display                                    //
////////////////////////////////////////////////////////////////////////////////
Display* SysWindow::getDisplay()
{
    return m_display;
}

////////////////////////////////////////////////////////////////////////////////
//  Get window handle                                                         //
//  return : Reference to the window handle                                   //
////////////////////////////////////////////////////////////////////////////////
Window& SysWindow::getHandle()
{
    return m_handle;
}


////////////////////////////////////////////////////////////////////////////////
//  Process window events                                                     //
////////////////////////////////////////////////////////////////////////////////
void SysWindow::processEvent(XEvent msg)
{
    if (m_handle)
    {
        Event event;
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

            // Keys events
            case KeyPress:
                event.type = EVENT_KEYPRESSED;
                event.key = transcriptKey(XLookupKeysym(&msg.xkey, 0));
                m_events.push(event);
                break;

            case KeyRelease:
                event.type = EVENT_KEYRELEASED;
                event.key = transcriptKey(XLookupKeysym(&msg.xkey, 0));
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
EventKey SysWindow::transcriptKey(KeySym key)
{
    switch (key)
    {
        case XK_Escape:
            return EVENT_KEY_ESCAPE;

        case XK_Return:
            return EVENT_KEY_RETURN;

        default:
            return EVENT_KEY_NONE;
    }
}
