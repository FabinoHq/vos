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
//     Event.h : VOS Events management                                        //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_EVENT_HEADER
#define VOS_EVENT_HEADER

    #include "System/System.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Event type enumeration                                                //
    ////////////////////////////////////////////////////////////////////////////
    enum EventType
    {
        EVENT_NONE,
        EVENT_CREATED,
        EVENT_CLOSED,
        EVENT_KEYPRESSED,
        EVENT_KEYRELEASED,
        EVENT_MOUSEMOVED,
        EVENT_MOUSEPRESSED,
        EVENT_MOUSERELEASED,
        EVENT_MOUSEWHEEL
    };

    ////////////////////////////////////////////////////////////////////////////
    //  Event key enumeration                                                 //
    ////////////////////////////////////////////////////////////////////////////
    enum EventKey
    {
        EVENT_KEY_NONE,
        EVENT_KEY_ESCAPE,
        EVENT_KEY_RETURN,
        EVENT_KEY_SPACE,

        EVENT_KEY_UP,
        EVENT_KEY_DOWN,
        EVENT_KEY_LEFT,
        EVENT_KEY_RIGHT,

        EVENT_KEY_F1,
        EVENT_KEY_F2,
        EVENT_KEY_F3,
        EVENT_KEY_F4,
        EVENT_KEY_F5,
        EVENT_KEY_F6,
        EVENT_KEY_F7,
        EVENT_KEY_F8,
        EVENT_KEY_F9,
        EVENT_KEY_F10,
        EVENT_KEY_F11,
        EVENT_KEY_F12,
        EVENT_KEY_F13,
        EVENT_KEY_F14,
        EVENT_KEY_F15,

        EVENT_KEY_A,
        EVENT_KEY_B,
        EVENT_KEY_C,
        EVENT_KEY_D,
        EVENT_KEY_E,
        EVENT_KEY_F,
        EVENT_KEY_G,
        EVENT_KEY_H,
        EVENT_KEY_I,
        EVENT_KEY_J,
        EVENT_KEY_K,
        EVENT_KEY_L,
        EVENT_KEY_M,
        EVENT_KEY_N,
        EVENT_KEY_O,
        EVENT_KEY_P,
        EVENT_KEY_Q,
        EVENT_KEY_R,
        EVENT_KEY_S,
        EVENT_KEY_T,
        EVENT_KEY_U,
        EVENT_KEY_V,
        EVENT_KEY_W,
        EVENT_KEY_X,
        EVENT_KEY_Y,
        EVENT_KEY_Z,

        EVENT_KEY_0,
        EVENT_KEY_1,
        EVENT_KEY_2,
        EVENT_KEY_3,
        EVENT_KEY_4,
        EVENT_KEY_5,
        EVENT_KEY_6,
        EVENT_KEY_7,
        EVENT_KEY_8,
        EVENT_KEY_9
    };

    ////////////////////////////////////////////////////////////////////////////
    //  Event mouse button enumeration                                        //
    ////////////////////////////////////////////////////////////////////////////
    enum EventMouseButton
    {
        EVENT_MOUSE_NONE,
        EVENT_MOUSE_LEFT,
        EVENT_MOUSE_RIGHT,
        EVENT_MOUSE_MIDDLE
    };

    ////////////////////////////////////////////////////////////////////////////
    //  Event mouse struct definition                                         //
    ////////////////////////////////////////////////////////////////////////////
    struct EventMouse
    {
        EventMouseButton    button;
        int                 x;
        int                 y;
        int                 wheel;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  Event struct definition                                               //
    ////////////////////////////////////////////////////////////////////////////
    struct Event
    {
        EventType   type;

        union
        {
            EventKey    key;
            EventMouse  mouse;
        };
    };


#endif // VOS_EVENT_HEADER
