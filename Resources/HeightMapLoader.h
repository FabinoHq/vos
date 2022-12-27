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
//     Resources/HeightMapLoader.h : HeightMap loading management             //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RESOURCES_HEIGHTMAPLOADER_HEADER
#define VOS_RESOURCES_HEIGHTMAPLOADER_HEADER

    #include "../System/System.h"
    #include "../System/SysThread.h"
    #include "../System/SysMutex.h"


    ////////////////////////////////////////////////////////////////////////////
    //  HeightMapLoader settings                                              //
    ////////////////////////////////////////////////////////////////////////////
    const uint64_t HeightMapFenceTimeout = 100000000000;
    const double HeightMapLoaderIdleSleepTime = 0.01;
    const double HeightMapLoaderErrorSleepTime = 0.1;


    ////////////////////////////////////////////////////////////////////////////
    //  HeightMapLoaderState enumeration                                      //
    ////////////////////////////////////////////////////////////////////////////
    enum HeightMapLoaderState
    {
        HEIGHTMAPLOADER_STATE_NONE = 0,
        HEIGHTMAPLOADER_STATE_INIT = 1,

        HEIGHTMAPLOADER_STATE_IDLE = 2,
        HEIGHTMAPLOADER_STATE_LOAD = 3,

        HEIGHTMAPLOADER_STATE_ERROR = 4
    };


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class declaration                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer;


    ////////////////////////////////////////////////////////////////////////////
    //  HeightMapLoader class definition                                      //
    ////////////////////////////////////////////////////////////////////////////
    class HeightMapLoader : public SysThread
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  HeightMapLoader default constructor                           //
            ////////////////////////////////////////////////////////////////////
            HeightMapLoader(Renderer& renderer);

            ////////////////////////////////////////////////////////////////////
            //  HeightMapLoader virtual destructor                            //
            ////////////////////////////////////////////////////////////////////
            virtual ~HeightMapLoader();


            ////////////////////////////////////////////////////////////////////
            //  HeightMapLoader thread process                                //
            ////////////////////////////////////////////////////////////////////
            virtual void process();


            ////////////////////////////////////////////////////////////////////
            //  Init HeightMapLoader                                          //
            //  return : True if heightmap loader is ready                    //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Get heightmap loader state                                    //
            //  return : Current heightmap loader state                       //
            ////////////////////////////////////////////////////////////////////
            HeightMapLoaderState getState();

            ////////////////////////////////////////////////////////////////////
            //  Destroy heightmap loader                                      //
            ////////////////////////////////////////////////////////////////////
            void destroyHeightMapLoader();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Load heightmaps assets                                        //
            //  return : True if heightmaps assets are loaded                 //
            ////////////////////////////////////////////////////////////////////
            bool loadHeightMaps();


        private:
            ////////////////////////////////////////////////////////////////////
            //  HeightMapLoader private copy constructor : Not copyable       //
            ////////////////////////////////////////////////////////////////////
            HeightMapLoader(const HeightMapLoader&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  HeightMapLoader private copy operator : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            HeightMapLoader& operator=(const HeightMapLoader&) = delete;


        private:
            Renderer&               m_renderer;         // Renderer
            HeightMapLoaderState    m_state;            // HeightMapLoader state
            SysMutex                m_stateMutex;       // State mutex
    };


#endif // VOS_RESOURCES_HEIGHTMAPLOADER_HEADER
