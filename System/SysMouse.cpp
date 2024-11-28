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
//     System/SysMouse.cpp : System Mouse management                          //
////////////////////////////////////////////////////////////////////////////////
#include "SysMouse.h"
#include "../Renderer/Vulkan/Swapchain.h"


////////////////////////////////////////////////////////////////////////////////
//  SysMouse global instance                                                  //
////////////////////////////////////////////////////////////////////////////////
SysMouse GSysMouse = SysMouse();


////////////////////////////////////////////////////////////////////////////////
//  SysMouse default constructor                                              //
////////////////////////////////////////////////////////////////////////////////
SysMouse::SysMouse() :
m_mutex(),
m_angle(0.0f),
previousX(0),
previousY(0),
mouseX(0.0f),
mouseY(0.0f),
deltaX(0.0f),
deltaY(0.0f),
angle(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  SysMouse destructor                                                       //
////////////////////////////////////////////////////////////////////////////////
SysMouse::~SysMouse()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Update mouse position                                                     //
////////////////////////////////////////////////////////////////////////////////
void SysMouse::update(int x, int y)
{
    // Get renderer scale and ratio
    float scale = GSwapchain.getScale();
    float ratio = GSwapchain.getRatio();

    // Compute mouse position
    #if (VOS_POINTERLOCK == 1)
        // High precision mouse delta
        deltaX = (x*1.0f);
        deltaY = (y*1.0f);
        mouseX += (x*scale*2.0f);
        mouseY -= (y*scale*2.0f);
        mouseX = Math::clamp(mouseX, -ratio, ratio);
        mouseY = Math::clamp(mouseY, -1.0f, 1.0f);
    #else
        // OS absolute mouse position
        deltaX = ((x-previousX)*1.0f);
        deltaY = ((y-previousY)*1.0f);
        mouseX = Math::clamp((-ratio + (x*scale*2.0f)), -ratio, ratio);
        mouseY = Math::clamp((1.0f - (y*scale*2.0f)), -1.0f, 1.0f);
    #endif // VOS_POINTERLOCK

    // Compute mouse angle
    m_mutex.lock();
    m_angle = Math::atan(mouseX, mouseY);
    m_mutex.unlock();

    // Update previous mouse position
    previousX = x;
    previousY = y;
}


////////////////////////////////////////////////////////////////////////////////
//  Sync mouse with physics (copy internal states)                            //
////////////////////////////////////////////////////////////////////////////////
void SysMouse::sync()
{
    // Copy mouse internal states
    m_mutex.lock();
    angle = static_cast<int32_t>(m_angle*RendererAngleToPhysics);
    m_mutex.unlock();
}
