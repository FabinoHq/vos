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
//     Renderer/GUI/GUISlider.cpp : GUI Slider management                     //
////////////////////////////////////////////////////////////////////////////////
#include "GUISlider.h"


////////////////////////////////////////////////////////////////////////////////
//  GUISlider default constructor                                             //
////////////////////////////////////////////////////////////////////////////////
GUISlider::GUISlider() :
Transform2(),
m_texture(0),
m_color(1.0f, 1.0f, 1.0f, 1.0f),
m_uvFactor(1.0f),
m_increments(GUISliderDefaultIncrements),
m_ctrlIncrements(GUISliderControlIncrements),
m_value(0.0f),
m_vertical(false),
m_control(false),
m_valueChanged(false),
m_disabled(false),
m_state(GUISLIDER_NONE)
{

}

////////////////////////////////////////////////////////////////////////////////
//  GUISlider virtual destructor                                              //
////////////////////////////////////////////////////////////////////////////////
GUISlider::~GUISlider()
{
    m_state = GUISLIDER_NONE;
    m_disabled = false;
    m_valueChanged = false;
    m_control = false;
    m_vertical = false;
    m_value = 0.0f;
    m_ctrlIncrements = 0.0f;
    m_increments = 0.0f;
    m_uvFactor = 0.0f;
    m_color.reset();
    m_texture = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Init slider                                                               //
//  return : True if the slider is successfully created                       //
////////////////////////////////////////////////////////////////////////////////
bool GUISlider::init(Texture& texture, float width, float height,
    float uvFactor, bool vertical)
{
    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Reset slider transformations
    resetTransforms();

    // Set slider size
    setSize(width, height);

    // Set slider texture pointer
    m_texture = &texture;

    // Reset slider color
    m_color.set(1.0f, 1.0f, 1.0f, 1.0f);

    // Set slider UV factor
    m_uvFactor = uvFactor;

    // Reset slider increments
    m_increments = GUISliderDefaultIncrements;
    m_ctrlIncrements = GUISliderControlIncrements;

    // Reset slider value
    m_value = 0.0f;

    // Set slider vertical state
    m_vertical = vertical;

    // Reset control state
    m_control = false;

    // Reset slider value changed
    m_valueChanged = false;

    // Reset slider disabled state
    m_disabled = false;

    // Reset slider state
    m_state = GUISLIDER_NONE;

    // Slider successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set slider texture                                                        //
//  return : True if slider texture is successfully set                       //
////////////////////////////////////////////////////////////////////////////////
bool GUISlider::setTexture(Texture& texture)
{
    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Set slider texture pointer
    m_texture = &texture;
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set slider color                                                          //
////////////////////////////////////////////////////////////////////////////////
void GUISlider::setColor(const Vector4& color)
{
    m_color.vec[0] = color.vec[0];
    m_color.vec[1] = color.vec[1];
    m_color.vec[2] = color.vec[2];
    m_color.vec[3] = color.vec[3];
}

////////////////////////////////////////////////////////////////////////////////
//  Set slider color                                                          //
////////////////////////////////////////////////////////////////////////////////
void GUISlider::setColor(float red, float green, float blue, float alpha)
{
    m_color.vec[0] = red;
    m_color.vec[1] = green;
    m_color.vec[2] = blue;
    m_color.vec[3] = alpha;
}


////////////////////////////////////////////////////////////////////////////////
//  Get slider picking state                                                  //
////////////////////////////////////////////////////////////////////////////////
bool GUISlider::isPicking(float mouseX, float mouseY)
{
    // Check if slider is picking
    if (m_vertical)
    {
        // Vertical slider
        if ((mouseX >= (m_position.vec[0] - m_size.vec[1]*0.5f)) &&
            (mouseX <= (m_position.vec[0] + m_size.vec[1]*0.5f)) &&
            (mouseY >= (m_position.vec[1] - m_size.vec[0]*0.5f)) &&
            (mouseY <= (m_position.vec[1] + m_size.vec[0]*0.5f)))
        {
            // Slider is picking
            return true;
        }
    }
    else
    {
        // Horizontal slider
        if ((mouseX >= (m_position.vec[0] - m_size.vec[0]*0.5f)) &&
            (mouseX <= (m_position.vec[0] + m_size.vec[0]*0.5f)) &&
            (mouseY >= (m_position.vec[1] - m_size.vec[1]*0.5f)) &&
            (mouseY <= (m_position.vec[1] + m_size.vec[1]*0.5f)))
        {
            // Slider is picking
            return true;
        }
    }
    return false;
}


////////////////////////////////////////////////////////////////////////////////
//  Handle slider mouse move event                                            //
////////////////////////////////////////////////////////////////////////////////
bool GUISlider::mouseMove(float mouseX, float mouseY)
{
    // Disabled state
    if (m_disabled) { m_state = GUISLIDER_NONE; return false; }

    // Set slider state
    if (isPicking(mouseX, mouseY))
    {
        if ((m_state == GUISLIDER_PRESSED) ||
            (m_state == GUISLIDER_PRESSEDHOVER))
        {
            m_state = GUISLIDER_PRESSEDHOVER;
            computeSliderValue(mouseX, mouseY);
            m_valueChanged = true;
            return true;
        }
        else
        {
            m_state = GUISLIDER_HOVER;
        }
    }
    else
    {
        if ((m_state == GUISLIDER_PRESSED) ||
            (m_state == GUISLIDER_PRESSEDHOVER))
        {
            m_state = GUISLIDER_PRESSED;
            computeSliderValue(mouseX, mouseY);
            m_valueChanged = true;
            return true;
        }
        else
        {
            m_state = GUISLIDER_NONE;
        }
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Handle slider mouse press event                                           //
////////////////////////////////////////////////////////////////////////////////
bool GUISlider::mousePress(float mouseX, float mouseY)
{
    // Disabled state
    if (m_disabled) { m_state = GUISLIDER_NONE; return false; }

    // Set slider state
    if (isPicking(mouseX, mouseY))
    {
        m_state = GUISLIDER_PRESSEDHOVER;
        computeSliderValue(mouseX, mouseY);
        m_valueChanged = true;
        return true;
    }
    else
    {
        m_state = GUISLIDER_NONE;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Handle slider mouse release event                                         //
////////////////////////////////////////////////////////////////////////////////
bool GUISlider::mouseRelease(float mouseX, float mouseY)
{
    // Disabled state
    if (m_disabled) { m_state = GUISLIDER_NONE; return false; }

    // Set slider state
    if ((m_state == GUISLIDER_PRESSED) || (m_state == GUISLIDER_PRESSEDHOVER))
    {
        computeSliderValue(mouseX, mouseY);
        if (isPicking(mouseX, mouseY))
        {
            m_state = GUISLIDER_HOVER;
        }
        else
        {
            m_state = GUISLIDER_NONE;
        }
        m_valueChanged = true;
        return true;
    }
    if (isPicking(mouseX, mouseY))
    {
        m_state = GUISLIDER_HOVER;
    }
    else
    {
        m_state = GUISLIDER_NONE;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Handle slider mouse wheel event                                           //
////////////////////////////////////////////////////////////////////////////////
void GUISlider::mouseWheel(int mouseWheel)
{
    // Disabled state
    if (m_disabled) { m_state = GUISLIDER_NONE; return; }

    // Mouse wheel event
    if (m_state == GUISLIDER_HOVER)
    {
        if (mouseWheel > 0)
        {
            // Mouse wheel up
            increment();
        }
        else if (mouseWheel < 0)
        {
            // Mouse wheel down
            decrement();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Increment slider value                                                    //
////////////////////////////////////////////////////////////////////////////////
void GUISlider::increment()
{
    // Disabled state
    if (m_disabled) { return; }

    // Increment slider value
    m_value = Math::clamp(
        m_value+(m_control?m_ctrlIncrements:m_increments), 0.0f, 1.0f
    );
    m_valueChanged = true;
}

////////////////////////////////////////////////////////////////////////////////
//  Decrement slider value                                                    //
////////////////////////////////////////////////////////////////////////////////
void GUISlider::decrement()
{
    // Disabled state
    if (m_disabled) { return; }

    // Decrement slider value
    m_value = Math::clamp(
        m_value-(m_control?m_ctrlIncrements:m_increments), 0.0f, 1.0f
    );
    m_valueChanged = true;
}

////////////////////////////////////////////////////////////////////////////////
//  Render slider                                                             //
////////////////////////////////////////////////////////////////////////////////
void GUISlider::render()
{
    // Disabled state
    if (m_disabled) { m_state = GUISLIDER_NONE; }

    // Compute slider transformations
    m_matrix.setIdentity();
    m_matrix.translate(m_position);
    if (m_vertical)
    {
        // Vertical slider
        m_matrix.rotateZ(Math::PiHalf);
        m_matrix.translate(-m_origin);
    }
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
    switch (m_state)
    {
        case GUISLIDER_HOVER:
        case GUISLIDER_PRESSED:
        case GUISLIDER_PRESSEDHOVER:
            pushConstants.offset[0] = 0.5f;
            pushConstants.offset[1] = 0.0f;
            break;

        default:
            pushConstants.offset[0] = 0.0f;
            pushConstants.offset[1] = 0.0f;
            break;
    }

    vkCmdPushConstants(
        GSwapchain.commandBuffers[GSwapchain.current],
        GGraphicsLayout.handle, VK_SHADER_STAGE_FRAGMENT_BIT,
        PushConstantDataOffset, PushConstantDataNoSizeTimeSize, &pushConstants
    );

    // Draw background bar triangles
    vkCmdDrawIndexed(
        GSwapchain.commandBuffers[GSwapchain.current],
        6, 1, 0, 0, 0
    );
}


////////////////////////////////////////////////////////////////////////////////
//  Compute slider value from mouse position                                  //
////////////////////////////////////////////////////////////////////////////////
void GUISlider::computeSliderValue(float mouseX, float mouseY)
{
    if (m_vertical)
    {
        // Vertical slider
        if (m_size.vec[0] != 0.0f)
        {
            m_value = Math::clamp(((mouseY-(m_position.vec[1]-
                (m_size.vec[0]*0.5f)))/m_size.vec[0]), 0.0f, 1.0f);
        }
    }
    else
    {
        // Horizontal slider
        if (m_size.vec[0] != 0.0f)
        {
            m_value = Math::clamp(((mouseX-(m_position.vec[0]-
                (m_size.vec[0]*0.5f)))/m_size.vec[0]), 0.0f, 1.0f);
        }
    }
}
