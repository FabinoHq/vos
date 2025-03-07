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
//     Physics/Collision2.cpp : 2 components collision management             //
////////////////////////////////////////////////////////////////////////////////
#include "Collision2.h"


////////////////////////////////////////////////////////////////////////////////
//  Collision2 default constructor                                            //
////////////////////////////////////////////////////////////////////////////////
Collision2::Collision2() :
collide(false),
position(0, 0),
offset(0, 0),
normal(0, 0),
length(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  Collision2 copy constructor                                               //
////////////////////////////////////////////////////////////////////////////////
Collision2::Collision2(const Collision2& collision2)
{
    collide = collision2.collide;
    position = collision2.position;
    offset = collision2.offset;
    normal = collision2.normal;
    length = collision2.length;
}

////////////////////////////////////////////////////////////////////////////////
//  Collision2 position and offset constructor                                //
////////////////////////////////////////////////////////////////////////////////
Collision2::Collision2(const Vector2i& collisionPosition,
    const Vector2i& collisionOffset)
{
    collide = false;
    position = collisionPosition;
    offset = collisionOffset;
    normal.reset();
    length = offset.squaredLength();
}

////////////////////////////////////////////////////////////////////////////////
//  Collision2 destructor                                                     //
////////////////////////////////////////////////////////////////////////////////
Collision2::~Collision2()
{
    length = 0;
    normal.reset();
    offset.reset();
    position.reset();
    collide = false;
}


////////////////////////////////////////////////////////////////////////////////
//  Reset collision                                                           //
////////////////////////////////////////////////////////////////////////////////
void Collision2::reset()
{
    collide = false;
    position.reset();
    offset.reset();
    normal.reset();
    length = 0;
}

////////////////////////////////////////////////////////////////////////////////
//  Set collision from position and offset                                    //
////////////////////////////////////////////////////////////////////////////////
void Collision2::set(const Vector2i& collisionPosition,
    const Vector2i& collisionOffset)
{
    collide = false;
    position = collisionPosition;
    offset = collisionOffset;
    normal.reset();
    length = offset.squaredLength();
}


////////////////////////////////////////////////////////////////////////////////
//  Collision2 affectation operator                                           //
////////////////////////////////////////////////////////////////////////////////
Collision2& Collision2::operator=(const Collision2& collision2)
{
    collide = collision2.collide;
    position = collision2.position;
    offset = collision2.offset;
    normal = collision2.normal;
    length = collision2.length;
    return *this;
}
