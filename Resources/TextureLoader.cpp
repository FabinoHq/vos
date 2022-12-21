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
m_stagingBuffer()
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
	switch (m_state)
	{
		case TEXTURELOADER_STATE_NONE:
			// Boot to init state
			m_state = TEXTURELOADER_STATE_INIT;
			break;

		case TEXTURELOADER_STATE_INIT:
			// Init texture loader
			if (init())
			{
				m_state = TEXTURELOADER_STATE_READY;
			}
			else
			{
				m_state = TEXTURELOADER_STATE_ERROR;
			}
			break;

		case TEXTURELOADER_STATE_READY:
			// Texture loader ready
			SysSleep(0.1);
			break;

		case TEXTURELOADER_STATE_ERROR:
			// Texture loader error
			SysSleep(0.1);
			break;

		default:
			// Invalid state
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

	// Texture loader ready
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy texture loader                                                    //
////////////////////////////////////////////////////////////////////////////////
void TextureLoader::destroyTextureLoader()
{
	// Destroy staging buffer
    m_stagingBuffer.destroyBuffer(
    	m_renderer.m_vulkanDevice, m_renderer.m_vulkanMemory
    );
}
