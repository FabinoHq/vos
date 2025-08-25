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
//     Softwares/Isometric3D/Isometric3D.h : Isometric3D class management     //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_SOFTWARES_ISOMETRIC3D_ISOMETRIC3D_HEADER
#define VOS_SOFTWARES_ISOMETRIC3D_ISOMETRIC3D_HEADER

    #include "../../System/System.h"
    #include "../../System/SysEvent.h"
    #include "../../System/SysMouse.h"
    #include "../../System/SysKeys.h"

    #include "../../Renderer/Renderer.h"
    #include "../../Renderer/BackRenderer.h"
    #include "../../Renderer/Camera.h"
    #include "../../Renderer/Plane.h"

    #include "../../Resources/Resources.h"
    #include "../../Renderer/GUI/GUICursor.h"
    #include "../../Renderer/GUI/GUIPxText.h"

    #include "../../Renderer/TileMap/IsoMapStream.h"

    #include "Isometric3DPlayer.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  Isometric3D main class definition                                     //
    ////////////////////////////////////////////////////////////////////////////
    class Isometric3D
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Isometric3D default constructor                               //
            ////////////////////////////////////////////////////////////////////
            Isometric3D();

            ////////////////////////////////////////////////////////////////////
            //  Isometric3D destructor                                        //
            ////////////////////////////////////////////////////////////////////
            ~Isometric3D();


            ////////////////////////////////////////////////////////////////////
            //  Init isometric 3D game                                        //
            //  return : True if isometric 3D game is ready, false otherwise  //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Destroy isometric 3D game                                     //
            ////////////////////////////////////////////////////////////////////
            void destroy();


            ////////////////////////////////////////////////////////////////////
            //  Compute isometric 3D game events                              //
            ////////////////////////////////////////////////////////////////////
            void events(SysEvent& event);

            ////////////////////////////////////////////////////////////////////
            //  Precompute isometric 3D game physics (thread sync)            //
            ////////////////////////////////////////////////////////////////////
            void prephysics();

            ////////////////////////////////////////////////////////////////////
            //  Compute isometric 3D game warp                                //
            ////////////////////////////////////////////////////////////////////
            Vector2i warp();

            ////////////////////////////////////////////////////////////////////
            //  Compute isometric 3D game physics (threaded)                  //
            ////////////////////////////////////////////////////////////////////
            void physics();

            ////////////////////////////////////////////////////////////////////
            //  Precompute isometric 3D game renderer interpolations          //
            ////////////////////////////////////////////////////////////////////
            void precompute(float physicstime);

            ////////////////////////////////////////////////////////////////////
            //  Compute isometric 3D game logic                               //
            ////////////////////////////////////////////////////////////////////
            void compute(float frametime);

            ////////////////////////////////////////////////////////////////////
            //  Render isometric 3D game                                      //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Isometric3D private copy constructor : Not copyable           //
            ////////////////////////////////////////////////////////////////////
            Isometric3D(const Isometric3D&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Isometric3D private copy operator : Not copyable              //
            ////////////////////////////////////////////////////////////////////
            Isometric3D& operator=(const Isometric3D&) = delete;


        private:
            BackRenderer        m_backRenderer;         // Back renderer

            Camera              m_camera;               // Camera

            Plane               m_plane;                // Plane billboard

            GUICursor           m_cursor;               // GUI Cursor
            GUIPxText           m_pxText;               // GUI pixel text

            bool                m_chunkWarp;            // Chunk warp
            int32_t             m_chunkX;               // Chunk X
            int32_t             m_chunkY;               // Chunk Y
            IsoMapStream        m_isomap;               // Isomap
            Isometric3DPlayer   m_player;               // Player
    };


    ////////////////////////////////////////////////////////////////////////////
    //  Isometric3D global instance                                           //
    ////////////////////////////////////////////////////////////////////////////
    extern Isometric3D GIsometric3D;


#endif // VOS_SOFTWARES_ISOMETRIC3D_ISOMETRIC3D_HEADER
