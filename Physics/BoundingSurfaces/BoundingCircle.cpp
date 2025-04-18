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
//     Physics/BoundingSurfaces/BoundingCircle.cpp : Bounding Circle          //
////////////////////////////////////////////////////////////////////////////////
#include "BoundingCircle.h"
#include "BoundingAlignRect.h"


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
    position = boundingCircle.position;
    radius = boundingCircle.radius;
    angle = boundingCircle.angle;
}

////////////////////////////////////////////////////////////////////////////////
//  BoundingCircle position radius and angle constructor                      //
////////////////////////////////////////////////////////////////////////////////
BoundingCircle::BoundingCircle(const Vector2i& circlePosition,
    int32_t circleRadius, int32_t circleAngle)
{
    position = circlePosition;
    radius = Math::max(circleRadius, PhysicsMinEntityHalfSize);
    angle = Math::modulo(circleAngle, Math::TwoPiInt);
}

////////////////////////////////////////////////////////////////////////////////
//  BoundingCircle destructor                                                 //
////////////////////////////////////////////////////////////////////////////////
BoundingCircle::~BoundingCircle()
{
    angle = 0;
    radius = 0;
    position.reset();
}


////////////////////////////////////////////////////////////////////////////////
//  Set bounding circle position radius and angle                             //
////////////////////////////////////////////////////////////////////////////////
void BoundingCircle::set(const Vector2i& circlePosition,
    int32_t circleRadius, int32_t circleAngle)
{
    position = circlePosition;
    radius = Math::max(circleRadius, PhysicsMinEntityHalfSize);
    angle = Math::modulo(circleAngle, Math::TwoPiInt);
}


////////////////////////////////////////////////////////////////////////////////
//  Collide bounding circle with bounding circle                              //
////////////////////////////////////////////////////////////////////////////////
bool BoundingCircle::collideCircle(const BoundingCircle& boundingCircle)
{
    // Compute distance between circles
    Vector2i dist = (position - boundingCircle.position);

    // Compute radiuses sum
    int64_t radiuses = (
        static_cast<int64_t>(radius)+
        static_cast<int64_t>(boundingCircle.radius)
    );

    // Check if circles are colliding
    return (dist.squaredLength() <= (radiuses*radiuses));
}

////////////////////////////////////////////////////////////////////////////////
//  Collide bounding circle with bounding circle                              //
////////////////////////////////////////////////////////////////////////////////
bool BoundingCircle::collideCircle(const BoundingCircle& boundingCircle,
    const Vector2i& offset, Collision2& collision)
{
    // Reset collision
    collision.reset();
    collision.position = position;
    collision.length = offset.squaredLength();

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
    int32_t stepOffset = Math::max(
        Math::min(radius, boundingCircle.radius), PhysicsMinEntityHalfSize
    );
    int32_t stepX = (Math::abs(offset.vec[0]) / stepOffset);
    int32_t stepY = (Math::abs(offset.vec[1]) / stepOffset);
    int32_t step = Math::max(((stepX >= stepY) ? stepX : stepY), 1);
    stepX = (offset.vec[0] / step);
    stepY = (offset.vec[1] / step);

    // Iterative collision detection
    bool collide = false;
    BoundingCircle currentCircle(*this);
    for (int32_t i = 0; i < step; ++i)
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
            collision.position = currentCircle.position;
            currentCircle.position.vec[0] += stepX;
            currentCircle.position.vec[1] += stepY;
        }
    }

    if (!collide)
    {
        // Last collision detection
        currentCircle.position = (position + offset);
        if (!currentCircle.collideCircle(boundingCircle))
        {
            // No collision detected
            collision.position = (position + offset);
            collision.offset = offset;
            collision.collide = false;
            return collision.collide;
        }
    }

    // Small steps iterative collision
    stepX >>= 1;    // stepX = stepX/2
    stepY >>= 1;    // stepY = stepY/2
    currentCircle.position = collision.position;
    for (int32_t i = 0; i < PhysicsMaxSmallStepsIterations; ++i)
    {
        currentCircle.position.vec[0] += stepX;
        currentCircle.position.vec[1] += stepY;
        if (currentCircle.collideCircle(boundingCircle))
        {
            // Rollback to previous position
            currentCircle.position = collision.position;
            stepX >>= 1;    // stepX = stepX/2
            stepY >>= 1;    // stepY = stepY/2
        }
        else
        {
            // Store current position
            collision.position = currentCircle.position;
        }
        if ((stepX == 0) && (stepY == 0)) { break; }
    }

    // Collision detected
    collision.offset = (currentCircle.position - position);
    collision.offset.clampAbs(offset);
    collision.position = (position + collision.offset);
    /*collision.normal = (collision.position - boundingCircle.position);
    collision.normal.normalize();*/
    collision.length = collision.offset.squaredLength();
    collision.collide = true;
    return collision.collide;
}

