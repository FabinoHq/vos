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
//     Renderer/Vulkan/VertexBuffer.cpp : Vertex buffer management            //
////////////////////////////////////////////////////////////////////////////////
#include "VertexBuffer.h"


////////////////////////////////////////////////////////////////////////////////
//  VertexBuffer default constructor                                          //
////////////////////////////////////////////////////////////////////////////////
VertexBuffer::VertexBuffer() :
vertexBuffer(),
vertexStagingBuffer(),
indexBuffer(),
indexStagingBuffer()
{

}

////////////////////////////////////////////////////////////////////////////////
//  VertexBuffer destructor                                                   //
////////////////////////////////////////////////////////////////////////////////
VertexBuffer::~VertexBuffer()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Create Vertex buffer                                                      //
//  return : True if Vertex buffer is successfully created                    //
////////////////////////////////////////////////////////////////////////////////
bool VertexBuffer::createBuffer(VkPhysicalDevice& physicalDevice,
    VkDevice& vulkanDevice, VulkanMemory& vulkanMemory,
    VkCommandPool& commandPool, VulkanQueue& transferQueue,
    const float* vertices, const uint16_t* indices,
    uint32_t verticesCount, uint32_t indicesCount)
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
    if (!commandPool)
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

    // Check input vertices and indices
    if (!vertices || !indices || (verticesCount <= 0) || (indicesCount <= 0))
    {
        return false;
    }

    // Check current buffers
    if (indexBuffer.handle || indexStagingBuffer.handle ||
        vertexBuffer.handle || vertexStagingBuffer.handle)
    {
        // Destroy current buffers
        destroyBuffer(vulkanDevice);
    }

    // Compute vertices and indices sizes
    verticesCount *= sizeof(float);
    indicesCount *= sizeof(uint16_t);


    // Create vertex staging buffer
    if (!vertexStagingBuffer.createBuffer(
        physicalDevice, vulkanDevice, vulkanMemory,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VULKAN_MEMORY_RENDERHOST, verticesCount))
    {
        // Could not create staging buffer
        return false;
    }

    // Write vertices into staging buffer memory
    if (!vulkanMemory.writeBufferMemory(
        vulkanDevice, vertexStagingBuffer, vertices, VULKAN_MEMORY_RENDERHOST))
    {
        // Could not write vertices into staging buffer memory
        return false;
    }


    // Create vertex buffer
    if (!vertexBuffer.createBuffer(
        physicalDevice, vulkanDevice, vulkanMemory,
        VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
        VULKAN_MEMORY_RENDERDEVICE, verticesCount))
    {
        // Could not create vertex buffer
        return false;
    }


    // Allocate command buffers
    VkCommandBuffer commandBuffer = 0;
    VkCommandBufferAllocateInfo bufferAllocate;
    bufferAllocate.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    bufferAllocate.pNext = 0;
    bufferAllocate.commandPool = commandPool;
    bufferAllocate.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    bufferAllocate.commandBufferCount = 1;

    if (vkAllocateCommandBuffers(
        vulkanDevice, &bufferAllocate, &commandBuffer) != VK_SUCCESS)
    {
        // Could not allocate command buffers
        return false;
    }

    // Transfert staging buffer data to vertex buffer
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
    bufferCopy.size = vertexStagingBuffer.size;

    vkCmdCopyBuffer(
        commandBuffer, vertexStagingBuffer.handle,
        vertexBuffer.handle, 1, &bufferCopy
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
    if (vkWaitForFences(vulkanDevice, 1,
        &fence, VK_FALSE, VertexBufferFenceTimeout) != VK_SUCCESS)
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
        vkFreeCommandBuffers(vulkanDevice, commandPool, 1, &commandBuffer);
    }


    // Create index staging buffer
    if (!indexStagingBuffer.createBuffer(
        physicalDevice, vulkanDevice, vulkanMemory,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VULKAN_MEMORY_RENDERHOST, indicesCount))
    {
        // Could not create staging buffer
        return false;
    }

    // Write indices into staging buffer memory
    if (!vulkanMemory.writeBufferMemory(
        vulkanDevice, indexStagingBuffer, indices, VULKAN_MEMORY_RENDERHOST))
    {
        // Could not write indices into staging buffer memory
        return false;
    }


    // Create index buffer
    if (!indexBuffer.createBuffer(
        physicalDevice, vulkanDevice, vulkanMemory,
        VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
        VULKAN_MEMORY_RENDERDEVICE, indicesCount))
    {
        // Could not create index buffer
        return false;
    }


    // Allocate command buffers
    commandBuffer = 0;
    bufferAllocate.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    bufferAllocate.pNext = 0;
    bufferAllocate.commandPool = commandPool;
    bufferAllocate.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    bufferAllocate.commandBufferCount = 1;

    if (vkAllocateCommandBuffers(
        vulkanDevice, &bufferAllocate, &commandBuffer) != VK_SUCCESS)
    {
        // Could not allocate command buffers
        return false;
    }


    // Transfert staging buffer data to vertex buffer
    bufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    bufferBeginInfo.pNext = 0;
    bufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    bufferBeginInfo.pInheritanceInfo = 0;

    if (vkBeginCommandBuffer(commandBuffer, &bufferBeginInfo) != VK_SUCCESS)
    {
        // Could not record command buffer
        return false;
    }

    bufferCopy.srcOffset = 0;
    bufferCopy.dstOffset = 0;
    bufferCopy.size = indexStagingBuffer.size;

    vkCmdCopyBuffer(
        commandBuffer, indexStagingBuffer.handle,
        indexBuffer.handle, 1, &bufferCopy
    );

    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
    {
        // Could not end command buffer
        return false;
    }

    fence = 0;
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
    if (vkWaitForFences(vulkanDevice, 1,
        &fence, VK_FALSE, VertexBufferFenceTimeout) != VK_SUCCESS)
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
        vkFreeCommandBuffers(vulkanDevice, commandPool, 1, &commandBuffer);
    }

    // Vertex buffer successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Update Vertex buffer                                                      //
