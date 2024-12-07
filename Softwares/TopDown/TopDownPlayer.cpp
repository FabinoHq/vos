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
m_transforms(),
m_speed(),
m_bounding(),
m_matrixChunk(),
m_rectangle(),
m_ellipse()
{
    m_transforms.reset();
    m_speed.reset();
}

////////////////////////////////////////////////////////////////////////////////
//  TopDownPlayer destructor                                                  //
////////////////////////////////////////////////////////////////////////////////
TopDownPlayer::~TopDownPlayer()
{
    m_speed.reset();
    m_transforms.reset();
}


////////////////////////////////////////////////////////////////////////////////
//  Init top down player                                                      //
//  return : True if top down player is ready, false otherwise                //
////////////////////////////////////////////////////////////////////////////////
bool TopDownPlayer::init()
{
    // Reset player transformations
    m_transforms.reset();

    // Reset player speed
    m_speed.reset();

    // Init bounding aligned rectangle
    m_bounding.setPosition(0, 0);
    m_bounding.setHalfSize(40000, 40000);
    //m_bounding.setAngle(0);

    // Init test matrix chunk
    if (!m_matrixChunk.init())
    {
        // Could not init matrix chunk
        return false;
    }

    // Init rectangle shape
    if (!m_rectangle.init(0.2f, 0.2f))
    {
        // Could not init rectangle shape
        return false;
    }
    m_rectangle.setSmooth(0.05f);
    m_rectangle.setColor(0.0f, 0.8f, 0.2f, 0.8f);
    m_rectangle.setOrigin(0.0f, 0.0f);
    m_rectangle.setSize(
        (m_bounding.halfSize.vec[0]*PhysicsToRenderer*2.05f),
        (m_bounding.halfSize.vec[1]*PhysicsToRenderer*2.05f)
    );

    // Init ellipse shape
    /*if (!m_ellipse.init(0.2f, 0.2f))
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
    );*/

    // Top down player is ready
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Precompute top down player physics (thread sync)                          //
////////////////////////////////////////////////////////////////////////////////
void TopDownPlayer::prephysics()
{
    // Compute prephysics transformations
    m_transforms.prephysics(m_bounding.position, 0);
    //m_transforms.prephysics(m_bounding.position, m_bounding.angle);
}

////////////////////////////////////////////////////////////////////////////////
//  Compute top down player physics (threaded)                                //
////////////////////////////////////////////////////////////////////////////////
void TopDownPlayer::physics()
{
    // Compute top down player speed
    if (GSysKeys.axis.vec[0] != 0)
    {
        // Accelerate X
        m_speed.vec[0] += (GSysKeys.axis.vec[0] * 4);
    }
    else
    {
        // Decelerate X
        m_speed.moveXTowards(0, Math::OneInt);
    }
    if (GSysKeys.axis.vec[1] != 0)
    {
        // Accelerate Y
        m_speed.vec[1] += (GSysKeys.axis.vec[1] * 4);
    }
    else
    {
        // Decelerate Y
        m_speed.moveYTowards(0, Math::OneInt);
    }

    // Clamp speed
    if (m_speed.length() >= (Math::OneInt * 12))
    {
        m_speed.normalize();
        m_speed *= 12;
    }

    // Compute top down player collisions
    Collision2 collide;
    Vector2i position = m_bounding.position;
    Vector2i remain = Vector2i(0, 0);
    Vector2i offset = Vector2i(
        (m_speed.vec[0] >> PhysicsSpeedToPositionShift),
        (m_speed.vec[1] >> PhysicsSpeedToPositionShift)
    );
    int64_t squaredLen = offset.squaredLength();

    // Compute top down player matrix collisions
    if (m_bounding.collideMatrix2(m_matrixChunk, offset, collide))
    {
        // Compute separated X axis
        squaredLen = Math::min(squaredLen, collide.length);
        remain = (offset - collide.offset);
        m_bounding.position = collide.position;
        offset = Vector2i(remain.vec[0], 0);
        if (m_bounding.collideMatrix2(m_matrixChunk, offset, collide))
        {
            // Compute separated Y axis
            squaredLen = Math::min(squaredLen, collide.length);
            m_bounding.position = collide.position;
            offset = Vector2i(0, remain.vec[1]);
            m_bounding.collideMatrix2(m_matrixChunk, offset, collide);
        }
    }
    squaredLen = Math::min(squaredLen, collide.length);
    m_bounding.position = collide.position;
}

////////////////////////////////////////////////////////////////////////////////
//  Precompute top down player renderer interpolations                        //
////////////////////////////////////////////////////////////////////////////////
void TopDownPlayer::precompute(float physicstime)
{
    // Precompute transformations
    m_rectangle.precomputeTransforms(m_transforms, physicstime);
    //m_ellipse.precomputeTransforms(m_transforms, physicstime);
}

////////////////////////////////////////////////////////////////////////////////
//  Render top down player                                                    //
////////////////////////////////////////////////////////////////////////////////
void TopDownPlayer::render()
{
    // Render rectangle shape
    GRenderer.bindPipeline(RENDERER_PIPELINE_RECTANGLE);
    m_rectangle.render();
    // Render ellipse shape
    /*GRenderer.bindPipeline(RENDERER_PIPELINE_ELLIPSE);
    m_ellipse.render();*/
}
