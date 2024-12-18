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
//  Resources global instance                                                 //
////////////////////////////////////////////////////////////////////////////////
Resources GResources = Resources();


////////////////////////////////////////////////////////////////////////////////
//  Resources default constructor                                             //
////////////////////////////////////////////////////////////////////////////////
Resources::Resources() :
textures(),
meshes(),
matrixcols(),
tilemaps(),
isomaps(),
heightmaps(),
heightfars()
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

    // Start matrixcol loader thread
    matrixcols.start();

    // Start tilemap loader thread
    tilemaps.start();

    // Start isomap loader thread
    isomaps.start();

    // Start heightmap loader thread
    heightmaps.start();

    // Start heightfar loader thread
    heightfars.start();

    // Wait for resources init
    bool resourcesReady = false;
    while (!resourcesReady)
    {
        // Get resources loader states
        TextureLoaderState textureState = textures.getState();
        MeshLoaderState meshState = meshes.getState();
        MatrixColLoaderState matrixcolState = matrixcols.getState();
        TileMapLoaderState tilemapState = tilemaps.getState();
        IsoMapLoaderState isomapState = isomaps.getState();
        HeightMapLoaderState heightmapState = heightmaps.getState();
        HeightFarLoaderState heightfarState = heightfars.getState();

        // Check texture loader state
        if (textureState == TEXTURELOADER_STATE_ERROR)
        {
            // Texture loader error
            SysMessage::box() << "[0x4000] Could not init textures loader\n";
            SysMessage::box() << "Please check your resources files";
            return false;
        }

        // Check mesh loader state
        if (meshState == MESHLOADER_STATE_ERROR)
        {
            // Mesh loader error
            SysMessage::box() << "[0x4001] Could not init meshes loader\n";
            SysMessage::box() << "Please check your resources files";
            return false;
        }

        // Check matrixcols loader state
        if (matrixcolState == MATRIXCOLLOADER_STATE_ERROR)
        {
            // Mesh loader error
            SysMessage::box() << "[0x4002] Could not init matrixcols loader\n";
            SysMessage::box() << "Please check your resources files";
            return false;
        }

        // Check tilemaps loader state
        if (tilemapState == TILEMAPLOADER_STATE_ERROR)
        {
            // Mesh loader error
            SysMessage::box() << "[0x4003] Could not init tilemaps loader\n";
            SysMessage::box() << "Please check your resources files";
            return false;
        }

        // Check isomaps loader state
        if (isomapState == ISOMAPLOADER_STATE_ERROR)
        {
            // Mesh loader error
            SysMessage::box() << "[0x4004] Could not init isomaps loader\n";
            SysMessage::box() << "Please check your resources files";
            return false;
        }

        // Check heightmaps loader state
        if (heightmapState == HEIGHTMAPLOADER_STATE_ERROR)
        {
            // Mesh loader error
            SysMessage::box() << "[0x4005] Could not init heightmaps loader\n";
            SysMessage::box() << "Please check your resources files";
            return false;
        }

        // Check heightfars loader state
        if (heightfarState == HEIGHTFARLOADER_STATE_ERROR)
        {
            // Mesh loader error
            SysMessage::box() << "[0x4006] Could not init heightfars loader\n";
            SysMessage::box() << "Please check your resources files";
            return false;
        }

        // Check resources init state
        if ((textureState == TEXTURELOADER_STATE_IDLE) &&
            (meshState == MESHLOADER_STATE_IDLE) &&
            (heightmapState == HEIGHTMAPLOADER_STATE_IDLE) &&
            (heightfarState == HEIGHTFARLOADER_STATE_IDLE))
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
//  Preload resources assets                                                  //
//  return : True if resources assets are successfully preloaded              //
////////////////////////////////////////////////////////////////////////////////
bool Resources::preload()
{
    // Start texture preloading
    textures.startPreload();

    // Start meshes preloading
    meshes.startPreload();

    // Wait for resources preload
    bool resourcesPreloaded = false;
    while (!resourcesPreloaded)
    {
        // Get resources loader states
        TextureLoaderState textureState = textures.getState();
        MeshLoaderState meshState = meshes.getState();

        // Check texture loader state
        if (textureState == TEXTURELOADER_STATE_ERROR)
        {
            // Texture loader error
            SysMessage::box() << "[0x4007] Could not preload textures\n";
            SysMessage::box() << "Please check your resources files";
            return false;
        }

        // Check mesh loader state
        if (meshState == MESHLOADER_STATE_ERROR)
        {
            // Texture loader error
            SysMessage::box() << "[0x4008] Could not preload meshes\n";
            SysMessage::box() << "Please check your resources files";
            return false;
        }

        // Check resources preload state
        if ((textureState == TEXTURELOADER_STATE_IDLE) &&
            (meshState == MESHLOADER_STATE_IDLE))
        {
            // Resources are preloaded
            resourcesPreloaded = true;
        }
        else
        {
            // Release some CPU while loading
            SysSleep(ResourcesWaitSleepTime);
        }
    }

    // Resources assets are successfully preloaded
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
        SysMessage::box() << "[0x4009] Could not start textures loader\n";
        SysMessage::box() << "Please check your resources files";
        return false;
    }

    // Start meshes assets loading
    if (!meshes.startLoading())
    {
        // Could not start meshes loading
        SysMessage::box() << "[0x400A] Could not start meshes loader\n";
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
    MeshLoaderState meshState = meshes.getState();

    // Check resources loader states
    if ((textureState == TEXTURELOADER_STATE_IDLE) &&
        (meshState == MESHLOADER_STATE_IDLE))
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
    // Stop heightfar loader thread
    heightfars.stop();

    // Stop heightmap loader thread
    heightmaps.stop();

    // Stop isomap loader thread
    isomaps.stop();

    // Stop tilemap loader thread
    tilemaps.stop();

    // Stop matrixcol loader thread
    matrixcols.stop();

    // Stop mesh loader thread
    meshes.stop();

    // Stop texture loader thread
    textures.stop();

    // Destroy heightfar loader
    heightfars.destroyHeightFarLoader();

    // Destroy heightmap loader
    heightmaps.destroyHeightMapLoader();

    // Destroy isomap loader
    isomaps.destroyIsoMapLoader();

    // Destroy tilemap loader
    tilemaps.destroyTileMapLoader();

    // Destroy matrixcol loader
    matrixcols.destroyMatrixColLoader();

    // Destroy mesh loader
    meshes.destroyMeshLoader();

    // Destroy texture loader
    textures.destroyTextureLoader();
}
