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
//     Physics/BoundingSurfaces/BoundingAlignRect.h : Aligned Rectangle       //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_PHYSICS_BOUNDINGSURFACES_BOUNDINGALIGNRECT_HEADER
#define VOS_PHYSICS_BOUNDINGSURFACES_BOUNDINGALIGNRECT_HEADER

    #include "../../System/System.h"
    #include "../../Math/Math.h"
    #include "../../Math/Vector2i.h"

    #include "../Physics.h"
    #include "../Collision2.h"
    #include "../MatrixChunk2.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  BoundingAlignRect class definition                                    //
    ////////////////////////////////////////////////////////////////////////////
    class BoundingAlignRect
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  BoundingAlignRect default constructor                         //
            ////////////////////////////////////////////////////////////////////
            BoundingAlignRect();

            ////////////////////////////////////////////////////////////////////
            //  BoundingAlignRect copy constructor                            //
            ////////////////////////////////////////////////////////////////////
            BoundingAlignRect(const BoundingAlignRect& boundingAlignRect);

            ////////////////////////////////////////////////////////////////////
            //  BoundingAlignRect position and half size constructor          //
            ////////////////////////////////////////////////////////////////////
            BoundingAlignRect(const Vector2i& rectPosition,
                const Vector2i& rectHalfSize);

            ////////////////////////////////////////////////////////////////////
            //  BoundingAlignRect destructor                                  //
            ////////////////////////////////////////////////////////////////////
            ~BoundingAlignRect();


            ////////////////////////////////////////////////////////////////////
            //  Set bounding align rect position and half size                //
            ////////////////////////////////////////////////////////////////////
            void set(const Vector2i& rectPosition,
                const Vector2i& rectHalfSize);

            ////////////////////////////////////////////////////////////////////
            //  Set bounding align rect position                              //
            ////////////////////////////////////////////////////////////////////
            inline void setPosition(const Vector2i& rectPosition)
            {
                position.vec[0] = rectPosition.vec[0];
                position.vec[1] = rectPosition.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding align rect position                              //
            ////////////////////////////////////////////////////////////////////
            inline void setPosition(int32_t x, int32_t y)
            {
                position.vec[0] = x;
                position.vec[1] = y;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding align rect X position                            //
            ////////////////////////////////////////////////////////////////////
            inline void setX(int32_t x)
            {
                position.vec[0] = x;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding align rect Y position                            //
            ////////////////////////////////////////////////////////////////////
            inline void setY(int32_t y)
            {
                position.vec[1] = y;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding align rect half size                             //
            ////////////////////////////////////////////////////////////////////
            inline void setHalfSize(Vector2i rectHalfSize)
            {
                halfSize.vec[0] = Math::max(
                    rectHalfSize.vec[0], PhysicsMinEntityHalfSize
                );
                halfSize.vec[1] = Math::max(
                    rectHalfSize.vec[1], PhysicsMinEntityHalfSize
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding align rect half size                             //
            ////////////////////////////////////////////////////////////////////
            inline void setHalfSize(int32_t halfWidth, int32_t halfHeight)
            {
                halfSize.vec[0] = Math::max(
                    halfWidth, PhysicsMinEntityHalfSize
                );
                halfSize.vec[1] = Math::max(
                    halfHeight, PhysicsMinEntityHalfSize
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding align rect size                                  //
            ////////////////////////////////////////////////////////////////////
            inline void setSize(Vector2i rectSize)
            {
                halfSize.vec[0] = Math::max(
                    (rectSize.vec[0] >> 1), PhysicsMinEntityHalfSize
                );
                halfSize.vec[1] = Math::max(
                    (rectSize.vec[1] >> 1), PhysicsMinEntityHalfSize
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding align rect size                                  //
            ////////////////////////////////////////////////////////////////////
            inline void setSize(int32_t width, int32_t height)
            {
                halfSize.vec[0] = Math::max(
                    (width >> 1), PhysicsMinEntityHalfSize
                );
                halfSize.vec[1] = Math::max(
                    (height >> 1), PhysicsMinEntityHalfSize
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding align rect half width                            //
            ////////////////////////////////////////////////////////////////////
            inline void setHalfWidth(int32_t halfWidth)
            {
                halfSize.vec[0] = Math::max(
                    halfWidth, PhysicsMinEntityHalfSize
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding align rect width                                 //
            ////////////////////////////////////////////////////////////////////
            inline void setWidth(int32_t width)
            {
                halfSize.vec[0] = Math::max(
                    (width >> 1), PhysicsMinEntityHalfSize
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding align rect half height                           //
            ////////////////////////////////////////////////////////////////////
            inline void setHalfHeight(int32_t halfHeight)
            {
                halfSize.vec[1] = Math::max(
                    halfHeight, PhysicsMinEntityHalfSize
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Set bounding align rect height                                //
            ////////////////////////////////////////////////////////////////////
            inline void setHeight(int32_t height)
            {
                halfSize.vec[1] = Math::max(
                    (height >> 1), PhysicsMinEntityHalfSize
                );
            }


            ////////////////////////////////////////////////////////////////////
            //  Collide bounding align rect with bounding align rect          //
            ////////////////////////////////////////////////////////////////////
            bool collideAlignRect(const BoundingAlignRect& boundingAlignRect);

            ////////////////////////////////////////////////////////////////////
            //  Collide bounding align rect with bounding align rect          //
            ////////////////////////////////////////////////////////////////////
            bool collideAlignRect(const BoundingAlignRect& boundingAlignRect,
                const Vector2i& offset, Collision2& collision);


            ////////////////////////////////////////////////////////////////////
            //  Collide bounding align rect with matrix chunk 2               //
            ////////////////////////////////////////////////////////////////////
            bool collideMatrix2(const MatrixChunk2& matrixChunk2);

            ////////////////////////////////////////////////////////////////////
            //  Collide bounding align rect with matrix chunk 2               //
            ////////////////////////////////////////////////////////////////////
            bool collideMatrix2(const MatrixChunk2& matrixChunk2,
                const Vector2i& offset, Collision2& collision);


            ////////////////////////////////////////////////////////////////////
            //  Get bounding align rect position                              //
            ////////////////////////////////////////////////////////////////////
            inline Vector2i getPosition() const
            {
                return position;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get bounding align rect X position                            //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getX() const
            {
                return position.vec[0];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get bounding align rect Y position                            //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getY() const
            {
                return position.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get bounding align rect half size                             //
            ////////////////////////////////////////////////////////////////////
            inline Vector2i getHalfSize() const
            {
                return halfSize;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get bounding align rect size                                  //
            ////////////////////////////////////////////////////////////////////
            inline Vector2i getSize() const
            {
                return Vector2i((halfSize.vec[0] << 1), (halfSize.vec[1] << 1));
            }

            ////////////////////////////////////////////////////////////////////
            //  Get bounding align rect half width                            //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getHalfWidth() const
            {
                return halfSize.vec[0];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get bounding align rect width                                 //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getWidth() const
            {
                return (halfSize.vec[0] << 1);
            }

            ////////////////////////////////////////////////////////////////////
            //  Get bounding align rect half height                           //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getHalfHeight() const
            {
                return halfSize.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get bounding align rect height                                //
            ////////////////////////////////////////////////////////////////////
            inline int32_t getHeight() const
            {
                return (halfSize.vec[1] << 1);
            }


            ////////////////////////////////////////////////////////////////////
            //  BoundingAlignRect affectation operator                        //
            ////////////////////////////////////////////////////////////////////
            BoundingAlignRect& operator=(
                const BoundingAlignRect& boundingAlignRect);


        public:
            Vector2i    position;   // Bounding aligned rectangle position
            Vector2i    halfSize;   // Bounding aligned rectangle half size
    };


#endif // VOS_PHYSICS_BOUNDINGSURFACES_BOUNDINGALIGNRECT_HEADER
