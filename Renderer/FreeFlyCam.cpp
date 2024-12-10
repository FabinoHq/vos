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
m_cross()
{

}

////////////////////////////////////////////////////////////////////////////////
//  FreeFlyCam virtual destructor                                             //
////////////////////////////////////////////////////////////////////////////////
FreeFlyCam::~FreeFlyCam()
{
    m_cross.reset();
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
    m_boundingAngles.vec[0] = GSysMouse.anglesInt.vec[1];
    m_boundingAngles.vec[1] = GSysMouse.anglesInt.vec[0];

    // Compute freefly camera target
    Vector3i target;
    int64_t targetX = Math::cos(m_boundingAngles.vec[0]);
    int64_t targetZ = Math::cos(m_boundingAngles.vec[0]);
    targetX *= Math::sin(m_boundingAngles.vec[1]);
    targetX >>= Math::OneIntShift;
    targetZ *= Math::cos(m_boundingAngles.vec[1]);
    targetZ >>= Math::OneIntShift;
    target.vec[0] = static_cast<int32_t>(targetX);
    target.vec[1] = Math::sin(m_boundingAngles.vec[0]);
    target.vec[2] = static_cast<int32_t>(targetZ);
    target.normalize();

    // Compute freefly camera cross product
    Vector3i cross;
    cross.crossUpward(target);

    // Compute freefly camera speed
    int32_t speed = (Math::OneInt >> 10);
    int32_t crossSpeed = (Math::InvSqrtTwoInt >> 10);

    // Compute keystates
    if (GSysKeys.up && !GSysKeys.down && !GSysKeys.left && !GSysKeys.right)
    {
        // Move forward
        m_boundingPos.vec[0] -= ((target.vec[0] * speed) >> 10);
        m_boundingPos.vec[1] += ((target.vec[1] * speed) >> 10);
        m_boundingPos.vec[2] -= ((target.vec[2] * speed) >> 10);
    }
    if (GSysKeys.up && GSysKeys.left && GSysKeys.right && !GSysKeys.down)
    {
        // Move forward
        m_boundingPos.vec[0] -= ((target.vec[0] * speed) >> 10);
        m_boundingPos.vec[1] += ((target.vec[1] * speed) >> 10);
        m_boundingPos.vec[2] -= ((target.vec[2] * speed) >> 10);
    }
    if (GSysKeys.down && !GSysKeys.up && !GSysKeys.left && !GSysKeys.right)
    {
        // Move backward
        m_boundingPos.vec[0] += ((target.vec[0] * speed) >> 10);
        m_boundingPos.vec[1] -= ((target.vec[1] * speed) >> 10);
        m_boundingPos.vec[2] += ((target.vec[2] * speed) >> 10);
    }
    if (GSysKeys.down && GSysKeys.left && GSysKeys.right && !GSysKeys.up)
    {
        // Move backward
        m_boundingPos.vec[0] += ((target.vec[0] * speed) >> 10);
        m_boundingPos.vec[1] -= ((target.vec[1] * speed) >> 10);
        m_boundingPos.vec[2] += ((target.vec[2] * speed) >> 10);
    }
    if (GSysKeys.left && !GSysKeys.right && !GSysKeys.up && !GSysKeys.down)
    {
        // Move leftward
        m_boundingPos.vec[0] -= ((cross.vec[0] * speed) >> 10);
        m_boundingPos.vec[1] += ((cross.vec[1] * speed) >> 10);
        m_boundingPos.vec[2] -= ((cross.vec[2] * speed) >> 10);
    }
    if (GSysKeys.left && GSysKeys.up && GSysKeys.down && !GSysKeys.right)
    {
        // Move leftward
        m_boundingPos.vec[0] -= ((cross.vec[0] * speed) >> 10);
        m_boundingPos.vec[1] += ((cross.vec[1] * speed) >> 10);
        m_boundingPos.vec[2] -= ((cross.vec[2] * speed) >> 10);
    }
    if (GSysKeys.right && !GSysKeys.left && !GSysKeys.up && !GSysKeys.down)
    {
        // Move rightward
        m_boundingPos.vec[0] += ((cross.vec[0] * speed) >> 10);
        m_boundingPos.vec[1] -= ((cross.vec[1] * speed) >> 10);
        m_boundingPos.vec[2] += ((cross.vec[2] * speed) >> 10);
    }
    if (GSysKeys.right && GSysKeys.up && GSysKeys.down && !GSysKeys.left)
    {
        // Move rightward
        m_boundingPos.vec[0] += ((cross.vec[0] * speed) >> 10);
        m_boundingPos.vec[1] -= ((cross.vec[1] * speed) >> 10);
        m_boundingPos.vec[2] += ((cross.vec[2] * speed) >> 10);
    }
    if (GSysKeys.up && GSysKeys.left && !GSysKeys.down && !GSysKeys.right)
    {
        // Move forward leftward
        m_boundingPos.vec[0] -= ((target.vec[0] * crossSpeed) >> 10);
        m_boundingPos.vec[1] += ((target.vec[1] * crossSpeed) >> 10);
        m_boundingPos.vec[2] -= ((target.vec[2] * crossSpeed) >> 10);
        m_boundingPos.vec[0] -= ((cross.vec[0] * crossSpeed) >> 10);
        m_boundingPos.vec[1] += ((cross.vec[1] * crossSpeed) >> 10);
        m_boundingPos.vec[2] -= ((cross.vec[2] * crossSpeed) >> 10);
    }
    if (GSysKeys.up && GSysKeys.right && !GSysKeys.down && !GSysKeys.left)
    {
        // Move forward rightward
        m_boundingPos.vec[0] -= ((target.vec[0] * crossSpeed) >> 10);
        m_boundingPos.vec[1] += ((target.vec[1] * crossSpeed) >> 10);
        m_boundingPos.vec[2] -= ((target.vec[2] * crossSpeed) >> 10);
        m_boundingPos.vec[0] += ((cross.vec[0] * crossSpeed) >> 10);
        m_boundingPos.vec[1] -= ((cross.vec[1] * crossSpeed) >> 10);
        m_boundingPos.vec[2] += ((cross.vec[2] * crossSpeed) >> 10);
    }
    if (GSysKeys.down && GSysKeys.left && !GSysKeys.up && !GSysKeys.right)
    {
        // Move backward leftward
        m_boundingPos.vec[0] += ((target.vec[0] * crossSpeed) >> 10);
        m_boundingPos.vec[1] -= ((target.vec[1] * crossSpeed) >> 10);
        m_boundingPos.vec[2] += ((target.vec[2] * crossSpeed) >> 10);
        m_boundingPos.vec[0] -= ((cross.vec[0] * crossSpeed) >> 10);
        m_boundingPos.vec[1] += ((cross.vec[1] * crossSpeed) >> 10);
        m_boundingPos.vec[2] -= ((cross.vec[2] * crossSpeed) >> 10);
    }
    if (GSysKeys.down && GSysKeys.right && !GSysKeys.left && !GSysKeys.up)
    {
        // Move backward rightward
        m_boundingPos.vec[0] += ((target.vec[0] * crossSpeed) >> 10);
        m_boundingPos.vec[1] -= ((target.vec[1] * crossSpeed) >> 10);
        m_boundingPos.vec[2] += ((target.vec[2] * crossSpeed) >> 10);
        m_boundingPos.vec[0] += ((cross.vec[0] * crossSpeed) >> 10);
        m_boundingPos.vec[1] -= ((cross.vec[1] * crossSpeed) >> 10);
        m_boundingPos.vec[2] += ((cross.vec[2] * crossSpeed) >> 10);
    }
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
    // Compute freefly camera angles
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
