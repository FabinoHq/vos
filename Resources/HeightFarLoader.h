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
//     Resources/HeightFarLoader.h : HeightFar loading management             //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RESOURCES_HEIGHTFARLOADER_HEADER
#define VOS_RESOURCES_HEIGHTFARLOADER_HEADER

    #include "../System/System.h"
    #include "../System/SysThread.h"
    #include "../System/SysMutex.h"

    #include "../Renderer/Vulkan/Vulkan.h"
    #include "../Renderer/Vulkan/Swapchain.h"
    #include "../Renderer/Vulkan/VulkanMemory.h"
    #include "../Renderer/Vulkan/VulkanQueue.h"
    #include "../Renderer/Vulkan/VulkanBuffer.h"
    #include "../Renderer/Vulkan/VertexBuffer.h"
    #include "../Renderer/HeightMap/HeightFarChunk.h"

    #include "../Math/Math.h"

    #include <string>
    #include <sstream>
    #include <fstream>
    #include <cstdint>
    #include <new>


    ////////////////////////////////////////////////////////////////////////////
    //  HeightFarLoader settings                                              //
    ////////////////////////////////////////////////////////////////////////////
    const uint64_t HeightFarFenceTimeout = 100000000000;
    const uint32_t HeightFarLoaderSyncFrames = (RendererMaxSwapchainFrames+3);
    const double HeightFarLoaderIdleSleepTime = 0.01;
    const double HeightFarLoaderSyncSleepTime = 0.001;
    const double HeightFarLoaderErrorSleepTime = 0.1;
    const float HeightFarLoaderDefaultFlatY = 10.0f;
    const char HeightFarLoaderVHMPFilePath[] = "World/vhmf/";


    ////////////////////////////////////////////////////////////////////////////
    //  HeightFar flags enumeration                                           //
    ////////////////////////////////////////////////////////////////////////////
    enum HeightFarFlags
    {
        HEIGHTFAR_FLAGS_NONE = 0x00,
        HEIGHTFAR_FLAGS_RENDERSEA = 0x01
    };


    ////////////////////////////////////////////////////////////////////////////
    //  HeightFar stream assets definitions                                   //
    ////////////////////////////////////////////////////////////////////////////
    #define HEIGHTFAR_STREAMWIDTH 9
    #define HEIGHTFAR_STREAMHEIGHT 9
    #define HEIGHTFAR_STREAMHALFWIDTH 4
    #define HEIGHTFAR_STREAMHALFHEIGHT 4
    #define HEIGHTFAR_ASSETSCOUNT (HEIGHTFAR_STREAMWIDTH*HEIGHTFAR_STREAMHEIGHT)


    ////////////////////////////////////////////////////////////////////////////
    //  HeightFarLoaderState enumeration                                      //
    ////////////////////////////////////////////////////////////////////////////
    enum HeightFarLoaderState
    {
        HEIGHTFARLOADER_STATE_NONE = 0,
        HEIGHTFARLOADER_STATE_INIT = 1,

        HEIGHTFARLOADER_STATE_IDLE = 2,
        HEIGHTFARLOADER_STATE_SYNC = 3,
        HEIGHTFARLOADER_STATE_LOAD = 4,

        HEIGHTFARLOADER_STATE_ERROR = 5
    };


    ////////////////////////////////////////////////////////////////////////////
    //  HeightFarpChunkData structure                                         //
    ////////////////////////////////////////////////////////////////////////////
    struct HeightFarChunkData
    {
        bool loading;
        int32_t chunkX;
        int32_t chunkY;
        int32_t flags;
        VertexBuffer* heightfar;
    };


    ////////////////////////////////////////////////////////////////////////////
    //  HeightFarLoader class definition                                      //
    ////////////////////////////////////////////////////////////////////////////
    class HeightFarLoader : public SysThread
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  HeightFarLoader default constructor                           //
            ////////////////////////////////////////////////////////////////////
            HeightFarLoader();

            ////////////////////////////////////////////////////////////////////
            //  HeightFarLoader virtual destructor                            //
            ////////////////////////////////////////////////////////////////////
            virtual ~HeightFarLoader();


            ////////////////////////////////////////////////////////////////////
            //  HeightFarLoader thread process                                //
            ////////////////////////////////////////////////////////////////////
            virtual void process();


            ////////////////////////////////////////////////////////////////////
            //  Init HeightFarLoader                                          //
            //  return : True if heightfar loader is ready                    //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Get heightfar loader state                                    //
            //  return : Current heightfar loader state                       //
            ////////////////////////////////////////////////////////////////////
            HeightFarLoaderState getState();

            ////////////////////////////////////////////////////////////////////
            //  Get heightfar loader ready state                              //
            //  return : True if heightfar loader is ready, false otherwise   //
            ////////////////////////////////////////////////////////////////////
            bool isReady();

            ////////////////////////////////////////////////////////////////////
            //  Reload heightfars pointers based on current chunk position    //
            //  return : True if heightfars pointers are reloaded             //
            ////////////////////////////////////////////////////////////////////
            bool reload(int32_t chunkX, int32_t chunkY);

            ////////////////////////////////////////////////////////////////////
            //  Update heightfars pointers based on current chunk position    //
            //  return : True if heightfars pointers are updated              //
            ////////////////////////////////////////////////////////////////////
            bool update(int32_t chunkX, int32_t chunkY);

            ////////////////////////////////////////////////////////////////////
            //  Synchronize heightfars pointers with renderer                 //
            ////////////////////////////////////////////////////////////////////
            void sync();

            ////////////////////////////////////////////////////////////////////
            //  Get heightfar vertex buffer                                   //
            //  return : heightfar vertex buffer                              //
            ////////////////////////////////////////////////////////////////////
            inline VertexBuffer& heightfar(int32_t chunkX, int32_t chunkY)
            {
                return (*m_chunksptrs[Math::clamp(static_cast<uint32_t>(
                    (chunkY*HEIGHTFAR_STREAMWIDTH)+chunkX),
                    0u, (HEIGHTFAR_ASSETSCOUNT-1u))]->heightfar);
            }

            ////////////////////////////////////////////////////////////////////
            //  Get heightfar flags                                           //
            //  return : heightfar flags                                      //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getFlags(int32_t chunkX, int32_t chunkY)
            {
                return (m_chunksptrs[Math::clamp(static_cast<uint32_t>(
                    (chunkY*HEIGHTFAR_STREAMWIDTH)+chunkX),
                    0u, (HEIGHTFAR_ASSETSCOUNT-1u))]->flags);
            }

            ////////////////////////////////////////////////////////////////////
            //  Get heightfar chunk X                                         //
            //  return : heightfar chunk X                                    //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getChunkX() const
            {
                return m_chunkX;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get heightfar chunk Y                                         //
            //  return : heightfar chunk Y                                    //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getChunkY() const
            {
                return m_chunkY;
            }

            ////////////////////////////////////////////////////////////////////
            //  Destroy heightfar loader                                      //
            ////////////////////////////////////////////////////////////////////
            void destroyHeightFarLoader();


            ////////////////////////////////////////////////////////////////////
            //  Upload vertex buffer to graphics memory                       //
            //  return : True if vertex buffer is successfully uploaded       //
            ////////////////////////////////////////////////////////////////////
            bool uploadVertexBuffer(VertexBuffer& vertexBuffer,
                const float* vertices, const uint16_t* indices,
                uint32_t verticesCount, uint32_t indicesCount);


        private:
            ////////////////////////////////////////////////////////////////////
            //  Load heightfars assets                                        //
            //  return : True if heightfars assets are loaded                 //
            ////////////////////////////////////////////////////////////////////
            bool loadHeightFars();


            ////////////////////////////////////////////////////////////////////
            //  Generate flat heightfar chunk                                 //
            //  return : True if the heightfar chunk is generated             //
            ////////////////////////////////////////////////////////////////////
            bool generateFlatChunk(HeightFarChunkData& chunkData);

            ////////////////////////////////////////////////////////////////////
            //  Update flat heightfar chunk                                   //
            //  return : True if the heightfar chunk is updated               //
            ////////////////////////////////////////////////////////////////////
            bool updateFlatChunk(HeightFarChunkData& chunkData);

            ////////////////////////////////////////////////////////////////////
            //  Update heightfar chunk                                        //
            //  return : True if the heightfar chunk is updated               //
            ////////////////////////////////////////////////////////////////////
            bool updateChunk(HeightFarChunkData& chunkData,
                int32_t chunkX, int32_t chunkY);

            ////////////////////////////////////////////////////////////////////
            //  Swap heightfars pointers towards top                          //
            //  return : True if heightfars pointers are swapped              //
            ////////////////////////////////////////////////////////////////////
            bool swapTop();

            ////////////////////////////////////////////////////////////////////
            //  Swap heightfars pointers towards bottom                       //
            //  return : True if heightfars pointers are swapped              //
            ////////////////////////////////////////////////////////////////////
            bool swapBottom();

            ////////////////////////////////////////////////////////////////////
            //  Swap heightfars pointers towards left                         //
            //  return : True if heightfars pointers are swapped              //
            ////////////////////////////////////////////////////////////////////
            bool swapLeft();

            ////////////////////////////////////////////////////////////////////
            //  Swap heightfars pointers towards right                        //
            //  return : True if heightfars pointers are swapped              //
            ////////////////////////////////////////////////////////////////////
            bool swapRight();


        private:
            ////////////////////////////////////////////////////////////////////
            //  HeightFarLoader private copy constructor : Not copyable       //
            ////////////////////////////////////////////////////////////////////
            HeightFarLoader(const HeightFarLoader&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  HeightFarLoader private copy operator : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            HeightFarLoader& operator=(const HeightFarLoader&) = delete;


        private:
            HeightFarLoaderState    m_state;            // HeightFarLoader state
            SysMutex                m_stateMutex;       // State mutex

            VulkanQueue             m_transferQueue;    // Transfer queue
            VkCommandPool           m_commandPool;      // Command pool
            VkCommandBuffer         m_commandBuffer;    // Command buffer
            VulkanBuffer            m_stagingBuffer;    // Staging buffer
            VkFence                 m_fence;            // Staging fence
            uint32_t                m_sync;             // Renderer sync

            VertexBuffer*           m_heightfars;       // Heightfars meshes
            HeightFarChunkData      m_chunks[HEIGHTFAR_ASSETSCOUNT];
            HeightFarChunkData*     m_chunksptrs[HEIGHTFAR_ASSETSCOUNT];

            float*                  m_vertices;         // Chunk vertices
            uint16_t*               m_indices;          // Chunk indices

            int32_t                 m_chunkX;           // Heightfar chunk X
            int32_t                 m_chunkY;           // Heightfar chunk Y
    };


#endif // VOS_RESOURCES_HEIGHTFARLOADER_HEADER
