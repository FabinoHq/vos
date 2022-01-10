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
//     Renderer/Camera.cpp : Camera management                                //
////////////////////////////////////////////////////////////////////////////////
#include "Camera.h"
#include "Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  Camera default constructor                                                //
////////////////////////////////////////////////////////////////////////////////
Camera::Camera() :
m_projMatrix(),
m_viewMatrix(),
m_projViewMatrix(),
m_position(0.0f, 0.0f, 0.0f),
m_angles(0.0f, 0.0f, 0.0f),
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
    m_viewMatrix.reset();
    m_projViewMatrix.reset();
}

////////////////////////////////////////////////////////////////////////////////
//  Camera destructor                                                         //
////////////////////////////////////////////////////////////////////////////////
Camera::~Camera()
{
    m_farPlane = 0.0f;
    m_nearPlane = 0.0f;
    m_fovy = 0.0f;
    m_upward.reset();
    m_target.reset();
    m_angles.reset();
    m_position.reset();
    m_projViewMatrix.reset();
    m_viewMatrix.reset();
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
bool Camera::init(Renderer& renderer)
{
    // Check physical device
    if (!renderer.m_physicalDevice)
    {
        // Invalid physical device
        return false;
    }

    // Check Vulkan device
    if (!renderer.m_vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Check transfer commands pool
    if (!renderer.m_transferCommandPool)
    {
        // Invalid transfer commands pool
        return false;
    }

    // Check transfer queue
    if (!renderer.m_transferQueue.handle)
    {
        // Invalid transfer queue
        return false;
    }

    // Reset camera position
    m_position.reset();

    // Reset camera angles
    m_angles.reset();

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
        m_fovy, renderer.m_swapchain.ratio, m_nearPlane, m_farPlane
    );

    // Reset view matrix
    m_viewMatrix.setIdentity();

    // Reset projview matrix
    m_projViewMatrix.set(m_projMatrix);
    m_projViewMatrix *= m_viewMatrix;

    // Copy matrices data into uniform data
    UniformData uniformData;
    memcpy(
        uniformData.projView, m_projViewMatrix.mat, sizeof(m_projViewMatrix.mat)
    );

    // Create uniform buffers
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        if (!m_uniformBuffers[i].updateBuffer(renderer.m_physicalDevice,
            renderer.m_vulkanDevice, renderer.m_vulkanMemory,
            renderer.m_transferCommandPool, renderer.m_transferQueue,
            &uniformData, sizeof(uniformData)))
        {
            // Could not create uniform buffer
            return false;
        }
    }

    // Create matrices descriptor set
    VkDescriptorSetAllocateInfo descriptorInfo;
    descriptorInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    descriptorInfo.pNext = 0;
    descriptorInfo.descriptorPool = renderer.m_uniformsDescPool;
    descriptorInfo.descriptorSetCount = RendererMaxSwapchainFrames;
    descriptorInfo.pSetLayouts = &renderer.m_layout.swapSetLayouts[
        DESC_MATRICES*RendererMaxSwapchainFrames
    ];

    if (vkAllocateDescriptorSets(renderer.m_vulkanDevice,
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
        descriptorWrites.descriptorType =
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrites.pImageInfo = 0;
        descriptorWrites.pBufferInfo = &descBufferInfo;
        descriptorWrites.pTexelBufferView = 0;

        vkUpdateDescriptorSets(
            renderer.m_vulkanDevice, 1, &descriptorWrites, 0, 0
        );
    }

    // Camera is successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Bind camera                                                               //
//  return : True if the camera is successfully binded                        //
////////////////////////////////////////////////////////////////////////////////
bool Camera::bind(Renderer& renderer)
{
    // Check physical device
    if (!renderer.m_physicalDevice)
    {
        // Invalid physical device
        return false;
    }

    // Check Vulkan device
    if (!renderer.m_vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Check swapchain handle
    if (!renderer.m_swapchain.handle)
    {
        // Invalid swapchain handle
        return false;
    }

    // Check transfer commands pool
    if (!renderer.m_transferCommandPool)
    {
        // Invalid transfer commands pool
        return false;
    }

    // Check transfer queue
    if (!renderer.m_transferQueue.handle)
    {
        // Invalid transfer queue
        return false;
    }

    // Compute camera target
    m_target.vec[0] = std::cos(m_angles.vec[0]);
    m_target.vec[0] *= std::sin(m_angles.vec[1]);
    m_target.vec[1] = std::sin(m_angles.vec[0]);
    m_target.vec[2] = std::sin(m_angles.vec[0]);
    m_target.vec[2] *= std::cos(m_angles.vec[1]);
    m_target.normalize();

    // Compute projection matrix
    m_projMatrix.setPerspective(
        m_fovy, renderer.m_swapchain.ratio, m_nearPlane, m_farPlane
    );

    // Compute view matrix
    m_viewMatrix.setIdentity();
    m_viewMatrix.rotateX(m_angles.vec[0]);
    m_viewMatrix.rotateY(m_angles.vec[1]);
    m_viewMatrix.rotateZ(m_angles.vec[2]);
    m_viewMatrix.translate(m_position);

    // Compute projview matrix
    m_projViewMatrix.set(m_projMatrix);
    m_projViewMatrix *= m_viewMatrix;

    // Copy matrices data into uniform data
    UniformData uniformData;
    memcpy(
        uniformData.projView, m_projViewMatrix.mat, sizeof(m_projViewMatrix.mat)
    );

    // Update uniform buffer
    if (!m_uniformBuffers[renderer.m_swapchain.current].updateBuffer(
        renderer.m_physicalDevice, renderer.m_vulkanDevice,
        renderer.m_vulkanMemory, renderer.m_transferCommandPool,
        renderer.m_transferQueue, &uniformData, sizeof(uniformData)))
    {
        // Could not update uniform buffer
        return false;
    }

    // Bind matrices descriptor set
    vkCmdBindDescriptorSets(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        VK_PIPELINE_BIND_POINT_GRAPHICS, renderer.m_layout.handle,
        DESC_MATRICES, 1, &m_descriptorSets[renderer.m_swapchain.current], 0, 0
    );

    // Camera successfully binded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy camera                                                            //
////////////////////////////////////////////////////////////////////////////////
void Camera::destroyCamera(Renderer& renderer)
{
    // Destroy uniform buffers
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        m_uniformBuffers[i].destroyBuffer(
            renderer.m_vulkanDevice, renderer.m_vulkanMemory
        );
        m_descriptorSets[i] = 0;
    }

    m_farPlane = 0.0f;
    m_nearPlane = 0.0f;
    m_fovy = 0.0f;
    m_upward.reset();
    m_target.reset();
    m_angles.reset();
    m_position.reset();
    m_projViewMatrix.reset();
    m_viewMatrix.reset();
    m_projMatrix.reset();
}


////////////////////////////////////////////////////////////////////////////////
//  Set camera position                                                       //
////////////////////////////////////////////////////////////////////////////////
void Camera::setPosition(float x, float y, float z)
{
    m_position.vec[0] = x;
    m_position.vec[1] = y;
    m_position.vec[2] = z;
}

////////////////////////////////////////////////////////////////////////////////
//  Set camera position                                                       //
////////////////////////////////////////////////////////////////////////////////
void Camera::setPosition(Vector3& position)
{
    m_position.vec[0] = position.vec[0];
    m_position.vec[1] = position.vec[1];
    m_position.vec[2] = position.vec[2];
}

////////////////////////////////////////////////////////////////////////////////
//  Set camera X position                                                     //
////////////////////////////////////////////////////////////////////////////////
void Camera::setX(float x)
{
    m_position.vec[0] = x;
}

////////////////////////////////////////////////////////////////////////////////
//  Set camera Y position                                                     //
////////////////////////////////////////////////////////////////////////////////
void Camera::setY(float y)
{
    m_position.vec[1] = y;
}

////////////////////////////////////////////////////////////////////////////////
//  Set camera Z position                                                     //
////////////////////////////////////////////////////////////////////////////////
void Camera::setZ(float z)
{
    m_position.vec[2] = z;
}

////////////////////////////////////////////////////////////////////////////////
//  Translate camera                                                          //
////////////////////////////////////////////////////////////////////////////////
void Camera::move(float x, float y, float z)
{
    m_position.vec[0] += x;
    m_position.vec[1] += y;
    m_position.vec[2] += z;
}

////////////////////////////////////////////////////////////////////////////////
//  Translate camera                                                          //
////////////////////////////////////////////////////////////////////////////////
void Camera::move(Vector3& vector)
{
    m_position.vec[0] += vector.vec[0];
    m_position.vec[1] += vector.vec[1];
    m_position.vec[2] += vector.vec[2];
}

////////////////////////////////////////////////////////////////////////////////
//  Translate camera on X axis                                                //
////////////////////////////////////////////////////////////////////////////////
void Camera::moveX(float x)
{
    m_position.vec[0] += x;
}

////////////////////////////////////////////////////////////////////////////////
//  Translate camera on Y axis                                                //
////////////////////////////////////////////////////////////////////////////////
void Camera::moveY(float y)
{
    m_position.vec[1] += y;
}

////////////////////////////////////////////////////////////////////////////////
//  Translate camera on Z axis                                                //
////////////////////////////////////////////////////////////////////////////////
void Camera::moveZ(float z)
{
    m_position.vec[2] += z;
}

////////////////////////////////////////////////////////////////////////////////
//  Set camera angles                                                         //
////////////////////////////////////////////////////////////////////////////////
void Camera::setAngles(float angleX, float angleY, float angleZ)
{
    m_angles.vec[0] = angleX;
    m_angles.vec[1] = angleY;
    m_angles.vec[2] = angleZ;
}

////////////////////////////////////////////////////////////////////////////////
//  Set camera angles                                                         //
////////////////////////////////////////////////////////////////////////////////
void Camera::setAngles(Vector3& angles)
{
    m_angles.vec[0] = angles.vec[0];
    m_angles.vec[1] = angles.vec[1];
    m_angles.vec[2] = angles.vec[2];
}

////////////////////////////////////////////////////////////////////////////////
//  Set camera X angle                                                        //
////////////////////////////////////////////////////////////////////////////////
void Camera::setAngleX(float angleX)
{
    m_angles.vec[0] = angleX;
}

////////////////////////////////////////////////////////////////////////////////
//  Set camera Y angle                                                        //
////////////////////////////////////////////////////////////////////////////////
void Camera::setAngleY(float angleY)
{
    m_angles.vec[1] = angleY;
}

////////////////////////////////////////////////////////////////////////////////
//  Set camera Z angle                                                        //
////////////////////////////////////////////////////////////////////////////////
void Camera::setAngleZ(float angleZ)
{
    m_angles.vec[2] = angleZ;
}

////////////////////////////////////////////////////////////////////////////////
//  Rotate camera                                                             //
////////////////////////////////////////////////////////////////////////////////
void Camera::rotate(float angleX, float angleY, float angleZ)
{
    m_angles.vec[0] += angleX;
    m_angles.vec[1] += angleY;
    m_angles.vec[2] += angleZ;
}

////////////////////////////////////////////////////////////////////////////////
//  Rotate camera                                                             //
////////////////////////////////////////////////////////////////////////////////
void Camera::rotate(Vector3& angles)
{
    m_angles.vec[0] += angles.vec[0];
    m_angles.vec[1] += angles.vec[1];
    m_angles.vec[2] += angles.vec[2];
}

////////////////////////////////////////////////////////////////////////////////
//  Rotate camera around the X axis                                           //
////////////////////////////////////////////////////////////////////////////////
void Camera::rotateX(float angleX)
{
    m_angles.vec[0] += angleX;
}

////////////////////////////////////////////////////////////////////////////////
//  Rotate camera around the Y axis                                           //
////////////////////////////////////////////////////////////////////////////////
void Camera::rotateY(float angleY)
{
    m_angles.vec[1] += angleY;
}

////////////////////////////////////////////////////////////////////////////////
//  Rotate camera around the Z axis                                           //
////////////////////////////////////////////////////////////////////////////////
void Camera::rotateZ(float angleZ)
{
    m_angles.vec[2] += angleZ;
}

////////////////////////////////////////////////////////////////////////////////
//  Set camera fovy angle                                                     //
////////////////////////////////////////////////////////////////////////////////
void Camera::setFovy(float fovy)
{
    m_fovy = fovy;
}

////////////////////////////////////////////////////////////////////////////////
//  Set camera near plane                                                     //
////////////////////////////////////////////////////////////////////////////////
void Camera::setNearPlane(float nearPlane)
{
    m_nearPlane = nearPlane;
}

////////////////////////////////////////////////////////////////////////////////
//  Set camera far plane                                                      //
////////////////////////////////////////////////////////////////////////////////
void Camera::setFarPlane(float farPlane)
{
    m_farPlane = farPlane;
}
