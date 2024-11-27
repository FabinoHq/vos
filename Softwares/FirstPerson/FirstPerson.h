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
//     Softwares/FirstPerson/FirstPerson.h : FirstPerson class management     //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_SOFTWARES_FIRSTPERSON_FIRSTPERSON_HEADER
#define VOS_SOFTWARES_FIRSTPERSON_FIRSTPERSON_HEADER

    #include "../../System/System.h"
    #include "../../System/SysEvent.h"
    #include "../../System/SysMouse.h"

    #include "../../Renderer/Renderer.h"
    #include "../../Renderer/BackRenderer.h"
    #include "../../Renderer/View.h"
    #include "../../Renderer/Camera.h"
    #include "../../Renderer/FreeFlyCam.h"
    #include "../../Renderer/OrbitalCam.h"
    #include "../../Renderer/Sprite.h"
    #include "../../Renderer/ProcSprite.h"
    #include "../../Renderer/Plane.h"
    #include "../../Renderer/SkyBox.h"
    #include "../../Renderer/SkyProc.h"
    #include "../../Renderer/WorldLight.h"

    #include "../../Resources/Resources.h"
    #include "../../Renderer/GUI/GUICursor.h"
    #include "../../Renderer/GUI/GUIWindow.h"
    #include "../../Renderer/GUI/GUIPxText.h"
    #include "../../Renderer/GUI/GUIButton.h"
    #include "../../Renderer/GUI/GUIToggleButton.h"
    #include "../../Renderer/GUI/GUIProgressBar.h"

    #include "../../Renderer/Shapes/RectangleShape.h"
    #include "../../Renderer/Shapes/EllipseShape.h"
    #include "../../Renderer/Shapes/CuboidShape.h"

    #include "../../Renderer/StaticMesh.h"
    #include "../../Renderer/HeightMapStream.h"
    #include "../../Renderer/HeightFarStream.h"
    #include "../../Renderer/SeaNearStream.h"
    #include "../../Renderer/SeaFarStream.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  FirstPerson main class definition                                     //
    ////////////////////////////////////////////////////////////////////////////
    class FirstPerson
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  FirstPerson default constructor                               //
            ////////////////////////////////////////////////////////////////////
            FirstPerson();

            ////////////////////////////////////////////////////////////////////
            //  FirstPerson destructor                                        //
            ////////////////////////////////////////////////////////////////////
            ~FirstPerson();


            ////////////////////////////////////////////////////////////////////
            //  Init first person game                                        //
            //  return : True if first person game is ready, false otherwise  //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Destroy first person game                                     //
            ////////////////////////////////////////////////////////////////////
            void destroy();


            ////////////////////////////////////////////////////////////////////
            //  Compute first person game events                              //
            ////////////////////////////////////////////////////////////////////
            void events(SysEvent& event);

            ////////////////////////////////////////////////////////////////////
            //  Compute first person game physics (threaded)                  //
            ////////////////////////////////////////////////////////////////////
            void physics();

            ////////////////////////////////////////////////////////////////////
            //  Precompute person game                                        //
            ////////////////////////////////////////////////////////////////////
            void precompute(float physicstime);

            ////////////////////////////////////////////////////////////////////
            //  Compute first person game logic                               //
            ////////////////////////////////////////////////////////////////////
            void compute(float frametime);

            ////////////////////////////////////////////////////////////////////
            //  Render first person game                                      //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  FirstPerson private copy constructor : Not copyable           //
            ////////////////////////////////////////////////////////////////////
            FirstPerson(const FirstPerson&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  FirstPerson private copy operator : Not copyable              //
            ////////////////////////////////////////////////////////////////////
            FirstPerson& operator=(const FirstPerson&) = delete;


        private:
            BackRenderer    m_backRenderer;     // Back renderer

            View            m_view;             // View
            Camera          m_camera;           // Camera
            FreeFlyCam      m_freeflycam;       // Freefly camera
            FreeFlyCam      m_farflycam;        // Freefly camera far
            OrbitalCam      m_orbitalcam;       // Orbital camera

            SkyBox          m_skybox;           // SkyBox
            SkyProc         m_skyproc;          // Procedural skybox

            Sprite          m_sprite;           // Sprite
            ProcSprite      m_procSprite;       // Procedural sprite
            RectangleShape  m_rectangle;        // Rectangle shape
            EllipseShape    m_ellipse;          // Ellipse shape
            CuboidShape     m_cuboid;           // Cuboid shape
            Plane           m_plane;            // Plane billboard

            GUICursor       m_cursor;           // GUI Cursor
            GUIPxText       m_pxText;           // GUI pixel text

            StaticMesh      m_staticMesh;       // Static mesh
            HeightMapStream m_heightMapStream;  // HeightMap stream
            HeightFarStream m_heightFarStream;  // HeightFar stream
            SeaNearStream   m_seaNearStream;    // SeaNear stream
            SeaFarStream    m_seaFarStream;     // SeaFar stream

            bool            m_spaceReleased;    // Space released event
    };


    ////////////////////////////////////////////////////////////////////////////
    //  FirstPerson global instance                                           //
    ////////////////////////////////////////////////////////////////////////////
    extern FirstPerson GFirstPerson;


#endif // VOS_SOFTWARES_FIRSTPERSON_FIRSTPERSON_HEADER
