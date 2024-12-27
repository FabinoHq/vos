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
//     Resources/IsoMapLoader.h : IsoMap loading management                   //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RESOURCES_ISOMAPLOADER_HEADER
#define VOS_RESOURCES_ISOMAPLOADER_HEADER

    #include "../System/System.h"
    #include "../System/SysThread.h"
    #include "../System/SysMutex.h"

    #include "../Renderer/Vulkan/Vulkan.h"
    #include "../Renderer/Vulkan/Swapchain.h"
    #include "../Renderer/Vulkan/VulkanMemory.h"
    #include "../Renderer/Vulkan/VulkanQueue.h"
    #include "../Renderer/Vulkan/VulkanBuffer.h"
    #include "../Renderer/Vulkan/VertexBuffer.h"
    #include "../Renderer/TileMap/IsoMapChunk.h"

    #include "../Math/Math.h"

    #include <string>
    #include <sstream>
    #include <fstream>
    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  IsoMapLoader settings                                                 //
    ////////////////////////////////////////////////////////////////////////////
    const uint64_t IsoMapFenceTimeout = 100000000000;
    const uint32_t IsoMapLoaderSyncFrames = (RendererMaxSwapchainFrames+3);
    const double IsoMapLoaderIdleSleepTime = 0.01;
    const double IsoMapLoaderSyncSleepTime = 0.001;
    const double IsoMapLoaderErrorSleepTime = 0.1;
    const char IsoMapLoaderVIMPFilePath[] = "World/vimp/";


    ////////////////////////////////////////////////////////////////////////////
    //  IsoMap flags enumeration                                              //
    ////////////////////////////////////////////////////////////////////////////
    enum IsoMapFlags
    {
        ISOMAP_FLAGS_NONE = 0x00,
        ISOMAP_FLAGS_EMPTY = 0x01,
        ISOMAP_FLAGS_WATER = 0x02
    };


    ////////////////////////////////////////////////////////////////////////////
    //  IsoMap stream assets definitions                                      //
    ////////////////////////////////////////////////////////////////////////////
    #define ISOMAP_STREAMWIDTH 7
    #define ISOMAP_STREAMHEIGHT 7
    #define ISOMAP_STREAMHALFWIDTH 3
    #define ISOMAP_STREAMHALFHEIGHT 3
    #define ISOMAP_ASSETSCOUNT (ISOMAP_STREAMWIDTH*ISOMAP_STREAMHEIGHT)


    ////////////////////////////////////////////////////////////////////////////
    //  IsoMapLoaderState enumeration                                         //
    ////////////////////////////////////////////////////////////////////////////
    enum IsoMapLoaderState
    {
        ISOMAPLOADER_STATE_NONE = 0,
        ISOMAPLOADER_STATE_INIT = 1,

        ISOMAPLOADER_STATE_IDLE = 2,
        ISOMAPLOADER_STATE_SYNC = 3,
        ISOMAPLOADER_STATE_LOAD = 4,

        ISOMAPLOADER_STATE_ERROR = 5
    };


    ////////////////////////////////////////////////////////////////////////////
    //  IsoMapChunkData structure                                             //
    ////////////////////////////////////////////////////////////////////////////
    struct IsoMapChunkData
    {
        bool loading;
        int32_t chunkX;
        int32_t chunkY;
        int32_t flags;
        IsoMapChunk* isomap;
    };


    ////////////////////////////////////////////////////////////////////////////
    //  IsoMapLoader class definition                                         //
    ////////////////////////////////////////////////////////////////////////////
    class IsoMapLoader : public SysThread
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  IsoMapLoader default constructor                              //
            ////////////////////////////////////////////////////////////////////
            IsoMapLoader();

            ////////////////////////////////////////////////////////////////////
            //  IsoMapLoader virtual destructor                               //
            ////////////////////////////////////////////////////////////////////
            virtual ~IsoMapLoader();


            ////////////////////////////////////////////////////////////////////
            //  IsoMapLoader thread process                                   //
            ////////////////////////////////////////////////////////////////////
            virtual void process();


            ////////////////////////////////////////////////////////////////////
            //  Init IsoMapLoader                                             //
            //  return : True if isomap loader is ready                       //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Get isomap loader state                                       //
            //  return : Current isomap loader state                          //
            ////////////////////////////////////////////////////////////////////
            IsoMapLoaderState getState();

            ////////////////////////////////////////////////////////////////////
            //  Get isomap loader ready state                                 //
            //  return : True if isomap loader is ready, false otherwise      //
            ////////////////////////////////////////////////////////////////////
            bool isReady();

            ////////////////////////////////////////////////////////////////////
            //  Reload isomaps pointers based on current chunk position       //
            //  return : True if isomaps pointers are reloaded                //
            ////////////////////////////////////////////////////////////////////
            bool reload(int32_t chunkX, int32_t chunkY);

            ////////////////////////////////////////////////////////////////////
            //  Update isomaps pointers based on current chunk position       //
            //  return : True if isomaps pointers are updated                 //
            ////////////////////////////////////////////////////////////////////
            bool update(int32_t chunkX, int32_t chunkY);

            ////////////////////////////////////////////////////////////////////
            //  Synchronize isomaps pointers with renderer                    //
            ////////////////////////////////////////////////////////////////////
            void sync();

            ////////////////////////////////////////////////////////////////////
            //  Get isomap chunk                                              //
            //  return : isomap chunk                                         //
            ////////////////////////////////////////////////////////////////////
            inline IsoMapChunk& isomap(int32_t chunkX, int32_t chunkY)
            {
                return (*m_chunksptrs[Math::clamp(static_cast<uint32_t>(
                    (chunkY*ISOMAP_STREAMWIDTH)+chunkX),
                    0u, (ISOMAP_ASSETSCOUNT-1u))]->isomap);
            }

            ////////////////////////////////////////////////////////////////////
            //  Get isomap flags                                              //
            //  return : isomap flags                                         //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getFlags(int32_t chunkX, int32_t chunkY)
            {
                return (m_chunksptrs[Math::clamp(static_cast<uint32_t>(
                    (chunkY*ISOMAP_STREAMWIDTH)+chunkX),
                    0u, (ISOMAP_ASSETSCOUNT-1u))]->flags);
            }

            ////////////////////////////////////////////////////////////////////
            //  Get isomap chunk X                                            //
            //  return : isomap chunk X                                       //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getChunkX() const
            {
                return m_chunkX;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get isomap chunk Y                                            //
            //  return : isomap chunk Y                                       //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getChunkY() const
            {
                return m_chunkY;
            }

            ////////////////////////////////////////////////////////////////////
            //  Destroy isomap loader                                         //
            ////////////////////////////////////////////////////////////////////
            void destroyIsoMapLoader();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Load isomaps assets                                           //
            //  return : True if isomaps assets are loaded                    //
            ////////////////////////////////////////////////////////////////////
            bool loadIsoMaps();


            ////////////////////////////////////////////////////////////////////
            //  Generate flat isomap chunk                                    //
            //  return : True if the isomap chunk is generated                //
            ////////////////////////////////////////////////////////////////////
            bool generateFlatChunk(IsoMapChunkData& chunkData);

            ////////////////////////////////////////////////////////////////////
            //  Update flat isomap chunk                                      //
            //  return : True if the isomap chunk is updated                  //
            ////////////////////////////////////////////////////////////////////
            bool updateFlatChunk(IsoMapChunkData& chunkData);

            ////////////////////////////////////////////////////////////////////
            //  Update isomap chunk                                           //
            //  return : True if the isomap chunk is updated                  //
            ////////////////////////////////////////////////////////////////////
            bool updateChunk(IsoMapChunkData& chunkData,
                int32_t chunkX, int32_t chunkY);


            ////////////////////////////////////////////////////////////////////
            //  Swap isomaps pointers towards top                             //
            ////////////////////////////////////////////////////////////////////
            void swapTop();

            ////////////////////////////////////////////////////////////////////
            //  Swap isomaps pointers towards bottom                          //
            ////////////////////////////////////////////////////////////////////
            void swapBottom();

            ////////////////////////////////////////////////////////////////////
            //  Swap isomaps pointers towards left                            //
            ////////////////////////////////////////////////////////////////////
            void swapLeft();

            ////////////////////////////////////////////////////////////////////
            //  Swap isomaps pointers towards right                           //
            ////////////////////////////////////////////////////////////////////
            void swapRight();


        private:
            ////////////////////////////////////////////////////////////////////
            //  IsoMapLoader private copy constructor : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            IsoMapLoader(const IsoMapLoader&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  IsoMapLoader private copy operator : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            IsoMapLoader& operator=(const IsoMapLoader&) = delete;


        private:
            IsoMapLoaderState       m_state;            // IsoMapLoader state
            SysMutex                m_stateMutex;       // State mutex

            uint32_t                m_sync;             // Renderer sync

            IsoMapChunk*            m_isomaps;          // Isomaps chunks
            IsoMapChunkData         m_chunks[ISOMAP_ASSETSCOUNT];
            IsoMapChunkData*        m_chunksptrs[ISOMAP_ASSETSCOUNT];

            int32_t                 m_chunkX;           // Isomap chunk X
            int32_t                 m_chunkY;           // Isomap chunk Y
    };


#endif // VOS_RESOURCES_ISOMAPLOADER_HEADER
