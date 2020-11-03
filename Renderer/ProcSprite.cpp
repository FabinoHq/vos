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
//     Renderer/ProcSprite.cpp : Procedural sprite management                 //
////////////////////////////////////////////////////////////////////////////////
#include "ProcSprite.h"
#include "Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  ProcSprite default constructor                                            //
////////////////////////////////////////////////////////////////////////////////
ProcSprite::ProcSprite() :
m_modelMatrix(),
m_position(0.0f, 0.0f),
m_size(1.0f, 1.0f),
m_angle(0.0f)
{
    m_modelMatrix.reset();
}

////////////////////////////////////////////////////////////////////////////////
//  ProcSprite destructor                                                     //
////////////////////////////////////////////////////////////////////////////////
ProcSprite::~ProcSprite()
{
    m_angle = 0.0f;
    m_size.reset();
    m_position.reset();
    m_modelMatrix.reset();
}


////////////////////////////////////////////////////////////////////////////////
//  Init procedural sprite                                                    //
//  return : True if the proc sprite is successfully created                  //
////////////////////////////////////////////////////////////////////////////////
bool ProcSprite::init(float width, float height)
{
    // Reset procedural sprite model matrix
    m_modelMatrix.setIdentity();

    // Reset procedural sprite position
    m_position.reset();

    // Set procedural sprite size
    m_size.set(width, height);

    // Reset procedural sprite angle
    m_angle = 0.0f;

    // Procedural sprite successfully created
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Set procedural sprite position                                            //
////////////////////////////////////////////////////////////////////////////////
void ProcSprite::setPosition(float x, float y)
{
    m_position.vec[0] = x;
    m_position.vec[1] = y;
}

////////////////////////////////////////////////////////////////////////////////
//  Set procedural sprite position                                            //
////////////////////////////////////////////////////////////////////////////////
void ProcSprite::setPosition(Vector2& position)
{
    m_position.vec[0] = position.vec[0];
    m_position.vec[1] = position.vec[1];
}

////////////////////////////////////////////////////////////////////////////////
//  Set procedural sprite X position                                          //
////////////////////////////////////////////////////////////////////////////////
void ProcSprite::setX(float x)
{
    m_position.vec[0] = x;
}

////////////////////////////////////////////////////////////////////////////////
//  Set procedural sprite Y position                                          //
////////////////////////////////////////////////////////////////////////////////
void ProcSprite::setY(float y)
{
    m_position.vec[1] = y;
}

////////////////////////////////////////////////////////////////////////////////
//  Translate procedural sprite                                               //
////////////////////////////////////////////////////////////////////////////////
void ProcSprite::move(float x, float y)
{
    m_position.vec[0] += x;
    m_position.vec[1] += y;
}

////////////////////////////////////////////////////////////////////////////////
//  Translate procedural sprite                                               //
////////////////////////////////////////////////////////////////////////////////
void ProcSprite::move(Vector2& vector)
{
    m_position.vec[0] += vector.vec[0];
    m_position.vec[1] += vector.vec[1];
}

////////////////////////////////////////////////////////////////////////////////
//  Translate procedural sprite on X axis                                     //
////////////////////////////////////////////////////////////////////////////////
void ProcSprite::moveX(float x)
{
    m_position.vec[0] += x;
}

////////////////////////////////////////////////////////////////////////////////
//  Translate procedural sprite on Y axis                                     //
////////////////////////////////////////////////////////////////////////////////
void ProcSprite::moveY(float y)
{
    m_position.vec[1] += y;
}

////////////////////////////////////////////////////////////////////////////////
//  Set procedural sprite size                                                //
////////////////////////////////////////////////////////////////////////////////
void ProcSprite::setSize(float width, float height)
{
    m_size.vec[0] = width;
    m_size.vec[1] = height;
}

////////////////////////////////////////////////////////////////////////////////
//  Set procedural sprite size                                                //
////////////////////////////////////////////////////////////////////////////////
void ProcSprite::setSize(Vector2& size)
{
    m_size.vec[0] = size.vec[0];
    m_size.vec[1] = size.vec[1];
}

////////////////////////////////////////////////////////////////////////////////
//  Set procedural sprite width                                               //
////////////////////////////////////////////////////////////////////////////////
void ProcSprite::setWidth(float width)
{
    m_size.vec[0] = width;
}

////////////////////////////////////////////////////////////////////////////////
//  Set procedural sprite height                                              //
////////////////////////////////////////////////////////////////////////////////
void ProcSprite::setHeight(float height)
{
    m_size.vec[1] = height;
}

////////////////////////////////////////////////////////////////////////////////
//  Set procedural sprite rotation angle                                      //
////////////////////////////////////////////////////////////////////////////////
void ProcSprite::setAngle(float angle)
{
    m_angle = angle;
}

////////////////////////////////////////////////////////////////////////////////
//  Rotate procedural sprite                                                  //
////////////////////////////////////////////////////////////////////////////////
void ProcSprite::rotate(float angle)
{
    m_angle += angle;
}


////////////////////////////////////////////////////////////////////////////////
//  Render procedural sprite                                                  //
////////////////////////////////////////////////////////////////////////////////
void ProcSprite::render(Renderer& renderer)
{
    // Set procedural sprite model matrix
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

    // Draw procedural sprite triangles
    vkCmdDrawIndexed(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        6, 1, 0, 0, 0
    );
}
