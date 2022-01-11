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
//     Renderer/Shapes/Rect.cpp : Rectangle shape management                  //
////////////////////////////////////////////////////////////////////////////////
#include "Rect.h"
#include "../Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  Rect default constructor                                                  //
////////////////////////////////////////////////////////////////////////////////
Rect::Rect() :
m_modelMatrix(),
m_position(0.0f, 0.0f),
m_size(1.0f, 1.0f),
m_angle(0.0f),
m_color(1.0f, 1.0f, 1.0f, 1.0f)
{
    m_modelMatrix.reset();
}

////////////////////////////////////////////////////////////////////////////////
//  Rect destructor                                                           //
////////////////////////////////////////////////////////////////////////////////
Rect::~Rect()
{
    m_color.reset();
    m_angle = 0.0f;
    m_size.reset();
    m_position.reset();
    m_modelMatrix.reset();
}


////////////////////////////////////////////////////////////////////////////////
//  Init rect                                                                 //
//  return : True if the rect is successfully created                         //
////////////////////////////////////////////////////////////////////////////////
bool Rect::init(float width, float height)
{
    // Reset rect model matrix
    m_modelMatrix.setIdentity();

    // Reset rect position
    m_position.reset();

    // Set rect size
    m_size.set(width, height);

    // Reset rect angle
    m_angle = 0.0f;

    // Reset rect color
    m_color.set(1.0f, 1.0f, 1.0f, 1.0f);

    // Rect successfully created
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Set rect position                                                         //
////////////////////////////////////////////////////////////////////////////////
void Rect::setPosition(float x, float y)
{
    m_position.vec[0] = x;
    m_position.vec[1] = y;
}

////////////////////////////////////////////////////////////////////////////////
//  Set rect position                                                         //
////////////////////////////////////////////////////////////////////////////////
void Rect::setPosition(Vector2& position)
{
    m_position.vec[0] = position.vec[0];
    m_position.vec[1] = position.vec[1];
}

////////////////////////////////////////////////////////////////////////////////
//  Set rect X position                                                       //
////////////////////////////////////////////////////////////////////////////////
void Rect::setX(float x)
{
    m_position.vec[0] = x;
}

////////////////////////////////////////////////////////////////////////////////
//  Set rect Y position                                                       //
////////////////////////////////////////////////////////////////////////////////
void Rect::setY(float y)
{
    m_position.vec[1] = y;
}

////////////////////////////////////////////////////////////////////////////////
//  Translate rect                                                            //
////////////////////////////////////////////////////////////////////////////////
void Rect::move(float x, float y)
{
    m_position.vec[0] += x;
    m_position.vec[1] += y;
}

////////////////////////////////////////////////////////////////////////////////
//  Translate rect                                                            //
////////////////////////////////////////////////////////////////////////////////
void Rect::move(Vector2& vector)
{
    m_position.vec[0] += vector.vec[0];
    m_position.vec[1] += vector.vec[1];
}

////////////////////////////////////////////////////////////////////////////////
//  Translate rect on X axis                                                  //
////////////////////////////////////////////////////////////////////////////////
void Rect::moveX(float x)
{
    m_position.vec[0] += x;
}

////////////////////////////////////////////////////////////////////////////////
//  Translate rect on Y axis                                                  //
////////////////////////////////////////////////////////////////////////////////
void Rect::moveY(float y)
{
    m_position.vec[1] += y;
}

////////////////////////////////////////////////////////////////////////////////
//  Set rect size                                                             //
////////////////////////////////////////////////////////////////////////////////
void Rect::setSize(float width, float height)
{
    m_size.vec[0] = width;
    m_size.vec[1] = height;
}

////////////////////////////////////////////////////////////////////////////////
//  Set rect size                                                             //
////////////////////////////////////////////////////////////////////////////////
void Rect::setSize(Vector2& size)
{
    m_size.vec[0] = size.vec[0];
    m_size.vec[1] = size.vec[1];
}

////////////////////////////////////////////////////////////////////////////////
//  Set rect width                                                            //
////////////////////////////////////////////////////////////////////////////////
void Rect::setWidth(float width)
{
    m_size.vec[0] = width;
}

////////////////////////////////////////////////////////////////////////////////
//  Set rect height                                                           //
////////////////////////////////////////////////////////////////////////////////
void Rect::setHeight(float height)
{
    m_size.vec[1] = height;
}

////////////////////////////////////////////////////////////////////////////////
//  Set rect rotation angle                                                   //
////////////////////////////////////////////////////////////////////////////////
void Rect::setAngle(float angle)
{
    m_angle = angle;
}

////////////////////////////////////////////////////////////////////////////////
//  Rotate rect                                                               //
////////////////////////////////////////////////////////////////////////////////
void Rect::rotate(float angle)
{
    m_angle += angle;
}


////////////////////////////////////////////////////////////////////////////////
//  Set rect color                                                            //
////////////////////////////////////////////////////////////////////////////////
void Rect::setColor(Vector4 color)
{
    m_color.vec[0] = color.vec[0];
    m_color.vec[1] = color.vec[1];
    m_color.vec[2] = color.vec[2];
    m_color.vec[3] = color.vec[3];
}

////////////////////////////////////////////////////////////////////////////////
//  Set rect color                                                            //
////////////////////////////////////////////////////////////////////////////////
void Rect::setColor(float red, float green, float blue, float alpha)
{
    m_color.vec[0] = red;
    m_color.vec[1] = green;
    m_color.vec[2] = blue;
    m_color.vec[3] = alpha;
}

////////////////////////////////////////////////////////////////////////////////
//  Set rect red channel                                                      //
////////////////////////////////////////////////////////////////////////////////
void Rect::setRed(float red)
{
    m_color.vec[0] = red;
}

////////////////////////////////////////////////////////////////////////////////
//  Set rect green channel                                                    //
////////////////////////////////////////////////////////////////////////////////
void Rect::setGreen(float green)
{
    m_color.vec[1] = green;
}

////////////////////////////////////////////////////////////////////////////////
//  Set rect blue channel                                                     //
////////////////////////////////////////////////////////////////////////////////
void Rect::setBlue(float blue)
{
    m_color.vec[2] = blue;
}

////////////////////////////////////////////////////////////////////////////////
//  Set rect alpha channel                                                    //
////////////////////////////////////////////////////////////////////////////////
void Rect::setAlpha(float alpha)
{
    m_color.vec[3] = alpha;
}


////////////////////////////////////////////////////////////////////////////////
//  Render rect                                                               //
////////////////////////////////////////////////////////////////////////////////
void Rect::render(Renderer& renderer)
{
    // Set rect model matrix
    m_modelMatrix.setIdentity();
    m_modelMatrix.translate(m_position.vec[0], m_position.vec[1]);
    m_modelMatrix.translate(m_size.vec[0]*0.5f, m_size.vec[1]*0.5f);
    m_modelMatrix.rotateZ(m_angle);
    m_modelMatrix.translate(-m_size.vec[0]*0.5f, -m_size.vec[1]*0.5f);
    m_modelMatrix.scale(m_size.vec[0], m_size.vec[1]);

    // Push model matrix into command buffer
    vkCmdPushConstants(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        renderer.m_layout.handle, VK_SHADER_STAGE_VERTEX_BIT,
        PushConstantMatrixOffset, PushConstantMatrixSize, m_modelMatrix.mat
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

    // Draw rect triangles
    vkCmdDrawIndexed(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        6, 1, 0, 0, 0
    );
}
