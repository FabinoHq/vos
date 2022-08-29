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
radius(PhysicsMinEntityHalfSize)
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
	if (circleRadius <= PhysicsMinEntityHalfSize)
	{
		circleRadius = PhysicsMinEntityHalfSize;
	}
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
	if (circleRadius <= PhysicsMinEntityHalfSize)
	{
		circleRadius = PhysicsMinEntityHalfSize;
	}
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
	if (circleRadius <= PhysicsMinEntityHalfSize)
	{
		circleRadius = PhysicsMinEntityHalfSize;
	}
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
	collision.position.vec[0] = position.vec[0];
	collision.position.vec[1] = position.vec[1];

	// Check offset vector
	if ((offset.vec[0] == 0) && (offset.vec[1] == 0)) { return false; }

	// Check current collision
	if (collideCircle(boundingCircle))
	{
		// Currently colliding
		collision.collide = true;
		return collision.collide;
	}

	// Compute step offset
	int64_t stepRadius =
		(radius <= boundingCircle.radius) ? radius : boundingCircle.radius;
	if (stepRadius <= 0) { return false; }
	int64_t stepX = Math::abs(offset.vec[0])/stepRadius;
	int64_t stepY = Math::abs(offset.vec[1])/stepRadius;
	int64_t step = (stepX >= stepY) ? stepX : stepY;
	if (step <= 1) { step = 1; }
	stepX = offset.vec[0]/step;
	stepY = offset.vec[1]/step;

	// Iterative collision detection
	bool collide = false;
	BoundingCircle currentCircle(*this);
	for (int64_t i = 0; i < step; ++i)
	{
		if (currentCircle.collideCircle(boundingCircle))
		{
			// Collision detected
			collide = true;
			break;
		}
		else
		{
			// Next iteration
			collision.position.vec[0] = currentCircle.position.vec[0];
			collision.position.vec[1] = currentCircle.position.vec[1];
			currentCircle.position.vec[0] += stepX;
			currentCircle.position.vec[1] += stepY;
		}
	}

	if (!collide)
	{
		// Last collision detection
		currentCircle.position.vec[0] = position.vec[0]+offset.vec[0];
		currentCircle.position.vec[1] = position.vec[1]+offset.vec[1];
		if (!currentCircle.collideCircle(boundingCircle))
		{
			// No collision detected
			collision.position.vec[0] = position.vec[0]+offset.vec[0];
			collision.position.vec[1] = position.vec[1]+offset.vec[1];
			collision.offset.vec[0] = offset.vec[0];
			collision.offset.vec[1] = offset.vec[1];
			collision.collide = false;
			return collision.collide;
		}
	}

	// Small steps iterative collision
	stepX >>= 1;	// stepX = stepX/2
	stepY >>= 1;	// stepY = stepY/2
	currentCircle.position.vec[0] = collision.position.vec[0];
	currentCircle.position.vec[1] = collision.position.vec[1];
	for (int64_t i = 0; i < PhysicsMaxSmallStepsIterations; ++i)
	{
		currentCircle.position.vec[0] += stepX;
		currentCircle.position.vec[1] += stepY;
		if (currentCircle.collideCircle(boundingCircle))
		{
			// Rollback to previous position
			currentCircle.position.vec[0] = collision.position.vec[0];
			currentCircle.position.vec[1] = collision.position.vec[1];
			stepX >>= 1;	// stepX = stepX/2
			stepY >>= 1;	// stepY = stepY/2
		}
		else
		{
			// Store current position
			collision.position.vec[0] = currentCircle.position.vec[0];
			collision.position.vec[1] = currentCircle.position.vec[1];
		}
		if ((stepX == 0) && (stepY == 0)) { break; }
	}

	// Collision detected
	collision.offset.vec[0] = currentCircle.position.vec[0] - position.vec[0];
	collision.offset.vec[1] = currentCircle.position.vec[1] - position.vec[1];
	collision.position.vec[0] = currentCircle.position.vec[0];
	collision.position.vec[1] = currentCircle.position.vec[1];
	collision.collide = true;
	return collision.collide;
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
