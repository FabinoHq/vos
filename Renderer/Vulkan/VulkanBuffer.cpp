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
//     Renderer/Vulkan/VulkanBuffer.cpp : Vulkan buffer management            //
////////////////////////////////////////////////////////////////////////////////
#include "VulkanBuffer.h"


////////////////////////////////////////////////////////////////////////////////
//  VulkanBuffer default constructor                                          //
////////////////////////////////////////////////////////////////////////////////
VulkanBuffer::VulkanBuffer() :
handle(0),
size(0),
memorySize(0),
memoryOffset(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  VulkanBuffer destructor                                                   //
////////////////////////////////////////////////////////////////////////////////
VulkanBuffer::~VulkanBuffer()
{
    memoryOffset = 0;
    memorySize = 0;
    size = 0;
    handle = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Create Vulkan buffer                                                      //
//  return : True if Vulkan buffer is successfully created                    //
////////////////////////////////////////////////////////////////////////////////
bool VulkanBuffer::createBuffer(VkBufferUsageFlags usage,
    VulkanMemoryPool memoryPool, uint32_t bufferSize)
{
    // Check buffer handle
    if (handle)
    {
        // Destroy Vulkan Buffer
        destroyBuffer();
    }

    // Check buffer size
    if (bufferSize <= 0)
    {
        // Invalid buffer size
        return false;
    }

    // Create Vulkan Buffer
    VkBufferCreateInfo bufferInfo;
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.pNext = 0;
    bufferInfo.flags = 0;
    bufferInfo.size = bufferSize;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    bufferInfo.queueFamilyIndexCount = 0;
    bufferInfo.pQueueFamilyIndices = 0;

    if (vkCreateBuffer(GVulkanDevice, &bufferInfo,
        SYSVKMEMORY_BUFFER_ALLOC, &handle) != VK_SUCCESS)
    {
        // Could not create buffer
        return false;
    }
    if (!handle)
    {
        // Invalid buffer
        return false;
    }

    // Set buffer size
    size = bufferSize;

    // Allocate buffer memory
    if (!GVulkanMemory.allocateBufferMemory(*this, memoryPool))
    {
        // Could not allocate buffer memory
        return false;
    }

    // Buffer successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy Vulkan buffer                                                     //
////////////////////////////////////////////////////////////////////////////////
void VulkanBuffer::destroyBuffer()
{
    // Check Vulkan device
    if (!GVulkanDevice)
    {
        // Invalid Vulkan device
        return;
    }

    // Destroy buffer
    if (handle)
    {
        vkDestroyBuffer(GVulkanDevice, handle, SYSVKMEMORY_BUFFER_ALLOC);
    }
    handle = 0;

    memoryOffset = 0;
    memorySize = 0;
    size = 0;
}
