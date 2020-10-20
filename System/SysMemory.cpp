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
//     System/SysMemory.cpp : System memory management                        //
////////////////////////////////////////////////////////////////////////////////
#include "SysMemory.h"


////////////////////////////////////////////////////////////////////////////////
//  Check system memory representation                                        //
//  return : True if the system memory is ready, false otherwise              //
////////////////////////////////////////////////////////////////////////////////
bool SysMemoryCheck()
{
    if (!SysMemoryCheckChar())
    {
        // Invalid char memory representation
        return false;
    }

    // System memory is ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Check system memory char representation                                   //
//  return : True if the system memory char representation is correct         //
////////////////////////////////////////////////////////////////////////////////
bool SysMemoryCheckChar()
{
    // Check char representation
    std::size_t charsize = sizeof(char);
    char charunderflow = -128;
    --charunderflow;
    char charoverflow = 127;
    ++charoverflow;
    std::size_t unsignedcharsize = sizeof(unsigned char);
    unsigned char unsignedcharunderflow = 0;
    --unsignedcharunderflow;
    unsigned char unsignedcharoverflow = 255;
    ++unsignedcharoverflow;

    if (charsize != 1)
    {
        // Invalid char memory size
        SysMessage::box() << "[0x1001] Invalid char size\n";
        SysMessage::box() << "Char size must be 8 bits (1 byte)";
        return false;
    }

    if (charunderflow != 127)
    {
        // Invalid char undeflow
        SysMessage::box() << "[0x1002] Invalid char underflow\n";
        SysMessage::box() << "Char must be signed [-128; 127]";
        return false;
    }

    if (charoverflow != -128)
    {
        // Invalid char overflow
        SysMessage::box() << "[0x1002] Invalid char overflow\n";
        SysMessage::box() << "Char must be signed [-128; 127]";
        return false;
    }

    if (unsignedcharsize != 1)
    {
        // Invalid unsigned char memory size
        SysMessage::box() << "[0x1003] Invalid unsigned char size\n";
        SysMessage::box() << "Unsigned char size must be 8 bits (1 byte)";
        return false;
    }

    if (unsignedcharunderflow != 255)
    {
        // Invalid unsigned char undeflow
        SysMessage::box() << "[0x1004] Invalid unsigned char underflow\n";
        SysMessage::box() << "Unsigned char must be unsigned [0; 255]";
        return false;
    }

    if (unsignedcharoverflow != 0)
    {
        // Invalid unsigned char overflow
        SysMessage::box() << "[0x1005] Invalid unsigned char overflow\n";
        SysMessage::box() << "Unsigned char must be signed [0; 255]";
        return false;
    }

    // Char memory representation is valid
    return true;
}
