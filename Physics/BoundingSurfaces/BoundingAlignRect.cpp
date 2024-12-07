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
//     Physics/BoundingSurfaces/BoundingAlignRect.cpp : Aligned Rectangle     //
////////////////////////////////////////////////////////////////////////////////
#include "BoundingAlignRect.h"
#include "BoundingCircle.h"


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
	collision.position = position;
	collision.setFactor(Math::OneInt);

	// Check offset vector
	if (offset.isZero()) { return false; }

	// Check current collision
	if (collideAlignRect(boundingAlignRect))
	{
		// Currently colliding
		collision.collide = true;
		return collision.collide;
	}

	// Compute step offset
	int32_t stepOffset = Math::max(Math::min(
		Math::min(halfSize.vec[0], boundingAlignRect.halfSize.vec[0]),
		Math::min(halfSize.vec[1], boundingAlignRect.halfSize.vec[1])),
		PhysicsMinEntityHalfSize
	);
	int32_t stepX = (Math::abs(offset.vec[0]) / stepOffset);
	int32_t stepY = (Math::abs(offset.vec[1]) / stepOffset);
	int32_t step = Math::max(((stepX >= stepY) ? stepX : stepY), 1);
	stepX = (offset.vec[0] / step);
	stepY = (offset.vec[1] / step);

	// Iterative collision detection
	bool collide = false;
	BoundingAlignRect currentAlignRect(*this);
	for (int32_t i = 0; i < step; ++i)
	{
		if (currentAlignRect.collideAlignRect(boundingAlignRect))
		{
			// Collision detected
			collide = true;
			break;
		}
		else
		{
			// Next iteration
			collision.position = currentAlignRect.position;
			currentAlignRect.position.vec[0] += stepX;
			currentAlignRect.position.vec[1] += stepY;
		}
	}

	if (!collide)
	{
		// Last collision detection
		currentAlignRect.position = (position + offset);
		if (!currentAlignRect.collideAlignRect(boundingAlignRect))
		{
			// No collision detected
			collision.position = (position + offset);
			collision.offset = offset;
			collision.collide = false;
			return collision.collide;
		}
	}

	// Small steps iterative collision
	stepX >>= 1;	// stepX = stepX/2
	stepY >>= 1;	// stepY = stepY/2
	currentAlignRect.position = collision.position;
	for (int32_t i = 0; i < PhysicsMaxSmallStepsIterations; ++i)
	{
		currentAlignRect.position.vec[0] += stepX;
		currentAlignRect.position.vec[1] += stepY;
		if (currentAlignRect.collideAlignRect(boundingAlignRect))
		{
			// Rollback to previous position
			currentAlignRect.position = collision.position;
			stepX >>= 1;	// stepX = stepX/2
			stepY >>= 1;	// stepY = stepY/2
		}
		else
		{
			// Store current position
			collision.position = currentAlignRect.position;
		}
		if ((stepX == 0) && (stepY == 0)) { break; }
	}

	// Collision detected
	collision.offset = (currentAlignRect.position - position);
	collision.position = currentAlignRect.position;
	collision.normal = (collision.position - boundingAlignRect.position);
	collision.normal.normalize();
	collision.setFactor(static_cast<int32_t>(
		(collision.offset.length() << Math::OneIntShift) / offset.length()
	));
	collision.collide = true;
	return collision.collide;
}


////////////////////////////////////////////////////////////////////////////////
//  Collide bounding align rect with bounding circle                          //
////////////////////////////////////////////////////////////////////////////////
bool BoundingAlignRect::collideCircle(const BoundingCircle& boundingCircle)
{
	// Compute clamped distance between align rect and circle
	Vector2i dist = (position - boundingCircle.position);
	dist.clamp(
		-halfSize.vec[0], -halfSize.vec[1],
		halfSize.vec[0], halfSize.vec[1]
	);

	// Compute distance between circle and closest align rect point
	dist = (position - (boundingCircle.position + dist));
	int64_t distance = (
		(static_cast<int64_t>(dist.vec[0])*
		static_cast<int64_t>(dist.vec[0]))+
		(static_cast<int64_t>(dist.vec[1])*
		static_cast<int64_t>(dist.vec[1]))
	);

	// Check if align rect is colliding with circle
	return (
		distance <= (
			static_cast<int64_t>(boundingCircle.radius)*
			static_cast<int64_t>(boundingCircle.radius)
		)
	);
}

