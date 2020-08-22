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
//     Renderer/Swapchain.cpp : Swapchain management                          //
////////////////////////////////////////////////////////////////////////////////
#include "Swapchain.h"


////////////////////////////////////////////////////////////////////////////////
//  Swapchain default constructor                                             //
////////////////////////////////////////////////////////////////////////////////
Swapchain::Swapchain() :
handle(0),
format(VK_FORMAT_UNDEFINED),
frames(0),
current(0)
{
    extent.width = 0;
    extent.height = 0;
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        images[i] = 0;
        views[i]= 0;
        framebuffers[i] = 0;
        renderReady[i] = 0;
        renderFinished[i] = 0;
        fences[i] = 0;
        commandBuffers[i] = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Swapchain destructor                                                      //
////////////////////////////////////////////////////////////////////////////////
Swapchain::~Swapchain()
{
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        commandBuffers[i] = 0;
        fences[i] = 0;
        renderFinished[i] = 0;
        renderReady[i] = 0;
        framebuffers[i] = 0;
        views[i]= 0;
        images[i] = 0;
    }
    extent.height = 0;
    extent.width = 0;
    current = 0;
    frames = 0;
    format = VK_FORMAT_UNDEFINED;
    handle = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Create swapchain                                                          //
//  return : True if swapchain is successfully created                        //
////////////////////////////////////////////////////////////////////////////////
bool Swapchain::createSwapchain(VkPhysicalDevice& physicalDevice,
    VkDevice& vulkanDevice, VkSurfaceKHR& vulkanSurface)
{
    // Check physical device
    if (!physicalDevice)
    {
        // Invalid physical device
        return false;
    }

    // Check Vulkan device
    if (!vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Check Vulkan surface
    if (!vulkanSurface)
    {
        // Invalid Vulkan surface
        return false;
    }

    // Wait for device idle
    if (vkDeviceWaitIdle(vulkanDevice) != VK_SUCCESS)
    {
        // Could not get the device ready
        return false;
    }

    // Cleanup swapchain images views
    for (uint32_t i = 0; i < frames; ++i)
    {
        if (views[i])
        {
            // Destroy image view
            vkDestroyImageView(vulkanDevice, views[i], 0);
            views[i] = 0;
        }
    }


    // Get device surface capabilities
    VkSurfaceCapabilitiesKHR surfaceCapabilities;
    if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
        physicalDevice, vulkanSurface, &surfaceCapabilities) != VK_SUCCESS)
    {
        // Could not get device surface capabilities
        return false;
    }

    // Get surface formats
    uint32_t formatsCnt = 0;
    if (vkGetPhysicalDeviceSurfaceFormatsKHR(
        physicalDevice, vulkanSurface, &formatsCnt, 0) != VK_SUCCESS)
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
    if (vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice,
        vulkanSurface, &formatsCnt, surfaceFormats.data()) != VK_SUCCESS)
    {
        // Could not get surface formats
        return false;
    }

    // Get present modes
    uint32_t presentModesCnt = 0;
    if (vkGetPhysicalDeviceSurfacePresentModesKHR(
        physicalDevice, vulkanSurface, &presentModesCnt, 0) != VK_SUCCESS)
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
    if (vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice,
        vulkanSurface, &presentModesCnt, presentModes.data()) != VK_SUCCESS)
    {
        // Could not get present modes
        return false;
    }


    // Set swapchain images count
    uint32_t imagesCount = RendererMaxSwapchainFrames;

    // Images count clamping
    if (imagesCount <= surfaceCapabilities.minImageCount)
    {
        imagesCount = surfaceCapabilities.minImageCount;
    }
    if (imagesCount >= surfaceCapabilities.maxImageCount)
    {
        imagesCount = surfaceCapabilities.maxImageCount;
    }
    if (imagesCount >= RendererMaxSwapchainFrames)
    {
        imagesCount = RendererMaxSwapchainFrames;
    }
    if (imagesCount <= 0)
    {
        // Invalid swapchain images count
        return false;
    }

    // Set swapchain surface format
    VkSurfaceFormatKHR surfaceFormat;
    surfaceFormat.format = VK_FORMAT_UNDEFINED;
    surfaceFormat.colorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
    if (surfaceFormats.size() <= 0)
    {
        // Invalid surface formats count
        return false;
    }

    // Select best surface format
    if (surfaceFormats[0].format == VK_FORMAT_UNDEFINED)
    {
        surfaceFormat.format = VK_FORMAT_R8G8B8A8_UNORM;
        surfaceFormat.colorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
    }
    else
    {
        bool formatFound = false;
        for (size_t i = 0; i < surfaceFormats.size(); ++i)
        {
            if (surfaceFormats[i].format == VK_FORMAT_R8G8B8A8_UNORM)
            {
                // Surface format found
                surfaceFormat.format = surfaceFormats[i].format;
                surfaceFormat.colorSpace = surfaceFormats[i].colorSpace;
                formatFound = true;
                break;
            }
        }
        if (!formatFound)
        {
            // Select first surface format
            surfaceFormat.format = surfaceFormats[0].format;
            surfaceFormat.colorSpace = surfaceFormats[0].colorSpace;
        }
    }

    // Set swapchain extent
    VkExtent2D swapchainExtent;
    swapchainExtent.width = surfaceCapabilities.currentExtent.width;
    swapchainExtent.height = surfaceCapabilities.currentExtent.height;

    // Clamp swapchain extent
    if (swapchainExtent.width < surfaceCapabilities.minImageExtent.width)
    {
        swapchainExtent.width = surfaceCapabilities.minImageExtent.width;
    }
    if (swapchainExtent.height < surfaceCapabilities.minImageExtent.height)
    {
        swapchainExtent.height = surfaceCapabilities.minImageExtent.height;
    }
    if (swapchainExtent.width > surfaceCapabilities.maxImageExtent.width)
    {
        swapchainExtent.width = surfaceCapabilities.maxImageExtent.width;
    }
    if (swapchainExtent.height > surfaceCapabilities.maxImageExtent.height)
    {
        swapchainExtent.height = surfaceCapabilities.maxImageExtent.height;
    }

    if ((swapchainExtent.width <= 0) || (swapchainExtent.height <= 0))
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
    VkSwapchainKHR oldSwapchain = handle;

    // Create swapchain
    VkSwapchainCreateInfoKHR swapchainInfos;
    swapchainInfos.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchainInfos.pNext = 0;
    swapchainInfos.flags = 0;
    swapchainInfos.surface = vulkanSurface;
    swapchainInfos.minImageCount = imagesCount;
    swapchainInfos.imageFormat = surfaceFormat.format;
    swapchainInfos.imageColorSpace = surfaceFormat.colorSpace;
    swapchainInfos.imageExtent = swapchainExtent;
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
        vulkanDevice, &swapchainInfos, 0, &handle) != VK_SUCCESS)
    {
        // Could not create Vulkan swapchain
        return false;
    }

    // Destroy old swapchain
    if (oldSwapchain)
    {
        vkDestroySwapchainKHR(vulkanDevice, oldSwapchain, 0);
    }

    // Set swapchain format
    format = surfaceFormat.format;

    // Get swapchain frames count
    uint32_t swapchainFramesCount = 0;
    if (vkGetSwapchainImagesKHR(
        vulkanDevice, handle, &swapchainFramesCount, 0) != VK_SUCCESS)
    {
        // Could not get swapchain frames count
        return false;
    }

    // Check swapchain frames count
    if (swapchainFramesCount <= 0)
    {
        // Invalid swapchain frames count
        return false;
    }
    if (swapchainFramesCount > RendererMaxSwapchainFrames)
    {
        // Invalid swapchain frames count
        return false;
    }

    // Get current swapchain images
    VkImage swapchainImages[RendererMaxSwapchainFrames];
    if (vkGetSwapchainImagesKHR(vulkanDevice,
        handle, &swapchainFramesCount, swapchainImages) != VK_SUCCESS)
    {
        // Could not get swapchain images count
        return false;
    }

    // Set swapchain images
    frames = swapchainFramesCount;
    for (uint32_t i = 0; i < frames; ++i)
    {
        images[i] = swapchainImages[i];
    }

    // Set swapchain extent
    extent.width = swapchainExtent.width;
    extent.height = swapchainExtent.height;

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

    for (uint32_t i = 0; i < frames; ++i)
    {
        // Create image view
        VkImageViewCreateInfo imageView;
        imageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageView.pNext = 0;
        imageView.flags = 0;
        imageView.image = images[i];
        imageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
        imageView.format = format;
        imageView.components = components;
        imageView.subresourceRange = subresource;

        if (vkCreateImageView(
            vulkanDevice, &imageView, 0, &views[i]) != VK_SUCCESS)
        {
            // Could not create swapchain image view
            return false;
        }
    }

    // Wait for device idle
    if (vkDeviceWaitIdle(vulkanDevice) != VK_SUCCESS)
    {
        // Could not get the device ready
        return false;
    }

    // Vulkan swapchain successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy swapchain                                                         //
