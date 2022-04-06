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
//     Renderer/FreeFlyCam.cpp : Free fly camera management                   //
////////////////////////////////////////////////////////////////////////////////
#include "FreeFlyCam.h"
#include "Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  FreeFlyCam default constructor                                            //
////////////////////////////////////////////////////////////////////////////////
FreeFlyCam::FreeFlyCam() :
Camera(),
m_cross(),
m_speed(1.0f),
m_forward(false),
m_backward(false),
m_leftward(false),
m_rightward(false)
{

}

////////////////////////////////////////////////////////////////////////////////
//  FreeFlyCam virtual destructor                                             //
////////////////////////////////////////////////////////////////////////////////
FreeFlyCam::~FreeFlyCam()
{
    m_rightward = false;
    m_leftward = false;
    m_backward = false;
    m_forward = false;
    m_speed = 0.0f;
    m_cross.reset();
}


////////////////////////////////////////////////////////////////////////////////
//  Compute freefly camera                                                    //
////////////////////////////////////////////////////////////////////////////////
void FreeFlyCam::compute(Renderer& renderer, float frametime)
{
    // Compute freefly camera speed
    float speed = m_speed*frametime;
    float crossSpeed = speed*Math::OneSqrtTwo;

    // Compute freefly camera target
    m_target.vec[0] = std::cos(m_angles.vec[0]);
    m_target.vec[0] *= std::sin(m_angles.vec[1]);
    m_target.vec[1] = std::sin(m_angles.vec[0]);
    m_target.vec[2] = std::cos(m_angles.vec[0]);
    m_target.vec[2] *= std::cos(m_angles.vec[1]);
    m_target.normalize();

    // Compute freefly camera cross product
    m_cross.crossProduct(m_target, m_upward);
    m_cross.normalize();

    // Compute keystates
    if (m_forward && !m_backward && !m_leftward && !m_rightward)
    {
        // Move forward
        m_position.vec[0] -= m_target.vec[0]*speed;
        m_position.vec[1] += m_target.vec[1]*speed;
        m_position.vec[2] -= m_target.vec[2]*speed;
    }
    if (m_forward && m_leftward && m_rightward && !m_backward)
    {
        // Move forward
        m_position.vec[0] -= m_target.vec[0]*speed;
        m_position.vec[1] += m_target.vec[1]*speed;
        m_position.vec[2] -= m_target.vec[2]*speed;
    }
    if (m_backward && !m_forward && !m_leftward && !m_rightward)
    {
        // Move backward
        m_position.vec[0] += m_target.vec[0]*speed;
        m_position.vec[1] -= m_target.vec[1]*speed;
        m_position.vec[2] += m_target.vec[2]*speed;
    }
    if (m_backward && m_leftward && m_rightward && !m_forward)
    {
        // Move backward
        m_position.vec[0] += m_target.vec[0]*speed;
        m_position.vec[1] -= m_target.vec[1]*speed;
        m_position.vec[2] += m_target.vec[2]*speed;
    }
    if (m_leftward && !m_rightward && !m_forward && !m_backward)
    {
        // Move leftward
        m_position.vec[0] -= m_cross.vec[0]*speed;
        m_position.vec[1] += m_cross.vec[1]*speed;
        m_position.vec[2] -= m_cross.vec[2]*speed;
    }
    if (m_leftward && m_forward && m_backward && !m_rightward)
    {
        // Move leftward
        m_position.vec[0] -= m_cross.vec[0]*speed;
        m_position.vec[1] += m_cross.vec[1]*speed;
        m_position.vec[2] -= m_cross.vec[2]*speed;
    }
    if (m_rightward && !m_leftward && !m_forward && !m_backward)
    {
        // Move rightward
        m_position.vec[0] += m_cross.vec[0]*speed;
        m_position.vec[1] -= m_cross.vec[1]*speed;
        m_position.vec[2] += m_cross.vec[2]*speed;
    }
    if (m_rightward && m_forward && m_backward && !m_leftward)
    {
        // Move rightward
        m_position.vec[0] += m_cross.vec[0]*speed;
        m_position.vec[1] -= m_cross.vec[1]*speed;
        m_position.vec[2] += m_cross.vec[2]*speed;
    }
    if (m_forward && m_leftward && !m_backward && !m_rightward)
    {
        // Move forward leftward
        m_position.vec[0] -= m_target.vec[0]*crossSpeed;
        m_position.vec[1] += m_target.vec[1]*crossSpeed;
        m_position.vec[2] -= m_target.vec[2]*crossSpeed;
        m_position.vec[0] -= m_cross.vec[0]*crossSpeed;
        m_position.vec[1] += m_cross.vec[1]*crossSpeed;
        m_position.vec[2] -= m_cross.vec[2]*crossSpeed;
    }
    if (m_forward && m_rightward && !m_backward && !m_leftward)
    {
        // Move forward rightward
        m_position.vec[0] -= m_target.vec[0]*crossSpeed;
        m_position.vec[1] += m_target.vec[1]*crossSpeed;
        m_position.vec[2] -= m_target.vec[2]*crossSpeed;
        m_position.vec[0] += m_cross.vec[0]*crossSpeed;
        m_position.vec[1] -= m_cross.vec[1]*crossSpeed;
        m_position.vec[2] += m_cross.vec[2]*crossSpeed;
    }
    if (m_backward && m_leftward && !m_forward && !m_rightward)
    {
        // Move backward leftward
        m_position.vec[0] += m_target.vec[0]*crossSpeed;
        m_position.vec[1] -= m_target.vec[1]*crossSpeed;
        m_position.vec[2] += m_target.vec[2]*crossSpeed;
        m_position.vec[0] -= m_cross.vec[0]*crossSpeed;
        m_position.vec[1] += m_cross.vec[1]*crossSpeed;
        m_position.vec[2] -= m_cross.vec[2]*crossSpeed;
    }
    if (m_backward && m_rightward && !m_leftward && !m_forward)
    {
        // Move backward rightward
        m_position.vec[0] += m_target.vec[0]*crossSpeed;
        m_position.vec[1] -= m_target.vec[1]*crossSpeed;
        m_position.vec[2] += m_target.vec[2]*crossSpeed;
        m_position.vec[0] += m_cross.vec[0]*crossSpeed;
        m_position.vec[1] -= m_cross.vec[1]*crossSpeed;
        m_position.vec[2] += m_cross.vec[2]*crossSpeed;
    }

    // Compute projection matrix
    m_projMatrix.setPerspective(
        m_fovy, renderer.m_swapchain.ratio, m_nearPlane, m_farPlane
    );

    // Compute view matrix
    m_viewMatrix.setIdentity();
    m_viewMatrix.rotate(-m_angles);
    m_viewMatrix.translate(-m_position);

    // Compute projview matrix
    m_projViewMatrix.set(m_projMatrix);
    m_projViewMatrix *= m_viewMatrix;
}


