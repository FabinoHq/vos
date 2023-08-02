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
            Vector4i(int64_t x, int64_t y, int64_t z, int64_t w)
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
            inline void set(int64_t x, int64_t y, int64_t z, int64_t w)
            {
                vec[0] = x;
                vec[1] = y;
                vec[2] = z;
                vec[3] = w;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector4i X component                                      //
            ////////////////////////////////////////////////////////////////////
            inline void setX(int64_t x)
            {
                vec[0] = x;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector4i Y component                                      //
            ////////////////////////////////////////////////////////////////////
            inline void setY(int64_t y)
            {
                vec[1] = y;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector4i Z component                                      //
            ////////////////////////////////////////////////////////////////////
            inline void setZ(int64_t z)
            {
                vec[2] = z;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector4i W component                                      //
            ////////////////////////////////////////////////////////////////////
            inline void setW(int64_t w)
            {
                vec[3] = w;
            }

            ////////////////////////////////////////////////////////////////////
            //  dotProduct : Get the dot product of this vector and another   //
            ////////////////////////////////////////////////////////////////////
            inline int64_t dotProduct(Vector4i& v) const
            {
                return (
                    (vec[0]*v.vec[0]) + (vec[1]*v.vec[1]) +
                    (vec[2]*v.vec[2]) + (vec[3]*v.vec[3])
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector4i length                                           //
            ////////////////////////////////////////////////////////////////////
            inline int64_t length() const
            {
                return Math::sqrt(
                    (vec[0]*vec[0]) + (vec[1]*vec[1]) +
                    (vec[2]*vec[2]) + (vec[3]*vec[3])
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Normalize Vector4i                                            //
            ////////////////////////////////////////////////////////////////////
            inline void normalize()
            {
                int64_t len = length();
                if (len != 0.0f)
                {
                    // Normalize between 0 and Math::OneInt
                    vec[0] = (vec[0] << Math::OneIntShift) / len;
                    vec[1] = (vec[1] << Math::OneIntShift) / len;
                    vec[2] = (vec[2] << Math::OneIntShift) / len;
                    vec[3] = (vec[3] << Math::OneIntShift) / len;
                }
            }


            ////////////////////////////////////////////////////////////////////
            //  Get Vector4i x component                                      //
            //  return : X component of the vector                            //
            ////////////////////////////////////////////////////////////////////
            inline int64_t& x()
            {
                return vec[0];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector4i y component                                      //
            //  return : Y component of the vector                            //
            ////////////////////////////////////////////////////////////////////
            inline int64_t& y()
            {
                return vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector4i z component                                      //
            //  return : Z component of the vector                            //
            ////////////////////////////////////////////////////////////////////
            inline int64_t& z()
            {
                return vec[2];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector4i w component                                      //
            //  return : W component of the vector                            //
            ////////////////////////////////////////////////////////////////////
            inline int64_t& w()
            {
                return vec[3];
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

            inline Vector4i& operator=(int64_t val)
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

            inline Vector4i operator+(int64_t val) const
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

            inline Vector4i operator-(int64_t val) const
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

            inline Vector4i operator*(int64_t val) const
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

            inline Vector4i operator/(int64_t val) const
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

            inline Vector4i& operator+=(int64_t val)
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

            inline Vector4i& operator-=(int64_t val)
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

            inline Vector4i& operator*=(int64_t val)
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

            inline Vector4i& operator/=(int64_t val)
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
            int64_t     vec[4];     // 4 components int vector representation
    };


#endif // VOS_MATH_VECTOR4I_HEADER
