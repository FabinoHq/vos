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
//     Softwares/Isometric/Isometric.h : Isometric class management           //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_SOFTWARES_ISOMETRIC_ISOMETRIC_HEADER
#define VOS_SOFTWARES_ISOMETRIC_ISOMETRIC_HEADER

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

    #include "../../Renderer/Shapes/RectangleShape.h"
    #include "../../Renderer/Shapes/EllipseShape.h"

    #include "../../Renderer/TileMap/IsoMapStream.h"

    #include "IsometricPlayer.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  Isometric main class definition                                       //
    ////////////////////////////////////////////////////////////////////////////
    class Isometric
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Isometric default constructor                                 //
            ////////////////////////////////////////////////////////////////////
            Isometric();

            ////////////////////////////////////////////////////////////////////
            //  Isometric destructor                                          //
            ////////////////////////////////////////////////////////////////////
            ~Isometric();


            ////////////////////////////////////////////////////////////////////
            //  Init isometric game                                           //
            //  return : True if isometric game is ready, false otherwise     //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Destroy isometric game                                        //
            ////////////////////////////////////////////////////////////////////
            void destroy();


            ////////////////////////////////////////////////////////////////////
            //  Compute isometric game events                                 //
            ////////////////////////////////////////////////////////////////////
            void events(SysEvent& event);

            ////////////////////////////////////////////////////////////////////
            //  Precompute isometric game physics (thread sync)               //
            ////////////////////////////////////////////////////////////////////
            void prephysics();

            ////////////////////////////////////////////////////////////////////
            //  Compute isometric game warp                                   //
            ////////////////////////////////////////////////////////////////////
            Vector2i warp();

            ////////////////////////////////////////////////////////////////////
            //  Compute isometric game physics (threaded)                     //
            ////////////////////////////////////////////////////////////////////
            void physics();

            ////////////////////////////////////////////////////////////////////
            //  Precompute isometric game renderer interpolations             //
            ////////////////////////////////////////////////////////////////////
            void precompute(float physicstime);

            ////////////////////////////////////////////////////////////////////
            //  Compute isometric game logic                                  //
            ////////////////////////////////////////////////////////////////////
            void compute(float frametime);

            ////////////////////////////////////////////////////////////////////
            //  Render isometric game                                         //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Isometric private copy constructor : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            Isometric(const Isometric&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Isometric private copy operator : Not copyable                //
            ////////////////////////////////////////////////////////////////////
            Isometric& operator=(const Isometric&) = delete;


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

            bool                m_chunkWarp;            // Chunk warp
            int32_t             m_chunkX;               // Chunk X
            int32_t             m_chunkY;               // Chunk Y
            IsoMapStream        m_isomap;               // Isomap
            IsometricPlayer     m_player;               // Player

            float               m_zoom;                 // Zoom
    };


    ////////////////////////////////////////////////////////////////////////////
    //  Isometric global instance                                             //
    ////////////////////////////////////////////////////////////////////////////
    extern Isometric GIsometric;


#endif // VOS_SOFTWARES_ISOMETRIC_ISOMETRIC_HEADER
