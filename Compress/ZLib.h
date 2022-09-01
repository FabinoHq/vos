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
//     Compress/ZLib.h : ZLib compression management                          //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_COMPRESS_ZLIB_HEADER
#define VOS_COMPRESS_ZLIB_HEADER

    #include "../System/System.h"
    #include "../System/SysCRC.h"

    #include <cstddef>
    #include <cstdint>
    #include <cstring>


    ////////////////////////////////////////////////////////////////////////////
    //  ZLib deflate compression level hint enumeration                       //
    ////////////////////////////////////////////////////////////////////////////
    enum ZLibCompressionLevelHint
    {
        ZLIB_DEFLATE_FASTEST_COMPRESSION = 0,
        ZLIB_DEFLATE_FAST_COMPRESSION = 1,
        ZLIB_DEFLATE_DEFAULT_COMPRESSION = 2,
        ZLIB_DEFLATE_SLOWEST_COMPRESSION = 3
    };

    ////////////////////////////////////////////////////////////////////////////
    //  ZLib deflate block types enumeration                                  //
    ////////////////////////////////////////////////////////////////////////////
    enum ZLibDeflateBlockType
    {
        ZLIB_DEFLATE_BLOCK_UNCOMPRESSED = 0,
        ZLIB_DEFLATE_BLOCK_STATIC_HUFFMAN = 1,
        ZLIB_DEFLATE_BLOCK_DYNAMIC_HUFFMAN = 2
    };

    ////////////////////////////////////////////////////////////////////////////
    //  Compute compressed ZLib deflate data size                             //
    //  return : Computed compressed ZLib deflate data size                   //
    ////////////////////////////////////////////////////////////////////////////
    size_t ZLibComputeDeflateCompressSize(size_t inSize);

    ////////////////////////////////////////////////////////////////////////////
    //  Compress ZLib deflate data                                            //
    //  return : True if the data is successfully compressed                  //
    ////////////////////////////////////////////////////////////////////////////
    bool ZLibDeflateCompress(
        unsigned char* in, size_t inSize, unsigned char* out, size_t* outSize);

    ////////////////////////////////////////////////////////////////////////////
    //  Decompress ZLib deflate data                                          //
    //  return : True if the data is successfully decompressed                //
    ////////////////////////////////////////////////////////////////////////////
    bool ZLibDeflateDecompress(
        unsigned char* in, size_t inSize, unsigned char* out, size_t* outSize);


#endif // VOS_COMPRESS_ZLIB_HEADER