////////////////////////////////////////////////////////////////////////////////
//  Collide bounding align rect with bounding circle                          //
////////////////////////////////////////////////////////////////////////////////
bool BoundingAlignRect::collideCircle(const BoundingCircle& boundingCircle,
	const Vector2i& offset, Collision2& collision)
{
	// Reset collision
	collision.reset();
	collision.position = position;
	collision.setFactor(Math::OneInt);

	// Check offset vector
	if (offset.isZero()) { return false; }

	// Check current collision
	if (collideCircle(boundingCircle))
	{
		// Currently colliding
		collision.collide = true;
		return collision.collide;
	}

	// Compute step offset
	int32_t stepOffset = Math::max(Math::min(boundingCircle.radius,
		Math::min(halfSize.vec[0], halfSize.vec[1])),
		PhysicsMinEntityHalfSize
	);
	int32_t stepX = (Math::abs(offset.vec[0]) / stepOffset);
	int32_t stepY = (Math::abs(offset.vec[1]) / stepOffset);
	int32_t step = Math::max(((stepX >= stepY) ? stepX : stepY), 1);
	stepX = (offset.vec[0] / step);
	stepY = (offset.vec[1] / step);

	// Iterative collision detection
	bool collide = false;
	BoundingAlignRect currentAlignRect(*this);
	for (int32_t i = 0; i < step; ++i)
	{
		if (currentAlignRect.collideCircle(boundingCircle))
		{
			// Collision detected
			collide = true;
			break;
		}
		else
		{
			// Next iteration
			collision.position = currentAlignRect.position;
			currentAlignRect.position.vec[0] += stepX;
			currentAlignRect.position.vec[1] += stepY;
		}
	}

	if (!collide)
	{
		// Last collision detection
		currentAlignRect.position = (position + offset);
		if (!currentAlignRect.collideCircle(boundingCircle))
		{
			// No collision detected
			collision.position = (position + offset);
			collision.offset = offset;
			collision.collide = false;
			return collision.collide;
		}
	}

	// Small steps iterative collision
	stepX >>= 1;	// stepX = stepX/2
	stepY >>= 1;	// stepY = stepY/2
	currentAlignRect.position = collision.position;
	for (int32_t i = 0; i < PhysicsMaxSmallStepsIterations; ++i)
	{
		currentAlignRect.position.vec[0] += stepX;
		currentAlignRect.position.vec[1] += stepY;
		if (currentAlignRect.collideCircle(boundingCircle))
		{
			// Rollback to previous position
			currentAlignRect.position = collision.position;
			stepX >>= 1;	// stepX = stepX/2
			stepY >>= 1;	// stepY = stepY/2
		}
		else
		{
			// Store current position
			collision.position = currentAlignRect.position;
		}
		if ((stepX == 0) && (stepY == 0)) { break; }
	}

	// Collision detected
	collision.offset = (currentAlignRect.position - position);
	collision.position = currentAlignRect.position;
	collision.normal = (collision.position - boundingCircle.position);
	collision.normal.normalize();
	collision.setFactor(static_cast<int32_t>(
		(collision.offset.length() << Math::OneIntShift) / offset.length()
	));
	collision.collide = true;
	return collision.collide;
}


