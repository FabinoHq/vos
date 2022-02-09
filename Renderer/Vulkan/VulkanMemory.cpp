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
//     Renderer/Vulkan/VulkanMemory.cpp : Vulkan memory management            //
////////////////////////////////////////////////////////////////////////////////
#include "VulkanMemory.h"
#include "VulkanBuffer.h"
#include "../Texture.h"
#include "../CubeMap.h"


////////////////////////////////////////////////////////////////////////////////
//  VulkanMemory default constructor                                          //
////////////////////////////////////////////////////////////////////////////////
VulkanMemory::VulkanMemory() :
m_memoryReady(false),
m_deviceMemoryIndex(0),
m_hostMemoryIndex(0),
m_maxAllocationCount(0),
m_memoryAlignment(0),
m_swapchainMemory(0),
m_swapchainMemoryOffset(0),
m_deviceMemory(0),
m_deviceMemoryOffset(0),
m_hostMemory(0),
m_hostMemoryOffset(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  VulkanMemory destructor                                                   //
////////////////////////////////////////////////////////////////////////////////
VulkanMemory::~VulkanMemory()
{
    m_hostMemoryOffset = 0;
    m_hostMemory = 0;
    m_deviceMemoryOffset = 0;
    m_deviceMemory = 0;
    m_swapchainMemoryOffset = 0;
    m_swapchainMemory = 0;
    m_memoryAlignment = 0;
    m_maxAllocationCount = 0;
    m_hostMemoryIndex = 0;
    m_deviceMemoryIndex = 0;
    m_memoryReady = false;
}


////////////////////////////////////////////////////////////////////////////////
//  Init Vulkan memory                                                        //
//  return : True if Vulkan memory is ready                                   //
////////////////////////////////////////////////////////////////////////////////
bool VulkanMemory::init(VkPhysicalDevice& physicalDevice,
    VkDevice& vulkanDevice)
{
    // Init Vulkan memory
    m_memoryReady = false;

    // Check physical device
    if (!physicalDevice)
    {
        // Invalid physical device
        SysMessage::box() << "[0x3101] Invalid physical device\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Get physical device properties
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
    m_maxAllocationCount = deviceProperties.limits.maxMemoryAllocationCount;

    // Set memory alignment
    m_memoryAlignment = deviceProperties.limits.minMemoryMapAlignment;
    if (deviceProperties.limits.nonCoherentAtomSize >= m_memoryAlignment)
    {
        m_memoryAlignment = deviceProperties.limits.nonCoherentAtomSize;
        if ((m_memoryAlignment %
            deviceProperties.limits.minMemoryMapAlignment) != 0)
        {
            // Invalid memory alignment
            SysMessage::box() << "[0x3102] Invalid memory alignment\n";
            SysMessage::box() << "Please update your graphics drivers";
            return false;
        }
    }
    else
    {
        if ((m_memoryAlignment %
            deviceProperties.limits.nonCoherentAtomSize) != 0)
        {
            // Invalid memory alignment
            SysMessage::box() << "[0x3103] Invalid memory alignment\n";
            SysMessage::box() << "Please update your graphics drivers";
            return false;
        }
    }

    // Check maximum allocation count
    if (m_maxAllocationCount <= 0)
    {
        // Invalid maximum allocation count
        SysMessage::box() << "[0x3104] Invalid maximum allocation count\n";
        SysMessage::box() << "Please update your graphics drivers";
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
        SysMessage::box() << "[0x3105] No physical memory type\n";
        SysMessage::box() << "Please update your graphics drivers";
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
        SysMessage::box() << "[0x3106] Could not find all memory types\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Allocate swapchain memory
    VkMemoryAllocateInfo allocateInfo;
    allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocateInfo.pNext = 0;
    allocateInfo.allocationSize = 16777216;
    allocateInfo.memoryTypeIndex = m_deviceMemoryIndex;

    if (vkAllocateMemory(
        vulkanDevice, &allocateInfo, 0, &m_swapchainMemory) != VK_SUCCESS)
    {
        // Could not allocate device memory
        SysMessage::box() << "[0x3107] Could not allocate swapchain memory\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Allocate device memory
    allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocateInfo.pNext = 0;
    allocateInfo.allocationSize = 268435456;
    allocateInfo.memoryTypeIndex = m_deviceMemoryIndex;

    if (vkAllocateMemory(
        vulkanDevice, &allocateInfo, 0, &m_deviceMemory) != VK_SUCCESS)
    {
        // Could not allocate device memory
        SysMessage::box() << "[0x3107] Could not allocate device memory\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Allocate host memory
    allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocateInfo.pNext = 0;
    allocateInfo.allocationSize = 268435456;
    allocateInfo.memoryTypeIndex = m_hostMemoryIndex;

    if (vkAllocateMemory(
        vulkanDevice, &allocateInfo, 0, &m_hostMemory) != VK_SUCCESS)
    {
        // Could not allocate host memory
        SysMessage::box() << "[0x3108] Could not allocate host memory\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Vulkan memory is ready
    m_memoryReady = true;
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Cleanup Vulkan memory                                                     //
////////////////////////////////////////////////////////////////////////////////
void VulkanMemory::cleanup(VkDevice& vulkanDevice)
{
    if (m_memoryReady && vulkanDevice)
    {
        if (m_hostMemory)
        {
            vkFreeMemory(vulkanDevice, m_hostMemory, 0);
        }

        if (m_deviceMemory)
        {
            vkFreeMemory(vulkanDevice, m_deviceMemory, 0);
        }

        if (m_swapchainMemory)
        {
            vkFreeMemory(vulkanDevice, m_swapchainMemory, 0);
        }
    }

    m_hostMemoryOffset = 0;
    m_hostMemory = 0;
    m_deviceMemoryOffset = 0;
    m_deviceMemory = 0;
    m_swapchainMemoryOffset = 0;
    m_swapchainMemory = 0;
    m_memoryAlignment = 0;
    m_maxAllocationCount = 0;
    m_hostMemoryIndex = 0;
    m_deviceMemoryIndex = 0;
    m_memoryReady = false;
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

    if (memoryType == VULKAN_MEMORY_DEVICE)
    {
        // Check memory type bits
        if (!(memoryRequirements.memoryTypeBits & (1 << m_deviceMemoryIndex)))
        {
            // Invalid memory type bits
            return false;
        }

        // Compute memory alignment
        VkDeviceSize size = memoryRequirements.size;
        VkDeviceSize alignment = m_memoryAlignment;
        if (memoryRequirements.alignment >= alignment)
        {
            alignment = memoryRequirements.alignment;
            if ((alignment % m_memoryAlignment) != 0)
            {
                // Invalid memory alignment
                return false;
            }
        }
        else
        {
            if ((alignment % memoryRequirements.alignment) != 0)
            {
                // Invalid memory alignment
                return false;
            }
        }

        // Adjust memory size according to alignment
        VkDeviceSize sizeOffset = (size % alignment);
        if (sizeOffset != 0)
        {
            size += (alignment - sizeOffset);
        }

        // Adjust memory start offset according to alignment
        VkDeviceSize startOffset = (m_deviceMemoryOffset % alignment);
        if (startOffset != 0)
        {
            m_deviceMemoryOffset += (alignment - startOffset);
        }

        // Set buffer memory size and offset
        buffer.memorySize = size;
        buffer.memoryOffset = m_deviceMemoryOffset;

        // Bind buffer memory
        if (vkBindBufferMemory(vulkanDevice,
            buffer.handle, m_deviceMemory, buffer.memoryOffset) != VK_SUCCESS)
        {
            // Could not bind buffer memory
            return false;
        }

        // Update current memory offset
        m_deviceMemoryOffset += size;
    }
    else
    {
        // Check memory type bits
        if (!(memoryRequirements.memoryTypeBits & (1 << m_hostMemoryIndex)))
        {
            // Invalid memory type bits
            return false;
        }

        // Compute memory alignment
        VkDeviceSize size = memoryRequirements.size;
        VkDeviceSize alignment = m_memoryAlignment;
        if (memoryRequirements.alignment >= alignment)
        {
            alignment = memoryRequirements.alignment;
            if ((alignment % m_memoryAlignment) != 0)
            {
                // Invalid memory alignment
                return false;
            }
        }
        else
        {
            if ((alignment % memoryRequirements.alignment) != 0)
            {
                // Invalid memory alignment
                return false;
            }
        }

        // Adjust memory size according to alignment
        VkDeviceSize sizeOffset = (size % alignment);
        if (sizeOffset != 0)
        {
            size += (alignment - sizeOffset);
        }

        // Adjust memory start offset according to alignment
        VkDeviceSize startOffset = (m_hostMemoryOffset % alignment);
        if (startOffset != 0)
        {
            m_hostMemoryOffset += (alignment - startOffset);
        }

        // Set buffer memory size and offset
        buffer.memorySize = size;
        buffer.memoryOffset = m_hostMemoryOffset;

        // Bind buffer memory
        if (vkBindBufferMemory(vulkanDevice,
            buffer.handle, m_hostMemory, buffer.memoryOffset) != VK_SUCCESS)
        {
            // Could not bind buffer memory
            return false;
        }

        // Update current memory offset
        m_hostMemoryOffset += size;
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
    if (vkMapMemory(vulkanDevice, m_hostMemory,
        buffer.memoryOffset, buffer.memorySize, 0, &bufferMemory) != VK_SUCCESS)
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
    memoryRange.memory = m_hostMemory;
    memoryRange.offset = buffer.memoryOffset;
    memoryRange.size = buffer.memorySize;

    if (vkFlushMappedMemoryRanges(vulkanDevice, 1, &memoryRange) != VK_SUCCESS)
    {
        // Could not flush buffer mapped memory ranges
        return false;
    }

    vkUnmapMemory(vulkanDevice, m_hostMemory);

    // Buffer memory successfully mapped
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Free buffer memory                                                        //
////////////////////////////////////////////////////////////////////////////////
void VulkanMemory::freeBufferMemory(VkDevice& vulkanDevice,
    VulkanBuffer& buffer)
{
    // Free buffer memory
    if (m_memoryReady && vulkanDevice)
    {
        //vkFreeMemory(vulkanDevice, memory, 0);
    }
}


////////////////////////////////////////////////////////////////////////////////
//  Allocate swapchain image memory                                           //
//  return : True if swapchain image is successfully allocated                //
////////////////////////////////////////////////////////////////////////////////
bool VulkanMemory::allocateSwapchainImage(VkDevice& vulkanDevice, VkImage& image)
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

    // Check image handle
    if (!image)
    {
        // Invalid image handle
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

    // Check memory type bits
    if (!(memoryRequirements.memoryTypeBits & (1 << m_deviceMemoryIndex)))
    {
        // Invalid memory type bits
        return false;
    }

    // Compute memory alignment
    VkDeviceSize size = memoryRequirements.size;
    VkDeviceSize alignment = m_memoryAlignment;
    if (memoryRequirements.alignment >= alignment)
    {
        alignment = memoryRequirements.alignment;
        if ((alignment % m_memoryAlignment) != 0)
        {
            // Invalid memory alignment
            return false;
        }
    }
    else
    {
        if ((alignment % memoryRequirements.alignment) != 0)
        {
            // Invalid memory alignment
            return false;
        }
    }

    // Adjust memory size according to alignment
    VkDeviceSize sizeOffset = (size % alignment);
    if (sizeOffset != 0)
    {
        size += (alignment - sizeOffset);
    }

    // Adjust memory start offset according to alignment
    VkDeviceSize startOffset = (m_swapchainMemoryOffset % alignment);
    if (startOffset != 0)
    {
        m_swapchainMemoryOffset += (alignment - startOffset);
    }

    // Bind image memory
    if (vkBindImageMemory(vulkanDevice,
        image, m_swapchainMemory, m_swapchainMemoryOffset) != VK_SUCCESS)
    {
        // Could not bind image memory
        return false;
    }

    // Update current memory offset
    m_swapchainMemoryOffset += size;

    // Texture memory successfully allocated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Reset swapchain image memory                                              //
////////////////////////////////////////////////////////////////////////////////
void VulkanMemory::resetSwapchainMemory()
{
    // Reset swapchain image memory
    if (m_memoryReady)
    {
        m_swapchainMemoryOffset = 0;
    }
}


////////////////////////////////////////////////////////////////////////////////
//  Allocate texture memory                                                   //
//  return : True if texture memory is successfully allocated                 //
////////////////////////////////////////////////////////////////////////////////
bool VulkanMemory::allocateTextureMemory(VkDevice& vulkanDevice,
    Texture& texture)
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

    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Get memory requirements
    VkMemoryRequirements memoryRequirements;
    texture.getMemoryRequirements(vulkanDevice, &memoryRequirements);

    // Check memory requirements size
    if (memoryRequirements.size <= 0)
    {
        // Invalid memory requirements size
        return false;
    }

    // Check memory type bits
    if (!(memoryRequirements.memoryTypeBits & (1 << m_deviceMemoryIndex)))
    {
        // Invalid memory type bits
        return false;
    }

    // Compute memory alignment
    VkDeviceSize size = memoryRequirements.size;
    VkDeviceSize alignment = m_memoryAlignment;
    if (memoryRequirements.alignment >= alignment)
    {
        alignment = memoryRequirements.alignment;
        if ((alignment % m_memoryAlignment) != 0)
        {
            // Invalid memory alignment
            return false;
        }
    }
    else
    {
        if ((alignment % memoryRequirements.alignment) != 0)
        {
            // Invalid memory alignment
            return false;
        }
    }

    // Adjust memory size according to alignment
    VkDeviceSize sizeOffset = (size % alignment);
    if (sizeOffset != 0)
    {
        size += (alignment - sizeOffset);
    }

    // Adjust memory start offset according to alignment
    VkDeviceSize startOffset = (m_deviceMemoryOffset % alignment);
    if (startOffset != 0)
    {
        m_deviceMemoryOffset += (alignment - startOffset);
    }

    // Bind texture memory
    if (!texture.bindTextureMemory(
        vulkanDevice, m_deviceMemory, size, m_deviceMemoryOffset))
    {
        // Could not bind texture memory
        return false;
    }

    // Update current memory offset
    m_deviceMemoryOffset += size;

    // Texture memory successfully allocated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Free texture memory                                                       //
////////////////////////////////////////////////////////////////////////////////
void VulkanMemory::freeTextureMemory(VkDevice& vulkanDevice, Texture& texture)
{
    // Free image memory
    if (m_memoryReady && vulkanDevice)
    {
        //vkFreeMemory(vulkanDevice, memory, 0);
    }
}


////////////////////////////////////////////////////////////////////////////////
//  Allocate cubemap memory                                                   //
//  return : True if cubemap memory is successfully allocated                 //
////////////////////////////////////////////////////////////////////////////////
bool VulkanMemory::allocateCubeMapMemory(VkDevice& vulkanDevice,
    CubeMap& cubemap)
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

    // Check cubemap handle
    if (!cubemap.isValid())
    {
        // Invalid cubemap handle
        return false;
    }

    // Get memory requirements
    VkMemoryRequirements memoryRequirements;
    cubemap.getMemoryRequirements(vulkanDevice, &memoryRequirements);

    // Check memory requirements size
    if (memoryRequirements.size <= 0)
    {
        // Invalid memory requirements size
        return false;
    }

    // Check memory type bits
    if (!(memoryRequirements.memoryTypeBits & (1 << m_deviceMemoryIndex)))
    {
        // Invalid memory type bits
        return false;
    }

    // Compute memory alignment
    VkDeviceSize size = memoryRequirements.size;
    VkDeviceSize alignment = m_memoryAlignment;
    if (memoryRequirements.alignment >= alignment)
    {
        alignment = memoryRequirements.alignment;
        if ((alignment % m_memoryAlignment) != 0)
        {
            // Invalid memory alignment
            return false;
        }
    }
    else
    {
        if ((alignment % memoryRequirements.alignment) != 0)
        {
            // Invalid memory alignment
            return false;
        }
    }

    // Adjust memory size according to alignment
    VkDeviceSize sizeOffset = (size % alignment);
    if (sizeOffset != 0)
    {
        size += (alignment - sizeOffset);
    }

    // Adjust memory start offset according to alignment
    VkDeviceSize startOffset = (m_deviceMemoryOffset % alignment);
    if (startOffset != 0)
    {
        m_deviceMemoryOffset += (alignment - startOffset);
    }

    // Bind cubemap memory
    if (!cubemap.bindCubeMapMemory(
        vulkanDevice, m_deviceMemory, size, m_deviceMemoryOffset))
    {
        // Could not bind cubemap memory
        return false;
    }

    // Update current memory offset
    m_deviceMemoryOffset += size;

    // CubeMap memory successfully allocated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Free cubemap memory                                                       //
////////////////////////////////////////////////////////////////////////////////
void VulkanMemory::freeCubeMapMemory(VkDevice& vulkanDevice, CubeMap& cubemap)
{
    // Free image memory
    if (m_memoryReady && vulkanDevice)
    {
        //vkFreeMemory(vulkanDevice, memory, 0);
    }
}
