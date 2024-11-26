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
m_bounding(),
m_ellipse(),
m_mutex()
{
    m_position.pos.vec[0] = 0.0f;
    m_position.pos.vec[1] = 0.0f;
    m_position.nextPos.vec[0] = 0.0f;
    m_position.nextPos.vec[1] = 0.0f;
    m_position.prevPos.vec[0] = 0.0f;
    m_position.prevPos.vec[1] = 0.0f;
    m_position.angle = 0.0f;
    m_position.nextAngle = 0.0f;
    m_position.prevAngle = 0.0f;
    m_position.time = 0.0f;
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
    // Reset position
    m_position.pos.vec[0] = 0.0f;
    m_position.pos.vec[1] = 0.0f;
    m_position.nextPos.vec[0] = 0.0f;
    m_position.nextPos.vec[1] = 0.0f;
    m_position.prevPos.vec[0] = 0.0f;
    m_position.prevPos.vec[1] = 0.0f;
    m_position.angle = 0.0f;
    m_position.nextAngle = 0.0f;
    m_position.prevAngle = 0.0f;
    m_position.time = 0.0f;

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

    // Top down player is ready
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Compute top down player physics (threaded)                                //
////////////////////////////////////////////////////////////////////////////////
void TopDownPlayer::physics(int64_t tick)
{
    (void)tick;

    // Lock position mutex
    m_mutex.lock();

    // Convert previous position to renderer
    m_position.prevPos.vec[0] = (m_bounding.position.vec[0]*PhysicsToRenderer);
    m_position.prevPos.vec[1] = (m_bounding.position.vec[1]*PhysicsToRenderer);
    m_position.prevAngle = (m_bounding.angle*PhysicsAngleToRenderer);

    // Compute top down player physics
    m_bounding.position.vec[0] += 10000;

    // Convert next position to renderer
    m_position.nextPos.vec[0] = (m_bounding.position.vec[0]*PhysicsToRenderer);
    m_position.nextPos.vec[1] = (m_bounding.position.vec[1]*PhysicsToRenderer);
    m_position.nextAngle = (m_bounding.angle*PhysicsAngleToRenderer);
    m_position.time = 0.0f;

    // Unlock position mutex
    m_mutex.unlock();
}

////////////////////////////////////////////////////////////////////////////////
//  Compute top down player logic                                             //
////////////////////////////////////////////////////////////////////////////////
void TopDownPlayer::compute(float frametime)
{
    // Compute physics time
    float physicstime = (frametime/(static_cast<float>(PhysicsTickTime)));

    // Compute current position
    m_mutex.lock();
    m_position.time = Math::clamp((m_position.time + physicstime), 0.0f, 1.0f);
    m_position.pos.vec[0] = (m_position.prevPos.vec[0] +
        ((m_position.nextPos.vec[0]-m_position.prevPos.vec[0])*m_position.time)
    );
    m_position.pos.vec[1] = (m_position.prevPos.vec[1] +
        ((m_position.nextPos.vec[1]-m_position.prevPos.vec[1])*m_position.time)
    );
    m_position.angle = (m_position.prevAngle +
        ((m_position.nextAngle-m_position.prevAngle)*m_position.time)
    );
    m_mutex.unlock();
}

////////////////////////////////////////////////////////////////////////////////
//  Render top down player                                                    //
////////////////////////////////////////////////////////////////////////////////
void TopDownPlayer::render()
{
    // Render ellipse shape
    GRenderer.bindPipeline(RENDERER_PIPELINE_ELLIPSE);
    m_ellipse.setColor(0.0f, 0.8f, 0.2f, 0.8f);
    m_ellipse.setOrigin(0.0f, 0.0f);
    m_ellipse.setPosition(m_position.pos.vec[0], m_position.pos.vec[1]);
    m_ellipse.setSize(
        (m_bounding.radius*PhysicsToRenderer*2.05f),
        (m_bounding.radius*PhysicsToRenderer*2.05f)
    );
    m_ellipse.setAngle(m_position.angle);
    m_ellipse.setSmooth(0.025f);
    m_ellipse.render();
}
