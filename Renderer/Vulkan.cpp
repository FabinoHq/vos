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

// vkEnumerateInstanceLayerProperties function
PFN_vkEnumerateInstanceLayerProperties vkEnumerateInstanceLayerProperties = 0;


// vkDestroyInstance function
PFN_vkDestroyInstance vkDestroyInstance = 0;

// vkEnumeratePhysicalDevices function
PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices = 0;

// vkGetPhysicalDeviceProperties function
PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties = 0;

// vkGetPhysicalDeviceFeatures function
PFN_vkGetPhysicalDeviceFeatures vkGetPhysicalDeviceFeatures = 0;

// vkGetPhysicalDeviceFormatProperties function
PFN_vkGetPhysicalDeviceFormatProperties vkGetPhysicalDeviceFormatProperties = 0;

// vkGetPhysicalDeviceImageFormatProperties function
PFN_vkGetPhysicalDeviceImageFormatProperties
    vkGetPhysicalDeviceImageFormatProperties = 0;

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

// vkEnumerateDeviceLayerProperties function
PFN_vkEnumerateDeviceLayerProperties vkEnumerateDeviceLayerProperties = 0;

// vkGetPhysicalDeviceMemoryProperties function
PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties = 0;

// vkGetPhysicalDeviceSparseImageFormatProperties function
PFN_vkGetPhysicalDeviceSparseImageFormatProperties
    vkGetPhysicalDeviceSparseImageFormatProperties = 0;


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

// vkInvalidateMappedMemoryRanges function
PFN_vkInvalidateMappedMemoryRanges vkInvalidateMappedMemoryRanges = 0;

// vkGetDeviceMemoryCommitment function
PFN_vkGetDeviceMemoryCommitment vkGetDeviceMemoryCommitment = 0;

// vkBindBufferMemory function
PFN_vkBindBufferMemory vkBindBufferMemory = 0;

// vkBindImageMemory function
PFN_vkBindImageMemory vkBindImageMemory = 0;


// vkCreateRenderPass function
PFN_vkCreateRenderPass vkCreateRenderPass = 0;

// vkDestroyRenderPass function
PFN_vkDestroyRenderPass vkDestroyRenderPass = 0;

// vkGetRenderAreaGranularity function
PFN_vkGetRenderAreaGranularity vkGetRenderAreaGranularity = 0;

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

// vkCreatePipelineCache function
PFN_vkCreatePipelineCache vkCreatePipelineCache = 0;

// vkDestroyPipelineCache function
PFN_vkDestroyPipelineCache vkDestroyPipelineCache = 0;

// vkGetPipelineCacheData function
PFN_vkGetPipelineCacheData vkGetPipelineCacheData = 0;

// vkMergePipelineCaches function
PFN_vkMergePipelineCaches vkMergePipelineCaches = 0;

// vkCreatePipelineLayout function
PFN_vkCreatePipelineLayout vkCreatePipelineLayout = 0;

// vkDestroyPipelineLayout function
PFN_vkDestroyPipelineLayout vkDestroyPipelineLayout = 0;

// vkCreateSampler function
PFN_vkCreateSampler vkCreateSampler = 0;

// vkDestroySampler function
PFN_vkDestroySampler vkDestroySampler = 0;

// vkCreateGraphicsPipelines function
PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines = 0;

// vkCreateComputePipelines function
PFN_vkCreateComputePipelines vkCreateComputePipelines = 0;

// vkDestroyPipeline function
PFN_vkDestroyPipeline vkDestroyPipeline = 0;

// vkCreateDescriptorSetLayout function
PFN_vkCreateDescriptorSetLayout vkCreateDescriptorSetLayout = 0;

// vkDestroyDescriptorSetLayout function
PFN_vkDestroyDescriptorSetLayout vkDestroyDescriptorSetLayout = 0;

// vkCreateDescriptorPool function
PFN_vkCreateDescriptorPool vkCreateDescriptorPool = 0;

// vkDestroyDescriptorPool function
PFN_vkDestroyDescriptorPool vkDestroyDescriptorPool = 0;

// vkResetDescriptorPool function
PFN_vkResetDescriptorPool vkResetDescriptorPool = 0;

// vkAllocateDescriptorSets function
PFN_vkAllocateDescriptorSets vkAllocateDescriptorSets = 0;

// vkFreeDescriptorSets function
PFN_vkFreeDescriptorSets vkFreeDescriptorSets = 0;

// vkUpdateDescriptorSets function
PFN_vkUpdateDescriptorSets vkUpdateDescriptorSets = 0;

// vkCreateBuffer function
PFN_vkCreateBuffer vkCreateBuffer = 0;

