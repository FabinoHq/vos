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
//     Renderer/GUI/GUIPxText.h : GUI PixelText (distance field) management   //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_GUI_GUIPXTEXT_HEADER
#define VOS_RENDERER_GUI_GUIPXTEXT_HEADER

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

    #include <cstddef>
    #include <string>


    ////////////////////////////////////////////////////////////////////////////
    //  Pixel text default settings                                           //
    ////////////////////////////////////////////////////////////////////////////
    const float PixelTextDefaultUVWidth = 0.0625f;
    const float PixelTextDefaultUVHeight = 0.125f;
    const float PixelTextDefaultXStart = 0.24f;
    const float PixelTextDefaultXOffset = 0.44f;
    const float PixelTextDefaultYOffset = 0.92f;
    const float PixelTextDefaultSmoothFactor = 0.4f;


    ////////////////////////////////////////////////////////////////////////////
    //  GUIPxText class definition                                            //
    ////////////////////////////////////////////////////////////////////////////
    class GUIPxText : public Transform2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  GUIPxText default constructor                                 //
            ////////////////////////////////////////////////////////////////////
            GUIPxText();

            ////////////////////////////////////////////////////////////////////
            //  GUIPxText virtual destructor                                  //
            ////////////////////////////////////////////////////////////////////
            virtual ~GUIPxText();


            ////////////////////////////////////////////////////////////////////
            //  Init pixel text                                               //
            //  return : True if the pixel text is successfully created       //
            ////////////////////////////////////////////////////////////////////
            bool init(Texture& texture, float height);

            ////////////////////////////////////////////////////////////////////
            //  Set pixel text texture                                        //
            //  return : True if pixel text texture is successfully set       //
            ////////////////////////////////////////////////////////////////////
            bool setTexture(Texture& texture);

            ////////////////////////////////////////////////////////////////////
            //  Set pixel text internal string                                //
            ////////////////////////////////////////////////////////////////////
            void setText(const std::string& text);

            ////////////////////////////////////////////////////////////////////
            //  Set pixel text with size clamping                             //
            ////////////////////////////////////////////////////////////////////
            void setTextAndClamp(const std::string& text, float width);

            ////////////////////////////////////////////////////////////////////
            //  Clamp current pixel text width                                //
            ////////////////////////////////////////////////////////////////////
            void clampTextWidth(float width);

            ////////////////////////////////////////////////////////////////////
            //  Clear pixel text internal string                              //
            ////////////////////////////////////////////////////////////////////
            inline void clear()
            {
                m_text = std::string();
            }

            ////////////////////////////////////////////////////////////////////
            //  Insert character into pixel text at given index               //
            ////////////////////////////////////////////////////////////////////
            void insertCharacter(size_t index, char code);

            ////////////////////////////////////////////////////////////////////
            //  Append character to pixel text                                //
            ////////////////////////////////////////////////////////////////////
            void appendCharacter(char code);

            ////////////////////////////////////////////////////////////////////
            //  Erase pixel text character at given index                     //
            ////////////////////////////////////////////////////////////////////
            void eraseCharacter(size_t index);

            ////////////////////////////////////////////////////////////////////
            //  Erase pixel text selection between given indices              //
            ////////////////////////////////////////////////////////////////////
            void eraseSelection(size_t left, size_t right);


            ////////////////////////////////////////////////////////////////////
            //  Set pixel text color                                          //
            ////////////////////////////////////////////////////////////////////
            void setColor(const Vector4& color);

            ////////////////////////////////////////////////////////////////////
            //  Set pixel text color                                          //
            ////////////////////////////////////////////////////////////////////
            void setColor(float red, float green, float blue, float alpha);

            ////////////////////////////////////////////////////////////////////
            //  Set pixel text red channel                                    //
            ////////////////////////////////////////////////////////////////////
            inline void setRed(float red)
            {
                m_color.vec[0] = red;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set pixel text green channel                                  //
            ////////////////////////////////////////////////////////////////////
            inline void setGreen(float green)
            {
                m_color.vec[1] = green;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set pixel text blue channel                                   //
            ////////////////////////////////////////////////////////////////////
            inline void setBlue(float blue)
            {
                m_color.vec[2] = blue;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set pixel text alpha channel                                  //
            ////////////////////////////////////////////////////////////////////
            inline void setAlpha(float alpha)
            {
                m_color.vec[3] = alpha;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set pixel text smooth amount                                  //
            ////////////////////////////////////////////////////////////////////
            inline void setSmooth(float smooth)
            {
                m_smooth = Math::clamp(smooth, 0.0f, 1.0f);
            }


            ////////////////////////////////////////////////////////////////////
            //  Get pixel text picking state                                  //
            ////////////////////////////////////////////////////////////////////
            bool isPicking(float mouseX, float mouseY);


            ////////////////////////////////////////////////////////////////////
            //  Get pixel text string                                         //
            ////////////////////////////////////////////////////////////////////
            inline std::string getText()
            {
                return m_text;
            }

            ////////////////////////////////////////////////////////////////////
            //  Convert pixel text string to integer                          //
            ////////////////////////////////////////////////////////////////////
            int64_t toInt();

            ////////////////////////////////////////////////////////////////////
            //  Convert pixel text string to float                            //
            ////////////////////////////////////////////////////////////////////
            float toFloat();

            ////////////////////////////////////////////////////////////////////
            //  Convert pixel text string to double                           //
            ////////////////////////////////////////////////////////////////////
            double toDouble();

            ////////////////////////////////////////////////////////////////////
            //  Get pixel text length                                         //
            ////////////////////////////////////////////////////////////////////
            inline size_t getLength() const
            {
                return m_text.length();
            }

            ////////////////////////////////////////////////////////////////////
            //  Get character at given index                                  //
            ////////////////////////////////////////////////////////////////////
            inline char getChar(size_t index)
            {
                if (index < m_text.size()) { return m_text[index]; }
                return 0;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get pixel text character position at given index              //
            ////////////////////////////////////////////////////////////////////
            float getCharPos(size_t index);

            ////////////////////////////////////////////////////////////////////
            //  Get pixel text next size after inserting a character          //
            ////////////////////////////////////////////////////////////////////
            float getNextSize(char code);

            ////////////////////////////////////////////////////////////////////
            //  Check if pixel text contains the specified char code          //
            ////////////////////////////////////////////////////////////////////
            bool contains(char code);


            ////////////////////////////////////////////////////////////////////
            //  Bind pixel text texture                                       //
            ////////////////////////////////////////////////////////////////////
            inline void bindTexture()
            {
                m_texture->bind();
            }

            ////////////////////////////////////////////////////////////////////
            //  Render pixel text                                             //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  GUIPxText private copy constructor : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            GUIPxText(const GUIPxText&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  GUIPxText private copy operator : Not copyable                //
            ////////////////////////////////////////////////////////////////////
            GUIPxText& operator=(const GUIPxText&) = delete;


        private:
            Texture*            m_texture;          // PxText texture pointer
            Vector4             m_color;            // PxText color
            float               m_smooth;           // PxText smooth amount

            std::string         m_text;             // PxText internal string
    };


#endif // VOS_RENDERER_GUI_GUIPXTEXT_HEADER
