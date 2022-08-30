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
//     System/Win/SysWindow.h : Window management for Windows                 //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_SYSTEM_WIN_SYSWINDOW_HEADER
#define VOS_SYSTEM_WIN_SYSWINDOW_HEADER

    #include "../System.h"
    #include "../SysMessage.h"
    #include "SysDisplayMode.h"
    #include "../../Event.h"

    #undef UNICODE
    #define UNICODE
    #undef _WINSOCKAPI_
    #define _WINSOCKAPI_
    #include <windows.h>
    #include <hidusage.h>
    #include <queue>


    ////////////////////////////////////////////////////////////////////////////
    //  SysWindow class name                                                  //
    ////////////////////////////////////////////////////////////////////////////
    const wchar_t VOSWindowClassName[] = L"VosWindow";


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
            //  Get window width                                              //
            //  return : Window width                                         //
            ////////////////////////////////////////////////////////////////////
            int getWidth();

            ////////////////////////////////////////////////////////////////////
            //  Get window height                                             //
            //  return : Window height                                        //
            ////////////////////////////////////////////////////////////////////
            int getHeight();

            ////////////////////////////////////////////////////////////////////
            //  Get window event                                              //
            //  return : True if an event occurred, false otherwise           //
            ////////////////////////////////////////////////////////////////////
            bool getEvent(Event& event);


            ////////////////////////////////////////////////////////////////////
            //  Get window instance                                           //
            //  return : Reference to the window instance                     //
            ////////////////////////////////////////////////////////////////////
            HINSTANCE& getInstance();

            ////////////////////////////////////////////////////////////////////
            //  Get window handle                                             //
            //  return : Reference to the window handle                       //
            ////////////////////////////////////////////////////////////////////
            HWND& getHandle();


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
            //  Window static event callback function                         //
            ////////////////////////////////////////////////////////////////////
            static LRESULT CALLBACK OnEvent(
                HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam
            );

            ////////////////////////////////////////////////////////////////////
            //  Process window events                                         //
            ////////////////////////////////////////////////////////////////////
            void processEvent(UINT msg, WPARAM wparam, LPARAM lparam);

            ////////////////////////////////////////////////////////////////////
            //  Transcript key event                                          //
            ////////////////////////////////////////////////////////////////////
            EventKey transcriptKey(WPARAM key);


        private:
            HINSTANCE           m_instance;     // Window instance
            HWND                m_handle;       // Window handle
            bool                m_hasFocus;     // Window has focus

            SysDisplayMode      m_systemMode;   // System display mode
            int                 m_width;        // Window width
            int                 m_height;       // Window height

            std::queue<Event>   m_events;       // Events FIFO queue
    };


#endif // VOS_SYSTEM_WIN_SYSWINDOW_HEADER
