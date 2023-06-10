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
//     Renderer/Plane.cpp : Plane management                                  //
////////////////////////////////////////////////////////////////////////////////
#include "Plane.h"
#include "Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  Plane default constructor                                                 //
////////////////////////////////////////////////////////////////////////////////
Plane::Plane() :
Transform3(),
m_texture(0),
m_color(1.0f, 1.0f, 1.0f, 1.0f),
m_uvOffset(0.0f, 0.0f),
m_uvSize(1.0f, 1.0f),
m_billboard(PLANE_BILLBOARD_NONE)
{

}

////////////////////////////////////////////////////////////////////////////////
//  Plane virtual destructor                                                  //
////////////////////////////////////////////////////////////////////////////////
Plane::~Plane()
{
    m_billboard = PLANE_BILLBOARD_NONE;
    m_uvSize.reset();
    m_uvOffset.reset();
    m_color.reset();
    m_texture = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Init plane                                                                //
//  return : True if the plane is successfully created                        //
////////////////////////////////////////////////////////////////////////////////
bool Plane::init(Texture& texture, float width, float height)
{
    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Reset plane transformations
    resetTransforms();

    // Set plane size
    setSize(width, height, 1.0f);

    // Set plane texture pointer
    m_texture = &texture;

    // Reset plane color
    m_color.set(1.0f, 1.0f, 1.0f, 1.0f);

    // Reset plane UV offset
    m_uvOffset.reset();

    // Reset plane UV size
    m_uvSize.set(1.0f, 1.0f);

    // Reset billboard mode
    m_billboard = PLANE_BILLBOARD_NONE;

    // Plane successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set plane texture                                                         //
//  return : True if plane texture is successfully set                        //
////////////////////////////////////////////////////////////////////////////////
bool Plane::setTexture(Texture& texture)
{
    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Set plane texture pointer
    m_texture = &texture;
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set plane billboard mode                                                  //
////////////////////////////////////////////////////////////////////////////////
void Plane::setBillboard(PlaneBillboardMode billboard)
{
    if (billboard <= PLANE_BILLBOARD_NONE)
    {
        billboard = PLANE_BILLBOARD_NONE;
    }
    if (billboard >= PLANE_BILLBOARD_SPHERICAL)
    {
        billboard = PLANE_BILLBOARD_SPHERICAL;
    }
    m_billboard = billboard;
}

////////////////////////////////////////////////////////////////////////////////
//  Set plane color                                                           //
////////////////////////////////////////////////////////////////////////////////
void Plane::setColor(const Vector4& color)
{
    m_color.vec[0] = color.vec[0];
    m_color.vec[1] = color.vec[1];
    m_color.vec[2] = color.vec[2];
    m_color.vec[3] = color.vec[3];
}

////////////////////////////////////////////////////////////////////////////////
//  Set plane color                                                           //
////////////////////////////////////////////////////////////////////////////////
void Plane::setColor(float red, float green, float blue, float alpha)
{
    m_color.vec[0] = red;
    m_color.vec[1] = green;
    m_color.vec[2] = blue;
    m_color.vec[3] = alpha;
}


////////////////////////////////////////////////////////////////////////////////
//  Set plane subrectangle                                                    //
////////////////////////////////////////////////////////////////////////////////
void Plane::setSubrect(const Vector2& offset, const Vector2& size)
{
    m_uvOffset.vec[0] = offset.vec[0];
    m_uvOffset.vec[1] = offset.vec[1];
    m_uvSize.vec[0] = size.vec[0];
    m_uvSize.vec[1] = size.vec[1];
}

////////////////////////////////////////////////////////////////////////////////
//  Set plane subrectangle                                                    //
////////////////////////////////////////////////////////////////////////////////
void Plane::setSubrect(float uOffset, float vOffset, float uSize, float vSize)
{
    m_uvOffset.vec[0] = uOffset;
    m_uvOffset.vec[1] = vOffset;
    m_uvSize.vec[0] = uSize;
    m_uvSize.vec[1] = vSize;
}


////////////////////////////////////////////////////////////////////////////////
//  Compute plane                                                             //
////////////////////////////////////////////////////////////////////////////////
void Plane::compute(Camera* camera)
{
    PlaneBillboardMode billboard = m_billboard;
    Vector3 lookAt = Vector3(0.0f, 0.0f, 1.0f);
    Vector3 delta = Vector3(0.0f, 0.0f, 0.0f);
    Vector3 delta2 = Vector3(0.0f, 0.0f, 0.0f);
    Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f);
    float dotProduct = 0.0f;
    float angle = 0.0f;

    // Check camera
    if (!camera)
    {
        // Force billboard mode off
        billboard = PLANE_BILLBOARD_NONE;
    }

    // Set plane model matrix
    m_matrix.setIdentity();
    m_matrix.translate(m_position);
    if (billboard == PLANE_BILLBOARD_CYLINDRICAL_Y)
    {
        // Cylindrical billboard (Y)
        delta.set(
            (m_position.vec[0] - camera->getX()),
            0.0f,
            (m_position.vec[2] - camera->getZ())
        );
        delta.normalize();
        rotation.crossProduct(lookAt, delta);
        dotProduct = lookAt.dotProduct(delta);
        if (dotProduct <= -1.0) { dotProduct = -1.0; }
        if (dotProduct >= 1.0) { dotProduct = 1.0; }
        angle = (Math::Pi - std::acos(dotProduct));
        m_matrix.rotate(
            angle, rotation.vec[0], rotation.vec[1], rotation.vec[2]
        );
        m_matrix.rotateZ(m_angles.vec[2]);
    }
    else if (billboard == PLANE_BILLBOARD_CYLINDRICAL_X)
    {
        // Cylindrical billboard (X)
        delta.set(
            0.0f,
            (m_position.vec[1] - camera->getY()),
            (m_position.vec[2] - camera->getZ())
        );
        delta.normalize();
        rotation.crossProduct(lookAt, delta);
        dotProduct = lookAt.dotProduct(delta);
        if (dotProduct <= -1.0) { dotProduct = -1.0; }
        if (dotProduct >= 1.0) { dotProduct = 1.0; }
        angle = (Math::Pi - std::acos(dotProduct));
        m_matrix.rotate(
            angle, rotation.vec[0], rotation.vec[1], rotation.vec[2]
        );
        m_matrix.rotateZ(m_angles.vec[2]);
    }
    else if (billboard == PLANE_BILLBOARD_SPHERICAL)
    {
        // Spherical billboard
        delta.set(
            (m_position.vec[0] - camera->getX()),
            0.0f,
            (m_position.vec[2] - camera->getZ())
        );
        delta.normalize();
        rotation.crossProduct(lookAt, delta);
        dotProduct = lookAt.dotProduct(delta);
        if (dotProduct <= -1.0) { dotProduct = -1.0; }
        if (dotProduct >= 1.0) { dotProduct = 1.0; }
        angle = (Math::Pi - std::acos(dotProduct));
        m_matrix.rotate(
            angle, rotation.vec[0], rotation.vec[1], rotation.vec[2]
        );
        delta2.set(
            (m_position.vec[0] - camera->getX()),
            (m_position.vec[1] - camera->getY()),
            (m_position.vec[2] - camera->getZ())
        );
        delta2.normalize();
        dotProduct = delta.dotProduct(delta2);
        if (dotProduct <= -1.0) { dotProduct = -1.0; }
        if (dotProduct >= 1.0) { dotProduct = 1.0; }
        angle = std::acos(dotProduct)*Math::signZero(delta2.vec[1]);
        m_matrix.rotateX(angle);
        m_matrix.rotateZ(m_angles.vec[2]);
    }
    else
    {
        // No billboard mode
        m_matrix.rotate(m_angles);
    }
    m_matrix.translate(-m_origin);
    m_matrix.scale(m_size);
}

////////////////////////////////////////////////////////////////////////////////
//  Render plane                                                              //
////////////////////////////////////////////////////////////////////////////////
void Plane::render()
{
    // Push model matrix into command buffer
    vkCmdPushConstants(
        GSwapchain.commandBuffers[GSwapchain.current],
        GGraphicsLayout.handle, VK_SHADER_STAGE_VERTEX_BIT,
        PushConstantMatrixOffset, PushConstantMatrixSize, m_matrix.mat
    );

    // Push constants into command buffer
    PushConstantData pushConstants;
    pushConstants.color[0] = m_color.vec[0];
    pushConstants.color[1] = m_color.vec[1];
    pushConstants.color[2] = m_color.vec[2];
    pushConstants.color[3] = m_color.vec[3];
    pushConstants.offset[0] = m_uvOffset.vec[0];
    pushConstants.offset[1] = m_uvOffset.vec[1];
    pushConstants.size[0] = m_uvSize.vec[0];
    pushConstants.size[1] = m_uvSize.vec[1];

    vkCmdPushConstants(
        GSwapchain.commandBuffers[GSwapchain.current],
        GGraphicsLayout.handle, VK_SHADER_STAGE_FRAGMENT_BIT,
        PushConstantDataOffset, PushConstantDataNoTimeSize, &pushConstants
    );

    // Draw plane triangles
    vkCmdDrawIndexed(
        GSwapchain.commandBuffers[GSwapchain.current],
        6, 1, 0, 0, 0
    );
}
