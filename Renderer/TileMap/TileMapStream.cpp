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
//     Renderer/TileMap/TileMapStream.cpp : TileMap stream renderer           //
////////////////////////////////////////////////////////////////////////////////
#include "TileMapStream.h"


////////////////////////////////////////////////////////////////////////////////
//  TileMapStream default constructor                                         //
////////////////////////////////////////////////////////////////////////////////
TileMapStream::TileMapStream() :
m_chunkX(0),
m_chunkY(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  TileMapStream destructor                                                  //
////////////////////////////////////////////////////////////////////////////////
TileMapStream::~TileMapStream()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Init tilemap stream                                                       //
//  return : True if the tilemap stream is successfully created               //
////////////////////////////////////////////////////////////////////////////////
bool TileMapStream::init()
{
    // Tilemap stream successfully created
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Render tilemap stream                                                     //
////////////////////////////////////////////////////////////////////////////////
void TileMapStream::render(Sprite& sprite)
{
    // Synchronize tilemap stream with renderer
    GResources.tilemaps.sync();

    // Render tilemap chunks
    for (int i = 1; i < (TILEMAP_STREAMWIDTH-1); ++i)
    {
        for (int j = 1; j < (TILEMAP_STREAMHEIGHT-1); ++j)
        {
            GResources.tilemaps.tilemap(i, j).setPosition(
                -(TILEMAP_STREAMHALFWIDTH*TileMapChunkXStride)+
                (i*TileMapChunkXStride),
                -(TILEMAP_STREAMHALFHEIGHT*TileMapChunkYStride)+
                (j*TileMapChunkYStride)
            );
            GResources.tilemaps.tilemap(i, j).render(sprite);
        }
    }
}
