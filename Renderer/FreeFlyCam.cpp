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
//     Renderer/FreeFlyCam.cpp : Free fly camera management                   //
////////////////////////////////////////////////////////////////////////////////
#include "FreeFlyCam.h"


////////////////////////////////////////////////////////////////////////////////
//  FreeFlyCam default constructor                                            //
////////////////////////////////////////////////////////////////////////////////
FreeFlyCam::FreeFlyCam() :
Camera(),
m_transforms(),
m_boundingPos(),
m_boundingAngles(),
m_targetInt(),
m_crossInt()
{

}

////////////////////////////////////////////////////////////////////////////////
//  FreeFlyCam virtual destructor                                             //
////////////////////////////////////////////////////////////////////////////////
FreeFlyCam::~FreeFlyCam()
{
    m_crossInt.reset();
    m_targetInt.reset();
    m_boundingAngles.reset();
    m_boundingPos.reset();
    m_transforms.reset();
}


////////////////////////////////////////////////////////////////////////////////
//  Precompute freefly camera physics (thread sync)                           //
////////////////////////////////////////////////////////////////////////////////
void FreeFlyCam::prephysics()
{
    // Compute prephysics transformations
    m_transforms.prephysics(m_boundingPos, m_boundingAngles);
}

////////////////////////////////////////////////////////////////////////////////
//  Compute freefly camera physics (threaded)                                 //
////////////////////////////////////////////////////////////////////////////////
void FreeFlyCam::physics()
{
    // Compute freefly camera angles
    m_boundingAngles.vec[0] = GSysMouse.physicsAngles.vec[1];
    m_boundingAngles.vec[1] = GSysMouse.physicsAngles.vec[0];

    // Compute freefly camera target
    m_targetInt.vec[0] = static_cast<int32_t>(
        (static_cast<int64_t>(Math::cos(m_boundingAngles.vec[0])) *
        static_cast<int64_t>(Math::sin(m_boundingAngles.vec[1]))) >>
        Math::OneIntShift
    );
    m_targetInt.vec[1] = Math::sin(m_boundingAngles.vec[0]);
    m_targetInt.vec[2] = static_cast<int32_t>(
        (static_cast<int64_t>(Math::cos(m_boundingAngles.vec[0])) *
        static_cast<int64_t>(Math::cos(m_boundingAngles.vec[1]))) >>
        Math::OneIntShift
    );
    m_targetInt.normalize();

    // Compute freefly camera cross vector
    m_crossInt.crossUpward(m_targetInt);
    m_crossInt.normalize();

    // Compute freefly camera position
    m_boundingPos.vec[0] += static_cast<int32_t>(
        ((static_cast<int64_t>(m_crossInt.vec[0]) *
        static_cast<int64_t>(GSysKeys.axis.vec[0])) -
        (static_cast<int64_t>(m_targetInt.vec[0]) *
        static_cast<int64_t>(GSysKeys.axis.vec[1]))) >>
        Math::OneIntShift
    );
    m_boundingPos.vec[1] += static_cast<int32_t>(
        ((static_cast<int64_t>(m_targetInt.vec[1]) *
        static_cast<int64_t>(GSysKeys.axis.vec[1])) -
        (static_cast<int64_t>(m_crossInt.vec[1]) *
        static_cast<int64_t>(GSysKeys.axis.vec[0]))) >>
        Math::OneIntShift
    );
    m_boundingPos.vec[2] += static_cast<int32_t>(
        ((static_cast<int64_t>(m_crossInt.vec[2]) *
        static_cast<int64_t>(GSysKeys.axis.vec[0])) -
        (static_cast<int64_t>(m_targetInt.vec[2]) *
        static_cast<int64_t>(GSysKeys.axis.vec[1]))) >>
        Math::OneIntShift
    );
}

////////////////////////////////////////////////////////////////////////////////
//  Precompute freefly camera renderer interpolations                         //
////////////////////////////////////////////////////////////////////////////////
void FreeFlyCam::precompute(float physicstime)
{
    // Precompute transformations
    precomputeTransforms(m_transforms, physicstime);
}

////////////////////////////////////////////////////////////////////////////////
//  Compute freefly camera                                                    //
//  return : True if the freefly camera is successfully computed              //
////////////////////////////////////////////////////////////////////////////////
bool FreeFlyCam::compute(float ratio)
{
    // Compute freefly camera angles (overwrite interpolations)
    m_angles.vec[1] = GSysMouse.angles.vec[0];
    m_angles.vec[0] = GSysMouse.angles.vec[1];

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

    // Freefly camera successfully computed
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Compute freefly camera from another freefly camera                        //
//  return : True if the freefly camera is successfully computed              //
////////////////////////////////////////////////////////////////////////////////
bool FreeFlyCam::compute(float ratio, FreeFlyCam& freeFlyCam)
{
    // Copy freefly camera parameters
    m_origin = freeFlyCam.m_origin;
    m_position = freeFlyCam.m_position;
    m_size = freeFlyCam.m_size;
    m_angles = freeFlyCam.m_angles;

    // Compute projection matrix
    m_projMatrix.setPerspective(m_fovy, ratio, m_nearPlane, m_farPlane);

    // Compute view matrix
    m_matrix.set(freeFlyCam.m_matrix);

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

    // Freefly camera successfully computed
    return true;
}
