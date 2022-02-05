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
//     Renderer/Shapes/Oval.h : Ellipse shape management                      //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_SHAPES_OVAL_HEADER
#define VOS_RENDERER_SHAPES_OVAL_HEADER

    #include "../Shader.h"
    #include "../../Math/Math.h"
    #include "../../Math/Vector2.h"
    #include "../../Math/Vector4.h"
    #include "../../Math/Matrix4x4.h"
    #include "../../Math/Transform2.h"

    #include "../Shaders/Oval.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class declaration                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer;


    ////////////////////////////////////////////////////////////////////////////
    //  Oval class definition                                                 //
    ////////////////////////////////////////////////////////////////////////////
    class Oval : public Transform2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Oval default constructor                                      //
            ////////////////////////////////////////////////////////////////////
            Oval();

            ////////////////////////////////////////////////////////////////////
            //  Oval virtual destructor                                       //
            ////////////////////////////////////////////////////////////////////
            virtual ~Oval();


            ////////////////////////////////////////////////////////////////////
            //  Init oval                                                     //
            //  return : True if the oval is successfully created             //
            ////////////////////////////////////////////////////////////////////
            bool init(float width, float height);

            ////////////////////////////////////////////////////////////////////
            //  Set oval color                                                //
            ////////////////////////////////////////////////////////////////////
            void setColor(Vector4 color);

            ////////////////////////////////////////////////////////////////////
            //  Set oval color                                                //
            ////////////////////////////////////////////////////////////////////
            void setColor(float red, float green, float blue, float alpha);

            ////////////////////////////////////////////////////////////////////
            //  Set oval red channel                                          //
            ////////////////////////////////////////////////////////////////////
            void setRed(float red);

            ////////////////////////////////////////////////////////////////////
            //  Set oval green channel                                        //
            ////////////////////////////////////////////////////////////////////
            void setGreen(float green);

            ////////////////////////////////////////////////////////////////////
            //  Set oval blue channel                                         //
            ////////////////////////////////////////////////////////////////////
            void setBlue(float blue);

            ////////////////////////////////////////////////////////////////////
            //  Set oval alpha channel                                        //
            ////////////////////////////////////////////////////////////////////
            void setAlpha(float alpha);


            ////////////////////////////////////////////////////////////////////
            //  Render oval                                                  //
            ////////////////////////////////////////////////////////////////////
            void render(Renderer& renderer);


        private:
            ////////////////////////////////////////////////////////////////////
            //  Oval private copy constructor : Not copyable                  //
            ////////////////////////////////////////////////////////////////////
            Oval(const Oval&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Oval private copy operator : Not copyable                     //
            ////////////////////////////////////////////////////////////////////
            Oval& operator=(const Oval&) = delete;


        private:
            Vector4             m_color;            // Oval color
    };


#endif // VOS_RENDERER_SHAPES_OVAL_HEADER
