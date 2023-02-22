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
//     Renderer/SeaFarChunk.h : Sea far chunk management                      //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_SEAFARCHUNK_HEADER
#define VOS_RENDERER_SEAFARCHUNK_HEADER

    #include "../System/System.h"
    #include "Vulkan/Vulkan.h"
    #include "Vulkan/Swapchain.h"
    #include "Vulkan/GraphicsLayout.h"
    #include "Vulkan/VertexBuffer.h"
    #include "../Math/Math.h"
    #include "../Math/Vector3.h"
    #include "../Math/Matrix4x4.h"
    #include "../Math/Transform3.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  SeaFarChunk settings                                                  //
    ////////////////////////////////////////////////////////////////////////////
    const uint16_t SeaFarChunkWidth = 64;
    const uint16_t SeaFarChunkHeight = 64;
    const float SeaFarChunkPlaneWidth = 128.0f;
    const float SeaFarChunkPlaneHeight = 128.0f;
    const float SeaFarChunkXStride = 8192.0f;
    const float SeaFarChunkZStride = 8192.0f;
    const float SeaFarChunkTexcoordsWidth = 128.0f;
    const float SeaFarChunkTexcoordsHeight = 128.0f;
    const uint32_t SeaFarChunkVerticesCount =
        ((SeaFarChunkWidth+1)*(SeaFarChunkHeight+1)*8);
    const uint32_t SeaFarChunkIndicesCount =
        (6*SeaFarChunkWidth*SeaFarChunkHeight);


    ////////////////////////////////////////////////////////////////////////////
    //  SeaFarChunk class definition                                          //
    ////////////////////////////////////////////////////////////////////////////
    class SeaFarChunk : public Transform3
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  SeaFarChunk default constructor                               //
            ////////////////////////////////////////////////////////////////////
            SeaFarChunk();

            ////////////////////////////////////////////////////////////////////
            //  SeaFarChunk virtual destructor                                //
            ////////////////////////////////////////////////////////////////////
            virtual ~SeaFarChunk();


            ////////////////////////////////////////////////////////////////////
            //  Init sea far chunk                                            //
            //  return : True if the sea far chunk is successfully created    //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Render sea far chunk                                          //
            ////////////////////////////////////////////////////////////////////
            void render();


        public:
            ////////////////////////////////////////////////////////////////////
            //  Generate sea far chunk                                        //
            //  return : True if the sea far chunk is generated               //
            ////////////////////////////////////////////////////////////////////
            static bool generateSeaFarChunk(VertexBuffer& vertexBuffer);


        private:
            ////////////////////////////////////////////////////////////////////
            //  SeaFarChunk private copy constructor : Not copyable           //
            ////////////////////////////////////////////////////////////////////
            SeaFarChunk(const SeaFarChunk&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  SeaFarChunk private copy operator : Not copyable              //
            ////////////////////////////////////////////////////////////////////
            SeaFarChunk& operator=(const SeaFarChunk&) = delete;


        private:
    };


#endif // VOS_RENDERER_SEAFARCHUNK_HEADER
