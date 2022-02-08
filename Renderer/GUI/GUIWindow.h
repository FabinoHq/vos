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
//     Renderer/GUI/GUIWindow.h : GUI Window management                       //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_GUI_GUIWINDOW_HEADER
#define VOS_RENDERER_GUI_GUIWINDOW_HEADER

    #include "../Texture.h"
    #include "../../Math/Math.h"
    #include "../../Math/Vector2.h"
    #include "../../Math/Vector4.h"
    #include "../../Math/Matrix4x4.h"
    #include "../../Math/Transform2.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class declaration                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer;


    ////////////////////////////////////////////////////////////////////////////
    //  GUIWindow class definition                                            //
    ////////////////////////////////////////////////////////////////////////////
    class GUIWindow : public Transform2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  GUIWindow default constructor                                 //
            ////////////////////////////////////////////////////////////////////
            GUIWindow();

            ////////////////////////////////////////////////////////////////////
            //  GUIWindow virtual destructor                                  //
            ////////////////////////////////////////////////////////////////////
            virtual ~GUIWindow();


            ////////////////////////////////////////////////////////////////////
            //  Init window                                                   //
            //  return : True if the window is successfully created           //
            ////////////////////////////////////////////////////////////////////
            bool init(Texture& texture,
                float width, float height, float uvFactor);

            ////////////////////////////////////////////////////////////////////
            //  Set window texture                                            //
            //  return : True if window texture is successfully set           //
            ////////////////////////////////////////////////////////////////////
            bool setTexture(Texture& texture);

            ////////////////////////////////////////////////////////////////////
            //  Set window color                                              //
            ////////////////////////////////////////////////////////////////////
            void setColor(const Vector4& color);

            ////////////////////////////////////////////////////////////////////
            //  Set window color                                              //
            ////////////////////////////////////////////////////////////////////
            void setColor(float red, float green, float blue, float alpha);

            ////////////////////////////////////////////////////////////////////
            //  Set window red channel                                        //
            ////////////////////////////////////////////////////////////////////
            void setRed(float red);

            ////////////////////////////////////////////////////////////////////
            //  Set window green channel                                      //
            ////////////////////////////////////////////////////////////////////
            void setGreen(float green);

            ////////////////////////////////////////////////////////////////////
            //  Set window blue channel                                       //
            ////////////////////////////////////////////////////////////////////
            void setBlue(float blue);

            ////////////////////////////////////////////////////////////////////
            //  Set window alpha channel                                      //
            ////////////////////////////////////////////////////////////////////
            void setAlpha(float alpha);


            ////////////////////////////////////////////////////////////////////
            //  Set size                                                      //
            ////////////////////////////////////////////////////////////////////
            inline void setSize(float width, float height)
            {
                m_size.vec[0] = width;
                m_size.vec[1] = height;
                clampWindowSize();
            }

            ////////////////////////////////////////////////////////////////////
            //  Set size                                                      //
            ////////////////////////////////////////////////////////////////////
            inline void setSize(const Vector2& size)
            {
                m_size.vec[0] = size.vec[0];
                m_size.vec[1] = size.vec[1];
                clampWindowSize();
            }

            ////////////////////////////////////////////////////////////////////
            //  Set width                                                     //
            ////////////////////////////////////////////////////////////////////
            inline void setWidth(float width)
            {
                m_size.vec[0] = width;
                clampWindowSize();
            }

            ////////////////////////////////////////////////////////////////////
            //  Set height                                                    //
            ////////////////////////////////////////////////////////////////////
            inline void setHeight(float height)
            {
                m_size.vec[1] = height;
                clampWindowSize();
            }


            ////////////////////////////////////////////////////////////////////
            //  Set window UV factor                                          //
            ////////////////////////////////////////////////////////////////////
            void setUVFactor(float uvFactor);

            ////////////////////////////////////////////////////////////////////
            //  Set window movable state                                      //
            ////////////////////////////////////////////////////////////////////
            void setMovable(bool movable);

            ////////////////////////////////////////////////////////////////////
            //  Set window resizable state                                    //
            ////////////////////////////////////////////////////////////////////
            void setResizable(bool resizable);

            ////////////////////////////////////////////////////////////////////
            //  Set window minimum size                                       //
            ////////////////////////////////////////////////////////////////////
            void setMinSize(const Vector2& minSize);

            ////////////////////////////////////////////////////////////////////
            //  Set window minimum size                                       //
            ////////////////////////////////////////////////////////////////////
            void setMinSize(float minWidth, float minHeight);

            ////////////////////////////////////////////////////////////////////
            //  Set window maximum size                                       //
            ////////////////////////////////////////////////////////////////////
            void setMaxSize(const Vector2& maxSize);

            ////////////////////////////////////////////////////////////////////
            //  Set window maximum size                                       //
            ////////////////////////////////////////////////////////////////////
            void setMaxSize(float maxWidth, float maxHeight);

            ////////////////////////////////////////////////////////////////////
            //  Set window top bar size                                       //
            ////////////////////////////////////////////////////////////////////
            void setTopBarSize(float topBarSize);

            ////////////////////////////////////////////////////////////////////
            //  Set window resize bar size                                    //
            ////////////////////////////////////////////////////////////////////
            void setResizeBarSize(float resizeBarSize);


            ////////////////////////////////////////////////////////////////////
            //  Get window picking state                                      //
            ////////////////////////////////////////////////////////////////////
            bool isPicking(float mouseX, float mouseY);

            ////////////////////////////////////////////////////////////////////
            //  Get window top bar picking state                              //
            ////////////////////////////////////////////////////////////////////
            bool isTopBarPicking(float mouseX, float mouseY);

            ////////////////////////////////////////////////////////////////////
            //  Get window top resize bar picking state                       //
            ////////////////////////////////////////////////////////////////////
            bool isTopResizePicking(float mouseX, float mouseY);

            ////////////////////////////////////////////////////////////////////
            //  Get window bottom resize bar picking state                    //
            ////////////////////////////////////////////////////////////////////
            bool isBottomResizePicking(float mouseX, float mouseY);

            ////////////////////////////////////////////////////////////////////
            //  Get window left resize bar picking state                      //
            ////////////////////////////////////////////////////////////////////
            bool isLeftResizePicking(float mouseX, float mouseY);

            ////////////////////////////////////////////////////////////////////
            //  Get window right resize bar picking state                     //
            ////////////////////////////////////////////////////////////////////
            bool isRightResizePicking(float mouseX, float mouseY);


            ////////////////////////////////////////////////////////////////////
            //  Handle window mouse press event                               //
            ////////////////////////////////////////////////////////////////////
            bool mousePress(float mouseX, float mouseY);

            ////////////////////////////////////////////////////////////////////
            //  Handle window mouse release event                             //
            ////////////////////////////////////////////////////////////////////
            bool mouseRelease(float mouseX, float mouseY);

            ////////////////////////////////////////////////////////////////////
            //  Handle window mouse move event                                //
            ////////////////////////////////////////////////////////////////////
            bool mouseMove(float mouseX, float mouseY);


            ////////////////////////////////////////////////////////////////////
            //  Render window                                                 //
            ////////////////////////////////////////////////////////////////////
            void render(Renderer& renderer);


        private:
            ////////////////////////////////////////////////////////////////////
            //  Clamp window size                                             //
            ////////////////////////////////////////////////////////////////////
            void clampWindowSize();


        private:
            ////////////////////////////////////////////////////////////////////
            //  GUIWindow private copy constructor : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            GUIWindow(const GUIWindow&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  GUIWindow private copy operator : Not copyable                //
            ////////////////////////////////////////////////////////////////////
            GUIWindow& operator=(const GUIWindow&) = delete;


        private:
            Texture*            m_texture;          // Window texture pointer
            Vector4             m_color;            // Window color
            float               m_uvFactor;         // Ninepatch UV factor

            bool                m_movable;          // Window movable state
            bool                m_resizable;        // Window resizable state

            Vector2             m_minSize;          // Window minimum size
            Vector2             m_maxSize;          // Window maximum size
            float               m_topBarSize;       // Window top bar size
            float               m_resizeBarSize;    // Window resize bar size

            bool                m_grabWindow;       // Window grabbing state
            bool                m_grabTop;          // Top grabbing state
            bool                m_grabBottom;       // Bottom grabbing state
            bool                m_grabLeft;         // Left grabbing state
            bool                m_grabRight;        // Right grabbing state
            Vector2             m_grabVector;       // Window grabbing vector
    };


#endif // VOS_RENDERER_GUI_GUIWINDOW_HEADER
