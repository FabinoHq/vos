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
//     Renderer/Vulkan/GraphicsPipeline.cpp : Graphics pipeline management    //
////////////////////////////////////////////////////////////////////////////////
#include "GraphicsPipeline.h"


////////////////////////////////////////////////////////////////////////////////
//  GraphicsPipeline default constructor                                      //
////////////////////////////////////////////////////////////////////////////////
GraphicsPipeline::GraphicsPipeline() :
handle(0),
layout(0)
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
//  GraphicsPipeline destructor                                               //
////////////////////////////////////////////////////////////////////////////////
GraphicsPipeline::~GraphicsPipeline()
{
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames*DESC_SETS_COUNT; ++i)
    {
        swapSetLayouts[i] = 0;
    }
    for (uint32_t i = 0; i < DESC_SETS_COUNT; ++i)
    {
        descSetLayouts[i] = 0;
    }
    layout = 0;
    handle = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Create graphics pipeline                                                  //
//  return : True if graphics pipeline is successfully created                //
////////////////////////////////////////////////////////////////////////////////
bool GraphicsPipeline::createPipeline(VkDevice& vulkanDevice,
    Swapchain& swapchain, Shader& shader)
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

    // Check shader
    if (!shader.isValid())
    {
        // Invalid shader
        return false;
    }

    // Shader stage
    VkPipelineShaderStageCreateInfo shaderStages[2];
    shader.getShaderStagesInfo(shaderStages);

    // Input binding
    VkVertexInputBindingDescription vertexBinding;
    vertexBinding.binding = 0;
    vertexBinding.stride = sizeof(VertexData);
    vertexBinding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    // Vertex attribute
    VkVertexInputAttributeDescription vertexAttributes[2];

    vertexAttributes[0].location = 0;
    vertexAttributes[0].binding = vertexBinding.binding;
    vertexAttributes[0].format = VK_FORMAT_R32G32B32_SFLOAT;
    vertexAttributes[0].offset = 0;

    vertexAttributes[1].location = 1;
    vertexAttributes[1].binding = vertexBinding.binding;
    vertexAttributes[1].format = VK_FORMAT_R32G32_SFLOAT;
    vertexAttributes[1].offset = sizeof(float) * 3;

    // Vertex input
    VkPipelineVertexInputStateCreateInfo vertexInput;
    vertexInput.sType =
        VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInput.pNext = 0;
    vertexInput.flags = 0;
    vertexInput.vertexBindingDescriptionCount = 1;
    vertexInput.pVertexBindingDescriptions = &vertexBinding;
    vertexInput.vertexAttributeDescriptionCount = 2;
    vertexInput.pVertexAttributeDescriptions = vertexAttributes;

    // Input assembly
    VkPipelineInputAssemblyStateCreateInfo inputAssembly;
    inputAssembly.sType =
        VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.pNext = 0;
    inputAssembly.flags = 0;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    // Viewport
    VkPipelineViewportStateCreateInfo viewportInfo;
    viewportInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportInfo.pNext = 0;
    viewportInfo.flags = 0;
    viewportInfo.viewportCount = 1;
    viewportInfo.pViewports = 0;
    viewportInfo.scissorCount = 1;
    viewportInfo.pScissors = 0;

    // Rasterizer
    VkPipelineRasterizationStateCreateInfo rasterizerInfo;
    rasterizerInfo.sType =
        VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizerInfo.pNext = 0;
    rasterizerInfo.flags = 0;
    rasterizerInfo.depthClampEnable = VK_FALSE;
    rasterizerInfo.rasterizerDiscardEnable = VK_FALSE;
    rasterizerInfo.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizerInfo.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizerInfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rasterizerInfo.depthBiasEnable = VK_FALSE;
    rasterizerInfo.depthBiasConstantFactor = 0.0f;
    rasterizerInfo.depthBiasClamp = 0.0f;
    rasterizerInfo.depthBiasSlopeFactor = 0.0f;
    rasterizerInfo.lineWidth = 1.0f;

    // Multisample
    VkPipelineMultisampleStateCreateInfo multisampleInfo;
    multisampleInfo.sType =
        VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampleInfo.pNext = 0;
    multisampleInfo.flags = 0;
    multisampleInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisampleInfo.sampleShadingEnable = VK_FALSE;
    multisampleInfo.minSampleShading = 1.0f;
    multisampleInfo.pSampleMask = 0;
    multisampleInfo.alphaToCoverageEnable = VK_FALSE;
    multisampleInfo.alphaToOneEnable = VK_FALSE;

    // Blend
    VkPipelineColorBlendAttachmentState colorBlend;
    colorBlend.blendEnable = VK_TRUE;
    colorBlend.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    colorBlend.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorBlend.colorBlendOp = VK_BLEND_OP_ADD;
    colorBlend.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlend.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorBlend.alphaBlendOp = VK_BLEND_OP_ADD;
    colorBlend.colorWriteMask =
        VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
        VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

    VkPipelineColorBlendStateCreateInfo blendState;
    blendState.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    blendState.pNext = 0;
    blendState.flags = 0;
    blendState.logicOpEnable = VK_FALSE;
    blendState.logicOp = VK_LOGIC_OP_COPY;
    blendState.attachmentCount = 1;
    blendState.pAttachments = &colorBlend;
    blendState.blendConstants[0] = 0.0f;
    blendState.blendConstants[1] = 0.0f;
    blendState.blendConstants[2] = 0.0f;
    blendState.blendConstants[3] = 0.0f;

    // Dynamic states
    VkDynamicState dynamicStates[2];
    dynamicStates[0] = VK_DYNAMIC_STATE_VIEWPORT;
    dynamicStates[1] = VK_DYNAMIC_STATE_SCISSOR;

    VkPipelineDynamicStateCreateInfo dynamicInfo;
    dynamicInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicInfo.pNext = 0;
    dynamicInfo.flags = 0;
    dynamicInfo.dynamicStateCount = 2;
    dynamicInfo.pDynamicStates = dynamicStates;

    // Create graphics pipeline
    VkGraphicsPipelineCreateInfo pipelineInfo;
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.pNext = 0;
    pipelineInfo.flags = 0;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = &vertexInput;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pTessellationState = 0;
    pipelineInfo.pViewportState = &viewportInfo;
    pipelineInfo.pRasterizationState = &rasterizerInfo;
    pipelineInfo.pMultisampleState = &multisampleInfo;
    pipelineInfo.pDepthStencilState = 0;
    pipelineInfo.pColorBlendState = &blendState;
    pipelineInfo.pDynamicState = &dynamicInfo;
    pipelineInfo.layout = layout;
    pipelineInfo.renderPass = swapchain.renderPass;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = 0;
    pipelineInfo.basePipelineIndex = -1;

    if (vkCreateGraphicsPipelines(
        vulkanDevice, 0, 1, &pipelineInfo, 0, &handle) != VK_SUCCESS)
    {
        // Could not create pipeline
        return false;
    }
    if (!handle)
    {
        // Invalid pipeline handle
        return false;
    }

    // Graphics pipeline successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create descriptor set layouts                                             //
