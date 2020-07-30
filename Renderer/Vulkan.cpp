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


// vkCreateSwapchainKHR function
PFN_vkCreateSwapchainKHR vkCreateSwapchainKHR = 0;

// vkDestroySwapchainKHR function
PFN_vkDestroySwapchainKHR vkDestroySwapchainKHR = 0;

// vkGetSwapchainImagesKHR function
PFN_vkGetSwapchainImagesKHR vkGetSwapchainImagesKHR = 0;

// vkAcquireNextImageKHR function
PFN_vkAcquireNextImageKHR vkAcquireNextImageKHR = 0;


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


    // Load vkCreateSwapchainKHR
    vkCreateSwapchainKHR = (PFN_vkCreateSwapchainKHR)vkGetDeviceProcAddr(
        vulkanDevice, "vkCreateSwapchainKHR"
    );
    if (!vkCreateSwapchainKHR)
    {
        // Could not load vkCreateSwapchainKHR
        return false;
    }

    // Load vkDestroySwapchainKHR
    vkDestroySwapchainKHR = (PFN_vkDestroySwapchainKHR)vkGetDeviceProcAddr(
        vulkanDevice, "vkDestroySwapchainKHR"
    );
    if (!vkDestroySwapchainKHR)
    {
        // Could not load vkDestroySwapchainKHR
        return false;
    }

    // Load vkGetSwapchainImagesKHR
    vkGetSwapchainImagesKHR = (PFN_vkGetSwapchainImagesKHR)vkGetDeviceProcAddr(
        vulkanDevice, "vkGetSwapchainImagesKHR"
    );
    if (!vkGetSwapchainImagesKHR)
    {
        // Could not load vkGetSwapchainImagesKHR
        return false;
    }


    // Load vkAcquireNextImageKHR
    vkAcquireNextImageKHR = (PFN_vkAcquireNextImageKHR)vkGetDeviceProcAddr(
        vulkanDevice, "vkAcquireNextImageKHR"
    );
    if (!vkAcquireNextImageKHR)
    {
        // Could not load vkAcquireNextImageKHR
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

    vkAcquireNextImageKHR = 0;
    vkGetSwapchainImagesKHR = 0;
    vkDestroySwapchainKHR = 0;
    vkCreateSwapchainKHR = 0;

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
