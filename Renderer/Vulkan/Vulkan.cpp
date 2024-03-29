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
//     Renderer/Vulkan/Vulkan.cpp : Vulkan management                         //
////////////////////////////////////////////////////////////////////////////////
#include "Vulkan.h"


////////////////////////////////////////////////////////////////////////////////
//  PhysicalDevice global instance                                            //
////////////////////////////////////////////////////////////////////////////////
VkPhysicalDevice GPhysicalDevice = 0;

////////////////////////////////////////////////////////////////////////////////
//  VulkanDevice global instance                                              //
////////////////////////////////////////////////////////////////////////////////
VkDevice GVulkanDevice = 0;


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

// vkEnumerateInstanceVersion function
PFN_vkEnumerateInstanceVersion vkEnumerateInstanceVersion = 0;


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

// vkEnumeratePhysicalDeviceGroups function
PFN_vkEnumeratePhysicalDeviceGroups vkEnumeratePhysicalDeviceGroups = 0;


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


// vkGetPhysicalDeviceFeatures2 function
PFN_vkGetPhysicalDeviceFeatures2 vkGetPhysicalDeviceFeatures2 = 0;

// vkGetPhysicalDeviceProperties2 function
PFN_vkGetPhysicalDeviceProperties2 vkGetPhysicalDeviceProperties2 = 0;

// vkGetPhysicalDeviceFormatProperties2 function
PFN_vkGetPhysicalDeviceFormatProperties2
    vkGetPhysicalDeviceFormatProperties2 = 0;

// vkGetPhysicalDeviceImageFormatProperties2 function
PFN_vkGetPhysicalDeviceImageFormatProperties2
    vkGetPhysicalDeviceImageFormatProperties2 = 0;

// vkGetPhysicalDeviceQueueFamilyProperties2 function
PFN_vkGetPhysicalDeviceQueueFamilyProperties2
    vkGetPhysicalDeviceQueueFamilyProperties2 = 0;

// vkGetPhysicalDeviceMemoryProperties2 function
PFN_vkGetPhysicalDeviceMemoryProperties2
    vkGetPhysicalDeviceMemoryProperties2 = 0;

// vkGetPhysicalDeviceSparseImageFormatProperties2 function
PFN_vkGetPhysicalDeviceSparseImageFormatProperties2
    vkGetPhysicalDeviceSparseImageFormatProperties2 = 0;

// vkGetPhysicalDeviceExternalBufferProperties function
PFN_vkGetPhysicalDeviceExternalBufferProperties
    vkGetPhysicalDeviceExternalBufferProperties = 0;

// vkGetPhysicalDeviceExternalFenceProperties function
PFN_vkGetPhysicalDeviceExternalFenceProperties
    vkGetPhysicalDeviceExternalFenceProperties = 0;

// vkGetPhysicalDeviceExternalSemaphoreProperties function
PFN_vkGetPhysicalDeviceExternalSemaphoreProperties
    vkGetPhysicalDeviceExternalSemaphoreProperties = 0;


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

// vkGetDeviceGroupPresentCapabilitiesKHR function
PFN_vkGetDeviceGroupPresentCapabilitiesKHR
    vkGetDeviceGroupPresentCapabilitiesKHR = 0;

// vkGetDeviceGroupSurfacePresentModesKHR function
PFN_vkGetDeviceGroupSurfacePresentModesKHR
    vkGetDeviceGroupSurfacePresentModesKHR = 0;

// vkGetPhysicalDevicePresentRectanglesKHR function
/*PFN_vkGetPhysicalDevicePresentRectanglesKHR
    vkGetPhysicalDevicePresentRectanglesKHR = 0;*/

// vkAcquireNextImage2KHR function
PFN_vkAcquireNextImage2KHR vkAcquireNextImage2KHR = 0;


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

// vkCmdUpdateBuffer function
PFN_vkCmdUpdateBuffer vkCmdUpdateBuffer = 0;

// vkCmdFillBuffer function
PFN_vkCmdFillBuffer vkCmdFillBuffer = 0;

// vkCmdClearColorImage function
PFN_vkCmdClearColorImage vkCmdClearColorImage = 0;

// vkCmdClearDepthStencilImage function
PFN_vkCmdClearDepthStencilImage vkCmdClearDepthStencilImage = 0;

// vkCmdClearAttachments function
PFN_vkCmdClearAttachments vkCmdClearAttachments = 0;

// vkCmdResolveImage function
PFN_vkCmdResolveImage vkCmdResolveImage = 0;

// vkCmdSetEvent function
PFN_vkCmdSetEvent vkCmdSetEvent = 0;

// vkCmdResetEvent function
PFN_vkCmdResetEvent vkCmdResetEvent = 0;

// vkCmdWaitEvents function
PFN_vkCmdWaitEvents vkCmdWaitEvents = 0;

// vkCmdPipelineBarrier function
PFN_vkCmdPipelineBarrier vkCmdPipelineBarrier = 0;

// vkCmdBeginQuery function
PFN_vkCmdBeginQuery vkCmdBeginQuery = 0;

// vkCmdEndQuery function
PFN_vkCmdEndQuery vkCmdEndQuery = 0;

// vkCmdResetQueryPool function
PFN_vkCmdResetQueryPool vkCmdResetQueryPool = 0;

// vkCmdWriteTimestamp function
PFN_vkCmdWriteTimestamp vkCmdWriteTimestamp = 0;

// vkCmdCopyQueryPoolResults function
PFN_vkCmdCopyQueryPoolResults vkCmdCopyQueryPoolResults = 0;

// vkCmdPushConstants function
PFN_vkCmdPushConstants vkCmdPushConstants = 0;

// vkCmdBeginRenderPass function
PFN_vkCmdBeginRenderPass vkCmdBeginRenderPass = 0;

// vkCmdNextSubpass function
PFN_vkCmdNextSubpass vkCmdNextSubpass = 0;

// vkCmdEndRenderPass function
PFN_vkCmdEndRenderPass vkCmdEndRenderPass = 0;

// vkCmdExecuteCommands function
PFN_vkCmdExecuteCommands vkCmdExecuteCommands = 0;


// vkBindBufferMemory2 function
PFN_vkBindBufferMemory2 vkBindBufferMemory2 = 0;

// vkBindImageMemory2 function
PFN_vkBindImageMemory2 vkBindImageMemory2 = 0;

// vkGetDeviceGroupPeerMemoryFeatures function
PFN_vkGetDeviceGroupPeerMemoryFeatures vkGetDeviceGroupPeerMemoryFeatures = 0;

// vkCmdSetDeviceMask function
PFN_vkCmdSetDeviceMask vkCmdSetDeviceMask = 0;

// vkCmdDispatchBase function
PFN_vkCmdDispatchBase vkCmdDispatchBase = 0;

// vkGetImageMemoryRequirements2 function
PFN_vkGetImageMemoryRequirements2 vkGetImageMemoryRequirements2 = 0;

// vkGetBufferMemoryRequirements2 function
PFN_vkGetBufferMemoryRequirements2 vkGetBufferMemoryRequirements2 = 0;

// vkGetImageSparseMemoryRequirements2 function
PFN_vkGetImageSparseMemoryRequirements2 vkGetImageSparseMemoryRequirements2 = 0;

// vkTrimCommandPool function
PFN_vkTrimCommandPool vkTrimCommandPool = 0;

// vkGetDeviceQueue2 function
PFN_vkGetDeviceQueue2 vkGetDeviceQueue2 = 0;

// vkCreateSamplerYcbcrConversion function
PFN_vkCreateSamplerYcbcrConversion vkCreateSamplerYcbcrConversion = 0;

// vkDestroySamplerYcbcrConversion function
PFN_vkDestroySamplerYcbcrConversion vkDestroySamplerYcbcrConversion = 0;

// vkCreateDescriptorUpdateTemplate function
PFN_vkCreateDescriptorUpdateTemplate vkCreateDescriptorUpdateTemplate = 0;

// vkDestroyDescriptorUpdateTemplate function
PFN_vkDestroyDescriptorUpdateTemplate vkDestroyDescriptorUpdateTemplate = 0;

//  vkUpdateDescriptorSetWithTemplate function
PFN_vkUpdateDescriptorSetWithTemplate vkUpdateDescriptorSetWithTemplate = 0;

// vkGetDescriptorSetLayoutSupport function
PFN_vkGetDescriptorSetLayoutSupport vkGetDescriptorSetLayoutSupport = 0;


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

    // Load vkEnumerateInstanceVersion
    vkEnumerateInstanceVersion = (PFN_vkEnumerateInstanceVersion)
        vkGetInstanceProcAddr(0, "vkEnumerateInstanceVersion"
    );
    if (!vkEnumerateInstanceVersion)
    {
        // Could not load vkEnumerateInstanceVersion
        return false;
    }

    // Vulkan global functions successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Load Vulkan instance functions                                            //
