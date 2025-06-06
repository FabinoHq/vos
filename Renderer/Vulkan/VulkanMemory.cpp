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
//  VulkanMemory global instance                                              //
////////////////////////////////////////////////////////////////////////////////
VulkanMemory GVulkanMemory = VulkanMemory();


////////////////////////////////////////////////////////////////////////////////
//  VulkanMemory default constructor                                          //
////////////////////////////////////////////////////////////////////////////////
VulkanMemory::VulkanMemory() :
m_deviceMemoryIndex(0),
m_deviceMemoryHeap(0),
m_hostMemoryIndex(0),
m_hostMemoryHeap(0),
m_maxAllocationCount(0),
m_memoryAlignment(0)
{
    // Reset memory arrays
    for (int i = 0; i < VULKAN_MEMORY_POOLSCOUNT; ++i)
    {
        m_memory[i] = 0;
        m_offset[i] = 0;
        m_index[i] = 0;
        m_usage[i] = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  VulkanMemory destructor                                                   //
////////////////////////////////////////////////////////////////////////////////
VulkanMemory::~VulkanMemory()
{
    // Reset memory arrays
    for (int i = 0; i < VULKAN_MEMORY_POOLSCOUNT; ++i)
    {
        m_memory[i] = 0;
        m_offset[i] = 0;
        m_index[i] = 0;
        m_usage[i] = 0;
    }
    m_memoryAlignment = 0;
    m_maxAllocationCount = 0;
    m_hostMemoryHeap = 0;
    m_hostMemoryIndex = 0;
    m_deviceMemoryHeap = 0;
    m_deviceMemoryIndex = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Init Vulkan memory                                                        //
//  return : True if Vulkan memory is ready                                   //
////////////////////////////////////////////////////////////////////////////////
bool VulkanMemory::init()
{
    // Check physical device
    if (!GPhysicalDevice)
    {
        // Invalid physical device
        GSysMessage << "[0x3101] Invalid physical device\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Reset memory arrays
    for (int i = 0; i < VULKAN_MEMORY_POOLSCOUNT; ++i)
    {
        m_memory[i] = 0;
        m_offset[i] = 0;
        m_index[i] = 0;
        m_usage[i] = 0;
    }

    // Get physical device properties
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(GPhysicalDevice, &deviceProperties);
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
            GSysMessage << "[0x3102] Invalid memory alignment\n";
            GSysMessage << "Please update your graphics drivers";
            return false;
        }
    }
    else
    {
        if ((m_memoryAlignment %
            deviceProperties.limits.nonCoherentAtomSize) != 0)
        {
            // Invalid memory alignment
            GSysMessage << "[0x3103] Invalid memory alignment\n";
            GSysMessage << "Please update your graphics drivers";
            return false;
        }
    }

    // Check maximum allocation count
    if (m_maxAllocationCount < VULKAN_MEMORY_POOLSCOUNT)
    {
        // Invalid maximum allocation count
        GSysMessage << "[0x3104] Invalid maximum allocation count\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Get physical device memory properties
    VkPhysicalDeviceMemoryProperties physicalMemoryProperties;
    physicalMemoryProperties.memoryTypeCount = 0;
    physicalMemoryProperties.memoryHeapCount = 0;
    for (int i = 0; i < VK_MAX_MEMORY_TYPES; ++i)
    {
        physicalMemoryProperties.memoryTypes[i].propertyFlags = 0;
        physicalMemoryProperties.memoryTypes[i].heapIndex = 0;
    }
    for (int i = 0; i < VK_MAX_MEMORY_HEAPS; ++i)
    {
        physicalMemoryProperties.memoryHeaps[i].size = 0;
        physicalMemoryProperties.memoryHeaps[i].flags = 0;
    }
    vkGetPhysicalDeviceMemoryProperties(
        GPhysicalDevice, &physicalMemoryProperties
    );

    // Check physical memory types
    if (physicalMemoryProperties.memoryTypeCount <= 0)
    {
        // No physical memory type
        GSysMessage << "[0x3105] No physical memory types\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Select device and host memory
    bool deviceMemoryFound = false;
    bool hostMemoryFound = false;
    VkDeviceSize deviceMemorySize = 0;
    VkDeviceSize hostMemorySize = 0;
    for (uint32_t i = 0; i < physicalMemoryProperties.memoryTypeCount; ++i)
    {
        // Device local memory type
        if (physicalMemoryProperties.memoryTypes[i].propertyFlags &
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
        {
            if (physicalMemoryProperties.memoryHeaps[
                physicalMemoryProperties.memoryTypes[i].heapIndex].size >
                deviceMemorySize)
            {
                m_deviceMemoryIndex = i;
                m_deviceMemoryHeap =
                    (physicalMemoryProperties.memoryTypes[i].heapIndex);
                deviceMemorySize = physicalMemoryProperties.memoryHeaps[
                    m_deviceMemoryHeap].size;
                deviceMemoryFound = true;
            }
        }

        // Host memory type
        if (physicalMemoryProperties.memoryTypes[i].propertyFlags &
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
        {
            if (physicalMemoryProperties.memoryHeaps[
                physicalMemoryProperties.memoryTypes[i].heapIndex].size >
                hostMemorySize)
            {
                m_hostMemoryIndex = i;
                m_hostMemoryHeap =
                    (physicalMemoryProperties.memoryTypes[i].heapIndex);
                hostMemorySize = physicalMemoryProperties.memoryHeaps[
                    m_hostMemoryHeap].size;
                hostMemoryFound = true;
            }
        }
    }

    // Check if all memory types are found
    if (!deviceMemoryFound || !hostMemoryFound)
    {
        // Could not find all memory types
        GSysMessage << "[0x3106] Could not find all memory types\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Check required memory
    VkDeviceSize deviceTotalMemory = 0;
    VkDeviceSize hostTotalMemory = 0;
    for (int i = 0; i < VULKAN_MEMORY_POOLSCOUNT; ++i)
    {
        // Check memory pool index
        if (VulkanMemoryArray[i].pool != i)
        {
            // Invalid memory pool index
            GSysMessage << "[0x3107] Invalid memory pool index\n";
            GSysMessage << "Please update your graphics drivers";
            return false;
        }

        // Compute total required memory
        if (VulkanMemoryArray[i].type == VULKAN_MEMORY_DEVICE)
        {
            deviceTotalMemory += VulkanMemoryArray[i].size;
        }
        else if (VulkanMemoryArray[i].type == VULKAN_MEMORY_HOST)
        {
            hostTotalMemory += VulkanMemoryArray[i].size;
        }
    }

    // Check available device memory
    if (physicalMemoryProperties.memoryHeaps[m_deviceMemoryHeap].size <
        deviceTotalMemory)
    {
        GSysMessage << "[0x3108] Not enough graphics memory available\n";
        GSysMessage << "You need at least 4GB of graphics memory";
        return false;
    }

    // Check available host memory
    if (physicalMemoryProperties.memoryHeaps[m_hostMemoryHeap].size <
        hostTotalMemory)
    {
        GSysMessage << "[0x3109] Not enough graphics memory available\n";
        GSysMessage << "You need at least 4GB of graphics memory";
        return false;
    }

    // Allocate memory pools
    for (int i = 0; i < VULKAN_MEMORY_POOLSCOUNT; ++i)
    {
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
            GSysMessage << "[0x310A] Invalid graphics memory pool type\n";
            GSysMessage << "Please update your graphics drivers";
            return false;
        }

        // Allocate Vulkan memory
        VkMemoryAllocateInfo allocateInfo;
        allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocateInfo.pNext = 0;
        allocateInfo.allocationSize = VulkanMemoryArray[i].size;
        allocateInfo.memoryTypeIndex = m_index[i];

        if (vkAllocateMemory(GVulkanDevice, &allocateInfo,
            SYSVKMEMORY_VULKAN_ALLOC, &m_memory[i]) != VK_SUCCESS)
        {
            // Could not allocate device memory pool
            GSysMessage << "[0x310B] Could not allocate graphics memory pool\n";
            GSysMessage << "Please update your graphics drivers";
            return false;
        }
    }

    // Vulkan memory is ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy Vulkan memory                                                     //
////////////////////////////////////////////////////////////////////////////////
void VulkanMemory::destroyVulkanMemory()
{
    // Free memory arrays
    if (GVulkanDevice)
    {
        for (int i = 0; i < VULKAN_MEMORY_POOLSCOUNT; ++i)
        {
            if (m_memory[i])
            {
                vkFreeMemory(
                    GVulkanDevice, m_memory[i], SYSVKMEMORY_VULKAN_ALLOC
                );
            }
        }
    }

    // Reset memory arrays
    for (int i = 0; i < VULKAN_MEMORY_POOLSCOUNT; ++i)
    {
        m_memory[i] = 0;
        m_offset[i] = 0;
        m_index[i] = 0;
        m_usage[i] = 0;
    }
    m_memoryAlignment = 0;
    m_maxAllocationCount = 0;
    m_hostMemoryHeap = 0;
    m_hostMemoryIndex = 0;
    m_deviceMemoryHeap = 0;
    m_deviceMemoryIndex = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Allocate backchain image memory                                           //
//  return : True if backchain image is successfully allocated                //
////////////////////////////////////////////////////////////////////////////////
bool VulkanMemory::allocateBackchainImage(VkImage& image,
    VulkanMemoryPool memoryPool)
{
    // Check image handle
    if (!image)
    {
        // Invalid image handle
        return false;
    }

    // Get memory requirements
    VkMemoryRequirements memoryRequirements;
    vkGetImageMemoryRequirements(GVulkanDevice, image, &memoryRequirements);

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
    if (sizeOffset != 0) { size += (alignment - sizeOffset); }

    // Adjust memory start offset according to alignment
    VkDeviceSize offset = m_offset[memoryPool];
    VkDeviceSize startOffset = (offset % alignment);
    if (startOffset != 0) { offset += (alignment - startOffset); }

    // Check remaining memory in pool
    if ((offset + size) > VulkanMemoryArray[memoryPool].size)
    {
        // Not enough remaining memory in pool
        return false;
    }

    // Bind image memory
    if (vkBindImageMemory(GVulkanDevice, image,
        m_memory[memoryPool], offset) != VK_SUCCESS)
    {
        // Could not bind image memory
        return false;
    }

    // Update current memory offset
    m_offset[memoryPool] = (offset + size);

    // Update current memory usage
    if (m_offset[memoryPool] >= m_usage[memoryPool])
    {
        m_usage[memoryPool] = m_offset[memoryPool];
    }

    // Swapchain image successfully allocated
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Allocate buffer memory                                                    //
//  return : True if buffer memory is successfully allocated                  //
////////////////////////////////////////////////////////////////////////////////
bool VulkanMemory::allocateBufferMemory(VulkanBuffer& buffer,
    VulkanMemoryPool memoryPool)
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
        GVulkanDevice, buffer.handle, &memoryRequirements
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
    if (sizeOffset != 0) { size += (alignment - sizeOffset); }

    // Adjust memory start offset according to alignment
    VkDeviceSize offset = m_offset[memoryPool];
    VkDeviceSize startOffset = (offset % alignment);
    if (startOffset != 0) { offset += (alignment - startOffset); }

    // Check remaining memory in pool
    if ((offset + size) > VulkanMemoryArray[memoryPool].size)
    {
        // Not enough remaining memory in pool
        return false;
    }

    // Set buffer memory size and offset
    buffer.memorySize = size;
    buffer.memoryOffset = offset;

    // Bind buffer memory
    if (vkBindBufferMemory(GVulkanDevice, buffer.handle,
        m_memory[memoryPool], buffer.memoryOffset) != VK_SUCCESS)
    {
        // Could not bind buffer memory
        return false;
    }

    // Update current memory offset
    m_offset[memoryPool] = (offset + size);

    // Update current memory usage
    if (m_offset[memoryPool] >= m_usage[memoryPool])
    {
        m_usage[memoryPool] = m_offset[memoryPool];
    }

    // Buffer memory successfully allocated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Write buffer memory                                                       //
//  return : True if buffer memory is successfully written                    //
////////////////////////////////////////////////////////////////////////////////
bool VulkanMemory::writeBufferMemory(VulkanBuffer& buffer,
    const void* data, VulkanMemoryPool memoryPool)
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
    if (vkMapMemory(GVulkanDevice, m_memory[memoryPool],
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

    if (vkFlushMappedMemoryRanges(GVulkanDevice, 1, &memoryRange) != VK_SUCCESS)
    {
        // Could not flush buffer mapped memory ranges
        return false;
    }

    vkUnmapMemory(GVulkanDevice, m_memory[memoryPool]);

    // Buffer memory successfully mapped
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Allocate texture memory                                                   //
//  return : True if texture memory is successfully allocated                 //
////////////////////////////////////////////////////////////////////////////////
bool VulkanMemory::allocateTextureMemory(Texture& texture,
    VulkanMemoryPool memoryPool)
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
    texture.getMemoryRequirements(&memoryRequirements);

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
    if (sizeOffset != 0) { size += (alignment - sizeOffset); }

    // Adjust memory start offset according to alignment
    VkDeviceSize offset = m_offset[memoryPool];
    VkDeviceSize startOffset = (offset % alignment);
    if (startOffset != 0) { offset += (alignment - startOffset); }

    // Check remaining memory in pool
    if ((offset + size) > VulkanMemoryArray[memoryPool].size)
    {
        // Not enough remaining memory in pool
        return false;
    }

    // Bind texture memory
    if (!texture.bindTextureMemory(m_memory[memoryPool], size, offset))
    {
        // Could not bind texture memory
        return false;
    }

    // Update current memory offset
    m_offset[memoryPool] = (offset + size);

    // Update current memory usage
    if (m_offset[memoryPool] >= m_usage[memoryPool])
    {
        m_usage[memoryPool] = m_offset[memoryPool];
    }

    // Texture memory successfully allocated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Allocate texture array memory                                             //
//  return : True if texture array memory is allocated                        //
////////////////////////////////////////////////////////////////////////////////
bool VulkanMemory::allocateTextureArrayMemory(TextureArray& textureArray,
    VulkanMemoryPool memoryPool)
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
    textureArray.getMemoryRequirements(&memoryRequirements);

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
    if (sizeOffset != 0) { size += (alignment - sizeOffset); }

    // Adjust memory start offset according to alignment
    VkDeviceSize offset = m_offset[memoryPool];
    VkDeviceSize startOffset = (offset % alignment);
    if (startOffset != 0) { offset += (alignment - startOffset); }

    // Check remaining memory in pool
    if ((offset + size) > VulkanMemoryArray[memoryPool].size)
    {
        // Not enough remaining memory in pool
        return false;
    }

    // Bind texture array memory
    if (!textureArray.bindTextureArrayMemory(
        m_memory[memoryPool], size, offset))
    {
        // Could not bind texture array memory
        return false;
    }

    // Update current memory offset
    m_offset[memoryPool] = (offset + size);

    // Update current memory usage
    if (m_offset[memoryPool] >= m_usage[memoryPool])
    {
        m_usage[memoryPool] = m_offset[memoryPool];
    }

    // Texture array memory successfully allocated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Allocate cubemap memory                                                   //
//  return : True if cubemap memory is successfully allocated                 //
////////////////////////////////////////////////////////////////////////////////
bool VulkanMemory::allocateCubeMapMemory(CubeMap& cubemap,
    VulkanMemoryPool memoryPool)
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
    cubemap.getMemoryRequirements(&memoryRequirements);

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
    if (sizeOffset != 0) { size += (alignment - sizeOffset); }

    // Adjust memory start offset according to alignment
    VkDeviceSize offset = m_offset[memoryPool];
    VkDeviceSize startOffset = (offset % alignment);
    if (startOffset != 0) { offset += (alignment - startOffset); }

    // Check remaining memory in pool
    if ((offset + size) > VulkanMemoryArray[memoryPool].size)
    {
        // Not enough remaining memory in pool
        return false;
    }

    // Bind cubemap memory
    if (!cubemap.bindCubeMapMemory(m_memory[memoryPool], size, offset))
    {
        // Could not bind cubemap memory
        return false;
    }

    // Update current memory offset
    m_offset[memoryPool] = (offset + size);

    // Update current memory usage
    if (m_offset[memoryPool] >= m_usage[memoryPool])
    {
        m_usage[memoryPool] = m_offset[memoryPool];
    }

    // CubeMap memory successfully allocated
    return true;
}
