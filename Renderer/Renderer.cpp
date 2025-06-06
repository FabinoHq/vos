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
//  Renderer global instance                                                  //
////////////////////////////////////////////////////////////////////////////////
Renderer GRenderer = Renderer();


////////////////////////////////////////////////////////////////////////////////
//  Renderer default constructor                                              //
////////////////////////////////////////////////////////////////////////////////
Renderer::Renderer() :
ready(false),
frameIndex(0),
pipelines(0),
view(),
plane()
{

}

////////////////////////////////////////////////////////////////////////////////
//  Renderer destructor                                                       //
////////////////////////////////////////////////////////////////////////////////
Renderer::~Renderer()
{
    // Destroy renderer
    destroyRenderer();

    // Destroy Vulkan instance
    if (GVulkanInstance)
    {
        vkDestroyInstance(GVulkanInstance, SYSVKMEMORY_INSTANCE_ALLOC);
    }
    GVulkanInstance = 0;

    // Free Vulkan functions
    FreeVulkanFunctions();

    // Free Vulkan library
    FreeVulkanLibrary();
}


////////////////////////////////////////////////////////////////////////////////
//  Init renderer                                                             //
//  return : True if the renderer is successfully loaded                      //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::init()
{
    ready = false;

    // Check SysWindow
    if (!GSysWindow.isValid())
    {
        // Invalid SysWindow
        GSysMessage << "[0x3001] Invalid system window\n";
        GSysMessage << "System window must be valid";
        return false;
    }

    // Load Vulkan library
    if (!LoadVulkanLibrary())
    {
        // Could not load Vulkan library
        GSysMessage << "[0x3002] Could not load Vulkan library\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Load Vulkan GetInstance function
    if (!LoadVulkanGetInstance())
    {
        // Could not load Vulkan GetInstance function
        GSysMessage << "[0x3003] Could not load Vulkan GetInstance\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Load Vulkan global functions
    if (!LoadVulkanGlobalFunctions())
    {
        // Could not load Vulkan global functions
        GSysMessage << "[0x3004] Could not load global functions\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Create Vulkan instance
    if (!createVulkanInstance())
    {
        // Could not create Vulkan instance
        return false;
    }

    // Load Vulkan CreateSystemSurface
    if (!LoadVulkanCreateSystemSurface())
    {
        // Could not load Vulkan CreateSystemSurface function
        GSysMessage << "[0x300B] Could not load CreateSystemSurface\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Create Vulkan SystemSurface
    if (!CreateVulkanSystemSurface())
    {
        // Could not create Vulkan SystemSurface
        GSysMessage << "[0x300C] Could not create Vulkan SystemSurface\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Load Vulkan instance functions
    if (!LoadVulkanInstanceFunctions())
    {
        // Could not load Vulkan instance functions
        GSysMessage << "[0x300D] Could not load instance functions\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Select Vulkan device
    if (!selectVulkanDevice())
    {
        // Could not select Vulkan device
        return false;
    }

    // Load Vulkan device functions
    if (!LoadVulkanDeviceFunctions())
    {
        // Could not load Vulkan device functions
        GSysMessage << "[0x301B] Could not load device functions\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Init Vulkan memory
    if (!GVulkanMemory.init())
    {
        return false;
    }

    // Create swapchain
    if (!GSwapchain.createSwapchain())
    {
        // Could not create swapchain
        return false;
    }

    // Create uniformchain
    if (!GUniformchain.createUniformchain())
    {
        // Could not create uniformchain
        return false;
    }

    // Create graphics layout
    if (!GGraphicsLayout.createLayout())
    {
        // Could not create graphics layout
        GSysMessage << "[0x3052] Could not create graphics layout\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Create compute layout
    if (!GComputeLayout.createLayout())
    {
        // Could not create compute layout
        GSysMessage << "[0x3052] Could not create compute layout\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Create main renderer
    if (!GMainRenderer.init(VULKAN_MEMORY_BACKCHAIN,
        GSwapchain.extent.width, GSwapchain.extent.height, true))
    {
        // Could not init main renderer
        return false;
    }

    // Init renderer pipelines
    if (!initPipelines())
    {
        // Could not init renderer pipelines
        return false;
    }

    // Init world light
    if (!GWorldLight.init())
    {
        // Could not init world light
        GSysMessage << "[0x3053] Could not init world light\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Init default view
    if (!view.init())
    {
        // Could not init default view
        return false;
    }

    // Create compositing plane
    plane.setSize(
        (GSwapchain.ratio*2.0f)+RendererCompositingPlaneOffset,
        2.0f+RendererCompositingPlaneOffset
    );
    plane.setColor(1.0f, 1.0f, 1.0f, 1.0f);
    plane.setUVSize(1.0f, 1.0f);
    plane.setUVOffset(0.0f, 0.0f);


    // Wait for device idle
    if (!waitDeviceIdle())
    {
        // Could not get the device ready
        return false;
    }

    // Renderer successfully loaded
    ready = true;
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Init renderer pipelines                                                   //
//  return : True if the renderer pipelines are ready                         //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::initPipelines()
{
    // Check pipelines
    if (pipelines)
    {
        // Pipelines already allocated
        return false;
    }

    // Allocate pipelines
    pipelines = GSysMemory.alloc<Pipeline>(
        RENDERER_PIPELINE_PIPELINESCOUNT, SYSMEMORY_RENDERER
    );
    if (!pipelines) { return false; }

    // Init pipelines
    for (int i = 0; i < RENDERER_PIPELINE_PIPELINESCOUNT; ++i)
    {
        pipelines[i].init();
    }


    // Create compositing pipeline
    pipelines[RENDERER_PIPELINE_COMPOSITING].createVertexShader(
        DefaultVertexShader, DefaultVertexShaderSize
    );
    pipelines[RENDERER_PIPELINE_COMPOSITING].createFragmentShader(
        DefaultFragmentShader, DefaultFragmentShaderSize
    );
    if (!pipelines[RENDERER_PIPELINE_COMPOSITING].createCompositingPipeline(
        ALPHA_BLENDING_PREMULTIPLIED))
    {
        // Could not create compositing pipeline
        return false;
    }


    // Create default pipeline
    pipelines[RENDERER_PIPELINE_DEFAULT].createVertexShader(
        DefaultVertexShader, DefaultVertexShaderSize
    );
    pipelines[RENDERER_PIPELINE_DEFAULT].createFragmentShader(
        DefaultFragmentShader, DefaultFragmentShaderSize
    );
    if (!pipelines[RENDERER_PIPELINE_DEFAULT].createPipeline(
        VERTEX_INPUTS_DEFAULT, false, false,
        ALPHA_BLENDING_PREMULTIPLIED))
    {
        // Could not create default pipeline
        GSysMessage << "[0x3053] Could not create default pipeline\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Create ninepatch pipeline
    pipelines[RENDERER_PIPELINE_NINEPATCH].createVertexShader(
        DefaultVertexShader, DefaultVertexShaderSize
    );
    pipelines[RENDERER_PIPELINE_NINEPATCH].createFragmentShader(
        NinePatchFragmentShader, NinePatchFragmentShaderSize
    );
    if (!pipelines[RENDERER_PIPELINE_NINEPATCH].createPipeline(
        VERTEX_INPUTS_DEFAULT, false, false,
        ALPHA_BLENDING_PREMULTIPLIED))
    {
        // Could not create ninepatch pipeline
        GSysMessage << "[0x3054] Could not create ninepatch pipeline\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Create rectangle pipeline
    pipelines[RENDERER_PIPELINE_RECTANGLE].createVertexShader(
        DefaultVertexShader, DefaultVertexShaderSize
    );
    pipelines[RENDERER_PIPELINE_RECTANGLE].createFragmentShader(
        RectangleFragmentShader, RectangleFragmentShaderSize
    );
    if (!pipelines[RENDERER_PIPELINE_RECTANGLE].createPipeline(
        VERTEX_INPUTS_DEFAULT, false, false,
        ALPHA_BLENDING_PREMULTIPLIED))
    {
        // Could not create rectangle pipeline
        GSysMessage << "[0x3055] Could not create rectangle pipeline\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Create ellipse pipeline
    pipelines[RENDERER_PIPELINE_ELLIPSE].createVertexShader(
        DefaultVertexShader, DefaultVertexShaderSize
    );
    pipelines[RENDERER_PIPELINE_ELLIPSE].createFragmentShader(
        EllipseFragmentShader, EllipseFragmentShaderSize
    );
    if (!pipelines[RENDERER_PIPELINE_ELLIPSE].createPipeline(
        VERTEX_INPUTS_DEFAULT, false, false,
        ALPHA_BLENDING_PREMULTIPLIED))
    {
        // Could not create ellipse pipeline
        GSysMessage << "[0x3056] Could not create ellipse pipeline\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Create pixel text pipeline
    pipelines[RENDERER_PIPELINE_PXTEXT].createVertexShader(
        DefaultVertexShader, DefaultVertexShaderSize
    );
    pipelines[RENDERER_PIPELINE_PXTEXT].createFragmentShader(
        PxTextFragmentShader, PxTextFragmentShaderSize
    );
    if (!pipelines[RENDERER_PIPELINE_PXTEXT].createPipeline(
        VERTEX_INPUTS_DEFAULT, false, false,
        ALPHA_BLENDING_PREMULTIPLIED))
    {
        // Could not create pixel text pipeline
        GSysMessage << "[0x3057] Could not create pixel text pipeline\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Create button pipeline
    pipelines[RENDERER_PIPELINE_BUTTON].createVertexShader(
        DefaultVertexShader, DefaultVertexShaderSize
    );
    pipelines[RENDERER_PIPELINE_BUTTON].createFragmentShader(
        ButtonFragmentShader, ButtonFragmentShaderSize
    );
    if (!pipelines[RENDERER_PIPELINE_BUTTON].createPipeline(
        VERTEX_INPUTS_DEFAULT, false, false,
        ALPHA_BLENDING_PREMULTIPLIED))
    {
        // Could not create button pipeline
        GSysMessage << "[0x3058] Could not create button pipeline\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Create toggle button pipeline
    pipelines[RENDERER_PIPELINE_TOGGLEBUTTON].createVertexShader(
        DefaultVertexShader, DefaultVertexShaderSize
    );
    pipelines[RENDERER_PIPELINE_TOGGLEBUTTON].createFragmentShader(
        ToggleButtonFragmentShader, ToggleButtonFragmentShaderSize
    );
    if (!pipelines[RENDERER_PIPELINE_TOGGLEBUTTON].createPipeline(
        VERTEX_INPUTS_DEFAULT, false, false,
        ALPHA_BLENDING_PREMULTIPLIED))
    {
        // Could not create toggle button pipeline
        GSysMessage << "[0x3058] Could not create toggle btn pipeline\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Create progress bar pipeline
    pipelines[RENDERER_PIPELINE_PROGRESSBAR].createVertexShader(
        DefaultVertexShader, DefaultVertexShaderSize
    );
    pipelines[RENDERER_PIPELINE_PROGRESSBAR].createFragmentShader(
        ProgressBarFragmentShader, ProgressBarFragmentShaderSize
    );
    if (!pipelines[RENDERER_PIPELINE_PROGRESSBAR].createPipeline(
        VERTEX_INPUTS_DEFAULT, false, false,
        ALPHA_BLENDING_PREMULTIPLIED))
    {
        // Could not create progress bar pipeline
        GSysMessage << "[0x3058] Could not create progressbar pipeline\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }


    // Create skybox pipeline
    pipelines[RENDERER_PIPELINE_SKYBOX].createVertexShader(
        SkyBoxVertexShader, SkyBoxVertexShaderSize
    );
    pipelines[RENDERER_PIPELINE_SKYBOX].createFragmentShader(
        SkyBoxFragmentShader, SkyBoxFragmentShaderSize
    );
    if (!pipelines[RENDERER_PIPELINE_SKYBOX].createPipeline(
        VERTEX_INPUTS_CUBEMAP, false, true,
        ALPHA_BLENDING_PREMULTIPLIED))
    {
        // Could not create skybox pipeline
        GSysMessage << "[0x3059] Could not create skybox pipeline\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Create static proc pipeline
    pipelines[RENDERER_PIPELINE_STATICPROC].createVertexShader(
        StaticMeshVertexShader, StaticMeshVertexShaderSize
    );
    pipelines[RENDERER_PIPELINE_STATICPROC].createFragmentShader(
        StaticProcFragmentShader, StaticProcFragmentShaderSize
    );
    if (!pipelines[RENDERER_PIPELINE_STATICPROC].createPipeline(
        VERTEX_INPUTS_STATICMESH, true, true,
        ALPHA_BLENDING_PREMULTIPLIED))
    {
        // Could not create static proc pipeline
        GSysMessage << "[0x3057] Could not create static proc pipeline\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Create static mesh pipeline
    pipelines[RENDERER_PIPELINE_STATICMESH].createVertexShader(
        StaticMeshVertexShader, StaticMeshVertexShaderSize
    );
    pipelines[RENDERER_PIPELINE_STATICMESH].createFragmentShader(
        StaticMeshFragmentShader, StaticMeshFragmentShaderSize
    );
    if (!pipelines[RENDERER_PIPELINE_STATICMESH].createPipeline(
        VERTEX_INPUTS_STATICMESH, true, true,
        ALPHA_BLENDING_PREMULTIPLIED))
    {
        // Could not create static mesh pipeline
        GSysMessage << "[0x305A] Could not create static mesh pipeline\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Create heightmap pipeline
    pipelines[RENDERER_PIPELINE_HEIGHTMAP].createVertexShader(
        HeightMapVertexShader, HeightMapVertexShaderSize
    );
    pipelines[RENDERER_PIPELINE_HEIGHTMAP].createFragmentShader(
        HeightMapFragmentShader, HeightMapFragmentShaderSize
    );
    if (!pipelines[RENDERER_PIPELINE_HEIGHTMAP].createPipeline(
        VERTEX_INPUTS_STATICMESH, true, true,
        ALPHA_BLENDING_PREMULTIPLIED))
    {
        // Could not create heightmap pipeline
        GSysMessage << "[0x305B] Could not create heightmap pipeline\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Create heightfar pipeline
    pipelines[RENDERER_PIPELINE_HEIGHTFAR].createVertexShader(
        HeightFarVertexShader, HeightFarVertexShaderSize
    );
    pipelines[RENDERER_PIPELINE_HEIGHTFAR].createFragmentShader(
        HeightFarFragmentShader, HeightFarFragmentShaderSize
    );
    if (!pipelines[RENDERER_PIPELINE_HEIGHTFAR].createPipeline(
        VERTEX_INPUTS_STATICMESH, true, true,
        ALPHA_BLENDING_PREMULTIPLIED))
    {
        // Could not create heightmap pipeline
        GSysMessage << "[0x305C] Could not create heightfar pipeline\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Create sea near pipeline
    pipelines[RENDERER_PIPELINE_SEANEAR].createVertexShader(
        SeaNearVertexShader, SeaNearVertexShaderSize
    );
    pipelines[RENDERER_PIPELINE_SEANEAR].createFragmentShader(
        SeaNearFragmentShader, SeaNearFragmentShaderSize
    );
    if (!pipelines[RENDERER_PIPELINE_SEANEAR].createPipeline(
        VERTEX_INPUTS_STATICMESH, true, false,
        ALPHA_BLENDING_PREMULTIPLIED))
    {
        // Could not create sea near pipeline
        GSysMessage << "[0x305D] Could not create seanear pipeline\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Create sea far pipeline
    pipelines[RENDERER_PIPELINE_SEAFAR].createVertexShader(
        SeaFarVertexShader, SeaFarVertexShaderSize
    );
    pipelines[RENDERER_PIPELINE_SEAFAR].createFragmentShader(
        SeaFarFragmentShader, SeaFarFragmentShaderSize
    );
    if (!pipelines[RENDERER_PIPELINE_SEAFAR].createPipeline(
        VERTEX_INPUTS_STATICMESH, true, false,
        ALPHA_BLENDING_PREMULTIPLIED))
    {
        // Could not create sea far pipeline
        GSysMessage << "[0x305E] Could not create seafar pipeline\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Renderer pipelines are ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Start rendering frame                                                     //
//  return : True if the rendering frame is ready                             //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::startFrame()
{
    // Check renderer state
    if (!ready)
    {
        // Resize renderer
        if (!resize())
        {
            // Could not resize renderer
            return false;
        }
    }

    // Wait for current frame rendering fence
    if (vkWaitForFences(GVulkanDevice, 1,
        &GSwapchain.fences[GSwapchain.current],
        VK_FALSE, RendererSwapchainFenceTimeout) != VK_SUCCESS)
    {
        // Rendering fence timed out
        ready = false;
        return false;
    }

    // Acquire current frame
    if (vkAcquireNextImageKHR(GVulkanDevice, GSwapchain.handle,
        UINT64_MAX, GSwapchain.renderReady[GSwapchain.current],
        0, &frameIndex) != VK_SUCCESS)
    {
        // Could not acquire swapchain frame
        ready = false;
        return false;
    }

    // Check current frame index
    if (frameIndex >= GSwapchain.frames)
    {
        // Invalid swapchain frame index
        ready = false;
        return false;
    }


    // Reset command pool
    if (vkResetCommandPool(GVulkanDevice,
        GSwapchain.commandPools[GSwapchain.current], 0) != VK_SUCCESS)
    {
        // Could not reset command pool
        ready = false;
        return false;
    }

    // Command buffer begin
    VkCommandBufferBeginInfo commandBegin;
    commandBegin.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    commandBegin.pNext = 0;
    commandBegin.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    commandBegin.pInheritanceInfo = 0;

    // Begin command buffer
    if (vkBeginCommandBuffer(GSwapchain.commandBuffers[GSwapchain.current],
        &commandBegin) != VK_SUCCESS)
    {
        // Could not begin command buffer
        ready = false;
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
    if (!ready)
    {
        // Renderer is not ready
        return false;
    }

    // End command buffer
    if (vkEndCommandBuffer(
        GSwapchain.commandBuffers[GSwapchain.current]) != VK_SUCCESS)
    {
        // Could not end command buffer
        ready = false;
        return false;
    }

    // Reset current frame rendering fence
    if (vkResetFences(GVulkanDevice, 1,
        &GSwapchain.fences[GSwapchain.current]) != VK_SUCCESS)
    {
        // Could not reset fence
        ready = false;
        return false;
    }

    // Submit current frame
    VkSemaphore waitSemaphores[2];
    waitSemaphores[0] = GSwapchain.renderReady[GSwapchain.current];
    waitSemaphores[1] = GUniformchain.uniformsReady[GSwapchain.current];

    VkPipelineStageFlags waitDstStage[2];
    waitDstStage[0] = VK_PIPELINE_STAGE_TRANSFER_BIT;
    waitDstStage[1] = VK_PIPELINE_STAGE_VERTEX_SHADER_BIT;

    VkSubmitInfo submitInfo;
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.pNext = 0;
    submitInfo.waitSemaphoreCount = 2;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitDstStage;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &GSwapchain.commandBuffers[GSwapchain.current];
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = &GSwapchain.renderDone[GSwapchain.current];

    VkPresentInfoKHR present;
    present.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    present.pNext = 0;
    present.waitSemaphoreCount = 1;
    present.pWaitSemaphores = &GSwapchain.renderDone[GSwapchain.current];
    present.swapchainCount = 1;
    present.pSwapchains = &GSwapchain.handle;
    present.pImageIndices = &frameIndex;
    present.pResults = 0;

    if (GSwapchain.swapchainQueue.shared > 0)
    {
        // Shared queue
        GVulkanQueues.queueMutex[GSwapchain.swapchainQueue.shared].lock();
        if (vkQueueSubmit(GSwapchain.swapchainQueue.handle, 1, &submitInfo,
            GSwapchain.fences[GSwapchain.current]) != VK_SUCCESS)
        {
            GVulkanQueues.queueMutex[GSwapchain.swapchainQueue.shared].unlock();
            ready = false;
            return false;
        }

        // Update surface when queue has finished rendering
        if (vkQueuePresentKHR(
            GSwapchain.swapchainQueue.handle, &present) != VK_SUCCESS)
        {
            GVulkanQueues.queueMutex[GSwapchain.swapchainQueue.shared].unlock();
            ready = false;
            return false;
        }
        GVulkanQueues.queueMutex[GSwapchain.swapchainQueue.shared].unlock();
    }
    else
    {
        // Dedicated queue
        if (vkQueueSubmit(GSwapchain.swapchainQueue.handle, 1, &submitInfo,
            GSwapchain.fences[GSwapchain.current]) != VK_SUCCESS)
        {
            ready = false;
            return false;
        }

        // Update surface when queue has finished rendering
        if (vkQueuePresentKHR(
            GSwapchain.swapchainQueue.handle, &present) != VK_SUCCESS)
        {
            ready = false;
            return false;
        }
    }

    // Next swapchain frame index
    ++GSwapchain.current;
    if (GSwapchain.current >= GSwapchain.frames)
    {
        GSwapchain.current = 0;
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
    renderPassInfo.renderPass = GMainRenderer.backchain.renderPass;
    renderPassInfo.framebuffer =
        GMainRenderer.backchain.framebuffers[frameIndex];
    renderPassInfo.renderArea.offset.x = 0;
    renderPassInfo.renderArea.offset.y = 0;
    renderPassInfo.renderArea.extent.width =
        GMainRenderer.backchain.extent.width;
    renderPassInfo.renderArea.extent.height =
        GMainRenderer.backchain.extent.height;
    renderPassInfo.clearValueCount = 2;
    renderPassInfo.pClearValues = clearValues;

    vkCmdBeginRenderPass(
        GSwapchain.commandBuffers[GSwapchain.current],
        &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE
    );

    // Set viewport
    VkViewport viewport;
    viewport.x = 0.0f;
    viewport.y = GMainRenderer.backchain.extent.height*1.0f;
    viewport.width = GMainRenderer.backchain.extent.width*1.0f;
    viewport.height = GMainRenderer.backchain.extent.height*-1.0f;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    vkCmdSetViewport(
        GSwapchain.commandBuffers[GSwapchain.current], 0, 1, &viewport
    );

    // Set scissor
    VkRect2D scissor;
    scissor.offset.x = 0;
    scissor.offset.y = 0;
    scissor.extent.width = GMainRenderer.backchain.extent.width;
    scissor.extent.height = GMainRenderer.backchain.extent.height;

    vkCmdSetScissor(
        GSwapchain.commandBuffers[GSwapchain.current], 0, 1, &scissor
    );

    // Push default model matrix into command buffer
    Matrix4x4 defaultMatrix;
    defaultMatrix.setIdentity();
    vkCmdPushConstants(
        GSwapchain.commandBuffers[GSwapchain.current],
        GGraphicsLayout.handle, VK_SHADER_STAGE_VERTEX_BIT,
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
        GSwapchain.commandBuffers[GSwapchain.current],
        GGraphicsLayout.handle, VK_SHADER_STAGE_FRAGMENT_BIT,
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
    renderPassInfo.renderPass = GSwapchain.renderPass;
    renderPassInfo.framebuffer = GSwapchain.framebuffers[frameIndex];
    renderPassInfo.renderArea.offset.x = 0;
    renderPassInfo.renderArea.offset.y = 0;
    renderPassInfo.renderArea.extent.width = GSwapchain.extent.width;
    renderPassInfo.renderArea.extent.height = GSwapchain.extent.height;
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = clearValues;

    vkCmdBeginRenderPass(
        GSwapchain.commandBuffers[GSwapchain.current],
        &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE
    );

    // Set viewport
    VkViewport viewport;
    viewport.x = 0.0f;
    viewport.y = GSwapchain.extent.height*1.0f;
    viewport.width = GSwapchain.extent.width*1.0f;
    viewport.height = GSwapchain.extent.height*-1.0f;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    vkCmdSetViewport(
        GSwapchain.commandBuffers[GSwapchain.current], 0, 1, &viewport
    );

    // Set scissor
    VkRect2D scissor;
    scissor.offset.x = 0;
    scissor.offset.y = 0;
    scissor.extent.width = GSwapchain.extent.width;
    scissor.extent.height = GSwapchain.extent.height;

    vkCmdSetScissor(
        GSwapchain.commandBuffers[GSwapchain.current], 0, 1, &scissor
    );

    // Push default model matrix into command buffer
    Matrix4x4 defaultMatrix;
    defaultMatrix.setIdentity();
    vkCmdPushConstants(
        GSwapchain.commandBuffers[GSwapchain.current],
        GGraphicsLayout.handle, VK_SHADER_STAGE_VERTEX_BIT,
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
        GSwapchain.commandBuffers[GSwapchain.current],
        GGraphicsLayout.handle, VK_SHADER_STAGE_FRAGMENT_BIT,
        PushConstantDataOffset, PushConstantDataSize, &pushConstants
    );
}

////////////////////////////////////////////////////////////////////////////////
//  Wait renderer device for idle state                                       //
//  return : True if the renderer device is in idle state                     //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::waitDeviceIdle()
{
    // Check Vulkan device
    if (!GVulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Wait for renderer device idle
    if (vkDeviceWaitIdle(GVulkanDevice) == VK_SUCCESS)
    {
        // Renderer device is in idle state
        return true;
    }

    // Could not wait for renderer device idle state
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy renderer                                                          //
////////////////////////////////////////////////////////////////////////////////
void Renderer::destroyRenderer()
{
    ready = false;

    // Check Vulkan device
    if (!GVulkanDevice)
    {
        // Invalid Vulkan device
        return;
    }

    // Destroy default view
    view.destroyView();

    // Destroy world light
    GWorldLight.destroyWorldLight();

    // Destroy pipeplines
    if (pipelines)
    {
        for (int i = 0; i < RENDERER_PIPELINE_PIPELINESCOUNT; ++i)
        {
            pipelines[i].destroyPipeline();
        }
    }
    pipelines = 0;

    // Destroy main renderer
    GMainRenderer.destroyBackRenderer();

    // Destroy compute layout
    GComputeLayout.destroyLayout();

    // Destroy graphics layout
    GGraphicsLayout.destroyLayout();

    // Destroy uniformchain
    GUniformchain.destroyUniformchain();

    // Destroy swapchain
    GSwapchain.destroySwapchain();

    // Destroy Vulkan memory
    GVulkanMemory.destroyVulkanMemory();

    // Destroy Vulkan device
    if (GVulkanDevice)
    {
        vkDestroyDevice(GVulkanDevice, SYSVKMEMORY_DEVICE_ALLOC);
    }
    GVulkanDevice = 0;

    // Destroy Vulkan surface
    if (GVulkanInstance && GVulkanSurface)
    {
        vkDestroySurfaceKHR(
            GVulkanInstance, GVulkanSurface, SYSVKMEMORY_SURFACE_ALLOC
        );
    }
    GVulkanSurface = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Bind renderer vertex buffer                                               //
////////////////////////////////////////////////////////////////////////////////
void Renderer::bindVertexBuffer(MeshesAssets meshAsset)
{
    // Bind default vertex buffer
    VkDeviceSize offset = 0;
    vkCmdBindVertexBuffers(
        GSwapchain.commandBuffers[GSwapchain.current],
        0, 1, &GResources.meshes.mesh(meshAsset).vertexBuffer.handle,
        &offset
    );

    vkCmdBindIndexBuffer(
        GSwapchain.commandBuffers[GSwapchain.current],
        GResources.meshes.mesh(meshAsset).indexBuffer.handle,
        0, VK_INDEX_TYPE_UINT16
    );
}


////////////////////////////////////////////////////////////////////////////////
//  Create Vulkan instance                                                    //
//  return : True if Vulkan instance is successfully created                  //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::createVulkanInstance()
{
    // Check current Vulkan instance
    if (GVulkanInstance)
    {
        // Vulkan instance already created
        GSysMessage << "[0x3005] Vulkan instance already created\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Enumerate Vulkan extensions properties
    uint32_t extCount = 0;
    if (vkEnumerateInstanceExtensionProperties(0, &extCount, 0) != VK_SUCCESS)
    {
        // Could not enumerate Vulkan extensions properties
        GSysMessage << "[0x3006] Could not enumerate extensions\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Get Vulkan extensions properties
    VkExtensionProperties* extProperties =
        GSysMemory.alloc<VkExtensionProperties>(extCount, SYSMEMORY_RENDERER);
    if (!extProperties) { return false; }
    for (uint32_t i = 0; i < extCount; ++i)
    {
        extProperties[i] = VkExtensionProperties();
    }
    if (vkEnumerateInstanceExtensionProperties(
        0, &extCount, extProperties) != VK_SUCCESS)
    {
        // Could not get Vulkan extensions properties
        GSysMessage << "[0x3007] Could not get extensions properties\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Check Vulkan extensions properties
    bool allExtFound = true;
    for (size_t i = 0; i < VulkanExtensionsSize; ++i)
    {
        bool extFound = false;
        for (size_t j = 0; j < extCount; ++j)
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
        GSysMessage << "[0x3008] Required extensions are not supported\n";
        GSysMessage << "Please update your graphics drivers";
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
    if (vkCreateInstance(&createInfos,
        SYSVKMEMORY_INSTANCE_ALLOC, &GVulkanInstance) != VK_SUCCESS)
    {
        // Could not create Vulkan instance
        GSysMessage << "[0x3009] Could not create Vulkan instance\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }
    if (!GVulkanInstance)
    {
        // Could not create Vulkan instance
        GSysMessage << "[0x300A] Could not create Vulkan instance\n";
        GSysMessage << "Please update your graphics drivers";
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
    if (!GVulkanInstance)
    {
        // Invalid Vulkan instance
        GSysMessage << "[0x300E] Invalid Vulkan instance\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Check Vulkan surface
    if (!GVulkanSurface)
    {
        // Invalid Vulkan surface
        GSysMessage << "[0x300F] Invalid Vulkan surface\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Check physical device
    if (GPhysicalDevice)
    {
        // Physical device already selected
        GSysMessage << "[0x3010] Physical device already selected\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Check Vulkan device
    if (GVulkanDevice)
    {
        // Vulkan device already selected
        GSysMessage << "[0x3011] Vulkan device already selected\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // List devices
    uint32_t devicesCounts = 0;
    if (vkEnumeratePhysicalDevices(
        GVulkanInstance, &devicesCounts, 0) != VK_SUCCESS)
    {
        // Could not enumerate physical devices
        GSysMessage << "[0x3012] Could not enumerate physical devices\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }
    if (devicesCounts <= 0)
    {
        // No physical device found
        GSysMessage << "[0x3013] No physical device found\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Get physical devices list
    VkPhysicalDevice* physicalDevices =
        GSysMemory.alloc<VkPhysicalDevice>(devicesCounts, SYSMEMORY_RENDERER);
    if (!physicalDevices) { return false; }
    for (uint32_t i = 0; i < devicesCounts; ++i)
    {
        physicalDevices[i] = VkPhysicalDevice();
    }
    if (vkEnumeratePhysicalDevices(
        GVulkanInstance, &devicesCounts, physicalDevices) != VK_SUCCESS)
    {
        // Could not get physical devices list
        GSysMessage << "[0x3014] Could not get physical devices list\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Select a physical device with matching extensions properties
    bool deviceFound = false;
    uint32_t deviceIndex = 0;
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
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
        VkExtensionProperties* extProperties =
            GSysMemory.alloc<VkExtensionProperties>(
                extCount, SYSMEMORY_RENDERER
            );
        if (!extProperties) { return false; }
        for (uint32_t j = 0; j < extCount; ++j)
        {
            extProperties[j] = VkExtensionProperties();
        }
        if (vkEnumerateDeviceExtensionProperties(physicalDevices[i], 0,
            &extCount, extProperties) != VK_SUCCESS)
        {
            // Could not get extensions properties list
            continue;
        }

        // Check device extensions properties
        bool allExtFound = true;
        for (size_t j = 0; j < VulkanDeviceExtensionsSize; ++j)
        {
            bool extFound = false;
            for (size_t k = 0; k < extCount; ++k)
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
        deviceProperties.apiVersion = 0;
        deviceFeatures.robustBufferAccess = VK_FALSE;
        deviceFeatures.fullDrawIndexUint32 = VK_FALSE;
        deviceFeatures.imageCubeArray = VK_FALSE;
        deviceFeatures.independentBlend = VK_FALSE;
        deviceFeatures.geometryShader = VK_FALSE;
        deviceFeatures.tessellationShader = VK_FALSE;
        deviceFeatures.sampleRateShading = VK_FALSE;
        deviceFeatures.dualSrcBlend = VK_FALSE;
        deviceFeatures.logicOp = VK_FALSE;
        deviceFeatures.multiDrawIndirect = VK_FALSE;
        deviceFeatures.drawIndirectFirstInstance = VK_FALSE;
        deviceFeatures.depthClamp = VK_FALSE;
        deviceFeatures.depthBiasClamp = VK_FALSE;
        deviceFeatures.fillModeNonSolid = VK_FALSE;
        deviceFeatures.depthBounds = VK_FALSE;
        deviceFeatures.wideLines = VK_FALSE;
        deviceFeatures.largePoints = VK_FALSE;
        deviceFeatures.alphaToOne = VK_FALSE;
        deviceFeatures.multiViewport = VK_FALSE;
        deviceFeatures.samplerAnisotropy = VK_FALSE;
        deviceFeatures.textureCompressionETC2 = VK_FALSE;
        deviceFeatures.textureCompressionASTC_LDR = VK_FALSE;
        deviceFeatures.textureCompressionBC = VK_FALSE;
        deviceFeatures.occlusionQueryPrecise = VK_FALSE;
        deviceFeatures.pipelineStatisticsQuery = VK_FALSE;
        deviceFeatures.vertexPipelineStoresAndAtomics = VK_FALSE;
        deviceFeatures.fragmentStoresAndAtomics = VK_FALSE;
        deviceFeatures.shaderTessellationAndGeometryPointSize = VK_FALSE;
        deviceFeatures.shaderImageGatherExtended = VK_FALSE;
        deviceFeatures.shaderStorageImageExtendedFormats = VK_FALSE;
        deviceFeatures.shaderStorageImageMultisample = VK_FALSE;
        deviceFeatures.shaderStorageImageReadWithoutFormat = VK_FALSE;
        deviceFeatures.shaderStorageImageWriteWithoutFormat = VK_FALSE;
        deviceFeatures.shaderUniformBufferArrayDynamicIndexing = VK_FALSE;
        deviceFeatures.shaderSampledImageArrayDynamicIndexing = VK_FALSE;
        deviceFeatures.shaderStorageBufferArrayDynamicIndexing = VK_FALSE;
        deviceFeatures.shaderStorageImageArrayDynamicIndexing = VK_FALSE;
        deviceFeatures.shaderClipDistance = VK_FALSE;
        deviceFeatures.shaderCullDistance = VK_FALSE;
        deviceFeatures.shaderFloat64 = VK_FALSE;
        deviceFeatures.shaderInt64 = VK_FALSE;
        deviceFeatures.shaderInt16 = VK_FALSE;
        deviceFeatures.shaderResourceResidency = VK_FALSE;
        deviceFeatures.shaderResourceMinLod = VK_FALSE;
        deviceFeatures.sparseBinding = VK_FALSE;
        deviceFeatures.sparseResidencyBuffer = VK_FALSE;
        deviceFeatures.sparseResidencyImage2D = VK_FALSE;
        deviceFeatures.sparseResidencyImage3D = VK_FALSE;
        deviceFeatures.sparseResidency2Samples = VK_FALSE;
        deviceFeatures.sparseResidency4Samples = VK_FALSE;
        deviceFeatures.sparseResidency8Samples = VK_FALSE;
        deviceFeatures.sparseResidency16Samples = VK_FALSE;
        deviceFeatures.sparseResidencyAliased = VK_FALSE;
        deviceFeatures.variableMultisampleRate = VK_FALSE;
        deviceFeatures.inheritedQueries = VK_FALSE;
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

        // Check for internal RGBA32 format support
        VkFormatProperties formatProperties;
        formatProperties.linearTilingFeatures = 0;
        formatProperties.optimalTilingFeatures = 0;
        formatProperties.bufferFeatures = 0;
        vkGetPhysicalDeviceFormatProperties(
            physicalDevices[i], VK_FORMAT_R8G8B8A8_UNORM, &formatProperties
        );

        // Check optimal tiling features
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
            // Color attachment blend RGBA32 is not supported by the device
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
        if (!(formatProperties.optimalTilingFeatures &
            VK_FORMAT_FEATURE_BLIT_SRC_BIT))
        {
            // Blit source RGBA32 is not supported by the device
            continue;
        }
        if (!(formatProperties.optimalTilingFeatures &
            VK_FORMAT_FEATURE_BLIT_DST_BIT))
        {
            // Blit destination RGBA32 is not supported by the device
            continue;
        }

        // Get device queue families
        if (VulkanQueue::getDeviceQueues(physicalDevices[i]))
        {
            // Current device supports graphics, compute, transfer, and surface
            deviceIndex = i;
            deviceFound = true;
            break;
        }
    }

    // Check if a suitable device has been found
    if (!deviceFound)
    {
        // Could not find a device with graphics, surface, and transfer queues
        GSysMessage << "[0x3017] Could not find a suitable device\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Set physical device global instance
    GPhysicalDevice = physicalDevices[deviceIndex];
    if (!GPhysicalDevice)
    {
        // Invalid physical device
        GSysMessage << "[0x3018] Invalid physical device\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Adjust system settings
    GSysSettings.adjustSettings(deviceProperties, deviceFeatures);

    // Set queue priorities
    float queuePriorities[1];
    queuePriorities[0] = 1.0f;

    // Set graphics queues create infos
    VkDeviceQueueCreateInfo queueInfos[1];
    queueInfos[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueInfos[0].pNext = 0;
    queueInfos[0].flags = 0;
    queueInfos[0].queueFamilyIndex = 0/*GVulkanQueues.graphicsQueueFamily*/;
    queueInfos[0].queueCount = 1;
    queueInfos[0].pQueuePriorities = queuePriorities;

    // Set device features to enable
    VkPhysicalDeviceFeatures enableDeviceFeatures;
    enableDeviceFeatures.robustBufferAccess = VK_FALSE;
    enableDeviceFeatures.fullDrawIndexUint32 = VK_FALSE;
    enableDeviceFeatures.imageCubeArray = VK_FALSE;
    enableDeviceFeatures.independentBlend = VK_FALSE;
    enableDeviceFeatures.geometryShader = VK_FALSE;
    enableDeviceFeatures.tessellationShader = VK_FALSE;
    enableDeviceFeatures.sampleRateShading = VK_FALSE;
    if (GSysSettings.getSampleShadingMode() > SAMPLE_SHADING_NONE)
    {
        enableDeviceFeatures.sampleRateShading = VK_TRUE;
    }
    enableDeviceFeatures.dualSrcBlend = VK_FALSE;
    enableDeviceFeatures.logicOp = VK_FALSE;
    enableDeviceFeatures.multiDrawIndirect = VK_FALSE;
    enableDeviceFeatures.drawIndirectFirstInstance = VK_FALSE;
    enableDeviceFeatures.depthClamp = VK_FALSE;
    enableDeviceFeatures.depthBiasClamp = VK_FALSE;
    enableDeviceFeatures.fillModeNonSolid = VK_FALSE;
    enableDeviceFeatures.depthBounds = VK_FALSE;
    enableDeviceFeatures.wideLines = VK_FALSE;
    enableDeviceFeatures.largePoints = VK_FALSE;
    enableDeviceFeatures.alphaToOne = VK_FALSE;
    enableDeviceFeatures.multiViewport = VK_FALSE;
    enableDeviceFeatures.samplerAnisotropy = VK_FALSE;
    if (GSysSettings.getAnisotropicFilteringMode() >
        ANISOTROPIC_FILTERING_NONE)
    {
        enableDeviceFeatures.samplerAnisotropy = VK_TRUE;
    }
    enableDeviceFeatures.textureCompressionETC2 = VK_FALSE;
    enableDeviceFeatures.textureCompressionASTC_LDR = VK_FALSE;
    enableDeviceFeatures.textureCompressionBC = VK_FALSE;
    enableDeviceFeatures.occlusionQueryPrecise = VK_FALSE;
    enableDeviceFeatures.pipelineStatisticsQuery = VK_FALSE;
    enableDeviceFeatures.vertexPipelineStoresAndAtomics = VK_FALSE;
    enableDeviceFeatures.fragmentStoresAndAtomics = VK_FALSE;
    enableDeviceFeatures.shaderTessellationAndGeometryPointSize = VK_FALSE;
    enableDeviceFeatures.shaderImageGatherExtended = VK_FALSE;
    enableDeviceFeatures.shaderStorageImageExtendedFormats = VK_FALSE;
    enableDeviceFeatures.shaderStorageImageMultisample = VK_FALSE;
    if (GSysSettings.getMultiSamplingMode() > MULTI_SAMPLING_NONE)
    {
        enableDeviceFeatures.shaderStorageImageMultisample = VK_TRUE;
    }
    enableDeviceFeatures.shaderStorageImageReadWithoutFormat = VK_FALSE;
    enableDeviceFeatures.shaderStorageImageWriteWithoutFormat = VK_FALSE;
    enableDeviceFeatures.shaderUniformBufferArrayDynamicIndexing = VK_FALSE;
    enableDeviceFeatures.shaderSampledImageArrayDynamicIndexing = VK_FALSE;
    enableDeviceFeatures.shaderStorageBufferArrayDynamicIndexing = VK_FALSE;
    enableDeviceFeatures.shaderStorageImageArrayDynamicIndexing = VK_FALSE;
    enableDeviceFeatures.shaderClipDistance = VK_FALSE;
    enableDeviceFeatures.shaderCullDistance = VK_FALSE;
    enableDeviceFeatures.shaderFloat64 = VK_FALSE;
    enableDeviceFeatures.shaderInt64 = VK_FALSE;
    enableDeviceFeatures.shaderInt16 = VK_FALSE;
    enableDeviceFeatures.shaderResourceResidency = VK_FALSE;
    enableDeviceFeatures.shaderResourceMinLod = VK_FALSE;
    enableDeviceFeatures.sparseBinding = VK_FALSE;
    enableDeviceFeatures.sparseResidencyBuffer = VK_FALSE;
    enableDeviceFeatures.sparseResidencyImage2D = VK_FALSE;
    enableDeviceFeatures.sparseResidencyImage3D = VK_FALSE;
    enableDeviceFeatures.sparseResidency2Samples = VK_FALSE;
    enableDeviceFeatures.sparseResidency4Samples = VK_FALSE;
    enableDeviceFeatures.sparseResidency8Samples = VK_FALSE;
    enableDeviceFeatures.sparseResidency16Samples = VK_FALSE;
    enableDeviceFeatures.sparseResidencyAliased = VK_FALSE;
    enableDeviceFeatures.variableMultisampleRate = VK_FALSE;
    enableDeviceFeatures.inheritedQueries = VK_FALSE;

    // Create Vulkan device
    VkDeviceCreateInfo deviceInfos;
    deviceInfos.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceInfos.pNext = 0;
    deviceInfos.flags = 0;
    deviceInfos.queueCreateInfoCount = 1;
    deviceInfos.pQueueCreateInfos = queueInfos;
    deviceInfos.enabledLayerCount = 0;
    deviceInfos.ppEnabledLayerNames = 0;
    deviceInfos.enabledExtensionCount = VulkanDeviceExtensionsSize;
    deviceInfos.ppEnabledExtensionNames = VulkanDeviceExtensions;
    deviceInfos.pEnabledFeatures = &enableDeviceFeatures;

    if (vkCreateDevice(GPhysicalDevice, &deviceInfos,
        SYSVKMEMORY_DEVICE_ALLOC, &GVulkanDevice) != VK_SUCCESS)
    {
        // Could not create Vulkan device
        GSysMessage << "[0x3019] Could not create Vulkan device\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }
    if (!GVulkanDevice)
    {
        // Invalid Vulkan device
        GSysMessage << "[0x301A] Invalid Vulkan device\n";
        GSysMessage << "Please update your graphics drivers";
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
    ready = false;
    if (!waitDeviceIdle())
    {
        // Could not wait for device idle
        return false;
    }

    // Resize swapchain
    if (!GSwapchain.resizeSwapchain())
    {
        return false;
    }

    // Reset backchain memory
    GVulkanMemory.resetMemory(VULKAN_MEMORY_BACKCHAIN);

    // Resize main renderer
    if (!GMainRenderer.resize(VULKAN_MEMORY_BACKCHAIN,
        GSwapchain.extent.width, GSwapchain.extent.height))
    {
        return false;
    }

    // Wait for device idle
    if (!waitDeviceIdle())
    {
        // Could not wait for device idle
        return false;
    }

    // Renderer successfully resized
    ready = true;
    return true;
}
