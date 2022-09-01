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
//     Compress/ZLib.cpp : ZLib compression management                        //
////////////////////////////////////////////////////////////////////////////////
#include "ZLib.h"


////////////////////////////////////////////////////////////////////////////////
//  Compute compressed ZLib deflate data size                                 //
//  return : Computed compressed ZLib deflate data size                       //
////////////////////////////////////////////////////////////////////////////////
size_t ZLibComputeDeflateCompressSize(size_t inSize)
{
    bool computed = false;
    size_t outSize = 0;

    // ZLib header
    outSize += 2;

    // Compute deflate data compressed size
    while (!computed)
    {
        // Check remaining size
        if (inSize <= 65535)
        {
            outSize += inSize;
            inSize = 0;
            computed = true;
        }
        else
        {
            outSize += 65535;
            inSize -= 65535;
        }

        // Block infos
        outSize += 1;
        // Block size
        outSize += 4;
    }

    // Adler32 CRC
    outSize += 4;

    // Compressed ZLib deflate data size successfully computed
    return outSize;
}

////////////////////////////////////////////////////////////////////////////////
//  Compress ZLib deflate data                                                //
//  return : True if the data is successfully compressed                      //
////////////////////////////////////////////////////////////////////////////////
bool ZLibDeflateCompress(
    unsigned char* in, size_t inSize, unsigned char* out, size_t* outSize)
{
    size_t inIndex = 0;
    size_t outIndex = 0;
    uint32_t bitsCount = 0;
    uint16_t blockSize = 0;
    uint16_t nBlockSize = 0;
    bool compressed = false;

    // Check data buffers
    if (!in || !out || (inSize <= 0) || (*outSize < 2))
    {
        // Invalid data buffers
        return false;
    }

    // Write ZLib header
    uint16_t zlibHeader = ((8 << 8) | (7 << 12));
    zlibHeader |= (ZLIB_DEFLATE_FASTEST_COMPRESSION << 6);
    zlibHeader |= (31 - (zlibHeader % 31));
    out[outIndex++] = ((zlibHeader >> 8) & 0xFF);
    out[outIndex++] = (zlibHeader & 0xFF);

    // Compress deflate data
    while (!compressed)
    {
        // Check remaining size
        if ((inSize-inIndex) <= 65535)
        {
            blockSize = (uint16_t)(inSize-inIndex);
            compressed = true;
        }
        else
        {
            blockSize = 65535;
        }

        // Check output buffer size
        if ((outIndex + 5) > *outSize) return false;

        // Write final block state
        out[outIndex] = 0;
        out[outIndex] |= ((compressed ? 1 : 0) << bitsCount);
        ++bitsCount;

        // Write block type
        out[outIndex] |= (ZLIB_DEFLATE_BLOCK_UNCOMPRESSED << bitsCount);
        ++bitsCount;

        // Align output
        bitsCount = 0;
        ++outIndex;

        // Write block size
        out[outIndex++] = (blockSize & 0xFF);
        out[outIndex++] = ((blockSize >> 8) & 0xFF);
        nBlockSize = ~blockSize;
        out[outIndex++] = (nBlockSize & 0xFF);
        out[outIndex++] = ((nBlockSize >> 8) & 0xFF);

        // Check buffers sizes
        if ((inIndex + blockSize) > inSize) return false;
        if ((outIndex + blockSize) > *outSize) return false;

        // Copy uncompressed block
        memcpy(&out[outIndex], &in[inIndex], blockSize);
        inIndex += blockSize;
        outIndex += blockSize;
    }

    // Write Adler32 CRC
    if ((outIndex + 4) > *outSize) return false;
    uint32_t zlibAdler32 = SysAdler32(in, inSize);
    out[outIndex++] = ((zlibAdler32 >> 24) & 0xFF);
    out[outIndex++] = ((zlibAdler32 >> 16) & 0xFF);
    out[outIndex++] = ((zlibAdler32 >> 8) & 0xFF);
    out[outIndex++] = (zlibAdler32 & 0xFF);

    // Set output data size
    if (outIndex > *outSize)
    {
        // Invalid output data size
        return false;
    }
    *outSize = outIndex;

    // Data is successfully compressed
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Decompress ZLib deflate data                                              //
//  return : True if the data is successfully decompressed                    //
////////////////////////////////////////////////////////////////////////////////
bool ZLibDeflateDecompress(
    unsigned char* in, size_t inSize, unsigned char* out, size_t* outSize)
{
    size_t inIndex = 0;
    size_t outIndex = 0;
    size_t endIndex = 0;
    uint32_t bitsLeft = 0;
    uint64_t current = 0;
    size_t overrun = 0;
    uint16_t blockSize = 0;
    uint16_t nBlockSize = 0;
    bool decompressed = false;

    // Check data buffers
    if (!in || !out || (inSize < 4) || (*outSize <= 0))
    {
        // Invalid data buffers
        return false;
    }

    // Compute end input index
    endIndex = inSize-4;

    // Check ZLib header
    uint16_t zlibHeader = (in[inIndex++] << 8);
    zlibHeader |= in[inIndex++];
    if ((zlibHeader % 31) != 0) return false;
    if (((zlibHeader >> 8) & 0x000F) != 8) return false;
    if ((zlibHeader >> 12) != 0x0007) return false;
    if ((zlibHeader >> 5) & 0x0001) return false;

    // Decompress deflate data
    while (!decompressed)
    {
        if (bitsLeft < 17)
        {
            do
            {
                if (inIndex < endIndex)
                {
                    current |= (uint64_t)in[inIndex++] << bitsLeft;
                }
                else
                {
                    ++overrun;
                }
                bitsLeft += 8;
            } while(bitsLeft <= 55);
        }

        // Read final block state
        decompressed = current & 0x01;
        current >>= 1;
        bitsLeft -= 1;

        // Read block type
        unsigned char blockType = current & 0x03;
        current >>= 2;
        bitsLeft -= 2;

        switch (blockType)
        {
            // Uncompressed block type
            case ZLIB_DEFLATE_BLOCK_UNCOMPRESSED:
            {
                // Align input
                inIndex -= (bitsLeft >> 3) - overrun;
                overrun = 0;
                current = 0;
                bitsLeft = 0;

                // Check input buffer size
                if ((inIndex + 4) > endIndex) return false;

                // Read block size
                blockSize = in[inIndex++];
                blockSize |= (in[inIndex++] << 8);
                nBlockSize = in[inIndex++];
                nBlockSize |= (in[inIndex++] << 8);

                // Check block size
                if (blockSize != (uint16_t)~nBlockSize) return false;

                // Check buffers sizes
                if ((inIndex + blockSize) > endIndex) return false;
                if ((outIndex + blockSize) > *outSize) return false;

                // Copy uncompressed block
                memcpy(&out[outIndex], &in[inIndex], blockSize);
                inIndex += blockSize;
                outIndex += blockSize;
                break;
            }

            // Static huffman block type
            case ZLIB_DEFLATE_BLOCK_STATIC_HUFFMAN:
            {
                // Unsupported block type
                return false;
            }

            // Dynamic huffman block type
            case ZLIB_DEFLATE_BLOCK_DYNAMIC_HUFFMAN:
            {
                // Unsupported block type
                return false;
            }

            default:
                // Invalid block type
                return false;
        }
    }

    // Align input
    inIndex -= (bitsLeft >> 3) - overrun;
    overrun = 0;
    current = 0;
    bitsLeft = 0;

    // Read Adler32 CRC
    if ((inIndex + 4) > inSize) return false;
    uint32_t zlibAdler32 = (in[inIndex++] << 24);
    zlibAdler32 |= (in[inIndex++] << 16);
    zlibAdler32 |= (in[inIndex++] << 8);
    zlibAdler32 |= in[inIndex++];

    // Check Adler32 CRC
    if (zlibAdler32 != SysAdler32(out, *outSize))
    {
        // Invalid Adler32 CRC
        return false;
    }

    // Set output data size
    if (outIndex > *outSize)
    {
        // Invalid output data size
        return false;
    }
    *outSize = outIndex;

    // Data is successfully decompressed
    return true;
}
