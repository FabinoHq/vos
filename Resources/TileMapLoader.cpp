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
//     Resources/TileMapLoader.cpp : TileMap loading management               //
////////////////////////////////////////////////////////////////////////////////
#include "TileMapLoader.h"


////////////////////////////////////////////////////////////////////////////////
//  TileMapLoader default constructor                                         //
////////////////////////////////////////////////////////////////////////////////
TileMapLoader::TileMapLoader() :
m_state(TILEMAPLOADER_STATE_NONE),
m_stateMutex(),
m_sync(0),
m_tilemaps(0),
m_chunkX(0),
m_chunkY(0)
{
    for (int i = 0; i < TILEMAP_ASSETSCOUNT; ++i)
    {
        m_chunks[i].loading = false;
        m_chunks[i].chunkX = 0;
        m_chunks[i].chunkY = 0;
        m_chunks[i].flags = TILEMAP_FLAGS_NONE;
        m_chunks[i].tilemap = 0;
        m_chunksptrs[i] = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  TileMapLoader virtual destructor                                          //
////////////////////////////////////////////////////////////////////////////////
TileMapLoader::~TileMapLoader()
{
    m_chunkY = 0;
    m_chunkX = 0;
    for (int i = 0; i < TILEMAP_ASSETSCOUNT; ++i)
    {
        m_chunks[i].loading = false;
        m_chunks[i].chunkX = 0;
        m_chunks[i].chunkY = 0;
        m_chunks[i].flags = TILEMAP_FLAGS_NONE;
        m_chunks[i].tilemap = 0;
        m_chunksptrs[i] = 0;
    }
    m_tilemaps = 0;
    m_sync = 0;
    m_state = TILEMAPLOADER_STATE_NONE;
}


////////////////////////////////////////////////////////////////////////////////
//  TileMapLoader thread process                                              //
////////////////////////////////////////////////////////////////////////////////
void TileMapLoader::process()
{
    TileMapLoaderState state = TILEMAPLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();

    switch (state)
    {
        case TILEMAPLOADER_STATE_NONE:
            // Boot to init state
            m_stateMutex.lock();
            m_state = TILEMAPLOADER_STATE_INIT;
            m_stateMutex.unlock();
            break;

        case TILEMAPLOADER_STATE_INIT:
            // Init tilemap loader
            if (init())
            {
                m_stateMutex.lock();
                m_state = TILEMAPLOADER_STATE_IDLE;
                m_stateMutex.unlock();
            }
            else
            {
                m_stateMutex.lock();
                m_state = TILEMAPLOADER_STATE_ERROR;
                m_stateMutex.unlock();
            }
            break;

        case TILEMAPLOADER_STATE_IDLE:
            // TileMap loader in idle state
            SysSleep(TileMapLoaderIdleSleepTime);
            break;

        case TILEMAPLOADER_STATE_SYNC:
            // TileMap loader in sync state
            SysSleep(TileMapLoaderSyncSleepTime);
            break;

        case TILEMAPLOADER_STATE_LOAD:
            // Load tilemaps assets
            if (loadTileMaps())
            {
                m_stateMutex.lock();
                m_state = TILEMAPLOADER_STATE_IDLE;
                m_stateMutex.unlock();
            }
            else
            {
                m_stateMutex.lock();
                m_state = TILEMAPLOADER_STATE_ERROR;
                m_stateMutex.unlock();
            }
            break;

        case TILEMAPLOADER_STATE_ERROR:
            // TileMap loader error
            SysSleep(TileMapLoaderErrorSleepTime);
            break;

        default:
            // Invalid state
            m_stateMutex.lock();
            m_state = TILEMAPLOADER_STATE_ERROR;
            m_stateMutex.unlock();
            break;
    }
}


////////////////////////////////////////////////////////////////////////////////
//  Init TileMapLoader                                                        //
//  return : True if tilemap loader is ready                                  //
////////////////////////////////////////////////////////////////////////////////
bool TileMapLoader::init()
{
    // Allocate tilemaps chunks
    m_tilemaps = GSysMemory.alloc<TileMapChunk>(
        TILEMAP_ASSETSCOUNT, SYSMEMORY_TILEMAPS
    );
    if (!m_tilemaps)
    {
        // Could not allocate tilemaps chunks
        return false;
    }

    // Set default chunks pointers
    for (int i = 0; i < TILEMAP_ASSETSCOUNT; ++i)
    {
        if (!m_tilemaps[i].init())
        {
            // Could not init tilemap chunk
            return false;
        }
        m_chunks[i].tilemap = &m_tilemaps[i];
        m_chunksptrs[i] = &m_chunks[i];
    }

    // Create default tilemap
    int32_t cnt = 0;
    for (int32_t j = 0; j < TILEMAP_STREAMHEIGHT; ++j)
    {
        for (int32_t i = 0; i < TILEMAP_STREAMWIDTH; ++i)
        {
            if (generateFlatChunk(m_chunks[cnt]))
            {
                m_chunks[cnt].loading = false;
                m_chunks[cnt].chunkX = (m_chunkX-TILEMAP_STREAMHALFWIDTH)+i;
                m_chunks[cnt].chunkY = (m_chunkY-TILEMAP_STREAMHALFHEIGHT)+j;
            }
            else
            {
                // Could not create default tilemap
                return false;
            }
            ++cnt;
        }
    }

    // Reset renderer sync
    m_sync = 0;

    // Tilemap loader ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Get tilemap loader state                                                  //
//  return : Current tilemap loader state                                     //
////////////////////////////////////////////////////////////////////////////////
TileMapLoaderState TileMapLoader::getState()
{
    TileMapLoaderState state = TILEMAPLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();
    return state;
}

////////////////////////////////////////////////////////////////////////////////
//  Get tilemap loader ready state                                            //
//  return : True if tilemap loader is ready, false otherwise                 //
////////////////////////////////////////////////////////////////////////////////
bool TileMapLoader::isReady()
{
    TileMapLoaderState state = TILEMAPLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();
    return (state == TILEMAPLOADER_STATE_IDLE);
}

////////////////////////////////////////////////////////////////////////////////
//  Reload tilemaps pointers based on current chunk position                  //
//  return : True if tilemaps pointers are reloaded                           //
////////////////////////////////////////////////////////////////////////////////
bool TileMapLoader::reload(int32_t chunkX, int32_t chunkY)
{
    // Check current state
    TileMapLoaderState state = TILEMAPLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();
    if (state != TILEMAPLOADER_STATE_IDLE)
    {
        // Tilemap loader is still in loading or sync state
        return false;
    }

    // Set chunkX and chunkY
    m_chunkX = chunkX;
    m_chunkY = chunkY;

    // Set chunks loading states
    int32_t cnt = 0;
    for (int32_t j = 0; j < TILEMAP_STREAMHEIGHT; ++j)
    {
        for (int32_t i = 0; i < TILEMAP_STREAMWIDTH; ++i)
        {
            m_chunks[cnt].loading = true;
            m_chunks[cnt].chunkX = (m_chunkX-TILEMAP_STREAMHALFWIDTH)+i;
            m_chunks[cnt].chunkY = (m_chunkY-TILEMAP_STREAMHALFHEIGHT)+j;
            ++cnt;
        }
    }

    // Reset renderer sync
    m_sync = 0;

    // Load new chunks
    m_stateMutex.lock();
    m_state = TILEMAPLOADER_STATE_LOAD;
    m_stateMutex.unlock();
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Update tilemaps pointers based on current chunk position                  //
//  return : True if tilemaps pointers are updated                            //
////////////////////////////////////////////////////////////////////////////////
bool TileMapLoader::update(int32_t chunkX, int32_t chunkY)
{
    // Check current state
    TileMapLoaderState state = TILEMAPLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();
    if (state != TILEMAPLOADER_STATE_IDLE)
    {
        // Tilemap loader is still in loading or sync state
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

    // Tilemaps pointers are up to date
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Synchronize tilemaps pointers with renderer                               //
////////////////////////////////////////////////////////////////////////////////
void TileMapLoader::sync()
{
    // Synchronize swap with renderer
    if (m_sync > 0)
    {
        // Wait for current swapchain frames to be rendered
        ++m_sync;
        if (m_sync > TileMapLoaderSyncFrames)
        {
            // Load new chunks
            m_sync = 0;
            m_stateMutex.lock();
            m_state = TILEMAPLOADER_STATE_LOAD;
            m_stateMutex.unlock();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy tilemap loader                                                    //
////////////////////////////////////////////////////////////////////////////////
void TileMapLoader::destroyTileMapLoader()
{
    // Reset chunk position
    m_chunkY = 0;
    m_chunkX = 0;

    // Reset tilemaps pointers
    for (int i = 0; i < TILEMAP_ASSETSCOUNT; ++i)
    {
        m_chunks[i].loading = false;
        m_chunks[i].chunkX = 0;
        m_chunks[i].chunkY = 0;
        m_chunks[i].flags = TILEMAP_FLAGS_NONE;
        m_chunks[i].tilemap = 0;
        m_chunksptrs[i] = 0;
    }
    m_tilemaps = 0;

    // Reset renderer sync
    m_sync = 0;

    // Reset state
    m_state = TILEMAPLOADER_STATE_NONE;
}


////////////////////////////////////////////////////////////////////////////////
//  Load tilemaps assets                                                      //
//  return : True if tilemaps assets are loaded                               //
////////////////////////////////////////////////////////////////////////////////
bool TileMapLoader::loadTileMaps()
{
    for (int i = 0; i < TILEMAP_ASSETSCOUNT; ++i)
    {
        // Tilemap needs update
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
                    // Could not update tilemap
                    return false;
                }
            }
        }
    }

    // Tilemaps assets are successfully loaded
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Generate flat tilemap chunk                                               //
//  return : True if the tilemap chunk is generated                           //
////////////////////////////////////////////////////////////////////////////////
bool TileMapLoader::generateFlatChunk(TileMapChunkData& chunkData)
{
    // Generate flat tilemap chunk
    memset(chunkData.tilemap->matrix, 0, sizeof(int32_t)*TileMapChunkSize);

    // Set tilemap chunk flags
    chunkData.flags = TILEMAP_FLAGS_EMPTY;

    // Tilemap chunk successfully generated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Update flat tilemap chunk                                                 //
//  return : True if the tilemap chunk is updated                             //
////////////////////////////////////////////////////////////////////////////////
bool TileMapLoader::updateFlatChunk(TileMapChunkData& chunkData)
{
    // Update flat tilemap chunk
    memset(chunkData.tilemap->matrix, 0, sizeof(int32_t)*TileMapChunkSize);

    // Set tilemap chunk flags
    chunkData.flags = TILEMAP_FLAGS_EMPTY;

    // Tilemap chunk successfully updated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Update tilemap chunk                                                      //
//  return : True if the tilemap chunk is updated                             //
////////////////////////////////////////////////////////////////////////////////
bool TileMapLoader::updateChunk(TileMapChunkData& chunkData,
    int32_t chunkX, int32_t chunkY)
{
    // Set VTMP file path
    std::ostringstream filepath;
    filepath << TileMapLoaderVTMPFilePath;
    filepath << chunkX << '_' << chunkY << ".vtmp";

    // Load tilemap data from file
    std::ifstream file;
    file.open(filepath.str().c_str(), std::ios::in);
    if (!file.is_open())
    {
        // Could not load tilemap data file
        return false;
    }

    // Read tilemap elements
    int elem = 0;
    for (int j = (TileMapChunkHeight-1); j >= 0; --j)
    {
        for (int i = 0; i < TileMapChunkWidth; ++i)
        {
            file >> elem;
            chunkData.tilemap->matrix[(j*TileMapChunkWidth)+i] =
                static_cast<int8_t>(elem);
        }
    }

    // Set tilemap chunk flags
    chunkData.flags = TILEMAP_FLAGS_NONE;

    // Close VTMP file
    file.close();

    // Tilemap chunk successfully updated
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Swap tilemaps pointers towards top                                        //
////////////////////////////////////////////////////////////////////////////////
void TileMapLoader::swapTop()
{
    // Copy bottom row into tmp
    TileMapChunkData* tmp[TILEMAP_STREAMWIDTH];
    for (uint32_t i = 0; i < TILEMAP_STREAMWIDTH; ++i)
    {
        tmp[i] = m_chunksptrs[
            ((TILEMAP_STREAMHEIGHT-1)*TILEMAP_STREAMWIDTH)+i
        ];
    }

    // Swap pointers towards top
    for (uint32_t j = (TILEMAP_STREAMHEIGHT-1); j > 0; --j)
    {
        for (uint32_t i = 0; i < TILEMAP_STREAMWIDTH; ++i)
        {
            m_chunksptrs[(j*TILEMAP_STREAMWIDTH)+i] =
                m_chunksptrs[((j-1)*TILEMAP_STREAMWIDTH)+i];
        }
    }

    // Copy tmp into top row
    for (uint32_t i = 0; i < TILEMAP_STREAMWIDTH; ++i)
    {
        m_chunksptrs[i] = tmp[i];
    }

    // Set new chunks loading states
    for (uint32_t i = 0; i < TILEMAP_STREAMWIDTH; ++i)
    {
        m_chunks[i].loading = true;
        m_chunks[i].chunkX = (m_chunkX-TILEMAP_STREAMHALFWIDTH)+i;
        m_chunks[i].chunkY = (m_chunkY-TILEMAP_STREAMHALFHEIGHT-1);
    }

    // Move chunkY
    --m_chunkY;

    // Synchronize swap with renderer
    m_sync = 1;
    m_stateMutex.lock();
    m_state = TILEMAPLOADER_STATE_SYNC;
    m_stateMutex.unlock();
}

////////////////////////////////////////////////////////////////////////////////
//  Swap tilemaps pointers towards bottom                                     //
////////////////////////////////////////////////////////////////////////////////
void TileMapLoader::swapBottom()
{
    // Copy top row into tmp
    TileMapChunkData* tmp[TILEMAP_STREAMWIDTH];
    for (uint32_t i = 0; i < TILEMAP_STREAMWIDTH; ++i)
    {
        tmp[i] = m_chunksptrs[i];
    }

    // Swap pointers towards bottom
    for (uint32_t j = 1; j < TILEMAP_STREAMHEIGHT; ++j)
    {
        for (uint32_t i = 0; i < TILEMAP_STREAMWIDTH; ++i)
        {
            m_chunksptrs[((j-1)*TILEMAP_STREAMWIDTH)+i] =
                m_chunksptrs[(j*TILEMAP_STREAMWIDTH)+i];
        }
    }

    // Copy tmp into bottom row
    for (uint32_t i = 0; i < TILEMAP_STREAMWIDTH; ++i)
    {
        m_chunksptrs[((TILEMAP_STREAMHEIGHT-1)*TILEMAP_STREAMWIDTH)+i] =
            tmp[i];
    }

    // Set new chunks loading states
    for (uint32_t i = 0; i < TILEMAP_STREAMWIDTH; ++i)
    {
        m_chunks[
            ((TILEMAP_STREAMHEIGHT-1)*TILEMAP_STREAMWIDTH)+i
        ].loading = true;
        m_chunks[
            ((TILEMAP_STREAMHEIGHT-1)*TILEMAP_STREAMWIDTH)+i
        ].chunkX = (m_chunkX-TILEMAP_STREAMHALFWIDTH)+i;
        m_chunks[
            ((TILEMAP_STREAMHEIGHT-1)*TILEMAP_STREAMWIDTH)+i
        ].chunkY = (m_chunkY+TILEMAP_STREAMHALFHEIGHT+1);
    }

    // Move chunkY
    ++m_chunkY;

    // Synchronize swap with renderer
    m_sync = 1;
    m_stateMutex.lock();
    m_state = TILEMAPLOADER_STATE_SYNC;
    m_stateMutex.unlock();
}

////////////////////////////////////////////////////////////////////////////////
//  Swap tilemaps pointers towards left                                       //
////////////////////////////////////////////////////////////////////////////////
void TileMapLoader::swapLeft()
{
    // Copy right row into tmp
    TileMapChunkData* tmp[TILEMAP_STREAMHEIGHT];
    for (uint32_t j = 0; j < TILEMAP_STREAMHEIGHT; ++j)
    {
        tmp[j] = m_chunksptrs[
            (j*TILEMAP_STREAMWIDTH)+(TILEMAP_STREAMWIDTH-1)
        ];
    }

    // Swap pointers towards left
    for (uint32_t i = (TILEMAP_STREAMWIDTH-1); i > 0; --i)
    {
        for (uint32_t j = 0; j < TILEMAP_STREAMHEIGHT; ++j)
        {
            m_chunksptrs[(j*TILEMAP_STREAMWIDTH)+i] =
                m_chunksptrs[(j*TILEMAP_STREAMWIDTH)+(i-1)];
        }
    }

    // Copy tmp into left row
    for (uint32_t j = 0; j < TILEMAP_STREAMHEIGHT; ++j)
    {
        m_chunksptrs[(j*TILEMAP_STREAMWIDTH)] = tmp[j];
    }

    // Set new chunks loading states
    for (uint32_t j = 0; j < TILEMAP_STREAMHEIGHT; ++j)
    {
        m_chunks[(j*TILEMAP_STREAMWIDTH)].loading = true;
        m_chunks[(j*TILEMAP_STREAMWIDTH)].chunkX =
            (m_chunkX-TILEMAP_STREAMHALFWIDTH-1);
        m_chunks[(j*TILEMAP_STREAMWIDTH)].chunkY =
            (m_chunkY-TILEMAP_STREAMHALFHEIGHT)+j;
    }

    // Move chunkX
    --m_chunkX;

    // Synchronize swap with renderer
    m_sync = 1;
    m_stateMutex.lock();
    m_state = TILEMAPLOADER_STATE_SYNC;
    m_stateMutex.unlock();
}

////////////////////////////////////////////////////////////////////////////////
//  Swap tilemaps pointers towards right                                      //
////////////////////////////////////////////////////////////////////////////////
void TileMapLoader::swapRight()
{
    // Copy left row into tmp
    TileMapChunkData* tmp[TILEMAP_STREAMHEIGHT];
    for (uint32_t j = 0; j < TILEMAP_STREAMHEIGHT; ++j)
    {
        tmp[j] = m_chunksptrs[(j*TILEMAP_STREAMWIDTH)];
    }

    // Swap pointers towards right
    for (uint32_t i = 1; i < TILEMAP_STREAMWIDTH; ++i)
    {
        for (uint32_t j = 0; j < TILEMAP_STREAMHEIGHT; ++j)
        {
            m_chunksptrs[(j*TILEMAP_STREAMWIDTH)+(i-1)] =
                m_chunksptrs[(j*TILEMAP_STREAMWIDTH)+i];
        }
    }

    // Copy tmp into right row
    for (uint32_t j = 0; j < TILEMAP_STREAMHEIGHT; ++j)
    {
        m_chunksptrs[(j*TILEMAP_STREAMWIDTH)+(TILEMAP_STREAMWIDTH-1)] =
            tmp[j];
    }

    // Set new chunks loading states
    for (uint32_t j = 0; j < TILEMAP_STREAMHEIGHT; ++j)
    {
        m_chunks[
            (j*TILEMAP_STREAMWIDTH)+(TILEMAP_STREAMWIDTH-1)
        ].loading = true;
        m_chunks[
            (j*TILEMAP_STREAMWIDTH)+(TILEMAP_STREAMWIDTH-1)
        ].chunkX = (m_chunkX+TILEMAP_STREAMHALFWIDTH+1);
        m_chunks[
            (j*TILEMAP_STREAMWIDTH)+(TILEMAP_STREAMWIDTH-1)
        ].chunkY = (m_chunkY-TILEMAP_STREAMHALFHEIGHT)+j;
    }

    // Move chunkX
    ++m_chunkX;

    // Synchronize swap with renderer
    m_sync = 1;
    m_stateMutex.lock();
    m_state = TILEMAPLOADER_STATE_SYNC;
    m_stateMutex.unlock();
}