// vkDestroyBuffer function
PFN_vkDestroyBuffer vkDestroyBuffer = 0;

// vkCreateBufferView function
PFN_vkCreateBufferView vkCreateBufferView = 0;

// vkDestroyBufferView function
PFN_vkDestroyBufferView vkDestroyBufferView = 0;

// vkCreateImage function
PFN_vkCreateImage vkCreateImage = 0;

// vkDestroyImage function
PFN_vkDestroyImage vkDestroyImage = 0;

// vkGetImageSubresourceLayout function
PFN_vkGetImageSubresourceLayout vkGetImageSubresourceLayout = 0;

// vkGetBufferMemoryRequirements function
PFN_vkGetBufferMemoryRequirements vkGetBufferMemoryRequirements = 0;

// vkGetImageMemoryRequirements function
PFN_vkGetImageMemoryRequirements vkGetImageMemoryRequirements = 0;

// vkGetImageSparseMemoryRequirements function
PFN_vkGetImageSparseMemoryRequirements vkGetImageSparseMemoryRequirements = 0;

// vkQueueBindSparse function
PFN_vkQueueBindSparse vkQueueBindSparse = 0;

// vkCreateFence function
PFN_vkCreateFence vkCreateFence = 0;

// vkDestroyFence function
PFN_vkDestroyFence vkDestroyFence = 0;

// vkResetFences function
PFN_vkResetFences vkResetFences = 0;

// vkGetFenceStatus function
PFN_vkGetFenceStatus vkGetFenceStatus = 0;

// vkWaitForFences function
PFN_vkWaitForFences vkWaitForFences = 0;

// vkCreateSemaphore function
PFN_vkCreateSemaphore vkCreateSemaphore = 0;

// vkDestroySemaphore function
PFN_vkDestroySemaphore vkDestroySemaphore = 0;

// vkCreateEvent function
PFN_vkCreateEvent vkCreateEvent = 0;

// vkDestroyEvent function
PFN_vkDestroyEvent vkDestroyEvent = 0;

// vkGetEventStatus function
PFN_vkGetEventStatus vkGetEventStatus = 0;

// vkSetEvent function
PFN_vkSetEvent vkSetEvent = 0;

// vkResetEvent function
PFN_vkResetEvent vkResetEvent = 0;

// vkCreateQueryPool function
PFN_vkCreateQueryPool vkCreateQueryPool = 0;

// vkDestroyQueryPool function
PFN_vkDestroyQueryPool vkDestroyQueryPool = 0;

// vkGetQueryPoolResults function
PFN_vkGetQueryPoolResults vkGetQueryPoolResults = 0;

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

// vkCmdSetLineWidth function
PFN_vkCmdSetLineWidth vkCmdSetLineWidth = 0;

// vkCmdSetDepthBias function
PFN_vkCmdSetDepthBias vkCmdSetDepthBias = 0;

// vkCmdSetBlendConstants function
PFN_vkCmdSetBlendConstants vkCmdSetBlendConstants = 0;

// vkCmdSetDepthBounds function
PFN_vkCmdSetDepthBounds vkCmdSetDepthBounds = 0;

// vkCmdSetStencilCompareMask function
PFN_vkCmdSetStencilCompareMask vkCmdSetStencilCompareMask = 0;

// vkCmdSetStencilWriteMask function
PFN_vkCmdSetStencilWriteMask vkCmdSetStencilWriteMask = 0;

// vkCmdSetStencilReference function
PFN_vkCmdSetStencilReference vkCmdSetStencilReference = 0;

// vkCmdBindDescriptorSets function
PFN_vkCmdBindDescriptorSets vkCmdBindDescriptorSets = 0;

// vkCmdBindIndexBuffer function
PFN_vkCmdBindIndexBuffer vkCmdBindIndexBuffer = 0;

// vkCmdBindVertexBuffers function
PFN_vkCmdBindVertexBuffers vkCmdBindVertexBuffers = 0;

// vkCmdDraw function
PFN_vkCmdDraw vkCmdDraw = 0;

// vkCmdDrawIndexed function
PFN_vkCmdDrawIndexed vkCmdDrawIndexed = 0;

// vkCmdDrawIndirect function
PFN_vkCmdDrawIndirect vkCmdDrawIndirect = 0;

// vkCmdDrawIndexedIndirect function
PFN_vkCmdDrawIndexedIndirect vkCmdDrawIndexedIndirect = 0;

// vkCmdDispatch function
PFN_vkCmdDispatch vkCmdDispatch = 0;

// vkCmdDispatchIndirect function
PFN_vkCmdDispatchIndirect vkCmdDispatchIndirect = 0;

