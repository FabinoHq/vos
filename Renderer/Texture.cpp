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
//     Renderer/Texture.cpp : Texture management                              //
////////////////////////////////////////////////////////////////////////////////
#include "Texture.h"
#include "Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  Texture default constructor                                               //
////////////////////////////////////////////////////////////////////////////////
Texture::Texture() :
m_handle(0),
m_sampler(0),
m_view(0),
m_descriptorPool(0),
m_stagingBuffer(),
m_memorySize(0),
m_memoryOffset(0),
m_width(0),
m_height(0),
m_depth(0)
{
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        m_descriptorSets[i] = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Texture destructor                                                        //
////////////////////////////////////////////////////////////////////////////////
Texture::~Texture()
{
    m_depth = 0;
    m_height = 0;
    m_width = 0;
    m_memoryOffset = 0;
    m_memorySize = 0;
    m_descriptorPool = 0;
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        m_descriptorSets[i] = 0;
    }
    m_view = 0;
    m_sampler = 0;
    m_handle = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Create texture                                                            //
//  return : True if texture is successfully created                          //
////////////////////////////////////////////////////////////////////////////////
bool Texture::createTexture(Renderer& renderer,
    uint32_t texWidth, uint32_t texHeight, uint32_t texDepth)
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

    // Check texture size
    if (texWidth == 0 || texHeight == 0 || texDepth == 0)
    {
        // Invalid texture size
        return false;
    }

    // Check texture handle
    if (m_handle)
    {
        // Destroy current texture
        destroyTexture(renderer);
    }

    // Set texture size
    m_width = texWidth;
    m_height = texHeight;
    m_depth = texDepth;

    // Create image
    VkImageCreateInfo imageInfo;
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.pNext = 0;
    imageInfo.flags = 0;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
    imageInfo.extent.width = m_width;
    imageInfo.extent.height = m_height;
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    imageInfo.usage =
        VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    imageInfo.queueFamilyIndexCount = 0;
    imageInfo.pQueueFamilyIndices = 0;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    if (vkCreateImage(
        renderer.m_vulkanDevice, &imageInfo, 0, &m_handle) != VK_SUCCESS)
    {
        // Could not create image
        return false;
    }
    if (!m_handle)
    {
        // Invalid image
        return false;
    }

    // Allocate texture memory
    if (!renderer.m_vulkanMemory.allocateTextureMemory(
        renderer.m_vulkanDevice, *this))
    {
        // Could not allocate texture memory
        return false;
    }

    // Create staging buffer
    uint32_t textureSize = m_width * m_height * m_depth;
    if (!m_stagingBuffer.createBuffer(
        renderer.m_physicalDevice, renderer.m_vulkanDevice,
        renderer.m_vulkanMemory, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VULKAN_MEMORY_HOST, textureSize))
    {
        // Could not create staging buffer
        return false;
    }

    // Create image sampler
    VkSamplerCreateInfo samplerInfo;
    samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    samplerInfo.pNext = 0;
    samplerInfo.flags = 0;
    samplerInfo.magFilter = VK_FILTER_NEAREST;
    samplerInfo.minFilter = VK_FILTER_NEAREST;
    samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
    samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerInfo.mipLodBias = 0.0f;
    samplerInfo.anisotropyEnable = VK_FALSE;
    samplerInfo.maxAnisotropy = 1.0f;
    samplerInfo.compareEnable = VK_FALSE;
    samplerInfo.compareOp = VK_COMPARE_OP_NEVER;
    samplerInfo.minLod = 0.0f;
    samplerInfo.maxLod = 0.0f;
    samplerInfo.borderColor = VK_BORDER_COLOR_INT_TRANSPARENT_BLACK;
    samplerInfo.unnormalizedCoordinates = VK_FALSE;

    if (vkCreateSampler(
        renderer.m_vulkanDevice, &samplerInfo, 0, &m_sampler) != VK_SUCCESS)
    {
        // Could not create image sampler
        return false;
    }
    if (!m_sampler)
    {
        // Invalid image sampler
        return false;
    }

    // Create image view
    VkImageViewCreateInfo viewInfo;
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.pNext = 0;
    viewInfo.flags = 0;
    viewInfo.image = m_handle;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
    viewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    viewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    viewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    viewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;

    if (vkCreateImageView(
        renderer.m_vulkanDevice, &viewInfo, 0, &m_view) != VK_SUCCESS)
    {
        // Could not create image view
        return false;
    }
    if (!m_view)
    {
        // Invalid image view
        return false;
    }

    // Create texture descriptor pool
    VkDescriptorPoolSize poolSize;
    poolSize.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
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
        // Could not create texture descriptor pool
        return false;
    }
    if (!m_descriptorPool)
    {
        // Invalid texture descriptor pool
        return false;
    }

    // Create texture descriptor sets
    VkDescriptorSetAllocateInfo descriptorInfo;
    descriptorInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    descriptorInfo.pNext = 0;
    descriptorInfo.descriptorPool = m_descriptorPool;
    descriptorInfo.descriptorSetCount = RendererMaxSwapchainFrames;
    descriptorInfo.pSetLayouts = &renderer.m_layout.swapSetLayouts[
        DESC_TEXTURE*RendererMaxSwapchainFrames
    ];

    if (vkAllocateDescriptorSets(renderer.m_vulkanDevice,
        &descriptorInfo, m_descriptorSets) != VK_SUCCESS)
    {
        // Could not allocate texture descriptor sets
        return false;
    }

    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        // Update texture descriptor sets
        VkDescriptorImageInfo descImageInfo;
        descImageInfo.sampler = m_sampler;
        descImageInfo.imageView = m_view;
        descImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

        VkWriteDescriptorSet descriptorWrites;

        descriptorWrites.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites.pNext = 0;
        descriptorWrites.dstSet = m_descriptorSets[i];
        descriptorWrites.dstBinding = 0;
        descriptorWrites.dstArrayElement = 0;
        descriptorWrites.descriptorCount = 1;
        descriptorWrites.descriptorType =
            VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptorWrites.pImageInfo = &descImageInfo;
        descriptorWrites.pBufferInfo = 0;
        descriptorWrites.pTexelBufferView = 0;

        vkUpdateDescriptorSets(
            renderer.m_vulkanDevice, 1, &descriptorWrites, 0, 0
        );
    }

    // Vulkan Texture successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Update texture                                                            //
