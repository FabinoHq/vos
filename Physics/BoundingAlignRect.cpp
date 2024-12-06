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
//     Physics/BoundingAlignRect.cpp : Bounding Aligned Rectangle management  //
////////////////////////////////////////////////////////////////////////////////
#include "BoundingAlignRect.h"


////////////////////////////////////////////////////////////////////////////////
//  BoundingAlignRect default constructor                                     //
////////////////////////////////////////////////////////////////////////////////
BoundingAlignRect::BoundingAlignRect() :
position(0, 0),
halfSize(PhysicsMinEntityHalfSize, PhysicsMinEntityHalfSize)
{

}

////////////////////////////////////////////////////////////////////////////////
//  BoundingAlignRect copy constructor                                        //
////////////////////////////////////////////////////////////////////////////////
BoundingAlignRect::BoundingAlignRect(const BoundingAlignRect& boundingAlignRect)
{
    position = boundingAlignRect.position;
	halfSize.vec[0] = Math::max(
		boundingAlignRect.halfSize.vec[0], PhysicsMinEntityHalfSize
	);
	halfSize.vec[1] = Math::max(
		boundingAlignRect.halfSize.vec[1], PhysicsMinEntityHalfSize
	);
}

////////////////////////////////////////////////////////////////////////////////
//  BoundingAlignRect position and size constructor                           //
////////////////////////////////////////////////////////////////////////////////
BoundingAlignRect::BoundingAlignRect(const Vector2i& rectPosition,
	const Vector2i& rectHalfSize)
{
	position = rectPosition;
	halfSize.vec[0] = Math::max(rectHalfSize.vec[0], PhysicsMinEntityHalfSize);
	halfSize.vec[1] = Math::max(rectHalfSize.vec[1], PhysicsMinEntityHalfSize);
}

////////////////////////////////////////////////////////////////////////////////
//  BoundingAlignRect destructor                                              //
////////////////////////////////////////////////////////////////////////////////
BoundingAlignRect::~BoundingAlignRect()
{
	halfSize.reset();
	position.reset();
}


////////////////////////////////////////////////////////////////////////////////
//  Set bounding align rect position and size                                 //
////////////////////////////////////////////////////////////////////////////////
void BoundingAlignRect::set(const Vector2i& rectPosition,
	const Vector2i& rectHalfSize)
{
	position = rectPosition;
	halfSize.vec[0] = Math::max(rectHalfSize.vec[0], PhysicsMinEntityHalfSize);
	halfSize.vec[1] = Math::max(rectHalfSize.vec[1], PhysicsMinEntityHalfSize);
}


////////////////////////////////////////////////////////////////////////////////
//  Collide bounding align rect with bounding align rect                      //
////////////////////////////////////////////////////////////////////////////////
bool BoundingAlignRect::collideAlignRect(
	const BoundingAlignRect& boundingAlignRect)
{
	return (
		((position.vec[0]-halfSize.vec[0]) <=
		(boundingAlignRect.position.vec[0]+boundingAlignRect.halfSize.vec[0]))&&
		((position.vec[0]+halfSize.vec[0]) >=
		(boundingAlignRect.position.vec[0]-boundingAlignRect.halfSize.vec[0]))&&
		((position.vec[1]-halfSize.vec[1]) <=
		(boundingAlignRect.position.vec[1]+boundingAlignRect.halfSize.vec[1]))&&
		((position.vec[1]+halfSize.vec[1]) >=
		(boundingAlignRect.position.vec[1]-boundingAlignRect.halfSize.vec[1]))
	);
}

////////////////////////////////////////////////////////////////////////////////
//  Collide bounding align rect with bounding align rect                      //
////////////////////////////////////////////////////////////////////////////////
bool BoundingAlignRect::collideAlignRect(
	const BoundingAlignRect& boundingAlignRect,
	const Vector2i& offset, Collision2& collision)
{
	// Reset collision
	collision.reset();
	collision.position = (position + offset);
	collision.offset = offset;
	collision.setFactor(Math::OneInt);
	collision.collide = false;
	return collision.collide;
}


////////////////////////////////////////////////////////////////////////////////
//  BoundingAlignRect affectation operator                                    //
////////////////////////////////////////////////////////////////////////////////
BoundingAlignRect& BoundingAlignRect::operator=(
	const BoundingAlignRect& boundingAlignRect)
{
	position = boundingAlignRect.position;
	halfSize = boundingAlignRect.halfSize;
	return *this;
}
