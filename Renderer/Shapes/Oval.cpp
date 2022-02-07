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
Transform2(),
m_color(1.0f, 1.0f, 1.0f, 1.0f)
{

}

////////////////////////////////////////////////////////////////////////////////
//  Oval virtual destructor                                                   //
////////////////////////////////////////////////////////////////////////////////
Oval::~Oval()
{
    m_color.reset();
}


////////////////////////////////////////////////////////////////////////////////
//  Init oval                                                                 //
//  return : True if the oval is successfully created                         //
////////////////////////////////////////////////////////////////////////////////
bool Oval::init(float width, float height)
{
    // Reset oval transformations
    resetTransforms();

    // Set oval size
    setSize(width, height);

    // Center oval origin (anchor)
    centerOrigin();

    // Reset oval color
    m_color.set(1.0f, 1.0f, 1.0f, 1.0f);

    // Oval successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set oval color                                                            //
////////////////////////////////////////////////////////////////////////////////
void Oval::setColor(const Vector4& color)
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
//  Render oval                                                               //
////////////////////////////////////////////////////////////////////////////////
void Oval::render(Renderer& renderer)
{
    // Compute oval transformations
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

    // Draw oval triangles
    vkCmdDrawIndexed(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        6, 1, 0, 0, 0
    );
}
