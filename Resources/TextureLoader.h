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
//     Resources/TextureLoader.h : Texture loading management                 //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RESOURCES_TEXTURELOADER_HEADER
#define VOS_RESOURCES_TEXTURELOADER_HEADER

    #include "../System/System.h"
    #include "../System/SysThread.h"
    #include "../System/SysMutex.h"
    #include "../Renderer/Vulkan/Vulkan.h"
    #include "../Renderer/Vulkan/VulkanBuffer.h"
    #include "../Renderer/Texture.h"

    #include "../Images/BMPFile.h"
    #include "../Images/PNGFile.h"

    #include <cstdint>
    #include <new>


    ////////////////////////////////////////////////////////////////////////////
    //  TexturesAssets enumeration                                            //
    ////////////////////////////////////////////////////////////////////////////
    enum TexturesAssets
    {
        TEXTURE_DEFAULT = 0,
        TEXTURE_CURSOR = 1,
        TEXTURE_NSCURSOR = 2,
        TEXTURE_EWCURSOR = 3,
        TEXTURE_NESWCURSOR = 4,
        TEXTURE_NWSECURSOR = 5,
        TEXTURE_WINDOW = 6,
        TEXTURE_PIXELFONT = 7,

        TEXTURE_TEST = 8,

        TEXTURE_ASSETSCOUNT = 9
    };


    ////////////////////////////////////////////////////////////////////////////
    //  TextureLoader settings                                                //
    ////////////////////////////////////////////////////////////////////////////
    const uint32_t TextureMaxWidth = 2048;
    const uint32_t TextureMaxHeight = 2048;
    const uint32_t TextureMaxSize = (TextureMaxWidth*TextureMaxHeight*4);
    const uint64_t TextureFenceTimeout = 100000000000;
    const double TextureLoaderIdleSleepTime = 0.01;
    const double TextureLoaderErrorSleepTime = 0.1;


    ////////////////////////////////////////////////////////////////////////////
    //  Embedded textures                                                     //
    ////////////////////////////////////////////////////////////////////////////
    #include "../Images/Embedded/Cursor.h"
    #include "../Images/Embedded/NSCursor.h"
    #include "../Images/Embedded/EWCursor.h"
    #include "../Images/Embedded/NESWCursor.h"
    #include "../Images/Embedded/NWSECursor.h"
    #include "../Images/Embedded/PxFont.h"
    #include "../Images/Embedded/Window.h"


    ////////////////////////////////////////////////////////////////////////////
    //  TextureLoaderState enumeration                                        //
    ////////////////////////////////////////////////////////////////////////////
    enum TextureLoaderState
    {
        TEXTURELOADER_STATE_NONE = 0,
        TEXTURELOADER_STATE_INIT = 1,
        TEXTURELOADER_STATE_LOADEMBEDDED = 2,

        TEXTURELOADER_STATE_IDLE = 3,
        TEXTURELOADER_STATE_PRELOAD = 4,
        TEXTURELOADER_STATE_LOAD = 5,

        TEXTURELOADER_STATE_ERROR = 6
    };


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class declaration                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer;


    ////////////////////////////////////////////////////////////////////////////
    //  TextureLoader class definition                                        //
    ////////////////////////////////////////////////////////////////////////////
    class TextureLoader : public SysThread
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  TextureLoader default constructor                             //
            ////////////////////////////////////////////////////////////////////
            TextureLoader(Renderer& renderer);

            ////////////////////////////////////////////////////////////////////
            //  TextureLoader virtual destructor                              //
            ////////////////////////////////////////////////////////////////////
            virtual ~TextureLoader();


            ////////////////////////////////////////////////////////////////////
            //  TextureLoader thread process                                  //
            ////////////////////////////////////////////////////////////////////
            virtual void process();


            ////////////////////////////////////////////////////////////////////
            //  Init TextureLoader                                            //
            //  return : True if texture loader is ready                      //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Start preloading textures assets                              //
            //  return : True if textures assets are preloading               //
            ////////////////////////////////////////////////////////////////////
            bool startPreload();

            ////////////////////////////////////////////////////////////////////
            //  Start loading textures assets                                 //
            //  return : True if textures assets are loading                  //
            ////////////////////////////////////////////////////////////////////
            bool startLoading();

            ////////////////////////////////////////////////////////////////////
            //  Get texture loader state                                      //
            //  return : Current texture loader state                         //
            ////////////////////////////////////////////////////////////////////
            TextureLoaderState getState();

            ////////////////////////////////////////////////////////////////////
            //  Get texture                                                   //
            //  return : Texture asset                                        //
            ////////////////////////////////////////////////////////////////////
            inline Texture& get(TexturesAssets texture)
            {
                return m_textures[texture];
            }

            ////////////////////////////////////////////////////////////////////
            //  Destroy texture loader                                        //
            ////////////////////////////////////////////////////////////////////
            void destroyTextureLoader();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Load embedded textures                                        //
            //  return : True if embedded textures are successfully loaded    //
            ////////////////////////////////////////////////////////////////////
            bool loadEmbeddedTextures();

            ////////////////////////////////////////////////////////////////////
            //  Preload textures assets                                       //
            //  return : True if textures assets are preloaded                //
            ////////////////////////////////////////////////////////////////////
            bool preloadTextures();

            ////////////////////////////////////////////////////////////////////
            //  Load textures assets                                          //
            //  return : True if textures assets are loaded                   //
            ////////////////////////////////////////////////////////////////////
            bool loadTextures();


        private:
            ////////////////////////////////////////////////////////////////////
            //  TextureLoader private copy constructor : Not copyable         //
            ////////////////////////////////////////////////////////////////////
            TextureLoader(const TextureLoader&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  TextureLoader private copy operator : Not copyable            //
            ////////////////////////////////////////////////////////////////////
            TextureLoader& operator=(const TextureLoader&) = delete;


        private:
            Renderer&               m_renderer;         // Renderer
            TextureLoaderState      m_state;            // TextureLoader state
            SysMutex                m_stateMutex;       // State mutex
            VulkanBuffer            m_stagingBuffer;    // Stagging buffer

            Texture*                m_textures;         // Textures assets
    };


#endif // VOS_RESOURCES_TEXTURELOADER_HEADER
