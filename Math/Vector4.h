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
//     Math/Vector4.h : 4 components vector management                        //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_MATH_VECTOR4_HEADER
#define VOS_MATH_VECTOR4_HEADER

    #include "../System/System.h"
    #include "Math.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Vector4 class definition                                              //
    ////////////////////////////////////////////////////////////////////////////
    class Vector4
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Vector4 default constructor                                   //
            ////////////////////////////////////////////////////////////////////
            Vector4()
            {
                vec[0] = 0.0f;
                vec[1] = 0.0f;
                vec[2] = 0.0f;
                vec[3] = 0.0f;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 copy constructor                                      //
            ////////////////////////////////////////////////////////////////////
            Vector4(const Vector4& vector)
            {
                vec[0] = vector.vec[0];
                vec[1] = vector.vec[1];
                vec[2] = vector.vec[2];
                vec[3] = vector.vec[3];
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 components constructor                                //
            ////////////////////////////////////////////////////////////////////
            Vector4(float x, float y, float z, float w)
            {
                vec[0] = x;
                vec[1] = y;
                vec[2] = z;
                vec[3] = w;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 destructor                                            //
            ////////////////////////////////////////////////////////////////////
            ~Vector4()
            {
                vec[0] = 0.0f;
                vec[1] = 0.0f;
                vec[2] = 0.0f;
                vec[3] = 0.0f;
            }


            ////////////////////////////////////////////////////////////////////
            //  Reset Vector4 to zero                                         //
            ////////////////////////////////////////////////////////////////////
            inline void reset()
            {
                vec[0] = 0.0f;
                vec[1] = 0.0f;
                vec[2] = 0.0f;
                vec[3] = 0.0f;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector4 components from a vector                          //
            ////////////////////////////////////////////////////////////////////
            inline void set(const Vector4& vector)
            {
                vec[0] = vector.vec[0];
                vec[1] = vector.vec[1];
                vec[2] = vector.vec[2];
                vec[3] = vector.vec[3];
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector4 components from X, Y, Z and W components          //
            ////////////////////////////////////////////////////////////////////
            inline void set(float x, float y, float z, float w)
            {
                vec[0] = x;
                vec[1] = y;
                vec[2] = z;
                vec[3] = w;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector4 components from a single value                    //
            ////////////////////////////////////////////////////////////////////
            inline void set(float val)
            {
                vec[0] = val;
                vec[1] = val;
                vec[2] = val;
                vec[3] = val;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector4 X component                                       //
            ////////////////////////////////////////////////////////////////////
            inline void setX(float x)
            {
                vec[0] = x;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector4 Y component                                       //
            ////////////////////////////////////////////////////////////////////
            inline void setY(float y)
            {
                vec[1] = y;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector4 Z component                                       //
            ////////////////////////////////////////////////////////////////////
            inline void setZ(float z)
            {
                vec[2] = z;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector4 W component                                       //
            ////////////////////////////////////////////////////////////////////
            inline void setW(float w)
            {
                vec[3] = w;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector4 x component                                       //
            //  return : X component of the vector                            //
            ////////////////////////////////////////////////////////////////////
            inline float& x()
            {
                return vec[0];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector4 y component                                       //
            //  return : Y component of the vector                            //
            ////////////////////////////////////////////////////////////////////
            inline float& y()
            {
                return vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector4 z component                                       //
            //  return : Z component of the vector                            //
            ////////////////////////////////////////////////////////////////////
            inline float& z()
            {
                return vec[2];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector4 w component                                       //
            //  return : W component of the vector                            //
            ////////////////////////////////////////////////////////////////////
            inline float& w()
            {
                return vec[3];
            }


            ////////////////////////////////////////////////////////////////////
            //  Check if vector is equal to zero                              //
            ////////////////////////////////////////////////////////////////////
            inline bool isZero() const
            {
                return (
                    Math::areEqual(vec[0], 0.0f) &&
                    Math::areEqual(vec[1], 0.0f) &&
                    Math::areEqual(vec[2], 0.0f) &&
                    Math::areEqual(vec[3], 0.0f)
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector absolute value                                     //
            ////////////////////////////////////////////////////////////////////
            inline void abs()
            {
                vec[0] = Math::abs(vec[0]);
                vec[1] = Math::abs(vec[1]);
                vec[2] = Math::abs(vec[2]);
                vec[4] = Math::abs(vec[4]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Get vector minimum value                                      //
            ////////////////////////////////////////////////////////////////////
            inline float min()
            {
                return Math::min(vec[0], Math::min(vec[1],
                    Math::min(vec[2], vec[3])));
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector minimum value between itself and min value         //
            ////////////////////////////////////////////////////////////////////
            inline void min(float min)
            {
                vec[0] = Math::min(vec[0], min);
                vec[1] = Math::min(vec[1], min);
                vec[2] = Math::min(vec[2], min);
                vec[3] = Math::min(vec[3], min);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector minimum value between itself and min vector        //
            ////////////////////////////////////////////////////////////////////
            inline void min(const Vector4& min)
            {
                vec[0] = Math::min(vec[0], min.vec[0]);
                vec[1] = Math::min(vec[1], min.vec[1]);
                vec[2] = Math::min(vec[2], min.vec[2]);
                vec[3] = Math::min(vec[3], min.vec[3]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector minimum value between itself and min X Y Z W       //
            ////////////////////////////////////////////////////////////////////
            inline void min(float minX, float minY, float minZ, float minW)
            {
                vec[0] = Math::min(vec[0], minX);
                vec[1] = Math::min(vec[1], minY);
                vec[2] = Math::min(vec[2], minZ);
                vec[3] = Math::min(vec[4], minW);
            }

            ////////////////////////////////////////////////////////////////////
            //  Get vector maximum value                                      //
            ////////////////////////////////////////////////////////////////////
            inline float max()
            {
                return Math::max(vec[0], Math::max(vec[1],
                    Math::max(vec[2], vec[3])));
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector maximum value between itself and max value         //
            ////////////////////////////////////////////////////////////////////
            inline void max(float max)
            {
                vec[0] = Math::max(vec[0], max);
                vec[1] = Math::max(vec[1], max);
                vec[2] = Math::max(vec[2], max);
                vec[3] = Math::max(vec[3], max);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector maximum value between itself and max vector        //
            ////////////////////////////////////////////////////////////////////
            inline void max(const Vector4& max)
            {
                vec[0] = Math::max(vec[0], max.vec[0]);
                vec[1] = Math::max(vec[1], max.vec[1]);
                vec[2] = Math::max(vec[2], max.vec[2]);
                vec[3] = Math::max(vec[3], max.vec[3]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector maximum value between itself and max X Y           //
            ////////////////////////////////////////////////////////////////////
            inline void max(float maxX, float maxY, float maxZ, float maxW)
            {
                vec[0] = Math::max(vec[0], maxX);
                vec[1] = Math::max(vec[1], maxY);
                vec[2] = Math::max(vec[2], maxZ);
                vec[3] = Math::max(vec[3], maxW);
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp vector between min and max                              //
            ////////////////////////////////////////////////////////////////////
            inline void clamp(float min, float max)
            {
                vec[0] = Math::clamp(vec[0], min, max);
                vec[1] = Math::clamp(vec[1], min, max);
                vec[2] = Math::clamp(vec[2], min, max);
                vec[3] = Math::clamp(vec[2], min, max);
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp vector between min and max vectors                      //
            ////////////////////////////////////////////////////////////////////
            inline void clamp(const Vector4& min, const Vector4& max)
            {
                vec[0] = Math::clamp(vec[0], min.vec[0], max.vec[0]);
                vec[1] = Math::clamp(vec[1], min.vec[1], max.vec[1]);
                vec[2] = Math::clamp(vec[2], min.vec[2], max.vec[2]);
                vec[3] = Math::clamp(vec[3], min.vec[3], max.vec[3]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp vector between min and max X Y Z W components           //
            ////////////////////////////////////////////////////////////////////
            inline void clamp(float minX, float minY, float minZ, float minW,
                float maxX, float maxY, float maxZ, float maxW)
            {
                vec[0] = Math::clamp(vec[0], minX, maxX);
                vec[1] = Math::clamp(vec[1], minY, maxY);
                vec[2] = Math::clamp(vec[2], minZ, maxZ);
                vec[3] = Math::clamp(vec[3], minW, maxW);
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp vector by absolute max value                            //
            ////////////////////////////////////////////////////////////////////
            inline void clampAbs(float max)
            {
                vec[0] = Math::clampAbs(vec[0], max);
                vec[1] = Math::clampAbs(vec[1], max);
                vec[2] = Math::clampAbs(vec[2], max);
                vec[3] = Math::clampAbs(vec[3], max);
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp vector by absolute max vector                           //
            ////////////////////////////////////////////////////////////////////
            inline void clampAbs(const Vector4& max)
            {
                vec[0] = Math::clampAbs(vec[0], max.vec[0]);
                vec[1] = Math::clampAbs(vec[1], max.vec[1]);
                vec[2] = Math::clampAbs(vec[2], max.vec[2]);
                vec[3] = Math::clampAbs(vec[3], max.vec[3]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp vector by absolute max X Y Z W components               //
            ////////////////////////////////////////////////////////////////////
            inline void clampAbs(float maxX, float maxY, float maxZ, float maxW)
            {
                vec[0] = Math::clampAbs(vec[0], maxX);
                vec[1] = Math::clampAbs(vec[1], maxY);
                vec[2] = Math::clampAbs(vec[2], maxZ);
                vec[3] = Math::clampAbs(vec[3], maxW);
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
                if (vec[2] > val)
                {
                    vec[2] = Math::max(vec[2]-delta, val);
                }
                else if (vec[2] < val)
                {
                    vec[2] = Math::min(vec[2]+delta, val);
                }
                if (vec[3] > val)
                {
                    vec[3] = Math::max(vec[3]-delta, val);
                }
                else if (vec[3] < val)
                {
                    vec[3] = Math::min(vec[3]+delta, val);
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
            //  Move Z component towards a specified value                    //
            ////////////////////////////////////////////////////////////////////
            inline void moveZTowards(float val, float delta)
            {
                if (vec[2] > val)
                {
                    vec[2] = Math::max(vec[2]-delta, val);
                }
                else if (vec[1] < val)
                {
                    vec[2] = Math::min(vec[2]+delta, val);
                }
            }

            ////////////////////////////////////////////////////////////////////
            //  Move W component towards a specified value                    //
            ////////////////////////////////////////////////////////////////////
            inline void moveWTowards(float val, float delta)
            {
                if (vec[3] > val)
                {
                    vec[3] = Math::max(vec[3]-delta, val);
                }
                else if (vec[1] < val)
                {
                    vec[3] = Math::min(vec[3]+delta, val);
                }
            }

            ////////////////////////////////////////////////////////////////////
            //  Linear interpolation                                          //
            ////////////////////////////////////////////////////////////////////
            inline void linearInterp(
                const Vector4& v1, const Vector4& v2, float t)
            {
                vec[0] = v1.vec[0] + t*(v2.vec[0]-v1.vec[0]);
                vec[1] = v1.vec[1] + t*(v2.vec[1]-v1.vec[1]);
                vec[2] = v1.vec[2] + t*(v2.vec[2]-v1.vec[2]);
                vec[3] = v1.vec[3] + t*(v2.vec[3]-v1.vec[3]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Angle linear interpolation                                    //
            ////////////////////////////////////////////////////////////////////
            inline void angleLinearInterp(
                const Vector4& v1, const Vector4& v2, float t)
            {
                vec[0] = Math::angleLinearInterp(v1.vec[0], v2.vec[0], t);
                vec[1] = Math::angleLinearInterp(v1.vec[1], v2.vec[1], t);
                vec[2] = Math::angleLinearInterp(v1.vec[2], v2.vec[2], t);
                vec[3] = Math::angleLinearInterp(v1.vec[3], v2.vec[3], t);
            }

            ////////////////////////////////////////////////////////////////////
            //  Cubic interpolation                                           //
            ////////////////////////////////////////////////////////////////////
            inline void cubicInterp(
                const Vector4& v1, const Vector4& v2, float t)
            {
                vec[0] = v1.vec[0] + (t*t*(3.0f-2.0f*t))*(v2.vec[0]-v1.vec[0]);
                vec[1] = v1.vec[1] + (t*t*(3.0f-2.0f*t))*(v2.vec[1]-v1.vec[1]);
                vec[2] = v1.vec[2] + (t*t*(3.0f-2.0f*t))*(v2.vec[2]-v1.vec[2]);
                vec[3] = v1.vec[3] + (t*t*(3.0f-2.0f*t))*(v2.vec[3]-v1.vec[3]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Hermit interpolation                                          //
            ////////////////////////////////////////////////////////////////////
            inline void hermitInterp(
                const Vector4& v0, const Vector4& v1,
                const Vector4& v2, const Vector4& v3, float t)
            {
                vec[0] = Math::hermitInterp(
                    v0.vec[0], v1.vec[0], v2.vec[0], v3.vec[0], t
                );
                vec[1] = Math::hermitInterp(
                    v0.vec[1], v1.vec[1], v2.vec[1], v3.vec[1], t
                );
                vec[2] = Math::hermitInterp(
                    v0.vec[2], v1.vec[2], v2.vec[2], v3.vec[2], t
                );
                vec[3] = Math::hermitInterp(
                    v0.vec[3], v1.vec[3], v2.vec[3], v3.vec[3], t
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Get the dot product of this vector and another                //
            ////////////////////////////////////////////////////////////////////
            inline float dotProduct(const Vector4& v) const
            {
                return (
                    (vec[0]*v.vec[0]) + (vec[1]*v.vec[1]) +
                    (vec[2]*v.vec[2]) + (vec[3]*v.vec[3])
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector4 length                                            //
            ////////////////////////////////////////////////////////////////////
            inline float length() const
            {
                return Math::sqrt(
                    (vec[0]*vec[0]) + (vec[1]*vec[1]) +
                    (vec[2]*vec[2]) + (vec[3]*vec[3])
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector4 squared length                                    //
            ////////////////////////////////////////////////////////////////////
            inline float squaredLength() const
            {
                return (
                    (vec[0]*vec[0]) + (vec[1]*vec[1]) +
                    (vec[2]*vec[2]) + (vec[3]*vec[3])
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Normalize Vector4                                             //
            ////////////////////////////////////////////////////////////////////
            inline void normalize()
            {
                float len = length();
                if (len != 0.0f)
                {
                    float invLength = (1.0f / len);
                    vec[0] *= invLength;
                    vec[1] *= invLength;
                    vec[2] *= invLength;
                    vec[3] *= invLength;
                }
            }


            ////////////////////////////////////////////////////////////////////
            //  Vector4 affectation operator                                  //
            ////////////////////////////////////////////////////////////////////
            inline Vector4& operator=(const Vector4& vector)
            {
                vec[0] = vector.vec[0];
                vec[1] = vector.vec[1];
                vec[2] = vector.vec[2];
                vec[3] = vector.vec[3];
                return *this;
            }

            inline Vector4& operator=(float val)
            {
                vec[0] = val;
                vec[1] = val;
                vec[2] = val;
                vec[3] = val;
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 addition operator                                     //
            ////////////////////////////////////////////////////////////////////
            inline Vector4 operator+(const Vector4& vector) const
            {
                return Vector4(
                    vec[0]+vector.vec[0], vec[1]+vector.vec[1],
                    vec[2]+vector.vec[2], vec[3]+vector.vec[3]
                );
            }

            inline Vector4 operator+(float val) const
            {
                return Vector4(vec[0]+val, vec[1]+val, vec[2]+val, vec[3]+val);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 subtraction operator                                  //
            ////////////////////////////////////////////////////////////////////
            inline Vector4 operator-(const Vector4& vector) const
            {
                return Vector4(
                    vec[0]-vector.vec[0], vec[1]-vector.vec[1],
                    vec[2]-vector.vec[2], vec[3]-vector.vec[3]
                );
            }

            inline Vector4 operator-(float val) const
            {
                return Vector4(vec[0]-val, vec[1]-val, vec[2]-val, vec[3]-val);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 unary plus operator                                   //
            ////////////////////////////////////////////////////////////////////
            inline Vector4 operator+() const
            {
                return Vector4(*this);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 unary minus operator                                  //
            ////////////////////////////////////////////////////////////////////
            inline Vector4 operator-() const
            {
                return Vector4(-vec[0], -vec[1], -vec[2], -vec[3]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 multiplication operator                               //
            ////////////////////////////////////////////////////////////////////
            inline Vector4 operator*(const Vector4& vector) const
            {
                return Vector4(
                    vec[0]*vector.vec[0], vec[1]*vector.vec[1],
                    vec[2]*vector.vec[2], vec[3]*vector.vec[3]
                );
            }

            inline Vector4 operator*(float val) const
            {
                return Vector4(vec[0]*val, vec[1]*val, vec[2]*val, vec[3]*val);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 division operator                                     //
            ////////////////////////////////////////////////////////////////////
            inline Vector4 operator/(const Vector4& vector) const
            {
                Vector4 result(*this);
                if (vector.vec[0] != 0.0f)
                {
                    result.vec[0] /= vector.vec[0];
                }
                if (vector.vec[1] != 0.0f)
                {
                    result.vec[1] /= vector.vec[1];
                }
                if (vector.vec[2] != 0.0f)
                {
                    result.vec[2] /= vector.vec[2];
                }
                if (vector.vec[3] != 0.0f)
                {
                    result.vec[3] /= vector.vec[3];
                }
                return result;
            }

            inline Vector4 operator/(float val) const
            {
                Vector4 result(*this);
                if (val != 0.0f)
                {
                    result.vec[0] /= val;
                    result.vec[1] /= val;
                    result.vec[2] /= val;
                    result.vec[3] /= val;
                }
                return result;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 prefix increment operator                             //
            ////////////////////////////////////////////////////////////////////
            inline Vector4& operator++()
            {
                ++vec[0];
                ++vec[1];
                ++vec[2];
                ++vec[3];
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 postfix increment operator                            //
            ////////////////////////////////////////////////////////////////////
            inline Vector4 operator++(int)
            {
                return Vector4(vec[0]++, vec[1]++, vec[2]++, vec[3]++);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 prefix decrement operator                             //
            ////////////////////////////////////////////////////////////////////
            inline Vector4& operator--()
            {
                --vec[0];
                --vec[1];
                --vec[2];
                --vec[3];
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 postfix decrement operator                            //
            ////////////////////////////////////////////////////////////////////
            inline Vector4 operator--(int)
            {
                return Vector4(vec[0]--, vec[1]--, vec[2]--, vec[3]--);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 addition assignment operator                          //
            ////////////////////////////////////////////////////////////////////
            inline Vector4& operator+=(const Vector4& vector)
            {
                vec[0] += vector.vec[0];
                vec[1] += vector.vec[1];
                vec[2] += vector.vec[2];
                vec[3] += vector.vec[3];
                return *this;
            }

            inline Vector4& operator+=(float val)
            {
                vec[0] += val;
                vec[1] += val;
                vec[2] += val;
                vec[3] += val;
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 subtraction assignment operator                       //
            ////////////////////////////////////////////////////////////////////
            inline Vector4& operator-=(const Vector4& vector)
            {
                vec[0] -= vector.vec[0];
                vec[1] -= vector.vec[1];
                vec[2] -= vector.vec[2];
                vec[3] -= vector.vec[3];
                return *this;
            }

            inline Vector4& operator-=(float val)
            {
                vec[0] -= val;
                vec[1] -= val;
                vec[2] -= val;
                vec[3] -= val;
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 multiplication assignment operator                    //
            ////////////////////////////////////////////////////////////////////
            inline Vector4& operator*=(const Vector4& vector)
            {
                vec[0] *= vector.vec[0];
                vec[1] *= vector.vec[1];
                vec[2] *= vector.vec[2];
                vec[3] *= vector.vec[3];
                return *this;
            }

            inline Vector4& operator*=(float val)
            {
                vec[0] *= val;
                vec[1] *= val;
                vec[2] *= val;
                vec[3] *= val;
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 division assignment operator                          //
            ////////////////////////////////////////////////////////////////////
            inline Vector4& operator/=(const Vector4& vector)
            {
                if (vector.vec[0] != 0.0f)
                {
                    vec[0] /= vector.vec[0];
                }
                if (vector.vec[1] != 0.0f)
                {
                    vec[1] /= vector.vec[1];
                }
                if (vector.vec[2] != 0.0f)
                {
                    vec[2] /= vector.vec[2];
                }
                if (vector.vec[3] != 0.0f)
                {
                    vec[3] /= vector.vec[3];
                }
                return *this;
            }

            inline Vector4& operator/=(float val)
            {
                if (val != 0.0f)
                {
                    vec[0] /= val;
                    vec[1] /= val;
                    vec[2] /= val;
                    vec[3] /= val;
                }
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 equal to operator                                     //
            ////////////////////////////////////////////////////////////////////
            inline bool operator==(const Vector4& vector) const
            {
                return (
                    Math::areEqual(vec[0], vector.vec[0]) &&
                    Math::areEqual(vec[1], vector.vec[1]) &&
                    Math::areEqual(vec[2], vector.vec[2]) &&
                    Math::areEqual(vec[3], vector.vec[3])
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 not equal to operator                                 //
            ////////////////////////////////////////////////////////////////////
            inline bool operator!=(const Vector4& vector) const
            {
                return (!(
                    Math::areEqual(vec[0], vector.vec[0]) &&
                    Math::areEqual(vec[1], vector.vec[1]) &&
                    Math::areEqual(vec[2], vector.vec[2]) &&
                    Math::areEqual(vec[3], vector.vec[3]))
                );
            }


        public:
            float   vec[4];     // 4 components vector representation
    };


#endif // VOS_MATH_VECTOR4_HEADER
