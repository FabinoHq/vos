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
//     Vos.h : VOS Main class management                                      //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_VOS_HEADER
#define VOS_VOS_HEADER

    #include "System/System.h"
    #include "System/SysMessage.h"
    #include "System/SysMemory.h"
    #include "System/SysWindow.h"
    #include "System/SysClock.h"
    #include "System/SysSleep.h"

    #include "Renderer/Renderer.h"
    #include "Renderer/Texture.h"
    #include "Renderer/CubeMap.h"
    #include "Renderer/View.h"
    #include "Renderer/Camera.h"
    #include "Renderer/FreeFlyCam.h"
    #include "Renderer/OrbitalCam.h"
    #include "Renderer/Sprite.h"
    #include "Renderer/ProcSprite.h"
    #include "Renderer/SkyBox.h"

    #include "Renderer/Shapes/RectangleShape.h"
    #include "Renderer/Shapes/EllipseShape.h"
    #include "Renderer/Shapes/CuboidShape.h"

    #include "Renderer/GUI/GUIPxText.h"
    #include "Renderer/GUI/GUIWindow.h"

    #include "Renderer/StaticMesh.h"
    #include "Renderer/HeightMapChunk.h"

    #include "Images/Embedded/PxFont.h"
    #include "Images/Embedded/Window.h"
    #include "Images/BMPFile.h"
    #include "Images/PNGFile.h"

    #include "Physics/Physics.h"
    #include "Physics/Collision2.h"
    #include "Physics/BoundingCircle.h"

    #include "Event.h"

    #include <cstddef>
    #include <cstdint>
    #include <new>


    ////////////////////////////////////////////////////////////////////////////
    //  VOS main class definition                                             //
    ////////////////////////////////////////////////////////////////////////////
    class Vos
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Vos default constructor                                       //
            ////////////////////////////////////////////////////////////////////
            Vos();

            ////////////////////////////////////////////////////////////////////
            //  Vos destructor                                                //
            ////////////////////////////////////////////////////////////////////
            ~Vos();


            ////////////////////////////////////////////////////////////////////
            //  Launch VOS                                                    //
            //  return : True if VOS successfully started, false otherwise    //
            ////////////////////////////////////////////////////////////////////
            bool launch();

            ////////////////////////////////////////////////////////////////////
            //  Run VOS                                                       //
            ////////////////////////////////////////////////////////////////////
            void run();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Vos private copy constructor : Not copyable                   //
            ////////////////////////////////////////////////////////////////////
            Vos(const Vos&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Vos private copy operator : Not copyable                      //
            ////////////////////////////////////////////////////////////////////
            Vos& operator=(const Vos&) = delete;

        private:
            bool            m_running;          // VOS running state
            SysWindow       m_window;           // VOS main window
            Renderer        m_renderer;         // VOS renderer
            SysClock        m_clock;            // VOS clock

            View            m_view;             // View
            Camera          m_camera;           // Camera
            FreeFlyCam      m_freeflycam;       // Freefly camera
            OrbitalCam      m_orbitalcam;       // Orbital camera

            CubeMap         m_cubemap;          // CubeMap
            SkyBox          m_skybox;           // SkyBox

            ProcSprite      m_procSprite;       // Procedural sprite
            RectangleShape  m_rectanle;         // Rectangle shape
            EllipseShape    m_ellipse;          // Ellipse shape
            CuboidShape     m_cuboid;           // Cuboid shape

            Texture         m_pxFontTexture;    // Pixel font texture
            GUIPxText       m_pxText;           // Test pixel text

            Texture         m_windowTexture;    // GUI Window texture
            GUIWindow       m_guiWindow;        // GUI Window

            Texture         m_testTexture;      // Test texture
            StaticMesh      m_staticMesh;       // Static mesh

            HeightMapChunk  m_heightMapChunk;   // HeightMap chunk

            BoundingCircle  m_boundingCircle;   // Bounding circle
            BoundingCircle  m_boundingCircle2;  // Bounding circle 2

            float           m_mouseX;           // Mouse X position
            float           m_mouseY;           // Mouse Y position
    };


#endif // VOS_VOS_HEADER
