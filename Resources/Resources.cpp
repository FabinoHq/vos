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
#include "../Renderer/Renderer.h"


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

    // Wait for resources init
    bool resourcesReady = false;
    while (!resourcesReady)
    {
        // Get resources loader states
        TextureLoaderState textureState = textures.getState();
        if (textureState == TEXTURELOADER_STATE_ERROR)
        {
            // Texture loader error
            SysMessage::box() << "[0x4000] Could not init textures loader\n";
            SysMessage::box() << "Please check your resources files";
            return false;
        }

        if (textureState == TEXTURELOADER_STATE_IDLE)
        {
            // Resources are ready
            resourcesReady = true;
        }
        else
        {
            // Release some CPU while loading
            SysSleep(ResourcesWaitSleepTime);
        }
    }

    // Resources loaders are ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Start loading resources assets                                            //
//  return : True if resources assets are loading                             //
////////////////////////////////////////////////////////////////////////////////
bool Resources::startLoading()
{
    // Start textures assets loading
    if (!textures.startLoading())
    {
        // Could not start textures loading
        SysMessage::box() << "[0x4001] Could not start textures loader\n";
        SysMessage::box() << "Please check your resources files";
        return false;
    }

    // Resources assets are loading
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Get resources loading status                                              //
//  return : True if resources assets are loaded, false otherwise             //
////////////////////////////////////////////////////////////////////////////////
bool Resources::isLoadingDone()
{
    // Get resources loader states
    TextureLoaderState textureState = textures.getState();
    if (textureState == TEXTURELOADER_STATE_IDLE)
    {
        // Resources assets are loaded
        return true;
    }

    // Resources assets are still loading, or an error occured
    return false;
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
