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
//     Renderer/SkyProc.h : Procedural skybox management                      //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_SKYPROC_HEADER
#define VOS_RENDERER_SKYPROC_HEADER

    #include "../System/System.h"
    #include "Vulkan/Vulkan.h"
    #include "Vulkan/Swapchain.h"
    #include "Vulkan/GraphicsLayout.h"
    #include "Vulkan/VertexBuffer.h"
    #include "Vulkan/Pipeline.h"
    #include "../Math/Math.h"
    #include "../Math/Vector4.h"
    #include "../Math/Matrix4x4.h"
    #include "../Math/Transform3.h"
    #include "Shaders/SkyBox.h"
    #include "Shaders/SkyProc.h"
    #include "SkyBox.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  SkyProc class definition                                              //
    ////////////////////////////////////////////////////////////////////////////
    class SkyProc : public Transform3
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  SkyProc default constructor                                   //
            ////////////////////////////////////////////////////////////////////
            SkyProc();

            ////////////////////////////////////////////////////////////////////
            //  SkyProc virtual destructor                                    //
            ////////////////////////////////////////////////////////////////////
            virtual ~SkyProc();


            ////////////////////////////////////////////////////////////////////
            //  Init procedural skybox                                        //
            //  return : True if procedural skybox is successfully created    //
            ////////////////////////////////////////////////////////////////////
            bool init(const uint32_t* fragmentSource = 0,
                const size_t fragmentSize = 0);

            ////////////////////////////////////////////////////////////////////
            //  Destroy procedural skybox                                     //
            ////////////////////////////////////////////////////////////////////
            void destroySkyProc();


            ////////////////////////////////////////////////////////////////////
            //  Bind procedural skybox pipeline                               //
            ////////////////////////////////////////////////////////////////////
            inline void bindPipeline()
            {
                m_pipeline.bind();
            }

            ////////////////////////////////////////////////////////////////////
            //  Render procedural skybox                                      //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  SkyProc private copy constructor : Not copyable               //
            ////////////////////////////////////////////////////////////////////
            SkyProc(const SkyProc&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  SkyProc private copy operator : Not copyable                  //
            ////////////////////////////////////////////////////////////////////
            SkyProc& operator=(const SkyProc&) = delete;


        private:
            Pipeline            m_pipeline;         // SkyProc pipeline
    };


#endif // VOS_RENDERER_SKYPROC_HEADER
