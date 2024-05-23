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
//     Renderer/GUI/GUIButton.h : GUI Button management                       //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_GUI_GUIBUTTON_HEADER
#define VOS_RENDERER_GUI_GUIBUTTON_HEADER

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
    //  GUIButton state enumeration                                           //
    ////////////////////////////////////////////////////////////////////////////
    enum GUIButtonState
    {
        GUIBUTTON_NONE = 0,
        GUIBUTTON_HOVER = 1,
        GUIBUTTON_PRESSED = 2,
        GUIBUTTON_PRESSEDHOVER = 3
    };


    ////////////////////////////////////////////////////////////////////////////
    //  GUIButton class definition                                            //
    ////////////////////////////////////////////////////////////////////////////
    class GUIButton : public Transform2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  GUIButton default constructor                                 //
            ////////////////////////////////////////////////////////////////////
            GUIButton();

            ////////////////////////////////////////////////////////////////////
            //  GUIButton virtual destructor                                  //
            ////////////////////////////////////////////////////////////////////
            virtual ~GUIButton();


            ////////////////////////////////////////////////////////////////////
            //  Init button                                                   //
            //  return : True if the button is successfully created           //
            ////////////////////////////////////////////////////////////////////
            bool init(Texture& texture,
                float width, float height, bool round = false);

            ////////////////////////////////////////////////////////////////////
            //  Set button texture                                            //
            //  return : True if button texture is successfully set           //
            ////////////////////////////////////////////////////////////////////
            bool setTexture(Texture& texture);

            ////////////////////////////////////////////////////////////////////
            //  Set button color                                              //
            ////////////////////////////////////////////////////////////////////
            void setColor(const Vector4& color);

            ////////////////////////////////////////////////////////////////////
            //  Set button color                                              //
            ////////////////////////////////////////////////////////////////////
            void setColor(float red, float green, float blue, float alpha);

            ////////////////////////////////////////////////////////////////////
            //  Set button red channel                                        //
            ////////////////////////////////////////////////////////////////////
            inline void setRed(float red)
            {
                m_color.vec[0] = red;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set button green channel                                      //
            ////////////////////////////////////////////////////////////////////
            inline void setGreen(float green)
            {
                m_color.vec[1] = green;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set button blue channel                                       //
            ////////////////////////////////////////////////////////////////////
            inline void setBlue(float blue)
            {
                m_color.vec[2] = blue;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set button alpha channel                                      //
            ////////////////////////////////////////////////////////////////////
            inline void setAlpha(float alpha)
            {
                m_color.vec[3] = alpha;
            }


            ////////////////////////////////////////////////////////////////////
            //  Get button picking state                                      //
            ////////////////////////////////////////////////////////////////////
            bool isPicking(float mouseX, float mouseY);


            ////////////////////////////////////////////////////////////////////
            //  Handle button mouse move event                                //
            ////////////////////////////////////////////////////////////////////
            bool mouseMove(float mouseX, float mouseY);

            ////////////////////////////////////////////////////////////////////
            //  Handle button mouse press event                               //
            ////////////////////////////////////////////////////////////////////
            bool mousePress(float mouseX, float mouseY);

            ////////////////////////////////////////////////////////////////////
            //  Handle button mouse release event                             //
            ////////////////////////////////////////////////////////////////////
            bool mouseRelease(float mouseX, float mouseY);


            ////////////////////////////////////////////////////////////////////
            //  Bind button texture                                           //
            ////////////////////////////////////////////////////////////////////
            inline void bindTexture()
            {
                m_texture->bind();
            }

            ////////////////////////////////////////////////////////////////////
            //  Render button                                                 //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  GUIButton private copy constructor : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            GUIButton(const GUIButton&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  GUIButton private copy operator : Not copyable                //
            ////////////////////////////////////////////////////////////////////
            GUIButton& operator=(const GUIButton&) = delete;


        private:
            Texture*            m_texture;          // Button texture pointer
            Vector4             m_color;            // Button color
            bool                m_round;            // Button round state
            GUIButtonState      m_state;            // Button state
    };


#endif // VOS_RENDERER_GUI_GUIBUTTON_HEADER
