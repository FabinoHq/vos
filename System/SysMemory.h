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
//     System/SysMemory.h : System memory management                          //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_SYSTEM_SYSMEMORY_HEADER
#define VOS_SYSTEM_SYSMEMORY_HEADER

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
    //  Check system memory representation                                    //
    //  return : True if the system memory is ready, false otherwise          //
    ////////////////////////////////////////////////////////////////////////////
    bool SysMemoryCheck();

    ////////////////////////////////////////////////////////////////////////////
    //  Check system memory char representation                               //
    //  return : True if the system memory char representation is correct     //
    ////////////////////////////////////////////////////////////////////////////
    bool SysMemoryCheckChar();

    ////////////////////////////////////////////////////////////////////////////
    //  Check system memory bool representation                               //
    //  return : True if the system memory bool representation is correct     //
    ////////////////////////////////////////////////////////////////////////////
    bool SysMemoryCheckBool();

    ////////////////////////////////////////////////////////////////////////////
    //  Check system memory int representation                                //
    //  return : True if the system memory int representation is correct      //
    ////////////////////////////////////////////////////////////////////////////
    bool SysMemoryCheckInt();

    ////////////////////////////////////////////////////////////////////////////
    //  Check system memory float representation                              //
    //  return : True if the system memory float representation is correct    //
    ////////////////////////////////////////////////////////////////////////////
    bool SysMemoryCheckFloat();

    ////////////////////////////////////////////////////////////////////////////
    //  Check system memory double representation                             //
    //  return : True if the system memory double representation is correct   //
    ////////////////////////////////////////////////////////////////////////////
    bool SysMemoryCheckDouble();

    ////////////////////////////////////////////////////////////////////////////
    //  Check system memory endianness                                        //
    //  return : True if the system memory is little-endian                   //
    ////////////////////////////////////////////////////////////////////////////
    bool SysMemoryCheckEndianness();

    ////////////////////////////////////////////////////////////////////////////
    //  Check system memory maths representations                             //
    //  return : True if the system memory maths representations are correct  //
    ////////////////////////////////////////////////////////////////////////////
    bool SysMemoryCheckMaths();

    ////////////////////////////////////////////////////////////////////////////
    //  Check system memory images representations                            //
    //  return : True if the system memory images representations are correct //
    ////////////////////////////////////////////////////////////////////////////
    bool SysMemoryCheckImages();


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


#endif // VOS_SYSTEM_SYSMEMORY_HEADER
