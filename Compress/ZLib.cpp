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
//     Compress/ZLib.cpp : ZLib compression management                        //
////////////////////////////////////////////////////////////////////////////////
#include "ZLib.h"


////////////////////////////////////////////////////////////////////////////////
//  Decompress ZLib deflate data                                              //
//  return : True if the data is successfully decompressed                    //
////////////////////////////////////////////////////////////////////////////////
bool ZLibDeflateDecompress(
	unsigned char* in, size_t inSize, unsigned char* out, size_t outSize)
{
	size_t inIndex = 0;
	size_t outIndex = 0;
	size_t endIndex = inSize-4;
	uint32_t bitsLeft = 0;
	uint64_t current = 0;
	size_t overrun = 0;
	uint16_t blockSize = 0;
	uint16_t nBlockSize = 0;
	bool decompressed = false;

	// Check data buffers
	if (!in || !out || (inSize < 4))
	{
		// Invalid data buffers
		return false;
	}

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

				// Read block size
				blockSize = in[inIndex++];
				blockSize |= (in[inIndex++] << 8);
				nBlockSize = in[inIndex++];
				nBlockSize |= (in[inIndex++] << 8);

				// Check block size
				if (blockSize != (uint16_t)~nBlockSize) return false;

				// Check buffers indices
				if ((inIndex + blockSize) > endIndex) return false;
				if ((outIndex + blockSize) > outSize) return false;

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
	if (zlibAdler32 != SysAdler32(out, outSize))
	{
		// Invalid Adler32 CRC
		return false;
	}

	// Data is successfully decompressed
	return true;
}
