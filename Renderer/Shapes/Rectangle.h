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
//     Renderer/Shapes/Rectangle.h : Rectangle shape management               //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_SHAPES_RECTANGLE_HEADER
#define VOS_RENDERER_SHAPES_RECTANGLE_HEADER

    #include "../Shader.h"
    #include "../../Math/Math.h"
    #include "../../Math/Vector2.h"
    #include "../../Math/Matrix4x4.h"

    #include "../Shaders/Rectangle.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class declaration                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer;


    ////////////////////////////////////////////////////////////////////////////
    //  Rectangle class definition                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Rectangle
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Rectangle default constructor                                 //
            ////////////////////////////////////////////////////////////////////
            Rectangle();

            ////////////////////////////////////////////////////////////////////
            //  Rectangle destructor                                          //
            ////////////////////////////////////////////////////////////////////
            ~Rectangle();


            ////////////////////////////////////////////////////////////////////
            //  Init rectangle                                                //
            //  return : True if the rectangle is successfully created        //
            ////////////////////////////////////////////////////////////////////
            bool init(float width, float height);

            ////////////////////////////////////////////////////////////////////
            //  Destroy rectangle                                             //
            ////////////////////////////////////////////////////////////////////
            void destroyRectangle(Renderer& renderer);


            ////////////////////////////////////////////////////////////////////
            //  Set rectangle position                                        //
            ////////////////////////////////////////////////////////////////////
            void setPosition(float x, float y);

            ////////////////////////////////////////////////////////////////////
            //  Set rectanglee position                                       //
            ////////////////////////////////////////////////////////////////////
            void setPosition(Vector2& position);

            ////////////////////////////////////////////////////////////////////
            //  Set rectangle X position                                      //
            ////////////////////////////////////////////////////////////////////
            void setX(float x);

            ////////////////////////////////////////////////////////////////////
            //  Set rectangle Y position                                      //
            ////////////////////////////////////////////////////////////////////
            void setY(float y);

            ////////////////////////////////////////////////////////////////////
            //  Translate rectangle                                           //
            ////////////////////////////////////////////////////////////////////
            void move(float x, float y);

            ////////////////////////////////////////////////////////////////////
            //  Translate rectangle                                           //
            ////////////////////////////////////////////////////////////////////
            void move(Vector2& vector);

            ////////////////////////////////////////////////////////////////////
            //  Translate rectangle on X axis                                 //
            ////////////////////////////////////////////////////////////////////
            void moveX(float x);

            ////////////////////////////////////////////////////////////////////
            //  Translate rectangle on Y axis                                 //
            ////////////////////////////////////////////////////////////////////
            void moveY(float y);

            ////////////////////////////////////////////////////////////////////
            //  Set rectangle size                                            //
            ////////////////////////////////////////////////////////////////////
            void setSize(float width, float height);

            ////////////////////////////////////////////////////////////////////
            //  Set rectangle size                                            //
            ////////////////////////////////////////////////////////////////////
            void setSize(Vector2& size);

            ////////////////////////////////////////////////////////////////////
            //  Set rectangle width                                           //
            ////////////////////////////////////////////////////////////////////
            void setWidth(float width);

            ////////////////////////////////////////////////////////////////////
            //  Set rectangle height                                          //
            ////////////////////////////////////////////////////////////////////
            void setHeight(float height);

            ////////////////////////////////////////////////////////////////////
            //  Set rectangle rotation angle                                  //
            ////////////////////////////////////////////////////////////////////
            void setAngle(float angle);

            ////////////////////////////////////////////////////////////////////
            //  Rotate rectangle                                              //
            ////////////////////////////////////////////////////////////////////
            void rotate(float angle);


            ////////////////////////////////////////////////////////////////////
            //  Render rectangle                                              //
            ////////////////////////////////////////////////////////////////////
            void render(Renderer& renderer);


        private:
            ////////////////////////////////////////////////////////////////////
            //  Rectangle private copy constructor : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            Rectangle(const Rectangle&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Rectangle private copy operator : Not copyable                //
            ////////////////////////////////////////////////////////////////////
            Rectangle& operator=(const Rectangle&) = delete;


        private:
            Matrix4x4           m_modelMatrix;      // Rectangle model matrix
            Vector2             m_position;         // Rectangle position
            Vector2             m_size;             // Rectangle size
            float               m_angle;            // Rectangle angle
    };


#endif // VOS_RENDERER_SHAPES_RECTANGLE_HEADER
