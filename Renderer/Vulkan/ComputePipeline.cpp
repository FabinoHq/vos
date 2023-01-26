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
//     Renderer/Vulkan/ComputePipeline.cpp : Compute pipeline management      //
////////////////////////////////////////////////////////////////////////////////
#include "ComputePipeline.h"


////////////////////////////////////////////////////////////////////////////////
//  ComputePipeline default constructor                                       //
////////////////////////////////////////////////////////////////////////////////
ComputePipeline::ComputePipeline() :
m_pipeline(0),
m_computeShader()
{

}

////////////////////////////////////////////////////////////////////////////////
//  ComputePipeline destructor                                                //
////////////////////////////////////////////////////////////////////////////////
ComputePipeline::~ComputePipeline()
{
    m_pipeline = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Create compute shader                                                     //
//  return : True if the compute shader is successfully created               //
////////////////////////////////////////////////////////////////////////////////
bool ComputePipeline::createComputeShader(
    const uint32_t* computeSource, const size_t computeSize)
{
    // Destroy previous compute shader
    if (m_computeShader.isValid())
    {
        m_computeShader.destroyShader();
    }

    // Create compute shader
    if (!m_computeShader.createShader(computeSource, computeSize))
    {
        // Invalid compute shader
        return false;
    }

    // Compute shader successfully created
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Create compute pipeline                                                   //
//  return : True if compute pipeline is successfully created                 //
////////////////////////////////////////////////////////////////////////////////
bool ComputePipeline::createComputePipeline()
{
    // Check current compute pipeline
    if (m_pipeline)
    {
        // Destroy current compute pipeline
        destroyComputePipeline();
    }

    // Shader stage
    VkPipelineShaderStageCreateInfo shaderStage;
    shaderStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStage.pNext = 0;
    shaderStage.flags = 0;
    shaderStage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
    shaderStage.module = m_computeShader.handle;
    shaderStage.pName = "main";
    shaderStage.pSpecializationInfo = 0;

    // Create compute pipeline
    VkComputePipelineCreateInfo pipelineInfo;
    pipelineInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
    pipelineInfo.pNext = 0;
    pipelineInfo.flags = 0;
    pipelineInfo.stage = shaderStage;
    pipelineInfo.layout = GComputeLayout.handle;
    pipelineInfo.basePipelineHandle = 0;
    pipelineInfo.basePipelineIndex = 0;

    if (vkCreateComputePipelines(GVulkanDevice,
        0, 1, &pipelineInfo, 0, &m_pipeline) != VK_SUCCESS)
    {
        // Could not create pipeline
        return false;
    }
    if (!m_pipeline)
    {
        // Invalid pipeline handle
        return false;
    }

    // Compute pipeline successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy compute pipeline                                                  //
////////////////////////////////////////////////////////////////////////////////
void ComputePipeline::destroyComputePipeline()
{
    // Check Vulkan device
    if (!GVulkanDevice)
    {
        // Invalid Vulkan device
        return;
    }

    // Destroy compute pipeline
    if (m_pipeline)
    {
        vkDestroyPipeline(GVulkanDevice, m_pipeline, 0);
    }
    m_pipeline = 0;

    // Destroy compute shader
    m_computeShader.destroyShader();
}
