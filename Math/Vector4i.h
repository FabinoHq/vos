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
//     Math/Vector4i.h : 4 components int vector management                   //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_MATH_VECTOR4I_HEADER
#define VOS_MATH_VECTOR4I_HEADER

    #include "../System/System.h"
    #include "Math.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Vector4i class definition                                             //
    ////////////////////////////////////////////////////////////////////////////
    class Vector4i
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Vector4i default constructor                                  //
            ////////////////////////////////////////////////////////////////////
            Vector4i()
            {
                vec[0] = 0;
                vec[1] = 0;
                vec[2] = 0;
                vec[3] = 0;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4i copy constructor                                     //
            ////////////////////////////////////////////////////////////////////
            Vector4i(const Vector4i& vector)
            {
                vec[0] = vector.vec[0];
                vec[1] = vector.vec[1];
                vec[2] = vector.vec[2];
                vec[3] = vector.vec[3];
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4i components constructor                               //
            ////////////////////////////////////////////////////////////////////
            Vector4i(int32_t x, int32_t y, int32_t z, int32_t w)
            {
                vec[0] = x;
                vec[1] = y;
                vec[2] = z;
                vec[3] = w;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4i destructor                                           //
            ////////////////////////////////////////////////////////////////////
            ~Vector4i()
            {
                vec[0] = 0;
                vec[1] = 0;
                vec[2] = 0;
                vec[3] = 0;
            }


            ////////////////////////////////////////////////////////////////////
            //  Reset Vector4i to zero                                        //
            ////////////////////////////////////////////////////////////////////
            inline void reset()
            {
                vec[0] = 0;
                vec[1] = 0;
                vec[2] = 0;
                vec[3] = 0;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector4i components from a vector                         //
            ////////////////////////////////////////////////////////////////////
            inline void set(const Vector4i& vector)
            {
                vec[0] = vector.vec[0];
                vec[1] = vector.vec[1];
                vec[2] = vector.vec[2];
                vec[3] = vector.vec[3];
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector4i components from X, Y, Z and W components         //
            ////////////////////////////////////////////////////////////////////
            inline void set(int32_t x, int32_t y, int32_t z, int32_t w)
            {
                vec[0] = x;
                vec[1] = y;
                vec[2] = z;
                vec[3] = w;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector4i components from a single value                   //
            ////////////////////////////////////////////////////////////////////
            inline void set(int32_t val)
            {
                vec[0] = val;
                vec[1] = val;
                vec[2] = val;
                vec[4] = val;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector4i X component                                      //
            ////////////////////////////////////////////////////////////////////
            inline void setX(int32_t x)
            {
                vec[0] = x;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector4i Y component                                      //
            ////////////////////////////////////////////////////////////////////
            inline void setY(int32_t y)
            {
                vec[1] = y;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector4i Z component                                      //
            ////////////////////////////////////////////////////////////////////
            inline void setZ(int32_t z)
            {
                vec[2] = z;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector4i W component                                      //
            ////////////////////////////////////////////////////////////////////
            inline void setW(int32_t w)
            {
                vec[3] = w;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector4i x component                                      //
            //  return : X component of the vector                            //
            ////////////////////////////////////////////////////////////////////
            inline int32_t& x()
            {
                return vec[0];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector4i y component                                      //
            //  return : Y component of the vector                            //
            ////////////////////////////////////////////////////////////////////
            inline int32_t& y()
            {
                return vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector4i z component                                      //
            //  return : Z component of the vector                            //
            ////////////////////////////////////////////////////////////////////
            inline int32_t& z()
            {
                return vec[2];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector4i w component                                      //
            //  return : W component of the vector                            //
            ////////////////////////////////////////////////////////////////////
            inline int32_t& w()
            {
                return vec[3];
            }


            ////////////////////////////////////////////////////////////////////
            //  Check if vector is equal to zero                              //
            ////////////////////////////////////////////////////////////////////
            inline bool isZero() const
            {
                return (
                    (vec[0] == 0) && (vec[1] == 0) &&
                    (vec[2] == 0) && (vec[3] == 0)
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
            inline int32_t min()
            {
                return Math::min(vec[0], Math::min(vec[1],
                    Math::min(vec[2], vec[3])));
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector minimum value between itself and min value         //
            ////////////////////////////////////////////////////////////////////
            inline void min(int32_t min)
            {
                vec[0] = Math::min(vec[0], min);
                vec[1] = Math::min(vec[1], min);
                vec[2] = Math::min(vec[2], min);
                vec[3] = Math::min(vec[3], min);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector minimum value between itself and min vector        //
            ////////////////////////////////////////////////////////////////////
            inline void min(const Vector4i& min)
            {
                vec[0] = Math::min(vec[0], min.vec[0]);
                vec[1] = Math::min(vec[1], min.vec[1]);
                vec[2] = Math::min(vec[2], min.vec[2]);
                vec[3] = Math::min(vec[3], min.vec[3]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector minimum value between itself and min X Y Z W       //
            ////////////////////////////////////////////////////////////////////
            inline void min(
                int32_t minX, int32_t minY, int32_t minZ, int32_t minW)
            {
                vec[0] = Math::min(vec[0], minX);
                vec[1] = Math::min(vec[1], minY);
                vec[2] = Math::min(vec[2], minZ);
                vec[3] = Math::min(vec[4], minW);
            }

            ////////////////////////////////////////////////////////////////////
            //  Get vector maximum value                                      //
            ////////////////////////////////////////////////////////////////////
            inline int32_t max()
            {
                return Math::max(vec[0], Math::max(vec[1],
                    Math::max(vec[2], vec[3])));
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector maximum value between itself and max value         //
            ////////////////////////////////////////////////////////////////////
            inline void max(int32_t max)
            {
                vec[0] = Math::max(vec[0], max);
                vec[1] = Math::max(vec[1], max);
                vec[2] = Math::max(vec[2], max);
                vec[3] = Math::max(vec[3], max);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector maximum value between itself and max vector        //
            ////////////////////////////////////////////////////////////////////
            inline void max(const Vector4i& max)
            {
                vec[0] = Math::max(vec[0], max.vec[0]);
                vec[1] = Math::max(vec[1], max.vec[1]);
                vec[2] = Math::max(vec[2], max.vec[2]);
                vec[3] = Math::max(vec[3], max.vec[3]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set vector maximum value between itself and max X Y           //
            ////////////////////////////////////////////////////////////////////
            inline void max(
                int32_t maxX, int32_t maxY, int32_t maxZ, int32_t maxW)
            {
                vec[0] = Math::max(vec[0], maxX);
                vec[1] = Math::max(vec[1], maxY);
                vec[2] = Math::max(vec[2], maxZ);
                vec[3] = Math::max(vec[3], maxW);
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp vector between min and max                              //
            ////////////////////////////////////////////////////////////////////
            inline void clamp(int32_t min, int32_t max)
            {
                vec[0] = Math::clamp(vec[0], min, max);
                vec[1] = Math::clamp(vec[1], min, max);
                vec[2] = Math::clamp(vec[2], min, max);
                vec[3] = Math::clamp(vec[3], min, max);
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp vector between min and max vectors                      //
            ////////////////////////////////////////////////////////////////////
            inline void clamp(const Vector4i& min, const Vector4i& max)
            {
                vec[0] = Math::clamp(vec[0], min.vec[0], max.vec[0]);
                vec[1] = Math::clamp(vec[1], min.vec[1], max.vec[1]);
                vec[2] = Math::clamp(vec[2], min.vec[2], max.vec[2]);
                vec[3] = Math::clamp(vec[3], min.vec[3], max.vec[3]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp vector between min and max X Y Z W components           //
            ////////////////////////////////////////////////////////////////////
            inline void clamp(
                int32_t minX, int32_t minY, int32_t minZ, int32_t minW,
                int32_t maxX, int32_t maxY, int32_t maxZ, int32_t maxW)
            {
                vec[0] = Math::clamp(vec[0], minX, maxX);
                vec[1] = Math::clamp(vec[1], minY, maxY);
                vec[2] = Math::clamp(vec[2], minZ, maxZ);
                vec[3] = Math::clamp(vec[3], minW, maxW);
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp vector by absolute max value                            //
            ////////////////////////////////////////////////////////////////////
            inline void clampAbs(int32_t max)
            {
                vec[0] = Math::clampAbs(vec[0], max);
                vec[1] = Math::clampAbs(vec[1], max);
                vec[2] = Math::clampAbs(vec[2], max);
                vec[3] = Math::clampAbs(vec[3], max);
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp vector by absolute max vector                           //
            ////////////////////////////////////////////////////////////////////
            inline void clampAbs(const Vector4i& max)
            {
                vec[0] = Math::clampAbs(vec[0], max.vec[0]);
                vec[1] = Math::clampAbs(vec[1], max.vec[1]);
                vec[2] = Math::clampAbs(vec[2], max.vec[2]);
                vec[3] = Math::clampAbs(vec[3], max.vec[3]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp vector by absolute max X Y Z W components               //
            ////////////////////////////////////////////////////////////////////
            inline void clampAbs(
                int32_t maxX, int32_t maxY, int32_t maxZ, int32_t maxW)
            {
                vec[0] = Math::clampAbs(vec[0], maxX);
                vec[1] = Math::clampAbs(vec[1], maxY);
                vec[2] = Math::clampAbs(vec[2], maxZ);
                vec[3] = Math::clampAbs(vec[3], maxW);
            }

            ////////////////////////////////////////////////////////////////////
            //  Move components towards a specified value                     //
            ////////////////////////////////////////////////////////////////////
            inline void moveTowards(int32_t val, int32_t delta)
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
            inline void moveXTowards(int32_t val, int32_t delta)
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
            inline void moveYTowards(int32_t val, int32_t delta)
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
            inline void moveZTowards(int32_t val, int32_t delta)
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
            inline void moveWTowards(int32_t val, int32_t delta)
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
            //  Get the dot product of this vector and another                //
            ////////////////////////////////////////////////////////////////////
            inline int64_t dotProduct(const Vector4i& v) const
            {
                return (
                    (static_cast<int64_t>(vec[0])*
                    static_cast<int64_t>(v.vec[0]))+
                    (static_cast<int64_t>(vec[1])*
                    static_cast<int64_t>(v.vec[1]))+
                    (static_cast<int64_t>(vec[2])*
                    static_cast<int64_t>(v.vec[2]))+
                    (static_cast<int64_t>(vec[3])*
                    static_cast<int64_t>(v.vec[3]))
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector4i length                                           //
            ////////////////////////////////////////////////////////////////////
            inline int64_t length() const
            {
                return Math::sqrt(
                    (static_cast<int64_t>(vec[0])*static_cast<int64_t>(vec[0]))+
                    (static_cast<int64_t>(vec[1])*static_cast<int64_t>(vec[1]))+
                    (static_cast<int64_t>(vec[2])*static_cast<int64_t>(vec[2]))+
                    (static_cast<int64_t>(vec[3])*static_cast<int64_t>(vec[3]))
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector4i squared length                                   //
            ////////////////////////////////////////////////////////////////////
            inline int64_t squaredLength() const
            {
                return (
                    (static_cast<int64_t>(vec[0])*static_cast<int64_t>(vec[0]))+
                    (static_cast<int64_t>(vec[1])*static_cast<int64_t>(vec[1]))+
                    (static_cast<int64_t>(vec[2])*static_cast<int64_t>(vec[2]))+
                    (static_cast<int64_t>(vec[3])*static_cast<int64_t>(vec[3]))
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Normalize Vector4i                                            //
            ////////////////////////////////////////////////////////////////////
            inline void normalize()
            {
                int64_t len = length();
                if (len != 0)
                {
                    vec[0] = static_cast<int32_t>(
                        (static_cast<int64_t>(vec[0])<<Math::OneIntShift) / len
                    );
                    vec[1] = static_cast<int32_t>(
                        (static_cast<int64_t>(vec[1])<<Math::OneIntShift) / len
                    );
                    vec[2] = static_cast<int32_t>(
                        (static_cast<int64_t>(vec[2])<<Math::OneIntShift) / len
                    );
                    vec[3] = static_cast<int32_t>(
                        (static_cast<int64_t>(vec[3])<<Math::OneIntShift) / len
                    );
                }
            }


            ////////////////////////////////////////////////////////////////////
            //  Vector4i affectation operator                                 //
            ////////////////////////////////////////////////////////////////////
            inline Vector4i& operator=(const Vector4i& vector)
            {
                vec[0] = vector.vec[0];
                vec[1] = vector.vec[1];
                vec[2] = vector.vec[2];
                vec[3] = vector.vec[3];
                return *this;
            }

            inline Vector4i& operator=(int32_t val)
            {
                vec[0] = val;
                vec[1] = val;
                vec[2] = val;
                vec[3] = val;
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4i addition operator                                    //
            ////////////////////////////////////////////////////////////////////
            inline Vector4i operator+(const Vector4i& vector) const
            {
                return Vector4i(
                    vec[0]+vector.vec[0], vec[1]+vector.vec[1],
                    vec[2]+vector.vec[2], vec[3]+vector.vec[3]
                );
            }

            inline Vector4i operator+(int32_t val) const
            {
                return Vector4i(vec[0]+val, vec[1]+val, vec[2]+val, vec[3]+val);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4i subtraction operator                                 //
            ////////////////////////////////////////////////////////////////////
            inline Vector4i operator-(const Vector4i& vector) const
            {
                return Vector4i(
                    vec[0]-vector.vec[0], vec[1]-vector.vec[1],
                    vec[2]-vector.vec[2], vec[3]-vector.vec[3]
                );
            }

            inline Vector4i operator-(int32_t val) const
            {
                return Vector4i(vec[0]-val, vec[1]-val, vec[2]-val, vec[3]-val);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4i unary plus operator                                  //
            ////////////////////////////////////////////////////////////////////
            inline Vector4i operator+() const
            {
                return Vector4i(*this);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4i unary minus operator                                 //
            ////////////////////////////////////////////////////////////////////
            inline Vector4i operator-() const
            {
                return Vector4i(-vec[0], -vec[1], -vec[2], -vec[3]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4i multiplication operator                              //
            ////////////////////////////////////////////////////////////////////
            inline Vector4i operator*(const Vector4i& vector) const
            {
                return Vector4i(
                    vec[0]*vector.vec[0], vec[1]*vector.vec[1],
                    vec[2]*vector.vec[2], vec[3]*vector.vec[3]
                );
            }

            inline Vector4i operator*(int32_t val) const
            {
                return Vector4i(vec[0]*val, vec[1]*val, vec[2]*val, vec[3]*val);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4i division operator                                    //
            ////////////////////////////////////////////////////////////////////
            inline Vector4i operator/(const Vector4i& vector) const
            {
                Vector4i result(*this);
                if (vector.vec[0] != 0)
                {
                    result.vec[0] /= vector.vec[0];
                }
                if (vector.vec[1] != 0)
                {
                    result.vec[1] /= vector.vec[1];
                }
                if (vector.vec[2] != 0)
                {
                    result.vec[2] /= vector.vec[2];
                }
                if (vector.vec[3] != 0)
                {
                    result.vec[3] /= vector.vec[3];
                }
                return result;
            }

            inline Vector4i operator/(int32_t val) const
            {
                Vector4i result(*this);
                if (val != 0)
                {
                    result.vec[0] /= val;
                    result.vec[1] /= val;
                    result.vec[2] /= val;
                    result.vec[3] /= val;
                }
                return result;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4i prefix increment operator                            //
            ////////////////////////////////////////////////////////////////////
            inline Vector4i& operator++()
            {
                ++vec[0];
                ++vec[1];
                ++vec[2];
                ++vec[3];
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4i postfix increment operator                           //
            ////////////////////////////////////////////////////////////////////
            inline Vector4i operator++(int)
            {
                return Vector4i(vec[0]++, vec[1]++, vec[2]++, vec[3]++);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4i prefix decrement operator                            //
            ////////////////////////////////////////////////////////////////////
            inline Vector4i& operator--()
            {
                --vec[0];
                --vec[1];
                --vec[2];
                --vec[3];
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4i postfix decrement operator                           //
            ////////////////////////////////////////////////////////////////////
            inline Vector4i operator--(int)
            {
                return Vector4i(vec[0]--, vec[1]--, vec[2]--, vec[3]--);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4i addition assignment operator                         //
            ////////////////////////////////////////////////////////////////////
            inline Vector4i& operator+=(const Vector4i& vector)
            {
                vec[0] += vector.vec[0];
                vec[1] += vector.vec[1];
                vec[2] += vector.vec[2];
                vec[3] += vector.vec[3];
                return *this;
            }

            inline Vector4i& operator+=(int32_t val)
            {
                vec[0] += val;
                vec[1] += val;
                vec[2] += val;
                vec[3] += val;
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4i subtraction assignment operator                      //
            ////////////////////////////////////////////////////////////////////
            inline Vector4i& operator-=(const Vector4i& vector)
            {
                vec[0] -= vector.vec[0];
                vec[1] -= vector.vec[1];
                vec[2] -= vector.vec[2];
                vec[3] -= vector.vec[3];
                return *this;
            }

            inline Vector4i& operator-=(int32_t val)
            {
                vec[0] -= val;
                vec[1] -= val;
                vec[2] -= val;
                vec[3] -= val;
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4i multiplication assignment operator                   //
            ////////////////////////////////////////////////////////////////////
            inline Vector4i& operator*=(const Vector4i& vector)
            {
                vec[0] *= vector.vec[0];
                vec[1] *= vector.vec[1];
                vec[2] *= vector.vec[2];
                vec[3] *= vector.vec[3];
                return *this;
            }

            inline Vector4i& operator*=(int32_t val)
            {
                vec[0] *= val;
                vec[1] *= val;
                vec[2] *= val;
                vec[3] *= val;
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4i division assignment operator                         //
            ////////////////////////////////////////////////////////////////////
            inline Vector4i& operator/=(const Vector4i& vector)
            {
                if (vector.vec[0] != 0)
                {
                    vec[0] /= vector.vec[0];
                }
                if (vector.vec[1] != 0)
                {
                    vec[1] /= vector.vec[1];
                }
                if (vector.vec[2] != 0)
                {
                    vec[2] /= vector.vec[2];
                }
                if (vector.vec[3] != 0)
                {
                    vec[3] /= vector.vec[3];
                }
                return *this;
            }

            inline Vector4i& operator/=(int32_t val)
            {
                if (val != 0)
                {
                    vec[0] /= val;
                    vec[1] /= val;
                    vec[2] /= val;
                    vec[3] /= val;
                }
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4i equal to operator                                    //
            ////////////////////////////////////////////////////////////////////
            inline bool operator==(const Vector4i& vector) const
            {
                return (
                    (vec[0] == vector.vec[0]) &&
                    (vec[1] == vector.vec[1]) &&
                    (vec[2] == vector.vec[2]) &&
                    (vec[3] == vector.vec[3])
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4i not equal to operator                                //
            ////////////////////////////////////////////////////////////////////
            inline bool operator!=(const Vector4i& vector) const
            {
                return (
                    (vec[0] != vector.vec[0]) ||
                    (vec[1] != vector.vec[1]) ||
                    (vec[2] != vector.vec[2]) ||
                    (vec[3] != vector.vec[3])
                );
            }


        public:
            int32_t     vec[4];     // 4 components int vector representation
    };


#endif // VOS_MATH_VECTOR4I_HEADER
