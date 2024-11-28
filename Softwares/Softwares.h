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
//     Softwares/Softwares.h : Softwares management                           //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_SOFTWARES_SOFTWARES_HEADER
#define VOS_SOFTWARES_SOFTWARES_HEADER

    #include "../System/System.h"
    #include "../System/SysEvent.h"
    #include "../System/SysMouse.h"
    #include "../System/SysKeys.h"

    #include "../Renderer/Renderer.h"
    #include "../Physics/Physics.h"

    #include "TopDown/TopDown.h"
    #include "FirstPerson/FirstPerson.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  Softwares main class definition                                       //
    ////////////////////////////////////////////////////////////////////////////
    class Softwares
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Softwares default constructor                                 //
            ////////////////////////////////////////////////////////////////////
            Softwares();

            ////////////////////////////////////////////////////////////////////
            //  Softwares destructor                                          //
            ////////////////////////////////////////////////////////////////////
            ~Softwares();


            ////////////////////////////////////////////////////////////////////
            //  Init softwares                                                //
            //  return : True if softwares are ready, false otherwise         //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Destroy softwares                                             //
            ////////////////////////////////////////////////////////////////////
            void destroy();


            ////////////////////////////////////////////////////////////////////
            //  Compute softwares events                                      //
            ////////////////////////////////////////////////////////////////////
            void events(SysEvent& event);

            ////////////////////////////////////////////////////////////////////
            //  Compute softwares physics (threaded)                          //
            ////////////////////////////////////////////////////////////////////
            void physics();

            ////////////////////////////////////////////////////////////////////
            //  Precompute softwares                                          //
            ////////////////////////////////////////////////////////////////////
            void precompute(float physicstime);

            ////////////////////////////////////////////////////////////////////
            //  Compute softwares logic                                       //
            ////////////////////////////////////////////////////////////////////
            void compute(float frametime);

            ////////////////////////////////////////////////////////////////////
            //  Render softwares                                              //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Softwares private copy constructor : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            Softwares(const Softwares&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Softwares private copy operator : Not copyable                //
            ////////////////////////////////////////////////////////////////////
            Softwares& operator=(const Softwares&) = delete;


        private:
    };


    ////////////////////////////////////////////////////////////////////////////
    //  Softwares global instance                                             //
    ////////////////////////////////////////////////////////////////////////////
    extern Softwares GSoftwares;


#endif // VOS_SOFTWARES_SOFTWARES_HEADER
