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
//     Renderer/GUI/GUISlider.h : GUI Slider management                       //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_GUI_GUISLIDER_HEADER
#define VOS_RENDERER_GUI_GUISLIDER_HEADER

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
    //  GUISlider default increments                                          //
    ////////////////////////////////////////////////////////////////////////////
    const float GUISliderDefaultIncrements = 0.02f;
    const float GUISliderControlIncrements = 0.002f;


    ////////////////////////////////////////////////////////////////////////////
    //  GUISlider state enumeration                                           //
    ////////////////////////////////////////////////////////////////////////////
    enum GUISliderState
    {
        GUISLIDER_NONE = 0,
        GUISLIDER_HOVER = 1,
        GUISLIDER_PRESSED = 2,
        GUISLIDER_PRESSEDHOVER = 3
    };


    ////////////////////////////////////////////////////////////////////////////
    //  GUISlider class definition                                            //
    ////////////////////////////////////////////////////////////////////////////
    class GUISlider : public Transform2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  GUISlider default constructor                                 //
            ////////////////////////////////////////////////////////////////////
            GUISlider();

            ////////////////////////////////////////////////////////////////////
            //  GUISlider virtual destructor                                  //
            ////////////////////////////////////////////////////////////////////
            virtual ~GUISlider();


            ////////////////////////////////////////////////////////////////////
            //  Init slider                                                   //
            //  return : True if the slider is successfully created           //
            ////////////////////////////////////////////////////////////////////
            bool init(Texture& texture, float width, float height,
                float uvFactor, bool vertical = false);

            ////////////////////////////////////////////////////////////////////
            //  Set slider texture                                            //
            //  return : True if slider texture is successfully set           //
            ////////////////////////////////////////////////////////////////////
            bool setTexture(Texture& texture);

            ////////////////////////////////////////////////////////////////////
            //  Set slider color                                              //
            ////////////////////////////////////////////////////////////////////
            void setColor(const Vector4& color);

            ////////////////////////////////////////////////////////////////////
            //  Set slider color                                              //
            ////////////////////////////////////////////////////////////////////
            void setColor(float red, float green, float blue, float alpha);

            ////////////////////////////////////////////////////////////////////
            //  Set slider red channel                                        //
            ////////////////////////////////////////////////////////////////////
            inline void setRed(float red)
            {
                m_color.vec[0] = red;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set slider green channel                                      //
            ////////////////////////////////////////////////////////////////////
            inline void setGreen(float green)
            {
                m_color.vec[1] = green;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set slider blue channel                                       //
            ////////////////////////////////////////////////////////////////////
            inline void setBlue(float blue)
            {
                m_color.vec[2] = blue;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set slider alpha channel                                      //
            ////////////////////////////////////////////////////////////////////
            inline void setAlpha(float alpha)
            {
                m_color.vec[3] = alpha;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set slider increments                                         //
            ////////////////////////////////////////////////////////////////////
            inline void setIncrements(float increments)
            {
                m_increments = Math::clamp(increments, 0.0f, 1.0f);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set slider control increments                                 //
            ////////////////////////////////////////////////////////////////////
            inline void setCtrlIncrements(float ctrlIncrements)
            {
                m_ctrlIncrements = Math::clamp(ctrlIncrements, 0.0f, 1.0f);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set slider vertical state                                     //
            ////////////////////////////////////////////////////////////////////
            inline void setVertical(bool vertical)
            {
                m_vertical = vertical;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set slider value changed                                      //
            ////////////////////////////////////////////////////////////////////
            inline void setValueChanged()
            {
                m_valueChanged = true;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set slider disabled state                                     //
            ////////////////////////////////////////////////////////////////////
            inline void setDisabled(bool disabled)
            {
                m_disabled = disabled;
            }

            ////////////////////////////////////////////////////////////////////
            //  Reset slider state                                            //
            ////////////////////////////////////////////////////////////////////
            inline void resetState()
            {
                m_state = GUISLIDER_NONE;
            }


            ////////////////////////////////////////////////////////////////////
            //  Get slider picking state                                      //
            ////////////////////////////////////////////////////////////////////
            bool isPicking(float mouseX, float mouseY);

            ////////////////////////////////////////////////////////////////////
            //  Get slider disabled state                                     //
            ////////////////////////////////////////////////////////////////////
            inline bool isDisabled()
            {
                return m_disabled;
            }


            ////////////////////////////////////////////////////////////////////
            //  Handle slider mouse move event                                //
            ////////////////////////////////////////////////////////////////////
            bool mouseMove(float mouseX, float mouseY);

            ////////////////////////////////////////////////////////////////////
            //  Handle slider mouse press event                               //
            ////////////////////////////////////////////////////////////////////
            bool mousePress(float mouseX, float mouseY);

            ////////////////////////////////////////////////////////////////////
            //  Handle slider mouse release event                             //
            ////////////////////////////////////////////////////////////////////
            bool mouseRelease(float mouseX, float mouseY);

            ////////////////////////////////////////////////////////////////////
            //  Handle slider mouse wheel event                               //
            ////////////////////////////////////////////////////////////////////
            void mouseWheel(int mouseWheel);

            ////////////////////////////////////////////////////////////////////
            //  Handle slider control key event                               //
            ////////////////////////////////////////////////////////////////////
            inline void controlPress(bool control)
            {
                m_control = control;
            }

            ////////////////////////////////////////////////////////////////////
            //  Increment slider value                                        //
            ////////////////////////////////////////////////////////////////////
            void increment();

            ////////////////////////////////////////////////////////////////////
            //  Decrement slider value                                        //
            ////////////////////////////////////////////////////////////////////
            void decrement();


            ////////////////////////////////////////////////////////////////////
            //  Set slider value                                              //
            ////////////////////////////////////////////////////////////////////
            inline void setValue(float value)
            {
                m_value = Math::clamp(value, 0.0f, 1.0f);
            }

            ////////////////////////////////////////////////////////////////////
            //  Get slider value                                              //
            ////////////////////////////////////////////////////////////////////
            inline float getValue()
            {
                return m_value;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get slider value changed state                                //
            ////////////////////////////////////////////////////////////////////
            inline bool valueChanged()
            {
                if (m_valueChanged) { m_valueChanged = false; return true; }
                return false;
            }


            ////////////////////////////////////////////////////////////////////
            //  Bind slider texture                                           //
            ////////////////////////////////////////////////////////////////////
            inline void bindTexture()
            {
                m_texture->bind();
            }

            ////////////////////////////////////////////////////////////////////
            //  Render slider                                                 //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Compute slider value from mouse position                      //
            ////////////////////////////////////////////////////////////////////
            void computeSliderValue(float mouseX, float mouseY);


        private:
            ////////////////////////////////////////////////////////////////////
            //  GUISlider private copy constructor : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            GUISlider(const GUISlider&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  GUISlider private copy operator : Not copyable                //
            ////////////////////////////////////////////////////////////////////
            GUISlider& operator=(const GUISlider&) = delete;


        private:
            Texture*            m_texture;          // Slider texture pointer
            Vector4             m_color;            // Slider color
            float               m_uvFactor;         // Threepatch UV factor
            float               m_increments;       // Slider increments
            float               m_ctrlIncrements;   // Slider control increments
            float               m_value;            // Slider value
            bool                m_vertical;         // Slider vertical state
            bool                m_control;          // Control state
            bool                m_valueChanged;     // Slider value changed
            bool                m_disabled;         // Slider disabled state
            GUISliderState      m_state;            // Slider state
    };


#endif // VOS_RENDERER_GUI_GUISLIDER_HEADER
