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
//     Resources/Resources.cpp : Resources management                         //
////////////////////////////////////////////////////////////////////////////////
#include "Resources.h"


////////////////////////////////////////////////////////////////////////////////
//  Resources default constructor                                             //
////////////////////////////////////////////////////////////////////////////////
Resources::Resources(Renderer& renderer) :
textures(renderer),
meshes(),
heightmaps()
{

}

////////////////////////////////////////////////////////////////////////////////
//  Resources destructor                                                      //
////////////////////////////////////////////////////////////////////////////////
Resources::~Resources()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Init resources loaders                                                    //
//  return : True if resources loaders are ready                              //
////////////////////////////////////////////////////////////////////////////////
bool Resources::init()
{
    // Start texture loader thread
    textures.start();

    // Start mesh loader thread
    meshes.start();

    // Start heightmap loader thread
    heightmaps.start();

    // Resources loaders are ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy resources                                                         //
////////////////////////////////////////////////////////////////////////////////
void Resources::destroyResources()
{
    // Stop heightmap loader thread
    heightmaps.stop();

    // Stop mesh loader thread
    meshes.stop();

    // Stop texture loader thread
    textures.stop();

    // Destroy heightmap loader
    heightmaps.destroyHeightMapLoader();

    // Destroy mesh loader
    meshes.destroyMeshLoader();

    // Destroy texture loader
    textures.destroyTextureLoader();
}
