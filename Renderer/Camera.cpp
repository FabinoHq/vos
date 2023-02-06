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
//     Renderer/Camera.cpp : Camera management                                //
////////////////////////////////////////////////////////////////////////////////
#include "Camera.h"


////////////////////////////////////////////////////////////////////////////////
//  Camera default constructor                                                //
////////////////////////////////////////////////////////////////////////////////
Camera::Camera() :
Transform3(),
m_projMatrix(),
m_projViewMatrix(),
m_target(0.0f, 0.0f, 0.0f),
m_upward(0.0f, 0.0f, 0.0f),
m_fovy(0.0f),
m_nearPlane(0.0f),
m_farPlane(0.0f)
{
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        m_descriptorSets[i] = 0;
    }
    m_projMatrix.reset();
    m_projViewMatrix.reset();
}

////////////////////////////////////////////////////////////////////////////////
//  Camera virtual destructor                                                 //
////////////////////////////////////////////////////////////////////////////////
Camera::~Camera()
{
    m_farPlane = 0.0f;
    m_nearPlane = 0.0f;
    m_fovy = 0.0f;
    m_upward.reset();
    m_target.reset();
    m_projViewMatrix.reset();
    m_projMatrix.reset();
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        m_descriptorSets[i] = 0;
    }
}


////////////////////////////////////////////////////////////////////////////////
//  Init camera                                                               //
//  return : True if the camera is successfully created                       //
////////////////////////////////////////////////////////////////////////////////
bool Camera::init()
{
    // Reset camera transforms
    resetTransforms();

    // Reset camera target vector
    m_target.reset();

    // Reset camera upward vector
    m_upward.set(0.0f, 1.0f, 0.0f);

    // Reset camera fovy
    m_fovy = CameraDefaultFovy;

    // Reset camera Z near and Z far
    m_nearPlane = CameraDefaultNearPlane;
    m_farPlane = CameraDefaultFarPlane;

    // Reset projection matrix
    m_projMatrix.setPerspective(
        m_fovy, GSwapchain.ratio, m_nearPlane, m_farPlane
    );

    // Reset view matrix
    m_matrix.setIdentity();

    // Reset projview matrix
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

    // Create uniform buffers
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        if (!m_uniformBuffers[i].createBuffer(sizeof(uniformData)))
        {
            // Could not create uniform buffer
            return false;
        }
    }

    // Create matrices descriptor set
    VkDescriptorSetAllocateInfo descriptorInfo;
    descriptorInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    descriptorInfo.pNext = 0;
    descriptorInfo.descriptorPool = GGraphicsLayout.uniformsDescPool;
    descriptorInfo.descriptorSetCount = RendererMaxSwapchainFrames;
    descriptorInfo.pSetLayouts = &GGraphicsLayout.swapSetLayouts[
        DESC_MATRICES*RendererMaxSwapchainFrames
    ];

    if (vkAllocateDescriptorSets(GVulkanDevice,
        &descriptorInfo, m_descriptorSets) != VK_SUCCESS)
    {
        // Could not allocate matrices descriptor sets
        return false;
    }

    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        // Update descriptor sets
        VkDescriptorBufferInfo descBufferInfo;
        descBufferInfo.buffer = m_uniformBuffers[i].uniformBuffer.handle;
        descBufferInfo.offset = 0;
        descBufferInfo.range = m_uniformBuffers[i].uniformBuffer.size;

        // Update matrices descriptor sets
        VkWriteDescriptorSet descriptorWrites;

        descriptorWrites.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites.pNext = 0;
        descriptorWrites.dstSet = m_descriptorSets[i];
        descriptorWrites.dstBinding = 0;
        descriptorWrites.dstArrayElement = 0;
        descriptorWrites.descriptorCount = 1;
        descriptorWrites.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrites.pImageInfo = 0;
        descriptorWrites.pBufferInfo = &descBufferInfo;
        descriptorWrites.pTexelBufferView = 0;

        vkUpdateDescriptorSets(GVulkanDevice, 1, &descriptorWrites, 0, 0);
    }

    // Camera is successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy camera                                                            //
////////////////////////////////////////////////////////////////////////////////
void Camera::destroyCamera()
{
    m_farPlane = 0.0f;
    m_nearPlane = 0.0f;
    m_fovy = 0.0f;
    m_upward.reset();
    m_target.reset();
    m_angles.reset();
    m_projViewMatrix.reset();
    m_projMatrix.reset();

    // Destroy uniform buffers and descriptor sets
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        m_uniformBuffers[i].destroyBuffer();
        m_descriptorSets[i] = 0;
    }

    resetTransforms();
}

////////////////////////////////////////////////////////////////////////////////
//  Compute camera                                                            //
//  return : True if the camera is successfully computed                      //
////////////////////////////////////////////////////////////////////////////////
bool Camera::compute(float ratio)
{
    // Compute camera target
    m_target.vec[0] = std::cos(m_angles.vec[0]);
    m_target.vec[0] *= std::sin(m_angles.vec[1]);
    m_target.vec[1] = std::sin(m_angles.vec[0]);
    m_target.vec[2] = std::cos(m_angles.vec[0]);
    m_target.vec[2] *= std::cos(m_angles.vec[1]);
    m_target.normalize();

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

    // Camera successfully computed
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Compute camera from another camera                                        //
//  return : True if the camera is successfully computed                      //
////////////////////////////////////////////////////////////////////////////////
bool Camera::compute(float ratio, Camera& camera)
{
    // Compute projection matrix
    m_projMatrix.setPerspective(m_fovy, ratio, m_nearPlane, m_farPlane);

    // Compute view matrix
    m_matrix.set(camera.m_matrix);

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

    // Camera successfully computed
    return true;
}
