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
//     Renderer/IsoMap/IsoMapStream.h : IsoMap stream renderer                //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_ISOMAP_ISOMAPSTREAM_HEADER
#define VOS_RENDERER_ISOMAP_ISOMAPSTREAM_HEADER

    #include "../../System/System.h"
    #include "../Vulkan/Vulkan.h"
    #include "../Vulkan/VertexBuffer.h"

    #include "../../Math/Math.h"

    #include "../../Resources/Resources.h"
    #include "../../Resources/IsoMapLoader.h"

    #include "../Sprite.h"
    #include "IsoMapChunk.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  IsoMapStream settings                                                 //
    ////////////////////////////////////////////////////////////////////////////
    const int32_t IsoMapStreamElemHalfWidth = 24;
    const int32_t IsoMapStreamElemHalfHeight = 24;
    const int32_t Iso3DMapStreamElemHalfWidth = 28;
    const int32_t Iso3DMapStreamElemHalfHeight = 28;


    ////////////////////////////////////////////////////////////////////////////
    //  IsoMapStream class definition                                         //
    ////////////////////////////////////////////////////////////////////////////
    class IsoMapStream
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  IsoMapStream default constructor                              //
            ////////////////////////////////////////////////////////////////////
            IsoMapStream();

            ////////////////////////////////////////////////////////////////////
            //  IsoMapStream destructor                                       //
            ////////////////////////////////////////////////////////////////////
            ~IsoMapStream();


            ////////////////////////////////////////////////////////////////////
            //  Init isomap stream                                            //
            //  return : True if the isomap stream is successfully created    //
            ////////////////////////////////////////////////////////////////////
            bool init();


            ////////////////////////////////////////////////////////////////////
            //  Get isomap stream ready state                                 //
            //  return : True if the isomap stream is ready                   //
            ////////////////////////////////////////////////////////////////////
            inline bool isReady()
            {
                return (GResources.isomaps.isReady());
            }

            ////////////////////////////////////////////////////////////////////
            //  Reload isomap stream                                          //
            //  return : True if the isomap stream is reloading               //
            ////////////////////////////////////////////////////////////////////
            inline bool reload(int32_t chunkX, int32_t chunkY)
            {
                if (GResources.isomaps.reload(chunkX, chunkY))
                {
                    m_chunkX = GResources.isomaps.getChunkX();
                    m_chunkY = GResources.isomaps.getChunkY();
                    return true;
                }
                return false;
            }

            ////////////////////////////////////////////////////////////////////
            //  Update isomap stream                                          //
            //  return : True if the isomap stream is updated                 //
            ////////////////////////////////////////////////////////////////////
            inline bool update(int32_t chunkX, int32_t chunkY)
            {
                if (GResources.isomaps.update(chunkX, chunkY))
                {
                    m_chunkX = GResources.isomaps.getChunkX();
                    m_chunkY = GResources.isomaps.getChunkY();
                    return true;
                }
                return false;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get isomap stream element                                     //
            ////////////////////////////////////////////////////////////////////
            int32_t getElem(int32_t i, int32_t j);


            ////////////////////////////////////////////////////////////////////
            //  Get isomap chunk X                                            //
            //  return : Isomap chunk X                                       //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getChunkX() const
            {
                return m_chunkX;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get isomap chunk Y                                            //
            //  return : Isomap chunk Y                                       //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getChunkY() const
            {
                return m_chunkY;
            }


        private:
            ////////////////////////////////////////////////////////////////////
            //  IsoMapStream private copy constructor : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            IsoMapStream(const IsoMapStream&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  IsoMapStream private copy operator : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            IsoMapStream& operator=(const IsoMapStream&) = delete;


        private:
            int32_t             m_chunkX;           // Chunk X
            int32_t             m_chunkY;           // Chunk Y
    };


#endif // VOS_RENDERER_ISOMAP_ISOMAPSTREAM_HEADER
