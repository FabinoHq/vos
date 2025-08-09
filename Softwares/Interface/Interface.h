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
//     Softwares/Interface/Interface.h : Interface class management           //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_SOFTWARES_INTERFACE_INTERFACE_HEADER
#define VOS_SOFTWARES_INTERFACE_INTERFACE_HEADER

    #include "../../System/System.h"
    #include "../../System/SysEvent.h"
    #include "../../System/SysMouse.h"
    #include "../../System/SysKeys.h"

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

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  Interface main class definition                                       //
    ////////////////////////////////////////////////////////////////////////////
    class Interface
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Interface default constructor                                 //
            ////////////////////////////////////////////////////////////////////
            Interface();

            ////////////////////////////////////////////////////////////////////
            //  Interface destructor                                          //
            ////////////////////////////////////////////////////////////////////
            ~Interface();


            ////////////////////////////////////////////////////////////////////
            //  Init interface                                                //
            //  return : True if interface is ready, false otherwise          //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Destroy interface                                             //
            ////////////////////////////////////////////////////////////////////
            void destroy();


            ////////////////////////////////////////////////////////////////////
            //  Compute interface events                                      //
            ////////////////////////////////////////////////////////////////////
            void events(SysEvent& event);

            ////////////////////////////////////////////////////////////////////
            //  Compute interface logic                                       //
            ////////////////////////////////////////////////////////////////////
            void compute(float frametime);

            ////////////////////////////////////////////////////////////////////
            //  Render interface                                              //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Interface private copy constructor : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            Interface(const Interface&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Interface private copy operator : Not copyable                //
            ////////////////////////////////////////////////////////////////////
            Interface& operator=(const Interface&) = delete;


        private:
            BackRenderer        m_backRenderer;         // Back renderer

            View                m_view;                 // View

            Sprite              m_sprite;               // Sprite
            ProcSprite          m_procSprite;           // Procedural sprite
            RectangleShape      m_rectangle;            // Rectangle shape
            EllipseShape        m_ellipse;              // Ellipse shape

            GUICursor           m_cursor;               // GUI Cursor
            GUIWindow           m_guiWindow;            // GUI Window
            GUIPxText           m_pxText;               // GUI pixel text
            GUIButton           m_button;               // GUI button
            GUIToggleButton     m_toggleButton;         // GUI toggle button
            GUIProgressBar      m_progressBar;          // GUI progress bar
    };


    ////////////////////////////////////////////////////////////////////////////
    //  Interface global instance                                             //
    ////////////////////////////////////////////////////////////////////////////
    extern Interface GInterface;


#endif // VOS_SOFTWARES_INTERFACE_INTERFACE_HEADER
