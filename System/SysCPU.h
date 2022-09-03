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
//     System/SysCPU.h : System CPU management                                //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_SYSTEM_SYSCPU_HEADER
#define VOS_SYSTEM_SYSCPU_HEADER

    #include "System.h"
    #include "SysMessage.h"
    #include "../Math/Math.h"
    #include "../Math/Vector2.h"
    #include "../Math/Vector3.h"
    #include "../Math/Vector4.h"
    #include "../Math/Matrix4x4.h"
    #include "../Images/BMPFile.h"
    #include "../Images/PNGFile.h"

    #include <cstddef>
    #include <cstdint>
    #include <limits>


    ////////////////////////////////////////////////////////////////////////////
    //  8 bits integer limits                                                 //
    ////////////////////////////////////////////////////////////////////////////
    const int64_t SysInt8MinLimit = -128;
    const int64_t SysInt8MaxLimit = 127;

    ////////////////////////////////////////////////////////////////////////////
    //  16 bits integer limits                                                //
    ////////////////////////////////////////////////////////////////////////////
    const int64_t SysInt16MinLimit = -32768;
    const int64_t SysInt16MaxLimit = 32767;

    ////////////////////////////////////////////////////////////////////////////
    //  32 bits integer limits                                                //
    ////////////////////////////////////////////////////////////////////////////
    const int64_t SysInt32MinLimit = -2147483648;
    const int64_t SysInt32MaxLimit = 2147483647;


    ////////////////////////////////////////////////////////////////////////////
    //  Check system CPU                                                      //
    //  return : True if the CPU is ready, false otherwise                    //
    ////////////////////////////////////////////////////////////////////////////
    bool SysCPUCheck();

    ////////////////////////////////////////////////////////////////////////////
    //  Check system CPU char representation                                  //
    //  return : True if the system CPU char representation is correct        //
    ////////////////////////////////////////////////////////////////////////////
    bool SysCPUCheckChar();

    ////////////////////////////////////////////////////////////////////////////
    //  Check system CPU bool representation                                  //
    //  return : True if the system CPU bool representation is correct        //
    ////////////////////////////////////////////////////////////////////////////
    bool SysCPUCheckBool();

    ////////////////////////////////////////////////////////////////////////////
    //  Check system CPU int representation                                   //
    //  return : True if the system CPU int representation is correct         //
    ////////////////////////////////////////////////////////////////////////////
    bool SysCPUCheckInt();

    ////////////////////////////////////////////////////////////////////////////
    //  Check system CPU float representation                                 //
    //  return : True if the system CPU float representation is correct       //
    ////////////////////////////////////////////////////////////////////////////
    bool SysCPUCheckFloat();

    ////////////////////////////////////////////////////////////////////////////
    //  Check system CPU double representation                                //
    //  return : True if the system CPU double representation is correct      //
    ////////////////////////////////////////////////////////////////////////////
    bool SysCPUCheckDouble();

    ////////////////////////////////////////////////////////////////////////////
    //  Check system CPU endianness                                           //
    //  return : True if the system CPU is little-endian                      //
    ////////////////////////////////////////////////////////////////////////////
    bool SysCPUCheckEndianness();

    ////////////////////////////////////////////////////////////////////////////
    //  Check system CPU maths representations                                //
    //  return : True if the system CPU maths representations are correct     //
    ////////////////////////////////////////////////////////////////////////////
    bool SysCPUCheckMaths();

    ////////////////////////////////////////////////////////////////////////////
    //  Check system CPU images representations                               //
    //  return : True if the system CPU images representations are correct    //
    ////////////////////////////////////////////////////////////////////////////
    bool SysCPUCheckImages();


    ////////////////////////////////////////////////////////////////////////////
    //  Swap 2 bytes unsigned integer endianness                              //
    //  return : Swapped 2 bytes unsigned integer                             //
    ////////////////////////////////////////////////////////////////////////////
    inline uint16_t SysSwapEndianness(uint16_t bytes)
    {
        return (((bytes & 0x00FF) << 8) | ((bytes & 0xFF00) >> 8));
    }

    ////////////////////////////////////////////////////////////////////////////
    //  Swap 4 bytes unsigned integer endianness                              //
    //  return : Swapped 4 bytes unsigned integer                             //
    ////////////////////////////////////////////////////////////////////////////
    inline uint32_t SysSwapEndianness(uint32_t bytes)
    {
        return (((bytes & 0x000000FF) << 24) | ((bytes & 0x0000FF00) << 8) |
            ((bytes & 0x00FF0000) >> 8) | ((bytes & 0xFF000000) >> 24));
    }


#endif // VOS_SYSTEM_SYSCPU_HEADER
