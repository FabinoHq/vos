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
//     System/SysKeys.cpp : System Keys management                            //
////////////////////////////////////////////////////////////////////////////////
#include "SysKeys.h"


////////////////////////////////////////////////////////////////////////////////
//  SysKeys global instance                                                   //
////////////////////////////////////////////////////////////////////////////////
SysKeys GSysKeys = SysKeys();


////////////////////////////////////////////////////////////////////////////////
//  SysKeys default constructor                                               //
////////////////////////////////////////////////////////////////////////////////
SysKeys::SysKeys() :
m_mutex(),
m_up(false),
m_down(false),
m_left(false),
m_right(false),
m_shift(false),
axis(),
up(false),
down(false),
left(false),
right(false),
shift(false)
{

}

////////////////////////////////////////////////////////////////////////////////
//  SysKeys destructor                                                        //
////////////////////////////////////////////////////////////////////////////////
SysKeys::~SysKeys()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Key pressed event                                                         //
////////////////////////////////////////////////////////////////////////////////
void SysKeys::pressed(const SysEventKey& key)
{
    // Compute key pressed event
    m_mutex.lock();
    switch (key)
    {
        case SYSEVENT_KEY_UP: m_up = true; break;
        case SYSEVENT_KEY_DOWN: m_down = true; break;
        case SYSEVENT_KEY_LEFT: m_left = true; break;
        case SYSEVENT_KEY_RIGHT: m_right = true; break;
        case SYSEVENT_KEY_Z: m_up = true; break;
        case SYSEVENT_KEY_S: m_down = true; break;
        case SYSEVENT_KEY_Q: m_left = true; break;
        case SYSEVENT_KEY_D: m_right = true; break;
        case SYSEVENT_KEY_LSHIFT: m_shift = true; break;
        case SYSEVENT_KEY_RSHIFT: m_shift = true; break;
        default: break;
    }
    m_mutex.unlock();
}

////////////////////////////////////////////////////////////////////////////////
//  Key released event                                                        //
////////////////////////////////////////////////////////////////////////////////
void SysKeys::released(const SysEventKey& key)
{
    // Compute key released event
    m_mutex.lock();
    switch (key)
    {
        case SYSEVENT_KEY_UP: m_up = false; break;
        case SYSEVENT_KEY_DOWN: m_down = false; break;
        case SYSEVENT_KEY_LEFT: m_left = false; break;
        case SYSEVENT_KEY_RIGHT: m_right = false; break;
        case SYSEVENT_KEY_Z: m_up = false; break;
        case SYSEVENT_KEY_S: m_down = false; break;
        case SYSEVENT_KEY_Q: m_left = false; break;
        case SYSEVENT_KEY_D: m_right = false; break;
        case SYSEVENT_KEY_LSHIFT: m_shift = false; break;
        case SYSEVENT_KEY_RSHIFT: m_shift = false; break;
        default: break;
    }
    m_mutex.unlock();
}


////////////////////////////////////////////////////////////////////////////////
//  Sync keys with physics (copy internal states)                             //
////////////////////////////////////////////////////////////////////////////////
void SysKeys::sync()
{
    // Copy keys internal states
    m_mutex.lock();
    up = m_up;
    down = m_down;
    left = m_left;
    right = m_right;
    shift = m_shift;
    m_mutex.unlock();

    // Compute input axis
    computeAxis();
}


////////////////////////////////////////////////////////////////////////////////
//  Compute input axis from keys states                                       //
////////////////////////////////////////////////////////////////////////////////
void SysKeys::computeAxis()
{
    // Compute input axis
    axis.reset();
    if (up && !down && !left && !right)
    {
        // Up
        axis.vec[1] = Math::OneInt;
    }
    else if (!up && down && !left && !right)
    {
        // Down
        axis.vec[1] = -Math::OneInt;
    }
    else if (!up && !down && left && !right)
    {
        // Left
        axis.vec[0] = -Math::OneInt;
    }
    else if (!up && !down && !left && right)
    {
        // Right
        axis.vec[0] = Math::OneInt;
    }
    else if (up && !down && left && right)
    {
        // Up (left and right pressed)
        axis.vec[1] = Math::OneInt;
    }
    else if (!up && down && left && right)
    {
        // Down (left and right pressed)
        axis.vec[1] = -Math::OneInt;
    }
    else if (up && down && left && !right)
    {
        // Left (up and down pressed)
        axis.vec[0] = -Math::OneInt;
    }
    else if (up && down && !left && right)
    {
        // Right (up and down pressed)
        axis.vec[0] = Math::OneInt;
    }
    else if (up && !down && left && !right)
    {
        // Up left
        axis.vec[0] = -Math::InvSqrtTwoInt;
        axis.vec[1] = Math::InvSqrtTwoInt;
    }
    else if (up && !down && !left && right)
    {
        // Up right
        axis.vec[0] = Math::InvSqrtTwoInt;
        axis.vec[1] = Math::InvSqrtTwoInt;
    }
    else if (!up && down && left && !right)
    {
        // Down left
        axis.vec[0] = -Math::InvSqrtTwoInt;
        axis.vec[1] = -Math::InvSqrtTwoInt;
    }
    else if (!up && down && !left && right)
    {
        // Down right
        axis.vec[0] = Math::InvSqrtTwoInt;
        axis.vec[1] = -Math::InvSqrtTwoInt;
    }
}
