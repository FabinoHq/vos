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
m_vertexBuffer(),
m_indicesCount(0),
m_texture(0),
m_modelMatrix(),
m_position(0.0f, 0.0f, 0.0f),
m_angles(0.0f, 0.0f, 0.0f)
{
    m_modelMatrix.reset();
}

////////////////////////////////////////////////////////////////////////////////
//  StaticMesh destructor                                                     //
////////////////////////////////////////////////////////////////////////////////
StaticMesh::~StaticMesh()
{
    m_angles.reset();
    m_position.reset();
    m_modelMatrix.reset();
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

    // Set static mesh texture pointer
    m_texture = &texture;

    // Reset static mesh model matrix
    m_modelMatrix.setIdentity();

    // Reset static mesh position
    m_position.reset();

    // Reset static mesh angles
    m_angles.reset();

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
        try
        {
            vertices = new float[verticesCount];
            indices = new uint16_t[indicesCount];
        }
        catch (const std::bad_alloc&)
        {
            vertices = 0;
            indices = 0;
        }
        catch (...)
        {
            vertices = 0;
            indices = 0;
        }
        if (!vertices || !indices)
        {
            // Invalid vertices or indices pointer
            return false;
        }

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

    // Set static mesh texture pointer
    m_texture = &texture;

    // Reset static mesh model matrix
    m_modelMatrix.setIdentity();

    // Reset static mesh position
    m_position.reset();

    // Reset static mesh angles
    m_angles.reset();

    // Static mesh successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy static mesh                                                       //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::destroyStaticMesh(Renderer& renderer)
{
    m_angles.reset();
    m_position.reset();
    m_modelMatrix.reset();
    m_texture = 0;
    m_indicesCount = 0;
    renderer.destroyVertexBuffer(m_vertexBuffer);
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
//  Set static mesh position                                                  //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::setPosition(float x, float y, float z)
{
    m_position.vec[0] = x;
    m_position.vec[1] = y;
    m_position.vec[2] = z;
}

////////////////////////////////////////////////////////////////////////////////
//  Set static mesh position                                                  //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::setPosition(Vector3& position)
{
    m_position.vec[0] = position.vec[0];
    m_position.vec[1] = position.vec[1];
    m_position.vec[2] = position.vec[2];
}

////////////////////////////////////////////////////////////////////////////////
//  Set static mesh X position                                                //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::setX(float x)
{
    m_position.vec[0] = x;
}

////////////////////////////////////////////////////////////////////////////////
//  Set static mesh Y position                                                //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::setY(float y)
{
    m_position.vec[1] = y;
}

////////////////////////////////////////////////////////////////////////////////
//  Set static mesh Z position                                                //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::setZ(float z)
{
    m_position.vec[2] = z;
}

////////////////////////////////////////////////////////////////////////////////
//  Translate static mesh                                                     //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::move(float x, float y, float z)
{
    m_position.vec[0] += x;
    m_position.vec[1] += y;
    m_position.vec[2] += z;
}

////////////////////////////////////////////////////////////////////////////////
//  Translate static mesh                                                     //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::move(Vector3& vector)
{
    m_position.vec[0] += vector.vec[0];
    m_position.vec[1] += vector.vec[1];
    m_position.vec[2] += vector.vec[2];
}

////////////////////////////////////////////////////////////////////////////////
//  Translate static mesh on X axis                                           //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::moveX(float x)
{
    m_position.vec[0] += x;
}

////////////////////////////////////////////////////////////////////////////////
//  Translate static mesh on Y axis                                           //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::moveY(float y)
{
    m_position.vec[1] += y;
}

////////////////////////////////////////////////////////////////////////////////
//  Translate static mesh on Z axis                                           //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::moveZ(float z)
{
    m_position.vec[2] += z;
}

////////////////////////////////////////////////////////////////////////////////
//  Set static mesh rotation angles                                           //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::setAngles(float angleX, float angleY, float angleZ)
{
    m_angles.vec[0] = angleX;
    m_angles.vec[1] = angleY;
    m_angles.vec[2] = angleZ;
}

////////////////////////////////////////////////////////////////////////////////
//  Set static mesh rotation angles                                           //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::setAngles(Vector3& angles)
{
    m_angles.vec[0] = angles.vec[0];
    m_angles.vec[1] = angles.vec[1];
    m_angles.vec[2] = angles.vec[2];
}

////////////////////////////////////////////////////////////////////////////////
//  Set static mesh X rotation angle                                          //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::setAngleX(float angleX)
{
    m_angles.vec[0] = angleX;
}

////////////////////////////////////////////////////////////////////////////////
//  Set static mesh Y rotation angle                                          //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::setAngleY(float angleY)
{
    m_angles.vec[1] = angleY;
}

////////////////////////////////////////////////////////////////////////////////
//  Set static mesh Z rotation angle                                          //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::setAngleZ(float angleZ)
{
    m_angles.vec[2] = angleZ;
}

////////////////////////////////////////////////////////////////////////////////
//  Rotate static mesh                                                        //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::rotate(float angleX, float angleY, float angleZ)
{
    m_angles.vec[0] += angleX;
    m_angles.vec[1] += angleY;
    m_angles.vec[2] += angleZ;
}

////////////////////////////////////////////////////////////////////////////////
//  Rotate static mesh                                                        //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::rotate(Vector3& angles)
{
    m_angles.vec[0] += angles.vec[0];
    m_angles.vec[1] += angles.vec[1];
    m_angles.vec[2] += angles.vec[2];
}

////////////////////////////////////////////////////////////////////////////////
//  Rotate static mesh around the X axis                                      //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::rotateX(float angleX)
{
    m_angles.vec[0] += angleX;
}

////////////////////////////////////////////////////////////////////////////////
//  Rotate static mesh around the Y axis                                      //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::rotateY(float angleY)
{
    m_angles.vec[1] += angleY;
}

////////////////////////////////////////////////////////////////////////////////
//  Rotate static mesh around the Z axis                                      //
////////////////////////////////////////////////////////////////////////////////
void StaticMesh::rotateZ(float angleZ)
{
    m_angles.vec[2] += angleZ;
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
    // Bind static mesh texture
    m_texture->bind(renderer);

    // Set static mesh model matrix
    m_modelMatrix.setIdentity();
    m_modelMatrix.translate(m_position);
    m_modelMatrix.rotate(m_angles);

    // Push model matrix into command buffer
    vkCmdPushConstants(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        renderer.m_layout.handle, VK_SHADER_STAGE_VERTEX_BIT,
        PushConstantMatrixOffset, PushConstantMatrixSize, m_modelMatrix.mat
    );

    // Draw static mesh triangles
    vkCmdDrawIndexed(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        m_indicesCount, 1, 0, 0, 0
    );
}
