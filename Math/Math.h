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

    #include <cstdint>
    #include <cmath>


    namespace Math
    {
        // Float precision epsilon
        const float FloatEpsilon = 2.5e-7f;

        // Double precision epsilon
        const double DoubleEpsilon = 5.0e-16;

        // Pi constants
        const float Pi = 3.1415926535897932384626433832795f;
        const float TwoPi = Pi*2.0f;
        const float TwoPiThree = (Pi*2.0f)/3.0f;
        const float PiTwo = Pi*0.5f;
        const float PiThree = Pi/3.0f;
        const float PiFour = Pi*0.25f;
        const float PiEight = Pi*0.125f;
        const float DegToRad = Pi/180.0f;
        const float RadToDeg = 180.0f/Pi;

        const float SqrtTwo = 1.4142135623730950488016887242097f;
        const float OneSqrtTwo = 0.7071067811865475244008443621048f;


        ////////////////////////////////////////////////////////////////////////
        //  Get number sign (-1 or +1)                                        //
        //  return : Sign of the number (-1 or +1)                            //
        ////////////////////////////////////////////////////////////////////////
        inline int32_t sign(int32_t x)
        {
            return (x >= 0) ? 1 : -1;
        }

        inline float sign(float x)
        {
            return (x >= 0.0f) ? 1.0f : -1.0f;
        }

        inline double sign(double x)
        {
            return (x >= 0.0) ? 1.0 : -1.0;
        }

        ////////////////////////////////////////////////////////////////////////
        //  Get the absolute value of x                                       //
        //  return : Absolute value of x                                      //
        ////////////////////////////////////////////////////////////////////////
        inline int32_t abs(int32_t x)
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
        inline int32_t modulus(int32_t x, int32_t n)
        {
            return ((x%n)+n)%n;
        }

        inline float modulus(float x, float n)
        {
            return (std::fmod((std::fmod(x,n)+n),n));
        }

        inline double modulus(double x, double n)
        {
            return (std::fmod((std::fmod(x,n)+n),n));
        }

        ////////////////////////////////////////////////////////////////////////
        //  Integer division                                                  //
        //  param x : Left operand                                            //
        //  param n : Right operand                                           //
        //  return : Integer division (x / n)                                 //
        ////////////////////////////////////////////////////////////////////////
        inline int32_t divide(int32_t x, int32_t n)
        {
            if (n == 0) return 0;
            if (x < 0) x -= (n-1);
            return (x/n);
        }

        ////////////////////////////////////////////////////////////////////////
        //  Integer square root                                               //
        //  param x : Integer to get square root of                           //
        //  return : Integer square root (sqrt(x))                            //
        ////////////////////////////////////////////////////////////////////////
        inline int32_t sqrt(int32_t x)
        {
            int32_t result = 0;
            while ((result+1)*(result+1) <= x) { ++result; }
            return result;
        }

        ////////////////////////////////////////////////////////////////////////
        //  Linear interpolation                                              //
        //  return : Interpolated value                                       //
        ////////////////////////////////////////////////////////////////////////
        inline float linearInterp(float x, float y, float t)
        {
            return x + t*(y-x);
        }

        inline double linearInterp(double x, double y, double t)
        {
            return x + t*(y-x);
        }

        ////////////////////////////////////////////////////////////////////////
        //  Cubic interpolation                                               //
        //  return : Interpolated value                                       //
        ////////////////////////////////////////////////////////////////////////
        inline float cubicInterp(float x, float y, float t)
        {
            return x + (t*t*(3.0f-2.0f*t))*(y-x);
        }

        inline double cubicInterp(double x, double y, double t)
        {
            return x + (t*t*(3.0-2.0*t))*(y-x);
        }

        ////////////////////////////////////////////////////////////////////////
        //  Hermit interpolation                                              //
        //  return : Interpolated value                                       //
        ////////////////////////////////////////////////////////////////////////
        inline float hermitInterp(float w, float x, float y, float z, float t)
        {
            return (x + (t*t*(3.0f-2.0f*t))*(y-x) +
                (0.5f*(x-w)+0.5f*(y-x))*(t*t*t-2.0f*t*t+t) +
                (0.5f*(y-x)+0.5f*(z-y))*(t*t*t-t*t));
        }

        inline double hermitInterp(
            double w, double x, double y, double z, double t)
        {
            return (x + (t*t*(3.0-2.0*t))*(y-x) +
                (0.5*(x-w)+0.5*(y-x))*(t*t*t-2.0*t*t+t) +
                (0.5*(y-x)+0.5*(z-y))*(t*t*t-t*t));
        }

        ////////////////////////////////////////////////////////////////////////
        //  Distance between two points                                       //
        //  return : Distance between the two given points                    //
        ////////////////////////////////////////////////////////////////////////
        inline int32_t distance(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
        {
            return Math::sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
        }

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
