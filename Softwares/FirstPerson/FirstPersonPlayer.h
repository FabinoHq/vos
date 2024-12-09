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
//     Softwares/FirstPerson/FirstPersonPlayer.h : FirstPersonPlayer class    //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_SOFTWARES_FIRSTPERSON_FIRSTPERSONPLAYER_HEADER
#define VOS_SOFTWARES_FIRSTPERSON_FIRSTPERSONPLAYER_HEADER

    #include "../../System/System.h"
    #include "../../System/SysEvent.h"
    #include "../../System/SysMouse.h"
    #include "../../System/SysKeys.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  FirstPersonPlayer class definition                                    //
    ////////////////////////////////////////////////////////////////////////////
    class FirstPersonPlayer
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  FirstPersonPlayer default constructor                         //
            ////////////////////////////////////////////////////////////////////
            FirstPersonPlayer();

            ////////////////////////////////////////////////////////////////////
            //  FirstPersonPlayer destructor                                  //
            ////////////////////////////////////////////////////////////////////
            ~FirstPersonPlayer();


            ////////////////////////////////////////////////////////////////////
            //  Init first person player                                      //
            //  return : True if first person player is ready                 //
            ////////////////////////////////////////////////////////////////////
            bool init();


            ////////////////////////////////////////////////////////////////////
            //  Precompute first person player physics (thread sync)          //
            ////////////////////////////////////////////////////////////////////
            void prephysics();

            ////////////////////////////////////////////////////////////////////
            //  Compute first person player physics (threaded)                //
            ////////////////////////////////////////////////////////////////////
            void physics();

            ////////////////////////////////////////////////////////////////////
            //  Precompute first person player renderer interpolations        //
            ////////////////////////////////////////////////////////////////////
            void precompute(float physicstime);

            ////////////////////////////////////////////////////////////////////
            //  Render first person player                                    //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  FirstPersonPlayer private copy constructor : Not copyable     //
            ////////////////////////////////////////////////////////////////////
            FirstPersonPlayer(const FirstPersonPlayer&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  FirstPersonPlayer private copy operator : Not copyable        //
            ////////////////////////////////////////////////////////////////////
            FirstPersonPlayer& operator=(const FirstPersonPlayer&) = delete;


        private:
    };


#endif // VOS_SOFTWARES_FIRSTPERSON_FIRSTPERSONPLAYER_HEADER
