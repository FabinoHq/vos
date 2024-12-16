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
//     Renderer/HeightMap/SeaNearChunk.h : Sea near chunk                     //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_HEIGHTMAP_SEANEARCHUNK_HEADER
#define VOS_RENDERER_HEIGHTMAP_SEANEARCHUNK_HEADER

    #include "../../System/System.h"
    #include "../Vulkan/Vulkan.h"
    #include "../Vulkan/Swapchain.h"
    #include "../Vulkan/GraphicsLayout.h"
    #include "../Vulkan/VertexBuffer.h"

    #include "../../Math/Math.h"
    #include "../../Math/Vector3.h"
    #include "../../Math/Matrix4x4.h"
    #include "../../Math/Transform3.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  SeaNearChunk settings                                                 //
    ////////////////////////////////////////////////////////////////////////////
    const uint16_t SeaNearChunkWidth = 64;
    const uint16_t SeaNearChunkHeight = 64;
    const float SeaNearChunkPlaneWidth = 8.0f;
    const float SeaNearChunkPlaneHeight = 8.0f;
    const float SeaNearChunkXStride = 512.0f;
    const float SeaNearChunkZStride = 512.0f;
    const float SeaNearChunkTexcoordsWidth = 128.0f;
    const float SeaNearChunkTexcoordsHeight = 128.0f;
    const uint32_t SeaNearChunkVerticesCount =
        ((SeaNearChunkWidth+1)*(SeaNearChunkHeight+1)*8);
    const uint32_t SeaNearChunkIndicesCount =
        (6*SeaNearChunkWidth*SeaNearChunkHeight);


    ////////////////////////////////////////////////////////////////////////////
    //  SeaNearChunk class definition                                         //
    ////////////////////////////////////////////////////////////////////////////
    class SeaNearChunk : public Transform3
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  SeaNearChunk default constructor                              //
            ////////////////////////////////////////////////////////////////////
            SeaNearChunk();

            ////////////////////////////////////////////////////////////////////
            //  SeaNearChunk virtual destructor                               //
            ////////////////////////////////////////////////////////////////////
            virtual ~SeaNearChunk();


            ////////////////////////////////////////////////////////////////////
            //  Init sea near chunk                                           //
            //  return : True if the sea near chunk is successfully created   //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Render sea near chunk                                         //
            ////////////////////////////////////////////////////////////////////
            void render();


        public:
            ////////////////////////////////////////////////////////////////////
            //  Generate sea near chunk                                       //
            //  return : True if the sea near chunk is generated              //
            ////////////////////////////////////////////////////////////////////
            static bool generateSeaNearChunk(VertexBuffer& vertexBuffer);


        private:
            ////////////////////////////////////////////////////////////////////
            //  SeaNearChunk private copy constructor : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            SeaNearChunk(const SeaNearChunk&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  SeaNearChunk private copy operator : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            SeaNearChunk& operator=(const SeaNearChunk&) = delete;


        private:
    };


#endif // VOS_RENDERER_HEIGHTMAP_SEANEARCHUNK_HEADER
