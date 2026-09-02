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
//     Renderer/GUI/GUIPxTextBox.cpp : GUI Pixel text box management          //
////////////////////////////////////////////////////////////////////////////////
#include "GUIPxTextBox.h"


////////////////////////////////////////////////////////////////////////////////
//  GUIPxTextBox default constructor                                          //
////////////////////////////////////////////////////////////////////////////////
GUIPxTextBox::GUIPxTextBox() :
Transform2(),
m_texture(0),
m_color(1.0f, 1.0f, 1.0f, 1.0f),
m_uvFactor(1.0f),
m_text(),
m_cursor(0),
m_cursorTime(0.0f),
m_leftSelection(0),
m_rightSelection(0),
m_shift(false),
m_selecting(false),
m_active(false),
m_textChanged(false),
m_disabled(false),
m_state(GUIPXTEXTBOX_NONE)
{

}

////////////////////////////////////////////////////////////////////////////////
//  GUIPxTextBox virtual destructor                                           //
////////////////////////////////////////////////////////////////////////////////
GUIPxTextBox::~GUIPxTextBox()
{
    m_state = GUIPXTEXTBOX_NONE;
    m_disabled = false;
    m_textChanged = false;
    m_active = false;
    m_selecting = false;
    m_shift = false;
    m_rightSelection = 0;
    m_leftSelection = 0;
    m_cursorTime = 0.0f;
    m_cursor = 0;
    m_text.clear();
    m_uvFactor = 0.0f;
    m_color.reset();
    m_texture = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Init pixel text box                                                       //
//  return : True if the pixel text box is successfully created               //
////////////////////////////////////////////////////////////////////////////////
bool GUIPxTextBox::init(Texture& texture, Texture& pixelFont,
    float width, float height, float uvFactor)
{
    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Reset text box transformations
    resetTransforms();

    // Set text box size
    setSize(width, height);

    // Set pixel text box texture pointer
    m_texture = &texture;

    // Reset text box color
    m_color.set(1.0f, 1.0f, 1.0f, 1.0f);

    // Set text box UV factor
    m_uvFactor = uvFactor;

    // Init text box text
    if (!m_text.init(pixelFont, height*GUIPxTextBoxHeightFactor))
    {
        // Could not init text box text
        return false;
    }

    // Reset text box cursor position
    m_cursor = 0;

    // Reset text box cursor time
    m_cursorTime = 0.0f;

    // Reset text box selection
    m_leftSelection = 0;
    m_rightSelection = 0;

    // Reset text box shift state
    m_shift = false;

    // Reset text box selecting state
    m_selecting = false;

    // Reset text box active state
    m_active = false;

    // Reset text box text changed
    m_textChanged = false;

    // Reset text box disabled state
    m_disabled = false;

    // Reset text box state
    m_state = GUIPXTEXTBOX_NONE;

    // Text box successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set text box texture                                                      //
//  return : True if text box texture is successfully set                     //
////////////////////////////////////////////////////////////////////////////////
bool GUIPxTextBox::setTexture(Texture& texture)
{
    // Check texture handle
    if (!texture.isValid())
    {
        // Invalid texture handle
        return false;
    }

    // Set text box texture pointer
    m_texture = &texture;
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Set pixel text box pixel font                                             //
//  return : True if pixel text box pixel font is set                         //
////////////////////////////////////////////////////////////////////////////////
bool GUIPxTextBox::setPixelFont(Texture& pixelFont)
{
    return (m_text.setTexture(pixelFont));
}

////////////////////////////////////////////////////////////////////////////////
//  Set pixel text box size                                                   //
////////////////////////////////////////////////////////////////////////////////
void GUIPxTextBox::setSize(float width, float height)
{
    float prevHeight = m_size.vec[1];
    Transform2::setSize(width, height);

    // Clamp text width
    if ((!Math::areEqual(m_size.vec[1], prevHeight)) || (m_text.getWidth() >=
        (m_size.vec[0] - (GUIPxTextBoxOffsetX*m_size.vec[1]*2.0f))))
    {
        m_text.setHeight(height*GUIPxTextBoxHeightFactor);
        m_cursor = 0;
        m_text.clampTextWidth(
            (m_size.vec[0] - (GUIPxTextBoxOffsetX*m_size.vec[1]*2.0f))
        );
        m_cursor = m_text.getLength();
        m_textChanged = true;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Set pixel text box size                                                   //
////////////////////////////////////////////////////////////////////////////////
void GUIPxTextBox::setSize(const Vector2& size)
{
    float prevHeight = m_size.vec[1];
    Transform2::setSize(size);

    // Clamp text width
    if ((!Math::areEqual(m_size.vec[1], prevHeight)) || (m_text.getWidth() >=
        (m_size.vec[0] - (GUIPxTextBoxOffsetX*m_size.vec[1]*2.0f))))
    {
        m_text.setHeight(size.vec[1]*GUIPxTextBoxHeightFactor);
        m_cursor = 0;
        m_text.clampTextWidth(
            (m_size.vec[0] - (GUIPxTextBoxOffsetX*m_size.vec[1]*2.0f))
        );
        m_cursor = m_text.getLength();
        m_textChanged = true;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Set pixel text box width                                                  //
////////////////////////////////////////////////////////////////////////////////
void GUIPxTextBox::setWidth(float width)
{
    Transform2::setWidth(width);

    // Clamp text width
    if (m_text.getWidth() >=
        (m_size.vec[0] - (GUIPxTextBoxOffsetX*m_size.vec[1]*2.0f)))
    {
        m_cursor = 0;
        m_text.clampTextWidth(
            (m_size.vec[0] - (GUIPxTextBoxOffsetX*m_size.vec[1]*2.0f))
        );
        m_cursor = m_text.getLength();
        m_textChanged = true;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Set pixel text box height                                                 //
////////////////////////////////////////////////////////////////////////////////
void GUIPxTextBox::setHeight(float height)
{
    float prevHeight = m_size.vec[1];
    Transform2::setHeight(height);

    // Recompute character positions
    if (!Math::areEqual(m_size.vec[1], prevHeight))
    {
        m_text.setHeight(height*GUIPxTextBoxHeightFactor);
        m_cursor = 0;
        m_text.clampTextWidth(
            (m_size.vec[0] - (GUIPxTextBoxOffsetX*m_size.vec[1]*2.0f))
        );
        m_cursor = m_text.getLength();
        m_textChanged = true;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Set pixel text box color                                                  //
////////////////////////////////////////////////////////////////////////////////
void GUIPxTextBox::setColor(const Vector4& color)
{
    m_color.vec[0] = color.vec[0];
    m_color.vec[1] = color.vec[1];
    m_color.vec[2] = color.vec[2];
    m_color.vec[3] = color.vec[3];
}

////////////////////////////////////////////////////////////////////////////////
//  Set pixel text box color                                                  //
////////////////////////////////////////////////////////////////////////////////
void GUIPxTextBox::setColor(float red, float green, float blue, float alpha)
{
    m_color.vec[0] = red;
    m_color.vec[1] = green;
    m_color.vec[2] = blue;
    m_color.vec[3] = alpha;
}

////////////////////////////////////////////////////////////////////////////////
//  Set pixel text box text                                                   //
////////////////////////////////////////////////////////////////////////////////
void GUIPxTextBox::setText(const std::string& text)
{
    m_cursor = 0;
    m_text.setTextAndClamp(
        text, (m_size.vec[0] - (GUIPxTextBoxOffsetX*m_size.vec[1]*2.0f))
    );
    m_cursor = m_text.getLength();
}


////////////////////////////////////////////////////////////////////////////////
//  Get pixel text box picking state                                          //
////////////////////////////////////////////////////////////////////////////////
bool GUIPxTextBox::isPicking(float mouseX, float mouseY)
{
    // Check if text box is picking
    if ((mouseX >= (m_position.vec[0] - m_size.vec[0]*0.5f)) &&
        (mouseX <= (m_position.vec[0] + m_size.vec[0]*0.5f)) &&
        (mouseY >= (m_position.vec[1] - m_size.vec[1]*0.5f)) &&
        (mouseY <= (m_position.vec[1] + m_size.vec[1]*0.5f)))
    {
        // Text box is picking
        return true;
    }
    return false;
}


////////////////////////////////////////////////////////////////////////////////
//  Handle pixel text box mouse move event                                    //
////////////////////////////////////////////////////////////////////////////////
bool GUIPxTextBox::mouseMove(float mouseX, float mouseY)
{
    // Disabled state
    if (m_disabled) { m_state = GUIPXTEXTBOX_NONE; return false; }

    // Compute selection
    if (m_selecting)
    {
        m_cursorTime = 0.0f;
        size_t cursor = computeCursorPosition(mouseX);
        if (cursor <= m_cursor)
        {
            m_leftSelection = cursor;
        }
        if (cursor >= m_cursor)
        {
            m_rightSelection = cursor;
        }
    }

    // Set text box state
    if (isPicking(mouseX, mouseY))
    {
        if ((m_state == GUIPXTEXTBOX_PRESSED) ||
            (m_state == GUIPXTEXTBOX_PRESSEDHOVER))
        {
            m_state = GUIPXTEXTBOX_PRESSEDHOVER;
            return true;
        }
        else
        {
            m_state = GUIPXTEXTBOX_HOVER;
        }
    }
    else
    {
        if ((m_state == GUIPXTEXTBOX_PRESSED) ||
            (m_state == GUIPXTEXTBOX_PRESSEDHOVER))
        {
            m_state = GUIPXTEXTBOX_PRESSED;
            return true;
        }
        else
        {
            m_state = GUIPXTEXTBOX_NONE;
        }
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Handle pixel text box mouse press event                                   //
////////////////////////////////////////////////////////////////////////////////
bool GUIPxTextBox::mousePress(float mouseX, float mouseY)
{
    // Disabled state
    if (m_disabled) { m_state = GUIPXTEXTBOX_NONE; return false; }

    // Set text box state
    if (isPicking(mouseX, mouseY))
    {
        m_state = GUIPXTEXTBOX_PRESSEDHOVER;
        m_active = true;
        m_cursor = computeCursorPosition(mouseX);
        m_leftSelection = m_cursor;
        m_rightSelection = m_cursor;
        m_selecting = true;
        m_cursorTime = 0.0f;
        return true;
    }
    else
    {
        m_state = GUIPXTEXTBOX_NONE;
        if (m_active)
        {
            m_textChanged = true;
            m_active = false;
        }
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Handle pixel text box mouse release event                                 //
////////////////////////////////////////////////////////////////////////////////
bool GUIPxTextBox::mouseRelease(float mouseX, float mouseY)
{
    // Disabled state
    if (m_disabled) { m_state = GUIPXTEXTBOX_NONE; return false; }

    // Set text box state
    m_selecting = false;
    if (isPicking(mouseX, mouseY))
    {
        if (m_state == GUIPXTEXTBOX_PRESSEDHOVER)
        {
            m_state = GUIPXTEXTBOX_HOVER;
            return true;
        }
        m_state = GUIPXTEXTBOX_HOVER;
    }
    else
    {
        m_state = GUIPXTEXTBOX_NONE;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Handle pixel text box shift key event                                     //
////////////////////////////////////////////////////////////////////////////////
bool GUIPxTextBox::shiftPress()
{
    m_shift = true;
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Handle pixel text box shift key release event                             //
////////////////////////////////////////////////////////////////////////////////
bool GUIPxTextBox::shiftRelease()
{
    m_shift = false;
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Handle pixel text box left key event                                      //
////////////////////////////////////////////////////////////////////////////////
bool GUIPxTextBox::leftPress()
{
    if (m_disabled) { return false; }
    if (!m_active) { return false; }
    m_cursorTime = 0.0f;

    // Extend selection to the left
    if (m_shift)
    {
        if (m_rightSelection > m_cursor)
        {
            if (m_rightSelection > 0)
            {
                --m_rightSelection;
                return true;
            }
        }
        else
        {
            if (m_leftSelection > 0)
            {
                --m_leftSelection;
                return true;
            }
        }
        return false;
    }

    // Move cursor to the left of the selection
    if (m_leftSelection < m_rightSelection)
    {
        m_cursor = m_leftSelection;
        m_rightSelection = m_cursor;
        return true;
    }

    // Move cursor backward
    if (m_cursor > 0)
    {
        --m_cursor;
        m_leftSelection = m_cursor;
        m_rightSelection = m_cursor;
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Handle pixel text box right key event                                     //
////////////////////////////////////////////////////////////////////////////////
bool GUIPxTextBox::rightPress()
{
    if (m_disabled) { return false; }
    if (!m_active) { return false; }
    m_cursorTime = 0.0f;

    // Extend selection to the right
    if (m_shift)
    {
        if (m_leftSelection < m_cursor)
        {
            if (m_leftSelection < m_text.getLength())
            {
                ++m_leftSelection;
                return true;
            }
        }
        else
        {
            if (m_rightSelection < m_text.getLength())
            {
                ++m_rightSelection;
                return true;
            }
        }
        return false;
    }

    // Move cursor to the right of the selection
    if (m_leftSelection < m_rightSelection)
    {
        m_cursor = m_rightSelection;
        m_leftSelection = m_cursor;
        return true;
    }

    // Move cursor forward
    if (m_cursor < m_text.getLength())
    {
        ++m_cursor;
        m_leftSelection = m_cursor;
        m_rightSelection = m_cursor;
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Handle pixel text box backspace key event                                 //
////////////////////////////////////////////////////////////////////////////////
bool GUIPxTextBox::backspacePress()
{
    if (m_disabled) { return false; }
    if (!m_active) { return false; }
    m_cursorTime = 0.0f;

    // Erase selection
    if (m_leftSelection < m_rightSelection)
    {
        m_text.eraseSelection(m_leftSelection, m_rightSelection);
        m_cursor = m_leftSelection;
        m_rightSelection = m_cursor;
        m_textChanged = true;
        return true;
    }

    // Erase previous character
    if ((m_text.getLength() > 0) && (m_cursor > 0))
    {
        m_text.eraseCharacter(m_cursor-1);
        --m_cursor;
        m_leftSelection = m_cursor;
        m_rightSelection = m_cursor;
        m_textChanged = true;
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Handle pixel text box delete key event                                    //
////////////////////////////////////////////////////////////////////////////////
bool GUIPxTextBox::deletePress()
{
    if (m_disabled) { return false; }
    if (!m_active) { return false; }
    m_cursorTime = 0.0f;

    // Erase selection
    if (m_leftSelection < m_rightSelection)
    {
        m_text.eraseSelection(m_leftSelection, m_rightSelection);
        m_cursor = m_leftSelection;
        m_rightSelection = m_cursor;
        m_textChanged = true;
        return true;
    }

    // Erase next character
    if ((m_text.getLength() > 0) && (m_cursor < m_text.getLength()))
    {
        m_text.eraseCharacter(m_cursor);
        m_leftSelection = m_cursor;
        m_rightSelection = m_cursor;
        m_textChanged = true;
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Handle pixel text box text entered event                                  //
////////////////////////////////////////////////////////////////////////////////
bool GUIPxTextBox::textEntered(uint32_t code)
{
    if (m_disabled) { return false; }
    if (!m_active) { return false; }
    m_cursorTime = 0.0f;

    // Erase selection
    if (m_leftSelection < m_rightSelection)
    {
        m_text.eraseSelection(m_leftSelection, m_rightSelection);
        m_cursor = m_leftSelection;
        m_rightSelection = m_cursor;
        m_textChanged = true;
    }

    // Convert code to character
    if (code >= 128) { code = 0; }
    char character = static_cast<char>(code);

    // Check next text size
    if (m_text.getNextSize(character) >=
        (m_size.vec[0] - (GUIPxTextBoxOffsetX*m_size.vec[1]*2.0f)))
    {
        return false;
    }

    // Insert new character
    m_text.insertCharacter(m_cursor, character);
    ++m_cursor;
    m_leftSelection = m_cursor;
    m_rightSelection = m_cursor;
    m_textChanged = true;
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Compute text box                                                          //
////////////////////////////////////////////////////////////////////////////////
void GUIPxTextBox::compute(float frametime)
{
    m_cursorTime = Math::modulo(m_cursorTime+frametime, 1.0f);
}

////////////////////////////////////////////////////////////////////////////////
//  Render text box                                                           //
////////////////////////////////////////////////////////////////////////////////
void GUIPxTextBox::render()
{
    // Disabled state
    if (m_disabled) { m_state = GUIPXTEXTBOX_NONE; m_active = false; }
}


////////////////////////////////////////////////////////////////////////////////
//  Compute cursor position from mouse x position                             //
////////////////////////////////////////////////////////////////////////////////
size_t GUIPxTextBox::computeCursorPosition(float mouseX)
{
    // Compute current cursor position
    size_t cursor = m_text.getLength();
    return cursor;
}
