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
//     Renderer/BackRenderer.cpp : Offscreen renderer management              //
////////////////////////////////////////////////////////////////////////////////
#include "BackRenderer.h"


////////////////////////////////////////////////////////////////////////////////
//  BackRenderer default constructor                                          //
////////////////////////////////////////////////////////////////////////////////
BackRenderer::BackRenderer() :
m_extent()
{
    m_extent.width = 0;
    m_extent.height = 0;
    for (uint32_t i = 0; i < BackRendererMaxFrames; ++i)
    {
        m_images[i] = 0;
        m_depthImages[i] = 0;
        m_views[i] = 0;
        m_depthViews[i] = 0;
        m_framebuffers[i] = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  BackRenderer destructor                                                   //
////////////////////////////////////////////////////////////////////////////////
BackRenderer::~BackRenderer()
{
    for (uint32_t i = 0; i < BackRendererMaxFrames; ++i)
    {
        m_framebuffers[i] = 0;
        m_depthViews[i] = 0;
        m_views[i] = 0;
        m_depthImages[i] = 0;
        m_images[i] = 0;
    }
    m_extent.height = 0;
    m_extent.width = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Init back renderer                                                        //
//  return : True if the back renderer is successfully loaded                 //
////////////////////////////////////////////////////////////////////////////////
bool BackRenderer::init(Renderer& renderer, uint32_t width, uint32_t height)
{
    // Check back renderer size
    if ((width <= 0) || (width > BackRendererMaxWidth) ||
        (height <= 0) || (height > BackRendererMaxHeight))
    {
        // Invalid back renderer size
        return false;
    }

    // Create back renderer images
    for (uint32_t i = 0; i < BackRendererMaxFrames; ++i)
    {
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
            VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        imageInfo.queueFamilyIndexCount = 0;
        imageInfo.pQueueFamilyIndices = 0;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

        if (vkCreateImage(
            renderer.m_vulkanDevice, &imageInfo, 0, &m_images[i]) != VK_SUCCESS)
        {
            // Could not create image
            return false;
        }
        if (!m_images[i])
        {
            // Invalid image
            return false;
        }

        // Allocate image memory
        if (!renderer.m_vulkanMemory.allocateBackRendererImage(
            renderer.m_vulkanDevice, m_images[i]))
        {
            // Could not allocate image memory
            return false;
        }
    }

    // Create back renderer depth images
    for (uint32_t i = 0; i < BackRendererMaxFrames; ++i)
    {
        // Create depth image
        VkImageCreateInfo imageInfo;
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.pNext = 0;
        imageInfo.flags = 0;
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        imageInfo.format = VK_FORMAT_D32_SFLOAT;
        imageInfo.extent.width = width;
        imageInfo.extent.height = height;
        imageInfo.extent.depth = 1;
        imageInfo.mipLevels = 1;
        imageInfo.arrayLayers = 1;
        imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        imageInfo.queueFamilyIndexCount = 0;
        imageInfo.pQueueFamilyIndices = 0;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

        if (vkCreateImage(renderer.m_vulkanDevice,
            &imageInfo, 0, &m_depthImages[i]) != VK_SUCCESS)
        {
            // Could not create depth image
            return false;
        }
        if (!m_depthImages[i])
        {
            // Invalid depth image
            return false;
        }

        // Allocate depth image memory
        if (!renderer.m_vulkanMemory.allocateBackRendererImage(
            renderer.m_vulkanDevice, m_depthImages[i]))
        {
            // Could not allocate depth image memory
            return false;
        }
    }

    // Create back renderer images views
    VkImageSubresourceRange subresource;
    subresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    subresource.baseMipLevel = 0;
    subresource.levelCount = 1;
    subresource.baseArrayLayer = 0;
    subresource.layerCount = 1;

    for (uint32_t i = 0; i < BackRendererMaxFrames; ++i)
    {
        // Create image view
        VkImageViewCreateInfo imageView;
        imageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageView.pNext = 0;
        imageView.flags = 0;
        imageView.image = m_images[i];
        imageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
        imageView.format = VK_FORMAT_R8G8B8A8_UNORM;
        imageView.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageView.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageView.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageView.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageView.subresourceRange = subresource;

        if (vkCreateImageView(
            renderer.m_vulkanDevice, &imageView, 0, &m_views[i]) != VK_SUCCESS)
        {
            return false;
        }
    }

    // Create back renderer depth images views
    VkImageSubresourceRange depthSubresource;
    depthSubresource.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    depthSubresource.baseMipLevel = 0;
    depthSubresource.levelCount = 1;
    depthSubresource.baseArrayLayer = 0;
    depthSubresource.layerCount = 1;

    for (uint32_t i = 0; i < BackRendererMaxFrames; ++i)
    {
        // Create depth image view
        VkImageViewCreateInfo depthImageView;
        depthImageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        depthImageView.pNext = 0;
        depthImageView.flags = 0;
        depthImageView.image = m_depthImages[i];
        depthImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
        depthImageView.format = VK_FORMAT_D32_SFLOAT;
        depthImageView.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        depthImageView.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        depthImageView.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        depthImageView.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        depthImageView.subresourceRange = depthSubresource;

        if (vkCreateImageView(renderer.m_vulkanDevice,
            &depthImageView, 0, &m_depthViews[i]) != VK_SUCCESS)
        {
            return false;
        }
    }

    // Set back renderer extent
    m_extent.width = width;
    m_extent.height = height;

    // Back renderer successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Cleanup back renderer                                                     //
////////////////////////////////////////////////////////////////////////////////
void BackRenderer::cleanup(Renderer& renderer)
{
    if (renderer.m_vulkanDevice)
    {
        if (vkDeviceWaitIdle)
        {
            if (vkDeviceWaitIdle(renderer.m_vulkanDevice) == VK_SUCCESS)
            {
                for (uint32_t i = 0; i < BackRendererMaxFrames; ++i)
                {
                    // Destroy framebuffers
                    if (m_framebuffers[i] && vkDestroyFramebuffer)
                    {
                        vkDestroyFramebuffer(
                            renderer.m_vulkanDevice, m_framebuffers[i], 0
                        );
                    }

                    // Destroy back renderer depth images views
                    if (m_depthViews[i] && vkDestroyImageView)
                    {
                        // Destroy image view
                        vkDestroyImageView(
                            renderer.m_vulkanDevice, m_depthViews[i], 0
                        );
                    }

                    // Destroy back renderer images views
                    if (m_views[i] && vkDestroyImageView)
                    {
                        // Destroy image view
                        vkDestroyImageView(
                            renderer.m_vulkanDevice, m_views[i], 0
                        );
                    }

                    // Destroy back renderer depth images
                    if (m_depthImages[i] && vkDestroyImage)
                    {
                        vkDestroyImage(
                            renderer.m_vulkanDevice, m_depthImages[i], 0
                        );
                    }

                    // Destroy back renderer images
                    if (m_depthImages[i] && vkDestroyImage)
                    {
                        vkDestroyImage(
                            renderer.m_vulkanDevice, m_images[i], 0
                        );
                    }
                }
            }
        }
    }

    for (uint32_t i = 0; i < BackRendererMaxFrames; ++i)
    {
        m_framebuffers[i] = 0;
        m_depthViews[i] = 0;
        m_views[i]= 0;
        m_depthImages[i] = 0;
        m_images[i] = 0;
    }
    m_extent.height = 0;
    m_extent.width = 0;
}
