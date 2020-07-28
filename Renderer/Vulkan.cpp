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
//     Renderer/Vulkan.cpp : Vulkan management                                //
////////////////////////////////////////////////////////////////////////////////
#include "Vulkan.h"


////////////////////////////////////////////////////////////////////////////////
//  Vulkan functions                                                          //
////////////////////////////////////////////////////////////////////////////////

// vkCreateInstance function
PFN_vkCreateInstance vkCreateInstance = 0;

// vkEnumerateInstanceExtensionProperties function
PFN_vkEnumerateInstanceExtensionProperties
    vkEnumerateInstanceExtensionProperties = 0;


// vkDestroyInstance function
PFN_vkDestroyInstance vkDestroyInstance = 0;

// vkEnumeratePhysicalDevices function
PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices = 0;

// vkGetPhysicalDeviceProperties function
PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties = 0;

// vkGetPhysicalDeviceFeatures function
PFN_vkGetPhysicalDeviceFeatures vkGetPhysicalDeviceFeatures = 0;

// vkGetPhysicalDeviceQueueFamilyProperties function
PFN_vkGetPhysicalDeviceQueueFamilyProperties
    vkGetPhysicalDeviceQueueFamilyProperties = 0;

// vkCreateDevice function
PFN_vkCreateDevice vkCreateDevice = 0;

// vkGetDeviceProcAddr function
PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr = 0;

// vkEnumerateDeviceExtensionProperties function
PFN_vkEnumerateDeviceExtensionProperties
    vkEnumerateDeviceExtensionProperties = 0;

// vkGetPhysicalDeviceMemoryProperties function
PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties = 0;


// vkDestroySurfaceKHR function
PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR = 0;

// vkGetPhysicalDeviceSurfaceSupportKHR function
PFN_vkGetPhysicalDeviceSurfaceSupportKHR
    vkGetPhysicalDeviceSurfaceSupportKHR = 0;

// vkGetPhysicalDeviceSurfaceCapabilitiesKHR function
PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR = 0;

// vkGetPhysicalDeviceSurfaceFormatsKHR function
PFN_vkGetPhysicalDeviceSurfaceFormatsKHR
    vkGetPhysicalDeviceSurfaceFormatsKHR = 0;

// vkGetPhysicalDeviceSurfacePresentModesKHR function
PFN_vkGetPhysicalDeviceSurfacePresentModesKHR
    vkGetPhysicalDeviceSurfacePresentModesKHR = 0;


// vkDestroyDevice function
PFN_vkDestroyDevice vkDestroyDevice = 0;

// vkDeviceWaitIdle function
PFN_vkDeviceWaitIdle vkDeviceWaitIdle = 0;

// vkGetDeviceQueue function
PFN_vkGetDeviceQueue vkGetDeviceQueue = 0;

// vkQueueSubmit function
PFN_vkQueueSubmit vkQueueSubmit = 0;

// vkQueueWaitIdle function
PFN_vkQueueWaitIdle vkQueueWaitIdle = 0;


