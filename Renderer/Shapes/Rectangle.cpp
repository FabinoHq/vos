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
//     Renderer/Shapes/Rectangle.cpp : Rectangle shape management             //
////////////////////////////////////////////////////////////////////////////////
#include "Rectangle.h"
#include "../Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  Rectangle default constructor                                             //
////////////////////////////////////////////////////////////////////////////////
Rectangle::Rectangle() :
m_modelMatrix(),
m_position(0.0f, 0.0f),
m_size(1.0f, 1.0f),
m_angle(0.0f)
{
    m_modelMatrix.reset();
}

////////////////////////////////////////////////////////////////////////////////
//  Rectangle destructor                                                      //
////////////////////////////////////////////////////////////////////////////////
Rectangle::~Rectangle()
{
    m_angle = 0.0f;
    m_size.reset();
    m_position.reset();
    m_modelMatrix.reset();
}


////////////////////////////////////////////////////////////////////////////////
//  Init rectangle                                                            //
//  return : True if the rectangle is successfully created                    //
////////////////////////////////////////////////////////////////////////////////
bool Rectangle::init(float width, float height)
{
    // Reset rectangle model matrix
    m_modelMatrix.setIdentity();

    // Reset rectangle position
    m_position.reset();

    // Set rectangle size
    m_size.set(width, height);

    // Reset rectangle angle
    m_angle = 0.0f;

    // Rectangle successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy rectangle                                                         //
////////////////////////////////////////////////////////////////////////////////
void Rectangle::destroyRectangle(Renderer& renderer)
{
    m_angle = 0.0f;
    m_size.reset();
    m_position.reset();
    m_modelMatrix.reset();
}


////////////////////////////////////////////////////////////////////////////////
//  Set rectangle position                                                    //
////////////////////////////////////////////////////////////////////////////////
void Rectangle::setPosition(float x, float y)
{
    m_position.vec[0] = x;
    m_position.vec[1] = y;
}

////////////////////////////////////////////////////////////////////////////////
//  Set rectangle position                                                    //
////////////////////////////////////////////////////////////////////////////////
void Rectangle::setPosition(Vector2& position)
{
    m_position.vec[0] = position.vec[0];
    m_position.vec[1] = position.vec[1];
}

////////////////////////////////////////////////////////////////////////////////
//  Set rectangle X position                                                  //
////////////////////////////////////////////////////////////////////////////////
void Rectangle::setX(float x)
{
    m_position.vec[0] = x;
}

////////////////////////////////////////////////////////////////////////////////
//  Set rectangle Y position                                                  //
////////////////////////////////////////////////////////////////////////////////
void Rectangle::setY(float y)
{
    m_position.vec[1] = y;
}

////////////////////////////////////////////////////////////////////////////////
//  Translate rectangle                                                       //
////////////////////////////////////////////////////////////////////////////////
void Rectangle::move(float x, float y)
{
    m_position.vec[0] += x;
    m_position.vec[1] += y;
}

////////////////////////////////////////////////////////////////////////////////
//  Translate rectangle                                                       //
////////////////////////////////////////////////////////////////////////////////
void Rectangle::move(Vector2& vector)
{
    m_position.vec[0] += vector.vec[0];
    m_position.vec[1] += vector.vec[1];
}

////////////////////////////////////////////////////////////////////////////////
//  Translate rectangle on X axis                                             //
////////////////////////////////////////////////////////////////////////////////
void Rectangle::moveX(float x)
{
    m_position.vec[0] += x;
}

////////////////////////////////////////////////////////////////////////////////
//  Translate rectangle on Y axis                                             //
////////////////////////////////////////////////////////////////////////////////
void Rectangle::moveY(float y)
{
    m_position.vec[1] += y;
}

////////////////////////////////////////////////////////////////////////////////
//  Set rectangle size                                                        //
////////////////////////////////////////////////////////////////////////////////
void Rectangle::setSize(float width, float height)
{
    m_size.vec[0] = width;
    m_size.vec[1] = height;
}

////////////////////////////////////////////////////////////////////////////////
//  Set rectangle size                                                        //
////////////////////////////////////////////////////////////////////////////////
void Rectangle::setSize(Vector2& size)
{
    m_size.vec[0] = size.vec[0];
    m_size.vec[1] = size.vec[1];
}

////////////////////////////////////////////////////////////////////////////////
//  Set rectangle width                                                       //
////////////////////////////////////////////////////////////////////////////////
void Rectangle::setWidth(float width)
{
    m_size.vec[0] = width;
}

////////////////////////////////////////////////////////////////////////////////
//  Set rectangle height                                                      //
////////////////////////////////////////////////////////////////////////////////
void Rectangle::setHeight(float height)
{
    m_size.vec[1] = height;
}

////////////////////////////////////////////////////////////////////////////////
//  Set rectangle rotation angle                                              //
////////////////////////////////////////////////////////////////////////////////
void Rectangle::setAngle(float angle)
{
    m_angle = angle;
}

////////////////////////////////////////////////////////////////////////////////
//  Rotate rectangle                                                          //
////////////////////////////////////////////////////////////////////////////////
void Rectangle::rotate(float angle)
{
    m_angle += angle;
}


////////////////////////////////////////////////////////////////////////////////
//  Render rectangle                                                          //
////////////////////////////////////////////////////////////////////////////////
void Rectangle::render(Renderer& renderer)
{
    // Set rectangle model matrix
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
        0, sizeof(Matrix4x4::mat), m_modelMatrix.mat
    );

    // Push constants into command buffer
    PushConstantData pushConstants;
    pushConstants.color[0] = 1.0f;
    pushConstants.color[1] = 1.0f;
    pushConstants.color[2] = 1.0f;
    pushConstants.color[3] = 1.0f;
    pushConstants.offset[0] = 0.0f;
    pushConstants.offset[1] = 0.0f;
    pushConstants.size[0] = 1.0f;
    pushConstants.size[1] = 1.0f;
    pushConstants.time = 0.0f;

    vkCmdPushConstants(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        renderer.m_layout.handle, VK_SHADER_STAGE_FRAGMENT_BIT,
        sizeof(Matrix4x4::mat), sizeof(PushConstantData), &pushConstants
    );

    // Draw rectangle triangles
    vkCmdDrawIndexed(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        6, 1, 0, 0, 0
    );
}
