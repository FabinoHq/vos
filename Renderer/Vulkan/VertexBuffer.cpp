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
//     Renderer/Vulkan/VertexBuffer.cpp : Vertex buffer management            //
////////////////////////////////////////////////////////////////////////////////
#include "VertexBuffer.h"
#include "../../Resources/Resources.h"


////////////////////////////////////////////////////////////////////////////////
//  VertexBuffer default constructor                                          //
////////////////////////////////////////////////////////////////////////////////
VertexBuffer::VertexBuffer() :
indexCount(0),
vertexBuffer(),
indexBuffer()
{

}

////////////////////////////////////////////////////////////////////////////////
//  VertexBuffer destructor                                                   //
////////////////////////////////////////////////////////////////////////////////
VertexBuffer::~VertexBuffer()
{
    indexCount = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Create Mesh Vertex buffer                                                 //
//  return : True if Vertex buffer is successfully created                    //
////////////////////////////////////////////////////////////////////////////////
bool VertexBuffer::createMeshBuffer(VulkanMemoryPool memoryPool,
    const float* vertices, const uint16_t* indices,
    uint32_t verticesCount, uint32_t indicesCount)
{
    // Check current buffers
    if (vertexBuffer.handle || indexBuffer.handle)
    {
        // Destroy current buffers
        destroyBuffer();
    }

    // Check input vertices and indices
    if (!vertices || !indices || (verticesCount <= 0) || (indicesCount <= 0))
    {
        return false;
    }

    // Compute vertices and indices sizes
    indexCount = indicesCount;
    verticesCount *= sizeof(float);
    indicesCount *= sizeof(uint16_t);

    // Create vertex buffer
    if (!vertexBuffer.createBuffer(
        (VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT),
        memoryPool, verticesCount))
    {
        // Could not create vertex buffer
        return false;
    }

    // Create index buffer
    if (!indexBuffer.createBuffer(
        (VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT),
        memoryPool, indicesCount))
    {
        // Could not create index buffer
        return false;
    }

    // Upload vertex buffer to graphics memory
    if (!GResources.meshes.uploadVertexBuffer(*this,
        vertices, indices, verticesCount, indicesCount))
    {
        // Could not upload vertex buffer to graphics memory
        return false;
    }

    // Vertex buffer successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create HeightMap Vertex buffer                                            //
//  return : True if Vertex buffer is successfully created                    //
////////////////////////////////////////////////////////////////////////////////
bool VertexBuffer::createHeightMapBuffer(VulkanMemoryPool memoryPool,
    const float* vertices, const uint16_t* indices,
    uint32_t verticesCount, uint32_t indicesCount)
{
    // Check current buffers
    if (vertexBuffer.handle || indexBuffer.handle)
    {
        // Destroy current buffers
        destroyBuffer();
    }

    // Check input vertices and indices
    if (!vertices || !indices || (verticesCount <= 0) || (indicesCount <= 0))
    {
        return false;
    }

    // Compute vertices and indices sizes
    indexCount = indicesCount;
    verticesCount *= sizeof(float);
    indicesCount *= sizeof(uint16_t);

    // Create vertex buffer
    if (!vertexBuffer.createBuffer(
        (VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT),
        memoryPool, verticesCount))
    {
        // Could not create vertex buffer
        return false;
    }

    // Create index buffer
    if (!indexBuffer.createBuffer(
        (VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT),
        memoryPool, indicesCount))
    {
        // Could not create index buffer
        return false;
    }

    // Upload vertex buffer to graphics memory
    if (!GResources.heightmaps.uploadVertexBuffer(*this,
        vertices, indices, verticesCount, indicesCount))
    {
        // Could not upload vertex buffer to graphics memory
        return false;
    }

    // Vertex buffer successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create HeightFar Vertex buffer                                            //
//  return : True if Vertex buffer is successfully created                    //
////////////////////////////////////////////////////////////////////////////////
bool VertexBuffer::createHeightFarBuffer(VulkanMemoryPool memoryPool,
    const float* vertices, const uint16_t* indices,
    uint32_t verticesCount, uint32_t indicesCount)
{
    // Check current buffers
    if (vertexBuffer.handle || indexBuffer.handle)
    {
        // Destroy current buffers
        destroyBuffer();
    }

    // Check input vertices and indices
    if (!vertices || !indices || (verticesCount <= 0) || (indicesCount <= 0))
    {
        return false;
    }

    // Compute vertices and indices sizes
    indexCount = indicesCount;
    verticesCount *= sizeof(float);
    indicesCount *= sizeof(uint16_t);

    // Create vertex buffer
    if (!vertexBuffer.createBuffer(
        (VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT),
        memoryPool, verticesCount))
    {
        // Could not create vertex buffer
        return false;
    }

    // Create index buffer
    if (!indexBuffer.createBuffer(
        (VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT),
        memoryPool, indicesCount))
    {
        // Could not create index buffer
        return false;
    }

    // Upload vertex buffer to graphics memory
    if (!GResources.heightfars.uploadVertexBuffer(*this,
        vertices, indices, verticesCount, indicesCount))
    {
        // Could not upload vertex buffer to graphics memory
        return false;
    }

    // Vertex buffer successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Update Mesh Vertex buffer                                                 //
//  return : True if Mesh Vertex buffer is successfully updated               //
////////////////////////////////////////////////////////////////////////////////
bool VertexBuffer::updateMeshBuffer(
    const float* vertices, const uint16_t* indices,
    uint32_t verticesCount, uint32_t indicesCount)
{
    // Check current buffers
    if (!vertexBuffer.handle || !indexBuffer.handle)
    {
        // Invalid current buffers
        return false;
    }

    // Check input vertices and indices
    if (!vertices || !indices || (verticesCount <= 0) || (indicesCount <= 0))
    {
        return false;
    }

    // Compute vertices and indices sizes
    indexCount = indicesCount;
    verticesCount *= sizeof(float);
    indicesCount *= sizeof(uint16_t);

    // Upload vertex buffer to graphics memory
    if (!GResources.meshes.uploadVertexBuffer(*this,
        vertices, indices, verticesCount, indicesCount))
    {
        // Could not upload vertex buffer to graphics memory
        return false;
    }

    // Vertex buffer successfully updated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Update HeightMap Vertex buffer                                            //
//  return : True if Vertex buffer is successfully updated                    //
////////////////////////////////////////////////////////////////////////////////
bool VertexBuffer::updateHeightMapBuffer(
    const float* vertices, const uint16_t* indices,
    uint32_t verticesCount, uint32_t indicesCount)
{
    // Check current buffers
    if (!vertexBuffer.handle || !indexBuffer.handle)
    {
        // Invalid current buffers
        return false;
    }

    // Check input vertices and indices
    if (!vertices || !indices || (verticesCount <= 0) || (indicesCount <= 0))
    {
        return false;
    }

    // Compute vertices and indices sizes
    indexCount = indicesCount;
    verticesCount *= sizeof(float);
    indicesCount *= sizeof(uint16_t);

    // Upload vertex buffer to graphics memory
    if (!GResources.heightmaps.uploadVertexBuffer(*this,
        vertices, indices, verticesCount, indicesCount))
    {
        // Could not upload vertex buffer to graphics memory
        return false;
    }

    // Vertex buffer successfully updated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Update HeightFar Vertex buffer                                            //
//  return : True if Vertex buffer is successfully updated                    //
////////////////////////////////////////////////////////////////////////////////
bool VertexBuffer::updateHeightFarBuffer(
    const float* vertices, const uint16_t* indices,
    uint32_t verticesCount, uint32_t indicesCount)
{
    // Check current buffers
    if (!vertexBuffer.handle || !indexBuffer.handle)
    {
        // Invalid current buffers
        return false;
    }

    // Check input vertices and indices
    if (!vertices || !indices || (verticesCount <= 0) || (indicesCount <= 0))
    {
        return false;
    }

    // Compute vertices and indices sizes
    indexCount = indicesCount;
    verticesCount *= sizeof(float);
    indicesCount *= sizeof(uint16_t);

    // Upload vertex buffer to graphics memory
    if (!GResources.heightfars.uploadVertexBuffer(*this,
        vertices, indices, verticesCount, indicesCount))
    {
        // Could not upload vertex buffer to graphics memory
        return false;
    }

    // Vertex buffer successfully updated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy Vertex buffer                                                     //
////////////////////////////////////////////////////////////////////////////////
void VertexBuffer::destroyBuffer()
{
    indexBuffer.destroyBuffer();
    vertexBuffer.destroyBuffer();
    indexCount = 0;
}
