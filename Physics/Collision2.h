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
                position.vec[0] = collisionPosition.vec[0];
                position.vec[1] = collisionPosition.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Set collision position                                        //
            ////////////////////////////////////////////////////////////////////
            inline void setPosition(int64_t positionX, int64_t positionY)
            {
                position.vec[0] = positionX;
                position.vec[1] = positionY;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set collision offset                                          //
            ////////////////////////////////////////////////////////////////////
            inline void setOffset(const Vector2i& collisionOffset)
            {
                offset.vec[0] = collisionOffset.vec[0];
                offset.vec[1] = collisionOffset.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Set collision offset                                          //
            ////////////////////////////////////////////////////////////////////
            inline void setOffset(int64_t offsetX, int64_t offsetY)
            {
                offset.vec[0] = offsetX;
                offset.vec[1] = offsetY;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set collision normal                                          //
            ////////////////////////////////////////////////////////////////////
            inline void setNormal(const Vector2i& collisionNormal)
            {
                normal.vec[0] = collisionNormal.vec[0];
                normal.vec[1] = collisionNormal.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Set collision normal                                          //
            ////////////////////////////////////////////////////////////////////
            inline void setNormal(int64_t normalX, int64_t normalY)
            {
                normal.vec[0] = normalX;
                normal.vec[1] = normalY;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set collision factor                                          //
            ////////////////////////////////////////////////////////////////////
            inline void setFactor(int64_t collisionFactor)
            {
                factor = Math::clamp(collisionFactor, 0ll, Math::OneInt);
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
            int64_t         factor;         // Collision factor
    };


#endif // VOS_PHYSICS_COLLISION2_HEADER
