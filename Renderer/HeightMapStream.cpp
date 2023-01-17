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
//     Renderer/HeightMapStream.cpp : HeightMap stream management             //
////////////////////////////////////////////////////////////////////////////////
#include "HeightMapStream.h"
#include "Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  HeightMapStream default constructor                                       //
////////////////////////////////////////////////////////////////////////////////
HeightMapStream::HeightMapStream() :
m_heightMapChunk(),
m_chunkX(0),
m_chunkY(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  HeightMapStream destructor                                                //
////////////////////////////////////////////////////////////////////////////////
HeightMapStream::~HeightMapStream()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Init heightmap stream                                                     //
//  return : True if the heightmap stream is successfully created             //
////////////////////////////////////////////////////////////////////////////////
bool HeightMapStream::init()
{
    // Init heightmap chunk
    if (!m_heightMapChunk.init(
        GResources.heightmaps.heightmap(0),
        GResources.textures.array(TEXTURE_ARRAY1)))
    {
        // Could not init heightmap chunk
        return false;
    }

    // Heightmap stream successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Render heightmap stream                                                   //
////////////////////////////////////////////////////////////////////////////////
void HeightMapStream::render()
{
    // Render heightmap chunks
    m_heightMapChunk.bindTextureArray();
    for (int i = 1; i < HEIGHTMAP_STREAMWIDTH-1; ++i)
    {
        for (int j = 1; j < HEIGHTMAP_STREAMHEIGHT-1; ++j)
        {
            m_heightMapChunk.setVertexBuffer(
                GResources.heightmaps.heightmap((j*HEIGHTMAP_STREAMWIDTH)+i)
            );
            m_heightMapChunk.setPosition(
                -(HEIGHTMAP_STREAMHALFWIDTH*HeightMapChunkXStride)+
                (m_chunkX*HeightMapChunkXStride)+(i*HeightMapChunkXStride),
                0.0f,
                -(HEIGHTMAP_STREAMHALFHEIGHT*HeightMapChunkZStride)+
                (m_chunkY*HeightMapChunkXStride)+(j*HeightMapChunkZStride)
            );
            m_heightMapChunk.bindVertexBuffer();
            m_heightMapChunk.render();
        }
    }
}
