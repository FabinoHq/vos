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
//     Renderer/SkyBox.h : SkyBox management                                  //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_SKYBOX_HEADER
#define VOS_RENDERER_SKYBOX_HEADER

    #include "../System/System.h"
    #include "Vulkan/Vulkan.h"
    #include "Vulkan/Swapchain.h"
    #include "Vulkan/GraphicsLayout.h"
    #include "Vulkan/VertexBuffer.h"
    #include "Vulkan/CubeMap.h"
    #include "../Math/Math.h"
    #include "../Math/Vector4.h"
    #include "../Math/Matrix4x4.h"
    #include "../Math/Transform3.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  SkyBox vertex buffer vertices                                         //
    ////////////////////////////////////////////////////////////////////////////
    const uint32_t SkyBoxVerticesCount = 72;
    const float SkyBoxVertices[SkyBoxVerticesCount] =
    {
        // Front face (+Z)
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        // Back face (-Z)
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        // Top face (+Y)
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        // Bottom face (-Y)
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        // Left face (-X)
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        // Right face (+X)
        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f
    };

    ////////////////////////////////////////////////////////////////////////////
    //  SkyBox vertex buffer indices                                          //
    ////////////////////////////////////////////////////////////////////////////
    const uint32_t SkyBoxIndicesCount = 36;
    const uint16_t SkyBoxIndices[SkyBoxIndicesCount] =
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
    //  SkyBox class definition                                               //
    ////////////////////////////////////////////////////////////////////////////
    class SkyBox : public Transform3
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  SkyBox default constructor                                    //
            ////////////////////////////////////////////////////////////////////
            SkyBox();

            ////////////////////////////////////////////////////////////////////
            //  SkyBox virtual destructor                                     //
            ////////////////////////////////////////////////////////////////////
            virtual ~SkyBox();


            ////////////////////////////////////////////////////////////////////
            //  Init skybox                                                   //
            //  return : True if the skybox is successfully created           //
            ////////////////////////////////////////////////////////////////////
            bool init(VertexBuffer& vertexBuffer, CubeMap& cubemap);

            ////////////////////////////////////////////////////////////////////
            //  Set skybox color                                              //
            ////////////////////////////////////////////////////////////////////
            void setColor(const Vector4& color);

            ////////////////////////////////////////////////////////////////////
            //  Set skybox color                                              //
            ////////////////////////////////////////////////////////////////////
            void setColor(float red, float green, float blue, float alpha);

            ////////////////////////////////////////////////////////////////////
            //  Set skybox red channel                                        //
            ////////////////////////////////////////////////////////////////////
            void setRed(float red);

            ////////////////////////////////////////////////////////////////////
            //  Set skybox green channel                                      //
            ////////////////////////////////////////////////////////////////////
            void setGreen(float green);

            ////////////////////////////////////////////////////////////////////
            //  Set skybox blue channel                                       //
            ////////////////////////////////////////////////////////////////////
            void setBlue(float blue);

            ////////////////////////////////////////////////////////////////////
            //  Set skybox alpha channel                                      //
            ////////////////////////////////////////////////////////////////////
            void setAlpha(float alpha);


            ////////////////////////////////////////////////////////////////////
            //  Bind skybox vertex buffer                                     //
            ////////////////////////////////////////////////////////////////////
            void bindVertexBuffer();

            ////////////////////////////////////////////////////////////////////
            //  Bind skybox cubemap                                           //
            ////////////////////////////////////////////////////////////////////
            void bindCubeMap();

            ////////////////////////////////////////////////////////////////////
            //  Render skybox                                                 //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  SkyBox private copy constructor : Not copyable                //
            ////////////////////////////////////////////////////////////////////
            SkyBox(const SkyBox&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  SkyBox private copy operator : Not copyable                   //
            ////////////////////////////////////////////////////////////////////
            SkyBox& operator=(const SkyBox&) = delete;


        private:
            VertexBuffer*       m_vertexBuffer;     // SkyBox vertex buffer
            CubeMap*            m_cubemap;          // SkyBox cubemap pointer
            Vector4             m_color;            // SkyBox color
    };


#endif // VOS_RENDERER_SKYBOX_HEADER
