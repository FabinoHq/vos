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

    if (!SysMemoryCheckBool())
    {
        // Invalid bool memory representation
        return false;
    }

    if (!SysMemoryCheckInt())
    {
        // Invalid int memory represantion
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

////////////////////////////////////////////////////////////////////////////////
//  Check system memory bool representation                                   //
//  return : True if the system memory bool representation is correct         //
////////////////////////////////////////////////////////////////////////////////
bool SysMemoryCheckBool()
{
    // Check bool representation
    std::size_t boolsize = sizeof(bool);
    bool booltrue = true;
    bool boolfalse = false;

    if (boolsize != 1)
    {
        // Invalid bool memory size
        SysMessage::box() << "[0x1006] Invalid bool size\n";
        SysMessage::box() << "Bool size must be 8 bits (1 byte)";
        return false;
    }

    if (static_cast<char>(booltrue) != 1)
    {
        // Invalid bool true value
        SysMessage::box() << "[0x1007] Invalid bool true value\n";
        SysMessage::box() << "Bool true value must be 1";
        return false;
    }

    if (static_cast<char>(boolfalse) != 0)
    {
        // Invalid bool false value
        SysMessage::box() << "[0x1008] Invalid bool false value\n";
        SysMessage::box() << "Bool false value must be 0";
        return false;
    }

    // Bool memory representation is valid
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Check system memory int representation                                    //
//  return : True if the system memory int representation is correct          //
////////////////////////////////////////////////////////////////////////////////
bool SysMemoryCheckInt()
{
    // Check int representation
    std::size_t intsize = sizeof(int);
    int intunderflow = -2147483648;
    --intunderflow;
    int intoverflow = 2147483647;
    ++intoverflow;
    std::size_t unsignedintsize = sizeof(unsigned int);
    unsigned int unsignedintunderflow = 0;
    --unsignedintunderflow;
    unsigned int unsignedintoverflow = 4294967295;
    ++unsignedintoverflow;

    if (intsize != 4)
    {
        // Invalid int memory size
        SysMessage::box() << "[0x1009] Invalid int size\n";
        SysMessage::box() << "Int size must be 32 bits (4 bytes)";
        return false;
    }

    if (intunderflow != 2147483647)
    {
        // Invalid int undeflow
        SysMessage::box() << "[0x100A] Invalid int underflow\n";
        SysMessage::box() << "Int must be signed [-2147483648; 2147483647]";
        return false;
    }

    if (intoverflow != -2147483648)
    {
        // Invalid int overflow
        SysMessage::box() << "[0x100B] Invalid int overflow\n";
        SysMessage::box() << "Int must be signed [-2147483648; 2147483647]";
        return false;
    }

    if (unsignedintsize != 4)
    {
        // Invalid unsigned int memory size
        SysMessage::box() << "[0x100C] Invalid unsigned int size\n";
        SysMessage::box() << "Unsigned int size must be 32 bits (4 bytes)";
        return false;
    }

    if (unsignedintunderflow != 4294967295)
    {
        // Invalid unsigned int undeflow
        SysMessage::box() << "[0x100D] Invalid unsigned int underflow\n";
        SysMessage::box() << "Unsigned int must be unsigned [0; 4294967295]";
        return false;
    }

    if (unsignedintoverflow != 0)
    {
        // Invalid unsigned int overflow
        SysMessage::box() << "[0x100E] Invalid unsigned int overflow\n";
        SysMessage::box() << "Unsigned int must be signed [0; 4294967295]";
        return false;
    }

    // Int memory representation is valid
    return true;
}
