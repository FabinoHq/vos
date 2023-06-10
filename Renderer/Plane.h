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
//     Renderer/Plane.h : Plane management                                    //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_PLANE_HEADER
#define VOS_RENDERER_PLANE_HEADER

    #include "../System/System.h"
    #include "Vulkan/Vulkan.h"
    #include "Vulkan/Swapchain.h"
    #include "Vulkan/GraphicsLayout.h"
    #include "Vulkan/Texture.h"
    #include "../Math/Math.h"
    #include "../Math/Vector2.h"
    #include "../Math/Vector4.h"
    #include "../Math/Matrix4x4.h"
    #include "../Math/Transform3.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  Plane vertex buffer vertices                                          //
    ////////////////////////////////////////////////////////////////////////////
    const uint32_t PlaneVerticesCount = 32;
    const float PlaneVertices[PlaneVerticesCount] =
    {
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
    };

    ////////////////////////////////////////////////////////////////////////////
    //  Plane vertex buffer indices                                           //
    ////////////////////////////////////////////////////////////////////////////
    const uint32_t PlaneIndicesCount = 6;
    const uint16_t PlaneIndices[PlaneIndicesCount] =
    {
        0, 1, 2,
        2, 3, 0,
    };


    ////////////////////////////////////////////////////////////////////////////
    //  Plane class definition                                                //
    ////////////////////////////////////////////////////////////////////////////
    enum PlaneBillboardMode
    {
        PLANE_BILLBOARD_NONE = 0,
        PLANE_BILLBOARD_CYLINDRICAL_Y = 1,
        PLANE_BILLBOARD_CYLINDRICAL_X = 2,
        PLANE_BILLBOARD_SPHERICAL = 3
    };


    ////////////////////////////////////////////////////////////////////////////
    //  Plane class definition                                                //
    ////////////////////////////////////////////////////////////////////////////
    class Plane : public Transform3
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Plane default constructor                                     //
            ////////////////////////////////////////////////////////////////////
            Plane();

            ////////////////////////////////////////////////////////////////////
            //  Plane virtual destructor                                      //
            ////////////////////////////////////////////////////////////////////
            virtual ~Plane();


            ////////////////////////////////////////////////////////////////////
            //  Init plane                                                    //
            //  return : True if the plane is successfully created            //
            ////////////////////////////////////////////////////////////////////
            bool init(Texture& texture, float width, float height);

            ////////////////////////////////////////////////////////////////////
            //  Set plane texture                                             //
            //  return : True if plane texture is successfully set            //
            ////////////////////////////////////////////////////////////////////
            bool setTexture(Texture& texture);

            ////////////////////////////////////////////////////////////////////
            //  Set plane color                                               //
            ////////////////////////////////////////////////////////////////////
            void setColor(const Vector4& color);

            ////////////////////////////////////////////////////////////////////
            //  Set plane color                                               //
            ////////////////////////////////////////////////////////////////////
            void setColor(float red, float green, float blue, float alpha);

            ////////////////////////////////////////////////////////////////////
            //  Set plane red channel                                         //
            ////////////////////////////////////////////////////////////////////
            inline void setRed(float red)
            {
                m_color.vec[0] = red;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set plane green channel                                       //
            ////////////////////////////////////////////////////////////////////
            inline void setGreen(float green)
            {
                m_color.vec[1] = green;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set plane blue channel                                        //
            ////////////////////////////////////////////////////////////////////
            inline void setBlue(float blue)
            {
                m_color.vec[2] = blue;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set plane alpha channel                                       //
            ////////////////////////////////////////////////////////////////////
            inline void setAlpha(float alpha)
            {
                m_color.vec[3] = alpha;
            }


            ////////////////////////////////////////////////////////////////////
            //  Set plane subrectangle                                        //
            ////////////////////////////////////////////////////////////////////
            void setSubrect(const Vector2& offset, const Vector2& size);

            ////////////////////////////////////////////////////////////////////
            //  Set plane subrectangle                                        //
            ////////////////////////////////////////////////////////////////////
            void setSubrect(
                float uOffset, float vOffset, float uSize, float vSize);

            ////////////////////////////////////////////////////////////////////
            //  Set plane UV offset                                           //
            ////////////////////////////////////////////////////////////////////
            inline void setUVOffset(const Vector2& offset)
            {
                m_uvOffset.vec[0] = offset.vec[0];
                m_uvOffset.vec[1] = offset.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Set plane UV offset                                           //
            ////////////////////////////////////////////////////////////////////
            inline void setUVOffset(float uOffset, float vOffset)
            {
                m_uvOffset.vec[0] = uOffset;
                m_uvOffset.vec[1] = vOffset;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set plane U offset                                            //
            ////////////////////////////////////////////////////////////////////
            inline void setUOffset(float uOffset)
            {
                m_uvOffset.vec[0] = uOffset;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set plane V offset                                            //
            ////////////////////////////////////////////////////////////////////
            inline void setVOffset(float vOffset)
            {
                m_uvOffset.vec[1] = vOffset;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set plane UV size                                             //
            ////////////////////////////////////////////////////////////////////
            inline void setUVSize(const Vector2& size)
            {
                m_uvSize.vec[0] = size.vec[0];
                m_uvSize.vec[1] = size.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Set plane UV size                                             //
            ////////////////////////////////////////////////////////////////////
            inline void setUVSize(float uSize, float vSize)
            {
                m_uvSize.vec[0] = uSize;
                m_uvSize.vec[1] = vSize;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set plane U size                                              //
            ////////////////////////////////////////////////////////////////////
            inline void setUSize(float uSize)
            {
                m_uvSize.vec[0] = uSize;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set plane V size                                              //
            ////////////////////////////////////////////////////////////////////
            inline void setVSize(float vSize)
            {
                m_uvSize.vec[1] = vSize;
            }


            ////////////////////////////////////////////////////////////////////
            //  Bind plane texture                                            //
            ////////////////////////////////////////////////////////////////////
            inline void bindTexture()
            {
                m_texture->bind();
            }

            ////////////////////////////////////////////////////////////////////
            //  Render plane                                                  //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Plane private copy constructor : Not copyable                 //
            ////////////////////////////////////////////////////////////////////
            Plane(const Plane&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Plane private copy operator : Not copyable                    //
            ////////////////////////////////////////////////////////////////////
            Plane& operator=(const Plane&) = delete;


        private:
            Texture*                m_texture;          // Plane texture pointer
            Vector4                 m_color;            // Plane color
            Vector2                 m_uvOffset;         // Plane UV offset
            Vector2                 m_uvSize;           // Plane UV size

            PlaneBillboardMode      m_billboard;        // Plane billboard mode
    };


#endif // VOS_RENDERER_PLANE_HEADER
