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
//     Renderer/Renderer.cpp : Renderer management                            //
////////////////////////////////////////////////////////////////////////////////
#include "Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  Renderer default constructor                                              //
////////////////////////////////////////////////////////////////////////////////
Renderer::Renderer() :
m_rendererReady(false),
m_sysWindow(0),
m_vulkanLibHandle(0),
m_vulkanInstance(0),
m_vulkanSurface(0),
m_physicalDevice(0),
m_vulkanDevice(0),
m_graphicsQueue(),
m_surfaceQueue(),
m_transferQueue(),
m_transferCommandPool(0),
m_vulkanMemory(),
m_swapchain(),
m_vertexBuffer(),
m_texture(),
m_shader(),
m_pipeline(),
m_sprite()
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
        SysMessage::box() << "[0x301C] Could not load device functions\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Init Vulkan memory
    if (!m_vulkanMemory.init(m_physicalDevice, m_vulkanDevice))
    {
        return false;
    }

    // Request graphics queue handle
    if (!m_graphicsQueue.createVulkanQueue(m_vulkanDevice))
    {
        // Could not get graphics queue handle
        return false;
    }

    // Request surface queue handle
    if (!m_surfaceQueue.createVulkanQueue(m_vulkanDevice))
    {
        // Could not get surface queue handle
        return false;
    }

    // Request transfer queue handle
    if (!m_transferQueue.createVulkanQueue(m_vulkanDevice))
    {
        // Could not get surface queue handle
        return false;
    }

    // Create Vulkan swapchain
    if (!m_swapchain.createSwapchain(m_physicalDevice,
        m_vulkanDevice, m_vulkanSurface, m_surfaceQueue.index))
    {
        // Could not create Vulkan swapchain
        return false;
    }

    // Create transfer commands pool
    VkCommandPoolCreateInfo commandPoolInfo;
    commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolInfo.pNext = 0;
    commandPoolInfo.flags =
        VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT |
        VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
    commandPoolInfo.queueFamilyIndex = m_transferQueue.index;

    if (vkCreateCommandPool(m_vulkanDevice,
        &commandPoolInfo, 0, &m_transferCommandPool) != VK_SUCCESS)
    {
        // Could not create transfer commands pool
        SysMessage::box() << "[0x3041] Could not create commands pool\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }
    if (!m_transferCommandPool)
    {
        // Invalid transfer commands pool
        SysMessage::box() << "[0x3042] Invalid transfer commands pool\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Create default shaders
    if (!m_shader.createShader(m_vulkanDevice,
        DefaultVertexShader, DefaultVertexShaderSize,
        DefaultFragmentShader, DefaultFragmentShaderSize))
    {
        // Could not create default shaders
        SysMessage::box() << "[0x3043] Could not create default shaders\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Create default pipeline
    if (!m_pipeline.createPipeline(m_vulkanDevice, m_swapchain, m_shader))
    {
        // Could not create default pipeline
        SysMessage::box() << "[0x3047] Could not create default pipeline\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Create vertex buffer
    if (!m_vertexBuffer.createBuffer(m_physicalDevice, m_vulkanDevice,
        m_vulkanMemory, m_transferCommandPool, m_transferQueue))
    {
        // Could not create vertex buffer
        SysMessage::box() << "[0x3048] Could not create vertex buffer\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Set default matrices
    Matrix4x4 projMatrix;
    projMatrix.setOrthographic(-1.0f, 1.0f, 1.0f, -1.0f, -2.0f, 2.0f);
    projMatrix.translateZ(-1.0f);

    Matrix4x4 viewMatrix;
    viewMatrix.setIdentity();

    Matrix4x4 modelMatrix;
    modelMatrix.setIdentity();

    // Copy matrices data into uniform data
    UniformData uniformData;
    memcpy(uniformData.projMatrix, projMatrix.mat, sizeof(projMatrix.mat));
    memcpy(uniformData.viewMatrix, viewMatrix.mat, sizeof(viewMatrix.mat));

    // Create uniform buffers
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        if (!m_uniformBuffers[i].updateBuffer(m_physicalDevice,
            m_vulkanDevice, m_vulkanMemory, m_transferCommandPool,
            m_transferQueue, &uniformData, sizeof(uniformData)))
        {
            // Could not create uniform buffer
            SysMessage::box() << "[0x3049] Could not create uniform buffer\n";
            SysMessage::box() << "Please update your graphics drivers";
            return false;
        }
    }

    // Load texture
    if (!m_texture.updateTexture(m_physicalDevice, m_vulkanDevice,
        m_vulkanMemory, m_swapchain.commandsPool, m_graphicsQueue,
        TestSpriteWidth, TestSpriteHeight, TestSpriteDepth, TestSprite))
    {
        // Could not load texture
        SysMessage::box() << "[0x304A] Could not load texture\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Init test sprite
    if (!m_sprite.init(
        m_vulkanDevice, m_pipeline, m_uniformBuffers, m_texture, 1.0f, 1.0f))
    {
        return false;
    }

    // Renderer successfully loaded
    m_rendererReady = true;
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Render frame                                                              //
////////////////////////////////////////////////////////////////////////////////
void Renderer::render()
{
    // Check renderer state
    if (!m_rendererReady)
    {
        // Resize renderer
        if (!resize())
        {
            // Could not resize renderer
            return;
        }
        return;
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
        return;
    }

    // Acquire current frame
    uint32_t frameIndex = 0;
    if (vkAcquireNextImageKHR(m_vulkanDevice, m_swapchain.handle,
        UINT64_MAX, m_swapchain.renderReady[m_swapchain.current],
        0, &frameIndex) != VK_SUCCESS)
    {
        // Could not acquire swapchain frame
        m_rendererReady = false;
        return;
    }

    // Check current frame index
    if (frameIndex >= m_swapchain.frames)
    {
        // Invalid swapchain frame index
        m_rendererReady = false;
        return;
    }


    // Command buffer begin
    VkCommandBufferBeginInfo commandBegin;
    commandBegin.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    commandBegin.pNext = 0;
    commandBegin.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    commandBegin.pInheritanceInfo = 0;

    // Image subresource
    VkImageSubresourceRange subresource;
    subresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    subresource.baseMipLevel = 0;
    subresource.levelCount = 1;
    subresource.baseArrayLayer = 0;
    subresource.layerCount = 1;

    // Record command buffers
    VkImageMemoryBarrier presentToDraw;
    presentToDraw.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    presentToDraw.pNext = 0;
    presentToDraw.srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
    presentToDraw.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    presentToDraw.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    presentToDraw.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    presentToDraw.srcQueueFamilyIndex = m_surfaceQueue.index;
    presentToDraw.dstQueueFamilyIndex = m_graphicsQueue.index;
    presentToDraw.image = m_swapchain.images[frameIndex];
    presentToDraw.subresourceRange = subresource;

    VkImageMemoryBarrier drawToPresent;
    drawToPresent.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    drawToPresent.pNext = 0;
    drawToPresent.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    drawToPresent.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
    drawToPresent.oldLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    drawToPresent.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    drawToPresent.srcQueueFamilyIndex = m_graphicsQueue.index;
    drawToPresent.dstQueueFamilyIndex = m_surfaceQueue.index;
    drawToPresent.image = m_swapchain.images[frameIndex];
    drawToPresent.subresourceRange = subresource;

    VkRenderPassBeginInfo renderPassInfo;
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.pNext = 0;
    renderPassInfo.renderPass = m_swapchain.renderPass;
    renderPassInfo.framebuffer = m_swapchain.framebuffers[frameIndex];
    renderPassInfo.renderArea.offset.x = 0;
    renderPassInfo.renderArea.offset.y = 0;
    renderPassInfo.renderArea.extent.width = m_swapchain.extent.width;
    renderPassInfo.renderArea.extent.height = m_swapchain.extent.height;
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &RendererClearColor;

    // Begin command buffer
    if (vkBeginCommandBuffer(m_swapchain.commandBuffers[m_swapchain.current],
        &commandBegin) != VK_SUCCESS)
    {
        // Could not begin command buffer
        m_rendererReady = false;
        return;
    }
    
    vkCmdPipelineBarrier(
        m_swapchain.commandBuffers[m_swapchain.current],
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        0, 0, 0, 0, 0, 1, &presentToDraw
    );

    // Begin render pass
    vkCmdBeginRenderPass(
        m_swapchain.commandBuffers[m_swapchain.current],
        &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE
    );

    vkCmdBindPipeline(
        m_swapchain.commandBuffers[m_swapchain.current],
        VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline.handle
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

    // Bind descriptor set
    vkCmdBindDescriptorSets(
        m_swapchain.commandBuffers[m_swapchain.current],
        VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline.layout, 0, 1,
        &m_sprite.m_descriptorSets[m_swapchain.current], 0, 0
    );

    // Update matrices
    float ratio = 1.0f;
    if ((m_swapchain.extent.width > 0) && (m_swapchain.extent.height > 0))
    {
        ratio = (m_swapchain.extent.width*1.0f) /
            (m_swapchain.extent.height*1.0f);
    }
    Matrix4x4 projMatrix;
    projMatrix.setOrthographic(-ratio, ratio, 1.0f, -1.0f, -2.0f, 2.0f);
    projMatrix.translateZ(-1.0f);

    Matrix4x4 viewMatrix;
    viewMatrix.setIdentity();

    // Copy matrices data into uniform data
    UniformData uniformData;
    memcpy(uniformData.projMatrix, projMatrix.mat, sizeof(projMatrix.mat));
    memcpy(uniformData.viewMatrix, viewMatrix.mat, sizeof(viewMatrix.mat));

    // Update uniform buffer
    if (!m_uniformBuffers[m_swapchain.current].updateBuffer(
        m_physicalDevice, m_vulkanDevice, m_vulkanMemory, m_transferCommandPool,
        m_transferQueue, &uniformData, sizeof(uniformData)))
    {
        // Could not update uniform buffer
        m_rendererReady = false;
        return;
    }

    // Bind vertices
    VkDeviceSize offset = 0;
    vkCmdBindVertexBuffers(
        m_swapchain.commandBuffers[m_swapchain.current],
        0, 1, &m_vertexBuffer.vertexBuffer.handle, &offset
    );

    vkCmdBindIndexBuffer(
        m_swapchain.commandBuffers[m_swapchain.current],
        m_vertexBuffer.indexBuffer.handle, 0, VK_INDEX_TYPE_UINT16
    );

    // Render test sprite
    m_sprite.setSize(ratio*2.0f, 2.0f);
    m_sprite.setPosition(-ratio, -1.0f);
    m_sprite.render(
        m_swapchain.commandBuffers[m_swapchain.current], m_pipeline
    );

    // End render pass
    vkCmdEndRenderPass(m_swapchain.commandBuffers[m_swapchain.current]);

    vkCmdPipelineBarrier(
        m_swapchain.commandBuffers[m_swapchain.current],
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
        0, 0, 0, 0, 0, 1, &drawToPresent
    );

    // End command buffer
    if (vkEndCommandBuffer(
        m_swapchain.commandBuffers[m_swapchain.current]) != VK_SUCCESS)
    {
        // Could not end command buffer
        m_rendererReady = false;
        return;
    }

    // Reset current frame rendering fence
    if (vkResetFences(m_vulkanDevice, 1,
        &m_swapchain.fences[m_swapchain.current]) != VK_SUCCESS)
    {
        // Could not reset fence
        m_rendererReady = false;
        return;
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
    submitInfo.pSignalSemaphores =
        &m_swapchain.renderFinished[m_swapchain.current];

    if (vkQueueSubmit(m_surfaceQueue.handle, 1, &submitInfo,
        m_swapchain.fences[m_swapchain.current]) != VK_SUCCESS)
    {
        m_rendererReady = false;
        return;
    }

    // Update surface when queue has finished rendering
    VkPresentInfoKHR present;
    present.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    present.pNext = 0;
    present.waitSemaphoreCount = 1;
    present.pWaitSemaphores = &m_swapchain.renderFinished[m_swapchain.current];
    present.swapchainCount = 1;
    present.pSwapchains = &m_swapchain.handle;
    present.pImageIndices = &frameIndex;
    present.pResults = 0;

    if (vkQueuePresentKHR(m_surfaceQueue.handle, &present) != VK_SUCCESS)
    {
        m_rendererReady = false;
        return;
    }

    // Next swapchain frame index
    ++m_swapchain.current;
    if (m_swapchain.current >= m_swapchain.frames)
    {
        m_swapchain.current = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Cleanup renderer                                                          //
////////////////////////////////////////////////////////////////////////////////
void Renderer::cleanup()
{
    m_rendererReady = false;

    // Destroy swapchain and device
    if (m_vulkanDevice)
    {
        // Destroy swapchain
        m_swapchain.destroySwapchain(m_vulkanDevice);

        // Destroy shader
        m_shader.destroyShader(m_vulkanDevice);

        // Destroy texture
        m_texture.destroyTexture(m_vulkanDevice, m_vulkanMemory);

        // Destroy uniform buffer
        for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
        {
            m_uniformBuffers[i].destroyBuffer(m_vulkanDevice, m_vulkanMemory);
        }

        // Destroy vertex buffer
        m_vertexBuffer.destroyBuffer(m_vulkanDevice, m_vulkanMemory);

        // Destroy transfer commands pool
        if (m_transferCommandPool && vkDestroyCommandPool)
        {
            vkDestroyCommandPool(m_vulkanDevice, m_transferCommandPool, 0);
        }

        // Destroy default pipeline
        m_pipeline.destroyPipeline(m_vulkanDevice);

        // Cleanup Vulkan memory
        m_vulkanMemory.cleanup(m_vulkanDevice);

        // Destroy Vulkan device
        if (vkDestroyDevice)
        {
            vkDestroyDevice(m_vulkanDevice, 0);
        }
    }

    // Destroy Vulkan surface
    if (m_vulkanInstance && m_vulkanSurface && vkDestroySurfaceKHR)
    {
        vkDestroySurfaceKHR(m_vulkanInstance, m_vulkanSurface, 0);
    }

    m_swapchain.handle = 0;
    m_vulkanDevice = 0;
    m_vulkanSurface = 0;
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
        if (VulkanQueue::getDeviceQueues(m_vulkanSurface, physicalDevices[i],
            m_graphicsQueue, m_surfaceQueue, m_transferQueue))
        {
            // Current device supports graphics, surface, and transfer queues
            deviceIndex = i;
            deviceFound = true;
            break;
        }
    }

    if (!deviceFound)
    {
        // Could not find a device with graphics, surface, and transfer queues
        return false;
    }

    m_physicalDevice = physicalDevices[deviceIndex];
    if (!m_physicalDevice)
    {
        // Invalid physical device
        SysMessage::box() << "[0x3019] Invalid physical device\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Set queue priorities
    std::vector<float> queuePriorities;
    queuePriorities.push_back(1.0f);

    // Set queue create infos
    std::vector<VkDeviceQueueCreateInfo> queueInfos;
    queueInfos.push_back(VkDeviceQueueCreateInfo());
    queueInfos.back().sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueInfos.back().pNext = 0;
    queueInfos.back().flags = 0;
    queueInfos.back().queueFamilyIndex = m_graphicsQueue.index;
    queueInfos.back().queueCount = static_cast<uint32_t>(
        queuePriorities.size()
    );
    queueInfos.back().pQueuePriorities = queuePriorities.data();

    // Add another queue if the surface queue is different
    if (m_surfaceQueue.index != m_graphicsQueue.index)
    {
        queueInfos.push_back(VkDeviceQueueCreateInfo());
        queueInfos.back().sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueInfos.back().pNext = 0;
        queueInfos.back().flags = 0;
        queueInfos.back().queueFamilyIndex = m_surfaceQueue.index;
        queueInfos.back().queueCount = static_cast<uint32_t>(
            queuePriorities.size()
        );
        queueInfos.back().pQueuePriorities = queuePriorities.data();
    }

    // Add another queue if the transfer queue is different
    if ((m_transferQueue.index != m_graphicsQueue.index) &&
        (m_transferQueue.index != m_surfaceQueue.index))
    {
        queueInfos.push_back(VkDeviceQueueCreateInfo());
        queueInfos.back().sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueInfos.back().pNext = 0;
        queueInfos.back().flags = 0;
        queueInfos.back().queueFamilyIndex = m_transferQueue.index;
        queueInfos.back().queueCount = static_cast<uint32_t>(
            queuePriorities.size()
        );
        queueInfos.back().pQueuePriorities = queuePriorities.data();
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
        SysMessage::box() << "[0x301A] Could not create Vulkan device\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }
    if (!m_vulkanDevice)
    {
        // Invalid Vulkan device
        SysMessage::box() << "[0x301B] Invalid Vulkan device\n";
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
    m_rendererReady = false;

    // Resize swapchain
    if (!m_swapchain.resizeSwapchain(
        m_physicalDevice, m_vulkanDevice, m_vulkanSurface))
    {
        return false;
    }

    // Renderer successfully resized
    m_rendererReady = true;
    return true;
}
