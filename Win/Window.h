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
//     Win/Window.h : Window management for Windows                           //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_WIN_WINDOW_HEADER
#define VOS_WIN_WINDOW_HEADER

    #include <windows.h>

    #include "DisplayMode.h"


    // Window class name
    const wchar_t VOSWindowClassName[] = L"VosWindow";


    ////////////////////////////////////////////////////////////////////////////
    //  Window class definition                                               //
    ////////////////////////////////////////////////////////////////////////////
    class Window
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Window default constructor                                    //
            ////////////////////////////////////////////////////////////////////
            Window();

            ////////////////////////////////////////////////////////////////////
            //  Window destructor                                             //
            ////////////////////////////////////////////////////////////////////
            ~Window();


            ////////////////////////////////////////////////////////////////////
            //  Create the window                                             //
            //  return : True if the window is successfully created           //
            ////////////////////////////////////////////////////////////////////
            bool create();

            ////////////////////////////////////////////////////////////////////
            //  Update the window (swap front and back buffers)               //
            ////////////////////////////////////////////////////////////////////
            void udpate();

            ////////////////////////////////////////////////////////////////////
            //  Close the window                                              //
            ////////////////////////////////////////////////////////////////////
            void close();

        private:
            ////////////////////////////////////////////////////////////////////
            //  Window private copy constructor : Not copyable                //
            ////////////////////////////////////////////////////////////////////
            Window(const Window&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Window private copy operator : Not copyable                   //
            ////////////////////////////////////////////////////////////////////
            Window& operator=(const Window&) = delete;


            ////////////////////////////////////////////////////////////////////
            //  Create window context                                         //
            //  return : True if the window context is successfully created   //
            ////////////////////////////////////////////////////////////////////
            bool createContext();

            ////////////////////////////////////////////////////////////////////
            //  Window static event callback function                         //
            ////////////////////////////////////////////////////////////////////
            static LRESULT CALLBACK OnEvent(
                HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam
            );

        private:
            HINSTANCE   m_instance;     // Window instance
            HWND        m_handle;       // Window handle
            HDC         m_device;       // Window device
            HGLRC       m_context;      // Window context
    };


#endif // VOS_WIN_WINDOW_HEADER
