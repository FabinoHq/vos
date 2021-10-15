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
//     Renderer/ProcSprite.h : Procedural sprite management                   //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_PROCSPRITE_HEADER
#define VOS_RENDERER_PROCSPRITE_HEADER

    #include "Pipeline.h"
    #include "../Math/Math.h"
    #include "../Math/Vector2.h"
    #include "../Math/Vector4.h"
    #include "../Math/Matrix4x4.h"

    #include "Shaders/DefaultProc.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class declaration                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer;


    ////////////////////////////////////////////////////////////////////////////
    //  ProcSprite class definition                                           //
    ////////////////////////////////////////////////////////////////////////////
    class ProcSprite
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  ProcSprite default constructor                                //
            ////////////////////////////////////////////////////////////////////
            ProcSprite();

            ////////////////////////////////////////////////////////////////////
            //  ProcSprite destructor                                         //
            ////////////////////////////////////////////////////////////////////
            ~ProcSprite();


            ////////////////////////////////////////////////////////////////////
            //  Init procedural sprite                                        //
            //  return : True if the proc sprite is successfully created      //
            ////////////////////////////////////////////////////////////////////
            bool init(Renderer& renderer, const uint32_t* fragmentSource,
                const size_t fragmentSize, float width, float height);

            ////////////////////////////////////////////////////////////////////
            //  Destroy procedural sprite                                     //
            ////////////////////////////////////////////////////////////////////
            void destroyProcSprite(Renderer& renderer);


            ////////////////////////////////////////////////////////////////////
            //  Set procedural sprite position                                //
            ////////////////////////////////////////////////////////////////////
            void setPosition(float x, float y);

            ////////////////////////////////////////////////////////////////////
            //  Set procedural sprite position                                //
            ////////////////////////////////////////////////////////////////////
            void setPosition(Vector2& position);

            ////////////////////////////////////////////////////////////////////
            //  Set procedural sprite X position                              //
            ////////////////////////////////////////////////////////////////////
            void setX(float x);

            ////////////////////////////////////////////////////////////////////
            //  Set procedural sprite Y position                              //
            ////////////////////////////////////////////////////////////////////
            void setY(float y);

            ////////////////////////////////////////////////////////////////////
            //  Translate procedural sprite                                   //
            ////////////////////////////////////////////////////////////////////
            void move(float x, float y);

            ////////////////////////////////////////////////////////////////////
            //  Translate procedural sprite                                   //
            ////////////////////////////////////////////////////////////////////
            void move(Vector2& vector);

            ////////////////////////////////////////////////////////////////////
            //  Translate procedural sprite on X axis                         //
            ////////////////////////////////////////////////////////////////////
            void moveX(float x);

            ////////////////////////////////////////////////////////////////////
            //  Translate procedural sprite on Y axis                         //
            ////////////////////////////////////////////////////////////////////
            void moveY(float y);

            ////////////////////////////////////////////////////////////////////
            //  Set procedural sprite size                                    //
            ////////////////////////////////////////////////////////////////////
            void setSize(float width, float height);

            ////////////////////////////////////////////////////////////////////
            //  Set procedural sprite size                                    //
            ////////////////////////////////////////////////////////////////////
            void setSize(Vector2& size);

            ////////////////////////////////////////////////////////////////////
            //  Set procedural sprite width                                   //
            ////////////////////////////////////////////////////////////////////
            void setWidth(float width);

            ////////////////////////////////////////////////////////////////////
            //  Set procedural sprite height                                  //
            ////////////////////////////////////////////////////////////////////
            void setHeight(float height);

            ////////////////////////////////////////////////////////////////////
            //  Set procedural sprite rotation angle                          //
            ////////////////////////////////////////////////////////////////////
            void setAngle(float angle);

            ////////////////////////////////////////////////////////////////////
            //  Rotate procedural sprite                                      //
            ////////////////////////////////////////////////////////////////////
            void rotate(float angle);


            ////////////////////////////////////////////////////////////////////
            //  Set procedural sprite color                                   //
            ////////////////////////////////////////////////////////////////////
            void setColor(Vector4 color);

            ////////////////////////////////////////////////////////////////////
            //  Set procedural sprite color                                   //
            ////////////////////////////////////////////////////////////////////
            void setColor(float red, float green, float blue, float alpha);

            ////////////////////////////////////////////////////////////////////
            //  Set procedural sprite red channel                             //
            ////////////////////////////////////////////////////////////////////
            void setRed(float red);

            ////////////////////////////////////////////////////////////////////
            //  Set procedural sprite green channel                           //
            ////////////////////////////////////////////////////////////////////
            void setGreen(float green);

            ////////////////////////////////////////////////////////////////////
            //  Set procedural sprite blue channel                            //
            ////////////////////////////////////////////////////////////////////
            void setBlue(float blue);

            ////////////////////////////////////////////////////////////////////
            //  Set procedural sprite alpha channel                           //
            ////////////////////////////////////////////////////////////////////
            void setAlpha(float alpha);


            ////////////////////////////////////////////////////////////////////
            //  Render procedural sprite                                      //
            ////////////////////////////////////////////////////////////////////
            void render(Renderer& renderer);


        private:
            ////////////////////////////////////////////////////////////////////
            //  ProcSprite private copy constructor : Not copyable            //
            ////////////////////////////////////////////////////////////////////
            ProcSprite(const ProcSprite&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  ProcSprite private copy operator : Not copyable               //
            ////////////////////////////////////////////////////////////////////
            ProcSprite& operator=(const ProcSprite&) = delete;


        private:
            Pipeline            m_pipeline;         // ProcSprite pipeline
            Matrix4x4           m_modelMatrix;      // ProcSprite model matrix
            Vector2             m_position;         // ProcSprite position
            Vector2             m_size;             // ProcSprite size
            float               m_angle;            // ProcSprite angle
            Vector4             m_color;            // ProcSprite color
    };


#endif // VOS_RENDERER_PROCSPRITE_HEADER
