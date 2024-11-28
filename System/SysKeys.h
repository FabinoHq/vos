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
//     System/SysKeys.h : System Keys management                              //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_SYSTEM_SYSKEYS_HEADER
#define VOS_SYSTEM_SYSKEYS_HEADER

    #include "System.h"
    #include "SysEvent.h"
    #include "SysMutex.h"


    ////////////////////////////////////////////////////////////////////////////
    //  SysKeys class definition                                              //
    ////////////////////////////////////////////////////////////////////////////
    class SysKeys
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  SysKeys default constructor                                   //
            ////////////////////////////////////////////////////////////////////
            SysKeys();

            ////////////////////////////////////////////////////////////////////
            //  SysKeys destructor                                            //
            ////////////////////////////////////////////////////////////////////
            ~SysKeys();


            ////////////////////////////////////////////////////////////////////
            //  Key pressed event                                             //
            ////////////////////////////////////////////////////////////////////
            void pressed(const SysEventKey& key);

            ////////////////////////////////////////////////////////////////////
            //  Key released event                                            //
            ////////////////////////////////////////////////////////////////////
            void released(const SysEventKey& key);


            ////////////////////////////////////////////////////////////////////
            //  Sync keys with physics (copy internal states)                 //
            ////////////////////////////////////////////////////////////////////
            void sync();


        private:
            ////////////////////////////////////////////////////////////////////
            //  SysKeys private copy constructor : Not copyable               //
            ////////////////////////////////////////////////////////////////////
            SysKeys(const SysKeys&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  SysKeys private copy operator : Not copyable                  //
            ////////////////////////////////////////////////////////////////////
            SysKeys& operator=(const SysKeys&) = delete;


        private:
            SysMutex        m_mutex;            // Keys mutex
            bool            m_up;               // Internal key up
            bool            m_down;             // Internal key down
            bool            m_left;             // Internal key left
            bool            m_right;            // Internal key right


        public:
            bool            up;                 // Key up
            bool            down;               // Key down
            bool            left;               // Key left
            bool            right;              // Key right
    };


    ////////////////////////////////////////////////////////////////////////////
    //  SysKeys global instance                                               //
    ////////////////////////////////////////////////////////////////////////////
    extern SysKeys GSysKeys;


#endif // VOS_SYSTEM_SYSKEYS_HEADER
