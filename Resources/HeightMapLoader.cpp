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
//  pseudoRand : 2D based pseudo-random value                                 //
//  param seed : Normalized seed of the pseudo-random generation              //
//  param x : X offset                                                        //
//  param y : Y offset                                                        //
//  return : Generated pseudo-random value                                    //
////////////////////////////////////////////////////////////////////////////////
float pseudoRand(float seed, float x, float y)
{
    seed = (std::fmod(seed,1.0f))*158.0f+31.45f;
    float xrnd =
        std::fmod((std::sin(x+713.148f*seed)*14.5787f*seed),0.5f)+0.5f;
    float yrnd =
        std::fmod((std::sin(y+358.735f*seed)*768.3458f*seed),0.5f)+0.5f;
    return (std::fmod((std::sin((xrnd*yrnd*18.45f*seed)+59.76f*seed)*
        28.845f*seed),0.5f)+0.5f);
}

////////////////////////////////////////////////////////////////////////////////
//  fractalHeigthmap : 2D Fractal pseudo random heightmap                     //
//  param seed : Normalized seed of the pseudo-random generation              //
//  param i : Integer I index (X) offset                                      //
//  param j : Integer J index (Y) offset                                      //
//  return : Generated fractal heightmap value at (i,j) coordinates           //
////////////////////////////////////////////////////////////////////////////////
float fractalHeigthmap(float seed, int i, int j)
{
    /*i += 25000;
    j += 25000;
    float ix = i*1.0f;
    float jy = j*1.0f;

    // Fractal frequencies
    const int freqsCnt = 8;
    float freqs[8] = {0.0f};
    freqs[0] = 434.2f;
    freqs[1] = 278.37f;
    freqs[2] = 387.18f;
    freqs[3] = 186.75f;
    freqs[4] = 52.23f;
    freqs[5] = 34.78f;
    freqs[6] = 18.32f;
    freqs[7] = 7.12f;

    // Fractal amplitudes
    float amplitudes[8] = {0.0f};
    amplitudes[0] = 0.8f;
    amplitudes[1] = 0.3f;
    amplitudes[2] = 0.8f;
    amplitudes[3] = 0.4f;
    amplitudes[4] = 0.2f;
    amplitudes[5] = 0.12f;
    amplitudes[6] = 0.05f;
    amplitudes[7] = 0.02f;

    // Compute fractal heightmap
    float fondamentalValue = 0.0f;
    float fractalValue = 0.0f;
    for (int k = 0; k < freqsCnt; ++k)
    {
        float ixf = ((std::fmod(ix, freqs[k]))/freqs[k])*1.0f;
        float jyf = ((std::fmod(jy, freqs[k]))/freqs[k])*1.0f;
        ixf = (ixf*ixf*(3.0f-2.0f*ixf));
        jyf = (jyf*jyf*(3.0f-2.0f*jyf));

        float rnd = pseudoRand(
            seed, std::floor(ix/freqs[k]),
            std::floor(jy/freqs[k])
        );
        float rnd2 = pseudoRand(
            seed, std::floor(ix/freqs[k]),
            std::floor((jy+freqs[k])/freqs[k])
        );
        float rnd3 = pseudoRand(
            seed, std::floor((ix+freqs[k])/freqs[k]),
            std::floor(jy/freqs[k])
        );
        float rnd4 = pseudoRand(
            seed, std::floor((ix+freqs[k])/freqs[k]),
            std::floor((jy+freqs[k])/freqs[k])
        );

        if (k < 2)
        {
            fondamentalValue += (
                (rnd + (rnd3-rnd)*ixf + (rnd2-rnd)*jyf +
                ((rnd4+rnd)-(rnd3+rnd2))*ixf*jyf
            )*amplitudes[k]);
        }
        else
        {
            fractalValue += (
                (rnd + (rnd3-rnd)*ixf + (rnd2-rnd)*jyf +
                ((rnd4+rnd)-(rnd3+rnd2))*ixf*jyf
            )*amplitudes[k]);
        }
    }
    fractalValue *= fondamentalValue;

    // Final fractal heightmap
    return ((fractalValue*1000.0f)-100.0f);*/
    return 0.0f;
}


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
m_heightmaps(0),
m_chunkX(0),
m_chunkY(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  HeightMapLoader virtual destructor                                        //
////////////////////////////////////////////////////////////////////////////////
HeightMapLoader::~HeightMapLoader()
{

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

    switch (m_state)
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
    if (!m_transferQueue.createGraphicsQueue())
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

    // Set default heightmaps pointers
    for (int i = 0; i < HEIGHTMAP_ASSETSCOUNT; ++i)
    {
        m_heightptrs[i] = &m_heightmaps[i];
    }

    // Create default heightmap
    int32_t cnt = 0;
    for (int32_t j = 0; j < HEIGHTMAP_STREAMHEIGHT; ++j)
    {
        for (int32_t i = 0; i < HEIGHTMAP_STREAMWIDTH; ++i)
        {
            if (generateChunk(m_heightmaps[cnt]))
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
//  Destroy heightmap loader                                                  //
////////////////////////////////////////////////////////////////////////////////
void HeightMapLoader::destroyHeightMapLoader()
{
    // Destroy heightmaps vertex buffers
    for (int i = 0; i < HEIGHTMAP_ASSETSCOUNT; ++i)
    {
        m_heightmaps[i].destroyBuffer();
    }
    if (m_heightmaps) { delete[] m_heightmaps; }
    m_heightmaps = 0;

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

    VkBufferCopy bufferCopy;
    bufferCopy.srcOffset = 0;
    bufferCopy.dstOffset = 0;
    bufferCopy.size = m_stagingBuffer.size;

    vkCmdCopyBuffer(
        m_commandBuffer, m_stagingBuffer.handle,
        vertexBuffer.vertexBuffer.handle, 1, &bufferCopy
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

    if (vkQueueSubmit(
        m_transferQueue.handle, 1, &submitInfo, m_fence) != VK_SUCCESS)
    {
        // Could not submit queue
        return false;
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

    bufferCopy.srcOffset = 0;
    bufferCopy.dstOffset = 0;
    bufferCopy.size = m_stagingBuffer.size;

    vkCmdCopyBuffer(
        m_commandBuffer, m_stagingBuffer.handle,
        vertexBuffer.indexBuffer.handle, 1, &bufferCopy
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

    if (vkQueueSubmit(
        m_transferQueue.handle, 1, &submitInfo, m_fence) != VK_SUCCESS)
    {
        // Could not submit queue
        return false;
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
            if (updateChunk(
                (*m_heightptrs[i]), m_chunks[i].chunkX, m_chunks[i].chunkY))
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

    // Heightmaps assets are successfully loaded
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Generate flat heightmap chunk                                             //
//  return : True if the heightmap chunk is generated                         //
////////////////////////////////////////////////////////////////////////////////
bool HeightMapLoader::generateChunk(VertexBuffer& vertexBuffer)
{
    // Init heightmap chunk data
    float* vertices = 0;
    uint16_t* indices = 0;

    uint16_t hmWidthP1 = (HeightMapChunkWidth+1);
    uint16_t hmHeightP1 = (HeightMapChunkHeight+1);
    uint32_t verticesCount = ((HeightMapChunkWidth+1)*hmHeightP1*8);
    uint32_t indicesCount = (6*HeightMapChunkWidth*HeightMapChunkHeight);

    // Allocate vertices and indices
    vertices = new (std::nothrow) float[verticesCount];
    indices = new (std::nothrow) uint16_t[indicesCount];
    if (!vertices || !indices) return false;

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

    for (uint32_t j = 0; j <= HeightMapChunkHeight; ++j)
    {
        vertX = 0.0f;
        texCoordX = 0.0f;

        for (uint32_t i = 0; i <= HeightMapChunkWidth; ++i)
        {
            // Set flat heightmap
            vertices[vIndex+0] = vertX;
            vertices[vIndex+1] = 0.0f;
            vertices[vIndex+2] = vertZ;

            vertices[vIndex+3] = texCoordX;
            vertices[vIndex+4] = texCoordY;

            vertices[vIndex+5] = 0.0f;
            vertices[vIndex+6] = 1.0f;
            vertices[vIndex+7] = 0.0f;

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
            indices[iIndex+0] = iOffset+hmWidthP1;
            indices[iIndex+1] = iOffset+hmWidthP1+1;
            indices[iIndex+2] = iOffset+1;
            indices[iIndex+3] = iOffset+1;
            indices[iIndex+4] = iOffset;
            indices[iIndex+5] = iOffset+hmWidthP1;

            iIndex += 6;
            ++iOffset;
        }
        ++iOffset;
    }

    // Create vertex buffer
    if (!vertexBuffer.createHeightMapBuffer(VULKAN_MEMORY_HEIGHTMAPS,
        vertices, indices, verticesCount, indicesCount))
    {
        // Could not create vertex buffer
        if (vertices) { delete[] vertices; }
        if (indices) { delete[] indices; }
        return false;
    }

    // Destroy mesh data
    if (vertices) { delete[] vertices; }
    if (indices) { delete[] indices; }

    // Heightmap chunk successfully generated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Update heightmap chunk                                                    //
//  return : True if the heightmap chunk is updated                           //
////////////////////////////////////////////////////////////////////////////////
bool HeightMapLoader::updateChunk(VertexBuffer& vertexBuffer,
    int32_t chunkX, int32_t chunkY)
{
    // Init heightmap chunk data
    float* vertices = 0;
    uint16_t* indices = 0;

    uint16_t hmWidthP1 = (HeightMapChunkWidth+1);
    uint16_t hmHeightP1 = (HeightMapChunkHeight+1);
    uint32_t verticesCount = ((HeightMapChunkWidth+1)*hmHeightP1*8);
    uint32_t indicesCount = (6*HeightMapChunkWidth*HeightMapChunkHeight);

    // Allocate vertices and indices
    vertices = new (std::nothrow) float[verticesCount];
    indices = new (std::nothrow) uint16_t[indicesCount];
    if (!vertices || !indices) return false;

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

    for (uint32_t j = 0; j <= HeightMapChunkHeight; ++j)
    {
        vertX = 0.0f;
        texCoordX = 0.0f;

        for (uint32_t i = 0; i <= HeightMapChunkWidth; ++i)
        {
            // Median filtering
            float median[9] = {0.0f};
            median[0] = fractalHeigthmap(0.7154,
                i-1+(chunkX*HeightMapChunkWidth),
                j-1+(chunkY*HeightMapChunkHeight)
            );
            median[1] = fractalHeigthmap(0.7154,
                i+(chunkX*HeightMapChunkWidth),
                j-1+(chunkY*HeightMapChunkHeight)
            );
            median[2] = fractalHeigthmap(0.7154,
                i+1+(chunkX*HeightMapChunkWidth),
                j-1+(chunkY*HeightMapChunkHeight)
            );
            median[3] = fractalHeigthmap(0.7154,
                i-1+(chunkX*HeightMapChunkWidth),
                j+(chunkY*HeightMapChunkHeight)
            );
            median[4] = fractalHeigthmap(0.7154,
                i+(chunkX*HeightMapChunkWidth),
                j+(chunkY*HeightMapChunkHeight)
            );
            median[5] = fractalHeigthmap(0.7154,
                i+1+(chunkX*HeightMapChunkWidth),
                j+(chunkY*HeightMapChunkHeight)
            );
            median[6] = fractalHeigthmap(0.7154,
                i-1+(chunkX*HeightMapChunkWidth),
                j+1+(chunkY*HeightMapChunkHeight)
            );
            median[7] = fractalHeigthmap(0.7154,
                i+(chunkX*HeightMapChunkWidth),
                j+1+(chunkY*HeightMapChunkHeight)
            );
            median[8] = fractalHeigthmap(0.7154,
                i+1+(chunkX*HeightMapChunkWidth),
                j+1+(chunkY*HeightMapChunkHeight)
            );

            // Sort median data
            for (int o = 0; o < (9-1); ++o)
            {
                for (int m = 0; m < ((9-1)-o); ++m)
                {
                    if (median[m] > median[m+1])
                    {
                        float tmp = median[m];
                        median[m] = median[m+1];
                        median[m+1] = tmp;
                    }
                }
            }

            // Set test heightmap
            vertices[vIndex+0] = vertX;
            vertices[vIndex+1] = median[4];
            vertices[vIndex+2] = vertZ;

            vertices[vIndex+3] = texCoordX;
            vertices[vIndex+4] = texCoordY;

            vertices[vIndex+5] = 0.0f;
            vertices[vIndex+6] = 1.0f;
            vertices[vIndex+7] = 0.0f;

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
            indices[iIndex+0] = iOffset+hmWidthP1;
            indices[iIndex+1] = iOffset+hmWidthP1+1;
            indices[iIndex+2] = iOffset+1;
            indices[iIndex+3] = iOffset+1;
            indices[iIndex+4] = iOffset;
            indices[iIndex+5] = iOffset+hmWidthP1;

            iIndex += 6;
            ++iOffset;
        }
        ++iOffset;
    }

    // Update vertex buffer
    if (!vertexBuffer.updateHeightMapBuffer(
        vertices, indices, verticesCount, indicesCount))
    {
        // Could not create vertex buffer
        if (vertices) { delete[] vertices; }
        if (indices) { delete[] indices; }
        return false;
    }

    // Destroy mesh data
    if (vertices) { delete[] vertices; }
    if (indices) { delete[] indices; }

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
    VertexBuffer* tmp[HEIGHTMAP_STREAMWIDTH];
    for (uint32_t i = 0; i < HEIGHTMAP_STREAMWIDTH; ++i)
    {
        tmp[i] = m_heightptrs[
            ((HEIGHTMAP_STREAMHEIGHT-1)*HEIGHTMAP_STREAMWIDTH)+i
        ];
    }

    // Swap pointers towards top
    for (uint32_t j = (HEIGHTMAP_STREAMHEIGHT-1); j > 0; --j)
    {
        for (uint32_t i = 0; i < HEIGHTMAP_STREAMWIDTH; ++i)
        {
            m_heightptrs[(j*HEIGHTMAP_STREAMWIDTH)+i] =
                m_heightptrs[((j-1)*HEIGHTMAP_STREAMWIDTH)+i];
        }
    }

    // Copy tmp into top row
    for (uint32_t i = 0; i < HEIGHTMAP_STREAMWIDTH; ++i)
    {
        m_heightptrs[i] = tmp[i];
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

    // Load new chunks
    m_stateMutex.lock();
    m_state = HEIGHTMAPLOADER_STATE_LOAD;
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
    VertexBuffer* tmp[HEIGHTMAP_STREAMWIDTH];
    for (uint32_t i = 0; i < HEIGHTMAP_STREAMWIDTH; ++i)
    {
        tmp[i] = m_heightptrs[i];
    }

    // Swap pointers towards bottom
    for (uint32_t j = 1; j < HEIGHTMAP_STREAMHEIGHT; ++j)
    {
        for (uint32_t i = 0; i < HEIGHTMAP_STREAMWIDTH; ++i)
        {
            m_heightptrs[((j-1)*HEIGHTMAP_STREAMWIDTH)+i] =
                m_heightptrs[(j*HEIGHTMAP_STREAMWIDTH)+i];
        }
    }

    // Copy tmp into bottom row
    for (uint32_t i = 0; i < HEIGHTMAP_STREAMWIDTH; ++i)
    {
        m_heightptrs[((HEIGHTMAP_STREAMHEIGHT-1)*HEIGHTMAP_STREAMWIDTH)+i] =
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

    // Load new chunks
    m_stateMutex.lock();
    m_state = HEIGHTMAPLOADER_STATE_LOAD;
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
    VertexBuffer* tmp[HEIGHTMAP_STREAMHEIGHT];
    for (uint32_t j = 0; j < HEIGHTMAP_STREAMHEIGHT; ++j)
    {
        tmp[j] = m_heightptrs[
            (j*HEIGHTMAP_STREAMWIDTH)+(HEIGHTMAP_STREAMWIDTH-1)
        ];
    }

    // Swap pointers towards left
    for (uint32_t i = (HEIGHTMAP_STREAMWIDTH-1); i > 0; --i)
    {
        for (uint32_t j = 0; j < HEIGHTMAP_STREAMHEIGHT; ++j)
        {
            m_heightptrs[(j*HEIGHTMAP_STREAMWIDTH)+i] =
                m_heightptrs[(j*HEIGHTMAP_STREAMWIDTH)+(i-1)];
        }
    }

    // Copy tmp into left row
    for (uint32_t j = 0; j < HEIGHTMAP_STREAMHEIGHT; ++j)
    {
        m_heightptrs[(j*HEIGHTMAP_STREAMWIDTH)] = tmp[j];
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

    // Load new chunks
    m_stateMutex.lock();
    m_state = HEIGHTMAPLOADER_STATE_LOAD;
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
    VertexBuffer* tmp[HEIGHTMAP_STREAMHEIGHT];
    for (uint32_t j = 0; j < HEIGHTMAP_STREAMHEIGHT; ++j)
    {
        tmp[j] = m_heightptrs[(j*HEIGHTMAP_STREAMWIDTH)];
    }

    // Swap pointers towards right
    for (uint32_t i = 1; i < HEIGHTMAP_STREAMWIDTH; ++i)
    {
        for (uint32_t j = 0; j < HEIGHTMAP_STREAMHEIGHT; ++j)
        {
            m_heightptrs[(j*HEIGHTMAP_STREAMWIDTH)+(i-1)] =
                m_heightptrs[(j*HEIGHTMAP_STREAMWIDTH)+i];
        }
    }

    // Copy tmp into right row
    for (uint32_t j = 0; j < HEIGHTMAP_STREAMHEIGHT; ++j)
    {
        m_heightptrs[(j*HEIGHTMAP_STREAMWIDTH)+(HEIGHTMAP_STREAMWIDTH-1)] =
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

    // Load new chunks
    m_stateMutex.lock();
    m_state = HEIGHTMAPLOADER_STATE_LOAD;
    m_stateMutex.unlock();
    return true;
}
