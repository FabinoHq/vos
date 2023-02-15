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
//     Renderer/SkyProc.cpp : Procedural skybox management                    //
////////////////////////////////////////////////////////////////////////////////
#include "SkyProc.h"


////////////////////////////////////////////////////////////////////////////////
//  SkyProc default constructor                                               //
////////////////////////////////////////////////////////////////////////////////
SkyProc::SkyProc() :
Transform3(),
m_pipeline(),
m_vertexBuffer(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  SkyProc virtual destructor                                                //
////////////////////////////////////////////////////////////////////////////////
SkyProc::~SkyProc()
{
    m_vertexBuffer = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Init procedural skybox                                                    //
//  return : True if the procedural skybox is successfully created            //
////////////////////////////////////////////////////////////////////////////////
bool SkyProc::init(VertexBuffer& vertexBuffer,
    const uint32_t* fragmentSource, const size_t fragmentSize)
{
    bool shaderCreated = false;
    if (fragmentSource && (fragmentSize > 0))
    {
        // Create procedural sprite pipeline
        m_pipeline.createVertexShader(
            SkyBoxVertexShader, SkyBoxVertexShaderSize
        );
        m_pipeline.createFragmentShader(
            fragmentSource, fragmentSize
        );
        if (m_pipeline.createPipeline(VERTEX_INPUTS_CUBEMAP))
        {
            shaderCreated = true;
        }
    }

    if (!shaderCreated)
    {
        // Create default procedural skybox pipeline
        m_pipeline.createVertexShader(
            SkyBoxVertexShader, SkyBoxVertexShaderSize
        );
        m_pipeline.createFragmentShader(
            SkyProcFragmentShader, SkyProcFragmentShaderSize
        );
        if (!m_pipeline.createPipeline(VERTEX_INPUTS_CUBEMAP))
        {
            // Could not create default procedural skybox pipeline
            return false;
        }
    }

    // Set cuboid vertex buffer
    m_vertexBuffer = &vertexBuffer;

    // Reset procedural skybox transformations
    resetTransforms();

    // Procedural skybox successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy procedural skybox                                                 //
////////////////////////////////////////////////////////////////////////////////
void SkyProc::destroySkyProc()
{
    m_vertexBuffer = 0;
    m_pipeline.destroyPipeline();
    resetTransforms();
}


////////////////////////////////////////////////////////////////////////////////
//  Bind procedural skybox vertex buffer                                      //
////////////////////////////////////////////////////////////////////////////////
void SkyProc::bindVertexBuffer()
{
    // Bind vertex buffer
    VkDeviceSize offset = 0;
    vkCmdBindVertexBuffers(
        GSwapchain.commandBuffers[GSwapchain.current],
        0, 1, &m_vertexBuffer->vertexBuffer.handle, &offset
    );

    vkCmdBindIndexBuffer(
        GSwapchain.commandBuffers[GSwapchain.current],
        m_vertexBuffer->indexBuffer.handle, 0, VK_INDEX_TYPE_UINT16
    );
}

////////////////////////////////////////////////////////////////////////////////
//  Render procedural skybox                                                  //
////////////////////////////////////////////////////////////////////////////////
void SkyProc::render()
{
    // Compute procedural skybox transformations
    computeTransforms();

    // Push model matrix into command buffer
    vkCmdPushConstants(
        GSwapchain.commandBuffers[GSwapchain.current],
        GGraphicsLayout.handle, VK_SHADER_STAGE_VERTEX_BIT,
        PushConstantMatrixOffset, PushConstantMatrixSize, m_matrix.mat
    );

    // Draw procedural skybox triangles
    vkCmdDrawIndexed(
        GSwapchain.commandBuffers[GSwapchain.current],
        SkyBoxIndicesCount, 1, 0, 0, 0
    );
}
