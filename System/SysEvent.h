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
//     System/SysEvent.h : System Events management                           //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_SYSTEM_SYSEVENT_HEADER
#define VOS_SYSTEM_SYSEVENT_HEADER

    #include "System.h"


    ////////////////////////////////////////////////////////////////////////////
    //  SysEvent type enumeration                                             //
    ////////////////////////////////////////////////////////////////////////////
    enum SysEventType
    {
        SYSEVENT_NONE = 0,
        SYSEVENT_CREATED = 1,
        SYSEVENT_CLOSED = 2,
        SYSEVENT_KEYPRESSED = 3,
        SYSEVENT_KEYRELEASED = 4,
        SYSEVENT_MOUSEMOVED = 5,
        SYSEVENT_MOUSEPRESSED = 6,
        SYSEVENT_MOUSERELEASED = 7,
        SYSEVENT_MOUSEWHEEL = 8
    };

    ////////////////////////////////////////////////////////////////////////////
    //  SysEvent key enumeration                                              //
    ////////////////////////////////////////////////////////////////////////////
    enum SysEventKey
    {
        SYSEVENT_KEY_NONE = 0,

        SYSEVENT_KEY_ESCAPE = 1,
        SYSEVENT_KEY_RETURN = 2,
        SYSEVENT_KEY_SPACE = 3,
        SYSEVENT_KEY_BACKSPACE = 4,

        SYSEVENT_KEY_RSYS = 5,
        SYSEVENT_KEY_LSYS = 6,
        SYSEVENT_KEY_RCTRL = 7,
        SYSEVENT_KEY_RALT = 8,
        SYSEVENT_KEY_RSHIFT = 9,
        SYSEVENT_KEY_LCTRL = 10,
        SYSEVENT_KEY_LALT = 11,
        SYSEVENT_KEY_LSHIFT = 12,
        SYSEVENT_KEY_TAB = 13,

        SYSEVENT_KEY_UP = 14,
        SYSEVENT_KEY_DOWN = 15,
        SYSEVENT_KEY_LEFT = 16,
        SYSEVENT_KEY_RIGHT = 17,

        SYSEVENT_KEY_F1 = 18,
        SYSEVENT_KEY_F2 = 19,
        SYSEVENT_KEY_F3 = 20,
        SYSEVENT_KEY_F4 = 21,
        SYSEVENT_KEY_F5 = 22,
        SYSEVENT_KEY_F6 = 23,
        SYSEVENT_KEY_F7 = 24,
        SYSEVENT_KEY_F8 = 25,
        SYSEVENT_KEY_F9 = 26,
        SYSEVENT_KEY_F10 = 27,
        SYSEVENT_KEY_F11 = 28,
        SYSEVENT_KEY_F12 = 29,
        SYSEVENT_KEY_F13 = 30,
        SYSEVENT_KEY_F14 = 31,
        SYSEVENT_KEY_F15 = 32,

        SYSEVENT_KEY_A = 33,
        SYSEVENT_KEY_B = 34,
        SYSEVENT_KEY_C = 35,
        SYSEVENT_KEY_D = 36,
        SYSEVENT_KEY_E = 37,
        SYSEVENT_KEY_F = 38,
        SYSEVENT_KEY_G = 39,
        SYSEVENT_KEY_H = 40,
        SYSEVENT_KEY_I = 41,
        SYSEVENT_KEY_J = 42,
        SYSEVENT_KEY_K = 43,
        SYSEVENT_KEY_L = 44,
        SYSEVENT_KEY_M = 45,
        SYSEVENT_KEY_N = 46,
        SYSEVENT_KEY_O = 47,
        SYSEVENT_KEY_P = 48,
        SYSEVENT_KEY_Q = 49,
        SYSEVENT_KEY_R = 50,
        SYSEVENT_KEY_S = 51,
        SYSEVENT_KEY_T = 52,
        SYSEVENT_KEY_U = 53,
        SYSEVENT_KEY_V = 54,
        SYSEVENT_KEY_W = 55,
        SYSEVENT_KEY_X = 56,
        SYSEVENT_KEY_Y = 57,
        SYSEVENT_KEY_Z = 58,

        SYSEVENT_KEY_0 = 59,
        SYSEVENT_KEY_1 = 60,
        SYSEVENT_KEY_2 = 61,
        SYSEVENT_KEY_3 = 62,
        SYSEVENT_KEY_4 = 63,
        SYSEVENT_KEY_5 = 64,
        SYSEVENT_KEY_6 = 65,
        SYSEVENT_KEY_7 = 66,
        SYSEVENT_KEY_8 = 67,
        SYSEVENT_KEY_9 = 68
    };

    ////////////////////////////////////////////////////////////////////////////
    //  SysEvent mouse button enumeration                                     //
    ////////////////////////////////////////////////////////////////////////////
    enum SysEventMouseButton
    {
        SYSEVENT_MOUSE_NONE = 0,
        SYSEVENT_MOUSE_LEFT = 1,
        SYSEVENT_MOUSE_RIGHT = 2,
        SYSEVENT_MOUSE_MIDDLE = 3
    };

    ////////////////////////////////////////////////////////////////////////////
    //  SysEvent mouse struct definition                                      //
    ////////////////////////////////////////////////////////////////////////////
    struct SysEventMouse
    {
        SysEventMouseButton     button;
        int                     x;
        int                     y;
        int                     wheel;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  SysEvent struct definition                                            //
    ////////////////////////////////////////////////////////////////////////////
    struct SysEvent
    {
        SysEventType    type;

        union
        {
            SysEventKey     key;
            SysEventMouse   mouse;
        };
    };


#endif // VOS_SYSTEM_SYSEVENT_HEADER
