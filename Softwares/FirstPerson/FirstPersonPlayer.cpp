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
//     Softwares/FirstPerson/FirstPersonPlayer.cpp : FirstPersonPlayer class  //
////////////////////////////////////////////////////////////////////////////////
#include "FirstPersonPlayer.h"


////////////////////////////////////////////////////////////////////////////////
//  FirstPersonPlayer default constructor                                     //
////////////////////////////////////////////////////////////////////////////////
FirstPersonPlayer::FirstPersonPlayer() :
Transform3(),
m_transforms(),
m_boundingPos(),
m_boundingAngles(),
m_physicsTarget(),
m_physicsCross()
{

}

////////////////////////////////////////////////////////////////////////////////
//  FirstPersonPlayer virtual destructor                                      //
////////////////////////////////////////////////////////////////////////////////
FirstPersonPlayer::~FirstPersonPlayer()
{
    m_physicsCross.reset();
    m_physicsTarget.reset();
    m_boundingAngles.reset();
    m_boundingPos.reset();
    m_transforms.reset();
}


////////////////////////////////////////////////////////////////////////////////
//  Init first person player                                                  //
//  return : True if first person player is ready                             //
////////////////////////////////////////////////////////////////////////////////
bool FirstPersonPlayer::init()
{
    // Reset first person player
    m_transforms.reset();
    m_boundingPos.reset();
    m_boundingAngles.reset();
    m_physicsTarget.reset();
    m_physicsCross.reset();

    // First person player is ready
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Precompute first person player physics (thread sync)                      //
////////////////////////////////////////////////////////////////////////////////
void FirstPersonPlayer::prephysics()
{
    // Compute prephysics transformations
    m_transforms.prephysics(m_boundingPos, m_boundingAngles);
}

////////////////////////////////////////////////////////////////////////////////
//  Compute first person player physics (threaded)                            //
////////////////////////////////////////////////////////////////////////////////
void FirstPersonPlayer::physics()
{
    // Compute player angles
    m_boundingAngles.vec[0] = GSysMouse.physicsAngles.vec[1];
    m_boundingAngles.vec[1] = GSysMouse.physicsAngles.vec[0];

    // Compute player target
    m_physicsTarget.vec[0] = static_cast<int32_t>(
        (static_cast<int64_t>(Math::cos(m_boundingAngles.vec[0])) *
        static_cast<int64_t>(Math::sin(m_boundingAngles.vec[1]))) >>
        Math::OneIntShift
    );
    m_physicsTarget.vec[1] = Math::sin(m_boundingAngles.vec[0]);
    m_physicsTarget.vec[2] = static_cast<int32_t>(
        (static_cast<int64_t>(Math::cos(m_boundingAngles.vec[0])) *
        static_cast<int64_t>(Math::cos(m_boundingAngles.vec[1]))) >>
        Math::OneIntShift
    );
    m_physicsTarget.normalize();

    // Compute player cross vector
    m_physicsCross.crossUpward(m_physicsTarget);
    m_physicsCross.normalize();

    // Compute player position
    m_boundingPos.vec[0] += static_cast<int32_t>(
        ((static_cast<int64_t>(m_physicsCross.vec[0]) *
        static_cast<int64_t>(GSysKeys.axis.vec[0])) -
        (static_cast<int64_t>(m_physicsTarget.vec[0]) *
        static_cast<int64_t>(GSysKeys.axis.vec[1]))) >>
        (GSysKeys.shift ? 18 : 22)
    );
    m_boundingPos.vec[1] += static_cast<int32_t>(
        ((static_cast<int64_t>(m_physicsTarget.vec[1]) *
        static_cast<int64_t>(GSysKeys.axis.vec[1])) -
        (static_cast<int64_t>(m_physicsCross.vec[1]) *
        static_cast<int64_t>(GSysKeys.axis.vec[0]))) >>
        (GSysKeys.shift ? 18 : 22)
    );
    m_boundingPos.vec[2] += static_cast<int32_t>(
        ((static_cast<int64_t>(m_physicsCross.vec[2]) *
        static_cast<int64_t>(GSysKeys.axis.vec[0])) -
        (static_cast<int64_t>(m_physicsTarget.vec[2]) *
        static_cast<int64_t>(GSysKeys.axis.vec[1]))) >>
        (GSysKeys.shift ? 18 : 22)
    );
}

////////////////////////////////////////////////////////////////////////////////
//  Precompute first person player renderer interpolations                    //
////////////////////////////////////////////////////////////////////////////////
void FirstPersonPlayer::precompute(float physicstime)
{
    // Precompute transformations
    precomputeTransforms(m_transforms, physicstime);
}

////////////////////////////////////////////////////////////////////////////////
//  Render first person player                                                //
////////////////////////////////////////////////////////////////////////////////
void FirstPersonPlayer::render()
{
    
}
