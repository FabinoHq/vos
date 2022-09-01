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
//     Renderer/Shapes/EllipseShape.cpp : Ellipse shape management            //
////////////////////////////////////////////////////////////////////////////////
#include "EllipseShape.h"
#include "../Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  EllipseShape default constructor                                          //
////////////////////////////////////////////////////////////////////////////////
EllipseShape::EllipseShape() :
Transform2(),
m_color(1.0f, 1.0f, 1.0f, 1.0f),
m_smooth(0.005f)
{

}

////////////////////////////////////////////////////////////////////////////////
//  EllipseShape virtual destructor                                           //
////////////////////////////////////////////////////////////////////////////////
EllipseShape::~EllipseShape()
{
    m_smooth = 0.0f;
    m_color.reset();
}


////////////////////////////////////////////////////////////////////////////////
//  Init ellipse                                                              //
//  return : True if the ellipse is successfully created                      //
////////////////////////////////////////////////////////////////////////////////
bool EllipseShape::init(float width, float height)
{
    // Reset ellipse transformations
    resetTransforms();

    // Set ellipse size
    setSize(width, height);

    // Center ellipse origin (anchor)
    centerOrigin();

    // Reset ellipse color
    m_color.set(1.0f, 1.0f, 1.0f, 1.0f);

    // Reset ellipse smooth amount
    m_smooth = 0.005f;

    // Ellipse successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set ellipse color                                                         //
////////////////////////////////////////////////////////////////////////////////
void EllipseShape::setColor(const Vector4& color)
{
    m_color.vec[0] = color.vec[0];
    m_color.vec[1] = color.vec[1];
    m_color.vec[2] = color.vec[2];
    m_color.vec[3] = color.vec[3];
}

////////////////////////////////////////////////////////////////////////////////
//  Set ellipse color                                                         //
////////////////////////////////////////////////////////////////////////////////
void EllipseShape::setColor(float red, float green, float blue, float alpha)
{
    m_color.vec[0] = red;
    m_color.vec[1] = green;
    m_color.vec[2] = blue;
    m_color.vec[3] = alpha;
}

////////////////////////////////////////////////////////////////////////////////
//  Set ellipse red channel                                                   //
////////////////////////////////////////////////////////////////////////////////
void EllipseShape::setRed(float red)
{
    m_color.vec[0] = red;
}

////////////////////////////////////////////////////////////////////////////////
//  Set ellipse green channel                                                 //
////////////////////////////////////////////////////////////////////////////////
void EllipseShape::setGreen(float green)
{
    m_color.vec[1] = green;
}

////////////////////////////////////////////////////////////////////////////////
//  Set ellipse blue channel                                                  //
////////////////////////////////////////////////////////////////////////////////
void EllipseShape::setBlue(float blue)
{
    m_color.vec[2] = blue;
}

////////////////////////////////////////////////////////////////////////////////
//  Set ellipse alpha channel                                                 //
////////////////////////////////////////////////////////////////////////////////
void EllipseShape::setAlpha(float alpha)
{
    m_color.vec[3] = alpha;
}

////////////////////////////////////////////////////////////////////////////////
//  Set ellipse smooth amount                                                 //
////////////////////////////////////////////////////////////////////////////////
void EllipseShape::setSmooth(float smooth)
{
    // Clamp smooth amount
    if (smooth <= 0.0f) { smooth = 0.0f; }
    if (smooth >= 1.0f) { smooth = 1.0f; }

    // Set smooth amount
    m_smooth = smooth;
}


////////////////////////////////////////////////////////////////////////////////
//  Render ellipse                                                            //
////////////////////////////////////////////////////////////////////////////////
void EllipseShape::render(Renderer& renderer)
{
    // Compute ellipse transformations
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
    pushConstants.offset[0] = 0.0f;
    pushConstants.offset[1] = 0.0f;
    pushConstants.size[0] = 1.0f;
    pushConstants.size[1] = 1.0f;
    pushConstants.time = m_smooth;

    vkCmdPushConstants(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        renderer.m_layout.handle, VK_SHADER_STAGE_FRAGMENT_BIT,
        PushConstantDataOffset, PushConstantDataSize, &pushConstants
    );

    // Draw ellipse triangles
    vkCmdDrawIndexed(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        6, 1, 0, 0, 0
    );
}
