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
//     Renderer/Vulkan/Uniformchain.cpp : Uniform chain management            //
////////////////////////////////////////////////////////////////////////////////
#include "Uniformchain.h"


////////////////////////////////////////////////////////////////////////////////
//  Uniformchain global instance                                              //
////////////////////////////////////////////////////////////////////////////////
Uniformchain GUniformchain = Uniformchain();


////////////////////////////////////////////////////////////////////////////////
//  Uniformchain default constructor                                          //
////////////////////////////////////////////////////////////////////////////////
Uniformchain::Uniformchain() :
uniformQueue()
{
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        uniformsReady[i] = 0;
        fences[i] = 0;
        commandPools[i] = 0;
        commandBuffers[i] = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Uniformchain destructor                                                   //
////////////////////////////////////////////////////////////////////////////////
Uniformchain::~Uniformchain()
{
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        commandBuffers[i] = 0;
        commandPools[i] = 0;
        fences[i] = 0;
        uniformsReady[i] = 0;
    }
}


////////////////////////////////////////////////////////////////////////////////
//  Create uniformchain                                                       //
//  return : True if uniformchain is successfully created                     //
////////////////////////////////////////////////////////////////////////////////
bool Uniformchain::createUniformchain()
{
    // Request uniforms queue handle
    if (!uniformQueue.getVulkanQueue(VULKAN_QUEUE_UNIFORMS))
    {
        // Could not get uniforms queue handle
        return false;
    }

    // Create semaphores
    VkSemaphoreCreateInfo semaphoreInfo;
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    semaphoreInfo.pNext = 0;
    semaphoreInfo.flags = 0;

    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        // Create uniforms ready semaphore
        if (vkCreateSemaphore(GVulkanDevice, &semaphoreInfo,
            SYSVKMEMORY_SEMAPHORE_ALLOC, &uniformsReady[i]) != VK_SUCCESS)
        {
            // Could not create uniforms ready semaphore
            return false;
        }
    }

    // Create fences
    VkFenceCreateInfo fenceInfo;
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.pNext = 0;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        // Create fence
        if (vkCreateFence(GVulkanDevice, &fenceInfo,
            SYSVKMEMORY_FENCE_ALLOC, &fences[i]) != VK_SUCCESS)
        {
            // Could not create fence
            return false;
        }
        if (!fences[i])
        {
            // Invalid fence
            return false;
        }
    }

    // Create commands pools
    VkCommandPoolCreateInfo commandPoolInfo;
    commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolInfo.pNext = 0;
    commandPoolInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
    commandPoolInfo.queueFamilyIndex = uniformQueue.family;

    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        // Create command pool
        if (vkCreateCommandPool(GVulkanDevice, &commandPoolInfo,
            SYSVKMEMORY_COMMANDPOOL_ALLOC, &commandPools[i]) != VK_SUCCESS)
        {
            // Could not create commands pool
            return false;
        }
        if (!commandPools[i])
        {
            // Invalid commands pool
            return false;
        }
    }

    // Allocate command buffers
    VkCommandBufferAllocateInfo commandBufferInfo;
    commandBufferInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    commandBufferInfo.pNext = 0;
    commandBufferInfo.commandPool = 0;
    commandBufferInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    commandBufferInfo.commandBufferCount = 1;

    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        // Allocate command buffer
        commandBufferInfo.commandPool = commandPools[i];

        if (vkAllocateCommandBuffers(GVulkanDevice,
            &commandBufferInfo, &commandBuffers[i]) != VK_SUCCESS)
        {
            // Could not allocate command buffers
            return false;
        }
        if (!commandBuffers[i])
        {
            // Invalid commands buffer
            return false;
        }
    }

    // Uniformchain sucessfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy uniformchain                                                      //
