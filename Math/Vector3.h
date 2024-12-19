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
//     Math/Vector3.h : 3 components vector management                        //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_MATH_VECTOR3_HEADER
#define VOS_MATH_VECTOR3_HEADER

    #include "../System/System.h"
    #include "Math.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Vector3 class definition                                              //
    ////////////////////////////////////////////////////////////////////////////
    class Vector3
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Vector3 default constructor                                   //
            ////////////////////////////////////////////////////////////////////
            Vector3()
            {
                vec[0] = 0.0f;
                vec[1] = 0.0f;
                vec[2] = 0.0f;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 copy constructor                                      //
            ////////////////////////////////////////////////////////////////////
            Vector3(const Vector3& vector)
            {
                vec[0] = vector.vec[0];
                vec[1] = vector.vec[1];
                vec[2] = vector.vec[2];
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 components constructor                                //
            ////////////////////////////////////////////////////////////////////
            Vector3(float x, float y, float z)
            {
                vec[0] = x;
                vec[1] = y;
                vec[2] = z;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 destructor                                            //
            ////////////////////////////////////////////////////////////////////
            ~Vector3()
            {
                vec[0] = 0.0f;
                vec[1] = 0.0f;
                vec[2] = 0.0f;
            }


            ////////////////////////////////////////////////////////////////////
            //  Reset Vector3 to zero                                         //
            ////////////////////////////////////////////////////////////////////
            inline void reset()
            {
                vec[0] = 0.0f;
                vec[1] = 0.0f;
                vec[2] = 0.0f;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector3 components from a vector                          //
            ////////////////////////////////////////////////////////////////////
            inline void set(const Vector3& vector)
            {
                vec[0] = vector.vec[0];
                vec[1] = vector.vec[1];
                vec[2] = vector.vec[2];
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector3 components from X, Y and Z components             //
            ////////////////////////////////////////////////////////////////////
            inline void set(float x, float y, float z)
            {
                vec[0] = x;
                vec[1] = y;
                vec[2] = z;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector3 components from a single value                    //
            ////////////////////////////////////////////////////////////////////
            inline void set(float val)
            {
                vec[0] = val;
                vec[1] = val;
                vec[2] = val;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector3 X component                                       //
            ////////////////////////////////////////////////////////////////////
            inline void setX(float x)
            {
                vec[0] = x;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector3 Y component                                       //
            ////////////////////////////////////////////////////////////////////
            inline void setY(float y)
            {
                vec[1] = y;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector3 Z component                                       //
            ////////////////////////////////////////////////////////////////////
            inline void setZ(float z)
            {
                vec[2] = z;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector3 x component                                       //
            //  return : X component of the vector                            //
            ////////////////////////////////////////////////////////////////////
            inline float& x()
            {
                return vec[0];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector3 y component                                       //
            //  return : Y component of the vector                            //
            ////////////////////////////////////////////////////////////////////
            inline float& y()
            {
                return vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector3 z component                                       //
            //  return : Z component of the vector                            //
            ////////////////////////////////////////////////////////////////////
            inline float& z()
            {
                return vec[2];
            }


            ////////////////////////////////////////////////////////////////////
            //  Check if vector is equal to zero                              //
            ////////////////////////////////////////////////////////////////////
            inline bool isZero() const
            {
                return (
                    Math::areEqual(vec[0], 0.0f) &&
                    Math::areEqual(vec[1], 0.0f) &&
                    Math::areEqual(vec[2], 0.0f)
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
            }

            ////////////////////////////////////////////////////////////////////
            //  Get vector minimum value                                      //
            ////////////////////////////////////////////////////////////////////
            inline float min()
            {
                return Math::min(vec[0], Math::min(vec[1], vec[2]));
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector minimum value between itself and min value         //
            ////////////////////////////////////////////////////////////////////
            inline void min(float min)
            {
                vec[0] = Math::min(vec[0], min);
                vec[1] = Math::min(vec[1], min);
                vec[2] = Math::min(vec[2], min);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector minimum value between itself and min vector        //
            ////////////////////////////////////////////////////////////////////
            inline void min(const Vector3& min)
            {
                vec[0] = Math::min(vec[0], min.vec[0]);
                vec[1] = Math::min(vec[1], min.vec[1]);
                vec[2] = Math::min(vec[2], min.vec[2]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector minimum value between itself and min X Y Z         //
            ////////////////////////////////////////////////////////////////////
            inline void min(float minX, float minY, float minZ)
            {
                vec[0] = Math::min(vec[0], minX);
                vec[1] = Math::min(vec[1], minY);
                vec[2] = Math::min(vec[2], minZ);
            }

            ////////////////////////////////////////////////////////////////////
            //  Get vector maximum value                                      //
            ////////////////////////////////////////////////////////////////////
            inline float max()
            {
                return Math::max(vec[0], Math::max(vec[1], vec[2]));
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector maximum value between itself and max value         //
            ////////////////////////////////////////////////////////////////////
            inline void max(float max)
            {
                vec[0] = Math::max(vec[0], max);
                vec[1] = Math::max(vec[1], max);
                vec[2] = Math::max(vec[2], max);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector maximum value between itself and max vector        //
            ////////////////////////////////////////////////////////////////////
            inline void max(const Vector3& max)
            {
                vec[0] = Math::max(vec[0], max.vec[0]);
                vec[1] = Math::max(vec[1], max.vec[1]);
                vec[2] = Math::max(vec[2], max.vec[2]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector maximum value between itself and max X Y           //
            ////////////////////////////////////////////////////////////////////
            inline void max(float maxX, float maxY, float maxZ)
            {
                vec[0] = Math::max(vec[0], maxX);
                vec[1] = Math::max(vec[1], maxY);
                vec[2] = Math::max(vec[2], maxZ);
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp vector between min and max                              //
            ////////////////////////////////////////////////////////////////////
            inline void clamp(float min, float max)
            {
                vec[0] = Math::clamp(vec[0], min, max);
                vec[1] = Math::clamp(vec[1], min, max);
                vec[2] = Math::clamp(vec[2], min, max);
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp vector between min and max vectors                      //
            ////////////////////////////////////////////////////////////////////
            inline void clamp(const Vector3& min, const Vector3& max)
            {
                vec[0] = Math::clamp(vec[0], min.vec[0], max.vec[0]);
                vec[1] = Math::clamp(vec[1], min.vec[1], max.vec[1]);
                vec[2] = Math::clamp(vec[2], min.vec[2], max.vec[2]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp vector between min and max X Y Z components             //
            ////////////////////////////////////////////////////////////////////
            inline void clamp(float minX, float minY, float minZ,
                float maxX, float maxY, float maxZ)
            {
                vec[0] = Math::clamp(vec[0], minX, maxX);
                vec[1] = Math::clamp(vec[1], minY, maxY);
                vec[2] = Math::clamp(vec[2], minZ, maxZ);
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp vector by absolute max value                            //
            ////////////////////////////////////////////////////////////////////
            inline void clampAbs(float max)
            {
                vec[0] = Math::clampAbs(vec[0], max);
                vec[1] = Math::clampAbs(vec[1], max);
                vec[2] = Math::clampAbs(vec[2], max);
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp vector by absolute max vector                           //
            ////////////////////////////////////////////////////////////////////
            inline void clampAbs(const Vector3& max)
            {
                vec[0] = Math::clampAbs(vec[0], max.vec[0]);
                vec[1] = Math::clampAbs(vec[1], max.vec[1]);
                vec[2] = Math::clampAbs(vec[2], max.vec[2]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp vector by absolute max X Y Z components                 //
            ////////////////////////////////////////////////////////////////////
            inline void clampAbs(float maxX, float maxY, float maxZ)
            {
                vec[0] = Math::clampAbs(vec[0], maxX);
                vec[1] = Math::clampAbs(vec[1], maxY);
                vec[2] = Math::clampAbs(vec[2], maxZ);
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
            //  linearInterp : Linear interpolation                           //
            ////////////////////////////////////////////////////////////////////
            inline void linearInterp(
                const Vector3& v1, const Vector3& v2, float t)
            {
                vec[0] = v1.vec[0] + t*(v2.vec[0]-v1.vec[0]);
                vec[1] = v1.vec[1] + t*(v2.vec[1]-v1.vec[1]);
                vec[2] = v1.vec[2] + t*(v2.vec[2]-v1.vec[2]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Angle linear interpolation                                    //
            ////////////////////////////////////////////////////////////////////
            inline void angleLinearInterp(
                const Vector3& v1, const Vector3& v2, float t)
            {
                vec[0] = Math::angleLinearInterp(v1.vec[0], v2.vec[0], t);
                vec[1] = Math::angleLinearInterp(v1.vec[1], v2.vec[1], t);
                vec[2] = Math::angleLinearInterp(v1.vec[2], v2.vec[2], t);
            }

            ////////////////////////////////////////////////////////////////////
            //  Cubic interpolation                                           //
            ////////////////////////////////////////////////////////////////////
            inline void cubicInterp(
                const Vector3& v1, const Vector3& v2, float t)
            {
                vec[0] = v1.vec[0] + (t*t*(3.0f-2.0f*t))*(v2.vec[0]-v1.vec[0]);
                vec[1] = v1.vec[1] + (t*t*(3.0f-2.0f*t))*(v2.vec[1]-v1.vec[1]);
                vec[2] = v1.vec[2] + (t*t*(3.0f-2.0f*t))*(v2.vec[2]-v1.vec[2]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Hermit interpolation                                          //
            ////////////////////////////////////////////////////////////////////
            inline void hermitInterp(
                const Vector3& v0, const Vector3& v1,
                const Vector3& v2, const Vector3& v3, float t)
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
            }

            ////////////////////////////////////////////////////////////////////
            //  Get the dot product of this vector and another                //
            ////////////////////////////////////////////////////////////////////
            inline float dotProduct(const Vector3& v) const
            {
                return (
                    (vec[0]*v.vec[0]) + (vec[1]*v.vec[1]) + (vec[2]*v.vec[2])
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Set this vector as the cross product from 2 vectors           //
            ////////////////////////////////////////////////////////////////////
            inline void crossProduct(const Vector3& v1, const Vector3& v2)
            {
                vec[0] = ((v2.vec[1]*v1.vec[2]) - (v2.vec[2]*v1.vec[1]));
                vec[1] = ((v2.vec[2]*v1.vec[0]) - (v2.vec[0]*v1.vec[2]));
                vec[2] = ((v2.vec[0]*v1.vec[1]) - (v2.vec[1]*v1.vec[0]));
            }

            ////////////////////////////////////////////////////////////////////
            //  Set this vector as the cross product from a vector and upward //
            ////////////////////////////////////////////////////////////////////
            inline void crossUpward(const Vector3& v)
            {
                vec[0] = v.vec[2];
                vec[1] = 0.0f;
                vec[2] = -v.vec[0];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector3 length                                            //
            ////////////////////////////////////////////////////////////////////
            inline float length() const
            {
                return Math::sqrt(
                    (vec[0]*vec[0]) + (vec[1]*vec[1]) + (vec[2]*vec[2])
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector3 squared length                                    //
            ////////////////////////////////////////////////////////////////////
            inline float squaredLength() const
            {
                return (
                    (vec[0]*vec[0]) + (vec[1]*vec[1]) + (vec[2]*vec[2])
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Normalize Vector3                                             //
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
                }
            }


            ////////////////////////////////////////////////////////////////////
            //  Vector3 affectation operator                                  //
            ////////////////////////////////////////////////////////////////////
            inline Vector3& operator=(const Vector3& vector)
            {
                vec[0] = vector.vec[0];
                vec[1] = vector.vec[1];
                vec[2] = vector.vec[2];
                return *this;
            }

            inline Vector3& operator=(float val)
            {
                vec[0] = val;
                vec[1] = val;
                vec[2] = val;
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 addition operator                                     //
            ////////////////////////////////////////////////////////////////////
            inline Vector3 operator+(const Vector3& vector) const
            {
                return Vector3(
                    vec[0]+vector.vec[0],
                    vec[1]+vector.vec[1],
                    vec[2]+vector.vec[2]
                );
            }

            inline Vector3 operator+(float val) const
            {
                return Vector3(vec[0]+val, vec[1]+val, vec[2]+val);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 subtraction operator                                  //
            ////////////////////////////////////////////////////////////////////
            inline Vector3 operator-(const Vector3& vector) const
            {
                return Vector3(
                    vec[0]-vector.vec[0],
                    vec[1]-vector.vec[1],
                    vec[2]-vector.vec[2]
                );
            }

            inline Vector3 operator-(float val) const
            {
                return Vector3(vec[0]-val, vec[1]-val, vec[2]-val);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 unary plus operator                                   //
            ////////////////////////////////////////////////////////////////////
            inline Vector3 operator+() const
            {
                return Vector3(*this);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 unary minus operator                                  //
            ////////////////////////////////////////////////////////////////////
            inline Vector3 operator-() const
            {
                return Vector3(-vec[0], -vec[1], -vec[2]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 multiplication operator                               //
            ////////////////////////////////////////////////////////////////////
            inline Vector3 operator*(const Vector3& vector) const
            {
                return Vector3(
                    vec[0]*vector.vec[0],
                    vec[1]*vector.vec[1],
                    vec[2]*vector.vec[2]
                );
            }

            inline Vector3 operator*(float val) const
            {
                return Vector3(vec[0]*val, vec[1]*val, vec[2]*val);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 division operator                                     //
            ////////////////////////////////////////////////////////////////////
            inline Vector3 operator/(const Vector3& vector) const
            {
                Vector3 result(*this);
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
                return result;
            }

            inline Vector3 operator/(float val) const
            {
                Vector3 result(*this);
                if (val != 0.0f)
                {
                    result.vec[0] /= val;
                    result.vec[1] /= val;
                    result.vec[2] /= val;
                }
                return result;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 prefix increment operator                             //
            ////////////////////////////////////////////////////////////////////
            inline Vector3& operator++()
            {
                ++vec[0];
                ++vec[1];
                ++vec[2];
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 postfix increment operator                            //
            ////////////////////////////////////////////////////////////////////
            inline Vector3 operator++(int)
            {
                return Vector3(vec[0]++, vec[1]++, vec[2]++);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 prefix decrement operator                             //
            ////////////////////////////////////////////////////////////////////
            inline Vector3& operator--()
            {
                --vec[0];
                --vec[1];
                --vec[2];
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 postfix decrement operator                            //
            ////////////////////////////////////////////////////////////////////
            inline Vector3 operator--(int)
            {
                return Vector3(vec[0]--, vec[1]--, vec[2]--);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 addition assignment operator                          //
            ////////////////////////////////////////////////////////////////////
            inline Vector3& operator+=(const Vector3& vector)
            {
                vec[0] += vector.vec[0];
                vec[1] += vector.vec[1];
                vec[2] += vector.vec[2];
                return *this;
            }

            inline Vector3& operator+=(float val)
            {
                vec[0] += val;
                vec[1] += val;
                vec[2] += val;
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 subtraction assignment operator                       //
            ////////////////////////////////////////////////////////////////////
            inline Vector3& operator-=(const Vector3& vector)
            {
                vec[0] -= vector.vec[0];
                vec[1] -= vector.vec[1];
                vec[2] -= vector.vec[2];
                return *this;
            }

            inline Vector3& operator-=(float val)
            {
                vec[0] -= val;
                vec[1] -= val;
                vec[2] -= val;
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 multiplication assignment operator                    //
            ////////////////////////////////////////////////////////////////////
            inline Vector3& operator*=(const Vector3& vector)
            {
                vec[0] *= vector.vec[0];
                vec[1] *= vector.vec[1];
                vec[2] *= vector.vec[2];
                return *this;
            }

            inline Vector3& operator*=(float val)
            {
                vec[0] *= val;
                vec[1] *= val;
                vec[2] *= val;
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 division assignment operator                          //
            ////////////////////////////////////////////////////////////////////
            inline Vector3& operator/=(const Vector3& vector)
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
                return *this;
            }

            inline Vector3& operator/=(float val)
            {
                if (val != 0.0f)
                {
                    vec[0] /= val;
                    vec[1] /= val;
                    vec[2] /= val;
                }
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 equal to operator                                     //
            ////////////////////////////////////////////////////////////////////
            inline bool operator==(const Vector3& vector) const
            {
                return (
                    Math::areEqual(vec[0], vector.vec[0]) &&
                    Math::areEqual(vec[1], vector.vec[1]) &&
                    Math::areEqual(vec[2], vector.vec[2])
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 not equal to operator                                 //
            ////////////////////////////////////////////////////////////////////
            inline bool operator!=(const Vector3& vector) const
            {
                return (!(
                    Math::areEqual(vec[0], vector.vec[0]) &&
                    Math::areEqual(vec[1], vector.vec[1]) &&
                    Math::areEqual(vec[2], vector.vec[2]))
                );
            }


        public:
            float   vec[3];     // 3 components vector representation
    };


#endif // VOS_MATH_VECTOR3_HEADER
