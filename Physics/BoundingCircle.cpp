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
//     Physics/BoundingCircle.cpp : Bounding Circle management                //
////////////////////////////////////////////////////////////////////////////////
#include "BoundingCircle.h"


////////////////////////////////////////////////////////////////////////////////
//  BoundingCircle default constructor                                        //
////////////////////////////////////////////////////////////////////////////////
BoundingCircle::BoundingCircle() :
position(0, 0),
radius(PhysicsMinEntityHalfSize),
angle(0)
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
    angle = boundingCircle.angle;
}

////////////////////////////////////////////////////////////////////////////////
//  BoundingCircle position radius and angle constructor                      //
////////////////////////////////////////////////////////////////////////////////
BoundingCircle::BoundingCircle(const Vector2i& circlePosition,
	int64_t circleRadius, int64_t circleAngle)
{
	position.vec[0] = circlePosition.vec[0];
	position.vec[1] = circlePosition.vec[1];
	radius = Math::max(circleRadius, PhysicsMinEntityHalfSize);
	angle = (circleAngle % Math::TwoPiInt);
}

////////////////////////////////////////////////////////////////////////////////
//  BoundingCircle destructor                                                 //
////////////////////////////////////////////////////////////////////////////////
BoundingCircle::~BoundingCircle()
{
	angle = 0;
	radius = 0;
	position.vec[1] = 0;
	position.vec[0] = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Set bounding circle position radius and angle                             //
////////////////////////////////////////////////////////////////////////////////
void BoundingCircle::set(const Vector2i& circlePosition,
	int64_t circleRadius, int64_t circleAngle)
{
	position.vec[0] = circlePosition.vec[0];
	position.vec[1] = circlePosition.vec[1];
	radius = Math::max(circleRadius, PhysicsMinEntityHalfSize);
	angle = (circleAngle % Math::TwoPiInt);
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
	collision.setFactor(Math::OneInt);

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
	int64_t step = Math::max(((stepX >= stepY) ? stepX : stepY), 1ll);
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
	collision.normal.vec[0] =
		(collision.position.vec[0] - boundingCircle.position.vec[0]);
	collision.normal.vec[1] =
		(collision.position.vec[1] - boundingCircle.position.vec[1]);
	collision.normal.normalize();
	collision.setFactor(
		(collision.offset.length() << Math::OneIntShift) / offset.length()
	);
	collision.collide = true;
	return collision.collide;
}


////////////////////////////////////////////////////////////////////////////////
//  Collide bounding circle with matrix chunk 2                               //
////////////////////////////////////////////////////////////////////////////////
bool BoundingCircle::collideMatrix2(const MatrixChunk2& matrixChunk2)
{
	return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Collide bounding circle with matrix chunk 2                               //
////////////////////////////////////////////////////////////////////////////////
bool BoundingCircle::collideMatrix2(const MatrixChunk2& matrixChunk2,
    const Vector2i& offset, Collision2& collision)
{
	// Reset collision
	collision.reset();
	collision.position.vec[0] = (position.vec[0]+offset.vec[0]);
	collision.position.vec[1] = (position.vec[1]+offset.vec[1]);
	collision.offset.vec[0] = offset.vec[0];
	collision.offset.vec[1] = offset.vec[1];
	collision.setFactor(Math::OneInt);
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
	angle = boundingCircle.angle;
	return *this;
}
