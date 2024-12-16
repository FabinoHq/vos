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
//     Resources/HeightMapLoader.h : HeightMap loading management             //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RESOURCES_HEIGHTMAPLOADER_HEADER
#define VOS_RESOURCES_HEIGHTMAPLOADER_HEADER

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

    #include "../Renderer/HeightMap/HeightMapChunk.h"


    ////////////////////////////////////////////////////////////////////////////
    //  HeightMapLoader settings                                              //
    ////////////////////////////////////////////////////////////////////////////
    const uint64_t HeightMapFenceTimeout = 100000000000;
    const uint32_t HeightMapLoaderSyncFrames = (RendererMaxSwapchainFrames+3);
    const double HeightMapLoaderIdleSleepTime = 0.01;
    const double HeightMapLoaderErrorSleepTime = 0.1;
    const float HeightMapLoaderDefaultFlatY = 10.0f;
    const char HeightMapLoaderVHMPFilePath[] = "World/vhmp/";


    ////////////////////////////////////////////////////////////////////////////
    //  HeightMap flags enumeration                                           //
    ////////////////////////////////////////////////////////////////////////////
    enum HeightMapFlags
    {
        HEIGHTMAP_FLAGS_NONE = 0x00,
        HEIGHTMAP_FLAGS_RENDERSEA = 0x01
    };


    ////////////////////////////////////////////////////////////////////////////
    //  HeightMap stream assets definitions                                   //
    ////////////////////////////////////////////////////////////////////////////
    #define HEIGHTMAP_STREAMWIDTH 9
    #define HEIGHTMAP_STREAMHEIGHT 9
    #define HEIGHTMAP_STREAMHALFWIDTH 4
    #define HEIGHTMAP_STREAMHALFHEIGHT 4
    #define HEIGHTMAP_ASSETSCOUNT (HEIGHTMAP_STREAMWIDTH*HEIGHTMAP_STREAMHEIGHT)


    ////////////////////////////////////////////////////////////////////////////
    //  HeightMapLoaderState enumeration                                      //
    ////////////////////////////////////////////////////////////////////////////
    enum HeightMapLoaderState
    {
        HEIGHTMAPLOADER_STATE_NONE = 0,
        HEIGHTMAPLOADER_STATE_INIT = 1,

        HEIGHTMAPLOADER_STATE_IDLE = 2,
        HEIGHTMAPLOADER_STATE_SYNC = 3,
        HEIGHTMAPLOADER_STATE_LOAD = 4,

        HEIGHTMAPLOADER_STATE_ERROR = 5
    };


    ////////////////////////////////////////////////////////////////////////////
    //  HeightMapChunkData structure                                          //
    ////////////////////////////////////////////////////////////////////////////
    struct HeightMapChunkData
    {
        bool loading;
        int32_t chunkX;
        int32_t chunkY;
        int32_t flags;
        VertexBuffer* heightmap;
    };


    ////////////////////////////////////////////////////////////////////////////
    //  HeightMapLoader class definition                                      //
    ////////////////////////////////////////////////////////////////////////////
    class HeightMapLoader : public SysThread
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  HeightMapLoader default constructor                           //
            ////////////////////////////////////////////////////////////////////
            HeightMapLoader();

            ////////////////////////////////////////////////////////////////////
            //  HeightMapLoader virtual destructor                            //
            ////////////////////////////////////////////////////////////////////
            virtual ~HeightMapLoader();


            ////////////////////////////////////////////////////////////////////
            //  HeightMapLoader thread process                                //
            ////////////////////////////////////////////////////////////////////
            virtual void process();


            ////////////////////////////////////////////////////////////////////
            //  Init HeightMapLoader                                          //
            //  return : True if heightmap loader is ready                    //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Get heightmap loader state                                    //
            //  return : Current heightmap loader state                       //
            ////////////////////////////////////////////////////////////////////
            HeightMapLoaderState getState();

            ////////////////////////////////////////////////////////////////////
            //  Get heightmap loader ready state                              //
            //  return : True if heightmap loader is ready, false otherwise   //
            ////////////////////////////////////////////////////////////////////
            bool isReady();

            ////////////////////////////////////////////////////////////////////
            //  Reload heightmaps pointers based on current chunk position    //
            //  return : True if heightmaps pointers are reloaded             //
            ////////////////////////////////////////////////////////////////////
            bool reload(int32_t chunkX, int32_t chunkY);

            ////////////////////////////////////////////////////////////////////
            //  Update heightmaps pointers based on current chunk position    //
            //  return : True if heightmaps pointers are updated              //
            ////////////////////////////////////////////////////////////////////
            bool update(int32_t chunkX, int32_t chunkY);

            ////////////////////////////////////////////////////////////////////
            //  Synchronize heightmaps pointers with renderer                 //
            ////////////////////////////////////////////////////////////////////
            void sync();

            ////////////////////////////////////////////////////////////////////
            //  Get heightmap vertex buffer                                   //
            //  return : heightmap vertex buffer                              //
            ////////////////////////////////////////////////////////////////////
            inline VertexBuffer& heightmap(uint32_t heightmap)
            {
                return (*m_chunksptrs[
                    Math::clamp(heightmap, 0u, (HEIGHTMAP_ASSETSCOUNT-1u))
                ]->heightmap);
            }

            ////////////////////////////////////////////////////////////////////
            //  Get heightmap flags                                           //
            //  return : heightmap flags                                      //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getFlags(uint32_t heightmap)
            {
                return (m_chunksptrs[heightmap]->flags);
            }

            ////////////////////////////////////////////////////////////////////
            //  Get heightmap chunk X                                         //
            //  return : heightmap chunk X                                    //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getChunkX() const
            {
                return m_chunkX;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get heightmap chunk Y                                         //
            //  return : heightmap chunk Y                                    //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getChunkY() const
            {
                return m_chunkY;
            }

            ////////////////////////////////////////////////////////////////////
            //  Destroy heightmap loader                                      //
            ////////////////////////////////////////////////////////////////////
            void destroyHeightMapLoader();


            ////////////////////////////////////////////////////////////////////
            //  Upload vertex buffer to graphics memory                       //
            //  return : True if vertex buffer is successfully uploaded       //
            ////////////////////////////////////////////////////////////////////
            bool uploadVertexBuffer(VertexBuffer& vertexBuffer,
                const float* vertices, const uint16_t* indices,
                uint32_t verticesCount, uint32_t indicesCount);


        private:
            ////////////////////////////////////////////////////////////////////
            //  Load heightmaps assets                                        //
            //  return : True if heightmaps assets are loaded                 //
            ////////////////////////////////////////////////////////////////////
            bool loadHeightMaps();


            ////////////////////////////////////////////////////////////////////
            //  Generate flat heightmap chunk                                 //
            //  return : True if the heightmap chunk is generated             //
            ////////////////////////////////////////////////////////////////////
            bool generateFlatChunk(HeightMapChunkData& chunkData);

            ////////////////////////////////////////////////////////////////////
            //  Update flat heightmap chunk                                   //
            //  return : True if the heightmap chunk is updated               //
            ////////////////////////////////////////////////////////////////////
            bool updateFlatChunk(HeightMapChunkData& chunkData);

            ////////////////////////////////////////////////////////////////////
            //  Update heightmap chunk                                        //
            //  return : True if the heightmap chunk is updated               //
            ////////////////////////////////////////////////////////////////////
            bool updateChunk(HeightMapChunkData& chunkData,
                int32_t chunkX, int32_t chunkY);

            ////////////////////////////////////////////////////////////////////
            //  Swap heightmaps pointers towards top                          //
            //  return : True if heightmaps pointers are swapped              //
            ////////////////////////////////////////////////////////////////////
            bool swapTop();

            ////////////////////////////////////////////////////////////////////
            //  Swap heightmaps pointers towards bottom                       //
            //  return : True if heightmaps pointers are swapped              //
            ////////////////////////////////////////////////////////////////////
            bool swapBottom();

            ////////////////////////////////////////////////////////////////////
            //  Swap heightmaps pointers towards left                         //
            //  return : True if heightmaps pointers are swapped              //
            ////////////////////////////////////////////////////////////////////
            bool swapLeft();

            ////////////////////////////////////////////////////////////////////
            //  Swap heightmaps pointers towards right                        //
            //  return : True if heightmaps pointers are swapped              //
            ////////////////////////////////////////////////////////////////////
            bool swapRight();


        private:
            ////////////////////////////////////////////////////////////////////
            //  HeightMapLoader private copy constructor : Not copyable       //
            ////////////////////////////////////////////////////////////////////
            HeightMapLoader(const HeightMapLoader&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  HeightMapLoader private copy operator : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            HeightMapLoader& operator=(const HeightMapLoader&) = delete;


        private:
            HeightMapLoaderState    m_state;            // HeightMapLoader state
            SysMutex                m_stateMutex;       // State mutex

            VulkanQueue             m_transferQueue;    // Transfer queue
            VkCommandPool           m_commandPool;      // Command pool
            VkCommandBuffer         m_commandBuffer;    // Command buffer
            VulkanBuffer            m_stagingBuffer;    // Staging buffer
            VkFence                 m_fence;            // Staging fence
            uint32_t                m_sync;             // Renderer sync

            VertexBuffer*           m_heightmaps;       // Heightmaps meshes
            HeightMapChunkData      m_chunks[HEIGHTMAP_ASSETSCOUNT];
            HeightMapChunkData*     m_chunksptrs[HEIGHTMAP_ASSETSCOUNT];

            float*                  m_vertices;         // Chunk vertices
            uint16_t*               m_indices;          // Chunk indices

            int32_t                 m_chunkX;           // Heightmap chunk X
            int32_t                 m_chunkY;           // Heightmap chunk Y
    };


#endif // VOS_RESOURCES_HEIGHTMAPLOADER_HEADER
