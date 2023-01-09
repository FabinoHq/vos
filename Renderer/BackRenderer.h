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
//     Renderer/BackRenderer.h : Offscreen renderer management                //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_BACKRENDERER_HEADER
#define VOS_RENDERER_BACKRENDERER_HEADER

    #include "../System/System.h"
    #include "Vulkan/Vulkan.h"
    #include "Renderer.h"


    ////////////////////////////////////////////////////////////////////////////
    //  BackRenderer settings                                                 //
    ////////////////////////////////////////////////////////////////////////////
    const uint32_t BackRendererMaxFrames = 2;
    const uint64_t BackRendererFenceTimeout = 5000000000;
    const uint32_t BackRendererMaxWidth = 4096;
    const uint32_t BackRendererMaxHeight = 4096;


    ////////////////////////////////////////////////////////////////////////////
    //  BackRenderer class definition                                         //
    ////////////////////////////////////////////////////////////////////////////
    class BackRenderer
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  BackRenderer default constructor                              //
            ////////////////////////////////////////////////////////////////////
            BackRenderer();

            ////////////////////////////////////////////////////////////////////
            //  BackRenderer destructor                                       //
            ////////////////////////////////////////////////////////////////////
            ~BackRenderer();


            ////////////////////////////////////////////////////////////////////
            //  Init back renderer                                            //
            //  return : True if the back renderer is successfully loaded     //
            ////////////////////////////////////////////////////////////////////
            bool init(Renderer& renderer, uint32_t width, uint32_t height);

            ////////////////////////////////////////////////////////////////////
            //  Start rendering frame                                         //
            //  return : True if the rendering frame is ready                 //
            ////////////////////////////////////////////////////////////////////
            bool startFrame(Renderer& renderer);

            ////////////////////////////////////////////////////////////////////
            //  End rendering frame                                           //
            //  return : True if the frame is rendering                       //
            ////////////////////////////////////////////////////////////////////
            bool endFrame(Renderer& renderer);

            ////////////////////////////////////////////////////////////////////
            //  Cleanup back renderer                                         //
            ////////////////////////////////////////////////////////////////////
            void cleanup(Renderer& renderer);


        private:
            ////////////////////////////////////////////////////////////////////
            //  BackRenderer private copy constructor : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            BackRenderer(const BackRenderer&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  BackRenderer private copy operator : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            BackRenderer& operator=(const BackRenderer&) = delete;


        public:
            VkExtent2D          m_extent;       // Extent
            VkRenderPass        m_renderPass;   // Render pass
            GraphicsLayout      m_layout;       // Graphics layout
            Pipeline            m_pipeline;     // Default pipeline
            View                m_view;         // Default view
            uint32_t            m_current;      // Current frame
            float               m_ratio;        // Aspect ratio

            VkImage             m_images[BackRendererMaxFrames];
            VkImage             m_depthImages[BackRendererMaxFrames];
            VkImageView         m_views[BackRendererMaxFrames];
            VkImageView         m_depthViews[BackRendererMaxFrames];
            VkFramebuffer       m_framebuffers[BackRendererMaxFrames];
            VkFence             m_fences[RendererMaxSwapchainFrames];
            VkCommandPool       m_commandPools[BackRendererMaxFrames];
            VkCommandBuffer     m_commandBuffers[BackRendererMaxFrames];
    };


#endif // VOS_RENDERER_BACKRENDERER_HEADER
