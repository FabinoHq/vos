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
//     Renderer/Vulkan/VulkanQueue.cpp : Vulkan Queue management              //
////////////////////////////////////////////////////////////////////////////////
#include "VulkanQueue.h"


////////////////////////////////////////////////////////////////////////////////
//  VulkanQueues global instance                                              //
////////////////////////////////////////////////////////////////////////////////
VulkanDeviceQueues GVulkanQueues = VulkanDeviceQueues();


////////////////////////////////////////////////////////////////////////////////
//  VulkanQueue default constructor                                           //
////////////////////////////////////////////////////////////////////////////////
VulkanQueue::VulkanQueue() :
handle(0),
family(0),
index(0),
shared(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  VulkanQueue destructor                                                    //
////////////////////////////////////////////////////////////////////////////////
VulkanQueue::~VulkanQueue()
{
    shared = 0;
    index = 0;
    family = 0;
    handle = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Get Vulkan queue                                                          //
//  return : True if the Vulkan queue is successfully retrieved               //
////////////////////////////////////////////////////////////////////////////////
bool VulkanQueue::getVulkanQueue(VulkanQueuePool queuePool)
{
    // Check Vulkan device
    if (!GVulkanDevice)
    {
        // Invalid Vulkan device
        GSysMessage << "[0x301C] Invalid Vulkan device\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Get queue handle
    vkGetDeviceQueue(GVulkanDevice, 0, 0, &handle);
    if (!handle)
    {
        // Invalid queue handle
        GSysMessage << "[0x301D] Invalid graphics queue handle\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Set shared mutex
    shared = 1;

    // Graphics queue successfully created
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Get Vulkan queue families availables for the device                       //
//  return : True if the device supports all queue families                   //
////////////////////////////////////////////////////////////////////////////////
bool VulkanQueue::getDeviceQueues(VkPhysicalDevice& physicalDevice)
{
    // Check Vulkan surface
    if (!GVulkanSurface)
    {
        // Invalid Vulkan surface
        GSysMessage << "[0x3015] Invalid Vulkan surface\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Check physical device
    if (!physicalDevice)
    {
        // Invalid physical device
        GSysMessage << "[0x3016] Invalid physical device\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Get device queue families
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(
        physicalDevice, &queueFamilyCount, 0
    );
    if (queueFamilyCount <= 0)
    {
        // No device queue families found
        return false;
    }

    // Get device queue families list
    VkQueueFamilyProperties* queueFamilies =
        GSysMemory.alloc<VkQueueFamilyProperties>(
            queueFamilyCount, SYSMEMORY_RENDERER
        );
    if (!queueFamilies) { return false; }
    for (uint32_t i = 0; i < queueFamilyCount; ++i)
    {
        queueFamilies[i] = VkQueueFamilyProperties();
    }
    VkBool32* queueSurfaceSupport =
        GSysMemory.alloc<VkBool32>(queueFamilyCount, SYSMEMORY_RENDERER);
    if (!queueSurfaceSupport) { return false; }
    for (uint32_t i = 0; i < queueFamilyCount; ++i)
    {
        queueSurfaceSupport[i] = VkBool32();
    }

    vkGetPhysicalDeviceQueueFamilyProperties(
        physicalDevice, &queueFamilyCount, queueFamilies
    );
    for (uint32_t i = 0; i < queueFamilyCount; ++i)
    {
        if (vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i,
            GVulkanSurface, &queueSurfaceSupport[i]) != VK_SUCCESS)
        {
            // Could not get physical device surface support
            continue;
        }

        if ((queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) &&
            (queueFamilies[i].queueFlags & VK_QUEUE_COMPUTE_BIT) &&
            (queueFamilies[i].queueFlags & VK_QUEUE_TRANSFER_BIT) &&
            (queueSurfaceSupport[i]))
        {
            // Queue family supports graphics, compute, transfer, and surface
            break;
        }
    }

    return true;
}
