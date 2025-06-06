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
//     Renderer/Vulkan/ComputePipeline.h : Compute pipeline management        //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_VULKAN_COMPUTEPIPELINE_HEADER
#define VOS_RENDERER_VULKAN_COMPUTEPIPELINE_HEADER

    #include "../../System/System.h"
    #include "../../System/SysVkMemory.h"
    #include "Vulkan.h"
    #include "ComputeLayout.h"
    #include "Shader.h"

    #include <cstddef>
    #include <cstdint>
    #include <vector>


    ////////////////////////////////////////////////////////////////////////////
    //  ComputePipeline class definition                                      //
    ////////////////////////////////////////////////////////////////////////////
    class ComputePipeline
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  ComputePipeline default constructor                           //
            ////////////////////////////////////////////////////////////////////
            ComputePipeline();

            ////////////////////////////////////////////////////////////////////
            //  ComputePipeline destructor                                    //
            ////////////////////////////////////////////////////////////////////
            ~ComputePipeline();


            ////////////////////////////////////////////////////////////////////
            //  Create compute shader                                         //
            //  return : True if the compute shader is successfully created   //
            ////////////////////////////////////////////////////////////////////
            bool createComputeShader(
                const uint32_t* computeSource, const size_t computeSize);


            ////////////////////////////////////////////////////////////////////
            //  Create compute pipeline                                       //
            //  return : True if compute pipeline is successfully created     //
            ////////////////////////////////////////////////////////////////////
            bool createComputePipeline();

            ////////////////////////////////////////////////////////////////////
            //  Destroy compute pipeline                                      //
            ////////////////////////////////////////////////////////////////////
            void destroyComputePipeline();


            ////////////////////////////////////////////////////////////////////
            //  Check if the compute pipeline is valid                        //
            //  return : True if the compute pipeline is valid                //
            ////////////////////////////////////////////////////////////////////
            inline bool isValid()
            {
                return m_pipeline;
            }


        private:
            ////////////////////////////////////////////////////////////////////
            //  ComputePipeline private copy constructor : Not copyable       //
            ////////////////////////////////////////////////////////////////////
            ComputePipeline(const ComputePipeline&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  ComputePipeline private copy operator : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            ComputePipeline& operator=(const ComputePipeline&) = delete;


        private:
            VkPipeline      m_pipeline;         // Compute pipeline handle
            Shader          m_computeShader;    // Compute shader
    };


#endif // VOS_RENDERER_VULKAN_COMPUTEPIPELINE_HEADER