//  return : True if texture is successfully updated                          //
////////////////////////////////////////////////////////////////////////////////
bool Texture::updateTexture(Renderer& renderer, uint32_t texWidth,
    uint32_t texHeight, uint32_t texDepth, const unsigned char* data)
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

    // Check commands pool
    if (!renderer.m_swapchain.commandsPool)
    {
        // Invalid commands pool
        return false;
    }

    // Check graphics queue
    if (!renderer.m_graphicsQueue.handle)
    {
        // Invalid graphics queue
        return false;
    }

    // Check texture size
    if (texWidth == 0 || texHeight == 0 || texDepth == 0)
    {
        // Invalid texture size
        return false;
    }

    // Check current texture
    if (!m_handle || (texWidth != m_width) ||
        (texHeight != m_height) || (texDepth != m_depth))
    {
        // Recreate texture
        destroyTexture(renderer);
        createTexture(renderer, texWidth, texHeight, texDepth);
    }

    // Write data into staging buffer memory
    if (!renderer.m_vulkanMemory.writeBufferMemory(
        renderer.m_vulkanDevice, m_stagingBuffer, data))
    {
        // Could not write data into staging buffer memory
        return false;
    }

    // Allocate command buffers
    VkCommandBuffer commandBuffer = 0;
    VkCommandBufferAllocateInfo bufferAllocate;
    bufferAllocate.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    bufferAllocate.pNext = 0;
    bufferAllocate.commandPool = renderer.m_swapchain.commandsPool;
    bufferAllocate.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    bufferAllocate.commandBufferCount = 1;

    if (vkAllocateCommandBuffers(
        renderer.m_vulkanDevice, &bufferAllocate, &commandBuffer) != VK_SUCCESS)
    {
        // Could not allocate command buffers
        return false;
    }

    // Transfert staging buffer data to texture buffer
    VkCommandBufferBeginInfo bufferBeginInfo;
    bufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    bufferBeginInfo.pNext = 0;
    bufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    bufferBeginInfo.pInheritanceInfo = 0;

    if (vkBeginCommandBuffer(commandBuffer, &bufferBeginInfo) != VK_SUCCESS)
    {
        // Could not record command buffer
        return false;
    }

    VkImageSubresourceRange subresourceRange;
    subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    subresourceRange.baseMipLevel = 0;
    subresourceRange.levelCount = 1;
    subresourceRange.baseArrayLayer = 0;
    subresourceRange.layerCount = 1;

    VkImageMemoryBarrier undefinedToTransfer;
    undefinedToTransfer.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    undefinedToTransfer.pNext = 0;
    undefinedToTransfer.srcAccessMask = 0;
    undefinedToTransfer.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    undefinedToTransfer.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    undefinedToTransfer.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    undefinedToTransfer.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    undefinedToTransfer.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    undefinedToTransfer.image = m_handle;
    undefinedToTransfer.subresourceRange = subresourceRange;

    VkImageMemoryBarrier transferToShader;
    transferToShader.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    transferToShader.pNext = 0;
    transferToShader.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    transferToShader.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    transferToShader.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    transferToShader.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    transferToShader.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    transferToShader.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    transferToShader.image = m_handle;
    transferToShader.subresourceRange = subresourceRange;

    vkCmdPipelineBarrier(
        commandBuffer,
        VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
        VK_PIPELINE_STAGE_TRANSFER_BIT,
        0, 0, 0, 0, 0, 1, &undefinedToTransfer
    );

    VkBufferImageCopy imageCopy;
    imageCopy.bufferOffset = 0;
    imageCopy.bufferRowLength = 0;
    imageCopy.bufferImageHeight = 0;
    imageCopy.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    imageCopy.imageSubresource.mipLevel = 0;
    imageCopy.imageSubresource.baseArrayLayer = 0;
    imageCopy.imageSubresource.layerCount = 1;
    imageCopy.imageOffset.x = 0;
    imageCopy.imageOffset.y = 0;
    imageCopy.imageOffset.z = 0;
    imageCopy.imageExtent.width = m_width;
    imageCopy.imageExtent.height = m_height;
    imageCopy.imageExtent.depth = 1;

    vkCmdCopyBufferToImage(
        commandBuffer, m_stagingBuffer.handle, m_handle,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &imageCopy
    );

    vkCmdPipelineBarrier(
        commandBuffer,
        VK_PIPELINE_STAGE_TRANSFER_BIT,
        VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
        0, 0, 0, 0, 0, 1, &transferToShader
    );

    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
    {
        // Could not end command buffer
        return false;
    }

    VkFence fence = 0;
    VkFenceCreateInfo fenceInfo;
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.pNext = 0;
    fenceInfo.flags = 0;

    if (vkCreateFence(
        renderer.m_vulkanDevice, &fenceInfo, 0, &fence) != VK_SUCCESS)
    {
        // Could not create fence
        return false;
    }
    if (!fence)
    {
        // Invalid fence
        return false;
    }

    // Submit queue
    VkSubmitInfo submitInfo;
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.pNext = 0;
    submitInfo.waitSemaphoreCount = 0;
    submitInfo.pWaitSemaphores = 0;
    submitInfo.pWaitDstStageMask = 0;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;
    submitInfo.signalSemaphoreCount = 0;
    submitInfo.pSignalSemaphores = 0;

    if (vkQueueSubmit(
        renderer.m_graphicsQueue.handle, 1, &submitInfo, fence) != VK_SUCCESS)
    {
        // Could not submit queue
        return false;
    }

    // Wait for transfer to finish
    if (vkWaitForFences(renderer.m_vulkanDevice, 1,
        &fence, VK_FALSE, 100000000000) != VK_SUCCESS)
    {
        // Transfer timed out
        return false;
    }

    // Destroy fence
    if (fence)
    {
        vkDestroyFence(renderer.m_vulkanDevice, fence, 0);
    }

    // Destroy buffers
    if (commandBuffer)
    {
        vkFreeCommandBuffers(renderer.m_vulkanDevice,
            renderer.m_swapchain.commandsPool, 1, &commandBuffer
        );
    }

    // Texture successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Bind texture                                                              //
