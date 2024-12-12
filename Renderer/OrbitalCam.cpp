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
//     Renderer/OrbitalCam.cpp : Orbital camera management                    //
////////////////////////////////////////////////////////////////////////////////
#include "OrbitalCam.h"


////////////////////////////////////////////////////////////////////////////////
//  OrbitalCam default constructor                                            //
////////////////////////////////////////////////////////////////////////////////
OrbitalCam::OrbitalCam() :
Camera(),
m_transforms(),
m_boundingPos(),
m_boundingAngles(),
m_physicsTarget(),
m_distance(1)
{

}

////////////////////////////////////////////////////////////////////////////////
//  OrbitalCam virtual destructor                                             //
////////////////////////////////////////////////////////////////////////////////
OrbitalCam::~OrbitalCam()
{
    m_distance = 0;
    m_physicsTarget.reset();
    m_boundingAngles.reset();
    m_boundingPos.reset();
    m_transforms.reset();
}


////////////////////////////////////////////////////////////////////////////////
//  Precompute orbital camera physics (thread sync)                           //
////////////////////////////////////////////////////////////////////////////////
void OrbitalCam::prephysics()
{
    // Compute prephysics transformations
    m_transforms.prephysics(m_boundingPos, m_boundingAngles);
}

////////////////////////////////////////////////////////////////////////////////
//  Compute orbital camera physics (threaded)                                 //
////////////////////////////////////////////////////////////////////////////////
void OrbitalCam::physics()
{
    // Compute orbital camera angles
    m_boundingAngles.vec[0] = GSysMouse.physicsAngles.vec[1];
    m_boundingAngles.vec[1] = GSysMouse.physicsAngles.vec[0];

    // Compute orbital camera position
    m_boundingPos.vec[0] = static_cast<int32_t>(
        (static_cast<int64_t>(Math::cos(m_boundingAngles.vec[0])) *
        static_cast<int64_t>(Math::sin(m_boundingAngles.vec[1]))) >>
        Math::OneIntShift
    );
    m_boundingPos.vec[1] = Math::sin(-m_boundingAngles.vec[0]);
    m_boundingPos.vec[2] = static_cast<int32_t>(
        (static_cast<int64_t>(Math::cos(m_boundingAngles.vec[0])) *
        static_cast<int64_t>(Math::cos(m_boundingAngles.vec[1]))) >>
        Math::OneIntShift
    );
    m_boundingPos *= m_distance;
    m_boundingPos += m_physicsTarget;
}

////////////////////////////////////////////////////////////////////////////////
//  Precompute orbital camera renderer interpolations                         //
////////////////////////////////////////////////////////////////////////////////
void OrbitalCam::precompute(float physicstime)
{
    // Precompute transformations
    precomputeTransforms(m_transforms, physicstime);
}

////////////////////////////////////////////////////////////////////////////////
//  Compute orbital camera                                                    //
//  return : True if the orbital camera is successfully computed              //
////////////////////////////////////////////////////////////////////////////////
bool OrbitalCam::compute(float ratio)
{
    // Compute projection matrix
    m_projMatrix.setPerspective(m_fovy, ratio, m_nearPlane, m_farPlane);

    // Compute view matrix
    m_matrix.setIdentity();
    m_matrix.rotate(-m_angles);
    m_matrix.translate(-m_position);

    // Compute projview matrix
    m_projviewMatrix.set(m_projMatrix);
    m_projviewMatrix *= m_matrix;

    // Copy matrices data into camera uniform data
    CameraUniformData cameraUniformData;
    memcpy(
        cameraUniformData.projview,
        m_projviewMatrix.mat,
        sizeof(m_projviewMatrix.mat)
    );
    memcpy(
        cameraUniformData.view,
        m_matrix.mat,
        sizeof(m_matrix.mat)
    );
    memcpy(
        cameraUniformData.position,
        m_position.vec,
        sizeof(m_position.vec)
    );
    cameraUniformData.align = 0.0f;

    // Update uniform buffer
    if (!m_uniformBuffers[GSwapchain.current].updateBufferVertex(
        &cameraUniformData, sizeof(cameraUniformData)))
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
    // Copy orbital camera parameters
    m_origin = orbitalCam.m_origin;
    m_position = orbitalCam.m_position;
    m_size = orbitalCam.m_size;
    m_angles = orbitalCam.m_angles;

    // Compute projection matrix
    m_projMatrix.setPerspective(m_fovy, ratio, m_nearPlane, m_farPlane);

    // Compute view matrix
    m_matrix.set(orbitalCam.m_matrix);

    // Compute projview matrix
    m_projviewMatrix.set(m_projMatrix);
    m_projviewMatrix *= m_matrix;

    // Copy matrices data into camera uniform data
    CameraUniformData cameraUniformData;
    memcpy(
        cameraUniformData.projview,
        m_projviewMatrix.mat,
        sizeof(m_projviewMatrix.mat)
    );
    memcpy(
        cameraUniformData.view,
        m_matrix.mat,
        sizeof(m_matrix.mat)
    );
    memcpy(
        cameraUniformData.position,
        m_position.vec,
        sizeof(m_position.vec)
    );
    cameraUniformData.align = 0.0f;

    // Update uniform buffer
    if (!m_uniformBuffers[GSwapchain.current].updateBufferVertex(
        &cameraUniformData, sizeof(cameraUniformData)))
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
void OrbitalCam::setDistance(int32_t distance)
{
    m_distance = Math::clamp(
        distance, OrbitalCameraMinDistance, OrbitalCameraMaxDistance
    );
}

////////////////////////////////////////////////////////////////////////////////
//  Set orbital camera target                                                 //
////////////////////////////////////////////////////////////////////////////////
void OrbitalCam::setTarget(const Vector3i& target)
{
    m_physicsTarget = target;
}

////////////////////////////////////////////////////////////////////////////////
//  Set orbital camera target                                                 //
////////////////////////////////////////////////////////////////////////////////
void OrbitalCam::setTarget(int32_t targetX, int32_t targetY, int32_t targetZ)
{
    m_physicsTarget.vec[0] = targetX;
    m_physicsTarget.vec[1] = targetY;
    m_physicsTarget.vec[2] = targetZ;
}
