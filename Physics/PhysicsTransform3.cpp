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
//     Physics/PhysicsTransform3.cpp : 3D physics transformations             //
////////////////////////////////////////////////////////////////////////////////
#include "PhysicsTransform3.h"


////////////////////////////////////////////////////////////////////////////////
//  PhysicsTransform3 default constructor                                     //
////////////////////////////////////////////////////////////////////////////////
PhysicsTransform3::PhysicsTransform3() :
pos(),
prevPos(),
angles(),
prevAngles()
{

}

////////////////////////////////////////////////////////////////////////////////
//  PhysicsTransform3 destructor                                              //
////////////////////////////////////////////////////////////////////////////////
PhysicsTransform3::~PhysicsTransform3()
{
    prevAngles.reset();
    angles.reset();
    prevPos.reset();
    pos.reset();
}


////////////////////////////////////////////////////////////////////////////////
//  Reset physics transformations                                             //
////////////////////////////////////////////////////////////////////////////////
void PhysicsTransform3::reset()
{
    pos.reset();
    prevPos.reset();
    angles.reset();
    prevAngles.reset();
}

////////////////////////////////////////////////////////////////////////////////
//  Precompute physics transforms (thread sync)                               //
////////////////////////////////////////////////////////////////////////////////
void PhysicsTransform3::prephysics(
    const Vector3i& physicsPos, const Vector3i& physicsAngles)
{
    // Store previous physics transformations
    prevPos = pos;
    prevAngles = angles;

    // Convert physics transformations to renderer
    pos.vec[0] = (physicsPos.vec[0]*PhysicsToRenderer);
    pos.vec[1] = (physicsPos.vec[1]*PhysicsToRenderer);
    pos.vec[2] = (physicsPos.vec[2]*PhysicsToRenderer);
    angles.vec[0] = (physicsAngles.vec[0]*PhysicsAngleToRenderer);
    angles.vec[1] = (physicsAngles.vec[1]*PhysicsAngleToRenderer);
    angles.vec[2] = (physicsAngles.vec[2]*PhysicsAngleToRenderer);
}
