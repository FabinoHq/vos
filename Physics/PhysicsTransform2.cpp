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
//     Physics/PhysicsTransform2.cpp : 2D physics transformations             //
////////////////////////////////////////////////////////////////////////////////
#include "PhysicsTransform2.h"


////////////////////////////////////////////////////////////////////////////////
//  PhysicsTransform2 default constructor                                     //
////////////////////////////////////////////////////////////////////////////////
PhysicsTransform2::PhysicsTransform2() :
pos(),
prevPos(),
angle(0.0f),
prevAngle(0.0f)
{
	pos.reset();
	prevPos.reset();
}

////////////////////////////////////////////////////////////////////////////////
//  PhysicsTransform2 destructor                                              //
////////////////////////////////////////////////////////////////////////////////
PhysicsTransform2::~PhysicsTransform2()
{
	prevAngle = 0.0f;
	angle = 0.0f;
	prevPos.reset();
	pos.reset();
}


////////////////////////////////////////////////////////////////////////////////
//  Reset physics transformations                                             //
////////////////////////////////////////////////////////////////////////////////
void PhysicsTransform2::reset()
{
	pos.reset();
	prevPos.reset();
	angle = 0.0f;
	prevAngle = 0.0f;
}

////////////////////////////////////////////////////////////////////////////////
//  Precompute physics transforms (thread sync)                               //
////////////////////////////////////////////////////////////////////////////////
void PhysicsTransform2::prephysics(
	const Vector2i& physicsPos, int32_t physicsAngle)
{
	// Store previous physics transformations
	prevPos = pos;
    prevAngle = angle;

    // Convert physics transformations to renderer
    pos.vec[0] = (physicsPos.vec[0]*PhysicsToRenderer);
    pos.vec[1] = (physicsPos.vec[1]*PhysicsToRenderer);
    angle = (physicsAngle*PhysicsAngleToRenderer);
}
