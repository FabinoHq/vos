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
//     Renderer/Sprite.cpp : Sprite management                                //
////////////////////////////////////////////////////////////////////////////////
#include "Sprite.h"
#include "Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  Sprite default constructor                                                //
////////////////////////////////////////////////////////////////////////////////
Sprite::Sprite() :
Transform2(),
m_texture(0),
m_color(1.0f, 1.0f, 1.0f, 1.0f)
{

}

////////////////////////////////////////////////////////////////////////////////
//  Sprite virtual destructor                                                 //
////////////////////////////////////////////////////////////////////////////////
Sprite::~Sprite()
{
    m_color.reset();
}


////////////////////////////////////////////////////////////////////////////////
//  Init sprite                                                               //
//  return : True if the sprite is successfully created                       //
////////////////////////////////////////////////////////////////////////////////
bool Sprite::init(Texture& texture, float width, float height)
{
    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Reset sprite transformations
    resetTransforms();

    // Set sprite size
    setSize(width, height);

    // Set sprite origin (anchor)
    setOrigin(width*0.5f, height*0.5f);

    // Set sprite texture pointer
    m_texture = &texture;

    // Reset sprite color
    m_color.set(1.0f, 1.0f, 1.0f, 1.0f);

    // Sprite successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set sprite texture                                                        //
//  return : True if sprite texture is successfully set                       //
////////////////////////////////////////////////////////////////////////////////
bool Sprite::setTexture(Texture& texture)
{
    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Set sprite texture pointer
    m_texture = &texture;
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set sprite color                                                          //
////////////////////////////////////////////////////////////////////////////////
void Sprite::setColor(const Vector4& color)
{
    m_color.vec[0] = color.vec[0];
    m_color.vec[1] = color.vec[1];
    m_color.vec[2] = color.vec[2];
    m_color.vec[3] = color.vec[3];
}

////////////////////////////////////////////////////////////////////////////////
//  Set sprite color                                                          //
////////////////////////////////////////////////////////////////////////////////
void Sprite::setColor(float red, float green, float blue, float alpha)
{
    m_color.vec[0] = red;
    m_color.vec[1] = green;
    m_color.vec[2] = blue;
    m_color.vec[3] = alpha;
}

////////////////////////////////////////////////////////////////////////////////
//  Set sprite red channel                                                    //
////////////////////////////////////////////////////////////////////////////////
void Sprite::setRed(float red)
{
    m_color.vec[0] = red;
}

////////////////////////////////////////////////////////////////////////////////
//  Set sprite green channel                                                  //
////////////////////////////////////////////////////////////////////////////////
void Sprite::setGreen(float green)
{
    m_color.vec[1] = green;
}

////////////////////////////////////////////////////////////////////////////////
//  Set sprite blue channel                                                   //
////////////////////////////////////////////////////////////////////////////////
void Sprite::setBlue(float blue)
{
    m_color.vec[2] = blue;
}

////////////////////////////////////////////////////////////////////////////////
//  Set sprite alpha channel                                                  //
////////////////////////////////////////////////////////////////////////////////
void Sprite::setAlpha(float alpha)
{
    m_color.vec[3] = alpha;
}


////////////////////////////////////////////////////////////////////////////////
//  Render sprite                                                             //
////////////////////////////////////////////////////////////////////////////////
void Sprite::render(Renderer& renderer)
{
    // Compute sprite transformations
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

    // Bind sprite texture
    m_texture->bind(renderer);

    // Draw sprite triangles
    vkCmdDrawIndexed(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        6, 1, 0, 0, 0
    );
}
