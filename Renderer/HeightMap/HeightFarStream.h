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
//     Renderer/HeightMap/HeightFarStream.h : HeightFar stream renderer       //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_HEIGHTMAP_HEIGHTFARSTREAM_HEADER
#define VOS_RENDERER_HEIGHTMAP_HEIGHTFARSTREAM_HEADER

    #include "../../System/System.h"
    #include "../Vulkan/Vulkan.h"
    #include "../Vulkan/VertexBuffer.h"

    #include "../../Math/Math.h"
    #include "../../Math/Vector3.h"
    #include "../../Math/Matrix4x4.h"
    #include "../../Math/Transform3.h"

    #include "../../Resources/Resources.h"
    #include "../../Resources/HeightFarLoader.h"
    #include "../../Resources/TextureLoader.h"

    #include "HeightFarChunk.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  HeightFarStream class definition                                      //
    ////////////////////////////////////////////////////////////////////////////
    class HeightFarStream
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  HeightFarStream default constructor                           //
            ////////////////////////////////////////////////////////////////////
            HeightFarStream();

            ////////////////////////////////////////////////////////////////////
            //  HeightFarStream destructor                                    //
            ////////////////////////////////////////////////////////////////////
            ~HeightFarStream();


            ////////////////////////////////////////////////////////////////////
            //  Init heightfar stream                                         //
            //  return : True if the heightfar stream is successfully created //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Reload heightfar stream                                       //
            //  return : True if the heightfar stream is reloading            //
            ////////////////////////////////////////////////////////////////////
            inline bool isReady()
            {
                return (GResources.heightfars.isReady());
            }

            ////////////////////////////////////////////////////////////////////
            //  Reload heightfar stream                                       //
            //  return : True if the heightfar stream is reloading            //
            ////////////////////////////////////////////////////////////////////
            inline bool reload(int32_t chunkX, int32_t chunkY)
            {
                if (GResources.heightfars.reload(chunkX, chunkY))
                {
                    m_chunkX = GResources.heightfars.getChunkX();
                    m_chunkY = GResources.heightfars.getChunkY();
                    return true;
                }
                return false;
            }

            ////////////////////////////////////////////////////////////////////
            //  Update heightfar stream                                       //
            //  return : True if the heightfar stream is updated              //
            ////////////////////////////////////////////////////////////////////
            inline bool update(int32_t chunkX, int32_t chunkY)
            {
                if (GResources.heightfars.update(chunkX, chunkY))
                {
                    m_chunkX = GResources.heightfars.getChunkX();
                    m_chunkY = GResources.heightfars.getChunkY();
                    return true;
                }
                return false;
            }

            ////////////////////////////////////////////////////////////////////
            //  Render heightfar stream                                       //
            ////////////////////////////////////////////////////////////////////
            void render();


            ////////////////////////////////////////////////////////////////////
            //  Get heightfar chunk X                                         //
            //  return : Heightfar chunk X                                    //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getChunkX() const
            {
                return m_chunkX;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get heightfar chunk Y                                         //
            //  return : Heightfar chunk Y                                    //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getChunkY() const
            {
                return m_chunkY;
            }


        private:
            ////////////////////////////////////////////////////////////////////
            //  HeightFarStream private copy constructor : Not copyable       //
            ////////////////////////////////////////////////////////////////////
            HeightFarStream(const HeightFarStream&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  HeightFarStream private copy operator : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            HeightFarStream& operator=(const HeightFarStream&) = delete;


        private:
            HeightFarChunk      m_heightFarChunk;   // HeightFar chunk
            int32_t             m_chunkX;           // Chunk X
            int32_t             m_chunkY;           // Chunk Y
    };


#endif // VOS_RENDERER_HEIGHTMAP_HEIGHTFARSTREAM_HEADER
