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
//     Math/Math.h : Math global functions                                    //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_MATH_MATH_HEADER
#define VOS_MATH_MATH_HEADER

    #include <cmath>


    namespace Math
    {
        // Float precision epsilon
        const float FloatEpsilon = 2.5e-7f;

        // Double precision epsilon
        const double DoubleEpsilon = 5.0e-16;


        ////////////////////////////////////////////////////////////////////////
        //  Get the absolute value of x                                       //
        //  return : Absolute value of x                                      //
        ////////////////////////////////////////////////////////////////////////
        inline int abs(int x)
        {
            return (x >= 0) ? x : -x;
        }

        inline float abs(float x)
        {
            return (x >= 0.0f) ? x : -x;
        }

        inline double abs(double x)
        {
            return (x >= 0.0) ? x : -x;
        }

        ////////////////////////////////////////////////////////////////////////
        //  Compare two floating points values                                //
        //  return : True if values are nearly equal, false otherwise         //
        ////////////////////////////////////////////////////////////////////////
        inline bool areEqual(float x, float y)
        {
            return (Math::abs(x - y) < Math::FloatEpsilon);
        }

        inline bool areEqual(double x, double y)
        {
            return (Math::abs(x - y) < Math::DoubleEpsilon);
        }


        ////////////////////////////////////////////////////////////////////////
        //  Integer modulo                                                    //
        //  return : Integer modulo (x % n)                                   //
        ////////////////////////////////////////////////////////////////////////
        inline int modulus(int x, int n)
        {
            return ((x%n)+n)%n;
        }

        ////////////////////////////////////////////////////////////////////////
        //  Linear interpolation                                              //
        //  return : Interpolated value                                       //
        ////////////////////////////////////////////////////////////////////////
        inline int linearInterp(int x, int y, int t)
        {
            return (1-t)*x + t*y;
        }

        inline float linearInterp(float x, float y, float t)
        {
            return (1.0f-t)*x + t*y;
        }

        inline double linearInterp(double x, double y, double t)
        {
            return (1.0-t)*x + t*y;
        }

        ////////////////////////////////////////////////////////////////////////
        //  Distance between two points                                       //
        //  return : Distance between the two given points                    //
        ////////////////////////////////////////////////////////////////////////
        inline float distance(float x1, float y1, float x2, float y2)
        {
            return std::sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
        }

        inline double distance(double x1, double y1, double x2, double y2)
        {
            return std::sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
        }
    };


#endif // VOS_MATH_MATH_HEADER
