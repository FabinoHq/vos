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
//     Renderer/IsoMap/IsoMapChunk.h : IsoMap chunk renderer                  //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_ISOMAP_ISOMAPCHUNK_HEADER
#define VOS_RENDERER_ISOMAP_ISOMAPCHUNK_HEADER

    #include "../../System/System.h"
    #include "../../System/SysMemory.h"
    #include "../Vulkan/Vulkan.h"
    #include "../Vulkan/Swapchain.h"
    #include "../Vulkan/GraphicsLayout.h"

    #include "../../Math/Math.h"

    #include "../../Physics/Physics.h"
    #include "../../Physics/MatrixChunk2.h"

    #include "../Sprite.h"

    #include <cstdint>
    #include <cstring>


    ////////////////////////////////////////////////////////////////////////////
    //  IsoMapChunk settings                                                  //
    ////////////////////////////////////////////////////////////////////////////
    const int32_t IsoMapChunkWidth = MatrixChunk2Width;
    const int32_t IsoMapChunkHeight = MatrixChunk2Height;
    const int32_t IsoMapChunkSize = (IsoMapChunkWidth*IsoMapChunkHeight);
    const float IsoMapElemHalfWidth =
        ((MatrixChunk2ElemHalfWidth*2)*PhysicsToRenderer);
    const float IsoMapElemHalfHeight =
        (MatrixChunk2ElemHalfHeight*PhysicsToRenderer);
    const float IsoMapElemWidth = ((MatrixChunk2ElemWidth*2)*PhysicsToRenderer);
    const float IsoMapElemHeight = (MatrixChunk2ElemHeight*PhysicsToRenderer);
    const float IsoMapChunkXStride = (IsoMapChunkWidth*IsoMapElemHalfWidth);
    const float IsoMapChunkYStride = (IsoMapChunkHeight*IsoMapElemHalfHeight);
    const float Iso3DMapElemWidth = (MatrixChunk2ElemWidth*PhysicsToRenderer);
    const float Iso3DMapElemHeight = (MatrixChunk2ElemHeight*PhysicsToRenderer);
    const float Iso3DMapElemDepth = (MatrixChunk2ElemDepth*PhysicsToRenderer);


    ////////////////////////////////////////////////////////////////////////////
    //  IsoMapChunk class definition                                          //
    ////////////////////////////////////////////////////////////////////////////
    class IsoMapChunk
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  IsoMapChunk default constructor                               //
            ////////////////////////////////////////////////////////////////////
            IsoMapChunk();

            ////////////////////////////////////////////////////////////////////
            //  IsoMapChunk destructor                                        //
            ////////////////////////////////////////////////////////////////////
            ~IsoMapChunk();


            ////////////////////////////////////////////////////////////////////
            //  Init isomap chunk                                             //
            //  return : True if the isomap chunk is successfully created     //
            ////////////////////////////////////////////////////////////////////
            bool init();


            ////////////////////////////////////////////////////////////////////
            //  Get isomap chunk element                                      //
            ////////////////////////////////////////////////////////////////////
            int32_t getElem(int32_t i, int32_t j);


        private:
            ////////////////////////////////////////////////////////////////////
            //  IsoMapChunk private copy constructor : Not copyable           //
            ////////////////////////////////////////////////////////////////////
            IsoMapChunk(const IsoMapChunk&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  IsoMapChunk private copy operator : Not copyable              //
            ////////////////////////////////////////////////////////////////////
            IsoMapChunk& operator=(const IsoMapChunk&) = delete;


        public:
            int32_t*    matrix;     // Isomap chunk representation
    };


#endif // VOS_RENDERER_ISOMAP_ISOMAPCHUNK_HEADER
