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
//     Renderer/VertexBuffer.cpp : Vertex buffer management                   //
////////////////////////////////////////////////////////////////////////////////
#include "VertexBuffer.h"


////////////////////////////////////////////////////////////////////////////////
//  VertexBuffer default constructor                                          //
////////////////////////////////////////////////////////////////////////////////
VertexBuffer::VertexBuffer() :
vertexBuffer(),
indexBuffer()
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
    VkDevice& vulkanDevice, VkCommandPool& commandsPool,
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

    // Check current buffers
    if (vertexBuffer.handle || indexBuffer.handle)
    {
        // Destroy current buffer
        destroyBuffer(vulkanDevice);
    }

    // Vertices
    VertexData vertices[4];
    vertices[0].x = -0.8f;  vertices[0].y = -0.8f;  vertices[0].z = 0.0f;
    vertices[1].x = 0.8f;   vertices[1].y = -0.8f;  vertices[1].z = 0.0f;
    vertices[2].x = 0.8f;   vertices[2].y = 0.8f;   vertices[2].z = 0.0f;
    vertices[3].x = -0.8f;  vertices[3].y = 0.8f;   vertices[3].z = 0.0f;

    vertices[0].u = 0.0f;   vertices[0].v = 1.0f;
    vertices[1].u = 1.0f;   vertices[1].v = 1.0f;
    vertices[2].u = 1.0f;   vertices[2].v = 0.0f;
    vertices[3].u = 0.0f;   vertices[3].v = 0.0f;

    // Indices
    uint16_t indices[6];
    indices[0] = 0; indices[1] = 1; indices[2] = 2;
    indices[3] = 2; indices[4] = 3; indices[5] = 0;


    // Create staging buffer
    VulkanBuffer stagingBuffer;
    stagingBuffer.size = sizeof(vertices);

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
        return false;
        // Could not map staging buffer memory
    }
    if (!stagingBufferMemory)
    {
        // Invalid staging buffer memory
        return false;
    }

    // Copy vertices into staging buffer memory
    memcpy(stagingBufferMemory, vertices, stagingBuffer.size);

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


    // Create vertex buffer
    vertexBuffer.size = sizeof(vertices);

    if (!vertexBuffer.createBuffer(
        physicalDevice, vulkanDevice,
        VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT))
    {
        // Could not create vertex buffer
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

    if (vkAllocateCommandBuffers(vulkanDevice,
        &bufferAllocate, &commandBuffer) != VK_SUCCESS)
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
    bufferCopy.size = stagingBuffer.size;

    vkCmdCopyBuffer(
        commandBuffer, stagingBuffer.handle,
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
    if (vkWaitForFences(
        vulkanDevice, 1, &fence, VK_FALSE, 100000000000) != VK_SUCCESS)
    {
        // Transfer timed out
        return false;
    }

    // Destroy fence
    if (fence && vkDestroyFence)
    {
        vkDestroyFence(vulkanDevice, fence, 0);
    }

    if (commandBuffer)
    {
        vkFreeCommandBuffers(
            vulkanDevice, commandsPool, 1, &commandBuffer
        );
    }
    stagingBuffer.destroyBuffer(vulkanDevice);


    // Create index buffer
    stagingBuffer.size = sizeof(indices);

    if (!stagingBuffer.createBuffer(
        physicalDevice, vulkanDevice,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
        VK_MEMORY_PROPERTY_HOST_COHERENT_BIT))
    {
        // Could not create staging buffer
        return false;
    }

    // Map staging buffer memory
    stagingBufferMemory = 0;
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

    // Copy vertices into staging buffer memory
    memcpy(stagingBufferMemory, indices, stagingBuffer.size);

    // Unmap staging buffer memory
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


    // Create index buffer
    indexBuffer.size = sizeof(indices);

    if (!indexBuffer.createBuffer(
        physicalDevice, vulkanDevice,
        VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT))
    {
        // Could not create index buffer
        return false;
    }


    // Allocate command buffers
    commandBuffer = 0;
    bufferAllocate.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    bufferAllocate.pNext = 0;
    bufferAllocate.commandPool = commandsPool;
    bufferAllocate.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    bufferAllocate.commandBufferCount = 1;

    if (vkAllocateCommandBuffers(vulkanDevice,
        &bufferAllocate, &commandBuffer) != VK_SUCCESS)
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
    bufferCopy.size = stagingBuffer.size;

    vkCmdCopyBuffer(
        commandBuffer, stagingBuffer.handle,
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
    if (vkWaitForFences(
        vulkanDevice, 1, &fence, VK_FALSE, 100000000000) != VK_SUCCESS)
    {
        // Transfer timed out
        return false;
    }

    // Destroy fence
    if (fence && vkDestroyFence)
    {
        vkDestroyFence(vulkanDevice, fence, 0);
    }

    // Destroy buffers
    if (commandBuffer)
    {
        vkFreeCommandBuffers(
            vulkanDevice, commandsPool, 1, &commandBuffer
        );
    }
    stagingBuffer.destroyBuffer(vulkanDevice);

    // Vertex buffer successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy Vertex buffer                                                     //
////////////////////////////////////////////////////////////////////////////////
void VertexBuffer::destroyBuffer(VkDevice& vulkanDevice)
{
    indexBuffer.destroyBuffer(vulkanDevice);
    vertexBuffer.destroyBuffer(vulkanDevice);
}