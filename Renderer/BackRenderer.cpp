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
//  MainRenderer global instance                                              //
////////////////////////////////////////////////////////////////////////////////
BackRenderer GMainRenderer = BackRenderer();


////////////////////////////////////////////////////////////////////////////////
//  BackRenderer default constructor                                          //
////////////////////////////////////////////////////////////////////////////////
BackRenderer::BackRenderer() :
backchain(),
view(),
current(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  BackRenderer destructor                                                   //
////////////////////////////////////////////////////////////////////////////////
BackRenderer::~BackRenderer()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Init back renderer                                                        //
//  return : True if the back renderer is successfully loaded                 //
////////////////////////////////////////////////////////////////////////////////
bool BackRenderer::init(VulkanMemoryPool memoryPool,
    uint32_t width, uint32_t height, bool smooth)
{
    // Check back renderer size
    if ((width <= 0) || (width > BackRendererMaxWidth) ||
        (height <= 0) || (height > BackRendererMaxHeight))
    {
        // Invalid back renderer size
        return false;
    }

    // Create backchain
    if (!backchain.createBackchain(memoryPool, width, height))
    {
        // Could not create backchain
        return false;
    }

    // Create image samplers
    VkSamplerCreateInfo samplerInfo;
    samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    samplerInfo.pNext = 0;
    samplerInfo.flags = 0;
    samplerInfo.magFilter = VK_FILTER_NEAREST;
    samplerInfo.minFilter = VK_FILTER_NEAREST;
    if (smooth)
    {
        samplerInfo.magFilter = VK_FILTER_LINEAR;
        samplerInfo.minFilter = VK_FILTER_LINEAR;
    }
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

    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        // Create image sampler
        if (vkCreateSampler(GVulkanDevice,
            &samplerInfo, 0, &samplers[i]) != VK_SUCCESS)
        {
            // Could not create image sampler
            return false;
        }
        if (!samplers[i])
        {
            // Invalid image sampler
            return false;
        }
    }

    // Create descriptor sets
    VkDescriptorSetAllocateInfo descriptorInfo;
    descriptorInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    descriptorInfo.pNext = 0;
    descriptorInfo.descriptorPool = GGraphicsLayout.texturesDescPool;
    descriptorInfo.descriptorSetCount = RendererMaxSwapchainFrames;
    descriptorInfo.pSetLayouts = &GGraphicsLayout.swapSetLayouts[
        DESC_TEXTURE*RendererMaxSwapchainFrames
    ];

    if (vkAllocateDescriptorSets(GVulkanDevice,
        &descriptorInfo, descriptorSets) != VK_SUCCESS)
    {
        // Could not allocate descriptor sets
        return false;
    }

    // Update descriptor sets
    VkDescriptorImageInfo descImageInfo;
    descImageInfo.sampler = 0;
    descImageInfo.imageView = 0;
    descImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    VkWriteDescriptorSet descriptorWrites;
    descriptorWrites.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrites.pNext = 0;
    descriptorWrites.dstSet = 0;
    descriptorWrites.dstBinding = 0;
    descriptorWrites.dstArrayElement = 0;
    descriptorWrites.descriptorCount = 1;
    descriptorWrites.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptorWrites.pImageInfo = 0;
    descriptorWrites.pBufferInfo = 0;
    descriptorWrites.pTexelBufferView = 0;

    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        // Update descriptor set
        descImageInfo.sampler = samplers[i];
        descImageInfo.imageView = backchain.views[i];
        descriptorWrites.dstSet = descriptorSets[i];
        descriptorWrites.pImageInfo = &descImageInfo;

        vkUpdateDescriptorSets(GVulkanDevice, 1, &descriptorWrites, 0, 0);
    }

    // Init default view
    if (!view.init())
    {
        // Could not init default view
        return false;
    }

    // Back renderer successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Start back renderer pass                                                  //
