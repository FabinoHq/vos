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
//     Renderer/HeightMap/SeaFarChunk.cpp : Sea far chunk                     //
////////////////////////////////////////////////////////////////////////////////
#include "SeaFarChunk.h"


////////////////////////////////////////////////////////////////////////////////
//  SeaFarChunk default constructor                                           //
////////////////////////////////////////////////////////////////////////////////
SeaFarChunk::SeaFarChunk() :
Transform3()
{

}

////////////////////////////////////////////////////////////////////////////////
//  SeaFarChunk virtual destructor                                            //
////////////////////////////////////////////////////////////////////////////////
SeaFarChunk::~SeaFarChunk()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Init sea far chunk                                                        //
//  return : True if the sea far is successfully created                      //
////////////////////////////////////////////////////////////////////////////////
bool SeaFarChunk::init()
{
    // Reset sea far chunk transformations
    resetTransforms();

    // Sea far chunk successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Render sea far chunk                                                      //
////////////////////////////////////////////////////////////////////////////////
void SeaFarChunk::render()
{
    // Compute sea far chunk transformations
    computeTransforms();

    // Push model matrix into command buffer
    vkCmdPushConstants(
        GSwapchain.commandBuffers[GSwapchain.current],
        GGraphicsLayout.handle, VK_SHADER_STAGE_VERTEX_BIT,
        PushConstantMatrixOffset, PushConstantMatrixSize, m_matrix.mat
    );

    // Draw sea far chunk triangles
    vkCmdDrawIndexed(
        GSwapchain.commandBuffers[GSwapchain.current],
        SeaFarChunkIndicesCount, 1, 0, 0, 0
    );
}


////////////////////////////////////////////////////////////////////////////////
//  Generate sea far chunk                                                    //
//  return : True if the sea far chunk is generated                           //
////////////////////////////////////////////////////////////////////////////////
bool SeaFarChunk::generateSeaFarChunk(VertexBuffer& vertexBuffer)
{
    // Allocate sea far vertices
    float* vertices = new(std::nothrow) float[SeaFarChunkVerticesCount];
    if (!vertices)
    {
        // Could not allocate sea far vertices
        return false;
    }

    // Allocate sea far indices
    uint16_t* indices = new(std::nothrow) uint16_t[SeaFarChunkIndicesCount];
    if (!indices)
    {
        // Could not allocate sea far indices
        if (vertices) { delete[] vertices; }
        return false;
    }

    // Generate vertices data
    float texCoordIncX = SeaFarChunkTexcoordsWidth /
        (SeaFarChunkWidth * 1.0f);
    float texCoordIncY = SeaFarChunkTexcoordsHeight /
        (SeaFarChunkHeight * 1.0f);
    float vertX = 0.0f;
    float vertZ = 0.0f;
    float texCoordX = 0.0f;
    float texCoordY = 0.0f;
    uint32_t vIndex = 0;
    uint32_t iIndex = 0;
    uint16_t iOffset = 0;

    // Flat sea far chunk
    for (uint32_t j = 0; j <= SeaFarChunkHeight; ++j)
    {
        vertX = 0.0f;
        texCoordX = 0.0f;

        for (uint32_t i = 0; i <= SeaFarChunkWidth; ++i)
        {
            // Set flat sea chunk
            vertices[vIndex+0] = vertX;
            vertices[vIndex+1] = 0.0f;
            vertices[vIndex+2] = vertZ;

            vertices[vIndex+3] = texCoordX;
            vertices[vIndex+4] = texCoordY;

            vertices[vIndex+5] = 0.0f;
            vertices[vIndex+6] = 1.0f;
            vertices[vIndex+7] = 0.0f;

            vIndex += 8;
            vertX += SeaFarChunkPlaneWidth;
            texCoordX += texCoordIncX;
        }

        vertZ += SeaFarChunkPlaneHeight;
        texCoordY += texCoordIncY;
    }

    // Generate indices data
    for (uint32_t j = 0; j < SeaFarChunkHeight; ++j)
    {
        for (uint32_t i = 0; i < SeaFarChunkWidth; ++i)
        {
            indices[iIndex+0] = iOffset+(SeaFarChunkWidth+1);
            indices[iIndex+1] = iOffset+(SeaFarChunkWidth+2);
            indices[iIndex+2] = iOffset+1;
            indices[iIndex+3] = iOffset+1;
            indices[iIndex+4] = iOffset;
            indices[iIndex+5] = iOffset+(SeaFarChunkWidth+1);

            iIndex += 6;
            ++iOffset;
        }
        ++iOffset;
    }

    // Create vertex buffer
    if (!vertexBuffer.createMeshBuffer(VULKAN_MEMORY_MESHES,
        vertices, indices,
        SeaFarChunkVerticesCount, SeaFarChunkIndicesCount))
    {
        // Could not create vertex buffer
        if (indices) { delete[] indices; }
        if (vertices) { delete[] vertices; }
        return false;
    }

    // Delete indices and vertices data
    if (indices) { delete[] indices; }
    if (vertices) { delete[] vertices; }

    // Sea far chunk successfully generated
    return true;
}
