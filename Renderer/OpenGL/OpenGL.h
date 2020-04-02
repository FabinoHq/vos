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
//     Renderer/OpenGL/OpenGL.h : OpenGL rendering management                 //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_OPENGL_OPENGL_HEADER
#define VOS_RENDERER_OPENGL_OPENGL_HEADER

    #include "../../OpenGL.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Clear all OpenGL constants                                            //
    ////////////////////////////////////////////////////////////////////////////
    #undef              GL_NONE
    #undef              GL_ONE
    #undef              GL_ZERO
    #undef              GL_TRUE
    #undef              GL_FALSE
    #undef              GL_NO_ERROR
    #undef              GL_LOGIC_OP
    #undef              GL_NEVER
    #undef              GL_LESS
    #undef              GL_EQUAL
    #undef              GL_LEQUAL
    #undef              GL_GREATER
    #undef              GL_NOTEQUAL
    #undef              GL_GEQUAL
    #undef              GL_ALWAYS
    #undef              GL_ACCUM
    #undef              GL_LOAD
    #undef              GL_RETURN
    #undef              GL_MULT
    #undef              GL_ADD
    #undef              GL_POINTS
    #undef              GL_LINES
    #undef              GL_LINE_LOOP
    #undef              GL_LINE_STRIP
    #undef              GL_TRIANGLES
    #undef              GL_TRIANGLE_STRIP
    #undef              GL_TRIANGLE_FAN
    #undef              GL_QUADS
    #undef              GL_QUAD_STRIP
    #undef              GL_POLYGON
    #undef              GL_TEXTURE_COMPONENTS
    #undef              GL_CURRENT_BIT
    #undef              GL_CLIENT_PIXEL_STORE_BIT
    #undef              GL_POINT_BIT
    #undef              GL_CLIENT_VERTEX_ARRAY_BIT
    #undef              GL_LINE_BIT
    #undef              GL_POLYGON_BIT
    #undef              GL_POLYGON_STIPPLE_BIT
    #undef              GL_PIXEL_MODE_BIT
    #undef              GL_LIGHTING_BIT
    #undef              GL_FOG_BIT
    #undef              GL_DEPTH_BUFFER_BIT
    #undef              GL_ACCUM_BUFFER_BIT
    

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL types definitions                                              //
    ////////////////////////////////////////////////////////////////////////////
    typedef             void                                GLvoid;
    typedef             signed char                         GLbyte;
    typedef             unsigned char                       GLubyte;
    typedef             char                                GLchar;
    typedef             unsigned char                       GLboolean;
    typedef             short                               GLshort;
    typedef             unsigned short                      GLushort;
    typedef             int                                 GLint;
    typedef             unsigned int                        GLuint;
    typedef             int                                 GLsizei;
    typedef             unsigned long                       GLulong;
    typedef             unsigned int                        GLenum;
    typedef             unsigned int                        GLbitfield;
    typedef             float                               GLfloat;
    typedef             double                              GLdouble;
    typedef             float                               GLclampf;
    typedef             double                              GLclampd;


    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL global constants                                               //
    ////////////////////////////////////////////////////////////////////////////
    #define             GL_NONE                             0
    #define             GL_ONE                              1
    #define             GL_ZERO                             0
    #define             GL_TRUE                             1
    #define             GL_FALSE                            0
    #define             GL_NO_ERROR                         0

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL logic constants                                                //
    ////////////////////////////////////////////////////////////////////////////
    #define             GL_LOGIC_OP                         0x0BF1
    #define             GL_NEVER                            0x0200
    #define             GL_LESS                             0x0201
    #define             GL_EQUAL                            0x0202
    #define             GL_LEQUAL                           0x0203
    #define             GL_GREATER                          0x0204
    #define             GL_NOTEQUAL                         0x0205
    #define             GL_GEQUAL                           0x0206
    #define             GL_ALWAYS                           0x0207

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL operators constants                                            //
    ////////////////////////////////////////////////////////////////////////////
    #define             GL_ACCUM                            0x0100
    #define             GL_LOAD                             0x0101
    #define             GL_RETURN                           0x0102
    #define             GL_MULT                             0x0103
    #define             GL_ADD                              0x0104

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL rendering constants                                            //
    ////////////////////////////////////////////////////////////////////////////
    #define             GL_POINTS                           0x0000
    #define             GL_LINES                            0x0001
    #define             GL_LINE_LOOP                        0x0002
    #define             GL_LINE_STRIP                       0x0003
    #define             GL_TRIANGLES                        0x0004
    #define             GL_TRIANGLE_STRIP                   0x0005
    #define             GL_TRIANGLE_FAN                     0x0006
    #define             GL_QUADS                            0x0007
    #define             GL_QUAD_STRIP                       0x0008
    #define             GL_POLYGON                          0x0009

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL buffers constants                                              //
    ////////////////////////////////////////////////////////////////////////////
    #define             GL_TEXTURE_COMPONENTS               0x1003
    #define             GL_CURRENT_BIT                      0x00000001
    #define             GL_CLIENT_PIXEL_STORE_BIT           0x00000001
    #define             GL_POINT_BIT                        0x00000002
    #define             GL_CLIENT_VERTEX_ARRAY_BIT          0x00000002
    #define             GL_LINE_BIT                         0x00000004
    #define             GL_POLYGON_BIT                      0x00000008
    #define             GL_POLYGON_STIPPLE_BIT              0x00000010
    #define             GL_PIXEL_MODE_BIT                   0x00000020
    #define             GL_LIGHTING_BIT                     0x00000040
    #define             GL_FOG_BIT                          0x00000080
    #define             GL_DEPTH_BUFFER_BIT                 0x00000100
    #define             GL_ACCUM_BUFFER_BIT                 0x00000200


#endif // VOS_RENDERER_OPENGL_OPENGL_HEADER
