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
//     Math/Vector3.h : 3 components vector management                        //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_MATH_VECTOR3_HEADER
#define VOS_MATH_VECTOR3_HEADER

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
            //  Get Vector3 length                                            //
            ////////////////////////////////////////////////////////////////////
            inline float length()
            {
                float result = std::sqrt(
                    (vec[0]*vec[0])+(vec[1]*vec[1])+(vec[2]*vec[2])
                );
                return result;
            }

            ////////////////////////////////////////////////////////////////////
            //  Normalize Vector3                                             //
            ////////////////////////////////////////////////////////////////////
            inline void normalize()
            {
                float len = length();
                if (len > 0.0f)
                {
                    float invLength = 1.0f/len;
                    vec[0] *= invLength;
                    vec[1] *= invLength;
                    vec[2] *= invLength;
                }
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
            inline Vector3 operator+(const Vector3& vector)
            {
                Vector3 result;
                result.vec[0] = vec[0]+vector.vec[0];
                result.vec[1] = vec[1]+vector.vec[1];
                result.vec[2] = vec[2]+vector.vec[2];
                return result;
            }

            inline Vector3 operator+(float val)
            {
                return Vector3(vec[0]+val, vec[1]+val, vec[2]+val);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 subtraction operator                                  //
            ////////////////////////////////////////////////////////////////////
            inline Vector3 operator-(const Vector3& vector)
            {
                Vector3 result;
                result.vec[0] = vec[0]-vector.vec[0];
                result.vec[1] = vec[1]-vector.vec[1];
                result.vec[2] = vec[2]-vector.vec[2];
                return result;
            }

            inline Vector3 operator-(float val)
            {
                return Vector3(vec[0]-val, vec[1]-val, vec[2]-val);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 unary plus operator                                   //
            ////////////////////////////////////////////////////////////////////
            inline Vector3 operator+()
            {
                return Vector3(*this);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 unary minus operator                                  //
            ////////////////////////////////////////////////////////////////////
            inline Vector3 operator-()
            {
                return Vector3(-vec[0], -vec[1], -vec[2]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 multiplication operator                               //
            ////////////////////////////////////////////////////////////////////
            inline Vector3 operator*(const Vector3& vector)
            {
                Vector3 result;
                result.vec[0] = vec[0]*vector.vec[0];
                result.vec[1] = vec[1]*vector.vec[1];
                result.vec[2] = vec[2]*vector.vec[2];
                return result;
            }

            inline Vector3 operator*(float val)
            {
                return Vector3(vec[0]*val, vec[1]*val, vec[2]*val);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 division operator                                     //
            ////////////////////////////////////////////////////////////////////
            inline Vector3 operator/(const Vector3& vector)
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

            inline Vector3 operator/(float val)
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
                    vec[0] *= vector.vec[0];
                }
                if (vector.vec[1] != 0.0f)
                {
                    vec[1] *= vector.vec[1];
                }
                if (vector.vec[2] != 0.0f)
                {
                    vec[2] *= vector.vec[2];
                }
                return *this;
            }

            inline Vector3& operator/=(float val)
            {
                if (val != 0.0f)
                {
                    vec[0] *= val;
                    vec[1] *= val;
                    vec[2] *= val;
                }
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 equal to operator                                     //
            ////////////////////////////////////////////////////////////////////
            inline bool operator==(const Vector3& vector)
            {
                bool areEqual = Math::areEqual(vec[0], vector.vec[0]) &&
                    Math::areEqual(vec[1], vector.vec[1]) &&
                    Math::areEqual(vec[2], vector.vec[2]);
                return areEqual;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector3 not equal to operator                                 //
            ////////////////////////////////////////////////////////////////////
            inline bool operator!=(const Vector3& vector)
            {
                bool areEqual = Math::areEqual(vec[0], vector.vec[0]) &&
                    Math::areEqual(vec[1], vector.vec[1]) &&
                    Math::areEqual(vec[2], vector.vec[2]);
                return !areEqual;
            }


        public:
            float   vec[3];     // 3 components vector representation
    };


#endif // VOS_MATH_VECTOR3_HEADER
