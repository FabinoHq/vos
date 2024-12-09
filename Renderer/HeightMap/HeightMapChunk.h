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
//     Renderer/HeightMap/HeightMapChunk.h : HeightMap chunk renderer         //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_HEIGHTMAP_HEIGHTMAPCHUNK_HEADER
#define VOS_RENDERER_HEIGHTMAP_HEIGHTMAPCHUNK_HEADER

    #include "../../System/System.h"
    #include "../Vulkan/Vulkan.h"
    #include "../Vulkan/Swapchain.h"
    #include "../Vulkan/GraphicsLayout.h"
    #include "../Vulkan/VertexBuffer.h"
    #include "../Vulkan/TextureArray.h"
    #include "../../Math/Math.h"
    #include "../../Math/Vector3.h"
    #include "../../Math/Matrix4x4.h"
    #include "../../Math/Transform3.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  HeightMapChunk settings                                               //
    ////////////////////////////////////////////////////////////////////////////
    const uint16_t HeightMapChunkWidth = 128;
    const uint16_t HeightMapChunkHeight = 128;
    const float HeightMapChunkPlaneWidth = 4.0f;
    const float HeightMapChunkPlaneHeight = 4.0f;
    const float HeightMapChunkXStride = 512.0f;
    const float HeightMapChunkZStride = 512.0f;
    const float HeightMapChunkTexcoordsWidth = 128.0f;
    const float HeightMapChunkTexcoordsHeight = 128.0f;
    const uint32_t HeightMapChunkVerticesCount =
        ((HeightMapChunkWidth+1)*(HeightMapChunkHeight+1)*8);
    const uint32_t HeightMapChunkIndicesCount =
        (6*HeightMapChunkWidth*HeightMapChunkHeight);


    ////////////////////////////////////////////////////////////////////////////
    //  HeightMapChunk class definition                                       //
    ////////////////////////////////////////////////////////////////////////////
    class HeightMapChunk : public Transform3
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  HeightMapChunk default constructor                            //
            ////////////////////////////////////////////////////////////////////
            HeightMapChunk();

            ////////////////////////////////////////////////////////////////////
            //  HeightMapChunk virtual destructor                             //
            ////////////////////////////////////////////////////////////////////
            virtual ~HeightMapChunk();


            ////////////////////////////////////////////////////////////////////
            //  Init heightmap chunk                                          //
            //  return : True if the heightmap chunk is successfully created  //
            ////////////////////////////////////////////////////////////////////
            bool init(VertexBuffer& vertexBuffer, TextureArray& textureArray);

            ////////////////////////////////////////////////////////////////////
            //  Set heightmap chunk vertex buffer                             //
            ////////////////////////////////////////////////////////////////////
            inline void setVertexBuffer(VertexBuffer& vertexBuffer)
            {
                m_vertexBuffer = &vertexBuffer;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set heightmap chunk texture array                             //
            //  return : True if heightmap chunk texture array is set         //
            ////////////////////////////////////////////////////////////////////
            bool setTextureArray(TextureArray& textureArray);

            ////////////////////////////////////////////////////////////////////
            //  Bind heightmap chunk vertex buffer                            //
            ////////////////////////////////////////////////////////////////////
            void bindVertexBuffer();

            ////////////////////////////////////////////////////////////////////
            //  Bind heightmap chunk texture array                            //
            ////////////////////////////////////////////////////////////////////
            inline void bindTextureArray()
            {
                m_textureArray->bind();
            }

            ////////////////////////////////////////////////////////////////////
            //  Render heightmap chunk                                        //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  HeightMapChunk private copy constructor : Not copyable        //
            ////////////////////////////////////////////////////////////////////
            HeightMapChunk(const HeightMapChunk&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  HeightMapChunk private copy operator : Not copyable           //
            ////////////////////////////////////////////////////////////////////
            HeightMapChunk& operator=(const HeightMapChunk&) = delete;


        private:
            VertexBuffer*   m_vertexBuffer;     // Heightmap chunk vertex buffer
            TextureArray*   m_textureArray;     // Heightmap chunk texture ptr
    };


#endif // VOS_RENDERER_HEIGHTMAP_HEIGHTMAPCHUNK_HEADER
