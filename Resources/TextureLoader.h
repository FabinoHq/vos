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
    #include "../Renderer/Vulkan/VulkanMemory.h"
    #include "../Renderer/Vulkan/VulkanQueue.h"
    #include "../Renderer/Vulkan/VulkanBuffer.h"
    #include "../Renderer/Vulkan/Texture.h"
    #include "../Renderer/Vulkan/CubeMap.h"

    #include "../Images/BMPFile.h"
    #include "../Images/PNGFile.h"

    #include <cstdint>
    #include <new>


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
    //  TextureLoader settings                                                //
    ////////////////////////////////////////////////////////////////////////////
    const uint32_t TextureMaxWidth = 4096;
    const uint32_t TextureMaxHeight = 4096;
    const uint32_t CubeMapMaxWidth = 2048;
    const uint32_t CubeMapMaxHeight = 2048;
    const uint32_t TextureMaxSize = (TextureMaxWidth*TextureMaxHeight*4);
    const uint32_t CubeMapMaxSize = (CubeMapMaxWidth*CubeMapMaxHeight*4*6);
    const uint64_t TextureFenceTimeout = 100000000000;
    const double TextureLoaderIdleSleepTime = 0.01;
    const double TextureLoaderErrorSleepTime = 0.1;


    ////////////////////////////////////////////////////////////////////////////
    //  TexturesGUI enumeration                                               //
    ////////////////////////////////////////////////////////////////////////////
    enum TexturesGUI
    {
        TEXTURE_CURSOR = 0,
        TEXTURE_NSCURSOR = 1,
        TEXTURE_EWCURSOR = 2,
        TEXTURE_NESWCURSOR = 3,
        TEXTURE_NWSECURSOR = 4,
        TEXTURE_WINDOW = 5,
        TEXTURE_PIXELFONT = 6,

        TEXTURE_GUICOUNT = 7
    };

    ////////////////////////////////////////////////////////////////////////////
    //  TexturesAssets enumeration                                            //
    ////////////////////////////////////////////////////////////////////////////
    enum TexturesAssets
    {
        TEXTURE_TEST = 0,

        TEXTURE_ASSETSCOUNT = 1
    };

    ////////////////////////////////////////////////////////////////////////////
    //  TexturesCubeMaps enumeration                                          //
    ////////////////////////////////////////////////////////////////////////////
    enum TexturesCubeMaps
    {
        TEXTURE_CUBEMAPTEST = 0,

        TEXTURE_CUBEMAPCOUNT = 1
    };


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
            //  Get GUI texture                                               //
            //  return : GUI texture                                          //
            ////////////////////////////////////////////////////////////////////
            inline Texture& gui(TexturesGUI texture)
            {
                return m_texturesGUI[texture];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get high texture                                              //
            //  return : high texture                                         //
            ////////////////////////////////////////////////////////////////////
            inline Texture& high(TexturesAssets texture)
            {
                return m_texturesHigh[texture];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get CubeMap texture                                           //
            //  return : CubeMap texture                                      //
            ////////////////////////////////////////////////////////////////////
            inline CubeMap& cubemap(TexturesCubeMaps cubemap)
            {
                return m_cubemaps[cubemap];
            }

            ////////////////////////////////////////////////////////////////////
            //  Destroy texture loader                                        //
            ////////////////////////////////////////////////////////////////////
            void destroyTextureLoader();


            ////////////////////////////////////////////////////////////////////
            //  Upload texture to graphics memory                             //
            //  return : True if texture is successfully uploaded             //
            ////////////////////////////////////////////////////////////////////
            bool uploadTexture(VkImage& handle,
                uint32_t width, uint32_t height, const unsigned char* data);

            ////////////////////////////////////////////////////////////////////
            //  Upload cubemap to graphics memory                             //
            //  return : True if cubemap is successfully uploaded             //
            ////////////////////////////////////////////////////////////////////
            bool uploadCubeMap(VkImage& handle,
                uint32_t width, uint32_t height, const unsigned char* data);


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

            VulkanQueue             m_graphicsQueue;    // Graphics queue
            VkCommandPool           m_commandPool;      // Command pool
            VkCommandBuffer         m_commandBuffer;    // Command buffer
            VulkanBuffer            m_stagingBuffer;    // Staging buffer
            VkFence                 m_fence;            // Staging fence

            Texture*                m_texturesGUI;      // GUI textures
            Texture*                m_texturesHigh;     // High textures
            CubeMap*                m_cubemaps;         // CubeMaps textures
    };


#endif // VOS_RESOURCES_TEXTURELOADER_HEADER
