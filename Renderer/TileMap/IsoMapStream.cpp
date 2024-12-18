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
//     Renderer/IsoMap/IsoMapStream.cpp : IsoMap stream renderer              //
////////////////////////////////////////////////////////////////////////////////
#include "IsoMapStream.h"


////////////////////////////////////////////////////////////////////////////////
//  IsoMapStream default constructor                                          //
////////////////////////////////////////////////////////////////////////////////
IsoMapStream::IsoMapStream() :
m_chunkX(0),
m_chunkY(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  IsoMapStream destructor                                                   //
////////////////////////////////////////////////////////////////////////////////
IsoMapStream::~IsoMapStream()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Init isomap stream                                                        //
//  return : True if the isomap stream is successfully created                //
////////////////////////////////////////////////////////////////////////////////
bool IsoMapStream::init()
{
    // Isomap stream successfully created
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Render isomap stream                                                      //
////////////////////////////////////////////////////////////////////////////////
void IsoMapStream::render(Sprite& sprite)
{
    // Synchronize isomap stream with renderer
    GResources.isomaps.sync();

    // Render isomap chunks
    for (int i = 1; i < (ISOMAP_STREAMWIDTH-1); ++i)
    {
        for (int j = (ISOMAP_STREAMHEIGHT-2); j > 0; --j)
        {
            if (GResources.isomaps.getFlags(i, j) != ISOMAP_FLAGS_EMPTY)
            {
                IsoMapChunk& isomap = GResources.isomaps.isomap(i, j);
                isomap.setPosition(
                    -(TILEMAP_STREAMHALFWIDTH*(TileMapChunkXStride*2.0f))+
                    (i*IsoMapChunkXStride)+(j*IsoMapChunkXStride),
                    (j*IsoMapChunkYStride)-(i*IsoMapChunkYStride)
                );
                isomap.render(sprite);
            }
        }
    }
}
