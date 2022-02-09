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
//     Renderer/SkyBox.cpp : SkyBox management                                //
////////////////////////////////////////////////////////////////////////////////
#include "SkyBox.h"
#include "Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  SkyBox default constructor                                                //
////////////////////////////////////////////////////////////////////////////////
SkyBox::SkyBox() :
Transform3(),
m_cubemap(0),
m_color(1.0f, 1.0f, 1.0f, 1.0f)
{

}

////////////////////////////////////////////////////////////////////////////////
//  SkyBox virtual destructor                                                 //
////////////////////////////////////////////////////////////////////////////////
SkyBox::~SkyBox()
{
    m_color.reset();
    m_cubemap = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Init skybox                                                               //
//  return : True if the skybox is successfully created                       //
////////////////////////////////////////////////////////////////////////////////
bool SkyBox::init(Renderer& renderer, CubeMap& cubemap)
{
    // Create skybox vertex buffer
    if (!renderer.createVertexBuffer(m_vertexBuffer,
        SkyBoxVertices, SkyBoxIndices,
        SkyBoxVerticesCount, SkyBoxIndicesCount))
    {
        // Could not create skybox vertex buffer
        return false;
    }

    // Check cubemap handle
    if (!cubemap.isValid())
    {
        // Invalid cubemap handle
        return false;
    }

    // Reset skybox transformations
    resetTransforms();

    // Set skybox cubemap pointer
    m_cubemap = &cubemap;

    // Reset skybox color
    m_color.set(1.0f, 1.0f, 1.0f, 1.0f);

    // SkyBox successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy skybox                                                            //
////////////////////////////////////////////////////////////////////////////////
void SkyBox::destroySkyBox(Renderer& renderer)
{
    renderer.destroyVertexBuffer(m_vertexBuffer);
    m_color.reset();
    resetTransforms();
}


////////////////////////////////////////////////////////////////////////////////
//  Set skybox color                                                          //
////////////////////////////////////////////////////////////////////////////////
void SkyBox::setColor(const Vector4& color)
{
    m_color.vec[0] = color.vec[0];
    m_color.vec[1] = color.vec[1];
    m_color.vec[2] = color.vec[2];
    m_color.vec[3] = color.vec[3];
}

////////////////////////////////////////////////////////////////////////////////
//  Set skybox color                                                          //
////////////////////////////////////////////////////////////////////////////////
void SkyBox::setColor(float red, float green, float blue, float alpha)
{
    m_color.vec[0] = red;
    m_color.vec[1] = green;
    m_color.vec[2] = blue;
    m_color.vec[3] = alpha;
}

////////////////////////////////////////////////////////////////////////////////
//  Set skybox red channel                                                    //
////////////////////////////////////////////////////////////////////////////////
void SkyBox::setRed(float red)
{
    m_color.vec[0] = red;
}

////////////////////////////////////////////////////////////////////////////////
//  Set skybox green channel                                                  //
////////////////////////////////////////////////////////////////////////////////
void SkyBox::setGreen(float green)
{
    m_color.vec[1] = green;
}

////////////////////////////////////////////////////////////////////////////////
//  Set skybox blue channel                                                   //
////////////////////////////////////////////////////////////////////////////////
void SkyBox::setBlue(float blue)
{
    m_color.vec[2] = blue;
}

////////////////////////////////////////////////////////////////////////////////
//  Set skybox alpha channel                                                  //
////////////////////////////////////////////////////////////////////////////////
void SkyBox::setAlpha(float alpha)
{
    m_color.vec[3] = alpha;
}


////////////////////////////////////////////////////////////////////////////////
//  Bind skybox vertex buffer                                                 //
////////////////////////////////////////////////////////////////////////////////
void SkyBox::bindVertexBuffer(Renderer& renderer)
{
    // Bind vertex buffer
    VkDeviceSize offset = 0;
    vkCmdBindVertexBuffers(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        0, 1, &m_vertexBuffer.vertexBuffer.handle, &offset
    );

    vkCmdBindIndexBuffer(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        m_vertexBuffer.indexBuffer.handle, 0, VK_INDEX_TYPE_UINT16
    );
}

////////////////////////////////////////////////////////////////////////////////
//  Render skybox                                                             //
////////////////////////////////////////////////////////////////////////////////
void SkyBox::render(Renderer& renderer)
{
    // Compute skybox transformations
    computeTransforms();

    // Push model matrix into command buffer
    vkCmdPushConstants(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        renderer.m_layout.handle, VK_SHADER_STAGE_VERTEX_BIT,
        PushConstantMatrixOffset, PushConstantMatrixSize, m_matrix.mat
    );

    // Push constants into command buffer
    PushConstantData pushConstants;
    pushConstants.color[0] = m_color.vec[0];
    pushConstants.color[1] = m_color.vec[1];
    pushConstants.color[2] = m_color.vec[2];
    pushConstants.color[3] = m_color.vec[3];

    vkCmdPushConstants(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        renderer.m_layout.handle, VK_SHADER_STAGE_FRAGMENT_BIT,
        PushConstantColorOffset, PushConstantColorSize, &pushConstants.color
    );

    // Bind skybox cubemap
    m_cubemap->bind(renderer);

    // Draw skybox triangles
    vkCmdDrawIndexed(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        SkyBoxIndicesCount, 1, 0, 0, 0
    );
}
