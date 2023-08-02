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
//     Math/Vector3i.h : 3 components int vector management                   //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_MATH_VECTOR3I_HEADER
#define VOS_MATH_VECTOR3I_HEADER

    #include "../System/System.h"
    #include "Math.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Vector3i class definition                                             //
    ////////////////////////////////////////////////////////////////////////////
    class Vector3i
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Vector3i default constructor                                  //
            ////////////////////////////////////////////////////////////////////
            Vector3i()
            {
                vec[0] = 0;
                vec[1] = 0;
                vec[2] = 0;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3i copy constructor                                     //
            ////////////////////////////////////////////////////////////////////
            Vector3i(const Vector3i& vector)
            {
                vec[0] = vector.vec[0];
                vec[1] = vector.vec[1];
                vec[2] = vector.vec[2];
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3i components constructor                               //
            ////////////////////////////////////////////////////////////////////
            Vector3i(int64_t x, int64_t y, int64_t z)
            {
                vec[0] = x;
                vec[1] = y;
                vec[2] = z;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3i destructor                                           //
            ////////////////////////////////////////////////////////////////////
            ~Vector3i()
            {
                vec[0] = 0;
                vec[1] = 0;
                vec[2] = 0;
            }


            ////////////////////////////////////////////////////////////////////
            //  Reset Vector3i to zero                                        //
            ////////////////////////////////////////////////////////////////////
            inline void reset()
            {
                vec[0] = 0;
                vec[1] = 0;
                vec[2] = 0;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector3i components from a vector                         //
            ////////////////////////////////////////////////////////////////////
            inline void set(const Vector3i& vector)
            {
                vec[0] = vector.vec[0];
                vec[1] = vector.vec[1];
                vec[2] = vector.vec[2];
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector3i components from X, Y and Z components            //
            ////////////////////////////////////////////////////////////////////
            inline void set(int64_t x, int64_t y, int64_t z)
            {
                vec[0] = x;
                vec[1] = y;
                vec[2] = z;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector3i X component                                      //
            ////////////////////////////////////////////////////////////////////
            inline void setX(int64_t x)
            {
                vec[0] = x;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector3i Y component                                      //
            ////////////////////////////////////////////////////////////////////
            inline void setY(int64_t y)
            {
                vec[1] = y;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Vector3i Z component                                      //
            ////////////////////////////////////////////////////////////////////
            inline void setZ(int64_t z)
            {
                vec[2] = z;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get the dot product of this vector and another                //
            ////////////////////////////////////////////////////////////////////
            inline int64_t dotProduct(Vector3i& v) const
            {
                return (
                    (vec[0]*v.vec[0]) + (vec[1]*v.vec[1]) + (vec[2]*v.vec[2])
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Set this vector as a cross product from 2 vectors             //
            ////////////////////////////////////////////////////////////////////
            inline void crossProduct(Vector3i& v1, Vector3i& v2)
            {
                vec[0] = ((v2.vec[1]*v1.vec[2]) - (v2.vec[2]*v1.vec[1]));
                vec[1] = ((v2.vec[2]*v1.vec[0]) - (v2.vec[0]*v1.vec[2]));
                vec[2] = ((v2.vec[0]*v1.vec[1]) - (v2.vec[1]*v1.vec[0]));
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector3i length                                           //
            ////////////////////////////////////////////////////////////////////
            inline int64_t length() const
            {
                return Math::sqrt(
                    (vec[0]*vec[0]) + (vec[1]*vec[1]) + (vec[2]*vec[2])
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Normalize Vector3i                                            //
            ////////////////////////////////////////////////////////////////////
            inline void normalize()
            {
                int64_t len = length();
                if (len != 0)
                {
                    // Normalize between 0 and Math::OneInt
                    vec[0] = (vec[0] << Math::OneIntShift) / len;
                    vec[1] = (vec[1] << Math::OneIntShift) / len;
                    vec[2] = (vec[2] << Math::OneIntShift) / len;
                }
            }


            ////////////////////////////////////////////////////////////////////
            //  Get Vector3i x component                                      //
            //  return : X component of the vector                            //
            ////////////////////////////////////////////////////////////////////
            inline int64_t& x()
            {
                return vec[0];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector3i y component                                      //
            //  return : Y component of the vector                            //
            ////////////////////////////////////////////////////////////////////
            inline int64_t& y()
            {
                return vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Vector3i z component                                      //
            //  return : Z component of the vector                            //
            ////////////////////////////////////////////////////////////////////
            inline int64_t& z()
            {
                return vec[2];
            }


            ////////////////////////////////////////////////////////////////////
            //  Vector3i affectation operator                                 //
            ////////////////////////////////////////////////////////////////////
            inline Vector3i& operator=(const Vector3i& vector)
            {
                vec[0] = vector.vec[0];
                vec[1] = vector.vec[1];
                vec[2] = vector.vec[2];
                return *this;
            }

            inline Vector3i& operator=(int64_t val)
            {
                vec[0] = val;
                vec[1] = val;
                vec[2] = val;
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3i addition operator                                    //
            ////////////////////////////////////////////////////////////////////
            inline Vector3i operator+(const Vector3i& vector) const
            {
                return Vector3i(
                    vec[0]+vector.vec[0],
                    vec[1]+vector.vec[1],
                    vec[2]+vector.vec[2]
                );
            }

            inline Vector3i operator+(int64_t val) const
            {
                return Vector3i(vec[0]+val, vec[1]+val, vec[2]+val);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3i subtraction operator                                 //
            ////////////////////////////////////////////////////////////////////
            inline Vector3i operator-(const Vector3i& vector) const
            {
                return Vector3i(
                    vec[0]-vector.vec[0],
                    vec[1]-vector.vec[1],
                    vec[2]-vector.vec[2]
                );
            }

            inline Vector3i operator-(int64_t val) const
            {
                return Vector3i(vec[0]-val, vec[1]-val, vec[2]-val);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3i unary plus operator                                  //
            ////////////////////////////////////////////////////////////////////
            inline Vector3i operator+() const
            {
                return Vector3i(*this);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3i unary minus operator                                 //
            ////////////////////////////////////////////////////////////////////
            inline Vector3i operator-() const
            {
                return Vector3i(-vec[0], -vec[1], -vec[2]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3i multiplication operator                              //
            ////////////////////////////////////////////////////////////////////
            inline Vector3i operator*(const Vector3i& vector) const
            {
                return Vector3i(vec[0]*vector.vec[0], vec[1]*vector.vec[1],
                    vec[2]*vector.vec[2]);
            }

            inline Vector3i operator*(int64_t val) const
            {
                return Vector3i(vec[0]*val, vec[1]*val, vec[2]*val);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3i division operator                                    //
            ////////////////////////////////////////////////////////////////////
            inline Vector3i operator/(const Vector3i& vector) const
            {
                Vector3i result(*this);
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
                return result;
            }

            inline Vector3i operator/(int64_t val) const
            {
                Vector3i result(*this);
                if (val != 0)
                {
                    result.vec[0] /= val;
                    result.vec[1] /= val;
                    result.vec[2] /= val;
                }
                return result;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3i prefix increment operator                            //
            ////////////////////////////////////////////////////////////////////
            inline Vector3i& operator++()
            {
                ++vec[0];
                ++vec[1];
                ++vec[2];
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3i postfix increment operator                           //
            ////////////////////////////////////////////////////////////////////
            inline Vector3i operator++(int)
            {
                return Vector3i(vec[0]++, vec[1]++, vec[2]++);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3i prefix decrement operator                            //
            ////////////////////////////////////////////////////////////////////
            inline Vector3i& operator--()
            {
                --vec[0];
                --vec[1];
                --vec[2];
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3i postfix decrement operator                           //
            ////////////////////////////////////////////////////////////////////
            inline Vector3i operator--(int)
            {
                return Vector3i(vec[0]--, vec[1]--, vec[2]--);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3i addition assignment operator                         //
            ////////////////////////////////////////////////////////////////////
            inline Vector3i& operator+=(const Vector3i& vector)
            {
                vec[0] += vector.vec[0];
                vec[1] += vector.vec[1];
                vec[2] += vector.vec[2];
                return *this;
            }

            inline Vector3i& operator+=(int64_t val)
            {
                vec[0] += val;
                vec[1] += val;
                vec[2] += val;
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3i subtraction assignment operator                      //
            ////////////////////////////////////////////////////////////////////
            inline Vector3i& operator-=(const Vector3i& vector)
            {
                vec[0] -= vector.vec[0];
                vec[1] -= vector.vec[1];
                vec[2] -= vector.vec[2];
                return *this;
            }

            inline Vector3i& operator-=(int64_t val)
            {
                vec[0] -= val;
                vec[1] -= val;
                vec[2] -= val;
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3i multiplication assignment operator                   //
            ////////////////////////////////////////////////////////////////////
            inline Vector3i& operator*=(const Vector3i& vector)
            {
                vec[0] *= vector.vec[0];
                vec[1] *= vector.vec[1];
                vec[2] *= vector.vec[2];
                return *this;
            }

            inline Vector3i& operator*=(int64_t val)
            {
                vec[0] *= val;
                vec[1] *= val;
                vec[2] *= val;
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3i division assignment operator                         //
            ////////////////////////////////////////////////////////////////////
            inline Vector3i& operator/=(const Vector3i& vector)
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
                return *this;
            }

            inline Vector3i& operator/=(int64_t val)
            {
                if (val != 0)
                {
                    vec[0] /= val;
                    vec[1] /= val;
                    vec[2] /= val;
                }
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3i equal to operator                                    //
            ////////////////////////////////////////////////////////////////////
            inline bool operator==(const Vector3i& vector) const
            {
                return (
                    (vec[0] == vector.vec[0]) &&
                    (vec[1] == vector.vec[1]) &&
                    (vec[2] == vector.vec[2])
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3i not equal to operator                                //
            ////////////////////////////////////////////////////////////////////
            inline bool operator!=(const Vector3i& vector) const
            {
                return (
                    (vec[0] != vector.vec[0]) ||
                    (vec[1] != vector.vec[1]) ||
                    (vec[2] != vector.vec[2])
                );
            }


        public:
            int64_t     vec[3];     // 3 components int vector representation
    };


#endif // VOS_MATH_VECTOR3I_HEADER