//  return : True if descriptor layout is successfully created                //
////////////////////////////////////////////////////////////////////////////////
bool GraphicsPipeline::createDescriptorSetLayouts(VkDevice& vulkanDevice)
{
    // Check Vulkan device
    if (!vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Create descriptor set layouts
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

    VkDescriptorSetLayoutCreateInfo descriptorSetInfo;
    descriptorSetInfo.sType =
        VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    descriptorSetInfo.pNext = 0;
    descriptorSetInfo.flags = 0;
    descriptorSetInfo.bindingCount = 1;
    descriptorSetInfo.pBindings = &descriptorSetBindings[DESC_MATRICES];

    VkDescriptorSetLayoutCreateInfo descriptorSetInfo2;
    descriptorSetInfo2.sType =
        VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    descriptorSetInfo2.pNext = 0;
    descriptorSetInfo2.flags = 0;
    descriptorSetInfo2.bindingCount = 1;
    descriptorSetInfo2.pBindings = &descriptorSetBindings[DESC_TEXTURE];

    // Create matrices descriptor set layout
    if (vkCreateDescriptorSetLayout(vulkanDevice, &descriptorSetInfo, 0,
        &descSetLayouts[DESC_MATRICES]) != VK_SUCCESS)
    {
        // Could not create matrices descriptor set layout
        return false;
    }
    if (!descSetLayouts[DESC_MATRICES])
    {
        // Invalid matrices descriptor set layout
        return false;
    }

    // Create texture descriptor set layout
    if (vkCreateDescriptorSetLayout(vulkanDevice, &descriptorSetInfo2, 0,
        &descSetLayouts[DESC_TEXTURE]) != VK_SUCCESS)
    {
        // Could not create texture descriptor set layout
        return false;
    }
    if (!descSetLayouts[DESC_TEXTURE])
    {
        // Invalid texture descriptor set layout
        return false;
    }

    // Copy descriptor set layouts to match swapchain frames count
    for (uint32_t i = 0; i < DESC_SETS_COUNT; ++i)
    {
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
bool GraphicsPipeline::createPipelineLayouts(VkDevice& vulkanDevice)
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

    // Create pipeline layout
    VkPushConstantRange pushConstantRange;
    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    pushConstantRange.offset = 0;
    pushConstantRange.size = sizeof(Matrix4x4::mat);

    VkPipelineLayoutCreateInfo pipelineInfo;
    pipelineInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineInfo.pNext = 0;
    pipelineInfo.flags = 0;
    pipelineInfo.setLayoutCount = DESC_SETS_COUNT;
    pipelineInfo.pSetLayouts = descSetLayouts;
    pipelineInfo.pushConstantRangeCount = 1;
    pipelineInfo.pPushConstantRanges = &pushConstantRange;

    if (vkCreatePipelineLayout(
        vulkanDevice, &pipelineInfo, 0, &layout) != VK_SUCCESS)
    {
        // Could not create pipeline layout
        return false;
    }
    if (!layout)
    {
        // Invalid pipeline layout
        return false;
    }

    // Pipeline layout successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy pipeline                                                          //
////////////////////////////////////////////////////////////////////////////////
void GraphicsPipeline::destroyPipeline(VkDevice& vulkanDevice)
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
        if (layout && vkDestroyPipelineLayout)
        {
            vkDestroyPipelineLayout(vulkanDevice, layout, 0);
        }

        // Destroy pipeline
        if (handle && vkDestroyPipeline)
        {
            vkDestroyPipeline(vulkanDevice, handle, 0);
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
    layout = 0;
    handle = 0;
}