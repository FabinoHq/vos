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
//   For more information, please refer to <http://unlicense.org>             //
////////////////////////////////////////////////////////////////////////////////
//    VOS : Virtual Operating System                                          //
//     Renderer/Shader.h : Shader management                                  //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_SHADER_HEADER
#define VOS_RENDERER_SHADER_HEADER

    #include "Vulkan/Vulkan.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class declaration                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer;


    ////////////////////////////////////////////////////////////////////////////
    //  Shader class definition                                               //
    ////////////////////////////////////////////////////////////////////////////
    class Shader
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Shader default constructor                                    //
            ////////////////////////////////////////////////////////////////////
            Shader();

            ////////////////////////////////////////////////////////////////////
            //  Shader destructor                                             //
            ////////////////////////////////////////////////////////////////////
            ~Shader();


            ////////////////////////////////////////////////////////////////////
            //  Create Shader                                                 //
            //  return : True if Shader is successfully created               //
            ////////////////////////////////////////////////////////////////////
            bool createShader(Renderer& renderer,
                const uint32_t* vertexSource, const size_t vertexSize,
                const uint32_t* fragmentSource, const size_t fragmentSize);

            ////////////////////////////////////////////////////////////////////
            //  Destroy Shader                                                //
            ////////////////////////////////////////////////////////////////////
            void destroyShader(Renderer& renderer);


            ////////////////////////////////////////////////////////////////////
            //  Check if the vertex and fragment shaders are valids           //
            //  return : True if the shader is valid                          //
            ////////////////////////////////////////////////////////////////////
            bool isValid();

            ////////////////////////////////////////////////////////////////////
            //  Get shader stages info                                        //
            ////////////////////////////////////////////////////////////////////
            void getShaderStagesInfo(
                VkPipelineShaderStageCreateInfo* shaderStageCreateInfo);


        private:
            ////////////////////////////////////////////////////////////////////
            //  Shader private copy constructor : Not copyable                //
            ////////////////////////////////////////////////////////////////////
            Shader(const Shader&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Shader private copy operator : Not copyable                   //
            ////////////////////////////////////////////////////////////////////
            Shader& operator=(const Shader&) = delete;


        private:
            VkShaderModule      m_vertexShader;         // Vertex shader
            VkShaderModule      m_fragmentShader;       // Fragment shader
    };


#endif // VOS_RENDERER_SHADER_HEADER
