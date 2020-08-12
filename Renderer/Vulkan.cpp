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

// vkQueuePresentKHR function
PFN_vkQueuePresentKHR vkQueuePresentKHR = 0;


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


// vkAllocateMemory function
PFN_vkAllocateMemory vkAllocateMemory = 0;

// vkFreeMemory function
PFN_vkFreeMemory vkFreeMemory = 0;

// vkMapMemory function
PFN_vkMapMemory vkMapMemory = 0;

// vkUnmapMemory function
PFN_vkUnmapMemory vkUnmapMemory = 0;

// vkFlushMappedMemoryRanges function
PFN_vkFlushMappedMemoryRanges vkFlushMappedMemoryRanges = 0;

// vkBindBufferMemory function
PFN_vkBindBufferMemory vkBindBufferMemory = 0;


// vkCreateRenderPass function
PFN_vkCreateRenderPass vkCreateRenderPass = 0;

// vkDestroyRenderPass function
PFN_vkDestroyRenderPass vkDestroyRenderPass = 0;

// vkCreateFramebuffer function
PFN_vkCreateFramebuffer vkCreateFramebuffer = 0;

// vkDestroyFramebuffer function
PFN_vkDestroyFramebuffer vkDestroyFramebuffer = 0;

// vkCreateImageView function 
PFN_vkCreateImageView vkCreateImageView = 0;

// vkDestroyImageView function
PFN_vkDestroyImageView vkDestroyImageView = 0;

// vkCreateShaderModule function
PFN_vkCreateShaderModule vkCreateShaderModule = 0;

// vkDestroyShaderModule function
PFN_vkDestroyShaderModule vkDestroyShaderModule = 0;

// vkCreatePipelineLayout function
PFN_vkCreatePipelineLayout vkCreatePipelineLayout = 0;

// vkDestroyPipelineLayout function
PFN_vkDestroyPipelineLayout vkDestroyPipelineLayout = 0;

// vkCreateGraphicsPipelines function
PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines = 0;

// vkDestroyPipeline function
PFN_vkDestroyPipeline vkDestroyPipeline = 0;

// vkCreateSemaphore function
PFN_vkCreateSemaphore vkCreateSemaphore = 0;

// vkDestroySemaphore function
PFN_vkDestroySemaphore vkDestroySemaphore = 0;

// vkCreateBuffer function
PFN_vkCreateBuffer vkCreateBuffer = 0;

// vkDestroyBuffer function
PFN_vkDestroyBuffer vkDestroyBuffer = 0;

// vkGetBufferMemoryRequirements function
PFN_vkGetBufferMemoryRequirements vkGetBufferMemoryRequirements = 0;

// vkCreateFence function
PFN_vkCreateFence vkCreateFence = 0;

// vkDestroyFence function
PFN_vkDestroyFence vkDestroyFence = 0;

// vkResetFences function
PFN_vkResetFences vkResetFences = 0;

// vkGetFenceStatus function
PFN_vkGetFenceStatus vkGetFenceStatus = 0;

// vkCreateCommandPool function
PFN_vkCreateCommandPool vkCreateCommandPool = 0;

// vkDestroyCommandPool function
PFN_vkDestroyCommandPool vkDestroyCommandPool = 0;

// vkResetCommandPool function
PFN_vkResetCommandPool vkResetCommandPool = 0;

// vkAllocateCommandBuffers function
PFN_vkAllocateCommandBuffers vkAllocateCommandBuffers = 0;

// vkFreeCommandBuffers function
PFN_vkFreeCommandBuffers vkFreeCommandBuffers = 0;

// vkBeginCommandBuffer function
PFN_vkBeginCommandBuffer vkBeginCommandBuffer = 0;

// vkEndCommandBuffer function
PFN_vkEndCommandBuffer vkEndCommandBuffer = 0;

// vkResetCommandBuffer function
PFN_vkResetCommandBuffer vkResetCommandBuffer = 0;

// vkCmdBindPipeline function
PFN_vkCmdBindPipeline vkCmdBindPipeline = 0;

// vkCmdSetViewport function
PFN_vkCmdSetViewport vkCmdSetViewport = 0;

// vkCmdSetScissor function
PFN_vkCmdSetScissor vkCmdSetScissor = 0;

// vkCmdBindVertexBuffers function
PFN_vkCmdBindVertexBuffers vkCmdBindVertexBuffers = 0;

