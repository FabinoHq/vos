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
//     Physics/BoundingSurfaces/BoundingCircle.h : Bounding Circle            //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_PHYSICS_BOUNDINGSURFACES_BOUNDINGCIRCLE_HEADER
#define VOS_PHYSICS_BOUNDINGSURFACES_BOUNDINGCIRCLE_HEADER

    #include "../../System/System.h"
    #include "../../Math/Math.h"
    #include "../../Math/Vector2i.h"

    #include "../Physics.h"
    #include "../Collision2.h"
    #include "../MatrixChunk2.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  Bounding Surfaces class declaration                                   //
    ////////////////////////////////////////////////////////////////////////////
    class BoundingAlignRect;


    ////////////////////////////////////////////////////////////////////////////
    //  BoundingCircle class definition                                       //
    ////////////////////////////////////////////////////////////////////////////
    class BoundingCircle
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  BoundingCircle default constructor                            //
            ////////////////////////////////////////////////////////////////////
            BoundingCircle();

            ////////////////////////////////////////////////////////////////////
            //  BoundingCircle copy constructor                               //
            ////////////////////////////////////////////////////////////////////
            BoundingCircle(const BoundingCircle& boundingCircle);

            ////////////////////////////////////////////////////////////////////
            //  BoundingCircle position radius and angle constructor          //
            ////////////////////////////////////////////////////////////////////
            BoundingCircle(const Vector2i& circlePosition,
                int32_t circleRadius, int32_t circleAngle = 0);

            ////////////////////////////////////////////////////////////////////
            //  BoundingCircle destructor                                     //
            ////////////////////////////////////////////////////////////////////
            ~BoundingCircle();


            ////////////////////////////////////////////////////////////////////
            //  Set bounding circle position radius and angle                 //
            ////////////////////////////////////////////////////////////////////
            void set(const Vector2i& circlePosition,
                int32_t circleRadius, int32_t circleAngle = 0);

            ////////////////////////////////////////////////////////////////////
            //  Set bounding circle position                                  //
            ////////////////////////////////////////////////////////////////////
            inline void setPosition(const Vector2i& circlePosition)
            {
                position = circlePosition;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding circle position                                  //
            ////////////////////////////////////////////////////////////////////
            inline void setPosition(int32_t x, int32_t y)
            {
                position.vec[0] = x;
                position.vec[1] = y;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding circle X position                                //
            ////////////////////////////////////////////////////////////////////
            inline void setX(int32_t x)
            {
                position.vec[0] = x;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding circle Y position                                //
            ////////////////////////////////////////////////////////////////////
            inline void setY(int32_t y)
            {
                position.vec[1] = y;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding circle radius                                    //
            ////////////////////////////////////////////////////////////////////
            inline void setRadius(int32_t circleRadius)
            {
                radius = Math::max(circleRadius, PhysicsMinEntityHalfSize);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding circle diameter                                  //
            ////////////////////////////////////////////////////////////////////
            inline void setDiameter(int32_t circleDiameter)
            {
                radius = Math::max(
                    (circleDiameter >> 1), PhysicsMinEntityHalfSize
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding circle angle                                     //
            ////////////////////////////////////////////////////////////////////
            inline void setAngle(int32_t circleAngle)
            {
                angle = (circleAngle % Math::TwoPiInt);
            }


            ////////////////////////////////////////////////////////////////////
            //  Collide bounding circle with bounding circle                  //
            ////////////////////////////////////////////////////////////////////
            bool collideCircle(const BoundingCircle& boundingCircle);

            ////////////////////////////////////////////////////////////////////
            //  Collide bounding circle with bounding circle                  //
            ////////////////////////////////////////////////////////////////////
            bool collideCircle(const BoundingCircle& boundingCircle,
                const Vector2i& offset, Collision2& collision);


            ////////////////////////////////////////////////////////////////////
            //  Collide bounding circle with bounding align rect              //
            ////////////////////////////////////////////////////////////////////
            bool collideAlignRect(const BoundingAlignRect& boundingAlignRect);

            ////////////////////////////////////////////////////////////////////
            //  Collide bounding circle with bounding align rect              //
            ////////////////////////////////////////////////////////////////////
            bool collideAlignRect(const BoundingAlignRect& boundingAlignRect,
                const Vector2i& offset, Collision2& collision);


            ////////////////////////////////////////////////////////////////////
            //  Collide bounding circle with matrix chunk 2                   //
            ////////////////////////////////////////////////////////////////////
            bool collideMatrix2(const MatrixChunk2& matrixChunk2);

            ////////////////////////////////////////////////////////////////////
            //  Collide bounding circle with matrix chunk 2                   //
            ////////////////////////////////////////////////////////////////////
            bool collideMatrix2(const MatrixChunk2& matrixChunk2,
                const Vector2i& offset, Collision2& collision);


            ////////////////////////////////////////////////////////////////////
            //  Get bounding circle position                                  //
            ////////////////////////////////////////////////////////////////////
            inline Vector2i getPosition() const
            {
                return position;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get bounding circle X position                                //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getX() const
            {
                return position.vec[0];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get bounding circle Y position                                //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getY() const
            {
                return position.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get bounding circle radius                                    //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getRadius() const
            {
                return radius;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get bounding circle diameter                                  //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getDiameter() const
            {
                return (radius << 1);
            }

            ////////////////////////////////////////////////////////////////////
            //  Get bounding circle angle                                     //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getAngle() const
            {
                return angle;
            }


            ////////////////////////////////////////////////////////////////////
            //  BoundingCircle affectation operator                           //
            ////////////////////////////////////////////////////////////////////
            BoundingCircle& operator=(const BoundingCircle& boundingCircle);


        public:
            Vector2i    position;   // Bounding circle position
            int32_t     radius;     // Bounding circle radius
            int32_t     angle;      // Bounding circle angle
    };


#endif // VOS_PHYSICS_BOUNDINGSURFACES_BOUNDINGCIRCLE_HEADER
