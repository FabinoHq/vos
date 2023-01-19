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
//  Swapchain global instance                                                 //
////////////////////////////////////////////////////////////////////////////////
Swapchain GSwapchain = Swapchain();


////////////////////////////////////////////////////////////////////////////////
//  Swapchain default constructor                                             //
////////////////////////////////////////////////////////////////////////////////
Swapchain::Swapchain() :
handle(0),
format(VK_FORMAT_UNDEFINED),
extent(),
renderPass(0),
frames(0),
current(0),
ratio(0.0f)
{
    extent.width = 0;
    extent.height = 0;
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        images[i] = 0;
        views[i] = 0;
        framebuffers[i] = 0;
        renderReady[i] = 0;
        renderDone[i] = 0;
        fences[i] = 0;
        commandPools[i] = 0;
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
        commandPools[i] = 0;
        fences[i] = 0;
        renderDone[i] = 0;
        renderReady[i] = 0;
        framebuffers[i] = 0;
        views[i] = 0;
        images[i] = 0;
    }
    ratio = 0.0f;
    current = 0;
    frames = 0;
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
bool Swapchain::createSwapchain()
{
    // Check physical device
    if (!GPhysicalDevice)
    {
        // Invalid physical device
        SysMessage::box() << "[0x3028] Invalid physical device\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Check device
    if (!GVulkanDevice)
    {
        // Invalid device
        SysMessage::box() << "[0x3029] Invalid device\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Check surface
    if (!GVulkanSurface)
    {
        // Invalid surface
        SysMessage::box() << "[0x302A] Invalid surface\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Check current swapchain
    if (handle)
    {
        // Destroy current swapchain
        destroySwapchain();
    }

    // Wait for device idle
    if (vkDeviceWaitIdle(GVulkanDevice) != VK_SUCCESS)
    {
        // Could not get the device ready
        SysMessage::box() << "[0x302B] Could not get the device ready\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Request swapchain queue handle
    if (!swapchainQueue.getVulkanQueue(VULKAN_QUEUE_SWAPCHAIN))
    {
        // Could not get swapchain queue handle
        return false;
    }

    // Get device surface capabilities
    VkSurfaceCapabilitiesKHR surfaceCapabilities;
    if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
        GPhysicalDevice, GVulkanSurface, &surfaceCapabilities) != VK_SUCCESS)
    {
        // Could not get device surface capabilities
        SysMessage::box() << "[0x302C] Could not get surface capabilities\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Get surface formats
    uint32_t formatsCnt = 0;
    if (vkGetPhysicalDeviceSurfaceFormatsKHR(
        GPhysicalDevice, GVulkanSurface, &formatsCnt, 0) != VK_SUCCESS)
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
    if (vkGetPhysicalDeviceSurfaceFormatsKHR(GPhysicalDevice,
        GVulkanSurface, &formatsCnt, surfaceFormats.data()) != VK_SUCCESS)
    {
        // Could not get surface formats
        SysMessage::box() << "[0x302F] Could not get surface formats\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Get present modes
    uint32_t presentModesCnt = 0;
    if (vkGetPhysicalDeviceSurfacePresentModesKHR(
        GPhysicalDevice, GVulkanSurface, &presentModesCnt, 0) != VK_SUCCESS)
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
    if (vkGetPhysicalDeviceSurfacePresentModesKHR(GPhysicalDevice,
        GVulkanSurface, &presentModesCnt, presentModes.data()) != VK_SUCCESS)
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
    swapchainInfos.surface = GVulkanSurface;
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

    if (vkCreateSwapchainKHR(GVulkanDevice,
        &swapchainInfos, 0, &handle) != VK_SUCCESS)
    {
        // Could not create swapchain
        SysMessage::box() << "[0x3038] Could not create swapchain\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Destroy old swapchain
    if (oldSwapchain)
    {
        vkDestroySwapchainKHR(GVulkanDevice, oldSwapchain, 0);
    }
    oldSwapchain = 0;

    // Set swapchain format
    format = surfaceFormat.format;

    // Get swapchain frames count
    uint32_t swapchainFramesCount = 0;
    if (vkGetSwapchainImagesKHR(GVulkanDevice,
        handle, &swapchainFramesCount, 0) != VK_SUCCESS)
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
    if (vkGetSwapchainImagesKHR(GVulkanDevice,
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

    // Create image views
    VkImageSubresourceRange subresource;
    subresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    subresource.baseMipLevel = 0;
    subresource.levelCount = 1;
    subresource.baseArrayLayer = 0;
    subresource.layerCount = 1;
    
    VkImageViewCreateInfo imageView;
    imageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageView.pNext = 0;
    imageView.flags = 0;
    imageView.image = 0;
    imageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
    imageView.format = format;
    imageView.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageView.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageView.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageView.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageView.subresourceRange = subresource;

    for (uint32_t i = 0; i < frames; ++i)
    {
        // Create image view
        imageView.image = images[i];

        if (vkCreateImageView(GVulkanDevice,
            &imageView, 0, &views[i]) != VK_SUCCESS)
        {
            // Could not create image view
            SysMessage::box() << "[0x303D] Could not create image view\n";
            SysMessage::box() << "Please update your graphics drivers";
            return false;
        }
        if (!images[i])
        {
            // Invalid image view
            SysMessage::box() << "[0x303E] Invalid image view\n";
            SysMessage::box() << "Please update your graphics drivers";
            return false;
        }
    }

    // Set color attachment
    VkAttachmentDescription attachmentDescription[1];
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

    // Render subpass
    VkSubpassDescription subpassDescription;
    subpassDescription.flags = 0;
    subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpassDescription.inputAttachmentCount = 0;
    subpassDescription.pInputAttachments = 0;
    subpassDescription.colorAttachmentCount = 1;
    subpassDescription.pColorAttachments = &colorAttachmentReference;
    subpassDescription.pResolveAttachments = 0;
    subpassDescription.pDepthStencilAttachment = 0;
    subpassDescription.preserveAttachmentCount = 0;
    subpassDescription.pPreserveAttachments = 0;

    VkSubpassDependency subpassDependencies[2];

    // Color dependencies
    subpassDependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
    subpassDependencies[0].dstSubpass = 0;
    subpassDependencies[0].srcStageMask =
        VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
    subpassDependencies[0].dstStageMask =
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpassDependencies[0].srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
    subpassDependencies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    subpassDependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

    subpassDependencies[1].srcSubpass = 0;
    subpassDependencies[1].dstSubpass = VK_SUBPASS_EXTERNAL;
    subpassDependencies[1].srcStageMask =
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpassDependencies[1].dstStageMask =
        VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
    subpassDependencies[1].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    subpassDependencies[1].dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
    subpassDependencies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

    // Create render pass
    VkRenderPassCreateInfo renderPassInfo;
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.pNext = 0;
    renderPassInfo.flags = 0;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = attachmentDescription;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpassDescription;
    renderPassInfo.dependencyCount = 2;
    renderPassInfo.pDependencies = subpassDependencies;

    if (vkCreateRenderPass(GVulkanDevice,
        &renderPassInfo, 0, &renderPass) != VK_SUCCESS)
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
    VkImageView imageViews[1];
    imageViews[0] = 0;

    VkFramebufferCreateInfo framebufferInfo;
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.pNext = 0;
    framebufferInfo.flags = 0;
    framebufferInfo.renderPass = renderPass;
    framebufferInfo.attachmentCount = 1;
    framebufferInfo.pAttachments = 0;
    framebufferInfo.width = extent.width;
    framebufferInfo.height = extent.height;
    framebufferInfo.layers = 1;

    for (uint32_t i = 0; i < frames; ++i)
    {
        // Create framebuffer
        imageViews[0] = views[i];
        framebufferInfo.pAttachments = imageViews;

        if (vkCreateFramebuffer(GVulkanDevice,
            &framebufferInfo, 0, &framebuffers[i]) != VK_SUCCESS)
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
        if (vkCreateSemaphore(GVulkanDevice,
            &semaphoreInfo, 0, &renderReady[i]) != VK_SUCCESS)
        {
            // Could not create render ready semaphore
            SysMessage::box() << "[0x3043] Could not create ready semaphore\n";
            SysMessage::box() << "Please update your graphics drivers";
            return false;
        }

        // Create render finished semaphore
        if (vkCreateSemaphore(GVulkanDevice,
            &semaphoreInfo, 0, &renderDone[i]) != VK_SUCCESS)
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
        // Create fence
        if (vkCreateFence(GVulkanDevice,
            &fenceInfo, 0, &fences[i]) != VK_SUCCESS)
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

    // Create commands pools
    VkCommandPoolCreateInfo commandPoolInfo;
    commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolInfo.pNext = 0;
    commandPoolInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
    commandPoolInfo.queueFamilyIndex = swapchainQueue.family;

    for (uint32_t i = 0; i < frames; ++i)
    {
        // Create command pool
        if (vkCreateCommandPool(GVulkanDevice,
            &commandPoolInfo, 0, &commandPools[i]) != VK_SUCCESS)
        {
            // Could not create commands pool
            SysMessage::box() << "[0x3047] Could not create commands pool\n";
            SysMessage::box() << "Please update your graphics drivers";
            return false;
        }
        if (!commandPools[i])
        {
            // Invalid commands pool
            SysMessage::box() << "[0x3048] Invalid commands pool\n";
            SysMessage::box() << "Please update your graphics drivers";
            return false;
        }
    }

    // Allocate command buffers
    VkCommandBufferAllocateInfo commandBufferInfo;
    commandBufferInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    commandBufferInfo.pNext = 0;
    commandBufferInfo.commandPool = 0;
    commandBufferInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    commandBufferInfo.commandBufferCount = 1;

    for (uint32_t i = 0; i < frames; ++i)
    {
        // Allocate command buffer
        commandBufferInfo.commandPool = commandPools[i];

        if (vkAllocateCommandBuffers(GVulkanDevice,
            &commandBufferInfo, &commandBuffers[i]) != VK_SUCCESS)
        {
            // Could not allocate command buffers
            SysMessage::box() << "[0x3049] Could not allocate command buffer\n";
            SysMessage::box() << "Please update your graphics drivers";
            return false;
        }
        if (!commandBuffers[i])
        {
            // Invalid commands buffer
            SysMessage::box() << "[0x304A] Invalid commands buffer\n";
            SysMessage::box() << "Please update your graphics drivers";
            return false;
        }
    }

    // Wait for device idle
    if (vkDeviceWaitIdle(GVulkanDevice) != VK_SUCCESS)
    {
        // Could not get the device ready
        SysMessage::box() << "[0x304B] Could not get the device ready\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Swapchain successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Resize swapchain                                                          //
//  return : True if swapchain is successfully resized                        //
////////////////////////////////////////////////////////////////////////////////
bool Swapchain::resizeSwapchain()
{
    // Destroy current swapchain
    for (uint32_t i = 0; i < frames; ++i)
    {
        // Destroy fences
        if (fences[i])
        {
            vkDestroyFence(GVulkanDevice, fences[i], 0);
        }
        fences[i] = 0;

        // Destroy framebuffers
        if (framebuffers[i])
        {
            vkDestroyFramebuffer(GVulkanDevice, framebuffers[i], 0);
        }
        framebuffers[i] = 0;

        // Destroy swapchain images views
        if (views[i])
        {
            vkDestroyImageView(GVulkanDevice, views[i], 0);
        }
        views[i] = 0;
    }

    // Get device surface capabilities
    VkSurfaceCapabilitiesKHR surfaceCapabilities;
    if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
        GPhysicalDevice, GVulkanSurface, &surfaceCapabilities) != VK_SUCCESS)
    {
        // Could not get device surface capabilities
        return false;
    }

    // Get surface formats
    uint32_t formatsCnt = 0;
    if (vkGetPhysicalDeviceSurfaceFormatsKHR(
        GPhysicalDevice, GVulkanSurface, &formatsCnt, 0) != VK_SUCCESS)
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
    if (vkGetPhysicalDeviceSurfaceFormatsKHR(GPhysicalDevice,
        GVulkanSurface, &formatsCnt, surfaceFormats.data()) != VK_SUCCESS)
    {
        // Could not get surface formats
        return false;
    }

    // Get present modes
    uint32_t presentModesCnt = 0;
    if (vkGetPhysicalDeviceSurfacePresentModesKHR(
        GPhysicalDevice, GVulkanSurface, &presentModesCnt, 0) != VK_SUCCESS)
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
    if (vkGetPhysicalDeviceSurfacePresentModesKHR(GPhysicalDevice,
        GVulkanSurface, &presentModesCnt, presentModes.data()) != VK_SUCCESS)
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
    swapchainInfos.surface = GVulkanSurface;
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

    if (vkCreateSwapchainKHR(GVulkanDevice,
        &swapchainInfos, 0, &handle) != VK_SUCCESS)
    {
        // Could not create swapchain
        return false;
    }

    // Destroy old swapchain
    if (oldSwapchain)
    {
        vkDestroySwapchainKHR(GVulkanDevice, oldSwapchain, 0);
    }

    // Set swapchain format
    format = surfaceFormat.format;

    // Get swapchain frames count
    uint32_t swapchainFramesCount = 0;
    if (vkGetSwapchainImagesKHR(GVulkanDevice,
        handle, &swapchainFramesCount, 0) != VK_SUCCESS)
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
    if (vkGetSwapchainImagesKHR(GVulkanDevice,
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

    // Recreate swapchain images views
    VkImageSubresourceRange subresource;
    subresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    subresource.baseMipLevel = 0;
    subresource.levelCount = 1;
    subresource.baseArrayLayer = 0;
    subresource.layerCount = 1;

    // Recreate image views
    VkImageViewCreateInfo imageView;
    imageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageView.pNext = 0;
    imageView.flags = 0;
    imageView.image = 0;
    imageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
    imageView.format = format;
    imageView.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageView.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageView.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageView.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageView.subresourceRange = subresource;

    for (uint32_t i = 0; i < frames; ++i)
    {
        // Recreate image view
        imageView.image = images[i];

        if (vkCreateImageView(GVulkanDevice,
            &imageView, 0, &views[i]) != VK_SUCCESS)
        {
            // Could not recreate swapchain image view
            return false;
        }
        if (!views[i])
        {
            // Invalid image view
            return false;
        }
    }

    // Recreate framebuffers
    VkImageView imageViews[1];
    imageViews[0] = 0;

    VkFramebufferCreateInfo framebufferInfo;
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.pNext = 0;
    framebufferInfo.flags = 0;
    framebufferInfo.renderPass = renderPass;
    framebufferInfo.attachmentCount = 1;
    framebufferInfo.pAttachments = 0;
    framebufferInfo.width = extent.width;
    framebufferInfo.height = extent.height;
    framebufferInfo.layers = 1;

    for (uint32_t i = 0; i < frames; ++i)
    {
        // Recreate framebuffer
        imageViews[0] = views[i];
        framebufferInfo.pAttachments = imageViews;

        if (vkCreateFramebuffer(GVulkanDevice,
            &framebufferInfo, 0, &framebuffers[i]) != VK_SUCCESS)
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
        // Recreate fence
        if (vkCreateFence(GVulkanDevice,
            &fenceInfo, 0, &fences[i]) != VK_SUCCESS)
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
void Swapchain::destroySwapchain()
{
    // Check Vulkan device
    if (!GVulkanDevice)
    {
        // Invalid Vulkan device
        return;
    }

    // Destroy render pass
    if (renderPass)
    {
        vkDestroyRenderPass(GVulkanDevice, renderPass, 0);
    }
    renderPass = 0;

    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        if (commandPools[i])
        {
            // Destroy command buffer
            if (commandBuffers[i])
            {
                vkFreeCommandBuffers(
                    GVulkanDevice, commandPools[i], 1, &commandBuffers[i]
                );
            }

            // Destroy commands pool
            vkDestroyCommandPool(GVulkanDevice, commandPools[i], 0);
        }
        commandBuffers[i] = 0;
        commandPools[i] = 0;

        // Destroy fences
        if (fences[i])
        {
            vkDestroyFence(GVulkanDevice, fences[i], 0);
        }
        fences[i] = 0;

        // Destroy semaphores
        if (renderDone[i])
        {
            vkDestroySemaphore(GVulkanDevice, renderDone[i], 0);
        }
        renderDone[i] = 0;

        if (renderReady[i])
        {
            vkDestroySemaphore(GVulkanDevice, renderReady[i], 0);
        }
        renderReady[i] = 0;

        // Destroy framebuffers
        if (framebuffers[i])
        {
            vkDestroyFramebuffer(GVulkanDevice, framebuffers[i], 0);
        }
        framebuffers[i] = 0;

        // Destroy swapchain images views
        if (views[i])
        {
            vkDestroyImageView(GVulkanDevice, views[i], 0);
        }
        views[i]= 0;
        images[i] = 0;
    }

    // Destroy swapchain
    if (handle)
    {
        vkDestroySwapchainKHR(GVulkanDevice, handle, 0);
    }
    handle = 0;

    ratio = 0.0f;
    current = 0;
    frames = 0;
    extent.height = 0;
    extent.width = 0;
    format = VK_FORMAT_UNDEFINED;
}
