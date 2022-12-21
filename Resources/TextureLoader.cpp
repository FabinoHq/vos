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
m_stagingBuffer(),
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
	// Create staging buffer
    if (!m_stagingBuffer.createBuffer(
        m_renderer.m_physicalDevice, m_renderer.m_vulkanDevice,
        m_renderer.m_vulkanMemory, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VULKAN_MEMORY_HOST, TextureMaxSize))
    {
        // Could not create staging buffer
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

	// Destroy staging buffer
    m_stagingBuffer.destroyBuffer(
    	m_renderer.m_vulkanDevice, m_renderer.m_vulkanMemory
    );
}


////////////////////////////////////////////////////////////////////////////////
//  Load embedded textures                                                    //
//  return : True if embedded textures are successfully loaded                //
////////////////////////////////////////////////////////////////////////////////
bool TextureLoader::loadEmbeddedTextures()
{
	// Load cursor texture
	if (!m_textures[TEXTURE_CURSOR].updateTexture(m_renderer,
        CursorImageWidth, CursorImageHeight, CursorImage,
        false, false))
    {
        // Could not load cursor texture
        return false;
    }

    // Load NS cursor texture
    if (!m_textures[TEXTURE_NSCURSOR].updateTexture(m_renderer,
        NSCursorImageWidth, NSCursorImageHeight, NSCursorImage,
        false, false))
    {
        // Could not load NS cursor texture
        return false;
    }

    // Load EW cursor texture
    if (!m_textures[TEXTURE_EWCURSOR].updateTexture(m_renderer,
        EWCursorImageWidth, EWCursorImageHeight, EWCursorImage,
        false, false))
    {
        // Could not load EW cursor texture
        return false;
    }

    // Load NE-SW cursor texture
    if (!m_textures[TEXTURE_NESWCURSOR].updateTexture(m_renderer,
        NESWCursorImageWidth, NESWCursorImageHeight, NESWCursorImage,
        false, false))
    {
        // Could not load NE-SW cursor texture
        return false;
    }

    // Load NW-SE cursor texture
    if (!m_textures[TEXTURE_NWSECURSOR].updateTexture(m_renderer,
        NWSECursorImageWidth, NWSECursorImageHeight, NWSECursorImage,
        false, false))
    {
        // Could not load NW-SE cursor texture
        return false;
    }

    // Embedded textures successfully loaded
    return true;
}
