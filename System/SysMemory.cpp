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

    if (!SysMemoryCheckFloat())
    {
        // Invalid float memory represantion
        return false;
    }

    if (!SysMemoryCheckDouble())
    {
        // Invalid double memory represantion
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
    std::size_t wchartsize = sizeof(wchar_t);
    wchar_t wchartunderflow = 0;
    --wchartunderflow;
    wchar_t wchartoverflow = 65535;
    ++wchartoverflow;

    if (charsize != 1)
    {
        // Invalid char memory size
        SysMessage::box() << "[0x1001] Invalid char memory size\n";
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
        SysMessage::box() << "[0x1003] Invalid char overflow\n";
        SysMessage::box() << "Char must be signed [-128; 127]";
        return false;
    }

    if (unsignedcharsize != 1)
    {
        // Invalid unsigned char memory size
        SysMessage::box() << "[0x1004] Invalid unsigned char memory size\n";
        SysMessage::box() << "Unsigned char size must be 8 bits (1 byte)";
        return false;
    }

    if (unsignedcharunderflow != 255)
    {
        // Invalid unsigned char undeflow
        SysMessage::box() << "[0x1005] Invalid unsigned char underflow\n";
        SysMessage::box() << "Unsigned char must be unsigned [0; 255]";
        return false;
    }

    if (unsignedcharoverflow != 0)
    {
        // Invalid unsigned char overflow
        SysMessage::box() << "[0x1006] Invalid unsigned char overflow\n";
        SysMessage::box() << "Unsigned char must be unsigned [0; 255]";
        return false;
    }

    if (wchartsize != 2)
    {
        // Invalid wchar_t memory size
        SysMessage::box() << "[0x1007] Invalid wchar_t memory size\n";
        SysMessage::box() << "Wchar_t size must be 16 bits (2 byte)";
        return false;
    }

    if (wchartunderflow != 65535)
    {
        // Invalid wchar_t undeflow
        SysMessage::box() << "[0x1008] Invalid wchar_t underflow\n";
        SysMessage::box() << "Wchar_t must be unsigned [0; 65535]";
        return false;
    }

    if (wchartoverflow != 0)
    {
        // Invalid wchar_t overflow
        SysMessage::box() << "[0x1009] Invalid wchar_t overflow\n";
        SysMessage::box() << "Wchar_t must be unsigned [0; 65535]\n";
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
        SysMessage::box() << "[0x100A] Invalid bool memory size\n";
        SysMessage::box() << "Bool size must be 8 bits (1 byte)";
        return false;
    }

    if (static_cast<char>(booltrue) != 1)
    {
        // Invalid bool true value
        SysMessage::box() << "[0x100B] Invalid bool true value\n";
        SysMessage::box() << "Bool true value must be 1";
        return false;
    }

    if (static_cast<char>(boolfalse) != 0)
    {
        // Invalid bool false value
        SysMessage::box() << "[0x100C] Invalid bool false value\n";
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
    std::size_t shortsize = sizeof(short);
    short shortunderflow = -32768;
    --shortunderflow;
    short shortoverflow = 32767;
    ++shortoverflow;
    std::size_t unsignedshortsize = sizeof(unsigned short);
    unsigned short unsignedshortunderflow = 0;
    --unsignedshortunderflow;
    unsigned short unsignedshortoverflow = 65535;
    ++unsignedshortoverflow;
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

    std::size_t int8tsize = sizeof(int8_t);
    int8_t int8tunderflow = -128;
    --int8tunderflow;
    int8_t int8toverflow = 127;
    ++int8toverflow;
    std::size_t uint8tsize = sizeof(uint8_t);
    uint8_t uint8tunderflow = 0;
    --uint8tunderflow;
    uint8_t uint8toverflow = 255;
    ++uint8toverflow;

    if (shortsize != 2)
    {
        // Invalid short memory size
        SysMessage::box() << "[0x100D] Invalid short memory size\n";
        SysMessage::box() << "Short size must be 16 bits (2 bytes)";
        return false;
    }

    if (shortunderflow != 32767)
    {
        // Invalid short undeflow
        SysMessage::box() << "[0x100E] Invalid short underflow\n";
        SysMessage::box() << "Short must be signed [-32768; 32767]";
        return false;
    }

    if (shortoverflow != -32768)
    {
        // Invalid short overflow
        SysMessage::box() << "[0x100F] Invalid short overflow\n";
        SysMessage::box() << "Short must be signed [-32768; 32767]";
        return false;
    }

    if (unsignedshortsize != 2)
    {
        // Invalid unsigned short memory size
        SysMessage::box() << "[0x1010] Invalid unsigned short memory size\n";
        SysMessage::box() << "Unsigned short size must be 16 bits (2 bytes)";
        return false;
    }

    if (unsignedshortunderflow != 65535)
    {
        // Invalid unsigned short undeflow
        SysMessage::box() << "[0x1011] Invalid unsigned short underflow\n";
        SysMessage::box() << "Unsigned short must be unsigned [0; 65535]";
        return false;
    }

    if (unsignedshortoverflow != 0)
    {
        // Invalid unsigned short overflow
        SysMessage::box() << "[0x1012] Invalid unsigned short overflow\n";
        SysMessage::box() << "Unsigned short must be unsigned [0; 65535]";
        return false;
    }

    if (intsize != 4)
    {
        // Invalid int memory size
        SysMessage::box() << "[0x1013] Invalid int memory size\n";
        SysMessage::box() << "Int size must be 32 bits (4 bytes)";
        return false;
    }

    if (intunderflow != 2147483647)
    {
        // Invalid int undeflow
        SysMessage::box() << "[0x1014] Invalid int underflow\n";
        SysMessage::box() << "Int must be signed [-2147483648; 2147483647]";
        return false;
    }

    if (intoverflow != -2147483648)
    {
        // Invalid int overflow
        SysMessage::box() << "[0x1015] Invalid int overflow\n";
        SysMessage::box() << "Int must be signed [-2147483648; 2147483647]";
        return false;
    }

    if (unsignedintsize != 4)
    {
        // Invalid unsigned int memory size
        SysMessage::box() << "[0x1016] Invalid unsigned int memory size\n";
        SysMessage::box() << "Unsigned int size must be 32 bits (4 bytes)";
        return false;
    }

    if (unsignedintunderflow != 4294967295)
    {
        // Invalid unsigned int undeflow
        SysMessage::box() << "[0x1017] Invalid unsigned int underflow\n";
        SysMessage::box() << "Unsigned int must be unsigned [0; 4294967295]";
        return false;
    }

    if (unsignedintoverflow != 0)
    {
        // Invalid unsigned int overflow
        SysMessage::box() << "[0x1018] Invalid unsigned int overflow\n";
        SysMessage::box() << "Unsigned int must be unsigned [0; 4294967295]";
        return false;
    }


    if (int8tsize != 1)
    {
        // Invalid int8_t memory size
        SysMessage::box() << "[0x1019] Invalid int8_t memory size\n";
        SysMessage::box() << "Int8_t size must be 8 bits (1 bytes)";
        return false;
    }

    if (int8tunderflow != 127)
    {
        // Invalid int8_t undeflow
        SysMessage::box() << "[0x101A] Invalid int8_t underflow\n";
        SysMessage::box() << "Int8_t must be signed [-128; 127]";
        return false;
    }

    if (int8toverflow != -128)
    {
        // Invalid int8_t overflow
        SysMessage::box() << "[0x101B] Invalid int8_t overflow\n";
        SysMessage::box() << "Int8_t must be signed [-128; 127]";
        return false;
    }

    if (uint8tsize != 1)
    {
        // Invalid uint8_t memory size
        SysMessage::box() << "[0x101C] Invalid uint8_t memory size\n";
        SysMessage::box() << "Int8_t size must be 8 bits (1 bytes)";
        return false;
    }

    if (uint8tunderflow != 255)
    {
        // Invalid uint8_t undeflow
        SysMessage::box() << "[0x101D] Invalid uint8_t underflow\n";
        SysMessage::box() << "Int8_t must be unsigned [0; 255]";
        return false;
    }

    if (uint8toverflow != 0)
    {
        // Invalid uint8_t overflow
        SysMessage::box() << "[0x101E] Invalid uint8_t overflow\n";
        SysMessage::box() << "Int8_t must be unsigned [0; 255]";
        return false;
    }

    // Int memory representation is valid
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Check system memory float representation                                  //
//  return : True if the system memory float representation is correct        //
////////////////////////////////////////////////////////////////////////////////
bool SysMemoryCheckFloat()
{
    // Check float representation
    std::size_t floatsize = sizeof(float);

    if (floatsize != 4)
    {
        // Invalid float memory size
        SysMessage::box() << "[0x101F] Invalid float memory size\n";
        SysMessage::box() << "Float size must be 32 bits (4 bytes)";
        return false;
    }

    if (std::numeric_limits<float>::epsilon() > Math::FloatEpsilon)
    {
        // Invalid float epsilon
        SysMessage::box() << "[0x1020] Invalid float epsilon\n";
        SysMessage::box() << "Float minimum epsilon must be 2.5e-07";
        return false;
    }

    // Float memory representation is valid
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Check system memory double representation                                 //
//  return : True if the system memory double representation is correct       //
////////////////////////////////////////////////////////////////////////////////
bool SysMemoryCheckDouble()
{
    // Check double representation
    std::size_t doublesize = sizeof(double);

    if (doublesize != 8)
    {
        // Invalid double memory size
        SysMessage::box() << "[0x1021] Invalid double memory size\n";
        SysMessage::box() << "Double size must be 64 bits (8 bytes)";
        return false;
    }

    if (std::numeric_limits<double>::epsilon() > Math::DoubleEpsilon)
    {
        // Invalid double epsilon
        SysMessage::box() << "[0x1022] Invalid double epsilon\n";
        SysMessage::box() << "Double minimum epsilon must be 5.0e-16";
        return false;
    }

    // Double memory representation is valid
    return true;
}
