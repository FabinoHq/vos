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
//     Renderer/GUI/GUIToggleButton.cpp : GUI Toggle Button management        //
////////////////////////////////////////////////////////////////////////////////
#include "GUIToggleButton.h"


////////////////////////////////////////////////////////////////////////////////
//  GUIToggleButton default constructor                                       //
////////////////////////////////////////////////////////////////////////////////
GUIToggleButton::GUIToggleButton() :
Transform2(),
m_texture(0),
m_color(1.0f, 1.0f, 1.0f, 1.0f),
m_round(false),
m_state(GUITOGGLEBUTTON_NONE),
m_toggle(false)
{

}

////////////////////////////////////////////////////////////////////////////////
//  GUIToggleButton virtual destructor                                        //
////////////////////////////////////////////////////////////////////////////////
GUIToggleButton::~GUIToggleButton()
{
    m_toggle = false;
    m_state = GUITOGGLEBUTTON_NONE;
    m_round = false;
	m_color.reset();
    m_texture = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Init toggle button                                                        //
//  return : True if the toggle button is successfully created                //
////////////////////////////////////////////////////////////////////////////////
bool GUIToggleButton::init(
    Texture& texture, float width, float height, bool round)
{
    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Reset toggle button transformations
    resetTransforms();

    // Set toggle button texture pointer
    m_texture = &texture;

    // Reset toggle button color
    m_color.set(1.0f, 1.0f, 1.0f, 1.0f);

    // Set toggle button round state
    m_round = round;

    // Set toggle button size
    setSize(width, height);

    // Reset toggle button state
    m_state = GUITOGGLEBUTTON_NONE;

    // Reset toggle state
    m_toggle = false;

    // Toggle button successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set toggle button texture                                                 //
//  return : True if toggle button texture is successfully set                //
////////////////////////////////////////////////////////////////////////////////
bool GUIToggleButton::setTexture(Texture& texture)
{
    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Set toggle button texture pointer
    m_texture = &texture;
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set toggle button color                                                   //
////////////////////////////////////////////////////////////////////////////////
void GUIToggleButton::setColor(const Vector4& color)
{
    m_color.vec[0] = color.vec[0];
    m_color.vec[1] = color.vec[1];
    m_color.vec[2] = color.vec[2];
    m_color.vec[3] = color.vec[3];
}

////////////////////////////////////////////////////////////////////////////////
//  Set toggle button color                                                   //
////////////////////////////////////////////////////////////////////////////////
void GUIToggleButton::setColor(float red, float green, float blue, float alpha)
{
    m_color.vec[0] = red;
    m_color.vec[1] = green;
    m_color.vec[2] = blue;
    m_color.vec[3] = alpha;
}


////////////////////////////////////////////////////////////////////////////////
//  Get toggle button picking state                                           //
////////////////////////////////////////////////////////////////////////////////
bool GUIToggleButton::isPicking(float mouseX, float mouseY)
{
    if ((mouseX >= (m_position.vec[0] - m_size.vec[0]*0.5f)) &&
        (mouseX <= (m_position.vec[0] + m_size.vec[0]*0.5f)) &&
        (mouseY >= (m_position.vec[1] - m_size.vec[1]*0.5f)) &&
        (mouseY <= (m_position.vec[1] + m_size.vec[1]*0.5f)))
    {
        if (m_round)
        {
            float rx = (m_size.vec[0]*0.5f);
            float ry = (m_size.vec[1]*0.5f);
            float dx = (mouseX - m_position.vec[0]);
            float dy = (mouseY - m_position.vec[1]);
            if ((rx != 0.0f) && (ry != 0.0f))
            {
                if ((((dx*dx) / (rx*rx)) + ((dy*dy) / (ry*ry))) < 1.0f)
                {
                    // Round toggle button is picking
                    return true;
                }
            }
        }
        else
        {
            // Toggle button is picking
            return true;
        }
    }
    return false;
}


////////////////////////////////////////////////////////////////////////////////
//  Handle toggle button mouse press event                                    //
////////////////////////////////////////////////////////////////////////////////
bool GUIToggleButton::mousePress(float mouseX, float mouseY)
{
    if (isPicking(mouseX, mouseY))
    {
        m_state = GUITOGGLEBUTTON_PRESSEDHOVER;
        return true;
    }
    else
    {
        m_state = GUITOGGLEBUTTON_NONE;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Handle toggle button mouse release event                                  //
////////////////////////////////////////////////////////////////////////////////
bool GUIToggleButton::mouseRelease(float mouseX, float mouseY)
{
    if (isPicking(mouseX, mouseY))
    {
        if (m_state == GUITOGGLEBUTTON_PRESSEDHOVER)
        {
            m_state = GUITOGGLEBUTTON_HOVER;
            return true;
        }
        m_state = GUITOGGLEBUTTON_HOVER;
    }
    else
    {
        m_state = GUITOGGLEBUTTON_NONE;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Handle toggle button mouse move event                                     //
////////////////////////////////////////////////////////////////////////////////
bool GUIToggleButton::mouseMove(float mouseX, float mouseY)
{
    if (isPicking(mouseX, mouseY))
    {
        if ((m_state == GUITOGGLEBUTTON_PRESSED) ||
            (m_state == GUITOGGLEBUTTON_PRESSEDHOVER))
        {
            m_state = GUITOGGLEBUTTON_PRESSEDHOVER;
            return true;
        }
        else
        {
            m_state = GUITOGGLEBUTTON_HOVER;
        }
    }
    else
    {
        if ((m_state == GUITOGGLEBUTTON_PRESSED) ||
            (m_state == GUITOGGLEBUTTON_PRESSEDHOVER))
        {
            m_state = GUITOGGLEBUTTON_PRESSED;
            return true;
        }
        else
        {
            m_state = GUITOGGLEBUTTON_NONE;
        }
    }
    return false;
}


////////////////////////////////////////////////////////////////////////////////
//  Render toggle button                                                      //
////////////////////////////////////////////////////////////////////////////////
void GUIToggleButton::render()
{
    // Compute toggle button transformations
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
    switch (m_state)
    {
        case GUITOGGLEBUTTON_HOVER:
            pushConstants.offset[0] = 0.5f;
            pushConstants.offset[1] = (m_toggle ? 0.5f : 0.0f);
            break;

        case GUITOGGLEBUTTON_PRESSED:
            pushConstants.offset[0] = 0.0f;
            pushConstants.offset[1] = (m_toggle ? 0.75f : 0.25f);
            break;

        case GUITOGGLEBUTTON_PRESSEDHOVER:
            pushConstants.offset[0] = 0.5f;
            pushConstants.offset[1] = (m_toggle ? 0.75f : 0.25f);
            break;

        default:
            pushConstants.offset[0] = 0.0f;
            pushConstants.offset[1] = (m_toggle ? 0.5f : 0.0f);
            break;
    }

    vkCmdPushConstants(
        GSwapchain.commandBuffers[GSwapchain.current],
        GGraphicsLayout.handle, VK_SHADER_STAGE_FRAGMENT_BIT,
        PushConstantDataOffset, PushConstantDataNoSizeTimeSize, &pushConstants
    );

    // Draw toggle button triangles
    vkCmdDrawIndexed(
        GSwapchain.commandBuffers[GSwapchain.current],
        6, 1, 0, 0, 0
    );
}
