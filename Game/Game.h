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
//     Game/Game.h : Main game class management                               //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_GAME_GAME_HEADER
#define VOS_GAME_GAME_HEADER

    #include "../System/System.h"
    #include "../System/SysEvent.h"

    #include "../Renderer/Renderer.h"
    #include "../Renderer/BackRenderer.h"
    #include "../Renderer/Vulkan/CubeMap.h"
    #include "../Renderer/View.h"
    #include "../Renderer/Camera.h"
    #include "../Renderer/FreeFlyCam.h"
    #include "../Renderer/OrbitalCam.h"
    #include "../Renderer/Sprite.h"
    #include "../Renderer/ProcSprite.h"
    #include "../Renderer/SkyBox.h"

    #include "../Resources/Resources.h"
    #include "../Renderer/GUI/GUICursor.h"
    #include "../Renderer/GUI/GUIWindow.h"
    #include "../Renderer/GUI/GUIPxText.h"

    #include "../Renderer/Shapes/RectangleShape.h"
    #include "../Renderer/Shapes/EllipseShape.h"
    #include "../Renderer/Shapes/CuboidShape.h"

    #include "../Renderer/StaticMesh.h"
    #include "../Renderer/HeightMapChunk.h"
    #include "../Renderer/HeightMapStream.h"

    #include "../Physics/Physics.h"
    #include "../Physics/Collision2.h"
    #include "../Physics/BoundingCircle.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Game main class definition                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Game
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Game default constructor                                      //
            ////////////////////////////////////////////////////////////////////
            Game();

            ////////////////////////////////////////////////////////////////////
            //  Game destructor                                               //
            ////////////////////////////////////////////////////////////////////
            ~Game();


            ////////////////////////////////////////////////////////////////////
            //  Init game                                                     //
            //  return : True if game is ready, false otherwise               //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Destroy game                                                  //
            ////////////////////////////////////////////////////////////////////
            void destroy();


            ////////////////////////////////////////////////////////////////////
            //  Compute game events                                           //
            ////////////////////////////////////////////////////////////////////
            void events(Event& event);

            ////////////////////////////////////////////////////////////////////
            //  Compute game logic                                            //
            ////////////////////////////////////////////////////////////////////
            void compute(float frametime);

            ////////////////////////////////////////////////////////////////////
            //  Render game                                                   //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Game private copy constructor : Not copyable                  //
            ////////////////////////////////////////////////////////////////////
            Game(const Game&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Game private copy operator : Not copyable                     //
            ////////////////////////////////////////////////////////////////////
            Game& operator=(const Game&) = delete;


        private:
            BackRenderer    m_backRenderer;     // Back renderer

            View            m_view;             // View
            Camera          m_camera;           // Camera
            FreeFlyCam      m_freeflycam;       // Freefly camera
            OrbitalCam      m_orbitalcam;       // Orbital camera

            CubeMap         m_cubemap;          // CubeMap
            SkyBox          m_skybox;           // SkyBox

            Sprite          m_sprite;           // Sprite
            ProcSprite      m_procSprite;       // Procedural sprite
            RectangleShape  m_rectanle;         // Rectangle shape
            EllipseShape    m_ellipse;          // Ellipse shape
            CuboidShape     m_cuboid;           // Cuboid shape

            GUICursor       m_cursor;           // GUI Cursor
            GUIWindow       m_guiWindow;        // GUI Window
            GUIPxText       m_pxText;           // GUI pixel text

            StaticMesh      m_staticMesh;       // Static mesh
            HeightMapStream m_heightMapStream;  // HeightMap stream

            BoundingCircle  m_boundingCircle;   // Bounding circle
            BoundingCircle  m_boundingCircle2;  // Bounding circle 2
            Collision2      m_collideCircle;    // Circles collision

            float           m_mouseX;           // Mouse X position
            float           m_mouseY;           // Mouse Y position
            bool            m_spaceReleased;    // Space released event
    };


#endif // VOS_GAME_GAME_HEADER
