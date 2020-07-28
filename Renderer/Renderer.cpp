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
m_sysWindow(0),
m_vulkanLibHandle(0),
m_vulkanInstance(0),
m_vulkanSurface(0),
m_physicalDevice(0),
m_vulkanDevice(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  Renderer destructor                                                       //
////////////////////////////////////////////////////////////////////////////////
Renderer::~Renderer()
{
	// Destroy Vulkan device
	if (m_vulkanDevice && vkDestroyDevice)
    {
        vkDestroyDevice(m_vulkanDevice, 0);
        m_vulkanDevice = 0;
    }
	
	// Destroy Vulkan surface
	DestroyVulkanSurface(m_vulkanInstance, m_vulkanSurface);

	// Destroy Vulkan instance
	if (m_vulkanInstance && vkDestroyInstance)
    {
        vkDestroyInstance(m_vulkanInstance, 0);
        m_vulkanInstance = 0;
    }

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

	// Renderer successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Clear renderer frame                                                      //
////////////////////////////////////////////////////////////////////////////////
void Renderer::clear()
{

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
