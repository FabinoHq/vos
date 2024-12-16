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
//     Resources/TileMapLoader.h : TileMap loading management                 //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RESOURCES_TILEMAPLOADER_HEADER
#define VOS_RESOURCES_TILEMAPLOADER_HEADER

    #include "../System/System.h"
    #include "../System/SysThread.h"
    #include "../System/SysMutex.h"
    #include "../Renderer/Vulkan/Vulkan.h"
    #include "../Renderer/Vulkan/Swapchain.h"
    #include "../Renderer/Vulkan/VulkanMemory.h"
    #include "../Renderer/Vulkan/VulkanQueue.h"
    #include "../Renderer/Vulkan/VulkanBuffer.h"
    #include "../Renderer/Vulkan/VertexBuffer.h"

    #include <string>
    #include <sstream>
    #include <fstream>
    #include <cstdint>
    #include <new>

    #include "../Renderer/TileMap/TileMapChunk.h"


    ////////////////////////////////////////////////////////////////////////////
    //  TileMapLoader settings                                                //
    ////////////////////////////////////////////////////////////////////////////
    const uint64_t TileMapFenceTimeout = 100000000000;
    const uint32_t TileMapLoaderSyncFrames = (RendererMaxSwapchainFrames+3);
    const double TileMapLoaderIdleSleepTime = 0.01;
    const double TileMapLoaderErrorSleepTime = 0.1;
    const char TileMapLoaderVTMPFilePath[] = "World/vtmp/";


    ////////////////////////////////////////////////////////////////////////////
    //  TileMap stream assets definitions                                     //
    ////////////////////////////////////////////////////////////////////////////
    #define TILEMAP_STREAMWIDTH 9
    #define TILEMAP_STREAMHEIGHT 9
    #define TILEMAP_STREAMHALFWIDTH 4
    #define TILEMAP_STREAMHALFHEIGHT 4
    #define TILEMAP_ASSETSCOUNT (TILEMAP_STREAMWIDTH*TILEMAP_STREAMHEIGHT)


    ////////////////////////////////////////////////////////////////////////////
    //  TileMapLoaderState enumeration                                        //
    ////////////////////////////////////////////////////////////////////////////
    enum TileMapLoaderState
    {
        TILEMAPLOADER_STATE_NONE = 0,
        TILEMAPLOADER_STATE_INIT = 1,

        TILEMAPLOADER_STATE_IDLE = 2,
        TILEMAPLOADER_STATE_SYNC = 3,
        TILEMAPLOADER_STATE_LOAD = 4,

        TILEMAPLOADER_STATE_ERROR = 5
    };


    ////////////////////////////////////////////////////////////////////////////
    //  TileMapChunkData structure                                            //
    ////////////////////////////////////////////////////////////////////////////
    struct TileMapChunkData
    {
        bool loading;
        int32_t chunkX;
        int32_t chunkY;
        int32_t flags;
        TileMapChunk* tilemap;
    };


    ////////////////////////////////////////////////////////////////////////////
    //  TileMapLoader class definition                                        //
    ////////////////////////////////////////////////////////////////////////////
    class TileMapLoader : public SysThread
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  TileMapLoader default constructor                             //
            ////////////////////////////////////////////////////////////////////
            TileMapLoader();

            ////////////////////////////////////////////////////////////////////
            //  TileMapLoader virtual destructor                              //
            ////////////////////////////////////////////////////////////////////
            virtual ~TileMapLoader();


            ////////////////////////////////////////////////////////////////////
            //  TileMapLoader thread process                                  //
            ////////////////////////////////////////////////////////////////////
            virtual void process();


            ////////////////////////////////////////////////////////////////////
            //  Init TileMapLoader                                            //
            //  return : True if tilemap loader is ready                      //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Get tilemap loader state                                      //
            //  return : Current tilemap loader state                         //
            ////////////////////////////////////////////////////////////////////
            TileMapLoaderState getState();

            ////////////////////////////////////////////////////////////////////
            //  Get tilemap loader ready state                                //
            //  return : True if tilemap loader is ready, false otherwise     //
            ////////////////////////////////////////////////////////////////////
            bool isReady();

            ////////////////////////////////////////////////////////////////////
            //  Reload tilemaps pointers based on current chunk position      //
            //  return : True if tilemaps pointers are reloaded               //
            ////////////////////////////////////////////////////////////////////
            bool reload(int32_t chunkX, int32_t chunkY);

            ////////////////////////////////////////////////////////////////////
            //  Update tilemaps pointers based on current chunk position      //
            //  return : True if tilemaps pointers are updated                //
            ////////////////////////////////////////////////////////////////////
            bool update(int32_t chunkX, int32_t chunkY);

            ////////////////////////////////////////////////////////////////////
            //  Synchronize tilemaps pointers with renderer                   //
            ////////////////////////////////////////////////////////////////////
            void sync();

            ////////////////////////////////////////////////////////////////////
            //  Get tilemap chunk                                             //
            //  return : tilemap chunk                                        //
            ////////////////////////////////////////////////////////////////////
            inline TileMapChunk& tilemap(uint32_t tilemap)
            {
                return (*m_chunksptrs[
                    Math::clamp(tilemap, 0u, (TILEMAP_ASSETSCOUNT-1u))
                ]->tilemap);
            }

            ////////////////////////////////////////////////////////////////////
            //  Get tilemap chunk X                                           //
            //  return : tilemap chunk X                                      //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getChunkX() const
            {
                return m_chunkX;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get tilemap chunk Y                                           //
            //  return : tilemap chunk Y                                      //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getChunkY() const
            {
                return m_chunkY;
            }

            ////////////////////////////////////////////////////////////////////
            //  Destroy tilemap loader                                        //
            ////////////////////////////////////////////////////////////////////
            void destroyTileMapLoader();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Load tilemaps assets                                          //
            //  return : True if tilemaps assets are loaded                   //
            ////////////////////////////////////////////////////////////////////
            bool loadTileMaps();


            ////////////////////////////////////////////////////////////////////
            //  Generate flat tilemap chunk                                   //
            //  return : True if the tilemap chunk is generated               //
            ////////////////////////////////////////////////////////////////////
            bool generateFlatChunk(TileMapChunkData& chunkData);

            ////////////////////////////////////////////////////////////////////
            //  Update flat tilemap chunk                                     //
            //  return : True if the tilemap chunk is updated                 //
            ////////////////////////////////////////////////////////////////////
            bool updateFlatChunk(TileMapChunkData& chunkData);

            ////////////////////////////////////////////////////////////////////
            //  Update tilemap chunk                                          //
            //  return : True if the tilemap chunk is updated                 //
            ////////////////////////////////////////////////////////////////////
            bool updateChunk(TileMapChunkData& chunkData,
                int32_t chunkX, int32_t chunkY);

            ////////////////////////////////////////////////////////////////////
            //  Swap tilemaps pointers towards top                            //
            //  return : True if tilemaps pointers are swapped                //
            ////////////////////////////////////////////////////////////////////
            bool swapTop();

            ////////////////////////////////////////////////////////////////////
            //  Swap tilemaps pointers towards bottom                         //
            //  return : True if tilemaps pointers are swapped                //
            ////////////////////////////////////////////////////////////////////
            bool swapBottom();

            ////////////////////////////////////////////////////////////////////
            //  Swap tilemaps pointers towards left                           //
            //  return : True if tilemaps pointers are swapped                //
            ////////////////////////////////////////////////////////////////////
            bool swapLeft();

            ////////////////////////////////////////////////////////////////////
            //  Swap tilemaps pointers towards right                          //
            //  return : True if tilemaps pointers are swapped                //
            ////////////////////////////////////////////////////////////////////
            bool swapRight();


        private:
            ////////////////////////////////////////////////////////////////////
            //  TileMapLoader private copy constructor : Not copyable         //
            ////////////////////////////////////////////////////////////////////
            TileMapLoader(const TileMapLoader&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  TileMapLoader private copy operator : Not copyable            //
            ////////////////////////////////////////////////////////////////////
            TileMapLoader& operator=(const TileMapLoader&) = delete;


        private:
            TileMapLoaderState      m_state;            // TileMapLoader state
            SysMutex                m_stateMutex;       // State mutex

            uint32_t                m_sync;             // Renderer sync

            TileMapChunk*           m_tilemaps;         // Tilemaps chunks
            TileMapChunkData        m_chunks[TILEMAP_ASSETSCOUNT];
            TileMapChunkData*       m_chunksptrs[TILEMAP_ASSETSCOUNT];

            int32_t                 m_chunkX;           // Tilemap chunk X
            int32_t                 m_chunkY;           // Tilemap chunk Y
    };


#endif // VOS_RESOURCES_TILEMAPLOADER_HEADER
