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
//     Physics/BoundingRect.cpp : Bounding Rectangle management               //
////////////////////////////////////////////////////////////////////////////////
#include "BoundingRect.h"


////////////////////////////////////////////////////////////////////////////////
//  BoundingRect default constructor                                          //
////////////////////////////////////////////////////////////////////////////////
BoundingRect::BoundingRect() :
position(0, 0),
size(PhysicsMinEntityHalfSize, PhysicsMinEntityHalfSize),
angle(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  BoundingRect copy constructor                                             //
////////////////////////////////////////////////////////////////////////////////
BoundingRect::BoundingRect(const BoundingRect& boundingRect)
{
    position.vec[0] = boundingRect.position.vec[0];
	position.vec[1] = boundingRect.position.vec[1];
	size.vec[0] = Math::max(boundingRect.size.vec[0], PhysicsMinEntityHalfSize);
	size.vec[1] = Math::max(boundingRect.size.vec[1], PhysicsMinEntityHalfSize);
	angle = boundingRect.angle;
}

////////////////////////////////////////////////////////////////////////////////
//  BoundingRect position size and angle constructor                          //
////////////////////////////////////////////////////////////////////////////////
BoundingRect::BoundingRect(const Vector2i& rectPosition,
	const Vector2i& rectSize, int64_t rectAngle)
{
	position.vec[0] = rectPosition.vec[0];
	position.vec[1] = rectPosition.vec[1];
	size.vec[0] = Math::max(rectSize.vec[0], PhysicsMinEntityHalfSize);
	size.vec[1] = Math::max(rectSize.vec[1], PhysicsMinEntityHalfSize);
	angle = (rectAngle % Math::TwoPiInt);
}

////////////////////////////////////////////////////////////////////////////////
//  BoundingRect destructor                                                   //
////////////////////////////////////////////////////////////////////////////////
BoundingRect::~BoundingRect()
{
	angle = 0;
	size.vec[1] = 0;
	size.vec[0] = 0;
	position.vec[1] = 0;
	position.vec[0] = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Set bounding rect position size and angle                                 //
////////////////////////////////////////////////////////////////////////////////
void BoundingRect::set(const Vector2i& rectPosition,
	const Vector2i& rectSize, int64_t rectAngle)
{
	position.vec[0] = rectPosition.vec[0];
	position.vec[1] = rectPosition.vec[1];
	size.vec[0] = Math::max(rectSize.vec[0], PhysicsMinEntityHalfSize);
	size.vec[1] = Math::max(rectSize.vec[1], PhysicsMinEntityHalfSize);
	angle = (rectAngle % Math::TwoPiInt);
}


////////////////////////////////////////////////////////////////////////////////
//  Collide bounding rect with bounding rect                                  //
////////////////////////////////////////////////////////////////////////////////
bool BoundingRect::collideRect(const BoundingRect& boundingRect)
{
	return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Collide bounding rect with bounding rect                                  //
////////////////////////////////////////////////////////////////////////////////
bool BoundingRect::collideRect(const BoundingRect& boundingRect,
	const Vector2i& offset, Collision2& collision)
{
	// Reset collision
	collision.reset();
	collision.position.vec[0] = position.vec[0]+offset.vec[0];
	collision.position.vec[1] = position.vec[1]+offset.vec[1];
	collision.offset.vec[0] = offset.vec[0];
	collision.offset.vec[1] = offset.vec[1];
	collision.setFactor(Math::OneInt);
	collision.collide = false;
	return collision.collide;
}


////////////////////////////////////////////////////////////////////////////////
//  BoundingRect affectation operator                                         //
////////////////////////////////////////////////////////////////////////////////
BoundingRect& BoundingRect::operator=(const BoundingRect& boundingRect)
{
	position.vec[0] = boundingRect.position.vec[0];
	position.vec[1] = boundingRect.position.vec[1];
	size.vec[0] = boundingRect.size.vec[0];
	size.vec[1] = boundingRect.size.vec[1];
	angle = (boundingRect.angle % Math::TwoPiInt);
	return *this;
}
