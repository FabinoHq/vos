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
    #include "../../Math/Vector2.h"

    #include "../../Renderer/Renderer.h"
    #include "../../Renderer/Shapes/EllipseShape.h"

    #include "../../Physics/Physics.h"
    #include "../../Physics/Collision2.h"
    #include "../../Physics/BoundingCircle.h"
    #include "../../Physics/BoundingRect.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  TopDownPlayerPos structure                                            //
    ////////////////////////////////////////////////////////////////////////////
    struct TopDownPlayerPos
    {
        Vector2     pos;
        Vector2     prevPos;
        float       angle;
        float       prevAngle;
    };


    ////////////////////////////////////////////////////////////////////////////
    //  TopDownPlayer class definition                                        //
    ////////////////////////////////////////////////////////////////////////////
    class TopDownPlayer
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  TopDownPlayer default constructor                             //
            ////////////////////////////////////////////////////////////////////
            TopDownPlayer();

            ////////////////////////////////////////////////////////////////////
            //  TopDownPlayer destructor                                      //
            ////////////////////////////////////////////////////////////////////
            ~TopDownPlayer();


            ////////////////////////////////////////////////////////////////////
            //  Init top down player                                          //
            //  return : True if top down player is ready, false otherwise    //
            ////////////////////////////////////////////////////////////////////
            bool init();


            ////////////////////////////////////////////////////////////////////
            //  Get player position                                           //
            ////////////////////////////////////////////////////////////////////
            inline Vector2 getPosition()
            {
                return m_ellipse.getPosition();
            }

            ////////////////////////////////////////////////////////////////////
            //  Get player X position                                         //
            ////////////////////////////////////////////////////////////////////
            inline float getX()
            {
                return m_ellipse.getX();
            }

            ////////////////////////////////////////////////////////////////////
            //  Get player Y position                                         //
            ////////////////////////////////////////////////////////////////////
            inline float getY()
            {
                return m_ellipse.getY();
            }


            ////////////////////////////////////////////////////////////////////
            //  Compute top down player physics (threaded)                    //
            ////////////////////////////////////////////////////////////////////
            void physics();

            ////////////////////////////////////////////////////////////////////
            //  Precompute top down player                                    //
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
            TopDownPlayerPos    m_position;             // Player position
            Vector2i            m_speed;                // Player speed
            BoundingCircle      m_bounding;             // Bounding circle

            EllipseShape        m_ellipse;              // Ellipse shape
    };


#endif // VOS_SOFTWARES_TOPDOWN_TOPDOWNPLAYER_HEADER
