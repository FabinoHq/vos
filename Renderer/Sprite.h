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
//     Renderer/Sprite.h : Sprite management                                  //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_SPRITE_HEADER
#define VOS_RENDERER_SPRITE_HEADER

    #include "../System/System.h"
    #include "Vulkan/Texture.h"
    #include "../Math/Math.h"
    #include "../Math/Vector2.h"
    #include "../Math/Vector4.h"
    #include "../Math/Matrix4x4.h"
    #include "../Math/Transform2.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class declaration                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer;

    ////////////////////////////////////////////////////////////////////////////
    //  BackRenderer class declaration                                        //
    ////////////////////////////////////////////////////////////////////////////
    class BackRenderer;


    ////////////////////////////////////////////////////////////////////////////
    //  Sprite class definition                                               //
    ////////////////////////////////////////////////////////////////////////////
    class Sprite : public Transform2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Sprite default constructor                                    //
            ////////////////////////////////////////////////////////////////////
            Sprite();

            ////////////////////////////////////////////////////////////////////
            //  Sprite virtual destructor                                     //
            ////////////////////////////////////////////////////////////////////
            virtual ~Sprite();


            ////////////////////////////////////////////////////////////////////
            //  Init sprite                                                   //
            //  return : True if the sprite is successfully created           //
            ////////////////////////////////////////////////////////////////////
            bool init(Texture& texture, float width, float height);

            ////////////////////////////////////////////////////////////////////
            //  Set sprite texture                                            //
            //  return : True if sprite texture is successfully set           //
            ////////////////////////////////////////////////////////////////////
            bool setTexture(Texture& texture);

            ////////////////////////////////////////////////////////////////////
            //  Set sprite color                                              //
            ////////////////////////////////////////////////////////////////////
            void setColor(const Vector4& color);

            ////////////////////////////////////////////////////////////////////
            //  Set sprite color                                              //
            ////////////////////////////////////////////////////////////////////
            void setColor(float red, float green, float blue, float alpha);

            ////////////////////////////////////////////////////////////////////
            //  Set sprite red channel                                        //
            ////////////////////////////////////////////////////////////////////
            void setRed(float red);

            ////////////////////////////////////////////////////////////////////
            //  Set sprite green channel                                      //
            ////////////////////////////////////////////////////////////////////
            void setGreen(float green);

            ////////////////////////////////////////////////////////////////////
            //  Set sprite blue channel                                       //
            ////////////////////////////////////////////////////////////////////
            void setBlue(float blue);

            ////////////////////////////////////////////////////////////////////
            //  Set sprite alpha channel                                      //
            ////////////////////////////////////////////////////////////////////
            void setAlpha(float alpha);


            ////////////////////////////////////////////////////////////////////
            //  Set sprite subrectangle                                       //
            ////////////////////////////////////////////////////////////////////
            void setSubrect(const Vector2& offset, const Vector2& size);

            ////////////////////////////////////////////////////////////////////
            //  Set sprite subrectangle                                       //
            ////////////////////////////////////////////////////////////////////
            void setSubrect(
                float uOffset, float vOffset, float uSize, float vSize);

            ////////////////////////////////////////////////////////////////////
            //  Set sprite UV offset                                          //
            ////////////////////////////////////////////////////////////////////
            void setUVOffset(const Vector2& offset);

            ////////////////////////////////////////////////////////////////////
            //  Set sprite UV offset                                          //
            ////////////////////////////////////////////////////////////////////
            void setUVOffset(float uOffset, float vOffset);

            ////////////////////////////////////////////////////////////////////
            //  Set sprite U offset                                           //
            ////////////////////////////////////////////////////////////////////
            void setUOffset(float uOffset);

            ////////////////////////////////////////////////////////////////////
            //  Set sprite V offset                                           //
            ////////////////////////////////////////////////////////////////////
            void setVOffset(float vOffset);

            ////////////////////////////////////////////////////////////////////
            //  Set sprite UV size                                            //
            ////////////////////////////////////////////////////////////////////
            void setUVSize(const Vector2& size);

            ////////////////////////////////////////////////////////////////////
            //  Set sprite UV size                                            //
            ////////////////////////////////////////////////////////////////////
            void setUVSize(float uSize, float vSize);

            ////////////////////////////////////////////////////////////////////
            //  Set sprite U size                                             //
            ////////////////////////////////////////////////////////////////////
            void setUSize(float uSize);

            ////////////////////////////////////////////////////////////////////
            //  Set sprite V size                                             //
            ////////////////////////////////////////////////////////////////////
            void setVSize(float vSize);


            ////////////////////////////////////////////////////////////////////
            //  Render sprite                                                 //
            ////////////////////////////////////////////////////////////////////
            void render(Renderer& renderer);

            ////////////////////////////////////////////////////////////////////
            //  Render sprite                                                 //
            ////////////////////////////////////////////////////////////////////
            void render(BackRenderer& backRenderer);


        private:
            ////////////////////////////////////////////////////////////////////
            //  Sprite private copy constructor : Not copyable                //
            ////////////////////////////////////////////////////////////////////
            Sprite(const Sprite&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Sprite private copy operator : Not copyable                   //
            ////////////////////////////////////////////////////////////////////
            Sprite& operator=(const Sprite&) = delete;


        private:
            Texture*            m_texture;          // Sprite texture pointer
            Vector4             m_color;            // Sprite color
            Vector2             m_uvOffset;         // Sprite UV offset
            Vector2             m_uvSize;           // Sprite UV size
    };


#endif // VOS_RENDERER_SPRITE_HEADER
