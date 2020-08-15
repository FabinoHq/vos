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
//   For more information, please refer to <http://unlicense.org>             //
////////////////////////////////////////////////////////////////////////////////
//    VOS : Virtual Operating System                                          //
//     Math/Vector2.h : 2 components vector management                        //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_MATH_VECTOR2_HEADER
#define VOS_MATH_VECTOR2_HEADER

    #include "Math.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Vector2 class definition                                              //
    ////////////////////////////////////////////////////////////////////////////
    class Vector2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Vector2 default constructor                                   //
            ////////////////////////////////////////////////////////////////////
            Vector2()
            {
                vec[0] = 0.0f;
                vec[1] = 0.0f;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 copy constructor                                      //
            ////////////////////////////////////////////////////////////////////
            Vector2(const Vector2& vector)
            {
                vec[0] = vector.vec[0];
                vec[1] = vector.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 components constructor                                //
            ////////////////////////////////////////////////////////////////////
            Vector2(float x, float y)
            {
                vec[0] = x;
                vec[1] = y;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 destructor                                            //
            ////////////////////////////////////////////////////////////////////
            ~Vector2()
            {
                vec[0] = 0.0f;
                vec[1] = 0.0f;
            }


            ////////////////////////////////////////////////////////////////////
            //  Reset Vector2 to zero                                         //
            ////////////////////////////////////////////////////////////////////
            inline void reset()
            {
                vec[0] = 0.0f;
                vec[1] = 0.0f;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector2 components from a vector                          //
            ////////////////////////////////////////////////////////////////////
            inline void set(const Vector2& vector)
            {
                vec[0] = vector.vec[0];
                vec[1] = vector.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector2 components from X and Y components                //
            ////////////////////////////////////////////////////////////////////
            inline void set(float x, float y)
            {
                vec[0] = x;
                vec[1] = y;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector2 X component                                       //
            ////////////////////////////////////////////////////////////////////
            inline void setX(float x)
            {
                vec[0] = x;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector2 Y component                                       //
            ////////////////////////////////////////////////////////////////////
            inline void setY(float y)
            {
                vec[1] = y;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector2 length                                            //
            ////////////////////////////////////////////////////////////////////
            inline float length()
            {
                return std::sqrt((vec[0]*vec[0])+(vec[1]*vec[1]));
            }

            ////////////////////////////////////////////////////////////////////
            //  Normalize Vector2                                             //
            ////////////////////////////////////////////////////////////////////
            inline void normalize()
            {
                float len = length();
                if (len > 0.0f)
                {
                    float invLength = 1.0f/len;
                    vec[0] *= invLength;
                    vec[1] *= invLength;
                }
            }


            ////////////////////////////////////////////////////////////////////
            //  Get Vector2 x component                                       //
            //  return : X component of the vector                            //
            ////////////////////////////////////////////////////////////////////
            inline float& x()
            {
                return vec[0];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector2 y component                                       //
            //  return : Y component of the vector                            //
            ////////////////////////////////////////////////////////////////////
            inline float& y()
            {
                return vec[1];
            }


            ////////////////////////////////////////////////////////////////////
            //  Vector2 affectation operator                                  //
            ////////////////////////////////////////////////////////////////////
            inline Vector2& operator=(const Vector2& vector)
            {
                vec[0] = vector.vec[0];
                vec[1] = vector.vec[1];
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 addition operator                                     //
            ////////////////////////////////////////////////////////////////////
            inline Vector2 operator+(const Vector2& vector)
            {
                return Vector2(vec[0]+vector.vec[0], vec[1]+vector.vec[1]);
            }

            inline Vector2 operator+(float val)
            {
                return Vector2(vec[0]+val, vec[1]+val);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 subtraction operator                                  //
            ////////////////////////////////////////////////////////////////////
            inline Vector2 operator-(const Vector2& vector)
            {
                return Vector2(vec[0]-vector.vec[0], vec[1]-vector.vec[1]);
            }

            inline Vector2 operator-(float val)
            {
                return Vector2(vec[0]-val, vec[1]-val);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 unary plus operator                                   //
            ////////////////////////////////////////////////////////////////////
            inline Vector2 operator+()
            {
                return Vector2(*this);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 unary minus operator                                  //
            ////////////////////////////////////////////////////////////////////
            inline Vector2 operator-()
            {
                return Vector2(-vec[0], -vec[1]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 multiplication operator                               //
            ////////////////////////////////////////////////////////////////////
            inline Vector2 operator*(const Vector2& vector)
            {
                return Vector2(vec[0]*vector.vec[0], vec[1]*vector.vec[1]);
            }

            inline Vector2 operator*(float val)
            {
                return Vector2(vec[0]*val, vec[1]*val);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 division operator                                     //
            ////////////////////////////////////////////////////////////////////
            inline Vector2 operator/(const Vector2& vector)
            {
                Vector2 result(*this);
                if (vector.vec[0] != 0.0f)
                {
                    result.vec[0] /= vector.vec[0];
                }
                if (vector.vec[1] != 0.0f)
                {
                    result.vec[1] /= vector.vec[1];
                }
                return result;
            }

            inline Vector2 operator/(float val)
            {
                Vector2 result(*this);
                if (val != 0.0f)
                {
                    result.vec[0] /= val;
                    result.vec[1] /= val;
                }
                return result;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 prefix increment operator                             //
            ////////////////////////////////////////////////////////////////////
            inline Vector2& operator++()
            {
                ++vec[0];
                ++vec[1];
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 postfix increment operator                            //
            ////////////////////////////////////////////////////////////////////
            inline Vector2 operator++(int)
            {
                return Vector2(vec[0]++, vec[1]++);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 prefix decrement operator                             //
            ////////////////////////////////////////////////////////////////////
            inline Vector2& operator--()
            {
                --vec[0];
                --vec[1];
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 postfix decrement operator                            //
            ////////////////////////////////////////////////////////////////////
            inline Vector2 operator--(int)
            {
                return Vector2(vec[0]--, vec[1]--);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 addition assignment operator                          //
            ////////////////////////////////////////////////////////////////////
            inline Vector2& operator+=(const Vector2& vector)
            {
                vec[0] += vector.vec[0];
                vec[1] += vector.vec[1];
                return *this;
            }

            inline Vector2& operator+=(float val)
            {
                vec[0] += val;
                vec[1] += val;
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 subtraction assignment operator                       //
            ////////////////////////////////////////////////////////////////////
            inline Vector2& operator-=(const Vector2& vector)
            {
                vec[0] -= vector.vec[0];
                vec[1] -= vector.vec[1];
                return *this;
            }

            inline Vector2& operator-=(float val)
            {
                vec[0] -= val;
                vec[1] -= val;
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 multiplication assignment operator                    //
            ////////////////////////////////////////////////////////////////////
            inline Vector2& operator*=(const Vector2& vector)
            {
                vec[0] *= vector.vec[0];
                vec[1] *= vector.vec[1];
                return *this;
            }

            inline Vector2& operator*=(float val)
            {
                vec[0] *= val;
                vec[1] *= val;
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 division assignment operator                          //
            ////////////////////////////////////////////////////////////////////
            inline Vector2& operator/=(const Vector2& vector)
            {
                if (vector.vec[0] != 0.0f)
                {
                    vec[0] *= vector.vec[0];
                }
                if (vector.vec[1] != 0.0f)
                {
                    vec[1] *= vector.vec[1];
                }
                return *this;
            }

            inline Vector2& operator/=(float val)
            {
                if (val != 0.0f)
                {
                    vec[0] *= val;
                    vec[1] *= val;
                }
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 equal to operator                                     //
            ////////////////////////////////////////////////////////////////////
            inline bool operator==(const Vector2& vector)
            {
                bool areEqual = Math::areEqual(vec[0], vector.vec[0]) &&
                    Math::areEqual(vec[1], vector.vec[1]);
                return areEqual;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 not equal to operator                                 //
            ////////////////////////////////////////////////////////////////////
            inline bool operator!=(const Vector2& vector)
            {
                bool areEqual = Math::areEqual(vec[0], vector.vec[0]) &&
                    Math::areEqual(vec[1], vector.vec[1]);
                return !areEqual;
            }


        public:
            float   vec[2];     // 2 components vector representation
    };


#endif // VOS_MATH_VECTOR2_HEADER
