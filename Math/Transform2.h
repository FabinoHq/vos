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
//     Math/Transform2.h : 2D transformations                                 //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_MATH_TRANSFORM2_HEADER
#define VOS_MATH_TRANSFORM2_HEADER

    #include "../System/System.h"
    #include "Math.h"
    #include "Vector2.h"
    #include "Matrix4x4.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Transform2 class definition                                           //
    ////////////////////////////////////////////////////////////////////////////
    class Transform2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Transform2 default constructor                                //
            ////////////////////////////////////////////////////////////////////
            Transform2() :
            m_matrix(),
            m_origin(0.0f, 0.0f),
            m_position(0.0f, 0.0f),
            m_size(1.0f, 1.0f),
            //m_shear(0.0f, 0.0f),
            m_angle(0.0f)
            {
                m_matrix.reset();
            }

            ////////////////////////////////////////////////////////////////////
            //  Transform2 virtual destructor                                 //
            ////////////////////////////////////////////////////////////////////
            virtual ~Transform2()
            {
                m_angle = 0.0f;
                //m_shear.reset();
                m_size.reset();
                m_position.reset();
                m_origin.reset();
                m_matrix.reset();
            }

            ////////////////////////////////////////////////////////////////////
            //  Reset transformations                                         //
            ////////////////////////////////////////////////////////////////////
            inline void resetTransforms()
            {
                m_matrix.setIdentity();
                m_origin.reset();
                m_position.reset();
                m_size.set(1.0f, 1.0f);
                //m_shear.reset();
                m_angle = 0.0f;
            }


            ////////////////////////////////////////////////////////////////////
            //  Center origin                                                 //
            ////////////////////////////////////////////////////////////////////
            inline void centerOrigin()
            {
                m_origin.vec[0] = m_size.vec[0]*0.5f;
                m_origin.vec[1] = m_size.vec[1]*0.5f;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set origin                                                    //
            ////////////////////////////////////////////////////////////////////
            inline void setOrigin(float x, float y)
            {
                m_origin.vec[0] = x;
                m_origin.vec[1] = y;
            }

            inline void setOrigin(const Vector2& origin)
            {
                m_origin.vec[0] = origin.vec[0];
                m_origin.vec[1] = origin.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Set X origin                                                  //
            ////////////////////////////////////////////////////////////////////
            inline void setOriginX(float x)
            {
                m_origin.vec[0] = x;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Y origin                                                  //
            ////////////////////////////////////////////////////////////////////
            inline void setOriginY(float y)
            {
                m_origin.vec[1] = y;
            }

            ////////////////////////////////////////////////////////////////////
            //  Translate origin                                              //
            ////////////////////////////////////////////////////////////////////
            inline void moveOrigin(float x, float y)
            {
                m_origin.vec[0] += x;
                m_origin.vec[1] += y;
            }

            inline void moveOrigin(const Vector2& vector)
            {
                m_origin.vec[0] += vector.vec[0];
                m_origin.vec[1] += vector.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Translate origin on X axis                                    //
            ////////////////////////////////////////////////////////////////////
            inline void moveOriginX(float x)
            {
                m_origin.vec[0] += x;
            }

            ////////////////////////////////////////////////////////////////////
            //  Translate origin on Y axis                                    //
            ////////////////////////////////////////////////////////////////////
            inline void moveOriginY(float y)
            {
                m_origin.vec[1] += y;
            }


            ////////////////////////////////////////////////////////////////////
            //  Set position                                                  //
            ////////////////////////////////////////////////////////////////////
            inline void setPosition(float x, float y)
            {
                m_position.vec[0] = x;
                m_position.vec[1] = y;
            }

            inline void setPosition(const Vector2& position)
            {
                m_position.vec[0] = position.vec[0];
                m_position.vec[1] = position.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Set X position                                                //
            ////////////////////////////////////////////////////////////////////
            inline void setX(float x)
            {
                m_position.vec[0] = x;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set Y position                                                //
            ////////////////////////////////////////////////////////////////////
            inline void setY(float y)
            {
                m_position.vec[1] = y;
            }

            ////////////////////////////////////////////////////////////////////
            //  Translate                                                     //
            ////////////////////////////////////////////////////////////////////
            inline void move(float x, float y)
            {
                m_position.vec[0] += x;
                m_position.vec[1] += y;
            }

            inline void move(const Vector2& vector)
            {
                m_position.vec[0] += vector.vec[0];
                m_position.vec[1] += vector.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Translate on X axis                                           //
            ////////////////////////////////////////////////////////////////////
            inline void moveX(float x)
            {
                m_position.vec[0] += x;
            }

            ////////////////////////////////////////////////////////////////////
            //  Translate on Y axis                                           //
            ////////////////////////////////////////////////////////////////////
            inline void moveY(float y)
            {
                m_position.vec[1] += y;
            }


            ////////////////////////////////////////////////////////////////////
            //  Set angle                                                     //
            ////////////////////////////////////////////////////////////////////
            inline void setAngle(float angle)
            {
                m_angle = angle;
            }

            ////////////////////////////////////////////////////////////////////
            //  Rotate                                                        //
            ////////////////////////////////////////////////////////////////////
            inline void rotate(float angle)
            {
                m_angle += angle;
            }


            ////////////////////////////////////////////////////////////////////
            //  Set size                                                      //
            ////////////////////////////////////////////////////////////////////
            inline void setSize(float width, float height)
            {
                m_size.vec[0] = width;
                m_size.vec[1] = height;
            }

            inline void setSize(const Vector2& size)
            {
                m_size.vec[0] = size.vec[0];
                m_size.vec[1] = size.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Set width                                                     //
            ////////////////////////////////////////////////////////////////////
            inline void setWidth(float width)
            {
                m_size.vec[0] = width;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set height                                                    //
            ////////////////////////////////////////////////////////////////////
            inline void setHeight(float height)
            {
                m_size.vec[1] = height;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set scale                                                     //
            ////////////////////////////////////////////////////////////////////
            inline void setScale(float scale)
            {
                m_size.vec[0] = scale;
                m_size.vec[1] = scale;
            }

            ////////////////////////////////////////////////////////////////////
            //  Scale                                                         //
            ////////////////////////////////////////////////////////////////////
            inline void scale(float scale)
            {
                m_size.vec[0] *= scale;
                m_size.vec[1] *= scale;
            }


            ////////////////////////////////////////////////////////////////////
            //  Set shear                                                     //
            ////////////////////////////////////////////////////////////////////
            /*inline void setShear(float x, float y)
            {
                m_shear.vec[0] = x;
                m_shear.vec[1] = y;
            }

            inline void setShear(const Vector2& shear)
            {
                m_shear.vec[0] = shear.vec[0];
                m_shear.vec[1] = shear.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Set shear on X axis                                           //
            ////////////////////////////////////////////////////////////////////
            inline void setShearX(float x)
            {
                m_shear.vec[0] = x;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set shear on Y axis                                           //
            ////////////////////////////////////////////////////////////////////
            inline void setShearY(float y)
            {
                m_shear.vec[1] = y;
            }

            ////////////////////////////////////////////////////////////////////
            //  Shear                                                         //
            ////////////////////////////////////////////////////////////////////
            inline void shear(float x, float y)
            {
                m_shear.vec[0] += x;
                m_shear.vec[1] += y;
            }

            inline void shear(const Vector2& shear)
            {
                m_shear.vec[0] += shear.vec[0];
                m_shear.vec[1] += shear.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Shear on X axis                                               //
            ////////////////////////////////////////////////////////////////////
            inline void shearX(float x)
            {
                m_shear.vec[0] += x;
            }

            ////////////////////////////////////////////////////////////////////
            //  Shear on Y axis                                               //
            ////////////////////////////////////////////////////////////////////
            inline void shearY(float y)
            {
                m_shear.vec[1] += y;
            }*/


            ////////////////////////////////////////////////////////////////////
            //  Get origin                                                    //
            ////////////////////////////////////////////////////////////////////
            inline Vector2 getOrigin() const
            {
                return m_origin;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get X origin                                                  //
            ////////////////////////////////////////////////////////////////////
            inline float getOriginX() const
            {
                return m_origin.vec[0];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Y origin                                                  //
            ////////////////////////////////////////////////////////////////////
            inline float getOriginY() const
            {
                return m_origin.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get position                                                  //
            ////////////////////////////////////////////////////////////////////
            inline Vector2 getPosition() const
            {
                return m_position;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get X position                                                //
            ////////////////////////////////////////////////////////////////////
            inline float getX() const
            {
                return m_position.vec[0];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get Y position                                                //
            ////////////////////////////////////////////////////////////////////
            inline float getY() const
            {
                return m_position.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get angle                                                     //
            ////////////////////////////////////////////////////////////////////
            inline float getAngle() const
            {
                return m_angle;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get size                                                      //
            ////////////////////////////////////////////////////////////////////
            inline Vector2 getSize() const
            {
                return m_size;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get width                                                     //
            ////////////////////////////////////////////////////////////////////
            inline float getWidth() const
            {
                return m_size.vec[0];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get height                                                    //
            ////////////////////////////////////////////////////////////////////
            inline float getHeight() const
            {
                return m_size.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get shear X                                                   //
            ////////////////////////////////////////////////////////////////////
            /*inline float getShearX() const
            {
                return m_shear.vec[0];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get shear Y                                                   //
            ////////////////////////////////////////////////////////////////////
            inline float getShearY() const
            {
                return m_shear.vec[1];
            }*/


            ////////////////////////////////////////////////////////////////////
            //  Compute transformations                                       //
            ////////////////////////////////////////////////////////////////////
            inline void computeTransforms()
            {
                m_matrix.setIdentity();
                m_matrix.translate(m_position);
                m_matrix.rotateZ(m_angle);
                m_matrix.translate(-m_origin);
                m_matrix.scale(m_size);
                /*m_matrix.translate(m_origin);
                m_matrix.shear(m_shear);
                m_matrix.translate(-m_origin);*/
            }


        private:
            ////////////////////////////////////////////////////////////////////
            //  Transform2 private copy constructor : Not copyable            //
            ////////////////////////////////////////////////////////////////////
            Transform2(const Transform2&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Transform2 private copy operator : Not copyable               //
            ////////////////////////////////////////////////////////////////////
            Transform2& operator=(const Transform2&) = delete;


        protected:
            Matrix4x4           m_matrix;           // Matrix
            Vector2             m_origin;           // Origin (anchor)
            Vector2             m_position;         // Position
            Vector2             m_size;             // Size
            //Vector2             m_shear;            // Shear
            float               m_angle;            // Angle
    };


#endif // VOS_MATH_TRANSFORM2_HEADER
