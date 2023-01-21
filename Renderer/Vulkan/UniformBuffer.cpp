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
//     Renderer/Vulkan/UniformBuffer.cpp : Uniform buffer management          //
////////////////////////////////////////////////////////////////////////////////
#include "UniformBuffer.h"


////////////////////////////////////////////////////////////////////////////////
//  UniformBuffer default constructor                                         //
////////////////////////////////////////////////////////////////////////////////
UniformBuffer::UniformBuffer() :
uniformBuffer(),
stagingBuffer()
{

}

////////////////////////////////////////////////////////////////////////////////
//  UniformBuffer destructor                                                  //
////////////////////////////////////////////////////////////////////////////////
UniformBuffer::~UniformBuffer()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Create Uniform buffer                                                     //
//  return : True if Uniform buffer is successfully created                   //
////////////////////////////////////////////////////////////////////////////////
bool UniformBuffer::createBuffer(uint32_t size)
{
    // Check current buffer
    if (uniformBuffer.handle)
    {
        // Destroy current buffer
        uniformBuffer.destroyBuffer();
    }

    // Check UniformData size
    size_t uniformDataSize = sizeof(UniformData);
    if (uniformDataSize != (sizeof(float)*16))
    {
        // Invalid UniformData size
        return false;
    }

    // Create uniform buffer
    if (!uniformBuffer.createBuffer(
        (VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT),
        VULKAN_MEMORY_UNIFORMS, size))
    {
        // Could not create uniform buffer
        return false;
    }

    // Create staging buffer
    if (!stagingBuffer.createBuffer(
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VULKAN_MEMORY_UNIFORMUPLOAD, size))
    {
        // Could not create staging buffer
        return false;
    }

    // Uniform buffer successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Update Uniform buffer                                                     //
//  return : True if Uniform buffer is successfully updated                   //
////////////////////////////////////////////////////////////////////////////////
bool UniformBuffer::updateBuffer(void* data, uint32_t size)
{
    // Check current buffer
    if (!uniformBuffer.handle || (uniformBuffer.size != size) ||
        !stagingBuffer.handle || (stagingBuffer.size != size))
    {
        // Recreate uniform buffer
        destroyBuffer();
        createBuffer(size);
    }

    // Write data into staging buffer memory
    if (!GVulkanMemory.writeBufferMemory(
        stagingBuffer, data, VULKAN_MEMORY_UNIFORMUPLOAD))
    {
        // Could not write data into staging buffer memory
        return false;
    }

    // Barrier from shader to transfer
    VkBufferMemoryBarrier shaderToTransfer;
    shaderToTransfer.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    shaderToTransfer.pNext = 0;
    shaderToTransfer.srcAccessMask = VK_ACCESS_UNIFORM_READ_BIT;
    shaderToTransfer.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    shaderToTransfer.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    shaderToTransfer.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    shaderToTransfer.buffer = uniformBuffer.handle;
    shaderToTransfer.offset = 0;
    shaderToTransfer.size = VK_WHOLE_SIZE;

    vkCmdPipelineBarrier(
        GUniformchain.commandBuffers[GSwapchain.current],
        VK_PIPELINE_STAGE_VERTEX_SHADER_BIT,
        VK_PIPELINE_STAGE_TRANSFER_BIT,
        0, 0, 0, 1, &shaderToTransfer, 0, 0
    );

    // Transfer staging buffer data to uniform buffer
    VkBufferCopy bufferCopy;
    bufferCopy.srcOffset = 0;
    bufferCopy.dstOffset = 0;
    bufferCopy.size = stagingBuffer.size;

    vkCmdCopyBuffer(
        GUniformchain.commandBuffers[GSwapchain.current],
        stagingBuffer.handle, uniformBuffer.handle, 1, &bufferCopy
    );

    // Barrier from transfer to shader
    VkBufferMemoryBarrier transferToShader;
    transferToShader.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    transferToShader.pNext = 0;
    transferToShader.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    transferToShader.dstAccessMask = VK_ACCESS_UNIFORM_READ_BIT;
    transferToShader.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    transferToShader.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    transferToShader.buffer = uniformBuffer.handle;
    transferToShader.offset = 0;
    transferToShader.size = VK_WHOLE_SIZE;

    vkCmdPipelineBarrier(
        GUniformchain.commandBuffers[GSwapchain.current],
        VK_PIPELINE_STAGE_TRANSFER_BIT,
        VK_PIPELINE_STAGE_VERTEX_SHADER_BIT,
        0, 0, 0, 1, &transferToShader, 0, 0
    );

    // Uniform buffer successfully updated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy Uniform buffer                                                    //
////////////////////////////////////////////////////////////////////////////////
void UniformBuffer::destroyBuffer()
{
    stagingBuffer.destroyBuffer();
    uniformBuffer.destroyBuffer();
}
