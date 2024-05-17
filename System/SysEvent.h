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
        EVENT_NONE = 0,
        EVENT_CREATED = 1,
        EVENT_CLOSED = 2,
        EVENT_KEYPRESSED = 3,
        EVENT_KEYRELEASED = 4,
        EVENT_MOUSEMOVED = 5,
        EVENT_MOUSEPRESSED = 6,
        EVENT_MOUSERELEASED = 7,
        EVENT_MOUSEWHEEL = 8
    };

    ////////////////////////////////////////////////////////////////////////////
    //  SysEvent key enumeration                                              //
    ////////////////////////////////////////////////////////////////////////////
    enum SysEventKey
    {
        EVENT_KEY_NONE = 0,

        EVENT_KEY_ESCAPE = 1,
        EVENT_KEY_RETURN = 2,
        EVENT_KEY_SPACE = 3,
        EVENT_KEY_BACKSPACE = 4,

        EVENT_KEY_RSYS = 5,
        EVENT_KEY_LSYS = 6,
        EVENT_KEY_RCTRL = 7,
        EVENT_KEY_RALT = 8,
        EVENT_KEY_RSHIFT = 9,
        EVENT_KEY_LCTRL = 10,
        EVENT_KEY_LALT = 11,
        EVENT_KEY_LSHIFT = 12,
        EVENT_KEY_TAB = 13,

        EVENT_KEY_UP = 14,
        EVENT_KEY_DOWN = 15,
        EVENT_KEY_LEFT = 16,
        EVENT_KEY_RIGHT = 17,

        EVENT_KEY_F1 = 18,
        EVENT_KEY_F2 = 19,
        EVENT_KEY_F3 = 20,
        EVENT_KEY_F4 = 21,
        EVENT_KEY_F5 = 22,
        EVENT_KEY_F6 = 23,
        EVENT_KEY_F7 = 24,
        EVENT_KEY_F8 = 25,
        EVENT_KEY_F9 = 26,
        EVENT_KEY_F10 = 27,
        EVENT_KEY_F11 = 28,
        EVENT_KEY_F12 = 29,
        EVENT_KEY_F13 = 30,
        EVENT_KEY_F14 = 31,
        EVENT_KEY_F15 = 32,

        EVENT_KEY_A = 33,
        EVENT_KEY_B = 34,
        EVENT_KEY_C = 35,
        EVENT_KEY_D = 36,
        EVENT_KEY_E = 37,
        EVENT_KEY_F = 38,
        EVENT_KEY_G = 39,
        EVENT_KEY_H = 40,
        EVENT_KEY_I = 41,
        EVENT_KEY_J = 42,
        EVENT_KEY_K = 43,
        EVENT_KEY_L = 44,
        EVENT_KEY_M = 45,
        EVENT_KEY_N = 46,
        EVENT_KEY_O = 47,
        EVENT_KEY_P = 48,
        EVENT_KEY_Q = 49,
        EVENT_KEY_R = 50,
        EVENT_KEY_S = 51,
        EVENT_KEY_T = 52,
        EVENT_KEY_U = 53,
        EVENT_KEY_V = 54,
        EVENT_KEY_W = 55,
        EVENT_KEY_X = 56,
        EVENT_KEY_Y = 57,
        EVENT_KEY_Z = 58,

        EVENT_KEY_0 = 59,
        EVENT_KEY_1 = 60,
        EVENT_KEY_2 = 61,
        EVENT_KEY_3 = 62,
        EVENT_KEY_4 = 63,
        EVENT_KEY_5 = 64,
        EVENT_KEY_6 = 65,
        EVENT_KEY_7 = 66,
        EVENT_KEY_8 = 67,
        EVENT_KEY_9 = 68
    };

    ////////////////////////////////////////////////////////////////////////////
    //  SysEvent mouse button enumeration                                     //
    ////////////////////////////////////////////////////////////////////////////
    enum SysEventMouseButton
    {
        EVENT_MOUSE_NONE = 0,
        EVENT_MOUSE_LEFT = 1,
        EVENT_MOUSE_RIGHT = 2,
        EVENT_MOUSE_MIDDLE = 3
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
