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

    if (!SysMemoryCheckEndianness())
    {
        // Invalid system memory endianness
        return false;
    }

    if (!SysMemoryCheckMaths())
    {
        // Invalid maths memory represantion
        return false;
    }

    if (!SysMemoryCheckImages())
    {
        // Invalid images memory represantion
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
    size_t charsize = sizeof(char);
    size_t signedcharsize = sizeof(signed char);
    signed char signedcharunderflow = -128;
    --signedcharunderflow;
    signed char signedcharoverflow = 127;
    ++signedcharoverflow;
    size_t unsignedcharsize = sizeof(unsigned char);
    unsigned char unsignedcharunderflow = 0;
    --unsignedcharunderflow;
    unsigned char unsignedcharoverflow = 255;
    ++unsignedcharoverflow;
    size_t wchartsize = sizeof(wchar_t);

    if (charsize != 1)
    {
        // Invalid char memory size
        SysMessage::box() << "[0x1001] Invalid char memory size\n";
        SysMessage::box() << "Char size must be 8 bits (1 byte)";
        return false;
    }

    if (signedcharsize != 1)
    {
        // Invalid signed char memory size
        SysMessage::box() << "[0x1002] Invalid signed char memory size\n";
        SysMessage::box() << "Signed char size must be 8 bits (1 byte)";
        return false;
    }

    if (!std::numeric_limits<signed char>::is_signed)
    {
        // Invalid signed char memory representation
        SysMessage::box() << "[0x1003] Invalid signed char memory type\n";
        SysMessage::box() << "Signed char must be signed [-128; 127]";
        return false;
    }

    if (signedcharunderflow != 127)
    {
        // Invalid signed char undeflow
        SysMessage::box() << "[0x1004] Invalid signed char underflow\n";
        SysMessage::box() << "Signed char must be signed [-128; 127]";
        return false;
    }

    if (signedcharoverflow != -128)
    {
        // Invalid signed char overflow
        SysMessage::box() << "[0x1005] Invalid signed char overflow\n";
        SysMessage::box() << "Signed char must be signed [-128; 127]";
        return false;
    }

    if (unsignedcharsize != 1)
    {
        // Invalid unsigned char memory size
        SysMessage::box() << "[0x1006] Invalid unsigned char memory size\n";
        SysMessage::box() << "Unsigned char size must be 8 bits (1 byte)";
        return false;
    }

    if (std::numeric_limits<unsigned char>::is_signed)
    {
        // Invalid unsigned char memory representation
        SysMessage::box() << "[0x1007] Invalid unsigned char memory type\n";
        SysMessage::box() << "Unsigned char must be unsigned [0; 255]";
        return false;
    }

    if (unsignedcharunderflow != 255)
    {
        // Invalid unsigned char undeflow
        SysMessage::box() << "[0x1008] Invalid unsigned char underflow\n";
        SysMessage::box() << "Unsigned char must be unsigned [0; 255]";
        return false;
    }

    if (unsignedcharoverflow != 0)
    {
        // Invalid unsigned char overflow
        SysMessage::box() << "[0x1009] Invalid unsigned char overflow\n";
        SysMessage::box() << "Unsigned char must be unsigned [0; 255]";
        return false;
    }

    if (wchartsize < 2)
    {
        // Invalid wchar_t memory size
        SysMessage::box() << "[0x100A] Invalid wchar_t memory size\n";
        SysMessage::box() << "Wchar_t must be at least 16 bits (2 bytes)";
        return false;
    }
    else
    {
        if (wchartsize == 2)
        {
            if (std::numeric_limits<wchar_t>::is_signed)
            {
                // Invalid wchar_t memory representation
                SysMessage::box() << "[0x100B] Invalid wchar_t memory type\n";
                SysMessage::box() << "Wchar_t must guarantee [0; 65535]";
                return false;
            }
        }
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
    size_t boolsize = sizeof(bool);
    bool booltrue = true;
    bool boolfalse = false;

    if (boolsize != 1)
    {
        // Invalid bool memory size
        SysMessage::box() << "[0x100C] Invalid bool memory size\n";
        SysMessage::box() << "Bool size must be 8 bits (1 byte)";
        return false;
    }

    if (static_cast<unsigned char>(booltrue) != 1)
    {
        // Invalid bool true value
        SysMessage::box() << "[0x100D] Invalid bool true value\n";
        SysMessage::box() << "Bool true value must be 1";
        return false;
    }

    if (static_cast<unsigned char>(boolfalse) != 0)
    {
        // Invalid bool false value
        SysMessage::box() << "[0x100E] Invalid bool false value\n";
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
    size_t intsize = sizeof(int);
    size_t signedintsize = sizeof(signed int);
    size_t unsignedintsize = sizeof(unsigned int);

    size_t int8tsize = sizeof(int8_t);
    int8_t int8tunderflow = -128;
    --int8tunderflow;
    int8_t int8toverflow = 127;
    ++int8toverflow;
    size_t uint8tsize = sizeof(uint8_t);
    uint8_t uint8tunderflow = 0;
    --uint8tunderflow;
    uint8_t uint8toverflow = 255;
    ++uint8toverflow;
    size_t int16tsize = sizeof(int16_t);
    int16_t int16tunderflow = -32768;
    --int16tunderflow;
    int16_t int16toverflow = 32767;
    ++int16toverflow;
    size_t uint16tsize = sizeof(uint16_t);
    uint16_t uint16tunderflow = 0;
    --uint16tunderflow;
    uint16_t uint16toverflow = 65535;
    ++uint16toverflow;
    size_t int32tsize = sizeof(int32_t);
    int32_t int32tunderflow = -2147483648;
    --int32tunderflow;
    int32_t int32toverflow = 2147483647;
    ++int32toverflow;
    size_t uint32tsize = sizeof(uint32_t);
    uint32_t uint32tunderflow = 0;
    --uint32tunderflow;
    uint32_t uint32toverflow = 4294967295;
    ++uint32toverflow;
    size_t int64tsize = sizeof(int64_t);
    size_t uint64tsize = sizeof(uint64_t);
    size_t sizetsize = sizeof(size_t);

    if (intsize < 2)
    {
        // Invalid int memory size
        SysMessage::box() << "[0x100F] Invalid int memory size\n";
        SysMessage::box() << "Int must be at least 16 bits (2 bytes)";
        return false;
    }

    if (signedintsize < 2)
    {
        // Invalid int memory size
        SysMessage::box() << "[0x1010] Invalid signed int memory size\n";
        SysMessage::box() << "Signed int must be at least 16 bits (2 bytes)";
        return false;
    }

    if (!std::numeric_limits<signed int>::is_signed)
    {
        // Invalid signed int memory representation
        SysMessage::box() << "[0x1011] Invalid signed int memory type\n";
        SysMessage::box() << "Signed int must be signed";
        return false;
    }

    if (unsignedintsize < 2)
    {
        // Invalid unsigned int memory size
        SysMessage::box() << "[0x1012] Invalid unsigned int memory size\n";
        SysMessage::box() << "Unsigned int must be at least 16 bits (2 bytes)";
        return false;
    }

    if (std::numeric_limits<unsigned int>::is_signed)
    {
        // Invalid unsigned int memory representation
        SysMessage::box() << "[0x1013] Invalid unsigned int memory type\n";
        SysMessage::box() << "Unsigned int must be unsigned";
        return false;
    }


    if (int8tsize != 1)
    {
        // Invalid int8_t memory size
        SysMessage::box() << "[0x1014] Invalid int8_t memory size\n";
        SysMessage::box() << "Int8_t size must be 8 bits (1 byte)";
        return false;
    }

    if (!std::numeric_limits<int8_t>::is_signed)
    {
        // Invalid int8_t memory representation
        SysMessage::box() << "[0x1015] Invalid int8_t memory type\n";
        SysMessage::box() << "Int8_t must be signed [-128; 127]";
        return false;
    }

    if (int8tunderflow != 127)
    {
        // Invalid int8_t undeflow
        SysMessage::box() << "[0x1016] Invalid int8_t underflow\n";
        SysMessage::box() << "Int8_t must be signed [-128; 127]";
        return false;
    }

    if (int8toverflow != -128)
    {
        // Invalid int8_t overflow
        SysMessage::box() << "[0x1017] Invalid int8_t overflow\n";
        SysMessage::box() << "Int8_t must be signed [-128; 127]";
        return false;
    }

    if (uint8tsize != 1)
    {
        // Invalid uint8_t memory size
        SysMessage::box() << "[0x1018] Invalid uint8_t memory size\n";
        SysMessage::box() << "Uint8_t size must be 8 bits (1 byte)";
        return false;
    }

    if (std::numeric_limits<uint8_t>::is_signed)
    {
        // Invalid uint8_t memory representation
        SysMessage::box() << "[0x1019] Invalid uint8_t memory type\n";
        SysMessage::box() << "Uint8_t must be unsigned [0; 255]";
        return false;
    }

    if (uint8tunderflow != 255)
    {
        // Invalid uint8_t undeflow
        SysMessage::box() << "[0x101A] Invalid uint8_t underflow\n";
        SysMessage::box() << "Uint8_t must be unsigned [0; 255]";
        return false;
    }

    if (uint8toverflow != 0)
    {
        // Invalid uint8_t overflow
        SysMessage::box() << "[0x101B] Invalid uint8_t overflow\n";
        SysMessage::box() << "Uint8_t must be unsigned [0; 255]";
        return false;
    }

    if (int16tsize != 2)
    {
        // Invalid int16_t memory size
        SysMessage::box() << "[0x101C] Invalid int16_t memory size\n";
        SysMessage::box() << "Int16_t size must be 16 bits (2 bytes)";
        return false;
    }

    if (!std::numeric_limits<int16_t>::is_signed)
    {
        // Invalid int16_t memory representation
        SysMessage::box() << "[0x101D] Invalid int16_t memory type\n";
        SysMessage::box() << "Int16_t must be signed [-32768; 32767]";
        return false;
    }

    if (int16tunderflow != 32767)
    {
        // Invalid int16_t undeflow
        SysMessage::box() << "[0x101E] Invalid int16_t underflow\n";
        SysMessage::box() << "Int16_t must be signed [-32768; 32767]";
        return false;
    }

    if (int16toverflow != -32768)
    {
        // Invalid int16_t overflow
        SysMessage::box() << "[0x101F] Invalid int16_t overflow\n";
        SysMessage::box() << "Int16_t must be signed [-32768; 32767]";
        return false;
    }

    if (uint16tsize != 2)
    {
        // Invalid uint16_t memory size
        SysMessage::box() << "[0x1020] Invalid uint16_t memory size\n";
        SysMessage::box() << "Uint16_t size must be 16 bits (2 bytes)";
        return false;
    }

    if (std::numeric_limits<uint16_t>::is_signed)
    {
        // Invalid uint16_t memory representation
        SysMessage::box() << "[0x1021] Invalid uint16_t memory type\n";
        SysMessage::box() << "Uint16_t must be unsigned [0; 65535]";
        return false;
    }

    if (uint16tunderflow != 65535)
    {
        // Invalid uint16_t undeflow
        SysMessage::box() << "[0x1022] Invalid uint16_t underflow\n";
        SysMessage::box() << "Uint16_t must be unsigned [0; 65535]";
        return false;
    }

    if (uint16toverflow != 0)
    {
        // Invalid uint16_t overflow
        SysMessage::box() << "[0x1023] Invalid uint16_t overflow\n";
        SysMessage::box() << "Uint16_t must be unsigned [0; 65535]";
        return false;
    }

    if (int32tsize != 4)
    {
        // Invalid int32_t memory size
        SysMessage::box() << "[0x1024] Invalid int32_t memory size\n";
        SysMessage::box() << "Int32_t size must be 32 bits (4 bytes)";
        return false;
    }

    if (!std::numeric_limits<int32_t>::is_signed)
    {
        // Invalid int32_t memory representation
        SysMessage::box() << "[0x1025] Invalid int32_t memory type\n";
        SysMessage::box() << "Int32_t must be signed [-2147483648; 2147483647]";
        return false;
    }

    if (int32tunderflow != 2147483647)
    {
        // Invalid int32_t undeflow
        SysMessage::box() << "[0x1026] Invalid int32_t underflow\n";
        SysMessage::box() << "Int32_t must be signed [-2147483648; 2147483647]";
        return false;
    }

    if (int32toverflow != -2147483648)
    {
        // Invalid int32_t overflow
        SysMessage::box() << "[0x1027] Invalid int32_t overflow\n";
        SysMessage::box() << "Int32_t must be signed [-2147483648; 2147483647]";
        return false;
    }

    if (uint32tsize != 4)
    {
        // Invalid uint32_t memory size
        SysMessage::box() << "[0x1028] Invalid uint32_t memory size\n";
        SysMessage::box() << "Uint32_t size must be 32 bits (4 bytes)";
        return false;
    }

    if (std::numeric_limits<uint32_t>::is_signed)
    {
        // Invalid uint32_t memory representation
        SysMessage::box() << "[0x1029] Invalid uint32_t memory type\n";
        SysMessage::box() << "Uint32_t must be unsigned [0; 4294967295]";
        return false;
    }

    if (uint32tunderflow != 4294967295)
    {
        // Invalid uint32_t undeflow
        SysMessage::box() << "[0x102A] Invalid uint32_t underflow\n";
        SysMessage::box() << "Uint32_t must be unsigned [0; 4294967295]";
        return false;
    }

    if (uint32toverflow != 0)
    {
        // Invalid uint32_t overflow
        SysMessage::box() << "[0x102B] Invalid uint32_t overflow\n";
        SysMessage::box() << "Uint32_t must be unsigned [0; 4294967295]";
        return false;
    }

    if (int64tsize != 8)
    {
        // Invalid int64_t memory size
        SysMessage::box() << "[0x102C] Invalid int64_t memory size\n";
        SysMessage::box() << "Int64_t size must be 64 bits (8 bytes)";
        return false;
    }

    if (!std::numeric_limits<int64_t>::is_signed)
    {
        // Invalid int64_t memory representation
        SysMessage::box() << "[0x102D] Invalid int64_t memory type\n";
        SysMessage::box() << "Int64_t must be signed\n";
        SysMessage::box() << "[-9223372036854775808; 9223372036854775807]";
        return false;
    }

    if (uint64tsize != 8)
    {
        // Invalid uint64_t memory size
        SysMessage::box() << "[0x102E] Invalid uint64_t memory size\n";
        SysMessage::box() << "Uint64_t size must be 64 bits (8 bytes)";
        return false;
    }

    if (std::numeric_limits<uint64_t>::is_signed)
    {
        // Invalid uint64_t memory representation
        SysMessage::box() << "[0x102F] Invalid uint64_t memory type\n";
        SysMessage::box() << "Uint64_t must be unsigned\n";
        SysMessage::box() << "[0; 18446744073709551615]";
        return false;
    }

    #ifdef VOS_64BITS
        if (sizetsize < 8)
        {
            // Invalid size_t memory size
            SysMessage::box() << "[0x1030] Invalid size_t memory size\n";
            SysMessage::box() << "Size_t must be at least 64 bits (8 bytes)";
            return false;
        }
    #else
        if (sizetsize < 4)
        {
            // Invalid size_t memory size
            SysMessage::box() << "[0x1031] Invalid size_t memory size\n";
            SysMessage::box() << "Size_t must be at least 32 bits (4 bytes)";
            return false;
        }
    #endif

    if (std::numeric_limits<size_t>::is_signed)
    {
        // Invalid size_t memory representation
        SysMessage::box() << "[0x1032] Invalid size_t memory type\n";
        SysMessage::box() << "Size_t must be unsigned";
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
    size_t floatsize = sizeof(float);

    if (floatsize != 4)
    {
        // Invalid float memory size
        SysMessage::box() << "[0x1033] Invalid float memory size\n";
        SysMessage::box() << "Float size must be 32 bits (4 bytes)";
        return false;
    }

    if (std::numeric_limits<float>::epsilon() > Math::FloatEpsilon)
    {
        // Invalid float epsilon
        SysMessage::box() << "[0x1034] Invalid float epsilon\n";
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
    size_t doublesize = sizeof(double);

    if (doublesize != 8)
    {
        // Invalid double memory size
        SysMessage::box() << "[0x1035] Invalid double memory size\n";
        SysMessage::box() << "Double size must be 64 bits (8 bytes)";
        return false;
    }

    if (std::numeric_limits<double>::epsilon() > Math::DoubleEpsilon)
    {
        // Invalid double epsilon
        SysMessage::box() << "[0x1036] Invalid double epsilon\n";
        SysMessage::box() << "Double minimum epsilon must be 5.0e-16";
        return false;
    }

    // Double memory representation is valid
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Check system memory endianness                                            //
//  return : True if the system memory is little-endian                       //
////////////////////////////////////////////////////////////////////////////////
bool SysMemoryCheckEndianness()
{
    // Check system memory endianness
    uint32_t endianness = 0x04030201;
    uint32_t byte0 = (endianness & 0x000000FF) >> 0;
    uint32_t byte1 = (endianness & 0x0000FF00) >> 8;
    uint32_t byte2 = (endianness & 0x00FF0000) >> 16;
    uint32_t byte3 = (endianness & 0xFF000000) >> 24;

    if (byte0 != 0x01 || byte1 != 0x02 || byte2 != 0x03 || byte3 != 0x04)
    {
        // System memory is not little-endian
        SysMessage::box() << "[0x1037] Invalid system memory endianness\n";
        SysMessage::box() << "System memory must be little-endian";
        return false;
    }

    // System memory is little-endian
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Check system memory maths representations                                 //
//  return : True if the system memory maths representations are correct      //
////////////////////////////////////////////////////////////////////////////////
bool SysMemoryCheckMaths()
{
    // Check Vector2 memory
    size_t vector2size = sizeof(Vector2::vec);
    if (vector2size != (sizeof(float)*2))
    {
        // Vector 2 memory representation is invalid
        SysMessage::box() << "[0x1038] Invalid Vector2 memory size\n";
        SysMessage::box() << "Vector2 memory size should be 64bits (8 bytes)";
        return false;
    }

    // Check Vector3 memory
    size_t vector3size = sizeof(Vector3::vec);
    if (vector3size != (sizeof(float)*3))
    {
        SysMessage::box() << "[0x1039] Invalid Vector3 memory size\n";
        SysMessage::box() << "Vector3 memory size should be 96bits (12 bytes)";
        return false;
    }

    // Check Vector4 memory
    size_t vector4size = sizeof(Vector4::vec);
    if (vector4size != (sizeof(float)*4))
    {
        SysMessage::box() << "[0x103A] Invalid Vector4 memory size\n";
        SysMessage::box() << "Vector4 memory size should be 128bits (16 bytes)";
        return false;
    }

    // Check Matrix4x4 memory
    size_t matrix4size = sizeof(Matrix4x4::mat);
    if (matrix4size != (sizeof(float)*16))
    {
        SysMessage::box() << "[0x103B] Invalid Matrix4 memory size\n";
        SysMessage::box() << "Matrix4 memory size should be 512bits (64 bytes)";
        return false;
    }

    // System memory maths representations are correct
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Check system memory images representations                                //
//  return : True if the system memory images representations are correct     //
////////////////////////////////////////////////////////////////////////////////
bool SysMemoryCheckImages()
{
    // Check BMPFileHeader memory
    size_t bmpFileHeaderSize = sizeof(BMPFileHeader);
    if (bmpFileHeaderSize < BMPFileHeaderSize)
    {
        // BMPFileHeader memory representation is invalid
        SysMessage::box() << "[0x103C] Invalid BMPFileHeader memory size\n";
        SysMessage::box() << "BMPFileHeader memory size should be " <<
            BMPFileHeaderSize << " bytes";
        return false;
    }

    // Check BMPFileInfo memory
    size_t bmpFileInfoSize = sizeof(BMPFileInfo);
    if (bmpFileInfoSize < BMPFileInfoSize)
    {
        // BMPFileInfo memory representation is invalid
        SysMessage::box() << "[0x103D] Invalid BMPFileInfo memory size\n";
        SysMessage::box() << "BMPFileInfo memory size should be " <<
            BMPFileInfoSize << " bytes";
        return false;
    }

    // Check PNGFileChunkHeader memory
    size_t pngFileChunkHeader = sizeof(PNGFileChunkHeader);
    if (pngFileChunkHeader < PNGFileChunkHeaderSize)
    {
        // PNGFileChunkHeader memory representation is invalid
        SysMessage::box() <<
            "[0x103E] Invalid PNGFileChunkHeader memory size\n";
        SysMessage::box() << "PNGFileChunkHeader memory size should be " <<
            PNGFileChunkHeaderSize << " bytes";
        return false;
    }

    // Check PNGFileIHDRChunk memory
    size_t pngFileIHDRChunk = sizeof(PNGFileIHDRChunk);
    if (pngFileIHDRChunk < PNGFileIHDRChunkSize)
    {
        // PNGFileIHDRChunk memory representation is invalid
        SysMessage::box() << "[0x103F] Invalid PNGFileIHDRChunk memory size\n";
        SysMessage::box() << "PNGFileIHDRChunk memory size should be " <<
            PNGFileIHDRChunkSize << " bytes";
        return false;
    }

    // System memory images representations are correct
    return true;
}
