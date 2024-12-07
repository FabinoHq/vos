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
//     Physics/Collision2.h : 2 components collision management               //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_PHYSICS_COLLISION2_HEADER
#define VOS_PHYSICS_COLLISION2_HEADER

    #include "../System/System.h"
    #include "../Math/Math.h"
    #include "../Math/Vector2i.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  Collision2 class definition                                           //
    ////////////////////////////////////////////////////////////////////////////
    class Collision2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Collision2 default constructor                                //
            ////////////////////////////////////////////////////////////////////
            Collision2();

            ////////////////////////////////////////////////////////////////////
            //  Collision2 copy constructor                                   //
            ////////////////////////////////////////////////////////////////////
            Collision2(const Collision2& collision2);

            ////////////////////////////////////////////////////////////////////
            //  Collision2 destructor                                         //
            ////////////////////////////////////////////////////////////////////
            ~Collision2();


            ////////////////////////////////////////////////////////////////////
            //  Reset collision                                               //
            ////////////////////////////////////////////////////////////////////
            void reset();

            ////////////////////////////////////////////////////////////////////
            //  Set collision collide state                                   //
            ////////////////////////////////////////////////////////////////////
            inline void setCollide(bool collisionCollide)
            {
                collide = collisionCollide;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set collision position                                        //
            ////////////////////////////////////////////////////////////////////
            inline void setPosition(const Vector2i& collisionPosition)
            {
                position = collisionPosition;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set collision position                                        //
            ////////////////////////////////////////////////////////////////////
            inline void setPosition(int32_t x, int32_t y)
            {
                position.vec[0] = x;
                position.vec[1] = y;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set collision offset                                          //
            ////////////////////////////////////////////////////////////////////
            inline void setOffset(const Vector2i& collisionOffset)
            {
                offset = collisionOffset;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set collision offset                                          //
            ////////////////////////////////////////////////////////////////////
            inline void setOffset(int32_t offsetX, int32_t offsetY)
            {
                offset.vec[0] = offsetX;
                offset.vec[1] = offsetY;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set collision normal                                          //
            ////////////////////////////////////////////////////////////////////
            inline void setNormal(const Vector2i& collisionNormal)
            {
                normal = collisionNormal;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set collision normal                                          //
            ////////////////////////////////////////////////////////////////////
            inline void setNormal(int32_t normalX, int32_t normalY)
            {
                normal.vec[0] = normalX;
                normal.vec[1] = normalY;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set collision squared length                                  //
            ////////////////////////////////////////////////////////////////////
            inline void setLength(int64_t collisionLength)
            {
                length = collisionLength;
            }


            ////////////////////////////////////////////////////////////////////
            //  Collision2 affectation operator                               //
            ////////////////////////////////////////////////////////////////////
            Collision2& operator=(const Collision2& collision2);


        public:
            bool            collide;        // Collision state
            Vector2i        position;       // Collision position
            Vector2i        offset;         // Collision offset
            Vector2i        normal;         // Collision normal
            int64_t         length;         // Collision squared length
    };


#endif // VOS_PHYSICS_COLLISION2_HEADER
