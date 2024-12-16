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
//     Renderer/TileMap/TileMapStream.h : TileMap stream renderer             //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_TILEMAP_TILEMAPSTREAM_HEADER
#define VOS_RENDERER_TILEMAP_TILEMAPSTREAM_HEADER

    #include "../../System/System.h"
    #include "../Vulkan/Vulkan.h"
    #include "../Vulkan/VertexBuffer.h"
    #include "../../Math/Math.h"
    #include "../../Math/Vector3.h"
    #include "../../Math/Matrix4x4.h"
    #include "../../Math/Transform3.h"
    #include "../../Resources/Resources.h"
    #include "../../Resources/TileMapLoader.h"

    #include "TileMapChunk.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  TileMapStream class definition                                        //
    ////////////////////////////////////////////////////////////////////////////
    class TileMapStream
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  TileMapStream default constructor                             //
            ////////////////////////////////////////////////////////////////////
            TileMapStream();

            ////////////////////////////////////////////////////////////////////
            //  TileMapStream destructor                                      //
            ////////////////////////////////////////////////////////////////////
            ~TileMapStream();


            ////////////////////////////////////////////////////////////////////
            //  Init tilemap stream                                           //
            //  return : True if the tilemap stream is successfully created   //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Get tilemap stream ready state                                //
            //  return : True if the tilemap stream is ready                  //
            ////////////////////////////////////////////////////////////////////
            inline bool isReady()
            {
                return (GResources.tilemaps.isReady());
            }

            ////////////////////////////////////////////////////////////////////
            //  Reload tilemap stream                                         //
            //  return : True if the tilemap stream is reloading              //
            ////////////////////////////////////////////////////////////////////
            inline bool reload(int32_t chunkX, int32_t chunkY)
            {
                if (GResources.tilemaps.reload(chunkX, chunkY))
                {
                    m_chunkX = GResources.tilemaps.getChunkX();
                    m_chunkY = GResources.tilemaps.getChunkY();
                    return true;
                }
                return false;
            }

            ////////////////////////////////////////////////////////////////////
            //  Update tilemap stream                                         //
            //  return : True if the tilemap stream is updated                //
            ////////////////////////////////////////////////////////////////////
            inline bool update(int32_t chunkX, int32_t chunkY)
            {
                if (GResources.tilemaps.update(chunkX, chunkY))
                {
                    m_chunkX = GResources.tilemaps.getChunkX();
                    m_chunkY = GResources.tilemaps.getChunkY();
                    return true;
                }
                return false;
            }

            ////////////////////////////////////////////////////////////////////
            //  Render tilemap stream                                         //
            ////////////////////////////////////////////////////////////////////
            void render();


            ////////////////////////////////////////////////////////////////////
            //  Get tilemap chunk X                                           //
            //  return : Tilemap chunk X                                      //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getChunkX() const
            {
                return m_chunkX;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get tilemap chunk Y                                           //
            //  return : Tilemap chunk Y                                      //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getChunkY() const
            {
                return m_chunkY;
            }


        private:
            ////////////////////////////////////////////////////////////////////
            //  TileMapStream private copy constructor : Not copyable         //
            ////////////////////////////////////////////////////////////////////
            TileMapStream(const TileMapStream&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  TileMapStream private copy operator : Not copyable            //
            ////////////////////////////////////////////////////////////////////
            TileMapStream& operator=(const TileMapStream&) = delete;


        private:
            TileMapChunk        m_tileMapChunk;     // TileMap chunk
            int32_t             m_chunkX;           // Chunk X
            int32_t             m_chunkY;           // Chunk Y
    };


#endif // VOS_RENDERER_TILEMAP_TILEMAPSTREAM_HEADER
