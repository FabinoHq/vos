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
m_descriptorPool(0),
m_descriptorSetLayout(0),
m_pipelineLayout(0),
m_pipeline(0),
m_vertexBuffer(),
m_texture(),
m_shader()
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

    // Create descriptor pool
    if (!createDescriptorPool())
    {
        // Could not create descriptor pool
        SysMessage::box() << "[0x3044] Could not create descriptor pool\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Create descriptor set layout
    if (!createDescriptorSetLayout())
    {
        // Could not create descriptor set layout
        SysMessage::box() << "[0x3045] Could not create descriptor layout\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Create pipeline layout
    if (!createPipelineLayout())
    {
        // Could not create pipeline layout
        SysMessage::box() << "[0x3046] Could not create pipeline layout\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Create pipeline
    if (!createPipeline())
    {
        // Could not create pipeline
        SysMessage::box() << "[0x3047] Could not create pipeline\n";
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
    memcpy(uniformData.modelMatrix, modelMatrix.mat, sizeof(modelMatrix.mat));

    // Create uniform buffers
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        if (!m_uniformBuffers[i].updateBuffer(m_physicalDevice, m_vulkanDevice,
            m_vulkanMemory, m_transferCommandPool, m_transferQueue,
            &uniformData, sizeof(uniformData)))
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

    // Create descriptor sets
    if (!createDescriptorSets())
    {
        // Could not create descriptor sets
        SysMessage::box() << "[0x304B] Could not create descriptor sets\n";
        SysMessage::box() << "Please update your graphics drivers";
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
        VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline
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
        VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipelineLayout, 0, 1,
        &m_descriptorSets[m_swapchain.current], 0, 0
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

    Matrix4x4 modelMatrix;
    modelMatrix.setIdentity();

    // Copy matrices data into uniform data
    UniformData uniformData;
    memcpy(uniformData.projMatrix, projMatrix.mat, sizeof(projMatrix.mat));
    memcpy(uniformData.viewMatrix, viewMatrix.mat, sizeof(viewMatrix.mat));
    memcpy(uniformData.modelMatrix, modelMatrix.mat, sizeof(modelMatrix.mat));

    // Update uniform buffer
    if (!m_uniformBuffers[m_swapchain.current].updateBuffer(
        m_physicalDevice, m_vulkanDevice, m_vulkanMemory, m_transferCommandPool,
        m_transferQueue, &uniformData, sizeof(uniformData)))
    {
        // Could not update uniform buffer
        m_rendererReady = false;
        return;
    }

    // Draw vertices
    VkDeviceSize offset = 0;
    vkCmdBindVertexBuffers(
        m_swapchain.commandBuffers[m_swapchain.current],
        0, 1, &m_vertexBuffer.vertexBuffer.handle, &offset
    );

    vkCmdBindIndexBuffer(
        m_swapchain.commandBuffers[m_swapchain.current],
        m_vertexBuffer.indexBuffer.handle, 0, VK_INDEX_TYPE_UINT16
    );

    vkCmdDrawIndexed(
        m_swapchain.commandBuffers[m_swapchain.current], 6, 1, 0, 0, 0
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

        // Destroy graphics pipeline
        if (m_pipeline && vkDestroyPipeline)
        {
            vkDestroyPipeline(m_vulkanDevice, m_pipeline, 0);
        }

        // Destroy pipeline layout
        if (m_pipelineLayout && vkDestroyPipelineLayout)
        {
            vkDestroyPipelineLayout(m_vulkanDevice, m_pipelineLayout, 0);
        }

        // Destroy descriptor set layout
        if (m_descriptorSetLayout && vkDestroyDescriptorSetLayout)
        {
            vkDestroyDescriptorSetLayout(
                m_vulkanDevice, m_descriptorSetLayout, 0
            );
        }

        // Destroy descriptor pool
        if (m_descriptorPool && vkDestroyDescriptorPool)
        {
            vkDestroyDescriptorPool(m_vulkanDevice, m_descriptorPool, 0);
        }

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
    m_pipeline = 0;
    m_pipelineLayout = 0;
    m_descriptorSetLayout = 0;
    m_descriptorPool = 0;
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
//  Create descriptor pool                                                    //
//  return : True if descriptor pool is successfully created                  //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::createDescriptorPool()
{
    // Check Vulkan device
    if (!m_vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Create descriptor pool
    VkDescriptorPoolSize poolSize[2];

    poolSize[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSize[0].descriptorCount = RendererMaxSwapchainFrames;

    poolSize[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    poolSize[1].descriptorCount = RendererMaxSwapchainFrames;

    VkDescriptorPoolCreateInfo poolInfo;
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.pNext = 0;
    poolInfo.flags = 0;
    poolInfo.maxSets = RendererMaxSwapchainFrames;
    poolInfo.poolSizeCount = 2;
    poolInfo.pPoolSizes = poolSize;

    if (vkCreateDescriptorPool(
        m_vulkanDevice, &poolInfo, 0, &m_descriptorPool) != VK_SUCCESS)
    {
        // Could not create descriptor pool
        return false;
    }
    if (!m_descriptorPool)
    {
        // Invalid descriptor pool
        return false;
    }

    // Descriptor pool successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create descriptor set layout                                              //
//  return : True if descriptor layout is successfully created                //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::createDescriptorSetLayout()
{
    // Check Vulkan device
    if (!m_vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Create descriptor set layout
    VkDescriptorSetLayoutBinding descriptorSetBindings[2];

    descriptorSetBindings[0].binding = 0;
    descriptorSetBindings[0].descriptorType =
        VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorSetBindings[0].descriptorCount = 1;
    descriptorSetBindings[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    descriptorSetBindings[0].pImmutableSamplers = 0;

    descriptorSetBindings[1].binding = 1;
    descriptorSetBindings[1].descriptorType =
        VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptorSetBindings[1].descriptorCount = 1;
    descriptorSetBindings[1].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    descriptorSetBindings[1].pImmutableSamplers = 0;

    VkDescriptorSetLayoutCreateInfo descriptorSetInfo;
    descriptorSetInfo.sType =
        VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    descriptorSetInfo.pNext = 0;
    descriptorSetInfo.flags = 0;
    descriptorSetInfo.bindingCount = 2;
    descriptorSetInfo.pBindings = descriptorSetBindings;

    if (vkCreateDescriptorSetLayout(m_vulkanDevice,
        &descriptorSetInfo, 0, &m_descriptorSetLayout) != VK_SUCCESS)
    {
        // Could not create descriptor set layout
        return false;
    }
    if (!m_descriptorSetLayout)
    {
        // Invalid descriptor set layout
        return false;
    }

    // Descriptor set layout successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create pipeline layout                                                    //
//  return : True if pipeline layout is successfully created                  //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::createPipelineLayout()
{
    // Check Vulkan device
    if (!m_vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Check descriptor set layout
    if (!m_descriptorSetLayout)
    {
        // Invalid descriptor set layout
        return false;
    }

    // Create pipeline layout
    VkPipelineLayoutCreateInfo pipelineInfo;
    pipelineInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineInfo.pNext = 0;
    pipelineInfo.flags = 0;
    pipelineInfo.setLayoutCount = 1;
    pipelineInfo.pSetLayouts = &m_descriptorSetLayout;
    pipelineInfo.pushConstantRangeCount = 0;
    pipelineInfo.pPushConstantRanges = 0;

    if (vkCreatePipelineLayout(
        m_vulkanDevice, &pipelineInfo, 0, &m_pipelineLayout) != VK_SUCCESS)
    {
        // Could not create pipeline layout
        return false;
    }
    if (!m_pipelineLayout)
    {
        // Invalid pipeline layout
        return false;
    }

    // Pipeline layout successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create pipeline                                                           //
//  return : True if pipeline is successfully created                         //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::createPipeline()
{
    // Check Vulkan device
    if (!m_vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Check render pass
    if (!m_swapchain.renderPass)
    {
        // Invalid render pass
        return false;
    }

    // Check vertex shader
    if (!m_shader.vertexShader)
    {
        // Invalid vertex shader
        return false;
    }

    // Check fragment shader
    if (!m_shader.fragmentShader)
    {
        // Invalid fragment shader
        return false;
    }

    // Check pipeline layout
    if (!m_pipelineLayout)
    {
        // Invalid pipeline layout
        return false;
    }

    // Shader stage
    VkPipelineShaderStageCreateInfo shaderStage[2];

    shaderStage[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStage[0].pNext = 0;
    shaderStage[0].flags = 0;
    shaderStage[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
    shaderStage[0].module = m_shader.vertexShader;
    shaderStage[0].pName = "main";
    shaderStage[0].pSpecializationInfo = 0;

    shaderStage[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStage[1].pNext = 0;
    shaderStage[1].flags = 0;
    shaderStage[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    shaderStage[1].module = m_shader.fragmentShader;
    shaderStage[1].pName = "main";
    shaderStage[1].pSpecializationInfo = 0;

    // Input binding
    VkVertexInputBindingDescription vertexBinding;
    vertexBinding.binding = 0;
    vertexBinding.stride = sizeof(VertexData);
    vertexBinding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    // Vertex attribute
    VkVertexInputAttributeDescription vertexAttributes[2];

    vertexAttributes[0].location = 0;
    vertexAttributes[0].binding = vertexBinding.binding;
    vertexAttributes[0].format = VK_FORMAT_R32G32B32_SFLOAT;
    vertexAttributes[0].offset = 0;

    vertexAttributes[1].location = 1;
    vertexAttributes[1].binding = vertexBinding.binding;
    vertexAttributes[1].format = VK_FORMAT_R32G32_SFLOAT;
    vertexAttributes[1].offset = sizeof(float) * 3;

    // Vertex input
    VkPipelineVertexInputStateCreateInfo vertexInput;
    vertexInput.sType =
        VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInput.pNext = 0;
    vertexInput.flags = 0;
    vertexInput.vertexBindingDescriptionCount = 1;
    vertexInput.pVertexBindingDescriptions = &vertexBinding;
    vertexInput.vertexAttributeDescriptionCount = 2;
    vertexInput.pVertexAttributeDescriptions = vertexAttributes;

    // Input assembly
    VkPipelineInputAssemblyStateCreateInfo inputAssembly;
    inputAssembly.sType =
        VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.pNext = 0;
    inputAssembly.flags = 0;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    // Viewport
    VkPipelineViewportStateCreateInfo viewportInfo;
    viewportInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportInfo.pNext = 0;
    viewportInfo.flags = 0;
    viewportInfo.viewportCount = 1;
    viewportInfo.pViewports = 0;
    viewportInfo.scissorCount = 1;
    viewportInfo.pScissors = 0;

    // Rasterizer
    VkPipelineRasterizationStateCreateInfo rasterizerInfo;
    rasterizerInfo.sType =
        VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizerInfo.pNext = 0;
    rasterizerInfo.flags = 0;
    rasterizerInfo.depthClampEnable = VK_FALSE;
    rasterizerInfo.rasterizerDiscardEnable = VK_FALSE;
    rasterizerInfo.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizerInfo.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizerInfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rasterizerInfo.depthBiasEnable = VK_FALSE;
    rasterizerInfo.depthBiasConstantFactor = 0.0f;
    rasterizerInfo.depthBiasClamp = 0.0f;
    rasterizerInfo.depthBiasSlopeFactor = 0.0f;
    rasterizerInfo.lineWidth = 1.0f;

    // Multisample
    VkPipelineMultisampleStateCreateInfo multisampleInfo;
    multisampleInfo.sType =
        VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampleInfo.pNext = 0;
    multisampleInfo.flags = 0;
    multisampleInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisampleInfo.sampleShadingEnable = VK_FALSE;
    multisampleInfo.minSampleShading = 1.0f;
    multisampleInfo.pSampleMask = 0;
    multisampleInfo.alphaToCoverageEnable = VK_FALSE;
    multisampleInfo.alphaToOneEnable = VK_FALSE;

    // Blend
    VkPipelineColorBlendAttachmentState colorBlend;
    colorBlend.blendEnable = VK_FALSE;
    colorBlend.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlend.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorBlend.colorBlendOp = VK_BLEND_OP_ADD;
    colorBlend.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlend.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorBlend.alphaBlendOp = VK_BLEND_OP_ADD;
    colorBlend.colorWriteMask =
        VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
        VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

    VkPipelineColorBlendStateCreateInfo blendState;
    blendState.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    blendState.pNext = 0;
    blendState.flags = 0;
    blendState.logicOpEnable = VK_FALSE;
    blendState.logicOp = VK_LOGIC_OP_COPY;
    blendState.attachmentCount = 1;
    blendState.pAttachments = &colorBlend;
    blendState.blendConstants[0] = 0.0f;
    blendState.blendConstants[1] = 0.0f;
    blendState.blendConstants[2] = 0.0f;
    blendState.blendConstants[3] = 0.0f;

    // Dynamic states
    VkDynamicState dynamicStates[2];
    dynamicStates[0] = VK_DYNAMIC_STATE_VIEWPORT;
    dynamicStates[1] = VK_DYNAMIC_STATE_SCISSOR;

    VkPipelineDynamicStateCreateInfo dynamicInfo;
    dynamicInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicInfo.pNext = 0;
    dynamicInfo.flags = 0;
    dynamicInfo.dynamicStateCount = 2;
    dynamicInfo.pDynamicStates = dynamicStates;

    // Create pipeline
    VkGraphicsPipelineCreateInfo pipelineInfo;
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.pNext = 0;
    pipelineInfo.flags = 0;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStage;
    pipelineInfo.pVertexInputState = &vertexInput;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pTessellationState = 0;
    pipelineInfo.pViewportState = &viewportInfo;
    pipelineInfo.pRasterizationState = &rasterizerInfo;
    pipelineInfo.pMultisampleState = &multisampleInfo;
    pipelineInfo.pDepthStencilState = 0;
    pipelineInfo.pColorBlendState = &blendState;
    pipelineInfo.pDynamicState = &dynamicInfo;
    pipelineInfo.layout = m_pipelineLayout;
    pipelineInfo.renderPass = m_swapchain.renderPass;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = 0;
    pipelineInfo.basePipelineIndex = -1;

    if (vkCreateGraphicsPipelines(
        m_vulkanDevice, 0, 1, &pipelineInfo, 0, &m_pipeline) != VK_SUCCESS)
    {
        // Could not create pipeline
        return false;
    }
    if (!m_pipeline)
    {
        // Invalid pipeline
        return false;
    }

    // Pipeline successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create descriptor sets                                                    //
//  return : True if descriptor sets are successfully created                 //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::createDescriptorSets()
{
    // Duplicate descriptor layout to match descriptor sets count
    VkDescriptorSetLayout layouts[RendererMaxSwapchainFrames];
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        layouts[i] = m_descriptorSetLayout;
    }

    // Create descriptor sets
    VkDescriptorSetAllocateInfo descriptorInfo;
    descriptorInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    descriptorInfo.pNext = 0;
    descriptorInfo.descriptorPool = m_descriptorPool;
    descriptorInfo.descriptorSetCount = RendererMaxSwapchainFrames;
    descriptorInfo.pSetLayouts = layouts;

    if (vkAllocateDescriptorSets(
        m_vulkanDevice, &descriptorInfo, m_descriptorSets) != VK_SUCCESS)
    {
        // Could not allocate descriptor sets
        return false;
    }

    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        // Update descriptor set
        VkDescriptorBufferInfo bufferInfo;
        bufferInfo.buffer = m_uniformBuffers[i].uniformBuffer.handle;
        bufferInfo.offset = 0;
        bufferInfo.range = m_uniformBuffers[i].uniformBuffer.size;

        VkDescriptorImageInfo imageInfo;
        imageInfo.sampler = m_texture.sampler;
        imageInfo.imageView = m_texture.view;
        imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

        VkWriteDescriptorSet descriptorWrites[2];

        descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[0].pNext = 0;
        descriptorWrites[0].dstSet = m_descriptorSets[i];
        descriptorWrites[0].dstBinding = 0;
        descriptorWrites[0].dstArrayElement = 0;
        descriptorWrites[0].descriptorCount = 1;
        descriptorWrites[0].descriptorType =
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrites[0].pImageInfo = 0;
        descriptorWrites[0].pBufferInfo = &bufferInfo;
        descriptorWrites[0].pTexelBufferView = 0;

        descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[1].pNext = 0;
        descriptorWrites[1].dstSet = m_descriptorSets[i];
        descriptorWrites[1].dstBinding = 1;
        descriptorWrites[1].dstArrayElement = 0;
        descriptorWrites[1].descriptorCount = 1;
        descriptorWrites[1].descriptorType =
            VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptorWrites[1].pImageInfo = &imageInfo;
        descriptorWrites[1].pBufferInfo = 0;
        descriptorWrites[1].pTexelBufferView = 0;

        vkUpdateDescriptorSets(m_vulkanDevice, 2, descriptorWrites, 0, 0);
    }

    // Descriptor sets successfully created
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
