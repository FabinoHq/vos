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