//  return : True if Vertex buffer is successfully updated                    //
////////////////////////////////////////////////////////////////////////////////
bool VertexBuffer::updateBuffer(VkPhysicalDevice& physicalDevice,
    VkDevice& vulkanDevice, VulkanMemory& vulkanMemory,
    VkCommandPool& commandPool, VulkanQueue& transferQueue,
    const float* vertices, const uint16_t* indices,
    uint32_t verticesCount, uint32_t indicesCount)
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
    if (!commandPool)
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

    // Check input vertices and indices
    if (!vertices || !indices || (verticesCount <= 0) || (indicesCount <= 0))
    {
        return false;
    }

    // Check current buffers
    if (!indexBuffer.handle || !indexStagingBuffer.handle ||
        !vertexBuffer.handle || !vertexStagingBuffer.handle)
    {
        // Invalid current buffers
        return false;
    }

    // Compute vertices and indices sizes
    verticesCount *= sizeof(float);
    indicesCount *= sizeof(uint16_t);


    // Write vertices into staging buffer memory
    if (!vulkanMemory.writeBufferMemory(
        vulkanDevice, vertexStagingBuffer, vertices, VULKAN_MEMORY_RENDERHOST))
    {
        // Could not write vertices into staging buffer memory
        return false;
    }


    // Allocate command buffers
    VkCommandBuffer commandBuffer = 0;
    VkCommandBufferAllocateInfo bufferAllocate;
    bufferAllocate.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    bufferAllocate.pNext = 0;
    bufferAllocate.commandPool = commandPool;
    bufferAllocate.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    bufferAllocate.commandBufferCount = 1;

    if (vkAllocateCommandBuffers(
        vulkanDevice, &bufferAllocate, &commandBuffer) != VK_SUCCESS)
    {
        // Could not allocate command buffers
        return false;
    }

    // Transfert staging buffer data to vertex buffer
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
    bufferCopy.size = vertexStagingBuffer.size;

    vkCmdCopyBuffer(
        commandBuffer, vertexStagingBuffer.handle,
        vertexBuffer.handle, 1, &bufferCopy
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
    if (vkWaitForFences(vulkanDevice, 1,
        &fence, VK_FALSE, VertexBufferFenceTimeout) != VK_SUCCESS)
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
        vkFreeCommandBuffers(vulkanDevice, commandPool, 1, &commandBuffer);
    }


    // Write indices into staging buffer memory
    if (!vulkanMemory.writeBufferMemory(
        vulkanDevice, indexStagingBuffer, indices, VULKAN_MEMORY_RENDERHOST))
    {
        // Could not write indices into staging buffer memory
        return false;
    }


    // Allocate command buffers
    commandBuffer = 0;
    bufferAllocate.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    bufferAllocate.pNext = 0;
    bufferAllocate.commandPool = commandPool;
    bufferAllocate.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    bufferAllocate.commandBufferCount = 1;

    if (vkAllocateCommandBuffers(
        vulkanDevice, &bufferAllocate, &commandBuffer) != VK_SUCCESS)
    {
        // Could not allocate command buffers
        return false;
    }


    // Transfert staging buffer data to vertex buffer
    bufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    bufferBeginInfo.pNext = 0;
    bufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    bufferBeginInfo.pInheritanceInfo = 0;

    if (vkBeginCommandBuffer(commandBuffer, &bufferBeginInfo) != VK_SUCCESS)
    {
        // Could not record command buffer
        return false;
    }

    bufferCopy.srcOffset = 0;
    bufferCopy.dstOffset = 0;
    bufferCopy.size = indexStagingBuffer.size;

    vkCmdCopyBuffer(
        commandBuffer, indexStagingBuffer.handle,
        indexBuffer.handle, 1, &bufferCopy
    );

    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
    {
        // Could not end command buffer
        return false;
    }

    fence = 0;
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
    if (vkWaitForFences(vulkanDevice, 1,
        &fence, VK_FALSE, VertexBufferFenceTimeout) != VK_SUCCESS)
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
        vkFreeCommandBuffers(vulkanDevice, commandPool, 1, &commandBuffer);
    }

    // Vertex buffer successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy Vertex buffer                                                     //
////////////////////////////////////////////////////////////////////////////////
void VertexBuffer::destroyBuffer(VkDevice& vulkanDevice)
{
    indexStagingBuffer.destroyBuffer(vulkanDevice);
    indexBuffer.destroyBuffer(vulkanDevice);
    vertexStagingBuffer.destroyBuffer(vulkanDevice);
    vertexBuffer.destroyBuffer(vulkanDevice);
}
