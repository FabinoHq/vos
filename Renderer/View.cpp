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
//     Renderer/View.cpp : View management                                    //
////////////////////////////////////////////////////////////////////////////////
#include "View.h"
#include "Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  View default constructor                                                  //
////////////////////////////////////////////////////////////////////////////////
View::View() :
Transform2(),
m_projMatrix(),
m_projViewMatrix()
{
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        m_descriptorSets[i] = 0;
    }
    m_projMatrix.reset();
    m_projViewMatrix.reset();
}

////////////////////////////////////////////////////////////////////////////////
//  View virtual destructor                                                   //
////////////////////////////////////////////////////////////////////////////////
View::~View()
{
    m_projViewMatrix.reset();
    m_projMatrix.reset();
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        m_descriptorSets[i] = 0;
    }
}


////////////////////////////////////////////////////////////////////////////////
//  Init view                                                                 //
//  return : True if the view is successfully created                         //
////////////////////////////////////////////////////////////////////////////////
bool View::init(Renderer& renderer)
{
    // Reset view transformations
    resetTransforms();

    // Set view size
    setSize(1.0f, 1.0f);

    // Reset projection matrix
    m_projMatrix.setOrthographic(-1.0f, 1.0f, 1.0f, -1.0f, -2.0f, 2.0f);
    m_projMatrix.translateZ(-1.0f);

    // Reset projview matrix
    m_projViewMatrix.set(m_projMatrix);
    m_projViewMatrix *= m_matrix;

    // Copy matrices data into uniform data
    UniformData uniformData;
    memcpy(
        uniformData.projView, m_projViewMatrix.mat, sizeof(m_projViewMatrix.mat)
    );

    // Create uniform buffers
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        if (!m_uniformBuffers[i].updateBuffer(renderer.m_physicalDevice,
            renderer.m_vulkanDevice, renderer.m_vulkanMemory,
            renderer.m_swapchain.commandPools[i], renderer.m_graphicsQueue,
            &uniformData, sizeof(uniformData)))
        {
            // Could not create uniform buffer
            return false;
        }
    }

    // Create matrices descriptor set
    VkDescriptorSetAllocateInfo descriptorInfo;
    descriptorInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    descriptorInfo.pNext = 0;
    descriptorInfo.descriptorPool = renderer.m_uniformsDescPool;
    descriptorInfo.descriptorSetCount = RendererMaxSwapchainFrames;
    descriptorInfo.pSetLayouts = &renderer.m_layout.swapSetLayouts[
        DESC_MATRICES*RendererMaxSwapchainFrames
    ];

    if (vkAllocateDescriptorSets(renderer.m_vulkanDevice,
        &descriptorInfo, m_descriptorSets) != VK_SUCCESS)
    {
        // Could not allocate matrices descriptor sets
        return false;
    }

    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        // Update descriptor sets
        VkDescriptorBufferInfo descBufferInfo;
        descBufferInfo.buffer = m_uniformBuffers[i].uniformBuffer.handle;
        descBufferInfo.offset = 0;
        descBufferInfo.range = m_uniformBuffers[i].uniformBuffer.size;

        // Update matrices descriptor sets
        VkWriteDescriptorSet descriptorWrites;

        descriptorWrites.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites.pNext = 0;
        descriptorWrites.dstSet = m_descriptorSets[i];
        descriptorWrites.dstBinding = 0;
        descriptorWrites.dstArrayElement = 0;
        descriptorWrites.descriptorCount = 1;
        descriptorWrites.descriptorType =
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrites.pImageInfo = 0;
        descriptorWrites.pBufferInfo = &descBufferInfo;
        descriptorWrites.pTexelBufferView = 0;

        vkUpdateDescriptorSets(
            renderer.m_vulkanDevice, 1, &descriptorWrites, 0, 0
        );
    }

    // View is successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy view                                                              //
////////////////////////////////////////////////////////////////////////////////
void View::destroyView(Renderer& renderer)
{
    m_projViewMatrix.reset();
    m_projMatrix.reset();

    // Destroy uniform buffers
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        m_uniformBuffers[i].destroyBuffer(renderer.m_vulkanDevice);
        m_descriptorSets[i] = 0;
    }

    resetTransforms();
}

////////////////////////////////////////////////////////////////////////////////
//  Compute view                                                              //
////////////////////////////////////////////////////////////////////////////////
void View::compute(Renderer& renderer)
{
    // Compute projection matrix
    m_projMatrix.setOrthographic(
        -renderer.m_swapchain.ratio, renderer.m_swapchain.ratio,
        1.0f, -1.0f, -2.0f, 2.0f
    );
    m_projMatrix.translateZ(-1.0f);

    // Compute view matrix
    m_matrix.setIdentity();
    m_matrix.translate(-m_position);
    m_matrix.rotateZ(-m_angle);
    m_matrix.translate(m_origin);
    m_matrix.scale(m_size);

    // Compute projview matrix
    m_projViewMatrix.set(m_projMatrix);
    m_projViewMatrix *= m_matrix;
}

////////////////////////////////////////////////////////////////////////////////
//  Bind view                                                                 //
//  return : True if the view is successfully binded                          //
////////////////////////////////////////////////////////////////////////////////
bool View::bind(Renderer& renderer)
{
    // Copy matrices data into uniform data
    UniformData uniformData;
    memcpy(
        uniformData.projView, m_projViewMatrix.mat, sizeof(m_projViewMatrix.mat)
    );

    // Update uniform buffer
    if (!m_uniformBuffers[renderer.m_swapchain.current].updateBuffer(
        renderer.m_physicalDevice, renderer.m_vulkanDevice,
        renderer.m_vulkanMemory,
        renderer.m_swapchain.commandPools[renderer.m_swapchain.current],
        renderer.m_graphicsQueue, &uniformData, sizeof(uniformData)))
    {
        // Could not update uniform buffer
        return false;
    }

    // Bind matrices descriptor set
    vkCmdBindDescriptorSets(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        VK_PIPELINE_BIND_POINT_GRAPHICS, renderer.m_layout.handle,
        DESC_MATRICES, 1, &m_descriptorSets[renderer.m_swapchain.current], 0, 0
    );

    // View successfully binded
    return true;
}
