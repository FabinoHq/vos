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
//     Renderer/GUI/GUIScrollBar.cpp : GUI Scroll bar management              //
////////////////////////////////////////////////////////////////////////////////
#include "GUIScrollBar.h"


////////////////////////////////////////////////////////////////////////////////
//  GUIScrollBar default constructor                                          //
////////////////////////////////////////////////////////////////////////////////
GUIScrollBar::GUIScrollBar() :
Transform2(),
m_texture(0),
m_color(1.0f, 1.0f, 1.0f, 1.0f),
m_uvFactor(1.0f),
m_increments(GUIScrollBarDefaultIncrements),
m_ctrlIncrements(GUIScrollBarControlIncrements),
m_scrollSize(GUIScrollBarMaxScrollSize),
m_value(0.0f),
m_vertical(false),
m_control(false),
m_valueChanged(false),
m_disabled(false),
m_state(GUISCROLLBAR_NONE)
{

}

////////////////////////////////////////////////////////////////////////////////
//  GUIScrollBar virtual destructor                                           //
////////////////////////////////////////////////////////////////////////////////
GUIScrollBar::~GUIScrollBar()
{
    m_state = GUISCROLLBAR_NONE;
    m_disabled = false;
    m_valueChanged = false;
    m_control = false;
    m_vertical = false;
    m_value = 0.0f;
    m_scrollSize = 0.0f;
    m_ctrlIncrements = 0.0f;
    m_increments = 0.0f;
    m_uvFactor = 0.0f;
    m_color.reset();
    m_texture = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Init scroll bar                                                           //
//  return : True if the scroll bar is successfully created                   //
////////////////////////////////////////////////////////////////////////////////
bool GUIScrollBar::init(Texture& texture, float width, float height,
    float uvFactor, bool vertical)
{
    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Reset scroll bar transformations
    resetTransforms();

    // Set scroll bar size
    setSize(width, height);

    // Set scroll bar texture pointer
    m_texture = &texture;

    // Reset scroll bar color
    m_color.set(1.0f, 1.0f, 1.0f, 1.0f);

    // Set scroll bar UV factor
    m_uvFactor = uvFactor;

    // Reset scroll bar increments
    m_increments = GUIScrollBarDefaultIncrements;
    m_ctrlIncrements = GUIScrollBarControlIncrements;

    // Reset scroll bar size
    m_scrollSize = GUIScrollBarMaxScrollSize;

    // Reset scroll bar value
    m_value = 0.0f;

    // Set scroll bar vertical state
    m_vertical = vertical;

    // Reset control state
    m_control = false;

    // Reset scroll bar value changed
    m_valueChanged = false;

    // Reset scroll bar disabled state
    m_disabled = false;

    // Reset scroll bar state
    m_state = GUISCROLLBAR_NONE;

    // Scroll bar successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set scroll bar texture                                                    //
//  return : True if scroll bar texture is successfully set                   //
////////////////////////////////////////////////////////////////////////////////
bool GUIScrollBar::setTexture(Texture& texture)
{
    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Set scroll bar texture pointer
    m_texture = &texture;
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set scroll bar color                                                      //
////////////////////////////////////////////////////////////////////////////////
void GUIScrollBar::setColor(const Vector4& color)
{
    m_color.vec[0] = color.vec[0];
    m_color.vec[1] = color.vec[1];
    m_color.vec[2] = color.vec[2];
    m_color.vec[3] = color.vec[3];
}

////////////////////////////////////////////////////////////////////////////////
//  Set scroll bar color                                                      //
////////////////////////////////////////////////////////////////////////////////
void GUIScrollBar::setColor(float red, float green, float blue, float alpha)
{
    m_color.vec[0] = red;
    m_color.vec[1] = green;
    m_color.vec[2] = blue;
    m_color.vec[3] = alpha;
}


////////////////////////////////////////////////////////////////////////////////
//  Get scroll bar picking state                                              //
////////////////////////////////////////////////////////////////////////////////
bool GUIScrollBar::isPicking(float mouseX, float mouseY)
{
    // Check if scroll bar is picking
    if (m_vertical)
    {
        // Vertical scroll bar
        if ((mouseX >= (m_position.vec[0] - m_size.vec[1]*0.5f)) &&
            (mouseX <= (m_position.vec[0] + m_size.vec[1]*0.5f)) &&
            (mouseY >= (m_position.vec[1] - m_size.vec[0]*0.5f)) &&
            (mouseY <= (m_position.vec[1] + m_size.vec[0]*0.5f)))
        {
            // Scroll bar is picking
            return true;
        }
    }
    else
    {
        // Horizontal scroll bar
        if ((mouseX >= (m_position.vec[0] - m_size.vec[0]*0.5f)) &&
            (mouseX <= (m_position.vec[0] + m_size.vec[0]*0.5f)) &&
            (mouseY >= (m_position.vec[1] - m_size.vec[1]*0.5f)) &&
            (mouseY <= (m_position.vec[1] + m_size.vec[1]*0.5f)))
        {
            // Scroll bar is picking
            return true;
        }
    }
    return false;
}


////////////////////////////////////////////////////////////////////////////////
//  Handle scroll bar mouse move event                                        //
////////////////////////////////////////////////////////////////////////////////
bool GUIScrollBar::mouseMove(float mouseX, float mouseY)
{
    // Disabled state
    if (m_disabled) { m_state = GUISCROLLBAR_NONE; return false; }

    // Set scroll bar state
    if (isPicking(mouseX, mouseY))
    {
        if ((m_state == GUISCROLLBAR_PRESSED) ||
            (m_state == GUISCROLLBAR_PRESSEDHOVER))
        {
            m_state = GUISCROLLBAR_PRESSEDHOVER;
            computeScrollBarValue(mouseX, mouseY);
            m_valueChanged = true;
            return true;
        }
        else
        {
            m_state = GUISCROLLBAR_HOVER;
        }
    }
    else
    {
        if ((m_state == GUISCROLLBAR_PRESSED) ||
            (m_state == GUISCROLLBAR_PRESSEDHOVER))
        {
            m_state = GUISCROLLBAR_PRESSED;
            computeScrollBarValue(mouseX, mouseY);
            m_valueChanged = true;
            return true;
        }
        else
        {
            m_state = GUISCROLLBAR_NONE;
        }
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Handle scroll bar mouse press event                                       //
////////////////////////////////////////////////////////////////////////////////
bool GUIScrollBar::mousePress(float mouseX, float mouseY)
{
    // Disabled state
    if (m_disabled) { m_state = GUISCROLLBAR_NONE; return false; }

    // Set scroll bar state
    if (isPicking(mouseX, mouseY))
    {
        m_state = GUISCROLLBAR_PRESSEDHOVER;
        computeScrollBarValue(mouseX, mouseY);
        m_valueChanged = true;
        return true;
    }
    else
    {
        m_state = GUISCROLLBAR_NONE;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Handle scroll bar mouse release event                                     //
////////////////////////////////////////////////////////////////////////////////
bool GUIScrollBar::mouseRelease(float mouseX, float mouseY)
{
    // Disabled state
    if (m_disabled) { m_state = GUISCROLLBAR_NONE; return false; }

    // Set scroll bar state
    if ((m_state == GUISCROLLBAR_PRESSED) ||
        (m_state == GUISCROLLBAR_PRESSEDHOVER))
    {
        computeScrollBarValue(mouseX, mouseY);
        if (isPicking(mouseX, mouseY))
        {
            m_state = GUISCROLLBAR_HOVER;
        }
        else
        {
            m_state = GUISCROLLBAR_NONE;
        }
        m_valueChanged = true;
        return true;
    }
    if (isPicking(mouseX, mouseY))
    {
        m_state = GUISCROLLBAR_HOVER;
    }
    else
    {
        m_state = GUISCROLLBAR_NONE;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Handle scroll bar mouse wheel event                                       //
////////////////////////////////////////////////////////////////////////////////
void GUIScrollBar::mouseWheel(int mouseWheel)
{
    // Disabled state
    if (m_disabled) { m_state = GUISCROLLBAR_NONE; return; }

    // Window mouse wheel event
    if (m_state == GUISCROLLBAR_HOVER)
    {
        windowMouseWheel(mouseWheel);
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Handle scroll bar window mouse wheel event                                //
////////////////////////////////////////////////////////////////////////////////
void GUIScrollBar::windowMouseWheel(int mouseWheel)
{
    // Disabled state
    if (m_disabled) { m_state = GUISCROLLBAR_NONE; return; }

    // Mouse wheel event
    if (mouseWheel > 0)
    {
        // Mouse wheel up
        if (m_vertical)
        {
            decrement();
        }
        else
        {
            increment();
        }
    }
    else if (mouseWheel < 0)
    {
        // Mouse wheel down
        if (m_vertical)
        {
            increment();
        }
        else
        {
            decrement();
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
//  Render scroll bar                                                         //
////////////////////////////////////////////////////////////////////////////////
void GUIScrollBar::render()
{
    // Disabled state
    if (m_disabled) { m_state = GUISCROLLBAR_NONE; }

    // Compute scroll bar transformations
    m_matrix.setIdentity();
    m_matrix.translate(m_position);
    if (m_vertical)
    {
        // Vertical scroll bar
        m_matrix.rotateZ(-Math::PiHalf);
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
        case GUISCROLLBAR_HOVER:
        case GUISCROLLBAR_PRESSED:
        case GUISCROLLBAR_PRESSEDHOVER:
            pushConstants.offset[0] = 0.5f;
            pushConstants.offset[1] = 0.0f;
            break;

        default:
            pushConstants.offset[0] = 0.0f;
            pushConstants.offset[1] = 0.0f;
            break;
    }
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
    m_matrix.translateX(m_value*(1.0f-m_scrollSize)-(0.5f-(m_scrollSize*0.5f)));
    m_matrix.scaleX(m_scrollSize);

    // Push model matrix into command buffer
    vkCmdPushConstants(
        GSwapchain.commandBuffers[GSwapchain.current],
        GGraphicsLayout.handle, VK_SHADER_STAGE_VERTEX_BIT,
        PushConstantMatrixOffset, PushConstantMatrixSize, m_matrix.mat
    );

    // Push constants into command buffer
    switch (m_state)
    {
        case GUISCROLLBAR_HOVER:
        case GUISCROLLBAR_PRESSED:
        case GUISCROLLBAR_PRESSEDHOVER:
            pushConstants.offset[0] = 0.5f;
            pushConstants.offset[1] = 0.5f;
            break;

        default:
            pushConstants.offset[0] = 0.0f;
            pushConstants.offset[1] = 0.5f;
            break;
    }
    pushConstants.time = (m_uvFactor*m_scrollSize);

    vkCmdPushConstants(
        GSwapchain.commandBuffers[GSwapchain.current],
        GGraphicsLayout.handle, VK_SHADER_STAGE_FRAGMENT_BIT,
        PushConstantDataOffset, PushConstantDataSize, &pushConstants
    );

    // Draw scroll bar triangles
    vkCmdDrawIndexed(
        GSwapchain.commandBuffers[GSwapchain.current],
        6, 1, 0, 0, 0
    );
}


////////////////////////////////////////////////////////////////////////////////
//  Compute scroll bar value from mouse position                              //
////////////////////////////////////////////////////////////////////////////////
void GUIScrollBar::computeScrollBarValue(float mouseX, float mouseY)
{
    float scrollSize = (m_size.vec[0]-(m_scrollSize*m_size.vec[0]));
    if (m_vertical)
    {
        // Vertical scroll bar
        if (scrollSize != 0.0f)
        {
            m_value = Math::clamp(((-mouseY-(-m_position.vec[1]-
                (m_size.vec[0]*0.5f)+(m_scrollSize*m_size.vec[0]*0.5f)))/
                scrollSize), 0.0f, 1.0f
            );
        }
    }
    else
    {
        // Horizontal scroll bar
        if (scrollSize != 0.0f)
        {
            m_value = Math::clamp(((mouseX-(m_position.vec[0]-
                (m_size.vec[0]*0.5f)+(m_scrollSize*m_size.vec[0]*0.5f)))/
                scrollSize), 0.0f, 1.0f
            );
        }
    }
}
