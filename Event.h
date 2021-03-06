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
        EVENT_KEY_RETURN
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
