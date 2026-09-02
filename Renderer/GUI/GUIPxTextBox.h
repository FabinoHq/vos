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
//     Renderer/GUI/GUIPxTextBox.h : GUI Pixel text box management            //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_GUI_GUIPXTEXTBOX_HEADER
#define VOS_RENDERER_GUI_GUIPXTEXTBOX_HEADER

    #include "../../System/System.h"

    #include "../Vulkan/Vulkan.h"
    #include "../Vulkan/Swapchain.h"
    #include "../Vulkan/GraphicsLayout.h"
    #include "../Vulkan/Texture.h"

    #include "../../Math/Math.h"
    #include "../../Math/Vector2.h"
    #include "../../Math/Vector4.h"
    #include "../../Math/Matrix4x4.h"
    #include "../../Math/Transform2.h"

    #include "GUIPxText.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  GUIPxTextBox default settings                                         //
    ////////////////////////////////////////////////////////////////////////////
    const float GUIPxTextBoxHeightFactor = 0.8f;
    const float GUIPxTextBoxOffsetY = ((1.0f-GUIPxTextBoxHeightFactor)*0.5f);
    const float GUIPxTextBoxOffsetX = 0.14f;
    const float GUIPxTextBoxSelectSizeOffset = 0.064f;


    ////////////////////////////////////////////////////////////////////////////
    //  GUIPxTextBox state enumeration                                        //
    ////////////////////////////////////////////////////////////////////////////
    enum GUIPxTextBoxState
    {
        GUIPXTEXTBOX_NONE = 0,
        GUIPXTEXTBOX_HOVER = 1,
        GUIPXTEXTBOX_PRESSED = 2,
        GUIPXTEXTBOX_PRESSEDHOVER = 3
    };


    ////////////////////////////////////////////////////////////////////////////
    //  GUIPxTextBox class definition                                         //
    ////////////////////////////////////////////////////////////////////////////
    class GUIPxTextBox : public Transform2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  GUIPxTextBox default constructor                              //
            ////////////////////////////////////////////////////////////////////
            GUIPxTextBox();

            ////////////////////////////////////////////////////////////////////
            //  GUIPxTextBox virtual destructor                               //
            ////////////////////////////////////////////////////////////////////
            virtual ~GUIPxTextBox();


            ////////////////////////////////////////////////////////////////////
            //  Init pixel text box                                           //
            //  return : True if the pixel text box is successfully created   //
            ////////////////////////////////////////////////////////////////////
            bool init(Texture& texture, Texture& pixelFont,
                float width, float height, float uvFactor);

            ////////////////////////////////////////////////////////////////////
            //  Set pixel text box texture                                    //
            //  return : True if pixel text box texture is successfully set   //
            ////////////////////////////////////////////////////////////////////
            bool setTexture(Texture& texture);

            ////////////////////////////////////////////////////////////////////
            //  Set pixel text box pixel font                                 //
            //  return : True if pixel text box pixel font is set             //
            ////////////////////////////////////////////////////////////////////
            bool setPixelFont(Texture& pixelFont);

            ////////////////////////////////////////////////////////////////////
            //  Set pixel text box size                                       //
            ////////////////////////////////////////////////////////////////////
            void setSize(float width, float height);

            ////////////////////////////////////////////////////////////////////
            //  Set pixel text box size                                       //
            ////////////////////////////////////////////////////////////////////
            void setSize(const Vector2& size);

            ////////////////////////////////////////////////////////////////////
            //  Set pixel text box width                                      //
            ////////////////////////////////////////////////////////////////////
            void setWidth(float width);

            ////////////////////////////////////////////////////////////////////
            //  Set pixel text box height                                     //
            ////////////////////////////////////////////////////////////////////
            void setHeight(float height);

            ////////////////////////////////////////////////////////////////////
            //  Set pixel text box color                                      //
            ////////////////////////////////////////////////////////////////////
            void setColor(const Vector4& color);

            ////////////////////////////////////////////////////////////////////
            //  Set pixel text box color                                      //
            ////////////////////////////////////////////////////////////////////
            void setColor(float red, float green, float blue, float alpha);

            ////////////////////////////////////////////////////////////////////
            //  Set pixel text box red channel                                //
            ////////////////////////////////////////////////////////////////////
            inline void setRed(float red)
            {
                m_color.vec[0] = red;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set pixel text box green channel                              //
            ////////////////////////////////////////////////////////////////////
            inline void setGreen(float green)
            {
                m_color.vec[1] = green;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set pixel text box blue channel                               //
            ////////////////////////////////////////////////////////////////////
            inline void setBlue(float blue)
            {
                m_color.vec[2] = blue;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set pixel text box alpha channel                              //
            ////////////////////////////////////////////////////////////////////
            inline void setAlpha(float alpha)
            {
                m_color.vec[3] = alpha;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set pixel text box text                                       //
            ////////////////////////////////////////////////////////////////////
            void setText(const std::string& text);

            ////////////////////////////////////////////////////////////////////
            //  Set pixel text box text changed                               //
            ////////////////////////////////////////////////////////////////////
            inline void setTextChanged()
            {
                m_textChanged = true;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set pixel text box disabled state                             //
            ////////////////////////////////////////////////////////////////////
            inline void setDisabled(bool disabled)
            {
                m_disabled = disabled;
            }

            ////////////////////////////////////////////////////////////////////
            //  Reset pixel text box state                                    //
            ////////////////////////////////////////////////////////////////////
            inline void resetState()
            {
                m_state = GUIPXTEXTBOX_NONE;
            }


            ////////////////////////////////////////////////////////////////////
            //  Get pixel text box picking state                              //
            ////////////////////////////////////////////////////////////////////
            bool isPicking(float mouseX, float mouseY);

            ////////////////////////////////////////////////////////////////////
            //  Get pixel text box disabled state                             //
            ////////////////////////////////////////////////////////////////////
            inline bool isDisabled()
            {
                return m_disabled;
            }


            ////////////////////////////////////////////////////////////////////
            //  Handle pixel text box mouse move event                        //
            ////////////////////////////////////////////////////////////////////
            bool mouseMove(float mouseX, float mouseY);

            ////////////////////////////////////////////////////////////////////
            //  Handle pixel text box mouse press event                       //
            ////////////////////////////////////////////////////////////////////
            bool mousePress(float mouseX, float mouseY);

            ////////////////////////////////////////////////////////////////////
            //  Handle pixel text box mouse release event                     //
            ////////////////////////////////////////////////////////////////////
            bool mouseRelease(float mouseX, float mouseY);

            ////////////////////////////////////////////////////////////////////
            //  Handle pixel text box shift key press event                   //
            ////////////////////////////////////////////////////////////////////
            bool shiftPress();

            ////////////////////////////////////////////////////////////////////
            //  Handle pixel text box shift key release event                 //
            ////////////////////////////////////////////////////////////////////
            bool shiftRelease();

            ////////////////////////////////////////////////////////////////////
            //  Handle pixel text box left key event                          //
            ////////////////////////////////////////////////////////////////////
            bool leftPress();

            ////////////////////////////////////////////////////////////////////
            //  Handle pixel text box right key event                         //
            ////////////////////////////////////////////////////////////////////
            bool rightPress();

            ////////////////////////////////////////////////////////////////////
            //  Handle pixel text box backspace key event                     //
            ////////////////////////////////////////////////////////////////////
            bool backspacePress();

            ////////////////////////////////////////////////////////////////////
            //  Handle pixel text box delete key event                        //
            ////////////////////////////////////////////////////////////////////
            bool deletePress();

            ////////////////////////////////////////////////////////////////////
            //  Handle pixel text box text entered event                      //
            ////////////////////////////////////////////////////////////////////
            bool textEntered(uint32_t code);


            ////////////////////////////////////////////////////////////////////
            //  Get pixel text box text                                       //
            ////////////////////////////////////////////////////////////////////
            inline std::string getText()
            {
                return m_text.getText();
            }

            ////////////////////////////////////////////////////////////////////
            //  Get pixel text box text length                                //
            ////////////////////////////////////////////////////////////////////
            inline size_t getLength()
            {
                return m_text.getLength();
            }

            ////////////////////////////////////////////////////////////////////
            //  Get pixel text box character at given index                   //
            ////////////////////////////////////////////////////////////////////
            inline char getChar(size_t index)
            {
                return m_text.getChar(index);
            }

            ////////////////////////////////////////////////////////////////////
            //  Get pixel text box character position at given index          //
            ////////////////////////////////////////////////////////////////////
            inline float getCharPos(size_t index)
            {
                return m_text.getCharPos(index);
            }

            ////////////////////////////////////////////////////////////////////
            //  Get pixel text box text changed state                         //
            ////////////////////////////////////////////////////////////////////
            inline bool textChanged()
            {
                if (m_textChanged) { m_textChanged = false; return true; }
                return false;
            }


            ////////////////////////////////////////////////////////////////////
            //  Compute pixel text box                                        //
            ////////////////////////////////////////////////////////////////////
            void compute(float frametime);

            ////////////////////////////////////////////////////////////////////
            //  Render pixel text box                                         //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Compute cursor position from mouse x position                 //
            ////////////////////////////////////////////////////////////////////
            size_t computeCursorPosition(float mouseX);


        private:
            ////////////////////////////////////////////////////////////////////
            //  GUIPxTextBox private copy constructor : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            GUIPxTextBox(const GUIPxTextBox&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  GUIPxTextBox private copy operator : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            GUIPxTextBox& operator=(const GUIPxTextBox&) = delete;


        private:
            Texture*            m_texture;          // PxTextBox texture pointer
            Vector4             m_color;            // PxTextBox color
            float               m_uvFactor;         // Threepatch UV factor
            GUIPxText           m_text;             // PxTextBox text
            size_t              m_cursor;           // PxTextBox cursor position
            float               m_cursorTime;       // PxTextBox cursor time
            size_t              m_leftSelection;    // PxTextBox left selection
            size_t              m_rightSelection;   // PxTextBox right selection
            bool                m_shift;            // PxTextBox shift state
            bool                m_selecting;        // PxTextBox selecting state
            bool                m_active;           // PxTextBox active state
            bool                m_textChanged;      // PxTextBox text changed
            bool                m_disabled;         // PxTextBox disabled state
            GUIPxTextBoxState   m_state;            // PxTextBox state
    };


#endif // VOS_RENDERER_GUI_GUIPXTEXTBOX_HEADER
