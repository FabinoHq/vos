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
//     Renderer/GUI/GUIToggleButton.h : GUI Toggle button management          //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_GUI_GUITOGGLEBUTTON_HEADER
#define VOS_RENDERER_GUI_GUITOGGLEBUTTON_HEADER

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
    //  GUIToggleButton state enumeration                                     //
    ////////////////////////////////////////////////////////////////////////////
    enum GUIToggleButtonState
    {
        GUITOGGLEBUTTON_NONE = 0,
        GUITOGGLEBUTTON_HOVER = 1,
        GUITOGGLEBUTTON_PRESSED = 2,
        GUITOGGLEBUTTON_PRESSEDHOVER = 3
    };


    ////////////////////////////////////////////////////////////////////////////
    //  GUIToggleButton class definition                                      //
    ////////////////////////////////////////////////////////////////////////////
    class GUIToggleButton : public Transform2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  GUIToggleButton default constructor                           //
            ////////////////////////////////////////////////////////////////////
            GUIToggleButton();

            ////////////////////////////////////////////////////////////////////
            //  GUIToggleButton virtual destructor                            //
            ////////////////////////////////////////////////////////////////////
            virtual ~GUIToggleButton();


            ////////////////////////////////////////////////////////////////////
            //  Init toggle button                                            //
            //  return : True if the toggle button is successfully created    //
            ////////////////////////////////////////////////////////////////////
            bool init(Texture& texture,
                float width, float height, bool round = false);

            ////////////////////////////////////////////////////////////////////
            //  Set toggle button texture                                     //
            //  return : True if toggle button texture is successfully set    //
            ////////////////////////////////////////////////////////////////////
            bool setTexture(Texture& texture);

            ////////////////////////////////////////////////////////////////////
            //  Set toggle button color                                       //
            ////////////////////////////////////////////////////////////////////
            void setColor(const Vector4& color);

            ////////////////////////////////////////////////////////////////////
            //  Set toggle button color                                       //
            ////////////////////////////////////////////////////////////////////
            void setColor(float red, float green, float blue, float alpha);

            ////////////////////////////////////////////////////////////////////
            //  Set toggle button red channel                                 //
            ////////////////////////////////////////////////////////////////////
            inline void setRed(float red)
            {
                m_color.vec[0] = red;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set toggle button green channel                               //
            ////////////////////////////////////////////////////////////////////
            inline void setGreen(float green)
            {
                m_color.vec[1] = green;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set toggle button blue channel                                //
            ////////////////////////////////////////////////////////////////////
            inline void setBlue(float blue)
            {
                m_color.vec[2] = blue;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set toggle button alpha channel                               //
            ////////////////////////////////////////////////////////////////////
            inline void setAlpha(float alpha)
            {
                m_color.vec[3] = alpha;
            }


            ////////////////////////////////////////////////////////////////////
            //  Get toggle button picking state                               //
            ////////////////////////////////////////////////////////////////////
            bool isPicking(float mouseX, float mouseY);


            ////////////////////////////////////////////////////////////////////
            //  Handle toggle button mouse move event                         //
            ////////////////////////////////////////////////////////////////////
            bool mouseMove(float mouseX, float mouseY);

            ////////////////////////////////////////////////////////////////////
            //  Handle toggle button mouse press event                        //
            ////////////////////////////////////////////////////////////////////
            bool mousePress(float mouseX, float mouseY);

            ////////////////////////////////////////////////////////////////////
            //  Handle toggle button mouse release event                      //
            ////////////////////////////////////////////////////////////////////
            bool mouseRelease(float mouseX, float mouseY);


            ////////////////////////////////////////////////////////////////////
            //  Toggle button state                                           //
            ////////////////////////////////////////////////////////////////////
            inline bool toggle()
            {
                return (m_toggle = !m_toggle);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set toggle button state                                       //
            ////////////////////////////////////////////////////////////////////
            inline bool setToggle(bool toggle)
            {
                return (m_toggle = toggle);
            }

            ////////////////////////////////////////////////////////////////////
            //  Get toggle button state                                       //
            ////////////////////////////////////////////////////////////////////
            inline bool getToggle()
            {
                return m_toggle;
            }


            ////////////////////////////////////////////////////////////////////
            //  Bind toggle button texture                                    //
            ////////////////////////////////////////////////////////////////////
            inline void bindTexture()
            {
                m_texture->bind();
            }

            ////////////////////////////////////////////////////////////////////
            //  Render toggle button                                          //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  GUIToggleButton private copy constructor : Not copyable       //
            ////////////////////////////////////////////////////////////////////
            GUIToggleButton(const GUIToggleButton&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  GUIToggleButton private copy operator : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            GUIToggleButton& operator=(const GUIToggleButton&) = delete;


        private:
            Texture*                m_texture;  // ToggleButton texture pointer
            Vector4                 m_color;    // ToggleButton color
            bool                    m_round;    // ToggleButton round state
            GUIToggleButtonState    m_state;    // ToggleButton state
            bool                    m_toggle;   // ToggleButton toggle state
    };


#endif // VOS_RENDERER_GUI_GUITOGGLEBUTTON_HEADER
