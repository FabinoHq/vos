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
//     Renderer/StaticMesh.cpp : Static mesh management                       //
////////////////////////////////////////////////////////////////////////////////
#include "StaticMesh.h"
#include "Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  StaticMesh default constructor                                            //
////////////////////////////////////////////////////////////////////////////////
StaticMesh::StaticMesh() :
Transform3(),
m_vertexBuffer(),
m_indicesCount(0),
m_texture(0),
m_color(1.0f, 1.0f, 1.0f, 1.0f)
{

}

////////////////////////////////////////////////////////////////////////////////
//  StaticMesh virtual destructor                                             //
////////////////////////////////////////////////////////////////////////////////
StaticMesh::~StaticMesh()
{
    m_color.reset();
    m_texture = 0;
    m_indicesCount = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Init static mesh                                                          //
//  return : True if the static mesh is successfully created                  //
////////////////////////////////////////////////////////////////////////////////
bool StaticMesh::init(Renderer& renderer, Texture& texture,
    const float* vertices, const uint16_t* indices,
    uint32_t verticesCount, uint32_t indicesCount)
{
    // Create vertex buffer
    if (!renderer.createVertexBuffer(
        m_vertexBuffer, vertices, indices, verticesCount, indicesCount))
    {
        // Could not create vertex buffer
        return false;
    }
    m_indicesCount = indicesCount;

    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Reset static mesh transformations
    resetTransforms();

    // Set static mesh texture pointer
    m_texture = &texture;

    // Reset static mesh color
    m_color.set(1.0f, 1.0f, 1.0f, 1.0f);

    // Static mesh successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Load static mesh from VMSH file                                           //
//  return : True if the static mesh is successfully loaded                   //
////////////////////////////////////////////////////////////////////////////////
bool StaticMesh::loadVMSH(Renderer& renderer,
    Texture& texture, const std::string& filepath)
{
    // Init mesh data
    float* vertices = 0;
    uint16_t* indices = 0;
    uint32_t verticesCount = 0;
    uint32_t indicesCount = 0;

    // Load mesh data from file
    std::ifstream file;
    file.open(filepath.c_str(), std::ios::in | std::ios::binary);
    if (file.is_open())
    {
        // Read VMSH header
        char header[4] = {0};
        char majorVersion = 0;
        char minorVersion = 0;
        file.read(header, sizeof(char)*4);
        file.read(&majorVersion, sizeof(char));
        file.read(&minorVersion, sizeof(char));

        // Check VMSH header
        if ((header[0] != 'V') || (header[1] != 'M') ||
            (header[2] != 'S') || (header[3] != 'H'))
        {
            // Invalid VMSH header
            return false;
        }

        // Check VMSH version
        if ((majorVersion != 1) || (minorVersion != 0))
        {
            // Invalid VMSH header
            return false;
        }

        // Read VMSH file type
        char type = 0;
        file.read(&type, sizeof(char));
        if (type != 0)
        {
            // Invalid VMSH type
            return false;
        }

        // Read vertices and indices count
        file.read((char*)&verticesCount, sizeof(uint32_t));
        file.read((char*)&indicesCount, sizeof(uint32_t));
        if ((verticesCount <= 0) || (indicesCount <= 0))
        {
            // Invalid vertices or indices count
            return false;
        }

        // Allocate vertices and indices
        vertices = new (std::nothrow) float[verticesCount];
        indices = new (std::nothrow) uint16_t[indicesCount];
        if (!vertices || !indices) return false;

        // Read vertices
        file.read((char*)vertices, sizeof(float)*verticesCount);

        // Read indices
        file.read((char*)indices, sizeof(uint16_t)*indicesCount);

        // Close file
        file.close();
    }

    // Create vertex buffer
    if (!renderer.createVertexBuffer(
        m_vertexBuffer, vertices, indices, verticesCount, indicesCount))
    {
        // Could not create vertex buffer
        if (vertices) { delete[] vertices; }
        if (indices) { delete[] indices; }
        return false;
    }
    m_indicesCount = indicesCount;

    // Destroy mesh data
    if (vertices) { delete[] vertices; }
    if (indices) { delete[] indices; }

    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Reset static mesh transformations
    resetTransforms();

    // Set static mesh texture pointer
    m_texture = &texture;

    // Reset static mesh color
    m_color.set(1.0f, 1.0f, 1.0f, 1.0f);

    // Static mesh successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy static mesh                                                       //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::destroyStaticMesh(Renderer& renderer)
{
    m_color.reset();
    m_texture = 0;
    m_indicesCount = 0;
    renderer.destroyVertexBuffer(m_vertexBuffer);
    resetTransforms();
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
//  Set static mesh color                                                     //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::setColor(const Vector4& color)
{
    m_color.vec[0] = color.vec[0];
    m_color.vec[1] = color.vec[1];
    m_color.vec[2] = color.vec[2];
    m_color.vec[3] = color.vec[3];
}

////////////////////////////////////////////////////////////////////////////////
//  Set static mesh color                                                     //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::setColor(float red, float green, float blue, float alpha)
{
    m_color.vec[0] = red;
    m_color.vec[1] = green;
    m_color.vec[2] = blue;
    m_color.vec[3] = alpha;
}

////////////////////////////////////////////////////////////////////////////////
//  Set static mesh red channel                                               //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::setRed(float red)
{
    m_color.vec[0] = red;
}

////////////////////////////////////////////////////////////////////////////////
//  Set static mesh green channel                                             //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::setGreen(float green)
{
    m_color.vec[1] = green;
}

////////////////////////////////////////////////////////////////////////////////
//  Set static mesh blue channel                                              //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::setBlue(float blue)
{
    m_color.vec[2] = blue;
}

////////////////////////////////////////////////////////////////////////////////
//  Set static mesh alpha channel                                             //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::setAlpha(float alpha)
{
    m_color.vec[3] = alpha;
}


////////////////////////////////////////////////////////////////////////////////
//  Bind static mesh vertex buffer                                            //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::bindVertexBuffer(Renderer& renderer)
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
//  Render static mesh                                                        //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::render(Renderer& renderer)
{
    // Compute static mesh transformations
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

    // Bind static mesh texture
    m_texture->bind(renderer);

    // Draw static mesh triangles
    vkCmdDrawIndexed(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        m_indicesCount, 1, 0, 0, 0
    );
}