////////////////////////////////////////////////////////////////////////////////
//  Set freefly camera speed                                                  //
////////////////////////////////////////////////////////////////////////////////
void FreeFlyCam::setSpeed(float speed)
{
    m_speed = speed;
}

////////////////////////////////////////////////////////////////////////////////
//  Set freefly camera forward key state                                      //
////////////////////////////////////////////////////////////////////////////////
void FreeFlyCam::setForward(bool forward)
{
    m_forward = forward;
}

////////////////////////////////////////////////////////////////////////////////
//  Set freefly camera backward key state                                     //
////////////////////////////////////////////////////////////////////////////////
void FreeFlyCam::setBackward(bool backward)
{
    m_backward = backward;
}

////////////////////////////////////////////////////////////////////////////////
//  Set freefly camera leftward key state                                     //
////////////////////////////////////////////////////////////////////////////////
void FreeFlyCam::setLeftward(bool leftward)
{
    m_leftward = leftward;
}

////////////////////////////////////////////////////////////////////////////////
//  Set freefly camera rightward key state                                    //
////////////////////////////////////////////////////////////////////////////////
void FreeFlyCam::setRightward(bool rightward)
{
    m_rightward = rightward;
}

////////////////////////////////////////////////////////////////////////////////
//  Handle mouse move event                                                   //
////////////////////////////////////////////////////////////////////////////////
void FreeFlyCam::mouseMove(float mouseDx, float mouseDy)
{
    // Set freefly camera angles
    m_angles.vec[1] -= mouseDx*FreeflyCameraMouseFactor;
    m_angles.vec[0] -= mouseDy*FreeflyCameraMouseFactor;

    // Clamp X freefly camera angle
    if (m_angles.vec[0] <= FreeflyCameraMinAngle)
    {
        m_angles.vec[0] = FreeflyCameraMinAngle;
    }
    if (m_angles.vec[0] >= FreeflyCameraMaxAngle)
    {
        m_angles.vec[0] = FreeflyCameraMaxAngle;
    }
}
