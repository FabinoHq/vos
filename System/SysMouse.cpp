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
m_previousX(0),
m_previousY(0),
tracking(false),
mouseX(0.0f),
mouseY(0.0f),
deltaX(0.0f),
deltaY(0.0f),
wheel(0),
left(false),
right(false),
target(0.0f),
physicsTarget(0),
angles(),
physicsAngles()
{

}

////////////////////////////////////////////////////////////////////////////////
//  SysMouse destructor                                                       //
////////////////////////////////////////////////////////////////////////////////
SysMouse::~SysMouse()
{
    physicsAngles.reset();
    angles.reset();
    physicsTarget = 0;
    target = 0.0f;
    right = false;
    left = false;
    wheel = 0;
    deltaY = 0.0f;
    deltaX = 0.0f;
    mouseY = 0.0f;
    mouseX = 0.0f;
    tracking = false;
    m_previousY = 0;
    m_previousX = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Mouse move event                                                          //
////////////////////////////////////////////////////////////////////////////////
void SysMouse::move(int x, int y)
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
        deltaX = ((x-m_previousX)*1.0f);
        deltaY = ((y-m_previousY)*1.0f);
        mouseX = Math::clamp((-ratio + (x*scale*2.0f)), -ratio, ratio);
        mouseY = Math::clamp((1.0f - (y*scale*2.0f)), -1.0f, 1.0f);
    #endif // VOS_POINTERLOCK

    // Lock mouse mutex
    m_mutex.lock();

    // Compute mouse target
    target = Math::atan(mouseX, mouseY);

    // Compute mouse angles
    if (tracking)
    {
        angles.vec[0] -= (deltaX*SysMouseSensitivityFactor);
        angles.vec[1] -= (deltaY*SysMouseSensitivityFactor);
    }

    // Clamp mouse angles
    angles.vec[0] = Math::modulo(angles.vec[0], Math::TwoPi);
    angles.vec[1] = Math::clamp(
        angles.vec[1], SysMouseMinAngle, SysMouseMaxAngle
    );

    // Unlock mouse mutex
    m_mutex.unlock();

    // Update previous mouse position
    m_previousX = x;
    m_previousY = y;
}

////////////////////////////////////////////////////////////////////////////////
//  Mouse button pressed event                                                //
////////////////////////////////////////////////////////////////////////////////
void SysMouse::pressed(const SysEventMouseButton& button)
{
    // Set mouse button pressed state
    switch (button)
    {
        case SYSEVENT_MOUSE_LEFT:
            left = true;
            break;
        case SYSEVENT_MOUSE_RIGHT:
            right = true;
            break;
        default:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Mouse button released event                                               //
////////////////////////////////////////////////////////////////////////////////
void SysMouse::released(const SysEventMouseButton& button)
{
    // Set mouse button released state
    switch (button)
    {
        case SYSEVENT_MOUSE_LEFT:
            left = false;
            break;
        case SYSEVENT_MOUSE_RIGHT:
            right = false;
            break;
        default:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Mouse wheel event                                                         //
////////////////////////////////////////////////////////////////////////////////
void SysMouse::mouseWheel(int mouseWheel)
{
    wheel = mouseWheel;
}


////////////////////////////////////////////////////////////////////////////////
//  Sync mouse with physics (copy internal states)                            //
////////////////////////////////////////////////////////////////////////////////
void SysMouse::sync()
{
    // Lock mouse mutex
    m_mutex.lock();

    // Copy mouse internal states to physics states
    physicsTarget = static_cast<int32_t>(target * RendererAngleToPhysics);
    physicsAngles.vec[0] = static_cast<int32_t>(
        angles.vec[0] * RendererAngleToPhysics
    );
    physicsAngles.vec[1] = static_cast<int32_t>(
        angles.vec[1] * RendererAngleToPhysics
    );

    // Unlock mouse mutex
    m_mutex.unlock();
}
