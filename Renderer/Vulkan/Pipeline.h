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
//     Renderer/Vulkan/Pipeline.h : Graphics pipeline management              //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_VULKAN_PIPELINE_HEADER
#define VOS_RENDERER_VULKAN_PIPELINE_HEADER

    #include "../../System/System.h"
    #include "../../System/SysVkMemory.h"
    #include "Vulkan.h"
    #include "Swapchain.h"
    #include "GraphicsLayout.h"
    #include "Shader.h"
    #include "../BackRenderer.h"

    #include <cstddef>
    #include <cstdint>
    #include <vector>


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer shaders stages count                                         //
    ////////////////////////////////////////////////////////////////////////////
    const uint32_t RendererShaderStagesCount = 2;

    ////////////////////////////////////////////////////////////////////////////
    //  Renderer max vertex attribs count                                     //
    ////////////////////////////////////////////////////////////////////////////
    const uint32_t RendererMaxVertexAttribsCount = 3;


    ////////////////////////////////////////////////////////////////////////////
    //  Vertex inputs types enumeration                                       //
    ////////////////////////////////////////////////////////////////////////////
    enum VertexInputsType
    {
        VERTEX_INPUTS_DEFAULT = 0,
        VERTEX_INPUTS_CUBEMAP = 1,
        VERTEX_INPUTS_STATICMESH = 2
    };


    ////////////////////////////////////////////////////////////////////////////
    //  Alpha blending mode enumeration                                       //
    ////////////////////////////////////////////////////////////////////////////
    enum AlphaBlendingMode
    {
        ALPHA_BLENDING_NONE = 0,
        ALPHA_BLENDING_PREMULTIPLIED = 1,
        ALPHA_BLENDING_STRAIGHT = 2
    };


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer pipeline enumeration                                         //
    ////////////////////////////////////////////////////////////////////////////
    enum RendererPipeline
    {
        RENDERER_PIPELINE_COMPOSITING = 0,

        RENDERER_PIPELINE_DEFAULT = 1,
        RENDERER_PIPELINE_NINEPATCH = 2,
        RENDERER_PIPELINE_RECTANGLE = 3,
        RENDERER_PIPELINE_ELLIPSE = 4,
        RENDERER_PIPELINE_PXTEXT = 5,
        RENDERER_PIPELINE_BUTTON = 6,
        RENDERER_PIPELINE_TOGGLEBUTTON = 7,
        RENDERER_PIPELINE_PROGRESSBAR = 8,

        RENDERER_PIPELINE_SKYBOX = 9,
        RENDERER_PIPELINE_STATICPROC = 10,
        RENDERER_PIPELINE_STATICMESH = 11,
        RENDERER_PIPELINE_HEIGHTMAP = 12,
        RENDERER_PIPELINE_HEIGHTFAR = 13,
        RENDERER_PIPELINE_SEANEAR = 14,
        RENDERER_PIPELINE_SEAFAR = 15,

        RENDERER_PIPELINE_PIPELINESCOUNT = 16
    };


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
            //  Init pipeline                                                 //
            ////////////////////////////////////////////////////////////////////
            inline void init()
            {
                m_pipeline = 0;
                m_vertexShader.init();
                m_fragmentShader.init();
            }

            ////////////////////////////////////////////////////////////////////
            //  Create vertex shader                                          //
            //  return : True if the vertex shader is successfully created    //
            ////////////////////////////////////////////////////////////////////
            bool createVertexShader(
                const uint32_t* vertexSource, const size_t vertexSize);

            ////////////////////////////////////////////////////////////////////
            //  Create fragment shader                                        //
            //  return : True if the fragment shader is successfully created  //
            ////////////////////////////////////////////////////////////////////
            bool createFragmentShader(
                const uint32_t* fragmentSource, const size_t fragmentSize);


            ////////////////////////////////////////////////////////////////////
            //  Create compositing pipeline                                   //
            //  return : True if compositing pipeline is successfully created //
            ////////////////////////////////////////////////////////////////////
            bool createCompositingPipeline(
                AlphaBlendingMode blendingMode = ALPHA_BLENDING_NONE);

            ////////////////////////////////////////////////////////////////////
            //  Create pipeline                                               //
            //  return : True if pipeline is successfully created             //
            ////////////////////////////////////////////////////////////////////
            bool createPipeline(
                VertexInputsType vertexInputsType = VERTEX_INPUTS_DEFAULT,
                bool depthTest = false, bool backFaceCulling = false,
                AlphaBlendingMode blendingMode = ALPHA_BLENDING_NONE);

            ////////////////////////////////////////////////////////////////////
            //  Bind renderer pipeline                                        //
            ////////////////////////////////////////////////////////////////////
            inline void bind()
            {
                vkCmdBindPipeline(
                    GSwapchain.commandBuffers[GSwapchain.current],
                    VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Destroy pipeline                                              //
            ////////////////////////////////////////////////////////////////////
            void destroyPipeline();


            ////////////////////////////////////////////////////////////////////
            //  Check if the pipeline is valid                                //
            //  return : True if the pipeline is valid                        //
            ////////////////////////////////////////////////////////////////////
            inline bool isValid()
            {
                return m_pipeline;
            }


        private:
            ////////////////////////////////////////////////////////////////////
            //  Pipeline private copy constructor : Not copyable              //
            ////////////////////////////////////////////////////////////////////
            Pipeline(const Pipeline&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Pipeline private copy operator : Not copyable                 //
            ////////////////////////////////////////////////////////////////////
            Pipeline& operator=(const Pipeline&) = delete;


            ////////////////////////////////////////////////////////////////////
            //  Set shader stages                                             //
            ////////////////////////////////////////////////////////////////////
            void setShaderStages(VkPipelineShaderStageCreateInfo* shaderStages);

            ////////////////////////////////////////////////////////////////////
            //  Set vertex inputs                                             //
            ////////////////////////////////////////////////////////////////////
            void setVertexInputs(VkVertexInputBindingDescription& vertexBinding,
                VkVertexInputAttributeDescription* vertexAttribs,
                uint32_t& vertexAttribsCount,
                VertexInputsType vertexInputsType);


        private:
            VkPipeline      m_pipeline;         // Pipeline handle
            Shader          m_vertexShader;     // Vertex shader
            Shader          m_fragmentShader;   // Fragment shader
    };


#endif // VOS_RENDERER_VULKAN_PIPELINE_HEADER
