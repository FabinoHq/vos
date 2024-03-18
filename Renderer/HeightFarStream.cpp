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
//     Renderer/HeightFarStream.cpp : HeightFar stream renderer management    //
////////////////////////////////////////////////////////////////////////////////
#include "HeightFarStream.h"


////////////////////////////////////////////////////////////////////////////////
//  HeightFarStream default constructor                                       //
////////////////////////////////////////////////////////////////////////////////
HeightFarStream::HeightFarStream() :
m_heightFarChunk(),
m_chunkX(0),
m_chunkY(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  HeightFarStream destructor                                                //
////////////////////////////////////////////////////////////////////////////////
HeightFarStream::~HeightFarStream()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Init heightfar stream                                                     //
//  return : True if the heightfar stream is successfully created             //
////////////////////////////////////////////////////////////////////////////////
bool HeightFarStream::init()
{
    // Init heightfar chunk
    if (!m_heightFarChunk.init(
        GResources.heightfars.heightfar(0),
        GResources.textures.array(TEXTURE_ARRAY1)))
    {
        // Could not init heightfar chunk
        return false;
    }

    // Heightfar stream successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Render heightfar stream                                                   //
////////////////////////////////////////////////////////////////////////////////
void HeightFarStream::render()
{
    // Synchronize heightfar stream with renderer
    GResources.heightfars.sync();

    // Render heightfar chunks
    m_heightFarChunk.bindTextureArray();
    for (int i = 1; i < HEIGHTFAR_STREAMWIDTH-1; ++i)
    {
        for (int j = 1; j < HEIGHTFAR_STREAMHEIGHT-1; ++j)
        {
            m_heightFarChunk.setVertexBuffer(
                GResources.heightfars.heightfar((j*HEIGHTFAR_STREAMWIDTH)+i)
            );
            m_heightFarChunk.setPosition(
                -(HEIGHTFAR_STREAMHALFWIDTH*HeightFarChunkXStride)+
                (m_chunkX*HeightFarChunkXStride)+(i*HeightFarChunkXStride),
                0.0f,
                -(HEIGHTFAR_STREAMHALFHEIGHT*HeightFarChunkZStride)+
                (m_chunkY*HeightFarChunkXStride)+(j*HeightFarChunkZStride)
            );
            m_heightFarChunk.bindVertexBuffer();
            m_heightFarChunk.render();
        }
    }
}
