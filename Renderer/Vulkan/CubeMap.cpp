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
//     Renderer/Vulkan/CubeMap.cpp : CubeMap management                       //
////////////////////////////////////////////////////////////////////////////////
#include "CubeMap.h"
#include "../Renderer.h"
#include "../../Resources/TextureLoader.h"


////////////////////////////////////////////////////////////////////////////////
//  CubeMap default constructor                                               //
////////////////////////////////////////////////////////////////////////////////
CubeMap::CubeMap() :
m_handle(0),
m_sampler(0),
m_view(0),
m_memorySize(0),
m_memoryOffset(0),
m_width(0),
m_height(0)
{
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        m_descriptorSets[i] = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  CubeMap destructor                                                        //
////////////////////////////////////////////////////////////////////////////////
CubeMap::~CubeMap()
{
    m_height = 0;
    m_width = 0;
    m_memoryOffset = 0;
    m_memorySize = 0;
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        m_descriptorSets[i] = 0;
    }
    m_view = 0;
    m_sampler = 0;
    m_handle = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Create cubemap                                                            //
//  return : True if cubemap is successfully created                          //
////////////////////////////////////////////////////////////////////////////////
bool CubeMap::createCubeMap(Renderer& renderer, VulkanMemoryPool memoryPool,
    uint32_t width, uint32_t height, bool smooth)
{
    // Check cubemap size
    if ((width <= 0) || (width > CubeMapMaxWidth) ||
        (height <= 0) || (height > CubeMapMaxHeight) ||
        (width != height))
    {
        // Invalid cubemap size
        return false;
    }

    // Check cubemap handle
    if (m_handle)
    {
        // Destroy current cubemap
        destroyCubeMap(renderer);
    }

    // Create image
    VkImageCreateInfo imageInfo;
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.pNext = 0;
    imageInfo.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
    imageInfo.extent.width = width;
    imageInfo.extent.height = height;
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 6;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    imageInfo.usage =
        (VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT);
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    imageInfo.queueFamilyIndexCount = 0;
    imageInfo.pQueueFamilyIndices = 0;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    if (vkCreateImage(
        renderer.m_vulkanDevice, &imageInfo, 0, &m_handle) != VK_SUCCESS)
    {
        // Could not create image
        return false;
    }
    if (!m_handle)
    {
        // Invalid image
        return false;
    }

    // Allocate cubemap memory
    if (!renderer.m_vulkanMemory.allocateCubeMapMemory(
        renderer.m_vulkanDevice, *this, memoryPool))
    {
        // Could not allocate cubemap memory
        return false;
    }

    // Create image sampler
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

    if (vkCreateSampler(
        renderer.m_vulkanDevice, &samplerInfo, 0, &m_sampler) != VK_SUCCESS)
    {
        // Could not create image sampler
        return false;
    }
    if (!m_sampler)
    {
        // Invalid image sampler
        return false;
    }

    // Create image view
    VkImageViewCreateInfo viewInfo;
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.pNext = 0;
    viewInfo.flags = 0;
    viewInfo.image = m_handle;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_CUBE;
    viewInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
    viewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    viewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    viewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    viewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 6;

    if (vkCreateImageView(
        renderer.m_vulkanDevice, &viewInfo, 0, &m_view) != VK_SUCCESS)
    {
        // Could not create image view
        return false;
    }
    if (!m_view)
    {
        // Invalid image view
        return false;
    }

    // Create cubemap descriptor sets
    VkDescriptorSetAllocateInfo descriptorInfo;
    descriptorInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    descriptorInfo.pNext = 0;
    descriptorInfo.descriptorPool = renderer.m_texturesDescPool;
    descriptorInfo.descriptorSetCount = RendererMaxSwapchainFrames;
    descriptorInfo.pSetLayouts = &renderer.m_layout.swapSetLayouts[
        DESC_TEXTURE*RendererMaxSwapchainFrames
    ];

    if (vkAllocateDescriptorSets(renderer.m_vulkanDevice,
        &descriptorInfo, m_descriptorSets) != VK_SUCCESS)
    {
        // Could not allocate cubemap descriptor sets
        return false;
    }

    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        // Update cubemap descriptor sets
        VkDescriptorImageInfo descImageInfo;
        descImageInfo.sampler = m_sampler;
        descImageInfo.imageView = m_view;
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

    // Set cubemap size
    m_width = width;
    m_height = height;

    // CubeMap successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Update cubemap                                                            //
//  return : True if cubemap is successfully updated                          //
////////////////////////////////////////////////////////////////////////////////
bool CubeMap::updateCubeMap(Renderer& renderer, TextureLoader& loader,
    VulkanMemoryPool memoryPool, uint32_t width, uint32_t height,
    const unsigned char* data, bool smooth)
{
    // Check cubemap size
    if ((width <= 0) || (width > CubeMapMaxWidth) ||
        (height <= 0) || (height > CubeMapMaxHeight) ||
        (width != height))
    {
        // Invalid cubemap size
        return false;
    }

    // Check cubemap data
    if (!data)
    {
        // Invalid cubemap data
        return false;
    }

    // Check current cubemap
    if (!m_handle || (width != m_width) || (height != m_height))
    {
        // Recreate cubemap
        destroyCubeMap(renderer);
        createCubeMap(renderer, memoryPool, width, height, smooth);
    }

    // Upload cubemap to graphics memory
    if (!loader.uploadCubeMap(m_handle, width, height, data))
    {
        // Could not upload cubemap to graphics memory
        return false;
    }

    // CubeMap successfully updated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Bind cubemap                                                              //
////////////////////////////////////////////////////////////////////////////////
void CubeMap::bind(Renderer& renderer)
{
    // Bind cubemap descriptor set
    vkCmdBindDescriptorSets(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        VK_PIPELINE_BIND_POINT_GRAPHICS, renderer.m_layout.handle,
        DESC_TEXTURE, 1, &m_descriptorSets[renderer.m_swapchain.current], 0, 0
    );
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy cubemap                                                           //
////////////////////////////////////////////////////////////////////////////////
void CubeMap::destroyCubeMap(Renderer& renderer)
{
    if (renderer.m_vulkanDevice)
    {
        // Destroy image view
        if (m_view && vkDestroyImageView)
        {
            vkDestroyImageView(renderer.m_vulkanDevice, m_view, 0);
        }

        // Destroy image sampler
        if (m_sampler && vkDestroySampler)
        {
            vkDestroySampler(renderer.m_vulkanDevice, m_sampler, 0);
        }

        // Destroy image
        if (m_handle && vkDestroyImage)
        {
            vkDestroyImage(renderer.m_vulkanDevice, m_handle, 0);
        }
    }

    m_height = 0;
    m_width = 0;
    m_memoryOffset = 0;
    m_memorySize = 0;
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        m_descriptorSets[i] = 0;
    }
    m_view = 0;
    m_sampler = 0;
    m_handle = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Check if the cubemap has a valid handle                                   //
//  return : True if the cubemap is valid                                     //
////////////////////////////////////////////////////////////////////////////////
bool CubeMap::isValid()
{
    return m_handle;
}

////////////////////////////////////////////////////////////////////////////////
//  Get cubemap memory requirements                                           //
////////////////////////////////////////////////////////////////////////////////
void CubeMap::getMemoryRequirements(VkDevice& vulkanDevice,
    VkMemoryRequirements* memoryRequirements)
{
    vkGetImageMemoryRequirements(vulkanDevice, m_handle, memoryRequirements);
}

////////////////////////////////////////////////////////////////////////////////
//  Bind cubemap memory                                                       //
//  return : True if cubemap memory is successfully binded                    //
////////////////////////////////////////////////////////////////////////////////
bool CubeMap::bindCubeMapMemory(VkDevice& vulkanDevice,
    VkDeviceMemory& deviceMemory, VkDeviceSize size, VkDeviceSize offset)
{
    // Bind cubemap memory
    if (vkBindImageMemory(
        vulkanDevice, m_handle, deviceMemory, offset) != VK_SUCCESS)
    {
        // Could not bind cubemap memory
        return false;
    }

    // CubeMap memory successfully binded
    m_memorySize = size;
    m_memoryOffset = offset;
    return true;
}
