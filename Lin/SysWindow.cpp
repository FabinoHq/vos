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
//     Lin/SysWindow.cpp : Window management for Linux                        //
////////////////////////////////////////////////////////////////////////////////
#include "SysWindow.h"


////////////////////////////////////////////////////////////////////////////////
//  SysWindow default constructor                                             //
////////////////////////////////////////////////////////////////////////////////
SysWindow::SysWindow() :
m_display(0),
m_handle(0),
m_screen(0),
m_context(0)
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
	// Window default colors
	unsigned long black = 0;
	unsigned long white = 0;

	// Get the system display
	m_display = XOpenDisplay((char*)0);
	if (!m_display)
	{
		// Unable to open the display
		return false;
	}

	// Get the default screen
	m_screen = DefaultScreen(m_display);

	// Get the default colors
	black = BlackPixel(m_display, m_screen);
	white = WhitePixel(m_display, m_screen);

	// Create the window
	m_handle = XCreateSimpleWindow(
		m_display, DefaultRootWindow(m_display),
		0, 0, 1024, 768, 5, white, black
	);
	if (!m_handle)
	{
		// Unable to create the window
		return false;
	}

	// Set window properties
	XSetStandardProperties(m_display, m_handle, "VOS", "VOS", None, 0, 0, 0);

	// Select window inputs
	XSelectInput(
		m_display, m_handle, ExposureMask|ButtonPressMask|KeyPressMask
	);

	// Enable the window
	XClearWindow(m_display, m_handle);
	XMapRaised(m_display, m_handle);
	XFlush(m_display);

	// Create the window context
    return createContext();
}

////////////////////////////////////////////////////////////////////////////////
//  Update the window (swap front and back buffers)                           //
////////////////////////////////////////////////////////////////////////////////
void SysWindow::update()
{

}

////////////////////////////////////////////////////////////////////////////////
//  Close the window                                                          //
////////////////////////////////////////////////////////////////////////////////
void SysWindow::close()
{
	if (m_context)
	{
		// Release the context
		XFreeGC(m_display, m_context);
		m_context = 0;
	}

	if (m_handle)
	{
		// Delete the window
		XDestroyWindow(m_display, m_handle);
		m_handle = 0;
	}

	if (m_display)
	{
		// Release the display
		XCloseDisplay(m_display);
		m_display = 0;
	}
}


////////////////////////////////////////////////////////////////////////////////
//  Get window event                                                          //
//  return : True if an event occurred, false otherwise                       //
////////////////////////////////////////////////////////////////////////////////
bool SysWindow::getEvent(Event& event)
{
    return false;
}


////////////////////////////////////////////////////////////////////////////////
//  Create window context                                                     //
//  return : True if the window context is successfully created               //
////////////////////////////////////////////////////////////////////////////////
bool SysWindow::createContext()
{
	if (!m_display)
	{
		// Invalid display
		return false;
	}

	if (!m_handle)
	{
		// Invalid window handle
		return false;
	}

	// Create the graphics context
	m_context = XCreateGC(m_display, m_handle, 0, 0);
	if (!m_context)
	{
		// Unable to create the graphics context
		return false;
	}

	// Context successfully created
    return true;
}

