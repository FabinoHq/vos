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
//     Math/Vector2.h : 2 components vector management                        //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_MATH_VECTOR2_HEADER
#define VOS_MATH_VECTOR2_HEADER

    #include "../System/System.h"
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
            //  Set Vector2 components from a single value                    //
            ////////////////////////////////////////////////////////////////////
            inline void set(float val)
            {
                vec[0] = val;
                vec[1] = val;
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
            //  Check if vector is equal to zero                              //
            ////////////////////////////////////////////////////////////////////
            inline bool isZero() const
            {
                return (
                    Math::areEqual(vec[0], 0.0f) &&
                    Math::areEqual(vec[1], 0.0f)
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector absolute value                                     //
            ////////////////////////////////////////////////////////////////////
            inline void abs()
            {
                vec[0] = Math::abs(vec[0]);
                vec[1] = Math::abs(vec[1]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Get vector minimum value                                      //
            ////////////////////////////////////////////////////////////////////
            inline float min()
            {
                return Math::min(vec[0], vec[1]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector minimum value between itself and min value         //
            ////////////////////////////////////////////////////////////////////
            inline void min(float min)
            {
                vec[0] = Math::min(vec[0], min);
                vec[1] = Math::min(vec[1], min);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector minimum value between itself and min vector        //
            ////////////////////////////////////////////////////////////////////
            inline void min(const Vector2& min)
            {
                vec[0] = Math::min(vec[0], min.vec[0]);
                vec[1] = Math::min(vec[1], min.vec[1]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector minimum value between itself and min X Y           //
            ////////////////////////////////////////////////////////////////////
            inline void min(float minX, float minY)
            {
                vec[0] = Math::min(vec[0], minX);
                vec[1] = Math::min(vec[1], minY);
            }

            ////////////////////////////////////////////////////////////////////
            //  Get vector maximum value                                      //
            ////////////////////////////////////////////////////////////////////
            inline float max()
            {
                return Math::max(vec[0], vec[1]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector maximum value between itself and max value         //
            ////////////////////////////////////////////////////////////////////
            inline void max(float max)
            {
                vec[0] = Math::max(vec[0], max);
                vec[1] = Math::max(vec[1], max);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector maximum value between itself and max vector        //
            ////////////////////////////////////////////////////////////////////
            inline void max(const Vector2& max)
            {
                vec[0] = Math::max(vec[0], max.vec[0]);
                vec[1] = Math::max(vec[1], max.vec[1]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector maximum value between itself and max X Y           //
            ////////////////////////////////////////////////////////////////////
            inline void max(float maxX, float maxY)
            {
                vec[0] = Math::max(vec[0], maxX);
                vec[1] = Math::max(vec[1], maxY);
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp vector between min and max                              //
            ////////////////////////////////////////////////////////////////////
            inline void clamp(float min, float max)
            {
                vec[0] = Math::clamp(vec[0], min, max);
                vec[1] = Math::clamp(vec[1], min, max);
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp vector between min and max vectors                      //
            ////////////////////////////////////////////////////////////////////
            inline void clamp(const Vector2& min, const Vector2& max)
            {
                vec[0] = Math::clamp(vec[0], min.vec[0], max.vec[0]);
                vec[1] = Math::clamp(vec[1], min.vec[1], max.vec[1]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp vector between min and max X Y components               //
            ////////////////////////////////////////////////////////////////////
            inline void clamp(float minX, float minY, float maxX, float maxY)
            {
                vec[0] = Math::clamp(vec[0], minX, maxX);
                vec[1] = Math::clamp(vec[1], minY, maxY);
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp vector by absolute max value                            //
            ////////////////////////////////////////////////////////////////////
            inline void clampAbs(float max)
            {
                vec[0] = Math::clampAbs(vec[0], max);
                vec[1] = Math::clampAbs(vec[1], max);
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp vector by absolute max vector                           //
            ////////////////////////////////////////////////////////////////////
            inline void clampAbs(const Vector2& max)
            {
                vec[0] = Math::clampAbs(vec[0], max.vec[0]);
                vec[1] = Math::clampAbs(vec[1], max.vec[1]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp vector by absolute max X Y components                   //
            ////////////////////////////////////////////////////////////////////
            inline void clampAbs(float maxX, float maxY)
            {
                vec[0] = Math::clampAbs(vec[0], maxX);
                vec[1] = Math::clampAbs(vec[1], maxY);
            }

            ////////////////////////////////////////////////////////////////////
            //  Move components towards a specified value                     //
            ////////////////////////////////////////////////////////////////////
            inline void moveTowards(float val, float delta)
            {
                if (vec[0] > val)
                {
                    vec[0] = Math::max(vec[0]-delta, val);
                }
                else if (vec[0] < val)
                {
                    vec[0] = Math::min(vec[0]+delta, val);
                }
                if (vec[1] > val)
                {
                    vec[1] = Math::max(vec[1]-delta, val);
                }
                else if (vec[1] < val)
                {
                    vec[1] = Math::min(vec[1]+delta, val);
                }
            }

            ////////////////////////////////////////////////////////////////////
            //  Move X component towards a specified value                    //
            ////////////////////////////////////////////////////////////////////
            inline void moveXTowards(float val, float delta)
            {
                if (vec[0] > val)
                {
                    vec[0] = Math::max(vec[0]-delta, val);
                }
                else if (vec[0] < val)
                {
                    vec[0] = Math::min(vec[0]+delta, val);
                }
            }

            ////////////////////////////////////////////////////////////////////
            //  Move Y component towards a specified value                    //
            ////////////////////////////////////////////////////////////////////
            inline void moveYTowards(float val, float delta)
            {
                if (vec[1] > val)
                {
                    vec[1] = Math::max(vec[1]-delta, val);
                }
                else if (vec[1] < val)
                {
                    vec[1] = Math::min(vec[1]+delta, val);
                }
            }

            ////////////////////////////////////////////////////////////////////
            //  Linear interpolation                                          //
            ////////////////////////////////////////////////////////////////////
            inline void linearInterp(
                const Vector2& v1, const Vector2& v2, float t)
            {
                vec[0] = v1.vec[0] + t*(v2.vec[0]-v1.vec[0]);
                vec[1] = v1.vec[1] + t*(v2.vec[1]-v1.vec[1]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Angle linear interpolation                                    //
            ////////////////////////////////////////////////////////////////////
            inline void angleLinearInterp(
                const Vector2& v1, const Vector2& v2, float t)
            {
                vec[0] = Math::angleLinearInterp(v1.vec[0], v2.vec[0], t);
                vec[1] = Math::angleLinearInterp(v1.vec[1], v2.vec[1], t);
            }

            ////////////////////////////////////////////////////////////////////
            //  Cubic interpolation                                           //
            ////////////////////////////////////////////////////////////////////
            inline void cubicInterp(
                const Vector2& v1, const Vector2& v2, float t)
            {
                vec[0] = v1.vec[0] + (t*t*(3.0f-2.0f*t))*(v2.vec[0]-v1.vec[0]);
                vec[1] = v1.vec[1] + (t*t*(3.0f-2.0f*t))*(v2.vec[1]-v1.vec[1]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Hermit interpolation                                          //
            ////////////////////////////////////////////////////////////////////
            inline void hermitInterp(
                const Vector2& v0, const Vector2& v1,
                const Vector2& v2, const Vector2& v3, float t)
            {
                vec[0] = Math::hermitInterp(
                    v0.vec[0], v1.vec[0], v2.vec[0], v3.vec[0], t
                );
                vec[1] = Math::hermitInterp(
                    v0.vec[1], v1.vec[1], v2.vec[1], v3.vec[1], t
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Get the dot product of this vector and another                //
            ////////////////////////////////////////////////////////////////////
            inline float dotProduct(const Vector2& v) const
            {
                return ((vec[0]*v.vec[0]) + (vec[1]*v.vec[1]));
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector2 length                                            //
            ////////////////////////////////////////////////////////////////////
            inline float length() const
            {
                return Math::sqrt((vec[0]*vec[0]) + (vec[1]*vec[1]));
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector2 squared length                                    //
            ////////////////////////////////////////////////////////////////////
            inline float squaredLength() const
            {
                return ((vec[0]*vec[0]) + (vec[1]*vec[1]));
            }

            ////////////////////////////////////////////////////////////////////
            //  Normalize Vector2                                             //
            ////////////////////////////////////////////////////////////////////
            inline void normalize()
            {
                float len = length();
                if (len != 0.0f)
                {
                    float invLength = (1.0f / len);
                    vec[0] *= invLength;
                    vec[1] *= invLength;
                }
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

            inline Vector2& operator=(float val)
            {
                vec[0] = val;
                vec[1] = val;
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 addition operator                                     //
            ////////////////////////////////////////////////////////////////////
            inline Vector2 operator+(const Vector2& vector) const
            {
                return Vector2(vec[0]+vector.vec[0], vec[1]+vector.vec[1]);
            }

            inline Vector2 operator+(float val) const
            {
                return Vector2(vec[0]+val, vec[1]+val);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 subtraction operator                                  //
            ////////////////////////////////////////////////////////////////////
            inline Vector2 operator-(const Vector2& vector) const
            {
                return Vector2(vec[0]-vector.vec[0], vec[1]-vector.vec[1]);
            }

            inline Vector2 operator-(float val) const
            {
                return Vector2(vec[0]-val, vec[1]-val);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 unary plus operator                                   //
            ////////////////////////////////////////////////////////////////////
            inline Vector2 operator+() const
            {
                return Vector2(*this);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 unary minus operator                                  //
            ////////////////////////////////////////////////////////////////////
            inline Vector2 operator-() const
            {
                return Vector2(-vec[0], -vec[1]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 multiplication operator                               //
            ////////////////////////////////////////////////////////////////////
            inline Vector2 operator*(const Vector2& vector) const
            {
                return Vector2(vec[0]*vector.vec[0], vec[1]*vector.vec[1]);
            }

            inline Vector2 operator*(float val) const
            {
                return Vector2(vec[0]*val, vec[1]*val);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 division operator                                     //
            ////////////////////////////////////////////////////////////////////
            inline Vector2 operator/(const Vector2& vector) const
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

            inline Vector2 operator/(float val) const
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
                    vec[0] /= vector.vec[0];
                }
                if (vector.vec[1] != 0.0f)
                {
                    vec[1] /= vector.vec[1];
                }
                return *this;
            }

            inline Vector2& operator/=(float val)
            {
                if (val != 0.0f)
                {
                    vec[0] /= val;
                    vec[1] /= val;
                }
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 equal to operator                                     //
            ////////////////////////////////////////////////////////////////////
            inline bool operator==(const Vector2& vector) const
            {
                return (
                    Math::areEqual(vec[0], vector.vec[0]) &&
                    Math::areEqual(vec[1], vector.vec[1])
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector2 not equal to operator                                 //
            ////////////////////////////////////////////////////////////////////
            inline bool operator!=(const Vector2& vector) const
            {
                return (!(
                    Math::areEqual(vec[0], vector.vec[0]) &&
                    Math::areEqual(vec[1], vector.vec[1]))
                );
            }


        public:
            float   vec[2];     // 2 components vector representation
    };


#endif // VOS_MATH_VECTOR2_HEADER
