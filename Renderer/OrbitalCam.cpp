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
//     Renderer/OrbitalCam.cpp : Free fly camera management                   //
////////////////////////////////////////////////////////////////////////////////
#include "OrbitalCam.h"
#include "Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  OrbitalCam default constructor                                            //
////////////////////////////////////////////////////////////////////////////////
OrbitalCam::OrbitalCam() :
Camera(),
m_target(),
m_cross(),
m_speed(1.0f)
{

}

////////////////////////////////////////////////////////////////////////////////
//  OrbitalCam virtual destructor                                             //
////////////////////////////////////////////////////////////////////////////////
OrbitalCam::~OrbitalCam()
{
    m_speed = 0.0f;
    m_cross.reset();
    m_target.reset();
}


////////////////////////////////////////////////////////////////////////////////
//  Compute orbital camera                                                    //
////////////////////////////////////////////////////////////////////////////////
void OrbitalCam::compute(Renderer& renderer, float frametime)
{
    // Compute orbital camera speed
    float speed = m_speed*frametime;

    // Normalize orbital camera target
    m_target.normalize();

    // Compute orbital camera cross product
    m_cross.crossProduct(m_target, m_upward);
    m_cross.normalize();

    // Compute move states
    if (m_forward)
    {
        // Move forward
        moveZ(-speed);
        m_forward = false;
    }
    if (m_backward)
    {
        // Move backward
        moveZ(speed);
        m_backward = false;
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
//  Set orbital camera target                                                 //
////////////////////////////////////////////////////////////////////////////////
void OrbitalCam::setTarget(const Vector3& target)
{
    m_target.vec[0] = target.vec[0];
    m_target.vec[1] = target.vec[1];
    m_target.vec[2] = target.vec[2];
}

////////////////////////////////////////////////////////////////////////////////
//  Set orbital camera target                                                 //
////////////////////////////////////////////////////////////////////////////////
void OrbitalCam::setTarget(float targetX, float targetY, float targetZ)
{
    m_target.vec[0] = targetX;
    m_target.vec[1] = targetY;
    m_target.vec[2] = targetZ;
}

////////////////////////////////////////////////////////////////////////////////
//  Set orbital camera speed                                                  //
////////////////////////////////////////////////////////////////////////////////
void OrbitalCam::setSpeed(float speed)
{
    m_speed = speed;
}

////////////////////////////////////////////////////////////////////////////////
//  Handle mouse move event                                                   //
////////////////////////////////////////////////////////////////////////////////
void OrbitalCam::mouseMove(float mouseDx, float mouseDy)
{
    // Set orbital camera angles
    m_angles.vec[1] -= mouseDx*OrbitalCameraMouseFactor;
    m_angles.vec[0] -= mouseDy*OrbitalCameraMouseFactor;

    // Clamp X orbital camera angle
    if (m_angles.vec[0] <= OrbitalCameraMinAngle)
    {
        m_angles.vec[0] = OrbitalCameraMinAngle;
    }
    if (m_angles.vec[0] >= OrbitalCameraMaxAngle)
    {
        m_angles.vec[0] = OrbitalCameraMaxAngle;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Handle mouse wheel event                                                  //
////////////////////////////////////////////////////////////////////////////////
void OrbitalCam::mouseWheel(int mouseWheel)
{
    if (mouseWheel > 0)
    {
        // Mouse wheel up
        m_forward = true;
        m_backward = false;
    }
    else if (mouseWheel < 0)
    {
        // Mouse wheel down
        m_backward = true;
        m_forward = false;
    }
}