////////////////////////////////////////////////////////////////////////////////
void Uniformchain::destroyUniformchain()
{
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        if (commandPools[i])
        {
            // Destroy command buffer
            if (commandBuffers[i])
            {
                vkFreeCommandBuffers(
                    GVulkanDevice, commandPools[i], 1, &commandBuffers[i]
                );
            }

            // Destroy commands pool
            vkDestroyCommandPool(
                GVulkanDevice, commandPools[i], SYSVKMEMORY_COMMANDPOOL_ALLOC
            );
        }
        commandBuffers[i] = 0;
        commandPools[i] = 0;

        // Destroy fences
        if (fences[i])
        {
            vkDestroyFence(GVulkanDevice, fences[i], SYSVKMEMORY_FENCE_ALLOC);
        }
        fences[i] = 0;

        // Destroy semaphores
        if (uniformsReady[i])
        {
            vkDestroySemaphore(
                GVulkanDevice, uniformsReady[i], SYSVKMEMORY_SEMAPHORE_ALLOC
            );
        }
        uniformsReady[i] = 0;
    }
}


////////////////////////////////////////////////////////////////////////////////
//  Start uniforms upload                                                     //
//  return : True if uniforms are ready to be uploaded                        //
////////////////////////////////////////////////////////////////////////////////
bool Uniformchain::startUpload()
{
    // Wait for current uploading fence
    if (vkWaitForFences(GVulkanDevice, 1, &fences[GSwapchain.current],
        VK_FALSE, RendererUniformchainFenceTimeout) != VK_SUCCESS)
    {
        // Uploading fence timed out
        return false;
    }

    // Reset command pool
    if (vkResetCommandPool(
        GVulkanDevice, commandPools[GSwapchain.current], 0) != VK_SUCCESS)
    {
        // Could not reset command pool
        return false;
    }

    // Begin command buffer recording
    VkCommandBufferBeginInfo bufferBeginInfo;
    bufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    bufferBeginInfo.pNext = 0;
    bufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    bufferBeginInfo.pInheritanceInfo = 0;

    if (vkBeginCommandBuffer(
        commandBuffers[GSwapchain.current], &bufferBeginInfo) != VK_SUCCESS)
    {
        // Could not record command buffer
        return false;
    }

    // Uniforms are ready to be uploaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  End uniforms upload                                                       //
//  return : True if uniforms are submitted for upload                        //
////////////////////////////////////////////////////////////////////////////////
bool Uniformchain::endUpload()
{
    // End command buffer recording
    if (vkEndCommandBuffer(commandBuffers[GSwapchain.current]) != VK_SUCCESS)
    {
        // Could not end command buffer
        return false;
    }

    // Reset current uploading fence
    if (vkResetFences(GVulkanDevice, 1,
        &fences[GSwapchain.current]) != VK_SUCCESS)
    {
        // Could not reset fence
        return false;
    }

    // Submit queue
    VkSubmitInfo submitInfo;
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.pNext = 0;
    submitInfo.waitSemaphoreCount = 0;
    submitInfo.pWaitSemaphores = 0;
    submitInfo.pWaitDstStageMask = 0;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffers[GSwapchain.current];
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = &uniformsReady[GSwapchain.current];

    if (uniformQueue.shared > 0)
    {
        // Shared queue
        GVulkanQueues.queueMutex[uniformQueue.shared].lock();
        if (vkQueueSubmit(uniformQueue.handle,
            1, &submitInfo, fences[GSwapchain.current]) != VK_SUCCESS)
        {
            // Could not submit queue
            GVulkanQueues.queueMutex[uniformQueue.shared].unlock();
            return false;
        }
        GVulkanQueues.queueMutex[uniformQueue.shared].unlock();
    }
    else
    {
        // Dedicated queue
        if (vkQueueSubmit(uniformQueue.handle, 1,
            &submitInfo, fences[GSwapchain.current]) != VK_SUCCESS)
        {
            // Could not submit queue
            return false;
        }
    }

    // Uniforms are submitted for upload
    return true;
}
