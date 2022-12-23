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
//     Renderer/StaticMesh.h : Static mesh management                         //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_STATICMESH_HEADER
#define VOS_RENDERER_STATICMESH_HEADER

    #include "../System/System.h"
    #include "Vulkan/VertexBuffer.h"
    #include "Vulkan/Texture.h"
    #include "../Math/Math.h"
    #include "../Math/Vector4.h"
    #include "../Math/Matrix4x4.h"
    #include "../Math/Transform3.h"

    #include <fstream>
    #include <cstdint>
    #include <new>


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class declaration                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer;


    ////////////////////////////////////////////////////////////////////////////
    //  StaticMesh class definition                                           //
    ////////////////////////////////////////////////////////////////////////////
    class StaticMesh : public Transform3
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  StaticMesh default constructor                                //
            ////////////////////////////////////////////////////////////////////
            StaticMesh();

            ////////////////////////////////////////////////////////////////////
            //  StaticMesh virtual destructor                                 //
            ////////////////////////////////////////////////////////////////////
            virtual ~StaticMesh();


            ////////////////////////////////////////////////////////////////////
            //  Init static mesh                                              //
            //  return : True if the static mesh is successfully created      //
            ////////////////////////////////////////////////////////////////////
            bool init(Renderer& renderer, Texture& texture,
                const float* vertices, const uint16_t* indices,
                uint32_t verticesCount, uint32_t indicesCount);

            ////////////////////////////////////////////////////////////////////
            //  Load static mesh from VMSH file                               //
            //  return : True if the static mesh is successfully loaded       //
            ////////////////////////////////////////////////////////////////////
            bool loadVMSH(Renderer& renderer,
                Texture& texture, const std::string& filepath);

            ////////////////////////////////////////////////////////////////////
            //  Destroy static mesh                                           //
            ////////////////////////////////////////////////////////////////////
            void destroyStaticMesh(Renderer& renderer);


            ////////////////////////////////////////////////////////////////////
            //  Set static mesh texture                                       //
            //  return : True if static mesh texture is successfully set      //
            ////////////////////////////////////////////////////////////////////
            bool setTexture(Texture& texture);

            ////////////////////////////////////////////////////////////////////
            //  Set static mesh color                                         //
            ////////////////////////////////////////////////////////////////////
            void setColor(const Vector4& color);

            ////////////////////////////////////////////////////////////////////
            //  Set static mesh color                                         //
            ////////////////////////////////////////////////////////////////////
            void setColor(float red, float green, float blue, float alpha);

            ////////////////////////////////////////////////////////////////////
            //  Set static mesh red channel                                   //
            ////////////////////////////////////////////////////////////////////
            void setRed(float red);

            ////////////////////////////////////////////////////////////////////
            //  Set static mesh green channel                                 //
            ////////////////////////////////////////////////////////////////////
            void setGreen(float green);

            ////////////////////////////////////////////////////////////////////
            //  Set static mesh blue channel                                  //
            ////////////////////////////////////////////////////////////////////
            void setBlue(float blue);

            ////////////////////////////////////////////////////////////////////
            //  Set static mesh alpha channel                                 //
            ////////////////////////////////////////////////////////////////////
            void setAlpha(float alpha);


            ////////////////////////////////////////////////////////////////////
            //  Bind static mesh vertex buffer                                //
            ////////////////////////////////////////////////////////////////////
            void bindVertexBuffer(Renderer& renderer);

            ////////////////////////////////////////////////////////////////////
            //  Render static mesh                                            //
            ////////////////////////////////////////////////////////////////////
            void render(Renderer& renderer);


        private:
            ////////////////////////////////////////////////////////////////////
            //  StaticMesh private copy constructor : Not copyable            //
            ////////////////////////////////////////////////////////////////////
            StaticMesh(const StaticMesh&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  StaticMesh private copy operator : Not copyable               //
            ////////////////////////////////////////////////////////////////////
            StaticMesh& operator=(const StaticMesh&) = delete;


        private:
            VertexBuffer    m_vertexBuffer;     // Static mesh vertex buffer
            uint32_t        m_indicesCount;     // Static mesh indices count
            Texture*        m_texture;          // Static mesh texture pointer
            Vector4         m_color;            // Static mesh color
    };


#endif // VOS_RENDERER_SPRITE_HEADER
