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
//     Softwares/TopDown/TopDown.h : TopDown class management                 //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_SOFTWARES_TOPDOWN_TOPDOWN_HEADER
#define VOS_SOFTWARES_TOPDOWN_TOPDOWN_HEADER

    #include "../../System/System.h"
    #include "../../System/SysEvent.h"
    #include "../../System/SysMouse.h"

    #include "../../Renderer/Renderer.h"
    #include "../../Renderer/BackRenderer.h"
    #include "../../Renderer/View.h"
    #include "../../Renderer/Sprite.h"
    #include "../../Renderer/ProcSprite.h"

    #include "../../Resources/Resources.h"
    #include "../../Renderer/GUI/GUICursor.h"
    #include "../../Renderer/GUI/GUIWindow.h"
    #include "../../Renderer/GUI/GUIPxText.h"
    #include "../../Renderer/GUI/GUIButton.h"
    #include "../../Renderer/GUI/GUIToggleButton.h"
    #include "../../Renderer/GUI/GUIProgressBar.h"

    #include "../../Renderer/Shapes/RectangleShape.h"
    #include "../../Renderer/Shapes/EllipseShape.h"

    #include "../../Physics/Physics.h"
    #include "../../Physics/Collision2.h"
    #include "../../Physics/BoundingCircle.h"
    #include "../../Physics/BoundingRect.h"


    ////////////////////////////////////////////////////////////////////////////
    //  TopDown main class definition                                         //
    ////////////////////////////////////////////////////////////////////////////
    class TopDown
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  TopDown default constructor                                   //
            ////////////////////////////////////////////////////////////////////
            TopDown();

            ////////////////////////////////////////////////////////////////////
            //  TopDown destructor                                            //
            ////////////////////////////////////////////////////////////////////
            ~TopDown();


            ////////////////////////////////////////////////////////////////////
            //  Init top down game                                            //
            //  return : True if top down game is ready, false otherwise      //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Destroy top down game                                         //
            ////////////////////////////////////////////////////////////////////
            void destroy();


            ////////////////////////////////////////////////////////////////////
            //  Compute top down game events                                  //
            ////////////////////////////////////////////////////////////////////
            void events(Event& event);

            ////////////////////////////////////////////////////////////////////
            //  Compute top down game logic                                   //
            ////////////////////////////////////////////////////////////////////
            void compute(float frametime);

            ////////////////////////////////////////////////////////////////////
            //  Render top down game                                          //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  TopDown private copy constructor : Not copyable               //
            ////////////////////////////////////////////////////////////////////
            TopDown(const TopDown&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  TopDown private copy operator : Not copyable                  //
            ////////////////////////////////////////////////////////////////////
            TopDown& operator=(const TopDown&) = delete;


        private:
            BackRenderer    m_backRenderer;     // Back renderer
            View            m_view;             // View

            Sprite          m_sprite;           // Sprite
            ProcSprite      m_procSprite;       // Procedural sprite
            RectangleShape  m_rectangle;        // Rectangle shape
            EllipseShape    m_ellipse;          // Ellipse shape

            GUICursor       m_cursor;           // GUI Cursor
            GUIWindow       m_guiWindow;        // GUI Window
            GUIPxText       m_pxText;           // GUI pixel text
            GUIButton       m_button;           // GUI button
            GUIToggleButton m_toggleButton;     // GUI toggle button
            GUIProgressBar  m_progressBar;      // GUI progress bar

            BoundingCircle  m_boundingCircle;   // Bounding circle
            BoundingCircle  m_boundingCircle2;  // Bounding circle 2
            BoundingRect    m_boundingRect;     // Bounding rect
            BoundingRect   m_boundingRect2;     // Bounding rect 2
            Collision2      m_collide;          // Collision

            bool            m_spaceReleased;    // Space released event
    };


#endif // VOS_SOFTWARES_TOPDOWN_TOPDOWN_HEADER
