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
//     Renderer/Vulkan/VulkanMemory.cpp : Vulkan memory management            //
////////////////////////////////////////////////////////////////////////////////
#include "VulkanMemory.h"
#include "VulkanBuffer.h"
#include "Texture.h"
#include "TextureArray.h"
#include "CubeMap.h"


////////////////////////////////////////////////////////////////////////////////
//  VulkanMemory default constructor                                          //
////////////////////////////////////////////////////////////////////////////////
VulkanMemory::VulkanMemory() :
m_deviceMemoryIndex(0),
m_hostMemoryIndex(0),
m_maxAllocationCount(0),
m_memoryAlignment(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  VulkanMemory destructor                                                   //
////////////////////////////////////////////////////////////////////////////////
VulkanMemory::~VulkanMemory()
{
    m_memoryAlignment = 0;
    m_maxAllocationCount = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Init Vulkan memory                                                        //
//  return : True if Vulkan memory is ready                                   //
////////////////////////////////////////////////////////////////////////////////
bool VulkanMemory::init(VkPhysicalDevice& physicalDevice,
    VkDevice& vulkanDevice)
{
    // Check physical device
    if (!physicalDevice)
    {
        // Invalid physical device
        SysMessage::box() << "[0x3101] Invalid physical device\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Reset memory arrays
    for (int i = 0; i < VULKAN_MEMORY_POOLSCOUNT; ++i)
    {
        m_memory[i] = 0;
        m_offset[i] = 0;
        m_index[i] = 0;
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
    if (m_maxAllocationCount < VULKAN_MEMORY_POOLSCOUNT)
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
        SysMessage::box() << "[0x3105] No physical memory types\n";
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

    // Allocate memory pools
    for (int i = 0; i < VULKAN_MEMORY_POOLSCOUNT; ++i)
    {
        // Check memory pool index
        if (VulkanMemoryArray[i].pool != i)
        {
            // Invalid memory pool index
            SysMessage::box() << "[0x3107] Invalid memory pool index\n";
            SysMessage::box() << "Please update your graphics drivers";
            return false;
        }

        // Check memory pool size
        if (VulkanMemoryArray[i].size <= 0) { continue; }

        // Check memory pool type
        if (VulkanMemoryArray[i].type == VULKAN_MEMORY_DEVICE)
        {
            m_index[i] = m_deviceMemoryIndex;
        }
        else if (VulkanMemoryArray[i].type == VULKAN_MEMORY_HOST)
        {
            m_index[i] = m_hostMemoryIndex;
        }
        else
        {
            // Invalid memory pool type
            SysMessage::box() << "[0x3108] Invalid memory pool type\n";
            SysMessage::box() << "Please update your graphics drivers";
            return false;
        }

        // Allocate Vulkan memory
        VkMemoryAllocateInfo allocateInfo;
        allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocateInfo.pNext = 0;
        allocateInfo.allocationSize = VulkanMemoryArray[i].size;
        allocateInfo.memoryTypeIndex = m_index[i];

        if (vkAllocateMemory(vulkanDevice,
            &allocateInfo, 0, &m_memory[i]) != VK_SUCCESS)
        {
            // Could not allocate device memory pool
            SysMessage::box() << "[0x3109] Could not allocate memory pool\n";
            SysMessage::box() << "Please update your graphics drivers";
            return false;
        }
    }

    // Vulkan memory is ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy Vulkan memory                                                     //
////////////////////////////////////////////////////////////////////////////////
void VulkanMemory::destroyVulkanMemory(VkDevice& vulkanDevice)
{
    if (vulkanDevice)
    {
        for (int i = 0; i < VULKAN_MEMORY_POOLSCOUNT; ++i)
        {
            if (m_memory[i])
            {
                vkFreeMemory(vulkanDevice, m_memory[i], 0);
            }
        }
    }

    m_memoryAlignment = 0;
    m_maxAllocationCount = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Allocate swapchain image memory                                           //
//  return : True if swapchain image is successfully allocated                //
////////////////////////////////////////////////////////////////////////////////
bool VulkanMemory::allocateSwapchainImage(VkDevice& vulkanDevice,
    VkImage& image, VulkanMemoryPool memoryPool)
{
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
    VkDeviceSize startOffset = (m_offset[memoryPool] % alignment);
    if (startOffset != 0)
    {
        m_offset[memoryPool] += (alignment - startOffset);
    }

    // Bind image memory
    if (vkBindImageMemory(vulkanDevice, image,
        m_memory[memoryPool], m_offset[memoryPool]) != VK_SUCCESS)
    {
        // Could not bind image memory
        return false;
    }

    // Update current memory offset
    m_offset[memoryPool] += size;

    // Swapchain image successfully allocated
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Allocate buffer memory                                                    //
//  return : True if buffer memory is successfully allocated                  //
////////////////////////////////////////////////////////////////////////////////
bool VulkanMemory::allocateBufferMemory(VkDevice& vulkanDevice,
    VulkanBuffer& buffer, VulkanMemoryPool memoryPool)
{
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

    // Check memory type bits
    if (!(memoryRequirements.memoryTypeBits & (1 << m_index[memoryPool])))
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
    VkDeviceSize startOffset = (m_offset[memoryPool] % alignment);
    if (startOffset != 0)
    {
        m_offset[memoryPool] += (alignment - startOffset);
    }

    // Set buffer memory size and offset
    buffer.memorySize = size;
    buffer.memoryOffset = m_offset[memoryPool];

    // Bind buffer memory
    if (vkBindBufferMemory(vulkanDevice, buffer.handle,
        m_memory[memoryPool], buffer.memoryOffset) != VK_SUCCESS)
    {
        // Could not bind buffer memory
        return false;
    }

    // Update current memory offset
    m_offset[memoryPool] += size;

    // Buffer memory successfully allocated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Write buffer memory                                                       //
//  return : True if buffer memory is successfully written                    //
////////////////////////////////////////////////////////////////////////////////
bool VulkanMemory::writeBufferMemory(VkDevice& vulkanDevice,
    VulkanBuffer& buffer, const void* data, VulkanMemoryPool memoryPool)
{
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

    // Check memory type
    if (m_index[memoryPool] != m_hostMemoryIndex)
    {
        // Invalid memory type
        return false;
    }

    // Map buffer memory
    void* bufferMemory = 0;
    if (vkMapMemory(vulkanDevice, m_memory[memoryPool],
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
    memoryRange.memory = m_memory[memoryPool];
    memoryRange.offset = buffer.memoryOffset;
    memoryRange.size = buffer.memorySize;

    if (vkFlushMappedMemoryRanges(vulkanDevice, 1, &memoryRange) != VK_SUCCESS)
    {
        // Could not flush buffer mapped memory ranges
        return false;
    }

    vkUnmapMemory(vulkanDevice, m_memory[memoryPool]);

    // Buffer memory successfully mapped
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Allocate texture memory                                                   //
//  return : True if texture memory is successfully allocated                 //
////////////////////////////////////////////////////////////////////////////////
bool VulkanMemory::allocateTextureMemory(VkDevice& vulkanDevice,
    Texture& texture, VulkanMemoryPool memoryPool)
{
    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Check memory type
    if (m_index[memoryPool] != m_deviceMemoryIndex)
    {
        // Invalid memory type
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
    if (!(memoryRequirements.memoryTypeBits & (1 << m_index[memoryPool])))
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
    VkDeviceSize startOffset = (m_offset[memoryPool] % alignment);
    if (startOffset != 0)
    {
        m_offset[memoryPool] += (alignment - startOffset);
    }

    // Bind texture memory
    if (!texture.bindTextureMemory(vulkanDevice,
        m_memory[memoryPool], size, m_offset[memoryPool]))
    {
        // Could not bind texture memory
        return false;
    }

    // Update current memory offset
    m_offset[memoryPool] += size;

    // Texture memory successfully allocated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Allocate texture array memory                                             //
//  return : True if texture array memory is allocated                        //
////////////////////////////////////////////////////////////////////////////////
bool VulkanMemory::allocateTextureArrayMemory(VkDevice& vulkanDevice,
    TextureArray& textureArray, VulkanMemoryPool memoryPool)
{
    // Check texture array handle
    if (!textureArray.isValid())
    {
        // Invalid texture array handle
        return false;
    }

    // Check memory type
    if (m_index[memoryPool] != m_deviceMemoryIndex)
    {
        // Invalid memory type
        return false;
    }

    // Get memory requirements
    VkMemoryRequirements memoryRequirements;
    textureArray.getMemoryRequirements(vulkanDevice, &memoryRequirements);

    // Check memory requirements size
    if (memoryRequirements.size <= 0)
    {
        // Invalid memory requirements size
        return false;
    }

    // Check memory type bits
    if (!(memoryRequirements.memoryTypeBits & (1 << m_index[memoryPool])))
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
    VkDeviceSize startOffset = (m_offset[memoryPool] % alignment);
    if (startOffset != 0)
    {
        m_offset[memoryPool] += (alignment - startOffset);
    }

    // Bind texture array memory
    if (!textureArray.bindTextureArrayMemory(vulkanDevice,
        m_memory[memoryPool], size, m_offset[memoryPool]))
    {
        // Could not bind texture array memory
        return false;
    }

    // Update current memory offset
    m_offset[memoryPool] += size;

    // Texture array memory successfully allocated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Allocate cubemap memory                                                   //
//  return : True if cubemap memory is successfully allocated                 //
////////////////////////////////////////////////////////////////////////////////
bool VulkanMemory::allocateCubeMapMemory(VkDevice& vulkanDevice,
    CubeMap& cubemap, VulkanMemoryPool memoryPool)
{
    // Check cubemap handle
    if (!cubemap.isValid())
    {
        // Invalid cubemap handle
        return false;
    }

    // Check memory type
    if (m_index[memoryPool] != m_deviceMemoryIndex)
    {
        // Invalid memory type
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
    if (!(memoryRequirements.memoryTypeBits & (1 << m_index[memoryPool])))
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
    VkDeviceSize startOffset = (m_offset[memoryPool] % alignment);
    if (startOffset != 0)
    {
        m_offset[memoryPool] += (alignment - startOffset);
    }

    // Bind cubemap memory
    if (!cubemap.bindCubeMapMemory(vulkanDevice,
        m_memory[memoryPool], size, m_offset[memoryPool]))
    {
        // Could not bind cubemap memory
        return false;
    }

    // Update current memory offset
    m_offset[memoryPool] += size;

    // CubeMap memory successfully allocated
    return true;
}
