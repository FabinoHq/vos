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
//     Physics/BoundingCircle.h : Bounding Circle management                  //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_PHYSICS_BOUNDINGCIRCLE_HEADER
#define VOS_PHYSICS_BOUNDINGCIRCLE_HEADER

    #include "../System/System.h"
    #include "../Math/Math.h"
    #include "../Math/Vector2i.h"

    #include "Physics.h"
    #include "Collision2.h"
    #include "MatrixChunk2.h"

    #include <cstdint>


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
                int64_t circleRadius, int64_t circleAngle = 0);

            ////////////////////////////////////////////////////////////////////
            //  BoundingCircle destructor                                     //
            ////////////////////////////////////////////////////////////////////
            ~BoundingCircle();


            ////////////////////////////////////////////////////////////////////
            //  Set bounding circle position radius and angle                 //
            ////////////////////////////////////////////////////////////////////
            void set(const Vector2i& circlePosition,
                int64_t circleRadius, int64_t circleAngle = 0);

            ////////////////////////////////////////////////////////////////////
            //  Set bounding circle position                                  //
            ////////////////////////////////////////////////////////////////////
            inline void setPosition(const Vector2i& circlePosition)
            {
                position.vec[0] = circlePosition.vec[0];
                position.vec[1] = circlePosition.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding circle position                                  //
            ////////////////////////////////////////////////////////////////////
            inline void setPosition(int64_t positionX, int64_t positionY)
            {
                position.vec[0] = positionX;
                position.vec[1] = positionY;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding circle X position                                //
            ////////////////////////////////////////////////////////////////////
            inline void setPositionX(int64_t positionX)
            {
                position.vec[0] = positionX;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding circle Y position                                //
            ////////////////////////////////////////////////////////////////////
            inline void setPositionY(int64_t positionY)
            {
                position.vec[1] = positionY;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding circle radius                                    //
            ////////////////////////////////////////////////////////////////////
            inline void setRadius(int64_t circleRadius)
            {
                radius = Math::max(circleRadius, PhysicsMinEntityHalfSize);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding circle angle                                     //
            ////////////////////////////////////////////////////////////////////
            inline void setAngle(int64_t circleAngle)
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
            //  Collide bounding circle with matrix chunk 2                   //
            ////////////////////////////////////////////////////////////////////
            bool collideMatrix2(const MatrixChunk2& matrixChunk2);

            ////////////////////////////////////////////////////////////////////
            //  Collide bounding circle with matrix chunk 2                   //
            ////////////////////////////////////////////////////////////////////
            bool collideMatrix2(const MatrixChunk2& matrixChunk2,
                const Vector2i& offset, Collision2& collision);


            ////////////////////////////////////////////////////////////////////
            //  BoundingCircle affectation operator                           //
            ////////////////////////////////////////////////////////////////////
            BoundingCircle& operator=(const BoundingCircle& boundingCircle);


        public:
            Vector2i    position;   // Bounding circle position
            int64_t     radius;     // Bounding circle radius
            int64_t     angle;      // Bounding circle angle
    };


#endif // VOS_PHYSICS_BOUNDINGCIRCLE_HEADER
