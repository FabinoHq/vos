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
//     Renderer/Renderer.cpp : Renderer management                            //
////////////////////////////////////////////////////////////////////////////////
#include "Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  Renderer default constructor                                              //
////////////////////////////////////////////////////////////////////////////////
Renderer::Renderer(Resources& resources) :
m_rendererReady(false),
m_frameIndex(0),
m_sysWindow(0),
m_vulkanLibHandle(0),
m_vulkanInstance(0),
m_vulkanSurface(0),
m_physicalDevice(0),
m_vulkanDevice(0),
m_vulkanQueues(),
m_graphicsQueue(),
m_surfaceQueue(),
m_uniformsDescPool(0),
m_texturesDescPool(0),
m_vulkanMemory(),
m_swapchain(),
m_layout(),
m_mainRenderer(),
m_mainPipeline(),
m_mainSprite(),
m_pipeline(),
m_ninePatchPipeline(),
m_rectanglePipeline(),
m_ellipsePipeline(),
m_shapePipeline(),
m_pxTextPipeline(),
m_skyBoxPipeline(),
m_staticMeshPipeline(),
m_heightMapPipeline(),
m_view(),
m_resources(resources),
m_cursorOffset(0.0f, 0.0f),
m_cursor()
{

}

////////////////////////////////////////////////////////////////////////////////
//  Renderer destructor                                                       //
////////////////////////////////////////////////////////////////////////////////
Renderer::~Renderer()
{
    // Cleanup renderer
    cleanup();

    // Destroy Vulkan instance
    if (m_vulkanInstance && vkDestroyInstance)
    {
        vkDestroyInstance(m_vulkanInstance, 0);
    }
    m_vulkanInstance = 0;

    // Free Vulkan functions
    FreeVulkanFunctions();

    // Free Vulkan library
    FreeVulkanLibrary(m_vulkanLibHandle);
}


