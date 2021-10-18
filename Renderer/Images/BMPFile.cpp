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
//     Renderer/Images/BMPFile.cpp : BMPFile image management                 //
////////////////////////////////////////////////////////////////////////////////
#include "BMPFile.h"


////////////////////////////////////////////////////////////////////////////////
//  BMPFile default constructor                                               //
////////////////////////////////////////////////////////////////////////////////
BMPFile::BMPFile() :
m_loaded(false),
m_image(0),
m_width(0),
m_height(0),
m_depth(0)
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
    m_depth = 0;
    m_height = 0;
    m_width = 0;
    m_image = 0;
    m_loaded = false;
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
    std::ifstream bmpfile;
    bmpfile.open(filepath.c_str(), std::ios::in | std::ios::binary);
    if (!bmpfile.is_open())
    {
        // Could not load BMP file
        m_loaded = false;
        return false;
    }

    // BMP file is successfully loaded
    m_loaded = true;
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Save BMP file                                                             //
//  return : True if BMP file is successfully saved                           //
////////////////////////////////////////////////////////////////////////////////
bool BMPFile::saveImage(const std::string& filepath)
{
    // Check image loaded state
    if (!m_loaded)
    {
        // No current image to save
        return false;
    }

    // Save BMP file
    std::ofstream bmpfile;
    bmpfile.open(
        filepath.c_str(), std::ios::out | std::ios::trunc | std::ios::binary
    );
    if (!bmpfile.is_open())
    {
        // Could not save BMP file
        m_loaded = false;
        return false;
    }

    // BMP file is successfully saved
    m_loaded = true;
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
    m_depth = 0;
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
unsigned char* BMPFile::getData()
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
//  Get BMP file image depth                                                  //
//  return : BMP file image depth in bits per pixels                          //
////////////////////////////////////////////////////////////////////////////////
uint32_t BMPFile::getDepth()
{
    return m_depth;
}
