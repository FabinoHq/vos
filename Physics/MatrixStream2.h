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
//     Physics/MatrixStream2.h : 2D Matrix stream physics management          //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_PHYSICS_MATRIXSTREAM2_HEADER
#define VOS_PHYSICS_MATRIXSTREAM2_HEADER

    #include "../System/System.h"
    #include "../Math/Math.h"
    #include "../Resources/Resources.h"
    #include "../Resources/MatrixColLoader.h"

    #include "Physics.h"
    #include "MatrixChunk2.h"


    ////////////////////////////////////////////////////////////////////////////
    //  MatrixStream2 class definition                                        //
    ////////////////////////////////////////////////////////////////////////////
    class MatrixStream2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  MatrixStream2 default constructor                             //
            ////////////////////////////////////////////////////////////////////
            MatrixStream2();

            ////////////////////////////////////////////////////////////////////
            //  MatrixStream2 destructor                                      //
            ////////////////////////////////////////////////////////////////////
            ~MatrixStream2();


            ////////////////////////////////////////////////////////////////////
            //  Init matrix stream                                            //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Get matrix stream ready state                                 //
            //  return : True if the matrix stream is ready                   //
            ////////////////////////////////////////////////////////////////////
            inline bool isReady()
            {
                return (GResources.matrixcols.getState() ==
                    MATRIXCOLLOADER_STATE_IDLE);
            }

            ////////////////////////////////////////////////////////////////////
            //  Reload matrix stream                                          //
            //  return : True if the matrix stream is reloading               //
            ////////////////////////////////////////////////////////////////////
            inline bool reload(int32_t chunkX, int32_t chunkY)
            {
                if (GResources.matrixcols.reload(chunkX, chunkY))
                {
                    m_chunkX = GResources.matrixcols.getChunkX();
                    m_chunkY = GResources.matrixcols.getChunkY();
                    return true;
                }
                return false;
            }

            ////////////////////////////////////////////////////////////////////
            //  Update matrix stream                                          //
            //  return : True if the matrix stream is updated                 //
            ////////////////////////////////////////////////////////////////////
            inline bool update(int32_t chunkX, int32_t chunkY)
            {
                if (GResources.matrixcols.update(chunkX, chunkY))
                {
                    m_chunkX = GResources.matrixcols.getChunkX();
                    m_chunkY = GResources.matrixcols.getChunkY();
                    return true;
                }
                return false;
            }


            ////////////////////////////////////////////////////////////////////
            //  Get matrix element at given coordinates                       //
            ////////////////////////////////////////////////////////////////////
            inline int8_t get(int32_t x, int32_t y) const
            {
                int32_t chunkX = (
                    MATRIXCOL_STREAMHALFWIDTH +
                    Math::divide(x, MatrixChunk2Width)
                );
                int32_t chunkY = (
                    MATRIXCOL_STREAMHALFHEIGHT +
                    Math::divide(y, MatrixChunk2Height)
                );
                return (GResources.matrixcols.matrixcol(
                    (chunkY*MATRIXCOL_STREAMWIDTH)+chunkX).get(
                    Math::modulo(x, MatrixChunk2Width),
                    Math::modulo(y, MatrixChunk2Height))
                );
            }


            ////////////////////////////////////////////////////////////////////
            //  Get matrixcol chunk X                                         //
            //  return : matrixcol chunk X                                    //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getChunkX() const
            {
                return m_chunkX;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get matrixcol chunk Y                                         //
            //  return : matrixcol chunk Y                                    //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getChunkY() const
            {
                return m_chunkY;
            }


        private:
            ////////////////////////////////////////////////////////////////////
            //  MatrixStream2 private copy constructor : Not copyable         //
            ////////////////////////////////////////////////////////////////////
            MatrixStream2(const MatrixStream2&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  MatrixStream2 private copy operator : Not copyable            //
            ////////////////////////////////////////////////////////////////////
            MatrixStream2& operator=(const MatrixStream2&) = delete;


        private:
            int32_t             m_chunkX;           // Chunk X
            int32_t             m_chunkY;           // Chunk Y
    };


    ////////////////////////////////////////////////////////////////////////////
    //  MatrixStream2 global instance                                         //
    ////////////////////////////////////////////////////////////////////////////
    extern MatrixStream2 GMatrixStream2;


#endif // VOS_PHYSICS_MATRIXSTREAM2_HEADER
