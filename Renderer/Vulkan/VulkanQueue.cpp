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
index(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  VulkanQueue destructor                                                    //
////////////////////////////////////////////////////////////////////////////////
VulkanQueue::~VulkanQueue()
{
    index = 0;
    family = 0;
    handle = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Create graphics queue                                                     //
//  return : True if the graphics queue is successfully created               //
////////////////////////////////////////////////////////////////////////////////
bool VulkanQueue::createGraphicsQueue()
{
    // Check Vulkan device
    if (!GVulkanDevice)
    {
        // Invalid Vulkan device
        SysMessage::box() << "[0x301F] Invalid Vulkan device\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Get graphics queue family
    family = GVulkanQueues.graphicsQueueFamily;
    index = GVulkanQueues.graphicsQueueIndex;
    if (index >= (GVulkanQueues.graphicsQueueMax-1))
    {
        // Invalid queue count
        SysMessage::box() << "[0x3020] Invalid graphics queue count\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Get queue handle
    vkGetDeviceQueue(GVulkanDevice, family, index, &handle);
    if (!handle)
    {
        // Invalid queue handle
        SysMessage::box() << "[0x3021] Invalid graphics queue handle\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Increment queue family usage
    ++GVulkanQueues.graphicsQueueIndex;
    if (GVulkanQueues.surfaceQueueFamily == family)
    {
        ++GVulkanQueues.surfaceQueueIndex;
    }
    if (GVulkanQueues.transferQueueFamily == family)
    {
        ++GVulkanQueues.transferQueueIndex;
    }

    // Graphics queue successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create surface queue                                                      //
//  return : True if the surface queue is successfully created                //
////////////////////////////////////////////////////////////////////////////////
bool VulkanQueue::createSurfaceQueue()
{
    // Check Vulkan device
    if (!GVulkanDevice)
    {
        // Invalid Vulkan device
        SysMessage::box() << "[0x3022] Invalid Vulkan device\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Get surface queue family
    family = GVulkanQueues.surfaceQueueFamily;
    index = GVulkanQueues.surfaceQueueIndex;
    if (index >= (GVulkanQueues.surfaceQueueMax-1))
    {
        // Invalid queue count
        SysMessage::box() << "[0x3023] Invalid surface queue count\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Get queue handle
    vkGetDeviceQueue(GVulkanDevice, family, index, &handle);
    if (!handle)
    {
        // Invalid queue handle
        SysMessage::box() << "[0x3024] Invalid surface queue handle\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Increment queue family usage
    ++GVulkanQueues.surfaceQueueIndex;
    if (GVulkanQueues.graphicsQueueFamily == family)
    {
        ++GVulkanQueues.graphicsQueueIndex;
    }
    if (GVulkanQueues.transferQueueFamily == family)
    {
        ++GVulkanQueues.transferQueueIndex;
    }

    // Surface queue successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create transfer queue                                                     //
//  return : True if the transfer queue is successfully created               //
////////////////////////////////////////////////////////////////////////////////
bool VulkanQueue::createTransferQueue()
{
    // Check Vulkan device
    if (!GVulkanDevice)
    {
        // Invalid Vulkan device
        SysMessage::box() << "[0x3025] Invalid Vulkan device\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Get transfer queue family
    family = GVulkanQueues.transferQueueFamily;
    index = GVulkanQueues.transferQueueIndex;
    if (index >= (GVulkanQueues.transferQueueMax-1))
    {
        // Invalid queue count
        SysMessage::box() << "[0x3026] Invalid transfer queue count\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Get queue handle
    vkGetDeviceQueue(GVulkanDevice, family, index, &handle);
    if (!handle)
    {
        // Invalid queue handle
        SysMessage::box() << "[0x3027] Invalid transfer queue handle\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Increment queue family usage
    ++GVulkanQueues.transferQueueIndex;
    if (GVulkanQueues.graphicsQueueFamily == family)
    {
        ++GVulkanQueues.graphicsQueueIndex;
    }
    if (GVulkanQueues.surfaceQueueFamily == family)
    {
        ++GVulkanQueues.surfaceQueueIndex;
    }

    // Transfer queue successfully created
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
    uint32_t graphicsQueueFamily = 0;
    uint32_t graphicsQueueMax = 0;
    bool surfaceQueueFound = false;
    uint32_t surfaceQueueFamily = 0;
    uint32_t surfaceQueueMax = 0;
    bool fallbackTransferQueueFound = false;
    uint32_t fallbackTransferQueueFamily = 0;
    uint32_t fallbackTransferQueueMax = 0;
    bool transferQueueFound = false;
    uint32_t transferQueueFamily = 0;
    uint32_t transferQueueMax = 0;
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    std::vector<VkBool32> queueSurfaceSupport(queueFamilyCount);

    vkGetPhysicalDeviceQueueFamilyProperties(
        physicalDevice, &queueFamilyCount, queueFamilies.data()
    );
    for (uint32_t i = 0; i < queueFamilyCount; ++i)
    {
        if (vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i,
            GVulkanSurface, &queueSurfaceSupport[i]) != VK_SUCCESS)
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
                    fallbackTransferQueueFamily = i;
                    fallbackTransferQueueFound = true;
                    fallbackTransferQueueMax = queueFamilies[i].queueCount;
                }
            }

            // Check if current queue supports graphics
            if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                // Check if current queue supports present surface
                if (queueSurfaceSupport[i])
                {
                    // Current queue supports both graphics and surface
                    graphicsQueueFamily = i;
                    graphicsQueueFound = true;
                    graphicsQueueMax = queueFamilies[i].queueCount;
                    surfaceQueueFamily = i;
                    surfaceQueueFound = true;
                    surfaceQueueMax = queueFamilies[i].queueCount;
                }
                else
                {
                    // Current queue supports only graphics
                    if (!graphicsQueueFound)
                    {
                        graphicsQueueFamily = i;
                        graphicsQueueFound = true;
                        graphicsQueueMax = queueFamilies[i].queueCount;
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
                        transferQueueFamily = i;
                        transferQueueFound = true;
                        transferQueueMax = queueFamilies[i].queueCount;
                    }
                }

                if (queueSurfaceSupport[i])
                {
                    // Current queue supports only surface
                    if (!surfaceQueueFound)
                    {
                        surfaceQueueFamily = i;
                        surfaceQueueFound = true;
                        surfaceQueueMax = queueFamilies[i].queueCount;
                    }
                }
            }
        }
    }

    // Set fallback transfer queue
    if (!transferQueueFound && fallbackTransferQueueFound)
    {
        transferQueueFamily = fallbackTransferQueueFamily;
        transferQueueFound = true;
        transferQueueMax = fallbackTransferQueueMax;
    }

    // Check if current device supports graphics, surface, and transfer queues
    if (!graphicsQueueFound || !surfaceQueueFound || !transferQueueFound)
    {
        SysMessage::box() << "[0x3018] Could not find a suitable device\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Current device supports graphics, surface, and transfer queues
    GVulkanQueues.graphicsQueueFamily = graphicsQueueFamily;
    GVulkanQueues.graphicsQueueIndex = 0;
    GVulkanQueues.graphicsQueueMax = graphicsQueueMax;
    GVulkanQueues.surfaceQueueFamily = surfaceQueueFamily;
    GVulkanQueues.surfaceQueueIndex = 0;
    GVulkanQueues.surfaceQueueMax = surfaceQueueMax;
    GVulkanQueues.transferQueueFamily = transferQueueFamily;
    GVulkanQueues.transferQueueIndex = 0;
    GVulkanQueues.transferQueueMax = transferQueueMax;
    return true;
}
