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
//     Renderer/BackRenderer.cpp : Offscreen renderer management              //
////////////////////////////////////////////////////////////////////////////////
#include "BackRenderer.h"


////////////////////////////////////////////////////////////////////////////////
//  BackRenderer default constructor                                          //
////////////////////////////////////////////////////////////////////////////////
BackRenderer::BackRenderer() :
m_extent(),
m_renderPass(0),
m_layout(),
m_pipeline(),
m_current(0),
m_ratio(0.0f)
{
    m_extent.width = 0;
    m_extent.height = 0;
    for (uint32_t i = 0; i < BackRendererMaxFrames; ++i)
    {
        m_images[i] = 0;
        m_depthImages[i] = 0;
        m_views[i] = 0;
        m_depthViews[i] = 0;
        m_framebuffers[i] = 0;
        m_fences[i] = 0;
        m_commandPools[i] = 0;
        m_commandBuffers[i] = 0;
        m_samplers[i] = 0;
        m_descriptorSets[i] = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  BackRenderer destructor                                                   //
////////////////////////////////////////////////////////////////////////////////
BackRenderer::~BackRenderer()
{
    for (uint32_t i = 0; i < BackRendererMaxFrames; ++i)
    {
        m_descriptorSets[i] = 0;
        m_samplers[i] = 0;
        m_commandBuffers[i] = 0;
        m_commandPools[i] = 0;
        m_fences[i] = 0;
        m_framebuffers[i] = 0;
        m_depthViews[i] = 0;
        m_views[i] = 0;
        m_depthImages[i] = 0;
        m_images[i] = 0;
    }
    m_ratio = 0.0f;
    m_current = 0;
    m_renderPass = 0;
    m_extent.height = 0;
    m_extent.width = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Init back renderer                                                        //
//  return : True if the back renderer is successfully loaded                 //
////////////////////////////////////////////////////////////////////////////////
bool BackRenderer::init(Renderer& renderer, uint32_t width, uint32_t height)
{
    // Check back renderer size
    if ((width <= 0) || (width > BackRendererMaxWidth) ||
        (height <= 0) || (height > BackRendererMaxHeight))
    {
        // Invalid back renderer size
        return false;
    }

    // Create back renderer images
    for (uint32_t i = 0; i < BackRendererMaxFrames; ++i)
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
        imageInfo.usage =
            VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        imageInfo.queueFamilyIndexCount = 0;
        imageInfo.pQueueFamilyIndices = 0;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

        if (vkCreateImage(
            renderer.m_vulkanDevice, &imageInfo, 0, &m_images[i]) != VK_SUCCESS)
        {
            // Could not create image
            return false;
        }
        if (!m_images[i])
        {
            // Invalid image
            return false;
        }

        // Allocate image memory
        if (!renderer.m_vulkanMemory.allocateBackRendererImage(
            renderer.m_vulkanDevice, m_images[i]))
        {
            // Could not allocate image memory
            return false;
        }
    }

    // Create back renderer depth images
    for (uint32_t i = 0; i < BackRendererMaxFrames; ++i)
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
        imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        imageInfo.queueFamilyIndexCount = 0;
        imageInfo.pQueueFamilyIndices = 0;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

        if (vkCreateImage(renderer.m_vulkanDevice,
            &imageInfo, 0, &m_depthImages[i]) != VK_SUCCESS)
        {
            // Could not create depth image
            return false;
        }
        if (!m_depthImages[i])
        {
            // Invalid depth image
            return false;
        }

        // Allocate depth image memory
        if (!renderer.m_vulkanMemory.allocateBackRendererImage(
            renderer.m_vulkanDevice, m_depthImages[i]))
        {
            // Could not allocate depth image memory
            return false;
        }
    }

    // Create back renderer images views
    VkImageSubresourceRange subresource;
    subresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    subresource.baseMipLevel = 0;
    subresource.levelCount = 1;
    subresource.baseArrayLayer = 0;
    subresource.layerCount = 1;

    for (uint32_t i = 0; i < BackRendererMaxFrames; ++i)
    {
        // Create image view
        VkImageViewCreateInfo imageView;
        imageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageView.pNext = 0;
        imageView.flags = 0;
        imageView.image = m_images[i];
        imageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
        imageView.format = VK_FORMAT_R8G8B8A8_UNORM;
        imageView.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageView.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageView.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageView.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageView.subresourceRange = subresource;

        if (vkCreateImageView(
            renderer.m_vulkanDevice, &imageView, 0, &m_views[i]) != VK_SUCCESS)
        {
            return false;
        }
    }

    // Create back renderer depth images views
    VkImageSubresourceRange depthSubresource;
    depthSubresource.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    depthSubresource.baseMipLevel = 0;
    depthSubresource.levelCount = 1;
    depthSubresource.baseArrayLayer = 0;
    depthSubresource.layerCount = 1;

    for (uint32_t i = 0; i < BackRendererMaxFrames; ++i)
    {
        // Create depth image view
        VkImageViewCreateInfo depthImageView;
        depthImageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        depthImageView.pNext = 0;
        depthImageView.flags = 0;
        depthImageView.image = m_depthImages[i];
        depthImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
        depthImageView.format = VK_FORMAT_D32_SFLOAT;
        depthImageView.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        depthImageView.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        depthImageView.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        depthImageView.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        depthImageView.subresourceRange = depthSubresource;

        if (vkCreateImageView(renderer.m_vulkanDevice,
            &depthImageView, 0, &m_depthViews[i]) != VK_SUCCESS)
        {
            return false;
        }
    }

    // Set color attachment
    VkAttachmentDescription attachmentDescription[2];
    attachmentDescription[0].flags = 0;
    attachmentDescription[0].format = VK_FORMAT_R8G8B8A8_UNORM;
    attachmentDescription[0].samples = VK_SAMPLE_COUNT_1_BIT;
    attachmentDescription[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachmentDescription[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachmentDescription[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachmentDescription[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachmentDescription[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachmentDescription[0].finalLayout =
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

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

    if (vkCreateRenderPass(renderer.m_vulkanDevice,
        &renderPassInfo, 0, &m_renderPass) != VK_SUCCESS)
    {
        // Could not create render pass
        return false;
    }
    if (!m_renderPass)
    {
        // Invalid render pass
        return false;
    }

    // Create framebuffers
    for (uint32_t i = 0; i < BackRendererMaxFrames; ++i)
    {
        VkImageView imageViews[2];
        imageViews[0] = m_views[i];
        imageViews[1] = m_depthViews[i];

        VkFramebufferCreateInfo framebufferInfo;
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.pNext = 0;
        framebufferInfo.flags = 0;
        framebufferInfo.renderPass = m_renderPass;
        framebufferInfo.attachmentCount = 2;
        framebufferInfo.pAttachments = imageViews;
        framebufferInfo.width = width;
        framebufferInfo.height = height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(renderer.m_vulkanDevice,
            &framebufferInfo, 0, &m_framebuffers[i]) != VK_SUCCESS)
        {
            // Could not create framebuffer
            return false;
        }
        if (!m_framebuffers[i])
        {
            // Invalid framebuffer
            return false;
        }
    }

    // Create image samplers
    for (uint32_t i = 0; i < BackRendererMaxFrames; ++i)
    {
        VkSamplerCreateInfo samplerInfo;
        samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        samplerInfo.pNext = 0;
        samplerInfo.flags = 0;
        samplerInfo.magFilter = VK_FILTER_NEAREST;
        samplerInfo.minFilter = VK_FILTER_NEAREST;
        samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
        samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        samplerInfo.mipLodBias = 0.0f;
        samplerInfo.anisotropyEnable = VK_FALSE;
        samplerInfo.maxAnisotropy = 1.0f;
        samplerInfo.compareEnable = VK_FALSE;
        samplerInfo.compareOp = VK_COMPARE_OP_NEVER;
        samplerInfo.minLod = 0.0f;
        samplerInfo.maxLod = 0.0f;
        samplerInfo.borderColor = VK_BORDER_COLOR_INT_TRANSPARENT_BLACK;
        samplerInfo.unnormalizedCoordinates = VK_FALSE;

        if (vkCreateSampler(renderer.m_vulkanDevice,
            &samplerInfo, 0, &m_samplers[i]) != VK_SUCCESS)
        {
            // Could not create image sampler
            return false;
        }
        if (!m_samplers[i])
        {
            // Invalid image sampler
            return false;
        }
    }

    // Create descriptor sets
    VkDescriptorSetAllocateInfo descriptorInfo;
    descriptorInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    descriptorInfo.pNext = 0;
    descriptorInfo.descriptorPool = renderer.m_texturesDescPool;
    descriptorInfo.descriptorSetCount = BackRendererMaxFrames;
    descriptorInfo.pSetLayouts = &renderer.m_layout.swapSetLayouts[
        DESC_TEXTURE*BackRendererMaxFrames
    ];

    if (vkAllocateDescriptorSets(renderer.m_vulkanDevice,
        &descriptorInfo, m_descriptorSets) != VK_SUCCESS)
    {
        // Could not allocate descriptor sets
        return false;
    }

    for (uint32_t i = 0; i < BackRendererMaxFrames; ++i)
    {
        // Update descriptor sets
        VkDescriptorImageInfo descImageInfo;
        descImageInfo.sampler = m_samplers[i];
        descImageInfo.imageView = m_views[i];
        descImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

        VkWriteDescriptorSet descriptorWrites;

        descriptorWrites.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites.pNext = 0;
        descriptorWrites.dstSet = m_descriptorSets[i];
        descriptorWrites.dstBinding = 0;
        descriptorWrites.dstArrayElement = 0;
        descriptorWrites.descriptorCount = 1;
        descriptorWrites.descriptorType =
            VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptorWrites.pImageInfo = &descImageInfo;
        descriptorWrites.pBufferInfo = 0;
        descriptorWrites.pTexelBufferView = 0;

        vkUpdateDescriptorSets(
            renderer.m_vulkanDevice, 1, &descriptorWrites, 0, 0
        );
    }

    // Create fences
    VkFenceCreateInfo fenceInfo;
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.pNext = 0;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (uint32_t i = 0; i < BackRendererMaxFrames; ++i)
    {
        if (vkCreateFence(
            renderer.m_vulkanDevice, &fenceInfo, 0, &m_fences[i]) != VK_SUCCESS)
        {
            // Could not create fence
            return false;
        }
        if (!m_fences[i])
        {
            // Invalid fence
            return false;
        }
    }

    // Create commands pools
    VkCommandPoolCreateInfo commandPoolInfo;
    commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolInfo.pNext = 0;
    commandPoolInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
    commandPoolInfo.queueFamilyIndex = renderer.m_graphicsQueue.family;

    for (uint32_t i = 0; i < BackRendererMaxFrames; ++i)
    {
        if (vkCreateCommandPool(renderer.m_vulkanDevice,
            &commandPoolInfo, 0, &m_commandPools[i]) != VK_SUCCESS)
        {
            // Could not create commands pool
            return false;
        }
        if (!m_commandPools[i])
        {
            // Invalid commands pool
            return false;
        }
    }

    // Allocate command buffers
    for (uint32_t i = 0; i < BackRendererMaxFrames; ++i)
    {
        VkCommandBufferAllocateInfo commandBufferInfo;
        commandBufferInfo.sType =
            VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        commandBufferInfo.pNext = 0;
        commandBufferInfo.commandPool = m_commandPools[i];
        commandBufferInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        commandBufferInfo.commandBufferCount = 1;

        if (vkAllocateCommandBuffers(renderer.m_vulkanDevice,
            &commandBufferInfo, &m_commandBuffers[i]) != VK_SUCCESS)
        {
            // Could not allocate command buffers
            return false;
        }
    }

    // Create pipeline layout
    if (!m_layout.createLayout(renderer.m_vulkanDevice))
    {
        // Could not create pipeline layout
        return false;
    }

    // Create default pipeline
    m_pipeline.createVertexShader(
        renderer, DefaultVertexShader, DefaultVertexShaderSize
    );
    m_pipeline.createFragmentShader(
        renderer, DefaultFragmentShader, DefaultFragmentShaderSize
    );
    if (!m_pipeline.createPipeline(renderer, *this))
    {
        // Could not create default pipeline
        return false;
    }

    // Init default view
    if (!m_view.init(renderer, *this))
    {
        // Could not init default view
        return false;
    }

    // Set back renderer extent
    m_extent.width = width;
    m_extent.height = height;

    // Set back renderer aspect ratio
    m_ratio = 1.0f;
    if ((m_extent.width > 0) && (m_extent.height > 0))
    {
        m_ratio = (m_extent.width*1.0f) / (m_extent.height*1.0f);
    }

    // Back renderer successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Start rendering frame                                                     //
//  return : True if the rendering frame is ready                             //
////////////////////////////////////////////////////////////////////////////////
bool BackRenderer::startFrame(Renderer& renderer)
{
    // Clamp current frame index
    if (m_current <= 0)
    {
        m_current = 0;
    }
    if (m_current >= (BackRendererMaxFrames-1))
    {
        m_current = (BackRendererMaxFrames-1);
    }

    // Wait for current frame rendering fence
    if (vkWaitForFences(renderer.m_vulkanDevice, 1,
        &m_fences[m_current],
        VK_FALSE, BackRendererFenceTimeout) != VK_SUCCESS)
    {
        // Rendering fence timed out
        return false;
    }

    // Reset command pool
    if (vkResetCommandPool(renderer.m_vulkanDevice,
        m_commandPools[m_current], 0) != VK_SUCCESS)
    {
        // Could not reset command pool
        return false;
    }

    // Command buffer begin
    VkCommandBufferBeginInfo commandBegin;
    commandBegin.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    commandBegin.pNext = 0;
    commandBegin.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    commandBegin.pInheritanceInfo = 0;

    // Begin command buffer
    if (vkBeginCommandBuffer(m_commandBuffers[m_current],
        &commandBegin) != VK_SUCCESS)
    {
        // Could not begin command buffer
        return false;
    }

    // Set clear values
    VkClearValue clearValues[2];
    clearValues[0].color = RendererClearColor;
    clearValues[1].depthStencil = RendererClearDepth;

    // Begin render pass
    VkRenderPassBeginInfo renderPassInfo;
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.pNext = 0;
    renderPassInfo.renderPass = m_renderPass;
    renderPassInfo.framebuffer = m_framebuffers[m_current];
    renderPassInfo.renderArea.offset.x = 0;
    renderPassInfo.renderArea.offset.y = 0;
    renderPassInfo.renderArea.extent.width = m_extent.width;
    renderPassInfo.renderArea.extent.height = m_extent.height;
    renderPassInfo.clearValueCount = 2;
    renderPassInfo.pClearValues = clearValues;

    vkCmdBeginRenderPass(
        m_commandBuffers[m_current],
        &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE
    );

    // Bind default pipeline
    m_pipeline.bind(*this);

    // Set viewport
    VkViewport viewport;
    viewport.x = 0.0f;
    viewport.y = m_extent.height*1.0f;
    viewport.width = m_extent.width*1.0f;
    viewport.height = m_extent.height*-1.0f;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    vkCmdSetViewport(
        m_commandBuffers[m_current], 0, 1, &viewport
    );

    // Set scissor
    VkRect2D scissor;
    scissor.offset.x = 0;
    scissor.offset.y = 0;
    scissor.extent.width = m_extent.width;
    scissor.extent.height = m_extent.height;

    vkCmdSetScissor(
        m_commandBuffers[m_current], 0, 1, &scissor
    );

    // Bind default view
    if (!m_view.bind(renderer, *this))
    {
        // Could not bind default view
        return false;
    }

    // Bind default vertex buffer
    VkDeviceSize offset = 0;
    vkCmdBindVertexBuffers(
        m_commandBuffers[m_current], 0, 1,
        &(renderer.m_resources.meshes.mesh(MESHES_DEFAULT).vertexBuffer.handle),
        &offset
    );

    vkCmdBindIndexBuffer(
        m_commandBuffers[m_current],
        (renderer.m_resources.meshes.mesh(MESHES_DEFAULT).indexBuffer.handle),
        0, VK_INDEX_TYPE_UINT16
    );

    // Push default model matrix into command buffer
    Matrix4x4 defaultMatrix;
    defaultMatrix.setIdentity();
    vkCmdPushConstants(
        m_commandBuffers[m_current],
        m_layout.handle, VK_SHADER_STAGE_VERTEX_BIT,
        PushConstantMatrixOffset, PushConstantMatrixSize, defaultMatrix.mat
    );

    // Push default constants into command buffer
    PushConstantData pushConstants;
    pushConstants.color[0] = 1.0f;
    pushConstants.color[1] = 1.0f;
    pushConstants.color[2] = 1.0f;
    pushConstants.color[3] = 1.0f;
    pushConstants.offset[0] = 0.0f;
    pushConstants.offset[1] = 0.0f;
    pushConstants.size[0] = 1.0f;
    pushConstants.size[1] = 1.0f;
    pushConstants.time = 0.0f;
    vkCmdPushConstants(
        m_commandBuffers[m_current],
        m_layout.handle, VK_SHADER_STAGE_FRAGMENT_BIT,
        PushConstantDataOffset, PushConstantDataSize, &pushConstants
    );

    // Rendering frame is ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  End rendering frame                                                       //
//  return : True if the frame is rendering                                   //
////////////////////////////////////////////////////////////////////////////////
bool BackRenderer::endFrame(Renderer& renderer)
{
    // End render pass
    vkCmdEndRenderPass(m_commandBuffers[m_current]);

    // End command buffer
    if (vkEndCommandBuffer(m_commandBuffers[m_current]) != VK_SUCCESS)
    {
        // Could not end command buffer
        return false;
    }

    // Reset current frame rendering fence
    if (vkResetFences(renderer.m_vulkanDevice, 1,
        &m_fences[m_current]) != VK_SUCCESS)
    {
        // Could not reset fence
        return false;
    }

    // Submit current frame
    VkPipelineStageFlags waitDstStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    VkSubmitInfo submitInfo;
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.pNext = 0;
    submitInfo.waitSemaphoreCount = 0;
    submitInfo.pWaitSemaphores = 0;
    submitInfo.pWaitDstStageMask = &waitDstStage;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &m_commandBuffers[m_current];
    submitInfo.signalSemaphoreCount = 0;
    submitInfo.pSignalSemaphores = 0;

    if (vkQueueSubmit(renderer.m_graphicsQueue.handle, 1, &submitInfo,
        m_fences[m_current]) != VK_SUCCESS)
    {
        return false;
    }

    // Next swapchain frame index
    ++m_current;
    if (m_current >= BackRendererMaxFrames)
    {
        m_current = 0;
    }

    // Current frame is submitted for rendering
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Bind back renderer texture                                                //
////////////////////////////////////////////////////////////////////////////////
void BackRenderer::bind(Renderer& renderer)
{
    // Bind texture descriptor set
    vkCmdBindDescriptorSets(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        VK_PIPELINE_BIND_POINT_GRAPHICS, renderer.m_layout.handle,
        DESC_TEXTURE, 1, &m_descriptorSets[renderer.m_swapchain.current], 0, 0
    );
}

////////////////////////////////////////////////////////////////////////////////
//  Cleanup back renderer                                                     //
////////////////////////////////////////////////////////////////////////////////
void BackRenderer::cleanup(Renderer& renderer)
{
    if (renderer.m_vulkanDevice)
    {
        if (vkDeviceWaitIdle)
        {
            if (vkDeviceWaitIdle(renderer.m_vulkanDevice) == VK_SUCCESS)
            {
                // Destroy default view
                m_view.destroyView(renderer);

                // Destroy default pipeline
                m_pipeline.destroyPipeline(renderer);

                // Destroy default pipeline layout
                m_layout.destroyLayout(renderer.m_vulkanDevice);

                // Destroy render pass
                if (m_renderPass && vkDestroyRenderPass)
                {
                    vkDestroyRenderPass(
                        renderer.m_vulkanDevice, m_renderPass, 0
                    );
                }

                for (uint32_t i = 0; i < BackRendererMaxFrames; ++i)
                {
                    // Destroy image sampler
                    if (m_samplers[i] && vkDestroySampler)
                    {
                        vkDestroySampler(
                            renderer.m_vulkanDevice, m_samplers[i], 0
                        );
                    }

                    // Destroy command buffer
                    if (m_commandPools[i] && vkFreeCommandBuffers)
                    {
                        if (m_commandBuffers[i])
                        {
                            vkFreeCommandBuffers(renderer.m_vulkanDevice,
                                m_commandPools[i], 1, &m_commandBuffers[i]
                            );
                        }
                    }

                    // Destroy commands pool
                    if (m_commandPools[i] && vkDestroyCommandPool)
                    {
                        vkDestroyCommandPool(
                            renderer.m_vulkanDevice, m_commandPools[i], 0
                        );
                    }

                    // Destroy fences
                    if (m_fences[i] && vkDestroyFence)
                    {
                        vkDestroyFence(renderer.m_vulkanDevice, m_fences[i], 0);
                    }

                    // Destroy framebuffers
                    if (m_framebuffers[i] && vkDestroyFramebuffer)
                    {
                        vkDestroyFramebuffer(
                            renderer.m_vulkanDevice, m_framebuffers[i], 0
                        );
                    }

                    // Destroy back renderer depth images views
                    if (m_depthViews[i] && vkDestroyImageView)
                    {
                        // Destroy image view
                        vkDestroyImageView(
                            renderer.m_vulkanDevice, m_depthViews[i], 0
                        );
                    }

                    // Destroy back renderer images views
                    if (m_views[i] && vkDestroyImageView)
                    {
                        // Destroy image view
                        vkDestroyImageView(
                            renderer.m_vulkanDevice, m_views[i], 0
                        );
                    }

                    // Destroy back renderer depth images
                    if (m_depthImages[i] && vkDestroyImage)
                    {
                        vkDestroyImage(
                            renderer.m_vulkanDevice, m_depthImages[i], 0
                        );
                    }

                    // Destroy back renderer images
                    if (m_depthImages[i] && vkDestroyImage)
                    {
                        vkDestroyImage(
                            renderer.m_vulkanDevice, m_images[i], 0
                        );
                    }
                }
            }
        }
    }

    for (uint32_t i = 0; i < BackRendererMaxFrames; ++i)
    {
        m_descriptorSets[i] = 0;
        m_samplers[i] = 0;
        m_commandBuffers[i] = 0;
        m_commandPools[i] = 0;
        m_fences[i] = 0;
        m_framebuffers[i] = 0;
        m_depthViews[i] = 0;
        m_views[i]= 0;
        m_depthImages[i] = 0;
        m_images[i] = 0;
    }
    m_ratio = 0.0f;
    m_current = 0;
    m_renderPass = 0;
    m_extent.height = 0;
    m_extent.width = 0;
}
