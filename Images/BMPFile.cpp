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
//     Images/BMPFile.cpp : BMPFile image management                          //
////////////////////////////////////////////////////////////////////////////////
#include "BMPFile.h"


////////////////////////////////////////////////////////////////////////////////
//  BMPFile default constructor                                               //
////////////////////////////////////////////////////////////////////////////////
BMPFile::BMPFile() :
m_loaded(false),
m_image(0),
m_width(0),
m_height(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  BMPFile destructor                                                        //
////////////////////////////////////////////////////////////////////////////////
BMPFile::~BMPFile()
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
//  Set BMP file image                                                        //
//  return : True if BMP file image is successfully set                       //
////////////////////////////////////////////////////////////////////////////////
bool BMPFile::setImage(uint32_t width, uint32_t height,
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
        (width > BMPFileMaxImageWidth) ||
        (height > BMPFileMaxImageHeight))
    {
        // Invalid image size
        return false;
    }

    // Set BMP image data
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

    // BMP file image is successfully set
    m_loaded = true;
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Load BMP file                                                             //
//  return : True if BMP file is successfully loaded                          //
////////////////////////////////////////////////////////////////////////////////
bool BMPFile::loadImage(const std::string& filepath)
{
    // Check image loaded state
    if (m_loaded)
    {
        // Destroy current image
        destroyImage();
    }

    // Load BMP file
    std::ifstream bmpFile;
    bmpFile.open(filepath.c_str(), std::ios::in | std::ios::binary);
    if (!bmpFile.is_open())
    {
        // Could not load BMP file
        return false;
    }

    // Read BMP file signature
    unsigned char bmpSignature[2] = {0, 0};
    bmpFile.read((char*)bmpSignature, 2);
    if (!bmpFile)
    {
        // Could not read BMP file signature
        return false;
    }

    // Check BMP file signature
    if ((bmpSignature[0] != BMPFileSignature[0]) ||
        (bmpSignature[1] != BMPFileSignature[1]))
    {
        // Invalid BMP file signature
        return false;
    }

    // Read BMP file header
    BMPFileHeader bmpHeader = {0, 0, 0};
    bmpFile.read((char*)&bmpHeader, BMPFileHeaderSize);
    if (!bmpFile)
    {
        // Could not read BMP file header
        return false;
    }

    // Read BMP file info
    BMPFileInfo bmpInfo = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    bmpFile.read((char*)&bmpInfo, BMPFileInfoSize);
    if (!bmpFile)
    {
        // Could not read BMP file info
        return false;
    }

    // Check BMP file info size
    if (bmpInfo.infoSize != BMPFileInfoSize)
    {
        // Invalid BMP file info size
        return false;
    }

    // Check BMP file image size
    if ((bmpInfo.width <= 0) || (bmpInfo.height <= 0) ||
        (bmpInfo.width > BMPFileMaxImageWidth) ||
        (bmpInfo.height > BMPFileMaxImageHeight))
    {
        // Invalid BMP file image size
        return false;
    }

    // Check BMP file image planes
    if (bmpInfo.planes != 1)
    {
        // Invalid BMP file image planes
        return false;
    }

    // Check BMP file bits per pixel
    switch (bmpInfo.bitsPerPixel)
    {
        case 1:
            // Monochrome palette
            // Unsupported BMP file bits per pixel
            return false;
        case 4:
            // 4 bits palletized
            // Unsupported BMP file bits per pixel
            return false;
        case 8:
            // 8 bits palletized
            // Unsupported BMP file bits per pixel
            return false;
        case 16:
            // 16 bits BGR
            if (bmpInfo.compression == 0)
            {
                // Load 16 bits uncompressed BMP image data
                if (!loadBMP16Bits(bmpFile, bmpHeader.dataOffset,
                    bmpInfo.width, bmpInfo.height))
                {
                    // Could not load 16 bits BMP image data
                    return false;
                }
            }
            else
            {
                // Unsupported 16 bits compression
                return false;
            }
            break;
        case 24:
            // 24 bits BGR
            if (bmpInfo.compression == 0)
            {
                // Load 24 bits uncompressed BMP image data
                if (!loadBMP24Bits(bmpFile, bmpHeader.dataOffset,
                    bmpInfo.width, bmpInfo.height))
                {
                    // Could not load 24 bits BMP image data
                    return false;
                }
            }
            else
            {
                // Unsupported 24 bits compression
                return false;
            }
            break;
        default:
            // Invalid BMP file bits per pixel
            return false;
    }

    // Set image size
    m_width = bmpInfo.width;
    m_height = bmpInfo.height;

    // Close BMP file
    bmpFile.close();

    // BMP file is successfully loaded
    m_loaded = true;
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Save BMP file                                                             //
//  return : True if BMP file is successfully saved                           //
////////////////////////////////////////////////////////////////////////////////
bool BMPFile::saveImage(const std::string& filepath, BMPFileImageFormat format)
{
    // Check image loaded state
    if (!m_loaded)
    {
        // No current image to save
        return false;
    }

    // Save BMP file
    if (!saveBMPImage(filepath, m_width, m_height, m_image, format))
    {
        // Could not save BMP file
        return false;
    }

    // BMP file is successfully saved
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy BMP image                                                         //
////////////////////////////////////////////////////////////////////////////////
void BMPFile::destroyImage()
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
//  Get BMP file loaded state                                                 //
//  return : True if BMP file is loaded                                       //
////////////////////////////////////////////////////////////////////////////////
bool BMPFile::isLoaded()
{
    return m_loaded;
}

////////////////////////////////////////////////////////////////////////////////
//  Get BMP file image data                                                   //
//  return : BMP file image data                                              //
////////////////////////////////////////////////////////////////////////////////
unsigned char* BMPFile::getImage()
{
    return m_image;
}

////////////////////////////////////////////////////////////////////////////////
//  Get BMP file image width                                                  //
//  return : BMP file image width in pixels                                   //
////////////////////////////////////////////////////////////////////////////////
uint32_t BMPFile::getWidth()
{
    return m_width;
}

////////////////////////////////////////////////////////////////////////////////
//  Get BMP file image height                                                 //
//  return : BMP file image height in pixels                                  //
////////////////////////////////////////////////////////////////////////////////
uint32_t BMPFile::getHeight()
{
    return m_height;
}


////////////////////////////////////////////////////////////////////////////////
//  Save BMP image                                                            //
//  return : True if BMP image is successfully saved                          //
////////////////////////////////////////////////////////////////////////////////
bool BMPFile::saveBMPImage(const std::string& filepath,
    uint32_t width, uint32_t height, const unsigned char* image,
    BMPFileImageFormat format)
{
    // Check image data
    if (!image)
    {
        // Invalid image data
        return false;
    }

    // Check image size
    if ((width <= 0) || (height <= 0) ||
        (width > BMPFileMaxImageWidth) ||
        (height > BMPFileMaxImageHeight))
    {
        // Invalid image size
        return false;
    }

    // Save BMP file
    std::ofstream bmpFile;
    bmpFile.open(
        filepath.c_str(), std::ios::out | std::ios::trunc | std::ios::binary
    );
    if (!bmpFile.is_open())
    {
        // Could not save BMP file
        return false;
    }

    // Write BMP file signature
    bmpFile.write((char*)BMPFileSignature, 2);
    if (!bmpFile)
    {
        // Could not write BMP file signature
        return false;
    }

    // Set BMP image format
    uint32_t fileSize = 0;
    uint32_t dataOffset = 0;
    uint32_t imageSize = 0;
    uint16_t bitsPerPixel = 0;
    switch (format)
    {
        case BMP_FILE_BGR_24BITS:
            // 24 bits uncompressed BMP file
            imageSize = (width*height*3);
            dataOffset = 2+BMPFileHeaderSize+BMPFileInfoSize;
            bitsPerPixel = 24;
            break;
        case BMP_FILE_BGR_16BITS:
            // 16 bits uncompressed BMP file
            imageSize = (width*height*2);
            dataOffset = 2+BMPFileHeaderSize+BMPFileInfoSize;
            bitsPerPixel = 16;
            break;
        default:
            // 24 bits uncompressed BMP file
            imageSize = (width*height*3);
            dataOffset = 2+BMPFileHeaderSize+BMPFileInfoSize;
            bitsPerPixel = 24;
            break;
    }
    fileSize = dataOffset+imageSize;

    // Write BMP file header
    BMPFileHeader bmpHeader;
    bmpHeader.fileSize = fileSize;
    bmpHeader.reserved = 0;
    bmpHeader.dataOffset = dataOffset;
    bmpFile.write((char*)&bmpHeader, BMPFileHeaderSize);
    if (!bmpFile)
    {
        // Could not write BMP file header
        return false;
    }

    // Read BMP file info
    BMPFileInfo bmpInfo;
    bmpInfo.infoSize = BMPFileInfoSize;
    bmpInfo.width = width;
    bmpInfo.height = height;
    bmpInfo.planes = 1;
    bmpInfo.bitsPerPixel = bitsPerPixel;
    bmpInfo.compression = 0;
    bmpInfo.imageSize = imageSize;
    bmpInfo.xResolution = BMPFileDefaultXResolution;
    bmpInfo.yResolution = BMPFileDefaultYResolution;
    bmpInfo.usedColors = 0;
    bmpInfo.importantColors = 0;
    bmpFile.write((char*)&bmpInfo, BMPFileInfoSize);
    if (!bmpFile)
    {
        // Could not write BMP file info
        return false;
    }

    // Save BMP image data
    switch (format)
    {
        case BMP_FILE_BGR_24BITS:
            // 24 bits uncompressed BMP file
            if (!saveBMP24Bits(bmpFile, imageSize, width, height, image))
            {
                return false;
            }
            break;
        case BMP_FILE_BGR_16BITS:
            // 16 bits uncompressed BMP file
            if (!saveBMP16Bits(bmpFile, imageSize, width, height, image))
            {
                return false;
            }
            break;
        default:
            // 24 bits uncompressed BMP file
            if (!saveBMP24Bits(bmpFile, imageSize, width, height, image))
            {
                return false;
            }
            break;
    }

    // Close BMP file
    bmpFile.close();

    // BMP image is successfully saved
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Load 24bits BMP file image data                                           //
//  return : True if BMP file image data is successfully loaded               //
////////////////////////////////////////////////////////////////////////////////
bool BMPFile::loadBMP24Bits(std::ifstream& bmpFile, uint32_t dataOffset,
    uint32_t width, uint32_t height)
{
    // Load BMP raw image data
    size_t rawDataSize = width*height*3;
    unsigned char* rawData = 0;
    try
    {
        // Allocate raw image data
        rawData = new unsigned char[rawDataSize];
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

    // Read BMP raw image data
    bmpFile.seekg(dataOffset);
    bmpFile.read((char*)rawData, rawDataSize);
    if (!bmpFile)
    {
        // Could not read BMP raw image data
        return false;
    }

    // Load BMP image data
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

    // Convert 24bits BMP image data
    for (uint32_t i = 0; i < width; ++i)
    {
        for (uint32_t j = 0; j < height; ++j)
        {
            size_t index = (j*width)+i;
            size_t rawIndex = ((height-j-1)*width)+i;

            m_image[(index*4)+0] = rawData[(rawIndex*3)+2]; // R component
            m_image[(index*4)+1] = rawData[(rawIndex*3)+1]; // G component
            m_image[(index*4)+2] = rawData[(rawIndex*3)+0]; // B component
            m_image[(index*4)+3] = 255;                     // A component
        }
    }

    // Destroy raw image data
    if (rawData)
    {
        delete[] rawData;
    }

    // BMP file image data is successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Save 24bits BMP file image data                                           //
//  return : True if BMP file image data is successfully saved                //
////////////////////////////////////////////////////////////////////////////////
bool BMPFile::saveBMP24Bits(std::ofstream& bmpFile, uint32_t imageSize,
    uint32_t width, uint32_t height, const unsigned char* image)
{
    // Check image data size
    size_t rawDataSize = width*height*3;
    if (imageSize != rawDataSize)
    {
        // Invalid image data size
        return false;
    }

    // Check image size
    if ((width <= 0) || (height <= 0) ||
        (width > BMPFileMaxImageWidth) ||
        (height > BMPFileMaxImageHeight))
    {
        // Invalid image size
        return false;
    }

    // Allocate raw image data
    unsigned char* rawData = 0;
    try
    {
        // Allocate raw image data
        rawData = new unsigned char[imageSize];
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

    // Convert 24bits BMP image data
    for (uint32_t i = 0; i < width; ++i)
    {
        for (uint32_t j = 0; j < height; ++j)
        {
            size_t index = (j*width)+i;
            size_t rawIndex = ((height-j-1)*width)+i;

            rawData[(rawIndex*3)+0] = image[(index*4)+2];   // B component
            rawData[(rawIndex*3)+1] = image[(index*4)+1];   // G component
            rawData[(rawIndex*3)+2] = image[(index*4)+0];   // R component
        }
    }

    // Write 24bits BMP image data
    bmpFile.write((char*)rawData, imageSize);
    if (!bmpFile)
    {
        // Could not write 24bits BMP image data
        return false;
    }

    // Destroy raw image data
    if (rawData)
    {
        delete[] rawData;
    }

    // BMP file image data is successfully saved
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Load 16bits BMP file image data                                           //
//  return : True if BMP file image data is successfully loaded               //
////////////////////////////////////////////////////////////////////////////////
bool BMPFile::loadBMP16Bits(std::ifstream& bmpFile, uint32_t dataOffset,
    uint32_t width, uint32_t height)
{
    // Load BMP raw image data
    size_t rawDataSize = width*height*2;
    unsigned char* rawData = 0;
    try
    {
        // Allocate raw image data
        rawData = new unsigned char[rawDataSize];
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

    // Read BMP raw image data
    bmpFile.seekg(dataOffset);
    bmpFile.read((char*)rawData, rawDataSize);
    if (!bmpFile)
    {
        // Could not read BMP raw image data
        return false;
    }

    // Load BMP image data
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

    // Convert 16bits BMP image data
    for (uint32_t i = 0; i < width; ++i)
    {
        for (uint32_t j = 0; j < height; ++j)
        {
            size_t index = (j*width)+i;
            size_t rawIndex = ((height-j-1)*width)+i;
            uint16_t rawPixel =
                (rawData[(rawIndex*2)+1] << 8) + rawData[(rawIndex*2)];

            m_image[(index*4)+0] = static_cast<unsigned char>(  // R component
                ((rawPixel&0x7C00) >> 10) * 8
            );
            m_image[(index*4)+1] = static_cast<unsigned char>(  // G component
                ((rawPixel&0x03E0) >> 5) * 8
            );
            m_image[(index*4)+2] = static_cast<unsigned char>(  // B component
                ((rawPixel&0x001F)) * 8
            );
            m_image[(index*4)+3] = 255;                         // A component
        }
    }

    // Destroy raw image data
    if (rawData)
    {
        delete[] rawData;
    }

    // BMP file image data is successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Save 16bits BMP file image data                                           //
//  return : True if BMP file image data is successfully saved                //
////////////////////////////////////////////////////////////////////////////////
bool BMPFile::saveBMP16Bits(std::ofstream& bmpFile, uint32_t imageSize,
    uint32_t width, uint32_t height, const unsigned char* image)
{
    // Check image data size
    size_t rawDataSize = width*height*2;
    if (imageSize != rawDataSize)
    {
        // Invalid image data size
        return false;
    }

    // Check image size
    if ((width <= 0) || (height <= 0) ||
        (width > BMPFileMaxImageWidth) ||
        (height > BMPFileMaxImageHeight))
    {
        // Invalid image size
        return false;
    }

    // Allocate raw image data
    uint16_t* rawData = 0;
    try
    {
        // Allocate raw image data
        rawData = new uint16_t[imageSize/2];
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

    // Convert 16bits BMP image data
    for (uint32_t i = 0; i < width; ++i)
    {
        for (uint32_t j = 0; j < height; ++j)
        {
            size_t index = (j*width)+i;
            size_t rawIndex = ((height-j-1)*width)+i;
            rawData[rawIndex] =
                (image[(index*4)+2]/8) |            // B component
                ((image[(index*4)+1]/8) << 5) |     // G component
                ((image[(index*4)+0]/8) << 10);     // R component
        }
    }

    // Write 16bits BMP image data
    bmpFile.write((char*)rawData, imageSize);
    if (!bmpFile)
    {
        // Could not write 16bits BMP image data
        return false;
    }

    // Destroy raw image data
    if (rawData)
    {
        delete[] rawData;
    }

    // BMP file image data is successfully saved
    return true;
}
