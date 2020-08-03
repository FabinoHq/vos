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
//     System/Lin/SysWindow.h : Window management for Linux                   //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_SYSTEM_LIN_SYSWINDOW_HEADER
#define VOS_SYSTEM_LIN_SYSWINDOW_HEADER

    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <queue>

    #include "SysDisplayMode.h"
    #include "../../Event.h"


    ////////////////////////////////////////////////////////////////////////////
    //  SysWindow class definition                                            //
    ////////////////////////////////////////////////////////////////////////////
    class SysWindow
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  SysWindow default constructor                                 //
            ////////////////////////////////////////////////////////////////////
            SysWindow();

            ////////////////////////////////////////////////////////////////////
            //  SysWindow destructor                                          //
            ////////////////////////////////////////////////////////////////////
            ~SysWindow();


            ////////////////////////////////////////////////////////////////////
            //  Create the window                                             //
            //  return : True if the window is successfully created           //
            ////////////////////////////////////////////////////////////////////
            bool create();

            ////////////////////////////////////////////////////////////////////
            //  Close the window                                              //
            ////////////////////////////////////////////////////////////////////
            void close();


            ////////////////////////////////////////////////////////////////////
            //  Get window event                                              //
            //  return : True if an event occurred, false otherwise           //
            ////////////////////////////////////////////////////////////////////
            bool getEvent(Event& event);


            ////////////////////////////////////////////////////////////////////
            //  Get window display                                            //
            //  return : Pointer to the window display                        //
            ////////////////////////////////////////////////////////////////////
            Display* getDisplay();

            ////////////////////////////////////////////////////////////////////
            //  Get window handle                                             //
            //  return : Reference to the window handle                       //
            ////////////////////////////////////////////////////////////////////
            Window& getHandle();


        private:
            ////////////////////////////////////////////////////////////////////
            //  SysWindow private copy constructor : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            SysWindow(const SysWindow&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  SysWindow private copy operator : Not copyable                //
            ////////////////////////////////////////////////////////////////////
            SysWindow& operator=(const SysWindow&) = delete;


            ////////////////////////////////////////////////////////////////////
            //  Process window events                                         //
            ////////////////////////////////////////////////////////////////////
            void processEvent(XEvent msg);


        private:
            Display*            m_display;      // Display handle
            Window              m_handle;       // Window handle
            int                 m_screen;       // Screen handle
            long int            m_closeMsg;     // Close message

            std::queue<Event>   m_events;       // Events FIFO queue
    };


#endif // VOS_SYSTEM_LIN_SYSWINDOW_HEADER
