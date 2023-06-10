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
//     Math/Transform3.h : 3D transformations                                 //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_MATH_TRANSFORM3_HEADER
#define VOS_MATH_TRANSFORM3_HEADER

    #include "../System/System.h"
    #include "Math.h"
    #include "Vector3.h"
    #include "Matrix4x4.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Transform3 class definition                                           //
    ////////////////////////////////////////////////////////////////////////////
    class Transform3
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Transform3 default constructor                                //
            ////////////////////////////////////////////////////////////////////
            Transform3() :
            m_matrix(),
            m_origin(0.0f, 0.0f, 0.0f),
            m_position(0.0f, 0.0f, 0.0f),
            m_size(1.0f, 1.0f, 1.0f),
            m_angles(0.0f, 0.0f, 0.0f)
            {
                m_matrix.reset();
            }

            ////////////////////////////////////////////////////////////////////
            //  Transform3 virtual destructor                                 //
            ////////////////////////////////////////////////////////////////////
            virtual ~Transform3()
            {
                m_angles.reset();
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
                m_size.set(1.0f, 1.0f, 1.0f);
                m_angles.reset();
            }


            ////////////////////////////////////////////////////////////////////
            //  Set origin                                                    //
            ////////////////////////////////////////////////////////////////////
            inline void setOrigin(float x, float y, float z)
            {
                m_origin.vec[0] = x;
                m_origin.vec[1] = y;
                m_origin.vec[2] = z;
            }

            inline void setOrigin(const Vector3& origin)
            {
                m_origin.vec[0] = origin.vec[0];
                m_origin.vec[1] = origin.vec[1];
                m_origin.vec[2] = origin.vec[2];
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
            //  Set Z origin                                                  //
            ////////////////////////////////////////////////////////////////////
            inline void setOriginZ(float z)
            {
                m_origin.vec[2] = z;
            }

            ////////////////////////////////////////////////////////////////////
            //  Translate origin                                              //
            ////////////////////////////////////////////////////////////////////
            inline void moveOrigin(float x, float y, float z)
            {
                m_origin.vec[0] += x;
                m_origin.vec[1] += y;
                m_origin.vec[2] += z;
            }

            inline void moveOrigin(const Vector3& vector)
            {
                m_origin.vec[0] += vector.vec[0];
                m_origin.vec[1] += vector.vec[1];
                m_origin.vec[2] += vector.vec[2];
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
            //  Translate origin on Z axis                                    //
            ////////////////////////////////////////////////////////////////////
            inline void moveOriginZ(float z)
            {
                m_origin.vec[2] += z;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set position                                                  //
            ////////////////////////////////////////////////////////////////////
            inline void setPosition(float x, float y, float z)
            {
                m_position.vec[0] = x;
                m_position.vec[1] = y;
                m_position.vec[2] = z;
            }

            inline void setPosition(const Vector3& position)
            {
                m_position.vec[0] = position.vec[0];
                m_position.vec[1] = position.vec[1];
                m_position.vec[2] = position.vec[2];
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
            //  Set Z position                                                //
            ////////////////////////////////////////////////////////////////////
            inline void setZ(float z)
            {
                m_position.vec[2] = z;
            }

            ////////////////////////////////////////////////////////////////////
            //  Translate                                                     //
            ////////////////////////////////////////////////////////////////////
            inline void move(float x, float y, float z)
            {
                m_position.vec[0] += x;
                m_position.vec[1] += y;
                m_position.vec[2] += z;
            }

            inline void move(const Vector3& vector)
            {
                m_position.vec[0] += vector.vec[0];
                m_position.vec[1] += vector.vec[1];
                m_position.vec[2] += vector.vec[2];
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
            //  Translate on Z axis                                           //
            ////////////////////////////////////////////////////////////////////
            inline void moveZ(float z)
            {
                m_position.vec[2] += z;
            }


            ////////////////////////////////////////////////////////////////////
            //  Set angles                                                    //
            ////////////////////////////////////////////////////////////////////
            inline void setAngles(float angleX, float angleY, float angleZ)
            {
                m_angles.vec[0] = angleX;
                m_angles.vec[1] = angleY;
                m_angles.vec[2] = angleZ;
            }

            inline void setAngles(const Vector3& angles)
            {
                m_angles.vec[0] = angles.vec[0];
                m_angles.vec[1] = angles.vec[1];
                m_angles.vec[2] = angles.vec[2];
            }

            ////////////////////////////////////////////////////////////////////
            //  Set angle X                                                   //
            ////////////////////////////////////////////////////////////////////
            inline void setAngleX(float angleX)
            {
                m_angles.vec[0] = angleX;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set angle Y                                                   //
            ////////////////////////////////////////////////////////////////////
            inline void setAngleY(float angleY)
            {
                m_angles.vec[1] = angleY;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set angle Z                                                   //
            ////////////////////////////////////////////////////////////////////
            inline void setAngleZ(float angleZ)
            {
                m_angles.vec[2] = angleZ;
            }

            ////////////////////////////////////////////////////////////////////
            //  Rotate                                                        //
            ////////////////////////////////////////////////////////////////////
            inline void rotate(float angleX, float angleY, float angleZ)
            {
                m_angles.vec[0] += angleX;
                m_angles.vec[1] += angleY;
                m_angles.vec[2] += angleZ;
            }

            inline void rotate(const Vector3& angles)
            {
                m_angles.vec[0] += angles.vec[0];
                m_angles.vec[1] += angles.vec[1];
                m_angles.vec[2] += angles.vec[2];
            }

            ////////////////////////////////////////////////////////////////////
            //  Rotate X                                                      //
            ////////////////////////////////////////////////////////////////////
            inline void rotateX(float angleX)
            {
                m_angles.vec[0] += angleX;
            }

            ////////////////////////////////////////////////////////////////////
            //  Rotate Y                                                      //
            ////////////////////////////////////////////////////////////////////
            inline void rotateY(float angleY)
            {
                m_angles.vec[1] += angleY;
            }

            ////////////////////////////////////////////////////////////////////
            //  Rotate Z                                                      //
            ////////////////////////////////////////////////////////////////////
            inline void rotateZ(float angleZ)
            {
                m_angles.vec[2] += angleZ;
            }


            ////////////////////////////////////////////////////////////////////
            //  Set size                                                      //
            ////////////////////////////////////////////////////////////////////
            inline void setSize(float width, float height, float depth)
            {
                m_size.vec[0] = width;
                m_size.vec[1] = height;
                m_size.vec[2] = depth;
            }

            inline void setSize(const Vector3& size)
            {
                m_size.vec[0] = size.vec[0];
                m_size.vec[1] = size.vec[1];
                m_size.vec[2] = size.vec[2];
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
            //  Set depth                                                     //
            ////////////////////////////////////////////////////////////////////
            inline void setDepth(float depth)
            {
                m_size.vec[2] = depth;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set scale                                                     //
            ////////////////////////////////////////////////////////////////////
            inline void setScale(float scale)
            {
                m_size.vec[0] = scale;
                m_size.vec[1] = scale;
                m_size.vec[2] = scale;
            }

            ////////////////////////////////////////////////////////////////////
            //  Scale                                                         //
            ////////////////////////////////////////////////////////////////////
            inline void scale(float scale)
            {
                m_size.vec[0] *= scale;
                m_size.vec[1] *= scale;
                m_size.vec[2] *= scale;
            }


            ////////////////////////////////////////////////////////////////////
            //  Get origin                                                    //
            ////////////////////////////////////////////////////////////////////
            inline Vector3 getOrigin() const
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
            //  Get Z origin                                                  //
            ////////////////////////////////////////////////////////////////////
            inline float getOriginZ() const
            {
                return m_origin.vec[2];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get position                                                  //
            ////////////////////////////////////////////////////////////////////
            inline Vector3 getPosition() const
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
            //  Get Z position                                                //
            ////////////////////////////////////////////////////////////////////
            inline float getZ() const
            {
                return m_position.vec[2];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get angles                                                    //
            ////////////////////////////////////////////////////////////////////
            inline Vector3 getAngles() const
            {
                return m_angles;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get angle X                                                   //
            ////////////////////////////////////////////////////////////////////
            inline float getAngleX() const
            {
                return m_angles.vec[0];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get angle Y                                                   //
            ////////////////////////////////////////////////////////////////////
            inline float getAngleY() const
            {
                return m_angles.vec[1];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get angle Z                                                   //
            ////////////////////////////////////////////////////////////////////
            inline float getAngleZ() const
            {
                return m_angles.vec[2];
            }

            ////////////////////////////////////////////////////////////////////
            //  Get size                                                      //
            ////////////////////////////////////////////////////////////////////
            inline Vector3 getSize() const
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
            //  Get depth                                                     //
            ////////////////////////////////////////////////////////////////////
            inline float getDepth() const
            {
                return m_size.vec[2];
            }


            ////////////////////////////////////////////////////////////////////
            //  Compute transformations                                       //
            ////////////////////////////////////////////////////////////////////
            inline void computeTransforms()
            {
                m_matrix.setIdentity();
                m_matrix.translate(m_position);
                m_matrix.rotate(m_angles);
                m_matrix.translate(-m_origin);
                m_matrix.scale(m_size);
            }


        private:
            ////////////////////////////////////////////////////////////////////
            //  Transform3 private copy constructor : Not copyable            //
            ////////////////////////////////////////////////////////////////////
            Transform3(const Transform3&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Transform3 private copy operator : Not copyable               //
            ////////////////////////////////////////////////////////////////////
            Transform3& operator=(const Transform3&) = delete;


        protected:
            Matrix4x4           m_matrix;           // Matrix
            Vector3             m_origin;           // Origin (anchor)
            Vector3             m_position;         // Position
            Vector3             m_size;             // Size
            Vector3             m_angles;           // Angles
    };


#endif // VOS_MATH_TRANSFORM3_HEADER
