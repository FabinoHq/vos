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
//     Resources/Resources.h : Resources management                           //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RESOURCES_RESOURCES_HEADER
#define VOS_RESOURCES_RESOURCES_HEADER

    #include "../System/System.h"
    #include "../System/SysMessage.h"
    #include "TextureLoader.h"
    #include "MeshLoader.h"
    #include "MatrixColLoader.h"
    #include "TileMapLoader.h"
    #include "IsoMapLoader.h"
    #include "HeightMapLoader.h"
    #include "HeightFarLoader.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Resources settings                                                    //
    ////////////////////////////////////////////////////////////////////////////
    const double ResourcesWaitSleepTime = 0.02;


    ////////////////////////////////////////////////////////////////////////////
    //  Resources class definition                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Resources
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Resources default constructor                                 //
            ////////////////////////////////////////////////////////////////////
            Resources();

            ////////////////////////////////////////////////////////////////////
            //  Resources destructor                                          //
            ////////////////////////////////////////////////////////////////////
            ~Resources();


            ////////////////////////////////////////////////////////////////////
            //  Init resources loaders                                        //
            //  return : True if resources loaders are ready                  //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Preload resources assets                                      //
            //  return : True if resources assets are successfully preloaded  //
            ////////////////////////////////////////////////////////////////////
            bool preload();

            ////////////////////////////////////////////////////////////////////
            //  Start loading resources assets                                //
            //  return : True if resources assets are loading                 //
            ////////////////////////////////////////////////////////////////////
            bool startLoading();

            ////////////////////////////////////////////////////////////////////
            //  Get resources loading status                                  //
            //  return : True if resources assets are loaded, false otherwise //
            ////////////////////////////////////////////////////////////////////
            bool isLoadingDone();

            ////////////////////////////////////////////////////////////////////
            //  Destroy resources                                             //
            ////////////////////////////////////////////////////////////////////
            void destroyResources();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Resources private copy constructor : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            Resources(const Resources&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Resources private copy operator : Not copyable                //
            ////////////////////////////////////////////////////////////////////
            Resources& operator=(const Resources&) = delete;


        public:
            TextureLoader       textures;       // Texture loader
            MeshLoader          meshes;         // Mesh loader
            MatrixColLoader     matrixcols;     // MatrixCol loader
            TileMapLoader       tilemaps;       // TileMap loader
            IsoMapLoader        isomaps;        // IsoMap loader
            HeightMapLoader     heightmaps;     // HeightMap loader
            HeightFarLoader     heightfars;     // HeightFar loader
    };


    ////////////////////////////////////////////////////////////////////////////
    //  Resources global instance                                             //
    ////////////////////////////////////////////////////////////////////////////
    extern Resources GResources;


#endif // VOS_RESOURCES_RESOURCES_HEADER
