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
m_stateMutex()
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
