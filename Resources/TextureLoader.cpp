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
#include "../Renderer/Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  TextureLoader default constructor                                         //
////////////////////////////////////////////////////////////////////////////////
TextureLoader::TextureLoader(Renderer& renderer) :
m_renderer(renderer),
m_state(TEXTURELOADER_STATE_NONE),
m_stateMutex(),
m_graphicsQueue(),
m_commandPool(),
m_commandBuffer(0),
m_stagingBuffer(),
m_fence(0),
m_textures(0)
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
    if (!m_graphicsQueue.createGraphicsQueue(
        m_renderer.m_vulkanDevice, m_renderer.m_vulkanQueues))
    {
        // Could not get graphics queue handle
        return false;
    }

    // Create command pool
    VkCommandPoolCreateInfo commandPoolInfo;
    commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolInfo.pNext = 0;
    commandPoolInfo.flags =
        VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT |
        VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
    commandPoolInfo.queueFamilyIndex = m_graphicsQueue.family;

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

	// Create staging buffer
    if (!m_stagingBuffer.createBuffer(
        m_renderer.m_physicalDevice, m_renderer.m_vulkanDevice,
        m_renderer.m_vulkanMemory, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VULKAN_MEMORY_HOST, TextureMaxSize))
    {
        // Could not create staging buffer
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

    // Allocate textures assets
    m_textures = new (std::nothrow) Texture[TEXTURE_ASSETSCOUNT];
    if (!m_textures)
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
	// Destroy textures assets
	for (unsigned int i = 0; i < TEXTURE_ASSETSCOUNT; ++i)
	{
		m_textures[i].destroyTexture(m_renderer);
	}
	if (m_textures) { delete[] m_textures; }

	// Destroy staging fence
    if (m_fence)
    {
        vkDestroyFence(m_renderer.m_vulkanDevice, m_fence, 0);
    }

	// Destroy staging buffer
    m_stagingBuffer.destroyBuffer(m_renderer.m_vulkanDevice);

    // Destroy command buffer
    if (m_commandBuffer)
    {
        vkFreeCommandBuffers(m_renderer.m_vulkanDevice,
            m_commandPool, 1, &m_commandBuffer
        );
    }

    // Destroy command pool
    if (m_commandPool)
    {
        vkDestroyCommandPool(m_renderer.m_vulkanDevice, m_commandPool, 0);
    }
}


////////////////////////////////////////////////////////////////////////////////
//  Upload texture to graphics memory                                         //
//  return : True if texture is successfully uploaded                         //
////////////////////////////////////////////////////////////////////////////////
bool TextureLoader::uploadTexture(VkImage& handle,
	uint32_t width, uint32_t height, const unsigned char* data)
{
	// Create staging buffer
    uint32_t textureSize = (width*height*4);
    if (!m_stagingBuffer.createBuffer(
        m_renderer.m_physicalDevice, m_renderer.m_vulkanDevice,
        m_renderer.m_vulkanMemory, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VULKAN_MEMORY_HOST, textureSize))
    {
        // Could not create staging buffer
        return false;
    }

    // Write data into staging buffer memory
    if (!m_renderer.m_vulkanMemory.writeBufferMemory(
        m_renderer.m_vulkanDevice, m_stagingBuffer, data))
    {
        // Could not write data into staging buffer memory
        return false;
    }

    // Transfert staging buffer data to texture buffer
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

    vkCmdCopyBufferToImage(
        m_commandBuffer, m_stagingBuffer.handle, handle,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &imageCopy
    );

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
    if (vkResetFences(
        m_renderer.m_vulkanDevice, 1, &m_fence) != VK_SUCCESS)
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
    if (vkWaitForFences(m_renderer.m_vulkanDevice, 1,
        &m_fence, VK_FALSE, TextureFenceTimeout) != VK_SUCCESS)
    {
        // Transfer timed out
        return false;
    }

    // Destroy staging buffer
    m_stagingBuffer.destroyBuffer(m_renderer.m_vulkanDevice);

	// Texture successfully uploaded
	return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Load embedded textures                                                    //
//  return : True if embedded textures are successfully loaded                //
////////////////////////////////////////////////////////////////////////////////
bool TextureLoader::loadEmbeddedTextures()
{
	// Load cursor texture
	if (!m_textures[TEXTURE_CURSOR].updateTexture(m_renderer, *this,
        CursorImageWidth, CursorImageHeight, CursorImage,
        false, false))
    {
        // Could not load cursor texture
        return false;
    }

    // Load NS cursor texture
    if (!m_textures[TEXTURE_NSCURSOR].updateTexture(m_renderer, *this,
        NSCursorImageWidth, NSCursorImageHeight, NSCursorImage,
        false, false))
    {
        // Could not load NS cursor texture
        return false;
    }

    // Load EW cursor texture
    if (!m_textures[TEXTURE_EWCURSOR].updateTexture(m_renderer, *this,
        EWCursorImageWidth, EWCursorImageHeight, EWCursorImage,
        false, false))
    {
        // Could not load EW cursor texture
        return false;
    }

    // Load NE-SW cursor texture
    if (!m_textures[TEXTURE_NESWCURSOR].updateTexture(m_renderer, *this,
        NESWCursorImageWidth, NESWCursorImageHeight, NESWCursorImage,
        false, false))
    {
        // Could not load NE-SW cursor texture
        return false;
    }

    // Load NW-SE cursor texture
    if (!m_textures[TEXTURE_NWSECURSOR].updateTexture(m_renderer, *this,
        NWSECursorImageWidth, NWSECursorImageHeight, NWSECursorImage,
        false, false))
    {
        // Could not load NW-SE cursor texture
        return false;
    }

    // Load window texture
    if (!m_textures[TEXTURE_WINDOW].updateTexture(m_renderer, *this,
        WindowImageWidth, WindowImageHeight, WindowImage,
        true, false))
    {
        // Could not load window texture
        return false;
    }

    // Load pixel font texture
    if (!m_textures[TEXTURE_PIXELFONT].updateTexture(m_renderer, *this,
        PxFontImageWidth, PxFontImageHeight, PxFontImage,
        true, false))
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
    if (!m_textures[TEXTURE_TEST].updateTexture(m_renderer, *this,
        pngfile.getWidth(), pngfile.getHeight(), pngfile.getImage(),
        false, true))
    {
        return false;
    }
    pngfile.destroyImage();

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