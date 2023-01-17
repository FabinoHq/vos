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
//     Renderer/Vulkan/TextureArray.cpp : Texture array management            //
////////////////////////////////////////////////////////////////////////////////
#include "TextureArray.h"
#include "../Renderer.h"
#include "../../Resources/TextureLoader.h"


////////////////////////////////////////////////////////////////////////////////
//  TextureArray default constructor                                          //
////////////////////////////////////////////////////////////////////////////////
TextureArray::TextureArray() :
m_handle(0),
m_sampler(0),
m_view(0),
m_memorySize(0),
m_memoryOffset(0),
m_width(0),
m_height(0),
m_layers(0)
{
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        m_descriptorSets[i] = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  TextureArray destructor                                                   //
////////////////////////////////////////////////////////////////////////////////
TextureArray::~TextureArray()
{
    m_layers = 0;
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
//  Create texture array                                                      //
//  return : True if texture array is successfully created                    //
////////////////////////////////////////////////////////////////////////////////
bool TextureArray::createTextureArray(VulkanMemoryPool memoryPool,
    uint32_t width, uint32_t height, uint32_t layers,
    uint32_t mipLevels, bool smooth, TextureRepeatMode repeat)
{
    // Check texture array handle
    if (m_handle)
    {
        // Destroy current texture array
        destroyTextureArray();
    }

    // Check texture array size
    if ((width <= 0) || (width > TextureMaxWidth) ||
        (height <= 0) || (height > TextureMaxHeight) ||
        (layers <= 0) || (layers > TextureMaxLayers))
    {
        // Invalid texture array size
        return false;
    }

    // Create image
    VkImageCreateInfo imageInfo;
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.pNext = 0;
    imageInfo.flags = 0;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
    imageInfo.extent.width = width;
    imageInfo.extent.height = height;
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = mipLevels;
    imageInfo.arrayLayers = layers;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    if (mipLevels > 1)
    {
        imageInfo.usage =
            (VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT |
            VK_IMAGE_USAGE_SAMPLED_BIT);
    }
    else
    {
        imageInfo.usage =
            (VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT);
    }
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    imageInfo.queueFamilyIndexCount = 0;
    imageInfo.pQueueFamilyIndices = 0;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    if (vkCreateImage(GVulkanDevice,
        &imageInfo, 0, &m_handle) != VK_SUCCESS)
    {
        // Could not create image
        return false;
    }
    if (!m_handle)
    {
        // Invalid image
        return false;
    }

    // Allocate texture array memory
    if (!GVulkanMemory.allocateTextureArrayMemory(*this, memoryPool))
    {
        // Could not allocate texture array memory
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
    if (mipLevels > 1)
    {
        samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    }
    samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    if (repeat == TEXTUREMODE_REPEAT)
    {
        samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    }
    else if (repeat == TEXTUREMODE_MIRROR)
    {
        samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
        samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
    }
    samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerInfo.mipLodBias = 0.0f;
    samplerInfo.anisotropyEnable = VK_FALSE;
    samplerInfo.maxAnisotropy = 1.0f;
    samplerInfo.compareEnable = VK_FALSE;
    samplerInfo.compareOp = VK_COMPARE_OP_NEVER;
    samplerInfo.minLod = 0.0f;
    samplerInfo.maxLod = 0.0f;
    if (mipLevels > 1)
    {
        samplerInfo.maxLod = (mipLevels*1.0f);
    }
    samplerInfo.borderColor = VK_BORDER_COLOR_INT_TRANSPARENT_BLACK;
    samplerInfo.unnormalizedCoordinates = VK_FALSE;

    if (vkCreateSampler(GVulkanDevice,
        &samplerInfo, 0, &m_sampler) != VK_SUCCESS)
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
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D_ARRAY;
    viewInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
    viewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    viewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    viewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    viewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = mipLevels;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = layers;

    if (vkCreateImageView(GVulkanDevice,
        &viewInfo, 0, &m_view) != VK_SUCCESS)
    {
        // Could not create image view
        return false;
    }
    if (!m_view)
    {
        // Invalid image view
        return false;
    }

    // Create texture array descriptor sets
    VkDescriptorSetAllocateInfo descriptorInfo;
    descriptorInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    descriptorInfo.pNext = 0;
    descriptorInfo.descriptorPool = GRenderer.m_texturesDescPool;
    descriptorInfo.descriptorSetCount = RendererMaxSwapchainFrames;
    descriptorInfo.pSetLayouts = &GRenderer.m_layout.swapSetLayouts[
        DESC_TEXTURE*RendererMaxSwapchainFrames
    ];

    if (vkAllocateDescriptorSets(GVulkanDevice,
        &descriptorInfo, m_descriptorSets) != VK_SUCCESS)
    {
        // Could not allocate texture array descriptor sets
        return false;
    }

    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        // Update texture array descriptor sets
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

        vkUpdateDescriptorSets(GVulkanDevice, 1, &descriptorWrites, 0, 0);
    }

    // Set texture array size
    m_width = width;
    m_height = height;
    m_layers = layers;

    // Texture array successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Update texture array                                                      //
//  return : True if texture array is successfully updated                    //
////////////////////////////////////////////////////////////////////////////////
bool TextureArray::updateTextureArray(
    TextureLoader& loader, VulkanMemoryPool memoryPool,
    uint32_t width, uint32_t height, uint32_t layers, const unsigned char* data,
    bool mipmaps, bool smooth, TextureRepeatMode repeat)
{
    // Check texture array size
    if ((width <= 0) || (width > TextureMaxWidth) ||
        (height <= 0) || (height > TextureMaxHeight))
    {
        // Invalid texture array size
        return false;
    }

    // Check texture array data
    if (!data)
    {
        // Invalid texture array data
        return false;
    }

    // Set mip levels
    uint32_t mipLevels = 1;
    if (mipmaps)
    {
        mipLevels = (Math::log2(((width > height) ? width : height)) + 1);
    }
    if (mipLevels <= 1) { mipLevels = 1; }

    // Check current texture array
    if (!m_handle ||
        (width != m_width) || (height != m_height) || (layers != m_layers))
    {
        // Recreate texture array
        destroyTextureArray();
        createTextureArray(
            memoryPool, width, height, layers,
            mipLevels, smooth, repeat
        );
    }

    // Upload texture array to graphics memory
    if (!loader.uploadTextureArray(
        m_handle, width, height, layers, mipLevels, data))
    {
        // Could not upload texture array to graphics memory
        return false;
    }

    // Texture array successfully updated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Bind texture array                                                        //
////////////////////////////////////////////////////////////////////////////////
void TextureArray::bind()
{
    // Bind texture array descriptor set
    vkCmdBindDescriptorSets(
        GRenderer.m_swapchain.commandBuffers[GRenderer.m_swapchain.current],
        VK_PIPELINE_BIND_POINT_GRAPHICS, GRenderer.m_layout.handle,
        DESC_TEXTURE, 1, &m_descriptorSets[GRenderer.m_swapchain.current], 0, 0
    );
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy texture array                                                     //
////////////////////////////////////////////////////////////////////////////////
void TextureArray::destroyTextureArray()
{
    // Check Vulkan device
    if (!GVulkanDevice)
    {
        // Invalid Vulkan device
        return;
    }

    // Destroy descriptor sets
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        m_descriptorSets[i] = 0;
    }

    // Destroy image view
    if (m_view)
    {
        vkDestroyImageView(GVulkanDevice, m_view, 0);
    }
    m_view = 0;

    // Destroy image sampler
    if (m_sampler)
    {
        vkDestroySampler(GVulkanDevice, m_sampler, 0);
    }
    m_sampler = 0;

    // Destroy image
    if (m_handle)
    {
        vkDestroyImage(GVulkanDevice, m_handle, 0);
    }
    m_handle = 0;

    m_layers = 0;
    m_height = 0;
    m_width = 0;
    m_memoryOffset = 0;
    m_memorySize = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Check if the texture array has a valid handle                             //
//  return : True if the texture array is valid                               //
////////////////////////////////////////////////////////////////////////////////
bool TextureArray::isValid()
{
    return m_handle;
}

////////////////////////////////////////////////////////////////////////////////
//  Get texture array memory requirements                                     //
////////////////////////////////////////////////////////////////////////////////
void TextureArray::getMemoryRequirements(
    VkMemoryRequirements* memoryRequirements)
{
    vkGetImageMemoryRequirements(GVulkanDevice, m_handle, memoryRequirements);
}

////////////////////////////////////////////////////////////////////////////////
//  Bind texture array memory                                                 //
//  return : True if texture array memory is successfully binded              //
////////////////////////////////////////////////////////////////////////////////
bool TextureArray::bindTextureArrayMemory(VkDeviceMemory& deviceMemory,
    VkDeviceSize size, VkDeviceSize offset)
{
    // Bind texture array memory
    if (vkBindImageMemory(GVulkanDevice,
        m_handle, deviceMemory, offset) != VK_SUCCESS)
    {
        // Could not bind texture array memory
        return false;
    }

    // Texture array memory successfully binded
    m_memorySize = size;
    m_memoryOffset = offset;
    return true;
}
