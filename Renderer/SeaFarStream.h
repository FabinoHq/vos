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
//     Renderer/SeaFarStream.h : SeaFar stream management                     //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_SEAFARSTREAM_HEADER
#define VOS_RENDERER_SEAFARSTREAM_HEADER

    #include "../System/System.h"
    #include "Vulkan/Vulkan.h"
    #include "Vulkan/VertexBuffer.h"
    #include "../Math/Math.h"
    #include "../Math/Vector3.h"
    #include "../Math/Matrix4x4.h"
    #include "../Math/Transform3.h"
    #include "../Resources/Resources.h"

    #include "SeaFarChunk.h"
    #include "HeightFarStream.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  SeaFarStream class definition                                         //
    ////////////////////////////////////////////////////////////////////////////
    class SeaFarStream
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  SeaFarStream default constructor                              //
            ////////////////////////////////////////////////////////////////////
            SeaFarStream();

            ////////////////////////////////////////////////////////////////////
            //  SeaFarStream destructor                                       //
            ////////////////////////////////////////////////////////////////////
            ~SeaFarStream();


            ////////////////////////////////////////////////////////////////////
            //  Init sea far stream                                           //
            //  return : True if the sea far stream is successfully created   //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Render sea far stream                                         //
            ////////////////////////////////////////////////////////////////////
            void render(int32_t chunkX, int32_t chunkY);


        private:
            ////////////////////////////////////////////////////////////////////
            //  SeaFarStream private copy constructor : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            SeaFarStream(const SeaFarStream&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  SeaFarStream private copy operator : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            SeaFarStream& operator=(const SeaFarStream&) = delete;


        private:
            SeaFarChunk         m_seaFarChunk;      // SeaFar chunk
    };


#endif // VOS_RENDERER_SEAFARSTREAM_HEADER
