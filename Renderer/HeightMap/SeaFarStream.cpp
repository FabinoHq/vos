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
//     Renderer/HeightMap/SeaFarStream.cpp : SeaFar stream                    //
////////////////////////////////////////////////////////////////////////////////
#include "SeaFarStream.h"


////////////////////////////////////////////////////////////////////////////////
//  SeaFarStream default constructor                                          //
////////////////////////////////////////////////////////////////////////////////
SeaFarStream::SeaFarStream() :
m_seaFarChunk()
{

}

////////////////////////////////////////////////////////////////////////////////
//  SeaFarStream destructor                                                   //
////////////////////////////////////////////////////////////////////////////////
SeaFarStream::~SeaFarStream()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Init sea far stream                                                       //
//  return : True if the sea far stream is successfully created               //
////////////////////////////////////////////////////////////////////////////////
bool SeaFarStream::init()
{
    // Init sea far chunk
    if (!m_seaFarChunk.init())
    {
        // Could not init sea far chunk
        return false;
    }

    // Sea far stream successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Render sea far stream                                                     //
////////////////////////////////////////////////////////////////////////////////
void SeaFarStream::render(int32_t chunkX, int32_t chunkY)
{
    for (int i = 1; i < HEIGHTFAR_STREAMWIDTH-1; ++i)
    {
        for (int j = 1; j < HEIGHTFAR_STREAMHEIGHT-1; ++j)
        {
            if (GResources.heightfars.getFlags(i, j) &
                HEIGHTFAR_FLAGS_RENDERSEA)
            {
                m_seaFarChunk.setPosition(
                    -(HEIGHTFAR_STREAMHALFWIDTH*SeaFarChunkXStride)+
                    (chunkX*SeaFarChunkXStride)+(i*SeaFarChunkXStride),
                    0.0f,
                    -(HEIGHTFAR_STREAMHALFHEIGHT*SeaFarChunkZStride)+
                    (chunkY*SeaFarChunkXStride)+(j*SeaFarChunkZStride)
                );
                m_seaFarChunk.render();
            }
        }
    }
}
