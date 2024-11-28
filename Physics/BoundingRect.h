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
//     Physics/BoundingRect.h : Bounding Rectangle management                 //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_PHYSICS_BOUNDINGRECT_HEADER
#define VOS_PHYSICS_BOUNDINGRECT_HEADER

    #include "../System/System.h"
    #include "../Math/Math.h"
    #include "../Math/Vector2i.h"

    #include "Physics.h"
    #include "Collision2.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  BoundingRect class definition                                         //
    ////////////////////////////////////////////////////////////////////////////
    class BoundingRect
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  BoundingRect default constructor                              //
            ////////////////////////////////////////////////////////////////////
            BoundingRect();

            ////////////////////////////////////////////////////////////////////
            //  BoundingRect copy constructor                                 //
            ////////////////////////////////////////////////////////////////////
            BoundingRect(const BoundingRect& boundingRect);

            ////////////////////////////////////////////////////////////////////
            //  BoundingRect position size and angle constructor              //
            ////////////////////////////////////////////////////////////////////
            BoundingRect(const Vector2i& rectPosition,
                const Vector2i& rectSize, int32_t rectAngle = 0);

            ////////////////////////////////////////////////////////////////////
            //  BoundingRect destructor                                       //
            ////////////////////////////////////////////////////////////////////
            ~BoundingRect();


            ////////////////////////////////////////////////////////////////////
            //  Set bounding rect position size and angle                     //
            ////////////////////////////////////////////////////////////////////
            void set(const Vector2i& rectPosition,
                const Vector2i& rectSize, int32_t rectAngle = 0);

            ////////////////////////////////////////////////////////////////////
            //  Set bounding rect position                                    //
            ////////////////////////////////////////////////////////////////////
            inline void setPosition(const Vector2i& rectPosition)
            {
                position.vec[0] = rectPosition.vec[0];
                position.vec[1] = rectPosition.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding rect position                                    //
            ////////////////////////////////////////////////////////////////////
            inline void setPosition(int32_t x, int32_t y)
            {
                position.vec[0] = x;
                position.vec[1] = y;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding rect X position                                  //
            ////////////////////////////////////////////////////////////////////
            inline void setX(int32_t x)
            {
                position.vec[0] = x;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding rect Y position                                  //
            ////////////////////////////////////////////////////////////////////
            inline void setY(int32_t y)
            {
                position.vec[1] = y;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding rect size                                        //
            ////////////////////////////////////////////////////////////////////
            inline void setSize(Vector2i rectSize)
            {
                size.vec[0] = Math::max(
                    rectSize.vec[0], PhysicsMinEntityHalfSize
                );
                size.vec[1] = Math::max(
                    rectSize.vec[1], PhysicsMinEntityHalfSize
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding rect size                                        //
            ////////////////////////////////////////////////////////////////////
            inline void setSize(int32_t width, int32_t height)
            {
                size.vec[0] = Math::max(width, PhysicsMinEntityHalfSize);
                size.vec[1] = Math::max(height, PhysicsMinEntityHalfSize);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding rect width                                       //
            ////////////////////////////////////////////////////////////////////
            inline void setWidth(int32_t rectWidth)
            {
                size.vec[0] = Math::max(rectWidth, PhysicsMinEntityHalfSize);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding rect height                                      //
            ////////////////////////////////////////////////////////////////////
            inline void setHeight(int32_t rectHeight)
            {
                size.vec[1] = Math::max(rectHeight, PhysicsMinEntityHalfSize);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding rect height                                      //
            ////////////////////////////////////////////////////////////////////
            inline void setAngle(int32_t rectAngle)
            {
                angle = (rectAngle % Math::TwoPiInt);
            }


            ////////////////////////////////////////////////////////////////////
            //  Collide bounding rect with bounding rect                      //
            ////////////////////////////////////////////////////////////////////
            bool collideRect(const BoundingRect& boundingRect);

            ////////////////////////////////////////////////////////////////////
            //  Collide bounding rect with bounding rect                      //
            ////////////////////////////////////////////////////////////////////
            bool collideRect(const BoundingRect& boundingRect,
                const Vector2i& offset, Collision2& collision);


            ////////////////////////////////////////////////////////////////////
            //  Get bounding rect position                                    //
            ////////////////////////////////////////////////////////////////////
            inline Vector2i getPosition() const
            {
                return position;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get bounding rect X position                                  //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getX() const
            {
                return position.vec[0];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get bounding rect Y position                                  //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getY() const
            {
                return position.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get bounding rect size                                        //
            ////////////////////////////////////////////////////////////////////
            inline Vector2i getSize() const
            {
                return size;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get bounding rect width                                       //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getWidth() const
            {
                return size.vec[0];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get bounding rect height                                      //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getHeight() const
            {
                return size.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get bounding rect angle                                       //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getAngle() const
            {
                return angle;
            }


            ////////////////////////////////////////////////////////////////////
            //  BoundingRect affectation operator                             //
            ////////////////////////////////////////////////////////////////////
            BoundingRect& operator=(const BoundingRect& boundingRect);


        public:
            Vector2i    position;   // Bounding rectangle position
            Vector2i    size;       // Bounding rectangle size
            int32_t     angle;      // Bounding rectangle angle
    };


#endif // VOS_PHYSICS_BOUNDINGRECT_HEADER
