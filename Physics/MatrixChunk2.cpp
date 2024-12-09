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
//     Physics/MatrixChunk2.cpp : 2D Matrix chunk physics management          //
////////////////////////////////////////////////////////////////////////////////
#include "MatrixChunk2.h"


////////////////////////////////////////////////////////////////////////////////
//  MatrixChunk2 default constructor                                          //
////////////////////////////////////////////////////////////////////////////////
MatrixChunk2::MatrixChunk2() :
m_matrix(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  MatrixChunk2 destructor                                                   //
////////////////////////////////////////////////////////////////////////////////
MatrixChunk2::~MatrixChunk2()
{
    if (m_matrix) { delete[] m_matrix; }
    m_matrix = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Init matrix chunk                                                         //
////////////////////////////////////////////////////////////////////////////////
bool MatrixChunk2::init()
{
    // Create matrix
    m_matrix = new(std::nothrow) int8_t[MatrixChunk2Size];
    if (!m_matrix) { return false; }
    for (int i = 0; i < MatrixChunk2Size; ++i)
    {
        m_matrix[i] = 0;
    }

    // Test elements
    m_matrix[(1*MatrixChunk2Width)+1] = 1;
    m_matrix[(1*MatrixChunk2Width)+5] = 1;
    m_matrix[(2*MatrixChunk2Width)+1] = 1;
    m_matrix[(2*MatrixChunk2Width)+5] = 1;
    m_matrix[(3*MatrixChunk2Width)+1] = 1;
    m_matrix[(3*MatrixChunk2Width)+5] = 1;
    m_matrix[(4*MatrixChunk2Width)+1] = 1;
    m_matrix[(4*MatrixChunk2Width)+5] = 1;
    m_matrix[(4*MatrixChunk2Width)+8] = 1;
    m_matrix[(5*MatrixChunk2Width)+1] = 1;
    m_matrix[(5*MatrixChunk2Width)+8] = 1;
    m_matrix[(6*MatrixChunk2Width)+1] = 1;
    m_matrix[(6*MatrixChunk2Width)+8] = 1;
    m_matrix[(7*MatrixChunk2Width)+1] = 1;
    m_matrix[(7*MatrixChunk2Width)+7] = 1;
    m_matrix[(7*MatrixChunk2Width)+8] = 1;
    m_matrix[(8*MatrixChunk2Width)+1] = 1;
    m_matrix[(8*MatrixChunk2Width)+2] = 1;
    m_matrix[(8*MatrixChunk2Width)+3] = 1;
    m_matrix[(8*MatrixChunk2Width)+4] = 1;
    m_matrix[(8*MatrixChunk2Width)+5] = 1;
    m_matrix[(8*MatrixChunk2Width)+6] = 1;
    m_matrix[(8*MatrixChunk2Width)+7] = 1;
    m_matrix[(8*MatrixChunk2Width)+8] = 1;
    m_matrix[(1*MatrixChunk2Width)+7] = 1;
    m_matrix[(2*MatrixChunk2Width)+7] = 1;
    m_matrix[(3*MatrixChunk2Width)+7] = 1;
    m_matrix[(1*MatrixChunk2Width)+8] = 1;
    m_matrix[(2*MatrixChunk2Width)+8] = 1;
    m_matrix[(3*MatrixChunk2Width)+8] = 1;
    m_matrix[(7*MatrixChunk2Width)+4] = 1;

    // Matrix chunk successfully created
    return true;
}
