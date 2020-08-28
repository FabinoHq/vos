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


////////////////////////////////////////////////////////////////////////////////
//  Texture default constructor                                               //
////////////////////////////////////////////////////////////////////////////////
Texture::Texture() :
width(0),
height(0),
handle(0),
memory(0),
sampler(0),
view(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  Texture destructor                                                        //
////////////////////////////////////////////////////////////////////////////////
Texture::~Texture()
{
    view = 0;
    sampler = 0;
    memory = 0;
    handle = 0;
    height = 0;
    width = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Create texture                                                            //
//  return : True if texture is successfully created                          //
////////////////////////////////////////////////////////////////////////////////
bool Texture::createTexture(VkPhysicalDevice& physicalDevice,
    VkDevice& vulkanDevice, VulkanMemory& vulkanMemory,
    uint32_t texWidth, uint32_t texHeight)
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

    // Check texture size
    if (texWidth == 0 || texHeight == 0)
    {
        // Invalid texture size
        return false;
    }

    // Check texture handle
    if (handle)
    {
        // Destroy texture
        destroyTexture(vulkanDevice, vulkanMemory);
    }

    // Set texture size
    width = texWidth;
    height = texHeight;

    // Create image
    VkImageCreateInfo imageInfo;
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.pNext = 0;
    imageInfo.flags = 0;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
    imageInfo.extent.width = width;
    imageInfo.extent.height = height;
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

    if (vkCreateImage(vulkanDevice, &imageInfo, 0, &handle) != VK_SUCCESS)
    {
        // Could not create image
        return false;
    }
    if (!handle)
    {
        // Invalid image
        return false;
    }

    // Allocate image memory
    if (!vulkanMemory.allocateImageMemory(
        physicalDevice, vulkanDevice, handle, memory))
    {
        // Could not allocate image memory
        return false;
    }

    // Bind image memory
    if (vkBindImageMemory(vulkanDevice, handle, memory, 0) != VK_SUCCESS)
    {
        // Could not bind image memory
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

    if (vkCreateSampler(vulkanDevice, &samplerInfo, 0, &sampler) != VK_SUCCESS)
    {
        // Could not create image sampler
        return false;
    }
    if (!sampler)
    {
        // Invalid image sampler
        return false;
    }

    // Create image view
    VkImageViewCreateInfo viewInfo;
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.pNext = 0;
    viewInfo.flags = 0;
    viewInfo.image = handle;
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

    if (vkCreateImageView(vulkanDevice, &viewInfo, 0, &view) != VK_SUCCESS)
    {
        // Could not create image view
        return false;
    }
    if (!view)
    {
        // Invalid image view
        return false;
    }

    // Vulkan Texture successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Update texture                                                            //
//  return : True if texture is successfully updated                          //
////////////////////////////////////////////////////////////////////////////////
bool Texture::updateTexture(VkPhysicalDevice& physicalDevice,
    VkDevice& vulkanDevice, VulkanMemory& vulkanMemory,
    VkCommandPool& commandsPool, VulkanQueue& graphicsQueue,
    uint32_t texWidth, uint32_t texHeight, uint32_t texDepth,
    const unsigned char* data)
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

    // Check commands pool
    if (!commandsPool)
    {
        // Invalid commands pool
        return false;
    }

    // Check graphics queue
    if (!graphicsQueue.handle)
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
    if (!handle || (texWidth != width) || (texHeight != height))
    {
        // Recreate texture
        destroyTexture(vulkanDevice, vulkanMemory);
        createTexture(
            physicalDevice, vulkanDevice, vulkanMemory, texWidth, texHeight
        );
    }

    uint32_t textureSize = width * height * texDepth;

    // Create staging buffer
    VulkanBuffer stagingBuffer;
    stagingBuffer.size = textureSize;

    if (!stagingBuffer.createBuffer(
        physicalDevice, vulkanDevice, vulkanMemory,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
        VK_MEMORY_PROPERTY_HOST_COHERENT_BIT))
    {
        // Could not create staging buffer
        return false;
    }

    // Map staging buffer memory
    void* stagingBufferMemory = 0;
    if (vkMapMemory(vulkanDevice, stagingBuffer.memory, 0,
        stagingBuffer.size, 0, &stagingBufferMemory) != VK_SUCCESS)
    {
        return false;
        // Could not map staging buffer memory
    }
    if (!stagingBufferMemory)
    {
        // Invalid staging buffer memory
        return false;
    }

    // Copy texture into staging buffer memory
    memcpy(stagingBufferMemory, data, stagingBuffer.size);

    // Unmap staging buffer memory
    VkMappedMemoryRange memoryRange;
    memoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
    memoryRange.pNext = 0;
    memoryRange.memory = stagingBuffer.memory;
    memoryRange.offset = 0;
    memoryRange.size = VK_WHOLE_SIZE;
    
    if (vkFlushMappedMemoryRanges(vulkanDevice, 1, &memoryRange) != VK_SUCCESS)
    {
        // Could not flush staging buffer mapped memory ranges
        return false;
    }

    vkUnmapMemory(vulkanDevice, stagingBuffer.memory);


    // Allocate command buffers
    VkCommandBuffer commandBuffer = 0;
    VkCommandBufferAllocateInfo bufferAllocate;
    bufferAllocate.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    bufferAllocate.pNext = 0;
    bufferAllocate.commandPool = commandsPool;
    bufferAllocate.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    bufferAllocate.commandBufferCount = 1;

    if (vkAllocateCommandBuffers(
        vulkanDevice, &bufferAllocate, &commandBuffer) != VK_SUCCESS)
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
    undefinedToTransfer.image = handle;
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
    transferToShader.image = handle;
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
    imageCopy.imageExtent.width = TestSpriteWidth;
    imageCopy.imageExtent.height = TestSpriteHeight;
    imageCopy.imageExtent.depth = 1;

    vkCmdCopyBufferToImage(
        commandBuffer, stagingBuffer.handle, handle,
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

    if (vkCreateFence(vulkanDevice, &fenceInfo, 0, &fence) != VK_SUCCESS)
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
        graphicsQueue.handle, 1, &submitInfo, fence) != VK_SUCCESS)
    {
        // Could not submit queue
        return false;
    }

    // Wait for transfer to finish
    if (vkWaitForFences(
        vulkanDevice, 1, &fence, VK_FALSE, 100000000000) != VK_SUCCESS)
    {
        // Transfer timed out
        return false;
    }

    // Destroy fence
    if (fence)
    {
        vkDestroyFence(vulkanDevice, fence, 0);
    }

    // Destroy buffers
    if (commandBuffer)
    {
        vkFreeCommandBuffers(vulkanDevice, commandsPool, 1, &commandBuffer);
    }
    stagingBuffer.destroyBuffer(vulkanDevice, vulkanMemory);

    // Texture successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy texture                                                           //
////////////////////////////////////////////////////////////////////////////////
void Texture::destroyTexture(VkDevice& vulkanDevice, VulkanMemory& vulkanMemory)
{
    if (vulkanDevice)
    {
        // Destroy image view
        if (view && vkDestroyImageView)
        {
            vkDestroyImageView(vulkanDevice, view, 0);
        }

        // Destroy image sampler
        if (sampler && vkDestroySampler)
        {
            vkDestroySampler(vulkanDevice, sampler, 0);
        }

        // Destroy image
        if (handle && vkDestroyImage)
        {
            vkDestroyImage(vulkanDevice, handle, 0);
        }

        // Free image memory
        vulkanMemory.freeImageMemory(vulkanDevice, memory);
    }

    view = 0;
    sampler = 0;
    memory = 0;
    handle = 0;
    height = 0;
    width = 0;
}
