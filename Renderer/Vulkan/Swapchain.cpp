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
//     Renderer/Vulkan/Swapchain.cpp : Swapchain management                   //
////////////////////////////////////////////////////////////////////////////////
#include "Swapchain.h"


////////////////////////////////////////////////////////////////////////////////
//  Swapchain default constructor                                             //
////////////////////////////////////////////////////////////////////////////////
Swapchain::Swapchain() :
handle(0),
format(VK_FORMAT_UNDEFINED),
extent(),
renderPass(0),
commandsPool(0),
frames(0),
current(0),
ratio(0.0f)
{
    extent.width = 0;
    extent.height = 0;
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        images[i] = 0;
        depthImages[i] = 0;
        views[i] = 0;
        depthViews[i] = 0;
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
        depthViews[i] = 0;
        views[i]= 0;
        depthImages[i] = 0;
        images[i] = 0;
    }
    ratio = 0.0f;
    current = 0;
    frames = 0;
    commandsPool = 0;
    renderPass = 0;
    extent.height = 0;
    extent.width = 0;
    format = VK_FORMAT_UNDEFINED;
    handle = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Create swapchain                                                          //
//  return : True if swapchain is successfully created                        //
////////////////////////////////////////////////////////////////////////////////
bool Swapchain::createSwapchain(VkPhysicalDevice& physicalDevice,
    VkDevice& vulkanDevice, VkSurfaceKHR& vulkanSurface,
    uint32_t surfaceQueueFamily, VulkanMemory& vulkanMemory)
{
    // Check physical device
    if (!physicalDevice)
    {
        // Invalid physical device
        SysMessage::box() << "[0x3028] Invalid physical device\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Check Vulkan device
    if (!vulkanDevice)
    {
        // Invalid Vulkan device
        SysMessage::box() << "[0x3029] Invalid Vulkan device\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Check Vulkan surface
    if (!vulkanSurface)
    {
        // Invalid Vulkan surface
        SysMessage::box() << "[0x302A] Invalid Vulkan surface\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Check current swapchain
    if (handle)
    {
        // Destroy current swapchain
        destroySwapchain(vulkanDevice);
    }

    // Wait for device idle
    if (vkDeviceWaitIdle(vulkanDevice) != VK_SUCCESS)
    {
        // Could not get the device ready
        SysMessage::box() << "[0x302B] Could not get the device ready\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Get device surface capabilities
    VkSurfaceCapabilitiesKHR surfaceCapabilities;
    if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
        physicalDevice, vulkanSurface, &surfaceCapabilities) != VK_SUCCESS)
    {
        // Could not get device surface capabilities
        SysMessage::box() << "[0x302C] Could not get surface capabilities\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Get surface formats
    uint32_t formatsCnt = 0;
    if (vkGetPhysicalDeviceSurfaceFormatsKHR(
        physicalDevice, vulkanSurface, &formatsCnt, 0) != VK_SUCCESS)
    {
        // Could not get surface formats count
        SysMessage::box() << "[0x302D] Could not get surface formats count\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }
    if (formatsCnt <= 0)
    {
        // No surface formats found
        SysMessage::box() << "[0x302E] No surface formats found\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    std::vector<VkSurfaceFormatKHR> surfaceFormats(formatsCnt);
    if (vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice,
        vulkanSurface, &formatsCnt, surfaceFormats.data()) != VK_SUCCESS)
    {
        // Could not get surface formats
        SysMessage::box() << "[0x302F] Could not get surface formats\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Get present modes
    uint32_t presentModesCnt = 0;
    if (vkGetPhysicalDeviceSurfacePresentModesKHR(
        physicalDevice, vulkanSurface, &presentModesCnt, 0) != VK_SUCCESS)
    {
        // Could not get present modes count
        SysMessage::box() << "[0x3030] Could not get present modes count\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }
    if (presentModesCnt <= 0)
    {
        // No present modes found
        SysMessage::box() << "[0x3031] No present modes found\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }
    std::vector<VkPresentModeKHR> presentModes(presentModesCnt);
    if (vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice,
        vulkanSurface, &presentModesCnt, presentModes.data()) != VK_SUCCESS)
    {
        // Could not get present modes
        SysMessage::box() << "[0x3032] Could not get present modes\n";
        SysMessage::box() << "Please update your graphics drivers";
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
        SysMessage::box() << "[0x3033] Invalid swapchain images count\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Set swapchain surface format
    VkSurfaceFormatKHR surfaceFormat;
    surfaceFormat.format = VK_FORMAT_UNDEFINED;
    surfaceFormat.colorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
    if (surfaceFormats.size() <= 0)
    {
        // Invalid surface formats count
        SysMessage::box() << "[0x3034] Invalid surface formats count\n";
        SysMessage::box() << "Please update your graphics drivers";
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
        // Invalid swapchain extents
        SysMessage::box() << "[0x3035] Invalid swapchain extents\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Set swapchain image usage
    VkImageUsageFlags imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    if (!(surfaceCapabilities.supportedUsageFlags &
        VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT))
    {
        // Color attachment flag is not supported
        SysMessage::box() << "[0x3036] Color attachment is not supported\n";
        SysMessage::box() << "Please update your graphics drivers";
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
                SysMessage::box() << "[0x3037] No present mode supported\n";
                SysMessage::box() << "Please update your graphics drivers";
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
        SysMessage::box() << "[0x3038] Could not create Vulkan swapchain\n";
        SysMessage::box() << "Please update your graphics drivers";
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
        SysMessage::box() << "[0x3039] Could not get swapchain frames count\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Check swapchain frames count
    if (swapchainFramesCount <= 0)
    {
        // Invalid swapchain frames count
        SysMessage::box() << "[0x303A] Invalid swapchain frames count\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }
    if (swapchainFramesCount > RendererMaxSwapchainFrames)
    {
        // Invalid swapchain frames count
        SysMessage::box() << "[0x303B] Invalid swapchain frames count\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Get current swapchain images
    VkImage swapchainImages[RendererMaxSwapchainFrames];
    if (vkGetSwapchainImagesKHR(vulkanDevice,
        handle, &swapchainFramesCount, swapchainImages) != VK_SUCCESS)
    {
        // Could not get swapchain images count
        SysMessage::box() << "[0x303C] Could not get swapchain images count\n";
        SysMessage::box() << "Please update your graphics drivers";
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

    // Set swapchain aspect ratio
    ratio = 1.0f;
    if ((extent.width > 0) && (extent.height > 0))
    {
        ratio = (extent.width*1.0f) / (extent.height*1.0f);
    }

    // Create swapchain depth images
    for (uint32_t i = 0; i < frames; ++i)
    {
        // Create depth image
        VkImageCreateInfo imageInfo;
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.pNext = 0;
        imageInfo.flags = 0;
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        imageInfo.format = VK_FORMAT_D32_SFLOAT;
        imageInfo.extent.width = extent.width;
        imageInfo.extent.height = extent.height;
        imageInfo.extent.depth = 1;
        imageInfo.mipLevels = 1;
        imageInfo.arrayLayers = 1;
        imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        imageInfo.queueFamilyIndexCount = 0;
        imageInfo.pQueueFamilyIndices = 0;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

        if (vkCreateImage(vulkanDevice,
            &imageInfo, 0, &depthImages[i]) != VK_SUCCESS)
        {
            // Could not create depth image
            return false;
        }
        if (!depthImages[i])
        {
            // Invalid depth image
            return false;
        }

        // Allocate depth image memory
        if (!vulkanMemory.allocateSwapchainImage(vulkanDevice, depthImages[i]))
        {
            // Could not allocate depth image memory
            return false;
        }
    }

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
            SysMessage::box() << "[0x303D] Could not create swapchain view\n";
            SysMessage::box() << "Please update your graphics drivers";
            return false;
        }
    }

    // Create swapchain depth images views
    VkComponentMapping depthComponents;
    depthComponents.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    depthComponents.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    depthComponents.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    depthComponents.a = VK_COMPONENT_SWIZZLE_IDENTITY;

    VkImageSubresourceRange depthSubresource;
    depthSubresource.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    depthSubresource.baseMipLevel = 0;
    depthSubresource.levelCount = 1;
    depthSubresource.baseArrayLayer = 0;
    depthSubresource.layerCount = 1;

    for (uint32_t i = 0; i < frames; ++i)
    {
        // Create depth image view
        VkImageViewCreateInfo depthImageView;
        depthImageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        depthImageView.pNext = 0;
        depthImageView.flags = 0;
        depthImageView.image = depthImages[i];
        depthImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
        depthImageView.format = VK_FORMAT_D32_SFLOAT;
        depthImageView.components = depthComponents;
        depthImageView.subresourceRange = depthSubresource;

        if (vkCreateImageView(
            vulkanDevice, &depthImageView, 0, &depthViews[i]) != VK_SUCCESS)
        {
            // Could not create swapchain depth image view
            SysMessage::box() << "[0x303E] Could not create swapchain view\n";
            SysMessage::box() << "Please update your graphics drivers";
            return false;
        }
    }

    // Set color attachment
    VkAttachmentDescription attachmentDescription[2];
    attachmentDescription[0].flags = 0;
    attachmentDescription[0].format = format;
    attachmentDescription[0].samples = VK_SAMPLE_COUNT_1_BIT;
    attachmentDescription[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachmentDescription[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachmentDescription[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachmentDescription[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachmentDescription[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachmentDescription[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorAttachmentReference;
    colorAttachmentReference.attachment = 0;
    colorAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    // Set depth attachment
    attachmentDescription[1].flags = 0;
    attachmentDescription[1].format = VK_FORMAT_D32_SFLOAT;
    attachmentDescription[1].samples = VK_SAMPLE_COUNT_1_BIT;
    attachmentDescription[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachmentDescription[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachmentDescription[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachmentDescription[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachmentDescription[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachmentDescription[1].finalLayout =
        VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkAttachmentReference depthAttachmentReference;
    depthAttachmentReference.attachment = 1;
    depthAttachmentReference.layout =
        VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    // Create render pass
    VkSubpassDescription subpassDescription;
    subpassDescription.flags = 0;
    subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpassDescription.inputAttachmentCount = 0;
    subpassDescription.pInputAttachments = 0;
    subpassDescription.colorAttachmentCount = 1;
    subpassDescription.pColorAttachments = &colorAttachmentReference;
    subpassDescription.pResolveAttachments = 0;
    subpassDescription.pDepthStencilAttachment = &depthAttachmentReference;
    subpassDescription.preserveAttachmentCount = 0;
    subpassDescription.pPreserveAttachments = 0;

    VkSubpassDependency subpassDependencies[3];

    subpassDependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
    subpassDependencies[0].dstSubpass = 0;
    subpassDependencies[0].srcStageMask =
        (VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT |
        VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT);
    subpassDependencies[0].dstStageMask =
        (VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT |
        VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT);
    subpassDependencies[0].srcAccessMask =
        VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
    subpassDependencies[0].dstAccessMask =
        (VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT |
        VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT);
    subpassDependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

    subpassDependencies[1].srcSubpass = VK_SUBPASS_EXTERNAL;
    subpassDependencies[1].dstSubpass = 0;
    subpassDependencies[1].srcStageMask =
        VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
    subpassDependencies[1].dstStageMask =
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpassDependencies[1].srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
    subpassDependencies[1].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    subpassDependencies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

    subpassDependencies[2].srcSubpass = 0;
    subpassDependencies[2].dstSubpass = VK_SUBPASS_EXTERNAL;
    subpassDependencies[2].srcStageMask =
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpassDependencies[2].dstStageMask =
        VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
    subpassDependencies[2].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    subpassDependencies[2].dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
    subpassDependencies[2].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

    VkRenderPassCreateInfo renderPassInfo;
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.pNext = 0;
    renderPassInfo.flags = 0;
    renderPassInfo.attachmentCount = 2;
    renderPassInfo.pAttachments = attachmentDescription;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpassDescription;
    renderPassInfo.dependencyCount = 3;
    renderPassInfo.pDependencies = subpassDependencies;

    if (vkCreateRenderPass(
        vulkanDevice, &renderPassInfo, 0, &renderPass) != VK_SUCCESS)
    {
        // Could not create render pass
        SysMessage::box() << "[0x303F] Could not create render pass\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }
    if (!renderPass)
    {
        // Invalid render pass
        SysMessage::box() << "[0x3040] Invalid render pass\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Create framebuffers
    for (uint32_t i = 0; i < frames; ++i)
    {
        VkImageView imageViews[2];
        imageViews[0] = views[i];
        imageViews[1] = depthViews[i];

        VkFramebufferCreateInfo framebufferInfo;
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.pNext = 0;
        framebufferInfo.flags = 0;
        framebufferInfo.renderPass = renderPass;
        framebufferInfo.attachmentCount = 2;
        framebufferInfo.pAttachments = imageViews;
        framebufferInfo.width = extent.width;
        framebufferInfo.height = extent.height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(
            vulkanDevice, &framebufferInfo, 0, &framebuffers[i]) != VK_SUCCESS)
        {
            // Could not create framebuffer
            SysMessage::box() << "[0x3041] Could not create framebuffer\n";
            SysMessage::box() << "Please update your graphics drivers";
            return false;
        }
        if (!framebuffers[i])
        {
            // Invalid framebuffer
            SysMessage::box() << "[0x3042] Invalid framebuffer\n";
            SysMessage::box() << "Please update your graphics drivers";
            return false;
        }
    }

    // Create semaphores
    VkSemaphoreCreateInfo semaphoreInfo;
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    semaphoreInfo.pNext = 0;
    semaphoreInfo.flags = 0;

    for (uint32_t i = 0; i < frames; ++i)
    {
        // Create render ready semaphore
        if (vkCreateSemaphore(
            vulkanDevice, &semaphoreInfo, 0, &renderReady[i]) != VK_SUCCESS)
        {
            // Could not create render ready semaphore
            SysMessage::box() << "[0x3043] Could not create ready semaphore\n";
            SysMessage::box() << "Please update your graphics drivers";
            return false;
        }

        // Create render finished semaphore
        if (vkCreateSemaphore(
            vulkanDevice, &semaphoreInfo, 0, &renderFinished[i]) != VK_SUCCESS)
        {
            // Could not create render finished semaphore
            SysMessage::box() << "[0x3044] Could not create finish semaphore\n";
            SysMessage::box() << "Please update your graphics drivers";
            return false;
        }
    }

    // Create fences
    VkFenceCreateInfo fenceInfo;
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.pNext = 0;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (uint32_t i = 0; i < frames; ++i)
    {
        if (vkCreateFence(
            vulkanDevice, &fenceInfo, 0, &fences[i]) != VK_SUCCESS)
        {
            // Could not create fence
            SysMessage::box() << "[0x3045] Could not create fence\n";
            SysMessage::box() << "Please update your graphics drivers";
            return false;
        }
        if (!fences[i])
        {
            // Invalid fence
            SysMessage::box() << "[0x3046] Invalid fence\n";
            SysMessage::box() << "Please update your graphics drivers";
            return false;
        }
    }

    // Create commands pool
    VkCommandPoolCreateInfo commandPoolInfo;
    commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolInfo.pNext = 0;
    commandPoolInfo.flags =
        VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT |
        VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
    commandPoolInfo.queueFamilyIndex = surfaceQueueFamily;

    if (vkCreateCommandPool(
        vulkanDevice, &commandPoolInfo, 0, &commandsPool) != VK_SUCCESS)
    {
        // Could not create commands pool
        SysMessage::box() << "[0x3047] Could not create commands pool\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }
    if (!commandsPool)
    {
        // Invalid commands pool
        SysMessage::box() << "[0x3048] Invalid commands pool\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Allocate command buffers
    VkCommandBufferAllocateInfo commandBufferInfo;
    commandBufferInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    commandBufferInfo.pNext = 0;
    commandBufferInfo.commandPool = commandsPool;
    commandBufferInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    commandBufferInfo.commandBufferCount = frames;

    if (vkAllocateCommandBuffers(
        vulkanDevice, &commandBufferInfo, commandBuffers) != VK_SUCCESS)
    {
        // Could not allocate command buffers
        SysMessage::box() << "[0x3049] Could not allocate command buffers\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Wait for device idle
    if (vkDeviceWaitIdle(vulkanDevice) != VK_SUCCESS)
    {
        // Could not get the device ready
        SysMessage::box() << "[0x304A] Could not get the device ready\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Vulkan swapchain successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Resize swapchain                                                          //
//  return : True if swapchain is successfully resized                        //
////////////////////////////////////////////////////////////////////////////////
bool Swapchain::resizeSwapchain(VkPhysicalDevice& physicalDevice,
    VkDevice& vulkanDevice, VkSurfaceKHR& vulkanSurface,
    VulkanMemory& vulkanMemory)
{
    // Recreate swapchain
    if (vulkanDevice)
    {
        // Wait for device idle
        if (vkDeviceWaitIdle)
        {
            if (vkDeviceWaitIdle(vulkanDevice) == VK_SUCCESS)
            {
                for (uint32_t i = 0; i < frames; ++i)
                {
                    // Destroy fences
                    if (fences[i] && vkDestroyFence)
                    {
                        vkDestroyFence(vulkanDevice, fences[i], 0);
                    }

                    // Destroy framebuffers
                    if (framebuffers[i] && vkDestroyFramebuffer)
                    {
                        vkDestroyFramebuffer(vulkanDevice, framebuffers[i], 0);
                    }

                    // Destroy swapchain depth images views
                    if (depthViews[i] && vkDestroyImageView)
                    {
                        vkDestroyImageView(vulkanDevice, depthViews[i], 0);
                    }

                    // Destroy swapchain images views
                    if (views[i] && vkDestroyImageView)
                    {
                        vkDestroyImageView(vulkanDevice, views[i], 0);
                    }

                    // Destroy swapchain depth images
                    if (depthImages[i] && vkDestroyImage)
                    {
                        vkDestroyImage(vulkanDevice, depthImages[i], 0);
                    }
                }
            }
            else
            {
                // Could not wait for device idle
                return false;
            }
        }
    }
    for (uint32_t i = 0; i < frames; ++i)
    {
        fences[i] = 0;
        framebuffers[i] = 0;
        views[i] = 0;
    }

    // Reset swapchain memory
    vulkanMemory.resetMemory(VULKAN_MEMORY_SWAPCHAIN);

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

    // Set swapchain aspect ratio
    ratio = 1.0f;
    if ((extent.width > 0) && (extent.height > 0))
    {
        ratio = (extent.width*1.0f) / (extent.height*1.0f);
    }

    // Recreate swapchain depth images
    for (uint32_t i = 0; i < frames; ++i)
    {
        // Recreate depth image
        VkImageCreateInfo imageInfo;
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.pNext = 0;
        imageInfo.flags = 0;
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        imageInfo.format = VK_FORMAT_D32_SFLOAT;
        imageInfo.extent.width = extent.width;
        imageInfo.extent.height = extent.height;
        imageInfo.extent.depth = 1;
        imageInfo.mipLevels = 1;
        imageInfo.arrayLayers = 1;
        imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        imageInfo.queueFamilyIndexCount = 0;
        imageInfo.pQueueFamilyIndices = 0;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

        if (vkCreateImage(vulkanDevice,
            &imageInfo, 0, &depthImages[i]) != VK_SUCCESS)
        {
            // Could not create depth image
            return false;
        }
        if (!depthImages[i])
        {
            // Invalid depth image
            return false;
        }

        // Allocate depth image memory
        if (!vulkanMemory.allocateSwapchainImage(vulkanDevice, depthImages[i]))
        {
            // Could not allocate depth image memory
            return false;
        }
    }

    // Recreate swapchain images views
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
        // Recreate image view
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
            // Could not recreate swapchain image view
            return false;
        }
    }

    // Recreate swapchain depth images views
    VkComponentMapping depthComponents;
    depthComponents.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    depthComponents.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    depthComponents.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    depthComponents.a = VK_COMPONENT_SWIZZLE_IDENTITY;

    VkImageSubresourceRange depthSubresource;
    depthSubresource.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    depthSubresource.baseMipLevel = 0;
    depthSubresource.levelCount = 1;
    depthSubresource.baseArrayLayer = 0;
    depthSubresource.layerCount = 1;

    for (uint32_t i = 0; i < frames; ++i)
    {
        // Recreate depth image view
        VkImageViewCreateInfo depthImageView;
        depthImageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        depthImageView.pNext = 0;
        depthImageView.flags = 0;
        depthImageView.image = depthImages[i];
        depthImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
        depthImageView.format = VK_FORMAT_D32_SFLOAT;
        depthImageView.components = depthComponents;
        depthImageView.subresourceRange = depthSubresource;

        if (vkCreateImageView(
            vulkanDevice, &depthImageView, 0, &depthViews[i]) != VK_SUCCESS)
        {
            // Could not recreate swapchain depth image view
            return false;
        }
    }

    // Recreate framebuffers
    for (uint32_t i = 0; i < frames; ++i)
    {
        VkImageView imageViews[2];
        imageViews[0] = views[i];
        imageViews[1] = depthViews[i];

        VkFramebufferCreateInfo framebufferInfo;
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.pNext = 0;
        framebufferInfo.flags = 0;
        framebufferInfo.renderPass = renderPass;
        framebufferInfo.attachmentCount = 2;
        framebufferInfo.pAttachments = imageViews;
        framebufferInfo.width = extent.width;
        framebufferInfo.height = extent.height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(
            vulkanDevice, &framebufferInfo, 0, &framebuffers[i]) != VK_SUCCESS)
        {
            // Could not recreate framebuffer
            return false;
        }
        if (!framebuffers[i])
        {
            // Invalid framebuffer
            return false;
        }
    }

    // Recreate fences
    VkFenceCreateInfo fenceInfo;
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.pNext = 0;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (uint32_t i = 0; i < frames; ++i)
    {
        if (vkCreateFence(
            vulkanDevice, &fenceInfo, 0, &fences[i]) != VK_SUCCESS)
        {
            // Could not recreate fence
            return false;
        }
        if (!fences[i])
        {
            // Invalid fence
            return false;
        }
    }

    // Reset swapchain current frame index
    current = 0;

    // Swapchain successfully resized
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy swapchain                                                         //
////////////////////////////////////////////////////////////////////////////////
void Swapchain::destroySwapchain(VkDevice& vulkanDevice)
{
    if (vulkanDevice)
    {
        if (vkDeviceWaitIdle)
        {
            if (vkDeviceWaitIdle(vulkanDevice) == VK_SUCCESS)
            {
                // Destroy render pass
                if (renderPass && vkDestroyRenderPass)
                {
                    vkDestroyRenderPass(vulkanDevice, renderPass, 0);
                }

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
                    if (fences[i] && vkDestroyFence)
                    {
                        vkDestroyFence(vulkanDevice, fences[i], 0);
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
                    if (framebuffers[i] && vkDestroyFramebuffer)
                    {
                        vkDestroyFramebuffer(
                            vulkanDevice, framebuffers[i], 0
                        );
                    }

                    // Destroy swapchain depth images views
                    if (depthViews[i] && vkDestroyImageView)
                    {
                        // Destroy image view
                        vkDestroyImageView(vulkanDevice, depthViews[i], 0);
                    }

                    // Destroy swapchain images views
                    if (views[i] && vkDestroyImageView)
                    {
                        // Destroy image view
                        vkDestroyImageView(vulkanDevice, views[i], 0);
                    }

                    // Destroy swapchain depth images
                    if (depthImages[i] && vkDestroyImage)
                    {
                        vkDestroyImage(vulkanDevice, depthImages[i], 0);
                    }
                }

                // Destroy commands pool
                if (commandsPool && vkDestroyCommandPool)
                {
                    vkDestroyCommandPool(vulkanDevice, commandsPool, 0);
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
    ratio = 0.0f;
    current = 0;
    frames = 0;
    commandsPool = 0;
    renderPass = 0;
    extent.height = 0;
    extent.width = 0;
    format = VK_FORMAT_UNDEFINED;
    handle = 0;
}
