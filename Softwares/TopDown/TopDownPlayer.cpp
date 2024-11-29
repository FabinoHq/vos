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
//     Softwares/TopDown/TopDownPlayer.cpp : TopDown player management        //
////////////////////////////////////////////////////////////////////////////////
#include "TopDownPlayer.h"


////////////////////////////////////////////////////////////////////////////////
//  TopDownPlayer default constructor                                         //
////////////////////////////////////////////////////////////////////////////////
TopDownPlayer::TopDownPlayer() :
m_position(),
m_speed(),
m_bounding(),
m_ellipse()
{
    m_position.pos.reset();
    m_position.prevPos.reset();
    m_position.angle = 0.0f;
    m_position.prevAngle = 0.0f;
}

////////////////////////////////////////////////////////////////////////////////
//  TopDownPlayer destructor                                                  //
////////////////////////////////////////////////////////////////////////////////
TopDownPlayer::~TopDownPlayer()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Init top down player                                                      //
//  return : True if top down player is ready, false otherwise                //
////////////////////////////////////////////////////////////////////////////////
bool TopDownPlayer::init()
{
    // Reset player position
    m_position.pos.reset();
    m_position.prevPos.reset();
    m_position.angle = 0.0f;
    m_position.prevAngle = 0.0f;

    // Reset player speed
    m_speed.reset();

    // Init bounding circle
    m_bounding.setPosition(0, 0);
    m_bounding.setRadius(40000);
    m_bounding.setAngle(0);

    // Init ellipse shape
    if (!m_ellipse.init(0.2f, 0.2f))
    {
        // Could not init ellipse shape
        return false;
    }
    m_ellipse.setSmooth(0.05f);
    m_ellipse.setColor(0.0f, 0.8f, 0.2f, 0.8f);
    m_ellipse.setOrigin(0.0f, 0.0f);
    m_ellipse.setSize(
        (m_bounding.radius*PhysicsToRenderer*2.05f),
        (m_bounding.radius*PhysicsToRenderer*2.05f)
    );

    // Top down player is ready
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Compute top down player physics (threaded)                                //
////////////////////////////////////////////////////////////////////////////////
void TopDownPlayer::physics()
{
    // Convert previous position to renderer
    m_position.prevPos.vec[0] = (m_bounding.position.vec[0]*PhysicsToRenderer);
    m_position.prevPos.vec[1] = (m_bounding.position.vec[1]*PhysicsToRenderer);
    m_position.prevAngle = (m_bounding.angle*PhysicsAngleToRenderer);

    // Compute top down player speed
    if (GSysKeys.axis.vec[0] != 0)
    {
        // Accelerate X
        m_speed.vec[0] += (GSysKeys.axis.vec[0] >> 2);
    }
    else
    {
        // Decelerate X
        m_speed.moveXTowards(0, 100000);
    }
    if (GSysKeys.axis.vec[1] != 0)
    {
        // Accelerate Y
        m_speed.vec[1] += (GSysKeys.axis.vec[1] >> 2);
    }
    else
    {
        // Decelerate Y
        m_speed.moveYTowards(0, 100000);
    }
    if (m_speed.length() >= Math::OneInt)
    {
        // Clamp speed
        m_speed.normalize();
    }

    // Compute top down player position
    m_bounding.position.vec[0] += (m_speed.vec[0] >> 7);
    m_bounding.position.vec[1] += (m_speed.vec[1] >> 7);

    // Convert position to renderer
    m_position.pos.vec[0] = (m_bounding.position.vec[0]*PhysicsToRenderer);
    m_position.pos.vec[1] = (m_bounding.position.vec[1]*PhysicsToRenderer);
    m_position.angle = (m_bounding.angle*PhysicsAngleToRenderer);
}

////////////////////////////////////////////////////////////////////////////////
//  Precompute top down player                                                //
////////////////////////////////////////////////////////////////////////////////
void TopDownPlayer::precompute(float physicstime)
{
    // Precompute ellipse position and angle
    m_ellipse.linearInterp(
        m_position.prevPos, m_position.pos,
        m_position.prevAngle, m_position.angle, physicstime
    );
}

////////////////////////////////////////////////////////////////////////////////
//  Render top down player                                                    //
////////////////////////////////////////////////////////////////////////////////
void TopDownPlayer::render()
{
    // Render ellipse shape
    GRenderer.bindPipeline(RENDERER_PIPELINE_ELLIPSE);
    m_ellipse.render();
}
