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
//     Renderer/Shapes/CuboidShape.h : Cuboid shape management                //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_SHAPES_CUBOIDSHAPE_HEADER
#define VOS_RENDERER_SHAPES_CUBOIDSHAPE_HEADER

    #include "../../System/System.h"
    #include "../Vulkan/VertexBuffer.h"
    #include "../../Math/Math.h"
    #include "../../Math/Vector4.h"
    #include "../../Math/Matrix4x4.h"
    #include "../../Math/Transform3.h"

    #include <cstdint>
    #include <cstring>


    ////////////////////////////////////////////////////////////////////////////
    //  CuboidShape vertex buffer vertices                                    //
    ////////////////////////////////////////////////////////////////////////////
    const uint32_t CuboidShapeVerticesCount = 192;
    const float CuboidShapeVertices[CuboidShapeVerticesCount] =
    {
        // Front face (+Z)
        -0.5f, -0.5f, 0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
        // Back face (-Z)
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
        -0.5f, 0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
        // Top face (+Y)
        -0.5f, 0.5f, 0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        // Bottom face (-Y)
        0.5f, -0.5f, 0.5f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
        // Left face (-X)
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
        // Right face (+X)
        0.5f, -0.5f, 0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f
    };

    ////////////////////////////////////////////////////////////////////////////
    //  CuboidShape vertex buffer indices                                     //
    ////////////////////////////////////////////////////////////////////////////
    const uint32_t CuboidShapeIndicesCount = 36;
    const uint16_t CuboidShapeIndices[CuboidShapeIndicesCount] =
    {
        0, 1, 2,
        2, 3, 0,
        4, 5, 6,
        6, 7, 4,
        8, 9, 10,
        10, 11, 8,
        12, 13, 14,
        14, 15, 12,
        16, 17, 18,
        18, 19, 16,
        20, 21, 22,
        22, 23, 20
    };


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class declaration                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer;

    ////////////////////////////////////////////////////////////////////////////
    //  Resources class declaration                                           //
    ////////////////////////////////////////////////////////////////////////////
    class Resources;


    ////////////////////////////////////////////////////////////////////////////
    //  CuboidShape class definition                                          //
    ////////////////////////////////////////////////////////////////////////////
    class CuboidShape : public Transform3
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  CuboidShape default constructor                               //
            ////////////////////////////////////////////////////////////////////
            CuboidShape();

            ////////////////////////////////////////////////////////////////////
            //  CuboidShape virtual destructor                                //
            ////////////////////////////////////////////////////////////////////
            virtual ~CuboidShape();


            ////////////////////////////////////////////////////////////////////
            //  Init cuboid                                                   //
            //  return : True if the cuboid is successfully created           //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Set cuboid color                                              //
            ////////////////////////////////////////////////////////////////////
            void setColor(const Vector4& color);

            ////////////////////////////////////////////////////////////////////
            //  Set cuboid color                                              //
            ////////////////////////////////////////////////////////////////////
            void setColor(float red, float green, float blue, float alpha);

            ////////////////////////////////////////////////////////////////////
            //  Set cuboid red channel                                        //
            ////////////////////////////////////////////////////////////////////
            void setRed(float red);

            ////////////////////////////////////////////////////////////////////
            //  Set cuboid green channel                                      //
            ////////////////////////////////////////////////////////////////////
            void setGreen(float green);

            ////////////////////////////////////////////////////////////////////
            //  Set cuboid blue channel                                       //
            ////////////////////////////////////////////////////////////////////
            void setBlue(float blue);

            ////////////////////////////////////////////////////////////////////
            //  Set cuboid alpha channel                                      //
            ////////////////////////////////////////////////////////////////////
            void setAlpha(float alpha);


            ////////////////////////////////////////////////////////////////////
            //  Bind cuboid vertex buffer                                     //
            ////////////////////////////////////////////////////////////////////
            void bindVertexBuffer();

            ////////////////////////////////////////////////////////////////////
            //  Render cuboid                                                 //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  CuboidShape private copy constructor : Not copyable           //
            ////////////////////////////////////////////////////////////////////
            CuboidShape(const CuboidShape&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  CuboidShape private copy operator : Not copyable              //
            ////////////////////////////////////////////////////////////////////
            CuboidShape& operator=(const CuboidShape&) = delete;


        private:
            VertexBuffer*       m_vertexBuffer;     // Cuboid vertex buffer
            Vector4             m_color;            // Cuboid color
    };


#endif // VOS_RENDERER_SHAPES_CUBOIDSHAPE_HEADER
