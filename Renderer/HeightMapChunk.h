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
//     Renderer/HeightMapChunk.h : HeightMap chunk management                 //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_HEIGHTMAPCHUNK_HEADER
#define VOS_RENDERER_HEIGHTMAPCHUNK_HEADER

    #include "Vulkan/VertexBuffer.h"
    #include "Texture.h"
    #include "../Math/Math.h"
    #include "../Math/Vector3.h"
    #include "../Math/Vector4.h"
    #include "../Math/Matrix4x4.h"

    #include <fstream>
    #include <exception>
    #include <ctype.h>


    ////////////////////////////////////////////////////////////////////////////
    //  HeightMapChunk settings                                               //
    ////////////////////////////////////////////////////////////////////////////
    const uint16_t HeightMapChunkWidth = 64;
    const uint16_t HeightMapChunkHeight = 64;
    const float HeightMapChunkPlaneWidth = 1.0f;
    const float HeightMapChunkPlaneHeight = 1.0f;


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class declaration                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer;


    ////////////////////////////////////////////////////////////////////////////
    //  HeightMapChunk class definition                                       //
    ////////////////////////////////////////////////////////////////////////////
    class HeightMapChunk
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  HeightMapChunk default constructor                            //
            ////////////////////////////////////////////////////////////////////
            HeightMapChunk();

            ////////////////////////////////////////////////////////////////////
            //  HeightMapChunk destructor                                     //
            ////////////////////////////////////////////////////////////////////
            ~HeightMapChunk();


            ////////////////////////////////////////////////////////////////////
            //  Init heightmap chunk                                          //
            //  return : True if the heightmap chunk is successfully created  //
            ////////////////////////////////////////////////////////////////////
            bool init(Renderer& renderer, Texture& texture,
                const float* vertices, const uint16_t* indices,
                uint32_t verticesCount, uint32_t indicesCount);

            ////////////////////////////////////////////////////////////////////
            //  Generate flat heightmap chunk                                 //
            //  return : True if the flat heightmap chunk is generated        //
            ////////////////////////////////////////////////////////////////////
            bool generateFlat(Renderer& renderer, Texture& texture);

            ////////////////////////////////////////////////////////////////////
            //  Load heightmap chunk from VMSH file                           //
            //  return : True if the heightmap chunk is successfully loaded   //
            ////////////////////////////////////////////////////////////////////
            bool loadVMSH(Renderer& renderer,
                Texture& texture, const std::string& filepath);

            ////////////////////////////////////////////////////////////////////
            //  Destroy heightmap chunk                                       //
            ////////////////////////////////////////////////////////////////////
            void destroyHeightMapChunk(Renderer& renderer);


            ////////////////////////////////////////////////////////////////////
            //  Set heightmap chunk texture                                   //
            //  return : True if heightmap chunk texture is successfully set  //
            ////////////////////////////////////////////////////////////////////
            bool setTexture(Texture& texture);

            ////////////////////////////////////////////////////////////////////
            //  Set heightmap chunk position                                  //
            ////////////////////////////////////////////////////////////////////
            void setPosition(float x, float y, float z);

            ////////////////////////////////////////////////////////////////////
            //  Set heightmap chunk position                                  //
            ////////////////////////////////////////////////////////////////////
            void setPosition(Vector3& position);

            ////////////////////////////////////////////////////////////////////
            //  Set heightmap chunk X position                                //
            ////////////////////////////////////////////////////////////////////
            void setX(float x);

            ////////////////////////////////////////////////////////////////////
            //  Set heightmap chunk Y position                                //
            ////////////////////////////////////////////////////////////////////
            void setY(float y);

            ////////////////////////////////////////////////////////////////////
            //  Set heightmap chunk Z position                                //
            ////////////////////////////////////////////////////////////////////
            void setZ(float z);

            ////////////////////////////////////////////////////////////////////
            //  Translate heightmap chunk                                     //
            ////////////////////////////////////////////////////////////////////
            void move(float x, float y, float z);

            ////////////////////////////////////////////////////////////////////
            //  Translate heightmap chunk                                     //
            ////////////////////////////////////////////////////////////////////
            void move(Vector3& vector);

            ////////////////////////////////////////////////////////////////////
            //  Translate heightmap chunk on X axis                           //
            ////////////////////////////////////////////////////////////////////
            void moveX(float x);

            ////////////////////////////////////////////////////////////////////
            //  Translate heightmap chunk on Y axis                           //
            ////////////////////////////////////////////////////////////////////
            void moveY(float y);

            ////////////////////////////////////////////////////////////////////
            //  Translate heightmap chunk on Z axis                           //
            ////////////////////////////////////////////////////////////////////
            void moveZ(float z);

            ////////////////////////////////////////////////////////////////////
            //  Set heightmap chunk rotation angles                           //
            ////////////////////////////////////////////////////////////////////
            void setAngles(float angleX, float angleY, float angleZ);

            ////////////////////////////////////////////////////////////////////
            //  Set heightmap chunk rotation angles                           //
            ////////////////////////////////////////////////////////////////////
            void setAngles(Vector3& angles);

            ////////////////////////////////////////////////////////////////////
            //  Set heightmap chunk chunk X rotation angle                    //
            ////////////////////////////////////////////////////////////////////
            void setAngleX(float angleX);

            ////////////////////////////////////////////////////////////////////
            //  Set heightmap chunk Y rotation angle                          //
            ////////////////////////////////////////////////////////////////////
            void setAngleY(float angleY);

            ////////////////////////////////////////////////////////////////////
            //  Set heightmap chunk Z rotation angle                          //
            ////////////////////////////////////////////////////////////////////
            void setAngleZ(float angleZ);

            ////////////////////////////////////////////////////////////////////
            //  Rotate heightmap chunk                                        //
            ////////////////////////////////////////////////////////////////////
            void rotate(float angleX, float angleY, float angleZ);

            ////////////////////////////////////////////////////////////////////
            //  Rotate heightmap chunk                                        //
            ////////////////////////////////////////////////////////////////////
            void rotate(Vector3& angles);

            ////////////////////////////////////////////////////////////////////
            //  Rotate heightmap chunk around the X axis                      //
            ////////////////////////////////////////////////////////////////////
            void rotateX(float angleX);

            ////////////////////////////////////////////////////////////////////
            //  Rotate heightmap chunk around the Y axis                      //
            ////////////////////////////////////////////////////////////////////
            void rotateY(float angleY);

            ////////////////////////////////////////////////////////////////////
            //  Rotate heightmap chunk around the Z axis                      //
            ////////////////////////////////////////////////////////////////////
            void rotateZ(float angleZ);


            ////////////////////////////////////////////////////////////////////
            //  Bind heightmap chunk vertex buffer                            //
            ////////////////////////////////////////////////////////////////////
            void bindVertexBuffer(Renderer& renderer);

            ////////////////////////////////////////////////////////////////////
            //  Render heightmap chunk                                        //
            ////////////////////////////////////////////////////////////////////
            void render(Renderer& renderer);


        private:
            ////////////////////////////////////////////////////////////////////
            //  HeightMapChunk private copy constructor : Not copyable        //
            ////////////////////////////////////////////////////////////////////
            HeightMapChunk(const HeightMapChunk&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  HeightMapChunk private copy operator : Not copyable           //
            ////////////////////////////////////////////////////////////////////
            HeightMapChunk& operator=(const HeightMapChunk&) = delete;


        private:
            VertexBuffer    m_vertexBuffer;     // Heightmap chunk vertex buffer
            uint32_t        m_indicesCount;     // Heightmap chunk indices count
            Texture*        m_texture;          // Heightmap chunk texture ptr
            Matrix4x4       m_modelMatrix;      // Heightmap chunk model matrix
            Vector3         m_position;         // Heightmap chunk position
            Vector3         m_angles;           // Heightmap chunk angles
    };


#endif // VOS_RENDERER_HEIGHTMAPCHUNK_HEADER
