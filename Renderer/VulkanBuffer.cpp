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
//     Renderer/VulkanBuffer.cpp : Vulkan Buffer management                   //
////////////////////////////////////////////////////////////////////////////////
#include "VulkanBuffer.h"


////////////////////////////////////////////////////////////////////////////////
//  VulkanBuffer default constructor                                          //
////////////////////////////////////////////////////////////////////////////////
VulkanBuffer::VulkanBuffer() :
handle(0),
memory(0),
size(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  VulkanBuffer destructor                                                   //
////////////////////////////////////////////////////////////////////////////////
VulkanBuffer::~VulkanBuffer()
{
    size = 0;
    memory = 0;
    handle = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Create Vulkan Buffer                                                      //
//  return : True if Vulkan Buffer is successfully created                    //
////////////////////////////////////////////////////////////////////////////////
bool VulkanBuffer::createBuffer(VkPhysicalDevice& physicalDevice,
    VkDevice& vulkanDevice, VkBufferUsageFlags usage,
    VkMemoryPropertyFlags properties)
{
    // Check physical device
    if (!physicalDevice)
    {
        // Invalid physical device
        return false;
    }

    // Check Vulkan device
    if (!vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Check Vulkan Buffer
    if (handle)
    {
        // Destroy Vulkan Buffer
        destroyBuffer(vulkanDevice);
    }

    // Create Vulkan Buffer
    VkBufferCreateInfo bufferInfo;
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.pNext = 0;
    bufferInfo.flags = 0;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    bufferInfo.queueFamilyIndexCount = 0;
    bufferInfo.pQueueFamilyIndices = 0;

    if (vkCreateBuffer(vulkanDevice, &bufferInfo, 0, &handle) != VK_SUCCESS)
    {
        // Could not create buffer
        return false;
    }
    if (!handle)
    {
        // Invalid buffer
        return false;
    }

    // Get memory requirements
    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(vulkanDevice, handle, &memoryRequirements);

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
                properties)
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

    // Bind buffer memory
    if (vkBindBufferMemory(vulkanDevice, handle, memory, 0) != VK_SUCCESS)
    {
        // Could not bind buffer memory
        return false;
    }

    // Buffer successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy Vulkan Buffer                                                     //
////////////////////////////////////////////////////////////////////////////////
void VulkanBuffer::destroyBuffer(VkDevice& vulkanDevice)
{
    if (vulkanDevice)
    {
        // Destroy buffer
        if (handle && vkDestroyBuffer)
        {
            vkDestroyBuffer(vulkanDevice, handle, 0);
        }

        // Free vertex buffer memory
        if (memory && vkFreeMemory)
        {
            vkFreeMemory(vulkanDevice, memory, 0);
        }
    }
    size = 0;
    memory = 0;
    handle = 0;
}
