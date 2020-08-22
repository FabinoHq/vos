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
//     Renderer/Swapchain.cpp : Swapchain management                          //
////////////////////////////////////////////////////////////////////////////////
#include "Swapchain.h"


////////////////////////////////////////////////////////////////////////////////
//  Swapchain default constructor                                             //
////////////////////////////////////////////////////////////////////////////////
Swapchain::Swapchain() :
handle(0),
format(VK_FORMAT_UNDEFINED),
frames(0),
current(0)
{
    extent.width = 0;
    extent.height = 0;
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        images[i] = 0;
        memories[i]= 0;
        views[i]= 0;
        framebuffers[i] = 0;
        renderReady[i] = 0;
        renderFinished[i] = 0;
        fences[i] = 0;
        commandBuffers[i] = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Swapchain destructor                                                      //
////////////////////////////////////////////////////////////////////////////////
Swapchain::~Swapchain()
{
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        commandBuffers[i] = 0;
        fences[i] = 0;
        renderFinished[i] = 0;
        renderReady[i] = 0;
        framebuffers[i] = 0;
        views[i]= 0;
        memories[i]= 0;
        images[i] = 0;
    }
    extent.height = 0;
    extent.width = 0;
    current = 0;
    frames = 0;
    format = VK_FORMAT_UNDEFINED;
    handle = 0;
}
