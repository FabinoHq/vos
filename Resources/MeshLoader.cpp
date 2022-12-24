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
#include "../Renderer/Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  MeshLoader default constructor                                            //
////////////////////////////////////////////////////////////////////////////////
MeshLoader::MeshLoader(Renderer& renderer) :
m_renderer(renderer),
m_state(MESHLOADER_STATE_NONE),
m_stateMutex()
{

}

////////////////////////////////////////////////////////////////////////////////
//  MeshLoader virtual destructor                                             //
////////////////////////////////////////////////////////////////////////////////
MeshLoader::~MeshLoader()
{

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

	switch (m_state)
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
	
}


////////////////////////////////////////////////////////////////////////////////
//  Load embedded meshes                                                      //
//  return : True if embedded meshes are successfully loaded                  //
////////////////////////////////////////////////////////////////////////////////
bool MeshLoader::loadEmbeddedMeshes()
{
    // Embedded meshes successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Preload meshes assets                                                     //
//  return : True if meshes assets are preloaded                              //
////////////////////////////////////////////////////////////////////////////////
bool MeshLoader::preloadMeshes()
{
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
