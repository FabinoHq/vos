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
m_graphicsQueueIndex(0),
m_graphicsQueueHandle(0),
m_surfaceQueueIndex(0),
m_surfaceQueueHandle(0),
m_swapchain(),
m_renderPass(0),
m_vertexShader(0),
m_fragmentShader(0),
m_pipelineLayout(0),
m_pipeline(0),
m_commandsPool(0),
m_vertexBuffer()
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

    // Check SysWindow pointer
    if (!sysWindow)
    {
        // Invalid SysWindow pointer
        return false;
    }
    m_sysWindow = sysWindow;

    // Load Vulkan library
    if (!LoadVulkanLibrary(m_vulkanLibHandle))
    {
        // Could not load Vulkan library
        return false;
    }

    // Load Vulkan GetInstance function
    if (!LoadVulkanGetInstance(m_vulkanLibHandle))
    {
        // Could not load Vulkan GetInstance function
        return false;
    }

    // Load Vulkan global functions
    if (!LoadVulkanGlobalFunctions())
    {
        // Could not load Vulkan global functions
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
        return false;
    }

    // Create Vulkan SystemSurface
    if (!CreateVulkanSystemSurface(
        m_vulkanInstance, *m_sysWindow, m_vulkanSurface))
    {
        // Could not create Vulkan SystemSurface
        return false;
    }

    // Load Vulkan instance functions
    if (!LoadVulkanInstanceFunctions(m_vulkanInstance))
    {
        // Could not load Vulkan instance functions
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
        return false;
    }

    // Get Vulkan queues handles
    if (!getQueuesHandles())
    {
        // Could not get Vulkan queues handles
        return false;
    }

    // Create Vulkan swapchain
    if (!createVulkanSwapchain())
    {
        // Could not create Vulkan swapchain
        return false;
    }

    // Create render pass
    if (!createRenderPass())
    {
        // Could not create render pass
        return false;
    }

    // Create framebuffers
    if (!createFramebuffers())
    {
        // Could not create framebuffers
        return false;
    }

    // Create default shaders
    if (!createDefaultShaders())
    {
        // Could not create default shaders
        return false;
    }

    // Create pipeline layout
    if (!createPipelineLayout())
    {
        // Could not create pipeline layout
        return false;
    }

    // Create pipeline
    if (!createPipeline())
    {
        // Could not create pipeline
        return false;
    }

    // Create vertex buffer
    if (!createVertexBuffer())
    {
        // Could not create vertex buffer
        return false;
    }

    // Create command buffers
    if (!createCommandBuffers())
    {
        // Could not create command buffers
        return false;
    }

    // Create semaphores
    if (!createSemaphores())
    {
        // Could not create semaphores
        return false;
    }

    // Create fences
    if (!createFences())
    {
        // Could not create fences
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

    // Wait for rendering fence
    if (vkWaitForFences(m_vulkanDevice, 1,
        &m_swapchain.fences[m_swapchain.current],
        VK_FALSE, RendererSwapchainFenceTimeout) != VK_SUCCESS)
    {
        // Rendering fence timed out
        m_rendererReady = false;
        return;
    }
    if (vkResetFences(m_vulkanDevice, 1,
        &m_swapchain.fences[m_swapchain.current]) != VK_SUCCESS)
    {
        // Could not reset fence
        m_rendererReady = false;
        return;
    }

    // Acquire next image
    uint32_t imageIndex = 0;
    if (vkAcquireNextImageKHR(m_vulkanDevice, m_swapchain.handle,
        UINT64_MAX, m_swapchain.imageAvailable[m_swapchain.current],
        0, &imageIndex) != VK_SUCCESS)
    {
        // Could not qcquire next swapchain image
        m_rendererReady = false;
        return;
    }

    // Check image index
    if ((imageIndex < 0) || (imageIndex >= m_swapchain.frames))
    {
        // Invalid swapchain image index
        m_rendererReady = false;
        return;
    }


    // Command buffer begin
    VkCommandBufferBeginInfo commandBegin;
    commandBegin.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    commandBegin.pNext = 0;
    commandBegin.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
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
    presentToDraw.srcQueueFamilyIndex = m_surfaceQueueIndex;
    presentToDraw.dstQueueFamilyIndex = m_graphicsQueueIndex;
    presentToDraw.image = m_swapchain.images[imageIndex].handle;
    presentToDraw.subresourceRange = subresource;

    VkImageMemoryBarrier drawToPresent;
    drawToPresent.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    drawToPresent.pNext = 0;
    drawToPresent.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    drawToPresent.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
    drawToPresent.oldLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    drawToPresent.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    drawToPresent.srcQueueFamilyIndex = m_graphicsQueueIndex;
    drawToPresent.dstQueueFamilyIndex = m_surfaceQueueIndex;
    drawToPresent.image = m_swapchain.images[imageIndex].handle;
    drawToPresent.subresourceRange = subresource;

    VkRenderPassBeginInfo renderPassInfo;
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.pNext = 0;
    renderPassInfo.renderPass = m_renderPass;
    renderPassInfo.framebuffer = m_swapchain.framebuffers[imageIndex];
    renderPassInfo.renderArea.offset.x = 0;
    renderPassInfo.renderArea.offset.y = 0;
    renderPassInfo.renderArea.extent.width = m_swapchain.extent.width;
    renderPassInfo.renderArea.extent.height = m_swapchain.extent.height;
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &RendererClearColor;

    // Begin command buffer
    if (vkBeginCommandBuffer(
        m_swapchain.commandBuffers[imageIndex], &commandBegin) != VK_SUCCESS)
    {
        // Could not begin command buffer
        m_rendererReady = false;
        return;
    }
    
    vkCmdPipelineBarrier(
        m_swapchain.commandBuffers[imageIndex],
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        0, 0, 0, 0, 0, 1, &presentToDraw
    );

    vkCmdBeginRenderPass(
        m_swapchain.commandBuffers[imageIndex],
        &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE
    );

    vkCmdBindPipeline(
        m_swapchain.commandBuffers[imageIndex],
        VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline
    );

    VkViewport viewport;
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = m_swapchain.extent.width*1.0f;
    viewport.height = m_swapchain.extent.height*1.0f;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    vkCmdSetViewport(m_swapchain.commandBuffers[imageIndex], 0, 1, &viewport);

    VkRect2D scissor;
    scissor.offset.x = 0;
    scissor.offset.y = 0;
    scissor.extent.width = m_swapchain.extent.width;
    scissor.extent.height = m_swapchain.extent.height;

    vkCmdSetScissor(m_swapchain.commandBuffers[imageIndex], 0, 1, &scissor);

    VkDeviceSize offset = 0;
    vkCmdBindVertexBuffers(
        m_swapchain.commandBuffers[imageIndex], 0, 1,
        &m_vertexBuffer.handle, &offset
    );

    vkCmdDraw(m_swapchain.commandBuffers[imageIndex], 4, 1, 0, 0);

    vkCmdEndRenderPass(m_swapchain.commandBuffers[imageIndex]);

    vkCmdPipelineBarrier(
        m_swapchain.commandBuffers[imageIndex],
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
        0, 0, 0, 0, 0, 1, &drawToPresent
    );

    // End command buffer
    if (vkEndCommandBuffer(
        m_swapchain.commandBuffers[imageIndex]) != VK_SUCCESS)
    {
        // Could not end command buffer
        m_rendererReady = false;
        return;
    }


    // Submit next image
    VkPipelineStageFlags waitDstStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    VkSubmitInfo submitInfo;
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.pNext = 0;
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores =
        &m_swapchain.imageAvailable[m_swapchain.current];
    submitInfo.pWaitDstStageMask = &waitDstStage;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &m_swapchain.commandBuffers[imageIndex];
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores =
        &m_swapchain.renderFinished[m_swapchain.current];

    if (vkQueueSubmit(m_surfaceQueueHandle, 1, &submitInfo,
        m_swapchain.fences[m_swapchain.current]) != VK_SUCCESS)
    {
        m_rendererReady = false;
        return;
    }

    // Update surface
    VkPresentInfoKHR present;
    present.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    present.pNext = 0;
    present.waitSemaphoreCount = 1;
    present.pWaitSemaphores = &m_swapchain.renderFinished[m_swapchain.current];
    present.swapchainCount = 1;
    present.pSwapchains = &m_swapchain.handle;
    present.pImageIndices = &imageIndex;
    present.pResults = 0;

    if (vkQueuePresentKHR(m_surfaceQueueHandle, &present) != VK_SUCCESS)
    {
        m_rendererReady = false;
        return;
    }

    // Next swapchain image
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
        // Wait for device idle
        if (vkDeviceWaitIdle)
        {
            if (vkDeviceWaitIdle(m_vulkanDevice) == VK_SUCCESS)
            {
                // Destroy fences
                if (vkDestroyFence)
                {
                    for (uint32_t i = 0; i < m_swapchain.frames; ++i)
                    {
                        if (m_swapchain.fences[i])
                        {
                            vkDestroyFence(
                                m_vulkanDevice, m_swapchain.fences[i], 0
                            );
                        }
                        m_swapchain.fences[i] = 0;
                    }
                }

                // Destroy semaphores
                if (vkDestroySemaphore)
                {
                    for (uint32_t i = 0; i < m_swapchain.frames; ++i)
                    {
                        if (m_swapchain.renderFinished[i])
                        {
                            vkDestroySemaphore(
                                m_vulkanDevice, m_swapchain.renderFinished[i], 0
                            );
                        }
                        m_swapchain.renderFinished[i] = 0;
                        if (m_swapchain.imageAvailable[i])
                        {
                            vkDestroySemaphore(
                                m_vulkanDevice, m_swapchain.imageAvailable[i], 0
                            );
                        }
                        m_swapchain.imageAvailable[i] = 0;
                    }
                }

                // Destroy command buffers
                if (m_commandsPool && vkFreeCommandBuffers)
                {
                    for (uint32_t i = 0; i < m_swapchain.frames; ++i)
                    {
                        if (m_swapchain.commandBuffers[i])
                        {
                            vkFreeCommandBuffers(m_vulkanDevice, m_commandsPool,
                                1, &m_swapchain.commandBuffers[i]
                            );
                        }
                        m_swapchain.commandBuffers[i] = 0;
                    }
                }

                // Destroy commands pool
                if (m_commandsPool && vkDestroyCommandPool)
                {
                    vkDestroyCommandPool(m_vulkanDevice, m_commandsPool, 0);
                }

                // Destroy vertex buffer
                if (m_vertexBuffer.handle && vkDestroyBuffer)
                {
                    vkDestroyBuffer(m_vulkanDevice, m_vertexBuffer.handle, 0);
                }

                // Free vertex buffer memory
                if (m_vertexBuffer.memory && vkFreeMemory)
                {
                    vkFreeMemory(m_vulkanDevice, m_vertexBuffer.memory, 0);
                }

                // Destroy graphics pipeline
                if (m_pipeline && vkDestroyPipeline)
                {
                    vkDestroyPipeline(m_vulkanDevice, m_pipeline, 0);
                }

                // Destroy pipeline layout
                if (m_pipelineLayout && vkDestroyPipelineLayout)
                {
                    vkDestroyPipelineLayout(
                        m_vulkanDevice, m_pipelineLayout, 0
                    );
                }

                // Destroy default shaders
                if (vkDestroyShaderModule)
                {
                    if (m_fragmentShader)
                    {
                        vkDestroyShaderModule(
                            m_vulkanDevice, m_fragmentShader, 0
                        );
                    }
                    if (m_vertexShader)
                    {
                        vkDestroyShaderModule(
                            m_vulkanDevice, m_vertexShader, 0
                        );
                    }
                }

                // Destroy framebuffers
                if (vkDestroyFramebuffer)
                {
                    for (uint32_t i = 0; i < m_swapchain.frames; ++i)
                    {
                        if (m_swapchain.framebuffers[i])
                        {
                            vkDestroyFramebuffer(
                                m_vulkanDevice, m_swapchain.framebuffers[i], 0
                            );
                        }
                        m_swapchain.framebuffers[i] = 0;
                    }
                }

                // Destroy render pass
                if (m_renderPass && vkDestroyRenderPass)
                {
                    vkDestroyRenderPass(m_vulkanDevice, m_renderPass, 0);
                }

                // Destroy swapchain images views
                if (vkDestroyImageView)
                {
                    for (uint32_t i = 0; i < m_swapchain.frames; ++i)
                    {
                        if (m_swapchain.images[i].view)
                        {
                            // Destroy image view
                            vkDestroyImageView(
                                m_vulkanDevice, m_swapchain.images[i].view, 0
                            );
                            m_swapchain.images[i].view = 0;
                        }
                    }
                }

                // Destroy Vulkan swapchain
                if (m_swapchain.handle && vkDestroySwapchainKHR)
                {
                    vkDestroySwapchainKHR(
                        m_vulkanDevice, m_swapchain.handle, 0
                    );
                }
            }
        }

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

    m_commandsPool = 0;
    m_vertexBuffer.size = 0;
    m_vertexBuffer.memory = 0;
    m_vertexBuffer.handle = 0;
    m_pipeline = 0;
    m_pipelineLayout = 0;
    m_fragmentShader = 0;
    m_vertexShader = 0;
    m_renderPass = 0;
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
        // Vulkan instance allready created
        return false;
    }

    // Enumerate Vulkan extensions properties
    uint32_t extCount = 0;
    if (vkEnumerateInstanceExtensionProperties(0, &extCount, 0) != VK_SUCCESS)
    {
        // Could not enumerate Vulkan extensions properties
        return false;
    }

    // Get Vulkan extensions properties
    std::vector<VkExtensionProperties> extProperties(extCount);
    if (vkEnumerateInstanceExtensionProperties(
        0, &extCount, extProperties.data()) != VK_SUCCESS)
    {
        // Could not get Vulkan extensions properties
        return false;
    }

    // Check Vulkan extensions properties
    bool allExtFound = true;
    for (size_t i = 0; i < VulkanExtensions.size(); ++i)
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
    appInfos.apiVersion = VK_API_VERSION;

    // VkInstanceCreateInfo
    VkInstanceCreateInfo createInfos;
    createInfos.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfos.pNext = 0;
    createInfos.flags = 0;
    createInfos.pApplicationInfo = &appInfos;
    createInfos.enabledLayerCount = 0;
    createInfos.ppEnabledLayerNames = 0;
    createInfos.enabledExtensionCount = static_cast<uint32_t>(
        VulkanExtensions.size()
    );
    createInfos.ppEnabledExtensionNames = VulkanExtensions.data();

    // Create Vulkan instance
    if (vkCreateInstance(&createInfos, 0, &m_vulkanInstance) != VK_SUCCESS)
    {
        // Could not create Vulkan instance
        return false;
    }
    if (!m_vulkanInstance)
    {
        // Could not create Vulkan instance
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
        // Vulkan instance is invalid
        return false;
    }

    // Check Vulkan surface
    if (!m_vulkanSurface)
    {
        // Vulkan surface is invalid
        return false;
    }

    // Check physical device
    if (m_physicalDevice)
    {
        // Physical device already selected
        return false;
    }

    // Check Vulkan device
    if (m_vulkanDevice)
    {
        // Vulkan device already created
        return false;
    }

    // List devices
    uint32_t devicesCounts = 0;
    if (vkEnumeratePhysicalDevices(
        m_vulkanInstance, &devicesCounts, 0) != VK_SUCCESS)
    {
        // Could not enumerate physical devices
        return false;
    }
    if (devicesCounts <= 0)
    {
        // No physical device found
        return false;
    }

    // Get physical devices list
    std::vector<VkPhysicalDevice> physicalDevices(devicesCounts);
    if (vkEnumeratePhysicalDevices(
        m_vulkanInstance, &devicesCounts, physicalDevices.data()) != VK_SUCCESS)
    {
        // Could not get physical devices list
        return false;
    }

    // Select a physical device with matching extensions properties
    bool deviceFound = false;
    uint32_t deviceIndex = 0;
    bool graphicsQueueFound = false;
    uint32_t graphicsQueueIndex = 0;
    bool surfaceQueueFound = false;
    uint32_t surfaceQueueIndex = 0;
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
        for (size_t j = 0; j < VulkanDeviceExtensions.size(); ++j)
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
            VK_VERSION_MAJOR(VK_API_VERSION))
        {
            // Vulkan version is not supported by the device
            continue;
        }

        // Get device queue families
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(
            physicalDevices[i], &queueFamilyCount, 0
        );
        if (queueFamilyCount <= 0)
        {
            // No device queue families found
            continue;
        }

        // Get device queue families list
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        std::vector<VkBool32> queueSurfaceSupport(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(
            physicalDevices[i], &queueFamilyCount, queueFamilies.data()
        );
        for (uint32_t j = 0; j < queueFamilyCount; ++j)
        {
            if (vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevices[i], j,
                m_vulkanSurface, &queueSurfaceSupport[j]) != VK_SUCCESS)
            {
                // Could not get physical device surface support
                continue;
            }

            if (queueFamilies[j].queueCount > 0)
            {
                // Check if current queue supports graphics
                if (queueFamilies[j].queueFlags & VK_QUEUE_GRAPHICS_BIT)
                {
                    // Check if current queue supports present surface
                    if (queueSurfaceSupport[j])
                    {
                        // Current queue supports both graphics and surface
                        graphicsQueueIndex = j;
                        graphicsQueueFound = true;
                        surfaceQueueIndex = j;
                        surfaceQueueFound = true;
                        break;
                    }
                    else
                    {
                        // Current queue supports only graphics
                        if (!graphicsQueueFound)
                        {
                            graphicsQueueIndex = j;
                            graphicsQueueFound = true;
                        }
                    }
                }
                else
                {
                    if (queueSurfaceSupport[j])
                    {
                        // Current queue supports only surface
                        if (!surfaceQueueFound)
                        {
                            surfaceQueueIndex = j;
                            surfaceQueueFound = true;
                        }
                    }
                }
            }
        }

        // Current device supports graphics and surface queues
        if (graphicsQueueFound && surfaceQueueFound)
        {
            m_graphicsQueueIndex = graphicsQueueIndex;
            m_surfaceQueueIndex = surfaceQueueIndex;
            deviceIndex = i;
            deviceFound = true;
            break;
        }
    }

    if (!deviceFound)
    {
        // Could not find a device with both graphics and surface queues
        return false;
    }

    m_physicalDevice = physicalDevices[deviceIndex];
    if (!m_physicalDevice)
    {
        // Invalid physical device pointer
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
    queueInfos.back().queueFamilyIndex = graphicsQueueIndex;
    queueInfos.back().queueCount = static_cast<uint32_t>(
        queuePriorities.size()
    );
    queueInfos.back().pQueuePriorities = queuePriorities.data();

    // Add another queue if the surface queue is different
    if (surfaceQueueIndex != graphicsQueueIndex)
    {
        queueInfos.push_back(VkDeviceQueueCreateInfo());
        queueInfos.back().sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueInfos.back().pNext = 0;
        queueInfos.back().flags = 0;
        queueInfos.back().queueFamilyIndex = surfaceQueueIndex;
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
    deviceInfos.enabledExtensionCount = static_cast<uint32_t>(
        VulkanDeviceExtensions.size()
    );
    deviceInfos.ppEnabledExtensionNames = VulkanDeviceExtensions.data();
    deviceInfos.pEnabledFeatures = 0;

    if (vkCreateDevice(
        m_physicalDevice, &deviceInfos, 0, &m_vulkanDevice) != VK_SUCCESS)
    {
        // Could not create Vulkan device
        return false;
    }
    if (!m_vulkanDevice)
    {
        // Invalid Vulkan device pointer
        return false;
    }

    // Vulkan device successfully selected
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Get Vulkan queues handles                                                 //
//  return : True if queues handles are valid                                 //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::getQueuesHandles()
{
    // Check Vulkan device
    if (!m_vulkanDevice)
    {
        // Vulkan device is invalid
        return false;
    }

    // Get graphics queue handle
    vkGetDeviceQueue(
        m_vulkanDevice, m_graphicsQueueIndex, 0, &m_graphicsQueueHandle
    );
    if (!m_graphicsQueueHandle)
    {
        // Could not get graphics queue handle
        return false;
    }

    // Get surface queue handle
    vkGetDeviceQueue(
        m_vulkanDevice, m_surfaceQueueIndex, 0, &m_surfaceQueueHandle
    );
    if (!m_surfaceQueueHandle)
    {
        // Could not get surface queue handle
        return false;
    }

    // Vulkan queues handles are valid
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create Vulkan swapchain                                                   //
//  return : True if Vulkan swapchain is successfully created                 //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::createVulkanSwapchain()
{
    m_rendererReady = false;

    // Check Vulkan device
    if (!m_vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Check Vulkan surface
    if (!m_vulkanSurface)
    {
        // Invalid Vulkan surface
        return false;
    }

    // Wait for device idle
    if (vkDeviceWaitIdle(m_vulkanDevice) != VK_SUCCESS)
    {
        // Could not get the device ready
        return false;
    }

    // Cleanup swapchain images views
    for (uint32_t i = 0; i < m_swapchain.frames; ++i)
    {
        if (m_swapchain.images[i].view)
        {
            // Destroy image view
            vkDestroyImageView(m_vulkanDevice, m_swapchain.images[i].view, 0);
            m_swapchain.images[i].view = 0;
        }
    }


    // Get device surface capabilities
    VkSurfaceCapabilitiesKHR surfaceCapabilities;
    if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
        m_physicalDevice, m_vulkanSurface, &surfaceCapabilities) != VK_SUCCESS)
    {
        // Could not get device surface capabilities
        return false;
    }

    // Get surface formats
    uint32_t formatsCnt = 0;
    if (vkGetPhysicalDeviceSurfaceFormatsKHR(
        m_physicalDevice, m_vulkanSurface, &formatsCnt, 0) != VK_SUCCESS)
    {
        // Could not get surface formats count
        return false;
    }
    if (formatsCnt <= 0)
    {
        // No surface formats found
        return false;
    }

    std::vector<VkSurfaceFormatKHR> surfaceFormats(formatsCnt);
    if (vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice,
        m_vulkanSurface, &formatsCnt, surfaceFormats.data()) != VK_SUCCESS)
    {
        // Could not get surface formats
        return false;
    }

    // Get present modes
    uint32_t presentModesCnt = 0;
    if (vkGetPhysicalDeviceSurfacePresentModesKHR(
        m_physicalDevice, m_vulkanSurface, &presentModesCnt, 0) != VK_SUCCESS)
    {
        // Could not get present modes count
        return false;
    }
    if (presentModesCnt <= 0)
    {
        // No present modes found
        return false;
    }
    std::vector<VkPresentModeKHR> presentModes(presentModesCnt);
    if (vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice,
        m_vulkanSurface, &presentModesCnt, presentModes.data()) != VK_SUCCESS)
    {
        // Could not get present modes
        return false;
    }


    // Set swapchain images count
    uint32_t imagesCount = RendererMaxSwapchainFrames;

    // Images count clamping
    if (imagesCount <= surfaceCapabilities.minImageCount)
    {
        imagesCount = surfaceCapabilities.minImageCount;
    }
    if (imagesCount >= surfaceCapabilities.maxImageCount)
    {
        imagesCount = surfaceCapabilities.maxImageCount;
    }
    if (imagesCount >= RendererMaxSwapchainFrames)
    {
        imagesCount = RendererMaxSwapchainFrames;
    }
    if (imagesCount <= 0)
    {
        // Invalid swapchain images count
        return false;
    }

    // Set swapchain surface format
    VkSurfaceFormatKHR format;
    format.format = VK_FORMAT_UNDEFINED;
    format.colorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
    if (surfaceFormats.size() <= 0)
    {
        // Invalid surface formats count
        return false;
    }

    // Select best surface format
    if (surfaceFormats[0].format == VK_FORMAT_UNDEFINED)
    {
        format.format = VK_FORMAT_R8G8B8A8_UNORM;
        format.colorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
    }
    else
    {
        bool formatFound = false;
        for (size_t i = 0; i < surfaceFormats.size(); ++i)
        {
            if (surfaceFormats[i].format == VK_FORMAT_R8G8B8A8_UNORM)
            {
                // Surface format found
                format.format = surfaceFormats[i].format;
                format.colorSpace = surfaceFormats[i].colorSpace;
                formatFound = true;
                break;
            }
        }
        if (!formatFound)
        {
            // Select first surface format
            format.format = surfaceFormats[0].format;
            format.colorSpace = surfaceFormats[0].colorSpace;
        }
    }

    // Set swapchain extent
    VkExtent2D extent;
    extent.width = surfaceCapabilities.currentExtent.width;
    extent.height = surfaceCapabilities.currentExtent.height;

    // Clamp swapchain extent
    if (extent.width < surfaceCapabilities.minImageExtent.width)
    {
        extent.width = surfaceCapabilities.minImageExtent.width;
    }
    if (extent.height < surfaceCapabilities.minImageExtent.height)
    {
        extent.height = surfaceCapabilities.minImageExtent.height;
    }
    if (extent.width > surfaceCapabilities.maxImageExtent.width)
    {
        extent.width = surfaceCapabilities.maxImageExtent.width;
    }
    if (extent.height > surfaceCapabilities.maxImageExtent.height)
    {
        extent.height = surfaceCapabilities.maxImageExtent.height;
    }

    if ((extent.width <= 0) || (extent.height <= 0))
    {
        // Invalid swapchain extent
        return false;
    }

    // Set swapchain image usage
    VkImageUsageFlags imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    if (!(surfaceCapabilities.supportedUsageFlags &
        VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT))
    {
        // Color attachment flag is not supported
        return false;
    }

    // Set surface transform flags
    VkSurfaceTransformFlagBitsKHR transformFlags =
        VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    if (!(surfaceCapabilities.supportedTransforms &
        VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR))
    {
        transformFlags = surfaceCapabilities.currentTransform;
    }

    // Set present mode
    VkPresentModeKHR present = VK_PRESENT_MODE_IMMEDIATE_KHR;
    bool immediateModeFound = false;
    bool mailboxModeFound = false;
    bool fifoModeFound = false;
    for (size_t i = 0; i < presentModes.size(); ++i)
    {
        if (presentModes[i] == VK_PRESENT_MODE_IMMEDIATE_KHR)
        {
            immediateModeFound = true;
        }
        if (presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            mailboxModeFound = true;
        }
        if (presentModes[i] == VK_PRESENT_MODE_FIFO_KHR)
        {
            fifoModeFound = true;
        }
    }
    if (!immediateModeFound)
    {
        if (mailboxModeFound)
        {
            present = VK_PRESENT_MODE_MAILBOX_KHR;
        }
        else
        {
            if (fifoModeFound)
            {
                present = VK_PRESENT_MODE_FIFO_KHR;
            }
            else
            {
                // No present mode is supported
                return false;
            }
        }
    }

    // Set old swapchain
    VkSwapchainKHR oldSwapchain = m_swapchain.handle;

    // Create swapchain
    VkSwapchainCreateInfoKHR swapchainInfos;
    swapchainInfos.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchainInfos.pNext = 0;
    swapchainInfos.flags = 0;
    swapchainInfos.surface = m_vulkanSurface;
    swapchainInfos.minImageCount = imagesCount;
    swapchainInfos.imageFormat = format.format;
    swapchainInfos.imageColorSpace = format.colorSpace;
    swapchainInfos.imageExtent = extent;
    swapchainInfos.imageArrayLayers = 1;
    swapchainInfos.imageUsage = imageUsage;
    swapchainInfos.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    swapchainInfos.queueFamilyIndexCount = 0;
    swapchainInfos.pQueueFamilyIndices = 0;
    swapchainInfos.preTransform = transformFlags;
    swapchainInfos.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchainInfos.presentMode = present;
    swapchainInfos.clipped = VK_TRUE;
    swapchainInfos.oldSwapchain = oldSwapchain;

    if (vkCreateSwapchainKHR(
        m_vulkanDevice, &swapchainInfos, 0, &m_swapchain.handle) != VK_SUCCESS)
    {
        // Could not create Vulkan swapchain
        return false;
    }

    // Destroy old swapchain
    if (oldSwapchain)
    {
        vkDestroySwapchainKHR(m_vulkanDevice, oldSwapchain, 0);
    }

    // Set swapchain format
    m_swapchain.format = format.format;

    // Get swapchain frames count
    uint32_t swapchainFramesCount = 0;
    if (vkGetSwapchainImagesKHR(m_vulkanDevice,
        m_swapchain.handle, &swapchainFramesCount, 0) != VK_SUCCESS)
    {
        // Could not get swapchain frames count
        return false;
    }

    // Check swapchain frames count
    if (swapchainFramesCount <= 0)
    {
        // Invalid swapchain frames count
        return false;
    }
    if (swapchainFramesCount > RendererMaxSwapchainFrames)
    {
        // Invalid swapchain frames count
        return false;
    }

    // Get current swapchain images
    VkImage images[RendererMaxSwapchainFrames];
    if (vkGetSwapchainImagesKHR(m_vulkanDevice,
        m_swapchain.handle, &swapchainFramesCount, images) != VK_SUCCESS)
    {
        // Could not get swapchain images count
        return false;
    }

    // Set swapchain images
    m_swapchain.frames = swapchainFramesCount;
    for (uint32_t i = 0; i < m_swapchain.frames; ++i)
    {
        m_swapchain.images[i].handle = images[i];
    }

    // Set swapchain extent
    m_swapchain.extent.width = extent.width;
    m_swapchain.extent.height = extent.height;

    // Create swapchain images views
    VkComponentMapping components;
    components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

    VkImageSubresourceRange subresource;
    subresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    subresource.baseMipLevel = 0;
    subresource.levelCount = 1;
    subresource.baseArrayLayer = 0;
    subresource.layerCount = 1;

    for (uint32_t i = 0; i < m_swapchain.frames; ++i)
    {
        // Create image view
        VkImageViewCreateInfo imageView;
        imageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageView.pNext = 0;
        imageView.flags = 0;
        imageView.image = m_swapchain.images[i].handle;
        imageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
        imageView.format = m_swapchain.format;
        imageView.components = components;
        imageView.subresourceRange = subresource;

        if (vkCreateImageView(m_vulkanDevice,
            &imageView, 0, &m_swapchain.images[i].view) != VK_SUCCESS)
        {
            // Could not create swapchain image view
            return false;
        }
    }

    // Wait for device idle
    if (vkDeviceWaitIdle(m_vulkanDevice) != VK_SUCCESS)
    {
        // Could not get the device ready
        return false;
    }

    // Vulkan swapchain successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create render pass                                                        //
//  return : True if render pass is successfully created                      //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::createRenderPass()
{
    // Check Vulkan device
    if (!m_vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Create render pass
    VkAttachmentDescription attachmentDescription;
    attachmentDescription.flags = 0;
    attachmentDescription.format = m_swapchain.format;
    attachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;
    attachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachmentDescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachmentDescription.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference attachmentReference;
    attachmentReference.attachment = 0;
    attachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpassDescription;
    subpassDescription.flags = 0;
    subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpassDescription.inputAttachmentCount = 0;
    subpassDescription.pInputAttachments = 0;
    subpassDescription.colorAttachmentCount = 1;
    subpassDescription.pColorAttachments = &attachmentReference;
    subpassDescription.pResolveAttachments = 0;
    subpassDescription.pDepthStencilAttachment = 0;
    subpassDescription.preserveAttachmentCount = 0;
    subpassDescription.pPreserveAttachments = 0;

    VkSubpassDependency subpassDependencies[2];

    subpassDependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
    subpassDependencies[0].dstSubpass = 0;
    subpassDependencies[0].srcStageMask =
        VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
    subpassDependencies[0].dstStageMask =
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpassDependencies[0].srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
    subpassDependencies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    subpassDependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

    subpassDependencies[1].srcSubpass = 0;
    subpassDependencies[1].dstSubpass = VK_SUBPASS_EXTERNAL;
    subpassDependencies[1].srcStageMask =
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpassDependencies[1].dstStageMask =
        VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
    subpassDependencies[1].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    subpassDependencies[1].dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
    subpassDependencies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

    VkRenderPassCreateInfo renderPassInfo;
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.pNext = 0;
    renderPassInfo.flags = 0;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &attachmentDescription;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpassDescription;
    renderPassInfo.dependencyCount = 2;
    renderPassInfo.pDependencies = subpassDependencies;

    if (vkCreateRenderPass(
        m_vulkanDevice, &renderPassInfo, 0, &m_renderPass) != VK_SUCCESS)
    {
        // Could not create render pass
        return false;
    }
    if (!m_renderPass)
    {
        // Invalid render pass
        return false;
    }

    // Render pass successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create framebuffers                                                       //
//  return : True if framebuffers are successfully created                    //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::createFramebuffers()
{
    // Check Vulkan device
    if (!m_vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Check render pass
    if (!m_renderPass)
    {
        // Invalid render pass
        return false;
    }

    // Check swapchain images count
    if (m_swapchain.frames <= 0)
    {
        // No swapchain images
        return false;
    }

    // Create framebuffers
    for (uint32_t i = 0; i < m_swapchain.frames; ++i)
    {
        VkFramebufferCreateInfo framebufferInfo;
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.pNext = 0;
        framebufferInfo.flags = 0;
        framebufferInfo.renderPass = m_renderPass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = &m_swapchain.images[i].view;
        framebufferInfo.width = m_swapchain.extent.width;
        framebufferInfo.height = m_swapchain.extent.height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(m_vulkanDevice,
            &framebufferInfo, 0, &m_swapchain.framebuffers[i]) != VK_SUCCESS)
        {
            // Could not create framebuffer
            return false;
        }
        if (!m_swapchain.framebuffers[i])
        {
            // Invalid framebuffer
            return false;
        }
    }

    // Framebuffers successfully created
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Create default shaders                                                    //
//  return : True if default shaders are successfully created                 //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::createDefaultShaders()
{
    // Check Vulkan device
    if (!m_vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Create default vertex shader
    VkShaderModuleCreateInfo vertexShaderInfo;
    vertexShaderInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    vertexShaderInfo.pNext = 0;
    vertexShaderInfo.flags = 0;
    vertexShaderInfo.codeSize = DefaultVertexShaderSize;
    vertexShaderInfo.pCode = DefaultVertexShader;

    if (vkCreateShaderModule(m_vulkanDevice,
        &vertexShaderInfo, 0, &m_vertexShader) != VK_SUCCESS)
    {
        // Could not create default vertex shader
        return false;
    }
    if (!m_vertexShader)
    {
        // Invalid default vertex shader
        return false;
    }

    // Create default fragment shader
    VkShaderModuleCreateInfo fragmentShaderInfo;
    fragmentShaderInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    fragmentShaderInfo.pNext = 0;
    fragmentShaderInfo.flags = 0;
    fragmentShaderInfo.codeSize = DefaultFragmentShaderSize;
    fragmentShaderInfo.pCode = DefaultFragmentShader;

    if (vkCreateShaderModule(m_vulkanDevice,
        &fragmentShaderInfo, 0, &m_fragmentShader) != VK_SUCCESS)
    {
        // Could not create default fragment shader
        return false;
    }
    if (!m_fragmentShader)
    {
        // Invalid default fragment shader
        return false;
    }

    // Default shaders successfully created
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

    // Create pipeline layout
    VkPipelineLayoutCreateInfo pipelineInfo;
    pipelineInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineInfo.pNext = 0;
    pipelineInfo.flags = 0;
    pipelineInfo.setLayoutCount = 0;
    pipelineInfo.pSetLayouts = 0;
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
    if (!m_renderPass)
    {
        // Invalid render pass
        return false;
    }

    // Check vertex shader
    if (!m_vertexShader)
    {
        // Invalid vertex shader
        return false;
    }

    // Check fragment shader
    if (!m_fragmentShader)
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
    shaderStage[0].module = m_vertexShader;
    shaderStage[0].pName = "main";
    shaderStage[0].pSpecializationInfo = 0;

    shaderStage[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStage[1].pNext = 0;
    shaderStage[1].flags = 0;
    shaderStage[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    shaderStage[1].module = m_fragmentShader;
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
    vertexAttributes[0].format = VK_FORMAT_R32G32B32A32_SFLOAT;
    vertexAttributes[0].offset = 0;

    vertexAttributes[1].location = 1;
    vertexAttributes[1].binding = vertexBinding.binding;
    vertexAttributes[1].format = VK_FORMAT_R32G32B32A32_SFLOAT;
    vertexAttributes[1].offset = sizeof(float)*4;

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
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
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
    pipelineInfo.renderPass = m_renderPass;
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
//  Create vertex buffer                                                      //
//  return : True if vertex buffer is successfully created                    //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::createVertexBuffer()
{
    // Check physical device
    if (!m_physicalDevice)
    {
        // Invalid physical device
        return false;
    }

    // Check Vulkan device
    if (!m_vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Create vertex buffer
    VertexData vertices[4];

    vertices[0].x = -0.8f;
    vertices[0].y = -0.8f;
    vertices[0].z = 0.0f;
    vertices[0].w = 1.0f;
    vertices[0].r = 0.2f;
    vertices[0].g = 0.5f;
    vertices[0].b = 0.8f;
    vertices[0].a = 1.0f;

    vertices[1].x = -0.8f;
    vertices[1].y = 0.8f;
    vertices[1].z = 0.0f;
    vertices[1].w = 1.0f;
    vertices[1].r = 0.2f;
    vertices[1].g = 0.5f;
    vertices[1].b = 0.8f;
    vertices[1].a = 1.0f;

    vertices[2].x = 0.8f;
    vertices[2].y = -0.8f;
    vertices[2].z = 0.0f;
    vertices[2].w = 1.0f;
    vertices[2].r = 0.2f;
    vertices[2].g = 0.5f;
    vertices[2].b = 0.8f;
    vertices[2].a = 1.0f;

    vertices[3].x = 0.8f;
    vertices[3].y = 0.8f;
    vertices[3].z = 0.0f;
    vertices[3].w = 1.0f;
    vertices[3].r = 0.2f;
    vertices[3].g = 0.5f;
    vertices[3].b = 0.8f;
    vertices[3].a = 1.0f;

    m_vertexBuffer.size = sizeof(vertices);

    VkBufferCreateInfo bufferInfo;
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.pNext = 0;
    bufferInfo.flags = 0;
    bufferInfo.size = m_vertexBuffer.size;
    bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    bufferInfo.queueFamilyIndexCount = 0;
    bufferInfo.pQueueFamilyIndices = 0;

    if (vkCreateBuffer(
        m_vulkanDevice, &bufferInfo, 0, &m_vertexBuffer.handle) != VK_SUCCESS)
    {
        // Could not create vertex buffer
        return false;
    }
    if (!m_vertexBuffer.handle)
    {
        // Invalid vertex buffer
        return false;
    }

    // Get memory requirements
    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(
        m_vulkanDevice, m_vertexBuffer.handle, &memoryRequirements
    );

    // Get physical device memory properties
    VkPhysicalDeviceMemoryProperties memoryProperties;
    vkGetPhysicalDeviceMemoryProperties(m_physicalDevice, &memoryProperties);

    // Allocate buffer memory
    bool memoryAllocated = false;
    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; ++i)
    {
        if (memoryRequirements.memoryTypeBits & (1 << i))
        {
            if (memoryProperties.memoryTypes[i].propertyFlags &
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
            {
                VkMemoryAllocateInfo allocateInfo;
                allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
                allocateInfo.pNext = 0;
                allocateInfo.allocationSize = memoryRequirements.size;
                allocateInfo.memoryTypeIndex = i;

                if (vkAllocateMemory(m_vulkanDevice,
                    &allocateInfo, 0, &m_vertexBuffer.memory) == VK_SUCCESS)
                {
                    memoryAllocated = true;
                    break;
                }
            }
        }
    }
    if (!memoryAllocated)
    {
        // Could not allocate buffer memory
        return false;
    }

    // Bind buffer memory
    if (vkBindBufferMemory(m_vulkanDevice,
        m_vertexBuffer.handle, m_vertexBuffer.memory, 0) != VK_SUCCESS)
    {
        // Could not bind buffer memory
        return false;
    }

    // Map buffer memory
    void* vertexBufferMemory = 0;
    if (vkMapMemory(m_vulkanDevice, m_vertexBuffer.memory, 0,
        m_vertexBuffer.size, 0, &vertexBufferMemory) != VK_SUCCESS)
    {
        return false;
        // Could not map buffer memory
    }
    if (!vertexBufferMemory)
    {
        // Invalid vertex buffer memory pointer
        return false;
    }

    // Copy vertices into vertex buffer memory
    memcpy(vertexBufferMemory, vertices, m_vertexBuffer.size);

    // Unmap buffer memory
    VkMappedMemoryRange memoryRange;
    memoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
    memoryRange.pNext = 0;
    memoryRange.memory = m_vertexBuffer.memory;
    memoryRange.offset = 0;
    memoryRange.size = VK_WHOLE_SIZE;
    
    if (vkFlushMappedMemoryRanges(
        m_vulkanDevice, 1, &memoryRange) != VK_SUCCESS)
    {
        // Could not flush vertex buffer mapped memory ranges
        return false;
    }

    vkUnmapMemory(m_vulkanDevice, m_vertexBuffer.memory);

    // Vertex buffer successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create command buffers                                                    //
//  return : True if command buffers are successfully created                 //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::createCommandBuffers()
{
    // Create commands pool
    VkCommandPoolCreateInfo commandPool;
    commandPool.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPool.pNext = 0;
    commandPool.flags =
        VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT |
        VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
    commandPool.queueFamilyIndex = m_surfaceQueueIndex;

    if (vkCreateCommandPool(
        m_vulkanDevice, &commandPool, 0, &m_commandsPool) != VK_SUCCESS)
    {
        // Could not create commands pool
        return false;
    }
    if (!m_commandsPool)
    {
        // Invalid commands pool
        return false;
    }

    // Allocate command buffers
    VkCommandBufferAllocateInfo commandBuffer;
    commandBuffer.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    commandBuffer.pNext = 0;
    commandBuffer.commandPool = m_commandsPool;
    commandBuffer.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    commandBuffer.commandBufferCount = m_swapchain.frames;

    if (vkAllocateCommandBuffers(m_vulkanDevice,
        &commandBuffer, m_swapchain.commandBuffers) != VK_SUCCESS)
    {
        // Could not allocate command buffers
        return false;
    }

    // Command buffers successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create semaphores                                                         //
//  return : True if semaphores are successfully created                      //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::createSemaphores()
{
    // Check Vulkan device
    if (!m_vulkanDevice)
    {
        // Vulkan device is invalid
        return false;
    }

    VkSemaphoreCreateInfo semaphoreInfo;
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    semaphoreInfo.pNext = 0;
    semaphoreInfo.flags = 0;

    for (uint32_t i = 0; i < m_swapchain.frames; ++i)
    {
        // Create image available semaphore
        if (vkCreateSemaphore(m_vulkanDevice,
            &semaphoreInfo, 0, &m_swapchain.imageAvailable[i]) != VK_SUCCESS)
        {
            // Could not create image available semaphore
            return false;
        }

        // Create render finished semaphore
        if (vkCreateSemaphore(m_vulkanDevice,
            &semaphoreInfo, 0, &m_swapchain.renderFinished[i]) != VK_SUCCESS)
        {
            // Could not create render finished semaphore
            return false;
        }
    }

    // Semaphores successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create fences                                                             //
//  return : True if fences are successfully created                          //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::createFences()
{
    // Check Vulkan device
    if (!m_vulkanDevice)
    {
        // Vulkan device is invalid
        return false;
    }

    // Create fences
    VkFenceCreateInfo fenceInfo;
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.pNext = 0;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (uint32_t i = 0; i < m_swapchain.frames; ++i)
    {
        if (vkCreateFence(m_vulkanDevice,
            &fenceInfo, 0, &m_swapchain.fences[i]) != VK_SUCCESS)
        {
            // Could not create fence
            return false;
        }
        if (!m_swapchain.fences[i])
        {
            // Invalid fence
            return false;
        }
    }

    // Fences successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Resize renderer frame                                                     //
//  return : True if the renderer is successfully resized                    //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::resize()
{
    m_rendererReady = false;

    // Cleanup renderer
    if (m_vulkanDevice && vkDeviceWaitIdle)
    {
        // Wait for device idle
        if (vkDeviceWaitIdle)
        {
            if (vkDeviceWaitIdle(m_vulkanDevice) == VK_SUCCESS)
            {
                // Destroy fences
                if (vkDestroyFence)
                {
                    for (uint32_t i = 0; i < m_swapchain.frames; ++i)
                    {
                        if (m_swapchain.fences[i])
                        {
                            vkDestroyFence(
                                m_vulkanDevice, m_swapchain.fences[i], 0
                            );
                        }
                        m_swapchain.fences[i] = 0;
                    }
                }

                // Destroy framebuffers
                if (vkDestroyFramebuffer)
                {
                    for (uint32_t i = 0; i < m_swapchain.frames; ++i)
                    {
                        if (m_swapchain.framebuffers[i])
                        {
                            vkDestroyFramebuffer(
                                m_vulkanDevice, m_swapchain.framebuffers[i], 0
                            );
                        }
                        m_swapchain.framebuffers[i] = 0;
                    }
                }

                // Destroy swapchain images views
                if (vkDestroyImageView)
                {
                    for (uint32_t i = 0; i < m_swapchain.frames; ++i)
                    {
                        if (m_swapchain.images[i].view)
                        {
                            // Destroy image view
                            vkDestroyImageView(
                                m_vulkanDevice, m_swapchain.images[i].view, 0
                            );
                            m_swapchain.images[i].view = 0;
                        }
                    }
                }

                // Destroy Vulkan swapchain
                if (m_swapchain.handle && vkDestroySwapchainKHR)
                {
                    vkDestroySwapchainKHR(
                        m_vulkanDevice, m_swapchain.handle, 0
                    );
                }
            }
        }
    }
    m_swapchain.handle = 0;

    // Recreate Vulkan swapchain
    if (!createVulkanSwapchain())
    {
        // Could not recreate Vulkan swapchain
        return false;
    }

    // Recreate framebuffers
    if (!createFramebuffers())
    {
        // Could not recreate framebuffers
        return false;
    }

    // Recreate fences
    if (!createFences())
    {
        // Could not recreate fences
        return false;
    }

    // Reset swapchain current frame index
    m_swapchain.current = 0;

    // Renderer successfully resized
    m_rendererReady = true;
    return true;
}