////////////////////////////////////////////////////////////////////////////////
//  Move bounding circle against bounding circle                              //
////////////////////////////////////////////////////////////////////////////////
bool BoundingCircle::moveCircle(const BoundingCircle& boundingCircle,
    const Vector2i& offset, Collision2& collision)
{
    // Compute both axis simultaneously
    Collision2 currentCollision;
    Vector2i currentPosition = position;
    Vector2i remaining = offset;
    int64_t currentLen = offset.squaredLength();
    if (collideCircle(boundingCircle, offset, currentCollision))
    {
        // Compute separated X axis
        currentLen = Math::min(currentLen, currentCollision.length);
        remaining = (offset - currentCollision.offset);
        position = currentCollision.position;
        if (collideCircle(boundingCircle,
            Vector2i(remaining.vec[0], 0), currentCollision))
        {
            // Compute separated Y axis
            currentLen = Math::min(currentLen, currentCollision.length);
            position = currentCollision.position;
            collideCircle(boundingCircle,
                Vector2i(0, remaining.vec[1]), currentCollision
            );
        }
        position = currentPosition;
    }
    currentLen = Math::min(currentLen, currentCollision.length);

    // Update collision if length is less than stored length
    if (currentLen <= collision.length) { collision = currentCollision; }
    return collision.collide;
}


////////////////////////////////////////////////////////////////////////////////
//  Collide bounding circle with bounding align rect                          //
////////////////////////////////////////////////////////////////////////////////
bool BoundingCircle::collideAlignRect(
    const BoundingAlignRect& boundingAlignRect)
{
    // Compute clamped distance between circle and align rect
    Vector2i dist = (position - boundingAlignRect.position);
    dist.clamp(
        -boundingAlignRect.halfSize.vec[0], -boundingAlignRect.halfSize.vec[1],
        boundingAlignRect.halfSize.vec[0], boundingAlignRect.halfSize.vec[1]
    );

    // Compute distance between circle and closest align rect point
    dist = (position - (boundingAlignRect.position + dist));

    // Check if circle is colliding with align rect
    return (dist.squaredLength() <= getSquaredRadius());
}

////////////////////////////////////////////////////////////////////////////////
//  Collide bounding circle with bounding align rect                          //
////////////////////////////////////////////////////////////////////////////////
bool BoundingCircle::collideAlignRect(
    const BoundingAlignRect& boundingAlignRect,
    const Vector2i& offset, Collision2& collision)
{
    // Reset collision
    collision.reset();
    collision.position = position;
    collision.length = offset.squaredLength();

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
    int32_t stepOffset = Math::max(Math::min(radius, Math::min(
        boundingAlignRect.halfSize.vec[0], boundingAlignRect.halfSize.vec[1])),
        PhysicsMinEntityHalfSize
    );
    int32_t stepX = (Math::abs(offset.vec[0]) / stepOffset);
    int32_t stepY = (Math::abs(offset.vec[1]) / stepOffset);
    int32_t step = Math::max(((stepX >= stepY) ? stepX : stepY), 1);
    stepX = (offset.vec[0] / step);
    stepY = (offset.vec[1] / step);

    // Iterative collision detection
    bool collide = false;
    BoundingCircle currentCircle(*this);
    for (int32_t i = 0; i < step; ++i)
    {
        if (currentCircle.collideAlignRect(boundingAlignRect))
        {
            // Collision detected
            collide = true;
            break;
        }
        else
        {
            // Next iteration
            collision.position = currentCircle.position;
            currentCircle.position.vec[0] += stepX;
            currentCircle.position.vec[1] += stepY;
        }
    }

    if (!collide)
    {
        // Last collision detection
        currentCircle.position = (position + offset);
        if (!currentCircle.collideAlignRect(boundingAlignRect))
        {
            // No collision detected
            collision.position = (position + offset);
            collision.offset = offset;
            collision.collide = false;
            return collision.collide;
        }
    }

    // Small steps iterative collision
    stepX >>= 1;    // stepX = stepX/2
    stepY >>= 1;    // stepY = stepY/2
    currentCircle.position = collision.position;
    for (int32_t i = 0; i < PhysicsMaxSmallStepsIterations; ++i)
    {
        currentCircle.position.vec[0] += stepX;
        currentCircle.position.vec[1] += stepY;
        if (currentCircle.collideAlignRect(boundingAlignRect))
        {
            // Rollback to previous position
            currentCircle.position = collision.position;
            stepX >>= 1;    // stepX = stepX/2
            stepY >>= 1;    // stepY = stepY/2
        }
        else
        {
            // Store current position
            collision.position = currentCircle.position;
        }
        if ((stepX == 0) && (stepY == 0)) { break; }
    }

    // Collision detected
    collision.offset = (currentCircle.position - position);
    collision.offset.clampAbs(offset);
    collision.position = (position + collision.offset);
    /*collision.normal = (collision.position - boundingAlignRect.position);
    collision.normal.normalize();*/
    collision.length = collision.offset.squaredLength();
    collision.collide = true;
    return collision.collide;
}

