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
//     System/SysMouse.h : System Mouse management                            //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_SYSTEM_SYSMOUSE_HEADER
#define VOS_SYSTEM_SYSMOUSE_HEADER

    #include "System.h"
    #include "../Math/Math.h"


    ////////////////////////////////////////////////////////////////////////////
    //  SysMouse class definition                                             //
    ////////////////////////////////////////////////////////////////////////////
    class SysMouse
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  SysMouse default constructor                                  //
            ////////////////////////////////////////////////////////////////////
            SysMouse();

            ////////////////////////////////////////////////////////////////////
            //  SysMouse destructor                                           //
            ////////////////////////////////////////////////////////////////////
            ~SysMouse();


            ////////////////////////////////////////////////////////////////////
            //  Update mouse position                                         //
            ////////////////////////////////////////////////////////////////////
            void update(int x, int y);


        private:
            ////////////////////////////////////////////////////////////////////
            //  SysMouse private copy constructor : Not copyable              //
            ////////////////////////////////////////////////////////////////////
            SysMouse(const SysMouse&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  SysMouse private copy operator : Not copyable                 //
            ////////////////////////////////////////////////////////////////////
            SysMouse& operator=(const SysMouse&) = delete;


        public:
            float           mouseX;             // Mouse X position
            float           mouseY;             // Mouse Y position
            float           deltaX;             // Mouse X delta
            float           deltaY;             // Mouse Y delta
            int             previousX;          // Previous mouse X position
            int             previousY;          // Previous mouse Y position
    };


    ////////////////////////////////////////////////////////////////////////////
    //  SysMouse global instance                                              //
    ////////////////////////////////////////////////////////////////////////////
    extern SysMouse GSysMouse;


#endif // VOS_SYSTEM_SYSMOUSE_HEADER
