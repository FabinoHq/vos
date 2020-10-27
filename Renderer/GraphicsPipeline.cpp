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
//     Renderer/GraphicsPipeline.cpp : Vulkan Graphics pipeline management    //
////////////////////////////////////////////////////////////////////////////////
#include "GraphicsPipeline.h"


////////////////////////////////////////////////////////////////////////////////
//  GraphicsPipeline default constructor                                      //
////////////////////////////////////////////////////////////////////////////////
GraphicsPipeline::GraphicsPipeline() :
handle(0),
layout(0),
descPool(0),
descSetLayout(0)
{
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        descSetLayouts[i] = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  GraphicsPipeline destructor                                               //
////////////////////////////////////////////////////////////////////////////////
GraphicsPipeline::~GraphicsPipeline()
{
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        descSetLayouts[i] = 0;
    }
    descSetLayout = 0;
    descPool = 0;
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

    // Create descriptor pool
    if (!createDescriptorPool(vulkanDevice))
    {
        // Could not create descriptor pool
        SysMessage::box() << "[0x3044] Could not create descriptor pool\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Create descriptor set layout
    if (!createDescriptorSetLayout(vulkanDevice))
    {
        // Could not create descriptor set layout
        SysMessage::box() << "[0x3045] Could not create descriptor layout\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Create pipeline layout
    if (!createPipelineLayout(vulkanDevice))
    {
        // Could not create pipeline layout
        SysMessage::box() << "[0x3046] Could not create pipeline layout\n";
        SysMessage::box() << "Please update your graphics drivers";
        return false;
    }

    // Check vertex shader
    if (!shader.vertexShader)
    {
        // Invalid vertex shader
        return false;
    }

    // Check fragment shader
    if (!shader.fragmentShader)
    {
        // Invalid fragment shader
        return false;
    }

    // Shader stage
    VkPipelineShaderStageCreateInfo shaderStage[2];

    shaderStage[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStage[0].pNext = 0;
    shaderStage[0].flags = 0;
    shaderStage[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
    shaderStage[0].module = shader.vertexShader;
    shaderStage[0].pName = "main";
    shaderStage[0].pSpecializationInfo = 0;

    shaderStage[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStage[1].pNext = 0;
    shaderStage[1].flags = 0;
    shaderStage[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    shaderStage[1].module = shader.fragmentShader;
    shaderStage[1].pName = "main";
    shaderStage[1].pSpecializationInfo = 0;

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
    colorBlend.blendEnable = VK_FALSE;
    colorBlend.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlend.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
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
    pipelineInfo.pStages = shaderStage;
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
//  Create descriptor pool                                                    //
//  return : True if descriptor pool is successfully created                  //
////////////////////////////////////////////////////////////////////////////////
bool GraphicsPipeline::createDescriptorPool(VkDevice& vulkanDevice)
{
    // Check Vulkan device
    if (!vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Create descriptor pool
    VkDescriptorPoolSize poolSize[2];

    poolSize[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSize[0].descriptorCount = RendererMaxSwapchainFrames;

    poolSize[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    poolSize[1].descriptorCount = RendererMaxSwapchainFrames;

    VkDescriptorPoolCreateInfo poolInfo;
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.pNext = 0;
    poolInfo.flags = 0;
    poolInfo.maxSets = RendererMaxSwapchainFrames;
    poolInfo.poolSizeCount = 2;
    poolInfo.pPoolSizes = poolSize;

    if (vkCreateDescriptorPool(
        vulkanDevice, &poolInfo, 0, &descPool) != VK_SUCCESS)
    {
        // Could not create descriptor pool
        return false;
    }
    if (!descPool)
    {
        // Invalid descriptor pool
        return false;
    }

    // Descriptor pool successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create descriptor set layout                                              //
//  return : True if descriptor layout is successfully created                //
////////////////////////////////////////////////////////////////////////////////
bool GraphicsPipeline::createDescriptorSetLayout(VkDevice& vulkanDevice)
{
    // Check Vulkan device
    if (!vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Create descriptor set layout
    VkDescriptorSetLayoutBinding descriptorSetBindings[2];

    descriptorSetBindings[0].binding = 0;
    descriptorSetBindings[0].descriptorType =
        VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorSetBindings[0].descriptorCount = 1;
    descriptorSetBindings[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    descriptorSetBindings[0].pImmutableSamplers = 0;

    descriptorSetBindings[1].binding = 1;
    descriptorSetBindings[1].descriptorType =
        VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptorSetBindings[1].descriptorCount = 1;
    descriptorSetBindings[1].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    descriptorSetBindings[1].pImmutableSamplers = 0;

    VkDescriptorSetLayoutCreateInfo descriptorSetInfo;
    descriptorSetInfo.sType =
        VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    descriptorSetInfo.pNext = 0;
    descriptorSetInfo.flags = 0;
    descriptorSetInfo.bindingCount = 2;
    descriptorSetInfo.pBindings = descriptorSetBindings;

    if (vkCreateDescriptorSetLayout(vulkanDevice,
        &descriptorSetInfo, 0, &descSetLayout) != VK_SUCCESS)
    {
        // Could not create descriptor set layout
        return false;
    }
    if (!descSetLayout)
    {
        // Invalid descriptor set layout
        return false;
    }

    // Duplicate descriptor set layout to match descriptor sets count
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        descSetLayouts[i] = descSetLayout;
    }

    // Descriptor set layout successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create pipeline layout                                                    //
//  return : True if pipeline layout is successfully created                  //
////////////////////////////////////////////////////////////////////////////////
bool GraphicsPipeline::createPipelineLayout(VkDevice& vulkanDevice)
{
    // Check Vulkan device
    if (!vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Check descriptor set layout
    if (!descSetLayout)
    {
        // Invalid descriptor set layout
        return false;
    }

    // Create pipeline layout
    VkPushConstantRange pushConstantRange;
    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    pushConstantRange.offset = 0;
    pushConstantRange.size = sizeof(float)*16;

    VkPipelineLayoutCreateInfo pipelineInfo;
    pipelineInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineInfo.pNext = 0;
    pipelineInfo.flags = 0;
    pipelineInfo.setLayoutCount = 1;
    pipelineInfo.pSetLayouts = &descSetLayout;
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
        // Destroy descriptor set layout
        if (descSetLayout && vkDestroyDescriptorSetLayout)
        {
            vkDestroyDescriptorSetLayout(vulkanDevice, descSetLayout, 0);
        }

        // Destroy descriptor pool
        if (descPool && vkDestroyDescriptorPool)
        {
            vkDestroyDescriptorPool(vulkanDevice, descPool, 0);
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

    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        descSetLayouts[i] = 0;
    }
    descSetLayout = 0;
    descPool = 0;
    layout = 0;
    handle = 0;
}
