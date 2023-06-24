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
//     Renderer/GUI/GUIButton.cpp : GUI Button management                     //
////////////////////////////////////////////////////////////////////////////////
#include "GUIButton.h"


////////////////////////////////////////////////////////////////////////////////
//  GUIButton default constructor                                             //
////////////////////////////////////////////////////////////////////////////////
GUIButton::GUIButton() :
Transform2(),
m_texture(0),
m_color(1.0f, 1.0f, 1.0f, 1.0f)
{

}

////////////////////////////////////////////////////////////////////////////////
//  GUIButton virtual destructor                                              //
////////////////////////////////////////////////////////////////////////////////
GUIButton::~GUIButton()
{
	m_color.reset();
    m_texture = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Init button                                                               //
//  return : True if the button is successfully created                       //
////////////////////////////////////////////////////////////////////////////////
bool GUIButton::init(Texture& texture)
{
    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Reset button transformations
    resetTransforms();

    // Set button texture pointer
    m_texture = &texture;

    // Reset button color
    m_color.set(1.0f, 1.0f, 1.0f, 1.0f);

    // Button successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set button texture                                                        //
//  return : True if button texture is successfully set                       //
////////////////////////////////////////////////////////////////////////////////
bool GUIButton::setTexture(Texture& texture)
{
    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Set button texture pointer
    m_texture = &texture;
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set button color                                                          //
////////////////////////////////////////////////////////////////////////////////
void GUIButton::setColor(const Vector4& color)
{
    m_color.vec[0] = color.vec[0];
    m_color.vec[1] = color.vec[1];
    m_color.vec[2] = color.vec[2];
    m_color.vec[3] = color.vec[3];
}

////////////////////////////////////////////////////////////////////////////////
//  Set button color                                                          //
////////////////////////////////////////////////////////////////////////////////
void GUIButton::setColor(float red, float green, float blue, float alpha)
{
    m_color.vec[0] = red;
    m_color.vec[1] = green;
    m_color.vec[2] = blue;
    m_color.vec[3] = alpha;
}


////////////////////////////////////////////////////////////////////////////////
//  Render button                                                             //
////////////////////////////////////////////////////////////////////////////////
void GUIButton::render()
{
    // Compute button transformations
    computeTransforms();

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
    pushConstants.offset[0] = 0.0f;
    pushConstants.offset[1] = 0.0f;
    pushConstants.size[0] = 1.0f;
    pushConstants.size[1] = 1.0f;

    vkCmdPushConstants(
        GSwapchain.commandBuffers[GSwapchain.current],
        GGraphicsLayout.handle, VK_SHADER_STAGE_FRAGMENT_BIT,
        PushConstantDataOffset, PushConstantDataNoTimeSize, &pushConstants
    );

    // Draw button triangles
    vkCmdDrawIndexed(
        GSwapchain.commandBuffers[GSwapchain.current],
        6, 1, 0, 0, 0
    );
}
