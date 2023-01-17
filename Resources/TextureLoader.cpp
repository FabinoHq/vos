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
//     Resources/TextureLoader.cpp : Texture loading management               //
////////////////////////////////////////////////////////////////////////////////
#include "TextureLoader.h"


////////////////////////////////////////////////////////////////////////////////
//  TextureLoader default constructor                                         //
////////////////////////////////////////////////////////////////////////////////
TextureLoader::TextureLoader() :
m_state(TEXTURELOADER_STATE_NONE),
m_stateMutex(),
m_graphicsQueue(),
m_commandPool(0),
m_commandBuffer(0),
m_stagingBuffer(),
m_fence(0),
m_texturesGUI(0),
m_texturesHigh(0),
m_texturesArrays(0),
m_cubemaps(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  TextureLoader virtual destructor                                          //
////////////////////////////////////////////////////////////////////////////////
TextureLoader::~TextureLoader()
{

}


////////////////////////////////////////////////////////////////////////////////
//  TextureLoader thread process                                              //
////////////////////////////////////////////////////////////////////////////////
void TextureLoader::process()
{
    TextureLoaderState state = TEXTURELOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();

    switch (m_state)
    {
        case TEXTURELOADER_STATE_NONE:
            // Boot to init state
            m_stateMutex.lock();
            m_state = TEXTURELOADER_STATE_INIT;
            m_stateMutex.unlock();
            break;

        case TEXTURELOADER_STATE_INIT:
            // Init texture loader
            if (init())
            {
                m_stateMutex.lock();
                m_state = TEXTURELOADER_STATE_LOADEMBEDDED;
                m_stateMutex.unlock();
            }
            else
            {
                m_stateMutex.lock();
                m_state = TEXTURELOADER_STATE_ERROR;
                m_stateMutex.unlock();
            }
            break;

        case TEXTURELOADER_STATE_LOADEMBEDDED:
            // Load embedded textures
            if (loadEmbeddedTextures())
            {
                m_stateMutex.lock();
                m_state = TEXTURELOADER_STATE_IDLE;
                m_stateMutex.unlock();
            }
            else
            {
                m_stateMutex.lock();
                m_state = TEXTURELOADER_STATE_ERROR;
                m_stateMutex.unlock();
            }
            break;

        case TEXTURELOADER_STATE_IDLE:
            // Texture loader in idle state
            SysSleep(TextureLoaderIdleSleepTime);
            break;

        case TEXTURELOADER_STATE_PRELOAD:
            // Preload textures assets
            if (preloadTextures())
            {
                m_stateMutex.lock();
                m_state = TEXTURELOADER_STATE_IDLE;
                m_stateMutex.unlock();
            }
            else
            {
                m_stateMutex.lock();
                m_state = TEXTURELOADER_STATE_ERROR;
                m_stateMutex.unlock();
            }
            break;

        case TEXTURELOADER_STATE_LOAD:
            // Load textures assets
            if (loadTextures())
            {
                m_stateMutex.lock();
                m_state = TEXTURELOADER_STATE_IDLE;
                m_stateMutex.unlock();
            }
            else
            {
                m_stateMutex.lock();
                m_state = TEXTURELOADER_STATE_ERROR;
                m_stateMutex.unlock();
            }
            break;

        case TEXTURELOADER_STATE_ERROR:
            // Texture loader error
            SysSleep(TextureLoaderErrorSleepTime);
            break;

        default:
            // Invalid state
            m_stateMutex.lock();
            m_state = TEXTURELOADER_STATE_ERROR;
            m_stateMutex.unlock();
            break;
    }
}


////////////////////////////////////////////////////////////////////////////////
//  Init TextureLoader                                                        //
//  return : True if texture loader is ready                                  //
////////////////////////////////////////////////////////////////////////////////
bool TextureLoader::init()
{
    // Request graphics queue handle
    if (!m_graphicsQueue.createGraphicsQueue())
    {
        // Could not get graphics queue handle
        return false;
    }

    // Create command pool
    VkCommandPoolCreateInfo commandPoolInfo;
    commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolInfo.pNext = 0;
    commandPoolInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
    commandPoolInfo.queueFamilyIndex = m_graphicsQueue.family;

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

    if (vkCreateFence(GVulkanDevice, &fenceInfo, 0, &m_fence) != VK_SUCCESS)
    {
        // Could not create staging fence
        return false;
    }
    if (!m_fence)
    {
        // Invalid staging fence
        return false;
    }

    // Allocate GUI textures
    m_texturesGUI = new (std::nothrow) Texture[TEXTURE_GUICOUNT];
    if (!m_texturesGUI)
    {
        // Could not allocate GUI textures
        return false;
    }

    // Allocate high textures
    m_texturesHigh = new (std::nothrow) Texture[TEXTURE_ASSETSCOUNT];
    if (!m_texturesHigh)
    {
        // Could not allocate high textures
        return false;
    }

    // Allocate textures arrays
    m_texturesArrays = new (std::nothrow) TextureArray[TEXTURE_ARRAYSCOUNT];
    if (!m_texturesArrays)
    {
        // Could not allocate textures arrays
        return false;
    }

    // Allocate cubemaps assets
    m_cubemaps = new (std::nothrow) CubeMap[TEXTURE_CUBEMAPCOUNT];
    if (!m_cubemaps)
    {
        // Could not allocate textures assets
        return false;
    }

    // Texture loader ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Start preloading textures assets                                          //
//  return : True if textures assets are preloading                           //
////////////////////////////////////////////////////////////////////////////////
bool TextureLoader::startPreload()
{
    bool preLoading = false;
    m_stateMutex.lock();

    // Check texture loader state
    if (m_state == TEXTURELOADER_STATE_IDLE)
    {
        // Switch to preload state
        m_state = TEXTURELOADER_STATE_PRELOAD;
        preLoading = true;
    }

    m_stateMutex.unlock();
    return preLoading;
}

////////////////////////////////////////////////////////////////////////////////
//  Start loading textures assets                                             //
//  return : True if textures assets are loading                              //
////////////////////////////////////////////////////////////////////////////////
bool TextureLoader::startLoading()
{
    bool loading = false;
    m_stateMutex.lock();

    // Check texture loader state
    if (m_state == TEXTURELOADER_STATE_IDLE)
    {
        // Switch to load state
        m_state = TEXTURELOADER_STATE_LOAD;
        loading = true;
    }

    m_stateMutex.unlock();
    return loading;
}

////////////////////////////////////////////////////////////////////////////////
//  Get texture loader state                                                  //
//  return : Current texture loader state                                     //
////////////////////////////////////////////////////////////////////////////////
TextureLoaderState TextureLoader::getState()
{
    TextureLoaderState state = TEXTURELOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();
    return state;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy texture loader                                                    //
////////////////////////////////////////////////////////////////////////////////
void TextureLoader::destroyTextureLoader()
{
    // Destroy cubemaps textures
    for (int i = 0; i < TEXTURE_CUBEMAPCOUNT; ++i)
    {
        m_cubemaps[i].destroyCubeMap();
    }
    if (m_cubemaps) { delete[] m_cubemaps; }
    m_cubemaps = 0;

    // Destroy textures arrays
    for (int i = 0; i < TEXTURE_ARRAYSCOUNT; ++i)
    {
        m_texturesArrays[i].destroyTextureArray();
    }
    if (m_texturesArrays) { delete[] m_texturesArrays; }
    m_texturesArrays = 0;

    // Destroy high textures
    for (int i = 0; i < TEXTURE_ASSETSCOUNT; ++i)
    {
        m_texturesHigh[i].destroyTexture();
    }
    if (m_texturesHigh) { delete[] m_texturesHigh; }
    m_texturesHigh = 0;

    // Destroy GUI textures
    for (int i = 0; i < TEXTURE_GUICOUNT; ++i)
    {
        m_texturesGUI[i].destroyTexture();
    }
    if (m_texturesGUI) { delete[] m_texturesGUI; }
    m_texturesGUI = 0;

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
        vkFreeCommandBuffers(GVulkanDevice, m_commandPool, 1, &m_commandBuffer);
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
//  Upload texture to graphics memory                                         //
//  return : True if texture is successfully uploaded                         //
////////////////////////////////////////////////////////////////////////////////
bool TextureLoader::uploadTexture(VkImage& handle,
    uint32_t width, uint32_t height, uint32_t mipLevels,
    const unsigned char* data)
{
    // Reset texture upload memory
    GVulkanMemory.resetMemory(VULKAN_MEMORY_TEXTUREUPLOAD);

    // Create staging buffer
    uint32_t textureSize = (width*height*4);
    if (!m_stagingBuffer.createBuffer(VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VULKAN_MEMORY_TEXTUREUPLOAD, textureSize))
    {
        // Could not create staging buffer
        return false;
    }

    // Write texture into staging buffer memory
    if (!GVulkanMemory.writeBufferMemory(
        m_stagingBuffer, data, VULKAN_MEMORY_TEXTUREUPLOAD))
    {
        // Could not write texture into staging buffer memory
        return false;
    }


    // Reset command pool
    if (vkResetCommandPool(GVulkanDevice, m_commandPool, 0) != VK_SUCCESS)
    {
        // Could not reset command pool
        return false;
    }

    // Transfer staging buffer data to texture buffer
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

    // Transfer barriers structures
    VkImageSubresourceRange subresourceRange;
    subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    subresourceRange.baseMipLevel = 0;
    subresourceRange.levelCount = mipLevels;
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

    // Barrier from undefined to transfer optimal
    vkCmdPipelineBarrier(
        m_commandBuffer,
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
    imageCopy.imageExtent.width = width;
    imageCopy.imageExtent.height = height;
    imageCopy.imageExtent.depth = 1;

    // Copy staging buffer into texture buffer
    vkCmdCopyBufferToImage(
        m_commandBuffer, m_stagingBuffer.handle, handle,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &imageCopy
    );

    // Barrier from transfer to shader read-only (done after mipmaps if any)
    if (mipLevels <= 1)
    {
        vkCmdPipelineBarrier(
            m_commandBuffer,
            VK_PIPELINE_STAGE_TRANSFER_BIT,
            VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
            0, 0, 0, 0, 0, 1, &transferToShader
        );
    }

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

    if (vkQueueSubmit(m_graphicsQueue.handle,
        1, &submitInfo, m_fence) != VK_SUCCESS)
    {
        // Could not submit queue
        return false;
    }

    // Wait for transfer to finish
    if (vkWaitForFences(GVulkanDevice, 1,
        &m_fence, VK_FALSE, TextureFenceTimeout) != VK_SUCCESS)
    {
        // Transfer timed out
        return false;
    }

    // Destroy staging buffer
    m_stagingBuffer.destroyBuffer();

    // Generate texture mipmaps
    if (!generateTextureMipmaps(handle, width, height, mipLevels))
    {
        // Could not generate texture mipmaps
        return false;
    }

    // Texture successfully uploaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Generate texture mipmaps                                                  //
//  return : True if texture mipmaps are generated                            //
////////////////////////////////////////////////////////////////////////////////
bool TextureLoader::generateTextureMipmaps(VkImage& handle,
    uint32_t width, uint32_t height, uint32_t mipLevels)
{
    // Check mip levels
    if (mipLevels <= 1)
    {
        // No mipmaps generation
        return true;
    }

    // Reset command pool
    if (vkResetCommandPool(GVulkanDevice, m_commandPool, 0) != VK_SUCCESS)
    {
        // Could not reset command pool
        return false;
    }

    // Transfer staging buffer data to texture buffer
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

    // Transfer barrier structure
    VkImageSubresourceRange subresourceRange;
    subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    subresourceRange.baseMipLevel = 0;
    subresourceRange.levelCount = 1;
    subresourceRange.baseArrayLayer = 0;
    subresourceRange.layerCount = 1;

    VkImageMemoryBarrier transferToTransfer;
    transferToTransfer.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    transferToTransfer.pNext = 0;
    transferToTransfer.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    transferToTransfer.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
    transferToTransfer.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    transferToTransfer.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    transferToTransfer.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    transferToTransfer.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    transferToTransfer.image = handle;
    transferToTransfer.subresourceRange = subresourceRange;

    // Mipmap blit structures
    VkImageSubresourceLayers srcSubresource;
    srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    srcSubresource.mipLevel = 0;
    srcSubresource.baseArrayLayer = 0;
    srcSubresource.layerCount = 1;

    VkImageSubresourceLayers dstSubresource;
    dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    dstSubresource.mipLevel = 1;
    dstSubresource.baseArrayLayer = 0;
    dstSubresource.layerCount = 1;

    VkImageBlit blit;
    blit.srcSubresource = srcSubresource;
    blit.srcOffsets[0].x = 0;
    blit.srcOffsets[0].y = 0;
    blit.srcOffsets[0].z = 0;
    blit.srcOffsets[1].x = 0;
    blit.srcOffsets[1].y = 0;
    blit.srcOffsets[1].z = 1;
    blit.dstSubresource = dstSubresource;
    blit.dstOffsets[0].x = 0;
    blit.dstOffsets[0].y = 0;
    blit.dstOffsets[0].z = 0;
    blit.dstOffsets[1].x = 0;
    blit.dstOffsets[1].y = 0;
    blit.dstOffsets[1].z = 1;

    // Transfer to shader barrier structure
    VkImageMemoryBarrier transferToShader;
    transferToShader.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    transferToShader.pNext = 0;
    transferToShader.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
    transferToShader.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    transferToShader.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    transferToShader.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    transferToShader.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    transferToShader.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    transferToShader.image = handle;
    transferToShader.subresourceRange = subresourceRange;

    // Generate mipmaps
    uint32_t mipWidth = width;
    uint32_t mipHeight = height;
    for (uint32_t i = 1; i < mipLevels; ++i)
    {
        subresourceRange.baseMipLevel = (i-1);
        transferToTransfer.subresourceRange = subresourceRange;
        transferToShader.subresourceRange = subresourceRange;
        srcSubresource.mipLevel = (i-1);
        dstSubresource.mipLevel = i;

        // Barrier from transfer dst to transfer src
        vkCmdPipelineBarrier(
            m_commandBuffer,
            VK_PIPELINE_STAGE_TRANSFER_BIT,
            VK_PIPELINE_STAGE_TRANSFER_BIT,
            0, 0, 0, 0, 0, 1, &transferToTransfer
        );

        blit.srcSubresource = srcSubresource;
        blit.srcOffsets[1].x = mipWidth;
        blit.srcOffsets[1].y = mipHeight;
        blit.dstSubresource = dstSubresource;
        blit.dstOffsets[1].x = ((mipWidth > 1) ? (mipWidth >> 1) : 1);
        blit.dstOffsets[1].y = ((mipHeight > 1) ? (mipHeight >> 1) : 1);

        // Blit mipmap image with linear filter
        vkCmdBlitImage(
            m_commandBuffer,
            handle, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
            handle, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            1, &blit, VK_FILTER_LINEAR
        );

        // Barrier from transfer to shader read-only
        vkCmdPipelineBarrier(
            m_commandBuffer,
            VK_PIPELINE_STAGE_TRANSFER_BIT,
            VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
            0, 0, 0, 0, 0, 1, &transferToShader
        );

        // Next mipmap
        if (mipWidth > 1) { mipWidth >>= 1; }   // mipWidth = mipWidth/2
        if (mipHeight > 1) { mipHeight >>= 1; } // mipHeight = mipHeight/2
    }

    transferToShader.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    transferToShader.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    transferToShader.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    transferToShader.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    subresourceRange.baseMipLevel = (mipLevels - 1);
    transferToShader.subresourceRange = subresourceRange;

    // Barrier from transfer to shader read-only (last mip level)
    vkCmdPipelineBarrier(
        m_commandBuffer,
        VK_PIPELINE_STAGE_TRANSFER_BIT,
        VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
        0, 0, 0, 0, 0, 1, &transferToShader
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

    if (vkQueueSubmit(m_graphicsQueue.handle,
        1, &submitInfo, m_fence) != VK_SUCCESS)
    {
        // Could not submit queue
        return false;
    }

    // Wait for transfer to finish
    if (vkWaitForFences(GVulkanDevice, 1,
        &m_fence, VK_FALSE, TextureFenceTimeout) != VK_SUCCESS)
    {
        // Transfer timed out
        return false;
    }

    // Texture mipmaps generated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Upload texture array to graphics memory                                   //
//  return : True if texture array is successfully uploaded                   //
////////////////////////////////////////////////////////////////////////////////
bool TextureLoader::uploadTextureArray(VkImage& handle,
    uint32_t width, uint32_t height, uint32_t layers,
    uint32_t mipLevels, const unsigned char* data)
{
    // Reset texture upload memory
    GVulkanMemory.resetMemory(VULKAN_MEMORY_TEXTUREUPLOAD);

    // Create staging buffer
    uint32_t textureSize = (width*height*layers*4);
    if (!m_stagingBuffer.createBuffer(VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VULKAN_MEMORY_TEXTUREUPLOAD, textureSize))
    {
        // Could not create staging buffer
        return false;
    }

    // Write data into staging buffer memory
    if (!GVulkanMemory.writeBufferMemory(
        m_stagingBuffer, data, VULKAN_MEMORY_TEXTUREUPLOAD))
    {
        // Could not write data into staging buffer memory
        return false;
    }


    // Reset command pool
    if (vkResetCommandPool(GVulkanDevice, m_commandPool, 0) != VK_SUCCESS)
    {
        // Could not reset command pool
        return false;
    }

    // Transfer staging buffer data to cubemap buffer
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

    // Transfer barriers structures
    VkImageSubresourceRange subresourceRange;
    subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    subresourceRange.baseMipLevel = 0;
    subresourceRange.levelCount = mipLevels;
    subresourceRange.baseArrayLayer = 0;
    subresourceRange.layerCount = layers;

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

    // Barrier from undefined to transfer optimal
    vkCmdPipelineBarrier(
        m_commandBuffer,
        VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
        VK_PIPELINE_STAGE_TRANSFER_BIT,
        0, 0, 0, 0, 0, 1, &undefinedToTransfer
    );

    VkBufferImageCopy imageCopy[TextureMaxLayers];
    for (uint32_t i = 0; i < layers; ++i)
    {
        imageCopy[i].bufferOffset = ((width*height*4) * i);
        imageCopy[i].bufferRowLength = 0;
        imageCopy[i].bufferImageHeight = 0;
        imageCopy[i].imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        imageCopy[i].imageSubresource.mipLevel = 0;
        imageCopy[i].imageSubresource.baseArrayLayer = i;
        imageCopy[i].imageSubresource.layerCount = 1;
        imageCopy[i].imageOffset.x = 0;
        imageCopy[i].imageOffset.y = 0;
        imageCopy[i].imageOffset.z = 0;
        imageCopy[i].imageExtent.width = width;
        imageCopy[i].imageExtent.height = height;
        imageCopy[i].imageExtent.depth = 1;
    }

    // Copy staging buffer into texture buffer
    vkCmdCopyBufferToImage(
        m_commandBuffer, m_stagingBuffer.handle, handle,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, layers, imageCopy
    );

    // Barrier from transfer to shader read-only (done after mipmaps if any)
    if (mipLevels <= 1)
    {
        vkCmdPipelineBarrier(
            m_commandBuffer,
            VK_PIPELINE_STAGE_TRANSFER_BIT,
            VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
            0, 0, 0, 0, 0, 1, &transferToShader
        );
    }

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

    if (vkQueueSubmit(m_graphicsQueue.handle,
        1, &submitInfo, m_fence) != VK_SUCCESS)
    {
        // Could not submit queue
        return false;
    }

    // Wait for transfer to finish
    if (vkWaitForFences(GVulkanDevice, 1,
        &m_fence, VK_FALSE, TextureFenceTimeout) != VK_SUCCESS)
    {
        // Transfer timed out
        return false;
    }

    // Destroy staging buffer
    m_stagingBuffer.destroyBuffer();

    // Generate texture array mipmaps
    if (!generateTextureArrayMipmaps(handle, width, height, layers, mipLevels))
    {
        // Could not generate texture array mipmaps
        return false;
    }

    // Texture array successfully uploaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Generate texture array mipmaps                                            //
//  return : True if texture array mipmaps are generated                      //
////////////////////////////////////////////////////////////////////////////////
bool TextureLoader::generateTextureArrayMipmaps(VkImage& handle,
    uint32_t width, uint32_t height, uint32_t layers, uint32_t mipLevels)
{
    // Check mip levels
    if (mipLevels <= 1)
    {
        // No mipmaps generation
        return true;
    }

    // Reset command pool
    if (vkResetCommandPool(GVulkanDevice, m_commandPool, 0) != VK_SUCCESS)
    {
        // Could not reset command pool
        return false;
    }

    // Transfer staging buffer data to texture buffer
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

    // Transfer barrier structure
    VkImageSubresourceRange subresourceRange;
    subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    subresourceRange.baseMipLevel = 0;
    subresourceRange.levelCount = 1;
    subresourceRange.baseArrayLayer = 0;
    subresourceRange.layerCount = layers;

    VkImageMemoryBarrier transferToTransfer;
    transferToTransfer.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    transferToTransfer.pNext = 0;
    transferToTransfer.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    transferToTransfer.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
    transferToTransfer.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    transferToTransfer.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    transferToTransfer.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    transferToTransfer.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    transferToTransfer.image = handle;
    transferToTransfer.subresourceRange = subresourceRange;

    // Mipmap blit structures
    VkImageSubresourceLayers srcSubresource;
    srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    srcSubresource.mipLevel = 0;
    srcSubresource.baseArrayLayer = 0;
    srcSubresource.layerCount = 1;

    VkImageSubresourceLayers dstSubresource;
    dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    dstSubresource.mipLevel = 1;
    dstSubresource.baseArrayLayer = 0;
    dstSubresource.layerCount = 1;

    VkImageBlit blit;
    blit.srcSubresource = srcSubresource;
    blit.srcOffsets[0].x = 0;
    blit.srcOffsets[0].y = 0;
    blit.srcOffsets[0].z = 0;
    blit.srcOffsets[1].x = 0;
    blit.srcOffsets[1].y = 0;
    blit.srcOffsets[1].z = 1;
    blit.dstSubresource = dstSubresource;
    blit.dstOffsets[0].x = 0;
    blit.dstOffsets[0].y = 0;
    blit.dstOffsets[0].z = 0;
    blit.dstOffsets[1].x = 0;
    blit.dstOffsets[1].y = 0;
    blit.dstOffsets[1].z = 1;

    // Transfer to shader barrier structure
    VkImageMemoryBarrier transferToShader;
    transferToShader.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    transferToShader.pNext = 0;
    transferToShader.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
    transferToShader.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    transferToShader.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    transferToShader.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    transferToShader.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    transferToShader.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    transferToShader.image = handle;
    transferToShader.subresourceRange = subresourceRange;

    // Generate mipmaps
    uint32_t mipWidth = width;
    uint32_t mipHeight = height;
    for (uint32_t i = 1; i < mipLevels; ++i)
    {
        subresourceRange.baseMipLevel = (i-1);
        transferToTransfer.subresourceRange = subresourceRange;
        transferToShader.subresourceRange = subresourceRange;

        // Barrier from transfer dst to transfer src
        vkCmdPipelineBarrier(
            m_commandBuffer,
            VK_PIPELINE_STAGE_TRANSFER_BIT,
            VK_PIPELINE_STAGE_TRANSFER_BIT,
            0, 0, 0, 0, 0, 1, &transferToTransfer
        );

        for (uint32_t j = 0; j < layers; ++j)
        {
            srcSubresource.mipLevel = (i-1);
            srcSubresource.baseArrayLayer = j;
            dstSubresource.mipLevel = i;
            dstSubresource.baseArrayLayer = j;
            blit.srcSubresource = srcSubresource;
            blit.srcOffsets[1].x = mipWidth;
            blit.srcOffsets[1].y = mipHeight;
            blit.dstSubresource = dstSubresource;
            blit.dstOffsets[1].x = ((mipWidth > 1) ? (mipWidth >> 1) : 1);
            blit.dstOffsets[1].y = ((mipHeight > 1) ? (mipHeight >> 1) : 1);

            // Blit mipmap image with linear filter
            vkCmdBlitImage(
                m_commandBuffer,
                handle, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                handle, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                1, &blit, VK_FILTER_LINEAR
            );
        }

        // Barrier from transfer to shader read-only
        vkCmdPipelineBarrier(
            m_commandBuffer,
            VK_PIPELINE_STAGE_TRANSFER_BIT,
            VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
            0, 0, 0, 0, 0, 1, &transferToShader
        );

        // Next mipmap
        if (mipWidth > 1) { mipWidth >>= 1; }   // mipWidth = mipWidth/2
        if (mipHeight > 1) { mipHeight >>= 1; } // mipHeight = mipHeight/2
    }

    subresourceRange.baseMipLevel = (mipLevels - 1);
    transferToShader.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    transferToShader.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    transferToShader.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    transferToShader.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    transferToShader.subresourceRange = subresourceRange;

    // Barrier from transfer to shader read-only (last mip level)
    vkCmdPipelineBarrier(
        m_commandBuffer,
        VK_PIPELINE_STAGE_TRANSFER_BIT,
        VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
        0, 0, 0, 0, 0, 1, &transferToShader
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

    if (vkQueueSubmit(m_graphicsQueue.handle,
        1, &submitInfo, m_fence) != VK_SUCCESS)
    {
        // Could not submit queue
        return false;
    }

    // Wait for transfer to finish
    if (vkWaitForFences(GVulkanDevice, 1,
        &m_fence, VK_FALSE, TextureFenceTimeout) != VK_SUCCESS)
    {
        // Transfer timed out
        return false;
    }

    // Texture array mipmaps generated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Upload cubemap to graphics memory                                         //
//  return : True if cubemap is successfully uploaded                         //
////////////////////////////////////////////////////////////////////////////////
bool TextureLoader::uploadCubeMap(VkImage& handle,
    uint32_t width, uint32_t height, const unsigned char* data)
{
    // Reset texture upload memory
    GVulkanMemory.resetMemory(VULKAN_MEMORY_TEXTUREUPLOAD);

    // Create staging buffer
    uint32_t textureSize = (width*height*6*4);
    if (!m_stagingBuffer.createBuffer(VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VULKAN_MEMORY_TEXTUREUPLOAD, textureSize))
    {
        // Could not create staging buffer
        return false;
    }

    // Write data into staging buffer memory
    if (!GVulkanMemory.writeBufferMemory(
        m_stagingBuffer, data, VULKAN_MEMORY_TEXTUREUPLOAD))
    {
        // Could not write data into staging buffer memory
        return false;
    }


    // Reset command pool
    if (vkResetCommandPool(GVulkanDevice, m_commandPool, 0) != VK_SUCCESS)
    {
        // Could not reset command pool
        return false;
    }

    // Transfer staging buffer data to cubemap buffer
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

    // Transfer barriers structures
    VkImageSubresourceRange subresourceRange;
    subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    subresourceRange.baseMipLevel = 0;
    subresourceRange.levelCount = 1;
    subresourceRange.baseArrayLayer = 0;
    subresourceRange.layerCount = 6;

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

    // Barrier from undefined to transfer optimal
    vkCmdPipelineBarrier(
        m_commandBuffer,
        VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
        VK_PIPELINE_STAGE_TRANSFER_BIT,
        0, 0, 0, 0, 0, 1, &undefinedToTransfer
    );

    VkBufferImageCopy imageCopy[6];
    for (uint32_t i = 0; i < 6; ++i)
    {
        imageCopy[i].bufferOffset = ((width*height*4) * i);
        imageCopy[i].bufferRowLength = 0;
        imageCopy[i].bufferImageHeight = 0;
        imageCopy[i].imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        imageCopy[i].imageSubresource.mipLevel = 0;
        imageCopy[i].imageSubresource.baseArrayLayer = i;
        imageCopy[i].imageSubresource.layerCount = 1;
        imageCopy[i].imageOffset.x = 0;
        imageCopy[i].imageOffset.y = 0;
        imageCopy[i].imageOffset.z = 0;
        imageCopy[i].imageExtent.width = width;
        imageCopy[i].imageExtent.height = height;
        imageCopy[i].imageExtent.depth = 1;
    }

    // Copy staging buffer into texture buffer
    vkCmdCopyBufferToImage(
        m_commandBuffer, m_stagingBuffer.handle, handle,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 6, imageCopy
    );

    // Barrier from transfer to shader read-only (done after mipmaps if any)
    vkCmdPipelineBarrier(
        m_commandBuffer,
        VK_PIPELINE_STAGE_TRANSFER_BIT,
        VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
        0, 0, 0, 0, 0, 1, &transferToShader
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

    if (vkQueueSubmit(m_graphicsQueue.handle,
        1, &submitInfo, m_fence) != VK_SUCCESS)
    {
        // Could not submit queue
        return false;
    }

    // Wait for transfer to finish
    if (vkWaitForFences(GVulkanDevice, 1,
        &m_fence, VK_FALSE, TextureFenceTimeout) != VK_SUCCESS)
    {
        // Transfer timed out
        return false;
    }

    // Destroy staging buffer
    m_stagingBuffer.destroyBuffer();

    // CubeMap successfully uploaded
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Load embedded textures                                                    //
//  return : True if embedded textures are successfully loaded                //
////////////////////////////////////////////////////////////////////////////////
bool TextureLoader::loadEmbeddedTextures()
{
    // Load cursor texture
    if (!m_texturesGUI[TEXTURE_CURSOR].createTexture(
        *this, VULKAN_MEMORY_TEXTURES,
        CursorImageWidth, CursorImageHeight, CursorImage,
        false, false, TEXTUREMODE_CLAMP))
    {
        // Could not load cursor texture
        return false;
    }

    // Load NS cursor texture
    if (!m_texturesGUI[TEXTURE_NSCURSOR].createTexture(
        *this, VULKAN_MEMORY_TEXTURES,
        NSCursorImageWidth, NSCursorImageHeight, NSCursorImage,
        false, false, TEXTUREMODE_CLAMP))
    {
        // Could not load NS cursor texture
        return false;
    }

    // Load EW cursor texture
    if (!m_texturesGUI[TEXTURE_EWCURSOR].createTexture(
        *this, VULKAN_MEMORY_TEXTURES,
        EWCursorImageWidth, EWCursorImageHeight, EWCursorImage,
        false, false, TEXTUREMODE_CLAMP))
    {
        // Could not load EW cursor texture
        return false;
    }

    // Load NE-SW cursor texture
    if (!m_texturesGUI[TEXTURE_NESWCURSOR].createTexture(
        *this, VULKAN_MEMORY_TEXTURES,
        NESWCursorImageWidth, NESWCursorImageHeight, NESWCursorImage,
        false, false, TEXTUREMODE_CLAMP))
    {
        // Could not load NE-SW cursor texture
        return false;
    }

    // Load NW-SE cursor texture
    if (!m_texturesGUI[TEXTURE_NWSECURSOR].createTexture(
        *this, VULKAN_MEMORY_TEXTURES,
        NWSECursorImageWidth, NWSECursorImageHeight, NWSECursorImage,
        false, false, TEXTUREMODE_CLAMP))
    {
        // Could not load NW-SE cursor texture
        return false;
    }

    // Load window texture
    if (!m_texturesGUI[TEXTURE_WINDOW].createTexture(
        *this, VULKAN_MEMORY_TEXTURES,
        WindowImageWidth, WindowImageHeight, WindowImage,
        false, true, TEXTUREMODE_CLAMP))
    {
        // Could not load window texture
        return false;
    }

    // Load pixel font texture
    if (!m_texturesGUI[TEXTURE_PIXELFONT].createTexture(
        *this, VULKAN_MEMORY_TEXTURES,
        PxFontImageWidth, PxFontImageHeight, PxFontImage,
        false, true, TEXTUREMODE_CLAMP))
    {
        // Could not load pixel font texture
        return false;
    }

    // Embedded textures successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Preload textures assets                                                   //
//  return : True if textures assets are preloaded                            //
////////////////////////////////////////////////////////////////////////////////
bool TextureLoader::preloadTextures()
{
    // Load test texture
    PNGFile pngfile;
    if (!pngfile.loadImage("Textures/testsprite.png"))
    {
        return false;
    }
    if (!m_texturesHigh[TEXTURE_TEST].createTexture(
        *this, VULKAN_MEMORY_TEXTURES,
        pngfile.getWidth(), pngfile.getHeight(), pngfile.getImage(),
        false, false, TEXTUREMODE_CLAMP))
    {
        // Could not load test texture
        return false;
    }
    pngfile.destroyImage();

    // Load tile texture
    if (!pngfile.loadImage("Textures/tile.png"))
    {
        return false;
    }
    if (!m_texturesHigh[TEXTURE_TILE].createTexture(
        *this, VULKAN_MEMORY_TEXTURES,
        pngfile.getWidth(), pngfile.getHeight(), pngfile.getImage(),
        true, true, TEXTUREMODE_REPEAT))
    {
        // Could not load tile texture
        return false;
    }
    pngfile.destroyImage();


    // Load texture array
    unsigned int texArrayLayers = 4;
    PNGFile texArray1;
    if (!texArray1.loadImage("Textures/tile.png")) return false;
    PNGFile texArray2;
    if (!texArray2.loadImage("Textures/tile2.png")) return false;
    PNGFile texArray3;
    if (!texArray3.loadImage("Textures/tile3.png")) return false;
    PNGFile texArray4;
    if (!texArray4.loadImage("Textures/tile4.png")) return false;

    // Allocate texture array data
    unsigned int texArrayWidth = texArray1.getWidth();
    unsigned int texArrayHeight = texArray1.getHeight();
    unsigned char* texArrayData = new (std::nothrow)
        unsigned char[texArrayWidth*texArrayHeight*4*texArrayLayers];
    if (!texArrayData) return false;

    // Copy texture array data
    memcpy(
        &texArrayData[texArrayWidth*texArrayHeight*4*0],
        texArray1.getImage(), texArrayWidth*texArrayHeight*4
    );
    memcpy(
        &texArrayData[texArrayWidth*texArrayHeight*4*1],
        texArray2.getImage(), texArrayWidth*texArrayHeight*4
    );
    memcpy(
        &texArrayData[texArrayWidth*texArrayHeight*4*2],
        texArray3.getImage(), texArrayWidth*texArrayHeight*4
    );
    memcpy(
        &texArrayData[texArrayWidth*texArrayHeight*4*3],
        texArray4.getImage(), texArrayWidth*texArrayHeight*4
    );

    // Destroy array textures
    texArray1.destroyImage();
    texArray2.destroyImage();
    texArray3.destroyImage();
    texArray4.destroyImage();

    // Create texture array
    if (!m_texturesArrays[TEXTURE_ARRAY1].createTextureArray(
        *this, VULKAN_MEMORY_TEXTURES,
        texArrayWidth, texArrayHeight, texArrayLayers, texArrayData,
        true, true, TEXTUREMODE_REPEAT))
    {
        // Could not load texture array
        return false;
    }


    // Load cubemap textures
    PNGFile cubeMapRight;
    if (!cubeMapRight.loadImage("Textures/cubemaptest.png")) return false;
    PNGFile cubeMapLeft;
    if (!cubeMapLeft.loadImage("Textures/cubemaptest.png")) return false;
    PNGFile cubeMapTop;
    if (!cubeMapTop.loadImage("Textures/cubemaptest.png")) return false;
    PNGFile cubeMapBottom;
    if (!cubeMapBottom.loadImage("Textures/cubemaptest.png")) return false;
    PNGFile cubeMapFront;
    if (!cubeMapFront.loadImage("Textures/cubemaptest.png")) return false;
    PNGFile cubeMapBack;
    if (!cubeMapBack.loadImage("Textures/cubemaptest.png")) return false;

    // Allocate cubemap data
    unsigned int cubemapWidth = cubeMapFront.getWidth();
    unsigned int cubemapHeight = cubeMapFront.getHeight();
    unsigned char* cubemapData = new (std::nothrow)
        unsigned char[cubemapWidth*cubemapHeight*4*6];
    if (!cubemapData) return false;

    // Copy cubemap data
    memcpy(
        &cubemapData[cubemapWidth*cubemapHeight*4*0],
        cubeMapRight.getImage(), cubemapWidth*cubemapHeight*4
    );
    memcpy(
        &cubemapData[cubemapWidth*cubemapHeight*4*1],
        cubeMapLeft.getImage(), cubemapWidth*cubemapHeight*4
    );
    memcpy(
        &cubemapData[cubemapWidth*cubemapHeight*4*2],
        cubeMapTop.getImage(), cubemapWidth*cubemapHeight*4
    );
    memcpy(
        &cubemapData[cubemapWidth*cubemapHeight*4*3],
        cubeMapBottom.getImage(), cubemapWidth*cubemapHeight*4
    );
    memcpy(
        &cubemapData[cubemapWidth*cubemapHeight*4*4],
        cubeMapFront.getImage(), cubemapWidth*cubemapHeight*4
    );
    memcpy(
        &cubemapData[cubemapWidth*cubemapHeight*4*5],
        cubeMapBack.getImage(), cubemapWidth*cubemapHeight*4
    );

    // Destroy cubemap textures
    cubeMapRight.destroyImage();
    cubeMapLeft.destroyImage();
    cubeMapTop.destroyImage();
    cubeMapBottom.destroyImage();
    cubeMapFront.destroyImage();
    cubeMapBack.destroyImage();

    // Create cubemap texture
    if (!m_cubemaps[TEXTURE_CUBEMAPTEST].createCubeMap(
        *this, VULKAN_MEMORY_TEXTURES,
        cubemapWidth, cubemapHeight, cubemapData, true))
    {
        // Could not load cubemap texture
        return false;
    }

    // Textures assets are successfully preloaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Load textures assets                                                      //
//  return : True if textures assets are loaded                               //
////////////////////////////////////////////////////////////////////////////////
bool TextureLoader::loadTextures()
{
    // Textures assets are successfully loaded
    return true;
}
