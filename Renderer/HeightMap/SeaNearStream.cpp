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
//     Renderer/HeightMap/SeaNearStream.cpp : SeaNear stream                  //
////////////////////////////////////////////////////////////////////////////////
#include "SeaNearStream.h"


////////////////////////////////////////////////////////////////////////////////
//  SeaNearStream default constructor                                         //
////////////////////////////////////////////////////////////////////////////////
SeaNearStream::SeaNearStream() :
m_seaNearChunk()
{

}

////////////////////////////////////////////////////////////////////////////////
//  SeaNearStream destructor                                                  //
////////////////////////////////////////////////////////////////////////////////
SeaNearStream::~SeaNearStream()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Init sea near stream                                                      //
//  return : True if the sea near stream is successfully created              //
////////////////////////////////////////////////////////////////////////////////
bool SeaNearStream::init()
{
    // Init sea near chunk
    if (!m_seaNearChunk.init())
    {
        // Could not init sea near chunk
        return false;
    }

    // Sea near stream successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Render sea near stream                                                    //
////////////////////////////////////////////////////////////////////////////////
void SeaNearStream::render(int32_t chunkX, int32_t chunkY)
{
    for (int i = 1; i < HEIGHTMAP_STREAMWIDTH-1; ++i)
    {
        for (int j = 1; j < HEIGHTMAP_STREAMHEIGHT-1; ++j)
        {
            if (GResources.heightmaps.getFlags(i, j) & HEIGHTMAP_FLAGS_WATER)
            {
                m_seaNearChunk.setPosition(
                    -(HEIGHTMAP_STREAMHALFWIDTH*SeaNearChunkXStride)+
                    (chunkX*SeaNearChunkXStride)+(i*SeaNearChunkXStride),
                    0.0f,
                    -(HEIGHTMAP_STREAMHALFHEIGHT*SeaNearChunkZStride)+
                    (chunkY*SeaNearChunkXStride)+(j*SeaNearChunkZStride)
                );
                m_seaNearChunk.render();
            }
        }
    }
}
