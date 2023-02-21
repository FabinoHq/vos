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
//     Resources/HeightMapLoader.cpp : HeightMap loading management           //
////////////////////////////////////////////////////////////////////////////////
#include "HeightMapLoader.h"


////////////////////////////////////////////////////////////////////////////////
//  HeightMapLoader default constructor                                       //
////////////////////////////////////////////////////////////////////////////////
HeightMapLoader::HeightMapLoader() :
m_state(HEIGHTMAPLOADER_STATE_NONE),
m_stateMutex(),
m_transferQueue(),
m_commandPool(0),
m_commandBuffer(0),
m_stagingBuffer(),
m_fence(0),
m_sync(0),
m_heightmaps(0),
m_vertices(0),
m_indices(0),
m_chunkX(0),
m_chunkY(0)
{
    for (int i = 0; i < HEIGHTMAP_ASSETSCOUNT; ++i)
    {
        m_chunks[i].loading = false;
        m_chunks[i].chunkX = 0;
        m_chunks[i].chunkY = 0;
        m_chunks[i].flags = HEIGHTMAP_FLAGS_NONE;
        m_chunks[i].heightmap = 0;
        m_chunksptrs[i] = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  HeightMapLoader virtual destructor                                        //
////////////////////////////////////////////////////////////////////////////////
HeightMapLoader::~HeightMapLoader()
{
    m_chunkY = 0;
    m_chunkX = 0;
    if (m_indices) { delete[] m_indices; }
    m_indices = 0;
    if (m_vertices) { delete[] m_vertices; }
    m_vertices = 0;
    for (int i = 0; i < HEIGHTMAP_ASSETSCOUNT; ++i)
    {
        m_chunks[i].loading = false;
        m_chunks[i].chunkX = 0;
        m_chunks[i].chunkY = 0;
        m_chunks[i].flags = HEIGHTMAP_FLAGS_NONE;
        m_chunks[i].heightmap = 0;
        m_chunksptrs[i] = 0;
    }
    m_heightmaps = 0;
    m_sync = 0;
    m_fence = 0;
    m_commandBuffer = 0;
    m_commandPool = 0;
    m_state = HEIGHTMAPLOADER_STATE_NONE;
}


////////////////////////////////////////////////////////////////////////////////
//  HeightMapLoader thread process                                            //
////////////////////////////////////////////////////////////////////////////////
void HeightMapLoader::process()
{
    HeightMapLoaderState state = HEIGHTMAPLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();

    switch (state)
    {
        case HEIGHTMAPLOADER_STATE_NONE:
            // Boot to init state
            m_stateMutex.lock();
            m_state = HEIGHTMAPLOADER_STATE_INIT;
            m_stateMutex.unlock();
            break;

        case HEIGHTMAPLOADER_STATE_INIT:
            // Init heightmap loader
            if (init())
            {
                m_stateMutex.lock();
                m_state = HEIGHTMAPLOADER_STATE_IDLE;
                m_stateMutex.unlock();
            }
            else
            {
                m_stateMutex.lock();
                m_state = HEIGHTMAPLOADER_STATE_ERROR;
                m_stateMutex.unlock();
            }
            break;

        case HEIGHTMAPLOADER_STATE_IDLE:
            // HeightMap loader in idle state
            SysSleep(HeightMapLoaderIdleSleepTime);
            break;

        case HEIGHTMAPLOADER_STATE_SYNC:
            // HeightMap loader in sync state
            break;

        case HEIGHTMAPLOADER_STATE_LOAD:
            // Load heightmaps assets
            if (loadHeightMaps())
            {
                m_stateMutex.lock();
                m_state = HEIGHTMAPLOADER_STATE_IDLE;
                m_stateMutex.unlock();
            }
            else
            {
                m_stateMutex.lock();
                m_state = HEIGHTMAPLOADER_STATE_ERROR;
                m_stateMutex.unlock();
            }
            break;

        case HEIGHTMAPLOADER_STATE_ERROR:
            // HeightMap loader error
            SysSleep(HeightMapLoaderErrorSleepTime);
            break;

        default:
            // Invalid state
            m_stateMutex.lock();
            m_state = HEIGHTMAPLOADER_STATE_ERROR;
            m_stateMutex.unlock();
            break;
    }
}


////////////////////////////////////////////////////////////////////////////////
//  Init HeightMapLoader                                                      //
//  return : True if heightmap loader is ready                                //
////////////////////////////////////////////////////////////////////////////////
bool HeightMapLoader::init()
{
    // Request transfer queue handle
    if (!m_transferQueue.getVulkanQueue(VULKAN_QUEUE_HEIGHTMAPS))
    {
        // Could not get transfer queue handle
        return false;
    }

    // Create command pool
    VkCommandPoolCreateInfo commandPoolInfo;
    commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolInfo.pNext = 0;
    commandPoolInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
    commandPoolInfo.queueFamilyIndex = m_transferQueue.family;

    if (vkCreateCommandPool(GVulkanDevice,
        &commandPoolInfo, 0, &m_commandPool) != VK_SUCCESS)
    {
        // Could not create commands pool
        return false;
    }
    if (!m_commandPool)
    {
        // Invalid commands pool
        return false;
    }

    // Allocate command buffer
    VkCommandBufferAllocateInfo bufferAllocate;
    bufferAllocate.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    bufferAllocate.pNext = 0;
    bufferAllocate.commandPool = m_commandPool;
    bufferAllocate.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    bufferAllocate.commandBufferCount = 1;

    if (vkAllocateCommandBuffers(GVulkanDevice,
        &bufferAllocate, &m_commandBuffer) != VK_SUCCESS)
    {
        // Could not allocate command buffer
        return false;
    }
    if (!m_commandBuffer)
    {
        // Invalid command buffer
        return false;
    }

    // Create staging fence
    VkFenceCreateInfo fenceInfo;
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.pNext = 0;
    fenceInfo.flags = 0;

    if (vkCreateFence(GVulkanDevice,
        &fenceInfo, 0, &m_fence) != VK_SUCCESS)
    {
        // Could not create staging fence
        return false;
    }
    if (!m_fence)
    {
        // Invalid staging fence
        return false;
    }

    // Allocate heightmaps vertex buffers
    m_heightmaps = new (std::nothrow) VertexBuffer[HEIGHTMAP_ASSETSCOUNT];
    if (!m_heightmaps)
    {
        // Could not allocate heightmaps vertex buffers
        return false;
    }

    // Set default chunks pointers
    for (int i = 0; i < HEIGHTMAP_ASSETSCOUNT; ++i)
    {
        m_chunks[i].heightmap = &m_heightmaps[i];
        m_chunksptrs[i] = &m_chunks[i];
    }

    // Allocate chunk vertices
    m_vertices = new (std::nothrow) float[HeightMapChunkVerticesCount];
    if (!m_vertices)
    {
        // Could not allocate chunk vertices
        return false;
    }

    // Allocate chunk indices
    m_indices = new (std::nothrow) uint16_t[HeightMapChunkIndicesCount];
    if (!m_indices)
    {
        // Could not allocate chunk indices
        return false;
    }

    // Create default heightmap
    int32_t cnt = 0;
    for (int32_t j = 0; j < HEIGHTMAP_STREAMHEIGHT; ++j)
    {
        for (int32_t i = 0; i < HEIGHTMAP_STREAMWIDTH; ++i)
        {
            if (generateFlatChunk(m_chunks[cnt]))
            {
                m_chunks[cnt].loading = false;
                m_chunks[cnt].chunkX = (m_chunkX-HEIGHTMAP_STREAMHALFWIDTH)+i;
                m_chunks[cnt].chunkY = (m_chunkY-HEIGHTMAP_STREAMHALFHEIGHT)+j;
            }
            else
            {
                // Could not create default heightmap
                return false;
            }
            ++cnt;
        }
    }

    // Reset renderer sync
    m_sync = 0;

    // Heightmap loader ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Get heightmap loader state                                                //
//  return : Current heightmap loader state                                   //
////////////////////////////////////////////////////////////////////////////////
HeightMapLoaderState HeightMapLoader::getState()
{
    HeightMapLoaderState state = HEIGHTMAPLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();
    return state;
}

////////////////////////////////////////////////////////////////////////////////
//  Reload heightmaps pointers based on current chunk position                //
//  return : True if heightmaps pointers are reloaded                         //
////////////////////////////////////////////////////////////////////////////////
bool HeightMapLoader::reload(int32_t chunkX, int32_t chunkY)
{
    // Check current loading state
    HeightMapLoaderState state = HEIGHTMAPLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();
    if (state != HEIGHTMAPLOADER_STATE_IDLE)
    {
        // Heightmap loader is still in loading state
        return false;
    }

    // Set chunkX and chunkY
    m_chunkX = chunkX;
    m_chunkY = chunkY;

    // Set chunks loading states
    int32_t cnt = 0;
    for (int32_t j = 0; j < HEIGHTMAP_STREAMHEIGHT; ++j)
    {
        for (int32_t i = 0; i < HEIGHTMAP_STREAMWIDTH; ++i)
        {
            m_chunks[cnt].loading = true;
            m_chunks[cnt].chunkX = (m_chunkX-HEIGHTMAP_STREAMHALFWIDTH)+i;
            m_chunks[cnt].chunkY = (m_chunkY-HEIGHTMAP_STREAMHALFHEIGHT)+j;
            ++cnt;
        }
    }

    // Reset renderer sync
    m_sync = 0;

    // Load new chunks
    m_stateMutex.lock();
    m_state = HEIGHTMAPLOADER_STATE_LOAD;
    m_stateMutex.unlock();
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Update heightmaps pointers based on current chunk position                //
//  return : True if heightmaps pointers are updated                          //
////////////////////////////////////////////////////////////////////////////////
bool HeightMapLoader::update(int32_t chunkX, int32_t chunkY)
{
    // Synchronize swap with renderer
    if (m_sync > 0)
    {
        // Heightmap loader is still in sync state
        return false;
    }

    // Check Y chunk position
    if (chunkY < m_chunkY)
    {
        return swapTop();
    }
    if (chunkY > m_chunkY)
    {
        return swapBottom();
    }

    // Check X chunk position
    if (chunkX < m_chunkX)
    {
        return swapLeft();
    }
    if (chunkX > m_chunkX)
    {
        return swapRight();
    }

    // Heightmaps pointers are up to date
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Synchronize heightmaps pointers with renderer                             //
////////////////////////////////////////////////////////////////////////////////
void HeightMapLoader::sync()
{
    // Synchronize swap with renderer
    if (m_sync > 0)
    {
        // Wait for current swapchain frames to be rendered
        ++m_sync;
        if (m_sync > HeightMapLoaderSyncFrames)
        {
            // Load new chunks
            m_sync = 0;
            m_stateMutex.lock();
            m_state = HEIGHTMAPLOADER_STATE_LOAD;
            m_stateMutex.unlock();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy heightmap loader                                                  //
////////////////////////////////////////////////////////////////////////////////
void HeightMapLoader::destroyHeightMapLoader()
{
    // Reset chunk position
    m_chunkY = 0;
    m_chunkX = 0;

    // Delete indices and vertices
    if (m_indices) { delete[] m_indices; }
    m_indices = 0;
    if (m_vertices) { delete[] m_vertices; }
    m_vertices = 0;

    // Reset heightmaps pointers
    for (int i = 0; i < HEIGHTMAP_ASSETSCOUNT; ++i)
    {
        m_chunks[i].loading = false;
        m_chunks[i].chunkX = 0;
        m_chunks[i].chunkY = 0;
        m_chunks[i].flags = HEIGHTMAP_FLAGS_NONE;
        m_chunks[i].heightmap = 0;
        m_chunksptrs[i] = 0;
    }

    // Destroy heightmaps vertex buffers
    for (int i = 0; i < HEIGHTMAP_ASSETSCOUNT; ++i)
    {
        m_heightmaps[i].destroyBuffer();
    }
    if (m_heightmaps) { delete[] m_heightmaps; }
    m_heightmaps = 0;

    // Reset renderer sync
    m_sync = 0;

    // Destroy staging fence
    if (m_fence)
    {
        vkDestroyFence(GVulkanDevice, m_fence, 0);
    }
    m_fence = 0;

    // Destroy staging buffer
    m_stagingBuffer.destroyBuffer();

    // Destroy command buffer
    if (m_commandBuffer)
    {
        vkFreeCommandBuffers(GVulkanDevice,
            m_commandPool, 1, &m_commandBuffer
        );
    }
    m_commandBuffer = 0;

    // Destroy command pool
    if (m_commandPool)
    {
        vkDestroyCommandPool(GVulkanDevice, m_commandPool, 0);
    }
    m_commandPool = 0;

    // Reset state
    m_state = HEIGHTMAPLOADER_STATE_NONE;
}


////////////////////////////////////////////////////////////////////////////////
//  Upload vertex buffer to graphics memory                                   //
//  return : True if vertex buffer is successfully uploaded                   //
////////////////////////////////////////////////////////////////////////////////
bool HeightMapLoader::uploadVertexBuffer(VertexBuffer& vertexBuffer,
    const float* vertices, const uint16_t* indices,
    uint32_t verticesCount, uint32_t indicesCount)
{
    // Reset mesh upload memory
    GVulkanMemory.resetMemory(VULKAN_MEMORY_HEIGHTMAPUPLOAD);

    // Create vertices staging buffer
    if (!m_stagingBuffer.createBuffer(VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VULKAN_MEMORY_HEIGHTMAPUPLOAD, verticesCount))
    {
        // Could not create vertices staging buffer
        return false;
    }

    // Write vertices into staging buffer memory
    if (!GVulkanMemory.writeBufferMemory(
        m_stagingBuffer, vertices, VULKAN_MEMORY_HEIGHTMAPUPLOAD))
    {
        // Could not write vertices into staging buffer memory
        return false;
    }


    // Reset command pool
    if (vkResetCommandPool(GVulkanDevice, m_commandPool, 0) != VK_SUCCESS)
    {
        // Could not reset command pool
        return false;
    }

    // Transfer staging buffer data to vertex buffer
    VkCommandBufferBeginInfo bufferBeginInfo;
    bufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    bufferBeginInfo.pNext = 0;
    bufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    bufferBeginInfo.pInheritanceInfo = 0;

    if (vkBeginCommandBuffer(m_commandBuffer, &bufferBeginInfo) != VK_SUCCESS)
    {
        // Could not record command buffer
        return false;
    }

    // Barrier from vertex input to transfer
    VkBufferMemoryBarrier vertexInputToTransfer;
    vertexInputToTransfer.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    vertexInputToTransfer.pNext = 0;
    vertexInputToTransfer.srcAccessMask = VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;
    vertexInputToTransfer.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    vertexInputToTransfer.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    vertexInputToTransfer.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    vertexInputToTransfer.buffer = vertexBuffer.vertexBuffer.handle;
    vertexInputToTransfer.offset = 0;
    vertexInputToTransfer.size = VK_WHOLE_SIZE;

    vkCmdPipelineBarrier(
        m_commandBuffer,
        VK_PIPELINE_STAGE_VERTEX_INPUT_BIT,
        VK_PIPELINE_STAGE_TRANSFER_BIT,
        0, 0, 0, 1, &vertexInputToTransfer, 0, 0
    );

    VkBufferCopy bufferCopy;
    bufferCopy.srcOffset = 0;
    bufferCopy.dstOffset = 0;
    bufferCopy.size = m_stagingBuffer.size;

    vkCmdCopyBuffer(
        m_commandBuffer, m_stagingBuffer.handle,
        vertexBuffer.vertexBuffer.handle, 1, &bufferCopy
    );

    // Barrier from transfer to vertex input
    VkBufferMemoryBarrier transferToVertexInput;
    transferToVertexInput.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    transferToVertexInput.pNext = 0;
    transferToVertexInput.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    transferToVertexInput.dstAccessMask = VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;
    transferToVertexInput.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    transferToVertexInput.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    transferToVertexInput.buffer = vertexBuffer.vertexBuffer.handle;
    transferToVertexInput.offset = 0;
    transferToVertexInput.size = VK_WHOLE_SIZE;

    vkCmdPipelineBarrier(
        m_commandBuffer,
        VK_PIPELINE_STAGE_TRANSFER_BIT,
        VK_PIPELINE_STAGE_VERTEX_INPUT_BIT,
        0, 0, 0, 1, &transferToVertexInput, 0, 0
    );

    if (vkEndCommandBuffer(m_commandBuffer) != VK_SUCCESS)
    {
        // Could not end command buffer
        return false;
    }

    // Reset staging fence
    if (vkResetFences(GVulkanDevice, 1, &m_fence) != VK_SUCCESS)
    {
        // Could not reset staging fence
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
    submitInfo.pCommandBuffers = &m_commandBuffer;
    submitInfo.signalSemaphoreCount = 0;
    submitInfo.pSignalSemaphores = 0;

    if (m_transferQueue.shared > 0)
    {
        // Shared queue
        GVulkanQueues.queueMutex[m_transferQueue.shared].lock();
        if (vkQueueSubmit(
            m_transferQueue.handle, 1, &submitInfo, m_fence) != VK_SUCCESS)
        {
            // Could not submit queue
            GVulkanQueues.queueMutex[m_transferQueue.shared].unlock();
            return false;
        }
        GVulkanQueues.queueMutex[m_transferQueue.shared].unlock();
    }
    else
    {
        // Dedicated queue
        if (vkQueueSubmit(
            m_transferQueue.handle, 1, &submitInfo, m_fence) != VK_SUCCESS)
        {
            // Could not submit queue
            return false;
        }
    }

    // Wait for transfer to finish
    if (vkWaitForFences(GVulkanDevice, 1,
        &m_fence, VK_FALSE, HeightMapFenceTimeout) != VK_SUCCESS)
    {
        // Transfer timed out
        return false;
    }

    // Destroy vertices staging buffer
    m_stagingBuffer.destroyBuffer();


    // Reset mesh upload memory
    GVulkanMemory.resetMemory(VULKAN_MEMORY_HEIGHTMAPUPLOAD);

    // Create indices staging buffer
    if (!m_stagingBuffer.createBuffer(VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VULKAN_MEMORY_HEIGHTMAPUPLOAD, indicesCount))
    {
        // Could not create indices staging buffer
        return false;
    }

    // Write indices into staging buffer memory
    if (!GVulkanMemory.writeBufferMemory(
        m_stagingBuffer, indices, VULKAN_MEMORY_HEIGHTMAPUPLOAD))
    {
        // Could not write indices into staging buffer memory
        return false;
    }


    // Reset command pool
    if (vkResetCommandPool(GVulkanDevice, m_commandPool, 0) != VK_SUCCESS)
    {
        // Could not reset command pool
        return false;
    }

    // Transfer staging buffer indices to vertex buffer
    bufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    bufferBeginInfo.pNext = 0;
    bufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    bufferBeginInfo.pInheritanceInfo = 0;

    if (vkBeginCommandBuffer(m_commandBuffer, &bufferBeginInfo) != VK_SUCCESS)
    {
        // Could not record command buffer
        return false;
    }

    // Barrier from index input to transfer
    VkBufferMemoryBarrier indexInputToTransfer;
    indexInputToTransfer.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    indexInputToTransfer.pNext = 0;
    indexInputToTransfer.srcAccessMask = VK_ACCESS_INDEX_READ_BIT;
    indexInputToTransfer.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    indexInputToTransfer.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    indexInputToTransfer.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    indexInputToTransfer.buffer = vertexBuffer.indexBuffer.handle;
    indexInputToTransfer.offset = 0;
    indexInputToTransfer.size = VK_WHOLE_SIZE;

    vkCmdPipelineBarrier(
        m_commandBuffer,
        VK_PIPELINE_STAGE_VERTEX_INPUT_BIT,
        VK_PIPELINE_STAGE_TRANSFER_BIT,
        0, 0, 0, 1, &indexInputToTransfer, 0, 0
    );

    bufferCopy.srcOffset = 0;
    bufferCopy.dstOffset = 0;
    bufferCopy.size = m_stagingBuffer.size;

    vkCmdCopyBuffer(
        m_commandBuffer, m_stagingBuffer.handle,
        vertexBuffer.indexBuffer.handle, 1, &bufferCopy
    );

    // Barrier from transfer to index input
    VkBufferMemoryBarrier transferToIndexInput;
    transferToIndexInput.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    transferToIndexInput.pNext = 0;
    transferToIndexInput.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    transferToIndexInput.dstAccessMask = VK_ACCESS_INDEX_READ_BIT;
    transferToIndexInput.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    transferToIndexInput.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    transferToIndexInput.buffer = vertexBuffer.indexBuffer.handle;
    transferToIndexInput.offset = 0;
    transferToIndexInput.size = VK_WHOLE_SIZE;

    vkCmdPipelineBarrier(
        m_commandBuffer,
        VK_PIPELINE_STAGE_TRANSFER_BIT,
        VK_PIPELINE_STAGE_VERTEX_INPUT_BIT,
        0, 0, 0, 1, &transferToIndexInput, 0, 0
    );

    if (vkEndCommandBuffer(m_commandBuffer) != VK_SUCCESS)
    {
        // Could not end command buffer
        return false;
    }

    // Reset staging fence
    if (vkResetFences(GVulkanDevice, 1, &m_fence) != VK_SUCCESS)
    {
        // Could not reset staging fence
        return false;
    }

    // Submit queue
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.pNext = 0;
    submitInfo.waitSemaphoreCount = 0;
    submitInfo.pWaitSemaphores = 0;
    submitInfo.pWaitDstStageMask = 0;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &m_commandBuffer;
    submitInfo.signalSemaphoreCount = 0;
    submitInfo.pSignalSemaphores = 0;

    if (m_transferQueue.shared > 0)
    {
        // Shared queue
        GVulkanQueues.queueMutex[m_transferQueue.shared].lock();
        if (vkQueueSubmit(
            m_transferQueue.handle, 1, &submitInfo, m_fence) != VK_SUCCESS)
        {
            // Could not submit queue
            GVulkanQueues.queueMutex[m_transferQueue.shared].unlock();
            return false;
        }
        GVulkanQueues.queueMutex[m_transferQueue.shared].unlock();
    }
    else
    {
        // Dedicated queue
        if (vkQueueSubmit(
            m_transferQueue.handle, 1, &submitInfo, m_fence) != VK_SUCCESS)
        {
            // Could not submit queue
            return false;
        }
    }

    // Wait for transfer to finish
    if (vkWaitForFences(GVulkanDevice, 1,
        &m_fence, VK_FALSE, HeightMapFenceTimeout) != VK_SUCCESS)
    {
        // Transfer timed out
        return false;
    }

    // Destroy indices staging buffer
    m_stagingBuffer.destroyBuffer();


    // Vertex buffer successfully uploaded
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Load heightmaps assets                                                    //
//  return : True if heightmaps assets are loaded                             //
////////////////////////////////////////////////////////////////////////////////
bool HeightMapLoader::loadHeightMaps()
{
    for (int i = 0; i < HEIGHTMAP_ASSETSCOUNT; ++i)
    {
        // Heightmap needs update
        if (m_chunks[i].loading)
        {
            // Update chunk from file
            if (updateChunk(
                (*m_chunksptrs[i]), m_chunks[i].chunkX, m_chunks[i].chunkY))
            {
                m_chunks[i].loading = false;
            }
            else
            {
                // Update flat chunk
                if (updateFlatChunk(*m_chunksptrs[i]))
                {
                    m_chunks[i].loading = false;
                }
                else
                {
                    // Could not update heightmap
                    return false;
                }
            }
        }
    }

    // Heightmaps assets are successfully loaded
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Generate flat heightmap chunk                                             //
//  return : True if the heightmap chunk is generated                         //
////////////////////////////////////////////////////////////////////////////////
bool HeightMapLoader::generateFlatChunk(HeightMapChunkData& chunkData)
{
    // Generate vertices data
    float texCoordIncX = HeightMapChunkTexcoordsWidth /
        (HeightMapChunkWidth * 1.0f);
    float texCoordIncY = HeightMapChunkTexcoordsHeight /
        (HeightMapChunkHeight * 1.0f);
    float vertX = 0.0f;
    float vertZ = 0.0f;
    float texCoordX = 0.0f;
    float texCoordY = 0.0f;
    uint32_t vIndex = 0;
    uint32_t iIndex = 0;
    uint16_t iOffset = 0;

    // Flat heightmap chunk
    for (uint32_t j = 0; j <= HeightMapChunkHeight; ++j)
    {
        vertX = 0.0f;
        texCoordX = 0.0f;

        for (uint32_t i = 0; i <= HeightMapChunkWidth; ++i)
        {
            // Set flat heightmap
            m_vertices[vIndex+0] = vertX;
            m_vertices[vIndex+1] = HeightMapLoaderDefaultFlatY;
            m_vertices[vIndex+2] = vertZ;

            m_vertices[vIndex+3] = texCoordX;
            m_vertices[vIndex+4] = texCoordY;

            m_vertices[vIndex+5] = 0.0f;
            m_vertices[vIndex+6] = 1.0f;
            m_vertices[vIndex+7] = 0.0f;

            vIndex += 8;
            vertX += HeightMapChunkPlaneWidth;
            texCoordX += texCoordIncX;
        }

        vertZ += HeightMapChunkPlaneHeight;
        texCoordY += texCoordIncY;
    }

    // Generate indices data
    for (uint32_t j = 0; j < HeightMapChunkHeight; ++j)
    {
        for (uint32_t i = 0; i < HeightMapChunkWidth; ++i)
        {
            m_indices[iIndex+0] = iOffset+(HeightMapChunkWidth+1);
            m_indices[iIndex+1] = iOffset+(HeightMapChunkWidth+2);
            m_indices[iIndex+2] = iOffset+1;
            m_indices[iIndex+3] = iOffset+1;
            m_indices[iIndex+4] = iOffset;
            m_indices[iIndex+5] = iOffset+(HeightMapChunkWidth+1);

            iIndex += 6;
            ++iOffset;
        }
        ++iOffset;
    }

    // Set heightmap chunk flags
    chunkData.flags = HEIGHTMAP_FLAGS_NONE;

    // Create vertex buffer
    if (!chunkData.heightmap->createHeightMapBuffer(VULKAN_MEMORY_HEIGHTMAPS,
        m_vertices, m_indices,
        HeightMapChunkVerticesCount, HeightMapChunkIndicesCount))
    {
        // Could not create vertex buffer
        return false;
    }

    // Heightmap chunk successfully generated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Update flat heightmap chunk                                               //
//  return : True if the heightmap chunk is updated                           //
////////////////////////////////////////////////////////////////////////////////
bool HeightMapLoader::updateFlatChunk(HeightMapChunkData& chunkData)
{
    // Generate vertices data
    float texCoordIncX = HeightMapChunkTexcoordsWidth /
        (HeightMapChunkWidth * 1.0f);
    float texCoordIncY = HeightMapChunkTexcoordsHeight /
        (HeightMapChunkHeight * 1.0f);
    float vertX = 0.0f;
    float vertZ = 0.0f;
    float texCoordX = 0.0f;
    float texCoordY = 0.0f;
    uint32_t vIndex = 0;
    uint32_t iIndex = 0;
    uint16_t iOffset = 0;

    // Flat heightmap chunk
    for (uint32_t j = 0; j <= HeightMapChunkHeight; ++j)
    {
        vertX = 0.0f;
        texCoordX = 0.0f;

        for (uint32_t i = 0; i <= HeightMapChunkWidth; ++i)
        {
            // Set flat heightmap
            m_vertices[vIndex+0] = vertX;
            m_vertices[vIndex+1] = HeightMapLoaderDefaultFlatY;
            m_vertices[vIndex+2] = vertZ;

            m_vertices[vIndex+3] = texCoordX;
            m_vertices[vIndex+4] = texCoordY;

            m_vertices[vIndex+5] = 0.0f;
            m_vertices[vIndex+6] = 1.0f;
            m_vertices[vIndex+7] = 0.0f;

            vIndex += 8;
            vertX += HeightMapChunkPlaneWidth;
            texCoordX += texCoordIncX;
        }

        vertZ += HeightMapChunkPlaneHeight;
        texCoordY += texCoordIncY;
    }

    // Generate indices data
    for (uint32_t j = 0; j < HeightMapChunkHeight; ++j)
    {
        for (uint32_t i = 0; i < HeightMapChunkWidth; ++i)
        {
            m_indices[iIndex+0] = iOffset+(HeightMapChunkWidth+1);
            m_indices[iIndex+1] = iOffset+(HeightMapChunkWidth+2);
            m_indices[iIndex+2] = iOffset+1;
            m_indices[iIndex+3] = iOffset+1;
            m_indices[iIndex+4] = iOffset;
            m_indices[iIndex+5] = iOffset+(HeightMapChunkWidth+1);

            iIndex += 6;
            ++iOffset;
        }
        ++iOffset;
    }

    // Set heightmap chunk flags
    chunkData.flags = HEIGHTMAP_FLAGS_NONE;

    // Update vertex buffer
    if (!chunkData.heightmap->updateHeightMapBuffer(m_vertices, m_indices,
        HeightMapChunkVerticesCount, HeightMapChunkIndicesCount))
    {
        // Could not update vertex buffer
        return false;
    }

    // Heightmap chunk successfully updated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Update heightmap chunk                                                    //
//  return : True if the heightmap chunk is updated                           //
////////////////////////////////////////////////////////////////////////////////
bool HeightMapLoader::updateChunk(HeightMapChunkData& chunkData,
    int32_t chunkX, int32_t chunkY)
{
    // Init vertices and indices count
    uint32_t verticesCount = 0;
    uint32_t indicesCount = 0;

    // Set VHMP file path
    std::ostringstream filepath;
    filepath << HeightMapLoaderVHMPFilePath;
    filepath << chunkX << '_' << chunkY << ".vhmp";

    // Load heightmap data from file
    std::ifstream file;
    file.open(filepath.str().c_str(), std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        // Could not load heightmap data file
        return false;
    }

    // Read VHMP header
    char header[4] = {0};
    char majorVersion = 0;
    char minorVersion = 0;
    file.read(header, sizeof(char)*4);
    file.read(&majorVersion, sizeof(char));
    file.read(&minorVersion, sizeof(char));

    // Check VHMP header
    if ((header[0] != 'V') || (header[1] != 'H') ||
        (header[2] != 'M') || (header[3] != 'P'))
    {
        // Invalid VHMP header
        return false;
    }

    // Check VHMP version
    if ((majorVersion != 1) || (minorVersion != 0))
    {
        // Invalid VHMP header
        return false;
    }

    // Read VHMP file type
    char type = 0;
    file.read(&type, sizeof(char));
    if (type != 0)
    {
        // Invalid VHMP type
        return false;
    }

    // Read VHMP flags
    file.read((char*)&chunkData.flags, sizeof(int32_t));

    // Read vertices and indices count
    file.read((char*)&verticesCount, sizeof(uint32_t));
    file.read((char*)&indicesCount, sizeof(uint32_t));
    if ((verticesCount <= 0) || (indicesCount <= 0) ||
        (verticesCount != HeightMapChunkVerticesCount) ||
        (indicesCount != HeightMapChunkIndicesCount))
    {
        // Invalid vertices or indices count
        return false;
    }

    // Read vertices
    file.read((char*)m_vertices, sizeof(float)*HeightMapChunkVerticesCount);

    // Read indices
    file.read((char*)m_indices, sizeof(uint16_t)*HeightMapChunkIndicesCount);

    // Close VHMP file
    file.close();

    // Update vertex buffer
    if (!chunkData.heightmap->updateHeightMapBuffer(m_vertices, m_indices,
        HeightMapChunkVerticesCount, HeightMapChunkIndicesCount))
    {
        // Could not update vertex buffer
        return false;
    }

    // Heightmap chunk successfully updated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Swap heightmaps pointers towards top                                      //
//  return : True if heightmaps pointers are swapped                          //
////////////////////////////////////////////////////////////////////////////////
bool HeightMapLoader::swapTop()
{
    // Check current loading state
    HeightMapLoaderState state = HEIGHTMAPLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();
    if (state != HEIGHTMAPLOADER_STATE_IDLE)
    {
        // Heightmap loader is still in loading state
        return false;
    }

    // Copy bottom row into tmp
    HeightMapChunkData* tmp[HEIGHTMAP_STREAMWIDTH];
    for (uint32_t i = 0; i < HEIGHTMAP_STREAMWIDTH; ++i)
    {
        tmp[i] = m_chunksptrs[
            ((HEIGHTMAP_STREAMHEIGHT-1)*HEIGHTMAP_STREAMWIDTH)+i
        ];
    }

    // Swap pointers towards top
    for (uint32_t j = (HEIGHTMAP_STREAMHEIGHT-1); j > 0; --j)
    {
        for (uint32_t i = 0; i < HEIGHTMAP_STREAMWIDTH; ++i)
        {
            m_chunksptrs[(j*HEIGHTMAP_STREAMWIDTH)+i] =
                m_chunksptrs[((j-1)*HEIGHTMAP_STREAMWIDTH)+i];
        }
    }

    // Copy tmp into top row
    for (uint32_t i = 0; i < HEIGHTMAP_STREAMWIDTH; ++i)
    {
        m_chunksptrs[i] = tmp[i];
    }

    // Set new chunks loading states
    for (uint32_t i = 0; i < HEIGHTMAP_STREAMWIDTH; ++i)
    {
        m_chunks[i].loading = true;
        m_chunks[i].chunkX = (m_chunkX-HEIGHTMAP_STREAMHALFWIDTH)+i;
        m_chunks[i].chunkY = (m_chunkY-HEIGHTMAP_STREAMHALFHEIGHT-1);
    }

    // Move chunkY
    --m_chunkY;

    // Synchronize swap with renderer
    m_sync = 1;
    m_stateMutex.lock();
    m_state = HEIGHTMAPLOADER_STATE_SYNC;
    m_stateMutex.unlock();
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Swap heightmaps pointers towards bottom                                   //
//  return : True if heightmaps pointers are swapped                          //
////////////////////////////////////////////////////////////////////////////////
bool HeightMapLoader::swapBottom()
{
    // Check current loading state
    HeightMapLoaderState state = HEIGHTMAPLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();
    if (state != HEIGHTMAPLOADER_STATE_IDLE)
    {
        // Heightmap loader is still in loading state
        return false;
    }

    // Copy top row into tmp
    HeightMapChunkData* tmp[HEIGHTMAP_STREAMWIDTH];
    for (uint32_t i = 0; i < HEIGHTMAP_STREAMWIDTH; ++i)
    {
        tmp[i] = m_chunksptrs[i];
    }

    // Swap pointers towards bottom
    for (uint32_t j = 1; j < HEIGHTMAP_STREAMHEIGHT; ++j)
    {
        for (uint32_t i = 0; i < HEIGHTMAP_STREAMWIDTH; ++i)
        {
            m_chunksptrs[((j-1)*HEIGHTMAP_STREAMWIDTH)+i] =
                m_chunksptrs[(j*HEIGHTMAP_STREAMWIDTH)+i];
        }
    }

    // Copy tmp into bottom row
    for (uint32_t i = 0; i < HEIGHTMAP_STREAMWIDTH; ++i)
    {
        m_chunksptrs[((HEIGHTMAP_STREAMHEIGHT-1)*HEIGHTMAP_STREAMWIDTH)+i] =
            tmp[i];
    }

    // Set new chunks loading states
    for (uint32_t i = 0; i < HEIGHTMAP_STREAMWIDTH; ++i)
    {
        m_chunks[
            ((HEIGHTMAP_STREAMHEIGHT-1)*HEIGHTMAP_STREAMWIDTH)+i
        ].loading = true;
        m_chunks[
            ((HEIGHTMAP_STREAMHEIGHT-1)*HEIGHTMAP_STREAMWIDTH)+i
        ].chunkX = (m_chunkX-HEIGHTMAP_STREAMHALFWIDTH)+i;
        m_chunks[
            ((HEIGHTMAP_STREAMHEIGHT-1)*HEIGHTMAP_STREAMWIDTH)+i
        ].chunkY = (m_chunkY+HEIGHTMAP_STREAMHALFHEIGHT+1);
    }

    // Move chunkY
    ++m_chunkY;

    // Synchronize swap with renderer
    m_sync = 1;
    m_stateMutex.lock();
    m_state = HEIGHTMAPLOADER_STATE_SYNC;
    m_stateMutex.unlock();
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Swap heightmaps pointers towards left                                     //
//  return : True if heightmaps pointers are swapped                          //
////////////////////////////////////////////////////////////////////////////////
bool HeightMapLoader::swapLeft()
{
    // Check current loading state
    HeightMapLoaderState state = HEIGHTMAPLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();
    if (state != HEIGHTMAPLOADER_STATE_IDLE)
    {
        // Heightmap loader is still in loading state
        return false;
    }

    // Copy right row into tmp
    HeightMapChunkData* tmp[HEIGHTMAP_STREAMHEIGHT];
    for (uint32_t j = 0; j < HEIGHTMAP_STREAMHEIGHT; ++j)
    {
        tmp[j] = m_chunksptrs[
            (j*HEIGHTMAP_STREAMWIDTH)+(HEIGHTMAP_STREAMWIDTH-1)
        ];
    }

    // Swap pointers towards left
    for (uint32_t i = (HEIGHTMAP_STREAMWIDTH-1); i > 0; --i)
    {
        for (uint32_t j = 0; j < HEIGHTMAP_STREAMHEIGHT; ++j)
        {
            m_chunksptrs[(j*HEIGHTMAP_STREAMWIDTH)+i] =
                m_chunksptrs[(j*HEIGHTMAP_STREAMWIDTH)+(i-1)];
        }
    }

    // Copy tmp into left row
    for (uint32_t j = 0; j < HEIGHTMAP_STREAMHEIGHT; ++j)
    {
        m_chunksptrs[(j*HEIGHTMAP_STREAMWIDTH)] = tmp[j];
    }

    // Set new chunks loading states
    for (uint32_t j = 0; j < HEIGHTMAP_STREAMHEIGHT; ++j)
    {
        m_chunks[(j*HEIGHTMAP_STREAMWIDTH)].loading = true;
        m_chunks[(j*HEIGHTMAP_STREAMWIDTH)].chunkX =
            (m_chunkX-HEIGHTMAP_STREAMHALFWIDTH-1);
        m_chunks[(j*HEIGHTMAP_STREAMWIDTH)].chunkY =
            (m_chunkY-HEIGHTMAP_STREAMHALFHEIGHT)+j;
    }

    // Move chunkX
    --m_chunkX;

    // Synchronize swap with renderer
    m_sync = 1;
    m_stateMutex.lock();
    m_state = HEIGHTMAPLOADER_STATE_SYNC;
    m_stateMutex.unlock();
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Swap heightmaps pointers towards right                                    //
//  return : True if heightmaps pointers are swapped                          //
////////////////////////////////////////////////////////////////////////////////
bool HeightMapLoader::swapRight()
{
    // Check current loading state
    HeightMapLoaderState state = HEIGHTMAPLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();
    if (state != HEIGHTMAPLOADER_STATE_IDLE)
    {
        // Heightmap loader is still in loading state
        return false;
    }

    // Copy left row into tmp
    HeightMapChunkData* tmp[HEIGHTMAP_STREAMHEIGHT];
    for (uint32_t j = 0; j < HEIGHTMAP_STREAMHEIGHT; ++j)
    {
        tmp[j] = m_chunksptrs[(j*HEIGHTMAP_STREAMWIDTH)];
    }

    // Swap pointers towards right
    for (uint32_t i = 1; i < HEIGHTMAP_STREAMWIDTH; ++i)
    {
        for (uint32_t j = 0; j < HEIGHTMAP_STREAMHEIGHT; ++j)
        {
            m_chunksptrs[(j*HEIGHTMAP_STREAMWIDTH)+(i-1)] =
                m_chunksptrs[(j*HEIGHTMAP_STREAMWIDTH)+i];
        }
    }

    // Copy tmp into right row
    for (uint32_t j = 0; j < HEIGHTMAP_STREAMHEIGHT; ++j)
    {
        m_chunksptrs[(j*HEIGHTMAP_STREAMWIDTH)+(HEIGHTMAP_STREAMWIDTH-1)] =
            tmp[j];
    }

    // Set new chunks loading states
    for (uint32_t j = 0; j < HEIGHTMAP_STREAMHEIGHT; ++j)
    {
        m_chunks[
            (j*HEIGHTMAP_STREAMWIDTH)+(HEIGHTMAP_STREAMWIDTH-1)
        ].loading = true;
        m_chunks[
            (j*HEIGHTMAP_STREAMWIDTH)+(HEIGHTMAP_STREAMWIDTH-1)
        ].chunkX = (m_chunkX+HEIGHTMAP_STREAMHALFWIDTH+1);
        m_chunks[
            (j*HEIGHTMAP_STREAMWIDTH)+(HEIGHTMAP_STREAMWIDTH-1)
        ].chunkY = (m_chunkY-HEIGHTMAP_STREAMHALFHEIGHT)+j;
    }

    // Move chunkX
    ++m_chunkX;

    // Synchronize swap with renderer
    m_sync = 1;
    m_stateMutex.lock();
    m_state = HEIGHTMAPLOADER_STATE_SYNC;
    m_stateMutex.unlock();
    return true;
}
