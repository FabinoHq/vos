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
//     Renderer/View.cpp : View management                                    //
////////////////////////////////////////////////////////////////////////////////
#include "View.h"
#include "Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  View default constructor                                                  //
////////////////////////////////////////////////////////////////////////////////
View::View() :
m_descriptorPool(0),
m_projMatrix(),
m_viewMatrix(),
m_position(0.0f, 0.0f),
m_size(1.0f, 1.0f),
m_angle(0.0f)
{
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        m_descriptorSets[i] = 0;
    }
    m_projMatrix.reset();
    m_viewMatrix.reset();
}

////////////////////////////////////////////////////////////////////////////////
//  View destructor                                                           //
////////////////////////////////////////////////////////////////////////////////
View::~View()
{
    m_angle = 0.0f;
    m_size.reset();
    m_position.reset();
    m_viewMatrix.reset();
    m_projMatrix.reset();
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        m_descriptorSets[i] = 0;
    }
    m_descriptorPool = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Init view                                                                 //
//  return : True if the view is successfully created                         //
////////////////////////////////////////////////////////////////////////////////
bool View::init(Renderer& renderer)
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

    // Reset view position
    m_position.reset();

    // Set view size
    m_size.set(1.0f, 1.0f);

    // Reset view angle
    m_angle = 0.0f;

    // Set default matrices
    m_projMatrix.setOrthographic(-1.0f, 1.0f, 1.0f, -1.0f, -2.0f, 2.0f);
    m_projMatrix.translateZ(-1.0f);

    m_viewMatrix.setIdentity();

    // Copy matrices data into uniform data
    UniformData uniformData;
    memcpy(uniformData.projMatrix, m_projMatrix.mat, sizeof(m_projMatrix.mat));
    memcpy(uniformData.viewMatrix, m_viewMatrix.mat, sizeof(m_viewMatrix.mat));

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

    // Create matrices descriptor pool
    VkDescriptorPoolSize poolSize;
    poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSize.descriptorCount = RendererMaxSwapchainFrames;

    VkDescriptorPoolCreateInfo poolInfo;
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.pNext = 0;
    poolInfo.flags = 0;
    poolInfo.maxSets = RendererMaxSwapchainFrames;
    poolInfo.poolSizeCount = 1;
    poolInfo.pPoolSizes = &poolSize;

    if (vkCreateDescriptorPool(
        renderer.m_vulkanDevice, &poolInfo, 0, &m_descriptorPool) != VK_SUCCESS)
    {
        // Could not create matrices descriptor pool
        return false;
    }
    if (!m_descriptorPool)
    {
        // Invalid matrices descriptor pool
        return false;
    }

    // Create matrices descriptor set
    VkDescriptorSetAllocateInfo descriptorInfo;
    descriptorInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    descriptorInfo.pNext = 0;
    descriptorInfo.descriptorPool = m_descriptorPool;
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

    // View is successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Bind view                                                                 //
//  return : True if the view is successfully binded                          //
////////////////////////////////////////////////////////////////////////////////
bool View::bind(Renderer& renderer)
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

    // Update matrices
    m_projMatrix.setOrthographic(
        -renderer.m_swapchain.ratio, renderer.m_swapchain.ratio,
        1.0f, -1.0f, -2.0f, 2.0f
    );
    m_projMatrix.translateZ(-1.0f);

    // Set view matrix
    m_viewMatrix.setIdentity();
    m_viewMatrix.translate(m_position.vec[0], m_position.vec[1]);
    m_viewMatrix.translate(m_size.vec[0]*0.5f, m_size.vec[1]*0.5f);
    m_viewMatrix.rotateZ(m_angle);
    m_viewMatrix.translate(-m_size.vec[0]*0.5f, -m_size.vec[1]*0.5f);
    m_viewMatrix.scale(m_size.vec[0], m_size.vec[1]);

    // Copy matrices data into uniform data
    UniformData uniformData;
    memcpy(uniformData.projMatrix, m_projMatrix.mat, sizeof(m_projMatrix.mat));
    memcpy(uniformData.viewMatrix, m_viewMatrix.mat, sizeof(m_viewMatrix.mat));

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

    // View successfully binded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy view                                                              //
