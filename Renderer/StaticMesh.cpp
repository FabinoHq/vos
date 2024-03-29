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
//     Renderer/StaticMesh.cpp : Static mesh management                       //
////////////////////////////////////////////////////////////////////////////////
#include "StaticMesh.h"


////////////////////////////////////////////////////////////////////////////////
//  StaticMesh default constructor                                            //
////////////////////////////////////////////////////////////////////////////////
StaticMesh::StaticMesh() :
Transform3(),
m_vertexBuffer(0),
m_texture(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  StaticMesh virtual destructor                                             //
////////////////////////////////////////////////////////////////////////////////
StaticMesh::~StaticMesh()
{
    m_texture = 0;
    m_vertexBuffer = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Init static mesh                                                          //
//  return : True if the static mesh is successfully created                  //
////////////////////////////////////////////////////////////////////////////////
bool StaticMesh::init(VertexBuffer& vertexBuffer, Texture& texture)
{
    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Set static mesh vertex buffer pointer
    m_vertexBuffer = &vertexBuffer;

    // Set static mesh texture pointer
    m_texture = &texture;

    // Reset static mesh transformations
    resetTransforms();

    // Static mesh successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set static mesh texture                                                   //
//  return : True if static mesh texture is successfully set                  //
////////////////////////////////////////////////////////////////////////////////
bool StaticMesh::setTexture(Texture& texture)
{
    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Set static mesh texture pointer
    m_texture = &texture;
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Bind static mesh vertex buffer                                            //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::bindVertexBuffer()
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
//  Render static mesh                                                        //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::render()
{
    // Compute static mesh transformations
    computeTransforms();

    // Push model matrix into command buffer
    vkCmdPushConstants(
        GSwapchain.commandBuffers[GSwapchain.current],
        GGraphicsLayout.handle, VK_SHADER_STAGE_VERTEX_BIT,
        PushConstantMatrixOffset, PushConstantMatrixSize, m_matrix.mat
    );

    // Draw static mesh triangles
    vkCmdDrawIndexed(
        GSwapchain.commandBuffers[GSwapchain.current],
        (m_vertexBuffer->indexCount), 1, 0, 0, 0
    );
}
