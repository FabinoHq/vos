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
//     Renderer/Vulkan/VulkanQueue.cpp : Vulkan Queue management              //
////////////////////////////////////////////////////////////////////////////////
#include "VulkanQueue.h"


////////////////////////////////////////////////////////////////////////////////
//  VulkanQueue default constructor                                           //
////////////////////////////////////////////////////////////////////////////////
VulkanQueue::VulkanQueue() :
handle(0),
index(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  VulkanQueue destructor                                                    //
////////////////////////////////////////////////////////////////////////////////
VulkanQueue::~VulkanQueue()
{
    index = 0;
    handle = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Create Vulkan queue from index                                            //
//  return : True if the queue is successfully created                        //
////////////////////////////////////////////////////////////////////////////////
bool VulkanQueue::createVulkanQueue(VkDevice& vulkanDevice)
{
    // Check Vulkan device
    if (!vulkanDevice)
    {
        // Invalid Vulkan device
        SysMessage::box() << "[0x301E] Invalid Vulkan device\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Get queue handle
    vkGetDeviceQueue(vulkanDevice, index, 0, &handle);
    if (!handle)
    {
        // Invalid queue handle
        SysMessage::box() << "[0x301F] Invalid queue handle\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Vulkan queue successfully created
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Get Vulkan queue families availables for the device                       //
//  return : True if the device supports all queue families                   //
////////////////////////////////////////////////////////////////////////////////
bool VulkanQueue::getDeviceQueues(VkSurfaceKHR& vulkanSurface,
    VkPhysicalDevice& physicalDevice, VulkanQueue& graphicsQueue,
    VulkanQueue& surfaceQueue, VulkanQueue& transferQueue)
{
    // Check Vulkan surface
    if (!vulkanSurface)
    {
        // Invalid Vulkan surface
        SysMessage::box() << "[0x3015] Invalid Vulkan surface\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Check physical device
    if (!physicalDevice)
    {
        // Invalid physical device
        SysMessage::box() << "[0x3016] Invalid physical device\n";
        SysMessage::box() << "Please update your graphics drivers";
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
        SysMessage::box() << "[0x3017] No device queue families found\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Get device queue families list
    bool graphicsQueueFound = false;
    uint32_t graphicsQueueIndex = 0;
    bool surfaceQueueFound = false;
    uint32_t surfaceQueueIndex = 0;
    bool fallbackTransferQueueFound = false;
    uint32_t fallbackTransferQueueIndex = 0;
    bool transferQueueFound = false;
    uint32_t transferQueueIndex = 0;
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    std::vector<VkBool32> queueSurfaceSupport(queueFamilyCount);

    vkGetPhysicalDeviceQueueFamilyProperties(
        physicalDevice, &queueFamilyCount, queueFamilies.data()
    );
    for (uint32_t i = 0; i < queueFamilyCount; ++i)
    {
        if (vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i,
            vulkanSurface, &queueSurfaceSupport[i]) != VK_SUCCESS)
        {
            // Could not get physical device surface support
            continue;
        }

        if (queueFamilies[i].queueCount > 0)
        {
            // Check if current queue supports transfer
            if (queueFamilies[i].queueFlags & VK_QUEUE_TRANSFER_BIT)
            {
                // Fallback transfer queue found
                if (!fallbackTransferQueueFound)
                {
                    fallbackTransferQueueIndex = i;
                    fallbackTransferQueueFound = true;
                }
            }

            // Check if current queue supports graphics
            if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                // Check if current queue supports present surface
                if (queueSurfaceSupport[i])
                {
                    // Current queue supports both graphics and surface
                    graphicsQueueIndex = i;
                    graphicsQueueFound = true;
                    surfaceQueueIndex = i;
                    surfaceQueueFound = true;
                }
                else
                {
                    // Current queue supports only graphics
                    if (!graphicsQueueFound)
                    {
                        graphicsQueueIndex = i;
                        graphicsQueueFound = true;
                    }
                }
            }
            else
            {
                // Check if current queue supports transfer
                if (queueFamilies[i].queueFlags & VK_QUEUE_TRANSFER_BIT)
                {
                    // Transfer queue found
                    if (!transferQueueFound)
                    {
                        transferQueueIndex = i;
                        transferQueueFound = true;
                    }
                }

                if (queueSurfaceSupport[i])
                {
                    // Current queue supports only surface
                    if (!surfaceQueueFound)
                    {
                        surfaceQueueIndex = i;
                        surfaceQueueFound = true;
                    }
                }
            }
        }
    }

    // Set fallback transfer queue
    if (!transferQueueFound && fallbackTransferQueueFound)
    {
        transferQueueIndex = fallbackTransferQueueIndex;
        transferQueueFound = true;
    }

    // Check if current device supports graphics, surface, and transfer queues
    if (!graphicsQueueFound || !surfaceQueueFound || !transferQueueFound)
    {
        SysMessage::box() << "[0x3018] Could not find a suitable device\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Current device supports graphics, surface, and transfer queues
    graphicsQueue.index = graphicsQueueIndex;
    surfaceQueue.index = surfaceQueueIndex;
    transferQueue.index = transferQueueIndex;
    return true;
}