////////////////////////////////////////////////////////////////////////////////
//  Init renderer                                                             //
//  return : True if the renderer is successfully loaded                      //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::init(SysWindow* sysWindow)
{
    m_rendererReady = false;

    // Check SysWindow
    if (!sysWindow)
    {
        // Invalid SysWindow
        SysMessage::box() << "[0x3001] Invalid system window\n";
        SysMessage::box() << "System window must be valid";
        return false;
    }
    m_sysWindow = sysWindow;

    // Load Vulkan library
    if (!LoadVulkanLibrary(m_vulkanLibHandle))
    {
        // Could not load Vulkan library
        SysMessage::box() << "[0x3002] Could not load Vulkan library\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Load Vulkan GetInstance function
    if (!LoadVulkanGetInstance(m_vulkanLibHandle))
    {
        // Could not load Vulkan GetInstance function
        SysMessage::box() << "[0x3003] Could not load Vulkan GetInstance\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Load Vulkan global functions
    if (!LoadVulkanGlobalFunctions())
    {
        // Could not load Vulkan global functions
        SysMessage::box() << "[0x3004] Could not load global functions\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Create Vulkan instance
    if (!createVulkanInstance())
    {
        // Could not create Vulkan instance
        return false;
    }

    // Load Vulkan CreateSystemSurface
    if (!LoadVulkanCreateSystemSurface(m_vulkanInstance))
    {
        // Could not load Vulkan CreateSystemSurface function
        SysMessage::box() << "[0x300B] Could not load CreateSystemSurface\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Create Vulkan SystemSurface
    if (!CreateVulkanSystemSurface(
        m_vulkanInstance, *m_sysWindow, m_vulkanSurface))
    {
        // Could not create Vulkan SystemSurface
        SysMessage::box() << "[0x300C] Could not create Vulkan SystemSurface\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Load Vulkan instance functions
    if (!LoadVulkanInstanceFunctions(m_vulkanInstance))
    {
        // Could not load Vulkan instance functions
        SysMessage::box() << "[0x300D] Could not load instance functions\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Select Vulkan device
    if (!selectVulkanDevice())
    {
        // Could not select Vulkan device
        return false;
    }

    // Load Vulkan device functions
    if (!LoadVulkanDeviceFunctions(m_vulkanDevice))
    {
        // Could not load Vulkan device functions
        SysMessage::box() << "[0x301E] Could not load device functions\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Init Vulkan memory
    if (!m_vulkanMemory.init(m_physicalDevice, m_vulkanDevice))
    {
        return false;
    }

    // Request graphics queue handle
    if (!m_graphicsQueue.createGraphicsQueue(m_vulkanDevice, m_vulkanQueues))
    {
        // Could not get graphics queue handle
        return false;
    }

    // Request surface queue handle
    if (!m_surfaceQueue.createSurfaceQueue(m_vulkanDevice, m_vulkanQueues))
    {
        // Could not get surface queue handle
        return false;
    }

    // Create swapchain
    if (!m_swapchain.createSwapchain(m_physicalDevice, m_vulkanDevice,
        m_vulkanSurface, m_surfaceQueue.family))
    {
        // Could not create swapchain
        return false;
    }

    // Create uniforms descriptor pool
    VkDescriptorPoolSize uniformsPoolSize;
    uniformsPoolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uniformsPoolSize.descriptorCount =
        RendererMaxUniformsDesc*RendererMaxSwapchainFrames;

    VkDescriptorPoolCreateInfo uniformsPoolInfo;
    uniformsPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    uniformsPoolInfo.pNext = 0;
    uniformsPoolInfo.flags = 0;
    uniformsPoolInfo.maxSets =
        RendererMaxUniformsDesc*RendererMaxSwapchainFrames;
    uniformsPoolInfo.poolSizeCount = 1;
    uniformsPoolInfo.pPoolSizes = &uniformsPoolSize;

    if (vkCreateDescriptorPool(m_vulkanDevice,
        &uniformsPoolInfo, 0, &m_uniformsDescPool) != VK_SUCCESS)
    {
        // Could not create uniforms descriptor pool
        SysMessage::box() << "[0x304C] Could not create uniforms desc pool\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }
    if (!m_uniformsDescPool)
    {
        // Invalid uniforms descriptor pool
        SysMessage::box() << "[0x304D] Invalid uniforms descriptor pool\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Create textures descriptor pool
    VkDescriptorPoolSize texturesPoolSize;
    texturesPoolSize.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    texturesPoolSize.descriptorCount =
        RendererMaxTexturesDesc*RendererMaxSwapchainFrames;

    VkDescriptorPoolCreateInfo texturesPoolInfo;
    texturesPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    texturesPoolInfo.pNext = 0;
    texturesPoolInfo.flags = 0;
    texturesPoolInfo.maxSets =
        RendererMaxTexturesDesc*RendererMaxSwapchainFrames;
    texturesPoolInfo.poolSizeCount = 1;
    texturesPoolInfo.pPoolSizes = &texturesPoolSize;

    if (vkCreateDescriptorPool(m_vulkanDevice,
        &texturesPoolInfo, 0, &m_texturesDescPool) != VK_SUCCESS)
    {
        // Could not create textures descriptor pool
        SysMessage::box() << "[0x304E] Could not create textures desc pool\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }
    if (!m_texturesDescPool)
    {
        // Invalid textures descriptor pool
        SysMessage::box() << "[0x304F] Invalid textures descriptor pool\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Create default pipeline layout
    if (!m_layout.createLayout(m_vulkanDevice))
    {
        // Could not create default pipeline layout
        SysMessage::box() << "[0x3052] Could not create default layout\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Create main renderer
    if (!m_mainRenderer.init(
        *this, VULKAN_MEMORY_BACKCHAIN,
        m_swapchain.extent.width, m_swapchain.extent.height, true))
    {
        // Could not init main renderer
        return false;
    }

    // Create main pipeline
    m_mainPipeline.createVertexShader(
        *this, DefaultVertexShader, DefaultVertexShaderSize
    );
    m_mainPipeline.createFragmentShader(
        *this, DefaultFragmentShader, DefaultFragmentShaderSize
    );
    if (!m_mainPipeline.createCompositingPipeline(*this))
    {
        // Could not create main pipeline
        return false;
    }

    // Create main sprite
    m_mainSprite.setSize(
        (m_swapchain.ratio*2.0f)+RendererCompositingQuadOffset,
        2.0f+RendererCompositingQuadOffset
    );
    m_mainSprite.setColor(1.0f, 1.0f, 1.0f, 1.0f);
    m_mainSprite.setUVSize(1.0f, 1.0f);
    m_mainSprite.setUVOffset(0.0f, 0.0f);

    // Create default pipeline
    m_pipeline.createVertexShader(
        *this, DefaultVertexShader, DefaultVertexShaderSize
    );
    m_pipeline.createFragmentShader(
        *this, DefaultFragmentShader, DefaultFragmentShaderSize
    );
    if (!m_pipeline.createPipeline(*this))
    {
        // Could not create default pipeline
        SysMessage::box() << "[0x3053] Could not create default pipeline\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Create ninepatch pipeline
    m_ninePatchPipeline.createVertexShader(
        *this, DefaultVertexShader, DefaultVertexShaderSize
    );
    m_ninePatchPipeline.createFragmentShader(
        *this, NinePatchFragmentShader, NinePatchFragmentShaderSize
    );
    if (!m_ninePatchPipeline.createPipeline(*this))
    {
        // Could not create ninepatch pipeline
        SysMessage::box() << "[0x3054] Could not create ninepatch pipeline\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Create rectangle pipeline
    m_rectanglePipeline.createVertexShader(
        *this, DefaultVertexShader, DefaultVertexShaderSize
    );
    m_rectanglePipeline.createFragmentShader(
        *this, RectangleFragmentShader, RectangleFragmentShaderSize
    );
    if (!m_rectanglePipeline.createPipeline(*this))
    {
        // Could not create rectangle pipeline
        SysMessage::box() << "[0x3055] Could not create rectangle pipeline\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Create ellipse pipeline
    m_ellipsePipeline.createVertexShader(
        *this, DefaultVertexShader, DefaultVertexShaderSize
    );
    m_ellipsePipeline.createFragmentShader(
        *this, EllipseFragmentShader, EllipseFragmentShaderSize
    );
    if (!m_ellipsePipeline.createPipeline(*this))
    {
        // Could not create ellipse pipeline
        SysMessage::box() << "[0x3056] Could not create ellipse pipeline\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Create shape pipeline
    m_shapePipeline.createVertexShader(
        *this, StaticMeshVertexShader, StaticMeshVertexShaderSize
    );
    m_shapePipeline.createFragmentShader(
        *this, StaticProcFragmentShader, StaticProcFragmentShaderSize
    );
    if (!m_shapePipeline.createPipeline(
        *this, VERTEX_INPUTS_STATICMESH, true, true))
    {
        // Could not create shape pipeline
        SysMessage::box() << "[0x3057] Could not create shape pipeline\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Create pixel text pipeline
    m_pxTextPipeline.createVertexShader(
        *this, DefaultVertexShader, DefaultVertexShaderSize
    );
    m_pxTextPipeline.createFragmentShader(
        *this, PxTextFragmentShader, PxTextFragmentShaderSize
    );
    if (!m_pxTextPipeline.createPipeline(*this))
    {
        // Could not create pixel text pipeline
        SysMessage::box() << "[0x3058] Could not create pixel text pipeline\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Create skybox pipeline
    m_skyBoxPipeline.createVertexShader(
        *this, SkyBoxVertexShader, SkyBoxVertexShaderSize
    );
    m_skyBoxPipeline.createFragmentShader(
        *this, SkyBoxFragmentShader, SkyBoxFragmentShaderSize
    );
    if (!m_skyBoxPipeline.createPipeline(
        *this, VERTEX_INPUTS_CUBEMAP, false, true))
    {
        // Could not create skybox pipeline
        SysMessage::box() << "[0x3059] Could not create skybox pipeline\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Create static mesh pipeline
    m_staticMeshPipeline.createVertexShader(
        *this, StaticMeshVertexShader, StaticMeshVertexShaderSize
    );
    m_staticMeshPipeline.createFragmentShader(
        *this, StaticMeshFragmentShader, StaticMeshFragmentShaderSize
    );
    if (!m_staticMeshPipeline.createPipeline(
        *this, VERTEX_INPUTS_STATICMESH, true, true))
    {
        // Could not create static mesh pipeline
        SysMessage::box() << "[0x305A] Could not create static mesh pipeline\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Create heightmap pipeline
    m_heightMapPipeline.createVertexShader(
        *this, HeightMapVertexShader, HeightMapVertexShaderSize
    );
    m_heightMapPipeline.createFragmentShader(
        *this, HeightMapFragmentShader, HeightMapFragmentShaderSize
    );
    if (!m_heightMapPipeline.createPipeline(
        *this, VERTEX_INPUTS_STATICMESH, true, true))
    {
        // Could not create heightmap pipeline
        SysMessage::box() << "[0x305B] Could not create heightmap pipeline\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Init default view
    if (!m_view.init(*this))
    {
        // Could not init default view
        return false;
    }

    // Set default cursor offset
    m_cursorOffset.set(RendererDefaultCursorOffset);

    // Renderer successfully loaded
    m_rendererReady = true;
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Init embedded resources                                                   //
//  return : True if the renderer embedded resources are ready                //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::initEmbedded()
{
    // Init cursor sprite
    if (!m_cursor.init(m_resources.textures.gui(TEXTURE_CURSOR), 1.0f, 1.0f))
    {
        // Could not init cursor sprite
        return false;
    }

    // Renderer embedded resources are ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Start rendering frame                                                     //
//  return : True if the rendering frame is ready                             //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::startFrame()
{
    // Check renderer state
    if (!m_rendererReady)
    {
        // Resize renderer
        if (!resize())
        {
            // Could not resize renderer
            return false;
        }
    }

    // Clamp swapchain current frame index
    if (m_swapchain.current <= 0)
    {
        m_swapchain.current = 0;
    }
    if (m_swapchain.current >= (m_swapchain.frames-1))
    {
        m_swapchain.current = (m_swapchain.frames-1);
    }

    // Wait for current frame rendering fence
    if (vkWaitForFences(m_vulkanDevice, 1,
        &m_swapchain.fences[m_swapchain.current],
        VK_FALSE, RendererSwapchainFenceTimeout) != VK_SUCCESS)
    {
        // Rendering fence timed out
        m_rendererReady = false;
        return false;
    }

    // Acquire current frame
    if (vkAcquireNextImageKHR(m_vulkanDevice, m_swapchain.handle,
        UINT64_MAX, m_swapchain.renderReady[m_swapchain.current],
        0, &m_frameIndex) != VK_SUCCESS)
    {
        // Could not acquire swapchain frame
        m_rendererReady = false;
        return false;
    }

    // Check current frame index
    if (m_frameIndex >= m_swapchain.frames)
    {
        // Invalid swapchain frame index
        m_rendererReady = false;
        return false;
    }


    // Reset command pool
    if (vkResetCommandPool(m_vulkanDevice,
        m_swapchain.commandPools[m_swapchain.current], 0) != VK_SUCCESS)
    {
        // Could not reset command pool
        m_rendererReady = false;
        return false;
    }

    // Command buffer begin
    VkCommandBufferBeginInfo commandBegin;
    commandBegin.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    commandBegin.pNext = 0;
    commandBegin.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    commandBegin.pInheritanceInfo = 0;

    // Begin command buffer
    if (vkBeginCommandBuffer(m_swapchain.commandBuffers[m_swapchain.current],
        &commandBegin) != VK_SUCCESS)
    {
        // Could not begin command buffer
        m_rendererReady = false;
        return false;
    }

    // Rendering frame is ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  End rendering frame                                                       //
//  return : True if the frame is rendering                                   //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::endFrame()
{
    // Check renderer state
    if (!m_rendererReady)
    {
        // Renderer is not ready
        return false;
    }

    // End command buffer
    if (vkEndCommandBuffer(
        m_swapchain.commandBuffers[m_swapchain.current]) != VK_SUCCESS)
    {
        // Could not end command buffer
        m_rendererReady = false;
        return false;
    }

    // Reset current frame rendering fence
    if (vkResetFences(m_vulkanDevice, 1,
        &m_swapchain.fences[m_swapchain.current]) != VK_SUCCESS)
    {
        // Could not reset fence
        m_rendererReady = false;
        return false;
    }

    // Submit current frame
    VkPipelineStageFlags waitDstStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    VkSubmitInfo submitInfo;
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.pNext = 0;
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores =
        &m_swapchain.renderReady[m_swapchain.current];
    submitInfo.pWaitDstStageMask = &waitDstStage;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers =
        &m_swapchain.commandBuffers[m_swapchain.current];
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = &m_swapchain.renderDone[m_swapchain.current];

    if (vkQueueSubmit(m_surfaceQueue.handle, 1, &submitInfo,
        m_swapchain.fences[m_swapchain.current]) != VK_SUCCESS)
    {
        m_rendererReady = false;
        return false;
    }

    // Update surface when queue has finished rendering
    VkPresentInfoKHR present;
    present.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    present.pNext = 0;
    present.waitSemaphoreCount = 1;
    present.pWaitSemaphores = &m_swapchain.renderDone[m_swapchain.current];
    present.swapchainCount = 1;
    present.pSwapchains = &m_swapchain.handle;
    present.pImageIndices = &m_frameIndex;
    present.pResults = 0;

    if (vkQueuePresentKHR(m_surfaceQueue.handle, &present) != VK_SUCCESS)
    {
        m_rendererReady = false;
        return false;
    }

    // Next swapchain frame index
    ++m_swapchain.current;
    if (m_swapchain.current >= m_swapchain.frames)
    {
        m_swapchain.current = 0;
    }

    // Current frame is submitted for rendering
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Start render pass                                                         //
////////////////////////////////////////////////////////////////////////////////
void Renderer::startRenderPass()
{
    // Set clear values
    VkClearValue clearValues[2];
    clearValues[0].color = BackRendererClearColor;
    clearValues[1].depthStencil = BackRendererClearDepth;

    // Begin render pass
    VkRenderPassBeginInfo renderPassInfo;
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.pNext = 0;
    renderPassInfo.renderPass = m_mainRenderer.m_backchain.renderPass;
    renderPassInfo.framebuffer =
        m_mainRenderer.m_backchain.framebuffers[m_frameIndex];
    renderPassInfo.renderArea.offset.x = 0;
    renderPassInfo.renderArea.offset.y = 0;
    renderPassInfo.renderArea.extent.width =
        m_mainRenderer.m_backchain.extent.width;
    renderPassInfo.renderArea.extent.height =
        m_mainRenderer.m_backchain.extent.height;
    renderPassInfo.clearValueCount = 2;
    renderPassInfo.pClearValues = clearValues;

    vkCmdBeginRenderPass(
        m_swapchain.commandBuffers[m_swapchain.current],
        &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE
    );

    // Set viewport
    VkViewport viewport;
    viewport.x = 0.0f;
    viewport.y = m_mainRenderer.m_backchain.extent.height*1.0f;
    viewport.width = m_mainRenderer.m_backchain.extent.width*1.0f;
    viewport.height = m_mainRenderer.m_backchain.extent.height*-1.0f;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    vkCmdSetViewport(
        m_swapchain.commandBuffers[m_swapchain.current], 0, 1, &viewport
    );

    // Set scissor
    VkRect2D scissor;
    scissor.offset.x = 0;
    scissor.offset.y = 0;
    scissor.extent.width = m_mainRenderer.m_backchain.extent.width;
    scissor.extent.height = m_mainRenderer.m_backchain.extent.height;

    vkCmdSetScissor(
        m_swapchain.commandBuffers[m_swapchain.current], 0, 1, &scissor
    );

    // Push default model matrix into command buffer
    Matrix4x4 defaultMatrix;
    defaultMatrix.setIdentity();
    vkCmdPushConstants(
        m_swapchain.commandBuffers[m_swapchain.current],
        m_layout.handle, VK_SHADER_STAGE_VERTEX_BIT,
        PushConstantMatrixOffset, PushConstantMatrixSize, defaultMatrix.mat
    );

    // Push default constants into command buffer
    PushConstantData pushConstants;
    pushConstants.color[0] = 1.0f;
    pushConstants.color[1] = 1.0f;
    pushConstants.color[2] = 1.0f;
    pushConstants.color[3] = 1.0f;
    pushConstants.offset[0] = 0.0f;
    pushConstants.offset[1] = 0.0f;
    pushConstants.size[0] = 1.0f;
    pushConstants.size[1] = 1.0f;
    pushConstants.time = 0.0f;
    vkCmdPushConstants(
        m_swapchain.commandBuffers[m_swapchain.current],
        m_layout.handle, VK_SHADER_STAGE_FRAGMENT_BIT,
        PushConstantDataOffset, PushConstantDataSize, &pushConstants
    );
}

////////////////////////////////////////////////////////////////////////////////
//  Start final render pass                                                   //
////////////////////////////////////////////////////////////////////////////////
void Renderer::startFinalPass()
{
    // Set clear values
    VkClearValue clearValues[1];
    clearValues[0].color = RendererClearColor;

    // Begin render pass
    VkRenderPassBeginInfo renderPassInfo;
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.pNext = 0;
    renderPassInfo.renderPass = m_swapchain.renderPass;
    renderPassInfo.framebuffer = m_swapchain.framebuffers[m_frameIndex];
    renderPassInfo.renderArea.offset.x = 0;
    renderPassInfo.renderArea.offset.y = 0;
    renderPassInfo.renderArea.extent.width = m_swapchain.extent.width;
    renderPassInfo.renderArea.extent.height = m_swapchain.extent.height;
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = clearValues;

    vkCmdBeginRenderPass(
        m_swapchain.commandBuffers[m_swapchain.current],
        &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE
    );

    // Set viewport
    VkViewport viewport;
    viewport.x = 0.0f;
    viewport.y = m_swapchain.extent.height*1.0f;
    viewport.width = m_swapchain.extent.width*1.0f;
    viewport.height = m_swapchain.extent.height*-1.0f;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    vkCmdSetViewport(
        m_swapchain.commandBuffers[m_swapchain.current], 0, 1, &viewport
    );

    // Set scissor
    VkRect2D scissor;
    scissor.offset.x = 0;
    scissor.offset.y = 0;
    scissor.extent.width = m_swapchain.extent.width;
    scissor.extent.height = m_swapchain.extent.height;

    vkCmdSetScissor(
        m_swapchain.commandBuffers[m_swapchain.current], 0, 1, &scissor
    );

    // Push default model matrix into command buffer
    Matrix4x4 defaultMatrix;
    defaultMatrix.setIdentity();
    vkCmdPushConstants(
        m_swapchain.commandBuffers[m_swapchain.current],
        m_layout.handle, VK_SHADER_STAGE_VERTEX_BIT,
        PushConstantMatrixOffset, PushConstantMatrixSize, defaultMatrix.mat
    );

    // Push default constants into command buffer
    PushConstantData pushConstants;
    pushConstants.color[0] = 1.0f;
    pushConstants.color[1] = 1.0f;
    pushConstants.color[2] = 1.0f;
    pushConstants.color[3] = 1.0f;
    pushConstants.offset[0] = 0.0f;
    pushConstants.offset[1] = 0.0f;
    pushConstants.size[0] = 1.0f;
    pushConstants.size[1] = 1.0f;
    pushConstants.time = 0.0f;
    vkCmdPushConstants(
        m_swapchain.commandBuffers[m_swapchain.current],
        m_layout.handle, VK_SHADER_STAGE_FRAGMENT_BIT,
        PushConstantDataOffset, PushConstantDataSize, &pushConstants
    );
}

////////////////////////////////////////////////////////////////////////////////
//  End render pass                                                           //
////////////////////////////////////////////////////////////////////////////////
void Renderer::endRenderPass()
{
    // End render pass
    vkCmdEndRenderPass(m_swapchain.commandBuffers[m_swapchain.current]);
}

////////////////////////////////////////////////////////////////////////////////
//  Wait renderer device for idle state                                       //
//  return : True if the renderer device is in idle state                     //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::waitDeviceIdle()
{
    // Check vulkan device
    if (!m_vulkanDevice)
    {
        return false;
    }

    // Wait for renderer device idle
    if (vkDeviceWaitIdle(m_vulkanDevice) == VK_SUCCESS)
    {
        // Renderer device is in idle state
        return true;
    }

    // Could not wait for renderer device idle state
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Cleanup renderer                                                          //
////////////////////////////////////////////////////////////////////////////////
void Renderer::cleanup()
{
    m_rendererReady = false;

    // Check vulkan device
    if (!m_vulkanDevice)
    {
        return;
    }

    // Destroy default view
    m_view.destroyView(*this);

    // Destroy heightmap pipeline
    m_heightMapPipeline.destroyPipeline(*this);

    // Destroy static mesh pipeline
    m_staticMeshPipeline.destroyPipeline(*this);

    // Destroy skybox pipeline
    m_skyBoxPipeline.destroyPipeline(*this);

    // Destroy pixel text pipeline
    m_pxTextPipeline.destroyPipeline(*this);

    // Destroy shape pipepline
    m_shapePipeline.destroyPipeline(*this);

    // Destroy ellipse pipeline
    m_ellipsePipeline.destroyPipeline(*this);

    // Destroy rectangle pipeline
    m_rectanglePipeline.destroyPipeline(*this);

    // Destroy ninepatch pipeline
    m_ninePatchPipeline.destroyPipeline(*this);

    // Destroy default pipeline
    m_pipeline.destroyPipeline(*this);

    // Destroy main pipeline
    m_mainPipeline.destroyPipeline(*this);

    // Destroy main renderer
    m_mainRenderer.cleanup(*this);

    // Destroy default pipeline layout
    m_layout.destroyLayout(m_vulkanDevice);

    // Destroy textures descriptor pool
    if (m_texturesDescPool && vkDestroyDescriptorPool)
    {
        vkDestroyDescriptorPool(m_vulkanDevice, m_texturesDescPool, 0);
    }

    // Destroy uniforms descriptor pool
    if (m_uniformsDescPool && vkDestroyDescriptorPool)
    {
        vkDestroyDescriptorPool(m_vulkanDevice, m_uniformsDescPool, 0);
    }

    // Destroy swapchain
    m_swapchain.destroySwapchain(m_vulkanDevice);

    // Cleanup Vulkan memory
    m_vulkanMemory.cleanup(m_vulkanDevice);

    // Destroy Vulkan device
    if (vkDestroyDevice)
    {
        vkDestroyDevice(m_vulkanDevice, 0);
    }

    // Destroy Vulkan surface
    if (m_vulkanInstance && m_vulkanSurface && vkDestroySurfaceKHR)
    {
        vkDestroySurfaceKHR(m_vulkanInstance, m_vulkanSurface, 0);
    }

    m_uniformsDescPool = 0;
    m_texturesDescPool = 0;
    m_vulkanDevice = 0;
    m_vulkanSurface = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Bind renderer default pipeline                                            //
////////////////////////////////////////////////////////////////////////////////
void Renderer::bindDefaultPipeline()
{
    m_pipeline.bind(*this);
}

////////////////////////////////////////////////////////////////////////////////
//  Bind renderer ninepatch pipeline                                          //
////////////////////////////////////////////////////////////////////////////////
void Renderer::bindNinePatchPipeline()
{
    m_ninePatchPipeline.bind(*this);
}

////////////////////////////////////////////////////////////////////////////////
//  Bind renderer rectangle pipeline                                          //
////////////////////////////////////////////////////////////////////////////////
void Renderer::bindRectanglePipeline()
{
    m_rectanglePipeline.bind(*this);
}

////////////////////////////////////////////////////////////////////////////////
//  Bind renderer ellipse pipeline                                            //
////////////////////////////////////////////////////////////////////////////////
void Renderer::bindEllipsePipeline()
{
    m_ellipsePipeline.bind(*this);
}

////////////////////////////////////////////////////////////////////////////////
//  Bind renderer shape pipeline                                              //
////////////////////////////////////////////////////////////////////////////////
void Renderer::bindShapePipeline()
{
    m_shapePipeline.bind(*this);
}

////////////////////////////////////////////////////////////////////////////////
//  Bind renderer pixel text pipeline                                         //
////////////////////////////////////////////////////////////////////////////////
void Renderer::bindPxTextPipeline()
{
    m_pxTextPipeline.bind(*this);
}

////////////////////////////////////////////////////////////////////////////////
//  Bind renderer skybox pipeline                                             //
////////////////////////////////////////////////////////////////////////////////
void Renderer::bindSkyBoxPipeline()
{
    m_skyBoxPipeline.bind(*this);
}

////////////////////////////////////////////////////////////////////////////////
//  Bind renderer static mesh pipeline                                        //
////////////////////////////////////////////////////////////////////////////////
void Renderer::bindStaticMeshPipeline()
{
    m_staticMeshPipeline.bind(*this);
}

////////////////////////////////////////////////////////////////////////////////
//  Bind renderer heightmap pipeline                                          //
////////////////////////////////////////////////////////////////////////////////
void Renderer::bindHeightMapPipeline()
{
    m_heightMapPipeline.bind(*this);
}


////////////////////////////////////////////////////////////////////////////////
//  Bind renderer default vertex buffer                                       //
////////////////////////////////////////////////////////////////////////////////
void Renderer::bindDefaultVertexBuffer()
{
    // Bind default vertex buffer
    VkDeviceSize offset = 0;
    vkCmdBindVertexBuffers(
        m_swapchain.commandBuffers[m_swapchain.current],
        0, 1, &(m_resources.meshes.mesh(MESHES_DEFAULT).vertexBuffer.handle),
        &offset
    );

    vkCmdBindIndexBuffer(
        m_swapchain.commandBuffers[m_swapchain.current],
        (m_resources.meshes.mesh(MESHES_DEFAULT).indexBuffer.handle),
        0, VK_INDEX_TYPE_UINT16
    );
}


////////////////////////////////////////////////////////////////////////////////
//  Set renderer default view                                                 //
//  return : True if the default view is successfully set                     //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::setDefaultView()
{
    // Compute default view
    m_view.compute(m_swapchain.ratio);

    // Bind default view
    if (!m_view.bind(*this))
    {
        // Could not bind default view
        m_rendererReady = false;
        return false;
    }

    // Default view successfully set
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set renderer view                                                         //
//  return : True if the view is successfully set                             //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::setView(View& view)
{
    // Bind view
    if (!view.bind(*this))
    {
        // Could not bind view
        m_rendererReady = false;
        return false;
    }

    // View successfully set
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set renderer camera                                                       //
//  return : True if the camera is successfully set                           //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::setCamera(Camera& camera)
{
    // Bind camera
    if (!camera.bind(*this))
    {
        // Could not bind view
        m_rendererReady = false;
        return false;
    }

    // Camera successfully set
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Set renderer default cursor                                               //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::setDefaultCursor()
{
    m_cursorOffset.set(RendererDefaultCursorOffset);
    return m_cursor.setTexture(m_resources.textures.gui(TEXTURE_CURSOR));
}

////////////////////////////////////////////////////////////////////////////////
//  Set renderer NS cursor                                                    //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::setNSCursor()
{
    m_cursorOffset.set(RendererNSCursorOffset);
    return m_cursor.setTexture(m_resources.textures.gui(TEXTURE_NSCURSOR));
}

////////////////////////////////////////////////////////////////////////////////
//  Set renderer EW cursor                                                    //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::setEWCursor()
{
    m_cursorOffset.set(RendererEWCursorOffset);
    return m_cursor.setTexture(m_resources.textures.gui(TEXTURE_EWCURSOR));
}

////////////////////////////////////////////////////////////////////////////////
//  Set renderer NE-SW cursor                                                 //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::setNESWCursor()
{
    m_cursorOffset.set(RendererNESWCursorOffset);
    return m_cursor.setTexture(m_resources.textures.gui(TEXTURE_NESWCURSOR));
}

////////////////////////////////////////////////////////////////////////////////
//  Set renderer NW-SE cursor                                                 //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::setNWSECursor()
{
    m_cursorOffset.set(RendererNWSECursorOffset);
    return m_cursor.setTexture(m_resources.textures.gui(TEXTURE_NWSECURSOR));
}

////////////////////////////////////////////////////////////////////////////////
//  Set renderer cursor texture                                               //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::setCursorTexture(Texture& texture, const Vector2& offset)
{
    m_cursorOffset.set(offset);
    return m_cursor.setTexture(texture);
}

////////////////////////////////////////////////////////////////////////////////
//  Render mouse cursor                                                       //
////////////////////////////////////////////////////////////////////////////////
void Renderer::renderCursor(float mouseX, float mouseY)
{
    float scale = getScale();
    float cursorSize = 64.0f*scale;
    m_cursor.setSize(cursorSize, cursorSize);
    m_cursor.setOrigin(
        m_cursorOffset.vec[0]*scale, cursorSize - (m_cursorOffset.vec[1]*scale)
    );
    m_cursor.setPosition(mouseX, mouseY);
    m_cursor.render(*this);
}


////////////////////////////////////////////////////////////////////////////////
//  Get renderer ready state                                                  //
//  return : True if the renderer is ready, false otherwise                   //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::isReady()
{
    return m_rendererReady;
}

////////////////////////////////////////////////////////////////////////////////
//  Get renderer width                                                        //
//  return : Renderer width                                                   //
////////////////////////////////////////////////////////////////////////////////
uint32_t Renderer::getWidth()
{
    return m_swapchain.extent.width;
}

////////////////////////////////////////////////////////////////////////////////
//  Get renderer height                                                       //
//  return : Renderer height                                                  //
////////////////////////////////////////////////////////////////////////////////
uint32_t Renderer::getHeight()
{
    return m_swapchain.extent.height;
}

////////////////////////////////////////////////////////////////////////////////
//  Get renderer scale                                                        //
//  return : Renderer scale (1/height)                                        //
////////////////////////////////////////////////////////////////////////////////
float Renderer::getScale()
{
    if (m_swapchain.extent.height > 0)
    {
        return 1.0f/(m_swapchain.extent.height*1.0f);
    }
    return 1.0f;
}

////////////////////////////////////////////////////////////////////////////////
//  Get renderer aspect ratio                                                 //
//  return : Renderer aspect ratio                                            //
////////////////////////////////////////////////////////////////////////////////
float Renderer::getRatio()
{
    return m_swapchain.ratio;
}


////////////////////////////////////////////////////////////////////////////////
//  Create Vulkan instance                                                    //
//  return : True if Vulkan instance is successfully created                  //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::createVulkanInstance()
{
    // Check current Vulkan instance
    if (m_vulkanInstance)
    {
        // Vulkan instance already created
        SysMessage::box() << "[0x3005] Vulkan instance already created\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Enumerate Vulkan extensions properties
    uint32_t extCount = 0;
    if (vkEnumerateInstanceExtensionProperties(0, &extCount, 0) != VK_SUCCESS)
    {
        // Could not enumerate Vulkan extensions properties
        SysMessage::box() << "[0x3006] Could not enumerate extensions\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Get Vulkan extensions properties
    std::vector<VkExtensionProperties> extProperties(extCount);
    if (vkEnumerateInstanceExtensionProperties(
        0, &extCount, extProperties.data()) != VK_SUCCESS)
    {
        // Could not get Vulkan extensions properties
        SysMessage::box() << "[0x3007] Could not get extensions properties\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Check Vulkan extensions properties
    bool allExtFound = true;
    for (size_t i = 0; i < VulkanExtensionsSize; ++i)
    {
        bool extFound = false;
        for (size_t j = 0; j < extProperties.size(); ++j)
        {
            if (strcmp(VulkanExtensions[i],
                extProperties[j].extensionName) == 0)
            {
                extFound = true;
                break;
            }
        }
        if (!extFound)
        {
            allExtFound = false;
            break;
        }
    }
    if (!allExtFound)
    {
        // One or more Vulkan extension is unavailable
        SysMessage::box() << "[0x3008] Required extensions are not supported\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // VkApplication
    VkApplicationInfo appInfos;
    appInfos.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfos.pNext = 0;
    appInfos.pApplicationName = "VOS";
    appInfos.applicationVersion = 1;
    appInfos.pEngineName = "VOS";
    appInfos.engineVersion = 1;
    appInfos.apiVersion = VK_REQ_API_VERSION;

    // VkInstanceCreateInfo
    VkInstanceCreateInfo createInfos;
    createInfos.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfos.pNext = 0;
    createInfos.flags = 0;
    createInfos.pApplicationInfo = &appInfos;
    createInfos.enabledLayerCount = 0;
    createInfos.ppEnabledLayerNames = 0;
    createInfos.enabledExtensionCount = VulkanExtensionsSize;
    createInfos.ppEnabledExtensionNames = VulkanExtensions;

    // Create Vulkan instance
    if (vkCreateInstance(&createInfos, 0, &m_vulkanInstance) != VK_SUCCESS)
    {
        // Could not create Vulkan instance
        SysMessage::box() << "[0x3009] Could not create Vulkan instance\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }
    if (!m_vulkanInstance)
    {
        // Could not create Vulkan instance
        SysMessage::box() << "[0x300A] Could not create Vulkan instance\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Vulkan instance successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Select Vulkan device                                                      //
//  return : True if Vulkan device is successfully selected                   //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::selectVulkanDevice()
{
    // Check Vulkan instance
    if (!m_vulkanInstance)
    {
        // Invalid Vulkan instance
        SysMessage::box() << "[0x300E] Invalid Vulkan instance\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Check Vulkan surface
    if (!m_vulkanSurface)
    {
        // Invalid vulkan surface
        SysMessage::box() << "[0x300F] Invalid vulkan surface\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Check physical device
    if (m_physicalDevice)
    {
        // Physical device already selected
        SysMessage::box() << "[0x3010] Physical device already selected\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Check Vulkan device
    if (m_vulkanDevice)
    {
        // Vulkan device already selected
        SysMessage::box() << "[0x3011] Vulkan device already selected\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // List devices
    uint32_t devicesCounts = 0;
    if (vkEnumeratePhysicalDevices(
        m_vulkanInstance, &devicesCounts, 0) != VK_SUCCESS)
    {
        // Could not enumerate physical devices
        SysMessage::box() << "[0x3012] Could not enumerate physical devices\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }
    if (devicesCounts <= 0)
    {
        // No physical device found
        SysMessage::box() << "[0x3013] No physical device found\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Get physical devices list
    std::vector<VkPhysicalDevice> physicalDevices(devicesCounts);
    if (vkEnumeratePhysicalDevices(
        m_vulkanInstance, &devicesCounts, physicalDevices.data()) != VK_SUCCESS)
    {
        // Could not get physical devices list
        SysMessage::box() << "[0x3014] Could not get physical devices list\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Select a physical device with matching extensions properties
    bool deviceFound = false;
    uint32_t deviceIndex = 0;
    for (uint32_t i = 0; i < devicesCounts; ++i)
    {
        // Get device extensions count
        uint32_t extCount = 0;
        if (vkEnumerateDeviceExtensionProperties(
            physicalDevices[i], 0, &extCount, 0) != VK_SUCCESS)
        {
            // Could not enumerate device extensions properties
            continue;
        }

        // Get device extensions list
        std::vector<VkExtensionProperties> extProperties(extCount);
        if (vkEnumerateDeviceExtensionProperties(physicalDevices[i], 0,
            &extCount, extProperties.data()) != VK_SUCCESS)
        {
            // Could not get extensions properties list
            continue;
        }

        // Check device extensions properties
        bool allExtFound = true;
        for (size_t j = 0; j < VulkanDeviceExtensionsSize; ++j)
        {
            bool extFound = false;
            for (size_t k = 0; k < extProperties.size(); ++k)
            {
                if (strcmp(VulkanDeviceExtensions[j],
                    extProperties[k].extensionName) == 0)
                {
                    extFound = true;
                    break;
                }
            }
            if (!extFound)
            {
                allExtFound = false;
                break;
            }
        }
        if (!allExtFound)
        {
            // One or more device extension is unavailable
            continue;
        }

        // Get physical device properties and features
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(physicalDevices[i], &deviceProperties);
        vkGetPhysicalDeviceFeatures(physicalDevices[i], &deviceFeatures);

        // Check Vulkan version of the device
        if (VK_VERSION_MAJOR(deviceProperties.apiVersion) <
            VK_REQ_MAJOR_API_VERSION)
        {
            // Vulkan version is not supported by the device
            continue;
        }
        else if (VK_VERSION_MAJOR(deviceProperties.apiVersion) ==
            VK_REQ_MAJOR_API_VERSION)
        {
            if (VK_VERSION_MINOR(deviceProperties.apiVersion) <
                VK_REQ_MINOR_API_VERSION)
            {
                // Vulkan version is not supported by the device
                continue;
            }
        }

        // Get device queue families
        if (VulkanQueue::getDeviceQueues(
            m_vulkanSurface, physicalDevices[i], m_vulkanQueues))
        {
            // Current device supports graphics, surface, and transfer queues
            VkFormatProperties formatProperties;
            formatProperties.linearTilingFeatures = 0;
            formatProperties.optimalTilingFeatures = 0;
            formatProperties.bufferFeatures = 0;

            // Check for internal RGBA32 format support
            vkGetPhysicalDeviceFormatProperties(
                physicalDevices[i], VK_FORMAT_R8G8B8A8_UNORM, &formatProperties
            );
            if (!(formatProperties.optimalTilingFeatures &
                VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT))
            {
                // Read-only sampled RGBA32 is not supported by the device
                continue;
            }
            if (!(formatProperties.optimalTilingFeatures &
                VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT))
            {
                // Read-write RGBA32 is not supported by the device
                continue;
            }
            if (!(formatProperties.optimalTilingFeatures &
                VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT))
            {
                // Color attachment RGBA32 is not supported by the device
                continue;
            }
            if (!(formatProperties.optimalTilingFeatures &
                VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT))
            {
                // Colod attachment blend RGBA32 is not supported by the device
                continue;
            }
            if (!(formatProperties.optimalTilingFeatures &
                VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT))
            {
                // Linear filtered RGBA32 is not supported by the device
                continue;
            }
            if (!(formatProperties.optimalTilingFeatures &
                VK_FORMAT_FEATURE_TRANSFER_SRC_BIT))
            {
                // Transfer source RGBA32 is not supported by the device
                continue;
            }
            if (!(formatProperties.optimalTilingFeatures &
                VK_FORMAT_FEATURE_TRANSFER_DST_BIT))
            {
                // Transfer destination RGBA32 is not supported by the device
                continue;
            }

            // Current device supports RGBA32 format
            deviceIndex = i;
            deviceFound = true;
            break;
        }
    }

    if (!deviceFound)
    {
        // Could not find a device with graphics, surface, and transfer queues
        SysMessage::box() << "[0x3019] Could not find a suitable device\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    m_physicalDevice = physicalDevices[deviceIndex];
    if (!m_physicalDevice)
    {
        // Invalid physical device
        SysMessage::box() << "[0x301A] Invalid physical device\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Set vulkan queues
    uint32_t graphicsQueues = RendererMaxGraphicsQueues;
    uint32_t surfaceQueues = RendererMaxSurfaceQueues;
    uint32_t transferQueues = RendererMaxTransferQueues;
    if (m_vulkanQueues.surfaceQueueFamily ==
        m_vulkanQueues.graphicsQueueFamily)
    {
        graphicsQueues += RendererMaxSurfaceQueues;
        surfaceQueues = 0;
    }
    if (m_vulkanQueues.transferQueueFamily ==
        m_vulkanQueues.graphicsQueueFamily)
    {
        graphicsQueues += RendererMaxTransferQueues;
        transferQueues = 0;
    }
    else
    {
        if (m_vulkanQueues.transferQueueFamily ==
            m_vulkanQueues.surfaceQueueFamily)
        {
            surfaceQueues += RendererMaxTransferQueues;
            transferQueues = 0;
        }
    }

    // Check queue count
    if ((graphicsQueues > m_vulkanQueues.graphicsQueueMax) ||
        (surfaceQueues > m_vulkanQueues.surfaceQueueMax) ||
        (transferQueues > m_vulkanQueues.transferQueueMax))
    {
        // Could not find a device with enough queues
        SysMessage::box() << "[0x301B] Device does not provide enough queues\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Set queue priorities
    std::vector<float> graphicsPriorities;
    for (uint32_t i = 0; i < graphicsQueues; ++i)
    {
        graphicsPriorities.push_back(1.0f);
    }

    std::vector<float> surfacePriorities;
    for (uint32_t i = 0; i < surfaceQueues; ++i)
    {
        surfacePriorities.push_back(1.0f);
    }

    std::vector<float> transferPriorities;
    for (uint32_t i = 0; i < transferQueues; ++i)
    {
        transferPriorities.push_back(1.0f);
    }

    // Set graphics queues create infos
    std::vector<VkDeviceQueueCreateInfo> queueInfos;
    queueInfos.push_back(VkDeviceQueueCreateInfo());
    queueInfos.back().sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueInfos.back().pNext = 0;
    queueInfos.back().flags = 0;
    queueInfos.back().queueFamilyIndex = m_vulkanQueues.graphicsQueueFamily;
    queueInfos.back().queueCount = graphicsQueues;
    queueInfos.back().pQueuePriorities = graphicsPriorities.data();

    // Set surface queues create infos
    if (surfaceQueues > 0)
    {
        queueInfos.push_back(VkDeviceQueueCreateInfo());
        queueInfos.back().sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueInfos.back().pNext = 0;
        queueInfos.back().flags = 0;
        queueInfos.back().queueFamilyIndex = m_vulkanQueues.surfaceQueueFamily;
        queueInfos.back().queueCount = surfaceQueues;
        queueInfos.back().pQueuePriorities = surfacePriorities.data();
    }

    // Set transfer queues create infos
    if (transferQueues > 0)
    {
        queueInfos.push_back(VkDeviceQueueCreateInfo());
        queueInfos.back().sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueInfos.back().pNext = 0;
        queueInfos.back().flags = 0;
        queueInfos.back().queueFamilyIndex = m_vulkanQueues.transferQueueFamily;
        queueInfos.back().queueCount = transferQueues;
        queueInfos.back().pQueuePriorities = transferPriorities.data();
    }

    // Create Vulkan device
    VkDeviceCreateInfo deviceInfos;
    deviceInfos.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceInfos.pNext = 0;
    deviceInfos.flags = 0;
    deviceInfos.queueCreateInfoCount = static_cast<uint32_t>(queueInfos.size());
    deviceInfos.pQueueCreateInfos = queueInfos.data();
    deviceInfos.enabledLayerCount = 0;
    deviceInfos.ppEnabledLayerNames = 0;
    deviceInfos.enabledExtensionCount = VulkanDeviceExtensionsSize;
    deviceInfos.ppEnabledExtensionNames = VulkanDeviceExtensions;
    deviceInfos.pEnabledFeatures = 0;

    if (vkCreateDevice(
        m_physicalDevice, &deviceInfos, 0, &m_vulkanDevice) != VK_SUCCESS)
    {
        // Could not create Vulkan device
        SysMessage::box() << "[0x301C] Could not create Vulkan device\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }
    if (!m_vulkanDevice)
    {
        // Invalid Vulkan device
        SysMessage::box() << "[0x301D] Invalid Vulkan device\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Vulkan device successfully selected
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Resize renderer frame                                                     //
//  return : True if the renderer is successfully resized                     //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::resize()
{
    // Wait for device idle
    m_rendererReady = false;
    if (vkDeviceWaitIdle(m_vulkanDevice) != VK_SUCCESS)
    {
        // Could not wait for device idle
        return false;
    }

    // Resize swapchain
    if (!m_swapchain.resizeSwapchain(
        m_physicalDevice, m_vulkanDevice, m_vulkanSurface))
    {
        return false;
    }

    // Reset backchain memory
    m_vulkanMemory.resetMemory(VULKAN_MEMORY_BACKCHAIN);

    // Resize main renderer
    if (!m_mainRenderer.resize(*this, VULKAN_MEMORY_BACKCHAIN,
        m_swapchain.extent.width, m_swapchain.extent.height))
    {
        return false;
    }

    // Wait for device idle
    if (vkDeviceWaitIdle(m_vulkanDevice) != VK_SUCCESS)
    {
        // Could not wait for device idle
        return false;
    }

    // Renderer successfully resized
    m_rendererReady = true;
    return true;
}
