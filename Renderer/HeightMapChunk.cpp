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
//     Renderer/HeightMapChunk.cpp : HeightMap chunk management               //
////////////////////////////////////////////////////////////////////////////////
#include "HeightMapChunk.h"
#include "Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  HeightMapChunk default constructor                                        //
////////////////////////////////////////////////////////////////////////////////
HeightMapChunk::HeightMapChunk() :
Transform3(),
m_vertexBuffer(),
m_indicesCount(0),
m_texture(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  HeightMapChunk virtual destructor                                         //
////////////////////////////////////////////////////////////////////////////////
HeightMapChunk::~HeightMapChunk()
{
    m_texture = 0;
    m_indicesCount = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Init heightmap chunk                                                      //
//  return : True if the heightmap chunk is successfully created              //
////////////////////////////////////////////////////////////////////////////////
bool HeightMapChunk::init(Renderer& renderer, Texture& texture,
    const float* vertices, const uint16_t* indices,
    uint32_t verticesCount, uint32_t indicesCount)
{
    // Create vertex buffer
    if (!m_vertexBuffer.createBuffer(
        renderer.m_vulkanDevice, renderer.m_vulkanMemory,
        renderer.m_transferCommandPool, renderer.m_transferQueue,
        vertices, indices, verticesCount, indicesCount))
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

    // Reset heightmap chunk transformations
    resetTransforms();

    // Set heightmap chunk texture pointer
    m_texture = &texture;

    // Heightmap chunk successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Generate flat heightmap chunk                                             //
//  return : True if the flat heightmap chunk is generated                    //
////////////////////////////////////////////////////////////////////////////////
bool HeightMapChunk::generateFlat(Renderer& renderer, Texture& texture)
{
    // Init heightmap chunk data
    float* vertices = 0;
    uint16_t* indices = 0;

    uint16_t hmWidthP1 = (HeightMapChunkWidth+1);
    uint16_t hmHeightP1 = (HeightMapChunkHeight+1);
    uint32_t verticesCount = ((HeightMapChunkWidth+1)*hmHeightP1*8);
    uint32_t indicesCount = (6*HeightMapChunkWidth*HeightMapChunkHeight);

    // Allocate vertices and indices
    vertices = new (std::nothrow) float[verticesCount];
    indices = new (std::nothrow) uint16_t[indicesCount];
    if (!vertices || !indices) return false;

    // Generate vertices data
    float texCoordIncX = HeightMapChunkTexcoordsWidth /
        (HeightMapChunkWidth * 1.0f);
    float texCoordIncY = HeightMapChunkTexcoordsHeight /
        (HeightMapChunkHeight * 1.0f);
    float vertX = 0.0f;
    float vertZ = 0.0f;
    float texCoordX = 0.0f;
    float texCoordY = 0.0f;
    uint32_t vIndex = 0;
    uint32_t iIndex = 0;
    uint16_t iOffset = 0;

    for (uint32_t j = 0; j <= HeightMapChunkHeight; ++j)
    {
        vertX = 0.0f;
        texCoordX = 0.0f;

        for (uint32_t i = 0; i <= HeightMapChunkWidth; ++i)
        {
            // Set flat heightmap
            vertices[vIndex+0] = vertX;
            vertices[vIndex+1] = 0.0f;
            vertices[vIndex+2] = vertZ;

            vertices[vIndex+3] = texCoordX;
            vertices[vIndex+4] = texCoordY;

            vertices[vIndex+5] = 0.0f;
            vertices[vIndex+6] = 1.0f;
            vertices[vIndex+7] = 0.0f;

            vIndex += 8;
            vertX += HeightMapChunkPlaneWidth;
            texCoordX += texCoordIncX;
        }

        vertZ += HeightMapChunkPlaneHeight;
        texCoordY += texCoordIncY;
    }

    // Generate indices data
    for (uint32_t j = 0; j < HeightMapChunkHeight; ++j)
    {
        for (uint32_t i = 0; i < HeightMapChunkWidth; ++i)
        {
            indices[iIndex+0] = iOffset+hmWidthP1;
            indices[iIndex+1] = iOffset+hmWidthP1+1;
            indices[iIndex+2] = iOffset+1;
            indices[iIndex+3] = iOffset+1;
            indices[iIndex+4] = iOffset;
            indices[iIndex+5] = iOffset+hmWidthP1;

            iIndex += 6;
            ++iOffset;
        }
        ++iOffset;
    }

    // Create vertex buffer
    if (!m_vertexBuffer.createBuffer(
        renderer.m_vulkanDevice, renderer.m_vulkanMemory,
        renderer.m_transferCommandPool, renderer.m_transferQueue,
        vertices, indices, verticesCount, indicesCount))
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

    // Reset heightmap chunk transformations
    resetTransforms();

    // Set heightmap chunk texture pointer
    m_texture = &texture;

    // Heightmap chunk successfully generated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Generate heightmap chunk                                                  //
//  return : True if the heightmap chunk is generated                         //
////////////////////////////////////////////////////////////////////////////////
bool HeightMapChunk::generate(Renderer& renderer, Texture& texture,
    float* heightmap)
{
    // Init heightmap chunk data
    float* vertices = 0;
    uint16_t* indices = 0;

    uint16_t hmWidthP1 = (HeightMapChunkWidth+1);
    uint16_t hmHeightP1 = (HeightMapChunkHeight+1);
    uint32_t verticesCount = ((HeightMapChunkWidth+1)*hmHeightP1*8);
    uint32_t indicesCount = (6*HeightMapChunkWidth*HeightMapChunkHeight);

    // Check heightmap pointer
    if (!heightmap)
    {
        return false;
    }

    // Allocate vertices and indices
    vertices = new (std::nothrow) float[verticesCount];
    indices = new (std::nothrow) uint16_t[indicesCount];
    if (!vertices || !indices) return false;

    // Generate vertices data
    float texCoordIncX = HeightMapChunkTexcoordsWidth /
        (HeightMapChunkWidth * 1.0f);
    float texCoordIncY = HeightMapChunkTexcoordsHeight /
        (HeightMapChunkHeight * 1.0f);
    float vertX = 0.0f;
    float vertZ = 0.0f;
    float texCoordX = 0.0f;
    float texCoordY = 0.0f;
    uint32_t vIndex = 0;
    uint32_t iIndex = 0;
    uint16_t iOffset = 0;

    float top = 0.0f;
    float bot = 0.0f;
    float left = 0.0f;
    float right = 0.0f;
    Vector3 normal(0.0, 0.0, 0.0);

    size_t heightmapIndex = 0;
    for (uint32_t j = 0; j <= HeightMapChunkHeight; ++j)
    {
        vertX = 0.0f;
        texCoordX = 0.0f;

        for (uint32_t i = 0; i <= HeightMapChunkWidth; ++i)
        {
            heightmapIndex = ((j+1) * (HeightMapChunkWidth+3)) + (i+1);

            // Set heightmap based on height data
            vertices[vIndex+0] = vertX;
            vertices[vIndex+1] = heightmap[heightmapIndex];
            vertices[vIndex+2] = vertZ;

            vertices[vIndex+3] = texCoordX;
            vertices[vIndex+4] = texCoordY;

            // Compute normal vector
            top = heightmap[((j+0) * (HeightMapChunkWidth+3)) + (i+1)];
            bot = heightmap[((j+2) * (HeightMapChunkWidth+3)) + (i+1)];
            left = heightmap[((j+1) * (HeightMapChunkWidth+3)) + (i+0)];
            right = heightmap[((j+1) * (HeightMapChunkWidth+3)) + (i+2)];
            normal.vec[0] = left-right;
            normal.vec[1] = 2.0;
            normal.vec[2] = top-bot;
            normal.normalize();

            // Set normal vector
            vertices[vIndex+5] = normal.vec[0];
            vertices[vIndex+6] = normal.vec[1];
            vertices[vIndex+7] = normal.vec[2];

            vIndex += 8;
            vertX += HeightMapChunkPlaneWidth;
            texCoordX += texCoordIncX;
        }

        vertZ += HeightMapChunkPlaneHeight;
        texCoordY += texCoordIncY;
    }

    // Generate indices data
    for (uint32_t j = 0; j < HeightMapChunkHeight; ++j)
    {
        for (uint32_t i = 0; i < HeightMapChunkWidth; ++i)
        {
            indices[iIndex+0] = iOffset+hmWidthP1;
            indices[iIndex+1] = iOffset+hmWidthP1+1;
            indices[iIndex+2] = iOffset+1;
            indices[iIndex+3] = iOffset+1;
            indices[iIndex+4] = iOffset;
            indices[iIndex+5] = iOffset+hmWidthP1;

            iIndex += 6;
            ++iOffset;
        }
        ++iOffset;
    }

    // Create vertex buffer
    if (!m_vertexBuffer.createBuffer(
        renderer.m_vulkanDevice, renderer.m_vulkanMemory,
        renderer.m_transferCommandPool, renderer.m_transferQueue,
        vertices, indices, verticesCount, indicesCount))
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

    // Set heightmap chunk texture pointer
    m_texture = &texture;

    // Reset heightmap chunk transformations
    resetTransforms();

    // Heightmap chunk successfully generated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Update heightmap chunk                                                    //
//  return : True if the heightmap chunk is updated                           //
////////////////////////////////////////////////////////////////////////////////
bool HeightMapChunk::update(Renderer& renderer, float* heightmap)
{
    // Init heightmap chunk data
    float* vertices = 0;
    uint16_t* indices = 0;

    uint16_t hmWidthP1 = (HeightMapChunkWidth+1);
    uint16_t hmHeightP1 = (HeightMapChunkHeight+1);
    uint32_t verticesCount = ((HeightMapChunkWidth+1)*hmHeightP1*8);
    uint32_t indicesCount = (6*HeightMapChunkWidth*HeightMapChunkHeight);

    // Check heightmap pointer
    if (!heightmap)
    {
        return false;
    }

    // Allocate vertices and indices
    vertices = new (std::nothrow) float[verticesCount];
    indices = new (std::nothrow) uint16_t[indicesCount];
    if (!vertices || !indices) return false;

    // Generate vertices data
    float texCoordIncX = HeightMapChunkTexcoordsWidth /
        (HeightMapChunkWidth * 1.0f);
    float texCoordIncY = HeightMapChunkTexcoordsHeight /
        (HeightMapChunkHeight * 1.0f);
    float vertX = 0.0f;
    float vertZ = 0.0f;
    float texCoordX = 0.0f;
    float texCoordY = 0.0f;
    uint32_t vIndex = 0;
    uint32_t iIndex = 0;
    uint16_t iOffset = 0;

    float top = 0.0f;
    float bot = 0.0f;
    float left = 0.0f;
    float right = 0.0f;
    Vector3 normal(0.0, 0.0, 0.0);

    size_t heightmapIndex = 0;
    for (uint32_t j = 0; j <= HeightMapChunkHeight; ++j)
    {
        vertX = 0.0f;
        texCoordX = 0.0f;

        for (uint32_t i = 0; i <= HeightMapChunkWidth; ++i)
        {
            heightmapIndex = ((j+1) * (HeightMapChunkWidth+3)) + (i+1);

            // Set heightmap based on height data
            vertices[vIndex+0] = vertX;
            vertices[vIndex+1] = heightmap[heightmapIndex];
            vertices[vIndex+2] = vertZ;

            vertices[vIndex+3] = texCoordX;
            vertices[vIndex+4] = texCoordY;

            // Compute normal vector
            top = heightmap[((j+0) * (HeightMapChunkWidth+3)) + (i+1)];
            bot = heightmap[((j+2) * (HeightMapChunkWidth+3)) + (i+1)];
            left = heightmap[((j+1) * (HeightMapChunkWidth+3)) + (i+0)];
            right = heightmap[((j+1) * (HeightMapChunkWidth+3)) + (i+2)];
            normal.vec[0] = left-right;
            normal.vec[1] = 2.0;
            normal.vec[2] = top-bot;
            normal.normalize();

            // Set normal vector
            vertices[vIndex+5] = normal.vec[0];
            vertices[vIndex+6] = normal.vec[1];
            vertices[vIndex+7] = normal.vec[2];

            vIndex += 8;
            vertX += HeightMapChunkPlaneWidth;
            texCoordX += texCoordIncX;
        }

        vertZ += HeightMapChunkPlaneHeight;
        texCoordY += texCoordIncY;
    }

    // Generate indices data
    for (uint32_t j = 0; j < HeightMapChunkHeight; ++j)
    {
        for (uint32_t i = 0; i < HeightMapChunkWidth; ++i)
        {
            indices[iIndex+0] = iOffset+hmWidthP1;
            indices[iIndex+1] = iOffset+hmWidthP1+1;
            indices[iIndex+2] = iOffset+1;
            indices[iIndex+3] = iOffset+1;
            indices[iIndex+4] = iOffset;
            indices[iIndex+5] = iOffset+hmWidthP1;

            iIndex += 6;
            ++iOffset;
        }
        ++iOffset;
    }

    // Update vertex buffer
    if (!m_vertexBuffer.updateBuffer(
        renderer.m_vulkanDevice, renderer.m_vulkanMemory,
        renderer.m_transferCommandPool, renderer.m_transferQueue,
        vertices, indices, verticesCount, indicesCount))
    {
        // Could not update vertex buffer
        if (vertices) { delete[] vertices; }
        if (indices) { delete[] indices; }
        return false;
    }
    m_indicesCount = indicesCount;

    // Destroy mesh data
    if (vertices) { delete[] vertices; }
    if (indices) { delete[] indices; }

    // Heightmap chunk successfully updated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Load heightmap chunk from VMSH file                                       //
//  return : True if the heightmap chunk is successfully loaded               //
////////////////////////////////////////////////////////////////////////////////
bool HeightMapChunk::loadVMSH(Renderer& renderer,
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
    if (!m_vertexBuffer.createBuffer(
        renderer.m_vulkanDevice, renderer.m_vulkanMemory,
        renderer.m_transferCommandPool, renderer.m_transferQueue,
        vertices, indices, verticesCount, indicesCount))
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

    // Reset heightmap chunk transformations
    resetTransforms();

    // Set heightmap chunk texture pointer
    m_texture = &texture;

    // Heightmap chunk successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy heightmap chunk                                                   //
////////////////////////////////////////////////////////////////////////////////
void HeightMapChunk::destroyHeightMapChunk(Renderer& renderer)
{
    m_texture = 0;
    m_indicesCount = 0;
    m_vertexBuffer.destroyBuffer(renderer.m_vulkanDevice);
    resetTransforms();
}


////////////////////////////////////////////////////////////////////////////////
//  Set heightmap chunk texture                                               //
//  return : True if heightmap chunk texture is successfully set              //
////////////////////////////////////////////////////////////////////////////////
bool HeightMapChunk::setTexture(Texture& texture)
{
    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Set heightmap chunk texture pointer
    m_texture = &texture;
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Bind heightmap chunk vertex buffer                                        //
////////////////////////////////////////////////////////////////////////////////
void HeightMapChunk::bindVertexBuffer(Renderer& renderer)
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
//  Render heightmap chunk                                                    //
////////////////////////////////////////////////////////////////////////////////
void HeightMapChunk::render(Renderer& renderer)
{
    // Compute heightmap chunk transformations
    computeTransforms();

    // Push model matrix into command buffer
    vkCmdPushConstants(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        renderer.m_layout.handle, VK_SHADER_STAGE_VERTEX_BIT,
        PushConstantMatrixOffset, PushConstantMatrixSize, m_matrix.mat
    );

    // Bind heightmap chunk texture
    m_texture->bind(renderer);

    // Draw heightmap chunk triangles
    vkCmdDrawIndexed(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        m_indicesCount, 1, 0, 0, 0
    );
}
