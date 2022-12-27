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
//     Resources/MeshLoader.h : Mesh loading management                       //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RESOURCES_MESHLOADER_HEADER
#define VOS_RESOURCES_MESHLOADER_HEADER

    #include "../System/System.h"
    #include "../System/SysThread.h"
    #include "../System/SysMutex.h"
    #include "../Renderer/Vulkan/Vulkan.h"
    #include "../Renderer/Vulkan/VulkanMemory.h"
    #include "../Renderer/Vulkan/VulkanQueue.h"
    #include "../Renderer/Vulkan/VulkanBuffer.h"
    #include "../Renderer/Vulkan/VertexBuffer.h"

    #include <cstdint>
    #include <new>


    ////////////////////////////////////////////////////////////////////////////
    //  Embedded meshes                                                       //
    ////////////////////////////////////////////////////////////////////////////
    #include "../Renderer/SkyBox.h"
    #include "../Renderer/Shapes/CuboidShape.h"


    ////////////////////////////////////////////////////////////////////////////
    //  MeshLoader settings                                                   //
    ////////////////////////////////////////////////////////////////////////////
    const uint64_t MeshFenceTimeout = 100000000000;
    const double MeshLoaderIdleSleepTime = 0.01;
    const double MeshLoaderErrorSleepTime = 0.1;


    ////////////////////////////////////////////////////////////////////////////
    //  MeshesAssets enumeration                                              //
    ////////////////////////////////////////////////////////////////////////////
    enum MeshesAssets
    {
        MESHES_DEFAULT = 0,
        MESHES_SKYBOX = 1,
        MESHES_CUBOID = 2,
        MESHES_TEST = 3,

        MESHES_ASSETSCOUNT = 4
    };


    ////////////////////////////////////////////////////////////////////////////
    //  MeshLoaderState enumeration                                           //
    ////////////////////////////////////////////////////////////////////////////
    enum MeshLoaderState
    {
        MESHLOADER_STATE_NONE = 0,
        MESHLOADER_STATE_INIT = 1,
        MESHLOADER_STATE_LOADEMBEDDED = 2,

        MESHLOADER_STATE_IDLE = 3,
        MESHLOADER_STATE_PRELOAD = 4,
        MESHLOADER_STATE_LOAD = 5,

        MESHLOADER_STATE_ERROR = 6
    };


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class declaration                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer;


    ////////////////////////////////////////////////////////////////////////////
    //  MeshLoader class definition                                           //
    ////////////////////////////////////////////////////////////////////////////
    class MeshLoader : public SysThread
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  MeshLoader default constructor                                //
            ////////////////////////////////////////////////////////////////////
            MeshLoader(Renderer& renderer);

            ////////////////////////////////////////////////////////////////////
            //  MeshLoader virtual destructor                                 //
            ////////////////////////////////////////////////////////////////////
            virtual ~MeshLoader();


            ////////////////////////////////////////////////////////////////////
            //  MeshLoader thread process                                     //
            ////////////////////////////////////////////////////////////////////
            virtual void process();


            ////////////////////////////////////////////////////////////////////
            //  Init MeshLoader                                               //
            //  return : True if mesh loader is ready                         //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Start preloading meshes assets                                //
            //  return : True if meshes assets are preloading                 //
            ////////////////////////////////////////////////////////////////////
            bool startPreload();

            ////////////////////////////////////////////////////////////////////
            //  Start loading meshes assets                                   //
            //  return : True if meshes assets are loading                    //
            ////////////////////////////////////////////////////////////////////
            bool startLoading();

            ////////////////////////////////////////////////////////////////////
            //  Get mesh loader state                                         //
            //  return : Current mesh loader state                            //
            ////////////////////////////////////////////////////////////////////
            MeshLoaderState getState();

            ////////////////////////////////////////////////////////////////////
            //  Get mesh vertex buffer                                        //
            //  return : mesh vertex buffer                                   //
            ////////////////////////////////////////////////////////////////////
            inline VertexBuffer& mesh(MeshesAssets mesh)
            {
                return m_meshes[mesh];
            }

            ////////////////////////////////////////////////////////////////////
            //  Destroy mesh loader                                           //
            ////////////////////////////////////////////////////////////////////
            void destroyMeshLoader();


            ////////////////////////////////////////////////////////////////////
            //  Upload vertex buffer to graphics memory                       //
            //  return : True if vertex buffer is successfully uploaded       //
            ////////////////////////////////////////////////////////////////////
            bool uploadVertexBuffer(VertexBuffer& vertexBuffer,
                const float* vertices, const uint16_t* indices,
                uint32_t verticesCount, uint32_t indicesCount);


        private:
            ////////////////////////////////////////////////////////////////////
            //  Load embedded meshes                                          //
            //  return : True if embedded meshes are successfully loaded      //
            ////////////////////////////////////////////////////////////////////
            bool loadEmbeddedMeshes();

            ////////////////////////////////////////////////////////////////////
            //  Preload meshes assets                                         //
            //  return : True if meshes assets are preloaded                  //
            ////////////////////////////////////////////////////////////////////
            bool preloadMeshes();

            ////////////////////////////////////////////////////////////////////
            //  Load meshes assets                                            //
            //  return : True if meshes assets are loaded                     //
            ////////////////////////////////////////////////////////////////////
            bool loadMeshes();


            ////////////////////////////////////////////////////////////////////
            //  Load mesh from VMSH file                                      //
            //  return : True if the mesh is successfully loaded              //
            ////////////////////////////////////////////////////////////////////
            bool loadVMSH(VertexBuffer& vertexBuffer,
                const std::string& filepath);


        private:
            ////////////////////////////////////////////////////////////////////
            //  MeshLoader private copy constructor : Not copyable            //
            ////////////////////////////////////////////////////////////////////
            MeshLoader(const MeshLoader&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  MeshLoader private copy operator : Not copyable               //
            ////////////////////////////////////////////////////////////////////
            MeshLoader& operator=(const MeshLoader&) = delete;


        private:
            Renderer&               m_renderer;         // Renderer
            MeshLoaderState         m_state;            // MeshLoader state
            SysMutex                m_stateMutex;       // State mutex

            VulkanQueue             m_transferQueue;    // Transfer queue
            VkCommandPool           m_commandPool;      // Command pool
            VkCommandBuffer         m_commandBuffer;    // Command buffer
            VulkanBuffer            m_stagingBuffer;    // Staging buffer
            VkFence                 m_fence;            // Staging fence

            VertexBuffer*           m_meshes;           // Meshes
    };


#endif // VOS_RESOURCES_MESHLOADER_HEADER
