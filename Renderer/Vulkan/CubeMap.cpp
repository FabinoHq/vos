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
#include "../../Resources/Resources.h"


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
//  Init cubemap                                                              //
////////////////////////////////////////////////////////////////////////////////
void CubeMap::init()
{
    m_handle = 0;
    m_sampler = 0;
    m_view = 0;
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        m_descriptorSets[i] = 0;
    }
    m_memorySize = 0;
    m_memoryOffset = 0;
    m_width = 0;
    m_height = 0;
}

////////////////////////////////////////////////////////////////////////////////
//  Create cubemap                                                            //
//  return : True if cubemap is successfully created                          //
////////////////////////////////////////////////////////////////////////////////
bool CubeMap::createCubeMap(VulkanMemoryPool memoryPool,
    uint32_t width, uint32_t height, const unsigned char* data, bool smooth)
{
    // Check cubemap handle
    if (m_handle)
    {
        // Destroy current cubemap
        destroyCubeMap();
    }

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

    if (vkCreateImage(GVulkanDevice, &imageInfo,
        SYSVKMEMORY_IMAGE_ALLOC, &m_handle) != VK_SUCCESS)
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
    if (!GVulkanMemory.allocateCubeMapMemory(*this, memoryPool))
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
    switch (GSysSettings.getAnisotropicFilteringMode())
    {
        case ANISOTROPIC_FILTERING_2X:
            samplerInfo.anisotropyEnable = VK_TRUE;
            samplerInfo.maxAnisotropy = 2.0f;
            break;
        case ANISOTROPIC_FILTERING_4X:
            samplerInfo.anisotropyEnable = VK_TRUE;
            samplerInfo.maxAnisotropy = 4.0f;
            break;
        case ANISOTROPIC_FILTERING_8X:
            samplerInfo.anisotropyEnable = VK_TRUE;
            samplerInfo.maxAnisotropy = 8.0f;
            break;
        case ANISOTROPIC_FILTERING_16X:
            samplerInfo.anisotropyEnable = VK_TRUE;
            samplerInfo.maxAnisotropy = 16.0f;
            break;
        default:
            samplerInfo.anisotropyEnable = VK_FALSE;
            samplerInfo.maxAnisotropy = 1.0f;
            break;
    }
    samplerInfo.compareEnable = VK_FALSE;
    samplerInfo.compareOp = VK_COMPARE_OP_NEVER;
    samplerInfo.minLod = 0.0f;
    samplerInfo.maxLod = 0.0f;
    samplerInfo.borderColor = VK_BORDER_COLOR_INT_TRANSPARENT_BLACK;
    samplerInfo.unnormalizedCoordinates = VK_FALSE;

    if (vkCreateSampler(GVulkanDevice, &samplerInfo,
        SYSVKMEMORY_SAMPLER_ALLOC, &m_sampler) != VK_SUCCESS)
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

    if (vkCreateImageView(GVulkanDevice, &viewInfo,
        SYSVKMEMORY_IMAGEVIEW_ALLOC, &m_view) != VK_SUCCESS)
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
    descriptorInfo.descriptorPool = GGraphicsLayout.texturesDescPool;
    descriptorInfo.descriptorSetCount = RendererMaxSwapchainFrames;
    descriptorInfo.pSetLayouts = &GGraphicsLayout.swapSetLayouts[
        DESC_TEXTURE*RendererMaxSwapchainFrames
    ];

    if (vkAllocateDescriptorSets(GVulkanDevice,
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

        vkUpdateDescriptorSets(GVulkanDevice, 1, &descriptorWrites, 0, 0);
    }

    // Upload cubemap to graphics memory
    if (!GResources.textures.uploadCubeMap(m_handle, width, height, data))
    {
        // Could not upload cubemap to graphics memory
        return false;
    }

    // Set cubemap size
    m_width = width;
    m_height = height;

    // CubeMap successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy cubemap                                                           //
////////////////////////////////////////////////////////////////////////////////
void CubeMap::destroyCubeMap()
{
    // Check Vulkan device
    if (!GVulkanDevice)
    {
        // Invalid Vulkan device
        return;
    }

    // Destroy image view
    if (m_view)
    {
        vkDestroyImageView(GVulkanDevice, m_view, SYSVKMEMORY_IMAGEVIEW_ALLOC);
    }
    m_view = 0;

    // Destroy image sampler
    if (m_sampler)
    {
        vkDestroySampler(GVulkanDevice, m_sampler, SYSVKMEMORY_SAMPLER_ALLOC);
    }
    m_sampler = 0;

    // Destroy image
    if (m_handle)
    {
        vkDestroyImage(GVulkanDevice, m_handle, SYSVKMEMORY_IMAGE_ALLOC);
    }
    m_handle = 0;

    // Destroy descriptor sets
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        m_descriptorSets[i] = 0;
    }

    m_height = 0;
    m_width = 0;
    m_memoryOffset = 0;
    m_memorySize = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Bind cubemap memory                                                       //
//  return : True if cubemap memory is successfully binded                    //
////////////////////////////////////////////////////////////////////////////////
bool CubeMap::bindCubeMapMemory(VkDeviceMemory& deviceMemory,
    VkDeviceSize size, VkDeviceSize offset)
{
    // Bind cubemap memory
    if (vkBindImageMemory(GVulkanDevice,
        m_handle, deviceMemory, offset) != VK_SUCCESS)
    {
        // Could not bind cubemap memory
        return false;
    }

    // CubeMap memory successfully binded
    m_memorySize = size;
    m_memoryOffset = offset;
    return true;
}
