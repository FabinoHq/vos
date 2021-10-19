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
//     Renderer/Images/BMPFile.h : BMPFile image management                   //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_IMAGES_BMPFILE_HEADER
#define VOS_RENDERER_IMAGES_BMPFILE_HEADER

    #include "../Texture.h"

    #include <string>
    #include <fstream>

    
    ////////////////////////////////////////////////////////////////////////////
    //  BMPFile image settings                                                //
    ////////////////////////////////////////////////////////////////////////////
    const uint32_t BMPFileMaxImageWidth = 4096;
    const uint32_t BMPFileMaxImageHeight = 4096;


    ////////////////////////////////////////////////////////////////////////////
    //  BMPFile header structure                                              //
    ////////////////////////////////////////////////////////////////////////////
    struct BMPFileHeader
    {
        uint32_t    fileSize;
        uint32_t    reserved;
        uint32_t    dataOffset;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  BMPFile info structure                                                //
    ////////////////////////////////////////////////////////////////////////////
    struct BMPFileInfo
    {
        uint32_t    infoSize;
        uint32_t    width;
        uint32_t    height;
        uint16_t    planes;
        uint16_t    bitsPerPixel;
        uint32_t    compression;
        uint32_t    imageSize;
        uint32_t    xResolution;
        uint32_t    yResolution;
        uint32_t    usedColors;
        uint32_t    importantColors;
    };


    ////////////////////////////////////////////////////////////////////////////
    //  BMPFile class definition                                              //
    ////////////////////////////////////////////////////////////////////////////
    class BMPFile
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  BMPFile default constructor                                   //
            ////////////////////////////////////////////////////////////////////
            BMPFile();

            ////////////////////////////////////////////////////////////////////
            //  BMPFile destructor                                            //
            ////////////////////////////////////////////////////////////////////
            ~BMPFile();


            ////////////////////////////////////////////////////////////////////
            //  Load BMP file                                                 //
            //  return : True if BMP file is successfully loaded              //
            ////////////////////////////////////////////////////////////////////
            bool loadImage(const std::string& filepath);

            ////////////////////////////////////////////////////////////////////
            //  Save BMP file                                                 //
            //  return : True if BMP file is successfully saved               //
            ////////////////////////////////////////////////////////////////////
            bool saveImage(const std::string& filepath);

            ////////////////////////////////////////////////////////////////////
            //  Destroy BMP image                                             //
            ////////////////////////////////////////////////////////////////////
            void destroyImage();


            ////////////////////////////////////////////////////////////////////
            //  Get BMP file loaded state                                     //
            //  return : True if BMP file is loaded                           //
            ////////////////////////////////////////////////////////////////////
            bool isLoaded();

            ////////////////////////////////////////////////////////////////////
            //  Get BMP file image data                                       //
            //  return : BMP file image data                                  //
            ////////////////////////////////////////////////////////////////////
            unsigned char* getData();

            ////////////////////////////////////////////////////////////////////
            //  Get BMP file image format                                     //
            //  return : BMP file image format                                //
            ////////////////////////////////////////////////////////////////////
            TextureFormat getFormat();

            ////////////////////////////////////////////////////////////////////
            //  Get BMP file image width                                      //
            //  return : BMP file image width in pixels                       //
            ////////////////////////////////////////////////////////////////////
            uint32_t getWidth();

            ////////////////////////////////////////////////////////////////////
            //  Get BMP file image height                                     //
            //  return : BMP file image height in pixels                      //
            ////////////////////////////////////////////////////////////////////
            uint32_t getHeight();


        private:
            ////////////////////////////////////////////////////////////////////
            //  BMPFile private copy constructor : Not copyable               //
            ////////////////////////////////////////////////////////////////////
            BMPFile(const BMPFile&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  BMPFile private copy operator : Not copyable                  //
            ////////////////////////////////////////////////////////////////////
            BMPFile& operator=(const BMPFile&) = delete;


            ////////////////////////////////////////////////////////////////////
            //  Set BMP file image settings from BMPFileInfo                  //
            //  return : True if BMP file image settings are successfully set //
            ////////////////////////////////////////////////////////////////////
            bool setBMPImageSettings(BMPFileInfo& bmpInfo);


        private:
            bool                m_loaded;       // Image loaded state
            unsigned char*      m_image;        // Image data
            TextureFormat       m_format;       // Image format
            uint32_t            m_width;        // Image width
            uint32_t            m_height;       // Image height
    };


#endif // VOS_RENDERER_IMAGES_BMPFILE_HEADER
