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

    // Load PNG file image data
    if (!loadPNGData(pngFile, pngIHDRChunk))
    {
        // Could not load PNG image data
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
//  Load PNG file image data                                                  //
//  return : True if PNG file image data is successfully loaded               //
////////////////////////////////////////////////////////////////////////////////
bool PNGFile::loadPNGData(std::ifstream& pngFile,
    PNGFileIHDRChunk& pngIHDRChunk)
{
    // Set pixel depth
    uint32_t pixelDepth = 0;
    switch (pngIHDRChunk.colorType)
    {
        case PNGFILE_COLOR_GREYSCALE:
            // Unsupported PNG file color type
            return false;
        case PNGFILE_COLOR_RGB:
            pixelDepth = 3;
            break;
        case PNGFILE_COLOR_PALETTE:
            // Unsupported PNG file color type
            return false;
        case PNGFILE_COLOR_GREYSCALE_ALPHA:
            // Unsupported PNG file color type
            return false;
        case PNGFILE_COLOR_RGBA:
            pixelDepth = 4;
            break;
        default:
            // Unsupported PNG file color type
            return false;
    }

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

    // Allocate decompressed data
    size_t pngDataSize =
        (pngIHDRChunk.width*pngIHDRChunk.height*pixelDepth)+pngIHDRChunk.height;
    unsigned char* pngData = 0;
    try
    {
        pngData = new unsigned char[pngDataSize];
    }
    catch (const std::bad_alloc&)
    {
        // Could not allocate decompressed data
        return false;
    }
    catch (...)
    {
        // Could not allocate decompressed data
        return false;
    }
    if (!pngData)
    {
        // Invalid decompressed data
        return false;
    }

    // Decompress deflate data
    if (!ZLibDeflateDecompress(
        rawData, pngIDATChunkHeader.length, pngData, pngDataSize))
    {
        // Could not decompress deflate data
        return false;
    }

    // Allocate image data
    size_t imageSize = pngIHDRChunk.width*pngIHDRChunk.height*4;
    try
    {
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

    // Decode PNG image data
    switch (pngIHDRChunk.colorType)
    {
        case PNGFILE_COLOR_GREYSCALE:
            // Unsupported PNG file color type
            return false;
        case PNGFILE_COLOR_RGB:
            // Decode 24 bits RGB PNG
            if (!decodePNG24bits(
                pngData, pngIHDRChunk.width, pngIHDRChunk.height))
            {
                // Could not decode 24 bits RGB PNG
                return false;
            }
            break;
        case PNGFILE_COLOR_PALETTE:
            // Unsupported PNG file color type
            return false;
        case PNGFILE_COLOR_GREYSCALE_ALPHA:
            // Unsupported PNG file color type
            return false;
        case PNGFILE_COLOR_RGBA:
            // Decode 32 bits RGBA PNG
            if (!decodePNG32bits(
                pngData, pngIHDRChunk.width, pngIHDRChunk.height))
            {
                // Could not decode 32 bits RGBA PNG
                return false;
            }
            break;
        default:
            // Unsupported PNG file color type
            return false;
    }

    // Destroy decompressed data
    if (pngData)
    {
        delete[] pngData;
    }

    // Destroy raw image data
    if (rawData)
    {
        delete[] rawData;
    }

    // Set image size
    m_width = pngIHDRChunk.width;
    m_height = pngIHDRChunk.height;

    // PNG file image data is successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Decode PNG 32 bits data                                                   //
//  return : True if PNG 32 bits data are successfully decoded                //
////////////////////////////////////////////////////////////////////////////////
bool PNGFile::decodePNG32bits(unsigned char* data,
    uint32_t width, uint32_t height)
{
    size_t inIndex = 0;
    size_t outIndex = 0;
    size_t scanlineSize = width*4;
    for (uint32_t j = 0; j < height; ++j)
    {
        // Check scanline filter type
        switch (data[inIndex++])
        {
            case PNGFILE_FILTER_NONE:
            {
                // No filter
                memcpy(&m_image[outIndex], &data[inIndex], scanlineSize);
                outIndex += scanlineSize;
                inIndex += scanlineSize;
                break;
            }
            case PNGFILE_FILTER_SUB:
            {
                // Sub filter
                size_t prevIndex = inIndex;

                // Copy first pixel
                memcpy(&m_image[outIndex], &data[inIndex], 4);
                inIndex += 4;
                outIndex += 4;

                // Decode sub filtered scanline
                for (size_t i = 4; i < scanlineSize; ++i)
                {
                    m_image[outIndex++] =
                        (data[inIndex++] += data[prevIndex++]);
                }
                break;
            }
            case PNGFILE_FILTER_UP:
            {
                // Up filter
                size_t prevIndex = inIndex-scanlineSize-1;
                bool firstLine = false;
                unsigned char prevData = 0;
                if (j <= 0) firstLine = true;

                // Decode up filtered scanline
                for (size_t i = 0; i < scanlineSize; ++i)
                {
                    if (!firstLine) prevData = data[prevIndex];
                    m_image[outIndex++] = (data[inIndex++] += prevData);
                    ++prevIndex;
                }
                break;
            }
            case PNGFILE_FILTER_AVERAGE:
            {
                // Average filter
                size_t prevIndex = inIndex-scanlineSize-1;
                size_t prevIndex2 = inIndex;
                bool firstLine = false;
                unsigned char prevData = 0;
                if (j <= 0) firstLine = true;

                // Decode first pixel (up filtered)
                for (size_t i = 0; i < 4; ++i)
                {
                    if (!firstLine) prevData = (data[prevIndex]/2);
                    m_image[outIndex++] = (data[inIndex++] += prevData);
                    ++prevIndex;
                }

                // Decode avarage filtered scanline
                for (size_t i = 0; i < scanlineSize-4; ++i)
                {
                    if (!firstLine) prevData = data[prevIndex];
                    m_image[outIndex++] = (data[inIndex++] +=
                        ((prevData + data[prevIndex2++])/2));
                    ++prevIndex;
                }
                break;
            }
            case PNGFILE_FILTER_PAETH:
            {
                // Paeth multibyte filter
                size_t prevIndex = inIndex-scanlineSize-1;
                size_t prevIndex2 = prevIndex;
                size_t prevIndex3 = inIndex;
                bool firstLine = false;
                unsigned char currentData = 0;
                unsigned char prevData = 0;
                unsigned char prevData2 = 0;
                int p = 0, pa = 0, pb = 0, pc = 0;

                // Decode first pixel
                for (size_t i = 0; i < 4; ++i)
                {
                    if (!firstLine) prevData = data[prevIndex];
                    m_image[outIndex++] = (data[inIndex++] += prevData);
                    ++prevIndex;
                }

                // Decode paeth filtered scanline
                for (size_t i = 0; i < scanlineSize-4; ++i)
                {
                    currentData = data[prevIndex3++];
                    if (!firstLine) prevData = data[prevIndex];
                    prevData2 = data[prevIndex2++];
                    p = prevData - prevData2;
                    pc = currentData - prevData2;
                    pa = (p < 0) ? -p : p;
                    pb = (pc < 0) ? -pc : pc;
                    pc = ((p + pc) < 0) ? -(p + pc) : (p + pc);
                    if (pb < pa) { pa = pb; currentData = prevData; }
                    if (pc < pa) { currentData = prevData2; }
                    m_image[outIndex++] = (data[inIndex++] += currentData);
                    ++prevIndex;
                }
                break;
            }
            default:
                // Invalid filter type
                return false;
        }
    }

    // PNG 32 bits data are successfully decoded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Decode PNG 24 bits data                                                   //
//  return : True if PNG 24 bits data are successfully decoded                //
////////////////////////////////////////////////////////////////////////////////
bool PNGFile::decodePNG24bits(unsigned char* data,
    uint32_t width, uint32_t height)
{
    size_t inIndex = 0;
    size_t outIndex = 0;
    size_t scanlineSize = width*3;
    size_t alphaMod = 0;
    for (uint32_t j = 0; j < height; ++j)
    {
        // Check scanline filter type
        switch (data[inIndex++])
        {
            case PNGFILE_FILTER_NONE:
            {
                // No filter
                alphaMod = 0;

                // Decode unfiltered scanline
                for (size_t i = 0; i < scanlineSize; ++i)
                {
                    // RGB channels
                    m_image[outIndex++] = data[inIndex++];
                    // Alpha channel
                    if (((++alphaMod) % 3) == 0) m_image[outIndex++] = 255;
                }
                break;
            }
            case PNGFILE_FILTER_SUB:
            {
                // Sub filter
                size_t prevIndex = inIndex;

                // Copy first pixel
                memcpy(&m_image[outIndex], &data[inIndex], 3);
                inIndex += 3;
                outIndex += 3;
                // Add first pixel alpha channel
                m_image[outIndex++] = 255;
                alphaMod = 0;

                // Decode sub filtered scanline
                for (size_t i = 3; i < scanlineSize; ++i)
                {
                    // RGB channels
                    m_image[outIndex++] =
                        (data[inIndex++] += data[prevIndex++]);
                    // Alpha channel
                    if (((++alphaMod) % 3) == 0) m_image[outIndex++] = 255;
                }
                break;
            }
            case PNGFILE_FILTER_UP:
            {
                // Up filter
                size_t prevIndex = inIndex-scanlineSize-1;
                bool firstLine = false;
                unsigned char prevData = 0;
                if (j <= 0) firstLine = true;
                alphaMod = 0;

                // Decode up filtered scanline
                for (size_t i = 0; i < scanlineSize; ++i)
                {
                    // RGB channels
                    if (!firstLine) prevData = data[prevIndex];
                    m_image[outIndex++] = (data[inIndex++] += prevData);
                    ++prevIndex;
                    // Alpha channel
                    if (((++alphaMod) % 3) == 0) m_image[outIndex++] = 255;
                }
                break;
            }
            case PNGFILE_FILTER_AVERAGE:
            {
                // Average filter
                size_t prevIndex = inIndex-scanlineSize-1;
                size_t prevIndex2 = inIndex;
                bool firstLine = false;
                unsigned char prevData = 0;
                if (j <= 0) firstLine = true;

                // Decode first pixel (up filtered)
                for (size_t i = 0; i < 3; ++i)
                {
                    if (!firstLine) prevData = (data[prevIndex]/2);
                    m_image[outIndex++] = (data[inIndex++] += prevData);
                    ++prevIndex;
                }
                // Add first pixel alpha channel
                m_image[outIndex++] = 255;
                alphaMod = 0;

                // Decode average filtered scanline
                for (size_t i = 0; i < scanlineSize-3; ++i)
                {
                    // RGB channels
                    if (!firstLine) prevData = data[prevIndex];
                    m_image[outIndex++] = (data[inIndex++] +=
                        ((prevData + data[prevIndex2++])/2));
                    ++prevIndex;
                    // Alpha channel
                    if (((++alphaMod) % 3) == 0) m_image[outIndex++] = 255;
                }
                break;
            }
            case PNGFILE_FILTER_PAETH:
            {
                // Paeth multibyte filter
                size_t prevIndex = inIndex-scanlineSize-1;
                size_t prevIndex2 = prevIndex;
                size_t prevIndex3 = inIndex;
                bool firstLine = false;
                unsigned char currentData = 0;
                unsigned char prevData = 0;
                unsigned char prevData2 = 0;
                int p = 0, pa = 0, pb = 0, pc = 0;

                // Decode first pixel
                for (size_t i = 0; i < 3; ++i)
                {
                    if (!firstLine) prevData = data[prevIndex];
                    m_image[outIndex++] = (data[inIndex++] += prevData);
                    ++prevIndex;
                }
                // Add first pixel alpha channel
                m_image[outIndex++] = 255;
                alphaMod = 0;

                // Decode paeth filtered scanline
                for (size_t i = 0; i < scanlineSize-3; ++i)
                {
                    // RGB channels
                    currentData = data[prevIndex3++];
                    if (!firstLine) prevData = data[prevIndex];
                    prevData2 = data[prevIndex2++];
                    p = prevData - prevData2;
                    pc = currentData - prevData2;
                    pa = (p < 0) ? -p : p;
                    pb = (pc < 0) ? -pc : pc;
                    pc = ((p + pc) < 0) ? -(p + pc) : (p + pc);
                    if (pb < pa) { pa = pb; currentData = prevData; }
                    if (pc < pa) { currentData = prevData2; }
                    m_image[outIndex++] = (data[inIndex++] += currentData);
                    ++prevIndex;
                    // Alpha channel
                    if (((++alphaMod) % 3) == 0) m_image[outIndex++] = 255;
                }
                break;
            }
            default:
                // Invalid filter type
                return false;
        }
    }

    // PNG 24 bits data are successfully decoded
    return true;
}