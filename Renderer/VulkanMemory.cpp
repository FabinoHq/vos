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
//     Renderer/VulkanMemory.cpp : Vulkan memory management                   //
////////////////////////////////////////////////////////////////////////////////
#include "VulkanMemory.h"
#include "VulkanBuffer.h"


////////////////////////////////////////////////////////////////////////////////
//  VulkanMemory default constructor                                          //
////////////////////////////////////////////////////////////////////////////////
VulkanMemory::VulkanMemory() :
m_memoryReady(false),
m_deviceMemoryIndex(0),
m_hostMemoryIndex(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  VulkanMemory destructor                                                   //
////////////////////////////////////////////////////////////////////////////////
VulkanMemory::~VulkanMemory()
{
    m_hostMemoryIndex = 0;
    m_deviceMemoryIndex = 0;
    m_memoryReady = false;
}


////////////////////////////////////////////////////////////////////////////////
//  Init Vulkan memory                                                        //
//  return : True if Vulkan memory is ready                                   //
////////////////////////////////////////////////////////////////////////////////
bool VulkanMemory::init(VkPhysicalDevice& physicalDevice)
{
    // Init Vulkan memory
    m_memoryReady = false;

    // Check physical device
    if (!physicalDevice)
    {
        // Invalid physical device
        return false;
    }

    // Check memory functions
    if (!vkGetPhysicalDeviceMemoryProperties ||
        !vkGetBufferMemoryRequirements || !vkGetImageMemoryRequirements ||
        !vkAllocateMemory || !vkFreeMemory ||
        !vkBindBufferMemory || !vkBindImageMemory)
    {
        // Invalid memory functions
        return false;
    }

    // Get physical device memory properties
    VkPhysicalDeviceMemoryProperties physicalMemoryProperties;
    vkGetPhysicalDeviceMemoryProperties(
        physicalDevice, &physicalMemoryProperties
    );

    // Check physical memory types
    if (physicalMemoryProperties.memoryTypeCount <= 0)
    {
        // No physical memory type
        return false;
    }

    bool deviceMemoryFound = false;
    bool hostMemoryFound = false;
    for (uint32_t i = 0; i < physicalMemoryProperties.memoryTypeCount; ++i)
    {
        // Device local memory type
        if (physicalMemoryProperties.memoryTypes[i].propertyFlags &
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
        {
            if (!deviceMemoryFound)
            {
                m_deviceMemoryIndex = i;
                deviceMemoryFound = true;
            }
        }

        // Host memory type
        if (physicalMemoryProperties.memoryTypes[i].propertyFlags &
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
        {
            if (!hostMemoryFound)
            {
                m_hostMemoryIndex = i;
                hostMemoryFound = true;
            }
        }

        // All memory types found
        if (deviceMemoryFound && hostMemoryFound)
        {
            break;
        }
    }

    // Check if all memory types are found
    if (!deviceMemoryFound || !hostMemoryFound)
    {
        // Could not find all memory types
        return false;
    }

    // Vulkan memory is ready
    m_memoryReady = true;
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Allocate buffer memory                                                    //
//  return : True if buffer memory is successfully allocated                  //
////////////////////////////////////////////////////////////////////////////////
bool VulkanMemory::allocateBufferMemory(VkDevice& vulkanDevice,
    VulkanBuffer& buffer, VulkanMemoryType memoryType)
{
    // Check Vulkan memory
    if (!m_memoryReady)
    {
        // Vulkan memory is not ready
        return false;
    }

    // Check Vulkan device
    if (!vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Check buffer handle
    if (!buffer.handle)
    {
        // Invalid buffer handle
        return false;
    }

    // Get memory requirements
    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(
        vulkanDevice, buffer.handle, &memoryRequirements
    );

    // Check memory requirements size
    if (memoryRequirements.size <= 0)
    {
        // Invalid memory requirements size
        return false;
    }

    // Allocate buffer memory
    VkMemoryAllocateInfo allocateInfo;
    allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocateInfo.pNext = 0;
    allocateInfo.allocationSize = memoryRequirements.size;

    // Set memory type index
    if (memoryType == VULKAN_MEMORY_DEVICE)
    {
        allocateInfo.memoryTypeIndex = m_deviceMemoryIndex;
    }
    else
    {
        allocateInfo.memoryTypeIndex = m_hostMemoryIndex;
    }

    // Check memory type bits
    if (!(memoryRequirements.memoryTypeBits &
        (1 << allocateInfo.memoryTypeIndex)))
    {
        // Invalid memory type bits
        return false;
    }

    if (vkAllocateMemory(
        vulkanDevice, &allocateInfo, 0, &buffer.memory) != VK_SUCCESS)
    {
        // Could not allocate buffer memory
        return false;
    }

    // Bind buffer memory
    if (vkBindBufferMemory(
        vulkanDevice, buffer.handle, buffer.memory, 0) != VK_SUCCESS)
    {
        // Could not bind buffer memory
        return false;
    }

    // Buffer memory successfully allocated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Write buffer memory                                                       //
//  return : True if buffer memory is successfully written                    //
////////////////////////////////////////////////////////////////////////////////
bool VulkanMemory::writeBufferMemory(VkDevice& vulkanDevice,
    VulkanBuffer& buffer, const void* data)
{
    // Check Vulkan memory
    if (!m_memoryReady)
    {
        // Vulkan memory is not ready
        return false;
    }

    // Check Vulkan device
    if (!vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Check buffer handle
    if (!buffer.handle)
    {
        // Invalid buffer handle
        return false;
    }

    // Check data
    if (!data || (buffer.size <= 0))
    {
        // Invalid data
        return false;
    }

    // Map buffer memory
    void* bufferMemory = 0;
    if (vkMapMemory(vulkanDevice,
        buffer.memory, 0, buffer.size, 0, &bufferMemory) != VK_SUCCESS)
    {
        // Could not map buffer memory
        return false;
    }
    if (!bufferMemory)
    {
        // Invalid buffer memory
        return false;
    }

    // Copy data into buffer memory
    memcpy(bufferMemory, data, buffer.size);

    // Unmap buffer memory
    VkMappedMemoryRange memoryRange;
    memoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
    memoryRange.pNext = 0;
    memoryRange.memory = buffer.memory;
    memoryRange.offset = 0;
    memoryRange.size = VK_WHOLE_SIZE;

    if (vkFlushMappedMemoryRanges(vulkanDevice, 1, &memoryRange) != VK_SUCCESS)
    {
        // Could not flush buffer mapped memory ranges
        return false;
    }

    vkUnmapMemory(vulkanDevice, buffer.memory);

    // Buffer memory successfully mapped
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Free buffer memory                                                        //
////////////////////////////////////////////////////////////////////////////////
void VulkanMemory::freeBufferMemory(VkDevice& vulkanDevice,
    VkDeviceMemory& memory)
{
    // Free buffer memory
    if (m_memoryReady && vulkanDevice && memory)
    {
        vkFreeMemory(vulkanDevice, memory, 0);
    }
    memory = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Allocate image memory                                                     //
//  return : True if image memory is successfully allocated                   //
////////////////////////////////////////////////////////////////////////////////
bool VulkanMemory::allocateImageMemory(VkDevice& vulkanDevice,
    VkImage& image, VkDeviceMemory& memory)
{
    // Check Vulkan memory
    if (!m_memoryReady)
    {
        // Vulkan memory is not ready
        return false;
    }

    // Check Vulkan device
    if (!vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Check image
    if (!image)
    {
        // Invalid image
        return false;
    }

    // Get memory requirements
    VkMemoryRequirements memoryRequirements;
    vkGetImageMemoryRequirements(vulkanDevice, image, &memoryRequirements);

    // Check memory requirements size
    if (memoryRequirements.size <= 0)
    {
        // Invalid memory requirements size
        return false;
    }

    // Allocate image memory
    VkMemoryAllocateInfo allocateInfo;
    allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocateInfo.pNext = 0;
    allocateInfo.allocationSize = memoryRequirements.size;
    allocateInfo.memoryTypeIndex = m_deviceMemoryIndex;

    // Check memory type bits
    if (!(memoryRequirements.memoryTypeBits &
        (1 << allocateInfo.memoryTypeIndex)))
    {
        // Invalid memory type bits
        return false;
    }

    if (vkAllocateMemory(vulkanDevice, &allocateInfo, 0, &memory) != VK_SUCCESS)
    {
        // Could not allocate image memory
        return false;
    }

    // Bind image memory
    if (vkBindImageMemory(vulkanDevice, image, memory, 0) != VK_SUCCESS)
    {
        // Could not bind image memory
        return false;
    }

    // Image memory successfully allocated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Free image memory                                                         //
////////////////////////////////////////////////////////////////////////////////
void VulkanMemory::freeImageMemory(VkDevice& vulkanDevice,
    VkDeviceMemory& memory)
{
    // Free image memory
    if (m_memoryReady && vulkanDevice && memory)
    {
        vkFreeMemory(vulkanDevice, memory, 0);
    }
    memory = 0;
}
