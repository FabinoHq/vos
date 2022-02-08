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
//     Renderer/Shapes/RectangleShape.h : Rectangle shape management          //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_SHAPES_RECTANGLESHAPE_HEADER
#define VOS_RENDERER_SHAPES_RECTANGLESHAPE_HEADER

    #include "../Shader.h"
    #include "../../Math/Math.h"
    #include "../../Math/Vector4.h"
    #include "../../Math/Matrix4x4.h"
    #include "../../Math/Transform2.h"

    #include "../Shaders/Rectangle.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class declaration                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer;


    ////////////////////////////////////////////////////////////////////////////
    //  RectangleShape class definition                                       //
    ////////////////////////////////////////////////////////////////////////////
    class RectangleShape : public Transform2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  RectangleShape default constructor                            //
            ////////////////////////////////////////////////////////////////////
            RectangleShape();

            ////////////////////////////////////////////////////////////////////
            //  RectangleShape virtual destructor                             //
            ////////////////////////////////////////////////////////////////////
            virtual ~RectangleShape();


            ////////////////////////////////////////////////////////////////////
            //  Init rectangle                                                //
            //  return : True if the rectangle is successfully created        //
            ////////////////////////////////////////////////////////////////////
            bool init(float width, float height);

            ////////////////////////////////////////////////////////////////////
            //  Set rectangle color                                           //
            ////////////////////////////////////////////////////////////////////
            void setColor(const Vector4& color);

            ////////////////////////////////////////////////////////////////////
            //  Set rectangle color                                           //
            ////////////////////////////////////////////////////////////////////
            void setColor(float red, float green, float blue, float alpha);

            ////////////////////////////////////////////////////////////////////
            //  Set rectangle red channel                                     //
            ////////////////////////////////////////////////////////////////////
            void setRed(float red);

            ////////////////////////////////////////////////////////////////////
            //  Set rectangle green channel                                   //
            ////////////////////////////////////////////////////////////////////
            void setGreen(float green);

            ////////////////////////////////////////////////////////////////////
            //  Set rectangle blue channel                                    //
            ////////////////////////////////////////////////////////////////////
            void setBlue(float blue);

            ////////////////////////////////////////////////////////////////////
            //  Set rectangle alpha channel                                   //
            ////////////////////////////////////////////////////////////////////
            void setAlpha(float alpha);

            ////////////////////////////////////////////////////////////////////
            //  Set rectangle smooth amount                                   //
            ////////////////////////////////////////////////////////////////////
            void setSmooth(float smooth);


            ////////////////////////////////////////////////////////////////////
            //  Render rectangle                                              //
            ////////////////////////////////////////////////////////////////////
            void render(Renderer& renderer);


        private:
            ////////////////////////////////////////////////////////////////////
            //  RectangleShape private copy constructor : Not copyable        //
            ////////////////////////////////////////////////////////////////////
            RectangleShape(const RectangleShape&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  RectangleShape private copy operator : Not copyable           //
            ////////////////////////////////////////////////////////////////////
            RectangleShape& operator=(const RectangleShape&) = delete;


        private:
            Vector4             m_color;            // Rectangle color
            float               m_smooth;           // Rectangle smooth amount
    };


#endif // VOS_RENDERER_SHAPES_RECTANGLESHAPE_HEADER
