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
//     Renderer/GUI/GUIWindow.h : GUI Window management                       //
////////////////////////////////////////////////////////////////////////////////
#include "GUIWindow.h"
#include "../Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  GUIWindow default constructor                                             //
////////////////////////////////////////////////////////////////////////////////
GUIWindow::GUIWindow() :
Transform2(),
m_texture(0),
m_color(1.0f, 1.0f, 1.0f, 1.0f),
m_uvFactor(1.0f)
{

}

////////////////////////////////////////////////////////////////////////////////
//  GUIWindow virtual destructor                                              //
////////////////////////////////////////////////////////////////////////////////
GUIWindow::~GUIWindow()
{
    m_color.reset();
}


////////////////////////////////////////////////////////////////////////////////
//  Init window                                                               //
//  return : True if the window is successfully created                       //
////////////////////////////////////////////////////////////////////////////////
bool GUIWindow::init(Texture& texture,
    float width, float height, float uvFactor)
{
    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Reset window transformations
    resetTransforms();

    // Set window size
    setSize(width, height);

    // Center window origin (anchor)
    centerOrigin();

    // Set window texture pointer
    m_texture = &texture;

    // Reset window color
    m_color.set(1.0f, 1.0f, 1.0f, 1.0f);

    // Set ninepatch UV factor
    m_uvFactor = uvFactor;

    // Window successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set window texture                                                        //
//  return : True if window texture is successfully set                       //
////////////////////////////////////////////////////////////////////////////////
bool GUIWindow::setTexture(Texture& texture)
{
    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Set window texture pointer
    m_texture = &texture;
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set window color                                                          //
////////////////////////////////////////////////////////////////////////////////
void GUIWindow::setColor(const Vector4& color)
{
    m_color.vec[0] = color.vec[0];
    m_color.vec[1] = color.vec[1];
    m_color.vec[2] = color.vec[2];
    m_color.vec[3] = color.vec[3];
}

////////////////////////////////////////////////////////////////////////////////
//  Set window color                                                          //
////////////////////////////////////////////////////////////////////////////////
void GUIWindow::setColor(float red, float green, float blue, float alpha)
{
    m_color.vec[0] = red;
    m_color.vec[1] = green;
    m_color.vec[2] = blue;
    m_color.vec[3] = alpha;
}

////////////////////////////////////////////////////////////////////////////////
//  Set window red channel                                                    //
////////////////////////////////////////////////////////////////////////////////
void GUIWindow::setRed(float red)
{
    m_color.vec[0] = red;
}

////////////////////////////////////////////////////////////////////////////////
//  Set window green channel                                                  //
////////////////////////////////////////////////////////////////////////////////
void GUIWindow::setGreen(float green)
{
    m_color.vec[1] = green;
}

////////////////////////////////////////////////////////////////////////////////
//  Set window blue channel                                                   //
////////////////////////////////////////////////////////////////////////////////
void GUIWindow::setBlue(float blue)
{
    m_color.vec[2] = blue;
}

////////////////////////////////////////////////////////////////////////////////
//  Set window alpha channel                                                  //
////////////////////////////////////////////////////////////////////////////////
void GUIWindow::setAlpha(float alpha)
{
    m_color.vec[3] = alpha;
}


////////////////////////////////////////////////////////////////////////////////
//  Render window                                                             //
////////////////////////////////////////////////////////////////////////////////
void GUIWindow::render(Renderer& renderer)
{
    // Compute window transformations
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
    pushConstants.size[0] = m_size.vec[0];
    pushConstants.size[1] = m_size.vec[1];
    pushConstants.time = m_uvFactor;

    vkCmdPushConstants(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        renderer.m_layout.handle, VK_SHADER_STAGE_FRAGMENT_BIT,
        PushConstantDataOffset, PushConstantDataSize, &pushConstants
    );

    // Bind window texture
    m_texture->bind(renderer);

    // Draw window triangles
    vkCmdDrawIndexed(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        6, 1, 0, 0, 0
    );
}
