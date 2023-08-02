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
//     System/Win/SysCPU.h : System CPU management for Windows                //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_SYSTEM_WIN_SYSCPU_HEADER
#define VOS_SYSTEM_WIN_SYSCPU_HEADER

    #include "../System.h"

    #include <cstddef>
    #include <cstdint>
    #include <cstdlib>
    #include <intrin.h>


    ////////////////////////////////////////////////////////////////////////////
    //  Swap 2 bytes unsigned integer endianness                              //
    //  return : Swapped 2 bytes unsigned integer                             //
    ////////////////////////////////////////////////////////////////////////////
    #define SysByteSwap16 _byteswap_ushort

    ////////////////////////////////////////////////////////////////////////////
    //  Swap 4 bytes unsigned integer endianness                              //
    //  return : Swapped 4 bytes unsigned integer                             //
    ////////////////////////////////////////////////////////////////////////////
    #define SysByteSwap32 _byteswap_ulong

    ////////////////////////////////////////////////////////////////////////////
    //  Swap 8 bytes unsigned integer endianness                              //
    //  return : Swapped 8 bytes unsigned integer                             //
    ////////////////////////////////////////////////////////////////////////////
    #define SysByteSwap64 _byteswap_uint64


    ////////////////////////////////////////////////////////////////////////////
    //  Compute 32 bits scan forward                                          //
    //  return : Computed 32 bits scan forward                                //
    ////////////////////////////////////////////////////////////////////////////
    inline uint32_t SysBitScanForward32(uint32_t bits)
    {
        _BitScanForward((unsigned long*)&bits, bits);
        return bits;
    }

    ////////////////////////////////////////////////////////////////////////////
    //  Compute 32 bits scan reverse                                          //
    //  return : Computed 32 bits scan reverse                                //
    ////////////////////////////////////////////////////////////////////////////
    inline uint32_t SysBitScanReverse32(uint32_t bits)
    {
        _BitScanReverse((unsigned long*)&bits, bits);
        return bits;
    }

    ////////////////////////////////////////////////////////////////////////////
    //  Compute 64 bits scan forward                                          //
    //  return : Computed 64 bits scan forward                                //
    ////////////////////////////////////////////////////////////////////////////
    inline uint64_t SysBitScanForward64(uint64_t bits)
    {
        _BitScanForward64((unsigned long*)&bits, bits);
        return bits;
    }

    ////////////////////////////////////////////////////////////////////////////
    //  Compute 64 bits scan reverse                                          //
    //  return : Computed 64 bits scan reverse                                //
    ////////////////////////////////////////////////////////////////////////////
    inline uint64_t SysBitScanReverse64(uint64_t bits)
    {
        _BitScanReverse64((unsigned long*)&bits, bits);
        return bits;
    }


    ////////////////////////////////////////////////////////////////////////////
    //  SSE Branchless float minimum                                          //
    //  return : Minimum value between x and y                                //
    ////////////////////////////////////////////////////////////////////////////
    inline float SysFloatMin(float x, float y)
    {
        _mm_store_ss(&x, _mm_min_ss(_mm_set_ss(x), _mm_set_ss(y)));
        return x;
    }

    inline double SysDoubleMin(double x, double y)
    {
        _mm_store_sd(&x, _mm_min_sd(_mm_set_sd(x), _mm_set_sd(y)));
        return x;
    }

    ////////////////////////////////////////////////////////////////////////////
    //  SSE Branchless float maximum                                          //
    //  return : Maximum value between x and y                                //
    ////////////////////////////////////////////////////////////////////////////
    inline float SysFloatMax(float x, float y)
    {
        _mm_store_ss(&x, _mm_max_ss(_mm_set_ss(x), _mm_set_ss(y)));
        return x;
    }

    inline double SysDoubleMax(double x, double y)
    {
        _mm_store_sd(&x, _mm_max_sd(_mm_set_sd(x), _mm_set_sd(y)));
        return x;
    }

    ////////////////////////////////////////////////////////////////////////////
    //  SSE Branchless float clamping                                         //
    //  return : Value clamped between min and max                            //
    ////////////////////////////////////////////////////////////////////////////
    inline float SysFloatClamp(float x, float min, float max)
    {
        _mm_store_ss(&x, _mm_min_ss(_mm_max_ss(
            _mm_set_ss(x), _mm_set_ss(min)), _mm_set_ss(max))
        );
        return x;
    }

    inline double SysDoubleClamp(double x, double min, double max)
    {
        _mm_store_sd(&x, _mm_min_sd(_mm_max_sd(
            _mm_set_sd(x), _mm_set_sd(min)), _mm_set_sd(max))
        );
        return x;
    }


#endif // VOS_SYSTEM_WIN_SYSCPU_HEADER
