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
//     Renderer/IsoMap/IsoMapChunk.cpp : IsoMap chunk renderer                //
////////////////////////////////////////////////////////////////////////////////
#include "IsoMapChunk.h"


////////////////////////////////////////////////////////////////////////////////
//  IsoMapChunk default constructor                                           //
////////////////////////////////////////////////////////////////////////////////
IsoMapChunk::IsoMapChunk() :
Transform2(),
matrix(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  IsoMapChunk virtual destructor                                            //
////////////////////////////////////////////////////////////////////////////////
IsoMapChunk::~IsoMapChunk()
{
    if (matrix) { delete[] matrix; }
    matrix = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Init isomap chunk                                                         //
//  return : True if the isomap chunk is successfully created                 //
////////////////////////////////////////////////////////////////////////////////
bool IsoMapChunk::init()
{
    // Reset isomap chunk transformations
    resetTransforms();

    // Init matrix chunk
    matrix = new(std::nothrow) int32_t[IsoMapChunkSize];
    if (!matrix) { return false; }
    memset(matrix, 0, sizeof(int32_t)*IsoMapChunkSize);

    // Isomap chunk successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy isomap chunk                                                      //
////////////////////////////////////////////////////////////////////////////////
void IsoMapChunk::destroyIsoMap()
{
    if (matrix) { delete[] matrix; }
    matrix = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Render isomap chunk                                                       //
////////////////////////////////////////////////////////////////////////////////
void IsoMapChunk::render(Sprite& sprite)
{
    // Render isomap chunk
    for (int i = 0; i < IsoMapChunkWidth; ++i)
    {
        for (int j = 0; j < IsoMapChunkHeight; ++j)
        {
            // Get current isomap element
            if (matrix[(j*IsoMapChunkWidth)+i] != 0)
            {
                // Render isomap element
                sprite.setPosition(
                    (IsoMapElemHalfWidth+m_position.vec[0])+
                    (i*IsoMapElemHalfWidth)+(j*IsoMapElemHalfWidth),
                    m_position.vec[1]+
                    (j*IsoMapElemHalfHeight)-(i*IsoMapElemHalfHeight)
                );
                sprite.bindTexture();
                sprite.render();
            }
        }
    }
}
