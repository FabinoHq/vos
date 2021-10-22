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
//     Images/BMPFile.h : BMPFile image management                            //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_IMAGES_BMPFILE_HEADER
#define VOS_IMAGES_BMPFILE_HEADER

    #include <exception>
    #include <cstdint>
    #include <cstring>
    #include <string>
    #include <fstream>


    ////////////////////////////////////////////////////////////////////////////
    //  BMPFile image settings                                                //
    ////////////////////////////////////////////////////////////////////////////
    const unsigned char BMPFileSignature[2] = {0x42, 0x4D};
    const uint32_t BMPFileMaxImageWidth = 4096;
    const uint32_t BMPFileMaxImageHeight = 4096;
    const uint32_t BMPFileDefaultXResolution = 2835;
    const uint32_t BMPFileDefaultYResolution = 2835;

    ////////////////////////////////////////////////////////////////////////////
    //  BMPFile image format                                                  //
    ////////////////////////////////////////////////////////////////////////////
    enum BMPFileImageFormat
    {
        BMP_FILE_BGR_24BITS,
        BMP_FILE_BGR_16BITS
    };


    ////////////////////////////////////////////////////////////////////////////
    //  BMPFile header structure                                              //
    ////////////////////////////////////////////////////////////////////////////
    struct BMPFileHeader
    {
        uint32_t    fileSize;
        uint32_t    reserved;
        uint32_t    dataOffset;
    };
    const size_t BMPFileHeaderSize = 12;

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
    const size_t BMPFileInfoSize = 40;


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
            //  Set BMP file image                                            //
            //  return : True if BMP file image is successfully set           //
            ////////////////////////////////////////////////////////////////////
            bool setImage(uint32_t width, uint32_t height,
                const unsigned char* image);

            ////////////////////////////////////////////////////////////////////
            //  Load BMP file                                                 //
            //  return : True if BMP file is successfully loaded              //
            ////////////////////////////////////////////////////////////////////
            bool loadImage(const std::string& filepath);

            ////////////////////////////////////////////////////////////////////
            //  Save BMP file                                                 //
            //  return : True if BMP file is successfully saved               //
            ////////////////////////////////////////////////////////////////////
            bool saveImage(const std::string& filepath,
                BMPFileImageFormat format = BMP_FILE_BGR_24BITS);

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
            unsigned char* getImage();

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


            ////////////////////////////////////////////////////////////////////
            //  Save BMP image                                                //
            //  return : True if BMP image is successfully saved              //
            ////////////////////////////////////////////////////////////////////
            static bool saveBMPImage(const std::string& filepath,
                uint32_t width, uint32_t height, const unsigned char* image,
                BMPFileImageFormat format = BMP_FILE_BGR_24BITS);


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
            //  Load 24bits BMP file image data                               //
            //  return : True if BMP file image data is successfully loaded   //
            ////////////////////////////////////////////////////////////////////
            bool loadBMP24Bits(std::ifstream& bmpFile, uint32_t dataOffset,
                uint32_t width, uint32_t height);

            ////////////////////////////////////////////////////////////////////
            //  Save 24bits BMP file image data                               //
            //  return : True if BMP file image data is successfully saved    //
            ////////////////////////////////////////////////////////////////////
            static bool saveBMP24Bits(std::ofstream& bmpFile,
                uint32_t imageSize, uint32_t width, uint32_t height,
                const unsigned char* image);

            ////////////////////////////////////////////////////////////////////
            //  Load 16bits BMP file image data                               //
            //  return : True if BMP file image data is successfully loaded   //
            ////////////////////////////////////////////////////////////////////
            bool loadBMP16Bits(std::ifstream& bmpFile, uint32_t dataOffset,
                uint32_t width, uint32_t height);

            ////////////////////////////////////////////////////////////////////
            //  Save 16bits BMP file image data                               //
            //  return : True if BMP file image data is successfully saved    //
            ////////////////////////////////////////////////////////////////////
            static bool saveBMP16Bits(std::ofstream& bmpFile,
                uint32_t imageSize, uint32_t width, uint32_t height,
                const unsigned char* image);


        private:
            bool                m_loaded;       // Image loaded state
            unsigned char*      m_image;        // Image data
            uint32_t            m_width;        // Image width
            uint32_t            m_height;       // Image height
    };


#endif // VOS_IMAGES_BMPFILE_HEADER
