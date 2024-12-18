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
//     Softwares/Isometric/IsometricPlayer.h : Isometric player management    //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_SOFTWARES_ISOMETRIC_ISOMETRICPLAYER_HEADER
#define VOS_SOFTWARES_ISOMETRIC_ISOMETRICPLAYER_HEADER

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

    #include "../../Physics/Physics.h"
    #include "../../Physics/PhysicsTransform2.h"
    #include "../../Physics/Collision2.h"
    #include "../../Physics/MatrixStream2.h"
    #include "../../Physics/BoundingSurfaces/BoundingCircle.h"
    #include "../../Physics/BoundingSurfaces/BoundingAlignRect.h"
    #include "../../Physics/BoundingSurfaces/BoundingRect.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  IsometricPlayer class definition                                      //
    ////////////////////////////////////////////////////////////////////////////
    class IsometricPlayer : public Transform2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  IsometricPlayer default constructor                           //
            ////////////////////////////////////////////////////////////////////
            IsometricPlayer();

            ////////////////////////////////////////////////////////////////////
            //  IsometricPlayer virtual destructor                            //
            ////////////////////////////////////////////////////////////////////
            virtual ~IsometricPlayer();


            ////////////////////////////////////////////////////////////////////
            //  Init isometric player                                         //
            //  return : True if isometric player is ready, false otherwise   //
            ////////////////////////////////////////////////////////////////////
            bool init();


            ////////////////////////////////////////////////////////////////////
            //  Precompute isometric player physics (thread sync)             //
            ////////////////////////////////////////////////////////////////////
            void prephysics(const Vector2i& warpOffset);

            ////////////////////////////////////////////////////////////////////
            //  Compute isometric player physics (threaded)                   //
            ////////////////////////////////////////////////////////////////////
            void physics();

            ////////////////////////////////////////////////////////////////////
            //  Precompute isometric player renderer interpolations           //
            ////////////////////////////////////////////////////////////////////
            void precompute(float physicstime);

            ////////////////////////////////////////////////////////////////////
            //  Render isometric player                                       //
            ////////////////////////////////////////////////////////////////////
            void render();


            ////////////////////////////////////////////////////////////////////
            //  Check if isometric player needs warp                          //
            ////////////////////////////////////////////////////////////////////
            inline bool needWarp()
            {
                return (topWarp() || bottomWarp() || leftWarp() || rightWarp());
            }

            ////////////////////////////////////////////////////////////////////
            //  Check if isometric player needs top warp                      //
            ////////////////////////////////////////////////////////////////////
            inline bool topWarp()
            {
                return (m_bounding.position.vec[1] > MatrixChunk2TopWarp);
            }

            ////////////////////////////////////////////////////////////////////
            //  Check if isometric player needs bottom warp                   //
            ////////////////////////////////////////////////////////////////////
            inline bool bottomWarp()
            {
                return (m_bounding.position.vec[1] < MatrixChunk2BottomWarp);
            }

            ////////////////////////////////////////////////////////////////////
            //  Check if isometric player needs left warp                     //
            ////////////////////////////////////////////////////////////////////
            inline bool leftWarp()
            {
                return (m_bounding.position.vec[0] < MatrixChunk2LeftWarp);
            }

            ////////////////////////////////////////////////////////////////////
            //  Check if isometric player needs right warp                    //
            ////////////////////////////////////////////////////////////////////
            inline bool rightWarp()
            {
                return (m_bounding.position.vec[0] > MatrixChunk2RightWarp);
            }


        private:
            ////////////////////////////////////////////////////////////////////
            //  IsometricPlayer private copy constructor : Not copyable       //
            ////////////////////////////////////////////////////////////////////
            IsometricPlayer(const IsometricPlayer&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  IsometricPlayer private copy operator : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            IsometricPlayer& operator=(const IsometricPlayer&) = delete;


        private:
            PhysicsTransform2       m_transforms;       // Player transforms
            Vector2i                m_speed;            // Player speed
            BoundingAlignRect       m_bounding;         // Bounding align rect

            RectangleShape          m_rectangle;        // Rectangle shape
    };


#endif // VOS_SOFTWARES_ISOMETRIC_ISOMETRICPLAYER_HEADER