//  return : True if Vulkan instance functions are successfully loaded        //
////////////////////////////////////////////////////////////////////////////////
bool LoadVulkanInstanceFunctions()
{
    // Check Vulkan instance
    if (!GVulkanInstance)
    {
        // Vulkan instance is invalid
        return false;
    }

    // Load vkDestroyInstance
    vkDestroyInstance = (PFN_vkDestroyInstance)
        vkGetInstanceProcAddr(GVulkanInstance, "vkDestroyInstance"
    );
    if (!vkDestroyInstance)
    {
        // Could not load vkDestroyInstance
        return false;
    }

    // Load vkEnumeratePhysicalDevices
    vkEnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices)
        vkGetInstanceProcAddr(GVulkanInstance, "vkEnumeratePhysicalDevices"
    );
    if (!vkEnumeratePhysicalDevices)
    {
        // Could not load vkEnumeratePhysicalDevices
        return false;
    }

    // Load vkGetPhysicalDeviceProperties
    vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties)
        vkGetInstanceProcAddr(GVulkanInstance, "vkGetPhysicalDeviceProperties"
    );
    if (!vkGetPhysicalDeviceProperties)
    {
        // Could not load vkGetPhysicalDeviceProperties
        return false;
    }

    // Load vkGetPhysicalDeviceFeatures
    vkGetPhysicalDeviceFeatures = (PFN_vkGetPhysicalDeviceFeatures)
        vkGetInstanceProcAddr(GVulkanInstance, "vkGetPhysicalDeviceFeatures"
    );
    if (!vkGetPhysicalDeviceFeatures)
    {
        // Could not load vkGetPhysicalDeviceFeatures
        return false;
    }

    // Load vkGetPhysicalDeviceFormatProperties
    vkGetPhysicalDeviceFormatProperties =
        (PFN_vkGetPhysicalDeviceFormatProperties)vkGetInstanceProcAddr(
        GVulkanInstance, "vkGetPhysicalDeviceFormatProperties"
    );
    if (!vkGetPhysicalDeviceFormatProperties)
    {
        // Could not load vkGetPhysicalDeviceFormatProperties
        return false;
    }

    // Load vkGetPhysicalDeviceImageFormatProperties
    vkGetPhysicalDeviceImageFormatProperties =
        (PFN_vkGetPhysicalDeviceImageFormatProperties)vkGetInstanceProcAddr(
        GVulkanInstance, "vkGetPhysicalDeviceImageFormatProperties"
    );
    if (!vkGetPhysicalDeviceImageFormatProperties)
    {
        // Could not load vkGetPhysicalDeviceImageFormatProperties
        return false;
    }

    // Load vkGetPhysicalDeviceQueueFamilyProperties
    vkGetPhysicalDeviceQueueFamilyProperties =
        (PFN_vkGetPhysicalDeviceQueueFamilyProperties)vkGetInstanceProcAddr(
        GVulkanInstance, "vkGetPhysicalDeviceQueueFamilyProperties"
    );
    if (!vkGetPhysicalDeviceQueueFamilyProperties)
    {
        // Could not load vkGetPhysicalDeviceQueueFamilyProperties
        return false;
    }

    // Load vkCreateDevice
    vkCreateDevice = (PFN_vkCreateDevice)
        vkGetInstanceProcAddr(GVulkanInstance, "vkCreateDevice"
    );
    if (!vkCreateDevice)
    {
        // Could not load vkCreateDevice
        return false;
    }

    // Load vkGetDeviceProcAddr
    vkGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr)
        vkGetInstanceProcAddr(GVulkanInstance, "vkGetDeviceProcAddr"
    );
    if (!vkGetDeviceProcAddr)
    {
        // Could not load vkGetDeviceProcAddr
        return false;
    }

    // Load vkEnumerateDeviceExtensionProperties
    vkEnumerateDeviceExtensionProperties =
        (PFN_vkEnumerateDeviceExtensionProperties)vkGetInstanceProcAddr(
        GVulkanInstance, "vkEnumerateDeviceExtensionProperties"
    );
    if (!vkEnumerateDeviceExtensionProperties)
    {
        // Could not load vkEnumerateDeviceExtensionProperties
        return false;
    }

    // Load vkEnumerateDeviceLayerProperties
    vkEnumerateDeviceLayerProperties =
        (PFN_vkEnumerateDeviceLayerProperties)vkGetInstanceProcAddr(
        GVulkanInstance, "vkEnumerateDeviceLayerProperties"
    );
    if (!vkEnumerateDeviceLayerProperties)
    {
        // Could not load vkEnumerateDeviceLayerProperties
        return false;
    }

    // Load vkGetPhysicalDeviceMemoryProperties
    vkGetPhysicalDeviceMemoryProperties =
        (PFN_vkGetPhysicalDeviceMemoryProperties)vkGetInstanceProcAddr(
        GVulkanInstance, "vkGetPhysicalDeviceMemoryProperties"
    );
    if (!vkGetPhysicalDeviceMemoryProperties)
    {
        // Could not load vkGetPhysicalDeviceMemoryProperties
        return false;
    }

    // Load vkGetPhysicalDeviceSparseImageFormatProperties
    vkGetPhysicalDeviceSparseImageFormatProperties =
        (PFN_vkGetPhysicalDeviceSparseImageFormatProperties)
        vkGetInstanceProcAddr(GVulkanInstance,
        "vkGetPhysicalDeviceSparseImageFormatProperties"
    );
    if (!vkGetPhysicalDeviceSparseImageFormatProperties)
    {
        // Could not load vkGetPhysicalDeviceSparseImageFormatProperties
        return false;
    }

    // Load vkEnumeratePhysicalDeviceGroups
    vkEnumeratePhysicalDeviceGroups = (PFN_vkEnumeratePhysicalDeviceGroups)
        vkGetInstanceProcAddr(GVulkanInstance, "vkEnumeratePhysicalDeviceGroups"
    );
    if (!vkEnumeratePhysicalDeviceGroups)
    {
        // Could not load vkEnumeratePhysicalDeviceGroups
        return false;
    }


    // Load vkDestroySurfaceKHR
    vkDestroySurfaceKHR = (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(
        GVulkanInstance, "vkDestroySurfaceKHR"
    );
    if (!vkDestroySurfaceKHR)
    {
        // Could not load vkDestroySurfaceKHR
        return false;
    }

    // Load vkGetPhysicalDeviceSurfaceSupportKHR
    vkGetPhysicalDeviceSurfaceSupportKHR =
        (PFN_vkGetPhysicalDeviceSurfaceSupportKHR)vkGetInstanceProcAddr(
        GVulkanInstance, "vkGetPhysicalDeviceSurfaceSupportKHR"
    );
    if (!vkGetPhysicalDeviceSurfaceSupportKHR)
    {
        // Could not load vkGetPhysicalDeviceSurfaceSupportKHR
        return false;
    }

    // Load vkGetPhysicalDeviceSurfaceCapabilitiesKHR
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR =
        (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR)vkGetInstanceProcAddr(
        GVulkanInstance, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR"
    );
    if (!vkGetPhysicalDeviceSurfaceCapabilitiesKHR)
    {
        // Could not load vkGetPhysicalDeviceSurfaceCapabilitiesKHR
        return false;
    }

    // Load vkGetPhysicalDeviceSurfaceFormatsKHR
    vkGetPhysicalDeviceSurfaceFormatsKHR =
        (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR)vkGetInstanceProcAddr(
        GVulkanInstance, "vkGetPhysicalDeviceSurfaceFormatsKHR"
    );
    if (!vkGetPhysicalDeviceSurfaceFormatsKHR)
    {
        // Could not load vkGetPhysicalDeviceSurfaceFormatsKHR
        return false;
    }

    // Load vkGetPhysicalDeviceSurfacePresentModesKHR
    vkGetPhysicalDeviceSurfacePresentModesKHR =
        (PFN_vkGetPhysicalDeviceSurfacePresentModesKHR)vkGetInstanceProcAddr(
        GVulkanInstance, "vkGetPhysicalDeviceSurfacePresentModesKHR"
    );
    if (!vkGetPhysicalDeviceSurfacePresentModesKHR)
    {
        // Could not load vkGetPhysicalDeviceSurfacePresentModesKHR
        return false;
    }


    // Load vkGetPhysicalDeviceFeatures2
    vkGetPhysicalDeviceFeatures2 = (PFN_vkGetPhysicalDeviceFeatures2)
        vkGetInstanceProcAddr(GVulkanInstance, "vkGetPhysicalDeviceFeatures2"
    );
    if (!vkGetPhysicalDeviceFeatures2)
    {
        // Could not load vkGetPhysicalDeviceFeatures2
        return false;
    }

    // Load vkGetPhysicalDeviceProperties2
    vkGetPhysicalDeviceProperties2 = (PFN_vkGetPhysicalDeviceProperties2)
        vkGetInstanceProcAddr(GVulkanInstance, "vkGetPhysicalDeviceProperties2"
    );
    if (!vkGetPhysicalDeviceProperties2)
    {
        // Could not load vkGetPhysicalDeviceProperties2
        return false;
    }

    // Load vkGetPhysicalDeviceFormatProperties2
    vkGetPhysicalDeviceFormatProperties2 =
        (PFN_vkGetPhysicalDeviceFormatProperties2)vkGetInstanceProcAddr(
        GVulkanInstance, "vkGetPhysicalDeviceFormatProperties2"
    );
    if (!vkGetPhysicalDeviceFormatProperties2)
    {
        // Could not load vkGetPhysicalDeviceFormatProperties2
        return false;
    }

    // Load vkGetPhysicalDeviceImageFormatProperties2
    vkGetPhysicalDeviceImageFormatProperties2 =
        (PFN_vkGetPhysicalDeviceImageFormatProperties2)vkGetInstanceProcAddr(
        GVulkanInstance, "vkGetPhysicalDeviceImageFormatProperties2"
    );
    if (!vkGetPhysicalDeviceImageFormatProperties2)
    {
        // Could not load vkGetPhysicalDeviceImageFormatProperties2
        return false;
    }

    // Load vkGetPhysicalDeviceQueueFamilyProperties2
    vkGetPhysicalDeviceQueueFamilyProperties2 =
        (PFN_vkGetPhysicalDeviceQueueFamilyProperties2)vkGetInstanceProcAddr(
        GVulkanInstance, "vkGetPhysicalDeviceQueueFamilyProperties2"
    );
    if (!vkGetPhysicalDeviceQueueFamilyProperties2)
    {
        // Could not load vkGetPhysicalDeviceQueueFamilyProperties2
        return false;
    }

    // Load vkGetPhysicalDeviceMemoryProperties2
    vkGetPhysicalDeviceMemoryProperties2 =
        (PFN_vkGetPhysicalDeviceMemoryProperties2)vkGetInstanceProcAddr(
        GVulkanInstance, "vkGetPhysicalDeviceMemoryProperties2"
    );
    if (!vkGetPhysicalDeviceMemoryProperties2)
    {
        // Could not load vkGetPhysicalDeviceMemoryProperties2
        return false;
    }

    // Load vkGetPhysicalDeviceSparseImageFormatProperties2
    vkGetPhysicalDeviceSparseImageFormatProperties2 =
        (PFN_vkGetPhysicalDeviceSparseImageFormatProperties2)
        vkGetInstanceProcAddr(GVulkanInstance,
        "vkGetPhysicalDeviceSparseImageFormatProperties2"
    );
    if (!vkGetPhysicalDeviceSparseImageFormatProperties2)
    {
        // Could not load vkGetPhysicalDeviceSparseImageFormatProperties2
        return false;
    }

    // Load vkGetPhysicalDeviceExternalBufferProperties
    vkGetPhysicalDeviceExternalBufferProperties =
        (PFN_vkGetPhysicalDeviceExternalBufferProperties)vkGetInstanceProcAddr(
        GVulkanInstance, "vkGetPhysicalDeviceExternalBufferProperties"
    );
    if (!vkGetPhysicalDeviceExternalBufferProperties)
    {
        // Could not load vkGetPhysicalDeviceExternalBufferProperties
        return false;
    }

    // Load vkGetPhysicalDeviceExternalFenceProperties
    vkGetPhysicalDeviceExternalFenceProperties =
        (PFN_vkGetPhysicalDeviceExternalFenceProperties)vkGetInstanceProcAddr(
        GVulkanInstance, "vkGetPhysicalDeviceExternalFenceProperties"
    );
    if (!vkGetPhysicalDeviceExternalFenceProperties)
    {
        // Could not load vkGetPhysicalDeviceExternalFenceProperties
        return false;
    }

    // Load vkGetPhysicalDeviceExternalSemaphoreProperties
    vkGetPhysicalDeviceExternalSemaphoreProperties =
        (PFN_vkGetPhysicalDeviceExternalSemaphoreProperties)
        vkGetInstanceProcAddr(GVulkanInstance,
        "vkGetPhysicalDeviceExternalSemaphoreProperties"
    );
    if (!vkGetPhysicalDeviceExternalSemaphoreProperties)
    {
        // Could not load vkGetPhysicalDeviceExternalSemaphoreProperties
        return false;
    }


    // Vulkan instance functions successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Load Vulkan device functions                                              //
//  return : True if Vulkan device functions are successfully loaded         //
////////////////////////////////////////////////////////////////////////////////
bool LoadVulkanDeviceFunctions()
{
    // Check Vulkan device
    if (!GVulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }


    // Load vkCreateSwapchainKHR
    vkCreateSwapchainKHR = (PFN_vkCreateSwapchainKHR)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCreateSwapchainKHR"
    );
    if (!vkCreateSwapchainKHR)
    {
        // Could not load vkCreateSwapchainKHR
        return false;
    }

    // Load vkDestroySwapchainKHR
    vkDestroySwapchainKHR = (PFN_vkDestroySwapchainKHR)vkGetDeviceProcAddr(
        GVulkanDevice, "vkDestroySwapchainKHR"
    );
    if (!vkDestroySwapchainKHR)
    {
        // Could not load vkDestroySwapchainKHR
        return false;
    }

    // Load vkGetSwapchainImagesKHR
    vkGetSwapchainImagesKHR = (PFN_vkGetSwapchainImagesKHR)vkGetDeviceProcAddr(
        GVulkanDevice, "vkGetSwapchainImagesKHR"
    );
    if (!vkGetSwapchainImagesKHR)
    {
        // Could not load vkGetSwapchainImagesKHR
        return false;
    }

    // Load vkAcquireNextImageKHR
    vkAcquireNextImageKHR = (PFN_vkAcquireNextImageKHR)vkGetDeviceProcAddr(
        GVulkanDevice, "vkAcquireNextImageKHR"
    );
    if (!vkAcquireNextImageKHR)
    {
        // Could not load vkAcquireNextImageKHR
        return false;
    }

    // Load vkQueuePresentKHR
    vkQueuePresentKHR = (PFN_vkQueuePresentKHR)vkGetDeviceProcAddr(
        GVulkanDevice, "vkQueuePresentKHR"
    );
    if (!vkQueuePresentKHR)
    {
        // Could not load vkQueuePresentKHR
        return false;
    }

    // Load vkGetDeviceGroupPresentCapabilitiesKHR
    vkGetDeviceGroupPresentCapabilitiesKHR =
        (PFN_vkGetDeviceGroupPresentCapabilitiesKHR)vkGetDeviceProcAddr(
        GVulkanDevice, "vkGetDeviceGroupPresentCapabilitiesKHR"
    );
    if (!vkGetDeviceGroupPresentCapabilitiesKHR)
    {
        // Could not load vkGetDeviceGroupPresentCapabilitiesKHR
        return false;
    }

    // Load vkGetDeviceGroupSurfacePresentModesKHR
    vkGetDeviceGroupSurfacePresentModesKHR =
        (PFN_vkGetDeviceGroupSurfacePresentModesKHR)vkGetDeviceProcAddr(
        GVulkanDevice, "vkGetDeviceGroupSurfacePresentModesKHR"
    );
    if (!vkGetDeviceGroupSurfacePresentModesKHR)
    {
        // Could not load vkGetDeviceGroupSurfacePresentModesKHR
        return false;
    }

    // Load vkGetPhysicalDevicePresentRectanglesKHR
    /*vkGetPhysicalDevicePresentRectanglesKHR =
        (PFN_vkGetPhysicalDevicePresentRectanglesKHR)vkGetDeviceProcAddr(
        GVulkanDevice, "vkGetPhysicalDevicePresentRectanglesKHR"
    );
    if (!vkGetPhysicalDevicePresentRectanglesKHR)
    {
        // Could not load vkGetPhysicalDevicePresentRectanglesKHR
        return false;
    }*/

    // Load vkAcquireNextImage2KHR
    vkAcquireNextImage2KHR = (PFN_vkAcquireNextImage2KHR)vkGetDeviceProcAddr(
        GVulkanDevice, "vkAcquireNextImage2KHR"
    );
    if (!vkAcquireNextImage2KHR)
    {
        // Could not load vkAcquireNextImage2KHR
        return false;
    }


    // Load vkDestroyDevice
    vkDestroyDevice = (PFN_vkDestroyDevice)vkGetDeviceProcAddr(
        GVulkanDevice, "vkDestroyDevice"
    );
    if (!vkDestroyDevice)
    {
        // Could not load vkDestroyDevice
        return false;
    }

    // Load vkDeviceWaitIdle
    vkDeviceWaitIdle = (PFN_vkDeviceWaitIdle)vkGetDeviceProcAddr(
        GVulkanDevice, "vkDeviceWaitIdle"
    );
    if (!vkDeviceWaitIdle)
    {
        // Could not load vkDeviceWaitIdle
        return false;
    }

    // Load vkGetDeviceQueue
    vkGetDeviceQueue = (PFN_vkGetDeviceQueue)vkGetDeviceProcAddr(
        GVulkanDevice, "vkGetDeviceQueue"
    );
    if (!vkGetDeviceQueue)
    {
        // Could not load vkGetDeviceQueue
        return false;
    }

    // Load vkQueueSubmit
    vkQueueSubmit = (PFN_vkQueueSubmit)vkGetDeviceProcAddr(
        GVulkanDevice, "vkQueueSubmit"
    );
    if (!vkQueueSubmit)
    {
        // Could not load vkQueueSubmit
        return false;
    }

    // Load vkQueueWaitIdle
    vkQueueWaitIdle = (PFN_vkQueueWaitIdle)vkGetDeviceProcAddr(
        GVulkanDevice, "vkQueueWaitIdle"
    );
    if (!vkQueueWaitIdle)
    {
        // Could not load vkQueueWaitIdle
        return false;
    }


    // Load vkAllocateMemory
    vkAllocateMemory = (PFN_vkAllocateMemory)vkGetDeviceProcAddr(
        GVulkanDevice, "vkAllocateMemory"
    );
    if (!vkAllocateMemory)
    {
        // Could not load vkAllocateMemory
        return false;
    }

    // Load vkFreeMemory
    vkFreeMemory = (PFN_vkFreeMemory)vkGetDeviceProcAddr(
        GVulkanDevice, "vkFreeMemory"
    );
    if (!vkFreeMemory)
    {
        // Could not load vkFreeMemory
        return false;
    }

    // Load vkMapMemory
    vkMapMemory = (PFN_vkMapMemory)vkGetDeviceProcAddr(
        GVulkanDevice, "vkMapMemory"
    );
    if (!vkMapMemory)
    {
        // Could not load vkMapMemory
        return false;
    }

    // Load vkUnmapMemory
    vkUnmapMemory = (PFN_vkUnmapMemory)vkGetDeviceProcAddr(
        GVulkanDevice, "vkUnmapMemory"
    );
    if (!vkUnmapMemory)
    {
        // Could not load vkUnmapMemory
        return false;
    }

    // Load vkFlushMappedMemoryRanges
    vkFlushMappedMemoryRanges = (PFN_vkFlushMappedMemoryRanges)
        vkGetDeviceProcAddr(GVulkanDevice, "vkFlushMappedMemoryRanges"
    );
    if (!vkFlushMappedMemoryRanges)
    {
        // Could not load vkFlushMappedMemoryRanges
        return false;
    }

    // Load vkInvalidateMappedMemoryRanges
    vkInvalidateMappedMemoryRanges = (PFN_vkInvalidateMappedMemoryRanges)
        vkGetDeviceProcAddr(GVulkanDevice, "vkInvalidateMappedMemoryRanges"
    );
    if (!vkInvalidateMappedMemoryRanges)
    {
        // Could not load vkInvalidateMappedMemoryRanges
        return false;
    }

    // Load vkGetDeviceMemoryCommitment
    vkGetDeviceMemoryCommitment = (PFN_vkGetDeviceMemoryCommitment)
        vkGetDeviceProcAddr(GVulkanDevice, "vkGetDeviceMemoryCommitment"
    );
    if (!vkGetDeviceMemoryCommitment)
    {
        // Could not load vkGetDeviceMemoryCommitment
        return false;
    }

    // Load vkBindBufferMemory
    vkBindBufferMemory = (PFN_vkBindBufferMemory)vkGetDeviceProcAddr(
        GVulkanDevice, "vkBindBufferMemory"
    );
    if (!vkBindBufferMemory)
    {
        // Could not load vkBindBufferMemory
        return false;
    }

    // Load vkBindImageMemory
    vkBindImageMemory = (PFN_vkBindImageMemory)vkGetDeviceProcAddr(
        GVulkanDevice, "vkBindImageMemory"
    );
    if (!vkBindImageMemory)
    {
        // Could not load vkBindImageMemory
        return false;
    }


    // Load vkCreateRenderPass
    vkCreateRenderPass = (PFN_vkCreateRenderPass)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCreateRenderPass"
    );
    if (!vkCreateRenderPass)
    {
        // Could not load vkCreateRenderPass
        return false;
    }

    // Load vkDestroyRenderPass
    vkDestroyRenderPass = (PFN_vkDestroyRenderPass)vkGetDeviceProcAddr(
        GVulkanDevice, "vkDestroyRenderPass"
    );
    if (!vkDestroyRenderPass)
    {
        // Could not load vkDestroyRenderPass
        return false;
    }

    // Load vkGetRenderAreaGranularity
    vkGetRenderAreaGranularity = (PFN_vkGetRenderAreaGranularity)
        vkGetDeviceProcAddr(GVulkanDevice, "vkGetRenderAreaGranularity"
    );
    if (!vkGetRenderAreaGranularity)
    {
        // Could not load vkGetRenderAreaGranularity
        return false;
    }

    // Load vkCreateFramebuffer
    vkCreateFramebuffer = (PFN_vkCreateFramebuffer)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCreateFramebuffer"
    );
    if (!vkCreateFramebuffer)
    {
        // Could not load vkCreateFramebuffer
        return false;
    }

    // Load vkDestroyFramebuffer
    vkDestroyFramebuffer = (PFN_vkDestroyFramebuffer)vkGetDeviceProcAddr(
        GVulkanDevice, "vkDestroyFramebuffer"
    );
    if (!vkDestroyFramebuffer)
    {
        // Could not load vkDestroyFramebuffer
        return false;
    }

    // Load vkCreateImageView
    vkCreateImageView = (PFN_vkCreateImageView)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCreateImageView"
    );
    if (!vkCreateImageView)
    {
        // Could not load vkCreateImageView
        return false;
    }

    // Load vkDestroyImageView
    vkDestroyImageView = (PFN_vkDestroyImageView)vkGetDeviceProcAddr(
        GVulkanDevice, "vkDestroyImageView"
    );
    if (!vkDestroyImageView)
    {
        // Could not load vkDestroyImageView
        return false;
    }

    // Load vkCreateShaderModule
    vkCreateShaderModule = (PFN_vkCreateShaderModule)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCreateShaderModule"
    );
    if (!vkCreateShaderModule)
    {
        // Could not load vkCreateShaderModule
        return false;
    }

    // Load vkDestroyShaderModule
    vkDestroyShaderModule = (PFN_vkDestroyShaderModule)vkGetDeviceProcAddr(
        GVulkanDevice, "vkDestroyShaderModule"
    );
    if (!vkDestroyShaderModule)
    {
        // Could not load vkDestroyShaderModule
        return false;
    }

    // Load vkCreatePipelineCache
    vkCreatePipelineCache = (PFN_vkCreatePipelineCache)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCreatePipelineCache"
    );
    if (!vkCreatePipelineCache)
    {
        // Could not load vkCreatePipelineCache
        return false;
    }

    // Load vkDestroyPipelineCache
    vkDestroyPipelineCache = (PFN_vkDestroyPipelineCache)vkGetDeviceProcAddr(
        GVulkanDevice, "vkDestroyPipelineCache"
    );
    if (!vkDestroyPipelineCache)
    {
        // Could not load vkDestroyPipelineCache
        return false;
    }

    // Load vkGetPipelineCacheData
    vkGetPipelineCacheData = (PFN_vkGetPipelineCacheData)vkGetDeviceProcAddr(
        GVulkanDevice, "vkGetPipelineCacheData"
    );
    if (!vkGetPipelineCacheData)
    {
        // Could not load vkGetPipelineCacheData
        return false;
    }

    // Load vkMergePipelineCaches
    vkMergePipelineCaches = (PFN_vkMergePipelineCaches)vkGetDeviceProcAddr(
        GVulkanDevice, "vkMergePipelineCaches"
    );
    if (!vkMergePipelineCaches)
    {
        // Could not load vkMergePipelineCaches
        return false;
    }

    // Load vkCreatePipelineLayout
    vkCreatePipelineLayout = (PFN_vkCreatePipelineLayout)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCreatePipelineLayout"
    );
    if (!vkCreatePipelineLayout)
    {
        // Could not load vkCreatePipelineLayout
        return false;
    }

    // Load vkDestroyPipelineLayout
    vkDestroyPipelineLayout = (PFN_vkDestroyPipelineLayout)vkGetDeviceProcAddr(
        GVulkanDevice, "vkDestroyPipelineLayout"
    );
    if (!vkDestroyPipelineLayout)
    {
        // Could not load vkDestroyPipelineLayout
        return false;
    }

    // Load vkCreateSampler
    vkCreateSampler = (PFN_vkCreateSampler)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCreateSampler"
    );
    if (!vkCreateSampler)
    {
        // Could not load vkCreateSampler
        return false;
    }

    // Load vkDestroySampler
    vkDestroySampler = (PFN_vkDestroySampler)vkGetDeviceProcAddr(
        GVulkanDevice, "vkDestroySampler"
    );
    if (!vkDestroySampler)
    {
        // Could not load vkDestroySampler
        return false;
    }

    // Load vkCreateGraphicsPipelines
    vkCreateGraphicsPipelines = (PFN_vkCreateGraphicsPipelines)
        vkGetDeviceProcAddr(GVulkanDevice, "vkCreateGraphicsPipelines"
    );
    if (!vkCreateGraphicsPipelines)
    {
        // Could not load vkCreateGraphicsPipelines
        return false;
    }

    // Load vkCreateComputePipelines
    vkCreateComputePipelines = (PFN_vkCreateComputePipelines)
        vkGetDeviceProcAddr(GVulkanDevice, "vkCreateComputePipelines"
    );
    if (!vkCreateComputePipelines)
    {
        // Could not load vkCreateComputePipelines
        return false;
    }

    // Load vkDestroyPipeline
    vkDestroyPipeline = (PFN_vkDestroyPipeline)vkGetDeviceProcAddr(
        GVulkanDevice, "vkDestroyPipeline"
    );
    if (!vkDestroyPipeline)
    {
        // Could not load vkDestroyPipeline
        return false;
    }

    // Load vkCreateDescriptorSetLayout
    vkCreateDescriptorSetLayout = (PFN_vkCreateDescriptorSetLayout)
        vkGetDeviceProcAddr(GVulkanDevice, "vkCreateDescriptorSetLayout"
    );
    if (!vkCreateDescriptorSetLayout)
    {
        // Could not load vkCreateDescriptorSetLayout
        return false;
    }

    // Load vkDestroyDescriptorSetLayout
    vkDestroyDescriptorSetLayout = (PFN_vkDestroyDescriptorSetLayout)
        vkGetDeviceProcAddr(GVulkanDevice, "vkDestroyDescriptorSetLayout"
    );
    if (!vkDestroyDescriptorSetLayout)
    {
        // Could not load vkDestroyDescriptorSetLayout
        return false;
    }

    // Load vkCreateDescriptorPool
    vkCreateDescriptorPool = (PFN_vkCreateDescriptorPool)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCreateDescriptorPool"
    );
    if (!vkCreateDescriptorPool)
    {
        // Could not load vkCreateDescriptorPool
        return false;
    }

    // Load vkDestroyDescriptorPool
    vkDestroyDescriptorPool = (PFN_vkDestroyDescriptorPool)vkGetDeviceProcAddr(
        GVulkanDevice, "vkDestroyDescriptorPool"
    );
    if (!vkDestroyDescriptorPool)
    {
        // Could not load vkDestroyDescriptorPool
        return false;
    }

    // Load vkResetDescriptorPool
    vkResetDescriptorPool = (PFN_vkResetDescriptorPool)vkGetDeviceProcAddr(
        GVulkanDevice, "vkResetDescriptorPool"
    );
    if (!vkResetDescriptorPool)
    {
        // Could not load vkResetDescriptorPool
        return false;
    }

    // Load vkAllocateDescriptorSets
    vkAllocateDescriptorSets = (PFN_vkAllocateDescriptorSets)
        vkGetDeviceProcAddr(GVulkanDevice, "vkAllocateDescriptorSets"
    );
    if (!vkAllocateDescriptorSets)
    {
        // Could not load vkAllocateDescriptorSets
        return false;
    }

    // Load vkFreeDescriptorSets
    vkFreeDescriptorSets = (PFN_vkFreeDescriptorSets)vkGetDeviceProcAddr(
        GVulkanDevice, "vkFreeDescriptorSets"
    );
    if (!vkFreeDescriptorSets)
    {
        // Could not load vkFreeDescriptorSets
        return false;
    }

    // Load vkUpdateDescriptorSets
    vkUpdateDescriptorSets = (PFN_vkUpdateDescriptorSets)vkGetDeviceProcAddr(
        GVulkanDevice, "vkUpdateDescriptorSets"
    );
    if (!vkUpdateDescriptorSets)
    {
        // Could not load vkUpdateDescriptorSets
        return false;
    }

    // Load vkCreateBuffer
    vkCreateBuffer = (PFN_vkCreateBuffer)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCreateBuffer"
    );
    if (!vkCreateBuffer)
    {
        // Could not load vkCreateBuffer
        return false;
    }

    // Load vkDestroyBuffer
    vkDestroyBuffer = (PFN_vkDestroyBuffer)vkGetDeviceProcAddr(
        GVulkanDevice, "vkDestroyBuffer"
    );
    if (!vkDestroyBuffer)
    {
        // Could not load vkDestroyBuffer
        return false;
    }

    // Load vkCreateBufferView
    vkCreateBufferView = (PFN_vkCreateBufferView)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCreateBufferView"
    );
    if (!vkCreateBufferView)
    {
        // Could not load vkCreateBufferView
        return false;
    }

    // Load vkDestroyBufferView
    vkDestroyBufferView = (PFN_vkDestroyBufferView)vkGetDeviceProcAddr(
        GVulkanDevice, "vkDestroyBufferView"
    );
    if (!vkDestroyBufferView)
    {
        // Could not load vkDestroyBufferView
        return false;
    }

    // Load vkCreateImage
    vkCreateImage = (PFN_vkCreateImage)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCreateImage"
    );
    if (!vkCreateImage)
    {
        // Could not load vkCreateImage
        return false;
    }

    // Load vkDestroyImage
    vkDestroyImage = (PFN_vkDestroyImage)vkGetDeviceProcAddr(
        GVulkanDevice, "vkDestroyImage"
    );
    if (!vkDestroyImage)
    {
        // Could not load vkDestroyImage
        return false;
    }

    // Load vkGetImageSubresourceLayout
    vkGetImageSubresourceLayout = (PFN_vkGetImageSubresourceLayout)
        vkGetDeviceProcAddr(GVulkanDevice, "vkGetImageSubresourceLayout"
    );
    if (!vkGetImageSubresourceLayout)
    {
        // Could not load vkGetImageSubresourceLayout
        return false;
    }

    // Load vkGetBufferMemoryRequirements
    vkGetBufferMemoryRequirements = (PFN_vkGetBufferMemoryRequirements)
        vkGetDeviceProcAddr(GVulkanDevice, "vkGetBufferMemoryRequirements"
    );
    if (!vkGetBufferMemoryRequirements)
    {
        // Could not load vkGetBufferMemoryRequirements
        return false;
    }

    // Load vkGetImageMemoryRequirements
    vkGetImageMemoryRequirements = (PFN_vkGetImageMemoryRequirements)
        vkGetDeviceProcAddr(GVulkanDevice, "vkGetImageMemoryRequirements"
    );
    if (!vkGetImageMemoryRequirements)
    {
        // Could not load vkGetImageMemoryRequirements
        return false;
    }

    // Load vkGetImageSparseMemoryRequirements
    vkGetImageSparseMemoryRequirements =
        (PFN_vkGetImageSparseMemoryRequirements)vkGetDeviceProcAddr(
        GVulkanDevice, "vkGetImageSparseMemoryRequirements"
    );
    if (!vkGetImageSparseMemoryRequirements)
    {
        // Could not load vkGetImageSparseMemoryRequirements
        return false;
    }

    // Load vkQueueBindSparse
    vkQueueBindSparse = (PFN_vkQueueBindSparse)vkGetDeviceProcAddr(
        GVulkanDevice, "vkQueueBindSparse"
    );
    if (!vkQueueBindSparse)
    {
        // Could not load vkQueueBindSparse
        return false;
    }

    // Load vkCreateFence
    vkCreateFence = (PFN_vkCreateFence)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCreateFence"
    );
    if (!vkCreateFence)
    {
        // Could not load vkCreateFence
        return false;
    }

    // Load vkDestroyFence
    vkDestroyFence = (PFN_vkDestroyFence)vkGetDeviceProcAddr(
        GVulkanDevice, "vkDestroyFence"
    );
    if (!vkDestroyFence)
    {
        // Could not load vkDestroyFence
        return false;
    }

    // Load vkResetFences
    vkResetFences = (PFN_vkResetFences)vkGetDeviceProcAddr(
        GVulkanDevice, "vkResetFences"
    );
    if (!vkResetFences)
    {
        // Could not load vkResetFences
        return false;
    }

    // Load vkGetFenceStatus
    vkGetFenceStatus = (PFN_vkGetFenceStatus)vkGetDeviceProcAddr(
        GVulkanDevice, "vkGetFenceStatus"
    );
    if (!vkGetFenceStatus)
    {
        // Could not load vkGetFenceStatus
        return false;
    }

    // Load vkWaitForFences
    vkWaitForFences = (PFN_vkWaitForFences)vkGetDeviceProcAddr(
        GVulkanDevice, "vkWaitForFences"
    );
    if (!vkWaitForFences)
    {
        // Could not load vkWaitForFences
        return false;
    }

    // Load vkCreateSemaphore
    vkCreateSemaphore = (PFN_vkCreateSemaphore)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCreateSemaphore"
    );
    if (!vkCreateSemaphore)
    {
        // Could not load vkCreateSemaphore
        return false;
    }

    // Load vkDestroySemaphore
    vkDestroySemaphore = (PFN_vkDestroySemaphore)vkGetDeviceProcAddr(
        GVulkanDevice, "vkDestroySemaphore"
    );
    if (!vkDestroySemaphore)
    {
        // Could not load vkDestroySemaphore
        return false;
    }

    // Load vkCreateEvent
    vkCreateEvent = (PFN_vkCreateEvent)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCreateEvent"
    );
    if (!vkCreateEvent)
    {
        // Could not load vkCreateEvent
        return false;
    }

    // Load vkDestroyEvent
    vkDestroyEvent = (PFN_vkDestroyEvent)vkGetDeviceProcAddr(
        GVulkanDevice, "vkDestroyEvent"
    );
    if (!vkDestroyEvent)
    {
        // Could not load vkDestroyEvent
        return false;
    }

    // Load vkGetEventStatus
    vkGetEventStatus = (PFN_vkGetEventStatus)vkGetDeviceProcAddr(
        GVulkanDevice, "vkGetEventStatus"
    );
    if (!vkGetEventStatus)
    {
        // Could not load vkGetEventStatus
        return false;
    }

    // Load vkSetEvent
    vkSetEvent = (PFN_vkSetEvent)vkGetDeviceProcAddr(
        GVulkanDevice, "vkSetEvent"
    );
    if (!vkSetEvent)
    {
        // Could not load vkSetEvent
        return false;
    }

    // Load vkResetEvent
    vkResetEvent = (PFN_vkResetEvent)vkGetDeviceProcAddr(
        GVulkanDevice, "vkResetEvent"
    );
    if (!vkResetEvent)
    {
        // Could not load vkResetEvent
        return false;
    }

    // Load vkCreateQueryPool
    vkCreateQueryPool = (PFN_vkCreateQueryPool)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCreateQueryPool"
    );
    if (!vkCreateQueryPool)
    {
        // Could not load vkCreateQueryPool
        return false;
    }

    // Load vkDestroyQueryPool
    vkDestroyQueryPool = (PFN_vkDestroyQueryPool)vkGetDeviceProcAddr(
        GVulkanDevice, "vkDestroyQueryPool"
    );
    if (!vkDestroyQueryPool)
    {
        // Could not load vkDestroyQueryPool
        return false;
    }

    // Load vkGetQueryPoolResults
    vkGetQueryPoolResults = (PFN_vkGetQueryPoolResults)vkGetDeviceProcAddr(
        GVulkanDevice, "vkGetQueryPoolResults"
    );
    if (!vkGetQueryPoolResults)
    {
        // Could not load vkGetQueryPoolResults
        return false;
    }

    // Load vkCreateCommandPool
    vkCreateCommandPool = (PFN_vkCreateCommandPool)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCreateCommandPool"
    );
    if (!vkCreateCommandPool)
    {
        // Could not load vkCreateCommandPool
        return false;
    }

    // Load vkDestroyCommandPool
    vkDestroyCommandPool = (PFN_vkDestroyCommandPool)vkGetDeviceProcAddr(
        GVulkanDevice, "vkDestroyCommandPool"
    );
    if (!vkDestroyCommandPool)
    {
        // Could not load vkDestroyCommandPool
        return false;
    }

    // Load vkResetCommandPool
    vkResetCommandPool = (PFN_vkResetCommandPool)vkGetDeviceProcAddr(
        GVulkanDevice, "vkResetCommandPool"
    );
    if (!vkResetCommandPool)
    {
        // Could not load vkResetCommandPool
        return false;
    }

    // Load vkAllocateCommandBuffers
    vkAllocateCommandBuffers = (PFN_vkAllocateCommandBuffers)
        vkGetDeviceProcAddr(GVulkanDevice, "vkAllocateCommandBuffers"
    );
    if (!vkAllocateCommandBuffers)
    {
        // Could not load vkAllocateCommandBuffers
        return false;
    }

    // Load vkFreeCommandBuffers
    vkFreeCommandBuffers = (PFN_vkFreeCommandBuffers)vkGetDeviceProcAddr(
        GVulkanDevice, "vkFreeCommandBuffers"
    );
    if (!vkFreeCommandBuffers)
    {
        // Could not load vkFreeCommandBuffers
        return false;
    }

    // Load vkBeginCommandBuffer
    vkBeginCommandBuffer = (PFN_vkBeginCommandBuffer)vkGetDeviceProcAddr(
        GVulkanDevice, "vkBeginCommandBuffer"
    );
    if (!vkBeginCommandBuffer)
    {
        // Could not load vkBeginCommandBuffer
        return false;
    }

    // Load vkBeginCommandBuffer
    vkEndCommandBuffer = (PFN_vkEndCommandBuffer)vkGetDeviceProcAddr(
        GVulkanDevice, "vkEndCommandBuffer"
    );
    if (!vkEndCommandBuffer)
    {
        // Could not load vkEndCommandBuffer
        return false;
    }

    // Load vkResetCommandBuffer
    vkResetCommandBuffer = (PFN_vkResetCommandBuffer)vkGetDeviceProcAddr(
        GVulkanDevice, "vkResetCommandBuffer"
    );
    if (!vkResetCommandBuffer)
    {
        // Could not load vkResetCommandBuffer
        return false;
    }


    // Load vkCmdBindPipeline
    vkCmdBindPipeline = (PFN_vkCmdBindPipeline)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdBindPipeline"
    );
    if (!vkCmdBindPipeline)
    {
        // Could not load vkCmdBindPipeline
        return false;
    }

    // Load vkCmdSetViewport
    vkCmdSetViewport = (PFN_vkCmdSetViewport)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdSetViewport"
    );
    if (!vkCmdSetViewport)
    {
        // Could not load vkCmdSetViewport
        return false;
    }

    // Load vkCmdSetScissor
    vkCmdSetScissor = (PFN_vkCmdSetScissor)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdSetScissor"
    );
    if (!vkCmdSetScissor)
    {
        // Could not load vkCmdSetScissor
        return false;
    }

    // Load vkCmdSetLineWidth
    vkCmdSetLineWidth = (PFN_vkCmdSetLineWidth)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdSetLineWidth"
    );
    if (!vkCmdSetLineWidth)
    {
        // Could not load vkCmdSetLineWidth
        return false;
    }

    // Load vkCmdSetDepthBias
    vkCmdSetDepthBias = (PFN_vkCmdSetDepthBias)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdSetDepthBias"
    );
    if (!vkCmdSetDepthBias)
    {
        // Could not load vkCmdSetDepthBias
        return false;
    }

    // Load vkCmdSetBlendConstants
    vkCmdSetBlendConstants = (PFN_vkCmdSetBlendConstants)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdSetBlendConstants"
    );
    if (!vkCmdSetBlendConstants)
    {
        // Could not load vkCmdSetBlendConstants
        return false;
    }

    // Load vkCmdSetDepthBounds
    vkCmdSetDepthBounds = (PFN_vkCmdSetDepthBounds)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdSetDepthBounds"
    );
    if (!vkCmdSetDepthBounds)
    {
        // Could not load vkCmdSetDepthBounds
        return false;
    }

    // Load vkCmdSetStencilCompareMask
    vkCmdSetStencilCompareMask = (PFN_vkCmdSetStencilCompareMask)
        vkGetDeviceProcAddr(GVulkanDevice, "vkCmdSetStencilCompareMask"
    );
    if (!vkCmdSetStencilCompareMask)
    {
        // Could not load vkCmdSetStencilCompareMask
        return false;
    }

    // Load vkCmdSetStencilWriteMask
    vkCmdSetStencilWriteMask = (PFN_vkCmdSetStencilWriteMask)
        vkGetDeviceProcAddr(GVulkanDevice, "vkCmdSetStencilWriteMask"
    );
    if (!vkCmdSetStencilWriteMask)
    {
        // Could not load vkCmdSetStencilWriteMask
        return false;
    }

    // Load vkCmdSetStencilReference
    vkCmdSetStencilReference = (PFN_vkCmdSetStencilReference)
        vkGetDeviceProcAddr(GVulkanDevice, "vkCmdSetStencilReference"
    );
    if (!vkCmdSetStencilReference)
    {
        // Could not load vkCmdSetStencilReference
        return false;
    }

    // Load vkCmdBindDescriptorSets
    vkCmdBindDescriptorSets = (PFN_vkCmdBindDescriptorSets)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdBindDescriptorSets"
    );
    if (!vkCmdBindDescriptorSets)
    {
        // Could not load vkCmdBindDescriptorSets
        return false;
    }

    // Load vkCmdBindIndexBuffer
    vkCmdBindIndexBuffer = (PFN_vkCmdBindIndexBuffer)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdBindIndexBuffer"
    );
    if (!vkCmdBindIndexBuffer)
    {
        // Could not load vkCmdBindIndexBuffer
        return false;
    }

    // Load vkCmdBindVertexBuffers
    vkCmdBindVertexBuffers = (PFN_vkCmdBindVertexBuffers)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdBindVertexBuffers"
    );
    if (!vkCmdBindVertexBuffers)
    {
        // Could not load vkCmdBindVertexBuffers
        return false;
    }

    // Load vkCmdDraw
    vkCmdDraw = (PFN_vkCmdDraw)vkGetDeviceProcAddr(GVulkanDevice, "vkCmdDraw");
    if (!vkCmdDraw)
    {
        // Could not load vkCmdDraw
        return false;
    }

    // Load vkCmdDrawIndexed
    vkCmdDrawIndexed = (PFN_vkCmdDrawIndexed)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdDrawIndexed"
    );
    if (!vkCmdDrawIndexed)
    {
        // Could not load vkCmdDrawIndexed
        return false;
    }

    // Load vkCmdDrawIndirect
    vkCmdDrawIndirect = (PFN_vkCmdDrawIndirect)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdDrawIndirect"
    );
    if (!vkCmdDrawIndirect)
    {
        // Could not load vkCmdDrawIndirect
        return false;
    }

    // Load vkCmdDrawIndexedIndirect
    vkCmdDrawIndexedIndirect = (PFN_vkCmdDrawIndexedIndirect)
        vkGetDeviceProcAddr(GVulkanDevice, "vkCmdDrawIndexedIndirect"
    );
    if (!vkCmdDrawIndexedIndirect)
    {
        // Could not load vkCmdDrawIndexedIndirect
        return false;
    }

    // Load vkCmdDispatch
    vkCmdDispatch = (PFN_vkCmdDispatch)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdDispatch"
    );
    if (!vkCmdDispatch)
    {
        // Could not load vkCmdDispatch
        return false;
    }

    // Load vkCmdDispatchIndirect
    vkCmdDispatchIndirect = (PFN_vkCmdDispatchIndirect)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdDispatchIndirect"
    );
    if (!vkCmdDispatchIndirect)
    {
        // Could not load vkCmdDispatchIndirect
        return false;
    }

    // Load vkCmdCopyBuffer
    vkCmdCopyBuffer = (PFN_vkCmdCopyBuffer)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdCopyBuffer"
    );
    if (!vkCmdCopyBuffer)
    {
        // Could not load vkCmdCopyBuffer
        return false;
    }

    // Load vkCmdCopyImage
    vkCmdCopyImage = (PFN_vkCmdCopyImage)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdCopyImage"
    );
    if (!vkCmdCopyImage)
    {
        // Could not load vkCmdCopyImage
        return false;
    }

    // Load vkCmdBlitImage
    vkCmdBlitImage = (PFN_vkCmdBlitImage)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdBlitImage"
    );
    if (!vkCmdBlitImage)
    {
        // Could not load vkCmdBlitImage
        return false;
    }

    // Load vkCmdCopyBufferToImage
    vkCmdCopyBufferToImage = (PFN_vkCmdCopyBufferToImage)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdCopyBufferToImage"
    );
    if (!vkCmdCopyBufferToImage)
    {
        // Could not load vkCmdCopyBufferToImage
        return false;
    }

    // Load vkCmdCopyImageToBuffer
    vkCmdCopyImageToBuffer = (PFN_vkCmdCopyImageToBuffer)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdCopyImageToBuffer"
    );
    if (!vkCmdCopyImageToBuffer)
    {
        // Could not load vkCmdCopyImageToBuffer
        return false;
    }

    // Load vkCmdUpdateBuffer
    vkCmdUpdateBuffer = (PFN_vkCmdUpdateBuffer)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdUpdateBuffer"
    );
    if (!vkCmdUpdateBuffer)
    {
        // Could not load vkCmdUpdateBuffer
        return false;
    }

    // Load vkCmdFillBuffer
    vkCmdFillBuffer = (PFN_vkCmdFillBuffer)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdFillBuffer"
    );
    if (!vkCmdFillBuffer)
    {
        // Could not load vkCmdFillBuffer
        return false;
    }

    // Load vkCmdClearColorImage
    vkCmdClearColorImage = (PFN_vkCmdClearColorImage)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdClearColorImage"
    );
    if (!vkCmdClearColorImage)
    {
        // Could not load vkCmdClearColorImage
        return false;
    }

    // Load vkCmdClearDepthStencilImage
    vkCmdClearDepthStencilImage = (PFN_vkCmdClearDepthStencilImage)
        vkGetDeviceProcAddr(GVulkanDevice, "vkCmdClearDepthStencilImage"
    );
    if (!vkCmdClearDepthStencilImage)
    {
        // Could not load vkCmdClearDepthStencilImage
        return false;
    }

    // Load vkCmdClearAttachments
    vkCmdClearAttachments = (PFN_vkCmdClearAttachments)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdClearAttachments"
    );
    if (!vkCmdClearAttachments)
    {
        // Could not load vkCmdClearAttachments
        return false;
    }

    // Load vkCmdResolveImage
    vkCmdResolveImage = (PFN_vkCmdResolveImage)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdResolveImage"
    );
    if (!vkCmdResolveImage)
    {
        // Could not load vkCmdResolveImage
        return false;
    }

    // Load vkCmdSetEvent
    vkCmdSetEvent = (PFN_vkCmdSetEvent)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdSetEvent"
    );
    if (!vkCmdSetEvent)
    {
        // Could not load vkCmdSetEvent
        return false;
    }

    // Load vkCmdResetEvent
    vkCmdResetEvent = (PFN_vkCmdResetEvent)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdResetEvent"
    );
    if (!vkCmdResetEvent)
    {
        // Could not load vkCmdResetEvent
        return false;
    }

    // Load vkCmdWaitEvents
    vkCmdWaitEvents = (PFN_vkCmdWaitEvents)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdWaitEvents"
    );
    if (!vkCmdWaitEvents)
    {
        // Could not load vkCmdWaitEvents
        return false;
    }

    // Load vkCmdPipelineBarrier
    vkCmdPipelineBarrier = (PFN_vkCmdPipelineBarrier)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdPipelineBarrier"
    );
    if (!vkCmdPipelineBarrier)
    {
        // Could not load vkCmdPipelineBarrier
        return false;
    }

    // Load vkCmdBeginQuery
    vkCmdBeginQuery = (PFN_vkCmdBeginQuery)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdBeginQuery"
    );
    if (!vkCmdBeginQuery)
    {
        // Could not load vkCmdBeginQuery
        return false;
    }

    // Load vkCmdEndQuery
    vkCmdEndQuery = (PFN_vkCmdEndQuery)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdEndQuery"
    );
    if (!vkCmdEndQuery)
    {
        // Could not load vkCmdEndQuery
        return false;
    }

    // Load vkCmdResetQueryPool
    vkCmdResetQueryPool = (PFN_vkCmdResetQueryPool)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdResetQueryPool"
    );
    if (!vkCmdResetQueryPool)
    {
        // Could not load vkCmdResetQueryPool
        return false;
    }

    // Load vkCmdWriteTimestamp
    vkCmdWriteTimestamp = (PFN_vkCmdWriteTimestamp)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdWriteTimestamp"
    );
    if (!vkCmdWriteTimestamp)
    {
        // Could not load vkCmdWriteTimestamp
        return false;
    }

    // Load vkCmdCopyQueryPoolResults
    vkCmdCopyQueryPoolResults = (PFN_vkCmdCopyQueryPoolResults)
        vkGetDeviceProcAddr(GVulkanDevice, "vkCmdCopyQueryPoolResults"
    );
    if (!vkCmdCopyQueryPoolResults)
    {
        // Could not load vkCmdCopyQueryPoolResults
        return false;
    }

    // Load vkCmdPushConstants
    vkCmdPushConstants = (PFN_vkCmdPushConstants)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdPushConstants"
    );
    if (!vkCmdPushConstants)
    {
        // Could not load vkCmdPushConstants
        return false;
    }

    // Load vkCmdBeginRenderPass
    vkCmdBeginRenderPass = (PFN_vkCmdBeginRenderPass)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdBeginRenderPass"
    );
    if (!vkCmdBeginRenderPass)
    {
        // Could not load vkCmdBeginRenderPass
        return false;
    }

    // Load vkCmdNextSubpass
    vkCmdNextSubpass = (PFN_vkCmdNextSubpass)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdNextSubpass"
    );
    if (!vkCmdNextSubpass)
    {
        // Could not load vkCmdNextSubpass
        return false;
    }

    // Load vkCmdEndRenderPass
    vkCmdEndRenderPass = (PFN_vkCmdEndRenderPass)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdEndRenderPass"
    );
    if (!vkCmdEndRenderPass)
    {
        // Could not load vkCmdEndRenderPass
        return false;
    }

    // Load vkCmdExecuteCommands
    vkCmdExecuteCommands = (PFN_vkCmdExecuteCommands)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdExecuteCommands"
    );
    if (!vkCmdExecuteCommands)
    {
        // Could not load vkCmdExecuteCommands
        return false;
    }


    // Load vkBindBufferMemory2
    vkBindBufferMemory2 = (PFN_vkBindBufferMemory2)vkGetDeviceProcAddr(
        GVulkanDevice, "vkBindBufferMemory2"
    );
    if (!vkBindBufferMemory2)
    {
        // Could not load vkBindBufferMemory2
        return false;
    }

    // Load vkBindImageMemory2
    vkBindImageMemory2 = (PFN_vkBindImageMemory2)vkGetDeviceProcAddr(
        GVulkanDevice, "vkBindImageMemory2"
    );
    if (!vkBindImageMemory2)
    {
        // Could not load vkBindImageMemory2
        return false;
    }

    // Load vkGetDeviceGroupPeerMemoryFeatures
    vkGetDeviceGroupPeerMemoryFeatures =
        (PFN_vkGetDeviceGroupPeerMemoryFeatures)vkGetDeviceProcAddr(
        GVulkanDevice, "vkGetDeviceGroupPeerMemoryFeatures"
    );
    if (!vkGetDeviceGroupPeerMemoryFeatures)
    {
        // Could not load vkGetDeviceGroupPeerMemoryFeatures
        return false;
    }

    // Load vkCmdSetDeviceMask
    vkCmdSetDeviceMask = (PFN_vkCmdSetDeviceMask)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdSetDeviceMask"
    );
    if (!vkCmdSetDeviceMask)
    {
        // Could not load vkCmdSetDeviceMask
        return false;
    }

    // Load vkCmdDispatchBase
    vkCmdDispatchBase = (PFN_vkCmdDispatchBase)vkGetDeviceProcAddr(
        GVulkanDevice, "vkCmdDispatchBase"
    );
    if (!vkCmdDispatchBase)
    {
        // Could not load vkCmdDispatchBase
        return false;
    }

    // Load vkGetImageMemoryRequirements2
    vkGetImageMemoryRequirements2 = (PFN_vkGetImageMemoryRequirements2)
        vkGetDeviceProcAddr(GVulkanDevice, "vkGetImageMemoryRequirements2"
    );
    if (!vkGetImageMemoryRequirements2)
    {
        // Could not load vkGetImageMemoryRequirements2
        return false;
    }

    // Load vkGetBufferMemoryRequirements2
    vkGetBufferMemoryRequirements2 = (PFN_vkGetBufferMemoryRequirements2)
        vkGetDeviceProcAddr(GVulkanDevice, "vkGetBufferMemoryRequirements2"
    );
    if (!vkGetBufferMemoryRequirements2)
    {
        // Could not load vkGetBufferMemoryRequirements2
        return false;
    }

    // Load vkGetImageSparseMemoryRequirements2
    vkGetImageSparseMemoryRequirements2 =
        (PFN_vkGetImageSparseMemoryRequirements2)vkGetDeviceProcAddr(
        GVulkanDevice, "vkGetImageSparseMemoryRequirements2"
    );
    if (!vkGetImageSparseMemoryRequirements2)
    {
        // Could not load vkGetImageSparseMemoryRequirements2
        return false;
    }

    // Load vkTrimCommandPool
    vkTrimCommandPool = (PFN_vkTrimCommandPool)vkGetDeviceProcAddr(
        GVulkanDevice, "vkTrimCommandPool"
    );
    if (!vkTrimCommandPool)
    {
        // Could not load vkTrimCommandPool
        return false;
    }

    // Load vkGetDeviceQueue2
    vkGetDeviceQueue2 = (PFN_vkGetDeviceQueue2)vkGetDeviceProcAddr(
        GVulkanDevice, "vkGetDeviceQueue2"
    );
    if (!vkGetDeviceQueue2)
    {
        // Could not load vkGetDeviceQueue2
        return false;
    }

    // Load vkCreateSamplerYcbcrConversion
    vkCreateSamplerYcbcrConversion = (PFN_vkCreateSamplerYcbcrConversion)
        vkGetDeviceProcAddr(GVulkanDevice, "vkCreateSamplerYcbcrConversion"
    );
    if (!vkCreateSamplerYcbcrConversion)
    {
        // Could not load vkCreateSamplerYcbcrConversion
        return false;
    }

    // Load vkDestroySamplerYcbcrConversion
    vkDestroySamplerYcbcrConversion = (PFN_vkDestroySamplerYcbcrConversion)
        vkGetDeviceProcAddr(GVulkanDevice, "vkDestroySamplerYcbcrConversion"
    );
    if (!vkDestroySamplerYcbcrConversion)
    {
        // Could not load vkDestroySamplerYcbcrConversion
        return false;
    }

    // Load vkCreateDescriptorUpdateTemplate
    vkCreateDescriptorUpdateTemplate = (PFN_vkCreateDescriptorUpdateTemplate)
        vkGetDeviceProcAddr(GVulkanDevice, "vkCreateDescriptorUpdateTemplate"
    );
    if (!vkCreateDescriptorUpdateTemplate)
    {
        // Could not load vkCreateDescriptorUpdateTemplate
        return false;
    }

    // Load vkDestroyDescriptorUpdateTemplate
    vkDestroyDescriptorUpdateTemplate = (PFN_vkDestroyDescriptorUpdateTemplate)
        vkGetDeviceProcAddr(GVulkanDevice, "vkDestroyDescriptorUpdateTemplate"
    );
    if (!vkDestroyDescriptorUpdateTemplate)
    {
        // Could not load vkDestroyDescriptorUpdateTemplate
        return false;
    }

    // Load vkUpdateDescriptorSetWithTemplate
    vkUpdateDescriptorSetWithTemplate = (PFN_vkUpdateDescriptorSetWithTemplate)
        vkGetDeviceProcAddr(GVulkanDevice, "vkUpdateDescriptorSetWithTemplate"
    );
    if (!vkUpdateDescriptorSetWithTemplate)
    {
        // Could not load vkUpdateDescriptorSetWithTemplate
        return false;
    }

    // Load vkGetDescriptorSetLayoutSupport
    vkGetDescriptorSetLayoutSupport = (PFN_vkGetDescriptorSetLayoutSupport)
        vkGetDeviceProcAddr(GVulkanDevice, "vkGetDescriptorSetLayoutSupport"
    );
    if (!vkGetDescriptorSetLayoutSupport)
    {
        // Could not load vkGetDescriptorSetLayoutSupport
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
    vkGetDescriptorSetLayoutSupport = 0;
    vkUpdateDescriptorSetWithTemplate = 0;
    vkDestroyDescriptorUpdateTemplate = 0;
    vkCreateDescriptorUpdateTemplate = 0;
    vkDestroySamplerYcbcrConversion = 0;
    vkCreateSamplerYcbcrConversion = 0;
    vkGetDeviceQueue2 = 0;
    vkTrimCommandPool = 0;
    vkGetImageSparseMemoryRequirements2 = 0;
    vkGetBufferMemoryRequirements2 = 0;
    vkGetImageMemoryRequirements2 = 0;
    vkCmdDispatchBase = 0;
    vkCmdSetDeviceMask = 0;
    vkGetDeviceGroupPeerMemoryFeatures = 0;
    vkBindImageMemory2 = 0;
    vkBindBufferMemory2 = 0;

    vkCmdExecuteCommands = 0;
    vkCmdEndRenderPass = 0;
    vkCmdNextSubpass = 0;
    vkCmdBeginRenderPass = 0;
    vkCmdPushConstants = 0;
    vkCmdCopyQueryPoolResults = 0;
    vkCmdWriteTimestamp = 0;
    vkCmdResetQueryPool = 0;
    vkCmdEndQuery = 0;
    vkCmdBeginQuery = 0;
    vkCmdPipelineBarrier = 0;
    vkCmdWaitEvents = 0;
    vkCmdResetEvent = 0;
    vkCmdSetEvent = 0;
    vkCmdResolveImage = 0;
    vkCmdClearAttachments = 0;
    vkCmdClearDepthStencilImage = 0;
    vkCmdClearColorImage = 0;
    vkCmdFillBuffer = 0;
    vkCmdUpdateBuffer = 0;
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

    vkAcquireNextImage2KHR = 0;
    //vkGetPhysicalDevicePresentRectanglesKHR = 0;
    vkGetDeviceGroupSurfacePresentModesKHR = 0;
    vkGetDeviceGroupPresentCapabilitiesKHR = 0;
    vkQueuePresentKHR = 0;
    vkAcquireNextImageKHR = 0;
    vkGetSwapchainImagesKHR = 0;
    vkDestroySwapchainKHR = 0;
    vkCreateSwapchainKHR = 0;

    vkGetPhysicalDeviceExternalSemaphoreProperties = 0;
    vkGetPhysicalDeviceExternalFenceProperties = 0;
    vkGetPhysicalDeviceExternalBufferProperties = 0;
    vkGetPhysicalDeviceSparseImageFormatProperties2 = 0;
    vkGetPhysicalDeviceMemoryProperties2 = 0;
    vkGetPhysicalDeviceQueueFamilyProperties2 = 0;
    vkGetPhysicalDeviceImageFormatProperties2 = 0;
    vkGetPhysicalDeviceFormatProperties2 = 0;
    vkGetPhysicalDeviceProperties2 = 0;
    vkGetPhysicalDeviceFeatures2 = 0;

    vkGetPhysicalDeviceSurfacePresentModesKHR = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR = 0;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR = 0;
    vkGetPhysicalDeviceSurfaceSupportKHR = 0;
    vkDestroySurfaceKHR = 0;

    vkEnumeratePhysicalDeviceGroups = 0;
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

    vkEnumerateInstanceVersion = 0;
    vkEnumerateInstanceLayerProperties = 0;
    vkEnumerateInstanceExtensionProperties = 0;
    vkCreateInstance = 0;
}