////////////////////////////////////////////////////////////////////////////////
void Swapchain::destroySwapchain(VkDevice& vulkanDevice,
    VkCommandPool& commandsPool)
{
    if (vulkanDevice)
    {
        if (vkDeviceWaitIdle)
        {
            if (vkDeviceWaitIdle(vulkanDevice) == VK_SUCCESS)
            {
                for (uint32_t i = 0; i < frames; ++i)
                {
                    // Destroy command buffers
                    if (commandsPool && vkFreeCommandBuffers)
                    {
                        if (commandBuffers[i])
                        {
                            vkFreeCommandBuffers(vulkanDevice,
                                commandsPool, 1, &commandBuffers[i]
                            );
                        }
                    }

                    // Destroy fences
                    if (vkDestroyFence)
                    {
                        if (fences[i])
                        {
                            vkDestroyFence(vulkanDevice, fences[i], 0);
                        }
                    }

                    // Destroy semaphores
                    if (vkDestroySemaphore)
                    {
                        if (renderFinished[i])
                        {
                            vkDestroySemaphore(
                                vulkanDevice, renderFinished[i], 0
                            );
                        }
                        if (renderReady[i])
                        {
                            vkDestroySemaphore(vulkanDevice, renderReady[i], 0);
                        }
                    }

                    // Destroy framebuffers
                    if (vkDestroyFramebuffer)
                    {
                        if (framebuffers[i])
                        {
                            vkDestroyFramebuffer(
                                vulkanDevice, framebuffers[i], 0
                            );
                        }
                    }

                    // Destroy swapchain images views
                    if (vkDestroyImageView)
                    {
                        if (views[i])
                        {
                            // Destroy image view
                            vkDestroyImageView(vulkanDevice, views[i], 0);
                        }
                    }
                }

                // Destroy Vulkan swapchain
                if (handle && vkDestroySwapchainKHR)
                {
                    vkDestroySwapchainKHR(vulkanDevice, handle, 0);
                }
            }
        }
    }

    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        commandBuffers[i] = 0;
        fences[i] = 0;
        renderFinished[i] = 0;
        renderReady[i] = 0;
        framebuffers[i] = 0;
        views[i]= 0;
        images[i] = 0;
    }
    extent.height = 0;
    extent.width = 0;
    current = 0;
    frames = 0;
    format = VK_FORMAT_UNDEFINED;
    handle = 0;
}
