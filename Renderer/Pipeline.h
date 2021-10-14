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
//     Renderer/Pipeline.h : Graphics pipeline management                     //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_PIPELINE_HEADER
#define VOS_RENDERER_PIPELINE_HEADER

    #include "Vulkan/Vulkan.h"
    #include "Shader.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class declaration                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer;


    ////////////////////////////////////////////////////////////////////////////
    //  Pipeline class definition                                             //
    ////////////////////////////////////////////////////////////////////////////
    class Pipeline
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Pipeline default constructor                                  //
            ////////////////////////////////////////////////////////////////////
            Pipeline();

            ////////////////////////////////////////////////////////////////////
            //  Pipeline destructor                                           //
            ////////////////////////////////////////////////////////////////////
            ~Pipeline();


            ////////////////////////////////////////////////////////////////////
            //  Create vertex shader                                          //
            //  return : True if the vertex shader is successfully created    //
            ////////////////////////////////////////////////////////////////////
            bool createVertexShader(Renderer& renderer,
                const uint32_t* vertexSource, const size_t vertexSize);

            ////////////////////////////////////////////////////////////////////
            //  Create fragment shader                                        //
            //  return : True if the fragment shader is successfully created  //
            ////////////////////////////////////////////////////////////////////
            bool createFragmentShader(Renderer& renderer,
                const uint32_t* fragmentSource, const size_t fragmentSize);


            ////////////////////////////////////////////////////////////////////
            //  Create Pipeline                                               //
            //  return : True if Pipeline is successfully created             //
            ////////////////////////////////////////////////////////////////////
            bool createPipeline(Renderer& renderer);

            ////////////////////////////////////////////////////////////////////
            //  Bind Pipeline                                                 //
            ////////////////////////////////////////////////////////////////////
            void bind(Renderer& renderer);

            ////////////////////////////////////////////////////////////////////
            //  Destroy Pipeline                                              //
            ////////////////////////////////////////////////////////////////////
            void destroyPipeline(Renderer& renderer);


            ////////////////////////////////////////////////////////////////////
            //  Check if the pipeline is valid                                //
            //  return : True if the pipeline is valid                        //
            ////////////////////////////////////////////////////////////////////
            bool isValid();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Pipeline private copy constructor : Not copyable              //
            ////////////////////////////////////////////////////////////////////
            Pipeline(const Pipeline&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Pipeline private copy operator : Not copyable                 //
            ////////////////////////////////////////////////////////////////////
            Pipeline& operator=(const Pipeline&) = delete;


        private:
            VkPipeline      m_pipeline;         // Pipeline handle
            Shader          m_vertexShader;     // Vertex shader
            Shader          m_fragmentShader;   // Fragment shader
    };


#endif // VOS_RENDERER_PIPELINE_HEADER
