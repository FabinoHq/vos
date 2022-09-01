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
//     Renderer/Vulkan/GraphicsLayout.cpp : Graphics layout management        //
////////////////////////////////////////////////////////////////////////////////
#include "GraphicsLayout.h"


////////////////////////////////////////////////////////////////////////////////
//  GraphicsLayout default constructor                                        //
////////////////////////////////////////////////////////////////////////////////
GraphicsLayout::GraphicsLayout() :
handle(0)
{
    for (uint32_t i = 0; i < DESC_SETS_COUNT; ++i)
    {
        descSetLayouts[i] = 0;
    }
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames*DESC_SETS_COUNT; ++i)
    {
        swapSetLayouts[i] = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  GraphicsLayout destructor                                                 //
////////////////////////////////////////////////////////////////////////////////
GraphicsLayout::~GraphicsLayout()
{
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames*DESC_SETS_COUNT; ++i)
    {
        swapSetLayouts[i] = 0;
    }
    for (uint32_t i = 0; i < DESC_SETS_COUNT; ++i)
    {
        descSetLayouts[i] = 0;
    }
    handle = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Create graphics pipeline layout                                           //
//  return : True if graphics layout is successfully created                  //
////////////////////////////////////////////////////////////////////////////////
bool GraphicsLayout::createLayout(VkDevice& vulkanDevice, Swapchain& swapchain)
{
    // Check Vulkan device
    if (!vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Check render pass
    if (!swapchain.renderPass)
    {
        // Invalid render pass
        return false;
    }

    // Create descriptor set layouts
    if (!createDescriptorSetLayouts(vulkanDevice))
    {
        // Could not create descriptor set layouts
        SysMessage::box() << "[0x3044] Could not create descriptor layouts\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Create pipeline layouts
    if (!createPipelineLayouts(vulkanDevice))
    {
        // Could not create pipeline layouts
        SysMessage::box() << "[0x3045] Could not create pipeline layouts\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Graphics pipeline successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create descriptor set layouts                                             //
//  return : True if descriptor layout is successfully created                //
////////////////////////////////////////////////////////////////////////////////
bool GraphicsLayout::createDescriptorSetLayouts(VkDevice& vulkanDevice)
{
    // Check Vulkan device
    if (!vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Descriptor sets bindings
    VkDescriptorSetLayoutBinding descriptorSetBindings[DESC_SETS_COUNT];

    descriptorSetBindings[DESC_MATRICES].binding = 0;
    descriptorSetBindings[DESC_MATRICES].descriptorType =
        VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorSetBindings[DESC_MATRICES].descriptorCount = 1;
    descriptorSetBindings[DESC_MATRICES].stageFlags =
        VK_SHADER_STAGE_VERTEX_BIT;
    descriptorSetBindings[DESC_MATRICES].pImmutableSamplers = 0;

    descriptorSetBindings[DESC_TEXTURE].binding = 0;
    descriptorSetBindings[DESC_TEXTURE].descriptorType =
        VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptorSetBindings[DESC_TEXTURE].descriptorCount = 1;
    descriptorSetBindings[DESC_TEXTURE].stageFlags =
        VK_SHADER_STAGE_FRAGMENT_BIT;
    descriptorSetBindings[DESC_TEXTURE].pImmutableSamplers = 0;

    // Descriptor sets infos
    VkDescriptorSetLayoutCreateInfo descriptorSetInfo[DESC_SETS_COUNT];

    descriptorSetInfo[DESC_MATRICES].sType =
        VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    descriptorSetInfo[DESC_MATRICES].pNext = 0;
    descriptorSetInfo[DESC_MATRICES].flags = 0;
    descriptorSetInfo[DESC_MATRICES].bindingCount = 1;
    descriptorSetInfo[DESC_MATRICES].pBindings =
        &descriptorSetBindings[DESC_MATRICES];

    descriptorSetInfo[DESC_TEXTURE].sType =
        VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    descriptorSetInfo[DESC_TEXTURE].pNext = 0;
    descriptorSetInfo[DESC_TEXTURE].flags = 0;
    descriptorSetInfo[DESC_TEXTURE].bindingCount = 1;
    descriptorSetInfo[DESC_TEXTURE].pBindings =
        &descriptorSetBindings[DESC_TEXTURE];

    // Create descriptor sets layouts
    for (uint32_t i = 0; i < DESC_SETS_COUNT; ++i)
    {
        // Create current descriptor set layout
        if (vkCreateDescriptorSetLayout(vulkanDevice, &descriptorSetInfo[i], 0,
            &descSetLayouts[i]) != VK_SUCCESS)
        {
            // Could not create descriptor set layout
            return false;
        }
        if (!descSetLayouts[i])
        {
            // Invalid descriptor set layout
            return false;
        }

        // Copy descriptor set layouts to match swapchain frames count
        for (uint32_t j = 0; j < RendererMaxSwapchainFrames; ++j)
        {
            swapSetLayouts[(i*RendererMaxSwapchainFrames)+j] =
                descSetLayouts[i];
        }
    }

    // Descriptor set layouts successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create pipeline layouts                                                   //
//  return : True if pipeline layout is successfully created                  //
////////////////////////////////////////////////////////////////////////////////
bool GraphicsLayout::createPipelineLayouts(VkDevice& vulkanDevice)
{
    // Check Vulkan device
    if (!vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Check descriptor set layouts
    for (uint32_t i = 0; i < DESC_SETS_COUNT; ++i)
    {
        if (!descSetLayouts[i])
        {
            // Invalid descriptor set layout
            return false;
        }
    }

    // Check PushConstantData size
    size_t pushConstantDataSize = sizeof(PushConstantData);
    if (pushConstantDataSize != (sizeof(float)*9))
    {
        // Invalid PushConstantData size
        return false;
    }

    // Set push constant range
    VkPushConstantRange pushConstantRange[PUSH_CONSTANT_COUNT];

    // Vertex push constant
    pushConstantRange[PUSH_CONSTANT_VERTEX].stageFlags =
        VK_SHADER_STAGE_VERTEX_BIT;
    pushConstantRange[PUSH_CONSTANT_VERTEX].offset = PushConstantMatrixOffset;
    pushConstantRange[PUSH_CONSTANT_VERTEX].size = PushConstantMatrixSize;

    // Fragment push constants
    pushConstantRange[PUSH_CONSTANT_FRAGMENT].stageFlags =
        VK_SHADER_STAGE_FRAGMENT_BIT;
    pushConstantRange[PUSH_CONSTANT_FRAGMENT].offset = PushConstantDataOffset;
    pushConstantRange[PUSH_CONSTANT_FRAGMENT].size = PushConstantDataSize;

    // Create pipeline layout
    VkPipelineLayoutCreateInfo pipelineInfo;
    pipelineInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineInfo.pNext = 0;
    pipelineInfo.flags = 0;
    pipelineInfo.setLayoutCount = DESC_SETS_COUNT;
    pipelineInfo.pSetLayouts = descSetLayouts;
    pipelineInfo.pushConstantRangeCount = PUSH_CONSTANT_COUNT;
    pipelineInfo.pPushConstantRanges = pushConstantRange;

    if (vkCreatePipelineLayout(
        vulkanDevice, &pipelineInfo, 0, &handle) != VK_SUCCESS)
    {
        // Could not create pipeline layout
        return false;
    }
    if (!handle)
    {
        // Invalid pipeline layout
        return false;
    }

    // Pipeline layout successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy pipeline layout                                                   //
////////////////////////////////////////////////////////////////////////////////
void GraphicsLayout::destroyLayout(VkDevice& vulkanDevice)
{
    if (vulkanDevice)
    {
        for (uint32_t i = 0; i < DESC_SETS_COUNT; ++i)
        {
            // Destroy descriptor set layout
            if (descSetLayouts[i] && vkDestroyDescriptorSetLayout)
            {
                vkDestroyDescriptorSetLayout(
                    vulkanDevice, descSetLayouts[i], 0
                );
            }
        }

        // Destroy pipeline layout
        if (handle && vkDestroyPipelineLayout)
        {
            vkDestroyPipelineLayout(vulkanDevice, handle, 0);
        }
    }

    for (uint32_t i = 0; i < RendererMaxSwapchainFrames*DESC_SETS_COUNT; ++i)
    {
        swapSetLayouts[i] = 0;
    }
    for (uint32_t i = 0; i < DESC_SETS_COUNT; ++i)
    {
        descSetLayouts[i] = 0;
    }
    handle = 0;
}
