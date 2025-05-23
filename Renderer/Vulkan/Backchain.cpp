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
//     Renderer/Vulkan/Backchain.cpp : Backchain management                   //
////////////////////////////////////////////////////////////////////////////////
#include "Backchain.h"


////////////////////////////////////////////////////////////////////////////////
//  Backchain default constructor                                             //
////////////////////////////////////////////////////////////////////////////////
Backchain::Backchain() :
extent(),
renderPass(0),
ratio(0.0f)
{
    extent.width = 0;
    extent.height = 0;
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        msaaImages[i] = 0;
        images[i] = 0;
        depthImages[i] = 0;
        msaaViews[i] = 0;
        views[i] = 0;
        depthViews[i] = 0;
        framebuffers[i] = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Backchain destructor                                                      //
////////////////////////////////////////////////////////////////////////////////
Backchain::~Backchain()
{
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        framebuffers[i] = 0;
        depthViews[i] = 0;
        views[i] = 0;
        msaaViews[i] = 0;
        depthImages[i] = 0;
        images[i] = 0;
        msaaImages[i] = 0;
    }
    ratio = 0.0f;
    renderPass = 0;
    extent.height = 0;
    extent.width = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Create backchain                                                          //
//  return : True if backchain is successfully created                        //
////////////////////////////////////////////////////////////////////////////////
bool Backchain::createBackchain(VulkanMemoryPool memoryPool,
    uint32_t width, uint32_t height)
{
    // Check backchain size
    if ((width <= 0) || (height <= 0))
    {
        // Invalid backchain size
        return false;
    }

    // Get multisample configuration
    MultiSamplingMode multiSamplingMode = GSysSettings.getMultiSamplingMode();

    // Create backchain msaa images
    if (multiSamplingMode > MULTI_SAMPLING_NONE)
    {
        for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
        {
            VkImageCreateInfo imageInfo;
            imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
            imageInfo.pNext = 0;
            imageInfo.flags = 0;
            imageInfo.imageType = VK_IMAGE_TYPE_2D;
            imageInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
            imageInfo.extent.width = width;
            imageInfo.extent.height = height;
            imageInfo.extent.depth = 1;
            imageInfo.mipLevels = 1;
            imageInfo.arrayLayers = 1;
            imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
            imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
            imageInfo.usage = (VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
                VK_IMAGE_USAGE_SAMPLED_BIT);
            imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
            imageInfo.queueFamilyIndexCount = 0;
            imageInfo.pQueueFamilyIndices = 0;
            imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

            if (vkCreateImage(GVulkanDevice, &imageInfo,
                SYSVKMEMORY_IMAGE_ALLOC, &msaaImages[i]) != VK_SUCCESS)
            {
                // Could not create image
                return false;
            }
            if (!msaaImages[i])
            {
                // Invalid image
                return false;
            }

            // Allocate image memory
            if (!GVulkanMemory.allocateBackchainImage(
                msaaImages[i], memoryPool))
            {
                // Could not allocate image memory
                return false;
            }
        }
    }

    // Create backchain images
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        VkImageCreateInfo imageInfo;
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.pNext = 0;
        imageInfo.flags = 0;
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        imageInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
        imageInfo.extent.width = width;
        imageInfo.extent.height = height;
        imageInfo.extent.depth = 1;
        imageInfo.mipLevels = 1;
        imageInfo.arrayLayers = 1;
        imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        switch (multiSamplingMode)
        {
            case MULTI_SAMPLING_2X:
                imageInfo.samples = VK_SAMPLE_COUNT_2_BIT;
                break;
            case MULTI_SAMPLING_4X:
                imageInfo.samples = VK_SAMPLE_COUNT_4_BIT;
                break;
            case MULTI_SAMPLING_8X:
                imageInfo.samples = VK_SAMPLE_COUNT_8_BIT;
                break;
            default:
                imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
                break;
        }
        imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        imageInfo.usage =
            (VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT);
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        imageInfo.queueFamilyIndexCount = 0;
        imageInfo.pQueueFamilyIndices = 0;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

        if (vkCreateImage(GVulkanDevice, &imageInfo,
            SYSVKMEMORY_IMAGE_ALLOC, &images[i]) != VK_SUCCESS)
        {
            // Could not create image
            return false;
        }
        if (!images[i])
        {
            // Invalid image
            return false;
        }

        // Allocate image memory
        if (!GVulkanMemory.allocateBackchainImage(images[i], memoryPool))
        {
            // Could not allocate image memory
            return false;
        }
    }

    // Create backchain depth images
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        // Create depth image
        VkImageCreateInfo imageInfo;
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.pNext = 0;
        imageInfo.flags = 0;
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        imageInfo.format = VK_FORMAT_D32_SFLOAT;
        imageInfo.extent.width = width;
        imageInfo.extent.height = height;
        imageInfo.extent.depth = 1;
        imageInfo.mipLevels = 1;
        imageInfo.arrayLayers = 1;
        imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        switch (multiSamplingMode)
        {
            case MULTI_SAMPLING_2X:
                imageInfo.samples = VK_SAMPLE_COUNT_2_BIT;
                break;
            case MULTI_SAMPLING_4X:
                imageInfo.samples = VK_SAMPLE_COUNT_4_BIT;
                break;
            case MULTI_SAMPLING_8X:
                imageInfo.samples = VK_SAMPLE_COUNT_8_BIT;
                break;
            default:
                imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
                break;
        }
        imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        imageInfo.queueFamilyIndexCount = 0;
        imageInfo.pQueueFamilyIndices = 0;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

        if (vkCreateImage(GVulkanDevice, &imageInfo,
            SYSVKMEMORY_IMAGE_ALLOC, &depthImages[i]) != VK_SUCCESS)
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
        if (!GVulkanMemory.allocateBackchainImage(depthImages[i], memoryPool))
        {
            // Could not allocate depth image memory
            return false;
        }
    }

    // Create backchain msaa images views
    if (multiSamplingMode > MULTI_SAMPLING_NONE)
    {
        VkImageSubresourceRange msaaSubresource;
        msaaSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        msaaSubresource.baseMipLevel = 0;
        msaaSubresource.levelCount = 1;
        msaaSubresource.baseArrayLayer = 0;
        msaaSubresource.layerCount = 1;

        for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
        {
            // Create image view
            VkImageViewCreateInfo imageView;
            imageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            imageView.pNext = 0;
            imageView.flags = 0;
            imageView.image = msaaImages[i];
            imageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
            imageView.format = VK_FORMAT_R8G8B8A8_UNORM;
            imageView.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            imageView.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            imageView.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            imageView.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            imageView.subresourceRange = msaaSubresource;

            if (vkCreateImageView(GVulkanDevice, &imageView,
                SYSVKMEMORY_IMAGEVIEW_ALLOC, &msaaViews[i]) != VK_SUCCESS)
            {
                // Could not create msaa image view
                return false;
            }
            if (!msaaViews[i])
            {
                // Invalid msaa image view
                return false;
            }
        }
    }

    // Create backchain images views
    VkImageSubresourceRange subresource;
    subresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    subresource.baseMipLevel = 0;
    subresource.levelCount = 1;
    subresource.baseArrayLayer = 0;
    subresource.layerCount = 1;

    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        // Create image view
        VkImageViewCreateInfo imageView;
        imageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageView.pNext = 0;
        imageView.flags = 0;
        imageView.image = images[i];
        imageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
        imageView.format = VK_FORMAT_R8G8B8A8_UNORM;
        imageView.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageView.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageView.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageView.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageView.subresourceRange = subresource;

        if (vkCreateImageView(GVulkanDevice, &imageView,
            SYSVKMEMORY_IMAGEVIEW_ALLOC, &views[i]) != VK_SUCCESS)
        {
            // Could not create image view
            return false;
        }
        if (!views[i])
        {
            // Invalid image view
            return false;
        }
    }

    // Create backchain depth images views
    VkImageSubresourceRange depthSubresource;
    depthSubresource.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    depthSubresource.baseMipLevel = 0;
    depthSubresource.levelCount = 1;
    depthSubresource.baseArrayLayer = 0;
    depthSubresource.layerCount = 1;

    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        // Create depth image view
        VkImageViewCreateInfo depthImageView;
        depthImageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        depthImageView.pNext = 0;
        depthImageView.flags = 0;
        depthImageView.image = depthImages[i];
        depthImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
        depthImageView.format = VK_FORMAT_D32_SFLOAT;
        depthImageView.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        depthImageView.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        depthImageView.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        depthImageView.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        depthImageView.subresourceRange = depthSubresource;

        if (vkCreateImageView(GVulkanDevice, &depthImageView,
            SYSVKMEMORY_IMAGEVIEW_ALLOC, &depthViews[i]) != VK_SUCCESS)
        {
            // Could not create depth image view
            return false;
        }
        if (!depthViews[i])
        {
            // Invalid depth image view
            return false;
        }
    }

    // Set color attachment
    VkAttachmentDescription attachmentDescription[3];
    attachmentDescription[0].flags = 0;
    attachmentDescription[0].format = VK_FORMAT_R8G8B8A8_UNORM;
    attachmentDescription[0].samples = VK_SAMPLE_COUNT_1_BIT;
    switch (multiSamplingMode)
    {
        case MULTI_SAMPLING_2X:
            attachmentDescription[0].samples = VK_SAMPLE_COUNT_2_BIT;
            break;
        case MULTI_SAMPLING_4X:
            attachmentDescription[0].samples = VK_SAMPLE_COUNT_4_BIT;
            break;
        case MULTI_SAMPLING_8X:
            attachmentDescription[0].samples = VK_SAMPLE_COUNT_8_BIT;
            break;
        default:
            attachmentDescription[0].samples = VK_SAMPLE_COUNT_1_BIT;
            break;
    }
    attachmentDescription[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachmentDescription[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    if (multiSamplingMode > MULTI_SAMPLING_NONE)
    {
        attachmentDescription[0].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    }
    attachmentDescription[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachmentDescription[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachmentDescription[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachmentDescription[0].finalLayout =
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    if (multiSamplingMode > MULTI_SAMPLING_NONE)
    {
        attachmentDescription[0].finalLayout =
            VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    }

    VkAttachmentReference colorAttachmentReference;
    colorAttachmentReference.attachment = 0;
    colorAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    // Set depth attachment
    attachmentDescription[1].flags = 0;
    attachmentDescription[1].format = VK_FORMAT_D32_SFLOAT;
    attachmentDescription[1].samples = VK_SAMPLE_COUNT_1_BIT;
    switch (multiSamplingMode)
    {
        case MULTI_SAMPLING_2X:
            attachmentDescription[1].samples = VK_SAMPLE_COUNT_2_BIT;
            break;
        case MULTI_SAMPLING_4X:
            attachmentDescription[1].samples = VK_SAMPLE_COUNT_4_BIT;
            break;
        case MULTI_SAMPLING_8X:
            attachmentDescription[1].samples = VK_SAMPLE_COUNT_8_BIT;
            break;
        default:
            attachmentDescription[1].samples = VK_SAMPLE_COUNT_1_BIT;
            break;
    }
    attachmentDescription[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachmentDescription[1].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachmentDescription[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachmentDescription[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachmentDescription[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachmentDescription[1].finalLayout =
        VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkAttachmentReference depthAttachmentReference;
    depthAttachmentReference.attachment = 1;
    depthAttachmentReference.layout =
        VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    // Set resolve attachment (msaa)
    attachmentDescription[2].flags = 0;
    attachmentDescription[2].format = VK_FORMAT_R8G8B8A8_UNORM;
    attachmentDescription[2].samples = VK_SAMPLE_COUNT_1_BIT;
    attachmentDescription[2].loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachmentDescription[2].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachmentDescription[2].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachmentDescription[2].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachmentDescription[2].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachmentDescription[2].finalLayout =
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    VkAttachmentReference resolveAttachmentReference;
    resolveAttachmentReference.attachment = 2;
    resolveAttachmentReference.layout =
        VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    // Render subpass
    VkSubpassDescription subpassDescription;
    subpassDescription.flags = 0;
    subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpassDescription.inputAttachmentCount = 0;
    subpassDescription.pInputAttachments = 0;
    subpassDescription.colorAttachmentCount = 1;
    subpassDescription.pColorAttachments = &colorAttachmentReference;
    subpassDescription.pResolveAttachments = 0;
    if (multiSamplingMode > MULTI_SAMPLING_NONE)
    {
        subpassDescription.pResolveAttachments = &resolveAttachmentReference;
    }
    subpassDescription.pDepthStencilAttachment = &depthAttachmentReference;
    subpassDescription.preserveAttachmentCount = 0;
    subpassDescription.pPreserveAttachments = 0;

    VkSubpassDependency subpassDependencies[3];

    // Depth dependency
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

    // Color dependencies
    subpassDependencies[1].srcSubpass = VK_SUBPASS_EXTERNAL;
    subpassDependencies[1].dstSubpass = 0;
    subpassDependencies[1].srcStageMask =
        VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    subpassDependencies[1].dstStageMask =
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpassDependencies[1].srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
    subpassDependencies[1].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    subpassDependencies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

    subpassDependencies[2].srcSubpass = 0;
    subpassDependencies[2].dstSubpass = VK_SUBPASS_EXTERNAL;
    subpassDependencies[2].srcStageMask =
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpassDependencies[2].dstStageMask =
        VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    subpassDependencies[2].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    subpassDependencies[2].dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    subpassDependencies[2].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

    // Create render pass
    VkRenderPassCreateInfo renderPassInfo;
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.pNext = 0;
    renderPassInfo.flags = 0;
    renderPassInfo.attachmentCount = 2;
    if (multiSamplingMode > MULTI_SAMPLING_NONE)
    {
        renderPassInfo.attachmentCount = 3;
    }
    renderPassInfo.pAttachments = attachmentDescription;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpassDescription;
    renderPassInfo.dependencyCount = 3;
    renderPassInfo.pDependencies = subpassDependencies;

    if (vkCreateRenderPass(GVulkanDevice, &renderPassInfo,
        SYSVKMEMORY_RENDERPASS_ALLOC, &renderPass) != VK_SUCCESS)
    {
        // Could not create render pass
        return false;
    }
    if (!renderPass)
    {
        // Invalid render pass
        return false;
    }

    // Create framebuffers
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        VkImageView imageViews[3];
        imageViews[0] = views[i];
        imageViews[1] = depthViews[i];
        imageViews[2] = msaaViews[i];

        VkFramebufferCreateInfo framebufferInfo;
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.pNext = 0;
        framebufferInfo.flags = 0;
        framebufferInfo.renderPass = renderPass;
        framebufferInfo.attachmentCount = 2;
        if (multiSamplingMode > MULTI_SAMPLING_NONE)
        {
            framebufferInfo.attachmentCount = 3;
        }
        framebufferInfo.pAttachments = imageViews;
        framebufferInfo.width = width;
        framebufferInfo.height = height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(GVulkanDevice, &framebufferInfo,
            SYSVKMEMORY_FRAMEBUFFER_ALLOC, &framebuffers[i]) != VK_SUCCESS)
        {
            // Could not create framebuffer
            return false;
        }
        if (!framebuffers[i])
        {
            // Invalid framebuffer
            return false;
        }
    }

    // Set backchain extent
    extent.width = width;
    extent.height = height;

    // Set backchain aspect ratio
    ratio = 1.0f;
    if ((extent.width > 0) && (extent.height > 0))
    {
        ratio = (extent.width*1.0f) / (extent.height*1.0f);
    }

    // Backchain successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Resize backchain                                                          //
//  return : True if backchain is successfully resized                        //
////////////////////////////////////////////////////////////////////////////////
bool Backchain::resizeBackchain(VulkanMemoryPool memoryPool,
    uint32_t width, uint32_t height)
{
    // Check Vulkan device
    if (!GVulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Check backchain size
    if ((width <= 0) || (height <= 0))
    {
        // Invalid backchain size
        return false;
    }

    // Get multisample configuration
    MultiSamplingMode multiSamplingMode = GSysSettings.getMultiSamplingMode();

    // Destroy current backchain
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        // Destroy framebuffers
        if (framebuffers[i])
        {
            vkDestroyFramebuffer(
                GVulkanDevice, framebuffers[i], SYSVKMEMORY_FRAMEBUFFER_ALLOC
            );
        }
        framebuffers[i] = 0;

        // Destroy backchain depth images views
        if (depthViews[i])
        {
            vkDestroyImageView(
                GVulkanDevice, depthViews[i], SYSVKMEMORY_IMAGEVIEW_ALLOC
            );
        }
        depthViews[i] = 0;

        // Destroy backchain images views
        if (views[i])
        {
            vkDestroyImageView(
                GVulkanDevice, views[i], SYSVKMEMORY_IMAGEVIEW_ALLOC
            );
        }
        views[i]= 0;

        // Destroy backchain msaa images views
        if (msaaViews[i])
        {
            vkDestroyImageView(
                GVulkanDevice, msaaViews[i], SYSVKMEMORY_IMAGEVIEW_ALLOC
            );
        }
        msaaViews[i]= 0;

        // Destroy backchain depth images
        if (depthImages[i])
        {
            vkDestroyImage(
                GVulkanDevice, depthImages[i], SYSVKMEMORY_IMAGE_ALLOC
            );
        }
        depthImages[i] = 0;

        // Destroy backchain images
        if (images[i])
        {
            vkDestroyImage(GVulkanDevice, images[i], SYSVKMEMORY_IMAGE_ALLOC);
        }
        images[i] = 0;

        // Destroy backchain msaa images
        if (msaaImages[i])
        {
            vkDestroyImage(
                GVulkanDevice, msaaImages[i], SYSVKMEMORY_IMAGE_ALLOC
            );
        }
        msaaImages[i] = 0;
    }

    // Recreate backchain msaa images
    if (multiSamplingMode > MULTI_SAMPLING_NONE)
    {
        for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
        {
            VkImageCreateInfo imageInfo;
            imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
            imageInfo.pNext = 0;
            imageInfo.flags = 0;
            imageInfo.imageType = VK_IMAGE_TYPE_2D;
            imageInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
            imageInfo.extent.width = width;
            imageInfo.extent.height = height;
            imageInfo.extent.depth = 1;
            imageInfo.mipLevels = 1;
            imageInfo.arrayLayers = 1;
            imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
            imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
            imageInfo.usage = (VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
                VK_IMAGE_USAGE_SAMPLED_BIT);
            imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
            imageInfo.queueFamilyIndexCount = 0;
            imageInfo.pQueueFamilyIndices = 0;
            imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

            if (vkCreateImage(GVulkanDevice, &imageInfo,
                SYSVKMEMORY_IMAGE_ALLOC, &msaaImages[i]) != VK_SUCCESS)
            {
                // Could not recreate image
                return false;
            }
            if (!msaaImages[i])
            {
                // Invalid image
                return false;
            }

            // Reallocate image memory
            if (!GVulkanMemory.allocateBackchainImage(
                msaaImages[i], memoryPool))
            {
                // Could not reallocate image memory
                return false;
            }
        }
    }

    // Recreate backchain images
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        VkImageCreateInfo imageInfo;
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.pNext = 0;
        imageInfo.flags = 0;
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        imageInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
        imageInfo.extent.width = width;
        imageInfo.extent.height = height;
        imageInfo.extent.depth = 1;
        imageInfo.mipLevels = 1;
        imageInfo.arrayLayers = 1;
        imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        switch (multiSamplingMode)
        {
            case MULTI_SAMPLING_2X:
                imageInfo.samples = VK_SAMPLE_COUNT_2_BIT;
                break;
            case MULTI_SAMPLING_4X:
                imageInfo.samples = VK_SAMPLE_COUNT_4_BIT;
                break;
            case MULTI_SAMPLING_8X:
                imageInfo.samples = VK_SAMPLE_COUNT_8_BIT;
                break;
            default:
                imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
                break;
        }
        imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        imageInfo.usage =
            (VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT);
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        imageInfo.queueFamilyIndexCount = 0;
        imageInfo.pQueueFamilyIndices = 0;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

        if (vkCreateImage(GVulkanDevice, &imageInfo,
            SYSVKMEMORY_IMAGE_ALLOC, &images[i]) != VK_SUCCESS)
        {
            // Could not recreate image
            return false;
        }
        if (!images[i])
        {
            // Invalid image
            return false;
        }

        // Reallocate image memory
        if (!GVulkanMemory.allocateBackchainImage(images[i], memoryPool))
        {
            // Could not reallocate image memory
            return false;
        }
    }

    // Recreate backchain depth images
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        // Recreate depth image
        VkImageCreateInfo imageInfo;
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.pNext = 0;
        imageInfo.flags = 0;
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        imageInfo.format = VK_FORMAT_D32_SFLOAT;
        imageInfo.extent.width = width;
        imageInfo.extent.height = height;
        imageInfo.extent.depth = 1;
        imageInfo.mipLevels = 1;
        imageInfo.arrayLayers = 1;
        imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        switch (multiSamplingMode)
        {
            case MULTI_SAMPLING_2X:
                imageInfo.samples = VK_SAMPLE_COUNT_2_BIT;
                break;
            case MULTI_SAMPLING_4X:
                imageInfo.samples = VK_SAMPLE_COUNT_4_BIT;
                break;
            case MULTI_SAMPLING_8X:
                imageInfo.samples = VK_SAMPLE_COUNT_8_BIT;
                break;
            default:
                imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
                break;
        }
        imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        imageInfo.queueFamilyIndexCount = 0;
        imageInfo.pQueueFamilyIndices = 0;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

        if (vkCreateImage(GVulkanDevice, &imageInfo,
            SYSVKMEMORY_IMAGE_ALLOC, &depthImages[i]) != VK_SUCCESS)
        {
            // Could not create depth image
            return false;
        }
        if (!depthImages[i])
        {
            // Invalid depth image
            return false;
        }

        // Reallocate depth image memory
        if (!GVulkanMemory.allocateBackchainImage(depthImages[i], memoryPool))
        {
            // Could not reallocate depth image memory
            return false;
        }
    }

    // Recreate backchain msaa images views
    if (multiSamplingMode > MULTI_SAMPLING_NONE)
    {
        VkImageSubresourceRange msaaSubresource;
        msaaSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        msaaSubresource.baseMipLevel = 0;
        msaaSubresource.levelCount = 1;
        msaaSubresource.baseArrayLayer = 0;
        msaaSubresource.layerCount = 1;

        for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
        {
            // Recreate image view
            VkImageViewCreateInfo imageView;
            imageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            imageView.pNext = 0;
            imageView.flags = 0;
            imageView.image = msaaImages[i];
            imageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
            imageView.format = VK_FORMAT_R8G8B8A8_UNORM;
            imageView.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            imageView.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            imageView.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            imageView.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            imageView.subresourceRange = msaaSubresource;

            if (vkCreateImageView(GVulkanDevice, &imageView,
                SYSVKMEMORY_IMAGEVIEW_ALLOC, &msaaViews[i]) != VK_SUCCESS)
            {
                // Could not recreate image view
                return false;
            }
            if (!msaaViews[i])
            {
                // Invalid msaa image view
                return false;
            }
        }
    }

    // Recreate backchain images views
    VkImageSubresourceRange subresource;
    subresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    subresource.baseMipLevel = 0;
    subresource.levelCount = 1;
    subresource.baseArrayLayer = 0;
    subresource.layerCount = 1;

    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        // Recreate image view
        VkImageViewCreateInfo imageView;
        imageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageView.pNext = 0;
        imageView.flags = 0;
        imageView.image = images[i];
        imageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
        imageView.format = VK_FORMAT_R8G8B8A8_UNORM;
        imageView.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageView.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageView.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageView.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageView.subresourceRange = subresource;

        if (vkCreateImageView(GVulkanDevice, &imageView,
            SYSVKMEMORY_IMAGEVIEW_ALLOC, &views[i]) != VK_SUCCESS)
        {
            // Could not recreate image view
            return false;
        }
        if (!views[i])
        {
            // Invalid image view
            return false;
        }
    }

    // Recreate backchain depth images views
    VkImageSubresourceRange depthSubresource;
    depthSubresource.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    depthSubresource.baseMipLevel = 0;
    depthSubresource.levelCount = 1;
    depthSubresource.baseArrayLayer = 0;
    depthSubresource.layerCount = 1;

    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        // Recreate depth image view
        VkImageViewCreateInfo depthImageView;
        depthImageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        depthImageView.pNext = 0;
        depthImageView.flags = 0;
        depthImageView.image = depthImages[i];
        depthImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
        depthImageView.format = VK_FORMAT_D32_SFLOAT;
        depthImageView.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        depthImageView.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        depthImageView.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        depthImageView.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        depthImageView.subresourceRange = depthSubresource;

        if (vkCreateImageView(GVulkanDevice, &depthImageView,
            SYSVKMEMORY_IMAGEVIEW_ALLOC, &depthViews[i]) != VK_SUCCESS)
        {
            // Could not recreate depth image view
            return false;
        }
        if (!depthViews[i])
        {
            // Invalid depth image view
            return false;
        }
    }

    // Recreate framebuffers
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        VkImageView imageViews[3];
        imageViews[0] = views[i];
        imageViews[1] = depthViews[i];
        imageViews[2] = msaaViews[i];

        VkFramebufferCreateInfo framebufferInfo;
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.pNext = 0;
        framebufferInfo.flags = 0;
        framebufferInfo.renderPass = renderPass;
        framebufferInfo.attachmentCount = 2;
        if (multiSamplingMode > MULTI_SAMPLING_NONE)
        {
            framebufferInfo.attachmentCount = 3;
        }
        framebufferInfo.pAttachments = imageViews;
        framebufferInfo.width = width;
        framebufferInfo.height = height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(GVulkanDevice, &framebufferInfo,
            SYSVKMEMORY_FRAMEBUFFER_ALLOC, &framebuffers[i]) != VK_SUCCESS)
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

    // Set backchain extent
    extent.width = width;
    extent.height = height;

    // Set backchain aspect ratio
    ratio = 1.0f;
    if ((extent.width > 0) && (extent.height > 0))
    {
        ratio = (extent.width*1.0f) / (extent.height*1.0f);
    }

    // Backchain successfully resized
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy backchain                                                         //
////////////////////////////////////////////////////////////////////////////////
void Backchain::destroyBackchain()
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
        vkDestroyRenderPass(
            GVulkanDevice, renderPass, SYSVKMEMORY_RENDERPASS_ALLOC
        );
    }
    renderPass = 0;

    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        // Destroy framebuffers
        if (framebuffers[i])
        {
            vkDestroyFramebuffer(
                GVulkanDevice, framebuffers[i], SYSVKMEMORY_FRAMEBUFFER_ALLOC
            );
        }
        framebuffers[i] = 0;

        // Destroy backchain depth images views
        if (depthViews[i])
        {
            vkDestroyImageView(
                GVulkanDevice, depthViews[i], SYSVKMEMORY_IMAGEVIEW_ALLOC
            );
        }
        depthViews[i] = 0;

        // Destroy backchain images views
        if (views[i])
        {
            vkDestroyImageView(
                GVulkanDevice, views[i], SYSVKMEMORY_IMAGEVIEW_ALLOC
            );
        }
        views[i]= 0;

        // Destroy backchain msaa images views
        if (msaaViews[i])
        {
            vkDestroyImageView(
                GVulkanDevice, msaaViews[i], SYSVKMEMORY_IMAGEVIEW_ALLOC
            );
        }
        msaaViews[i]= 0;

        // Destroy backchain depth images
        if (depthImages[i])
        {
            vkDestroyImage(
                GVulkanDevice, depthImages[i], SYSVKMEMORY_IMAGE_ALLOC
            );
        }
        depthImages[i] = 0;

        // Destroy backchain images
        if (images[i])
        {
            vkDestroyImage(GVulkanDevice, images[i], SYSVKMEMORY_IMAGE_ALLOC);
        }
        images[i] = 0;

        // Destroy backchain msaa images
        if (msaaImages[i])
        {
            vkDestroyImage(
                GVulkanDevice, msaaImages[i], SYSVKMEMORY_IMAGE_ALLOC
            );
        }
        msaaImages[i] = 0;
    }

    ratio = 0.0f;
    extent.height = 0;
    extent.width = 0;
}
