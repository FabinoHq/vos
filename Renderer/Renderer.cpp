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
m_commands(),
m_semaphores()
{

}

////////////////////////////////////////////////////////////////////////////////
//  Renderer destructor                                                       //
////////////////////////////////////////////////////////////////////////////////
Renderer::~Renderer()
{
    close();
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

    // Renderer successfully loaded
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
        return;
    }

    // Acquire next image
    uint32_t imageIndex = 0;
    if (vkAcquireNextImageKHR(m_vulkanDevice, m_swapchain.handle, UINT64_MAX,
        m_semaphores.imageAvailable, 0, &imageIndex) != VK_SUCCESS)
    {
        return;
    }

    VkPipelineStageFlags waitDstStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    VkSubmitInfo submitInfo;
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.pNext = 0;
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = &m_semaphores.imageAvailable;
    submitInfo.pWaitDstStageMask = &waitDstStage;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &m_commands.buffers[imageIndex];
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = &m_semaphores.renderFinished;

    if (vkQueueSubmit(m_surfaceQueueHandle, 1, &submitInfo, 0) != VK_SUCCESS)
    {
        return;
    }

    VkPresentInfoKHR present;
    present.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    present.pNext = 0;
    present.waitSemaphoreCount = 1;
    present.pWaitSemaphores = &m_semaphores.renderFinished;;
    present.swapchainCount = 1;
    present.pSwapchains = &m_swapchain.handle;
    present.pImageIndices = &imageIndex;
    present.pResults = 0;

    if (!vkQueuePresentKHR(m_surfaceQueueHandle, &present) != VK_SUCCESS)
    {
        return;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Close renderer                                                            //
////////////////////////////////////////////////////////////////////////////////
void Renderer::close()
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
                // Destroy semaphores
                if (vkDestroySemaphore)
                {
                    if (m_semaphores.renderFinished)
                    {
                        vkDestroySemaphore(
                            m_vulkanDevice, m_semaphores.renderFinished, 0
                        );
                    }
                    if (m_semaphores.imageAvailable)
                    {
                        vkDestroySemaphore(
                            m_vulkanDevice, m_semaphores.imageAvailable, 0
                        );
                    }
                }

                // Destroy command buffers
                if (m_commands.buffers.size() > 0)
                {
                    bool validBuffers = true;
                    for (size_t i = 0; i < m_commands.buffers.size(); ++i)
                    {
                        if (!m_commands.buffers[i])
                        {
                            validBuffers = false;
                            break;
                        }
                    }
                    if (validBuffers && m_commands.pool && vkFreeCommandBuffers)
                    {
                        vkFreeCommandBuffers(m_vulkanDevice, m_commands.pool,
                            static_cast<uint32_t>(m_commands.buffers.size()),
                            m_commands.buffers.data()
                        );
                    }
                }

                // Destroy commands pool
                if (m_commands.pool && vkDestroyCommandPool)
                {
                    vkDestroyCommandPool(m_vulkanDevice, m_commands.pool, 0);
                }

                // Destroy swapchain images views
                if (vkDestroyImageView)
                {
                    for (size_t i = 0; i < m_swapchain.images.size(); ++i)
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
    m_semaphores.renderFinished = 0;
    m_semaphores.imageAvailable = 0;
    m_commands.pool = 0;
    m_swapchain.handle = 0;
    m_vulkanDevice = 0;
    
    // Destroy Vulkan surface
    if (m_vulkanInstance && m_vulkanSurface && vkDestroySurfaceKHR)
    {
        vkDestroySurfaceKHR(m_vulkanInstance, m_vulkanSurface, 0);
    }
    m_vulkanSurface = 0;

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
    for (size_t i = 0; i < m_swapchain.images.size(); ++i)
    {
        if (m_swapchain.images[i].view)
        {
            // Destroy image view
            vkDestroyImageView(m_vulkanDevice, m_swapchain.images[i].view, 0);
            m_swapchain.images[i].view = 0;
        }
    }
    m_swapchain.images.clear();


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
    uint32_t imagesCount = surfaceCapabilities.minImageCount + 2;
    if (surfaceCapabilities.maxImageCount <= 0)
    {
        // Invalid swapchain max images count
        return false;
    }
    if (imagesCount >= surfaceCapabilities.maxImageCount)
    {
        imagesCount = surfaceCapabilities.maxImageCount;
    }

    // Set swapchain surface format
    VkSurfaceFormatKHR format;
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

    // Get swapchain images count
    uint32_t swapchainImagesCount = 0;
    if (vkGetSwapchainImagesKHR(m_vulkanDevice,
        m_swapchain.handle, &swapchainImagesCount, 0) != VK_SUCCESS)
    {
        // Could not get swapchain images count
        return false;
    }

    // Get current swapchain images
    std::vector<VkImage> images(swapchainImagesCount);
    if (vkGetSwapchainImagesKHR(m_vulkanDevice,
        m_swapchain.handle, &swapchainImagesCount, images.data()) != VK_SUCCESS)
    {
        // Could not get swapchain images count
        return false;
    }

    // Set swapchain images
    m_swapchain.imagesCnt = swapchainImagesCount;
    m_swapchain.images.resize(swapchainImagesCount);
    for (size_t i = 0; i < m_swapchain.images.size(); ++i)
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

    for (size_t i = 0; i < m_swapchain.images.size(); ++i)
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

    // Vulkan swapchain successfully created
    m_rendererReady = true;
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
    commandPool.flags = 0;
    commandPool.queueFamilyIndex = m_surfaceQueueIndex;

    if (vkCreateCommandPool(
        m_vulkanDevice, &commandPool, 0, &m_commands.pool) != VK_SUCCESS)
    {
        // Could not create commands pool
        return false;
    }
    if (!m_commands.pool)
    {
        // Invalid commands pool
        return false;
    }

    // Allocate command buffers
    m_commands.buffers.resize(m_swapchain.imagesCnt);

    VkCommandBufferAllocateInfo commandBuffer;
    commandBuffer.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    commandBuffer.pNext = 0;
    commandBuffer.commandPool = m_commands.pool;
    commandBuffer.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    commandBuffer.commandBufferCount = m_swapchain.imagesCnt;

    if (vkAllocateCommandBuffers(m_vulkanDevice,
        &commandBuffer, m_commands.buffers.data()) != VK_SUCCESS)
    {
        // Could not allocate command buffers
        return false;
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
    for (uint32_t i = 0; i < m_swapchain.imagesCnt; ++i)
    {
        VkImageMemoryBarrier presentToClear;
        presentToClear.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        presentToClear.pNext = 0;
        presentToClear.srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
        presentToClear.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        presentToClear.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        presentToClear.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        presentToClear.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        presentToClear.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        presentToClear.image = m_swapchain.images[i].handle;
        presentToClear.subresourceRange = subresource;

        VkImageMemoryBarrier clearToPresent;
        clearToPresent.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        clearToPresent.pNext = 0;
        clearToPresent.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        clearToPresent.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
        clearToPresent.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        clearToPresent.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        clearToPresent.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        clearToPresent.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        clearToPresent.image = m_swapchain.images[i].handle;
        clearToPresent.subresourceRange = subresource;

        // Begin command buffer
        if (vkBeginCommandBuffer(
            m_commands.buffers[i], &commandBegin) != VK_SUCCESS)
        {
            // Could not begin command buffer
            return false;
        }
        
        vkCmdPipelineBarrier(
            m_commands.buffers[i], VK_PIPELINE_STAGE_TRANSFER_BIT,
            VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, 0, 0, 0, 1,
            &presentToClear
        );

        vkCmdClearColorImage(
            m_commands.buffers[i], m_swapchain.images[i].handle,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            &RendererClearColor, 1, &subresource
        );

        vkCmdPipelineBarrier(
            m_commands.buffers[i], VK_PIPELINE_STAGE_TRANSFER_BIT,
            VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0, 0, 0, 0, 0, 1,
            &clearToPresent
        );

        // End command buffer
        if (vkEndCommandBuffer(m_commands.buffers[i]) != VK_SUCCESS)
        {
            // Could not end command buffer
            return false;
        }
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

    // Create image available semaphore
    if (vkCreateSemaphore(m_vulkanDevice,
        &semaphoreInfo, 0, &m_semaphores.imageAvailable) != VK_SUCCESS)
    {
        // Could not create image available semaphore
        return false;
    }

    // Create render finished semaphore
    if (vkCreateSemaphore(m_vulkanDevice,
        &semaphoreInfo, 0, &m_semaphores.renderFinished) != VK_SUCCESS)
    {
        // Could not create render finished semaphore
        return false;
    }

    // Semaphores successfully created
    return true;
}
