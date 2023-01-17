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
//     Renderer/HeightMapStream.h : HeightMap stream management               //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_HEIGHTMAPSTREAM_HEADER
#define VOS_RENDERER_HEIGHTMAPSTREAM_HEADER

    #include "../System/System.h"
    #include "Vulkan/VertexBuffer.h"
    #include "../Math/Math.h"
    #include "../Math/Vector3.h"
    #include "../Math/Matrix4x4.h"
    #include "../Math/Transform3.h"
    #include "../Resources/Resources.h"
    #include "../Resources/HeightMapLoader.h"
    #include "../Resources/TextureLoader.h"

    #include "HeightMapChunk.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class declaration                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer;


    ////////////////////////////////////////////////////////////////////////////
    //  HeightMapStream class definition                                      //
    ////////////////////////////////////////////////////////////////////////////
    class HeightMapStream
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  HeightMapStream default constructor                           //
            ////////////////////////////////////////////////////////////////////
            HeightMapStream();

            ////////////////////////////////////////////////////////////////////
            //  HeightMapStream destructor                                    //
            ////////////////////////////////////////////////////////////////////
            ~HeightMapStream();


            ////////////////////////////////////////////////////////////////////
            //  Init heightmap stream                                         //
            //  return : True if the heightmap stream is successfully created //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Reload heightmap stream                                       //
            //  return : True if the heightmap stream is reloading            //
            ////////////////////////////////////////////////////////////////////
            inline bool isReady()
            {
                return (GResources.heightmaps.getState() ==
                    HEIGHTMAPLOADER_STATE_IDLE);
            }

            ////////////////////////////////////////////////////////////////////
            //  Reload heightmap stream                                       //
            //  return : True if the heightmap stream is reloading            //
            ////////////////////////////////////////////////////////////////////
            inline bool reload(int32_t chunkX, int32_t chunkY)
            {
                if (GResources.heightmaps.reload(chunkX, chunkY))
                {
                    m_chunkX = GResources.heightmaps.getChunkX();
                    m_chunkY = GResources.heightmaps.getChunkY();
                    return true;
                }
                return false;
            }

            ////////////////////////////////////////////////////////////////////
            //  Update heightmap stream                                       //
            //  return : True if the heightmap stream is updated              //
            ////////////////////////////////////////////////////////////////////
            inline bool update(int32_t chunkX, int32_t chunkY)
            {
                if (GResources.heightmaps.update(chunkX, chunkY))
                {
                    m_chunkX = GResources.heightmaps.getChunkX();
                    m_chunkY = GResources.heightmaps.getChunkY();
                    return true;
                }
                return false;
            }

            ////////////////////////////////////////////////////////////////////
            //  Render heightmap stream                                       //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  HeightMapStream private copy constructor : Not copyable       //
            ////////////////////////////////////////////////////////////////////
            HeightMapStream(const HeightMapStream&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  HeightMapStream private copy operator : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            HeightMapStream& operator=(const HeightMapStream&) = delete;


        private:
            HeightMapChunk      m_heightMapChunk;   // HeightMap chunk
            int32_t             m_chunkX;           // Chunk X
            int32_t             m_chunkY;           // Chunk Y
    };


#endif // VOS_RENDERER_HEIGHTMAPSTREAM_HEADER
