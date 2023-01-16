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
//     Renderer/Vulkan/UniformBuffer.cpp : Uniform buffer management          //
////////////////////////////////////////////////////////////////////////////////
#include "UniformBuffer.h"


////////////////////////////////////////////////////////////////////////////////
//  UniformBuffer default constructor                                         //
////////////////////////////////////////////////////////////////////////////////
UniformBuffer::UniformBuffer() :
uniformBuffer(),
stagingBuffer()
{

}

////////////////////////////////////////////////////////////////////////////////
//  UniformBuffer destructor                                                  //
////////////////////////////////////////////////////////////////////////////////
UniformBuffer::~UniformBuffer()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Create Uniform buffer                                                     //
//  return : True if Uniform buffer is successfully created                   //
////////////////////////////////////////////////////////////////////////////////
bool UniformBuffer::createBuffer(VulkanMemory& vulkanMemory, uint32_t size)
{
    // Check current buffer
    if (uniformBuffer.handle)
    {
        // Destroy current buffer
        uniformBuffer.destroyBuffer();
    }

    // Check UniformData size
    size_t uniformDataSize = sizeof(UniformData);
    if (uniformDataSize != (sizeof(float)*16))
    {
        // Invalid UniformData size
        return false;
    }

    // Create uniform buffer
    if (!uniformBuffer.createBuffer(
        vulkanMemory,
        (VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT),
        VULKAN_MEMORY_RENDERDEVICE, size))
    {
        // Could not create uniform buffer
        return false;
    }

    // Create staging buffer
    if (!stagingBuffer.createBuffer(
        vulkanMemory,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VULKAN_MEMORY_RENDERHOST, size))
    {
        // Could not create staging buffer
        return false;
    }

    // Uniform buffer successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Update Uniform buffer                                                     //
//  return : True if Uniform buffer is successfully updated                   //
////////////////////////////////////////////////////////////////////////////////
bool UniformBuffer::updateBuffer(VulkanMemory& vulkanMemory,
    VkCommandPool& transferCommandPool,
    VulkanQueue& transferQueue, void* data, uint32_t size)
{
    // Check current buffer
    if (!uniformBuffer.handle || (uniformBuffer.size != size) ||
        !stagingBuffer.handle || (stagingBuffer.size != size))
    {
        // Recreate uniform buffer
        destroyBuffer();
        createBuffer(vulkanMemory, size);
    }

    // Write data into staging buffer memory
    if (!vulkanMemory.writeBufferMemory(
        stagingBuffer, data, VULKAN_MEMORY_RENDERHOST))
    {
        // Could not write data into staging buffer memory
        return false;
    }

    // Allocate command buffers
    VkCommandBuffer commandBuffer = 0;
    VkCommandBufferAllocateInfo bufferAllocate;
    bufferAllocate.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    bufferAllocate.pNext = 0;
    bufferAllocate.commandPool = transferCommandPool;
    bufferAllocate.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    bufferAllocate.commandBufferCount = 1;

    if (vkAllocateCommandBuffers(
        GVulkanDevice, &bufferAllocate, &commandBuffer) != VK_SUCCESS)
    {
        // Could not allocate command buffers
        return false;
    }


    // Transfer staging buffer data to uniform buffer
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

    VkBufferCopy bufferCopy;
    bufferCopy.srcOffset = 0;
    bufferCopy.dstOffset = 0;
    bufferCopy.size = stagingBuffer.size;

    vkCmdCopyBuffer(
        commandBuffer, stagingBuffer.handle,
        uniformBuffer.handle, 1, &bufferCopy
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

    if (vkCreateFence(GVulkanDevice,
        &fenceInfo, 0, &fence) != VK_SUCCESS)
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
        transferQueue.handle, 1, &submitInfo, fence) != VK_SUCCESS)
    {
        // Could not submit queue
        return false;
    }

    // Wait for transfer to finish
    if (vkWaitForFences(GVulkanDevice, 1,
        &fence, VK_FALSE, UniformBufferFenceTimeout) != VK_SUCCESS)
    {
        // Transfer timed out
        return false;
    }

    // Destroy fence
    if (fence)
    {
        vkDestroyFence(GVulkanDevice, fence, 0);
    }

    // Destroy command buffer
    if (commandBuffer)
    {
        vkFreeCommandBuffers(GVulkanDevice,
            transferCommandPool, 1, &commandBuffer
        );
    }

    // Uniform buffer successfully updated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy Uniform buffer                                                    //
////////////////////////////////////////////////////////////////////////////////
void UniformBuffer::destroyBuffer()
{
    stagingBuffer.destroyBuffer();
    uniformBuffer.destroyBuffer();
}
