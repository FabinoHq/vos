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
#include "../Renderer/Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  HeightMapLoader default constructor                                       //
////////////////////////////////////////////////////////////////////////////////
HeightMapLoader::HeightMapLoader(Renderer& renderer) :
m_renderer(renderer),
m_state(HEIGHTMAPLOADER_STATE_NONE),
m_stateMutex(),
m_transferQueue(),
m_commandPool(0),
m_commandBuffer(0),
m_stagingBuffer(),
m_fence(0),
m_heightmaps(0)
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
    if (!m_transferQueue.createGraphicsQueue(
        m_renderer.m_vulkanDevice, m_renderer.m_vulkanQueues))
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

    if (vkCreateCommandPool(m_renderer.m_vulkanDevice,
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

    if (vkAllocateCommandBuffers(m_renderer.m_vulkanDevice,
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

    if (vkCreateFence(
        m_renderer.m_vulkanDevice, &fenceInfo, 0, &m_fence) != VK_SUCCESS)
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

    // Create default heightmap
    if (!generateFlat(m_heightmaps[HEIGHTMAP_DEFAULT]))
    {
        // Could not create default heightmap
        return false;
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
//  Destroy heightmap loader                                                  //
////////////////////////////////////////////////////////////////////////////////
void HeightMapLoader::destroyHeightMapLoader()
{
    // Destroy heightmaps vertex buffers
    for (int i = 0; i < HEIGHTMAP_ASSETSCOUNT; ++i)
    {
        m_heightmaps[i].destroyBuffer(m_renderer.m_vulkanDevice);
    }
    if (m_heightmaps) { delete[] m_heightmaps; }
    m_heightmaps = 0;

    // Destroy staging fence
    if (m_fence)
    {
        vkDestroyFence(m_renderer.m_vulkanDevice, m_fence, 0);
    }
    m_fence = 0;

    // Destroy staging buffer
    m_stagingBuffer.destroyBuffer(m_renderer.m_vulkanDevice);

    // Destroy command buffer
    if (m_commandBuffer)
    {
        vkFreeCommandBuffers(m_renderer.m_vulkanDevice,
            m_commandPool, 1, &m_commandBuffer
        );
    }
    m_commandBuffer = 0;

    // Destroy command pool
    if (m_commandPool)
    {
        vkDestroyCommandPool(m_renderer.m_vulkanDevice, m_commandPool, 0);
    }
    m_commandPool = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Load heightmaps assets                                                    //
//  return : True if heightmaps assets are loaded                             //
////////////////////////////////////////////////////////////////////////////////
bool HeightMapLoader::loadHeightMaps()
{
    // Heightmaps assets are successfully loaded
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Generate flat heightmap chunk                                             //
//  return : True if the flat heightmap chunk is generated                    //
////////////////////////////////////////////////////////////////////////////////
bool HeightMapLoader::generateFlat(VertexBuffer& vertexBuffer)
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
    if (!vertexBuffer.createBuffer(
        m_renderer.m_vulkanDevice, m_renderer.m_vulkanMemory,
        m_commandPool, m_transferQueue,
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
