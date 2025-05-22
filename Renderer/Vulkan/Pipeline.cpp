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
//     Renderer/Vulkan/Pipeline.cpp : Graphics pipeline management            //
////////////////////////////////////////////////////////////////////////////////
#include "Pipeline.h"


////////////////////////////////////////////////////////////////////////////////
//  Pipeline default constructor                                              //
////////////////////////////////////////////////////////////////////////////////
Pipeline::Pipeline() :
m_pipeline(0),
m_vertexShader(),
m_fragmentShader()
{

}

////////////////////////////////////////////////////////////////////////////////
//  Pipeline destructor                                                       //
////////////////////////////////////////////////////////////////////////////////
Pipeline::~Pipeline()
{
    m_pipeline = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Create vertex shader                                                      //
//  return : True if the vertex shader is successfully created                //
////////////////////////////////////////////////////////////////////////////////
bool Pipeline::createVertexShader(
    const uint32_t* vertexSource, const size_t vertexSize)
{
    // Destroy previous vertex shader
    if (m_vertexShader.isValid())
    {
        m_vertexShader.destroyShader();
    }

    // Create vertex shader
    if (!m_vertexShader.createShader(vertexSource, vertexSize))
    {
        // Invalid vertex shader
        return false;
    }

    // Vertex shader successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create fragment shader                                                    //
//  return : True if the fragment shader is successfully created              //
////////////////////////////////////////////////////////////////////////////////
bool Pipeline::createFragmentShader(
    const uint32_t* fragmentSource, const size_t fragmentSize)
{
    // Destroy previous fragment shader
    if (m_fragmentShader.isValid())
    {
        m_fragmentShader.destroyShader();
    }

    // Create fragment shader
    if (!m_fragmentShader.createShader(fragmentSource, fragmentSize))
    {
        // Invalid fragment shader
        return false;
    }

    // Fragment shader successfully created
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Create compositing pipeline                                               //
//  return : True if compositing pipeline is successfully created             //
////////////////////////////////////////////////////////////////////////////////
bool Pipeline::createCompositingPipeline(AlphaBlendingMode blendingMode)
{
    // Check current pipeline
    if (m_pipeline)
    {
        // Destroy current pipeline
        destroyPipeline();
    }

    // Check vertex shader
    if (!m_vertexShader.isValid())
    {
        // Invalid vertex shader
        return false;
    }

    // Check fragment shader
    if (!m_fragmentShader.isValid())
    {
        // Invalid fragment shader
        return false;
    }

    // Shader stages
    VkPipelineShaderStageCreateInfo* shaderStages =
        GSysMemory.alloc<VkPipelineShaderStageCreateInfo>(
            RendererShaderStagesCount, SYSMEMORY_RENDERER
        );
    if (!shaderStages) { return false; }
    for (uint32_t i = 0; i < RendererShaderStagesCount; ++i)
    {
        shaderStages[i] = VkPipelineShaderStageCreateInfo();
    }
    setShaderStages(shaderStages);

    // Vertex attributes
    VkVertexInputBindingDescription vertexBinding;
    VkVertexInputAttributeDescription* vertexAttributes =
        GSysMemory.alloc<VkVertexInputAttributeDescription>(
            RendererMaxVertexAttribsCount, SYSMEMORY_RENDERER
        );
    if (!vertexAttributes) { return false; }
    for (uint32_t i = 0; i < RendererMaxVertexAttribsCount; ++i)
    {
        vertexAttributes[i] = VkVertexInputAttributeDescription();
    }
    uint32_t vertexAttribsCount = 0;
    setVertexInputs(vertexBinding, vertexAttributes,
        vertexAttribsCount, VERTEX_INPUTS_DEFAULT);

    // Vertex input
    VkPipelineVertexInputStateCreateInfo vertexInput;
    vertexInput.sType =
        VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInput.pNext = 0;
    vertexInput.flags = 0;
    vertexInput.vertexBindingDescriptionCount = 1;
    vertexInput.pVertexBindingDescriptions = &vertexBinding;
    vertexInput.vertexAttributeDescriptionCount = vertexAttribsCount;
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

    // Depth stencil
    VkStencilOpState stencilOpFront;
    stencilOpFront.failOp = VK_STENCIL_OP_ZERO;
    stencilOpFront.passOp = VK_STENCIL_OP_ZERO;
    stencilOpFront.depthFailOp = VK_STENCIL_OP_ZERO;
    stencilOpFront.compareOp = VK_COMPARE_OP_NEVER;
    stencilOpFront.compareMask = 0;
    stencilOpFront.writeMask = 0;
    stencilOpFront.reference = 0;

    VkStencilOpState stencilOpBack;
    stencilOpBack.failOp = VK_STENCIL_OP_ZERO;
    stencilOpBack.passOp = VK_STENCIL_OP_ZERO;
    stencilOpBack.depthFailOp = VK_STENCIL_OP_ZERO;
    stencilOpBack.compareOp = VK_COMPARE_OP_NEVER;
    stencilOpBack.compareMask = 0;
    stencilOpBack.writeMask = 0;
    stencilOpBack.reference = 0;

    VkPipelineDepthStencilStateCreateInfo depthStencil;
    depthStencil.sType =
        VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencil.pNext = 0;
    depthStencil.flags = 0;
    depthStencil.depthTestEnable = VK_FALSE;
    depthStencil.depthWriteEnable = VK_FALSE;
    depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
    depthStencil.depthBoundsTestEnable = VK_FALSE;
    depthStencil.stencilTestEnable = VK_FALSE;
    depthStencil.front = stencilOpFront;
    depthStencil.back = stencilOpBack;
    depthStencil.minDepthBounds = 0.0f;
    depthStencil.maxDepthBounds = 1.0f;

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
        (VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
        VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT);
    if (blendingMode != ALPHA_BLENDING_NONE)
    {
        colorBlend.blendEnable = VK_TRUE;
        colorBlend.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
        if (blendingMode == ALPHA_BLENDING_STRAIGHT)
        {
            colorBlend.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
        }
        colorBlend.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        colorBlend.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        colorBlend.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    }

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
    pipelineInfo.stageCount = RendererShaderStagesCount;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = &vertexInput;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pTessellationState = 0;
    pipelineInfo.pViewportState = &viewportInfo;
    pipelineInfo.pRasterizationState = &rasterizerInfo;
    pipelineInfo.pMultisampleState = &multisampleInfo;
    pipelineInfo.pDepthStencilState = &depthStencil;
    pipelineInfo.pColorBlendState = &blendState;
    pipelineInfo.pDynamicState = &dynamicInfo;
    pipelineInfo.layout = GGraphicsLayout.handle;
    pipelineInfo.renderPass = GSwapchain.renderPass;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = 0;
    pipelineInfo.basePipelineIndex = -1;

    if (vkCreateGraphicsPipelines(GVulkanDevice, 0, 1, &pipelineInfo,
        SYSVKMEMORY_PIPELINE_ALLOC, &m_pipeline) != VK_SUCCESS)
    {
        // Could not create pipeline
        return false;
    }
    if (!m_pipeline)
    {
        // Invalid pipeline handle
        return false;
    }

    // Pipeline successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create pipeline                                                           //
//  return : True if pipeline is successfully created                         //
////////////////////////////////////////////////////////////////////////////////
bool Pipeline::createPipeline(
    VertexInputsType vertexInputsType, bool depthTest, bool backFaceCulling,
    AlphaBlendingMode blendingMode)
{
    // Check current pipeline
    if (m_pipeline)
    {
        // Destroy current pipeline
        destroyPipeline();
    }

    // Check vertex shader
    if (!m_vertexShader.isValid())
    {
        // Invalid vertex shader
        return false;
    }

    // Check fragment shader
    if (!m_fragmentShader.isValid())
    {
        // Invalid fragment shader
        return false;
    }

    // Shader stages
    VkPipelineShaderStageCreateInfo* shaderStages =
        GSysMemory.alloc<VkPipelineShaderStageCreateInfo>(
            RendererShaderStagesCount, SYSMEMORY_RENDERER
        );
    if (!shaderStages) { return false; }
    for (uint32_t i = 0; i < RendererShaderStagesCount; ++i)
    {
        shaderStages[i] = VkPipelineShaderStageCreateInfo();
    }
    setShaderStages(shaderStages);

    // Vertex attributes
    VkVertexInputBindingDescription vertexBinding;
    VkVertexInputAttributeDescription* vertexAttributes =
        GSysMemory.alloc<VkVertexInputAttributeDescription>(
            RendererMaxVertexAttribsCount, SYSMEMORY_RENDERER
        );
    if (!vertexAttributes) { return false; }
    for (uint32_t i = 0; i < RendererMaxVertexAttribsCount; ++i)
    {
        vertexAttributes[i] = VkVertexInputAttributeDescription();
    }
    uint32_t vertexAttribsCount = 0;
    setVertexInputs(vertexBinding, vertexAttributes,
        vertexAttribsCount, vertexInputsType);

    // Vertex input
    VkPipelineVertexInputStateCreateInfo vertexInput;
    vertexInput.sType =
        VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInput.pNext = 0;
    vertexInput.flags = 0;
    vertexInput.vertexBindingDescriptionCount = 1;
    vertexInput.pVertexBindingDescriptions = &vertexBinding;
    vertexInput.vertexAttributeDescriptionCount = vertexAttribsCount;
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
    rasterizerInfo.cullMode = VK_CULL_MODE_NONE;
    if (backFaceCulling)
    {
        rasterizerInfo.cullMode = VK_CULL_MODE_BACK_BIT;
    }
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
    switch (GSysSettings.getMultiSamplingMode())
    {
        case MULTI_SAMPLING_2X:
            multisampleInfo.rasterizationSamples = VK_SAMPLE_COUNT_2_BIT;
            break;
        case MULTI_SAMPLING_4X:
            multisampleInfo.rasterizationSamples = VK_SAMPLE_COUNT_4_BIT;
            break;
        case MULTI_SAMPLING_8X:
            multisampleInfo.rasterizationSamples = VK_SAMPLE_COUNT_8_BIT;
            break;
        default:
            multisampleInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
            break;
    }
    multisampleInfo.sampleShadingEnable = VK_FALSE;
    multisampleInfo.minSampleShading = 1.0f;
    switch (GSysSettings.getSampleShadingMode())
    {
        case SAMPLE_SHADING_QUARTER:
            multisampleInfo.sampleShadingEnable = VK_TRUE;
            multisampleInfo.minSampleShading = 0.25f;
            break;
        case SAMPLE_SHADING_HALF:
            multisampleInfo.sampleShadingEnable = VK_TRUE;
            multisampleInfo.minSampleShading = 0.5f;
            break;
        case SAMPLE_SHADING_ONE:
            multisampleInfo.sampleShadingEnable = VK_TRUE;
            multisampleInfo.minSampleShading = 1.0f;
            break;
        default:
            multisampleInfo.sampleShadingEnable = VK_FALSE;
            multisampleInfo.minSampleShading = 1.0f;
            break;
    }
    multisampleInfo.pSampleMask = 0;
    multisampleInfo.alphaToCoverageEnable = VK_FALSE;
    multisampleInfo.alphaToOneEnable = VK_FALSE;

    // Depth stencil
    VkStencilOpState stencilOpFront;
    stencilOpFront.failOp = VK_STENCIL_OP_ZERO;
    stencilOpFront.passOp = VK_STENCIL_OP_ZERO;
    stencilOpFront.depthFailOp = VK_STENCIL_OP_ZERO;
    stencilOpFront.compareOp = VK_COMPARE_OP_NEVER;
    stencilOpFront.compareMask = 0;
    stencilOpFront.writeMask = 0;
    stencilOpFront.reference = 0;

    VkStencilOpState stencilOpBack;
    stencilOpBack.failOp = VK_STENCIL_OP_ZERO;
    stencilOpBack.passOp = VK_STENCIL_OP_ZERO;
    stencilOpBack.depthFailOp = VK_STENCIL_OP_ZERO;
    stencilOpBack.compareOp = VK_COMPARE_OP_NEVER;
    stencilOpBack.compareMask = 0;
    stencilOpBack.writeMask = 0;
    stencilOpBack.reference = 0;

    VkPipelineDepthStencilStateCreateInfo depthStencil;
    depthStencil.sType =
        VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencil.pNext = 0;
    depthStencil.flags = 0;
    depthStencil.depthTestEnable = VK_FALSE;
    depthStencil.depthWriteEnable = VK_FALSE;
    if (depthTest)
    {
        depthStencil.depthTestEnable = VK_TRUE;
        depthStencil.depthWriteEnable = VK_TRUE;
    }
    depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
    depthStencil.depthBoundsTestEnable = VK_FALSE;
    depthStencil.stencilTestEnable = VK_FALSE;
    depthStencil.front = stencilOpFront;
    depthStencil.back = stencilOpBack;
    depthStencil.minDepthBounds = 0.0f;
    depthStencil.maxDepthBounds = 1.0f;

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
        (VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
        VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT);
    if (blendingMode != ALPHA_BLENDING_NONE)
    {
        colorBlend.blendEnable = VK_TRUE;
        colorBlend.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
        if (blendingMode == ALPHA_BLENDING_STRAIGHT)
        {
            colorBlend.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
        }
        colorBlend.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        colorBlend.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        colorBlend.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    }

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
    pipelineInfo.stageCount = RendererShaderStagesCount;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = &vertexInput;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pTessellationState = 0;
    pipelineInfo.pViewportState = &viewportInfo;
    pipelineInfo.pRasterizationState = &rasterizerInfo;
    pipelineInfo.pMultisampleState = &multisampleInfo;
    pipelineInfo.pDepthStencilState = &depthStencil;
    pipelineInfo.pColorBlendState = &blendState;
    pipelineInfo.pDynamicState = &dynamicInfo;
    pipelineInfo.layout = GGraphicsLayout.handle;
    pipelineInfo.renderPass = GMainRenderer.backchain.renderPass;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = 0;
    pipelineInfo.basePipelineIndex = -1;

    if (vkCreateGraphicsPipelines(GVulkanDevice, 0, 1, &pipelineInfo,
        SYSVKMEMORY_PIPELINE_ALLOC, &m_pipeline) != VK_SUCCESS)
    {
        // Could not create pipeline
        return false;
    }
    if (!m_pipeline)
    {
        // Invalid pipeline handle
        return false;
    }

    // Pipeline successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy pipeline                                                          //
////////////////////////////////////////////////////////////////////////////////
void Pipeline::destroyPipeline()
{
    // Check Vulkan device
    if (!GVulkanDevice)
    {
        // Invalid Vulkan device
        return;
    }

    // Destroy pipeline
    if (m_pipeline)
    {
        vkDestroyPipeline(
            GVulkanDevice, m_pipeline, SYSVKMEMORY_PIPELINE_ALLOC
        );
    }
    m_pipeline = 0;

    // Destroy fragment shader
    m_fragmentShader.destroyShader();

    // Destroy vertex shader
    m_vertexShader.destroyShader();
}


////////////////////////////////////////////////////////////////////////////////
//  Set shader stages                                                         //
////////////////////////////////////////////////////////////////////////////////
void Pipeline::setShaderStages(VkPipelineShaderStageCreateInfo* shaderStages)
{
    // Vertex shader
    shaderStages[0] = VkPipelineShaderStageCreateInfo();
    shaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[0].pNext = 0;
    shaderStages[0].flags = 0;
    shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
    shaderStages[0].module = m_vertexShader.handle;
    shaderStages[0].pName = "main";
    shaderStages[0].pSpecializationInfo = 0;

    // Fragment shader
    shaderStages[1] = VkPipelineShaderStageCreateInfo();
    shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[1].pNext = 0;
    shaderStages[1].flags = 0;
    shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    shaderStages[1].module = m_fragmentShader.handle;
    shaderStages[1].pName = "main";
    shaderStages[1].pSpecializationInfo = 0;
}

////////////////////////////////////////////////////////////////////////////////
//  Set vertex inputs                                                         //
////////////////////////////////////////////////////////////////////////////////
void Pipeline::setVertexInputs(VkVertexInputBindingDescription& vertexBinding,
    VkVertexInputAttributeDescription* vertexAttribs,
    uint32_t& vertexAttribsCount, VertexInputsType vertexInputsType)
{
    // Input binding
    vertexBinding.binding = 0;
    vertexBinding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    // Vertex attributes
    switch (vertexInputsType)
    {
        case VERTEX_INPUTS_DEFAULT:
        {
            // Vertex attribs count
            vertexAttribsCount = 2;

            // Vertex binding stride
            vertexBinding.stride = sizeof(float)*5;

            // Position
            vertexAttribs[0] = VkVertexInputAttributeDescription();
            vertexAttribs[0].location = 0;
            vertexAttribs[0].binding = vertexBinding.binding;
            vertexAttribs[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            vertexAttribs[0].offset = 0;

            // Texcoords
            vertexAttribs[1] = VkVertexInputAttributeDescription();
            vertexAttribs[1].location = 1;
            vertexAttribs[1].binding = vertexBinding.binding;
            vertexAttribs[1].format = VK_FORMAT_R32G32_SFLOAT;
            vertexAttribs[1].offset = sizeof(float)*3;
            break;
        }

        case VERTEX_INPUTS_CUBEMAP:
        {
            // Vertex attribs count
            vertexAttribsCount = 1;

            // Vertex binding stride
            vertexBinding.stride = sizeof(float)*3;

            // Position
            vertexAttribs[0] = VkVertexInputAttributeDescription();
            vertexAttribs[0].location = 0;
            vertexAttribs[0].binding = vertexBinding.binding;
            vertexAttribs[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            vertexAttribs[0].offset = 0;
            break;
        }

        case VERTEX_INPUTS_STATICMESH:
        {
            // Vertex attribs count
            vertexAttribsCount = 3;

            // Vertex binding stride
            vertexBinding.stride = sizeof(float)*8;

            // Position
            vertexAttribs[0] = VkVertexInputAttributeDescription();
            vertexAttribs[0].location = 0;
            vertexAttribs[0].binding = vertexBinding.binding;
            vertexAttribs[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            vertexAttribs[0].offset = 0;

            // Texcoords
            vertexAttribs[1] = VkVertexInputAttributeDescription();
            vertexAttribs[1].location = 1;
            vertexAttribs[1].binding = vertexBinding.binding;
            vertexAttribs[1].format = VK_FORMAT_R32G32_SFLOAT;
            vertexAttribs[1].offset = sizeof(float)*3;

            // Normals
            vertexAttribs[2] = VkVertexInputAttributeDescription();
            vertexAttribs[2].location = 2;
            vertexAttribs[2].binding = vertexBinding.binding;
            vertexAttribs[2].format = VK_FORMAT_R32G32B32_SFLOAT;
            vertexAttribs[2].offset = sizeof(float)*5;
            break;
        }

        default:
        {
            // Vertex attribs count
            vertexAttribsCount = 2;

            // Vertex binding stride
            vertexBinding.stride = sizeof(float)*5;

            // Position
            vertexAttribs[0] = VkVertexInputAttributeDescription();
            vertexAttribs[0].location = 0;
            vertexAttribs[0].binding = vertexBinding.binding;
            vertexAttribs[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            vertexAttribs[0].offset = 0;

            // Texcoords
            vertexAttribs[1] = VkVertexInputAttributeDescription();
            vertexAttribs[1].location = 1;
            vertexAttribs[1].binding = vertexBinding.binding;
            vertexAttribs[1].format = VK_FORMAT_R32G32_SFLOAT;
            vertexAttribs[1].offset = sizeof(float)*3;
            break;
        }
    }
}
