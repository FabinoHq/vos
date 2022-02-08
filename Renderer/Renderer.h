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
//     Renderer/Renderer.h : Renderer management                              //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_RENDERER_HEADER
#define VOS_RENDERER_RENDERER_HEADER

    #include "../System/SysMessage.h"
    #include "../System/SysWindow.h"
    #include "../System/SysVulkan.h"
    #include "Vulkan/Vulkan.h"
    #include "Vulkan/VulkanMemory.h"
    #include "Vulkan/VulkanQueue.h"
    #include "Vulkan/Swapchain.h"
    #include "Vulkan/VulkanBuffer.h"
    #include "Vulkan/VertexBuffer.h"
    #include "Vulkan/UniformBuffer.h"
    #include "Vulkan/GraphicsLayout.h"
    #include "Pipeline.h"
    #include "Shader.h"
    #include "Texture.h"
    #include "View.h"
    #include "Camera.h"
    #include "FreeFlyCam.h"
    #include "Sprite.h"
    #include "../Math/Math.h"
    #include "../Math/Vector2.h"
    #include "../Math/Matrix4x4.h"

    #include "Shaders/Default.h"
    #include "Shaders/DefaultProc.h"
    #include "Shaders/NinePatch.h"
    #include "Shaders/Rectangle.h"
    #include "Shaders/Ellipse.h"
    #include "Shaders/PxText.h"
    #include "Shaders/StaticMesh.h"

    #include "../Images/Embedded/Cursor.h"
    #include "../Images/Embedded/NSCursor.h"
    #include "../Images/Embedded/EWCursor.h"
    #include "../Images/Embedded/NESWCursor.h"
    #include "../Images/Embedded/NWSECursor.h"

    #include <cstdint>
    #include <vector>


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer clear color                                                  //
    ////////////////////////////////////////////////////////////////////////////
    const VkClearColorValue RendererClearColor = {0.0f, 0.0f, 0.0f, 1.0f};
    const VkClearDepthStencilValue RendererClearDepth = {1.0f, 0};

    ////////////////////////////////////////////////////////////////////////////
    //  Renderer max uniforms descriptor sets                                 //
    ////////////////////////////////////////////////////////////////////////////
    const uint32_t RendererMaxUniformsDesc = 4;

    ////////////////////////////////////////////////////////////////////////////
    //  Renderer max textures descriptor sets                                 //
    ////////////////////////////////////////////////////////////////////////////
    const uint32_t RendererMaxTexturesDesc = 2048;

    ////////////////////////////////////////////////////////////////////////////
    //  Renderer cursors offsets                                              //
    ////////////////////////////////////////////////////////////////////////////
    const Vector2 RendererDefaultCursorOffset = Vector2(2.0f, 2.0f);
    const Vector2 RendererNSCursorOffset = Vector2(10.0f, 24.0f);
    const Vector2 RendererEWCursorOffset = Vector2(24.0f, 10.0f);
    const Vector2 RendererNESWCursorOffset = Vector2(18.0f, 18.0f);
    const Vector2 RendererNWSECursorOffset = Vector2(18.0f, 18.0f);


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class definition                                             //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Renderer default constructor                                  //
            ////////////////////////////////////////////////////////////////////
            Renderer();

            ////////////////////////////////////////////////////////////////////
            //  Renderer destructor                                           //
            ////////////////////////////////////////////////////////////////////
            ~Renderer();


            ////////////////////////////////////////////////////////////////////
            //  Init renderer                                                 //
            //  return : True if the renderer is successfully loaded          //
            ////////////////////////////////////////////////////////////////////
            bool init(SysWindow* sysWindow);

            ////////////////////////////////////////////////////////////////////
            //  Start rendering frame                                         //
            //  return : True if the rendering frame is ready                 //
            ////////////////////////////////////////////////////////////////////
            bool startFrame();

            ////////////////////////////////////////////////////////////////////
            //  End rendering frame                                           //
            //  return : True if the frame is rendering                       //
            ////////////////////////////////////////////////////////////////////
            bool endFrame();

            ////////////////////////////////////////////////////////////////////
            //  Wait renderer device for idle state                           //
            //  return : True if the renderer device is in idle state         //
            ////////////////////////////////////////////////////////////////////
            bool waitDeviceIdle();

            ////////////////////////////////////////////////////////////////////
            //  Cleanup renderer                                              //
            ////////////////////////////////////////////////////////////////////
            void cleanup();


            ////////////////////////////////////////////////////////////////////
            //  Create vertex buffer                                          //
            ////////////////////////////////////////////////////////////////////
            bool createVertexBuffer(VertexBuffer& vertexBuffer,
                const float* vertices, const uint16_t* indices,
                uint32_t verticesCount, uint32_t indicesCount);

            ////////////////////////////////////////////////////////////////////
            //  Update vertex buffer                                          //
            ////////////////////////////////////////////////////////////////////
            bool updateVertexBuffer(VertexBuffer& vertexBuffer,
                const float* vertices, const uint16_t* indices,
                uint32_t verticesCount, uint32_t indicesCount);

            ////////////////////////////////////////////////////////////////////
            //  Destroy vertex buffer                                         //
            ////////////////////////////////////////////////////////////////////
            void destroyVertexBuffer(VertexBuffer& vertexBuffer);


            ////////////////////////////////////////////////////////////////////
            //  Bind renderer default pipeline                                //
            ////////////////////////////////////////////////////////////////////
            void bindDefaultPipeline();

            ////////////////////////////////////////////////////////////////////
            //  Bind renderer ninepatch pipeline                              //
            ////////////////////////////////////////////////////////////////////
            void bindNinePatchPipeline();

            ////////////////////////////////////////////////////////////////////
            //  Bind renderer rectangle pipeline                              //
            ////////////////////////////////////////////////////////////////////
            void bindRectanglePipeline();

            ////////////////////////////////////////////////////////////////////
            //  Bind renderer ellipse pipeline                                //
            ////////////////////////////////////////////////////////////////////
            void bindEllipsePipeline();

            ////////////////////////////////////////////////////////////////////
            //  Bind renderer shape pipeline                                  //
            ////////////////////////////////////////////////////////////////////
            void bindShapePipeline();

            ////////////////////////////////////////////////////////////////////
            //  Bind renderer pixel text pipeline                             //
            ////////////////////////////////////////////////////////////////////
            void bindPxTextPipeline();

            ////////////////////////////////////////////////////////////////////
            //  Bind renderer skybox pipeline                                 //
            ////////////////////////////////////////////////////////////////////
            void bindSkyBoxPipeline();

            ////////////////////////////////////////////////////////////////////
            //  Bind renderer static mesh pipeline                            //
            ////////////////////////////////////////////////////////////////////
            void bindStaticMeshPipeline();


            ////////////////////////////////////////////////////////////////////
            //  Bind renderer default vertex buffer                           //
            ////////////////////////////////////////////////////////////////////
            void bindDefaultVertexBuffer();


            ////////////////////////////////////////////////////////////////////
            //  Set renderer default view                                     //
            //  return : True if the default view is successfully set         //
            ////////////////////////////////////////////////////////////////////
            bool setDefaultView();

            ////////////////////////////////////////////////////////////////////
            //  Set renderer view                                             //
            //  return : True if the view is successfully set                 //
            ////////////////////////////////////////////////////////////////////
            bool setView(View& view);

            ////////////////////////////////////////////////////////////////////
            //  Set renderer camera                                           //
            //  return : True if the camera is successfully set               //
            ////////////////////////////////////////////////////////////////////
            bool setCamera(Camera& camera);


            ////////////////////////////////////////////////////////////////////
            //  Set renderer default cursor                                   //
            ////////////////////////////////////////////////////////////////////
            bool setDefaultCursor();

            ////////////////////////////////////////////////////////////////////
            //  Set renderer NS cursor                                        //
            ////////////////////////////////////////////////////////////////////
            bool setNSCursor();

            ////////////////////////////////////////////////////////////////////
            //  Set renderer EW cursor                                        //
            ////////////////////////////////////////////////////////////////////
            bool setEWCursor();

            ////////////////////////////////////////////////////////////////////
            //  Set renderer NE-SW cursor                                     //
            ////////////////////////////////////////////////////////////////////
            bool setNESWCursor();

            ////////////////////////////////////////////////////////////////////
            //  Set renderer NW-SE cursor                                     //
            ////////////////////////////////////////////////////////////////////
            bool setNWSECursor();

            ////////////////////////////////////////////////////////////////////
            //  Set renderer cursor texture                                   //
            ////////////////////////////////////////////////////////////////////
            bool setCursorTexture(Texture& texture, const Vector2& offset);

            ////////////////////////////////////////////////////////////////////
            //  Render mouse cursor                                           //
            ////////////////////////////////////////////////////////////////////
            void renderCursor(float mouseX, float mouseY);


            ////////////////////////////////////////////////////////////////////
            //  Get renderer ready state                                      //
            //  return : True if the renderer is ready, false otherwise       //
            ////////////////////////////////////////////////////////////////////
            bool isReady();

            ////////////////////////////////////////////////////////////////////
            //  Get renderer width                                            //
            //  return : Renderer width                                       //
            ////////////////////////////////////////////////////////////////////
            uint32_t getWidth();

            ////////////////////////////////////////////////////////////////////
            //  Get renderer height                                           //
            //  return : Renderer height                                      //
            ////////////////////////////////////////////////////////////////////
            uint32_t getHeight();

            ////////////////////////////////////////////////////////////////////
            //  Get renderer scale                                            //
            //  return : Renderer scale (1/height)                            //
            ////////////////////////////////////////////////////////////////////
            float getScale();

            ////////////////////////////////////////////////////////////////////
            //  Get renderer aspect ratio                                     //
            //  return : Renderer aspect ratio                                //
            ////////////////////////////////////////////////////////////////////
            float getRatio();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Renderer private copy constructor : Not copyable              //
            ////////////////////////////////////////////////////////////////////
            Renderer(const Renderer&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Renderer private copy operator : Not copyable                 //
            ////////////////////////////////////////////////////////////////////
            Renderer& operator=(const Renderer&) = delete;


            ////////////////////////////////////////////////////////////////////
            //  Create Vulkan instance                                        //
            //  return : True if Vulkan instance is successfully created      //
            ////////////////////////////////////////////////////////////////////
            bool createVulkanInstance();

            ////////////////////////////////////////////////////////////////////
            //  Select Vulkan device                                          //
            //  return : True if Vulkan device is successfully selected       //
            ////////////////////////////////////////////////////////////////////
            bool selectVulkanDevice();

            ////////////////////////////////////////////////////////////////////
            //  Resize renderer frame                                         //
            //  return : True if the renderer is successfully resized         //
            ////////////////////////////////////////////////////////////////////
            bool resize();


        public:
            bool                m_rendererReady;        // Renderer ready state
            uint32_t            m_frameIndex;           // Current frame index
            SysWindow*          m_sysWindow;            // SysWindow pointer
            VulkanLibHandle     m_vulkanLibHandle;      // Vulkan library handle
            VkInstance          m_vulkanInstance;       // Vulkan instance
            VkSurfaceKHR        m_vulkanSurface;        // Vulkan surface
            VkPhysicalDevice    m_physicalDevice;       // Physical device
            VkDevice            m_vulkanDevice;         // Vulkan device
            VulkanQueue         m_graphicsQueue;        // Graphics queue
            VulkanQueue         m_surfaceQueue;         // Surface queue
            VulkanQueue         m_transferQueue;        // Transfer queue
            VkCommandPool       m_transferCommandPool;  // Transfer command pool
            VkDescriptorPool    m_uniformsDescPool;     // Uniforms desc pool
            VkDescriptorPool    m_texturesDescPool;     // Textures desc pool

            VulkanMemory        m_vulkanMemory;         // Vulkan memory
            Swapchain           m_swapchain;            // Swapchain
            VertexBuffer        m_vertexBuffer;         // Default vertex buffer
            GraphicsLayout      m_layout;               // Graphics layout
            Pipeline            m_pipeline;             // Default pipeline
            Pipeline            m_ninePatchPipeline;    // NinePatch pipeline
            Pipeline            m_rectanglePipeline;    // Rectangle pipeline
            Pipeline            m_ellipsePipeline;      // Ellipse pipeline
            Pipeline            m_shapePipeline;        // Shape pipeline
            Pipeline            m_pxTextPipeline;       // Pixel text pipeline
            Pipeline            m_skyBoxPipeline;       // SkyBox pipeline
            Pipeline            m_staticMeshPipeline;   // Static mesh pipeline
            View                m_view;                 // Default view

            Texture             m_cursorTexture;        // Cursor texture
            Texture             m_nsCursorTexture;      // NS cursor texture
            Texture             m_ewCursorTexture;      // EW cursor texture
            Texture             m_neswCursorTexture;    // NE-SW cursor texture
            Texture             m_nwseCursorTexture;    // NW-SE cursor texture
            Vector2             m_cursorOffset;         // Cursor offset
            Sprite              m_cursor;               // Cursor sprite
    };


#endif // VOS_RENDERER_RENDERER_HEADER
