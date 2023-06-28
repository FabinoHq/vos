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
//     Renderer/GUI/GUIProgressBar.h : GUI Progress bar management            //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_GUI_GUIPROGRESSBAR_HEADER
#define VOS_RENDERER_GUI_GUIPROGRESSBAR_HEADER

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
    //  GUIProgressBar class definition                                       //
    ////////////////////////////////////////////////////////////////////////////
    class GUIProgressBar : public Transform2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  GUIProgressBar default constructor                            //
            ////////////////////////////////////////////////////////////////////
            GUIProgressBar();

            ////////////////////////////////////////////////////////////////////
            //  GUIProgressBar virtual destructor                             //
            ////////////////////////////////////////////////////////////////////
            virtual ~GUIProgressBar();


            ////////////////////////////////////////////////////////////////////
            //  Init progress bar                                             //
            //  return : True if the progress bar is successfully created     //
            ////////////////////////////////////////////////////////////////////
            bool init(Texture& texture,
                float width, float height, float uvFactor);

            ////////////////////////////////////////////////////////////////////
            //  Set progress bar texture                                      //
            //  return : True if progress bar texture is successfully set     //
            ////////////////////////////////////////////////////////////////////
            bool setTexture(Texture& texture);

            ////////////////////////////////////////////////////////////////////
            //  Set progress bar color                                        //
            ////////////////////////////////////////////////////////////////////
            void setColor(const Vector4& color);

            ////////////////////////////////////////////////////////////////////
            //  Set progress bar color                                        //
            ////////////////////////////////////////////////////////////////////
            void setColor(float red, float green, float blue, float alpha);

            ////////////////////////////////////////////////////////////////////
            //  Set progress bar red channel                                  //
            ////////////////////////////////////////////////////////////////////
            inline void setRed(float red)
            {
                m_color.vec[0] = red;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set progress bar green channel                                //
            ////////////////////////////////////////////////////////////////////
            inline void setGreen(float green)
            {
                m_color.vec[1] = green;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set progress bar blue channel                                 //
            ////////////////////////////////////////////////////////////////////
            inline void setBlue(float blue)
            {
                m_color.vec[2] = blue;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set progress bar alpha channel                                //
            ////////////////////////////////////////////////////////////////////
            inline void setAlpha(float alpha)
            {
                m_color.vec[3] = alpha;
            }


            ////////////////////////////////////////////////////////////////////
            //  Set progress bar value                                        //
            ////////////////////////////////////////////////////////////////////
            inline void setValue(float value)
            {
                if (value <= 0.0f) { value = 0.0f; }
                if (value >= 1.0f) { value = 1.0f; }
                m_value = value;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get progress bar value                                        //
            ////////////////////////////////////////////////////////////////////
            inline float getValue()
            {
                return m_value;
            }


            ////////////////////////////////////////////////////////////////////
            //  Bind progress bar texture                                     //
            ////////////////////////////////////////////////////////////////////
            inline void bindTexture()
            {
                m_texture->bind();
            }

            ////////////////////////////////////////////////////////////////////
            //  Render progress bar                                           //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  GUIProgressBar private copy constructor : Not copyable        //
            ////////////////////////////////////////////////////////////////////
            GUIProgressBar(const GUIProgressBar&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  GUIProgressBar private copy operator : Not copyable           //
            ////////////////////////////////////////////////////////////////////
            GUIProgressBar& operator=(const GUIProgressBar&) = delete;


        private:
            Texture*        m_texture;      // ProgressBar texture pointer
            Vector4         m_color;        // ProgressBar color
            float           m_uvFactor;     // Threepatch UV factor
            float           m_value;        // ProgressBar value
    };


#endif // VOS_RENDERER_GUI_GUIPROGRESSBAR_HEADER
