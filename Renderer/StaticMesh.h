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
//   For more information, please refer to <http://unlicense.org>             //
////////////////////////////////////////////////////////////////////////////////
//    VOS : Virtual Operating System                                          //
//     Renderer/StaticMesh.h : Static mesh management                         //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_STATICMESH_HEADER
#define VOS_RENDERER_STATICMESH_HEADER

    #include "Vulkan/VertexBuffer.h"
    #include "Texture.h"
    #include "../Math/Math.h"
    #include "../Math/Vector3.h"
    #include "../Math/Vector4.h"
    #include "../Math/Matrix4x4.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class declaration                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer;


    ////////////////////////////////////////////////////////////////////////////
    //  StaticMesh class definition                                           //
    ////////////////////////////////////////////////////////////////////////////
    class StaticMesh
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  StaticMesh default constructor                                //
            ////////////////////////////////////////////////////////////////////
            StaticMesh();

            ////////////////////////////////////////////////////////////////////
            //  StaticMesh destructor                                         //
            ////////////////////////////////////////////////////////////////////
            ~StaticMesh();


            ////////////////////////////////////////////////////////////////////
            //  Init static mesh                                              //
            //  return : True if the static mesh is successfully created      //
            ////////////////////////////////////////////////////////////////////
            bool init(Renderer& renderer, Texture& texture);

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
            //  Set static mesh position                                      //
            ////////////////////////////////////////////////////////////////////
            void setPosition(float x, float y, float z);

            ////////////////////////////////////////////////////////////////////
            //  Set static mesh position                                      //
            ////////////////////////////////////////////////////////////////////
            void setPosition(Vector3& position);

            ////////////////////////////////////////////////////////////////////
            //  Set static mesh X position                                    //
            ////////////////////////////////////////////////////////////////////
            void setX(float x);

            ////////////////////////////////////////////////////////////////////
            //  Set static mesh Y position                                    //
            ////////////////////////////////////////////////////////////////////
            void setY(float y);

            ////////////////////////////////////////////////////////////////////
            //  Set static mesh Z position                                    //
            ////////////////////////////////////////////////////////////////////
            void setZ(float z);

            ////////////////////////////////////////////////////////////////////
            //  Translate static mesh                                         //
            ////////////////////////////////////////////////////////////////////
            void move(float x, float y, float z);

            ////////////////////////////////////////////////////////////////////
            //  Translate static mesh                                         //
            ////////////////////////////////////////////////////////////////////
            void move(Vector3& vector);

            ////////////////////////////////////////////////////////////////////
            //  Translate static mesh on X axis                               //
            ////////////////////////////////////////////////////////////////////
            void moveX(float x);

            ////////////////////////////////////////////////////////////////////
            //  Translate static mesh on Y axis                               //
            ////////////////////////////////////////////////////////////////////
            void moveY(float y);

            ////////////////////////////////////////////////////////////////////
            //  Translate static mesh on Z axis                               //
            ////////////////////////////////////////////////////////////////////
            void moveZ(float z);

            ////////////////////////////////////////////////////////////////////
            //  Set mesh rotation angles                                      //
            ////////////////////////////////////////////////////////////////////
            void setAngles(float angleX, float angleY, float angleZ);

            ////////////////////////////////////////////////////////////////////
            //  Set mesh rotation angles                                      //
            ////////////////////////////////////////////////////////////////////
            void setAngles(Vector3& angles);

            ////////////////////////////////////////////////////////////////////
            //  Set static mesh X rotation angle                              //
            ////////////////////////////////////////////////////////////////////
            void setAngleX(float angleX);

            ////////////////////////////////////////////////////////////////////
            //  Set static mesh Y rotation angle                              //
            ////////////////////////////////////////////////////////////////////
            void setAngleY(float angleY);

            ////////////////////////////////////////////////////////////////////
            //  Set static mesh Z rotation angle                              //
            ////////////////////////////////////////////////////////////////////
            void setAngleZ(float angleZ);

            ////////////////////////////////////////////////////////////////////
            //  Rotate static mesh                                            //
            ////////////////////////////////////////////////////////////////////
            void rotate(float angleX, float angleY, float angleZ);

            ////////////////////////////////////////////////////////////////////
            //  Rotate static mesh                                            //
            ////////////////////////////////////////////////////////////////////
            void rotate(Vector3& angles);

            ////////////////////////////////////////////////////////////////////
            //  Rotate static mesh around the X axis                          //
            ////////////////////////////////////////////////////////////////////
            void rotateX(float angleX);

            ////////////////////////////////////////////////////////////////////
            //  Rotate static mesh around the Y axis                          //
            ////////////////////////////////////////////////////////////////////
            void rotateY(float angleY);

            ////////////////////////////////////////////////////////////////////
            //  Rotate static mesh around the Z axis                          //
            ////////////////////////////////////////////////////////////////////
            void rotateZ(float angleZ);


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
            Texture*        m_texture;          // Static mesh texture pointer
            Matrix4x4       m_modelMatrix;      // Static mesh model matrix
            Vector3         m_position;         // Static mesh position
            Vector3         m_angles;           // Static mesh angles
    };


#endif // VOS_RENDERER_SPRITE_HEADER
