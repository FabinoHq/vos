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
//     Resources/IsoMapLoader.cpp : IsoMap loading management                 //
////////////////////////////////////////////////////////////////////////////////
#include "IsoMapLoader.h"


////////////////////////////////////////////////////////////////////////////////
//  IsoMapLoader default constructor                                          //
////////////////////////////////////////////////////////////////////////////////
IsoMapLoader::IsoMapLoader() :
m_state(ISOMAPLOADER_STATE_NONE),
m_stateMutex(),
m_sync(0),
m_isomaps(0),
m_chunkX(0),
m_chunkY(0)
{
    for (int i = 0; i < ISOMAP_ASSETSCOUNT; ++i)
    {
        m_chunks[i].loading = false;
        m_chunks[i].chunkX = 0;
        m_chunks[i].chunkY = 0;
        m_chunks[i].flags = ISOMAP_FLAGS_NONE;
        m_chunks[i].isomap = 0;
        m_chunksptrs[i] = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  IsoMapLoader virtual destructor                                           //
////////////////////////////////////////////////////////////////////////////////
IsoMapLoader::~IsoMapLoader()
{
    m_chunkY = 0;
    m_chunkX = 0;
    for (int i = 0; i < ISOMAP_ASSETSCOUNT; ++i)
    {
        m_chunks[i].loading = false;
        m_chunks[i].chunkX = 0;
        m_chunks[i].chunkY = 0;
        m_chunks[i].flags = ISOMAP_FLAGS_NONE;
        m_chunks[i].isomap = 0;
        m_chunksptrs[i] = 0;
    }
    m_isomaps = 0;
    m_sync = 0;
    m_state = ISOMAPLOADER_STATE_NONE;
}


////////////////////////////////////////////////////////////////////////////////
//  IsoMapLoader thread process                                               //
////////////////////////////////////////////////////////////////////////////////
void IsoMapLoader::process()
{
    IsoMapLoaderState state = ISOMAPLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();

    switch (state)
    {
        case ISOMAPLOADER_STATE_NONE:
            // Boot to init state
            m_stateMutex.lock();
            m_state = ISOMAPLOADER_STATE_INIT;
            m_stateMutex.unlock();
            break;

        case ISOMAPLOADER_STATE_INIT:
            // Init isomap loader
            if (init())
            {
                m_stateMutex.lock();
                m_state = ISOMAPLOADER_STATE_IDLE;
                m_stateMutex.unlock();
            }
            else
            {
                m_stateMutex.lock();
                m_state = ISOMAPLOADER_STATE_ERROR;
                m_stateMutex.unlock();
            }
            break;

        case ISOMAPLOADER_STATE_IDLE:
            // IsoMap loader in idle state
            SysSleep(IsoMapLoaderIdleSleepTime);
            break;

        case ISOMAPLOADER_STATE_SYNC:
            // IsoMap loader in sync state
            SysSleep(IsoMapLoaderSyncSleepTime);
            break;

        case ISOMAPLOADER_STATE_LOAD:
            // Load isomaps assets
            if (loadIsoMaps())
            {
                m_stateMutex.lock();
                m_state = ISOMAPLOADER_STATE_IDLE;
                m_stateMutex.unlock();
            }
            else
            {
                m_stateMutex.lock();
                m_state = ISOMAPLOADER_STATE_ERROR;
                m_stateMutex.unlock();
            }
            break;

        case ISOMAPLOADER_STATE_ERROR:
            // IsoMap loader error
            SysSleep(IsoMapLoaderErrorSleepTime);
            break;

        default:
            // Invalid state
            m_stateMutex.lock();
            m_state = ISOMAPLOADER_STATE_ERROR;
            m_stateMutex.unlock();
            break;
    }
}


////////////////////////////////////////////////////////////////////////////////
//  Init IsoMapLoader                                                         //
//  return : True if isomap loader is ready                                   //
////////////////////////////////////////////////////////////////////////////////
bool IsoMapLoader::init()
{
    // Allocate isomaps chunks
    m_isomaps = new(std::nothrow) IsoMapChunk[ISOMAP_ASSETSCOUNT];
    if (!m_isomaps)
    {
        // Could not allocate isomaps chunks
        return false;
    }

    // Set default chunks pointers
    for (int i = 0; i < ISOMAP_ASSETSCOUNT; ++i)
    {
        if (!m_isomaps[i].init())
        {
            // Could not init isomap chunk
            return false;
        }
        m_chunks[i].isomap = &m_isomaps[i];
        m_chunksptrs[i] = &m_chunks[i];
    }

    // Create default isomap
    int32_t cnt = 0;
    for (int32_t j = 0; j < ISOMAP_STREAMHEIGHT; ++j)
    {
        for (int32_t i = 0; i < ISOMAP_STREAMWIDTH; ++i)
        {
            if (generateFlatChunk(m_chunks[cnt]))
            {
                m_chunks[cnt].loading = false;
                m_chunks[cnt].chunkX = (m_chunkX-ISOMAP_STREAMHALFWIDTH)+i;
                m_chunks[cnt].chunkY = (m_chunkY-ISOMAP_STREAMHALFHEIGHT)+j;
            }
            else
            {
                // Could not create default isomap
                return false;
            }
            ++cnt;
        }
    }

    // Reset renderer sync
    m_sync = 0;

    // Isomap loader ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Get isomap loader state                                                   //
//  return : Current isomap loader state                                      //
////////////////////////////////////////////////////////////////////////////////
IsoMapLoaderState IsoMapLoader::getState()
{
    IsoMapLoaderState state = ISOMAPLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();
    return state;
}

////////////////////////////////////////////////////////////////////////////////
//  Get isomap loader ready state                                             //
//  return : True if isomap loader is ready, false otherwise                  //
////////////////////////////////////////////////////////////////////////////////
bool IsoMapLoader::isReady()
{
    IsoMapLoaderState state = ISOMAPLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();
    return (state == ISOMAPLOADER_STATE_IDLE);
}

////////////////////////////////////////////////////////////////////////////////
//  Reload isomaps pointers based on current chunk position                   //
//  return : True if isomaps pointers are reloaded                            //
////////////////////////////////////////////////////////////////////////////////
bool IsoMapLoader::reload(int32_t chunkX, int32_t chunkY)
{
    // Check current state
    IsoMapLoaderState state = ISOMAPLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();
    if (state != ISOMAPLOADER_STATE_IDLE)
    {
        // Isomap loader is still in loading or sync state
        return false;
    }

    // Set chunkX and chunkY
    m_chunkX = chunkX;
    m_chunkY = chunkY;

    // Set chunks loading states
    int32_t cnt = 0;
    for (int32_t j = 0; j < ISOMAP_STREAMHEIGHT; ++j)
    {
        for (int32_t i = 0; i < ISOMAP_STREAMWIDTH; ++i)
        {
            m_chunks[cnt].loading = true;
            m_chunks[cnt].chunkX = (m_chunkX-ISOMAP_STREAMHALFWIDTH)+i;
            m_chunks[cnt].chunkY = (m_chunkY-ISOMAP_STREAMHALFHEIGHT)+j;
            ++cnt;
        }
    }

    // Reset renderer sync
    m_sync = 0;

    // Load new chunks
    m_stateMutex.lock();
    m_state = ISOMAPLOADER_STATE_LOAD;
    m_stateMutex.unlock();
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Update isomaps pointers based on current chunk position                   //
//  return : True if isomaps pointers are updated                             //
////////////////////////////////////////////////////////////////////////////////
bool IsoMapLoader::update(int32_t chunkX, int32_t chunkY)
{
    // Check current state
    IsoMapLoaderState state = ISOMAPLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();
    if (state != ISOMAPLOADER_STATE_IDLE)
    {
        // Isomap loader is still in loading or sync state
        return false;
    }

    // Check Y chunk position
    if (chunkY < m_chunkY)
    {
        // Top swap
        swapTop();
        return true;
    }
    if (chunkY > m_chunkY)
    {
        // Bottom swap
        swapBottom();
        return true;
    }

    // Check X chunk position
    if (chunkX < m_chunkX)
    {
        // Left swap
        swapLeft();
        return true;
    }
    if (chunkX > m_chunkX)
    {
        // Right swap
        swapRight();
        return true;
    }

    // Isomaps pointers are up to date
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Synchronize isomaps pointers with renderer                                //
////////////////////////////////////////////////////////////////////////////////
void IsoMapLoader::sync()
{
    // Synchronize swap with renderer
    if (m_sync > 0)
    {
        // Wait for current swapchain frames to be rendered
        ++m_sync;
        if (m_sync > IsoMapLoaderSyncFrames)
        {
            // Load new chunks
            m_sync = 0;
            m_stateMutex.lock();
            m_state = ISOMAPLOADER_STATE_LOAD;
            m_stateMutex.unlock();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy isomap loader                                                     //
////////////////////////////////////////////////////////////////////////////////
void IsoMapLoader::destroyIsoMapLoader()
{
    // Reset chunk position
    m_chunkY = 0;
    m_chunkX = 0;

    // Reset isomaps pointers
    for (int i = 0; i < ISOMAP_ASSETSCOUNT; ++i)
    {
        m_chunks[i].loading = false;
        m_chunks[i].chunkX = 0;
        m_chunks[i].chunkY = 0;
        m_chunks[i].flags = ISOMAP_FLAGS_NONE;
        m_chunks[i].isomap = 0;
        m_chunksptrs[i] = 0;
    }

    // Destroy isomaps chunks
    for (int i = 0; i < ISOMAP_ASSETSCOUNT; ++i)
    {
        m_isomaps[i].destroyIsoMap();
    }
    if (m_isomaps) { delete[] m_isomaps; }
    m_isomaps = 0;

    // Reset renderer sync
    m_sync = 0;

    // Reset state
    m_state = ISOMAPLOADER_STATE_NONE;
}


////////////////////////////////////////////////////////////////////////////////
//  Load isomaps assets                                                       //
//  return : True if isomaps assets are loaded                                //
////////////////////////////////////////////////////////////////////////////////
bool IsoMapLoader::loadIsoMaps()
{
    for (int i = 0; i < ISOMAP_ASSETSCOUNT; ++i)
    {
        // Isomap needs update
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
                    // Could not update isomap
                    return false;
                }
            }
        }
    }

    // Isomaps assets are successfully loaded
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Generate flat isomap chunk                                                //
//  return : True if the isomap chunk is generated                            //
////////////////////////////////////////////////////////////////////////////////
bool IsoMapLoader::generateFlatChunk(IsoMapChunkData& chunkData)
{
    // Generate flat isomap chunk
    memset(chunkData.isomap->matrix, 0, sizeof(int32_t)*IsoMapChunkSize);

    // Set isomap chunk flags
    chunkData.flags = ISOMAP_FLAGS_EMPTY;

    // Isomap chunk successfully generated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Update flat isomap chunk                                                  //
//  return : True if the isomap chunk is updated                              //
////////////////////////////////////////////////////////////////////////////////
bool IsoMapLoader::updateFlatChunk(IsoMapChunkData& chunkData)
{
    // Update flat isomap chunk
    memset(chunkData.isomap->matrix, 0, sizeof(int32_t)*IsoMapChunkSize);

    // Set isomap chunk flags
    chunkData.flags = ISOMAP_FLAGS_EMPTY;

    // Isomap chunk successfully updated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Update isomap chunk                                                       //
//  return : True if the isomap chunk is updated                              //
////////////////////////////////////////////////////////////////////////////////
bool IsoMapLoader::updateChunk(IsoMapChunkData& chunkData,
    int32_t chunkX, int32_t chunkY)
{
    // Set VTMP file path
    std::ostringstream filepath;
    filepath << IsoMapLoaderVIMPFilePath;
    filepath << chunkX << '_' << chunkY << ".vimp";

    // Load isomap data from file
    std::ifstream file;
    file.open(filepath.str().c_str(), std::ios::in);
    if (!file.is_open())
    {
        // Could not load isomap data file
        return false;
    }

    // Read isomap elements
    int elem = 0;
    for (int j = (IsoMapChunkHeight-1); j >= 0; --j)
    {
        for (int i = 0; i < IsoMapChunkWidth; ++i)
        {
            file >> elem;
            chunkData.isomap->matrix[(j*IsoMapChunkWidth)+i] =
                static_cast<int8_t>(elem);
        }
    }

    // Set isomap chunk flags
    chunkData.flags = ISOMAP_FLAGS_NONE;

    // Close VTMP file
    file.close();

    // Isomap chunk successfully updated
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Swap isomaps pointers towards top                                         //
////////////////////////////////////////////////////////////////////////////////
void IsoMapLoader::swapTop()
{
    // Copy bottom row into tmp
    IsoMapChunkData* tmp[ISOMAP_STREAMWIDTH];
    for (uint32_t i = 0; i < ISOMAP_STREAMWIDTH; ++i)
    {
        tmp[i] = m_chunksptrs[
            ((ISOMAP_STREAMHEIGHT-1)*ISOMAP_STREAMWIDTH)+i
        ];
    }

    // Swap pointers towards top
    for (uint32_t j = (ISOMAP_STREAMHEIGHT-1); j > 0; --j)
    {
        for (uint32_t i = 0; i < ISOMAP_STREAMWIDTH; ++i)
        {
            m_chunksptrs[(j*ISOMAP_STREAMWIDTH)+i] =
                m_chunksptrs[((j-1)*ISOMAP_STREAMWIDTH)+i];
        }
    }

    // Copy tmp into top row
    for (uint32_t i = 0; i < ISOMAP_STREAMWIDTH; ++i)
    {
        m_chunksptrs[i] = tmp[i];
    }

    // Set new chunks loading states
    for (uint32_t i = 0; i < ISOMAP_STREAMWIDTH; ++i)
    {
        m_chunks[i].loading = true;
        m_chunks[i].chunkX = (m_chunkX-ISOMAP_STREAMHALFWIDTH)+i;
        m_chunks[i].chunkY = (m_chunkY-ISOMAP_STREAMHALFHEIGHT-1);
    }

    // Move chunkY
    --m_chunkY;

    // Synchronize swap with renderer
    m_sync = 1;
    m_stateMutex.lock();
    m_state = ISOMAPLOADER_STATE_SYNC;
    m_stateMutex.unlock();
}

////////////////////////////////////////////////////////////////////////////////
//  Swap isomaps pointers towards bottom                                      //
////////////////////////////////////////////////////////////////////////////////
void IsoMapLoader::swapBottom()
{
    // Copy top row into tmp
    IsoMapChunkData* tmp[ISOMAP_STREAMWIDTH];
    for (uint32_t i = 0; i < ISOMAP_STREAMWIDTH; ++i)
    {
        tmp[i] = m_chunksptrs[i];
    }

    // Swap pointers towards bottom
    for (uint32_t j = 1; j < ISOMAP_STREAMHEIGHT; ++j)
    {
        for (uint32_t i = 0; i < ISOMAP_STREAMWIDTH; ++i)
        {
            m_chunksptrs[((j-1)*ISOMAP_STREAMWIDTH)+i] =
                m_chunksptrs[(j*ISOMAP_STREAMWIDTH)+i];
        }
    }

    // Copy tmp into bottom row
    for (uint32_t i = 0; i < ISOMAP_STREAMWIDTH; ++i)
    {
        m_chunksptrs[((ISOMAP_STREAMHEIGHT-1)*ISOMAP_STREAMWIDTH)+i] =
            tmp[i];
    }

    // Set new chunks loading states
    for (uint32_t i = 0; i < ISOMAP_STREAMWIDTH; ++i)
    {
        m_chunks[
            ((ISOMAP_STREAMHEIGHT-1)*ISOMAP_STREAMWIDTH)+i
        ].loading = true;
        m_chunks[
            ((ISOMAP_STREAMHEIGHT-1)*ISOMAP_STREAMWIDTH)+i
        ].chunkX = (m_chunkX-ISOMAP_STREAMHALFWIDTH)+i;
        m_chunks[
            ((ISOMAP_STREAMHEIGHT-1)*ISOMAP_STREAMWIDTH)+i
        ].chunkY = (m_chunkY+ISOMAP_STREAMHALFHEIGHT+1);
    }

    // Move chunkY
    ++m_chunkY;

    // Synchronize swap with renderer
    m_sync = 1;
    m_stateMutex.lock();
    m_state = ISOMAPLOADER_STATE_SYNC;
    m_stateMutex.unlock();
}

////////////////////////////////////////////////////////////////////////////////
//  Swap isomaps pointers towards left                                        //
////////////////////////////////////////////////////////////////////////////////
void IsoMapLoader::swapLeft()
{
    // Copy right row into tmp
    IsoMapChunkData* tmp[ISOMAP_STREAMHEIGHT];
    for (uint32_t j = 0; j < ISOMAP_STREAMHEIGHT; ++j)
    {
        tmp[j] = m_chunksptrs[
            (j*ISOMAP_STREAMWIDTH)+(ISOMAP_STREAMWIDTH-1)
        ];
    }

    // Swap pointers towards left
    for (uint32_t i = (ISOMAP_STREAMWIDTH-1); i > 0; --i)
    {
        for (uint32_t j = 0; j < ISOMAP_STREAMHEIGHT; ++j)
        {
            m_chunksptrs[(j*ISOMAP_STREAMWIDTH)+i] =
                m_chunksptrs[(j*ISOMAP_STREAMWIDTH)+(i-1)];
        }
    }

    // Copy tmp into left row
    for (uint32_t j = 0; j < ISOMAP_STREAMHEIGHT; ++j)
    {
        m_chunksptrs[(j*ISOMAP_STREAMWIDTH)] = tmp[j];
    }

    // Set new chunks loading states
    for (uint32_t j = 0; j < ISOMAP_STREAMHEIGHT; ++j)
    {
        m_chunks[(j*ISOMAP_STREAMWIDTH)].loading = true;
        m_chunks[(j*ISOMAP_STREAMWIDTH)].chunkX =
            (m_chunkX-ISOMAP_STREAMHALFWIDTH-1);
        m_chunks[(j*ISOMAP_STREAMWIDTH)].chunkY =
            (m_chunkY-ISOMAP_STREAMHALFHEIGHT)+j;
    }

    // Move chunkX
    --m_chunkX;

    // Synchronize swap with renderer
    m_sync = 1;
    m_stateMutex.lock();
    m_state = ISOMAPLOADER_STATE_SYNC;
    m_stateMutex.unlock();
}

////////////////////////////////////////////////////////////////////////////////
//  Swap isomaps pointers towards right                                       //
////////////////////////////////////////////////////////////////////////////////
void IsoMapLoader::swapRight()
{
    // Copy left row into tmp
    IsoMapChunkData* tmp[ISOMAP_STREAMHEIGHT];
    for (uint32_t j = 0; j < ISOMAP_STREAMHEIGHT; ++j)
    {
        tmp[j] = m_chunksptrs[(j*ISOMAP_STREAMWIDTH)];
    }

    // Swap pointers towards right
    for (uint32_t i = 1; i < ISOMAP_STREAMWIDTH; ++i)
    {
        for (uint32_t j = 0; j < ISOMAP_STREAMHEIGHT; ++j)
        {
            m_chunksptrs[(j*ISOMAP_STREAMWIDTH)+(i-1)] =
                m_chunksptrs[(j*ISOMAP_STREAMWIDTH)+i];
        }
    }

    // Copy tmp into right row
    for (uint32_t j = 0; j < ISOMAP_STREAMHEIGHT; ++j)
    {
        m_chunksptrs[(j*ISOMAP_STREAMWIDTH)+(ISOMAP_STREAMWIDTH-1)] =
            tmp[j];
    }

    // Set new chunks loading states
    for (uint32_t j = 0; j < ISOMAP_STREAMHEIGHT; ++j)
    {
        m_chunks[
            (j*ISOMAP_STREAMWIDTH)+(ISOMAP_STREAMWIDTH-1)
        ].loading = true;
        m_chunks[
            (j*ISOMAP_STREAMWIDTH)+(ISOMAP_STREAMWIDTH-1)
        ].chunkX = (m_chunkX+ISOMAP_STREAMHALFWIDTH+1);
        m_chunks[
            (j*ISOMAP_STREAMWIDTH)+(ISOMAP_STREAMWIDTH-1)
        ].chunkY = (m_chunkY-ISOMAP_STREAMHALFHEIGHT)+j;
    }

    // Move chunkX
    ++m_chunkX;

    // Synchronize swap with renderer
    m_sync = 1;
    m_stateMutex.lock();
    m_state = ISOMAPLOADER_STATE_SYNC;
    m_stateMutex.unlock();
}
