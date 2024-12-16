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
//     Softwares/TopDown/TopDownPlayer.h : TopDown player management          //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_SOFTWARES_TOPDOWN_TOPDOWNPLAYER_HEADER
#define VOS_SOFTWARES_TOPDOWN_TOPDOWNPLAYER_HEADER

    #include "../../System/System.h"
    #include "../../System/SysEvent.h"
    #include "../../System/SysMouse.h"
    #include "../../System/SysKeys.h"
    #include "../../System/SysMutex.h"

    #include "../../Math/Math.h"
    #include "../../Math/Vector2i.h"
    #include "../../Math/Transform2.h"

    #include "../../Renderer/Renderer.h"
    #include "../../Renderer/Shapes/RectangleShape.h"
    #include "../../Renderer/Shapes/EllipseShape.h"

    #include "../../Physics/Physics.h"
    #include "../../Physics/PhysicsTransform2.h"
    #include "../../Physics/Collision2.h"
    #include "../../Physics/MatrixStream2.h"
    #include "../../Physics/BoundingSurfaces/BoundingCircle.h"
    #include "../../Physics/BoundingSurfaces/BoundingAlignRect.h"
    #include "../../Physics/BoundingSurfaces/BoundingRect.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  TopDownPlayer class definition                                        //
    ////////////////////////////////////////////////////////////////////////////
    class TopDownPlayer : public Transform2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  TopDownPlayer default constructor                             //
            ////////////////////////////////////////////////////////////////////
            TopDownPlayer();

            ////////////////////////////////////////////////////////////////////
            //  TopDownPlayer virtual destructor                              //
            ////////////////////////////////////////////////////////////////////
            virtual ~TopDownPlayer();


            ////////////////////////////////////////////////////////////////////
            //  Init top down player                                          //
            //  return : True if top down player is ready, false otherwise    //
            ////////////////////////////////////////////////////////////////////
            bool init();


            ////////////////////////////////////////////////////////////////////
            //  Precompute top down player physics (thread sync)              //
            ////////////////////////////////////////////////////////////////////
            void prephysics();

            ////////////////////////////////////////////////////////////////////
            //  Compute top down player physics (threaded)                    //
            ////////////////////////////////////////////////////////////////////
            void physics();

            ////////////////////////////////////////////////////////////////////
            //  Precompute top down player renderer interpolations            //
            ////////////////////////////////////////////////////////////////////
            void precompute(float physicstime);

            ////////////////////////////////////////////////////////////////////
            //  Render top down player                                        //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  TopDownPlayer private copy constructor : Not copyable         //
            ////////////////////////////////////////////////////////////////////
            TopDownPlayer(const TopDownPlayer&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  TopDownPlayer private copy operator : Not copyable            //
            ////////////////////////////////////////////////////////////////////
            TopDownPlayer& operator=(const TopDownPlayer&) = delete;


        private:
            PhysicsTransform2       m_transforms;       // Player transforms
            Vector2i                m_speed;            // Player speed
            BoundingAlignRect       m_bounding;         // Bounding align rect

            RectangleShape          m_rectangle;        // Rectangle shape
            EllipseShape            m_ellipse;          // Ellipse shape

            int32_t                 m_chunkX;           // Chunk X
            int32_t                 m_chunkY;           // Chunk Y
    };


#endif // VOS_SOFTWARES_TOPDOWN_TOPDOWNPLAYER_HEADER
