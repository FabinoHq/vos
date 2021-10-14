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
//     Renderer/Pipeline.cpp : Graphics pipeline management                   //
////////////////////////////////////////////////////////////////////////////////
#include "Pipeline.h"
#include "Renderer.h"


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
bool Pipeline::createVertexShader(Renderer& renderer,
    const uint32_t* vertexSource, const size_t vertexSize)
{
    // Destroy previous vertex shader
    if (m_vertexShader.isValid())
    {
        m_vertexShader.destroyShader(renderer);
    }

    // Create vertex shader
    if (!m_vertexShader.createShader(renderer, vertexSource, vertexSize))
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
bool Pipeline::createFragmentShader(Renderer& renderer,
    const uint32_t* fragmentSource, const size_t fragmentSize)
{
    // Destroy previous fragment shader
    if (m_fragmentShader.isValid())
    {
        m_fragmentShader.destroyShader(renderer);
    }

    // Create fragment shader
    if (!m_fragmentShader.createShader(renderer, fragmentSource, fragmentSize))
    {
        // Invalid fragment shader
        return false;
    }

    // Fragment shader successfully created
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Create Pipeline                                                           //
//  return : True if Pipeline is successfully created                         //
////////////////////////////////////////////////////////////////////////////////
bool Pipeline::createPipeline(Renderer& renderer)
{
    // Check Vulkan device
    if (!renderer.m_vulkanDevice)
    {
        // Invalid Vulkan device
        m_pipeline = 0;
        return false;
    }

    // Check render pass
    if (!renderer.m_swapchain.renderPass)
    {
        // Invalid render pass
        m_pipeline = 0;
        return false;
    }

    // Check vertex shader
    if (!m_vertexShader.isValid())
    {
        // Invalid vertex shader
        m_pipeline = 0;
        return false;
    }

    // Check fragment shader
    if (!m_fragmentShader.isValid())
    {
        // Invalid fragment shader
        m_pipeline = 0;
        return false;
    }

    // Shader stages
    VkPipelineShaderStageCreateInfo shaderStages[2];
    shaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[0].pNext = 0;
    shaderStages[0].flags = 0;
    shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
    shaderStages[0].module = m_vertexShader.m_shader;
    shaderStages[0].pName = "main";
    shaderStages[0].pSpecializationInfo = 0;

    shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[1].pNext = 0;
    shaderStages[1].flags = 0;
    shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    shaderStages[1].module = m_fragmentShader.m_shader;
    shaderStages[1].pName = "main";
    shaderStages[1].pSpecializationInfo = 0;

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
    pipelineInfo.layout = renderer.m_layout.handle;
    pipelineInfo.renderPass = renderer.m_swapchain.renderPass;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = 0;
    pipelineInfo.basePipelineIndex = -1;

    if (vkCreateGraphicsPipelines(renderer.m_vulkanDevice,
        0, 1, &pipelineInfo, 0, &m_pipeline) != VK_SUCCESS)
    {
        // Could not create pipeline
        m_pipeline = 0;
        return false;
    }
    if (!m_pipeline)
    {
        // Invalid pipeline handle
        m_pipeline = 0;
        return false;
    }

    // Pipeline successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Bind Pipeline                                                             //
////////////////////////////////////////////////////////////////////////////////
void Pipeline::bind(Renderer& renderer)
{
    if (m_pipeline)
    {
        vkCmdBindPipeline(
            renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
            VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline
        );
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy Pipeline                                                          //
////////////////////////////////////////////////////////////////////////////////
void Pipeline::destroyPipeline(Renderer& renderer)
{
    // Destroy pipeline
    if (renderer.m_vulkanDevice && m_pipeline && vkDestroyPipeline)
    {
        // Destroy pipeline
        vkDestroyPipeline(renderer.m_vulkanDevice, m_pipeline, 0);
    }
    m_pipeline = 0;

    // Destroy fragment shader
    m_fragmentShader.destroyShader(renderer);

    // Destroy vertex shader
    m_vertexShader.destroyShader(renderer);
}


////////////////////////////////////////////////////////////////////////////////
//  Check if the pipeline is valid                                            //
//  return : True if the pipeline is valid                                    //
////////////////////////////////////////////////////////////////////////////////
bool Pipeline::isValid()
{
    return m_pipeline;
}
