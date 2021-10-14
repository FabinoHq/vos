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
//     Renderer/Shapes/Oval.cpp : Ellipse shape management                    //
////////////////////////////////////////////////////////////////////////////////
#include "Oval.h"
#include "../Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  Oval default constructor                                                  //
////////////////////////////////////////////////////////////////////////////////
Oval::Oval() :
m_modelMatrix(),
m_position(0.0f, 0.0f),
m_size(1.0f, 1.0f),
m_angle(0.0f),
m_color(1.0f, 1.0f, 1.0f, 1.0f)
{
    m_modelMatrix.reset();
}

////////////////////////////////////////////////////////////////////////////////
//  Oval destructor                                                           //
////////////////////////////////////////////////////////////////////////////////
Oval::~Oval()
{
    m_color.reset();
    m_angle = 0.0f;
    m_size.reset();
    m_position.reset();
    m_modelMatrix.reset();
}


////////////////////////////////////////////////////////////////////////////////
//  Init oval                                                                 //
//  return : True if the oval is successfully created                         //
////////////////////////////////////////////////////////////////////////////////
bool Oval::init(float width, float height)
{
    // Reset oval model matrix
    m_modelMatrix.setIdentity();

    // Reset oval position
    m_position.reset();

    // Set oval size
    m_size.set(width, height);

    // Reset oval angle
    m_angle = 0.0f;

    // Reset oval color
    m_color.set(1.0f, 1.0f, 1.0f, 1.0f);

    // Oval successfully created
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Set oval position                                                         //
////////////////////////////////////////////////////////////////////////////////
void Oval::setPosition(float x, float y)
{
    m_position.vec[0] = x;
    m_position.vec[1] = y;
}

////////////////////////////////////////////////////////////////////////////////
//  Set oval position                                                         //
////////////////////////////////////////////////////////////////////////////////
void Oval::setPosition(Vector2& position)
{
    m_position.vec[0] = position.vec[0];
    m_position.vec[1] = position.vec[1];
}

////////////////////////////////////////////////////////////////////////////////
//  Set oval X position                                                       //
////////////////////////////////////////////////////////////////////////////////
void Oval::setX(float x)
{
    m_position.vec[0] = x;
}

////////////////////////////////////////////////////////////////////////////////
//  Set oval Y position                                                       //
////////////////////////////////////////////////////////////////////////////////
void Oval::setY(float y)
{
    m_position.vec[1] = y;
}

////////////////////////////////////////////////////////////////////////////////
//  Translate oval                                                            //
////////////////////////////////////////////////////////////////////////////////
void Oval::move(float x, float y)
{
    m_position.vec[0] += x;
    m_position.vec[1] += y;
}

////////////////////////////////////////////////////////////////////////////////
//  Translate oval                                                            //
////////////////////////////////////////////////////////////////////////////////
void Oval::move(Vector2& vector)
{
    m_position.vec[0] += vector.vec[0];
    m_position.vec[1] += vector.vec[1];
}

////////////////////////////////////////////////////////////////////////////////
//  Translate oval on X axis                                                  //
////////////////////////////////////////////////////////////////////////////////
void Oval::moveX(float x)
{
    m_position.vec[0] += x;
}

////////////////////////////////////////////////////////////////////////////////
//  Translate oval on Y axis                                                  //
////////////////////////////////////////////////////////////////////////////////
void Oval::moveY(float y)
{
    m_position.vec[1] += y;
}

////////////////////////////////////////////////////////////////////////////////
//  Set oval size                                                             //
////////////////////////////////////////////////////////////////////////////////
void Oval::setSize(float width, float height)
{
    m_size.vec[0] = width;
    m_size.vec[1] = height;
}

////////////////////////////////////////////////////////////////////////////////
//  Set oval size                                                             //
////////////////////////////////////////////////////////////////////////////////
void Oval::setSize(Vector2& size)
{
    m_size.vec[0] = size.vec[0];
    m_size.vec[1] = size.vec[1];
}

////////////////////////////////////////////////////////////////////////////////
//  Set oval width                                                            //
////////////////////////////////////////////////////////////////////////////////
void Oval::setWidth(float width)
{
    m_size.vec[0] = width;
}

////////////////////////////////////////////////////////////////////////////////
//  Set oval height                                                           //
////////////////////////////////////////////////////////////////////////////////
void Oval::setHeight(float height)
{
    m_size.vec[1] = height;
}

////////////////////////////////////////////////////////////////////////////////
//  Set oval rotation angle                                                   //
////////////////////////////////////////////////////////////////////////////////
void Oval::setAngle(float angle)
{
    m_angle = angle;
}

////////////////////////////////////////////////////////////////////////////////
//  Rotate oval                                                               //
////////////////////////////////////////////////////////////////////////////////
void Oval::rotate(float angle)
{
    m_angle += angle;
}


////////////////////////////////////////////////////////////////////////////////
//  Set oval color                                                            //
////////////////////////////////////////////////////////////////////////////////
void Oval::setColor(Vector4 color)
{
    m_color.vec[0] = color.vec[0];
    m_color.vec[1] = color.vec[1];
    m_color.vec[2] = color.vec[2];
    m_color.vec[3] = color.vec[3];
}

////////////////////////////////////////////////////////////////////////////////
//  Set oval color                                                            //
////////////////////////////////////////////////////////////////////////////////
void Oval::setColor(float red, float green, float blue, float alpha)
{
    m_color.vec[0] = red;
    m_color.vec[1] = green;
    m_color.vec[2] = blue;
    m_color.vec[3] = alpha;
}

////////////////////////////////////////////////////////////////////////////////
//  Set oval red channel                                                      //
////////////////////////////////////////////////////////////////////////////////
void Oval::setRed(float red)
{
    m_color.vec[0] = red;
}

////////////////////////////////////////////////////////////////////////////////
//  Set oval green channel                                                    //
////////////////////////////////////////////////////////////////////////////////
void Oval::setGreen(float green)
{
    m_color.vec[1] = green;
}

////////////////////////////////////////////////////////////////////////////////
//  Set oval blue channel                                                     //
////////////////////////////////////////////////////////////////////////////////
void Oval::setBlue(float blue)
{
    m_color.vec[2] = blue;
}

////////////////////////////////////////////////////////////////////////////////
//  Set oval alpha channel                                                    //
////////////////////////////////////////////////////////////////////////////////
void Oval::setAlpha(float alpha)
{
    m_color.vec[3] = alpha;
}


////////////////////////////////////////////////////////////////////////////////
//  Render oval                                                          //
////////////////////////////////////////////////////////////////////////////////
void Oval::render(Renderer& renderer)
{
    // Bind oval pipeline
    renderer.bindOvalPipeline();

    // Set oval model matrix
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
    pushConstants.color[0] = m_color.vec[0];
    pushConstants.color[1] = m_color.vec[1];
    pushConstants.color[2] = m_color.vec[2];
    pushConstants.color[3] = m_color.vec[3];
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

    // Draw oval triangles
    vkCmdDrawIndexed(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        6, 1, 0, 0, 0
    );
}
