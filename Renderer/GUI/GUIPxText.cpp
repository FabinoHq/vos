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
//     Renderer/GUI/GUIPxText.cpp : GUI PixelText (distance field) management //
////////////////////////////////////////////////////////////////////////////////
#include "GUIPxText.h"


////////////////////////////////////////////////////////////////////////////////
//  GUIPxText default constructor                                             //
////////////////////////////////////////////////////////////////////////////////
GUIPxText::GUIPxText() :
Transform2(),
m_texture(0),
m_color(1.0f, 1.0f, 1.0f, 1.0f),
m_smooth(0.1f),
m_text("")
{

}

////////////////////////////////////////////////////////////////////////////////
//  GUIPxText virtual destructor                                              //
////////////////////////////////////////////////////////////////////////////////
GUIPxText::~GUIPxText()
{
    m_text = "";
    m_smooth = 0.0f;
    m_color.reset();
}


////////////////////////////////////////////////////////////////////////////////
//  Init pixel text                                                           //
//  return : True if the pixel text is successfully created                   //
////////////////////////////////////////////////////////////////////////////////
bool GUIPxText::init(Texture& texture, float height)
{
    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Reset pixel text transformations
    resetTransforms();

    // Set pixel text size
    setSize(0.0f, height);

    // Center pixel text origin (anchor)
    centerOrigin();

    // Set pixel text texture pointer
    m_texture = &texture;

    // Reset pixel text color
    m_color.set(1.0f, 1.0f, 1.0f, 1.0f);

    // Reset pixel text smooth amount
    m_smooth = 0.1f;

    // Reset pixel text internal string
    m_text = "";

    // Pixel text successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set pixel text texture                                                    //
//  return : True if pixel text texture is successfully set                   //
////////////////////////////////////////////////////////////////////////////////
bool GUIPxText::setTexture(Texture& texture)
{
    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Set pixel text texture pointer
    m_texture = &texture;
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set pixel text internal string                                            //
////////////////////////////////////////////////////////////////////////////////
void GUIPxText::setText(const std::string& text)
{
    // Set pixel text internal string
    m_text = text;

    // Update pixel text width
    if (m_text.length() <= 0)
    {
        m_size.vec[0] = 0.0f;
    }
    else
    {
        m_size.vec[0] = (m_size.vec[1] +
            (m_size.vec[1] * PixelTextDefaultXOffset * (m_text.length()-1))
        );
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Set pixel text color                                                      //
////////////////////////////////////////////////////////////////////////////////
void GUIPxText::setColor(const Vector4& color)
{
    m_color.vec[0] = color.vec[0];
    m_color.vec[1] = color.vec[1];
    m_color.vec[2] = color.vec[2];
    m_color.vec[3] = color.vec[3];
}

////////////////////////////////////////////////////////////////////////////////
//  Set pixel text color                                                      //
////////////////////////////////////////////////////////////////////////////////
void GUIPxText::setColor(float red, float green, float blue, float alpha)
{
    m_color.vec[0] = red;
    m_color.vec[1] = green;
    m_color.vec[2] = blue;
    m_color.vec[3] = alpha;
}

////////////////////////////////////////////////////////////////////////////////
//  Set pixel text red channel                                                //
////////////////////////////////////////////////////////////////////////////////
void GUIPxText::setRed(float red)
{
    m_color.vec[0] = red;
}

////////////////////////////////////////////////////////////////////////////////
//  Set pixel text green channel                                              //
////////////////////////////////////////////////////////////////////////////////
void GUIPxText::setGreen(float green)
{
    m_color.vec[1] = green;
}

////////////////////////////////////////////////////////////////////////////////
//  Set pixel text blue channel                                               //
////////////////////////////////////////////////////////////////////////////////
void GUIPxText::setBlue(float blue)
{
    m_color.vec[2] = blue;
}

////////////////////////////////////////////////////////////////////////////////
//  Set pixel text alpha channel                                              //
////////////////////////////////////////////////////////////////////////////////
void GUIPxText::setAlpha(float alpha)
{
    m_color.vec[3] = alpha;
}

////////////////////////////////////////////////////////////////////////////////
//  Set pixel text smooth amount                                              //
////////////////////////////////////////////////////////////////////////////////
void GUIPxText::setSmooth(float smooth)
{
    // Clamp smooth amount
    if (smooth <= 0.0f) { smooth = 0.0f; }
    if (smooth >= 1.0f) { smooth = 1.0f; }

    // Set smooth amount
    m_smooth = smooth;
}


////////////////////////////////////////////////////////////////////////////////
//  Get pixel text length                                                     //
////////////////////////////////////////////////////////////////////////////////
size_t GUIPxText::getLength()
{
    return m_text.length();
}


////////////////////////////////////////////////////////////////////////////////
//  Bind pixel text texture                                                   //
////////////////////////////////////////////////////////////////////////////////
void GUIPxText::bindTexture()
{
    m_texture->bind();
}

////////////////////////////////////////////////////////////////////////////////
//  Render pixel text                                                         //
////////////////////////////////////////////////////////////////////////////////
void GUIPxText::render()
{
    // Compute pixel text transformations
    m_matrix.setIdentity();
    m_matrix.translate(m_position);
    m_matrix.rotateZ(m_angle);
    m_matrix.translate(-m_origin);
    m_matrix.scale(m_size.vec[1], m_size.vec[1]);

    // Push UV constants into command buffer
    PushConstantData pushConstants;
    pushConstants.color[0] = m_color.vec[0];
    pushConstants.color[1] = m_color.vec[1];
    pushConstants.color[2] = m_color.vec[2];
    pushConstants.color[3] = m_color.vec[3];
    pushConstants.offset[0] = 0.0f;
    pushConstants.offset[1] = 0.0f;
    pushConstants.size[0] = PixelTextDefaultUVWidth;
    pushConstants.size[1] = PixelTextDefaultUVHeight;
    pushConstants.time = m_smooth*PixelTextDefaultSmoothFactor;

    vkCmdPushConstants(
        GSwapchain.commandBuffers[GSwapchain.current],
        GGraphicsLayout.handle, VK_SHADER_STAGE_FRAGMENT_BIT,
        PushConstantDataOffset, PushConstantDataSize, &pushConstants
    );

    // Draw pixel text characters
    for (size_t i = 0; i < m_text.length(); ++i)
    {
        // Get char code
        char charCode = m_text[i]-32;
        if (charCode < 0) { charCode = 31; }
        if (charCode > 94) { charCode = 31; }
        int charX = (charCode%16);
        int charY = (charCode/16);
        if (charX <= 0) { charX = 0; }
        if (charX >= 15) { charX = 15; }
        if (charY <= 0) { charY = 0; }
        if (charY >= 5) { charY = 5; }

        // Push model matrix into command buffer
        vkCmdPushConstants(
            GSwapchain.commandBuffers[GSwapchain.current],
            GGraphicsLayout.handle, VK_SHADER_STAGE_VERTEX_BIT,
            PushConstantMatrixOffset, PushConstantMatrixSize, m_matrix.mat
        );

        // Push UV constants into command buffer
        pushConstants.offset[0] = charX*PixelTextDefaultUVWidth;
        pushConstants.offset[1] = charY*PixelTextDefaultUVHeight;

        vkCmdPushConstants(
            GSwapchain.commandBuffers[GSwapchain.current],
            GGraphicsLayout.handle, VK_SHADER_STAGE_FRAGMENT_BIT,
            PushConstantOffsetOffset, PushConstantOffsetSize,
            &pushConstants.offset
        );

        // Draw current character triangles
        vkCmdDrawIndexed(
            GSwapchain.commandBuffers[GSwapchain.current],
            6, 1, 0, 0, 0
        );

        // Move to the next character
        m_matrix.translateX(PixelTextDefaultXOffset);
    }
}
