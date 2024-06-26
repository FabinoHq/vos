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
//     Renderer/SkyBox.cpp : SkyBox management                                //
////////////////////////////////////////////////////////////////////////////////
#include "SkyBox.h"


////////////////////////////////////////////////////////////////////////////////
//  SkyBox default constructor                                                //
////////////////////////////////////////////////////////////////////////////////
SkyBox::SkyBox() :
Transform3(),
m_cubemap(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  SkyBox virtual destructor                                                 //
////////////////////////////////////////////////////////////////////////////////
SkyBox::~SkyBox()
{
    m_cubemap = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Init skybox                                                               //
//  return : True if the skybox is successfully created                       //
////////////////////////////////////////////////////////////////////////////////
bool SkyBox::init(CubeMap& cubemap)
{
    // Check cubemap handle
    if (!cubemap.isValid())
    {
        // Invalid cubemap handle
        return false;
    }

    // Set skybox cubemap pointer
    m_cubemap = &cubemap;

    // Reset skybox transformations
    resetTransforms();

    // SkyBox successfully created
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Render skybox                                                             //
////////////////////////////////////////////////////////////////////////////////
void SkyBox::render()
{
    // Compute skybox transformations
    computeTransforms();

    // Push model matrix into command buffer
    vkCmdPushConstants(
        GSwapchain.commandBuffers[GSwapchain.current],
        GGraphicsLayout.handle, VK_SHADER_STAGE_VERTEX_BIT,
        PushConstantMatrixOffset, PushConstantMatrixSize, m_matrix.mat
    );

    // Draw skybox triangles
    vkCmdDrawIndexed(
        GSwapchain.commandBuffers[GSwapchain.current],
        SkyBoxIndicesCount, 1, 0, 0, 0
    );
}
