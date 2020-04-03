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
    #undef              GL_LOGIC_OP_MODE
    #undef              GL_INDEX_LOGIC_OP
    #undef              GL_COLOR_LOGIC_OP
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
    #undef              GL_STENCIL_BUFFER_BIT
    #undef              GL_VIEWPORT_BIT
    #undef              GL_SRC_COLOR
    #undef              GL_ONE_MINUS_SRC_COLOR
    #undef              GL_SRC_ALPHA
    #undef              GL_ONE_MINUS_SRC_ALPHA
    #undef              GL_DST_ALPHA
    #undef              GL_ONE_MINUS_DST_ALPHA
    #undef              GL_DST_COLOR
    #undef              GL_ONE_MINUS_DST_COLOR
    #undef              GL_SRC_ALPHA_SATURATE
    #undef              GL_ALPHA_TEST
    #undef              GL_ALPHA_TEST_FUNC
    #undef              GL_ALPHA_TEST_REF
    #undef              GL_DITHER
    #undef              GL_BLEND_DST
    #undef              GL_BLEND_SRC
    #undef              GL_BLEND
    #undef              GL_FRONT_LEFT
    #undef              GL_FRONT_RIGHT
    #undef              GL_BACK_LEFT
    #undef              GL_BACK_RIGHT
    #undef              GL_FRONT
    #undef              GL_BACK
    #undef              GL_LEFT
    #undef              GL_RIGHT
    #undef              GL_FRONT_AND_BACK
    #undef              GL_AUX0
    #undef              GL_AUX1
    #undef              GL_AUX2
    #undef              GL_AUX3
    #undef              GL_INVALID_ENUM
    #undef              GL_INVALID_VALUE
    #undef              GL_INVALID_OPERATION
    #undef              GL_STACK_OVERFLOW
    #undef              GL_STACK_UNDERFLOW
    #undef              GL_OUT_OF_MEMORY
    #undef              GL_2D
    #undef              GL_3D
    #undef              GL_3D_COLOR
    #undef              GL_3D_COLOR_TEXTURE
    #undef              GL_4D_COLOR_TEXTURE
    #undef              GL_PASS_THROUGH_TOKEN
    #undef              GL_POINT_TOKEN
    #undef              GL_LINE_TOKEN
    #undef              GL_POLYGON_TOKEN
    #undef              GL_BITMAP_TOKEN
    #undef              GL_DRAW_PIXEL_TOKEN
    #undef              GL_COPY_PIXEL_TOKEN
    #undef              GL_LINE_RESET_TOKEN
    #undef              GL_EXP
    #undef              GL_EXP2
    #undef              GL_CW
    #undef              GL_CCW
    #undef              GL_CURRENT_COLOR
    #undef              GL_CURRENT_INDEX
    #undef              GL_CURRENT_NORMAL
    #undef              GL_CURRENT_TEXTURE_COORDS
    #undef              GL_CURRENT_RASTER_COLOR
    #undef              GL_CURRENT_RASTER_INDEX
    #undef              GL_CURRENT_RASTER_TEXTURE_COORDS
    #undef              GL_CURRENT_RASTER_POSITION
    #undef              GL_CURRENT_RASTER_POSITION_VALID
    #undef              GL_CURRENT_RASTER_DISTANCE
    #undef              GL_POINT_SMOOTH
    #undef              GL_POINT_SIZE
    #undef              GL_POINT_SIZE_RANGE
    #undef              GL_POINT_SIZE_GRANULARITY
    #undef              GL_LINE_SMOOTH
    #undef              GL_LINE_WIDTH
    #undef              GL_LINE_WIDTH_RANGE
    #undef              GL_LINE_WIDTH_GRANULARITY
    #undef              GL_LINE_STIPPLE
    #undef              GL_LINE_STIPPLE_PATTERN
    #undef              GL_LINE_STIPPLE_REPEAT
    #undef              GL_LIST_MODE
    #undef              GL_MAX_LIST_NESTING
    #undef              GL_LIST_BASE
    #undef              GL_LIST_INDEX
    #undef              GL_POLYGON_MODE
    #undef              GL_POLYGON_SMOOTH
    #undef              GL_POLYGON_STIPPLE
    #undef              GL_EDGE_FLAG
    #undef              GL_CULL_FACE
    #undef              GL_CULL_FACE_MODE
    #undef              GL_FRONT_FACE
    #undef              GL_SCISSOR_BOX
    #undef              GL_SCISSOR_TEST
    #undef              GL_AUX_BUFFERS
    #undef              GL_DRAW_BUFFER
    #undef              GL_READ_BUFFER
    #undef              GL_LIGHTING
    #undef              GL_LIGHT_MODEL_LOCAL_VIEWER
    #undef              GL_LIGHT_MODEL_TWO_SIDE
    #undef              GL_LIGHT_MODEL_AMBIENT
    #undef              GL_SHADE_MODEL
    #undef              GL_COLOR_MATERIAL_FACE
    #undef              GL_COLOR_MATERIAL_PARAMETER
    #undef              GL_COLOR_MATERIAL
    #undef              GL_FOG
    #undef              GL_FOG_INDEX
    #undef              GL_FOG_DENSITY
    #undef              GL_FOG_START
    #undef              GL_FOG_END
    #undef              GL_FOG_MODE
    #undef              GL_FOG_COLOR
    #undef              GL_DEPTH_RANGE
    #undef              GL_DEPTH_TEST
    #undef              GL_DEPTH_WRITEMASK
    #undef              GL_DEPTH_CLEAR_VALUE
    #undef              GL_DEPTH_FUNC
    #undef              GL_STENCIL_TEST
    #undef              GL_STENCIL_CLEAR_VALUE
    #undef              GL_STENCIL_FUNC
    #undef              GL_STENCIL_VALUE_MASK
    #undef              GL_STENCIL_FAIL
    #undef              GL_STENCIL_PASS_DEPTH_FAIL
    #undef              GL_STENCIL_PASS_DEPTH_PASS
    #undef              GL_STENCIL_REF
    #undef              GL_STENCIL_WRITEMASK
    #undef              GL_MATRIX_MODE
    #undef              GL_NORMALIZE
    #undef              GL_VIEWPORT
    #undef              GL_MODELVIEW_STACK_DEPTH
    #undef              GL_PROJECTION_STACK_DEPTH
    #undef              GL_TEXTURE_STACK_DEPTH
    #undef              GL_MODELVIEW_MATRIX
    #undef              GL_PROJECTION_MATRIX
    #undef              GL_TEXTURE_MATRIX
    #undef              GL_ATTRIB_STACK_DEPTH
    #undef              GL_CLIENT_ATTRIB_STACK_DEPTH
    

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
    #define             GL_LOGIC_OP_MODE                    0x0BF0
    #define             GL_INDEX_LOGIC_OP                   0x0BF1
    #define             GL_COLOR_LOGIC_OP                   0x0BF2
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
    //  OpenGL flags constants                                                //
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
    #define             GL_STENCIL_BUFFER_BIT               0x00000400
    #define             GL_VIEWPORT_BIT                     0x00000800

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL alpha blending constants                                       //
    ////////////////////////////////////////////////////////////////////////////
    #define             GL_SRC_COLOR                        0x0300
    #define             GL_ONE_MINUS_SRC_COLOR              0x0301
    #define             GL_SRC_ALPHA                        0x0302
    #define             GL_ONE_MINUS_SRC_ALPHA              0x0303
    #define             GL_DST_ALPHA                        0x0304
    #define             GL_ONE_MINUS_DST_ALPHA              0x0305
    #define             GL_DST_COLOR                        0x0306
    #define             GL_ONE_MINUS_DST_COLOR              0x0307
    #define             GL_SRC_ALPHA_SATURATE               0x0308
    #define             GL_ALPHA_TEST                       0x0BC0
    #define             GL_ALPHA_TEST_FUNC                  0x0BC1
    #define             GL_ALPHA_TEST_REF                   0x0BC2
    #define             GL_DITHER                           0x0BD0
    #define             GL_BLEND_DST                        0x0BE0
    #define             GL_BLEND_SRC                        0x0BE1
    #define             GL_BLEND                            0x0BE2

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL faces constants                                                //
    ////////////////////////////////////////////////////////////////////////////
    #define             GL_FRONT_LEFT                       0x0400
    #define             GL_FRONT_RIGHT                      0x0401
    #define             GL_BACK_LEFT                        0x0402
    #define             GL_BACK_RIGHT                       0x0403
    #define             GL_FRONT                            0x0404
    #define             GL_BACK                             0x0405
    #define             GL_LEFT                             0x0406
    #define             GL_RIGHT                            0x0407
    #define             GL_FRONT_AND_BACK                   0x0408
    #define             GL_AUX0                             0x0409
    #define             GL_AUX1                             0x040A
    #define             GL_AUX2                             0x040B
    #define             GL_AUX3                             0x040C

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL errors constants                                               //
    ////////////////////////////////////////////////////////////////////////////
    #define             GL_INVALID_ENUM                     0x0500
    #define             GL_INVALID_VALUE                    0x0501
    #define             GL_INVALID_OPERATION                0x0502
    #define             GL_STACK_OVERFLOW                   0x0503
    #define             GL_STACK_UNDERFLOW                  0x0504
    #define             GL_OUT_OF_MEMORY                    0x0505

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL dimensional constants                                          //
    ////////////////////////////////////////////////////////////////////////////
    #define             GL_2D                               0x0600
    #define             GL_3D                               0x0601
    #define             GL_3D_COLOR                         0x0602
    #define             GL_3D_COLOR_TEXTURE                 0x0603
    #define             GL_4D_COLOR_TEXTURE                 0x0604

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL tokens constants                                               //
    ////////////////////////////////////////////////////////////////////////////
    #define             GL_PASS_THROUGH_TOKEN               0x0700
    #define             GL_POINT_TOKEN                      0x0701
    #define             GL_LINE_TOKEN                       0x0702
    #define             GL_POLYGON_TOKEN                    0x0703
    #define             GL_BITMAP_TOKEN                     0x0704
    #define             GL_DRAW_PIXEL_TOKEN                 0x0705
    #define             GL_COPY_PIXEL_TOKEN                 0x0706
    #define             GL_LINE_RESET_TOKEN                 0x0707

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL expressions constants                                          //
    ////////////////////////////////////////////////////////////////////////////
    #define             GL_EXP                              0x0800
    #define             GL_EXP2                             0x0801

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL ordering constants                                             //
    ////////////////////////////////////////////////////////////////////////////
    #define             GL_CW                               0x0900
    #define             GL_CCW                              0x0901

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL current constants                                              //
    ////////////////////////////////////////////////////////////////////////////
    #define             GL_CURRENT_COLOR                    0x0B00
    #define             GL_CURRENT_INDEX                    0x0B01
    #define             GL_CURRENT_NORMAL                   0x0B02
    #define             GL_CURRENT_TEXTURE_COORDS           0x0B03
    #define             GL_CURRENT_RASTER_COLOR             0x0B04
    #define             GL_CURRENT_RASTER_INDEX             0x0B05
    #define             GL_CURRENT_RASTER_TEXTURE_COORDS    0x0B06
    #define             GL_CURRENT_RASTER_POSITION          0x0B07
    #define             GL_CURRENT_RASTER_POSITION_VALID    0x0B08
    #define             GL_CURRENT_RASTER_DISTANCE          0x0B09

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL points and lines constants                                     //
    ////////////////////////////////////////////////////////////////////////////
    #define             GL_POINT_SMOOTH                     0x0B10
    #define             GL_POINT_SIZE                       0x0B11
    #define             GL_POINT_SIZE_RANGE                 0x0B12
    #define             GL_POINT_SIZE_GRANULARITY           0x0B13
    #define             GL_LINE_SMOOTH                      0x0B20
    #define             GL_LINE_WIDTH                       0x0B21
    #define             GL_LINE_WIDTH_RANGE                 0x0B22
    #define             GL_LINE_WIDTH_GRANULARITY           0x0B23
    #define             GL_LINE_STIPPLE                     0x0B24
    #define             GL_LINE_STIPPLE_PATTERN             0x0B25
    #define             GL_LINE_STIPPLE_REPEAT              0x0B26

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL lists constants                                                //
    ////////////////////////////////////////////////////////////////////////////
    #define             GL_LIST_MODE                        0x0B30
    #define             GL_MAX_LIST_NESTING                 0x0B31
    #define             GL_LIST_BASE                        0x0B32
    #define             GL_LIST_INDEX                       0x0B33

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL polygons constants                                             //
    ////////////////////////////////////////////////////////////////////////////
    #define             GL_POLYGON_MODE                     0x0B40
    #define             GL_POLYGON_SMOOTH                   0x0B41
    #define             GL_POLYGON_STIPPLE                  0x0B42
    #define             GL_EDGE_FLAG                        0x0B43
    #define             GL_CULL_FACE                        0x0B44
    #define             GL_CULL_FACE_MODE                   0x0B45
    #define             GL_FRONT_FACE                       0x0B46
    #define             GL_SCISSOR_BOX                      0x0C10
    #define             GL_SCISSOR_TEST                     0x0C11

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL buffers constants                                              //
    ////////////////////////////////////////////////////////////////////////////
    #define             GL_AUX_BUFFERS                      0x0C00
    #define             GL_DRAW_BUFFER                      0x0C01
    #define             GL_READ_BUFFER                      0x0C02

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL lighting constants                                             //
    ////////////////////////////////////////////////////////////////////////////
    #define             GL_LIGHTING                         0x0B50
    #define             GL_LIGHT_MODEL_LOCAL_VIEWER         0x0B51
    #define             GL_LIGHT_MODEL_TWO_SIDE             0x0B52
    #define             GL_LIGHT_MODEL_AMBIENT              0x0B53
    #define             GL_SHADE_MODEL                      0x0B54
    #define             GL_COLOR_MATERIAL_FACE              0x0B55
    #define             GL_COLOR_MATERIAL_PARAMETER         0x0B56
    #define             GL_COLOR_MATERIAL                   0x0B57

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL fog constants                                                  //
    ////////////////////////////////////////////////////////////////////////////
    #define             GL_FOG                              0x0B60
    #define             GL_FOG_INDEX                        0x0B61
    #define             GL_FOG_DENSITY                      0x0B62
    #define             GL_FOG_START                        0x0B63
    #define             GL_FOG_END                          0x0B64
    #define             GL_FOG_MODE                         0x0B65
    #define             GL_FOG_COLOR                        0x0B66

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL depth constants                                                //
    ////////////////////////////////////////////////////////////////////////////
    #define             GL_DEPTH_RANGE                      0x0B70
    #define             GL_DEPTH_TEST                       0x0B71
    #define             GL_DEPTH_WRITEMASK                  0x0B72
    #define             GL_DEPTH_CLEAR_VALUE                0x0B73
    #define             GL_DEPTH_FUNC                       0x0B74

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL stencil constants                                              //
    ////////////////////////////////////////////////////////////////////////////
    #define             GL_STENCIL_TEST                     0x0B90
    #define             GL_STENCIL_CLEAR_VALUE              0x0B91
    #define             GL_STENCIL_FUNC                     0x0B92
    #define             GL_STENCIL_VALUE_MASK               0x0B93
    #define             GL_STENCIL_FAIL                     0x0B94
    #define             GL_STENCIL_PASS_DEPTH_FAIL          0x0B95
    #define             GL_STENCIL_PASS_DEPTH_PASS          0x0B96
    #define             GL_STENCIL_REF                      0x0B97
    #define             GL_STENCIL_WRITEMASK                0x0B98

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL matrices constants                                             //
    ////////////////////////////////////////////////////////////////////////////
    #define             GL_MATRIX_MODE                      0x0BA0
    #define             GL_NORMALIZE                        0x0BA1
    #define             GL_VIEWPORT                         0x0BA2
    #define             GL_MODELVIEW_STACK_DEPTH            0x0BA3
    #define             GL_PROJECTION_STACK_DEPTH           0x0BA4
    #define             GL_TEXTURE_STACK_DEPTH              0x0BA5
    #define             GL_MODELVIEW_MATRIX                 0x0BA6
    #define             GL_PROJECTION_MATRIX                0x0BA7
    #define             GL_TEXTURE_MATRIX                   0x0BA8

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL stack constants                                                //
    ////////////////////////////////////////////////////////////////////////////
    #define             GL_ATTRIB_STACK_DEPTH               0x0BB0
    #define             GL_CLIENT_ATTRIB_STACK_DEPTH        0x0BB1


#endif // VOS_RENDERER_OPENGL_OPENGL_HEADER
