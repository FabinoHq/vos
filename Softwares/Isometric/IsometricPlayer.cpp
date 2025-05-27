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
//     Softwares/Isometric/IsometricPlayer.cpp : Isometric player management  //
////////////////////////////////////////////////////////////////////////////////
#include "IsometricPlayer.h"


////////////////////////////////////////////////////////////////////////////////
//  IsometricPlayer default constructor                                       //
////////////////////////////////////////////////////////////////////////////////
IsometricPlayer::IsometricPlayer() :
Transform2(),
m_transforms(),
m_speed(),
m_bounding(),
m_physicsTile(),
m_tilePos(),
m_sprite()
{
    m_transforms.reset();
    m_speed.reset();
    m_physicsTile.reset();
    m_tilePos.reset();
}

////////////////////////////////////////////////////////////////////////////////
//  IsometricPlayer virtual destructor                                        //
////////////////////////////////////////////////////////////////////////////////
IsometricPlayer::~IsometricPlayer()
{
    m_tilePos.reset();
    m_physicsTile.reset();
    m_speed.reset();
    m_transforms.reset();
}


////////////////////////////////////////////////////////////////////////////////
//  Init isometric player                                                     //
//  return : True if isometric player is ready, false otherwise               //
////////////////////////////////////////////////////////////////////////////////
bool IsometricPlayer::init()
{
    // Reset player transformations
    m_transforms.reset();

    // Reset player speed
    m_speed.reset();

    // Init bounding aligned rectangle
    m_bounding.setPosition(0, 0);
    m_bounding.setHalfSize(32000, 32000);

    // Reset player tile position
    m_physicsTile.reset();
    m_tilePos.reset();

    // Init rectangle shape
    if (!m_sprite.init(GResources.textures.high(TEXTURE_PLAYER), 0.075f, 0.15f))
    {
        // Could not init sprite
        return false;
    }
    m_sprite.setOrigin(0.0f, -0.055f);

    // Isometric player is ready
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Precompute isometric player physics (thread sync)                         //
////////////////////////////////////////////////////////////////////////////////
void IsometricPlayer::prephysics(const Vector2i& warpOffset)
{
    // Compute prephysics transformations
    m_bounding.position += warpOffset;
    m_transforms.prephysicsIso(m_bounding.position, 0);
    m_transforms.offsetPrevPosIso(warpOffset);

    // Compute physics tile position
    m_physicsTile.vec[0] = Math::divide(
        m_bounding.position.vec[0], MatrixChunk2ElemWidth
    );
    m_physicsTile.vec[1] = Math::divide(
        m_bounding.position.vec[1], MatrixChunk2ElemHeight
    );
}

////////////////////////////////////////////////////////////////////////////////
//  Compute isometric player physics (threaded)                               //
////////////////////////////////////////////////////////////////////////////////
void IsometricPlayer::physics()
{
    // Compute isometric player speed
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
    if (m_speed.length() >= (Math::OneInt * 8))
    {
        m_speed.normalize();
        m_speed *= 8;
    }

    // Compute isometric player collisions
    Vector2i offset = Vector2i(
        (m_speed.vec[0] >> PhysicsSpeedToPositionShift)-
        (m_speed.vec[1] >> PhysicsSpeedToPositionShift),
        (m_speed.vec[0] >> PhysicsSpeedToPositionShift)+
        (m_speed.vec[1] >> PhysicsSpeedToPositionShift)
    );
    Collision2 collision((m_bounding.position + offset), offset);

    // Compute isometric player matrix collisions
    m_bounding.moveMatrix2(offset, collision);

    // Update isometric player position
    m_bounding.position = collision.position;
}

////////////////////////////////////////////////////////////////////////////////
//  Precompute isometric player renderer interpolations                       //
////////////////////////////////////////////////////////////////////////////////
void IsometricPlayer::precompute(float physicstime)
{
    // Precompute transformations
    precomputeTransforms(m_transforms, physicstime);

    // Set player tile position
    m_tilePos = m_physicsTile;
}

////////////////////////////////////////////////////////////////////////////////
//  Render isometric player                                                   //
////////////////////////////////////////////////////////////////////////////////
void IsometricPlayer::render()
{
    // Render rectangle shape
    GRenderer.bindPipeline(RENDERER_PIPELINE_DEFAULT);
    m_sprite.setPosition(m_position);
    m_sprite.bindTexture();
    m_sprite.render();
}