// vkCmdDraw function
PFN_vkCmdDraw vkCmdDraw = 0;

// vkCmdClearColorImage function
PFN_vkCmdClearColorImage vkCmdClearColorImage = 0;

// vkCmdPipelineBarrier function
PFN_vkCmdPipelineBarrier vkCmdPipelineBarrier = 0;

// vkCmdBeginRenderPass function
PFN_vkCmdBeginRenderPass vkCmdBeginRenderPass = 0;

// vkCmdEndRenderPass function
PFN_vkCmdEndRenderPass vkCmdEndRenderPass = 0;


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

    // Load vkQueuePresentKHR
    vkQueuePresentKHR = (PFN_vkQueuePresentKHR)vkGetDeviceProcAddr(
        vulkanDevice, "vkQueuePresentKHR"
    );
    if (!vkQueuePresentKHR)
    {
        // Could not load vkQueuePresentKHR
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


    // Load vkAllocateMemory
    vkAllocateMemory = (PFN_vkAllocateMemory)vkGetDeviceProcAddr(
        vulkanDevice, "vkAllocateMemory"
    );
    if (!vkAllocateMemory)
    {
        // Could not load vkAllocateMemory
        return false;
    }

    // Load vkFreeMemory
    vkFreeMemory = (PFN_vkFreeMemory)vkGetDeviceProcAddr(
        vulkanDevice, "vkFreeMemory"
    );
    if (!vkFreeMemory)
    {
        // Could not load vkFreeMemory
        return false;
    }

    // Load vkMapMemory
    vkMapMemory = (PFN_vkMapMemory)vkGetDeviceProcAddr(
        vulkanDevice, "vkMapMemory"
    );
    if (!vkMapMemory)
    {
        // Could not load vkMapMemory
        return false;
    }

    // Load vkUnmapMemory
    vkUnmapMemory = (PFN_vkUnmapMemory)vkGetDeviceProcAddr(
        vulkanDevice, "vkUnmapMemory"
    );
    if (!vkUnmapMemory)
    {
        // Could not load vkUnmapMemory
        return false;
    }

    // Load vkFlushMappedMemoryRanges
    vkFlushMappedMemoryRanges =
        (PFN_vkFlushMappedMemoryRanges)vkGetDeviceProcAddr(
        vulkanDevice, "vkFlushMappedMemoryRanges"
    );
    if (!vkFlushMappedMemoryRanges)
    {
        // Could not load vkFlushMappedMemoryRanges
        return false;
    }

    // Load vkBindBufferMemory
    vkBindBufferMemory = (PFN_vkBindBufferMemory)vkGetDeviceProcAddr(
        vulkanDevice, "vkBindBufferMemory"
    );
    if (!vkBindBufferMemory)
    {
        // Could not load vkBindBufferMemory
        return false;
    }


    // Load vkCreateRenderPass
    vkCreateRenderPass = (PFN_vkCreateRenderPass)vkGetDeviceProcAddr(
        vulkanDevice, "vkCreateRenderPass"
    );
    if (!vkCreateRenderPass)
    {
        // Could not load vkCreateRenderPass
        return false;
    }

    // Load vkDestroyRenderPass
    vkDestroyRenderPass = (PFN_vkDestroyRenderPass)vkGetDeviceProcAddr(
        vulkanDevice, "vkDestroyRenderPass"
    );
    if (!vkDestroyRenderPass)
    {
        // Could not load vkDestroyRenderPass
        return false;
    }

    // Load vkCreateFramebuffer
    vkCreateFramebuffer = (PFN_vkCreateFramebuffer)vkGetDeviceProcAddr(
        vulkanDevice, "vkCreateFramebuffer"
    );
    if (!vkCreateFramebuffer)
    {
        // Could not load vkCreateFramebuffer
        return false;
    }

    // Load vkDestroyFramebuffer
    vkDestroyFramebuffer = (PFN_vkDestroyFramebuffer)vkGetDeviceProcAddr(
        vulkanDevice, "vkDestroyFramebuffer"
    );
    if (!vkDestroyFramebuffer)
    {
        // Could not load vkDestroyFramebuffer
        return false;
    }

    // Load vkCreateImageView
    vkCreateImageView = (PFN_vkCreateImageView)vkGetDeviceProcAddr(
        vulkanDevice, "vkCreateImageView"
    );
    if (!vkCreateImageView)
    {
        // Could not load vkCreateImageView
        return false;
    }

    // Load vkDestroyImageView
    vkDestroyImageView = (PFN_vkDestroyImageView)vkGetDeviceProcAddr(
        vulkanDevice, "vkDestroyImageView"
    );
    if (!vkDestroyImageView)
    {
        // Could not load vkDestroyImageView
        return false;
    }

    // Load vkCreateShaderModule
    vkCreateShaderModule = (PFN_vkCreateShaderModule)vkGetDeviceProcAddr(
        vulkanDevice, "vkCreateShaderModule"
    );
    if (!vkCreateShaderModule)
    {
        // Could not load vkCreateShaderModule
        return false;
    }

    // Load vkDestroyShaderModule
    vkDestroyShaderModule = (PFN_vkDestroyShaderModule)vkGetDeviceProcAddr(
        vulkanDevice, "vkDestroyShaderModule"
    );
    if (!vkDestroyShaderModule)
    {
        // Could not load vkDestroyShaderModule
        return false;
    }

    // Load vkCreatePipelineLayout
    vkCreatePipelineLayout = (PFN_vkCreatePipelineLayout)vkGetDeviceProcAddr(
        vulkanDevice, "vkCreatePipelineLayout"
    );
    if (!vkCreatePipelineLayout)
    {
        // Could not load vkCreatePipelineLayout
        return false;
    }

    // Load vkDestroyPipelineLayout
    vkDestroyPipelineLayout = (PFN_vkDestroyPipelineLayout)vkGetDeviceProcAddr(
        vulkanDevice, "vkDestroyPipelineLayout"
    );
    if (!vkDestroyPipelineLayout)
    {
        // Could not load vkDestroyPipelineLayout
        return false;
    }

    // Load vkCreateGraphicsPipelines
    vkCreateGraphicsPipelines =
        (PFN_vkCreateGraphicsPipelines)vkGetDeviceProcAddr(
        vulkanDevice, "vkCreateGraphicsPipelines"
    );
    if (!vkCreateGraphicsPipelines)
    {
        // Could not load vkCreateGraphicsPipelines
        return false;
    }

    // Load vkDestroyPipeline
    vkDestroyPipeline = (PFN_vkDestroyPipeline)vkGetDeviceProcAddr(
        vulkanDevice, "vkDestroyPipeline"
    );
    if (!vkDestroyPipeline)
    {
        // Could not load vkDestroyPipeline
        return false;
    }

    // Load vkCreateSemaphore
    vkCreateSemaphore = (PFN_vkCreateSemaphore)vkGetDeviceProcAddr(
        vulkanDevice, "vkCreateSemaphore"
    );
    if (!vkCreateSemaphore)
    {
        // Could not load vkCreateSemaphore
        return false;
    }

    // Load vkDestroySemaphore
    vkDestroySemaphore = (PFN_vkDestroySemaphore)vkGetDeviceProcAddr(
        vulkanDevice, "vkDestroySemaphore"
    );
    if (!vkDestroySemaphore)
    {
        // Could not load vkDestroySemaphore
        return false;
    }

    // Load vkCreateBuffer
    vkCreateBuffer = (PFN_vkCreateBuffer)vkGetDeviceProcAddr(
        vulkanDevice, "vkCreateBuffer"
    );
    if (!vkCreateBuffer)
    {
        // Could not load vkCreateBuffer
        return false;
    }

    // Load vkDestroyBuffer
    vkDestroyBuffer = (PFN_vkDestroyBuffer)vkGetDeviceProcAddr(
        vulkanDevice, "vkDestroyBuffer"
    );
    if (!vkDestroyBuffer)
    {
        // Could not load vkDestroyBuffer
        return false;
    }

    // Load vkGetBufferMemoryRequirements
    vkGetBufferMemoryRequirements =
        (PFN_vkGetBufferMemoryRequirements)vkGetDeviceProcAddr(
        vulkanDevice, "vkGetBufferMemoryRequirements"
    );
    if (!vkGetBufferMemoryRequirements)
    {
        // Could not load vkGetBufferMemoryRequirements
        return false;
    }

    // Load vkCreateFence
    vkCreateFence = (PFN_vkCreateFence)vkGetDeviceProcAddr(
        vulkanDevice, "vkCreateFence"
    );
    if (!vkCreateFence)
    {
        // Could not load vkCreateFence
        return false;
    }

    // Load vkDestroyFence
    vkDestroyFence = (PFN_vkDestroyFence)vkGetDeviceProcAddr(
        vulkanDevice, "vkDestroyFence"
    );
    if (!vkDestroyFence)
    {
        // Could not load vkDestroyFence
        return false;
    }

    // Load vkResetFences
    vkResetFences = (PFN_vkResetFences)vkGetDeviceProcAddr(
        vulkanDevice, "vkResetFences"
    );
    if (!vkResetFences)
    {
        // Could not load vkResetFences
        return false;
    }

    // Load vkGetFenceStatus
    vkGetFenceStatus = (PFN_vkGetFenceStatus)vkGetDeviceProcAddr(
        vulkanDevice, "vkGetFenceStatus"
    );
    if (!vkGetFenceStatus)
    {
        // Could not load vkGetFenceStatus
        return false;
    }

    // Load vkCreateCommandPool
    vkCreateCommandPool = (PFN_vkCreateCommandPool)vkGetDeviceProcAddr(
        vulkanDevice, "vkCreateCommandPool"
    );
    if (!vkCreateCommandPool)
    {
        // Could not load vkCreateCommandPool
        return false;
    }

    // Load vkDestroyCommandPool
    vkDestroyCommandPool = (PFN_vkDestroyCommandPool)vkGetDeviceProcAddr(
        vulkanDevice, "vkDestroyCommandPool"
    );
    if (!vkDestroyCommandPool)
    {
        // Could not load vkDestroyCommandPool
        return false;
    }

    // Load vkResetCommandPool
    vkResetCommandPool = (PFN_vkResetCommandPool)vkGetDeviceProcAddr(
        vulkanDevice, "vkResetCommandPool"
    );
    if (!vkResetCommandPool)
    {
        // Could not load vkResetCommandPool
        return false;
    }

    // Load vkAllocateCommandBuffers
    vkAllocateCommandBuffers = (PFN_vkAllocateCommandBuffers)
        vkGetDeviceProcAddr(vulkanDevice, "vkAllocateCommandBuffers"
    );
    if (!vkAllocateCommandBuffers)
    {
        // Could not load vkAllocateCommandBuffers
        return false;
    }

    // Load vkFreeCommandBuffers
    vkFreeCommandBuffers = (PFN_vkFreeCommandBuffers)vkGetDeviceProcAddr(
        vulkanDevice, "vkFreeCommandBuffers"
    );
    if (!vkFreeCommandBuffers)
    {
        // Could not load vkFreeCommandBuffers
        return false;
    }

    // Load vkBeginCommandBuffer
    vkBeginCommandBuffer = (PFN_vkBeginCommandBuffer)vkGetDeviceProcAddr(
        vulkanDevice, "vkBeginCommandBuffer"
    );
    if (!vkBeginCommandBuffer)
    {
        // Could not load vkBeginCommandBuffer
        return false;
    }

    // Load vkBeginCommandBuffer
    vkEndCommandBuffer = (PFN_vkEndCommandBuffer)vkGetDeviceProcAddr(
        vulkanDevice, "vkEndCommandBuffer"
    );
    if (!vkEndCommandBuffer)
    {
        // Could not load vkEndCommandBuffer
        return false;
    }

    // Load vkResetCommandBuffer
    vkResetCommandBuffer = (PFN_vkResetCommandBuffer)vkGetDeviceProcAddr(
        vulkanDevice, "vkResetCommandBuffer"
    );
    if (!vkResetCommandBuffer)
    {
        // Could not load vkResetCommandBuffer
        return false;
    }

    // Load vkCmdBindPipeline
    vkCmdBindPipeline = (PFN_vkCmdBindPipeline)vkGetDeviceProcAddr(
        vulkanDevice, "vkCmdBindPipeline"
    );
    if (!vkCmdBindPipeline)
    {
        // Could not load vkCmdBindPipeline
        return false;
    }

    // Load vkCmdSetViewport
    vkCmdSetViewport = (PFN_vkCmdSetViewport)vkGetDeviceProcAddr(
        vulkanDevice, "vkCmdSetViewport"
    );
    if (!vkCmdSetViewport)
    {
        // Could not load vkCmdSetViewport
        return false;
    }

    // Load vkCmdSetScissor
    vkCmdSetScissor = (PFN_vkCmdSetScissor)vkGetDeviceProcAddr(
        vulkanDevice, "vkCmdSetScissor"
    );
    if (!vkCmdSetScissor)
    {
        // Could not load vkCmdSetScissor
        return false;
    }

    // Load vkCmdBindVertexBuffers
    vkCmdBindVertexBuffers = (PFN_vkCmdBindVertexBuffers)vkGetDeviceProcAddr(
        vulkanDevice, "vkCmdBindVertexBuffers"
    );
    if (!vkCmdBindVertexBuffers)
    {
        // Could not load vkCmdBindVertexBuffers
        return false;
    }

    // Load vkCmdDraw
    vkCmdDraw = (PFN_vkCmdDraw)vkGetDeviceProcAddr(vulkanDevice, "vkCmdDraw");
    if (!vkCmdDraw)
    {
        // Could not load vkCmdDraw
        return false;
    }

    // Load vkCmdClearColorImage
    vkCmdClearColorImage = (PFN_vkCmdClearColorImage)
        vkGetDeviceProcAddr(vulkanDevice, "vkCmdClearColorImage"
    );
    if (!vkCmdClearColorImage)
    {
        // Could not load vkCmdClearColorImage
        return false;
    }

    // Load vkCmdPipelineBarrier
    vkCmdPipelineBarrier = (PFN_vkCmdPipelineBarrier)
        vkGetDeviceProcAddr(vulkanDevice, "vkCmdPipelineBarrier"
    );
    if (!vkCmdPipelineBarrier)
    {
        // Could not load vkCmdPipelineBarrier
        return false;
    }

    // Load vkCmdBeginRenderPass
    vkCmdBeginRenderPass = (PFN_vkCmdBeginRenderPass)
        vkGetDeviceProcAddr(vulkanDevice, "vkCmdBeginRenderPass"
    );
    if (!vkCmdBeginRenderPass)
    {
        // Could not load vkCmdBeginRenderPass
        return false;
    }

    // Load vkCmdEndRenderPass
    vkCmdEndRenderPass = (PFN_vkCmdEndRenderPass)
        vkGetDeviceProcAddr(vulkanDevice, "vkCmdEndRenderPass"
    );
    if (!vkCmdEndRenderPass)
    {
        // Could not load vkCmdEndRenderPass
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
    vkCmdEndRenderPass = 0;
    vkCmdBeginRenderPass = 0;
    vkCmdPipelineBarrier = 0;
    vkCmdClearColorImage = 0;
    vkCmdDraw = 0;
    vkCmdBindVertexBuffers = 0;
    vkCmdSetScissor = 0;
    vkCmdSetViewport = 0;
    vkCmdBindPipeline = 0;
    vkResetCommandBuffer = 0;
    vkEndCommandBuffer = 0;
    vkBeginCommandBuffer = 0;
    vkFreeCommandBuffers = 0;
    vkAllocateCommandBuffers = 0;
    vkResetCommandPool = 0;
    vkDestroyCommandPool = 0;
    vkCreateCommandPool = 0;
    vkGetFenceStatus = 0;
    vkResetFences = 0;
    vkDestroyFence = 0;
    vkCreateFence = 0;
    vkGetBufferMemoryRequirements = 0;
    vkDestroyBuffer = 0;
    vkCreateBuffer = 0;
    vkDestroySemaphore = 0;
    vkCreateSemaphore = 0;
    vkDestroyPipeline = 0;
    vkCreateGraphicsPipelines = 0;
    vkDestroyPipelineLayout = 0;
    vkCreatePipelineLayout = 0;
    vkDestroyShaderModule = 0;
    vkCreateShaderModule = 0;
    vkDestroyImageView = 0;
    vkCreateImageView = 0;
    vkDestroyFramebuffer = 0;
    vkCreateFramebuffer = 0;
    vkDestroyRenderPass = 0;
    vkCreateRenderPass = 0;

    vkBindBufferMemory = 0;
    vkFlushMappedMemoryRanges = 0;
    vkUnmapMemory = 0;
    vkMapMemory = 0;
    vkFreeMemory = 0;
    vkAllocateMemory = 0;

    vkQueueWaitIdle = 0;
    vkQueueSubmit = 0;
    vkGetDeviceQueue = 0;
    vkDeviceWaitIdle = 0;
    vkDestroyDevice = 0;

    vkQueuePresentKHR = 0;
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
