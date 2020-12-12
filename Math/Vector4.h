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
//     Math/Vector4.h : 4 components vector management                        //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_MATH_VECTOR4_HEADER
#define VOS_MATH_VECTOR4_HEADER

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
            //  Get Vector4 length                                            //
            ////////////////////////////////////////////////////////////////////
            inline float length()
            {
                float result = std::sqrt(
                    (vec[0]*vec[0])+(vec[1]*vec[1])+
                    (vec[2]*vec[2])+(vec[3]*vec[3])
                );
                return result;
            }

            ////////////////////////////////////////////////////////////////////
            //  Normalize Vector4                                             //
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
                    vec[3] *= invLength;
                }
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
            inline Vector4 operator+(const Vector4& vector)
            {
                Vector4 result;
                result.vec[0] = vec[0]+vector.vec[0];
                result.vec[1] = vec[1]+vector.vec[1];
                result.vec[2] = vec[2]+vector.vec[2];
                result.vec[3] = vec[3]+vector.vec[3];
                return result;
            }

            inline Vector4 operator+(float val)
            {
                return Vector4(vec[0]+val, vec[1]+val, vec[2]+val, vec[3]+val);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 subtraction operator                                  //
            ////////////////////////////////////////////////////////////////////
            inline Vector4 operator-(const Vector4& vector)
            {
                Vector4 result;
                result.vec[0] = vec[0]-vector.vec[0];
                result.vec[1] = vec[1]-vector.vec[1];
                result.vec[2] = vec[2]-vector.vec[2];
                result.vec[3] = vec[3]-vector.vec[3];
                return result;
            }

            inline Vector4 operator-(float val)
            {
                return Vector4(vec[0]-val, vec[1]-val, vec[2]-val, vec[3]-val);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 unary plus operator                                   //
            ////////////////////////////////////////////////////////////////////
            inline Vector4 operator+()
            {
                return Vector4(*this);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 unary minus operator                                  //
            ////////////////////////////////////////////////////////////////////
            inline Vector4 operator-()
            {
                return Vector4(-vec[0], -vec[1], -vec[2], -vec[3]);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 multiplication operator                               //
            ////////////////////////////////////////////////////////////////////
            inline Vector4 operator*(const Vector4& vector)
            {
                Vector4 result;
                result.vec[0] = vec[0]*vector.vec[0];
                result.vec[1] = vec[1]*vector.vec[1];
                result.vec[2] = vec[2]*vector.vec[2];
                result.vec[3] = vec[3]*vector.vec[3];
                return result;
            }

            inline Vector4 operator*(float val)
            {
                return Vector4(vec[0]*val, vec[1]*val, vec[2]*val, vec[3]*val);
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 division operator                                     //
            ////////////////////////////////////////////////////////////////////
            inline Vector4 operator/(const Vector4& vector)
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

            inline Vector4 operator/(float val)
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
                if (vector.vec[3] != 0.0f)
                {
                    vec[3] *= vector.vec[3];
                }
                return *this;
            }

            inline Vector4& operator/=(float val)
            {
                if (val != 0.0f)
                {
                    vec[0] *= val;
                    vec[1] *= val;
                    vec[2] *= val;
                    vec[3] *= val;
                }
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 equal to operator                                     //
            ////////////////////////////////////////////////////////////////////
            inline bool operator==(const Vector4& vector)
            {
                bool areEqual = Math::areEqual(vec[0], vector.vec[0]) &&
                    Math::areEqual(vec[1], vector.vec[1]) &&
                    Math::areEqual(vec[2], vector.vec[2]) &&
                    Math::areEqual(vec[3], vector.vec[3]);
                return areEqual;
            }

            ////////////////////////////////////////////////////////////////////
            //  Vector4 not equal to operator                                 //
            ////////////////////////////////////////////////////////////////////
            inline bool operator!=(const Vector4& vector)
            {
                bool areEqual = Math::areEqual(vec[0], vector.vec[0]) &&
                    Math::areEqual(vec[1], vector.vec[1]) &&
                    Math::areEqual(vec[2], vector.vec[2]) &&
                    Math::areEqual(vec[3], vector.vec[3]);
                return !areEqual;
            }


        public:
            float   vec[4];     // 4 components vector representation
    };


#endif // VOS_MATH_VECTOR4_HEADER
