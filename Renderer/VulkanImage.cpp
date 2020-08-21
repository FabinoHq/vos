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
//     Renderer/VulkanImage.cpp : Vulkan Image management                     //
////////////////////////////////////////////////////////////////////////////////
#include "VulkanImage.h"


////////////////////////////////////////////////////////////////////////////////
//  VulkanImage default constructor                                           //
////////////////////////////////////////////////////////////////////////////////
VulkanImage::VulkanImage() :
handle(0),
memory(0),
sampler(0),
view(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  VulkanImage destructor                                                    //
////////////////////////////////////////////////////////////////////////////////
VulkanImage::~VulkanImage()
{
    view = 0;
    sampler = 0;
    memory = 0;
    handle = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Create Vulkan Image                                                       //
//  return : True if Vulkan Image is successfully created                     //
////////////////////////////////////////////////////////////////////////////////
bool VulkanImage::createImage(VkPhysicalDevice& physicalDevice,
    VkDevice& vulkanDevice, uint32_t width, uint32_t height)
{
    // Check image size
    if (width == 0 || height == 0)
    {
        // Invalid image size
        return false;
    }

    // Check image handle
    if (handle)
    {
        // Destroy Vulkan Image
        destroyImage(vulkanDevice);
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
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    imageInfo.usage =
        VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    imageInfo.queueFamilyIndexCount = 0;
    imageInfo.pQueueFamilyIndices = 0;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    if (vkCreateImage(vulkanDevice, &imageInfo, 0, &handle) != VK_SUCCESS)
    {
        // Could not create image
        return false;
    }
    if (!handle)
    {
        // Invalid image
        return false;
    }

    // Get memory requirements
    VkMemoryRequirements memoryRequirements;
    vkGetImageMemoryRequirements(vulkanDevice, handle, &memoryRequirements);

    // Get physical device memory properties
    VkPhysicalDeviceMemoryProperties memoryProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);

    // Allocate buffer memory
    bool memoryAllocated = false;
    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; ++i)
    {
        if (memoryRequirements.memoryTypeBits & (1 << i))
        {
            if (memoryProperties.memoryTypes[i].propertyFlags &
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
            {
                VkMemoryAllocateInfo allocateInfo;
                allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
                allocateInfo.pNext = 0;
                allocateInfo.allocationSize = memoryRequirements.size;
                allocateInfo.memoryTypeIndex = i;

                if (vkAllocateMemory(
                    vulkanDevice, &allocateInfo, 0, &memory) == VK_SUCCESS)
                {
                    memoryAllocated = true;
                    break;
                }
            }
        }
    }
    if (!memoryAllocated)
    {
        // Could not allocate buffer memory
        return false;
    }

    // Bind image memory
    if (vkBindImageMemory(vulkanDevice, handle, memory, 0) != VK_SUCCESS)
    {
        // Could not bind image memory
        return false;
    }

    // Vulkan Image successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy Vulkan Image                                                      //
////////////////////////////////////////////////////////////////////////////////
void VulkanImage::destroyImage(VkDevice& vulkanDevice)
{
    // Destroy image view
    if (view && vkDestroyImageView)
    {
        vkDestroyImageView(vulkanDevice, view, 0);
    }
    view = 0;

    // Destroy image sampler
    if (sampler && vkDestroySampler)
    {
        vkDestroySampler(vulkanDevice, sampler, 0);
    }
    sampler = 0;

    // Free image memory
    if (memory && vkFreeMemory)
    {
        vkFreeMemory(vulkanDevice, memory, 0);
    }
    memory = 0;

    // Destroy image
    if (handle && vkDestroyImage)
    {
        vkDestroyImage(vulkanDevice, handle, 0);
    }
    handle = 0;
}
