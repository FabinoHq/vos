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
//     Resources/MatrixColLoader.cpp : MatrixCol loading management           //
////////////////////////////////////////////////////////////////////////////////
#include "MatrixColLoader.h"


////////////////////////////////////////////////////////////////////////////////
//  MatrixColLoader default constructor                                       //
////////////////////////////////////////////////////////////////////////////////
MatrixColLoader::MatrixColLoader() :
m_state(MATRIXCOLLOADER_STATE_NONE),
m_stateMutex(),
m_sync(0),
m_matrixcols(0),
m_chunkX(0),
m_chunkY(0)
{
    for (int i = 0; i < MATRIXCOL_ASSETSCOUNT; ++i)
    {
        m_chunks[i].loading = false;
        m_chunks[i].chunkX = 0;
        m_chunks[i].chunkY = 0;
        m_chunks[i].chunk = 0;
        m_chunksptrs[i] = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  MatrixColLoader virtual destructor                                        //
////////////////////////////////////////////////////////////////////////////////
MatrixColLoader::~MatrixColLoader()
{
    m_chunkY = 0;
    m_chunkX = 0;
    for (int i = 0; i < MATRIXCOL_ASSETSCOUNT; ++i)
    {
        m_chunks[i].loading = false;
        m_chunks[i].chunkX = 0;
        m_chunks[i].chunkY = 0;
        m_chunks[i].chunk = 0;
        m_chunksptrs[i] = 0;
    }
    m_matrixcols = 0;
    m_sync = 0;
    m_state = MATRIXCOLLOADER_STATE_NONE;
}


////////////////////////////////////////////////////////////////////////////////
//  MatrixColLoader thread process                                            //
////////////////////////////////////////////////////////////////////////////////
void MatrixColLoader::process()
{
    MatrixColLoaderState state = MATRIXCOLLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();

    switch (state)
    {
        case MATRIXCOLLOADER_STATE_NONE:
            // Boot to init state
            m_stateMutex.lock();
            m_state = MATRIXCOLLOADER_STATE_INIT;
            m_stateMutex.unlock();
            break;

        case MATRIXCOLLOADER_STATE_INIT:
            // Init matrixcol loader
            if (init())
            {
                m_stateMutex.lock();
                m_state = MATRIXCOLLOADER_STATE_IDLE;
                m_stateMutex.unlock();
            }
            else
            {
                m_stateMutex.lock();
                m_state = MATRIXCOLLOADER_STATE_ERROR;
                m_stateMutex.unlock();
            }
            break;

        case MATRIXCOLLOADER_STATE_IDLE:
            // MatrixCol loader in idle state
            SysSleep(MatrixColLoaderIdleSleepTime);
            break;

        case MATRIXCOLLOADER_STATE_SYNC:
            // MatrixCol loader in sync state
            break;

        case MATRIXCOLLOADER_STATE_LOAD:
            // Load matrixcols assets
            if (loadMatrixCols())
            {
                m_stateMutex.lock();
                m_state = MATRIXCOLLOADER_STATE_IDLE;
                m_stateMutex.unlock();
            }
            else
            {
                m_stateMutex.lock();
                m_state = MATRIXCOLLOADER_STATE_ERROR;
                m_stateMutex.unlock();
            }
            break;

        case MATRIXCOLLOADER_STATE_ERROR:
            // MatrixCol loader error
            SysSleep(MatrixColLoaderErrorSleepTime);
            break;

        default:
            // Invalid state
            m_stateMutex.lock();
            m_state = MATRIXCOLLOADER_STATE_ERROR;
            m_stateMutex.unlock();
            break;
    }
}


////////////////////////////////////////////////////////////////////////////////
//  Init MatrixColLoader                                                      //
//  return : True if matrixcol loader is ready                                //
////////////////////////////////////////////////////////////////////////////////
bool MatrixColLoader::init()
{
    // Allocate matrixcols chunks
    m_matrixcols = new(std::nothrow) MatrixChunk2[MATRIXCOL_ASSETSCOUNT];
    if (!m_matrixcols)
    {
        // Could not allocate matrixcols chunks
        return false;
    }

    // Set default chunks pointers
    for (int i = 0; i < MATRIXCOL_ASSETSCOUNT; ++i)
    {
        if (!m_matrixcols[i].init())
        {
            // Could not init matrixcol chunk
            return false;
        }
        m_chunks[i].chunk = &m_matrixcols[i];
        m_chunksptrs[i] = &m_chunks[i];
    }

    // Create default matrixcol
    int32_t cnt = 0;
    for (int32_t j = 0; j < MATRIXCOL_STREAMHEIGHT; ++j)
    {
        for (int32_t i = 0; i < MATRIXCOL_STREAMWIDTH; ++i)
        {
            if (generateFlatChunk(m_chunks[cnt]))
            {
                m_chunks[cnt].loading = false;
                m_chunks[cnt].chunkX = (m_chunkX-MATRIXCOL_STREAMHALFWIDTH)+i;
                m_chunks[cnt].chunkY = (m_chunkY-MATRIXCOL_STREAMHALFHEIGHT)+j;
            }
            else
            {
                // Could not create default matrixcol
                return false;
            }
            ++cnt;
        }
    }

    // Reset physics sync
    m_sync = 0;

    // Matrixcol loader ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Get matrixcol loader state                                                //
//  return : Current matrixcol loader state                                   //
////////////////////////////////////////////////////////////////////////////////
MatrixColLoaderState MatrixColLoader::getState()
{
    MatrixColLoaderState state = MATRIXCOLLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();
    return state;
}

////////////////////////////////////////////////////////////////////////////////
//  Reload matrixcols pointers based on current chunk position                //
//  return : True if matrixcols pointers are reloaded                         //
////////////////////////////////////////////////////////////////////////////////
bool MatrixColLoader::reload(int32_t chunkX, int32_t chunkY)
{
    // Check current loading state
    MatrixColLoaderState state = MATRIXCOLLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();
    if (state != MATRIXCOLLOADER_STATE_IDLE)
    {
        // Matrixcol loader is still in loading state
        return false;
    }

    // Set chunkX and chunkY
    m_chunkX = chunkX;
    m_chunkY = chunkY;

    // Set chunks loading states
    int32_t cnt = 0;
    for (int32_t j = 0; j < MATRIXCOL_STREAMHEIGHT; ++j)
    {
        for (int32_t i = 0; i < MATRIXCOL_STREAMWIDTH; ++i)
        {
            m_chunks[cnt].loading = true;
            m_chunks[cnt].chunkX = (m_chunkX-MATRIXCOL_STREAMHALFWIDTH)+i;
            m_chunks[cnt].chunkY = (m_chunkY-MATRIXCOL_STREAMHALFHEIGHT)+j;
            ++cnt;
        }
    }

    // Reset physics sync
    m_sync = 0;

    // Load new chunks
    m_stateMutex.lock();
    m_state = MATRIXCOLLOADER_STATE_LOAD;
    m_stateMutex.unlock();
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Update matrixcols pointers based on current chunk position                //
//  return : True if matrixcols pointers are updated                          //
////////////////////////////////////////////////////////////////////////////////
bool MatrixColLoader::update(int32_t chunkX, int32_t chunkY)
{
    // Synchronize swap with physics
    if (m_sync > 0)
    {
        // Matrixcol loader is still in sync state
        sync();
        return false;
    }

    // Check Y chunk position
    if (chunkY < m_chunkY)
    {
        return swapTop();
    }
    if (chunkY > m_chunkY)
    {
        return swapBottom();
    }

    // Check X chunk position
    if (chunkX < m_chunkX)
    {
        return swapLeft();
    }
    if (chunkX > m_chunkX)
    {
        return swapRight();
    }

    // Matrixcols pointers are up to date
    sync();
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Synchronize matrixcols pointers with physics                              //
////////////////////////////////////////////////////////////////////////////////
void MatrixColLoader::sync()
{
    // Synchronize swap with physics
    if (m_sync > 0)
    {
        // Wait for current ticks to be solved
        ++m_sync;
        if (m_sync > MatrixColLoaderSyncTicks)
        {
            // Load new chunks
            m_sync = 0;
            m_stateMutex.lock();
            m_state = MATRIXCOLLOADER_STATE_LOAD;
            m_stateMutex.unlock();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy matrixcol loader                                                  //
////////////////////////////////////////////////////////////////////////////////
void MatrixColLoader::destroyMatrixColLoader()
{
    // Reset chunk position
    m_chunkY = 0;
    m_chunkX = 0;

    // Reset matrixcols pointers
    for (int i = 0; i < MATRIXCOL_ASSETSCOUNT; ++i)
    {
        m_chunks[i].loading = false;
        m_chunks[i].chunkX = 0;
        m_chunks[i].chunkY = 0;
        m_chunks[i].chunk = 0;
        m_chunksptrs[i] = 0;
    }

    // Destroy matrixcols chunks
    if (m_matrixcols) { delete[] m_matrixcols; }
    m_matrixcols = 0;

    // Reset physics sync
    m_sync = 0;

    // Reset state
    m_state = MATRIXCOLLOADER_STATE_NONE;
}


////////////////////////////////////////////////////////////////////////////////
//  Load matrixcols assets                                                    //
//  return : True if matrixcols assets are loaded                             //
////////////////////////////////////////////////////////////////////////////////
bool MatrixColLoader::loadMatrixCols()
{
    for (int i = 0; i < MATRIXCOL_ASSETSCOUNT; ++i)
    {
        // Matrixcol needs update
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
                    // Could not update matrixcol
                    return false;
                }
            }
        }
    }

    // Matrixcols assets are successfully loaded
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Generate flat matrixcol chunk                                             //
//  return : True if the matrixcol chunk is generated                         //
////////////////////////////////////////////////////////////////////////////////
bool MatrixColLoader::generateFlatChunk(MatrixColChunkData& chunkData)
{
    // Matrixcol chunk successfully generated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Update flat matrixcol chunk                                               //
//  return : True if the matrixcol chunk is updated                           //
////////////////////////////////////////////////////////////////////////////////
bool MatrixColLoader::updateFlatChunk(MatrixColChunkData& chunkData)
{
    // Matrixcol chunk successfully updated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Update matrixcol chunk                                                    //
//  return : True if the matrixcol chunk is updated                           //
////////////////////////////////////////////////////////////////////////////////
bool MatrixColLoader::updateChunk(MatrixColChunkData& chunkData,
    int32_t chunkX, int32_t chunkY)
{
    // Matrixcol chunk successfully updated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Swap matrixcols pointers towards top                                      //
//  return : True if matrixcols pointers are swapped                          //
////////////////////////////////////////////////////////////////////////////////
bool MatrixColLoader::swapTop()
{
    // Check current loading state
    MatrixColLoaderState state = MATRIXCOLLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();
    if (state != MATRIXCOLLOADER_STATE_IDLE)
    {
        // Matrixcol loader is still in loading state
        return false;
    }

    // Copy bottom row into tmp
    MatrixColChunkData* tmp[MATRIXCOL_STREAMWIDTH];
    for (uint32_t i = 0; i < MATRIXCOL_STREAMWIDTH; ++i)
    {
        tmp[i] = m_chunksptrs[
            ((MATRIXCOL_STREAMHEIGHT-1)*MATRIXCOL_STREAMWIDTH)+i
        ];
    }

    // Swap pointers towards top
    for (uint32_t j = (MATRIXCOL_STREAMHEIGHT-1); j > 0; --j)
    {
        for (uint32_t i = 0; i < MATRIXCOL_STREAMWIDTH; ++i)
        {
            m_chunksptrs[(j*MATRIXCOL_STREAMWIDTH)+i] =
                m_chunksptrs[((j-1)*MATRIXCOL_STREAMWIDTH)+i];
        }
    }

    // Copy tmp into top row
    for (uint32_t i = 0; i < MATRIXCOL_STREAMWIDTH; ++i)
    {
        m_chunksptrs[i] = tmp[i];
    }

    // Set new chunks loading states
    for (uint32_t i = 0; i < MATRIXCOL_STREAMWIDTH; ++i)
    {
        m_chunks[i].loading = true;
        m_chunks[i].chunkX = (m_chunkX-MATRIXCOL_STREAMHALFWIDTH)+i;
        m_chunks[i].chunkY = (m_chunkY-MATRIXCOL_STREAMHALFHEIGHT-1);
    }

    // Move chunkY
    --m_chunkY;

    // Synchronize swap with physics
    m_sync = 1;
    m_stateMutex.lock();
    m_state = MATRIXCOLLOADER_STATE_SYNC;
    m_stateMutex.unlock();
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Swap matrixcols pointers towards bottom                                   //
//  return : True if matrixcols pointers are swapped                          //
////////////////////////////////////////////////////////////////////////////////
bool MatrixColLoader::swapBottom()
{
    // Check current loading state
    MatrixColLoaderState state = MATRIXCOLLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();
    if (state != MATRIXCOLLOADER_STATE_IDLE)
    {
        // Matrixcol loader is still in loading state
        return false;
    }

    // Copy top row into tmp
    MatrixColChunkData* tmp[MATRIXCOL_STREAMWIDTH];
    for (uint32_t i = 0; i < MATRIXCOL_STREAMWIDTH; ++i)
    {
        tmp[i] = m_chunksptrs[i];
    }

    // Swap pointers towards bottom
    for (uint32_t j = 1; j < MATRIXCOL_STREAMHEIGHT; ++j)
    {
        for (uint32_t i = 0; i < MATRIXCOL_STREAMWIDTH; ++i)
        {
            m_chunksptrs[((j-1)*MATRIXCOL_STREAMWIDTH)+i] =
                m_chunksptrs[(j*MATRIXCOL_STREAMWIDTH)+i];
        }
    }

    // Copy tmp into bottom row
    for (uint32_t i = 0; i < MATRIXCOL_STREAMWIDTH; ++i)
    {
        m_chunksptrs[((MATRIXCOL_STREAMHEIGHT-1)*MATRIXCOL_STREAMWIDTH)+i] =
            tmp[i];
    }

    // Set new chunks loading states
    for (uint32_t i = 0; i < MATRIXCOL_STREAMWIDTH; ++i)
    {
        m_chunks[
            ((MATRIXCOL_STREAMHEIGHT-1)*MATRIXCOL_STREAMWIDTH)+i
        ].loading = true;
        m_chunks[
            ((MATRIXCOL_STREAMHEIGHT-1)*MATRIXCOL_STREAMWIDTH)+i
        ].chunkX = (m_chunkX-MATRIXCOL_STREAMHALFWIDTH)+i;
        m_chunks[
            ((MATRIXCOL_STREAMHEIGHT-1)*MATRIXCOL_STREAMWIDTH)+i
        ].chunkY = (m_chunkY+MATRIXCOL_STREAMHALFHEIGHT+1);
    }

    // Move chunkY
    ++m_chunkY;

    // Synchronize swap with physics
    m_sync = 1;
    m_stateMutex.lock();
    m_state = MATRIXCOLLOADER_STATE_SYNC;
    m_stateMutex.unlock();
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Swap matrixcols pointers towards left                                     //
//  return : True if matrixcols pointers are swapped                          //
////////////////////////////////////////////////////////////////////////////////
bool MatrixColLoader::swapLeft()
{
    // Check current loading state
    MatrixColLoaderState state = MATRIXCOLLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();
    if (state != MATRIXCOLLOADER_STATE_IDLE)
    {
        // Matrixcol loader is still in loading state
        return false;
    }

    // Copy right row into tmp
    MatrixColChunkData* tmp[MATRIXCOL_STREAMHEIGHT];
    for (uint32_t j = 0; j < MATRIXCOL_STREAMHEIGHT; ++j)
    {
        tmp[j] = m_chunksptrs[
            (j*MATRIXCOL_STREAMWIDTH)+(MATRIXCOL_STREAMWIDTH-1)
        ];
    }

    // Swap pointers towards left
    for (uint32_t i = (MATRIXCOL_STREAMWIDTH-1); i > 0; --i)
    {
        for (uint32_t j = 0; j < MATRIXCOL_STREAMHEIGHT; ++j)
        {
            m_chunksptrs[(j*MATRIXCOL_STREAMWIDTH)+i] =
                m_chunksptrs[(j*MATRIXCOL_STREAMWIDTH)+(i-1)];
        }
    }

    // Copy tmp into left row
    for (uint32_t j = 0; j < MATRIXCOL_STREAMHEIGHT; ++j)
    {
        m_chunksptrs[(j*MATRIXCOL_STREAMWIDTH)] = tmp[j];
    }

    // Set new chunks loading states
    for (uint32_t j = 0; j < MATRIXCOL_STREAMHEIGHT; ++j)
    {
        m_chunks[(j*MATRIXCOL_STREAMWIDTH)].loading = true;
        m_chunks[(j*MATRIXCOL_STREAMWIDTH)].chunkX =
            (m_chunkX-MATRIXCOL_STREAMHALFWIDTH-1);
        m_chunks[(j*MATRIXCOL_STREAMWIDTH)].chunkY =
            (m_chunkY-MATRIXCOL_STREAMHALFHEIGHT)+j;
    }

    // Move chunkX
    --m_chunkX;

    // Synchronize swap with physics
    m_sync = 1;
    m_stateMutex.lock();
    m_state = MATRIXCOLLOADER_STATE_SYNC;
    m_stateMutex.unlock();
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Swap matrixcols pointers towards right                                    //
//  return : True if matrixcols pointers are swapped                          //
////////////////////////////////////////////////////////////////////////////////
bool MatrixColLoader::swapRight()
{
    // Check current loading state
    MatrixColLoaderState state = MATRIXCOLLOADER_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();
    if (state != MATRIXCOLLOADER_STATE_IDLE)
    {
        // Matrixcol loader is still in loading state
        return false;
    }

    // Copy left row into tmp
    MatrixColChunkData* tmp[MATRIXCOL_STREAMHEIGHT];
    for (uint32_t j = 0; j < MATRIXCOL_STREAMHEIGHT; ++j)
    {
        tmp[j] = m_chunksptrs[(j*MATRIXCOL_STREAMWIDTH)];
    }

    // Swap pointers towards right
    for (uint32_t i = 1; i < MATRIXCOL_STREAMWIDTH; ++i)
    {
        for (uint32_t j = 0; j < MATRIXCOL_STREAMHEIGHT; ++j)
        {
            m_chunksptrs[(j*MATRIXCOL_STREAMWIDTH)+(i-1)] =
                m_chunksptrs[(j*MATRIXCOL_STREAMWIDTH)+i];
        }
    }

    // Copy tmp into right row
    for (uint32_t j = 0; j < MATRIXCOL_STREAMHEIGHT; ++j)
    {
        m_chunksptrs[(j*MATRIXCOL_STREAMWIDTH)+(MATRIXCOL_STREAMWIDTH-1)] =
            tmp[j];
    }

    // Set new chunks loading states
    for (uint32_t j = 0; j < MATRIXCOL_STREAMHEIGHT; ++j)
    {
        m_chunks[
            (j*MATRIXCOL_STREAMWIDTH)+(MATRIXCOL_STREAMWIDTH-1)
        ].loading = true;
        m_chunks[
            (j*MATRIXCOL_STREAMWIDTH)+(MATRIXCOL_STREAMWIDTH-1)
        ].chunkX = (m_chunkX+MATRIXCOL_STREAMHALFWIDTH+1);
        m_chunks[
            (j*MATRIXCOL_STREAMWIDTH)+(MATRIXCOL_STREAMWIDTH-1)
        ].chunkY = (m_chunkY-MATRIXCOL_STREAMHALFHEIGHT)+j;
    }

    // Move chunkX
    ++m_chunkX;

    // Synchronize swap with physics
    m_sync = 1;
    m_stateMutex.lock();
    m_state = MATRIXCOLLOADER_STATE_SYNC;
    m_stateMutex.unlock();
    return true;
}
