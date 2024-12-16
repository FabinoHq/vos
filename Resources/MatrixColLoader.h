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
//     Resources/MatrixColLoader.h : MatrixCol loading management             //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RESOURCES_MATRIXCOLLOADER_HEADER
#define VOS_RESOURCES_MATRIXCOLLOADER_HEADER

    #include "../System/System.h"
    #include "../System/SysThread.h"
    #include "../System/SysMutex.h"

    #include "../Math/Math.h"
    #include "../Physics/Physics.h"
    #include "../Physics/MatrixChunk2.h"

    #include <string>
    #include <sstream>
    #include <fstream>
    #include <cstdint>
    #include <cstring>
    #include <new>


    ////////////////////////////////////////////////////////////////////////////
    //  MatrixColLoader settings                                              //
    ////////////////////////////////////////////////////////////////////////////
    const uint32_t MatrixColLoaderSyncTicks = 200;
    const double MatrixColLoaderIdleSleepTime = 0.01;
    const double MatrixColLoaderErrorSleepTime = 0.1;
    const char MatrixColLoaderVMCCFilePath[] = "World/vmcc/";


    ////////////////////////////////////////////////////////////////////////////
    //  MatrixCol stream assets definitions                                   //
    ////////////////////////////////////////////////////////////////////////////
    #define MATRIXCOL_STREAMWIDTH 7
    #define MATRIXCOL_STREAMHEIGHT 7
    #define MATRIXCOL_STREAMHALFWIDTH 3
    #define MATRIXCOL_STREAMHALFHEIGHT 3
    #define MATRIXCOL_ASSETSCOUNT (MATRIXCOL_STREAMWIDTH*MATRIXCOL_STREAMHEIGHT)


    ////////////////////////////////////////////////////////////////////////////
    //  MatrixColLoaderState enumeration                                      //
    ////////////////////////////////////////////////////////////////////////////
    enum MatrixColLoaderState
    {
        MATRIXCOLLOADER_STATE_NONE = 0,
        MATRIXCOLLOADER_STATE_INIT = 1,

        MATRIXCOLLOADER_STATE_IDLE = 2,
        MATRIXCOLLOADER_STATE_LOAD = 3,

        MATRIXCOLLOADER_STATE_ERROR = 4
    };


    ////////////////////////////////////////////////////////////////////////////
    //  MatrixColChunkData structure                                          //
    ////////////////////////////////////////////////////////////////////////////
    struct MatrixColChunkData
    {
        bool loading;
        int32_t chunkX;
        int32_t chunkY;
        MatrixChunk2* chunk;
    };


    ////////////////////////////////////////////////////////////////////////////
    //  MatrixColLoader class definition                                      //
    ////////////////////////////////////////////////////////////////////////////
    class MatrixColLoader : public SysThread
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  MatrixColLoader default constructor                           //
            ////////////////////////////////////////////////////////////////////
            MatrixColLoader();

            ////////////////////////////////////////////////////////////////////
            //  MatrixColLoader virtual destructor                            //
            ////////////////////////////////////////////////////////////////////
            virtual ~MatrixColLoader();


            ////////////////////////////////////////////////////////////////////
            //  MatrixColLoader thread process                                //
            ////////////////////////////////////////////////////////////////////
            virtual void process();


            ////////////////////////////////////////////////////////////////////
            //  Init MatrixColLoader                                          //
            //  return : True if matrixcol loader is ready                    //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Get matrixcol loader state                                    //
            //  return : Current matrixcol loader state                       //
            ////////////////////////////////////////////////////////////////////
            MatrixColLoaderState getState();

            ////////////////////////////////////////////////////////////////////
            //  Get matrixcol loader ready state                              //
            //  return : True if matrixcol loader is ready, false otherwise   //
            ////////////////////////////////////////////////////////////////////
            bool isReady();

            ////////////////////////////////////////////////////////////////////
            //  Reload matrixcols pointers based on current chunk position    //
            //  return : True if matrixcols pointers are reloaded             //
            ////////////////////////////////////////////////////////////////////
            bool reload(int32_t chunkX, int32_t chunkY);

            ////////////////////////////////////////////////////////////////////
            //  Update matrixcols pointers based on current chunk position    //
            //  return : True if matrixcols pointers are updated              //
            ////////////////////////////////////////////////////////////////////
            bool update(int32_t chunkX, int32_t chunkY);

            ////////////////////////////////////////////////////////////////////
            //  Get matrixcol chunk                                           //
            //  return : matrixcol chunk                                      //
            ////////////////////////////////////////////////////////////////////
            inline MatrixChunk2& matrixcol(int32_t chunkX, int32_t chunkY)
            {
                return (*m_chunksptrs[Math::clamp(static_cast<uint32_t>(
                    (chunkY*MATRIXCOL_STREAMWIDTH)+chunkX),
                    0u, (MATRIXCOL_ASSETSCOUNT-1u))]->chunk);
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

            ////////////////////////////////////////////////////////////////////
            //  Destroy matrixcol loader                                      //
            ////////////////////////////////////////////////////////////////////
            void destroyMatrixColLoader();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Load matrixcols assets                                        //
            //  return : True if matrixcols assets are loaded                 //
            ////////////////////////////////////////////////////////////////////
            bool loadMatrixCols();


            ////////////////////////////////////////////////////////////////////
            //  Generate flat matrixcol chunk                                 //
            //  return : True if the matrixcol chunk is generated             //
            ////////////////////////////////////////////////////////////////////
            bool generateFlatChunk(MatrixColChunkData& chunkData);

            ////////////////////////////////////////////////////////////////////
            //  Update flat matrixcol chunk                                   //
            //  return : True if the matrixcol chunk is updated               //
            ////////////////////////////////////////////////////////////////////
            bool updateFlatChunk(MatrixColChunkData& chunkData);

            ////////////////////////////////////////////////////////////////////
            //  Update matrixcol chunk                                        //
            //  return : True if the matrixcol chunk is updated               //
            ////////////////////////////////////////////////////////////////////
            bool updateChunk(MatrixColChunkData& chunkData,
                int32_t chunkX, int32_t chunkY);

            ////////////////////////////////////////////////////////////////////
            //  Swap matrixcols pointers towards top                          //
            //  return : True if matrixcols pointers are swapped              //
            ////////////////////////////////////////////////////////////////////
            bool swapTop();

            ////////////////////////////////////////////////////////////////////
            //  Swap matrixcols pointers towards bottom                       //
            //  return : True if matrixcols pointers are swapped              //
            ////////////////////////////////////////////////////////////////////
            bool swapBottom();

            ////////////////////////////////////////////////////////////////////
            //  Swap matrixcols pointers towards left                         //
            //  return : True if matrixcols pointers are swapped              //
            ////////////////////////////////////////////////////////////////////
            bool swapLeft();

            ////////////////////////////////////////////////////////////////////
            //  Swap matrixcols pointers towards right                        //
            //  return : True if matrixcols pointers are swapped              //
            ////////////////////////////////////////////////////////////////////
            bool swapRight();


        private:
            ////////////////////////////////////////////////////////////////////
            //  MatrixColLoader private copy constructor : Not copyable       //
            ////////////////////////////////////////////////////////////////////
            MatrixColLoader(const MatrixColLoader&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  MatrixColLoader private copy operator : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            MatrixColLoader& operator=(const MatrixColLoader&) = delete;


        private:
            MatrixColLoaderState    m_state;            // MatrixColLoader state
            SysMutex                m_stateMutex;       // State mutex

            MatrixChunk2*           m_matrixcols;       // Matrixcols chunks
            MatrixColChunkData      m_chunks[MATRIXCOL_ASSETSCOUNT];
            MatrixColChunkData*     m_chunksptrs[MATRIXCOL_ASSETSCOUNT];

            int32_t                 m_chunkX;           // Matrix chunk X
            int32_t                 m_chunkY;           // Matrix chunk Y
    };


#endif // VOS_RESOURCES_MATRIXCOLLOADER_HEADER
