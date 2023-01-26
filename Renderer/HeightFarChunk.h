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
//     Renderer/HeightFarChunk.h : HeightFar chunk management                 //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_HEIGHTFARCHUNK_HEADER
#define VOS_RENDERER_HEIGHTFARCHUNK_HEADER

    #include "../System/System.h"
    #include "Vulkan/Vulkan.h"
    #include "Vulkan/Swapchain.h"
    #include "Vulkan/GraphicsLayout.h"
    #include "Vulkan/VertexBuffer.h"
    #include "Vulkan/TextureArray.h"
    #include "../Math/Math.h"
    #include "../Math/Vector3.h"
    #include "../Math/Matrix4x4.h"
    #include "../Math/Transform3.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  HeightFarChunk settings                                               //
    ////////////////////////////////////////////////////////////////////////////
    const uint16_t HeightFarChunkWidth = 128;
    const uint16_t HeightFarChunkHeight = 128;
    const float HeightFarChunkPlaneWidth = 64.0f;
    const float HeightFarChunkPlaneHeight = 64.0f;
    const float HeightFarChunkXStride = 8192.0f;
    const float HeightFarChunkZStride = 8192.0f;
    const float HeightFarChunkTexcoordsWidth = 64.0f;
    const float HeightFarChunkTexcoordsHeight = 64.0f;
    const uint32_t HeightFarChunkVerticesCount =
        ((HeightFarChunkWidth+1)*(HeightFarChunkHeight+1)*8);
    const uint32_t HeightFarChunkIndicesCount =
        (6*HeightFarChunkWidth*HeightFarChunkHeight);


    ////////////////////////////////////////////////////////////////////////////
    //  HeightFarChunk class definition                                       //
    ////////////////////////////////////////////////////////////////////////////
    class HeightFarChunk : public Transform3
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  HeightFarChunk default constructor                            //
            ////////////////////////////////////////////////////////////////////
            HeightFarChunk();

            ////////////////////////////////////////////////////////////////////
            //  HeightFarChunk virtual destructor                             //
            ////////////////////////////////////////////////////////////////////
            virtual ~HeightFarChunk();


            ////////////////////////////////////////////////////////////////////
            //  Init heightfar chunk                                          //
            //  return : True if the heightfar chunk is successfully created  //
            ////////////////////////////////////////////////////////////////////
            bool init(VertexBuffer& vertexBuffer, TextureArray& textureArray);

            ////////////////////////////////////////////////////////////////////
            //  Set heightfar chunk vertex buffer                             //
            ////////////////////////////////////////////////////////////////////
            inline void setVertexBuffer(VertexBuffer& vertexBuffer)
            {
                m_vertexBuffer = &vertexBuffer;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set heightfar chunk texture array                             //
            //  return : True if heightfar chunk texture array is set         //
            ////////////////////////////////////////////////////////////////////
            bool setTextureArray(TextureArray& textureArray);

            ////////////////////////////////////////////////////////////////////
            //  Bind heightfar chunk vertex buffer                            //
            ////////////////////////////////////////////////////////////////////
            void bindVertexBuffer();

            ////////////////////////////////////////////////////////////////////
            //  Bind heightfar chunk texture array                            //
            ////////////////////////////////////////////////////////////////////
            inline void bindTextureArray()
            {
                m_textureArray->bind();
            }

            ////////////////////////////////////////////////////////////////////
            //  Render heightfar chunk                                        //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  HeightFarChunk private copy constructor : Not copyable        //
            ////////////////////////////////////////////////////////////////////
            HeightFarChunk(const HeightFarChunk&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  HeightFarChunk private copy operator : Not copyable           //
            ////////////////////////////////////////////////////////////////////
            HeightFarChunk& operator=(const HeightFarChunk&) = delete;


        private:
            VertexBuffer*   m_vertexBuffer;     // Heightfar chunk vertex buffer
            TextureArray*   m_textureArray;     // Heightfar chunk texture ptr
    };


#endif // VOS_RENDERER_HEIGHTFARCHUNK_HEADER
