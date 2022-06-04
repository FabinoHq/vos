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
//     Physics/BoundingCircle.cpp : Bounding Circle management                //
////////////////////////////////////////////////////////////////////////////////
#include "BoundingCircle.h"


////////////////////////////////////////////////////////////////////////////////
//  BoundingCircle default constructor                                        //
////////////////////////////////////////////////////////////////////////////////
BoundingCircle::BoundingCircle() :
position(0, 0),
radius(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  BoundingCircle copy constructor                                           //
////////////////////////////////////////////////////////////////////////////////
BoundingCircle::BoundingCircle(const BoundingCircle& boundingCircle)
{
    position.vec[0] = boundingCircle.position.vec[0];
	position.vec[1] = boundingCircle.position.vec[1];
    radius = boundingCircle.radius;
}

////////////////////////////////////////////////////////////////////////////////
//  BoundingCircle position and radius constructor                            //
////////////////////////////////////////////////////////////////////////////////
BoundingCircle::BoundingCircle(
	const Vector2i& circlePosition, int64_t circleRadius)
{
	position.vec[0] = circlePosition.vec[0];
	position.vec[1] = circlePosition.vec[1];
	radius = circleRadius;
}

////////////////////////////////////////////////////////////////////////////////
//  BoundingCircle destructor                                                 //
////////////////////////////////////////////////////////////////////////////////
BoundingCircle::~BoundingCircle()
{
	radius = 0;
	position.vec[1] = 0;
	position.vec[0] = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Set bounding circle position and radius                                   //
////////////////////////////////////////////////////////////////////////////////
void BoundingCircle::set(const Vector2i& circlePosition, int64_t circleRadius)
{
	position.vec[0] = circlePosition.vec[0];
	position.vec[1] = circlePosition.vec[1];
	radius = circleRadius;
}

////////////////////////////////////////////////////////////////////////////////
//  Set bounding circle position                                              //
////////////////////////////////////////////////////////////////////////////////
void BoundingCircle::setPosition(const Vector2i& circlePosition)
{
	position.vec[0] = circlePosition.vec[0];
	position.vec[1] = circlePosition.vec[1];
}

////////////////////////////////////////////////////////////////////////////////
//  Set bounding circle position                                              //
////////////////////////////////////////////////////////////////////////////////
void BoundingCircle::setPosition(int64_t positionX, int64_t positionY)
{
	position.vec[0] = positionX;
	position.vec[1] = positionY;
}

////////////////////////////////////////////////////////////////////////////////
//  Set bounding circle position X position                                   //
////////////////////////////////////////////////////////////////////////////////
void BoundingCircle::setPositionX(int64_t positionX)
{
	position.vec[0] = positionX;
}

////////////////////////////////////////////////////////////////////////////////
//  Set bounding circle position Y position                                   //
////////////////////////////////////////////////////////////////////////////////
void BoundingCircle::setPositionY(int64_t positionY)
{
	position.vec[1] = positionY;
}

////////////////////////////////////////////////////////////////////////////////
//  Set bounding circle radius                                                //
////////////////////////////////////////////////////////////////////////////////
void BoundingCircle::setRadius(int64_t circleRadius)
{
	radius = circleRadius;
}


////////////////////////////////////////////////////////////////////////////////
//  Collide bounding circle with bounding circle                              //
////////////////////////////////////////////////////////////////////////////////
bool BoundingCircle::collideCircle(const BoundingCircle& boundingCircle)
{
	Vector2i dist = (position - boundingCircle.position);
	int64_t distance = (dist.vec[0]*dist.vec[0])+(dist.vec[1]*dist.vec[1]);
	int64_t radiuses = (radius + boundingCircle.radius);
	return (distance <= (radiuses*radiuses));
}

////////////////////////////////////////////////////////////////////////////////
//  Collide bounding circle with bounding circle                              //
////////////////////////////////////////////////////////////////////////////////
bool BoundingCircle::collideCircle(const BoundingCircle& boundingCircle,
	const Vector2i& offset, Collision2& collision)
{
	// Reset collision
	collision.reset();
	collision.collide = false;
	collision.position.vec[0] = position.vec[0]+offset.vec[0];
	collision.position.vec[1] = position.vec[1]+offset.vec[1];
	collision.offset.vec[0] = offset.vec[0];
	collision.offset.vec[1] = offset.vec[1];

	// Collide circle
	Vector2i dist = (position - boundingCircle.position);
	int64_t distance = (dist.vec[0]*dist.vec[0])+(dist.vec[1]*dist.vec[1]);
	int64_t radiuses = (radius + boundingCircle.radius);
	bool colliding = (distance <= (radiuses*radiuses));
	collision.collide = colliding;
	return colliding;
}


////////////////////////////////////////////////////////////////////////////////
//  BoundingCircle affectation operator                                       //
////////////////////////////////////////////////////////////////////////////////
BoundingCircle& BoundingCircle::operator=(const BoundingCircle& boundingCircle)
{
	position.vec[0] = boundingCircle.position.vec[0];
	position.vec[1] = boundingCircle.position.vec[1];
	radius = boundingCircle.radius;
	return *this;
}
