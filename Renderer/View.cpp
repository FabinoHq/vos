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


////////////////////////////////////////////////////////////////////////////////
//  View default constructor                                                  //
////////////////////////////////////////////////////////////////////////////////
View::View() :
m_projMatrix(),
m_viewMatrix()
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
    m_viewMatrix.reset();
    m_projMatrix.reset();
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        m_descriptorSets[i] = 0;
    }
}


////////////////////////////////////////////////////////////////////////////////
//  Init view                                                                 //
//  return : True if the view is successfully created                         //
////////////////////////////////////////////////////////////////////////////////
bool View::init(VkPhysicalDevice& physicalDevice, VkDevice& vulkanDevice,
    VulkanMemory& vulkanMemory, GraphicsPipeline& pipeline,
    VkCommandPool& transferCommandPool, VulkanQueue& transferQueue)
{
    // Check physical device
    if (!physicalDevice)
    {
        // Invalid physical device
        return false;
    }

    // Check Vulkan device
    if (!vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Check pipeline handle
    if (!pipeline.handle)
    {
        // Invalid pipeline handle
        return false;
    }

    // Check commands pool
    if (!transferCommandPool)
    {
        // Invalid commands pool
        return false;
    }

    // Check transfer queue
    if (!transferQueue.handle)
    {
        // Invalid transfer queue
        return false;
    }

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
        if (!m_uniformBuffers[i].updateBuffer(physicalDevice,
            vulkanDevice, vulkanMemory, transferCommandPool, transferQueue,
            &uniformData, sizeof(uniformData)))
        {
            // Could not create uniform buffer
            SysMessage::box() << "[0x3049] Could not create uniform buffer\n";
            SysMessage::box() << "Please update your graphics drivers";
            return false;
        }
    }

    // Create matrices descriptor set
    VkDescriptorSetAllocateInfo descriptorInfo;
    descriptorInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    descriptorInfo.pNext = 0;
    descriptorInfo.descriptorPool = pipeline.descPools[DESC_MATRICES];
    descriptorInfo.descriptorSetCount = RendererMaxSwapchainFrames;
    descriptorInfo.pSetLayouts =
        &pipeline.swapSetLayouts[DESC_MATRICES*RendererMaxSwapchainFrames];

    if (vkAllocateDescriptorSets(
        vulkanDevice, &descriptorInfo, m_descriptorSets) != VK_SUCCESS)
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

        vkUpdateDescriptorSets(vulkanDevice, 1, &descriptorWrites, 0, 0);
    }

    // View is successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Bind view                                                                 //
//  return : True if the view is successfully binded                          //
////////////////////////////////////////////////////////////////////////////////
bool View::bind(VkPhysicalDevice& physicalDevice, VkDevice& vulkanDevice,
    Swapchain& swapchain, VulkanMemory& vulkanMemory,
    GraphicsPipeline& pipeline, VkCommandPool& transferCommandPool,
    VulkanQueue& transferQueue)
{
    // Check physical device
    if (!physicalDevice)
    {
        // Invalid physical device
        return false;
    }

    // Check Vulkan device
    if (!vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Check swapchain handle
    if (!swapchain.handle)
    {
        // Invalid swapchain handle
        return false;
    }

    // Check pipeline handle
    if (!pipeline.handle)
    {
        // Invalid pipeline handle
        return false;
    }

    // Check commands pool
    if (!transferCommandPool)
    {
        // Invalid commands pool
        return false;
    }

    // Check transfer queue
    if (!transferQueue.handle)
    {
        // Invalid transfer queue
        return false;
    }

    // Update matrices
    m_projMatrix.setOrthographic(
        -swapchain.ratio, swapchain.ratio, 1.0f, -1.0f, -2.0f, 2.0f
    );
    m_projMatrix.translateZ(-1.0f);

    m_viewMatrix.setIdentity();

    // Copy matrices data into uniform data
    UniformData uniformData;
    memcpy(uniformData.projMatrix, m_projMatrix.mat, sizeof(m_projMatrix.mat));
    memcpy(uniformData.viewMatrix, m_viewMatrix.mat, sizeof(m_viewMatrix.mat));

    // Update uniform buffer
    if (!m_uniformBuffers[swapchain.current].updateBuffer(
        physicalDevice, vulkanDevice, vulkanMemory, transferCommandPool,
        transferQueue, &uniformData, sizeof(uniformData)))
    {
        // Could not update uniform buffer
        return false;
    }

    // Bind matrices descriptor set
    vkCmdBindDescriptorSets(
        swapchain.commandBuffers[swapchain.current],
        VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.layout, DESC_MATRICES, 1,
        &m_descriptorSets[swapchain.current], 0, 0
    );

    // View successfully binded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy view                                                              //
////////////////////////////////////////////////////////////////////////////////
void View::destroyView(VkDevice& vulkanDevice, VulkanMemory& vulkanMemory)
{
    // Destroy uniform buffers
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        m_uniformBuffers[i].destroyBuffer(vulkanDevice, vulkanMemory);
        m_descriptorSets[i] = 0;
    }
    m_viewMatrix.reset();
    m_projMatrix.reset();
}
