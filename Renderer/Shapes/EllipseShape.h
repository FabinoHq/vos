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
//     Renderer/Shapes/EllipseShape.h : Ellipse shape management              //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_SHAPES_ELLIPSESHAPE_HEADER
#define VOS_RENDERER_SHAPES_ELLIPSESHAPE_HEADER

    #include "../../System/System.h"
    #include "../Vulkan/Vulkan.h"
    #include "../Vulkan/Swapchain.h"
    #include "../Vulkan/GraphicsLayout.h"
    #include "../../Math/Math.h"
    #include "../../Math/Vector4.h"
    #include "../../Math/Matrix4x4.h"
    #include "../../Math/Transform2.h"


    ////////////////////////////////////////////////////////////////////////////
    //  EllipseShape class definition                                         //
    ////////////////////////////////////////////////////////////////////////////
    class EllipseShape : public Transform2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  EllipseShape default constructor                              //
            ////////////////////////////////////////////////////////////////////
            EllipseShape();

            ////////////////////////////////////////////////////////////////////
            //  EllipseShape virtual destructor                               //
            ////////////////////////////////////////////////////////////////////
            virtual ~EllipseShape();


            ////////////////////////////////////////////////////////////////////
            //  Init ellipse                                                  //
            //  return : True if the ellipse is successfully created          //
            ////////////////////////////////////////////////////////////////////
            bool init(float width, float height);

            ////////////////////////////////////////////////////////////////////
            //  Set ellipse color                                             //
            ////////////////////////////////////////////////////////////////////
            void setColor(const Vector4& color);

            ////////////////////////////////////////////////////////////////////
            //  Set ellipse color                                             //
            ////////////////////////////////////////////////////////////////////
            void setColor(float red, float green, float blue, float alpha);

            ////////////////////////////////////////////////////////////////////
            //  Set ellipse red channel                                       //
            ////////////////////////////////////////////////////////////////////
            void setRed(float red);

            ////////////////////////////////////////////////////////////////////
            //  Set ellipse green channel                                     //
            ////////////////////////////////////////////////////////////////////
            void setGreen(float green);

            ////////////////////////////////////////////////////////////////////
            //  Set ellipse blue channel                                      //
            ////////////////////////////////////////////////////////////////////
            void setBlue(float blue);

            ////////////////////////////////////////////////////////////////////
            //  Set ellipse alpha channel                                     //
            ////////////////////////////////////////////////////////////////////
            void setAlpha(float alpha);

            ////////////////////////////////////////////////////////////////////
            //  Set ellipse smooth amount                                     //
            ////////////////////////////////////////////////////////////////////
            void setSmooth(float smooth);


            ////////////////////////////////////////////////////////////////////
            //  Render ellipse                                                //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  EllipseShape private copy constructor : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            EllipseShape(const EllipseShape&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  EllipseShape private copy operator : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            EllipseShape& operator=(const EllipseShape&) = delete;


        private:
            Vector4             m_color;            // Ellipse color
            float               m_smooth;           // Ellipse smooth amount
    };


#endif // VOS_RENDERER_SHAPES_ELLIPSESHAPE_HEADER
