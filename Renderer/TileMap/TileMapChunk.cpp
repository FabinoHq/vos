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
//     Renderer/TileMap/TileMapChunk.cpp : TileMap chunk renderer             //
////////////////////////////////////////////////////////////////////////////////
#include "TileMapChunk.h"


////////////////////////////////////////////////////////////////////////////////
//  TileMapChunk default constructor                                          //
////////////////////////////////////////////////////////////////////////////////
TileMapChunk::TileMapChunk() :
Transform2(),
matrix(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  TileMapChunk virtual destructor                                           //
////////////////////////////////////////////////////////////////////////////////
TileMapChunk::~TileMapChunk()
{
    if (matrix) { delete[] matrix; }
    matrix = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Init tilemap chunk                                                        //
//  return : True if the tilemap chunk is successfully created                //
////////////////////////////////////////////////////////////////////////////////
bool TileMapChunk::init()
{
    // Reset tilemap chunk transformations
    resetTransforms();

    // Init matrix chunk
    matrix = new(std::nothrow) int32_t[TileMapChunkSize];
    if (!matrix) { return false; }
    memset(matrix, 0, sizeof(int32_t)*TileMapChunkSize);

    // Tilemap chunk successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy tilemap chunk                                                     //
////////////////////////////////////////////////////////////////////////////////
void TileMapChunk::destroyTileMap()
{
    if (matrix) { delete[] matrix; }
    matrix = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Render tilemap chunk                                                      //
////////////////////////////////////////////////////////////////////////////////
void TileMapChunk::render(Sprite& sprite)
{
    // Render tilemap chunk
    for (int i = 0; i < TileMapChunkWidth; ++i)
    {
        for (int j = 0; j < TileMapChunkHeight; ++j)
        {
            // Get current tilemap element
            if (matrix[(j*TileMapChunkWidth)+i] != 0)
            {
                // Render tilemap element
                sprite.setPosition(
                    (TileMapElemHalfWidth+m_position.vec[0])+
                    (i*TileMapElemWidth),
                    (TileMapElemHalfHeight+m_position.vec[1])+
                    (j*TileMapElemHeight)
                );
                sprite.bindTexture();
                sprite.render();
            }
        }
    }
}
