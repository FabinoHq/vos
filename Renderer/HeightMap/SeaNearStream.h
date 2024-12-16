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
//     Renderer/HeightMap/SeaNearStream.h : SeaNear stream                    //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_HEIGHTMAP_SEANEARSTREAM_HEADER
#define VOS_RENDERER_HEIGHTMAP_SEANEARSTREAM_HEADER

    #include "../../System/System.h"

    #include "../Vulkan/Vulkan.h"
    #include "../Vulkan/VertexBuffer.h"

    #include "../../Math/Math.h"
    #include "../../Math/Vector3.h"
    #include "../../Math/Matrix4x4.h"
    #include "../../Math/Transform3.h"

    #include "../../Resources/Resources.h"

    #include "SeaNearChunk.h"
    #include "HeightMapStream.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  SeaNearStream class definition                                        //
    ////////////////////////////////////////////////////////////////////////////
    class SeaNearStream
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  SeaNearStream default constructor                             //
            ////////////////////////////////////////////////////////////////////
            SeaNearStream();

            ////////////////////////////////////////////////////////////////////
            //  SeaNearStream destructor                                      //
            ////////////////////////////////////////////////////////////////////
            ~SeaNearStream();


            ////////////////////////////////////////////////////////////////////
            //  Init sea near stream                                          //
            //  return : True if the sea near stream is successfully created  //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Render sea near stream                                        //
            ////////////////////////////////////////////////////////////////////
            void render(int32_t chunkX, int32_t chunkY);


        private:
            ////////////////////////////////////////////////////////////////////
            //  SeaNearStream private copy constructor : Not copyable         //
            ////////////////////////////////////////////////////////////////////
            SeaNearStream(const SeaNearStream&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  SeaNearStream private copy operator : Not copyable            //
            ////////////////////////////////////////////////////////////////////
            SeaNearStream& operator=(const SeaNearStream&) = delete;


        private:
            SeaNearChunk        m_seaNearChunk;     // SeaNear chunk
    };


#endif // VOS_RENDERER_HEIGHTMAP_SEANEARSTREAM_HEADER
