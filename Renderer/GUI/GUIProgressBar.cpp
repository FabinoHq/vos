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
//     Renderer/GUI/GUIProgressBar.cpp : GUI Progress bar management          //
////////////////////////////////////////////////////////////////////////////////
#include "GUIProgressBar.h"


////////////////////////////////////////////////////////////////////////////////
//  GUIProgressBar default constructor                                        //
////////////////////////////////////////////////////////////////////////////////
GUIProgressBar::GUIProgressBar() :
Transform2(),
m_texture(0),
m_color(1.0f, 1.0f, 1.0f, 1.0f),
m_uvFactor(1.0f),
m_value(0.0f)
{

}

////////////////////////////////////////////////////////////////////////////////
//  GUIProgressBar virtual destructor                                         //
////////////////////////////////////////////////////////////////////////////////
GUIProgressBar::~GUIProgressBar()
{
    m_value = 0.0f;
    m_uvFactor = 0.0f;
    m_color.reset();
    m_texture = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Init progress bar                                                         //
//  return : True if the progress bar is successfully created                 //
////////////////////////////////////////////////////////////////////////////////
bool GUIProgressBar::init(Texture& texture,
    float width, float height, float uvFactor)
{
    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Reset progress bar transformations
    resetTransforms();

    // Set progress bar texture pointer
    m_texture = &texture;

    // Reset progress bar color
    m_color.set(1.0f, 1.0f, 1.0f, 1.0f);

    // Set progress bar UV factor
    m_uvFactor = uvFactor;

    // Set progress bar size
    setSize(width, height);

    // Reset progress bar value
    m_value = 0.0f;

    // Progress bar successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set progress bar texture                                                  //
//  return : True if progress bar texture is successfully set                 //
////////////////////////////////////////////////////////////////////////////////
bool GUIProgressBar::setTexture(Texture& texture)
{
    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Set progress bar texture pointer
    m_texture = &texture;
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set progress bar color                                                    //
////////////////////////////////////////////////////////////////////////////////
void GUIProgressBar::setColor(const Vector4& color)
{
    m_color.vec[0] = color.vec[0];
    m_color.vec[1] = color.vec[1];
    m_color.vec[2] = color.vec[2];
    m_color.vec[3] = color.vec[3];
}

////////////////////////////////////////////////////////////////////////////////
//  Set progress bar color                                                    //
////////////////////////////////////////////////////////////////////////////////
void GUIProgressBar::setColor(float red, float green, float blue, float alpha)
{
    m_color.vec[0] = red;
    m_color.vec[1] = green;
    m_color.vec[2] = blue;
    m_color.vec[3] = alpha;
}


////////////////////////////////////////////////////////////////////////////////
//  Get progress bar picking state                                            //
////////////////////////////////////////////////////////////////////////////////
bool GUIProgressBar::isPicking(float mouseX, float mouseY)
{
    if ((mouseX >= (m_position.vec[0] - m_size.vec[0]*0.5f)) &&
        (mouseX <= (m_position.vec[0] + m_size.vec[0]*0.5f)) &&
        (mouseY >= (m_position.vec[1] - m_size.vec[1]*0.5f)) &&
        (mouseY <= (m_position.vec[1] + m_size.vec[1]*0.5f)))
    {
        // Progress bar is picking
        return true;
    }
    return false;
}


////////////////////////////////////////////////////////////////////////////////
//  Render progress bar                                                       //
////////////////////////////////////////////////////////////////////////////////
void GUIProgressBar::render()
{
    // Compute progress bar transformations
    m_matrix.setIdentity();
    m_matrix.translate(m_position);
    m_matrix.scale(m_size);

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
    pushConstants.offset[0] = 1.0f;
    pushConstants.offset[1] = 0.0f;
    pushConstants.size[0] = m_size.vec[0];
    pushConstants.size[1] = m_size.vec[1];
    pushConstants.time = m_uvFactor;

    vkCmdPushConstants(
        GSwapchain.commandBuffers[GSwapchain.current],
        GGraphicsLayout.handle, VK_SHADER_STAGE_FRAGMENT_BIT,
        PushConstantDataOffset, PushConstantDataSize, &pushConstants
    );

    // Draw background bar triangles
    vkCmdDrawIndexed(
        GSwapchain.commandBuffers[GSwapchain.current],
        6, 1, 0, 0, 0
    );

    // Update model matrix
    m_matrix.translateX((m_value*0.5f)-0.5f);
    m_matrix.scaleX(m_value);
    vkCmdPushConstants(
        GSwapchain.commandBuffers[GSwapchain.current],
        GGraphicsLayout.handle, VK_SHADER_STAGE_VERTEX_BIT,
        PushConstantMatrixOffset, PushConstantMatrixSize, m_matrix.mat
    );

    // Update UV offset
    pushConstants.offset[0] = m_value;
    pushConstants.offset[1] = 0.5f;
    vkCmdPushConstants(
        GSwapchain.commandBuffers[GSwapchain.current],
        GGraphicsLayout.handle, VK_SHADER_STAGE_FRAGMENT_BIT,
        PushConstantOffsetOffset, PushConstantOffsetSize, &pushConstants.offset
    );

    // Draw progress bar triangles
    vkCmdDrawIndexed(
        GSwapchain.commandBuffers[GSwapchain.current],
        6, 1, 0, 0, 0
    );
}
