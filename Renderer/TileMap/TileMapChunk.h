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
//     Renderer/TileMap/TileMapChunk.h : TileMap chunk renderer               //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_TILEMAP_TILEMAPCHUNK_HEADER
#define VOS_RENDERER_TILEMAP_TILEMAPCHUNK_HEADER

    #include "../../System/System.h"
    #include "../Vulkan/Vulkan.h"
    #include "../Vulkan/Swapchain.h"
    #include "../Vulkan/GraphicsLayout.h"

    #include "../../Math/Math.h"
    #include "../../Math/Vector2.h"
    #include "../../Math/Matrix4x4.h"
    #include "../../Math/Transform2.h"

    #include "../../Physics/Physics.h"
    #include "../../Physics/MatrixChunk2.h"

    #include "../Sprite.h"

    #include <cstdint>
    #include <cstring>


    ////////////////////////////////////////////////////////////////////////////
    //  TileMapChunk settings                                                 //
    ////////////////////////////////////////////////////////////////////////////
    const int32_t TileMapChunkWidth = MatrixChunk2Width;
    const int32_t TileMapChunkHeight = MatrixChunk2Height;
    const int32_t TileMapChunkSize = (TileMapChunkWidth*TileMapChunkHeight);
    const float TileMapElemHalfWidth =
        (MatrixChunk2ElemHalfWidth*PhysicsToRenderer);
    const float TileMapElemHalfHeight =
        (MatrixChunk2ElemHalfHeight*PhysicsToRenderer);
    const float TileMapElemWidth = (MatrixChunk2ElemWidth*PhysicsToRenderer);
    const float TileMapElemHeight = (MatrixChunk2ElemHeight*PhysicsToRenderer);
    const float TileMapChunkXStride = (TileMapChunkWidth*TileMapElemWidth);
    const float TileMapChunkYStride = (TileMapChunkHeight*TileMapElemHeight);


    ////////////////////////////////////////////////////////////////////////////
    //  TileMapChunk class definition                                         //
    ////////////////////////////////////////////////////////////////////////////
    class TileMapChunk : public Transform2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  TileMapChunk default constructor                              //
            ////////////////////////////////////////////////////////////////////
            TileMapChunk();

            ////////////////////////////////////////////////////////////////////
            //  TileMapChunk virtual destructor                               //
            ////////////////////////////////////////////////////////////////////
            virtual ~TileMapChunk();


            ////////////////////////////////////////////////////////////////////
            //  Init tilemap chunk                                            //
            //  return : True if the tilemap chunk is successfully created    //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Destroy tilemap chunk                                         //
            ////////////////////////////////////////////////////////////////////
            void destroyTileMap();


            ////////////////////////////////////////////////////////////////////
            //  Render tilemap chunk                                          //
            ////////////////////////////////////////////////////////////////////
            void render(Sprite& sprite);


        private:
            ////////////////////////////////////////////////////////////////////
            //  TileMapChunk private copy constructor : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            TileMapChunk(const TileMapChunk&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  TileMapChunk private copy operator : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            TileMapChunk& operator=(const TileMapChunk&) = delete;


        public:
            int32_t*    matrix;     // Tilemap chunk representation
    };


#endif // VOS_RENDERER_TILEMAP_TILEMAPCHUNK_HEADER
