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
//     Physics/MatrixChunk2.h : 2D Matrix chunk physics management            //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_PHYSICS_MATRIXCHUNK2_HEADER
#define VOS_PHYSICS_MATRIXCHUNK2_HEADER

    #include "../System/System.h"
    #include "../Math/Math.h"
    #include "Physics.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  MatrixChunk2 settings                                                 //
    ////////////////////////////////////////////////////////////////////////////
    const int32_t MatrixChunk2Width = 20;
    const int32_t MatrixChunk2Height = 20;
    const int32_t MatrixChunk2Size = (MatrixChunk2Width*MatrixChunk2Height);
    const int32_t MatrixChunk2ElemHalfWidth = 50000;
    const int32_t MatrixChunk2ElemHalfHeight = 50000;
    const int32_t MatrixChunk2ElemWidth = (MatrixChunk2ElemHalfWidth*2);
    const int32_t MatrixChunk2ElemHeight = (MatrixChunk2ElemHalfHeight*2);


    ////////////////////////////////////////////////////////////////////////////
    //  MatrixChunk2 class definition                                         //
    ////////////////////////////////////////////////////////////////////////////
    class MatrixChunk2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  MatrixChunk2 default constructor                              //
            ////////////////////////////////////////////////////////////////////
            MatrixChunk2();

            ////////////////////////////////////////////////////////////////////
            //  MatrixChunk2 destructor                                       //
            ////////////////////////////////////////////////////////////////////
            ~MatrixChunk2();


            ////////////////////////////////////////////////////////////////////
            //  Init matrix chunk                                             //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Destroy matrix chunk                                          //
            ////////////////////////////////////////////////////////////////////
            void destroyMatrix();


            ////////////////////////////////////////////////////////////////////
            //  Get matrix element at given coordinates                       //
            ////////////////////////////////////////////////////////////////////
            inline int8_t get(int32_t x, int32_t y) const
            {
                return matrix[
                    (Math::clamp(y, 0, (MatrixChunk2Height-1))*
                    MatrixChunk2Width)+Math::clamp(x, 0, (MatrixChunk2Width-1))
                ];
            }


        private:
            ////////////////////////////////////////////////////////////////////
            //  MatrixChunk2 private copy constructor : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            MatrixChunk2(const MatrixChunk2&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  MatrixChunk2 private copy operator : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            MatrixChunk2& operator=(const MatrixChunk2&) = delete;


        public:
            int8_t*     matrix;     // Matrix chunk representation
    };


#endif // VOS_PHYSICS_MATRIXCHUNK2_HEADER