////////////////////////////////////////////////////////////////////////////////
//  Collide bounding align rect with matrix chunk 2                           //
////////////////////////////////////////////////////////////////////////////////
bool BoundingAlignRect::collideMatrix2(const MatrixChunk2& matrixChunk2)
{
	// Compute start and end matrix coordinates
	int32_t startX = Math::divide(
		position.vec[0]-halfSize.vec[0], MatrixChunk2ElemWidth
	);
	int32_t endX = Math::divide(
		position.vec[0]+halfSize.vec[0], MatrixChunk2ElemWidth
	);
	int32_t startY = Math::divide(
		position.vec[1]-halfSize.vec[1], MatrixChunk2ElemHeight
	);
	int32_t endY = Math::divide(
		position.vec[1]+halfSize.vec[1], MatrixChunk2ElemHeight
	);

	// Check matrix elements
	for (int i = startX; i <= endX; ++i)
	{
		for (int j = startY; j <= endY; ++j)
		{
			// Check if align rect is colliding with matrix element
			if (matrixChunk2.isColliding(i, j)) { return true; }
		}
	}

	// No collision detected
	return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Collide bounding align rect with matrix chunk 2                           //
////////////////////////////////////////////////////////////////////////////////
bool BoundingAlignRect::collideMatrix2(const MatrixChunk2& matrixChunk2,
    const Vector2i& offset, Collision2& collision)
{
	// Reset collision
	collision.reset();
	collision.position = position;
	collision.setFactor(Math::OneInt);

	// Check offset vector
	if (offset.isZero()) { return false; }

	// Check current collision
	if (collideMatrix2(matrixChunk2))
	{
		// Currently colliding
		collision.collide = true;
		return collision.collide;
	}

	// Compute step offset
	int32_t stepOffset = Math::max(Math::min(
		Math::min(halfSize.vec[0], MatrixChunk2ElemHalfWidth),
		Math::min(halfSize.vec[1], MatrixChunk2ElemHalfHeight)),
		PhysicsMinEntityHalfSize
	);
	int32_t stepX = (Math::abs(offset.vec[0]) / stepOffset);
	int32_t stepY = (Math::abs(offset.vec[1]) / stepOffset);
	int32_t step = Math::max(((stepX >= stepY) ? stepX : stepY), 1);
	stepX = (offset.vec[0] / step);
	stepY = (offset.vec[1] / step);

	// Iterative collision detection
	bool collide = false;
	BoundingAlignRect currentAlignRect(*this);
	for (int32_t i = 0; i < step; ++i)
	{
		if (currentAlignRect.collideMatrix2(matrixChunk2))
		{
			// Collision detected
			collide = true;
			break;
		}
		else
		{
			// Next iteration
			collision.position = currentAlignRect.position;
			currentAlignRect.position.vec[0] += stepX;
			currentAlignRect.position.vec[1] += stepY;
		}
	}

	if (!collide)
	{
		// Last collision detection
		currentAlignRect.position = (position + offset);
		if (!currentAlignRect.collideMatrix2(matrixChunk2))
		{
			// No collision detected
			collision.position = (position + offset);
			collision.offset = offset;
			collision.collide = false;
			return collision.collide;
		}
	}

	// Small steps iterative collision
	stepX >>= 1;	// stepX = stepX/2
	stepY >>= 1;	// stepY = stepY/2
	currentAlignRect.position = collision.position;
	for (int32_t i = 0; i < PhysicsMaxSmallStepsIterations; ++i)
	{
		currentAlignRect.position.vec[0] += stepX;
		currentAlignRect.position.vec[1] += stepY;
		if (currentAlignRect.collideMatrix2(matrixChunk2))
		{
			// Rollback to previous position
			currentAlignRect.position = collision.position;
			stepX >>= 1;	// stepX = stepX/2
			stepY >>= 1;	// stepY = stepY/2
		}
		else
		{
			// Store current position
			collision.position = currentAlignRect.position;
		}
		if ((stepX == 0) && (stepY == 0)) { break; }
	}

	// Collision detected
	collision.offset = (currentAlignRect.position - position);
	collision.position = currentAlignRect.position;
	/*collision.normal = (collision.position - boundingAlignRect.position);
	collision.normal.normalize();*/
	collision.setFactor(static_cast<int32_t>(
		(collision.offset.length() << Math::OneIntShift) / offset.length()
	));
	collision.collide = true;
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