////////////////////////////////////////////////////////////////////////////////
//  Move bounding circle against bounding align rect                          //
////////////////////////////////////////////////////////////////////////////////
bool BoundingCircle::moveAlignRect(
    const BoundingAlignRect& boundingAlignRect,
    const Vector2i& offset, Collision2& collision)
{
    // Compute both axis simultaneously
    Collision2 currentCollision;
    Vector2i currentPosition = position;
    Vector2i remaining = offset;
    int64_t currentLen = offset.squaredLength();
    if (collideAlignRect(boundingAlignRect, offset, currentCollision))
    {
        // Compute separated X axis
        currentLen = Math::min(currentLen, currentCollision.length);
        remaining = (offset - currentCollision.offset);
        position = currentCollision.position;
        if (collideAlignRect(boundingAlignRect,
            Vector2i(remaining.vec[0], 0), currentCollision))
        {
            // Compute separated Y axis
            currentLen = Math::min(currentLen, currentCollision.length);
            position = currentCollision.position;
            collideAlignRect(boundingAlignRect,
                Vector2i(0, remaining.vec[1]), currentCollision
            );
        }
        position = currentPosition;
    }
    currentLen = Math::min(currentLen, currentCollision.length);

    // Update collision if length is less than stored length
    if (currentLen <= collision.length) { collision = currentCollision; }
    return collision.collide;
}