////////////////////////////////////////////////////////////////////////////////
//  Load Vulkan global functions                                              //
//  return : True if Vulkan global functions are successfully loaded          //
////////////////////////////////////////////////////////////////////////////////
bool LoadVulkanGlobalFunctions()
{
    // Load vkCreateInstance
    vkCreateInstance = (PFN_vkCreateInstance)vkGetInstanceProcAddr(
        0, "vkCreateInstance"
    );
    if (!vkCreateInstance)
    {
        // Could not load vkCreateInstance
        return false;
    }

    // Load vkEnumerateInstanceExtensionProperties
    vkEnumerateInstanceExtensionProperties =
        (PFN_vkEnumerateInstanceExtensionProperties)vkGetInstanceProcAddr(
        0, "vkEnumerateInstanceExtensionProperties"
    );
    if (!vkEnumerateInstanceExtensionProperties)
    {
        // Could not load vkEnumerateInstanceExtensionProperties
        return false;
    }

    // Vulkan global functions successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create Vulkan instance                                                    //
//  return : True if Vulkan instance is successfully created                  //
////////////////////////////////////////////////////////////////////////////////
bool CreateVulkanInstance(VkInstance& vulkanInstance)
{
    // Check current Vulkan instance
    if (vulkanInstance)
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
    vulkanInstance = 0;
    if (vkCreateInstance(&createInfos, 0, &vulkanInstance) != VK_SUCCESS)
    {
        // Could not create Vulkan instance
        return false;
    }
    if (!vulkanInstance)
    {
        // Could not create Vulkan instance
        return false;
    }

    // Vulkan instance successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Load Vulkan instance functions                                            //
//  return : True if Vulkan instance functions are successfully loaded        //
////////////////////////////////////////////////////////////////////////////////
bool LoadVulkanInstanceFunctions(VkInstance& vulkanInstance)
{
    // Check Vulkan instance
    if (!vulkanInstance)
    {
        // Vulkan instance is invalid
        return false;
    }

    // Load vkDestroyInstance
    vkDestroyInstance = (PFN_vkDestroyInstance)
        vkGetInstanceProcAddr(vulkanInstance, "vkDestroyInstance"
    );
    if (!vkDestroyInstance)
    {
        // Could not load vkDestroyInstance
        return false;
    }

    // Load vkEnumeratePhysicalDevices
    vkEnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices)
        vkGetInstanceProcAddr(vulkanInstance, "vkEnumeratePhysicalDevices"
    );
    if (!vkEnumeratePhysicalDevices)
    {
        // Could not load vkEnumeratePhysicalDevices
        return false;
    }

    // Load vkGetPhysicalDeviceProperties
    vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties)
        vkGetInstanceProcAddr(vulkanInstance, "vkGetPhysicalDeviceProperties"
    );
    if (!vkGetPhysicalDeviceProperties)
    {
        // Could not load vkGetPhysicalDeviceProperties
        return false;
    }

    // Load vkGetPhysicalDeviceFeatures
    vkGetPhysicalDeviceFeatures = (PFN_vkGetPhysicalDeviceFeatures)
        vkGetInstanceProcAddr(vulkanInstance, "vkGetPhysicalDeviceFeatures"
    );
    if (!vkGetPhysicalDeviceFeatures)
    {
        // Could not load vkGetPhysicalDeviceFeatures
        return false;
    }

    // Load vkGetPhysicalDeviceQueueFamilyProperties
    vkGetPhysicalDeviceQueueFamilyProperties =
        (PFN_vkGetPhysicalDeviceQueueFamilyProperties)vkGetInstanceProcAddr(
        vulkanInstance, "vkGetPhysicalDeviceQueueFamilyProperties"
    );
    if (!vkGetPhysicalDeviceQueueFamilyProperties)
    {
        // Could not load vkGetPhysicalDeviceQueueFamilyProperties
        return false;
    }

    // Load vkCreateDevice
    vkCreateDevice = (PFN_vkCreateDevice)
        vkGetInstanceProcAddr(vulkanInstance, "vkCreateDevice"
    );
    if (!vkCreateDevice)
    {
        // Could not load vkCreateDevice
        return false;
    }

    // Load vkGetDeviceProcAddr
    vkGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr)
        vkGetInstanceProcAddr(vulkanInstance, "vkGetDeviceProcAddr"
    );
    if (!vkGetDeviceProcAddr)
    {
        // Could not load vkGetDeviceProcAddr
        return false;
    }

    // Load vkEnumerateDeviceExtensionProperties
    vkEnumerateDeviceExtensionProperties =
        (PFN_vkEnumerateDeviceExtensionProperties)vkGetInstanceProcAddr(
        vulkanInstance, "vkEnumerateDeviceExtensionProperties"
    );
    if (!vkEnumerateDeviceExtensionProperties)
    {
        // Could not load vkEnumerateDeviceExtensionProperties
        return false;
    }

    // Load vkEnumerateDeviceExtensionProperties
    vkGetPhysicalDeviceMemoryProperties =
        (PFN_vkGetPhysicalDeviceMemoryProperties)vkGetInstanceProcAddr(
        vulkanInstance, "vkGetPhysicalDeviceMemoryProperties"
    );
    if (!vkGetPhysicalDeviceMemoryProperties)
    {
        // Could not load vkGetPhysicalDeviceMemoryProperties
        return false;
    }


    // Load vkDestroySurfaceKHR
    vkDestroySurfaceKHR = (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(
        vulkanInstance, "vkDestroySurfaceKHR"
    );
    if (!vkDestroySurfaceKHR)
    {
        // Could not load vkDestroySurfaceKHR
        return false;
    }

    // Load vkGetPhysicalDeviceSurfaceSupportKHR
    vkGetPhysicalDeviceSurfaceSupportKHR =
        (PFN_vkGetPhysicalDeviceSurfaceSupportKHR)vkGetInstanceProcAddr(
        vulkanInstance, "vkGetPhysicalDeviceSurfaceSupportKHR"
    );
    if (!vkGetPhysicalDeviceSurfaceSupportKHR)
    {
        // Could not load vkGetPhysicalDeviceSurfaceSupportKHR
        return false;
    }

    // Load vkGetPhysicalDeviceSurfaceCapabilitiesKHR
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR =
        (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR)vkGetInstanceProcAddr(
        vulkanInstance, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR"
    );
    if (!vkGetPhysicalDeviceSurfaceCapabilitiesKHR)
    {
        // Could not load vkGetPhysicalDeviceSurfaceCapabilitiesKHR
        return false;
    }

    // Load vkGetPhysicalDeviceSurfaceFormatsKHR
    vkGetPhysicalDeviceSurfaceFormatsKHR =
        (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR)vkGetInstanceProcAddr(
        vulkanInstance, "vkGetPhysicalDeviceSurfaceFormatsKHR"
    );
    if (!vkGetPhysicalDeviceSurfaceFormatsKHR)
    {
        // Could not load vkGetPhysicalDeviceSurfaceFormatsKHR
        return false;
    }

    // Load vkGetPhysicalDeviceSurfacePresentModesKHR
    vkGetPhysicalDeviceSurfacePresentModesKHR =
        (PFN_vkGetPhysicalDeviceSurfacePresentModesKHR)vkGetInstanceProcAddr(
        vulkanInstance, "vkGetPhysicalDeviceSurfacePresentModesKHR"
    );
    if (!vkGetPhysicalDeviceSurfacePresentModesKHR)
    {
        // Could not load vkGetPhysicalDeviceSurfacePresentModesKHR
        return false;
    }


    // Vulkan instance functions successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Select Vulkan device                                                      //
//  return : True if Vulkan device is successfully selected                   //
////////////////////////////////////////////////////////////////////////////////
bool SelectVulkanDevice(
    VkInstance& vulkanInstance, VkSurfaceKHR& vulkanSurface,
    VkPhysicalDevice& physicalDevice, VkDevice& vulkanDevice)
{
    // Check Vulkan instance
    if (!vulkanInstance)
    {
        // Vulkan instance is invalid
        return false;
    }

    // Check physical device
    if (physicalDevice)
    {
        // Physical device already selected
        return false;
    }

    // Check Vulkan device
    if (vulkanDevice)
    {
        // Vulkan device already created
        return false;
    }

    // List devices
    uint32_t devicesCounts = 0;
    if (vkEnumeratePhysicalDevices(
        vulkanInstance, &devicesCounts, 0) != VK_SUCCESS)
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
        vulkanInstance, &devicesCounts, physicalDevices.data()) != VK_SUCCESS)
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
                vulkanSurface, &queueSurfaceSupport[j]) != VK_SUCCESS)
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

    physicalDevice = physicalDevices[deviceIndex];
    if (!physicalDevice)
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
        physicalDevice, &deviceInfos, 0, &vulkanDevice) != VK_SUCCESS)
    {
        // Could not create Vulkan device
        return false;
    }
    if (!vulkanDevice)
    {
        // Invalid Vulkan device pointer
        return false;
    }

    // Vulkan device successfully selected
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Load Vulkan device functions                                              //
//  return : True if Vulkan device functions are successfully loaded         //
////////////////////////////////////////////////////////////////////////////////
bool LoadVulkanDeviceFunctions(VkDevice& vulkanDevice)
{
    // Check Vulkan device
    if (!vulkanDevice)
    {
        // Vulkan device is invalid
        return false;
    }

    // Load vkDestroyDevice
    vkDestroyDevice = (PFN_vkDestroyDevice)vkGetDeviceProcAddr(
        vulkanDevice, "vkDestroyDevice"
    );
    if (!vkDestroyDevice)
    {
        // Could not load vkDestroyDevice
        return false;
    }

    // Load vkDeviceWaitIdle
    vkDeviceWaitIdle = (PFN_vkDeviceWaitIdle)vkGetDeviceProcAddr(
        vulkanDevice, "vkDeviceWaitIdle"
    );
    if (!vkDeviceWaitIdle)
    {
        // Could not load vkDeviceWaitIdle
        return false;
    }

    // Load vkGetDeviceQueue
    vkGetDeviceQueue = (PFN_vkGetDeviceQueue)vkGetDeviceProcAddr(
        vulkanDevice, "vkGetDeviceQueue"
    );
    if (!vkGetDeviceQueue)
    {
        // Could not load vkGetDeviceQueue
        return false;
    }

    // Load vkQueueSubmit
    vkQueueSubmit = (PFN_vkQueueSubmit)vkGetDeviceProcAddr(
        vulkanDevice, "vkQueueSubmit"
    );
    if (!vkQueueSubmit)
    {
        // Could not load vkQueueSubmit
        return false;
    }

    // Load vkQueueWaitIdle
    vkQueueWaitIdle = (PFN_vkQueueWaitIdle)vkGetDeviceProcAddr(
        vulkanDevice, "vkQueueWaitIdle"
    );
    if (!vkQueueWaitIdle)
    {
        // Could not load vkQueueWaitIdle
        return false;
    }

    // Vulkan device functions successfully loaded
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Destroy Vulkan device                                                     //
////////////////////////////////////////////////////////////////////////////////
void DestroyVulkanDevice(VkDevice& vulkanDevice)
{
    if (vulkanDevice && vkDestroyDevice)
    {
        vkDestroyDevice(vulkanDevice, 0);
        vulkanDevice = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy Vulkan surface                                                    //
////////////////////////////////////////////////////////////////////////////////
void DestroyVulkanSurface(
    VkInstance& vulkanInstance, VkSurfaceKHR& vulkanSurface)
{
    if (vulkanInstance && vulkanSurface && vkDestroySurfaceKHR)
    {
        // Destroy Vulkan surface
        vkDestroySurfaceKHR(vulkanInstance, vulkanSurface, 0);
        vulkanSurface = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy Vulkan instance                                                   //
////////////////////////////////////////////////////////////////////////////////
void DestroyVulkanInstance(VkInstance& vulkanInstance)
{
    if (vulkanInstance && vkDestroyInstance)
    {
        // Destroy Vulkan instance
        vkDestroyInstance(vulkanInstance, 0);
        vulkanInstance = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Free Vulkan functions                                                     //
////////////////////////////////////////////////////////////////////////////////
void FreeVulkanFunctions()
{
    // Free all Vulkan functions
    vkQueueWaitIdle = 0;
    vkQueueSubmit = 0;
    vkGetDeviceQueue = 0;
    vkDeviceWaitIdle = 0;
    vkDestroyDevice = 0;

    vkGetPhysicalDeviceSurfacePresentModesKHR = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR = 0;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR = 0;
    vkGetPhysicalDeviceSurfaceSupportKHR = 0;
    vkDestroySurfaceKHR = 0;

    vkGetPhysicalDeviceMemoryProperties = 0;
    vkEnumerateDeviceExtensionProperties = 0;
    vkGetDeviceProcAddr = 0;
    vkCreateDevice = 0;
    vkGetPhysicalDeviceQueueFamilyProperties = 0;
    vkGetPhysicalDeviceFeatures = 0;
    vkGetPhysicalDeviceProperties = 0;
    vkEnumeratePhysicalDevices = 0;
    vkDestroyInstance = 0;

    vkEnumerateInstanceExtensionProperties = 0;
    vkCreateInstance = 0;
}
