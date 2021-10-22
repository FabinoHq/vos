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
//     Images/PNGFile.cpp : PNGFile image management                          //
////////////////////////////////////////////////////////////////////////////////
#include "PNGFile.h"


////////////////////////////////////////////////////////////////////////////////
//  PNGFile default constructor                                               //
////////////////////////////////////////////////////////////////////////////////
PNGFile::PNGFile() :
m_loaded(false),
m_image(0),
m_width(0),
m_height(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  PNGFile destructor                                                        //
////////////////////////////////////////////////////////////////////////////////
PNGFile::~PNGFile()
{
    if (m_image)
    {
        delete[] m_image;
    }
    m_height = 0;
    m_width = 0;
    m_image = 0;
    m_loaded = false;
}


////////////////////////////////////////////////////////////////////////////////
//  Set PNG file image                                                        //
//  return : True if PNG file image is successfully set                       //
////////////////////////////////////////////////////////////////////////////////
bool PNGFile::setImage(uint32_t width, uint32_t height,
    const unsigned char* image)
{
    // Check image loaded state
    if (m_loaded)
    {
        // Destroy current image
        destroyImage();
    }

    // Check image size
    if ((width <= 0) || (height <= 0) ||
        (width > PNGFileMaxImageWidth) ||
        (height > PNGFileMaxImageHeight))
    {
        // Invalid image size
        return false;
    }

    // Set PNG image data
    size_t imageSize = width*height*4;
    try
    {
        // Allocate raw image data
        m_image = new unsigned char[imageSize];
    }
    catch (const std::bad_alloc&)
    {
        // Could not allocate image data
        return false;
    }
    catch (...)
    {
        // Could not allocate image data
        return false;
    }
    if (!m_image)
    {
        // Invalid image data
        return false;
    }

    // Copy image data
    memcpy(m_image, image, imageSize);

    // Set image size
    m_width = width;
    m_height = height;

    // PNG file image is successfully set
    m_loaded = true;
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Load PNG file                                                             //
//  return : True if PNG file is successfully loaded                          //
////////////////////////////////////////////////////////////////////////////////
bool PNGFile::loadImage(const std::string& filepath)
{
    // Check image loaded state
    if (m_loaded)
    {
        // Destroy current image
        destroyImage();
    }

    // Load PNG file
    std::ifstream pngFile;
    pngFile.open(filepath.c_str(), std::ios::in | std::ios::binary);
    if (!pngFile.is_open())
    {
        // Could not load PNG file
        return false;
    }

    // Read PNG file signature
    unsigned char pngSignature[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    pngFile.read((char*)pngSignature, 8);
    if (!pngFile)
    {
        // Could not read PNG file signature
        return false;
    }

    // Check PNG file signature
    if ((pngSignature[0] != PNGFileSignature[0]) ||
        (pngSignature[1] != PNGFileSignature[1]) ||
        (pngSignature[2] != PNGFileSignature[2]) ||
        (pngSignature[3] != PNGFileSignature[3]) ||
        (pngSignature[4] != PNGFileSignature[4]) ||
        (pngSignature[5] != PNGFileSignature[5]) ||
        (pngSignature[6] != PNGFileSignature[6]) ||
        (pngSignature[7] != PNGFileSignature[7]))
    {
        // Invalid PNG file signature
        return false;
    }

    // Read PNG file IHDR chunk header
    PNGFileChunkHeader pngIHDRChunkHeader = {0, {0, 0, 0, 0}};
    pngFile.read((char*)&pngIHDRChunkHeader, PNGFileChunkHeaderSize);
    if (!pngFile)
    {
        // Could not read PNG file IHDR chunk header
        return false;
    }
    pngIHDRChunkHeader.length = SysSwapEndianness(pngIHDRChunkHeader.length);

    // Check PNG file IHDR chunk type
    if ((pngIHDRChunkHeader.type[0] != PNGFileIHDRChunkType[0]) ||
        (pngIHDRChunkHeader.type[1] != PNGFileIHDRChunkType[1]) ||
        (pngIHDRChunkHeader.type[2] != PNGFileIHDRChunkType[2]) ||
        (pngIHDRChunkHeader.type[3] != PNGFileIHDRChunkType[3]))
    {
        // Invalid PNG file IHDR chunk type
        return false;
    }

    // Check PNG file IHDR chunk length
    if (pngIHDRChunkHeader.length != PNGFileIHDRChunkSize)
    {
        // Invalid PNG file IHDR chunk length
        return false;
    }

    // Read PNG file IHDR chunk
    PNGFileIHDRChunk pngIHDRChunk = {0, 0, 0, 0, 0, 0, 0};
    pngFile.read((char*)&pngIHDRChunk, PNGFileIHDRChunkSize);
    if (!pngFile)
    {
        // Could not read PNG file IHDR chunk
        return false;
    }

    // Read PNG file IHDR chunk CRC
    uint32_t pngIHDRChunkCRC = 0;
    pngFile.read((char*)&pngIHDRChunkCRC, PNGFileChunkCRCSize);
    if (!pngFile)
    {
        // Could not read PNG file IHDR chunk CRC
        return false;
    }
    pngIHDRChunkCRC = SysSwapEndianness(pngIHDRChunkCRC);

    // Check PNG file IHDR chunk CRC
    uint32_t checkIHDRChunkCRC = SysCRC32Default;
    checkIHDRChunkCRC = SysUpdateCRC32(
        checkIHDRChunkCRC, pngIHDRChunkHeader.type, PNGFileChunkHeaderTypeSize
    );
    checkIHDRChunkCRC = SysUpdateCRC32(
        checkIHDRChunkCRC, (unsigned char*)&pngIHDRChunk, PNGFileIHDRChunkSize
    );
    if ((checkIHDRChunkCRC^SysCRC32Final) != pngIHDRChunkCRC)
    {
        // Invalid PNG file IHDR chunk CRC
        return false;
    }

    // Swap PNG file IHDR chunk byte endianness
    pngIHDRChunk.width = SysSwapEndianness(pngIHDRChunk.width);
    pngIHDRChunk.height = SysSwapEndianness(pngIHDRChunk.height);

    // Check PNG file image size
    if ((pngIHDRChunk.width <= 0) || (pngIHDRChunk.height <= 0) ||
        (pngIHDRChunk.width > PNGFileMaxImageWidth) ||
        (pngIHDRChunk.height > PNGFileMaxImageHeight))
    {
        // Invalid PNG file image size
        return false;
    }

    // Check PNG file bit depth
    if (pngIHDRChunk.bitDepth != 8)
    {
        // Unsupported PNG file bit depth
        return false;
    }

    // Check PNG file compression
    if (pngIHDRChunk.compression != 0)
    {
        // Unsupported PNG file compression
        return false;
    }

    // Check PNG file filter
    if (pngIHDRChunk.filter != 0)
    {
        // Unsupported PNG file filter
        return false;
    }

    // Check PNG file interlace
    if (pngIHDRChunk.interlace != 0)
    {
        // Unsupported PNG file interlace
        return false;
    }

    // Check PNG file color type
    switch (pngIHDRChunk.colorType)
    {
        case 0:
            // Greyscale color type
            // Unsupported PNG file color type
            return false;
        case 2:
            // RGB color type
            break;
        case 3:
            // Palette index color type
            // Unsupported PNG file color type
            return false;
        case 4:
            // Greyscale with alpha color type
            // Unsupported PNG file color type
            return false;
        case 6:
            // Load 32bits RGBA PNG
            if (!loadPNG32bits(
                pngFile, pngIHDRChunk.width, pngIHDRChunk.height))
            {
                return false;
            }
            break;
        default:
            // Unsupported PNG file color type
            return false;
    }

    // Close PNG file
    pngFile.close();

    // PNG file is successfully loaded
    m_loaded = true;
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Save PNG file                                                             //
//  return : True if PNG file is successfully saved                           //
////////////////////////////////////////////////////////////////////////////////
bool PNGFile::saveImage(const std::string& filepath)
{
    // Check image loaded state
    if (!m_loaded)
    {
        // No current image to save
        return false;
    }

    // Save PNG file
    if (!savePNGImage(filepath, m_width, m_height, m_image))
    {
        // Could not save PNG file
        return false;
    }

    // PNG file is successfully saved
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy PNG image                                                         //
////////////////////////////////////////////////////////////////////////////////
void PNGFile::destroyImage()
{
    if (m_image)
    {
        delete[] m_image;
    }
    m_height = 0;
    m_width = 0;
    m_image = 0;
    m_loaded = false;
}


////////////////////////////////////////////////////////////////////////////////
//  Get PNG file loaded state                                                 //
//  return : True if PNG file is loaded                                       //
////////////////////////////////////////////////////////////////////////////////
bool PNGFile::isLoaded()
{
    return m_loaded;
}

////////////////////////////////////////////////////////////////////////////////
//  Get PNG file image data                                                   //
//  return : PNG file image data                                              //
////////////////////////////////////////////////////////////////////////////////
unsigned char* PNGFile::getImage()
{
    return m_image;
}

////////////////////////////////////////////////////////////////////////////////
//  Get PNG file image width                                                  //
//  return : PNG file image width in pixels                                   //
////////////////////////////////////////////////////////////////////////////////
uint32_t PNGFile::getWidth()
{
    return m_width;
}

////////////////////////////////////////////////////////////////////////////////
//  Get PNG file image height                                                 //
//  return : PNG file image height in pixels                                  //
////////////////////////////////////////////////////////////////////////////////
uint32_t PNGFile::getHeight()
{
    return m_height;
}


////////////////////////////////////////////////////////////////////////////////
//  Save PNG image                                                            //
//  return : True if PNG image is successfully saved                          //
////////////////////////////////////////////////////////////////////////////////
bool PNGFile::savePNGImage(const std::string& filepath,
    uint32_t width, uint32_t height, const unsigned char* image)
{
    // Check image data
    if (!image)
    {
        // Invalid image data
        return false;
    }

    // Check image size
    if ((width <= 0) || (height <= 0) ||
        (width > PNGFileMaxImageWidth) ||
        (height > PNGFileMaxImageHeight))
    {
        // Invalid image size
        return false;
    }

    // Save PNG file
    std::ofstream pngFile;
    pngFile.open(
        filepath.c_str(), std::ios::out | std::ios::trunc | std::ios::binary
    );
    if (!pngFile.is_open())
    {
        // Could not save PNG file
        return false;
    }

    // Write PNG file signature
    pngFile.write((char*)PNGFileSignature, 8);
    if (!pngFile)
    {
        // Could not write PNG file signature
        return false;
    }

    // Close PNG file
    pngFile.close();

    // PNG image is successfully saved
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Load 32bits PNG file image data                                           //
//  return : True if PNG file image data is successfully loaded               //
////////////////////////////////////////////////////////////////////////////////
bool PNGFile::loadPNG32bits(std::ifstream& pngFile,
    uint32_t width, uint32_t height)
{
    // Read PNG file IDAT chunk header
    PNGFileChunkHeader pngIDATChunkHeader = {0, {0, 0, 0, 0}};
    bool pngIDATChunkFound = false;
    while (!pngIDATChunkFound)
    {
        pngFile.read((char*)&pngIDATChunkHeader, PNGFileChunkHeaderSize);
        if (!pngFile)
        {
            // Could not read PNG file chunk header
            return false;
        }
        pngIDATChunkHeader.length = SysSwapEndianness(
            pngIDATChunkHeader.length
        );
        if ((pngIDATChunkHeader.type[0] != PNGFileIDATChunkType[0]) ||
            (pngIDATChunkHeader.type[1] != PNGFileIDATChunkType[1]) ||
            (pngIDATChunkHeader.type[2] != PNGFileIDATChunkType[2]) ||
            (pngIDATChunkHeader.type[3] != PNGFileIDATChunkType[3]))
        {
            pngFile.ignore(pngIDATChunkHeader.length + PNGFileChunkCRCSize);
        }
        else
        {
            // PNG file IDAT chunk header found
            pngIDATChunkFound = true;
        }
    }
    if (!pngIDATChunkFound)
    {
        // Could not find PNG file IDAT chunk header
        return false;
    }

    // Allocate raw image data
    unsigned char* rawData = 0;
    try
    {
        // Allocate raw image data
        rawData = new unsigned char[pngIDATChunkHeader.length];
    }
    catch (const std::bad_alloc&)
    {
        // Could not allocate raw image data
        return false;
    }
    catch (...)
    {
        // Could not allocate raw image data
        return false;
    }
    if (!rawData)
    {
        // Invalid raw image data
        return false;
    }

    // Read PNG file raw image data
    pngFile.read((char*)rawData, pngIDATChunkHeader.length);
    if (!pngFile)
    {
        // Could not read PNG raw image data
        return false;
    }

    // Read PNG file IDAT chunk CRC
    uint32_t pngIDATChunkCRC = 0;
    pngFile.read((char*)&pngIDATChunkCRC, PNGFileChunkCRCSize);
    if (!pngFile)
    {
        // Could not read PNG file IDAT chunk CRC
        return false;
    }
    pngIDATChunkCRC = SysSwapEndianness(pngIDATChunkCRC);

    // Check PNG file IDAT chunk CRC
    uint32_t checkIDATChunkCRC = SysCRC32Default;
    checkIDATChunkCRC = SysUpdateCRC32(
        checkIDATChunkCRC, pngIDATChunkHeader.type, PNGFileChunkHeaderTypeSize
    );
    checkIDATChunkCRC = SysUpdateCRC32(
        checkIDATChunkCRC, rawData, pngIDATChunkHeader.length
    );
    if ((checkIDATChunkCRC^SysCRC32Final) != pngIDATChunkCRC)
    {
        // Invalid PNG file IDAT chunk CRC
        return false;
    }

    // Destroy raw image data
    if (rawData)
    {
        delete[] rawData;
    }

    // PNG file image data is successfully loaded
    return true;
}
