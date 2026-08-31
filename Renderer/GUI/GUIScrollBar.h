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
//     Renderer/GUI/GUIScrollBar.h : GUI Scroll bar management                //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_GUI_GUISCROLLBAR_HEADER
#define VOS_RENDERER_GUI_GUISCROLLBAR_HEADER

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


    ////////////////////////////////////////////////////////////////////////////
    //  GUIScrollBar default settings                                         //
    ////////////////////////////////////////////////////////////////////////////
    const float GUIScrollBarDefaultIncrements = 0.1f;
    const float GUIScrollBarControlIncrements = 0.01f;
    const float GUIScrollBarMinScrollSize = 0.02f;
    const float GUIScrollBarMaxScrollSize = 1.0f;


    ////////////////////////////////////////////////////////////////////////////
    //  GUIScrollBar state enumeration                                        //
    ////////////////////////////////////////////////////////////////////////////
    enum GUIScrollBarState
    {
        GUISCROLLBAR_NONE = 0,
        GUISCROLLBAR_HOVER = 1,
        GUISCROLLBAR_PRESSED = 2,
        GUISCROLLBAR_PRESSEDHOVER = 3
    };


    ////////////////////////////////////////////////////////////////////////////
    //  GUIScrollBar class definition                                         //
    ////////////////////////////////////////////////////////////////////////////
    class GUIScrollBar : public Transform2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  GUIScrollBar default constructor                              //
            ////////////////////////////////////////////////////////////////////
            GUIScrollBar();

            ////////////////////////////////////////////////////////////////////
            //  GUIScrollBar virtual destructor                               //
            ////////////////////////////////////////////////////////////////////
            virtual ~GUIScrollBar();


            ////////////////////////////////////////////////////////////////////
            //  Init scroll bar                                               //
            //  return : True if the scroll bar is successfully created       //
            ////////////////////////////////////////////////////////////////////
            bool init(Texture& texture, float width, float height,
                float uvFactor, bool vertical = false);

            ////////////////////////////////////////////////////////////////////
            //  Set scroll bar texture                                        //
            //  return : True if scroll bar texture is successfully set       //
            ////////////////////////////////////////////////////////////////////
            bool setTexture(Texture& texture);

            ////////////////////////////////////////////////////////////////////
            //  Set scroll bar color                                          //
            ////////////////////////////////////////////////////////////////////
            void setColor(const Vector4& color);

            ////////////////////////////////////////////////////////////////////
            //  Set scroll bar color                                          //
            ////////////////////////////////////////////////////////////////////
            void setColor(float red, float green, float blue, float alpha);

            ////////////////////////////////////////////////////////////////////
            //  Set scroll bar red channel                                    //
            ////////////////////////////////////////////////////////////////////
            inline void setRed(float red)
            {
                m_color.vec[0] = red;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set scroll bar green channel                                  //
            ////////////////////////////////////////////////////////////////////
            inline void setGreen(float green)
            {
                m_color.vec[1] = green;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set scroll bar blue channel                                   //
            ////////////////////////////////////////////////////////////////////
            inline void setBlue(float blue)
            {
                m_color.vec[2] = blue;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set scroll bar alpha channel                                  //
            ////////////////////////////////////////////////////////////////////
            inline void setAlpha(float alpha)
            {
                m_color.vec[3] = alpha;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set scroll bar increments                                     //
            ////////////////////////////////////////////////////////////////////
            inline void setIncrements(float increments)
            {
                m_increments = Math::clamp(increments, 0.0f, 1.0f);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set scroll bar control increments                             //
            ////////////////////////////////////////////////////////////////////
            inline void setCtrlIncrements(float ctrlIncrements)
            {
                m_ctrlIncrements = Math::clamp(ctrlIncrements, 0.0f, 1.0f);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set scroll bar vertical state                                 //
            ////////////////////////////////////////////////////////////////////
            inline void setVertical(bool vertical)
            {
                m_vertical = vertical;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set scroll bar value changed                                  //
            ////////////////////////////////////////////////////////////////////
            inline void setValueChanged()
            {
                m_valueChanged = true;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set scroll bar disabled state                                 //
            ////////////////////////////////////////////////////////////////////
            inline void setDisabled(bool disabled)
            {
                m_disabled = disabled;
            }

            ////////////////////////////////////////////////////////////////////
            //  Reset scroll bar state                                        //
            ////////////////////////////////////////////////////////////////////
            inline void resetState()
            {
                m_state = GUISCROLLBAR_NONE;
            }


            ////////////////////////////////////////////////////////////////////
            //  Get scroll bar picking state                                  //
            ////////////////////////////////////////////////////////////////////
            bool isPicking(float mouseX, float mouseY);

            ////////////////////////////////////////////////////////////////////
            //  Get scroll bar disabled state                                 //
            ////////////////////////////////////////////////////////////////////
            inline bool isDisabled()
            {
                return m_disabled;
            }


            ////////////////////////////////////////////////////////////////////
            //  Handle scroll bar mouse move event                            //
            ////////////////////////////////////////////////////////////////////
            bool mouseMove(float mouseX, float mouseY);

            ////////////////////////////////////////////////////////////////////
            //  Handle scroll bar mouse press event                           //
            ////////////////////////////////////////////////////////////////////
            bool mousePress(float mouseX, float mouseY);

            ////////////////////////////////////////////////////////////////////
            //  Handle scroll bar mouse release event                         //
            ////////////////////////////////////////////////////////////////////
            bool mouseRelease(float mouseX, float mouseY);

            ////////////////////////////////////////////////////////////////////
            //  Handle scroll bar mouse wheel event                           //
            ////////////////////////////////////////////////////////////////////
            void mouseWheel(int mouseWheel);

            ////////////////////////////////////////////////////////////////////
            //  Handle scroll bar window mouse wheel event                    //
            ////////////////////////////////////////////////////////////////////
            void windowMouseWheel(int mouseWheel);

            ////////////////////////////////////////////////////////////////////
            //  Handle scroll bar control key event                           //
            ////////////////////////////////////////////////////////////////////
            inline void controlPress(bool control)
            {
                m_control = control;
            }

            ////////////////////////////////////////////////////////////////////
            //  Increment scroll bar value                                    //
            ////////////////////////////////////////////////////////////////////
            inline void increment()
            {
                if (m_disabled) { return; }
                m_value = Math::clamp(
                    m_value+((m_control?m_ctrlIncrements:m_increments)*
                    m_scrollSize), 0.0f, 1.0f
                );
                m_valueChanged = true;
            }

            ////////////////////////////////////////////////////////////////////
            //  Decrement scroll bar value                                    //
            ////////////////////////////////////////////////////////////////////
            inline void decrement()
            {
                if (m_disabled) { return; }
                m_value = Math::clamp(
                    m_value-((m_control?m_ctrlIncrements:m_increments)*
                    m_scrollSize), 0.0f, 1.0f
                );
                m_valueChanged = true;
            }


            ////////////////////////////////////////////////////////////////////
            //  Set scroll bar size                                           //
            ////////////////////////////////////////////////////////////////////
            inline void setScrollSize(float scrollSize)
            {
                m_scrollSize = Math::clamp(scrollSize,
                    GUIScrollBarMinScrollSize, GUIScrollBarMaxScrollSize
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Set scroll bar value                                          //
            ////////////////////////////////////////////////////////////////////
            inline void setValue(float value)
            {
                m_value = Math::clamp(value, 0.0f, 1.0f);
            }

            ////////////////////////////////////////////////////////////////////
            //  Get scroll bar size                                           //
            ////////////////////////////////////////////////////////////////////
            inline float getScrollSize()
            {
                return m_scrollSize;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get scroll bar value                                          //
            ////////////////////////////////////////////////////////////////////
            inline float getValue()
            {
                return m_value;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get scroll bar value changed state                            //
            ////////////////////////////////////////////////////////////////////
            inline bool valueChanged()
            {
                if (m_valueChanged) { m_valueChanged = false; return true; }
                return false;
            }


            ////////////////////////////////////////////////////////////////////
            //  Bind scroll bar texture                                       //
            ////////////////////////////////////////////////////////////////////
            inline void bindTexture()
            {
                m_texture->bind();
            }

            ////////////////////////////////////////////////////////////////////
            //  Render scroll bar                                             //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Compute scroll bar value from mouse position                  //
            ////////////////////////////////////////////////////////////////////
            void computeScrollBarValue(float mouseX, float mouseY);


        private:
            ////////////////////////////////////////////////////////////////////
            //  GUIScrollBar private copy constructor : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            GUIScrollBar(const GUIScrollBar&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  GUIScrollBar private copy operator : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            GUIScrollBar& operator=(const GUIScrollBar&) = delete;


        private:
            Texture*            m_texture;          // ScrollBar texture pointer
            Vector4             m_color;            // ScrollBar color
            float               m_uvFactor;         // Threepatch UV factor
            float               m_increments;       // ScrollBar increments
            float               m_ctrlIncrements;   // Control increments
            float               m_scrollSize;       // ScrollBar size
            float               m_value;            // ScrollBar value
            bool                m_vertical;         // ScrollBar vertical state
            bool                m_control;          // Control state
            bool                m_valueChanged;     // ScrollBar value changed
            bool                m_disabled;         // ScrollBar disabled state
            GUIScrollBarState   m_state;            // ScrollBar state
    };


#endif // VOS_RENDERER_GUI_GUISCROLLBAR_HEADER
