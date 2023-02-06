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
//     Renderer/OrbitalCam.cpp : Free fly camera management                   //
////////////////////////////////////////////////////////////////////////////////
#include "OrbitalCam.h"


////////////////////////////////////////////////////////////////////////////////
//  OrbitalCam default constructor                                            //
////////////////////////////////////////////////////////////////////////////////
OrbitalCam::OrbitalCam() :
Camera(),
m_target(),
m_distance(1.0f),
m_speed(1.0f),
m_mousePressed(false),
m_forward(false),
m_backward(false)
{

}

////////////////////////////////////////////////////////////////////////////////
//  OrbitalCam virtual destructor                                             //
////////////////////////////////////////////////////////////////////////////////
OrbitalCam::~OrbitalCam()
{
    m_backward = false;
    m_forward = false;
    m_mousePressed = false;
    m_speed = 0.0f;
    m_distance = 0.0f;
    m_target.reset();
}


////////////////////////////////////////////////////////////////////////////////
//  Compute orbital camera                                                    //
//  return : True if the orbital camera is successfully computed              //
////////////////////////////////////////////////////////////////////////////////
bool OrbitalCam::compute(float ratio, float frametime)
{
    // Compute orbital camera speed
    float speed = m_speed*frametime;

    // Compute move states
    if (m_forward)
    {
        // Move forward
        m_distance -= speed;
        if (m_distance <= OrbitalCameraMinDistance)
        {
            m_distance = OrbitalCameraMinDistance;
        }
        m_forward = false;
    }
    if (m_backward)
    {
        // Move backward
        m_distance += speed;
        if (m_distance >= OrbitalCameraMaxDistance)
        {
            m_distance = OrbitalCameraMaxDistance;
        }
        m_backward = false;
    }

    // Compute camera position
    m_position.vec[0] = std::cos(m_angles.vec[0]);
    m_position.vec[0] *= std::sin(m_angles.vec[1]);
    m_position.vec[1] = std::sin(-m_angles.vec[0]);
    m_position.vec[2] = std::cos(m_angles.vec[0]);
    m_position.vec[2] *= std::cos(m_angles.vec[1]);
    m_position *= m_distance;
    m_position += m_target;

    // Compute projection matrix
    m_projMatrix.setPerspective(m_fovy, ratio, m_nearPlane, m_farPlane);

    // Compute view matrix
    m_matrix.setIdentity();
    m_matrix.rotate(-m_angles);
    m_matrix.translate(-m_position);

    // Compute projview matrix
    m_projViewMatrix.set(m_projMatrix);
    m_projViewMatrix *= m_matrix;

    // Copy matrices data into uniform data
    UniformData uniformData;
    memcpy(
        uniformData.projView, m_projViewMatrix.mat, sizeof(m_projViewMatrix.mat)
    );
    memcpy(
        uniformData.view, m_matrix.mat, sizeof(m_matrix.mat)
    );

    // Update uniform buffer
    if (!m_uniformBuffers[GSwapchain.current].updateBufferVertex(
        &uniformData, sizeof(uniformData)))
    {
        // Could not update uniform buffer
        return false;
    }

    // Orbital camera successfully computed
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Compute orbital camera from another orbital camera                        //
//  return : True if the orbital camera is successfully computed              //
////////////////////////////////////////////////////////////////////////////////
bool OrbitalCam::compute(float ratio, OrbitalCam& orbitalCam)
{
    // Compute projection matrix
    m_projMatrix.setPerspective(m_fovy, ratio, m_nearPlane, m_farPlane);

    // Compute view matrix
    m_matrix.set(orbitalCam.m_matrix);

    // Compute projview matrix
    m_projViewMatrix.set(m_projMatrix);
    m_projViewMatrix *= m_matrix;

    // Copy matrices data into uniform data
    UniformData uniformData;
    memcpy(
        uniformData.projView, m_projViewMatrix.mat, sizeof(m_projViewMatrix.mat)
    );
    memcpy(
        uniformData.view, m_matrix.mat, sizeof(m_matrix.mat)
    );

    // Update uniform buffer
    if (!m_uniformBuffers[GSwapchain.current].updateBufferVertex(
        &uniformData, sizeof(uniformData)))
    {
        // Could not update uniform buffer
        return false;
    }

    // Orbital camera successfully computed
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Set orbital camera distance from target                                   //
////////////////////////////////////////////////////////////////////////////////
void OrbitalCam::setDistance(float distance)
{
    if (m_distance <= OrbitalCameraMinDistance)
    {
        m_distance = OrbitalCameraMinDistance;
    }
    if (m_distance >= OrbitalCameraMaxDistance)
    {
        m_distance = OrbitalCameraMaxDistance;
    }
    m_distance = distance;
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
//  Handle mouse move event                                                   //
////////////////////////////////////////////////////////////////////////////////
void OrbitalCam::mouseMove(float mouseDx, float mouseDy)
{
    // Set orbital camera angles
    if (m_mousePressed)
    {
        m_angles.vec[1] -= mouseDx*OrbitalCameraMouseFactor;
        m_angles.vec[0] -= mouseDy*OrbitalCameraMouseFactor;
    }

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
