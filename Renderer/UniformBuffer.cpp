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
//     Renderer/UniformBuffer.cpp : Uniform buffer management                 //
////////////////////////////////////////////////////////////////////////////////
#include "UniformBuffer.h"


////////////////////////////////////////////////////////////////////////////////
//  UniformBuffer default constructor                                         //
////////////////////////////////////////////////////////////////////////////////
UniformBuffer::UniformBuffer()
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
bool UniformBuffer::createBuffer(VkPhysicalDevice& physicalDevice,
    VkDevice& vulkanDevice, VkCommandPool& commandsPool,
    VulkanQueue& transferQueue, void* data, uint32_t size)
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

    // Check transfer queue
    if (!transferQueue.handle)
    {
        // Invalid transfer queue
        return false;
    }

    // Check current buffer
    if (uniformBuffer.handle)
    {
        // Destroy current buffer
        destroyBuffer(vulkanDevice);
    }

    // Create staging buffer
    VulkanBuffer stagingBuffer;
    stagingBuffer.size = size;

    if (!stagingBuffer.createBuffer(
        physicalDevice, vulkanDevice,
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
        // Could not map staging buffer memory
        return false;
    }
    if (!stagingBufferMemory)
    {
        // Invalid staging buffer memory
        return false;
    }

    // Copy uniform data into staging buffer memory
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


    // Create uniform buffer
    uniformBuffer.size = size;

    if (!uniformBuffer.createBuffer(
        physicalDevice, vulkanDevice,
        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT))
    {
        // Could not create uniform buffer
        return false;
    }


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


    // Transfert staging buffer data to uniform buffer
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
        transferQueue.handle, 1, &submitInfo, fence) != VK_SUCCESS)
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
    stagingBuffer.destroyBuffer(vulkanDevice);

    // Uniform buffer successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy Uniform buffer                                                    //
////////////////////////////////////////////////////////////////////////////////
void UniformBuffer::destroyBuffer(VkDevice& vulkanDevice)
{
    uniformBuffer.destroyBuffer(vulkanDevice);
}
