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
//     Math/Math.h : Math global functions                                    //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_MATH_MATH_HEADER
#define VOS_MATH_MATH_HEADER

    #include "../System/System.h"
    #include "../System/SysCPU.h"

    #include "Sinus.h"

    #include <cstdint>
    #include <cmath>


    ////////////////////////////////////////////////////////////////////////////
    //  Math functions and constants namespace                                //
    ////////////////////////////////////////////////////////////////////////////
    namespace Math
    {
        // Float precision epsilon
        const float FloatEpsilon = 2.5e-7f;

        // Double precision epsilon
        const double DoubleEpsilon = 5.0e-16;

        // Pi constants
        const float Pi = 3.1415926535897932384626433832795f;
        const float InvPi = 0.31830988618379067153776752674503f;
        const float TwoPi = (Pi*2.0f);
        const float InvTwoPi = (1.0f/TwoPi);
        const float TwoPiThird = ((Pi*2.0f)/3.0f);
        const float PiHalf = (Pi*0.5f);
        const float InvPiHalf = (1.0f/PiHalf);
        const float PiThird = (Pi/3.0f);
        const float PiFourth = (Pi*0.25f);
        const float PiEighth = (Pi*0.125f);
        const float DegToRad = (Pi/180.0f);
        const float RadToDeg = (180.0f/Pi);

        // Square roots constants
        const float SqrtTwo = 1.4142135623730950488016887242097f;
        const float InvSqrtTwo = 0.7071067811865475244008443621048f;

        // Integer constants
        const int32_t OneIntShift = 20;
        const int32_t OneInt = (1 << OneIntShift);  // 1048576
        const int32_t PiInt = 3294198;
        const int32_t TwoPiInt = 6588396;
        const int32_t TwoPiThirdInt = 2196132;
        const int32_t PiHalfInt = 1647099;
        const int32_t PiThirdInt = 1098066;

        // 32bits powers of ten
        const int32_t MaxPowersOfTen32 = 10;
        const int32_t PowersOfTen32[MaxPowersOfTen32] = {
            1, 10, 100, 1000, 10000, 100000,
            1000000, 10000000, 100000000, 1000000000
        };

        // 64bits powers of ten
        const int64_t MaxPowersOfTen64 = 19;
        const int64_t PowersOfTen64[MaxPowersOfTen64] = {
            1ll, 10ll, 100ll, 1000ll, 10000ll, 100000ll, 1000000ll, 10000000ll,
            100000000ll, 1000000000ll, 10000000000ll, 100000000000ll,
            1000000000000ll, 10000000000000ll, 100000000000000ll,
            1000000000000000ll, 10000000000000000ll, 100000000000000000ll,
            1000000000000000000ll
        };


        ////////////////////////////////////////////////////////////////////////
        //  Get number sign (-1 or +1)                                        //
        //  return : Sign of the number (-1 or +1)                            //
        ////////////////////////////////////////////////////////////////////////
        inline int32_t sign(int32_t x)
        {
            return ((x >= 0) ? 1 : -1);
        }

        inline int64_t sign(int64_t x)
        {
            return ((x >= 0) ? 1 : -1);
        }

        inline float sign(float x)
        {
            return ((x >= 0.0f) ? 1.0f : -1.0f);
        }

        inline double sign(double x)
        {
            return ((x >= 0.0) ? 1.0 : -1.0);
        }

        ////////////////////////////////////////////////////////////////////////
        //  Get number sign with zero (-1, 0, or +1)                          //
        //  return : Sign of the number with zero (-1, 0, or +1)              //
        ////////////////////////////////////////////////////////////////////////
        inline int32_t signum(int32_t x)
        {
            return ((x > 0) - (x < 0));
        }

        inline int64_t signum(int64_t x)
        {
            return ((x > 0) - (x < 0));
        }

        inline float signum(float x)
        {
            return (((x > 0.0f) - (x < 0.0f))*1.0f);
        }

        inline double signum(double x)
        {
            return (((x > 0.0) - (x < 0.0))*1.0);
        }

        ////////////////////////////////////////////////////////////////////////
        //  Get number positive boolean (0 or +1)                             //
        //  return : Positive boolean of the number (0 or +1)                 //
        ////////////////////////////////////////////////////////////////////////
        inline int32_t positive(int32_t x)
        {
            return ((x >= 0) ? 1 : 0);
        }

        inline int64_t positive(int64_t x)
        {
            return ((x >= 0) ? 1 : 0);
        }

        inline float positive(float x)
        {
            return ((x >= 0.0f) ? 1.0f : 0.0f);
        }

        inline double positive(double x)
        {
            return ((x >= 0.0) ? 1.0 : 0.0);
        }

        ////////////////////////////////////////////////////////////////////////
        //  Get number negative boolean (0 or +1)                             //
        //  return : Negative boolean of the number (0 or +1)                 //
        ////////////////////////////////////////////////////////////////////////
        inline int32_t negative(int32_t x)
        {
            return ((x >= 0) ? 0 : 1);
        }

        inline int64_t negative(int64_t x)
        {
            return ((x >= 0) ? 0 : 1);
        }

        inline float negative(float x)
        {
            return ((x >= 0.0f) ? 0.0f : 1.0f);
        }

        inline double negative(double x)
        {
            return ((x >= 0.0) ? 0.0 : 1.0);
        }

        ////////////////////////////////////////////////////////////////////////
        //  Get the absolute value of x                                       //
        //  param x : Value to get absolute of                                //
        //  return : Absolute value of x                                      //
        ////////////////////////////////////////////////////////////////////////
        inline int32_t abs(int32_t x)
        {
            return ((x >= 0) ? x : -x);
        }

        inline int64_t abs(int64_t x)
        {
            return ((x >= 0) ? x : -x);
        }

        inline float abs(float x)
        {
            return ((x >= 0.0f) ? x : -x);
        }

        inline double abs(double x)
        {
            return ((x >= 0.0) ? x : -x);
        }

        ////////////////////////////////////////////////////////////////////////
        //  round : Get the round value of x                                  //
        //  param x : Value to get round value of                             //
        //  Return : Round value of x                                         //
        ////////////////////////////////////////////////////////////////////////
        inline float round(float x)
        {
            return std::round(x);
        }

        inline double round(double x)
        {
            return std::round(x);
        }

        ////////////////////////////////////////////////////////////////////////
        //  floor : Get the floor value of x                                  //
        //  param x : Value to get floor value of                             //
        //  Return : Floor value of x                                         //
        ////////////////////////////////////////////////////////////////////////
        inline float floor(float x)
        {
            return std::floor(x);
        }

        inline double floor(double x)
        {
            return std::floor(x);
        }

        ////////////////////////////////////////////////////////////////////////
        //  ceil : Get the ceil value of x                                    //
        //  param x : Value to get ceil value of                              //
        //  Return : Ceil value of x                                          //
        ////////////////////////////////////////////////////////////////////////
        inline float ceil(float x)
        {
            return std::ceil(x);
        }

        inline double ceil(double x)
        {
            return std::ceil(x);
        }

        ////////////////////////////////////////////////////////////////////////
        //  Compare two floating points values                                //
        //  param x : First value to compare                                  //
        //  param y : Second value to compare                                 //
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
        //  Get the minimum value between x and y                             //
        //  return : Minimum value between x and y                            //
        ////////////////////////////////////////////////////////////////////////
        inline int32_t min(int32_t x, int32_t y)
        {
            return ((x < y) ? x : y);
        }

        inline uint32_t min(uint32_t x, uint32_t y)
        {
            return ((x < y) ? x : y);
        }

        inline int64_t min(int64_t x, int64_t y)
        {
            return ((x < y) ? x : y);
        }

        inline uint64_t min(uint64_t x, uint64_t y)
        {
            return ((x < y) ? x : y);
        }

        inline float min(float x, float y)
        {
            return SysFloatMin(x, y);
        }

        inline double min(double x, double y)
        {
            return SysDoubleMin(x, y);
        }

        ////////////////////////////////////////////////////////////////////////
        //  Get the maximum value between x and y                             //
        //  return : Maximum value between x and y                            //
        ////////////////////////////////////////////////////////////////////////
        inline int32_t max(int32_t x, int32_t y)
        {
            return ((x > y) ? x : y);
        }

        inline uint32_t max(uint32_t x, uint32_t y)
        {
            return ((x > y) ? x : y);
        }

        inline int64_t max(int64_t x, int64_t y)
        {
            return ((x > y) ? x : y);
        }

        inline uint64_t max(uint64_t x, uint64_t y)
        {
            return ((x > y) ? x : y);
        }

        inline float max(float x, float y)
        {
            return SysFloatMax(x, y);
        }

        inline double max(double x, double y)
        {
            return SysDoubleMax(x, y);
        }

        ////////////////////////////////////////////////////////////////////////
        //  Clamp x value between min and max                                 //
        //  return : Clamped value between min and max                        //
        ////////////////////////////////////////////////////////////////////////
        inline int32_t clamp(int32_t x, int32_t min, int32_t max)
        {
            return ((x < max) ? ((x > min) ? x : min) : max);
        }

        inline uint32_t clamp(uint32_t x, uint32_t min, uint32_t max)
        {
            return ((x < max) ? ((x > min) ? x : min) : max);
        }

        inline int64_t clamp(int64_t x, int64_t min, int64_t max)
        {
            return ((x < max) ? ((x > min) ? x : min) : max);
        }

        inline uint64_t clamp(uint64_t x, uint64_t min, uint64_t max)
        {
            return ((x < max) ? ((x > min) ? x : min) : max);
        }

        inline float clamp(float x, float min, float max)
        {
            return SysFloatClamp(x, min, max);
        }

        inline double clamp(double x, double min, double max)
        {
            return SysDoubleClamp(x, min, max);
        }

        ////////////////////////////////////////////////////////////////////////
        //  Modulo                                                            //
        //  return : Modulo (x % n)                                           //
        ////////////////////////////////////////////////////////////////////////
        inline int32_t modulo(int32_t x, int32_t n)
        {
            return ((x%n)+n)%n;
        }

        inline int64_t modulo(int64_t x, int64_t n)
        {
            return ((x%n)+n)%n;
        }

        inline float modulo(float x, float n)
        {
            return (std::fmod((std::fmod(x,n)+n),n));
        }

        inline double modulo(double x, double n)
        {
            return (std::fmod((std::fmod(x,n)+n),n));
        }

        ////////////////////////////////////////////////////////////////////////
        //  Divide                                                            //
        //  param x : Left operand                                            //
        //  param n : Right operand                                           //
        //  return : Division (x / n)                                         //
        ////////////////////////////////////////////////////////////////////////
        inline int32_t divide(int32_t x, int32_t n)
        {
            if (n == 0) return 0;
            if (x < 0) { x -= (n-1); }
            return (x/n);
        }

        inline int64_t divide(int64_t x, int64_t n)
        {
            if (n == 0) return 0;
            if (x < 0) { x -= (n-1); }
            return (x/n);
        }

        inline int32_t divide(float x, float n)
        {
            if (n == 0.0f) return 0;
            if (x < 0.0f) { x -= (n-1.0f); }
            return (static_cast<int32_t>(x/n));
        }

        inline int32_t divide(double x, double n)
        {
            if (n == 0.0) return 0;
            if (x < 0.0) { x -= (n-1.0); }
            return (static_cast<int32_t>(x/n));
        }

        ////////////////////////////////////////////////////////////////////////
        //  Square root                                                       //
        //  param x : Number to get square root of                            //
        //  return : Square root (sqrt(x))                                    //
        ////////////////////////////////////////////////////////////////////////
        inline int32_t sqrt(int32_t x)
        {
            return (static_cast<int32_t>(std::sqrt(x)));
        }

        inline int64_t sqrt(int64_t x)
        {
            return (static_cast<int64_t>(std::sqrt(x)));
        }

        inline float sqrt(float x)
        {
            return std::sqrt(x);
        }

        inline double sqrt(double x)
        {
            return std::sqrt(x);
        }

        ////////////////////////////////////////////////////////////////////////
        //  Integer binary logarithm                                          //
        //  param x : Integer to get binary logarithm of                      //
        //  return : Integer binary logarithm (log2(x))                       //
        ////////////////////////////////////////////////////////////////////////
        inline int8_t log2(int32_t x)
        {
            int8_t result = 0;
            if (x >= 0x10000) { result += 16; x >>= 16; }
            if (x >= 0x100) { result += 8; x >>= 8; }
            if (x >= 0x10) { result += 4; x >>= 4; }
            if (x >= 0x4) { result += 2; x >>= 2; }
            if (x >= 0x2) { result += 1; x >>= 1; }
            return result;
        }

        inline int8_t log2(uint32_t x)
        {
            int8_t result = 0;
            if (x >= 0x10000) { result += 16; x >>= 16; }
            if (x >= 0x100) { result += 8; x >>= 8; }
            if (x >= 0x10) { result += 4; x >>= 4; }
            if (x >= 0x4) { result += 2; x >>= 2; }
            if (x >= 0x2) { result += 1; x >>= 1; }
            return result;
        }

        inline int8_t log2(int64_t x)
        {
            int8_t result = 0;
            if (x >= 0x100000000) { result += 32; x >>= 32; }
            if (x >= 0x10000) { result += 16; x >>= 16; }
            if (x >= 0x100) { result += 8; x >>= 8; }
            if (x >= 0x10) { result += 4; x >>= 4; }
            if (x >= 0x4) { result += 2; x >>= 2; }
            if (x >= 0x2) { result += 1; x >>= 1; }
            return result;
        }

        inline int8_t log2(uint64_t x)
        {
            int8_t result = 0;
            if (x >= 0x100000000) { result += 32; x >>= 32; }
            if (x >= 0x10000) { result += 16; x >>= 16; }
            if (x >= 0x100) { result += 8; x >>= 8; }
            if (x >= 0x10) { result += 4; x >>= 4; }
            if (x >= 0x4) { result += 2; x >>= 2; }
            if (x >= 0x2) { result += 1; x >>= 1; }
            return result;
        }

        ////////////////////////////////////////////////////////////////////////
        //  Integer base 10 logarithm                                         //
        //  param x : Integer to get base 10 logarithm of                     //
        //  return : Integer base 10 logarithm (log10(x))                     //
        ////////////////////////////////////////////////////////////////////////
        inline int8_t log10(int32_t x)
        {
            return static_cast<int8_t>(std::log10(x*1.0));
        }

        inline int8_t log10(uint32_t x)
        {
            return static_cast<int8_t>(std::log10(x*1.0));
        }

        inline int8_t log10(int64_t x)
        {
            return static_cast<int8_t>(std::log10(x*1.0));
        }

        inline int8_t log10(uint64_t x)
        {
            return static_cast<int8_t>(std::log10(x*1.0));
        }

        ////////////////////////////////////////////////////////////////////////
        //  Integer power of ten                                              //
        //  param x : Power of ten exponent                                   //
        //  return : Integer power of ten (10 ^ x)                            //
        ////////////////////////////////////////////////////////////////////////
        inline int32_t power10(int32_t x)
        {
            return PowersOfTen32[Math::clamp(x, 0, (MaxPowersOfTen32-1))];
        }

        inline int64_t power10(int64_t x)
        {
            return PowersOfTen64[Math::clamp(x, 0ll, (MaxPowersOfTen64-1ll))];
        }

        ////////////////////////////////////////////////////////////////////////
        //  Sinus                                                             //
        //  param x : Sinus argument                                          //
        //  return : Sinus of x (sin(x))                                      //
        ////////////////////////////////////////////////////////////////////////
        inline int32_t sin(int32_t x)
        {
            return SinusTable[Math::clamp(
                (Math::modulo(x, Math::TwoPiInt) >> SinusTableShift),
                0, (SinusTableSize-1)
            )];
        }

        inline int64_t sin(int64_t x)
        {
            return SinusTable[Math::clamp(
                (Math::modulo(x, ((int64_t)Math::TwoPiInt)) >> SinusTableShift),
                0ll, (SinusTableSize-1ll)
            )];
        }

        inline float sin(float x)
        {
            return std::sin(x);
        }

        inline double sin(double x)
        {
            return std::sin(x);
        }

        ////////////////////////////////////////////////////////////////////////
        //  Cosinus                                                           //
        //  param x : Cosinus argument                                        //
        //  return : Cosinus of x (cos(x))                                    //
        ////////////////////////////////////////////////////////////////////////
        inline int32_t cos(int32_t x)
        {
            return SinusTable[Math::clamp(
                (Math::modulo((x + Math::PiHalfInt),
                    Math::TwoPiInt) >> SinusTableShift),
                0, (SinusTableSize-1)
            )];
        }

        inline int64_t cos(int64_t x)
        {
            return SinusTable[Math::clamp(
                (Math::modulo((x + ((int64_t)Math::PiHalfInt)),
                    ((int64_t)Math::TwoPiInt)) >> SinusTableShift),
                0ll, (SinusTableSize-1ll)
            )];
        }

        inline float cos(float x)
        {
            return std::cos(x);
        }

        inline double cos(double x)
        {
            return std::cos(x);
        }

        ////////////////////////////////////////////////////////////////////////
        //  Tangent                                                           //
        //  param x : Tangent argument                                        //
        //  return : Tangent of x (tan(x))                                    //
        ////////////////////////////////////////////////////////////////////////
        inline float tan(float x)
        {
            return std::tan(x);
        }

        inline double tan(double x)
        {
            return std::tan(x);
        }

        ////////////////////////////////////////////////////////////////////////
        //  Arc sinus                                                         //
        //  param x : Arc sinus argument                                      //
        //  return : Arc sinus of x (asin(x))                                 //
        ////////////////////////////////////////////////////////////////////////
        inline float asin(float x)
        {
            return std::asin(x);
        }

        inline double asin(double x)
        {
            return std::asin(x);
        }

        ////////////////////////////////////////////////////////////////////////
        //  Arc cosinus                                                       //
        //  param x : Arc cosinus argument                                    //
        //  return : Arc cosinus of x (acos(x))                               //
        ////////////////////////////////////////////////////////////////////////
        inline float acos(float x)
        {
            return std::acos(x);
        }

        inline double acos(double x)
        {
            return std::acos(x);
        }

        ////////////////////////////////////////////////////////////////////////
        //  Arc tangent                                                       //
        //  param x : Arc tangent argument                                    //
        //  return : Arc tangent of x (atan(x))                               //
        ////////////////////////////////////////////////////////////////////////
        inline float atan(float x)
        {
            return std::atan(x);
        }

        inline double atan(double x)
        {
            return std::atan(x);
        }

        ////////////////////////////////////////////////////////////////////////
        //  Full quadrants arc tangent                                        //
        //  param x : Arc tangent x argument                                  //
        //  param y : Arc tangent y argument                                  //
        //  return : Full quadrants arc tangent of x/y (atan2(x, y))          //
        ////////////////////////////////////////////////////////////////////////
        inline float atan(float x, float y)
        {
            return std::atan2(x, y);
        }

        inline double atan(double x, float y)
        {
            return std::atan2(x, y);
        }

        ////////////////////////////////////////////////////////////////////////
        //  Exponential                                                       //
        //  param x : Exponential argument                                    //
        //  return : Exponential of x (exp(x))                                //
        ////////////////////////////////////////////////////////////////////////
        inline float exp(float x)
        {
            return std::exp(x);
        }

        inline double exp(double x)
        {
            return std::exp(x);
        }

        ////////////////////////////////////////////////////////////////////////
        //  Linear interpolation                                              //
        //  return : Interpolated value                                       //
        ////////////////////////////////////////////////////////////////////////
        inline float linearInterp(float x, float y, float t)
        {
            return (x + t*(y-x));
        }

        inline double linearInterp(double x, double y, double t)
        {
            return (x + t*(y-x));
        }

        ////////////////////////////////////////////////////////////////////////
        //  Cubic interpolation                                               //
        //  return : Interpolated value                                       //
        ////////////////////////////////////////////////////////////////////////
        inline float cubicInterp(float x, float y, float t)
        {
            return (x + (t*t*(3.0f-2.0f*t))*(y-x));
        }

        inline double cubicInterp(double x, double y, double t)
        {
            return (x + (t*t*(3.0-2.0*t))*(y-x));
        }

        ////////////////////////////////////////////////////////////////////////
        //  Hermit interpolation                                              //
        //  return : Interpolated value                                       //
        ////////////////////////////////////////////////////////////////////////
        inline float hermitInterp(float w, float x, float y, float z, float t)
        {
            return (x + (t*t*(3.0f-2.0f*t))*(y-x) +
                (0.5f*(x-w)+0.5f*(y-x))*((t*t*t)-(2.0f*t*t+t)) +
                (0.5f*(y-x)+0.5f*(z-y))*(t*t*t-t*t));
        }

        inline double hermitInterp(
            double w, double x, double y, double z, double t)
        {
            return (x + (t*t*(3.0-2.0*t))*(y-x) +
                (0.5*(x-w)+0.5*(y-x))*((t*t*t)-(2.0*t*t+t)) +
                (0.5*(y-x)+0.5*(z-y))*(t*t*t-t*t));
        }

        ////////////////////////////////////////////////////////////////////////
        //  Distance between two points                                       //
        //  return : Distance between the two given points                    //
        ////////////////////////////////////////////////////////////////////////
        inline int32_t distance(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
        {
            return (Math::sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1))));
        }

        inline int64_t distance(int64_t x1, int64_t y1, int64_t x2, int64_t y2)
        {
            return (Math::sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1))));
        }

        inline float distance(float x1, float y1, float x2, float y2)
        {
            return (Math::sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1))));
        }

        inline double distance(double x1, double y1, double x2, double y2)
        {
            return (Math::sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1))));
        }
    };


#endif // VOS_MATH_MATH_HEADER