//  return : True if the back renderer pass is started                        //
////////////////////////////////////////////////////////////////////////////////
bool BackRenderer::startRenderPass()
{
    // Set clear values
    VkClearValue clearValues[2];
    clearValues[0].color = BackRendererClearColor;
    clearValues[1].depthStencil = BackRendererClearDepth;

    // Begin render pass
    VkRenderPassBeginInfo renderPassInfo;
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.pNext = 0;
    renderPassInfo.renderPass = backchain.renderPass;
    renderPassInfo.framebuffer = backchain.framebuffers[GSwapchain.current];
    renderPassInfo.renderArea.offset.x = 0;
    renderPassInfo.renderArea.offset.y = 0;
    renderPassInfo.renderArea.extent.width = backchain.extent.width;
    renderPassInfo.renderArea.extent.height = backchain.extent.height;
    renderPassInfo.clearValueCount = 2;
    renderPassInfo.pClearValues = clearValues;

    vkCmdBeginRenderPass(
        GSwapchain.commandBuffers[GSwapchain.current],
        &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE
    );

    // Set viewport
    VkViewport viewport;
    viewport.x = 0.0f;
    viewport.y = backchain.extent.height*1.0f;
    viewport.width = backchain.extent.width*1.0f;
    viewport.height = backchain.extent.height*-1.0f;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    vkCmdSetViewport(
        GSwapchain.commandBuffers[GSwapchain.current], 0, 1, &viewport
    );

    // Set scissor
    VkRect2D scissor;
    scissor.offset.x = 0;
    scissor.offset.y = 0;
    scissor.extent.width = backchain.extent.width;
    scissor.extent.height = backchain.extent.height;

    vkCmdSetScissor(
        GSwapchain.commandBuffers[GSwapchain.current], 0, 1, &scissor
    );

    // Push default model matrix into command buffer
    Matrix4x4 defaultMatrix;
    defaultMatrix.setIdentity();
    vkCmdPushConstants(
        GSwapchain.commandBuffers[GSwapchain.current],
        GGraphicsLayout.handle, VK_SHADER_STAGE_VERTEX_BIT,
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
        GSwapchain.commandBuffers[GSwapchain.current],
        GGraphicsLayout.handle, VK_SHADER_STAGE_FRAGMENT_BIT,
        PushConstantDataOffset, PushConstantDataSize, &pushConstants
    );

    // Rendering frame is ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  End back renderer pass                                                    //
////////////////////////////////////////////////////////////////////////////////
void BackRenderer::endRenderPass()
{
    // End render pass
    vkCmdEndRenderPass(GSwapchain.commandBuffers[GSwapchain.current]);
    current = GSwapchain.current;
}

////////////////////////////////////////////////////////////////////////////////
//  Bind back renderer texture                                                //
////////////////////////////////////////////////////////////////////////////////
void BackRenderer::bind()
{
    // Bind texture descriptor set
    vkCmdBindDescriptorSets(
        GSwapchain.commandBuffers[GSwapchain.current],
        VK_PIPELINE_BIND_POINT_GRAPHICS, GGraphicsLayout.handle,
        DESC_TEXTURE, 1, &descriptorSets[current], 0, 0
    );
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy back renderer                                                     //
////////////////////////////////////////////////////////////////////////////////
void BackRenderer::destroyBackRenderer()
{
    // Check Vulkan device
    if (!GVulkanDevice)
    {
        // Invalid Vulkan device
        return;
    }

    // Reset current frame
    current = 0;

    // Destroy image samplers
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        if (samplers[i])
        {
            vkDestroySampler(GVulkanDevice, samplers[i], 0);
        }
        samplers[i] = 0;
    }

    // Destroy default view
    view.destroyView();

    // Destroy backchain
    backchain.destroyBackchain();
}


////////////////////////////////////////////////////////////////////////////////
//  Set back renderer default view                                            //
//  return : True if the default view is successfully set                     //
////////////////////////////////////////////////////////////////////////////////
bool BackRenderer::setDefaultView()
{
    // Compute default view
    view.compute(backchain.ratio);

    // Bind default view
    if (!view.bind())
    {
        // Could not bind default view
        return false;
    }

    // Default view successfully set
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Resize back renderer frame                                                //
//  return : True if the back renderer is successfully resized                //
////////////////////////////////////////////////////////////////////////////////
bool BackRenderer::resize(VulkanMemoryPool memoryPool,
    uint32_t width, uint32_t height)
{
    // Check Vulkan device
    if (!GVulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Resize backchain
    if (!backchain.resizeBackchain(memoryPool, width, height))
    {
        // Could not resize backchain
        return false;
    }

    // Update descriptor sets
    VkDescriptorImageInfo descImageInfo;
    descImageInfo.sampler = 0;
    descImageInfo.imageView = 0;
    descImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    VkWriteDescriptorSet descriptorWrites;
    descriptorWrites.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrites.pNext = 0;
    descriptorWrites.dstSet = 0;
    descriptorWrites.dstBinding = 0;
    descriptorWrites.dstArrayElement = 0;
    descriptorWrites.descriptorCount = 1;
    descriptorWrites.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptorWrites.pImageInfo = 0;
    descriptorWrites.pBufferInfo = 0;
    descriptorWrites.pTexelBufferView = 0;

    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        // Update descriptor set
        descImageInfo.sampler = samplers[i];
        descImageInfo.imageView = backchain.views[i];
        descriptorWrites.dstSet = descriptorSets[i];
        descriptorWrites.pImageInfo = &descImageInfo;

        vkUpdateDescriptorSets(GVulkanDevice, 1, &descriptorWrites, 0, 0);
    }

    // Back renderer successfully resized
    return true;
}
