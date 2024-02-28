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
//     Renderer/Vulkan/VertexBuffer.h : Vertex buffer management              //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_VULKAN_VERTEXBUFFER_HEADER
#define VOS_RENDERER_VULKAN_VERTEXBUFFER_HEADER

    #include "../../System/System.h"
    #include "Vulkan.h"
    #include "VulkanMemory.h"
    #include "VulkanQueue.h"
    #include "VulkanBuffer.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  Default vertex buffer vertices                                        //
    ////////////////////////////////////////////////////////////////////////////
    const uint32_t DefaultVerticesCount = 20;
    const float DefaultVertices[DefaultVerticesCount] =
    {
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, 0.0f,  1.0f, 1.0f,
        0.5f, 0.5f, 0.0f,  1.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,  0.0f, 0.0f
    };

    ////////////////////////////////////////////////////////////////////////////
    //  Default vertex buffer indices                                         //
    ////////////////////////////////////////////////////////////////////////////
    const uint32_t DefaultIndicesCount = 6;
    const uint16_t DefaultIndices[DefaultIndicesCount] =
    {
        0, 1, 2,
        2, 3, 0
    };


    ////////////////////////////////////////////////////////////////////////////
    //  VertexBuffer class definition                                         //
    ////////////////////////////////////////////////////////////////////////////
    class VertexBuffer
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  VertexBuffer default constructor                              //
            ////////////////////////////////////////////////////////////////////
            VertexBuffer();

            ////////////////////////////////////////////////////////////////////
            //  VertexBuffer destructor                                       //
            ////////////////////////////////////////////////////////////////////
            ~VertexBuffer();


            ////////////////////////////////////////////////////////////////////
            //  Create Mesh Vertex buffer                                     //
            //  return : True if Vertex buffer is successfully created        //
            ////////////////////////////////////////////////////////////////////
            bool createMeshBuffer(VulkanMemoryPool memoryPool,
                const float* vertices, const uint16_t* indices,
                uint32_t verticesCount, uint32_t indicesCount);

            ////////////////////////////////////////////////////////////////////
            //  Create HeightMap Vertex buffer                                //
            //  return : True if Vertex buffer is successfully created        //
            ////////////////////////////////////////////////////////////////////
            bool createHeightMapBuffer(VulkanMemoryPool memoryPool,
                const float* vertices, const uint16_t* indices,
                uint32_t verticesCount, uint32_t indicesCount);

            ////////////////////////////////////////////////////////////////////
            //  Create HeightFar Vertex buffer                                //
            //  return : True if Vertex buffer is successfully created        //
            ////////////////////////////////////////////////////////////////////
            bool createHeightFarBuffer(VulkanMemoryPool memoryPool,
                const float* vertices, const uint16_t* indices,
                uint32_t verticesCount, uint32_t indicesCount);

            ////////////////////////////////////////////////////////////////////
            //  Update Mesh Vertex buffer                                     //
            //  return : True if Vertex buffer is successfully updated        //
            ////////////////////////////////////////////////////////////////////
            bool updateMeshBuffer(
                const float* vertices, const uint16_t* indices,
                uint32_t verticesCount, uint32_t indicesCount);

            ////////////////////////////////////////////////////////////////////
            //  Update HeightMap Vertex buffer                                //
            //  return : True if Vertex buffer is successfully updated        //
            ////////////////////////////////////////////////////////////////////
            bool updateHeightMapBuffer(
                const float* vertices, const uint16_t* indices,
                uint32_t verticesCount, uint32_t indicesCount);

            ////////////////////////////////////////////////////////////////////
            //  Update HeightFar Vertex buffer                                //
            //  return : True if Vertex buffer is successfully updated        //
            ////////////////////////////////////////////////////////////////////
            bool updateHeightFarBuffer(
                const float* vertices, const uint16_t* indices,
                uint32_t verticesCount, uint32_t indicesCount);

            ////////////////////////////////////////////////////////////////////
            //  Destroy Vertex buffer                                         //
            ////////////////////////////////////////////////////////////////////
            void destroyBuffer();


        private:
            ////////////////////////////////////////////////////////////////////
            //  VertexBuffer private copy constructor : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            VertexBuffer(const VertexBuffer&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  VertexBuffer private copy operator : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            VertexBuffer& operator=(const VertexBuffer&) = delete;


        public:
            uint32_t        indexCount;             // Indices count
            VulkanBuffer    vertexBuffer;           // Vertex buffer
            VulkanBuffer    indexBuffer;            // Index buffer
    };


#endif // VOS_RENDERER_VULKAN_VERTEXBUFFER_HEADER