////////////////////////////////////////////////////////////////////////////////
void Texture::bind(Renderer& renderer)
{
    // Bind texture descriptor set
    vkCmdBindDescriptorSets(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        VK_PIPELINE_BIND_POINT_GRAPHICS, renderer.m_layout.handle,
        DESC_TEXTURE, 1, &m_descriptorSets[renderer.m_swapchain.current], 0, 0
    );
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy texture                                                           //
////////////////////////////////////////////////////////////////////////////////
void Texture::destroyTexture(Renderer& renderer)
{
    if (renderer.m_vulkanDevice)
    {
        // Destroy descriptor pool
        if (m_descriptorPool && vkDestroyDescriptorPool)
        {
            vkDestroyDescriptorPool(
                renderer.m_vulkanDevice, m_descriptorPool, 0
            );
        }

        // Destroy image view
        if (m_view && vkDestroyImageView)
        {
            vkDestroyImageView(renderer.m_vulkanDevice, m_view, 0);
        }

        // Destroy image sampler
        if (m_sampler && vkDestroySampler)
        {
            vkDestroySampler(renderer.m_vulkanDevice, m_sampler, 0);
        }

        // Destroy image
        if (m_handle && vkDestroyImage)
        {
            vkDestroyImage(renderer.m_vulkanDevice, m_handle, 0);
        }

        // Destroy staging buffer
        m_stagingBuffer.destroyBuffer(
            renderer.m_vulkanDevice, renderer.m_vulkanMemory
        );

        // Free texture memory
        renderer.m_vulkanMemory.freeTextureMemory(
            renderer.m_vulkanDevice, *this
        );
    }

    m_height = 0;
    m_width = 0;
    m_memoryOffset = 0;
    m_memorySize = 0;
    m_descriptorPool = 0;
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        m_descriptorSets[i] = 0;
    }
    m_view = 0;
    m_sampler = 0;
    m_handle = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Check if the texture has a valid handle                                   //
//  return : True if the texture is valid                                     //
////////////////////////////////////////////////////////////////////////////////
bool Texture::isValid()
{
    return m_handle;
}

////////////////////////////////////////////////////////////////////////////////
//  Get texture memory requirements                                           //
////////////////////////////////////////////////////////////////////////////////
void Texture::getMemoryRequirements(VkDevice& vulkanDevice,
    VkMemoryRequirements* memoryRequirements)
{
    vkGetImageMemoryRequirements(vulkanDevice, m_handle, memoryRequirements);
}

////////////////////////////////////////////////////////////////////////////////
//  Bind texture memory                                                       //
//  return : True if texture memory is successfully binded                    //
////////////////////////////////////////////////////////////////////////////////
bool Texture::bindTextureMemory(VkDevice& vulkanDevice,
    VkDeviceMemory& deviceMemory, VkDeviceSize size, VkDeviceSize offset)
{
    // Bind texture memory
    if (vkBindImageMemory(
        vulkanDevice, m_handle, deviceMemory, offset) != VK_SUCCESS)
    {
        // Could not bind texture memory
        return false;
    }

    // Texture memory successfully binded
    m_memorySize = size;
    m_memoryOffset = offset;
    return true;
}