////////////////////////////////////////////////////////////////////////////////
//  Collide bounding circle with matrix stream 2                              //
////////////////////////////////////////////////////////////////////////////////
bool BoundingCircle::collideMatrix2()
{
    // Compute start and end matrix coordinates
    int32_t startX = Math::divide(
        position.vec[0]-radius, MatrixChunk2ElemWidth
    );
    int32_t endX = Math::divide(
        position.vec[0]+radius, MatrixChunk2ElemWidth
    );
    int32_t startY = Math::divide(
        position.vec[1]-radius, MatrixChunk2ElemHeight
    );
    int32_t endY = Math::divide(
        position.vec[1]+radius, MatrixChunk2ElemHeight
    );

    // Check matrix elements
    Vector2i elem = Vector2i(0, 0);
    Vector2i dist = Vector2i(0, 0);
    int64_t squaredRadius = getSquaredRadius();
    for (int i = startX; i <= endX; ++i)
    {
        for (int j = startY; j <= endY; ++j)
        {
            if (GMatrixStream2.get(i, j) != 0)
            {
                // Compute clamped distance between circle and matrix element
                elem = Vector2i(
                    ((i*MatrixChunk2ElemWidth) + MatrixChunk2ElemHalfWidth),
                    ((j*MatrixChunk2ElemHeight) + MatrixChunk2ElemHalfHeight)
                );
                dist = (position - elem);
                dist.clamp(
                    -MatrixChunk2ElemHalfWidth, -MatrixChunk2ElemHalfHeight,
                    MatrixChunk2ElemHalfWidth, MatrixChunk2ElemHalfHeight
                );

                // Compute distance between circle and closest element point
                dist = (position - (elem + dist));

                // Check if circle is colliding with matrix element
                if (dist.squaredLength() <= squaredRadius) { return true; }
            }
        }
    }

    // No collision detected
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Collide bounding circle with matrix stream 2                              //
////////////////////////////////////////////////////////////////////////////////
bool BoundingCircle::collideMatrix2(
    const Vector2i& offset, Collision2& collision)
{
    // Reset collision
    collision.reset();
    collision.position = position;
    collision.length = offset.squaredLength();

    // Check offset vector
    if (offset.isZero()) { return false; }

    // Check current collision
    if (collideMatrix2())
    {
        // Currently colliding
        collision.collide = true;
        return collision.collide;
    }

    // Compute step offset
    int32_t stepOffset = Math::max(Math::min(radius,
        Math::min(MatrixChunk2ElemHalfWidth, MatrixChunk2ElemHalfHeight)),
        PhysicsMinEntityHalfSize
    );
    int32_t stepX = (Math::abs(offset.vec[0]) / stepOffset);
    int32_t stepY = (Math::abs(offset.vec[1]) / stepOffset);
    int32_t step = Math::max(((stepX >= stepY) ? stepX : stepY), 1);
    stepX = (offset.vec[0] / step);
    stepY = (offset.vec[1] / step);

    // Iterative collision detection
    bool collide = false;
    BoundingCircle currentCircle(*this);
    for (int32_t i = 0; i < step; ++i)
    {
        if (currentCircle.collideMatrix2())
        {
            // Collision detected
            collide = true;
            break;
        }
        else
        {
            // Next iteration
            collision.position = currentCircle.position;
            currentCircle.position.vec[0] += stepX;
            currentCircle.position.vec[1] += stepY;
        }
    }

    if (!collide)
    {
        // Last collision detection
        currentCircle.position = (position + offset);
        if (!currentCircle.collideMatrix2())
        {
            // No collision detected
            collision.position = (position + offset);
            collision.offset = offset;
            collision.collide = false;
            return collision.collide;
        }
    }

    // Small steps iterative collision
    stepX >>= 1;    // stepX = stepX/2
    stepY >>= 1;    // stepY = stepY/2
    currentCircle.position = collision.position;
    for (int32_t i = 0; i < PhysicsMaxSmallStepsIterations; ++i)
    {
        currentCircle.position.vec[0] += stepX;
        currentCircle.position.vec[1] += stepY;
        if (currentCircle.collideMatrix2())
        {
            // Rollback to previous position
            currentCircle.position = collision.position;
            stepX >>= 1;    // stepX = stepX/2
            stepY >>= 1;    // stepY = stepY/2
        }
        else
        {
            // Store current position
            collision.position = currentCircle.position;
        }
        if ((stepX == 0) && (stepY == 0)) { break; }
    }

    // Collision detected
    collision.offset = (currentCircle.position - position);
    collision.offset.clampAbs(offset);
    collision.position = (position + collision.offset);
    /*collision.normal = (collision.position - matrixElement.position);
    collision.normal.normalize();*/
    collision.length = collision.offset.squaredLength();
    collision.collide = true;
    return collision.collide;
}

////////////////////////////////////////////////////////////////////////////////
//  Move bounding circle against matrix stream 2                              //
////////////////////////////////////////////////////////////////////////////////
bool BoundingCircle::moveMatrix2(const Vector2i& offset, Collision2& collision)
{
    // Compute both axis simultaneously
    Collision2 currentCollision;
    Vector2i currentPosition = position;
    Vector2i remaining = offset;
    int64_t currentLen = offset.squaredLength();
    if (collideMatrix2(offset, currentCollision))
    {
        // Compute separated X axis
        currentLen = Math::min(currentLen, currentCollision.length);
        remaining = (offset - currentCollision.offset);
        position = currentCollision.position;
        if (collideMatrix2(Vector2i(remaining.vec[0], 0), currentCollision))
        {
            // Compute separated Y axis
            currentLen = Math::min(currentLen, currentCollision.length);
            position = currentCollision.position;
            collideMatrix2(Vector2i(0, remaining.vec[1]), currentCollision);
        }
        position = currentPosition;
    }
    currentLen = Math::min(currentLen, currentCollision.length);

    // Update collision if length is less than stored length
    if (currentLen <= collision.length) { collision = currentCollision; }
    return collision.collide;
}


////////////////////////////////////////////////////////////////////////////////
//  BoundingCircle affectation operator                                       //
////////////////////////////////////////////////////////////////////////////////
BoundingCircle& BoundingCircle::operator=(const BoundingCircle& boundingCircle)
{
    position = boundingCircle.position;
    radius = boundingCircle.radius;
    angle = boundingCircle.angle;
    return *this;
}