// vkCmdCopyBuffer function
PFN_vkCmdCopyBuffer vkCmdCopyBuffer = 0;

// vkCmdCopyImage function
PFN_vkCmdCopyImage vkCmdCopyImage = 0;

// vkCmdBlitImage function
PFN_vkCmdBlitImage vkCmdBlitImage = 0;

// vkCmdCopyBufferToImage function
PFN_vkCmdCopyBufferToImage vkCmdCopyBufferToImage = 0;

// vkCmdCopyImageToBuffer function
PFN_vkCmdCopyImageToBuffer vkCmdCopyImageToBuffer = 0;

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

    // Load vkEnumerateInstanceLayerProperties
    vkEnumerateInstanceLayerProperties =
        (PFN_vkEnumerateInstanceLayerProperties)vkGetInstanceProcAddr(
        0, "vkEnumerateInstanceLayerProperties"
    );
    if (!vkEnumerateInstanceLayerProperties)
    {
        // Could not load vkEnumerateInstanceLayerProperties
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

    // Load vkGetPhysicalDeviceFormatProperties
    vkGetPhysicalDeviceFormatProperties =
        (PFN_vkGetPhysicalDeviceFormatProperties)vkGetInstanceProcAddr(
        vulkanInstance, "vkGetPhysicalDeviceFormatProperties"
    );
    if (!vkGetPhysicalDeviceFormatProperties)
    {
        // Could not load vkGetPhysicalDeviceFormatProperties
        return false;
    }

    // Load vkGetPhysicalDeviceImageFormatProperties
    vkGetPhysicalDeviceImageFormatProperties =
        (PFN_vkGetPhysicalDeviceImageFormatProperties)vkGetInstanceProcAddr(
        vulkanInstance, "vkGetPhysicalDeviceImageFormatProperties"
    );
    if (!vkGetPhysicalDeviceImageFormatProperties)
    {
        // Could not load vkGetPhysicalDeviceImageFormatProperties
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

    // Load vkEnumerateDeviceLayerProperties
    vkEnumerateDeviceLayerProperties =
        (PFN_vkEnumerateDeviceLayerProperties)vkGetInstanceProcAddr(
        vulkanInstance, "vkEnumerateDeviceLayerProperties"
    );
    if (!vkEnumerateDeviceLayerProperties)
    {
        // Could not load vkEnumerateDeviceLayerProperties
        return false;
    }

    // Load vkGetPhysicalDeviceMemoryProperties
    vkGetPhysicalDeviceMemoryProperties =
        (PFN_vkGetPhysicalDeviceMemoryProperties)vkGetInstanceProcAddr(
        vulkanInstance, "vkGetPhysicalDeviceMemoryProperties"
    );
    if (!vkGetPhysicalDeviceMemoryProperties)
    {
        // Could not load vkGetPhysicalDeviceMemoryProperties
        return false;
    }

    // Load vkGetPhysicalDeviceSparseImageFormatProperties
    vkGetPhysicalDeviceSparseImageFormatProperties =
        (PFN_vkGetPhysicalDeviceSparseImageFormatProperties)
        vkGetInstanceProcAddr(vulkanInstance,
        "vkGetPhysicalDeviceSparseImageFormatProperties"
    );
    if (!vkGetPhysicalDeviceSparseImageFormatProperties)
    {
        // Could not load vkGetPhysicalDeviceSparseImageFormatProperties
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
    vkFlushMappedMemoryRanges = (PFN_vkFlushMappedMemoryRanges)
        vkGetDeviceProcAddr(vulkanDevice, "vkFlushMappedMemoryRanges"
    );
    if (!vkFlushMappedMemoryRanges)
    {
        // Could not load vkFlushMappedMemoryRanges
        return false;
    }

    // Load vkInvalidateMappedMemoryRanges
    vkInvalidateMappedMemoryRanges = (PFN_vkInvalidateMappedMemoryRanges)
        vkGetDeviceProcAddr(vulkanDevice, "vkInvalidateMappedMemoryRanges"
    );
    if (!vkInvalidateMappedMemoryRanges)
    {
        // Could not load vkInvalidateMappedMemoryRanges
        return false;
    }

    // Load vkGetDeviceMemoryCommitment
    vkGetDeviceMemoryCommitment = (PFN_vkGetDeviceMemoryCommitment)
        vkGetDeviceProcAddr(vulkanDevice, "vkGetDeviceMemoryCommitment"
    );
    if (!vkGetDeviceMemoryCommitment)
    {
        // Could not load vkGetDeviceMemoryCommitment
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

    // Load vkBindImageMemory
    vkBindImageMemory = (PFN_vkBindImageMemory)vkGetDeviceProcAddr(
        vulkanDevice, "vkBindImageMemory"
    );
    if (!vkBindImageMemory)
    {
        // Could not load vkBindImageMemory
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

    // Load vkGetRenderAreaGranularity
    vkGetRenderAreaGranularity = (PFN_vkGetRenderAreaGranularity)
        vkGetDeviceProcAddr(vulkanDevice, "vkGetRenderAreaGranularity"
    );
    if (!vkGetRenderAreaGranularity)
    {
        // Could not load vkGetRenderAreaGranularity
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

    // Load vkCreatePipelineCache
    vkCreatePipelineCache = (PFN_vkCreatePipelineCache)vkGetDeviceProcAddr(
        vulkanDevice, "vkCreatePipelineCache"
    );
    if (!vkCreatePipelineCache)
    {
        // Could not load vkCreatePipelineCache
        return false;
    }

    // Load vkDestroyPipelineCache
    vkDestroyPipelineCache = (PFN_vkDestroyPipelineCache)vkGetDeviceProcAddr(
        vulkanDevice, "vkDestroyPipelineCache"
    );
    if (!vkDestroyPipelineCache)
    {
        // Could not load vkDestroyPipelineCache
        return false;
    }

    // Load vkGetPipelineCacheData
    vkGetPipelineCacheData = (PFN_vkGetPipelineCacheData)vkGetDeviceProcAddr(
        vulkanDevice, "vkGetPipelineCacheData"
    );
    if (!vkGetPipelineCacheData)
    {
        // Could not load vkGetPipelineCacheData
        return false;
    }

    // Load vkMergePipelineCaches
    vkMergePipelineCaches = (PFN_vkMergePipelineCaches)vkGetDeviceProcAddr(
        vulkanDevice, "vkMergePipelineCaches"
    );
    if (!vkMergePipelineCaches)
    {
        // Could not load vkMergePipelineCaches
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

    // Load vkCreateSampler
    vkCreateSampler = (PFN_vkCreateSampler)vkGetDeviceProcAddr(
        vulkanDevice, "vkCreateSampler"
    );
    if (!vkCreateSampler)
    {
        // Could not load vkCreateSampler
        return false;
    }

    // Load vkDestroySampler
    vkDestroySampler = (PFN_vkDestroySampler)vkGetDeviceProcAddr(
        vulkanDevice, "vkDestroySampler"
    );
    if (!vkDestroySampler)
    {
        // Could not load vkDestroySampler
        return false;
    }

    // Load vkCreateGraphicsPipelines
    vkCreateGraphicsPipelines = (PFN_vkCreateGraphicsPipelines)
        vkGetDeviceProcAddr(vulkanDevice, "vkCreateGraphicsPipelines"
    );
    if (!vkCreateGraphicsPipelines)
    {
        // Could not load vkCreateGraphicsPipelines
        return false;
    }

    // Load vkCreateComputePipelines
    vkCreateComputePipelines = (PFN_vkCreateComputePipelines)
        vkGetDeviceProcAddr(vulkanDevice, "vkCreateComputePipelines"
    );
    if (!vkCreateComputePipelines)
    {
        // Could not load vkCreateComputePipelines
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

    // Load vkCreateDescriptorSetLayout
    vkCreateDescriptorSetLayout = (PFN_vkCreateDescriptorSetLayout)
        vkGetDeviceProcAddr(vulkanDevice, "vkCreateDescriptorSetLayout"
    );
    if (!vkCreateDescriptorSetLayout)
    {
        // Could not load vkCreateDescriptorSetLayout
        return false;
    }

    // Load vkDestroyDescriptorSetLayout
    vkDestroyDescriptorSetLayout = (PFN_vkDestroyDescriptorSetLayout)
        vkGetDeviceProcAddr(vulkanDevice, "vkDestroyDescriptorSetLayout"
    );
    if (!vkDestroyDescriptorSetLayout)
    {
        // Could not load vkDestroyDescriptorSetLayout
        return false;
    }

    // Load vkCreateDescriptorPool
    vkCreateDescriptorPool = (PFN_vkCreateDescriptorPool)vkGetDeviceProcAddr(
        vulkanDevice, "vkCreateDescriptorPool"
    );
    if (!vkCreateDescriptorPool)
    {
        // Could not load vkCreateDescriptorPool
        return false;
    }

    // Load vkDestroyDescriptorPool
    vkDestroyDescriptorPool = (PFN_vkDestroyDescriptorPool)vkGetDeviceProcAddr(
        vulkanDevice, "vkDestroyDescriptorPool"
    );
    if (!vkDestroyDescriptorPool)
    {
        // Could not load vkDestroyDescriptorPool
        return false;
    }

    // Load vkResetDescriptorPool
    vkResetDescriptorPool = (PFN_vkResetDescriptorPool)vkGetDeviceProcAddr(
        vulkanDevice, "vkResetDescriptorPool"
    );
    if (!vkResetDescriptorPool)
    {
        // Could not load vkResetDescriptorPool
        return false;
    }

    // Load vkAllocateDescriptorSets
    vkAllocateDescriptorSets = (PFN_vkAllocateDescriptorSets)
        vkGetDeviceProcAddr(vulkanDevice, "vkAllocateDescriptorSets"
    );
    if (!vkAllocateDescriptorSets)
    {
        // Could not load vkAllocateDescriptorSets
        return false;
    }

    // Load vkFreeDescriptorSets
    vkFreeDescriptorSets = (PFN_vkFreeDescriptorSets)
        vkGetDeviceProcAddr(vulkanDevice, "vkFreeDescriptorSets"
    );
    if (!vkFreeDescriptorSets)
    {
        // Could not load vkFreeDescriptorSets
        return false;
    }

    // Load vkUpdateDescriptorSets
    vkUpdateDescriptorSets = (PFN_vkUpdateDescriptorSets)
        vkGetDeviceProcAddr(vulkanDevice, "vkUpdateDescriptorSets"
    );
    if (!vkUpdateDescriptorSets)
    {
        // Could not load vkUpdateDescriptorSets
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

    // Load vkCreateBufferView
    vkCreateBufferView = (PFN_vkCreateBufferView)vkGetDeviceProcAddr(
        vulkanDevice, "vkCreateBufferView"
    );
    if (!vkCreateBufferView)
    {
        // Could not load vkCreateBufferView
        return false;
    }

    // Load vkDestroyBufferView
    vkDestroyBufferView = (PFN_vkDestroyBufferView)vkGetDeviceProcAddr(
        vulkanDevice, "vkDestroyBufferView"
    );
    if (!vkDestroyBufferView)
    {
        // Could not load vkDestroyBufferView
        return false;
    }

    // Load vkCreateImage
    vkCreateImage = (PFN_vkCreateImage)vkGetDeviceProcAddr(
        vulkanDevice, "vkCreateImage"
    );
    if (!vkCreateImage)
    {
        // Could not load vkCreateImage
        return false;
    }

    // Load vkDestroyImage
    vkDestroyImage = (PFN_vkDestroyImage)vkGetDeviceProcAddr(
        vulkanDevice, "vkDestroyImage"
    );
    if (!vkDestroyImage)
    {
        // Could not load vkDestroyImage
        return false;
    }

    // Load vkGetImageSubresourceLayout
    vkGetImageSubresourceLayout = (PFN_vkGetImageSubresourceLayout)
        vkGetDeviceProcAddr(vulkanDevice, "vkGetImageSubresourceLayout"
    );
    if (!vkGetImageSubresourceLayout)
    {
        // Could not load vkGetImageSubresourceLayout
        return false;
    }

    // Load vkGetBufferMemoryRequirements
    vkGetBufferMemoryRequirements = (PFN_vkGetBufferMemoryRequirements)
        vkGetDeviceProcAddr(vulkanDevice, "vkGetBufferMemoryRequirements"
    );
    if (!vkGetBufferMemoryRequirements)
    {
        // Could not load vkGetBufferMemoryRequirements
        return false;
    }

    // Load vkGetImageMemoryRequirements
    vkGetImageMemoryRequirements = (PFN_vkGetImageMemoryRequirements)
        vkGetDeviceProcAddr(vulkanDevice, "vkGetImageMemoryRequirements"
    );
    if (!vkGetImageMemoryRequirements)
    {
        // Could not load vkGetImageMemoryRequirements
        return false;
    }

    // Load vkGetImageSparseMemoryRequirements
    vkGetImageSparseMemoryRequirements =
        (PFN_vkGetImageSparseMemoryRequirements)vkGetDeviceProcAddr(
        vulkanDevice, "vkGetImageSparseMemoryRequirements"
    );
    if (!vkGetImageSparseMemoryRequirements)
    {
        // Could not load vkGetImageSparseMemoryRequirements
        return false;
    }

    // Load vkQueueBindSparse
    vkQueueBindSparse = (PFN_vkQueueBindSparse)vkGetDeviceProcAddr(
        vulkanDevice, "vkQueueBindSparse"
    );
    if (!vkQueueBindSparse)
    {
        // Could not load vkQueueBindSparse
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

    // Load vkWaitForFences
    vkWaitForFences = (PFN_vkWaitForFences)vkGetDeviceProcAddr(
        vulkanDevice, "vkWaitForFences"
    );
    if (!vkWaitForFences)
    {
        // Could not load vkWaitForFences
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

    // Load vkCreateEvent
    vkCreateEvent = (PFN_vkCreateEvent)vkGetDeviceProcAddr(
        vulkanDevice, "vkCreateEvent"
    );
    if (!vkCreateEvent)
    {
        // Could not load vkCreateEvent
        return false;
    }

    // Load vkDestroyEvent
    vkDestroyEvent = (PFN_vkDestroyEvent)vkGetDeviceProcAddr(
        vulkanDevice, "vkDestroyEvent"
    );
    if (!vkDestroyEvent)
    {
        // Could not load vkDestroyEvent
        return false;
    }

    // Load vkGetEventStatus
    vkGetEventStatus = (PFN_vkGetEventStatus)vkGetDeviceProcAddr(
        vulkanDevice, "vkGetEventStatus"
    );
    if (!vkGetEventStatus)
    {
        // Could not load vkGetEventStatus
        return false;
    }

    // Load vkSetEvent
    vkSetEvent = (PFN_vkSetEvent)vkGetDeviceProcAddr(
        vulkanDevice, "vkSetEvent"
    );
    if (!vkSetEvent)
    {
        // Could not load vkSetEvent
        return false;
    }

    // Load vkResetEvent
    vkResetEvent = (PFN_vkResetEvent)vkGetDeviceProcAddr(
        vulkanDevice, "vkResetEvent"
    );
    if (!vkResetEvent)
    {
        // Could not load vkResetEvent
        return false;
    }

    // Load vkCreateQueryPool
    vkCreateQueryPool = (PFN_vkCreateQueryPool)vkGetDeviceProcAddr(
        vulkanDevice, "vkCreateQueryPool"
    );
    if (!vkCreateQueryPool)
    {
        // Could not load vkCreateQueryPool
        return false;
    }

    // Load vkDestroyQueryPool
    vkDestroyQueryPool = (PFN_vkDestroyQueryPool)vkGetDeviceProcAddr(
        vulkanDevice, "vkDestroyQueryPool"
    );
    if (!vkDestroyQueryPool)
    {
        // Could not load vkDestroyQueryPool
        return false;
    }

    // Load vkGetQueryPoolResults
    vkGetQueryPoolResults = (PFN_vkGetQueryPoolResults)vkGetDeviceProcAddr(
        vulkanDevice, "vkGetQueryPoolResults"
    );
    if (!vkGetQueryPoolResults)
    {
        // Could not load vkGetQueryPoolResults
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

    // Load vkCmdSetLineWidth
    vkCmdSetLineWidth = (PFN_vkCmdSetLineWidth)vkGetDeviceProcAddr(
        vulkanDevice, "vkCmdSetLineWidth"
    );
    if (!vkCmdSetLineWidth)
    {
        // Could not load vkCmdSetLineWidth
        return false;
    }

    // Load vkCmdSetDepthBias
    vkCmdSetDepthBias = (PFN_vkCmdSetDepthBias)vkGetDeviceProcAddr(
        vulkanDevice, "vkCmdSetDepthBias"
    );
    if (!vkCmdSetDepthBias)
    {
        // Could not load vkCmdSetDepthBias
        return false;
    }

    // Load vkCmdSetBlendConstants
    vkCmdSetBlendConstants = (PFN_vkCmdSetBlendConstants)vkGetDeviceProcAddr(
        vulkanDevice, "vkCmdSetBlendConstants"
    );
    if (!vkCmdSetBlendConstants)
    {
        // Could not load vkCmdSetBlendConstants
        return false;
    }

    // Load vkCmdSetDepthBounds
    vkCmdSetDepthBounds = (PFN_vkCmdSetDepthBounds)vkGetDeviceProcAddr(
        vulkanDevice, "vkCmdSetDepthBounds"
    );
    if (!vkCmdSetDepthBounds)
    {
        // Could not load vkCmdSetDepthBounds
        return false;
    }

    // Load vkCmdSetStencilCompareMask
    vkCmdSetStencilCompareMask = (PFN_vkCmdSetStencilCompareMask)
        vkGetDeviceProcAddr(vulkanDevice, "vkCmdSetStencilCompareMask"
    );
    if (!vkCmdSetStencilCompareMask)
    {
        // Could not load vkCmdSetStencilCompareMask
        return false;
    }

    // Load vkCmdSetStencilWriteMask
    vkCmdSetStencilWriteMask = (PFN_vkCmdSetStencilWriteMask)
        vkGetDeviceProcAddr(vulkanDevice, "vkCmdSetStencilWriteMask"
    );
    if (!vkCmdSetStencilWriteMask)
    {
        // Could not load vkCmdSetStencilWriteMask
        return false;
    }

    // Load vkCmdSetStencilReference
    vkCmdSetStencilReference = (PFN_vkCmdSetStencilReference)
        vkGetDeviceProcAddr(vulkanDevice, "vkCmdSetStencilReference"
    );
    if (!vkCmdSetStencilReference)
    {
        // Could not load vkCmdSetStencilReference
        return false;
    }

    // Load vkCmdBindDescriptorSets
    vkCmdBindDescriptorSets = (PFN_vkCmdBindDescriptorSets)vkGetDeviceProcAddr(
        vulkanDevice, "vkCmdBindDescriptorSets"
    );
    if (!vkCmdBindDescriptorSets)
    {
        // Could not load vkCmdBindDescriptorSets
        return false;
    }

    // Load vkCmdBindIndexBuffer
    vkCmdBindIndexBuffer = (PFN_vkCmdBindIndexBuffer)vkGetDeviceProcAddr(
        vulkanDevice, "vkCmdBindIndexBuffer"
    );
    if (!vkCmdBindIndexBuffer)
    {
        // Could not load vkCmdBindIndexBuffer
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

    // Load vkCmdDrawIndexed
    vkCmdDrawIndexed = (PFN_vkCmdDrawIndexed)vkGetDeviceProcAddr(
        vulkanDevice, "vkCmdDrawIndexed"
    );
    if (!vkCmdDrawIndexed)
    {
        // Could not load vkCmdDrawIndexed
        return false;
    }

    // Load vkCmdDrawIndirect
    vkCmdDrawIndirect = (PFN_vkCmdDrawIndirect)vkGetDeviceProcAddr(
        vulkanDevice, "vkCmdDrawIndirect"
    );
    if (!vkCmdDrawIndirect)
    {
        // Could not load vkCmdDrawIndirect
        return false;
    }

    // Load vkCmdDrawIndexedIndirect
    vkCmdDrawIndexedIndirect = (PFN_vkCmdDrawIndexedIndirect)
        vkGetDeviceProcAddr(vulkanDevice, "vkCmdDrawIndexedIndirect"
    );
    if (!vkCmdDrawIndexedIndirect)
    {
        // Could not load vkCmdDrawIndexedIndirect
        return false;
    }

    // Load vkCmdDispatch
    vkCmdDispatch = (PFN_vkCmdDispatch)vkGetDeviceProcAddr(
        vulkanDevice, "vkCmdDispatch"
    );
    if (!vkCmdDispatch)
    {
        // Could not load vkCmdDispatch
        return false;
    }

    // Load vkCmdDispatchIndirect
    vkCmdDispatchIndirect = (PFN_vkCmdDispatchIndirect)vkGetDeviceProcAddr(
        vulkanDevice, "vkCmdDispatchIndirect"
    );
    if (!vkCmdDispatchIndirect)
    {
        // Could not load vkCmdDispatchIndirect
        return false;
    }

    // Load vkCmdCopyBuffer
    vkCmdCopyBuffer = (PFN_vkCmdCopyBuffer)vkGetDeviceProcAddr(
        vulkanDevice, "vkCmdCopyBuffer"
    );
    if (!vkCmdCopyBuffer)
    {
        // Could not load vkCmdCopyBuffer
        return false;
    }

    // Load vkCmdCopyImage
    vkCmdCopyImage = (PFN_vkCmdCopyImage)vkGetDeviceProcAddr(
        vulkanDevice, "vkCmdCopyImage"
    );
    if (!vkCmdCopyImage)
    {
        // Could not load vkCmdCopyImage
        return false;
    }

    // Load vkCmdBlitImage
    vkCmdBlitImage = (PFN_vkCmdBlitImage)vkGetDeviceProcAddr(
        vulkanDevice, "vkCmdBlitImage"
    );
    if (!vkCmdBlitImage)
    {
        // Could not load vkCmdBlitImage
        return false;
    }

    // Load vkCmdCopyBufferToImage
    vkCmdCopyBufferToImage = (PFN_vkCmdCopyBufferToImage)vkGetDeviceProcAddr(
        vulkanDevice, "vkCmdCopyBufferToImage"
    );
    if (!vkCmdCopyBufferToImage)
    {
        // Could not load vkCmdCopyBufferToImage
        return false;
    }

    // Load vkCmdCopyImageToBuffer
    vkCmdCopyImageToBuffer = (PFN_vkCmdCopyImageToBuffer)vkGetDeviceProcAddr(
        vulkanDevice, "vkCmdCopyImageToBuffer"
    );
    if (!vkCmdCopyImageToBuffer)
    {
        // Could not load vkCmdCopyImageToBuffer
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
    vkCmdCopyImageToBuffer = 0;
    vkCmdCopyBufferToImage = 0;
    vkCmdBlitImage = 0;
    vkCmdCopyImage = 0;
    vkCmdCopyBuffer = 0;
    vkCmdDispatchIndirect = 0;
    vkCmdDispatch = 0;
    vkCmdDrawIndexedIndirect = 0;
    vkCmdDrawIndirect = 0;
    vkCmdDrawIndexed = 0;
    vkCmdDraw = 0;
    vkCmdBindVertexBuffers = 0;
    vkCmdBindIndexBuffer = 0;
    vkCmdBindDescriptorSets = 0;
    vkCmdSetStencilReference = 0;
    vkCmdSetStencilWriteMask = 0;
    vkCmdSetStencilCompareMask = 0;
    vkCmdSetDepthBounds = 0;
    vkCmdSetBlendConstants = 0;
    vkCmdSetDepthBias = 0;
    vkCmdSetLineWidth = 0;
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
    vkGetQueryPoolResults = 0;
    vkDestroyQueryPool = 0;
    vkCreateQueryPool = 0;
    vkResetEvent = 0;
    vkSetEvent = 0;
    vkGetEventStatus = 0;
    vkDestroyEvent = 0;
    vkCreateEvent = 0;
    vkDestroySemaphore = 0;
    vkCreateSemaphore = 0;
    vkWaitForFences = 0;
    vkGetFenceStatus = 0;
    vkResetFences = 0;
    vkDestroyFence = 0;
    vkCreateFence = 0;
    vkQueueBindSparse = 0;
    vkGetImageSparseMemoryRequirements = 0;
    vkGetImageMemoryRequirements = 0;
    vkGetBufferMemoryRequirements = 0;
    vkGetImageSubresourceLayout = 0;
    vkDestroyImage = 0;
    vkCreateImage = 0;
    vkDestroyBufferView = 0;
    vkCreateBufferView = 0;
    vkDestroyBuffer = 0;
    vkCreateBuffer = 0;
    vkUpdateDescriptorSets = 0;
    vkFreeDescriptorSets = 0;
    vkAllocateDescriptorSets = 0;
    vkResetDescriptorPool = 0;
    vkDestroyDescriptorPool = 0;
    vkCreateDescriptorPool = 0;
    vkDestroyDescriptorSetLayout = 0;
    vkCreateDescriptorSetLayout = 0;
    vkDestroyPipeline = 0;
    vkCreateComputePipelines = 0;
    vkCreateGraphicsPipelines = 0;
    vkDestroySampler = 0;
    vkCreateSampler = 0;
    vkDestroyPipelineLayout = 0;
    vkCreatePipelineLayout = 0;
    vkMergePipelineCaches = 0;
    vkGetPipelineCacheData = 0;
    vkDestroyPipelineCache = 0;
    vkCreatePipelineCache = 0;
    vkDestroyShaderModule = 0;
    vkCreateShaderModule = 0;
    vkDestroyImageView = 0;
    vkCreateImageView = 0;
    vkDestroyFramebuffer = 0;
    vkCreateFramebuffer = 0;
    vkGetRenderAreaGranularity = 0;
    vkDestroyRenderPass = 0;
    vkCreateRenderPass = 0;

    vkBindImageMemory = 0;
    vkBindBufferMemory = 0;
    vkGetDeviceMemoryCommitment = 0;
    vkInvalidateMappedMemoryRanges = 0;
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

    vkGetPhysicalDeviceSparseImageFormatProperties = 0;
    vkGetPhysicalDeviceMemoryProperties = 0;
    vkEnumerateDeviceLayerProperties = 0;
    vkEnumerateDeviceExtensionProperties = 0;
    vkGetDeviceProcAddr = 0;
    vkCreateDevice = 0;
    vkGetPhysicalDeviceQueueFamilyProperties = 0;
    vkGetPhysicalDeviceImageFormatProperties = 0;
    vkGetPhysicalDeviceFormatProperties = 0;
    vkGetPhysicalDeviceFeatures = 0;
    vkGetPhysicalDeviceProperties = 0;
    vkEnumeratePhysicalDevices = 0;
    vkDestroyInstance = 0;

    vkEnumerateInstanceLayerProperties = 0;
    vkEnumerateInstanceExtensionProperties = 0;
    vkCreateInstance = 0;
}
