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
BoundingCircle::BoundingCircle()
{
	center.vec[0] = 0;
	center.vec[1] = 0;
	radius = 0;
}

////////////////////////////////////////////////////////////////////////////////
//  BoundingCircle copy constructor                                           //
////////////////////////////////////////////////////////////////////////////////
BoundingCircle::BoundingCircle(const BoundingCircle& boundingCircle)
{
    center.vec[0] = boundingCircle.center.vec[0];
	center.vec[1] = boundingCircle.center.vec[1];
    radius = boundingCircle.radius;
}

////////////////////////////////////////////////////////////////////////////////
//  BoundingCircle center and radius constructor                              //
////////////////////////////////////////////////////////////////////////////////
BoundingCircle::BoundingCircle(
	const Vector2i& circleCenter, int64_t circleRadius)
{
	center.vec[0] = circleCenter.vec[0];
	center.vec[1] = circleCenter.vec[1];
	radius = circleRadius;
}

////////////////////////////////////////////////////////////////////////////////
//  BoundingCircle destructor                                                 //
////////////////////////////////////////////////////////////////////////////////
BoundingCircle::~BoundingCircle()
{
	radius = 0;
	center.vec[1] = 0;
	center.vec[0] = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Set bounding circle center and radius                                     //
////////////////////////////////////////////////////////////////////////////////
void BoundingCircle::set(const Vector2i& circleCenter, int64_t circleRadius)
{
	center.vec[0] = circleCenter.vec[0];
	center.vec[1] = circleCenter.vec[1];
	radius = circleRadius;
}

////////////////////////////////////////////////////////////////////////////////
//  Set bounding circle center                                                //
////////////////////////////////////////////////////////////////////////////////
void BoundingCircle::setCenter(const Vector2i& circleCenter)
{
	center.vec[0] = circleCenter.vec[0];
	center.vec[1] = circleCenter.vec[1];
}

////////////////////////////////////////////////////////////////////////////////
//  Set bounding circle center                                                //
////////////////////////////////////////////////////////////////////////////////
void BoundingCircle::setCenter(int64_t centerX, int64_t centerY)
{
	center.vec[0] = centerX;
	center.vec[1] = centerY;
}

////////////////////////////////////////////////////////////////////////////////
//  Set bounding circle center X position                                     //
////////////////////////////////////////////////////////////////////////////////
void BoundingCircle::setCenterX(int64_t centerX)
{
	center.vec[0] = centerX;
}

////////////////////////////////////////////////////////////////////////////////
//  Set bounding circle center Y position                                     //
////////////////////////////////////////////////////////////////////////////////
void BoundingCircle::setCenterY(int64_t centerY)
{
	center.vec[1] = centerY;
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
	Vector2i dist = (center - boundingCircle.center);
	int64_t distance = (dist.vec[0]*dist.vec[0])+(dist.vec[1]*dist.vec[1]);
	int64_t radiuses = (radius + boundingCircle.radius);
	return (distance <= (radiuses*radiuses));
}


////////////////////////////////////////////////////////////////////////////////
//  BoundingCircle affectation operator                                       //
////////////////////////////////////////////////////////////////////////////////
BoundingCircle& BoundingCircle::operator=(const BoundingCircle& boundingCircle)
{
	center.vec[0] = boundingCircle.center.vec[0];
	center.vec[1] = boundingCircle.center.vec[1];
	radius = boundingCircle.radius;
}
