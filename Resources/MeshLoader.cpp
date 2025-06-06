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
//     Resources/MeshLoader.cpp : Mesh loading management                     //
////////////////////////////////////////////////////////////////////////////////
#include "MeshLoader.h"


////////////////////////////////////////////////////////////////////////////////
//  MeshLoader default constructor                                            //
////////////////////////////////////////////////////////////////////////////////
MeshLoader::MeshLoader() :
m_state(MESHLOADER_STATE_NONE),
m_stateMutex(),
m_transferQueue(),
m_commandPool(0),
m_commandBuffer(0),
m_stagingBuffer(),
m_fence(0),
m_meshes(0),
m_vertices(0),
m_indices(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  MeshLoader virtual destructor                                             //
////////////////////////////////////////////////////////////////////////////////
MeshLoader::~MeshLoader()
{
    m_indices = 0;
    m_vertices = 0;
    m_meshes = 0;
    m_fence = 0;
    m_commandBuffer = 0;
    m_commandPool = 0;
    m_state = MESHLOADER_STATE_NONE;
}


////////////////////////////////////////////////////////////////////////////////
//  MeshLoader thread process                                                 //
////////////////////////////////////////////////////////////////////////////////
void MeshLoader::process()
{
    MeshLoaderState state = MESHLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();

    switch (state)
    {
        case MESHLOADER_STATE_NONE:
            // Boot to init state
            m_stateMutex.lock();
            m_state = MESHLOADER_STATE_INIT;
            m_stateMutex.unlock();
            break;

        case MESHLOADER_STATE_INIT:
            // Init mesh loader
            if (init())
            {
                m_stateMutex.lock();
                m_state = MESHLOADER_STATE_LOADEMBEDDED;
                m_stateMutex.unlock();
            }
            else
            {
                m_stateMutex.lock();
                m_state = MESHLOADER_STATE_ERROR;
                m_stateMutex.unlock();
            }
            break;

        case MESHLOADER_STATE_LOADEMBEDDED:
            // Load embedded meshes
            if (loadEmbeddedMeshes())
            {
                m_stateMutex.lock();
                m_state = MESHLOADER_STATE_IDLE;
                m_stateMutex.unlock();
            }
            else
            {
                m_stateMutex.lock();
                m_state = MESHLOADER_STATE_ERROR;
                m_stateMutex.unlock();
            }
            break;

        case MESHLOADER_STATE_IDLE:
            // Mesh loader in idle state
            SysSleep(MeshLoaderIdleSleepTime);
            break;

        case MESHLOADER_STATE_PRELOAD:
            // Preload meshes assets
            if (preloadMeshes())
            {
                m_stateMutex.lock();
                m_state = MESHLOADER_STATE_IDLE;
                m_stateMutex.unlock();
            }
            else
            {
                m_stateMutex.lock();
                m_state = MESHLOADER_STATE_ERROR;
                m_stateMutex.unlock();
            }
            break;

        case MESHLOADER_STATE_LOAD:
            // Load meshes assets
            if (loadMeshes())
            {
                m_stateMutex.lock();
                m_state = MESHLOADER_STATE_IDLE;
                m_stateMutex.unlock();
            }
            else
            {
                m_stateMutex.lock();
                m_state = MESHLOADER_STATE_ERROR;
                m_stateMutex.unlock();
            }
            break;

        case MESHLOADER_STATE_ERROR:
            // Mesh loader error
            SysSleep(MeshLoaderErrorSleepTime);
            break;

        default:
            // Invalid state
            m_stateMutex.lock();
            m_state = MESHLOADER_STATE_ERROR;
            m_stateMutex.unlock();
            break;
    }
}


////////////////////////////////////////////////////////////////////////////////
//  Init MeshLoader                                                           //
//  return : True if mesh loader is ready                                     //
////////////////////////////////////////////////////////////////////////////////
bool MeshLoader::init()
{
    // Request transfer queue handle
    if (!m_transferQueue.getVulkanQueue(VULKAN_QUEUE_MESHES))
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

    if (vkCreateCommandPool(GVulkanDevice, &commandPoolInfo,
        SYSVKMEMORY_COMMANDPOOL_ALLOC, &m_commandPool) != VK_SUCCESS)
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

    if (vkCreateFence(GVulkanDevice, &fenceInfo,
        SYSVKMEMORY_FENCE_ALLOC, &m_fence) != VK_SUCCESS)
    {
        // Could not create staging fence
        return false;
    }
    if (!m_fence)
    {
        // Invalid staging fence
        return false;
    }

    // Allocate meshes vertex buffers
    m_meshes = GSysMemory.alloc<VertexBuffer>(
        MESHES_ASSETSCOUNT, SYSMEMORY_MESHES
    );
    if (!m_meshes) { return false; }

    // Init meshes vertex buffers
    for (int i = 0; i < MESHES_ASSETSCOUNT; ++i)
    {
        m_meshes[i].init();
    }

    // Allocate mesh vertices
    m_vertices = GSysMemory.alloc<float>(
        MeshLoaderMaxVerticesCount, SYSMEMORY_MESHES
    );
    if (!m_vertices) { return false; }

    // Allocate mesh indices
    m_indices = GSysMemory.alloc<uint16_t>(
        MeshLoaderMaxIndicesCount, SYSMEMORY_MESHES
    );
    if (!m_indices) { return false; }

    // Mesh loader ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Start preloading meshes assets                                            //
//  return : True if meshes assets are preloading                             //
////////////////////////////////////////////////////////////////////////////////
bool MeshLoader::startPreload()
{
    bool preLoading = false;
    m_stateMutex.lock();

    // Check mesh loader state
    if (m_state == MESHLOADER_STATE_IDLE)
    {
        // Switch to preload state
        m_state = MESHLOADER_STATE_PRELOAD;
        preLoading = true;
    }

    m_stateMutex.unlock();
    return preLoading;
}

////////////////////////////////////////////////////////////////////////////////
//  Start loading meshes assets                                               //
//  return : True if meshes assets are loading                                //
////////////////////////////////////////////////////////////////////////////////
bool MeshLoader::startLoading()
{
    bool loading = false;
    m_stateMutex.lock();

    // Check mesh loader state
    if (m_state == MESHLOADER_STATE_IDLE)
    {
        // Switch to load state
        m_state = MESHLOADER_STATE_LOAD;
        loading = true;
    }

    m_stateMutex.unlock();
    return loading;
}

////////////////////////////////////////////////////////////////////////////////
//  Get mesh loader state                                                     //
//  return : Current mesh loader state                                        //
////////////////////////////////////////////////////////////////////////////////
MeshLoaderState MeshLoader::getState()
{
    MeshLoaderState state = MESHLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();
    return state;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy mesh loader                                                       //
////////////////////////////////////////////////////////////////////////////////
void MeshLoader::destroyMeshLoader()
{
    // Reset indices and vertices
    m_indices = 0;
    m_vertices = 0;

    // Destroy meshes vertex buffers
    if (m_meshes)
    {
        for (int i = 0; i < MESHES_ASSETSCOUNT; ++i)
        {
            m_meshes[i].destroyBuffer();
        }
    }
    m_meshes = 0;

    // Destroy staging fence
    if (m_fence)
    {
        vkDestroyFence(GVulkanDevice, m_fence, SYSVKMEMORY_FENCE_ALLOC);
    }
    m_fence = 0;

    // Destroy staging buffer
    m_stagingBuffer.destroyBuffer();

    // Destroy command buffer
    if (m_commandBuffer)
    {
        vkFreeCommandBuffers(GVulkanDevice, m_commandPool, 1, &m_commandBuffer);
    }
    m_commandBuffer = 0;

    // Destroy command pool
    if (m_commandPool)
    {
        vkDestroyCommandPool(
            GVulkanDevice, m_commandPool, SYSVKMEMORY_COMMANDPOOL_ALLOC
        );
    }
    m_commandPool = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Upload vertex buffer to graphics memory                                   //
//  return : True if vertex buffer is successfully uploaded                   //
////////////////////////////////////////////////////////////////////////////////
bool MeshLoader::uploadVertexBuffer(VertexBuffer& vertexBuffer,
    const float* vertices, const uint16_t* indices,
    uint32_t verticesCount, uint32_t indicesCount)
{
    // Reset mesh upload memory
    GVulkanMemory.resetMemory(VULKAN_MEMORY_MESHUPLOAD);

    // Create vertices staging buffer
    if (!m_stagingBuffer.createBuffer(VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VULKAN_MEMORY_MESHUPLOAD, verticesCount))
    {
        // Could not create vertices staging buffer
        return false;
    }

    // Write vertices into staging buffer memory
    if (!GVulkanMemory.writeBufferMemory(
        m_stagingBuffer, vertices, VULKAN_MEMORY_MESHUPLOAD))
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
        &m_fence, VK_FALSE, MeshFenceTimeout) != VK_SUCCESS)
    {
        // Transfer timed out
        return false;
    }

    // Destroy vertices staging buffer
    m_stagingBuffer.destroyBuffer();


    // Reset mesh upload memory
    GVulkanMemory.resetMemory(VULKAN_MEMORY_MESHUPLOAD);

    // Create indices staging buffer
    if (!m_stagingBuffer.createBuffer(VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VULKAN_MEMORY_MESHUPLOAD, indicesCount))
    {
        // Could not create indices staging buffer
        return false;
    }

    // Write indices into staging buffer memory
    if (!GVulkanMemory.writeBufferMemory(
        m_stagingBuffer, indices, VULKAN_MEMORY_MESHUPLOAD))
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
        &m_fence, VK_FALSE, MeshFenceTimeout) != VK_SUCCESS)
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
//  Load embedded meshes                                                      //
//  return : True if embedded meshes are successfully loaded                  //
////////////////////////////////////////////////////////////////////////////////
bool MeshLoader::loadEmbeddedMeshes()
{
    // Load default vertex buffer
    if (!m_meshes[MESHES_DEFAULT].createMeshBuffer(
        VULKAN_MEMORY_MESHES,
        DefaultVertices, DefaultIndices,
        DefaultVerticesCount, DefaultIndicesCount))
    {
        // Could not load default vertex buffer
        return false;
    }

    // Load plane vertex buffer
    if (!m_meshes[MESHES_PLANE].createMeshBuffer(
        VULKAN_MEMORY_MESHES,
        PlaneVertices, PlaneIndices,
        PlaneVerticesCount, PlaneIndicesCount))
    {
        // Could not load plane vertex buffer
        return false;
    }

    // Load skybox vertex buffer
    if (!m_meshes[MESHES_SKYBOX].createMeshBuffer(
        VULKAN_MEMORY_MESHES,
        SkyBoxVertices, SkyBoxIndices,
        SkyBoxVerticesCount, SkyBoxIndicesCount))
    {
        // Could not load skybox vertex buffer
        return false;
    }

    // Load cuboid vertex buffer
    if (!m_meshes[MESHES_CUBOID].createMeshBuffer(
        VULKAN_MEMORY_MESHES,
        CuboidShapeVertices, CuboidShapeIndices,
        CuboidShapeVerticesCount, CuboidShapeIndicesCount))
    {
        // Could not load cuboid vertex buffer
        return false;
    }

    // Load sea near vertex buffer
    if (!SeaNearChunk::generateSeaNearChunk(m_meshes[MESHES_SEANEAR]))
    {
        // Could not load sea near vertex buffer
        return false;
    }

    // Load sea far vertex buffer
    if (!SeaFarChunk::generateSeaFarChunk(m_meshes[MESHES_SEAFAR]))
    {
        // Could not load sea near vertex buffer
        return false;
    }

    // Embedded meshes successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Preload meshes assets                                                     //
//  return : True if meshes assets are preloaded                              //
////////////////////////////////////////////////////////////////////////////////
bool MeshLoader::preloadMeshes()
{
    // Load test static mesh
    if (!loadVMSH(m_meshes[MESHES_TEST], "Models/testmodel.vmsh"))
    {
        // Could not load test static mesh
        return false;
    }

    // Meshes assets are successfully preloaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Load meshes assets                                                        //
//  return : True if meshes assets are loaded                                 //
////////////////////////////////////////////////////////////////////////////////
bool MeshLoader::loadMeshes()
{
    // Meshes assets are successfully loaded
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Load mesh from VMSH file                                                  //
//  return : True if the mesh is successfully loaded                          //
////////////////////////////////////////////////////////////////////////////////
bool MeshLoader::loadVMSH(VertexBuffer& vertexBuffer,
    const std::string& filepath)
{
    // Init vertices and indices count
    uint32_t verticesCount = 0;
    uint32_t indicesCount = 0;

    // Load mesh data from file
    std::ifstream file;
    file.open(filepath.c_str(), std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        // Could not load mesh data file
        return false;
    }

    // Read VMSH header
    char header[4] = {0};
    char majorVersion = 0;
    char minorVersion = 0;
    file.read(header, sizeof(char)*4);
    file.read(&majorVersion, sizeof(char));
    file.read(&minorVersion, sizeof(char));

    // Check VMSH header
    if ((header[0] != 'V') || (header[1] != 'M') ||
        (header[2] != 'S') || (header[3] != 'H'))
    {
        // Invalid VMSH header
        return false;
    }

    // Check VMSH version
    if ((majorVersion != 1) || (minorVersion != 0))
    {
        // Invalid VMSH header
        return false;
    }

    // Read VMSH file type
    char type = 0;
    file.read(&type, sizeof(char));
    if (type != 0)
    {
        // Invalid VMSH type
        return false;
    }

    // Read vertices and indices count
    file.read((char*)&verticesCount, sizeof(uint32_t));
    file.read((char*)&indicesCount, sizeof(uint32_t));
    if ((verticesCount <= 0) || (indicesCount <= 0))
    {
        // Invalid vertices or indices count
        return false;
    }

    // Check vertices count
    if (verticesCount >= MeshLoaderMaxVerticesCount)
    {
        // Invalid vertices count
        return false;
    }

    // Check indices count
    if (indicesCount >= MeshLoaderMaxIndicesCount)
    {
        // Invalid indices count
        return false;
    }

    // Read vertices
    file.read((char*)m_vertices, sizeof(float)*verticesCount);

    // Read indices
    file.read((char*)m_indices, sizeof(uint16_t)*indicesCount);

    // Close file
    file.close();

    // Create vertex buffer
    if (!vertexBuffer.createMeshBuffer(VULKAN_MEMORY_MESHES,
        m_vertices, m_indices, verticesCount, indicesCount))
    {
        // Could not create vertex buffer
        return false;
    }

    // Mesh successfully loaded
    return true;
}