////////////////////////////////////////////////////////////////////////////////
void View::destroyView(Renderer& renderer)
{
    // Destroy uniform buffers
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        m_uniformBuffers[i].destroyBuffer(
            renderer.m_vulkanDevice, renderer.m_vulkanMemory
        );
        m_descriptorSets[i] = 0;
    }

    // Destroy descriptor pool
    if (m_descriptorPool && vkDestroyDescriptorPool)
    {
        vkDestroyDescriptorPool(renderer.m_vulkanDevice, m_descriptorPool, 0);
    }

    m_angle = 0.0f;
    m_size.reset();
    m_position.reset();
    m_viewMatrix.reset();
    m_projMatrix.reset();
    m_descriptorPool = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Set view position                                                         //
////////////////////////////////////////////////////////////////////////////////
void View::setPosition(float x, float y)
{
    m_position.vec[0] = x;
    m_position.vec[1] = y;
}

////////////////////////////////////////////////////////////////////////////////
//  Set view position                                                         //
////////////////////////////////////////////////////////////////////////////////
void View::setPosition(Vector2& position)
{
    m_position.vec[0] = position.vec[0];
    m_position.vec[1] = position.vec[1];
}

////////////////////////////////////////////////////////////////////////////////
//  Set view X position                                                       //
////////////////////////////////////////////////////////////////////////////////
void View::setX(float x)
{
    m_position.vec[0] = x;
}

////////////////////////////////////////////////////////////////////////////////
//  Set view Y position                                                       //
////////////////////////////////////////////////////////////////////////////////
void View::setY(float y)
{
    m_position.vec[1] = y;
}

////////////////////////////////////////////////////////////////////////////////
//  Translate view                                                            //
////////////////////////////////////////////////////////////////////////////////
void View::move(float x, float y)
{
    m_position.vec[0] += x;
    m_position.vec[1] += y;
}

////////////////////////////////////////////////////////////////////////////////
//  Translate view                                                            //
////////////////////////////////////////////////////////////////////////////////
void View::move(Vector2& vector)
{
    m_position.vec[0] += vector.vec[0];
    m_position.vec[1] += vector.vec[1];
}

////////////////////////////////////////////////////////////////////////////////
//  Translate view on X axis                                                  //
////////////////////////////////////////////////////////////////////////////////
void View::moveX(float x)
{
    m_position.vec[0] += x;
}

////////////////////////////////////////////////////////////////////////////////
//  Translate view on Y axis                                                  //
////////////////////////////////////////////////////////////////////////////////
void View::moveY(float y)
{
    m_position.vec[1] += y;
}

////////////////////////////////////////////////////////////////////////////////
//  Set view size                                                             //
////////////////////////////////////////////////////////////////////////////////
void View::setSize(float width, float height)
{
    m_size.vec[0] = width;
    m_size.vec[1] = height;
}

////////////////////////////////////////////////////////////////////////////////
//  Set view size                                                             //
////////////////////////////////////////////////////////////////////////////////
void View::setSize(Vector2& size)
{
    m_size.vec[0] = size.vec[0];
    m_size.vec[1] = size.vec[1];
}

////////////////////////////////////////////////////////////////////////////////
//  Set view width                                                            //
////////////////////////////////////////////////////////////////////////////////
void View::setWidth(float width)
{
    m_size.vec[0] = width;
}

////////////////////////////////////////////////////////////////////////////////
//  Set view height                                                           //
////////////////////////////////////////////////////////////////////////////////
void View::setHeight(float height)
{
    m_size.vec[1] = height;
}

////////////////////////////////////////////////////////////////////////////////
//  Set view rotation angle                                                   //
////////////////////////////////////////////////////////////////////////////////
void View::setAngle(float angle)
{
    m_angle = angle;
}

////////////////////////////////////////////////////////////////////////////////
//  Rotate view                                                               //
////////////////////////////////////////////////////////////////////////////////
void View::rotate(float angle)
{
    m_angle += angle;
}
