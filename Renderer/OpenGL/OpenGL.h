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
    //  VOS OpenGL version                                                    //
    ////////////////////////////////////////////////////////////////////////////
    extern int VOSOpenGLMajorVersion;
    extern int VOSOpenGLMinorVersion;


    ////////////////////////////////////////////////////////////////////////////
    //  Clear all OpenGL constants                                            //
    ////////////////////////////////////////////////////////////////////////////
    #undef  GL_NONE
    #undef  GL_ONE
    #undef  GL_ZERO
    #undef  GL_TRUE
    #undef  GL_FALSE
    #undef  GL_NO_ERROR
    #undef  GL_EXP
    #undef  GL_EXP2
    #undef  GL_CW
    #undef  GL_CCW
    #undef  GL_COEFF
    #undef  GL_ORDER
    #undef  GL_DOMAIN
    #undef  GL_BYTE
    #undef  GL_UNSIGNED_BYTE
    #undef  GL_SHORT
    #undef  GL_UNSIGNED_SHORT
    #undef  GL_INT
    #undef  GL_UNSIGNED_INT
    #undef  GL_FLOAT
    #undef  GL_2_BYTES
    #undef  GL_3_BYTES
    #undef  GL_4_BYTES
    #undef  GL_DOUBLE
    #undef  GL_UNSIGNED_BYTE_3_3_2
    #undef  GL_UNSIGNED_SHORT_4_4_4_4
    #undef  GL_UNSIGNED_SHORT_5_5_5_1
    #undef  GL_UNSIGNED_INT_8_8_8_8
    #undef  GL_UNSIGNED_INT_10_10_10_2
    #undef  GL_UNSIGNED_BYTE_2_3_3_REV
    #undef  GL_UNSIGNED_SHORT_5_6_5
    #undef  GL_UNSIGNED_SHORT_5_6_5_REV
    #undef  GL_UNSIGNED_SHORT_4_4_4_4_REV
    #undef  GL_UNSIGNED_SHORT_1_5_5_5_REV
    #undef  GL_UNSIGNED_INT_8_8_8_8_REV
    #undef  GL_CLEAR
    #undef  GL_AND
    #undef  GL_AND_REVERSE
    #undef  GL_COPY
    #undef  GL_AND_INVERTED
    #undef  GL_NOOP
    #undef  GL_XOR
    #undef  GL_OR
    #undef  GL_NOR
    #undef  GL_EQUIV
    #undef  GL_INVERT
    #undef  GL_OR_REVERSE
    #undef  GL_COPY_INVERTED
    #undef  GL_OR_INVERTED
    #undef  GL_NAND
    #undef  GL_SET
    #undef  GL_EMISSION
    #undef  GL_SHININESS
    #undef  GL_AMBIENT_AND_DIFFUSE
    #undef  GL_COLOR_INDEXES
    #undef  GL_MODELVIEW
    #undef  GL_PROJECTION
    #undef  GL_TEXTURE
    #undef  GL_COLOR
    #undef  GL_DEPTH
    #undef  GL_STENCIL
    #undef  GL_COLOR_INDEX
    #undef  GL_STENCIL_INDEX
    #undef  GL_DEPTH_COMPONENT
    #undef  GL_RED
    #undef  GL_GREEN
    #undef  GL_BLUE
    #undef  GL_ALPHA
    #undef  GL_RGB
    #undef  GL_RGBA
    #undef  GL_LUMINANCE
    #undef  GL_LUMINANCE_ALPHA
    #undef  GL_BITMAP
    #undef  GL_POINT
    #undef  GL_LINE
    #undef  GL_FILL
    #undef  GL_RENDER
    #undef  GL_FEEDBACK
    #undef  GL_SELECT
    #undef  GL_FLAT
    #undef  GL_SMOOTH
    #undef  GL_KEEP
    #undef  GL_REPLACE
    #undef  GL_INCR
    #undef  GL_DECR
    #undef  GL_VENDOR
    #undef  GL_RENDERER
    #undef  GL_VERSION
    #undef  GL_EXTENSIONS
    #undef  GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT
    #undef  GL_MAJOR_VERSION
    #undef  GL_MINOR_VERSION
    #undef  GL_NUM_EXTENSIONS
    #undef  GL_CONTEXT_FLAGS
    #undef  GL_INDEX
    #undef  GL_UNSIGNED_INT_24_8
    #undef  GL_UNSIGNED_NORMALIZED
    #undef  GL_SRGB
    #undef  GL_LOGIC_OP
    #undef  GL_LOGIC_OP_MODE
    #undef  GL_INDEX_LOGIC_OP
    #undef  GL_COLOR_LOGIC_OP
    #undef  GL_NEVER
    #undef  GL_LESS
    #undef  GL_EQUAL
    #undef  GL_LEQUAL
    #undef  GL_GREATER
    #undef  GL_NOTEQUAL
    #undef  GL_GEQUAL
    #undef  GL_ALWAYS
    #undef  GL_ACCUM
    #undef  GL_LOAD
    #undef  GL_RETURN
    #undef  GL_MULT
    #undef  GL_ADD
    #undef  GL_SUBTRACT
    #undef  GL_POINTS
    #undef  GL_LINES
    #undef  GL_LINE_LOOP
    #undef  GL_LINE_STRIP
    #undef  GL_TRIANGLES
    #undef  GL_TRIANGLE_STRIP
    #undef  GL_TRIANGLE_FAN
    #undef  GL_QUADS
    #undef  GL_QUAD_STRIP
    #undef  GL_POLYGON
    #undef  GL_DONT_CARE
    #undef  GL_FASTEST
    #undef  GL_NICEST
    #undef  GL_AMBIENT
    #undef  GL_DIFFUSE
    #undef  GL_SPECULAR
    #undef  GL_POSITION
    #undef  GL_SPOT_DIRECTION
    #undef  GL_SPOT_EXPONENT
    #undef  GL_SPOT_CUTOFF
    #undef  GL_CONSTANT_ATTENUATION
    #undef  GL_LINEAR_ATTENUATION
    #undef  GL_QUADRATIC_ATTENUATION
    #undef  GL_QUERY_WAIT
    #undef  GL_QUERY_NO_WAIT
    #undef  GL_QUERY_BY_REGION_WAIT
    #undef  GL_QUERY_BY_REGION_NO_WAIT
    #undef  GL_ATTRIB_STACK_DEPTH
    #undef  GL_CLIENT_ATTRIB_STACK_DEPTH
    #undef  GL_INDEX_MODE
    #undef  GL_RGBA_MODE
    #undef  GL_RENDER_MODE
    #undef  GL_PERSPECTIVE_CORRECTION_HINT
    #undef  GL_POINT_SMOOTH_HINT
    #undef  GL_LINE_SMOOTH_HINT
    #undef  GL_POLYGON_SMOOTH_HINT
    #undef  GL_FOG_HINT
    #undef  GL_CURRENT_BIT
    #undef  GL_CLIENT_PIXEL_STORE_BIT
    #undef  GL_POINT_BIT
    #undef  GL_CLIENT_VERTEX_ARRAY_BIT
    #undef  GL_LINE_BIT
    #undef  GL_POLYGON_BIT
    #undef  GL_POLYGON_STIPPLE_BIT
    #undef  GL_PIXEL_MODE_BIT
    #undef  GL_LIGHTING_BIT
    #undef  GL_FOG_BIT
    #undef  GL_DEPTH_BUFFER_BIT
    #undef  GL_ACCUM_BUFFER_BIT
    #undef  GL_STENCIL_BUFFER_BIT
    #undef  GL_VIEWPORT_BIT
    #undef  GL_TRANSFORM_BIT
    #undef  GL_ENABLE_BIT
    #undef  GL_COLOR_BUFFER_BIT
    #undef  GL_HINT_BIT
    #undef  GL_EVAL_BIT
    #undef  GL_LIST_BIT
    #undef  GL_TEXTURE_BIT
    #undef  GL_SCISSOR_BIT
    #undef  GL_MULTISAMPLE_BIT
    #undef  GL_ALL_ATTRIB_BITS
    #undef  GL_CLIENT_ALL_ATTRIB_BITS
    #undef  GL_SRC_COLOR
    #undef  GL_ONE_MINUS_SRC_COLOR
    #undef  GL_SRC_ALPHA
    #undef  GL_ONE_MINUS_SRC_ALPHA
    #undef  GL_DST_ALPHA
    #undef  GL_ONE_MINUS_DST_ALPHA
    #undef  GL_DST_COLOR
    #undef  GL_ONE_MINUS_DST_COLOR
    #undef  GL_SRC_ALPHA_SATURATE
    #undef  GL_ALPHA_TEST
    #undef  GL_ALPHA_TEST_FUNC
    #undef  GL_ALPHA_TEST_REF
    #undef  GL_DITHER
    #undef  GL_BLEND_DST
    #undef  GL_BLEND_SRC
    #undef  GL_BLEND
    #undef  GL_BLEND_DST_RGB
    #undef  GL_BLEND_SRC_RGB
    #undef  GL_BLEND_DST_ALPHA
    #undef  GL_BLEND_SRC_ALPHA
    #undef  GL_BLEND_EQUATION_RGB
    #undef  GL_BLEND_EQUATION_ALPHA
    #undef  GL_FRONT_LEFT
    #undef  GL_FRONT_RIGHT
    #undef  GL_BACK_LEFT
    #undef  GL_BACK_RIGHT
    #undef  GL_FRONT
    #undef  GL_BACK
    #undef  GL_LEFT
    #undef  GL_RIGHT
    #undef  GL_FRONT_AND_BACK
    #undef  GL_AUX0
    #undef  GL_AUX1
    #undef  GL_AUX2
    #undef  GL_AUX3
    #undef  GL_INVALID_ENUM
    #undef  GL_INVALID_VALUE
    #undef  GL_INVALID_OPERATION
    #undef  GL_STACK_OVERFLOW
    #undef  GL_STACK_UNDERFLOW
    #undef  GL_OUT_OF_MEMORY
    #undef  GL_2D
    #undef  GL_3D
    #undef  GL_3D_COLOR
    #undef  GL_3D_COLOR_TEXTURE
    #undef  GL_4D_COLOR_TEXTURE
    #undef  GL_PASS_THROUGH_TOKEN
    #undef  GL_POINT_TOKEN
    #undef  GL_LINE_TOKEN
    #undef  GL_POLYGON_TOKEN
    #undef  GL_BITMAP_TOKEN
    #undef  GL_DRAW_PIXEL_TOKEN
    #undef  GL_COPY_PIXEL_TOKEN
    #undef  GL_LINE_RESET_TOKEN
    #undef  GL_CURRENT_COLOR
    #undef  GL_CURRENT_INDEX
    #undef  GL_CURRENT_NORMAL
    #undef  GL_CURRENT_TEXTURE_COORDS
    #undef  GL_CURRENT_RASTER_COLOR
    #undef  GL_CURRENT_RASTER_INDEX
    #undef  GL_CURRENT_RASTER_TEXTURE_COORDS
    #undef  GL_CURRENT_RASTER_POSITION
    #undef  GL_CURRENT_RASTER_POSITION_VALID
    #undef  GL_CURRENT_RASTER_DISTANCE
    #undef  GL_CURRENT_RASTER_SECONDARY_COLOR
    #undef  GL_POINT_SMOOTH
    #undef  GL_POINT_SIZE
    #undef  GL_POINT_SIZE_RANGE
    #undef  GL_POINT_SIZE_GRANULARITY
    #undef  GL_LINE_SMOOTH
    #undef  GL_LINE_WIDTH
    #undef  GL_LINE_WIDTH_RANGE
    #undef  GL_LINE_WIDTH_GRANULARITY
    #undef  GL_LINE_STIPPLE
    #undef  GL_LINE_STIPPLE_PATTERN
    #undef  GL_LINE_STIPPLE_REPEAT
    #undef  GL_SMOOTH_POINT_SIZE_RANGE
    #undef  GL_SMOOTH_POINT_SIZE_GRANULARITY
    #undef  GL_SMOOTH_LINE_WIDTH_RANGE
    #undef  GL_SMOOTH_LINE_WIDTH_GRANULARITY
    #undef  GL_ALIASED_POINT_SIZE_RANGE
    #undef  GL_ALIASED_LINE_WIDTH_RANGE
    #undef  GL_POINT_SIZE_MIN
    #undef  GL_POINT_SIZE_MAX
    #undef  GL_POINT_FADE_THRESHOLD_SIZE
    #undef  GL_POINT_DISTANCE_ATTENUATION
    #undef  GL_POINT_SPRITE
    #undef  GL_COORD_REPLACE
    #undef  GL_POINT_SPRITE_COORD_ORIGIN
    #undef  GL_LOWER_LEFT
    #undef  GL_UPPER_LEFT
    #undef  GL_LIST_MODE
    #undef  GL_MAX_LIST_NESTING
    #undef  GL_LIST_BASE
    #undef  GL_LIST_INDEX
    #undef  GL_POLYGON_MODE
    #undef  GL_POLYGON_SMOOTH
    #undef  GL_POLYGON_STIPPLE
    #undef  GL_EDGE_FLAG
    #undef  GL_CULL_FACE
    #undef  GL_CULL_FACE_MODE
    #undef  GL_FRONT_FACE
    #undef  GL_SCISSOR_BOX
    #undef  GL_SCISSOR_TEST
    #undef  GL_POLYGON_OFFSET_FILL
    #undef  GL_POLYGON_OFFSET_FACTOR
    #undef  GL_CLIP_PLANE0
    #undef  GL_CLIP_PLANE1
    #undef  GL_CLIP_PLANE2
    #undef  GL_CLIP_PLANE3
    #undef  GL_CLIP_PLANE4
    #undef  GL_CLIP_PLANE5
    #undef  GL_POLYGON_OFFSET_UNITS
    #undef  GL_POLYGON_OFFSET_POINT
    #undef  GL_POLYGON_OFFSET_LINE
    #undef  GL_AUX_BUFFERS
    #undef  GL_DRAW_BUFFER
    #undef  GL_READ_BUFFER
    #undef  GL_DOUBLEBUFFER
    #undef  GL_BUFFER_SIZE
    #undef  GL_BUFFER_USAGE
    #undef  GL_QUERY_COUNTER_BITS
    #undef  GL_CURRENT_QUERY
    #undef  GL_QUERY_RESULT
    #undef  GL_QUERY_RESULT_AVAILABLE
    #undef  GL_ARRAY_BUFFER
    #undef  GL_ELEMENT_ARRAY_BUFFER
    #undef  GL_ARRAY_BUFFER_BINDING
    #undef  GL_ELEMENT_ARRAY_BUFFER_BINDING
    #undef  GL_VERTEX_ARRAY_BUFFER_BINDING
    #undef  GL_NORMAL_ARRAY_BUFFER_BINDING
    #undef  GL_COLOR_ARRAY_BUFFER_BINDING
    #undef  GL_INDEX_ARRAY_BUFFER_BINDING
    #undef  GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING
    #undef  GL_EDGE_FLAG_ARRAY_BUFFER_BINDING
    #undef  GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING
    #undef  GL_WEIGHT_ARRAY_BUFFER_BINDING
    #undef  GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING
    #undef  GL_READ_ONLY
    #undef  GL_WRITE_ONLY
    #undef  GL_READ_WRITE
    #undef  GL_BUFFER_ACCESS
    #undef  GL_BUFFER_MAPPED
    #undef  GL_BUFFER_MAP_POINTER
    #undef  GL_STREAM_DRAW
    #undef  GL_STREAM_READ
    #undef  GL_STREAM_COPY
    #undef  GL_STATIC_DRAW
    #undef  GL_STATIC_READ
    #undef  GL_STATIC_COPY
    #undef  GL_DYNAMIC_DRAW
    #undef  GL_DYNAMIC_READ
    #undef  GL_DYNAMIC_COPY
    #undef  GL_SAMPLES_PASSED
    #undef  GL_VERTEX_ATTRIB_ARRAY_ENABLED
    #undef  GL_VERTEX_ATTRIB_ARRAY_SIZE
    #undef  GL_VERTEX_ATTRIB_ARRAY_STRIDE
    #undef  GL_VERTEX_ATTRIB_ARRAY_TYPE
    #undef  GL_CURRENT_VERTEX_ATTRIB
    #undef  GL_VERTEX_PROGRAM_POINT_SIZE
    #undef  GL_VERTEX_PROGRAM_TWO_SIDE
    #undef  GL_VERTEX_ATTRIB_ARRAY_POINTER
    #undef  GL_DRAW_BUFFER0
    #undef  GL_DRAW_BUFFER1
    #undef  GL_DRAW_BUFFER2
    #undef  GL_DRAW_BUFFER3
    #undef  GL_DRAW_BUFFER4
    #undef  GL_DRAW_BUFFER5
    #undef  GL_DRAW_BUFFER6
    #undef  GL_DRAW_BUFFER7
    #undef  GL_DRAW_BUFFER8
    #undef  GL_DRAW_BUFFER9
    #undef  GL_DRAW_BUFFER10
    #undef  GL_DRAW_BUFFER11
    #undef  GL_DRAW_BUFFER12
    #undef  GL_DRAW_BUFFER13
    #undef  GL_DRAW_BUFFER14
    #undef  GL_DRAW_BUFFER15
    #undef  GL_VERTEX_ATTRIB_ARRAY_NORMALIZED
    #undef  GL_DEPTH_BUFFER
    #undef  GL_STENCIL_BUFFER
    #undef  GL_CLIP_DISTANCE0
    #undef  GL_CLIP_DISTANCE1
    #undef  GL_CLIP_DISTANCE2
    #undef  GL_CLIP_DISTANCE3
    #undef  GL_CLIP_DISTANCE4
    #undef  GL_CLIP_DISTANCE5
    #undef  GL_VERTEX_ATTRIB_ARRAY_INTEGER
    #undef  GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH
    #undef  GL_TRANSFORM_FEEDBACK_BUFFER_MODE
    #undef  GL_TRANSFORM_FEEDBACK_VARYINGS
    #undef  GL_TRANSFORM_FEEDBACK_BUFFER_START
    #undef  GL_TRANSFORM_FEEDBACK_BUFFER_SIZE
    #undef  GL_PRIMITIVES_GENERATED
    #undef  GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN
    #undef  GL_RASTERIZER_DISCARD
    #undef  GL_INTERLEAVED_ATTRIBS
    #undef  GL_SEPARATE_ATTRIBS 
    #undef  GL_TRANSFORM_FEEDBACK_BUFFER
    #undef  GL_TRANSFORM_FEEDBACK_BUFFER_BINDING
    #undef  GL_LIGHTING
    #undef  GL_LIGHT_MODEL_LOCAL_VIEWER
    #undef  GL_LIGHT_MODEL_TWO_SIDE
    #undef  GL_LIGHT_MODEL_AMBIENT
    #undef  GL_SHADE_MODEL
    #undef  GL_COLOR_MATERIAL_FACE
    #undef  GL_COLOR_MATERIAL_PARAMETER
    #undef  GL_COLOR_MATERIAL
    #undef  GL_LIGHT0
    #undef  GL_LIGHT1
    #undef  GL_LIGHT2
    #undef  GL_LIGHT3
    #undef  GL_LIGHT4
    #undef  GL_LIGHT5
    #undef  GL_LIGHT6
    #undef  GL_LIGHT7
    #undef  GL_LIGHT_MODEL_COLOR_CONTROL
    #undef  GL_SINGLE_COLOR
    #undef  GL_SEPARATE_SPECULAR_COLOR
    #undef  GL_FOG
    #undef  GL_FOG_INDEX
    #undef  GL_FOG_DENSITY
    #undef  GL_FOG_START
    #undef  GL_FOG_END
    #undef  GL_FOG_MODE
    #undef  GL_FOG_COLOR
    #undef  GL_FOG_COORDINATE_SOURCE
    #undef  GL_FOG_COORDINATE
    #undef  GL_FRAGMENT_DEPTH
    #undef  GL_CURRENT_FOG_COORDINATE
    #undef  GL_FOG_COORDINATE_ARRAY_TYPE
    #undef  GL_FOG_COORDINATE_ARRAY_STRIDE
    #undef  GL_FOG_COORDINATE_ARRAY_POINTER
    #undef  GL_FOG_COORDINATE_ARRAY
    #undef  GL_CURRENT_FOG_COORD
    #undef  GL_FOG_COORD
    #undef  GL_FOG_COORD_ARRAY
    #undef  GL_FOG_COORD_ARRAY_BUFFER_BINDING
    #undef  GL_FOG_COORD_ARRAY_POINTER
    #undef  GL_FOG_COORD_ARRAY_STRIDE
    #undef  GL_FOG_COORD_ARRAY_TYPE
    #undef  GL_FOG_COORD_SRC
    #undef  GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING
    #undef  GL_DEPTH_RANGE
    #undef  GL_DEPTH_TEST
    #undef  GL_DEPTH_WRITEMASK
    #undef  GL_DEPTH_CLEAR_VALUE
    #undef  GL_DEPTH_FUNC
    #undef  GL_DEPTH_STENCIL
    #undef  GL_DEPTH24_STENCIL8
    #undef  GL_STENCIL_TEST
    #undef  GL_STENCIL_CLEAR_VALUE
    #undef  GL_STENCIL_FUNC
    #undef  GL_STENCIL_VALUE_MASK
    #undef  GL_STENCIL_FAIL
    #undef  GL_STENCIL_PASS_DEPTH_FAIL
    #undef  GL_STENCIL_PASS_DEPTH_PASS
    #undef  GL_STENCIL_REF
    #undef  GL_STENCIL_WRITEMASK
    #undef  GL_STENCIL_BACK_FUNC
    #undef  GL_STENCIL_BACK_FAIL
    #undef  GL_STENCIL_BACK_PASS_DEPTH_FAIL
    #undef  GL_STENCIL_BACK_PASS_DEPTH_PASS
    #undef  GL_STENCIL_BACK_REF
    #undef  GL_STENCIL_BACK_VALUE_MASK
    #undef  GL_STENCIL_BACK_WRITEMASK
    #undef  GL_STENCIL_INDEX1
    #undef  GL_STENCIL_INDEX4
    #undef  GL_STENCIL_INDEX8
    #undef  GL_STENCIL_INDEX16
    #undef  GL_MATRIX_MODE
    #undef  GL_NORMALIZE
    #undef  GL_VIEWPORT
    #undef  GL_MODELVIEW_STACK_DEPTH
    #undef  GL_PROJECTION_STACK_DEPTH
    #undef  GL_TEXTURE_STACK_DEPTH
    #undef  GL_MODELVIEW_MATRIX
    #undef  GL_PROJECTION_MATRIX
    #undef  GL_TEXTURE_MATRIX
    #undef  GL_TRANSPOSE_MODELVIEW_MATRIX
    #undef  GL_TRANSPOSE_PROJECTION_MATRIX
    #undef  GL_TRANSPOSE_TEXTURE_MATRIX
    #undef  GL_TRANSPOSE_COLOR_MATRIX
    #undef  GL_FLOAT_MAT2x3
    #undef  GL_FLOAT_MAT2x4
    #undef  GL_FLOAT_MAT3x2
    #undef  GL_FLOAT_MAT3x4
    #undef  GL_FLOAT_MAT4x2
    #undef  GL_FLOAT_MAT4x3
    #undef  GL_TEXTURE_COMPONENTS
    #undef  GL_INDEX_CLEAR_VALUE
    #undef  GL_INDEX_WRITEMASK
    #undef  GL_COLOR_CLEAR_VALUE
    #undef  GL_COLOR_WRITEMASK
    #undef  GL_STEREO
    #undef  GL_TEXTURE_GEN_S
    #undef  GL_TEXTURE_GEN_T
    #undef  GL_TEXTURE_GEN_R
    #undef  GL_TEXTURE_GEN_Q
    #undef  GL_PIXEL_MAP_I_TO_I
    #undef  GL_PIXEL_MAP_S_TO_S
    #undef  GL_PIXEL_MAP_I_TO_R
    #undef  GL_PIXEL_MAP_I_TO_G
    #undef  GL_PIXEL_MAP_I_TO_B
    #undef  GL_PIXEL_MAP_I_TO_A
    #undef  GL_PIXEL_MAP_R_TO_R
    #undef  GL_PIXEL_MAP_G_TO_G
    #undef  GL_PIXEL_MAP_B_TO_B
    #undef  GL_PIXEL_MAP_A_TO_A
    #undef  GL_PIXEL_MAP_I_TO_I_SIZE
    #undef  GL_PIXEL_MAP_S_TO_S_SIZE
    #undef  GL_PIXEL_MAP_I_TO_R_SIZE
    #undef  GL_PIXEL_MAP_I_TO_G_SIZE
    #undef  GL_PIXEL_MAP_I_TO_B_SIZE
    #undef  GL_PIXEL_MAP_I_TO_A_SIZE
    #undef  GL_PIXEL_MAP_R_TO_R_SIZE
    #undef  GL_PIXEL_MAP_G_TO_G_SIZE
    #undef  GL_PIXEL_MAP_B_TO_B_SIZE
    #undef  GL_PIXEL_MAP_A_TO_A_SIZE
    #undef  GL_UNPACK_SWAP_BYTES
    #undef  GL_UNPACK_LSB_FIRST
    #undef  GL_UNPACK_ROW_LENGTH
    #undef  GL_UNPACK_SKIP_ROWS
    #undef  GL_UNPACK_SKIP_PIXELS
    #undef  GL_UNPACK_ALIGNMENT
    #undef  GL_PACK_SWAP_BYTES
    #undef  GL_PACK_LSB_FIRST
    #undef  GL_PACK_ROW_LENGTH
    #undef  GL_PACK_SKIP_ROWS
    #undef  GL_PACK_SKIP_PIXELS
    #undef  GL_PACK_ALIGNMENT
    #undef  GL_MAP_COLOR
    #undef  GL_MAP_STENCIL
    #undef  GL_INDEX_SHIFT
    #undef  GL_INDEX_OFFSET
    #undef  GL_RED_SCALE
    #undef  GL_RED_BIAS
    #undef  GL_ZOOM_X
    #undef  GL_ZOOM_Y
    #undef  GL_GREEN_SCALE
    #undef  GL_GREEN_BIAS
    #undef  GL_BLUE_SCALE
    #undef  GL_BLUE_BIAS
    #undef  GL_ALPHA_SCALE
    #undef  GL_ALPHA_BIAS
    #undef  GL_DEPTH_SCALE
    #undef  GL_DEPTH_BIAS
    #undef  GL_SUBPIXEL_BITS
    #undef  GL_INDEX_BITS
    #undef  GL_RED_BITS
    #undef  GL_GREEN_BITS
    #undef  GL_BLUE_BITS
    #undef  GL_ALPHA_BITS
    #undef  GL_DEPTH_BITS
    #undef  GL_STENCIL_BITS
    #undef  GL_ACCUM_RED_BITS
    #undef  GL_ACCUM_GREEN_BITS
    #undef  GL_ACCUM_BLUE_BITS
    #undef  GL_ACCUM_ALPHA_BITS
    #undef  GL_ACCUM_CLEAR_VALUE
    #undef  GL_NAME_STACK_DEPTH
    #undef  GL_AUTO_NORMAL
    #undef  GL_MAP1_COLOR_4
    #undef  GL_MAP1_INDEX
    #undef  GL_MAP1_NORMAL
    #undef  GL_MAP1_TEXTURE_COORD_1
    #undef  GL_MAP1_TEXTURE_COORD_2
    #undef  GL_MAP1_TEXTURE_COORD_3
    #undef  GL_MAP1_TEXTURE_COORD_4
    #undef  GL_MAP1_VERTEX_3
    #undef  GL_MAP1_VERTEX_4
    #undef  GL_MAP2_COLOR_4
    #undef  GL_MAP2_INDEX
    #undef  GL_MAP2_NORMAL
    #undef  GL_MAP2_TEXTURE_COORD_1
    #undef  GL_MAP2_TEXTURE_COORD_2
    #undef  GL_MAP2_TEXTURE_COORD_3
    #undef  GL_MAP2_TEXTURE_COORD_4
    #undef  GL_MAP2_VERTEX_3
    #undef  GL_MAP2_VERTEX_4
    #undef  GL_MAP1_GRID_DOMAIN
    #undef  GL_MAP1_GRID_SEGMENTS
    #undef  GL_MAP2_GRID_DOMAIN
    #undef  GL_MAP2_GRID_SEGMENTS
    #undef  GL_TEXTURE_1D
    #undef  GL_TEXTURE_2D
    #undef  GL_FEEDBACK_BUFFER_POINTER
    #undef  GL_FEEDBACK_BUFFER_SIZE
    #undef  GL_FEEDBACK_BUFFER_TYPE
    #undef  GL_SELECTION_BUFFER_POINTER
    #undef  GL_SELECTION_BUFFER_SIZE
    #undef  GL_TEXTURE_WIDTH
    #undef  GL_TEXTURE_HEIGHT
    #undef  GL_TEXTURE_INTERNAL_FORMAT
    #undef  GL_TEXTURE_BORDER_COLOR
    #undef  GL_TEXTURE_BORDER
    #undef  GL_ALPHA4
    #undef  GL_ALPHA8
    #undef  GL_ALPHA12
    #undef  GL_ALPHA16
    #undef  GL_LUMINANCE4
    #undef  GL_LUMINANCE8
    #undef  GL_LUMINANCE12
    #undef  GL_LUMINANCE16
    #undef  GL_LUMINANCE4_ALPHA4
    #undef  GL_LUMINANCE6_ALPHA2
    #undef  GL_LUMINANCE8_ALPHA8
    #undef  GL_LUMINANCE12_ALPHA4
    #undef  GL_LUMINANCE12_ALPHA12
    #undef  GL_LUMINANCE16_ALPHA16
    #undef  GL_INTENSITY
    #undef  GL_INTENSITY4
    #undef  GL_INTENSITY8
    #undef  GL_INTENSITY12
    #undef  GL_INTENSITY16
    #undef  GL_RGB4
    #undef  GL_RGB5
    #undef  GL_RGB8
    #undef  GL_RGB10
    #undef  GL_RGB12
    #undef  GL_RGB16
    #undef  GL_RGBA2
    #undef  GL_RGBA4
    #undef  GL_RGB5_A1
    #undef  GL_RGBA8
    #undef  GL_RGB10_A2
    #undef  GL_RGBA12
    #undef  GL_RGBA16
    #undef  GL_TEXTURE_RED_SIZE
    #undef  GL_TEXTURE_GREEN_SIZE
    #undef  GL_TEXTURE_BLUE_SIZE
    #undef  GL_TEXTURE_ALPHA_SIZE
    #undef  GL_TEXTURE_LUMINANCE_SIZE
    #undef  GL_TEXTURE_INTENSITY_SIZE
    #undef  GL_PROXY_TEXTURE_1D
    #undef  GL_PROXY_TEXTURE_2D
    #undef  GL_TEXTURE_PRIORITY
    #undef  GL_TEXTURE_RESIDENT
    #undef  GL_TEXTURE_BINDING_1D
    #undef  GL_TEXTURE_BINDING_2D
    #undef  GL_COLOR_INDEX1_EXT
    #undef  GL_COLOR_INDEX2_EXT
    #undef  GL_COLOR_INDEX4_EXT
    #undef  GL_COLOR_INDEX8_EXT
    #undef  GL_COLOR_INDEX12_EXT
    #undef  GL_COLOR_INDEX16_EXT
    #undef  GL_S
    #undef  GL_T
    #undef  GL_R
    #undef  GL_Q
    #undef  GL_MODULATE
    #undef  GL_DECAL
    #undef  GL_TEXTURE_ENV_MODE
    #undef  GL_TEXTURE_ENV_COLOR
    #undef  GL_TEXTURE_ENV
    #undef  GL_EYE_LINEAR
    #undef  GL_OBJECT_LINEAR
    #undef  GL_SPHERE_MAP
    #undef  GL_TEXTURE_GEN_MODE
    #undef  GL_OBJECT_PLANE
    #undef  GL_EYE_PLANE
    #undef  GL_NEAREST
    #undef  GL_LINEAR
    #undef  GL_NEAREST_MIPMAP_NEAREST
    #undef  GL_LINEAR_MIPMAP_NEAREST
    #undef  GL_NEAREST_MIPMAP_LINEAR
    #undef  GL_LINEAR_MIPMAP_LINEAR
    #undef  GL_TEXTURE_MAG_FILTER
    #undef  GL_TEXTURE_MIN_FILTER
    #undef  GL_TEXTURE_WRAP_S
    #undef  GL_TEXTURE_WRAP_T
    #undef  GL_CLAMP
    #undef  GL_REPEAT
    #undef  GL_MAX_3D_TEXTURE_SIZE
    #undef  GL_BGR
    #undef  GL_BGRA
    #undef  GL_CLAMP_TO_EDGE
    #undef  GL_TEXTURE_MIN_LOD
    #undef  GL_TEXTURE_MAX_LOD
    #undef  GL_TEXTURE_BASE_LEVEL
    #undef  GL_TEXTURE_MAX_LEVEL
    #undef  GL_RESCALE_NORMAL
    #undef  GL_TEXTURE_BINDING_3D
    #undef  GL_PACK_SKIP_IMAGES
    #undef  GL_PACK_IMAGE_HEIGHT
    #undef  GL_UNPACK_SKIP_IMAGES
    #undef  GL_UNPACK_IMAGE_HEIGHT
    #undef  GL_TEXTURE_3D
    #undef  GL_PROXY_TEXTURE_3D
    #undef  GL_TEXTURE_DEPTH
    #undef  GL_TEXTURE_WRAP_R
    #undef  GL_MULTISAMPLE
    #undef  GL_SAMPLE_ALPHA_TO_COVERAGE
    #undef  GL_SAMPLE_ALPHA_TO_ONE
    #undef  GL_SAMPLE_COVERAGE
    #undef  GL_SAMPLE_BUFFERS
    #undef  GL_SAMPLES
    #undef  GL_SAMPLE_COVERAGE_VALUE
    #undef  GL_SAMPLE_COVERAGE_INVERT
    #undef  GL_CLAMP_TO_BORDER
    #undef  GL_TEXTURE0
    #undef  GL_TEXTURE1
    #undef  GL_TEXTURE2
    #undef  GL_TEXTURE3
    #undef  GL_TEXTURE4
    #undef  GL_TEXTURE5
    #undef  GL_TEXTURE6
    #undef  GL_TEXTURE7
    #undef  GL_TEXTURE8
    #undef  GL_TEXTURE9
    #undef  GL_TEXTURE10
    #undef  GL_TEXTURE11
    #undef  GL_TEXTURE12
    #undef  GL_TEXTURE13
    #undef  GL_TEXTURE14
    #undef  GL_TEXTURE15
    #undef  GL_TEXTURE16
    #undef  GL_TEXTURE17
    #undef  GL_TEXTURE18
    #undef  GL_TEXTURE19
    #undef  GL_TEXTURE20
    #undef  GL_TEXTURE21
    #undef  GL_TEXTURE22
    #undef  GL_TEXTURE23
    #undef  GL_TEXTURE24
    #undef  GL_TEXTURE25
    #undef  GL_TEXTURE26
    #undef  GL_TEXTURE27
    #undef  GL_TEXTURE28
    #undef  GL_TEXTURE29
    #undef  GL_TEXTURE30
    #undef  GL_TEXTURE31
    #undef  GL_ACTIVE_TEXTURE
    #undef  GL_CLIENT_ACTIVE_TEXTURE
    #undef  GL_COMPRESSED_ALPHA
    #undef  GL_COMPRESSED_LUMINANCE
    #undef  GL_COMPRESSED_LUMINANCE_ALPHA
    #undef  GL_COMPRESSED_INTENSITY
    #undef  GL_COMPRESSED_RGB
    #undef  GL_COMPRESSED_RGBA
    #undef  GL_TEXTURE_COMPRESSION_HINT
    #undef  GL_NORMAL_MAP
    #undef  GL_REFLECTION_MAP
    #undef  GL_TEXTURE_CUBE_MAP
    #undef  GL_TEXTURE_BINDING_CUBE_MAP
    #undef  GL_TEXTURE_CUBE_MAP_POSITIVE_X
    #undef  GL_TEXTURE_CUBE_MAP_NEGATIVE_X
    #undef  GL_TEXTURE_CUBE_MAP_POSITIVE_Y
    #undef  GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
    #undef  GL_TEXTURE_CUBE_MAP_POSITIVE_Z
    #undef  GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
    #undef  GL_PROXY_TEXTURE_CUBE_MAP
    #undef  GL_MAX_CUBE_MAP_TEXTURE_SIZE
    #undef  GL_COMBINE
    #undef  GL_COMBINE_RGB
    #undef  GL_COMBINE_ALPHA
    #undef  GL_RGB_SCALE
    #undef  GL_ADD_SIGNED
    #undef  GL_INTERPOLATE
    #undef  GL_CONSTANT
    #undef  GL_PRIMARY_COLOR
    #undef  GL_PREVIOUS
    #undef  GL_SOURCE0_RGB
    #undef  GL_SOURCE1_RGB
    #undef  GL_SOURCE2_RGB
    #undef  GL_SOURCE0_ALPHA
    #undef  GL_SOURCE1_ALPHA
    #undef  GL_SOURCE2_ALPHA
    #undef  GL_SRC0_ALPHA
    #undef  GL_SRC0_RGB
    #undef  GL_SRC1_ALPHA
    #undef  GL_SRC1_RGB
    #undef  GL_SRC2_ALPHA
    #undef  GL_SRC2_RGB
    #undef  GL_OPERAND0_RGB
    #undef  GL_OPERAND1_RGB
    #undef  GL_OPERAND2_RGB
    #undef  GL_OPERAND0_ALPHA
    #undef  GL_OPERAND1_ALPHA
    #undef  GL_OPERAND2_ALPHA
    #undef  GL_TEXTURE_COMPRESSED_IMAGE_SIZE
    #undef  GL_TEXTURE_COMPRESSED
    #undef  GL_NUM_COMPRESSED_TEXTURE_FORMATS
    #undef  GL_COMPRESSED_TEXTURE_FORMATS
    #undef  GL_DOT3_RGB
    #undef  GL_DOT3_RGBA
    #undef  GL_GENERATE_MIPMAP
    #undef  GL_GENERATE_MIPMAP_HINT
    #undef  GL_DEPTH_COMPONENT16
    #undef  GL_DEPTH_COMPONENT24
    #undef  GL_DEPTH_COMPONENT32
    #undef  GL_MIRRORED_REPEAT
    #undef  GL_COLOR_SUM
    #undef  GL_CURRENT_SECONDARY_COLOR
    #undef  GL_SECONDARY_COLOR_ARRAY_SIZE
    #undef  GL_SECONDARY_COLOR_ARRAY_TYPE
    #undef  GL_SECONDARY_COLOR_ARRAY_STRIDE
    #undef  GL_SECONDARY_COLOR_ARRAY_POINTER
    #undef  GL_SECONDARY_COLOR_ARRAY
    #undef  GL_TEXTURE_FILTER_CONTROL
    #undef  GL_TEXTURE_LOD_BIAS
    #undef  GL_INCR_WRAP
    #undef  GL_DECR_WRAP
    #undef  GL_TEXTURE_DEPTH_SIZE
    #undef  GL_DEPTH_TEXTURE_MODE
    #undef  GL_TEXTURE_COMPARE_MODE
    #undef  GL_TEXTURE_COMPARE_FUNC
    #undef  GL_COMPARE_R_TO_TEXTURE
    #undef  GL_PIXEL_PACK_BUFFER
    #undef  GL_PIXEL_UNPACK_BUFFER
    #undef  GL_PIXEL_PACK_BUFFER_BINDING
    #undef  GL_PIXEL_UNPACK_BUFFER_BINDING
    #undef  GL_SRGB
    #undef  GL_SRGB8
    #undef  GL_SRGB_ALPHA
    #undef  GL_SRGB8_ALPHA8
    #undef  GL_SLUMINANCE_ALPHA
    #undef  GL_SLUMINANCE8_ALPHA8
    #undef  GL_SLUMINANCE
    #undef  GL_SLUMINANCE8
    #undef  GL_COMPRESSED_SRGB
    #undef  GL_COMPRESSED_SRGB_ALPHA
    #undef  GL_COMPRESSED_SLUMINANCE
    #undef  GL_COMPRESSED_SLUMINANCE_ALPHA
    #undef  GL_CLAMP_VERTEX_COLOR
    #undef  GL_CLAMP_FRAGMENT_COLOR
    #undef  GL_CLAMP_READ_COLOR
    #undef  GL_FIXED_ONLY
    #undef  GL_COMPARE_REF_TO_TEXTURE
    #undef  GL_TEXTURE_RED_TYPE
    #undef  GL_TEXTURE_GREEN_TYPE
    #undef  GL_TEXTURE_BLUE_TYPE
    #undef  GL_TEXTURE_ALPHA_TYPE
    #undef  GL_TEXTURE_LUMINANCE_TYPE
    #undef  GL_TEXTURE_INTENSITY_TYPE
    #undef  GL_TEXTURE_DEPTH_TYPE
    #undef  GL_TEXTURE_1D_ARRAY
    #undef  GL_PROXY_TEXTURE_1D_ARRAY
    #undef  GL_TEXTURE_2D_ARRAY
    #undef  GL_PROXY_TEXTURE_2D_ARRAY
    #undef  GL_TEXTURE_BINDING_1D_ARRAY
    #undef  GL_TEXTURE_BINDING_2D_ARRAY
    #undef  GL_R11F_G11F_B10F
    #undef  GL_UNSIGNED_INT_10F_11F_11F_REV
    #undef  GL_RGB9_E5
    #undef  GL_UNSIGNED_INT_5_9_9_9_REV
    #undef  GL_TEXTURE_SHARED_SIZE
    #undef  GL_RGBA32F
    #undef  GL_RGB32F
    #undef  GL_RGBA16F
    #undef  GL_RGB16F
    #undef  GL_RGBA32UI
    #undef  GL_RGB32UI
    #undef  GL_RGBA16UI
    #undef  GL_RGB16UI
    #undef  GL_RGBA8UI
    #undef  GL_RGB8UI
    #undef  GL_RGBA32I
    #undef  GL_RGB32I
    #undef  GL_RGBA16I
    #undef  GL_RGB16I
    #undef  GL_RGBA8I
    #undef  GL_RGB8I
    #undef  GL_RED_INTEGER
    #undef  GL_GREEN_INTEGER
    #undef  GL_BLUE_INTEGER
    #undef  GL_ALPHA_INTEGER
    #undef  GL_RGB_INTEGER
    #undef  GL_RGBA_INTEGER
    #undef  GL_BGR_INTEGER
    #undef  GL_BGRA_INTEGER
    #undef  GL_SAMPLER_1D_ARRAY
    #undef  GL_SAMPLER_2D_ARRAY
    #undef  GL_SAMPLER_1D_ARRAY_SHADOW
    #undef  GL_SAMPLER_2D_ARRAY_SHADOW
    #undef  GL_SAMPLER_CUBE_SHADOW
    #undef  GL_UNSIGNED_INT_VEC2
    #undef  GL_UNSIGNED_INT_VEC3
    #undef  GL_UNSIGNED_INT_VEC4
    #undef  GL_INT_SAMPLER_1D
    #undef  GL_INT_SAMPLER_2D
    #undef  GL_INT_SAMPLER_3D
    #undef  GL_INT_SAMPLER_CUBE
    #undef  GL_INT_SAMPLER_1D_ARRAY
    #undef  GL_INT_SAMPLER_2D_ARRAY
    #undef  GL_UNSIGNED_INT_SAMPLER_1D
    #undef  GL_UNSIGNED_INT_SAMPLER_2D
    #undef  GL_UNSIGNED_INT_SAMPLER_3D
    #undef  GL_UNSIGNED_INT_SAMPLER_CUBE
    #undef  GL_UNSIGNED_INT_SAMPLER_1D_ARRAY
    #undef  GL_UNSIGNED_INT_SAMPLER_2D_ARRAY
    #undef  GL_TEXTURE_STENCIL_SIZE
    #undef  GL_MAX_EVAL_ORDER
    #undef  GL_MAX_LIGHTS
    #undef  GL_MAX_CLIP_PLANES
    #undef  GL_MAX_TEXTURE_SIZE
    #undef  GL_MAX_PIXEL_MAP_TABLE
    #undef  GL_MAX_ATTRIB_STACK_DEPTH
    #undef  GL_MAX_MODELVIEW_STACK_DEPTH
    #undef  GL_MAX_NAME_STACK_DEPTH
    #undef  GL_MAX_PROJECTION_STACK_DEPTH
    #undef  GL_MAX_TEXTURE_STACK_DEPTH
    #undef  GL_MAX_VIEWPORT_DIMS
    #undef  GL_MAX_CLIENT_ATTRIB_STACK_DEPTH
    #undef  GL_MAX_ELEMENTS_VERTICES
    #undef  GL_MAX_ELEMENTS_INDICES
    #undef  GL_MAX_TEXTURE_UNITS
    #undef  GL_MAX_TEXTURE_LOD_BIAS
    #undef  GL_MAX_DRAW_BUFFERS
    #undef  GL_MAX_VERTEX_ATTRIBS
    #undef  GL_MAX_TEXTURE_COORDS
    #undef  GL_MAX_TEXTURE_IMAGE_UNITS
    #undef  GL_MAX_FRAGMENT_UNIFORM_COMPONENTS
    #undef  GL_MAX_VERTEX_UNIFORM_COMPONENTS
    #undef  GL_MAX_VARYING_FLOATS
    #undef  GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS
    #undef  GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
    #undef  GL_MAX_CLIP_DISTANCES
    #undef  GL_MAX_VARYING_COMPONENTS
    #undef  GL_MAX_ARRAY_TEXTURE_LAYERS
    #undef  GL_MIN_PROGRAM_TEXEL_OFFSET
    #undef  GL_MAX_PROGRAM_TEXEL_OFFSET
    #undef  GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS
    #undef  GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS
    #undef  GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS
    #undef  GL_MAX_RENDERBUFFER_SIZE
    #undef  GL_MAX_COLOR_ATTACHMENTS
    #undef  GL_MAX_SAMPLES
    #undef  GL_VERTEX_ARRAY
    #undef  GL_NORMAL_ARRAY
    #undef  GL_COLOR_ARRAY
    #undef  GL_INDEX_ARRAY
    #undef  GL_TEXTURE_COORD_ARRAY
    #undef  GL_EDGE_FLAG_ARRAY
    #undef  GL_VERTEX_ARRAY_SIZE
    #undef  GL_VERTEX_ARRAY_TYPE
    #undef  GL_VERTEX_ARRAY_STRIDE
    #undef  GL_NORMAL_ARRAY_TYPE
    #undef  GL_NORMAL_ARRAY_STRIDE
    #undef  GL_COLOR_ARRAY_SIZE
    #undef  GL_COLOR_ARRAY_TYPE
    #undef  GL_COLOR_ARRAY_STRIDE
    #undef  GL_INDEX_ARRAY_TYPE
    #undef  GL_INDEX_ARRAY_STRIDE
    #undef  GL_TEXTURE_COORD_ARRAY_SIZE
    #undef  GL_TEXTURE_COORD_ARRAY_TYPE
    #undef  GL_TEXTURE_COORD_ARRAY_STRIDE
    #undef  GL_EDGE_FLAG_ARRAY_STRIDE
    #undef  GL_VERTEX_ARRAY_POINTER
    #undef  GL_NORMAL_ARRAY_POINTER
    #undef  GL_COLOR_ARRAY_POINTER
    #undef  GL_INDEX_ARRAY_POINTER
    #undef  GL_TEXTURE_COORD_ARRAY_POINTER
    #undef  GL_EDGE_FLAG_ARRAY_POINTER
    #undef  GL_R3_G3_B2
    #undef  GL_V2F
    #undef  GL_V3F
    #undef  GL_C4UB_V2F
    #undef  GL_C4UB_V3F
    #undef  GL_C3F_V3F
    #undef  GL_N3F_V3F
    #undef  GL_C4F_N3F_V3F
    #undef  GL_T2F_V3F
    #undef  GL_T4F_V4F
    #undef  GL_T2F_C4UB_V3F
    #undef  GL_T2F_C3F_V3F
    #undef  GL_T2F_N3F_V3F
    #undef  GL_T2F_C4F_N3F_V3F
    #undef  GL_T4F_C4F_N3F_V4F
    #undef  GL_COMPILE
    #undef  GL_COMPILE_AND_EXECUTE
    #undef  GL_FRAGMENT_SHADER
    #undef  GL_VERTEX_SHADER
    #undef  GL_SHADER_TYPE
    #undef  GL_FLOAT_VEC2
    #undef  GL_FLOAT_VEC3
    #undef  GL_FLOAT_VEC4
    #undef  GL_INT_VEC2
    #undef  GL_INT_VEC3
    #undef  GL_INT_VEC4
    #undef  GL_BOOL
    #undef  GL_BOOL_VEC2
    #undef  GL_BOOL_VEC3
    #undef  GL_BOOL_VEC4
    #undef  GL_FLOAT_MAT2
    #undef  GL_FLOAT_MAT3
    #undef  GL_FLOAT_MAT4
    #undef  GL_SAMPLER_1D
    #undef  GL_SAMPLER_2D
    #undef  GL_SAMPLER_3D
    #undef  GL_SAMPLER_CUBE
    #undef  GL_SAMPLER_1D_SHADOW
    #undef  GL_SAMPLER_2D_SHADOW
    #undef  GL_DELETE_STATUS
    #undef  GL_COMPILE_STATUS
    #undef  GL_LINK_STATUS
    #undef  GL_VALIDATE_STATUS
    #undef  GL_INFO_LOG_LENGTH
    #undef  GL_ATTACHED_SHADERS
    #undef  GL_ACTIVE_UNIFORMS
    #undef  GL_ACTIVE_UNIFORM_MAX_LENGTH
    #undef  GL_SHADER_SOURCE_LENGTH
    #undef  GL_ACTIVE_ATTRIBUTES
    #undef  GL_ACTIVE_ATTRIBUTE_MAX_LENGTH
    #undef  GL_FRAGMENT_SHADER_DERIVATIVE_HINT
    #undef  GL_SHADING_LANGUAGE_VERSION
    #undef  GL_CURRENT_PROGRAM
    #undef  GL_INVALID_FRAMEBUFFER_OPERATION
    #undef  GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING
    #undef  GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE
    #undef  GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE
    #undef  GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE
    #undef  GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE
    #undef  GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE
    #undef  GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE
    #undef  GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE
    #undef  GL_FRAMEBUFFER_DEFAULT
    #undef  GL_FRAMEBUFFER_UNDEFINED
    #undef  GL_DEPTH_STENCIL_ATTACHMENT
    #undef  GL_DRAW_FRAMEBUFFER_BINDING
    #undef  GL_FRAMEBUFFER_BINDING
    #undef  GL_RENDERBUFFER_BINDING
    #undef  GL_READ_FRAMEBUFFER
    #undef  GL_DRAW_FRAMEBUFFER
    #undef  GL_READ_FRAMEBUFFER_BINDING
    #undef  GL_RENDERBUFFER_SAMPLES
    #undef  GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE
    #undef  GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME
    #undef  GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL
    #undef  GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE
    #undef  GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER
    #undef  GL_FRAMEBUFFER_COMPLETE
    #undef  GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT
    #undef  GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT
    #undef  GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER
    #undef  GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER
    #undef  GL_FRAMEBUFFER_UNSUPPORTED
    #undef  GL_COLOR_ATTACHMENT0
    #undef  GL_COLOR_ATTACHMENT1
    #undef  GL_COLOR_ATTACHMENT2
    #undef  GL_COLOR_ATTACHMENT3
    #undef  GL_COLOR_ATTACHMENT4
    #undef  GL_COLOR_ATTACHMENT5
    #undef  GL_COLOR_ATTACHMENT6
    #undef  GL_COLOR_ATTACHMENT7
    #undef  GL_COLOR_ATTACHMENT8
    #undef  GL_COLOR_ATTACHMENT9
    #undef  GL_COLOR_ATTACHMENT10
    #undef  GL_COLOR_ATTACHMENT11
    #undef  GL_COLOR_ATTACHMENT12
    #undef  GL_COLOR_ATTACHMENT13
    #undef  GL_COLOR_ATTACHMENT14
    #undef  GL_COLOR_ATTACHMENT15
    #undef  GL_DEPTH_ATTACHMENT
    #undef  GL_STENCIL_ATTACHMENT
    #undef  GL_FRAMEBUFFER
    #undef  GL_RENDERBUFFER
    #undef  GL_RENDERBUFFER_WIDTH
    #undef  GL_RENDERBUFFER_HEIGHT
    #undef  GL_RENDERBUFFER_INTERNAL_FORMAT
    #undef  GL_RENDERBUFFER_RED_SIZE
    #undef  GL_RENDERBUFFER_GREEN_SIZE
    #undef  GL_RENDERBUFFER_BLUE_SIZE
    #undef  GL_RENDERBUFFER_ALPHA_SIZE
    #undef  GL_RENDERBUFFER_DEPTH_SIZE
    #undef  GL_RENDERBUFFER_STENCIL_SIZE
    #undef  GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE
    #undef  GL_MAP_READ_BIT
    #undef  GL_MAP_WRITE_BIT
    #undef  GL_MAP_INVALIDATE_RANGE_BIT
    #undef  GL_MAP_INVALIDATE_BUFFER_BIT
    #undef  GL_MAP_FLUSH_EXPLICIT_BIT
    #undef  GL_MAP_UNSYNCHRONIZED_BIT


    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL types definitions                                              //
    ////////////////////////////////////////////////////////////////////////////
    typedef void                                                    GLvoid;
    typedef signed char                                             GLbyte;
    typedef unsigned char                                           GLubyte;
    typedef char                                                    GLchar;
    typedef unsigned char                                           GLboolean;
    typedef short                                                   GLshort;
    typedef unsigned short                                          GLushort;
    typedef int                                                     GLint;
    typedef unsigned int                                            GLuint;
    typedef int                                                     GLsizei;
    typedef unsigned long                                           GLulong;
    typedef unsigned int                                            GLenum;
    typedef unsigned int                                            GLbitfield;
    typedef float                                                   GLfloat;
    typedef double                                                  GLdouble;
    typedef float                                                   GLclampf;
    typedef double                                                  GLclampd;
    typedef ptrdiff_t                                               GLintptr;
    typedef ptrdiff_t                                               GLsizeiptr;


    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL global constants                                               //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_NONE                                                 0
    #define GL_ONE                                                  1
    #define GL_ZERO                                                 0
    #define GL_TRUE                                                 1
    #define GL_FALSE                                                0
    #define GL_NO_ERROR                                             0
    #define GL_EXP                                                  0x0800
    #define GL_EXP2                                                 0x0801
    #define GL_CW                                                   0x0900
    #define GL_CCW                                                  0x0901
    #define GL_COEFF                                                0x0A00
    #define GL_ORDER                                                0x0A01
    #define GL_DOMAIN                                               0x0A02
    #define GL_BYTE                                                 0x1400
    #define GL_UNSIGNED_BYTE                                        0x1401
    #define GL_SHORT                                                0x1402
    #define GL_UNSIGNED_SHORT                                       0x1403
    #define GL_INT                                                  0x1404
    #define GL_UNSIGNED_INT                                         0x1405
    #define GL_FLOAT                                                0x1406
    #define GL_2_BYTES                                              0x1407
    #define GL_3_BYTES                                              0x1408
    #define GL_4_BYTES                                              0x1409
    #define GL_DOUBLE                                               0x140A
    #define GL_UNSIGNED_BYTE_3_3_2                                  0x8032
    #define GL_UNSIGNED_SHORT_4_4_4_4                               0x8033
    #define GL_UNSIGNED_SHORT_5_5_5_1                               0x8034
    #define GL_UNSIGNED_INT_8_8_8_8                                 0x8035
    #define GL_UNSIGNED_INT_10_10_10_2                              0x8036
    #define GL_UNSIGNED_BYTE_2_3_3_REV                              0x8362
    #define GL_UNSIGNED_SHORT_5_6_5                                 0x8363
    #define GL_UNSIGNED_SHORT_5_6_5_REV                             0x8364
    #define GL_UNSIGNED_SHORT_4_4_4_4_REV                           0x8365
    #define GL_UNSIGNED_SHORT_1_5_5_5_REV                           0x8366
    #define GL_UNSIGNED_INT_8_8_8_8_REV                             0x8367
    #define GL_CLEAR                                                0x1500
    #define GL_AND                                                  0x1501
    #define GL_AND_REVERSE                                          0x1502
    #define GL_COPY                                                 0x1503
    #define GL_AND_INVERTED                                         0x1504
    #define GL_NOOP                                                 0x1505
    #define GL_XOR                                                  0x1506
    #define GL_OR                                                   0x1507
    #define GL_NOR                                                  0x1508
    #define GL_EQUIV                                                0x1509
    #define GL_INVERT                                               0x150A
    #define GL_OR_REVERSE                                           0x150B
    #define GL_COPY_INVERTED                                        0x150C
    #define GL_OR_INVERTED                                          0x150D
    #define GL_NAND                                                 0x150E
    #define GL_SET                                                  0x150F
    #define GL_EMISSION                                             0x1600
    #define GL_SHININESS                                            0x1601
    #define GL_AMBIENT_AND_DIFFUSE                                  0x1602
    #define GL_COLOR_INDEXES                                        0x1603
    #define GL_MODELVIEW                                            0x1700
    #define GL_PROJECTION                                           0x1701
    #define GL_TEXTURE                                              0x1702
    #define GL_COLOR                                                0x1800
    #define GL_DEPTH                                                0x1801
    #define GL_STENCIL                                              0x1802
    #define GL_COLOR_INDEX                                          0x1900
    #define GL_STENCIL_INDEX                                        0x1901
    #define GL_DEPTH_COMPONENT                                      0x1902
    #define GL_RED                                                  0x1903
    #define GL_GREEN                                                0x1904
    #define GL_BLUE                                                 0x1905
    #define GL_ALPHA                                                0x1906
    #define GL_RGB                                                  0x1907
    #define GL_RGBA                                                 0x1908
    #define GL_LUMINANCE                                            0x1909
    #define GL_LUMINANCE_ALPHA                                      0x190A
    #define GL_BITMAP                                               0x1A00
    #define GL_POINT                                                0x1B00
    #define GL_LINE                                                 0x1B01
    #define GL_FILL                                                 0x1B02
    #define GL_RENDER                                               0x1C00
    #define GL_FEEDBACK                                             0x1C01
    #define GL_SELECT                                               0x1C02
    #define GL_FLAT                                                 0x1D00
    #define GL_SMOOTH                                               0x1D01
    #define GL_KEEP                                                 0x1E00
    #define GL_REPLACE                                              0x1E01
    #define GL_INCR                                                 0x1E02
    #define GL_DECR                                                 0x1E03
    #define GL_VENDOR                                               0x1F00
    #define GL_RENDERER                                             0x1F01
    #define GL_VERSION                                              0x1F02
    #define GL_EXTENSIONS                                           0x1F03
    #define GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT                  0x0001
    #define GL_MAJOR_VERSION                                        0x821B
    #define GL_MINOR_VERSION                                        0x821C
    #define GL_NUM_EXTENSIONS                                       0x821D
    #define GL_CONTEXT_FLAGS                                        0x821E
    #define GL_INDEX                                                0x8222
    #define GL_UNSIGNED_INT_24_8                                    0x84FA
    #define GL_UNSIGNED_NORMALIZED                                  0x8C17
    #define GL_SRGB                                                 0x8C40

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL logic constants                                                //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_LOGIC_OP                                             0x0BF1
    #define GL_LOGIC_OP_MODE                                        0x0BF0
    #define GL_INDEX_LOGIC_OP                                       0x0BF1
    #define GL_COLOR_LOGIC_OP                                       0x0BF2
    #define GL_NEVER                                                0x0200
    #define GL_LESS                                                 0x0201
    #define GL_EQUAL                                                0x0202
    #define GL_LEQUAL                                               0x0203
    #define GL_GREATER                                              0x0204
    #define GL_NOTEQUAL                                             0x0205
    #define GL_GEQUAL                                               0x0206
    #define GL_ALWAYS                                               0x0207

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL operators constants                                            //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_ACCUM                                                0x0100
    #define GL_LOAD                                                 0x0101
    #define GL_RETURN                                               0x0102
    #define GL_MULT                                                 0x0103
    #define GL_ADD                                                  0x0104
    #define GL_SUBTRACT                                             0x84E7

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL rendering constants                                            //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_POINTS                                               0x0000
    #define GL_LINES                                                0x0001
    #define GL_LINE_LOOP                                            0x0002
    #define GL_LINE_STRIP                                           0x0003
    #define GL_TRIANGLES                                            0x0004
    #define GL_TRIANGLE_STRIP                                       0x0005
    #define GL_TRIANGLE_FAN                                         0x0006
    #define GL_QUADS                                                0x0007
    #define GL_QUAD_STRIP                                           0x0008
    #define GL_POLYGON                                              0x0009
    #define GL_DONT_CARE                                            0x1100
    #define GL_FASTEST                                              0x1101
    #define GL_NICEST                                               0x1102
    #define GL_AMBIENT                                              0x1200
    #define GL_DIFFUSE                                              0x1201
    #define GL_SPECULAR                                             0x1202
    #define GL_POSITION                                             0x1203
    #define GL_SPOT_DIRECTION                                       0x1204
    #define GL_SPOT_EXPONENT                                        0x1205
    #define GL_SPOT_CUTOFF                                          0x1206
    #define GL_CONSTANT_ATTENUATION                                 0x1207
    #define GL_LINEAR_ATTENUATION                                   0x1208
    #define GL_QUADRATIC_ATTENUATION                                0x1209
    #define GL_QUERY_WAIT                                           0x8E13
    #define GL_QUERY_NO_WAIT                                        0x8E14
    #define GL_QUERY_BY_REGION_WAIT                                 0x8E15
    #define GL_QUERY_BY_REGION_NO_WAIT                              0x8E16
    #define GL_ATTRIB_STACK_DEPTH                                   0x0BB0
    #define GL_CLIENT_ATTRIB_STACK_DEPTH                            0x0BB1
    #define GL_INDEX_MODE                                           0x0C30
    #define GL_RGBA_MODE                                            0x0C31
    #define GL_RENDER_MODE                                          0x0C40
    #define GL_PERSPECTIVE_CORRECTION_HINT                          0x0C50
    #define GL_POINT_SMOOTH_HINT                                    0x0C51
    #define GL_LINE_SMOOTH_HINT                                     0x0C52
    #define GL_POLYGON_SMOOTH_HINT                                  0x0C53
    #define GL_FOG_HINT                                             0x0C54

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL flags constants                                                //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_CURRENT_BIT                                          0x00000001
    #define GL_CLIENT_PIXEL_STORE_BIT                               0x00000001
    #define GL_POINT_BIT                                            0x00000002
    #define GL_CLIENT_VERTEX_ARRAY_BIT                              0x00000002
    #define GL_LINE_BIT                                             0x00000004
    #define GL_POLYGON_BIT                                          0x00000008
    #define GL_POLYGON_STIPPLE_BIT                                  0x00000010
    #define GL_PIXEL_MODE_BIT                                       0x00000020
    #define GL_LIGHTING_BIT                                         0x00000040
    #define GL_FOG_BIT                                              0x00000080
    #define GL_DEPTH_BUFFER_BIT                                     0x00000100
    #define GL_ACCUM_BUFFER_BIT                                     0x00000200
    #define GL_STENCIL_BUFFER_BIT                                   0x00000400
    #define GL_VIEWPORT_BIT                                         0x00000800
    #define GL_TRANSFORM_BIT                                        0x00001000
    #define GL_ENABLE_BIT                                           0x00002000
    #define GL_COLOR_BUFFER_BIT                                     0x00004000
    #define GL_HINT_BIT                                             0x00008000
    #define GL_EVAL_BIT                                             0x00010000
    #define GL_LIST_BIT                                             0x00020000
    #define GL_TEXTURE_BIT                                          0x00040000
    #define GL_SCISSOR_BIT                                          0x00080000
    #define GL_MULTISAMPLE_BIT                                      0x20000000
    #define GL_ALL_ATTRIB_BITS                                      0x000FFFFF
    #define GL_CLIENT_ALL_ATTRIB_BITS                               0xFFFFFFFF

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL alpha blending constants                                       //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_SRC_COLOR                                            0x0300
    #define GL_ONE_MINUS_SRC_COLOR                                  0x0301
    #define GL_SRC_ALPHA                                            0x0302
    #define GL_ONE_MINUS_SRC_ALPHA                                  0x0303
    #define GL_DST_ALPHA                                            0x0304
    #define GL_ONE_MINUS_DST_ALPHA                                  0x0305
    #define GL_DST_COLOR                                            0x0306
    #define GL_ONE_MINUS_DST_COLOR                                  0x0307
    #define GL_SRC_ALPHA_SATURATE                                   0x0308
    #define GL_ALPHA_TEST                                           0x0BC0
    #define GL_ALPHA_TEST_FUNC                                      0x0BC1
    #define GL_ALPHA_TEST_REF                                       0x0BC2
    #define GL_DITHER                                               0x0BD0
    #define GL_BLEND_DST                                            0x0BE0
    #define GL_BLEND_SRC                                            0x0BE1
    #define GL_BLEND                                                0x0BE2
    #define GL_BLEND_DST_RGB                                        0x80C8
    #define GL_BLEND_SRC_RGB                                        0x80C9
    #define GL_BLEND_DST_ALPHA                                      0x80CA
    #define GL_BLEND_SRC_ALPHA                                      0x80CB
    #define GL_BLEND_EQUATION_RGB                                   0x8009
    #define GL_BLEND_EQUATION_ALPHA                                 0x883D

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL faces constants                                                //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_FRONT_LEFT                                           0x0400
    #define GL_FRONT_RIGHT                                          0x0401
    #define GL_BACK_LEFT                                            0x0402
    #define GL_BACK_RIGHT                                           0x0403
    #define GL_FRONT                                                0x0404
    #define GL_BACK                                                 0x0405
    #define GL_LEFT                                                 0x0406
    #define GL_RIGHT                                                0x0407
    #define GL_FRONT_AND_BACK                                       0x0408
    #define GL_AUX0                                                 0x0409
    #define GL_AUX1                                                 0x040A
    #define GL_AUX2                                                 0x040B
    #define GL_AUX3                                                 0x040C

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL errors constants                                               //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_INVALID_ENUM                                         0x0500
    #define GL_INVALID_VALUE                                        0x0501
    #define GL_INVALID_OPERATION                                    0x0502
    #define GL_STACK_OVERFLOW                                       0x0503
    #define GL_STACK_UNDERFLOW                                      0x0504
    #define GL_OUT_OF_MEMORY                                        0x0505

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL dimensional constants                                          //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_2D                                                   0x0600
    #define GL_3D                                                   0x0601
    #define GL_3D_COLOR                                             0x0602
    #define GL_3D_COLOR_TEXTURE                                     0x0603
    #define GL_4D_COLOR_TEXTURE                                     0x0604

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL tokens constants                                               //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_PASS_THROUGH_TOKEN                                   0x0700
    #define GL_POINT_TOKEN                                          0x0701
    #define GL_LINE_TOKEN                                           0x0702
    #define GL_POLYGON_TOKEN                                        0x0703
    #define GL_BITMAP_TOKEN                                         0x0704
    #define GL_DRAW_PIXEL_TOKEN                                     0x0705
    #define GL_COPY_PIXEL_TOKEN                                     0x0706
    #define GL_LINE_RESET_TOKEN                                     0x0707

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL current constants                                              //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_CURRENT_COLOR                                        0x0B00
    #define GL_CURRENT_INDEX                                        0x0B01
    #define GL_CURRENT_NORMAL                                       0x0B02
    #define GL_CURRENT_TEXTURE_COORDS                               0x0B03
    #define GL_CURRENT_RASTER_COLOR                                 0x0B04
    #define GL_CURRENT_RASTER_INDEX                                 0x0B05
    #define GL_CURRENT_RASTER_TEXTURE_COORDS                        0x0B06
    #define GL_CURRENT_RASTER_POSITION                              0x0B07
    #define GL_CURRENT_RASTER_POSITION_VALID                        0x0B08
    #define GL_CURRENT_RASTER_DISTANCE                              0x0B09
    #define GL_CURRENT_RASTER_SECONDARY_COLOR                       0x845F

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL points and lines constants                                     //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_POINT_SMOOTH                                         0x0B10
    #define GL_POINT_SIZE                                           0x0B11
    #define GL_POINT_SIZE_RANGE                                     0x0B12
    #define GL_POINT_SIZE_GRANULARITY                               0x0B13
    #define GL_LINE_SMOOTH                                          0x0B20
    #define GL_LINE_WIDTH                                           0x0B21
    #define GL_LINE_WIDTH_RANGE                                     0x0B22
    #define GL_LINE_WIDTH_GRANULARITY                               0x0B23
    #define GL_LINE_STIPPLE                                         0x0B24
    #define GL_LINE_STIPPLE_PATTERN                                 0x0B25
    #define GL_LINE_STIPPLE_REPEAT                                  0x0B26
    #define GL_SMOOTH_POINT_SIZE_RANGE                              0x0B12
    #define GL_SMOOTH_POINT_SIZE_GRANULARITY                        0x0B13
    #define GL_SMOOTH_LINE_WIDTH_RANGE                              0x0B22
    #define GL_SMOOTH_LINE_WIDTH_GRANULARITY                        0x0B23
    #define GL_ALIASED_POINT_SIZE_RANGE                             0x846D
    #define GL_ALIASED_LINE_WIDTH_RANGE                             0x846E
    #define GL_POINT_SIZE_MIN                                       0x8126
    #define GL_POINT_SIZE_MAX                                       0x8127
    #define GL_POINT_FADE_THRESHOLD_SIZE                            0x8128
    #define GL_POINT_DISTANCE_ATTENUATION                           0x8129
    #define GL_POINT_SPRITE                                         0x8861
    #define GL_COORD_REPLACE                                        0x8862
    #define GL_POINT_SPRITE_COORD_ORIGIN                            0x8CA0
    #define GL_LOWER_LEFT                                           0x8CA1
    #define GL_UPPER_LEFT                                           0x8CA2

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL lists constants                                                //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_LIST_MODE                                            0x0B30
    #define GL_MAX_LIST_NESTING                                     0x0B31
    #define GL_LIST_BASE                                            0x0B32
    #define GL_LIST_INDEX                                           0x0B33

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL polygons constants                                             //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_POLYGON_MODE                                         0x0B40
    #define GL_POLYGON_SMOOTH                                       0x0B41
    #define GL_POLYGON_STIPPLE                                      0x0B42
    #define GL_EDGE_FLAG                                            0x0B43
    #define GL_CULL_FACE                                            0x0B44
    #define GL_CULL_FACE_MODE                                       0x0B45
    #define GL_FRONT_FACE                                           0x0B46
    #define GL_SCISSOR_BOX                                          0x0C10
    #define GL_SCISSOR_TEST                                         0x0C11
    #define GL_POLYGON_OFFSET_FILL                                  0x8037
    #define GL_POLYGON_OFFSET_FACTOR                                0x8038
    #define GL_CLIP_PLANE0                                          0x3000
    #define GL_CLIP_PLANE1                                          0x3001
    #define GL_CLIP_PLANE2                                          0x3002
    #define GL_CLIP_PLANE3                                          0x3003
    #define GL_CLIP_PLANE4                                          0x3004
    #define GL_CLIP_PLANE5                                          0x3005
    #define GL_POLYGON_OFFSET_UNITS                                 0x2A00
    #define GL_POLYGON_OFFSET_POINT                                 0x2A01
    #define GL_POLYGON_OFFSET_LINE                                  0x2A02

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL buffers constants                                              //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_AUX_BUFFERS                                          0x0C00
    #define GL_DRAW_BUFFER                                          0x0C01
    #define GL_READ_BUFFER                                          0x0C02
    #define GL_DOUBLEBUFFER                                         0x0C32
    #define GL_BUFFER_SIZE                                          0x8764
    #define GL_BUFFER_USAGE                                         0x8765
    #define GL_QUERY_COUNTER_BITS                                   0x8864
    #define GL_CURRENT_QUERY                                        0x8865
    #define GL_QUERY_RESULT                                         0x8866
    #define GL_QUERY_RESULT_AVAILABLE                               0x8867
    #define GL_ARRAY_BUFFER                                         0x8892
    #define GL_ELEMENT_ARRAY_BUFFER                                 0x8893
    #define GL_ARRAY_BUFFER_BINDING                                 0x8894
    #define GL_ELEMENT_ARRAY_BUFFER_BINDING                         0x8895
    #define GL_VERTEX_ARRAY_BUFFER_BINDING                          0x8896
    #define GL_NORMAL_ARRAY_BUFFER_BINDING                          0x8897
    #define GL_COLOR_ARRAY_BUFFER_BINDING                           0x8898
    #define GL_INDEX_ARRAY_BUFFER_BINDING                           0x8899
    #define GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING                   0x889A
    #define GL_EDGE_FLAG_ARRAY_BUFFER_BINDING                       0x889B
    #define GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING                 0x889C
    #define GL_WEIGHT_ARRAY_BUFFER_BINDING                          0x889E
    #define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING                   0x889F
    #define GL_READ_ONLY                                            0x88B8
    #define GL_WRITE_ONLY                                           0x88B9
    #define GL_READ_WRITE                                           0x88BA
    #define GL_BUFFER_ACCESS                                        0x88BB
    #define GL_BUFFER_MAPPED                                        0x88BC
    #define GL_BUFFER_MAP_POINTER                                   0x88BD
    #define GL_STREAM_DRAW                                          0x88E0
    #define GL_STREAM_READ                                          0x88E1
    #define GL_STREAM_COPY                                          0x88E2
    #define GL_STATIC_DRAW                                          0x88E4
    #define GL_STATIC_READ                                          0x88E5
    #define GL_STATIC_COPY                                          0x88E6
    #define GL_DYNAMIC_DRAW                                         0x88E8
    #define GL_DYNAMIC_READ                                         0x88E9
    #define GL_DYNAMIC_COPY                                         0x88EA
    #define GL_SAMPLES_PASSED                                       0x8914
    #define GL_VERTEX_ATTRIB_ARRAY_ENABLED                          0x8622
    #define GL_VERTEX_ATTRIB_ARRAY_SIZE                             0x8623
    #define GL_VERTEX_ATTRIB_ARRAY_STRIDE                           0x8624
    #define GL_VERTEX_ATTRIB_ARRAY_TYPE                             0x8625
    #define GL_CURRENT_VERTEX_ATTRIB                                0x8626
    #define GL_VERTEX_PROGRAM_POINT_SIZE                            0x8642
    #define GL_VERTEX_PROGRAM_TWO_SIDE                              0x8643
    #define GL_VERTEX_ATTRIB_ARRAY_POINTER                          0x8645
    #define GL_DRAW_BUFFER0                                         0x8825
    #define GL_DRAW_BUFFER1                                         0x8826
    #define GL_DRAW_BUFFER2                                         0x8827
    #define GL_DRAW_BUFFER3                                         0x8828
    #define GL_DRAW_BUFFER4                                         0x8829
    #define GL_DRAW_BUFFER5                                         0x882A
    #define GL_DRAW_BUFFER6                                         0x882B
    #define GL_DRAW_BUFFER7                                         0x882C
    #define GL_DRAW_BUFFER8                                         0x882D
    #define GL_DRAW_BUFFER9                                         0x882E
    #define GL_DRAW_BUFFER10                                        0x882F
    #define GL_DRAW_BUFFER11                                        0x8830
    #define GL_DRAW_BUFFER12                                        0x8831
    #define GL_DRAW_BUFFER13                                        0x8832
    #define GL_DRAW_BUFFER14                                        0x8833
    #define GL_DRAW_BUFFER15                                        0x8834
    #define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED                       0x886A
    #define GL_DEPTH_BUFFER                                         0x8223
    #define GL_STENCIL_BUFFER                                       0x8224
    #define GL_CLIP_DISTANCE0                                       0x3000
    #define GL_CLIP_DISTANCE1                                       0x3001
    #define GL_CLIP_DISTANCE2                                       0x3002
    #define GL_CLIP_DISTANCE3                                       0x3003
    #define GL_CLIP_DISTANCE4                                       0x3004
    #define GL_CLIP_DISTANCE5                                       0x3005
    #define GL_VERTEX_ATTRIB_ARRAY_INTEGER                          0x88FD
    #define GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH                0x8C76
    #define GL_TRANSFORM_FEEDBACK_BUFFER_MODE                       0x8C7F
    #define GL_TRANSFORM_FEEDBACK_VARYINGS                          0x8C83
    #define GL_TRANSFORM_FEEDBACK_BUFFER_START                      0x8C84
    #define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE                       0x8C85
    #define GL_PRIMITIVES_GENERATED                                 0x8C87
    #define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN                0x8C88
    #define GL_RASTERIZER_DISCARD                                   0x8C89
    #define GL_INTERLEAVED_ATTRIBS                                  0x8C8C
    #define GL_SEPARATE_ATTRIBS                                     0x8C8D
    #define GL_TRANSFORM_FEEDBACK_BUFFER                            0x8C8E
    #define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING                    0x8C8F

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL lighting constants                                             //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_LIGHTING                                             0x0B50
    #define GL_LIGHT_MODEL_LOCAL_VIEWER                             0x0B51
    #define GL_LIGHT_MODEL_TWO_SIDE                                 0x0B52
    #define GL_LIGHT_MODEL_AMBIENT                                  0x0B53
    #define GL_SHADE_MODEL                                          0x0B54
    #define GL_COLOR_MATERIAL_FACE                                  0x0B55
    #define GL_COLOR_MATERIAL_PARAMETER                             0x0B56
    #define GL_COLOR_MATERIAL                                       0x0B57
    #define GL_LIGHT0                                               0x4000
    #define GL_LIGHT1                                               0x4001
    #define GL_LIGHT2                                               0x4002
    #define GL_LIGHT3                                               0x4003
    #define GL_LIGHT4                                               0x4004
    #define GL_LIGHT5                                               0x4005
    #define GL_LIGHT6                                               0x4006
    #define GL_LIGHT7                                               0x4007
    #define GL_LIGHT_MODEL_COLOR_CONTROL                            0x81F8
    #define GL_SINGLE_COLOR                                         0x81F9
    #define GL_SEPARATE_SPECULAR_COLOR                              0x81FA

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL fog constants                                                  //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_FOG                                                  0x0B60
    #define GL_FOG_INDEX                                            0x0B61
    #define GL_FOG_DENSITY                                          0x0B62
    #define GL_FOG_START                                            0x0B63
    #define GL_FOG_END                                              0x0B64
    #define GL_FOG_MODE                                             0x0B65
    #define GL_FOG_COLOR                                            0x0B66
    #define GL_FOG_COORDINATE_SOURCE                                0x8450
    #define GL_FOG_COORDINATE                                       0x8451
    #define GL_FRAGMENT_DEPTH                                       0x8452
    #define GL_CURRENT_FOG_COORDINATE                               0x8453
    #define GL_FOG_COORDINATE_ARRAY_TYPE                            0x8454
    #define GL_FOG_COORDINATE_ARRAY_STRIDE                          0x8455
    #define GL_FOG_COORDINATE_ARRAY_POINTER                         0x8456
    #define GL_FOG_COORDINATE_ARRAY                                 0x8457
    #define GL_CURRENT_FOG_COORD                                    0x8453
    #define GL_FOG_COORD                                            0x8451
    #define GL_FOG_COORD_ARRAY                                      0x8457
    #define GL_FOG_COORD_ARRAY_BUFFER_BINDING                       0x889D
    #define GL_FOG_COORD_ARRAY_POINTER                              0x8456
    #define GL_FOG_COORD_ARRAY_STRIDE                               0x8455
    #define GL_FOG_COORD_ARRAY_TYPE                                 0x8454
    #define GL_FOG_COORD_SRC                                        0x8450
    #define GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING                  0x889D

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL depth constants                                                //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_DEPTH_RANGE                                          0x0B70
    #define GL_DEPTH_TEST                                           0x0B71
    #define GL_DEPTH_WRITEMASK                                      0x0B72
    #define GL_DEPTH_CLEAR_VALUE                                    0x0B73
    #define GL_DEPTH_FUNC                                           0x0B74
    #define GL_DEPTH_STENCIL                                        0x84F9
    #define GL_DEPTH24_STENCIL8                                     0x88F0

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL stencil constants                                              //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_STENCIL_TEST                                         0x0B90
    #define GL_STENCIL_CLEAR_VALUE                                  0x0B91
    #define GL_STENCIL_FUNC                                         0x0B92
    #define GL_STENCIL_VALUE_MASK                                   0x0B93
    #define GL_STENCIL_FAIL                                         0x0B94
    #define GL_STENCIL_PASS_DEPTH_FAIL                              0x0B95
    #define GL_STENCIL_PASS_DEPTH_PASS                              0x0B96
    #define GL_STENCIL_REF                                          0x0B97
    #define GL_STENCIL_WRITEMASK                                    0x0B98
    #define GL_STENCIL_BACK_FUNC                                    0x8800
    #define GL_STENCIL_BACK_FAIL                                    0x8801
    #define GL_STENCIL_BACK_PASS_DEPTH_FAIL                         0x8802
    #define GL_STENCIL_BACK_PASS_DEPTH_PASS                         0x8803
    #define GL_STENCIL_BACK_REF                                     0x8CA3
    #define GL_STENCIL_BACK_VALUE_MASK                              0x8CA4
    #define GL_STENCIL_BACK_WRITEMASK                               0x8CA5
    #define GL_STENCIL_INDEX1                                       0x8D46
    #define GL_STENCIL_INDEX4                                       0x8D47
    #define GL_STENCIL_INDEX8                                       0x8D48
    #define GL_STENCIL_INDEX16                                      0x8D49

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL matrices constants                                             //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_MATRIX_MODE                                          0x0BA0
    #define GL_NORMALIZE                                            0x0BA1
    #define GL_VIEWPORT                                             0x0BA2
    #define GL_MODELVIEW_STACK_DEPTH                                0x0BA3
    #define GL_PROJECTION_STACK_DEPTH                               0x0BA4
    #define GL_TEXTURE_STACK_DEPTH                                  0x0BA5
    #define GL_MODELVIEW_MATRIX                                     0x0BA6
    #define GL_PROJECTION_MATRIX                                    0x0BA7
    #define GL_TEXTURE_MATRIX                                       0x0BA8
    #define GL_TRANSPOSE_MODELVIEW_MATRIX                           0x84E3
    #define GL_TRANSPOSE_PROJECTION_MATRIX                          0x84E4
    #define GL_TRANSPOSE_TEXTURE_MATRIX                             0x84E5
    #define GL_TRANSPOSE_COLOR_MATRIX                               0x84E6
    #define GL_FLOAT_MAT2x3                                         0x8B65
    #define GL_FLOAT_MAT2x4                                         0x8B66
    #define GL_FLOAT_MAT3x2                                         0x8B67
    #define GL_FLOAT_MAT3x4                                         0x8B68
    #define GL_FLOAT_MAT4x2                                         0x8B69
    #define GL_FLOAT_MAT4x3                                         0x8B6A

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL textures constants                                             //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_TEXTURE_COMPONENTS                                   0x1003
    #define GL_INDEX_CLEAR_VALUE                                    0x0C20
    #define GL_INDEX_WRITEMASK                                      0x0C21
    #define GL_COLOR_CLEAR_VALUE                                    0x0C22
    #define GL_COLOR_WRITEMASK                                      0x0C23
    #define GL_STEREO                                               0x0C33
    #define GL_TEXTURE_GEN_S                                        0x0C60
    #define GL_TEXTURE_GEN_T                                        0x0C61
    #define GL_TEXTURE_GEN_R                                        0x0C62
    #define GL_TEXTURE_GEN_Q                                        0x0C63
    #define GL_PIXEL_MAP_I_TO_I                                     0x0C70
    #define GL_PIXEL_MAP_S_TO_S                                     0x0C71
    #define GL_PIXEL_MAP_I_TO_R                                     0x0C72
    #define GL_PIXEL_MAP_I_TO_G                                     0x0C73
    #define GL_PIXEL_MAP_I_TO_B                                     0x0C74
    #define GL_PIXEL_MAP_I_TO_A                                     0x0C75
    #define GL_PIXEL_MAP_R_TO_R                                     0x0C76
    #define GL_PIXEL_MAP_G_TO_G                                     0x0C77
    #define GL_PIXEL_MAP_B_TO_B                                     0x0C78
    #define GL_PIXEL_MAP_A_TO_A                                     0x0C79
    #define GL_PIXEL_MAP_I_TO_I_SIZE                                0x0CB0
    #define GL_PIXEL_MAP_S_TO_S_SIZE                                0x0CB1
    #define GL_PIXEL_MAP_I_TO_R_SIZE                                0x0CB2
    #define GL_PIXEL_MAP_I_TO_G_SIZE                                0x0CB3
    #define GL_PIXEL_MAP_I_TO_B_SIZE                                0x0CB4
    #define GL_PIXEL_MAP_I_TO_A_SIZE                                0x0CB5
    #define GL_PIXEL_MAP_R_TO_R_SIZE                                0x0CB6
    #define GL_PIXEL_MAP_G_TO_G_SIZE                                0x0CB7
    #define GL_PIXEL_MAP_B_TO_B_SIZE                                0x0CB8
    #define GL_PIXEL_MAP_A_TO_A_SIZE                                0x0CB9
    #define GL_UNPACK_SWAP_BYTES                                    0x0CF0
    #define GL_UNPACK_LSB_FIRST                                     0x0CF1
    #define GL_UNPACK_ROW_LENGTH                                    0x0CF2
    #define GL_UNPACK_SKIP_ROWS                                     0x0CF3
    #define GL_UNPACK_SKIP_PIXELS                                   0x0CF4
    #define GL_UNPACK_ALIGNMENT                                     0x0CF5
    #define GL_PACK_SWAP_BYTES                                      0x0D00
    #define GL_PACK_LSB_FIRST                                       0x0D01
    #define GL_PACK_ROW_LENGTH                                      0x0D02
    #define GL_PACK_SKIP_ROWS                                       0x0D03
    #define GL_PACK_SKIP_PIXELS                                     0x0D04
    #define GL_PACK_ALIGNMENT                                       0x0D05
    #define GL_MAP_COLOR                                            0x0D10
    #define GL_MAP_STENCIL                                          0x0D11
    #define GL_INDEX_SHIFT                                          0x0D12
    #define GL_INDEX_OFFSET                                         0x0D13
    #define GL_RED_SCALE                                            0x0D14
    #define GL_RED_BIAS                                             0x0D15
    #define GL_ZOOM_X                                               0x0D16
    #define GL_ZOOM_Y                                               0x0D17
    #define GL_GREEN_SCALE                                          0x0D18
    #define GL_GREEN_BIAS                                           0x0D19
    #define GL_BLUE_SCALE                                           0x0D1A
    #define GL_BLUE_BIAS                                            0x0D1B
    #define GL_ALPHA_SCALE                                          0x0D1C
    #define GL_ALPHA_BIAS                                           0x0D1D
    #define GL_DEPTH_SCALE                                          0x0D1E
    #define GL_DEPTH_BIAS                                           0x0D1F
    #define GL_SUBPIXEL_BITS                                        0x0D50
    #define GL_INDEX_BITS                                           0x0D51
    #define GL_RED_BITS                                             0x0D52
    #define GL_GREEN_BITS                                           0x0D53
    #define GL_BLUE_BITS                                            0x0D54
    #define GL_ALPHA_BITS                                           0x0D55
    #define GL_DEPTH_BITS                                           0x0D56
    #define GL_STENCIL_BITS                                         0x0D57
    #define GL_ACCUM_RED_BITS                                       0x0D58
    #define GL_ACCUM_GREEN_BITS                                     0x0D59
    #define GL_ACCUM_BLUE_BITS                                      0x0D5A
    #define GL_ACCUM_ALPHA_BITS                                     0x0D5B
    #define GL_ACCUM_CLEAR_VALUE                                    0x0B80
    #define GL_NAME_STACK_DEPTH                                     0x0D70
    #define GL_AUTO_NORMAL                                          0x0D80
    #define GL_MAP1_COLOR_4                                         0x0D90
    #define GL_MAP1_INDEX                                           0x0D91
    #define GL_MAP1_NORMAL                                          0x0D92
    #define GL_MAP1_TEXTURE_COORD_1                                 0x0D93
    #define GL_MAP1_TEXTURE_COORD_2                                 0x0D94
    #define GL_MAP1_TEXTURE_COORD_3                                 0x0D95
    #define GL_MAP1_TEXTURE_COORD_4                                 0x0D96
    #define GL_MAP1_VERTEX_3                                        0x0D97
    #define GL_MAP1_VERTEX_4                                        0x0D98
    #define GL_MAP2_COLOR_4                                         0x0DB0
    #define GL_MAP2_INDEX                                           0x0DB1
    #define GL_MAP2_NORMAL                                          0x0DB2
    #define GL_MAP2_TEXTURE_COORD_1                                 0x0DB3
    #define GL_MAP2_TEXTURE_COORD_2                                 0x0DB4
    #define GL_MAP2_TEXTURE_COORD_3                                 0x0DB5
    #define GL_MAP2_TEXTURE_COORD_4                                 0x0DB6
    #define GL_MAP2_VERTEX_3                                        0x0DB7
    #define GL_MAP2_VERTEX_4                                        0x0DB8
    #define GL_MAP1_GRID_DOMAIN                                     0x0DD0
    #define GL_MAP1_GRID_SEGMENTS                                   0x0DD1
    #define GL_MAP2_GRID_DOMAIN                                     0x0DD2
    #define GL_MAP2_GRID_SEGMENTS                                   0x0DD3
    #define GL_TEXTURE_1D                                           0x0DE0
    #define GL_TEXTURE_2D                                           0x0DE1
    #define GL_FEEDBACK_BUFFER_POINTER                              0x0DF0
    #define GL_FEEDBACK_BUFFER_SIZE                                 0x0DF1
    #define GL_FEEDBACK_BUFFER_TYPE                                 0x0DF2
    #define GL_SELECTION_BUFFER_POINTER                             0x0DF3
    #define GL_SELECTION_BUFFER_SIZE                                0x0DF4
    #define GL_TEXTURE_WIDTH                                        0x1000
    #define GL_TEXTURE_HEIGHT                                       0x1001
    #define GL_TEXTURE_INTERNAL_FORMAT                              0x1003
    #define GL_TEXTURE_BORDER_COLOR                                 0x1004
    #define GL_TEXTURE_BORDER                                       0x1005
    #define GL_ALPHA4                                               0x803B
    #define GL_ALPHA8                                               0x803C
    #define GL_ALPHA12                                              0x803D
    #define GL_ALPHA16                                              0x803E
    #define GL_LUMINANCE4                                           0x803F
    #define GL_LUMINANCE8                                           0x8040
    #define GL_LUMINANCE12                                          0x8041
    #define GL_LUMINANCE16                                          0x8042
    #define GL_LUMINANCE4_ALPHA4                                    0x8043
    #define GL_LUMINANCE6_ALPHA2                                    0x8044
    #define GL_LUMINANCE8_ALPHA8                                    0x8045
    #define GL_LUMINANCE12_ALPHA4                                   0x8046
    #define GL_LUMINANCE12_ALPHA12                                  0x8047
    #define GL_LUMINANCE16_ALPHA16                                  0x8048
    #define GL_INTENSITY                                            0x8049
    #define GL_INTENSITY4                                           0x804A
    #define GL_INTENSITY8                                           0x804B
    #define GL_INTENSITY12                                          0x804C
    #define GL_INTENSITY16                                          0x804D
    #define GL_RGB4                                                 0x804F
    #define GL_RGB5                                                 0x8050
    #define GL_RGB8                                                 0x8051
    #define GL_RGB10                                                0x8052
    #define GL_RGB12                                                0x8053
    #define GL_RGB16                                                0x8054
    #define GL_RGBA2                                                0x8055
    #define GL_RGBA4                                                0x8056
    #define GL_RGB5_A1                                              0x8057
    #define GL_RGBA8                                                0x8058
    #define GL_RGB10_A2                                             0x8059
    #define GL_RGBA12                                               0x805A
    #define GL_RGBA16                                               0x805B
    #define GL_TEXTURE_RED_SIZE                                     0x805C
    #define GL_TEXTURE_GREEN_SIZE                                   0x805D
    #define GL_TEXTURE_BLUE_SIZE                                    0x805E
    #define GL_TEXTURE_ALPHA_SIZE                                   0x805F
    #define GL_TEXTURE_LUMINANCE_SIZE                               0x8060
    #define GL_TEXTURE_INTENSITY_SIZE                               0x8061
    #define GL_PROXY_TEXTURE_1D                                     0x8063
    #define GL_PROXY_TEXTURE_2D                                     0x8064
    #define GL_TEXTURE_PRIORITY                                     0x8066
    #define GL_TEXTURE_RESIDENT                                     0x8067
    #define GL_TEXTURE_BINDING_1D                                   0x8068
    #define GL_TEXTURE_BINDING_2D                                   0x8069
    #define GL_COLOR_INDEX1_EXT                                     0x80E2
    #define GL_COLOR_INDEX2_EXT                                     0x80E3
    #define GL_COLOR_INDEX4_EXT                                     0x80E4
    #define GL_COLOR_INDEX8_EXT                                     0x80E5
    #define GL_COLOR_INDEX12_EXT                                    0x80E6
    #define GL_COLOR_INDEX16_EXT                                    0x80E7
    #define GL_S                                                    0x2000
    #define GL_T                                                    0x2001
    #define GL_R                                                    0x2002
    #define GL_Q                                                    0x2003
    #define GL_MODULATE                                             0x2100
    #define GL_DECAL                                                0x2101
    #define GL_TEXTURE_ENV_MODE                                     0x2200
    #define GL_TEXTURE_ENV_COLOR                                    0x2201
    #define GL_TEXTURE_ENV                                          0x2300
    #define GL_EYE_LINEAR                                           0x2400
    #define GL_OBJECT_LINEAR                                        0x2401
    #define GL_SPHERE_MAP                                           0x2402
    #define GL_TEXTURE_GEN_MODE                                     0x2500
    #define GL_OBJECT_PLANE                                         0x2501
    #define GL_EYE_PLANE                                            0x2502
    #define GL_NEAREST                                              0x2600
    #define GL_LINEAR                                               0x2601
    #define GL_NEAREST_MIPMAP_NEAREST                               0x2700
    #define GL_LINEAR_MIPMAP_NEAREST                                0x2701
    #define GL_NEAREST_MIPMAP_LINEAR                                0x2702
    #define GL_LINEAR_MIPMAP_LINEAR                                 0x2703
    #define GL_TEXTURE_MAG_FILTER                                   0x2800
    #define GL_TEXTURE_MIN_FILTER                                   0x2801
    #define GL_TEXTURE_WRAP_S                                       0x2802
    #define GL_TEXTURE_WRAP_T                                       0x2803
    #define GL_CLAMP                                                0x2900
    #define GL_REPEAT                                               0x2901
    #define GL_MAX_3D_TEXTURE_SIZE                                  0x8073
    #define GL_BGR                                                  0x80E0
    #define GL_BGRA                                                 0x80E1
    #define GL_CLAMP_TO_EDGE                                        0x812F
    #define GL_TEXTURE_MIN_LOD                                      0x813A
    #define GL_TEXTURE_MAX_LOD                                      0x813B
    #define GL_TEXTURE_BASE_LEVEL                                   0x813C
    #define GL_TEXTURE_MAX_LEVEL                                    0x813D
    #define GL_RESCALE_NORMAL                                       0x803A
    #define GL_TEXTURE_BINDING_3D                                   0x806A
    #define GL_PACK_SKIP_IMAGES                                     0x806B
    #define GL_PACK_IMAGE_HEIGHT                                    0x806C
    #define GL_UNPACK_SKIP_IMAGES                                   0x806D
    #define GL_UNPACK_IMAGE_HEIGHT                                  0x806E
    #define GL_TEXTURE_3D                                           0x806F
    #define GL_PROXY_TEXTURE_3D                                     0x8070
    #define GL_TEXTURE_DEPTH                                        0x8071
    #define GL_TEXTURE_WRAP_R                                       0x8072
    #define GL_MULTISAMPLE                                          0x809D
    #define GL_SAMPLE_ALPHA_TO_COVERAGE                             0x809E
    #define GL_SAMPLE_ALPHA_TO_ONE                                  0x809F
    #define GL_SAMPLE_COVERAGE                                      0x80A0
    #define GL_SAMPLE_BUFFERS                                       0x80A8
    #define GL_SAMPLES                                              0x80A9
    #define GL_SAMPLE_COVERAGE_VALUE                                0x80AA
    #define GL_SAMPLE_COVERAGE_INVERT                               0x80AB
    #define GL_CLAMP_TO_BORDER                                      0x812D
    #define GL_TEXTURE0                                             0x84C0
    #define GL_TEXTURE1                                             0x84C1
    #define GL_TEXTURE2                                             0x84C2
    #define GL_TEXTURE3                                             0x84C3
    #define GL_TEXTURE4                                             0x84C4
    #define GL_TEXTURE5                                             0x84C5
    #define GL_TEXTURE6                                             0x84C6
    #define GL_TEXTURE7                                             0x84C7
    #define GL_TEXTURE8                                             0x84C8
    #define GL_TEXTURE9                                             0x84C9
    #define GL_TEXTURE10                                            0x84CA
    #define GL_TEXTURE11                                            0x84CB
    #define GL_TEXTURE12                                            0x84CC
    #define GL_TEXTURE13                                            0x84CD
    #define GL_TEXTURE14                                            0x84CE
    #define GL_TEXTURE15                                            0x84CF
    #define GL_TEXTURE16                                            0x84D0
    #define GL_TEXTURE17                                            0x84D1
    #define GL_TEXTURE18                                            0x84D2
    #define GL_TEXTURE19                                            0x84D3
    #define GL_TEXTURE20                                            0x84D4
    #define GL_TEXTURE21                                            0x84D5
    #define GL_TEXTURE22                                            0x84D6
    #define GL_TEXTURE23                                            0x84D7
    #define GL_TEXTURE24                                            0x84D8
    #define GL_TEXTURE25                                            0x84D9
    #define GL_TEXTURE26                                            0x84DA
    #define GL_TEXTURE27                                            0x84DB
    #define GL_TEXTURE28                                            0x84DC
    #define GL_TEXTURE29                                            0x84DD
    #define GL_TEXTURE30                                            0x84DE
    #define GL_TEXTURE31                                            0x84DF
    #define GL_ACTIVE_TEXTURE                                       0x84E0
    #define GL_CLIENT_ACTIVE_TEXTURE                                0x84E1
    #define GL_COMPRESSED_ALPHA                                     0x84E9
    #define GL_COMPRESSED_LUMINANCE                                 0x84EA
    #define GL_COMPRESSED_LUMINANCE_ALPHA                           0x84EB
    #define GL_COMPRESSED_INTENSITY                                 0x84EC
    #define GL_COMPRESSED_RGB                                       0x84ED
    #define GL_COMPRESSED_RGBA                                      0x84EE
    #define GL_TEXTURE_COMPRESSION_HINT                             0x84EF
    #define GL_NORMAL_MAP                                           0x8511
    #define GL_REFLECTION_MAP                                       0x8512
    #define GL_TEXTURE_CUBE_MAP                                     0x8513
    #define GL_TEXTURE_BINDING_CUBE_MAP                             0x8514
    #define GL_TEXTURE_CUBE_MAP_POSITIVE_X                          0x8515
    #define GL_TEXTURE_CUBE_MAP_NEGATIVE_X                          0x8516
    #define GL_TEXTURE_CUBE_MAP_POSITIVE_Y                          0x8517
    #define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y                          0x8518
    #define GL_TEXTURE_CUBE_MAP_POSITIVE_Z                          0x8519
    #define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z                          0x851A
    #define GL_PROXY_TEXTURE_CUBE_MAP                               0x851B
    #define GL_MAX_CUBE_MAP_TEXTURE_SIZE                            0x851C
    #define GL_COMBINE                                              0x8570
    #define GL_COMBINE_RGB                                          0x8571
    #define GL_COMBINE_ALPHA                                        0x8572
    #define GL_RGB_SCALE                                            0x8573
    #define GL_ADD_SIGNED                                           0x8574
    #define GL_INTERPOLATE                                          0x8575
    #define GL_CONSTANT                                             0x8576
    #define GL_PRIMARY_COLOR                                        0x8577
    #define GL_PREVIOUS                                             0x8578
    #define GL_SOURCE0_RGB                                          0x8580
    #define GL_SOURCE1_RGB                                          0x8581
    #define GL_SOURCE2_RGB                                          0x8582
    #define GL_SOURCE0_ALPHA                                        0x8588
    #define GL_SOURCE1_ALPHA                                        0x8589
    #define GL_SOURCE2_ALPHA                                        0x858A
    #define GL_SRC0_ALPHA                                           0x8588
    #define GL_SRC0_RGB                                             0x8580
    #define GL_SRC1_ALPHA                                           0x8589
    #define GL_SRC1_RGB                                             0x8581
    #define GL_SRC2_ALPHA                                           0x858A
    #define GL_SRC2_RGB                                             0x8582
    #define GL_OPERAND0_RGB                                         0x8590
    #define GL_OPERAND1_RGB                                         0x8591
    #define GL_OPERAND2_RGB                                         0x8592
    #define GL_OPERAND0_ALPHA                                       0x8598
    #define GL_OPERAND1_ALPHA                                       0x8599
    #define GL_OPERAND2_ALPHA                                       0x859A
    #define GL_TEXTURE_COMPRESSED_IMAGE_SIZE                        0x86A0
    #define GL_TEXTURE_COMPRESSED                                   0x86A1
    #define GL_NUM_COMPRESSED_TEXTURE_FORMATS                       0x86A2
    #define GL_COMPRESSED_TEXTURE_FORMATS                           0x86A3
    #define GL_DOT3_RGB                                             0x86AE
    #define GL_DOT3_RGBA                                            0x86AF
    #define GL_GENERATE_MIPMAP                                      0x8191
    #define GL_GENERATE_MIPMAP_HINT                                 0x8192
    #define GL_DEPTH_COMPONENT16                                    0x81A5
    #define GL_DEPTH_COMPONENT24                                    0x81A6
    #define GL_DEPTH_COMPONENT32                                    0x81A7
    #define GL_MIRRORED_REPEAT                                      0x8370
    #define GL_COLOR_SUM                                            0x8458
    #define GL_CURRENT_SECONDARY_COLOR                              0x8459
    #define GL_SECONDARY_COLOR_ARRAY_SIZE                           0x845A
    #define GL_SECONDARY_COLOR_ARRAY_TYPE                           0x845B
    #define GL_SECONDARY_COLOR_ARRAY_STRIDE                         0x845C
    #define GL_SECONDARY_COLOR_ARRAY_POINTER                        0x845D
    #define GL_SECONDARY_COLOR_ARRAY                                0x845E
    #define GL_TEXTURE_FILTER_CONTROL                               0x8500
    #define GL_TEXTURE_LOD_BIAS                                     0x8501
    #define GL_INCR_WRAP                                            0x8507
    #define GL_DECR_WRAP                                            0x8508
    #define GL_TEXTURE_DEPTH_SIZE                                   0x884A
    #define GL_DEPTH_TEXTURE_MODE                                   0x884B
    #define GL_TEXTURE_COMPARE_MODE                                 0x884C
    #define GL_TEXTURE_COMPARE_FUNC                                 0x884D
    #define GL_COMPARE_R_TO_TEXTURE                                 0x884E
    #define GL_PIXEL_PACK_BUFFER                                    0x88EB
    #define GL_PIXEL_UNPACK_BUFFER                                  0x88EC
    #define GL_PIXEL_PACK_BUFFER_BINDING                            0x88ED
    #define GL_PIXEL_UNPACK_BUFFER_BINDING                          0x88EF
    #define GL_SRGB                                                 0x8C40
    #define GL_SRGB8                                                0x8C41
    #define GL_SRGB_ALPHA                                           0x8C42
    #define GL_SRGB8_ALPHA8                                         0x8C43
    #define GL_SLUMINANCE_ALPHA                                     0x8C44
    #define GL_SLUMINANCE8_ALPHA8                                   0x8C45
    #define GL_SLUMINANCE                                           0x8C46
    #define GL_SLUMINANCE8                                          0x8C47
    #define GL_COMPRESSED_SRGB                                      0x8C48
    #define GL_COMPRESSED_SRGB_ALPHA                                0x8C49
    #define GL_COMPRESSED_SLUMINANCE                                0x8C4A
    #define GL_COMPRESSED_SLUMINANCE_ALPHA                          0x8C4B
    #define GL_CLAMP_VERTEX_COLOR                                   0x891A
    #define GL_CLAMP_FRAGMENT_COLOR                                 0x891B
    #define GL_CLAMP_READ_COLOR                                     0x891C
    #define GL_FIXED_ONLY                                           0x891D
    #define GL_COMPARE_REF_TO_TEXTURE                               0x884E
    #define GL_TEXTURE_RED_TYPE                                     0x8C10
    #define GL_TEXTURE_GREEN_TYPE                                   0x8C11
    #define GL_TEXTURE_BLUE_TYPE                                    0x8C12
    #define GL_TEXTURE_ALPHA_TYPE                                   0x8C13
    #define GL_TEXTURE_LUMINANCE_TYPE                               0x8C14
    #define GL_TEXTURE_INTENSITY_TYPE                               0x8C15
    #define GL_TEXTURE_DEPTH_TYPE                                   0x8C16
    #define GL_TEXTURE_1D_ARRAY                                     0x8C18
    #define GL_PROXY_TEXTURE_1D_ARRAY                               0x8C19
    #define GL_TEXTURE_2D_ARRAY                                     0x8C1A
    #define GL_PROXY_TEXTURE_2D_ARRAY                               0x8C1B
    #define GL_TEXTURE_BINDING_1D_ARRAY                             0x8C1C
    #define GL_TEXTURE_BINDING_2D_ARRAY                             0x8C1D
    #define GL_R11F_G11F_B10F                                       0x8C3A
    #define GL_UNSIGNED_INT_10F_11F_11F_REV                         0x8C3B
    #define GL_RGB9_E5                                              0x8C3D
    #define GL_UNSIGNED_INT_5_9_9_9_REV                             0x8C3E
    #define GL_TEXTURE_SHARED_SIZE                                  0x8C3F
    #define GL_RGBA32F                                              0x8814
    #define GL_RGB32F                                               0x8815
    #define GL_RGBA16F                                              0x881A
    #define GL_RGB16F                                               0x881B
    #define GL_RGBA32UI                                             0x8D70
    #define GL_RGB32UI                                              0x8D71
    #define GL_RGBA16UI                                             0x8D76
    #define GL_RGB16UI                                              0x8D77
    #define GL_RGBA8UI                                              0x8D7C
    #define GL_RGB8UI                                               0x8D7D
    #define GL_RGBA32I                                              0x8D82
    #define GL_RGB32I                                               0x8D83
    #define GL_RGBA16I                                              0x8D88
    #define GL_RGB16I                                               0x8D89
    #define GL_RGBA8I                                               0x8D8E
    #define GL_RGB8I                                                0x8D8F
    #define GL_RED_INTEGER                                          0x8D94
    #define GL_GREEN_INTEGER                                        0x8D95
    #define GL_BLUE_INTEGER                                         0x8D96
    #define GL_ALPHA_INTEGER                                        0x8D97
    #define GL_RGB_INTEGER                                          0x8D98
    #define GL_RGBA_INTEGER                                         0x8D99
    #define GL_BGR_INTEGER                                          0x8D9A
    #define GL_BGRA_INTEGER                                         0x8D9B
    #define GL_SAMPLER_1D_ARRAY                                     0x8DC0
    #define GL_SAMPLER_2D_ARRAY                                     0x8DC1
    #define GL_SAMPLER_1D_ARRAY_SHADOW                              0x8DC3
    #define GL_SAMPLER_2D_ARRAY_SHADOW                              0x8DC4
    #define GL_SAMPLER_CUBE_SHADOW                                  0x8DC5
    #define GL_UNSIGNED_INT_VEC2                                    0x8DC6
    #define GL_UNSIGNED_INT_VEC3                                    0x8DC7
    #define GL_UNSIGNED_INT_VEC4                                    0x8DC8
    #define GL_INT_SAMPLER_1D                                       0x8DC9
    #define GL_INT_SAMPLER_2D                                       0x8DCA
    #define GL_INT_SAMPLER_3D                                       0x8DCB
    #define GL_INT_SAMPLER_CUBE                                     0x8DCC
    #define GL_INT_SAMPLER_1D_ARRAY                                 0x8DCE
    #define GL_INT_SAMPLER_2D_ARRAY                                 0x8DCF
    #define GL_UNSIGNED_INT_SAMPLER_1D                              0x8DD1
    #define GL_UNSIGNED_INT_SAMPLER_2D                              0x8DD2
    #define GL_UNSIGNED_INT_SAMPLER_3D                              0x8DD3
    #define GL_UNSIGNED_INT_SAMPLER_CUBE                            0x8DD4
    #define GL_UNSIGNED_INT_SAMPLER_1D_ARRAY                        0x8DD6
    #define GL_UNSIGNED_INT_SAMPLER_2D_ARRAY                        0x8DD7
    #define GL_TEXTURE_STENCIL_SIZE                                 0x88F1

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL min and max constants                                          //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_MAX_EVAL_ORDER                                       0x0D30
    #define GL_MAX_LIGHTS                                           0x0D31
    #define GL_MAX_CLIP_PLANES                                      0x0D32
    #define GL_MAX_TEXTURE_SIZE                                     0x0D33
    #define GL_MAX_PIXEL_MAP_TABLE                                  0x0D34
    #define GL_MAX_ATTRIB_STACK_DEPTH                               0x0D35
    #define GL_MAX_MODELVIEW_STACK_DEPTH                            0x0D36
    #define GL_MAX_NAME_STACK_DEPTH                                 0x0D37
    #define GL_MAX_PROJECTION_STACK_DEPTH                           0x0D38
    #define GL_MAX_TEXTURE_STACK_DEPTH                              0x0D39
    #define GL_MAX_VIEWPORT_DIMS                                    0x0D3A
    #define GL_MAX_CLIENT_ATTRIB_STACK_DEPTH                        0x0D3B
    #define GL_MAX_ELEMENTS_VERTICES                                0x80E8
    #define GL_MAX_ELEMENTS_INDICES                                 0x80E9
    #define GL_MAX_TEXTURE_UNITS                                    0x84E2
    #define GL_MAX_TEXTURE_LOD_BIAS                                 0x84FD
    #define GL_MAX_DRAW_BUFFERS                                     0x8824
    #define GL_MAX_VERTEX_ATTRIBS                                   0x8869
    #define GL_MAX_TEXTURE_COORDS                                   0x8871
    #define GL_MAX_TEXTURE_IMAGE_UNITS                              0x8872
    #define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS                      0x8B49
    #define GL_MAX_VERTEX_UNIFORM_COMPONENTS                        0x8B4A
    #define GL_MAX_VARYING_FLOATS                                   0x8B4B
    #define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS                       0x8B4C
    #define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS                     0x8B4D
    #define GL_MAX_CLIP_DISTANCES                                   0x0D32
    #define GL_MAX_VARYING_COMPONENTS                               0x8B4B
    #define GL_MAX_ARRAY_TEXTURE_LAYERS                             0x88FF
    #define GL_MIN_PROGRAM_TEXEL_OFFSET                             0x8904
    #define GL_MAX_PROGRAM_TEXEL_OFFSET                             0x8905
    #define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS           0x8C80
    #define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS        0x8C8A
    #define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS              0x8C8B
    #define GL_MAX_RENDERBUFFER_SIZE                                0x84E8
    #define GL_MAX_COLOR_ATTACHMENTS                                0x8CDF
    #define GL_MAX_SAMPLES                                          0x8D57

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL arrays constants                                               //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_VERTEX_ARRAY                                         0x8074
    #define GL_NORMAL_ARRAY                                         0x8075
    #define GL_COLOR_ARRAY                                          0x8076
    #define GL_INDEX_ARRAY                                          0x8077
    #define GL_TEXTURE_COORD_ARRAY                                  0x8078
    #define GL_EDGE_FLAG_ARRAY                                      0x8079
    #define GL_VERTEX_ARRAY_SIZE                                    0x807A
    #define GL_VERTEX_ARRAY_TYPE                                    0x807B
    #define GL_VERTEX_ARRAY_STRIDE                                  0x807C
    #define GL_NORMAL_ARRAY_TYPE                                    0x807E
    #define GL_NORMAL_ARRAY_STRIDE                                  0x807F
    #define GL_COLOR_ARRAY_SIZE                                     0x8081
    #define GL_COLOR_ARRAY_TYPE                                     0x8082
    #define GL_COLOR_ARRAY_STRIDE                                   0x8083
    #define GL_INDEX_ARRAY_TYPE                                     0x8085
    #define GL_INDEX_ARRAY_STRIDE                                   0x8086
    #define GL_TEXTURE_COORD_ARRAY_SIZE                             0x8088
    #define GL_TEXTURE_COORD_ARRAY_TYPE                             0x8089
    #define GL_TEXTURE_COORD_ARRAY_STRIDE                           0x808A
    #define GL_EDGE_FLAG_ARRAY_STRIDE                               0x808C
    #define GL_VERTEX_ARRAY_POINTER                                 0x808E
    #define GL_NORMAL_ARRAY_POINTER                                 0x808F
    #define GL_COLOR_ARRAY_POINTER                                  0x8090
    #define GL_INDEX_ARRAY_POINTER                                  0x8091
    #define GL_TEXTURE_COORD_ARRAY_POINTER                          0x8092
    #define GL_EDGE_FLAG_ARRAY_POINTER                              0x8093
    #define GL_R3_G3_B2                                             0x2A10
    #define GL_V2F                                                  0x2A20
    #define GL_V3F                                                  0x2A21
    #define GL_C4UB_V2F                                             0x2A22
    #define GL_C4UB_V3F                                             0x2A23
    #define GL_C3F_V3F                                              0x2A24
    #define GL_N3F_V3F                                              0x2A25
    #define GL_C4F_N3F_V3F                                          0x2A26
    #define GL_T2F_V3F                                              0x2A27
    #define GL_T4F_V4F                                              0x2A28
    #define GL_T2F_C4UB_V3F                                         0x2A29
    #define GL_T2F_C3F_V3F                                          0x2A2A
    #define GL_T2F_N3F_V3F                                          0x2A2B
    #define GL_T2F_C4F_N3F_V3F                                      0x2A2C
    #define GL_T4F_C4F_N3F_V4F                                      0x2A2D

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL programs constants                                             //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_COMPILE                                              0x1300
    #define GL_COMPILE_AND_EXECUTE                                  0x1301
    #define GL_FRAGMENT_SHADER                                      0x8B30
    #define GL_VERTEX_SHADER                                        0x8B31
    #define GL_SHADER_TYPE                                          0x8B4F
    #define GL_FLOAT_VEC2                                           0x8B50
    #define GL_FLOAT_VEC3                                           0x8B51
    #define GL_FLOAT_VEC4                                           0x8B52
    #define GL_INT_VEC2                                             0x8B53
    #define GL_INT_VEC3                                             0x8B54
    #define GL_INT_VEC4                                             0x8B55
    #define GL_BOOL                                                 0x8B56
    #define GL_BOOL_VEC2                                            0x8B57
    #define GL_BOOL_VEC3                                            0x8B58
    #define GL_BOOL_VEC4                                            0x8B59
    #define GL_FLOAT_MAT2                                           0x8B5A
    #define GL_FLOAT_MAT3                                           0x8B5B
    #define GL_FLOAT_MAT4                                           0x8B5C
    #define GL_SAMPLER_1D                                           0x8B5D
    #define GL_SAMPLER_2D                                           0x8B5E
    #define GL_SAMPLER_3D                                           0x8B5F
    #define GL_SAMPLER_CUBE                                         0x8B60
    #define GL_SAMPLER_1D_SHADOW                                    0x8B61
    #define GL_SAMPLER_2D_SHADOW                                    0x8B62
    #define GL_DELETE_STATUS                                        0x8B80
    #define GL_COMPILE_STATUS                                       0x8B81
    #define GL_LINK_STATUS                                          0x8B82
    #define GL_VALIDATE_STATUS                                      0x8B83
    #define GL_INFO_LOG_LENGTH                                      0x8B84
    #define GL_ATTACHED_SHADERS                                     0x8B85
    #define GL_ACTIVE_UNIFORMS                                      0x8B86
    #define GL_ACTIVE_UNIFORM_MAX_LENGTH                            0x8B87
    #define GL_SHADER_SOURCE_LENGTH                                 0x8B88
    #define GL_ACTIVE_ATTRIBUTES                                    0x8B89
    #define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH                          0x8B8A
    #define GL_FRAGMENT_SHADER_DERIVATIVE_HINT                      0x8B8B
    #define GL_SHADING_LANGUAGE_VERSION                             0x8B8C
    #define GL_CURRENT_PROGRAM                                      0x8B8D

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL framebuffer constants                                          //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_INVALID_FRAMEBUFFER_OPERATION                        0x0506
    #define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING                0x8210
    #define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE                0x8211
    #define GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE                      0x8212
    #define GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE                    0x8213
    #define GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE                     0x8214
    #define GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE                    0x8215
    #define GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE                    0x8216
    #define GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE                  0x8217
    #define GL_FRAMEBUFFER_DEFAULT                                  0x8218
    #define GL_FRAMEBUFFER_UNDEFINED                                0x8219
    #define GL_DEPTH_STENCIL_ATTACHMENT                             0x821A
    #define GL_DRAW_FRAMEBUFFER_BINDING                             0x8CA6
    #define GL_FRAMEBUFFER_BINDING                                  0x8CA6
    #define GL_RENDERBUFFER_BINDING                                 0x8CA7
    #define GL_READ_FRAMEBUFFER                                     0x8CA8
    #define GL_DRAW_FRAMEBUFFER                                     0x8CA9
    #define GL_READ_FRAMEBUFFER_BINDING                             0x8CAA
    #define GL_RENDERBUFFER_SAMPLES                                 0x8CAB
    #define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE                   0x8CD0
    #define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME                   0x8CD1
    #define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL                 0x8CD2
    #define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE         0x8CD3
    #define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER                 0x8CD4
    #define GL_FRAMEBUFFER_COMPLETE                                 0x8CD5
    #define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT                    0x8CD6
    #define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT            0x8CD7
    #define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER                   0x8CDB
    #define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER                   0x8CDC
    #define GL_FRAMEBUFFER_UNSUPPORTED                              0x8CDD
    #define GL_COLOR_ATTACHMENT0                                    0x8CE0
    #define GL_COLOR_ATTACHMENT1                                    0x8CE1
    #define GL_COLOR_ATTACHMENT2                                    0x8CE2
    #define GL_COLOR_ATTACHMENT3                                    0x8CE3
    #define GL_COLOR_ATTACHMENT4                                    0x8CE4
    #define GL_COLOR_ATTACHMENT5                                    0x8CE5
    #define GL_COLOR_ATTACHMENT6                                    0x8CE6
    #define GL_COLOR_ATTACHMENT7                                    0x8CE7
    #define GL_COLOR_ATTACHMENT8                                    0x8CE8
    #define GL_COLOR_ATTACHMENT9                                    0x8CE9
    #define GL_COLOR_ATTACHMENT10                                   0x8CEA
    #define GL_COLOR_ATTACHMENT11                                   0x8CEB
    #define GL_COLOR_ATTACHMENT12                                   0x8CEC
    #define GL_COLOR_ATTACHMENT13                                   0x8CED
    #define GL_COLOR_ATTACHMENT14                                   0x8CEE
    #define GL_COLOR_ATTACHMENT15                                   0x8CEF
    #define GL_DEPTH_ATTACHMENT                                     0x8D00
    #define GL_STENCIL_ATTACHMENT                                   0x8D20
    #define GL_FRAMEBUFFER                                          0x8D40
    #define GL_RENDERBUFFER                                         0x8D41
    #define GL_RENDERBUFFER_WIDTH                                   0x8D42
    #define GL_RENDERBUFFER_HEIGHT                                  0x8D43
    #define GL_RENDERBUFFER_INTERNAL_FORMAT                         0x8D44
    #define GL_RENDERBUFFER_RED_SIZE                                0x8D50
    #define GL_RENDERBUFFER_GREEN_SIZE                              0x8D51
    #define GL_RENDERBUFFER_BLUE_SIZE                               0x8D52
    #define GL_RENDERBUFFER_ALPHA_SIZE                              0x8D53
    #define GL_RENDERBUFFER_DEPTH_SIZE                              0x8D54
    #define GL_RENDERBUFFER_STENCIL_SIZE                            0x8D55
    #define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE                   0x8D56

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL map buffer constants                                           //
    ////////////////////////////////////////////////////////////////////////////
    #define GL_MAP_READ_BIT                                         0x0001
    #define GL_MAP_WRITE_BIT                                        0x0002
    #define GL_MAP_INVALIDATE_RANGE_BIT                             0x0004
    #define GL_MAP_INVALIDATE_BUFFER_BIT                            0x0008
    #define GL_MAP_FLUSH_EXPLICIT_BIT                               0x0010
    #define GL_MAP_UNSYNCHRONIZED_BIT                               0x0020


    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL rendering functions                                            //
    ////////////////////////////////////////////////////////////////////////////
    VOSGLApi VOSGLEntry void glClear(GLbitfield mask);
    VOSGLApi VOSGLEntry void glClearAccum(
        GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha
    );
    VOSGLApi VOSGLEntry void glClearColor(
        GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha
    );
    VOSGLApi VOSGLEntry void glClearDepth(GLclampd depth);
    VOSGLApi VOSGLEntry void glClearIndex(GLfloat c);
    VOSGLApi VOSGLEntry void glClearStencil(GLint s);
    VOSGLApi VOSGLEntry GLint glRenderMode(GLenum mode);
    VOSGLApi VOSGLEntry void glBegin(GLenum mode);
    VOSGLApi VOSGLEntry void glEnd();
    VOSGLApi VOSGLEntry void glEnable(GLenum cap);
    VOSGLApi VOSGLEntry void glDisable(GLenum cap);
    VOSGLApi VOSGLEntry void glEnableClientState(GLenum array);
    VOSGLApi VOSGLEntry void glDisableClientState(GLenum array);
    VOSGLApi VOSGLEntry void glFinish();
    VOSGLApi VOSGLEntry void glFlush();
    VOSGLApi VOSGLEntry void glPassThrough(GLfloat token);
    VOSGLApi VOSGLEntry void glPushAttrib(GLbitfield mask);
    VOSGLApi VOSGLEntry void glPopAttrib();
    VOSGLApi VOSGLEntry void glPushClientAttrib(GLbitfield mask);
    VOSGLApi VOSGLEntry void glPopClientAttrib();
    VOSGLApi VOSGLEntry void glInitNames();
    VOSGLApi VOSGLEntry void glPushName(GLuint name);
    VOSGLApi VOSGLEntry void glPopName();
    VOSGLApi VOSGLEntry void glPointSize(GLfloat size);
    VOSGLApi VOSGLEntry void glLineWidth(GLfloat width);
    VOSGLApi VOSGLEntry void glLineStipple(GLint factor, GLushort pattern);
    VOSGLApi VOSGLEntry void glLoadName(GLuint name);
    VOSGLApi VOSGLEntry void glLogicOp(GLenum opcode);
    VOSGLApi VOSGLEntry void glHint(GLenum target, GLenum mode);
    VOSGLApi VOSGLEntry GLboolean glIsEnabled(GLenum cap);
    VOSGLApi VOSGLEntry void glAccum(GLenum op, GLfloat value);
    VOSGLApi VOSGLEntry GLenum glGetError();
    VOSGLApi VOSGLEntry void glGetPointerv(GLenum pname, void** params);
    VOSGLApi VOSGLEntry void glGetBooleanv(GLenum pname, GLboolean* params);
    VOSGLApi VOSGLEntry void glGetDoublev(GLenum pname, GLdouble* params);
    VOSGLApi VOSGLEntry void glGetFloatv(GLenum pname, GLfloat* params);
    VOSGLApi VOSGLEntry void glGetIntegerv(GLenum pname, GLint* params);
    VOSGLApi VOSGLEntry void glGetClipPlane(GLenum plane, GLdouble* equation);
    VOSGLApi VOSGLEntry const GLubyte* glGetString(GLenum name);

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL lists functions                                                //
    ////////////////////////////////////////////////////////////////////////////
    VOSGLApi VOSGLEntry GLuint glGenLists(GLsizei range);
    VOSGLApi VOSGLEntry void glListBase(GLuint base);
    VOSGLApi VOSGLEntry void glNewList(GLuint list, GLenum mode);
    VOSGLApi VOSGLEntry void glDeleteLists(GLuint list, GLsizei range);
    VOSGLApi VOSGLEntry void glCallList(GLuint list);
    VOSGLApi VOSGLEntry void glCallLists(
        GLsizei n, GLenum type, const void* lists
    );
    VOSGLApi VOSGLEntry void glEndList();
    VOSGLApi VOSGLEntry GLboolean glIsList(GLuint list);

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL blending and depths functions                                  //
    ////////////////////////////////////////////////////////////////////////////
    VOSGLApi VOSGLEntry void glAlphaFunc(GLenum func, GLclampf ref);
    VOSGLApi VOSGLEntry void glBlendFunc(GLenum sfactor, GLenum dfactor);
    VOSGLApi VOSGLEntry void glDepthFunc(GLenum func);
    VOSGLApi VOSGLEntry void glDepthMask(GLboolean flag);
    VOSGLApi VOSGLEntry void glDepthRange(GLclampd zNear, GLclampd zFar);

    typedef void (*PFNGLBLENDCOLORPROC)(
        GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha
    );
    VOSGLEntry PFNGLBLENDCOLORPROC glBlendColor;
    typedef void (*PFNGLBLENDEQUATIONPROC)(GLenum mode);
    VOSGLEntry PFNGLBLENDEQUATIONPROC glBlendEquation;
    typedef void (*PFNGLBLENDFUNCSEPARATEPROC)(
        GLenum sfactorRGB, GLenum dfactorRGB,
        GLenum sfactorAlpha, GLenum dfactorAlpha
    );
    VOSGLEntry PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate;

    typedef void (*PFNGLBLENDEQUATIONSEPARATEPROC)(
        GLenum modeRGB, GLenum modeAlpha
    );
    VOSGLEntry PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate;

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL matrices functions                                             //
    ////////////////////////////////////////////////////////////////////////////
    VOSGLApi VOSGLEntry void glMatrixMode(GLenum mode);
    VOSGLApi VOSGLEntry void glLoadIdentity();
    VOSGLApi VOSGLEntry void glLoadMatrixd(const GLdouble* m);
    VOSGLApi VOSGLEntry void glLoadMatrixf(const GLfloat* m);
    VOSGLApi VOSGLEntry void glMultMatrixd(const GLdouble* m);
    VOSGLApi VOSGLEntry void glMultMatrixf(const GLfloat* m);
    VOSGLApi VOSGLEntry void glTranslated(GLdouble x, GLdouble y, GLdouble z);
    VOSGLApi VOSGLEntry void glTranslatef(GLfloat x, GLfloat y, GLfloat z);
    VOSGLApi VOSGLEntry void glRotated(
        GLdouble angle, GLdouble x, GLdouble y, GLdouble z
    );
    VOSGLApi VOSGLEntry void glRotatef(
        GLfloat angle, GLfloat x, GLfloat y, GLfloat z
    );
    VOSGLApi VOSGLEntry void glScaled(GLdouble x, GLdouble y, GLdouble z);
    VOSGLApi VOSGLEntry void glScalef(GLfloat x, GLfloat y, GLfloat z);
    VOSGLApi VOSGLEntry void glPushMatrix();
    VOSGLApi VOSGLEntry void glPopMatrix();
        VOSGLApi VOSGLEntry void glViewport(
        GLint x, GLint y, GLsizei width, GLsizei height
    );
    VOSGLApi VOSGLEntry void glOrtho(
        GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
        GLdouble zNear, GLdouble zFar
    );
    VOSGLApi VOSGLEntry void glFrustum(
        GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
        GLdouble zNear, GLdouble zFar
    );

    typedef void (*PFNGLLOADTRANSPOSEMATRIXDPROC)(const GLdouble m[16]);
    VOSGLEntry PFNGLLOADTRANSPOSEMATRIXDPROC glLoadTransposeMatrixd;
    typedef void (*PFNGLLOADTRANSPOSEMATRIXFPROC)(const GLfloat m[16]);
    VOSGLEntry PFNGLLOADTRANSPOSEMATRIXFPROC glLoadTransposeMatrixf;
    typedef void (*PFNGLMULTTRANSPOSEMATRIXDPROC)(const GLdouble m[16]);
    VOSGLEntry PFNGLMULTTRANSPOSEMATRIXDPROC glMultTransposeMatrixd;
    typedef void (*PFNGLMULTTRANSPOSEMATRIXFPROC)(const GLfloat m[16]);
    VOSGLEntry PFNGLMULTTRANSPOSEMATRIXFPROC glMultTransposeMatrixf;

    typedef void (*PFNGLUNIFORMMATRIX2X3FVPROC)(
        GLint location, GLsizei count, GLboolean transpose, const GLfloat* value
    );
    VOSGLEntry PFNGLUNIFORMMATRIX2X3FVPROC glUniformMatrix2x3fv;
    typedef void (*PFNGLUNIFORMMATRIX2X4FVPROC)(
        GLint location, GLsizei count, GLboolean transpose, const GLfloat* value
    );
    VOSGLEntry PFNGLUNIFORMMATRIX2X4FVPROC glUniformMatrix2x4fv;
    typedef void (*PFNGLUNIFORMMATRIX3X2FVPROC)(
        GLint location, GLsizei count, GLboolean transpose, const GLfloat* value
    );
    VOSGLEntry PFNGLUNIFORMMATRIX3X2FVPROC glUniformMatrix3x2fv;
    typedef void (*PFNGLUNIFORMMATRIX3X4FVPROC)(
        GLint location, GLsizei count, GLboolean transpose, const GLfloat* value
    );
    VOSGLEntry PFNGLUNIFORMMATRIX3X4FVPROC glUniformMatrix3x4fv;
    typedef void (*PFNGLUNIFORMMATRIX4X2FVPROC)(
        GLint location, GLsizei count, GLboolean transpose, const GLfloat* value
    );
    VOSGLEntry PFNGLUNIFORMMATRIX4X2FVPROC glUniformMatrix4x2fv;
    typedef void (*PFNGLUNIFORMMATRIX4X3FVPROC)(
        GLint location, GLsizei count, GLboolean transpose, const GLfloat* value
    );
    VOSGLEntry PFNGLUNIFORMMATRIX4X3FVPROC glUniformMatrix4x3fv;

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL rasterizer functions                                           //
    ////////////////////////////////////////////////////////////////////////////
    VOSGLApi VOSGLEntry void glRasterPos2d(GLdouble x, GLdouble y);
    VOSGLApi VOSGLEntry void glRasterPos2dv(const GLdouble* v);
    VOSGLApi VOSGLEntry void glRasterPos2f(GLfloat x, GLfloat y);
    VOSGLApi VOSGLEntry void glRasterPos2fv(const GLfloat* v);
    VOSGLApi VOSGLEntry void glRasterPos2i(GLint x, GLint y);
    VOSGLApi VOSGLEntry void glRasterPos2iv(const GLint* v);
    VOSGLApi VOSGLEntry void glRasterPos2s(GLshort x, GLshort y);
    VOSGLApi VOSGLEntry void glRasterPos2sv(const GLshort* v);
    VOSGLApi VOSGLEntry void glRasterPos3d(GLdouble x, GLdouble y, GLdouble z);
    VOSGLApi VOSGLEntry void glRasterPos3dv(const GLdouble* v);
    VOSGLApi VOSGLEntry void glRasterPos3f(GLfloat x, GLfloat y, GLfloat z);
    VOSGLApi VOSGLEntry void glRasterPos3fv(const GLfloat* v);
    VOSGLApi VOSGLEntry void glRasterPos3i(GLint x, GLint y, GLint z);
    VOSGLApi VOSGLEntry void glRasterPos3iv(const GLint* v);
    VOSGLApi VOSGLEntry void glRasterPos3s(GLshort x, GLshort y, GLshort z);
    VOSGLApi VOSGLEntry void glRasterPos3sv(const GLshort* v);
    VOSGLApi VOSGLEntry void glRasterPos4d(
        GLdouble x, GLdouble y, GLdouble z, GLdouble w
    );
    VOSGLApi VOSGLEntry void glRasterPos4dv(const GLdouble* v);
    VOSGLApi VOSGLEntry void glRasterPos4f(
        GLfloat x, GLfloat y, GLfloat z, GLfloat w
    );
    VOSGLApi VOSGLEntry void glRasterPos4fv(const GLfloat* v);
    VOSGLApi VOSGLEntry void glRasterPos4i(GLint x, GLint y, GLint z, GLint w);
    VOSGLApi VOSGLEntry void glRasterPos4iv(const GLint* v);
    VOSGLApi VOSGLEntry void glRasterPos4s(
        GLshort x, GLshort y, GLshort z, GLshort w
    );
    VOSGLApi VOSGLEntry void glRasterPos4sv(const GLshort* v);

    typedef void (*PFNGLWINDOWPOS2DPROC)(GLdouble x, GLdouble y);
    VOSGLEntry PFNGLWINDOWPOS2DPROC glWindowPos2d;
    typedef void (*PFNGLWINDOWPOS2DVPROC)(const GLdouble* p);
    VOSGLEntry PFNGLWINDOWPOS2DVPROC glWindowPos2dv;
    typedef void (*PFNGLWINDOWPOS2FPROC)(GLfloat x, GLfloat y);
    VOSGLEntry PFNGLWINDOWPOS2FPROC glWindowPos2f;
    typedef void (*PFNGLWINDOWPOS2FVPROC)(const GLfloat* p);
    VOSGLEntry PFNGLWINDOWPOS2FVPROC glWindowPos2fv;
    typedef void (*PFNGLWINDOWPOS2IPROC)(GLint x, GLint y);
    VOSGLEntry PFNGLWINDOWPOS2IPROC glWindowPos2i;
    typedef void (*PFNGLWINDOWPOS2IVPROC)(const GLint* p);
    VOSGLEntry PFNGLWINDOWPOS2IVPROC glWindowPos2iv;
    typedef void (*PFNGLWINDOWPOS2SPROC)(GLshort x, GLshort y);
    VOSGLEntry PFNGLWINDOWPOS2SPROC glWindowPos2s;
    typedef void (*PFNGLWINDOWPOS2SVPROC)(const GLshort* p);
    VOSGLEntry PFNGLWINDOWPOS2SVPROC glWindowPos2sv;
    typedef void (*PFNGLWINDOWPOS3DPROC)(GLdouble x, GLdouble y, GLdouble z);
    VOSGLEntry PFNGLWINDOWPOS3DPROC glWindowPos3d;
    typedef void (*PFNGLWINDOWPOS3DVPROC)(const GLdouble* p);
    VOSGLEntry PFNGLWINDOWPOS3DVPROC glWindowPos3dv;
    typedef void (*PFNGLWINDOWPOS3FPROC)(GLfloat x, GLfloat y, GLfloat z);
    VOSGLEntry PFNGLWINDOWPOS3FPROC glWindowPos3f;
    typedef void (*PFNGLWINDOWPOS3FVPROC)(const GLfloat* p);
    VOSGLEntry PFNGLWINDOWPOS3FVPROC glWindowPos3fv;
    typedef void (*PFNGLWINDOWPOS3IPROC)(GLint x, GLint y, GLint z);
    VOSGLEntry PFNGLWINDOWPOS3IPROC glWindowPos3i;
    typedef void (*PFNGLWINDOWPOS3IVPROC)(const GLint* p);
    VOSGLEntry PFNGLWINDOWPOS3IVPROC glWindowPos3iv;
    typedef void (*PFNGLWINDOWPOS3SPROC) (GLshort x, GLshort y, GLshort z);
    VOSGLEntry PFNGLWINDOWPOS3SPROC glWindowPos3s;
    typedef void (*PFNGLWINDOWPOS3SVPROC)(const GLshort* p);
    VOSGLEntry PFNGLWINDOWPOS3SVPROC glWindowPos3sv;

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL eval functions                                                 //
    ////////////////////////////////////////////////////////////////////////////
    VOSGLApi VOSGLEntry void glEvalCoord1d(GLdouble u);
    VOSGLApi VOSGLEntry void glEvalCoord1dv(const GLdouble* u);
    VOSGLApi VOSGLEntry void glEvalCoord1f(GLfloat u);
    VOSGLApi VOSGLEntry void glEvalCoord1fv(const GLfloat* u);
    VOSGLApi VOSGLEntry void glEvalCoord2d(GLdouble u, GLdouble v);
    VOSGLApi VOSGLEntry void glEvalCoord2dv(const GLdouble* u);
    VOSGLApi VOSGLEntry void glEvalCoord2f(GLfloat u, GLfloat v);
    VOSGLApi VOSGLEntry void glEvalCoord2fv(const GLfloat* u);
    VOSGLApi VOSGLEntry void glEvalMesh1(GLenum mode, GLint i1, GLint i2);
    VOSGLApi VOSGLEntry void glEvalMesh2(
        GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2
    );
    VOSGLApi VOSGLEntry void glEvalPoint1(GLint i);
    VOSGLApi VOSGLEntry void glEvalPoint2(GLint i, GLint j);

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL points and lines functions                                     //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (*PFNGLPOINTPARAMETERFPROC)(GLenum pname, GLfloat param);
    VOSGLEntry PFNGLPOINTPARAMETERFPROC glPointParameterf;
    typedef void (*PFNGLPOINTPARAMETERFVPROC)(
        GLenum pname, const GLfloat* params
    );
    VOSGLEntry PFNGLPOINTPARAMETERFVPROC glPointParameterfv;
    typedef void (*PFNGLPOINTPARAMETERIPROC)(GLenum pname, GLint param);
    VOSGLEntry PFNGLPOINTPARAMETERIPROC glPointParameteri;
    typedef void (*PFNGLPOINTPARAMETERIVPROC)(
        GLenum pname, const GLint* params
    );
    VOSGLEntry PFNGLPOINTPARAMETERIVPROC glPointParameteriv;

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL indices functions                                              //
    ////////////////////////////////////////////////////////////////////////////
    VOSGLApi VOSGLEntry void glIndexMask(GLuint mask);
    VOSGLApi VOSGLEntry void glIndexPointer(
        GLenum type, GLsizei stride, const void* pointer
    );
    VOSGLApi VOSGLEntry void glIndexd(GLdouble c);
    VOSGLApi VOSGLEntry void glIndexdv(const GLdouble* c);
    VOSGLApi VOSGLEntry void glIndexf(GLfloat c);
    VOSGLApi VOSGLEntry void glIndexfv(const GLfloat* c);
    VOSGLApi VOSGLEntry void glIndexi(GLint c);
    VOSGLApi VOSGLEntry void glIndexiv(const GLint* c);
    VOSGLApi VOSGLEntry void glIndexs(GLshort c);
    VOSGLApi VOSGLEntry void glIndexsv(const GLshort* c);
    VOSGLApi VOSGLEntry void glIndexub(GLubyte c);
    VOSGLApi VOSGLEntry void glIndexubv(const GLubyte* c);

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL vertices functions                                             //
    ////////////////////////////////////////////////////////////////////////////
    VOSGLApi VOSGLEntry void glVertex2d(GLdouble x, GLdouble y);
    VOSGLApi VOSGLEntry void glVertex2dv(const GLdouble* v);
    VOSGLApi VOSGLEntry void glVertex2f(GLfloat x, GLfloat y);
    VOSGLApi VOSGLEntry void glVertex2fv(const GLfloat* v);
    VOSGLApi VOSGLEntry void glVertex2i(GLint x, GLint y);
    VOSGLApi VOSGLEntry void glVertex2iv(const GLint* v);
    VOSGLApi VOSGLEntry void glVertex2s(GLshort x, GLshort y);
    VOSGLApi VOSGLEntry void glVertex2sv(const GLshort* v);
    VOSGLApi VOSGLEntry void glVertex3d(GLdouble x, GLdouble y, GLdouble z);
    VOSGLApi VOSGLEntry void glVertex3dv(const GLdouble* v);
    VOSGLApi VOSGLEntry void glVertex3f(GLfloat x, GLfloat y, GLfloat z);
    VOSGLApi VOSGLEntry void glVertex3fv(const GLfloat* v);
    VOSGLApi VOSGLEntry void glVertex3i(GLint x, GLint y, GLint z);
    VOSGLApi VOSGLEntry void glVertex3iv(const GLint* v);
    VOSGLApi VOSGLEntry void glVertex3s(GLshort x, GLshort y, GLshort z);
    VOSGLApi VOSGLEntry void glVertex3sv(const GLshort* v);
    VOSGLApi VOSGLEntry void glVertex4d(
        GLdouble x, GLdouble y, GLdouble z, GLdouble w
    );
    VOSGLApi VOSGLEntry void glVertex4dv(const GLdouble* v);
    VOSGLApi VOSGLEntry void glVertex4f(
        GLfloat x, GLfloat y, GLfloat z, GLfloat w
    );
    VOSGLApi VOSGLEntry void glVertex4fv(const GLfloat* v);
    VOSGLApi VOSGLEntry void glVertex4i(
        GLint x, GLint y, GLint z, GLint w
    );
    VOSGLApi VOSGLEntry void glVertex4iv(const GLint* v);
    VOSGLApi VOSGLEntry void glVertex4s(
        GLshort x, GLshort y, GLshort z, GLshort w
    );
    VOSGLApi VOSGLEntry void glVertex4sv(const GLshort* v);
    VOSGLApi VOSGLEntry void glVertexPointer(
        GLint size, GLenum type, GLsizei stride, const void* pointer
    );

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL colors functions                                               //
    ////////////////////////////////////////////////////////////////////////////
    VOSGLApi VOSGLEntry void glColor3b(GLbyte red, GLbyte green, GLbyte blue);
    VOSGLApi VOSGLEntry void glColor3bv(const GLbyte* v);
    VOSGLApi VOSGLEntry void glColor3d(
        GLdouble red, GLdouble green, GLdouble blue
    );
    VOSGLApi VOSGLEntry void glColor3dv(const GLdouble* v);
    VOSGLApi VOSGLEntry void glColor3f(
        GLfloat red, GLfloat green, GLfloat blue
    );
    VOSGLApi VOSGLEntry void glColor3fv(const GLfloat* v);
    VOSGLApi VOSGLEntry void glColor3i(GLint red, GLint green, GLint blue);
    VOSGLApi VOSGLEntry void glColor3iv(const GLint* v);
    VOSGLApi VOSGLEntry void glColor3s(
        GLshort red, GLshort green, GLshort blue
    );
    VOSGLApi VOSGLEntry void glColor3sv(const GLshort* v);
    VOSGLApi VOSGLEntry void glColor3ub(
        GLubyte red, GLubyte green, GLubyte blue
    );
    VOSGLApi VOSGLEntry void glColor3ubv(const GLubyte* v);
    VOSGLApi VOSGLEntry void glColor3ui(
        GLuint red, GLuint green, GLuint blue
    );
    VOSGLApi VOSGLEntry void glColor3uiv(const GLuint* v);
    VOSGLApi VOSGLEntry void glColor3us(
        GLushort red, GLushort green, GLushort blue
    );
    VOSGLApi VOSGLEntry void glColor3usv(const GLushort* v);
    VOSGLApi VOSGLEntry void glColor4b(
        GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha
    );
    VOSGLApi VOSGLEntry void glColor4bv(const GLbyte* v);
    VOSGLApi VOSGLEntry void glColor4d(
        GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha
    );
    VOSGLApi VOSGLEntry void glColor4dv(const GLdouble* v);
    VOSGLApi VOSGLEntry void glColor4f(
        GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha
    );
    VOSGLApi VOSGLEntry void glColor4fv(const GLfloat* v);
    VOSGLApi VOSGLEntry void glColor4i(
        GLint red, GLint green, GLint blue, GLint alpha
    );
    VOSGLApi VOSGLEntry void glColor4iv(const GLint* v);
    VOSGLApi VOSGLEntry void glColor4s(
        GLshort red, GLshort green, GLshort blue, GLshort alpha
    );
    VOSGLApi VOSGLEntry void glColor4sv(const GLshort* v);
    VOSGLApi VOSGLEntry void glColor4ub(
        GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha
    );
    VOSGLApi VOSGLEntry void glColor4ubv(const GLubyte* v);
    VOSGLApi VOSGLEntry void glColor4ui(
        GLuint red, GLuint green, GLuint blue, GLuint alpha
    );
    VOSGLApi VOSGLEntry void glColor4uiv(const GLuint* v);
    VOSGLApi VOSGLEntry void glColor4us(
        GLushort red, GLushort green, GLushort blue, GLushort alpha
    );
    VOSGLApi VOSGLEntry void glColor4usv(const GLushort* v);
    VOSGLApi VOSGLEntry void glColorMask(
        GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha
    );
    VOSGLApi VOSGLEntry void glColorMaterial(GLenum face, GLenum mode);
    VOSGLApi VOSGLEntry void glColorPointer(
        GLint size, GLenum type, GLsizei stride, const void* pointer
    );

    typedef void (*PFNGLSECONDARYCOLOR3BPROC)(
        GLbyte red, GLbyte green, GLbyte blue
    );
    VOSGLEntry PFNGLSECONDARYCOLOR3BPROC glSecondaryColor3b;
    typedef void (*PFNGLSECONDARYCOLOR3BVPROC)(const GLbyte* v);
    VOSGLEntry PFNGLSECONDARYCOLOR3BVPROC glSecondaryColor3bv;
    typedef void (*PFNGLSECONDARYCOLOR3DPROC)(
        GLdouble red, GLdouble green, GLdouble blue
    );
    VOSGLEntry PFNGLSECONDARYCOLOR3DPROC glSecondaryColor3d;
    typedef void (*PFNGLSECONDARYCOLOR3DVPROC)(const GLdouble* v);
    VOSGLEntry PFNGLSECONDARYCOLOR3DVPROC glSecondaryColor3dv;
    typedef void (*PFNGLSECONDARYCOLOR3FPROC)(
        GLfloat red, GLfloat green, GLfloat blue
    );
    VOSGLEntry PFNGLSECONDARYCOLOR3FPROC glSecondaryColor3f;
    typedef void (*PFNGLSECONDARYCOLOR3FVPROC)(const GLfloat* v);
    VOSGLEntry PFNGLSECONDARYCOLOR3FVPROC glSecondaryColor3fv;
    typedef void (*PFNGLSECONDARYCOLOR3IPROC)(
        GLint red, GLint green, GLint blue
    );
    VOSGLEntry PFNGLSECONDARYCOLOR3IPROC glSecondaryColor3i;
    typedef void (*PFNGLSECONDARYCOLOR3IVPROC)(const GLint* v);
    VOSGLEntry PFNGLSECONDARYCOLOR3IVPROC glSecondaryColor3iv;
    typedef void (*PFNGLSECONDARYCOLOR3SPROC)(
        GLshort red, GLshort green, GLshort blue
    );
    VOSGLEntry PFNGLSECONDARYCOLOR3SPROC glSecondaryColor3s;
    typedef void (*PFNGLSECONDARYCOLOR3SVPROC)(const GLshort* v);
    VOSGLEntry PFNGLSECONDARYCOLOR3SVPROC glSecondaryColor3sv;
    typedef void (*PFNGLSECONDARYCOLOR3UBPROC)(
        GLubyte red, GLubyte green, GLubyte blue
    );
    VOSGLEntry PFNGLSECONDARYCOLOR3UBPROC glSecondaryColor3ub;
    typedef void (*PFNGLSECONDARYCOLOR3UBVPROC)(const GLubyte* v);
    VOSGLEntry PFNGLSECONDARYCOLOR3UBVPROC glSecondaryColor3ubv;
    typedef void (*PFNGLSECONDARYCOLOR3UIPROC)(
        GLuint red, GLuint green, GLuint blue
    );
    VOSGLEntry PFNGLSECONDARYCOLOR3UIPROC glSecondaryColor3ui;
    typedef void (*PFNGLSECONDARYCOLOR3UIVPROC)(const GLuint* v);
    VOSGLEntry PFNGLSECONDARYCOLOR3UIVPROC glSecondaryColor3uiv;
    typedef void (*PFNGLSECONDARYCOLOR3USPROC)(
        GLushort red, GLushort green, GLushort blue
    );
    VOSGLEntry PFNGLSECONDARYCOLOR3USPROC glSecondaryColor3us;
    typedef void (*PFNGLSECONDARYCOLOR3USVPROC)(const GLushort* v);
    VOSGLEntry PFNGLSECONDARYCOLOR3USVPROC glSecondaryColor3usv;
    typedef void (*PFNGLSECONDARYCOLORPOINTERPROC)(
        GLint size, GLenum type, GLsizei stride, const void* pointer
    );
    VOSGLEntry PFNGLSECONDARYCOLORPOINTERPROC glSecondaryColorPointer;

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL normals functions                                              //
    ////////////////////////////////////////////////////////////////////////////
    VOSGLApi VOSGLEntry void glNormal3b(GLbyte nx, GLbyte ny, GLbyte nz);
    VOSGLApi VOSGLEntry void glNormal3bv(const GLbyte* v);
    VOSGLApi VOSGLEntry void glNormal3d(GLdouble nx, GLdouble ny, GLdouble nz);
    VOSGLApi VOSGLEntry void glNormal3dv(const GLdouble* v);
    VOSGLApi VOSGLEntry void glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz);
    VOSGLApi VOSGLEntry void glNormal3fv(const GLfloat* v);
    VOSGLApi VOSGLEntry void glNormal3i(GLint nx, GLint ny, GLint nz);
    VOSGLApi VOSGLEntry void glNormal3iv(const GLint* v);
    VOSGLApi VOSGLEntry void glNormal3s(GLshort nx, GLshort ny, GLshort nz);
    VOSGLApi VOSGLEntry void glNormal3sv(const GLshort* v);
    VOSGLApi VOSGLEntry void glNormalPointer(
        GLenum type, GLsizei stride, const void* pointer
    );

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL edges functions                                                //
    ////////////////////////////////////////////////////////////////////////////
    VOSGLApi VOSGLEntry void glEdgeFlag(GLboolean flag);
    VOSGLApi VOSGLEntry void glEdgeFlagPointer(
        GLsizei stride, const void* pointer
    );
    VOSGLApi VOSGLEntry void glEdgeFlagv(const GLboolean* flag);

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL rects functions                                                //
    ////////////////////////////////////////////////////////////////////////////
    VOSGLApi VOSGLEntry void glRectd(
        GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2
    );
    VOSGLApi VOSGLEntry void glRectdv(const GLdouble* v1, const GLdouble* v2);
    VOSGLApi VOSGLEntry void glRectf(
        GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2
    );
    VOSGLApi VOSGLEntry void glRectfv(const GLfloat* v1, const GLfloat* v2);
    VOSGLApi VOSGLEntry void glRecti(GLint x1, GLint y1, GLint x2, GLint y2);
    VOSGLApi VOSGLEntry void glRectiv(const GLint* v1, const GLint* v2);
    VOSGLApi VOSGLEntry void glRects(
        GLshort x1, GLshort y1, GLshort x2, GLshort y2
    );
    VOSGLApi VOSGLEntry void glRectsv(const GLshort* v1, const GLshort* v2);

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL faces functions                                                //
    ////////////////////////////////////////////////////////////////////////////
    VOSGLApi VOSGLEntry void glFrontFace(GLenum mode);
    VOSGLApi VOSGLEntry void glCullFace(GLenum mode);
    VOSGLApi VOSGLEntry void glClipPlane(
        GLenum plane, const GLdouble* equation
    );
    VOSGLApi VOSGLEntry void glScissor(
        GLint x, GLint y, GLsizei width, GLsizei height
    );

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL polygons functions                                             //
    ////////////////////////////////////////////////////////////////////////////
    VOSGLApi VOSGLEntry void glPolygonMode(GLenum face, GLenum mode);
    VOSGLApi VOSGLEntry void glPolygonOffset(GLfloat factor, GLfloat units);
    VOSGLApi VOSGLEntry void glPolygonStipple(const GLubyte* mask);
    VOSGLApi VOSGLEntry void glGetPolygonStipple(GLubyte* mask);

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL textures functions                                             //
    ////////////////////////////////////////////////////////////////////////////
    VOSGLApi VOSGLEntry void glGenTextures(GLsizei n, GLuint* textures);
    VOSGLApi VOSGLEntry void glDeleteTextures(
        GLsizei n, const GLuint* textures
    );
    VOSGLApi VOSGLEntry void glBindTexture(GLenum target, GLuint texture);
    VOSGLApi VOSGLEntry void glBitmap(
        GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig,
        GLfloat xmove, GLfloat ymove, const GLubyte* bitmap
    );
    VOSGLApi VOSGLEntry GLboolean glAreTexturesResident(
        GLsizei n, const GLuint* textures, GLboolean* residences
    );
    VOSGLApi VOSGLEntry void glGetTexEnvfv(
        GLenum target, GLenum pname, GLfloat* params
    );
    VOSGLApi VOSGLEntry void glGetTexEnviv(
        GLenum target, GLenum pname, GLint* params
    );
    VOSGLApi VOSGLEntry void glGetTexGendv(
        GLenum coord, GLenum pname, GLdouble* params
    );
    VOSGLApi VOSGLEntry void glGetTexGenfv(
        GLenum coord, GLenum pname, GLfloat* params
    );
    VOSGLApi VOSGLEntry void glGetTexGeniv(
        GLenum coord, GLenum pname, GLint* params
    );
    VOSGLApi VOSGLEntry void glGetTexImage(
        GLenum target, GLint level, GLenum format, GLenum type, void* pixels
    );
    VOSGLApi VOSGLEntry void glGetTexLevelParameterfv(
        GLenum target, GLint level, GLenum pname, GLfloat* params
    );
    VOSGLApi VOSGLEntry void glGetTexLevelParameteriv(
        GLenum target, GLint level, GLenum pname, GLint* params
    );
    VOSGLApi VOSGLEntry void glGetTexParameterfv(
        GLenum target, GLenum pname, GLfloat* params
    );
    VOSGLApi VOSGLEntry void glGetTexParameteriv(
        GLenum target, GLenum pname, GLint* params
    );
    VOSGLApi VOSGLEntry void glTexCoord1d(GLdouble s);
    VOSGLApi VOSGLEntry void glTexCoord1dv(const GLdouble* v);
    VOSGLApi VOSGLEntry void glTexCoord1f(GLfloat s);
    VOSGLApi VOSGLEntry void glTexCoord1fv(const GLfloat* v);
    VOSGLApi VOSGLEntry void glTexCoord1i(GLint s);
    VOSGLApi VOSGLEntry void glTexCoord1iv(const GLint* v);
    VOSGLApi VOSGLEntry void glTexCoord1s(GLshort s);
    VOSGLApi VOSGLEntry void glTexCoord1sv(const GLshort* v);
    VOSGLApi VOSGLEntry void glTexCoord2d(GLdouble s, GLdouble t);
    VOSGLApi VOSGLEntry void glTexCoord2dv(const GLdouble* v);
    VOSGLApi VOSGLEntry void glTexCoord2f(GLfloat s, GLfloat t);
    VOSGLApi VOSGLEntry void glTexCoord2fv(const GLfloat* v);
    VOSGLApi VOSGLEntry void glTexCoord2i(GLint s, GLint t);
    VOSGLApi VOSGLEntry void glTexCoord2iv(const GLint* v);
    VOSGLApi VOSGLEntry void glTexCoord2s(GLshort s, GLshort t);
    VOSGLApi VOSGLEntry void glTexCoord2sv(const GLshort* v);
    VOSGLApi VOSGLEntry void glTexCoord3d(GLdouble s, GLdouble t, GLdouble r);
    VOSGLApi VOSGLEntry void glTexCoord3dv(const GLdouble* v);
    VOSGLApi VOSGLEntry void glTexCoord3f(GLfloat s, GLfloat t, GLfloat r);
    VOSGLApi VOSGLEntry void glTexCoord3fv(const GLfloat* v);
    VOSGLApi VOSGLEntry void glTexCoord3i(GLint s, GLint t, GLint r);
    VOSGLApi VOSGLEntry void glTexCoord3iv(const GLint* v);
    VOSGLApi VOSGLEntry void glTexCoord3s(GLshort s, GLshort t, GLshort r);
    VOSGLApi VOSGLEntry void glTexCoord3sv(const GLshort* v);
    VOSGLApi VOSGLEntry void glTexCoord4d(
        GLdouble s, GLdouble t, GLdouble r, GLdouble q
    );
    VOSGLApi VOSGLEntry void glTexCoord4dv(const GLdouble* v);
    VOSGLApi VOSGLEntry void glTexCoord4f(
        GLfloat s, GLfloat t, GLfloat r, GLfloat q
    );
    VOSGLApi VOSGLEntry void glTexCoord4fv(const GLfloat* v);
    VOSGLApi VOSGLEntry void glTexCoord4i(GLint s, GLint t, GLint r, GLint q);
    VOSGLApi VOSGLEntry void glTexCoord4iv(const GLint* v);
    VOSGLApi VOSGLEntry void glTexCoord4s(
        GLshort s, GLshort t, GLshort r, GLshort q
    );
    VOSGLApi VOSGLEntry void glTexCoord4sv(const GLshort* v);
    VOSGLApi VOSGLEntry void glTexCoordPointer(
        GLint size, GLenum type, GLsizei stride, const void* pointer
    );
    VOSGLApi VOSGLEntry void glTexEnvf(
        GLenum target, GLenum pname, GLfloat param
    );
    VOSGLApi VOSGLEntry void glTexEnvfv(
        GLenum target, GLenum pname, const GLfloat* params
    );
    VOSGLApi VOSGLEntry void glTexEnvi(
        GLenum target, GLenum pname, GLint param
    );
    VOSGLApi VOSGLEntry void glTexEnviv(
        GLenum target, GLenum pname, const GLint* params
    );
    VOSGLApi VOSGLEntry void glTexGend(
        GLenum coord, GLenum pname, GLdouble param
    );
    VOSGLApi VOSGLEntry void glTexGendv(
        GLenum coord, GLenum pname, const GLdouble* params
    );
    VOSGLApi VOSGLEntry void glTexGenf(
        GLenum coord, GLenum pname, GLfloat param
    );
    VOSGLApi VOSGLEntry void glTexGenfv(
        GLenum coord, GLenum pname, const GLfloat* params
    );
    VOSGLApi VOSGLEntry void glTexGeni(
        GLenum coord, GLenum pname, GLint param
    );
    VOSGLApi VOSGLEntry void glTexGeniv(
        GLenum coord, GLenum pname, const GLint* params
    );
    VOSGLApi VOSGLEntry void glTexImage1D(
        GLenum target, GLint level, GLint internalformat, GLsizei width,
        GLint border, GLenum format, GLenum type, const void* pixels
    );
    VOSGLApi VOSGLEntry void glTexImage2D(
        GLenum target, GLint level, GLint internalformat,
        GLsizei width, GLsizei height, GLint border,
        GLenum format, GLenum type, const void* pixels
    );
    VOSGLApi VOSGLEntry void glTexParameterf(
        GLenum target, GLenum pname, GLfloat param
    );
    VOSGLApi VOSGLEntry void glTexParameterfv(
        GLenum target, GLenum pname, const GLfloat* params
    );
    VOSGLApi VOSGLEntry void glTexParameteri(
        GLenum target, GLenum pname, GLint param
    );
    VOSGLApi VOSGLEntry void glTexParameteriv(
        GLenum target, GLenum pname, const GLint* params
    );
    VOSGLApi VOSGLEntry void glTexSubImage1D(
        GLenum target, GLint level, GLint xoffset, GLsizei width,
        GLenum format, GLenum type, const void* pixels
    );
    VOSGLApi VOSGLEntry void glTexSubImage2D(
        GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width,
        GLsizei height, GLenum format, GLenum type, const void* pixels
    );
    VOSGLApi VOSGLEntry void glPrioritizeTextures(
        GLsizei n, const GLuint* textures, const GLclampf* priorities
    );
    VOSGLApi VOSGLEntry void glPixelMapfv(
        GLenum map, GLsizei mapsize, const GLfloat* values
    );
    VOSGLApi VOSGLEntry void glPixelMapuiv(
        GLenum map, GLsizei mapsize, const GLuint* values
    );
    VOSGLApi VOSGLEntry void glPixelMapusv(
        GLenum map, GLsizei mapsize, const GLushort* values
    );
    VOSGLApi VOSGLEntry void glPixelStoref(GLenum pname, GLfloat param);
    VOSGLApi VOSGLEntry void glPixelStorei(GLenum pname, GLint param);
    VOSGLApi VOSGLEntry void glPixelTransferf(GLenum pname, GLfloat param);
    VOSGLApi VOSGLEntry void glPixelTransferi(GLenum pname, GLint param);
    VOSGLApi VOSGLEntry void glPixelZoom(GLfloat xfactor, GLfloat yfactor);
    VOSGLApi VOSGLEntry void glGetPixelMapfv(GLenum map, GLfloat* values);
    VOSGLApi VOSGLEntry void glGetPixelMapuiv(GLenum map, GLuint* values);
    VOSGLApi VOSGLEntry void glGetPixelMapusv(GLenum map, GLushort* values);
    VOSGLApi VOSGLEntry void glGetMapdv(
        GLenum target, GLenum query, GLdouble* v
    );
    VOSGLApi VOSGLEntry void glGetMapfv(
        GLenum target, GLenum query, GLfloat* v
    );
    VOSGLApi VOSGLEntry void glGetMapiv(GLenum target, GLenum query, GLint* v);
    VOSGLApi VOSGLEntry void glMap1d(
        GLenum target, GLdouble u1, GLdouble u2,
        GLint stride, GLint order, const GLdouble* points
    );
    VOSGLApi VOSGLEntry void glMap1f(
        GLenum target, GLfloat u1, GLfloat u2,
        GLint stride, GLint order, const GLfloat* points
    );
    VOSGLApi VOSGLEntry void glMap2d(
        GLenum target, GLdouble u1, GLdouble u2,
        GLint ustride, GLint uorder, GLdouble v1, GLdouble v2,
        GLint vstride, GLint vorder, const GLdouble* points
    );
    VOSGLApi VOSGLEntry void glMap2f(
        GLenum target, GLfloat u1, GLfloat u2,
        GLint ustride, GLint uorder, GLfloat v1, GLfloat v2,
        GLint vstride, GLint vorder, const GLfloat* points
    );
    VOSGLApi VOSGLEntry void glMapGrid1d(GLint un, GLdouble u1, GLdouble u2);
    VOSGLApi VOSGLEntry void glMapGrid1f(GLint un, GLfloat u1, GLfloat u2);
    VOSGLApi VOSGLEntry void glMapGrid2d(
        GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2
    );
    VOSGLApi VOSGLEntry void glMapGrid2f(
        GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2
    );
    VOSGLApi VOSGLEntry GLboolean glIsTexture(GLuint texture);

    typedef void (*PFNGLCOPYTEXSUBIMAGE3DPROC)(
        GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset,
        GLint x, GLint y, GLsizei width, GLsizei height
    );
    VOSGLEntry PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D;
    typedef void (*PFNGLTEXIMAGE3DPROC)(
        GLenum target, GLint level, GLint internalFormat,
        GLsizei width, GLsizei height, GLsizei depth, GLint border,
        GLenum format, GLenum type, const void* pixels
    );
    VOSGLEntry PFNGLTEXIMAGE3DPROC glTexImage3D;
    typedef void (*PFNGLTEXSUBIMAGE3DPROC)(
        GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset,
        GLsizei width, GLsizei height, GLsizei depth,
        GLenum format, GLenum type, const void* pixels
    );
    VOSGLEntry PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D;

    typedef void (*PFNGLACTIVETEXTUREPROC)(GLenum texture);
    VOSGLEntry PFNGLACTIVETEXTUREPROC glActiveTexture;
    typedef void (*PFNGLCLIENTACTIVETEXTUREPROC)(GLenum texture);
    VOSGLEntry PFNGLCLIENTACTIVETEXTUREPROC glClientActiveTexture;
    typedef void (*PFNGLCOMPRESSEDTEXIMAGE1DPROC)(
        GLenum target, GLint level, GLenum internalformat, GLsizei width,
        GLint border, GLsizei imageSize, const void* data
    );
    VOSGLEntry PFNGLCOMPRESSEDTEXIMAGE1DPROC glCompressedTexImage1D;
    typedef void (*PFNGLCOMPRESSEDTEXIMAGE2DPROC)(
        GLenum target, GLint level, GLenum internalformat, GLsizei width,
        GLsizei height, GLint border, GLsizei imageSize, const void* data
    );
    VOSGLEntry PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D;
    typedef void (*PFNGLCOMPRESSEDTEXIMAGE3DPROC)(
        GLenum target, GLint level, GLenum internalformat, GLsizei width,
        GLsizei height, GLsizei depth, GLint border,
        GLsizei imageSize, const void* data
    );
    VOSGLEntry PFNGLCOMPRESSEDTEXIMAGE3DPROC glCompressedTexImage3D;
    typedef void (*PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)(
        GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format,
        GLsizei imageSize, const void *data
    );
    VOSGLEntry PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glCompressedTexSubImage1D;
    typedef void (*PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)(
        GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width,
        GLsizei height, GLenum format, GLsizei imageSize, const void* data
    );
    VOSGLEntry PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D;
    typedef void (*PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)(
        GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset,
        GLsizei width, GLsizei height, GLsizei depth, GLenum format,
        GLsizei imageSize, const void* data
    );
    VOSGLEntry PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3D;
    typedef void (*PFNGLGETCOMPRESSEDTEXIMAGEPROC)(
        GLenum target, GLint lod, void* img
    );
    VOSGLEntry PFNGLGETCOMPRESSEDTEXIMAGEPROC glGetCompressedTexImage;
    typedef void (*PFNGLMULTITEXCOORD1DPROC)(GLenum target, GLdouble s);
    VOSGLEntry PFNGLMULTITEXCOORD1DPROC glMultiTexCoord1d;
    typedef void (*PFNGLMULTITEXCOORD1DVPROC)(GLenum target, const GLdouble* v);
    VOSGLEntry PFNGLMULTITEXCOORD1DVPROC glMultiTexCoord1dv;
    typedef void (*PFNGLMULTITEXCOORD1FPROC)(GLenum target, GLfloat s);
    VOSGLEntry PFNGLMULTITEXCOORD1FPROC glMultiTexCoord1f;
    typedef void (*PFNGLMULTITEXCOORD1FVPROC)(GLenum target, const GLfloat* v);
    VOSGLEntry PFNGLMULTITEXCOORD1FVPROC glMultiTexCoord1fv;
    typedef void (*PFNGLMULTITEXCOORD1IPROC)(GLenum target, GLint s);
    VOSGLEntry PFNGLMULTITEXCOORD1IPROC glMultiTexCoord1i;
    typedef void (*PFNGLMULTITEXCOORD1IVPROC)(GLenum target, const GLint* v);
    VOSGLEntry PFNGLMULTITEXCOORD1IVPROC glMultiTexCoord1iv;
    typedef void (*PFNGLMULTITEXCOORD1SPROC)(GLenum target, GLshort s);
    VOSGLEntry PFNGLMULTITEXCOORD1SPROC glMultiTexCoord1s;
    typedef void (*PFNGLMULTITEXCOORD1SVPROC)(GLenum target, const GLshort* v);
    VOSGLEntry PFNGLMULTITEXCOORD1SVPROC glMultiTexCoord1sv;
    typedef void (*PFNGLMULTITEXCOORD2DPROC)(
        GLenum target, GLdouble s, GLdouble t
    );
    VOSGLEntry PFNGLMULTITEXCOORD2DPROC glMultiTexCoord2d;
    typedef void (*PFNGLMULTITEXCOORD2DVPROC)(GLenum target, const GLdouble* v);
    VOSGLEntry PFNGLMULTITEXCOORD2DVPROC glMultiTexCoord2dv;
    typedef void (*PFNGLMULTITEXCOORD2FPROC)(
        GLenum target, GLfloat s, GLfloat t
    );
    VOSGLEntry PFNGLMULTITEXCOORD2FPROC glMultiTexCoord2f;
    typedef void (*PFNGLMULTITEXCOORD2FVPROC)(GLenum target, const GLfloat* v);
    VOSGLEntry PFNGLMULTITEXCOORD2FVPROC glMultiTexCoord2fv;
    typedef void (*PFNGLMULTITEXCOORD2IPROC)(GLenum target, GLint s, GLint t);
    VOSGLEntry PFNGLMULTITEXCOORD2IPROC glMultiTexCoord2i;
    typedef void (*PFNGLMULTITEXCOORD2IVPROC)(GLenum target, const GLint* v);
    VOSGLEntry PFNGLMULTITEXCOORD2IVPROC glMultiTexCoord2iv;
    typedef void (*PFNGLMULTITEXCOORD2SPROC)(
        GLenum target, GLshort s, GLshort t
    );
    VOSGLEntry PFNGLMULTITEXCOORD2SPROC glMultiTexCoord2s;
    typedef void (*PFNGLMULTITEXCOORD2SVPROC)(GLenum target, const GLshort* v);
    VOSGLEntry PFNGLMULTITEXCOORD2SVPROC glMultiTexCoord2sv;
    typedef void (*PFNGLMULTITEXCOORD3DPROC)(
        GLenum target, GLdouble s, GLdouble t, GLdouble r
    );
    VOSGLEntry PFNGLMULTITEXCOORD3DPROC glMultiTexCoord3d;
    typedef void (*PFNGLMULTITEXCOORD3DVPROC)(GLenum target, const GLdouble* v);
    VOSGLEntry PFNGLMULTITEXCOORD3DVPROC glMultiTexCoord3dv;
    typedef void (*PFNGLMULTITEXCOORD3FPROC)(
        GLenum target, GLfloat s, GLfloat t, GLfloat r
    );
    VOSGLEntry PFNGLMULTITEXCOORD3FPROC glMultiTexCoord3f;
    typedef void (*PFNGLMULTITEXCOORD3FVPROC)(GLenum target, const GLfloat* v);
    VOSGLEntry PFNGLMULTITEXCOORD3FVPROC glMultiTexCoord3fv;
    typedef void (*PFNGLMULTITEXCOORD3IPROC)(
        GLenum target, GLint s, GLint t, GLint r
    );
    VOSGLEntry PFNGLMULTITEXCOORD3IPROC glMultiTexCoord3i;
    typedef void (*PFNGLMULTITEXCOORD3IVPROC)(GLenum target, const GLint* v);
    VOSGLEntry PFNGLMULTITEXCOORD3IVPROC glMultiTexCoord3iv;
    typedef void (*PFNGLMULTITEXCOORD3SPROC)(
        GLenum target, GLshort s, GLshort t, GLshort r
    );
    VOSGLEntry PFNGLMULTITEXCOORD3SPROC glMultiTexCoord3s;
    typedef void (*PFNGLMULTITEXCOORD3SVPROC)(GLenum target, const GLshort* v);
    VOSGLEntry PFNGLMULTITEXCOORD3SVPROC glMultiTexCoord3sv;
    typedef void (*PFNGLMULTITEXCOORD4DPROC)(
        GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q
    );
    VOSGLEntry PFNGLMULTITEXCOORD4DPROC glMultiTexCoord4d;
    typedef void (*PFNGLMULTITEXCOORD4DVPROC)(GLenum target, const GLdouble* v);
    VOSGLEntry PFNGLMULTITEXCOORD4DVPROC glMultiTexCoord4dv;
    typedef void (*PFNGLMULTITEXCOORD4FPROC)(
        GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q
    );
    VOSGLEntry PFNGLMULTITEXCOORD4FPROC glMultiTexCoord4f;
    typedef void (*PFNGLMULTITEXCOORD4FVPROC)(GLenum target, const GLfloat* v);
    VOSGLEntry PFNGLMULTITEXCOORD4FVPROC glMultiTexCoord4fv;
    typedef void (*PFNGLMULTITEXCOORD4IPROC)(
        GLenum target, GLint s, GLint t, GLint r, GLint q
    );
    VOSGLEntry PFNGLMULTITEXCOORD4IPROC glMultiTexCoord4i;
    typedef void (*PFNGLMULTITEXCOORD4IVPROC)(GLenum target, const GLint* v);
    VOSGLEntry PFNGLMULTITEXCOORD4IVPROC glMultiTexCoord4iv;
    typedef void (*PFNGLMULTITEXCOORD4SPROC)(
        GLenum target, GLshort s, GLshort t, GLshort r, GLshort q
    );
    VOSGLEntry PFNGLMULTITEXCOORD4SPROC glMultiTexCoord4s;
    typedef void (*PFNGLMULTITEXCOORD4SVPROC)(GLenum target, const GLshort* v);
    VOSGLEntry PFNGLMULTITEXCOORD4SVPROC glMultiTexCoord4sv;
    typedef void (*PFNGLSAMPLECOVERAGEPROC)(GLclampf value, GLboolean invert);
    VOSGLEntry PFNGLSAMPLECOVERAGEPROC glSampleCoverage;

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL materials functions                                            //
    ////////////////////////////////////////////////////////////////////////////
    VOSGLApi VOSGLEntry void glGetMaterialfv(
        GLenum face, GLenum pname, GLfloat* params
    );
    VOSGLApi VOSGLEntry void glGetMaterialiv(
        GLenum face, GLenum pname, GLint* params
    );
    VOSGLApi VOSGLEntry void glMaterialf(
        GLenum face, GLenum pname, GLfloat param
    );
    VOSGLApi VOSGLEntry void glMaterialfv(
        GLenum face, GLenum pname, const GLfloat* params
    );
    VOSGLApi VOSGLEntry void glMateriali(
        GLenum face, GLenum pname, GLint param
    );
    VOSGLApi VOSGLEntry void glMaterialiv(
        GLenum face, GLenum pname, const GLint* params
    );

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL arrays functions                                               //
    ////////////////////////////////////////////////////////////////////////////
    VOSGLApi VOSGLEntry void glDrawArrays(
        GLenum mode, GLint first, GLsizei count
    );
    VOSGLApi VOSGLEntry void glDrawBuffer(GLenum mode);
    VOSGLApi VOSGLEntry void glDrawElements(
        GLenum mode, GLsizei count, GLenum type, const void* indices
    );
    VOSGLApi VOSGLEntry void glDrawPixels(
        GLsizei width, GLsizei height,
        GLenum format, GLenum type, const void* pixels
    );
    VOSGLApi VOSGLEntry void glArrayElement(GLint i);
    VOSGLApi VOSGLEntry void glInterleavedArrays(
        GLenum format, GLsizei stride, const void* pointer
    );

    typedef void (*PFNGLDRAWRANGEELEMENTSPROC)(
        GLenum mode, GLuint start, GLuint end, GLsizei count,
        GLenum type, const void* indices
    );
    VOSGLEntry PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements;

    typedef void (*PFNGLMULTIDRAWARRAYSPROC)(
        GLenum mode, const GLint* first,
        const GLsizei* count, GLsizei drawcount
    );
    VOSGLEntry PFNGLMULTIDRAWARRAYSPROC glMultiDrawArrays;
    typedef void (*PFNGLMULTIDRAWELEMENTSPROC)(
        GLenum mode, const GLsizei* count, GLenum type,
        const void* const* indices, GLsizei drawcount
    );
    VOSGLEntry PFNGLMULTIDRAWELEMENTSPROC glMultiDrawElements;

    typedef void (*PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
    VOSGLEntry PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
    typedef void (*PFNGLDISABLEVERTEXATTRIBARRAYPROC)(GLuint index);
    VOSGLEntry PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
    typedef void (*PFNGLDRAWBUFFERSPROC)(GLsizei n, const GLenum* bufs);
    VOSGLEntry PFNGLDRAWBUFFERSPROC glDrawBuffers;
    typedef void (*PFNGLVERTEXATTRIB1DPROC)(GLuint index, GLdouble x);
    VOSGLEntry PFNGLVERTEXATTRIB1DPROC glVertexAttrib1d;
    typedef void (*PFNGLVERTEXATTRIB1DVPROC)(GLuint index, const GLdouble* v);
    VOSGLEntry PFNGLVERTEXATTRIB1DVPROC glVertexAttrib1dv;
    typedef void (*PFNGLVERTEXATTRIB1FPROC)(GLuint index, GLfloat x);
    VOSGLEntry PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f;
    typedef void (*PFNGLVERTEXATTRIB1FVPROC)(GLuint index, const GLfloat* v);
    VOSGLEntry PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv;
    typedef void (*PFNGLVERTEXATTRIB1SPROC)(GLuint index, GLshort x);
    VOSGLEntry PFNGLVERTEXATTRIB1SPROC glVertexAttrib1s;
    typedef void (*PFNGLVERTEXATTRIB1SVPROC)(GLuint index, const GLshort* v);
    VOSGLEntry PFNGLVERTEXATTRIB1SVPROC glVertexAttrib1sv;
    typedef void (*PFNGLVERTEXATTRIB2DPROC)(
        GLuint index, GLdouble x, GLdouble y
    );
    VOSGLEntry PFNGLVERTEXATTRIB2DPROC glVertexAttrib2d;
    typedef void (*PFNGLVERTEXATTRIB2DVPROC)(GLuint index, const GLdouble* v);
    VOSGLEntry PFNGLVERTEXATTRIB2DVPROC glVertexAttrib2dv;
    typedef void (*PFNGLVERTEXATTRIB2FPROC)(GLuint index, GLfloat x, GLfloat y);
    VOSGLEntry PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f;
    typedef void (*PFNGLVERTEXATTRIB2FVPROC)(GLuint index, const GLfloat* v);
    VOSGLEntry PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv;
    typedef void (*PFNGLVERTEXATTRIB2SPROC)(GLuint index, GLshort x, GLshort y);
    VOSGLEntry PFNGLVERTEXATTRIB2SPROC glVertexAttrib2s;
    typedef void (*PFNGLVERTEXATTRIB2SVPROC)(GLuint index, const GLshort* v);
    VOSGLEntry PFNGLVERTEXATTRIB2SVPROC glVertexAttrib2sv;
    typedef void (*PFNGLVERTEXATTRIB3DPROC)(
        GLuint index, GLdouble x, GLdouble y, GLdouble z
    );
    VOSGLEntry PFNGLVERTEXATTRIB3DPROC glVertexAttrib3d;
    typedef void (*PFNGLVERTEXATTRIB3DVPROC)(GLuint index, const GLdouble* v);
    VOSGLEntry PFNGLVERTEXATTRIB3DVPROC glVertexAttrib3dv;
    typedef void (*PFNGLVERTEXATTRIB3FPROC)(
        GLuint index, GLfloat x, GLfloat y, GLfloat z
    );
    VOSGLEntry PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f;
    typedef void (*PFNGLVERTEXATTRIB3FVPROC)(GLuint index, const GLfloat* v);
    VOSGLEntry PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv;
    typedef void (*PFNGLVERTEXATTRIB3SPROC)(
        GLuint index, GLshort x, GLshort y, GLshort z
    );
    VOSGLEntry PFNGLVERTEXATTRIB3SPROC glVertexAttrib3s;
    typedef void (*PFNGLVERTEXATTRIB3SVPROC)(GLuint index, const GLshort* v);
    VOSGLEntry PFNGLVERTEXATTRIB3SVPROC glVertexAttrib3sv;
    typedef void (*PFNGLVERTEXATTRIB4NBVPROC)(GLuint index, const GLbyte* v);
    VOSGLEntry PFNGLVERTEXATTRIB4NBVPROC glVertexAttrib4Nbv;
    typedef void (*PFNGLVERTEXATTRIB4NIVPROC)(GLuint index, const GLint* v);
    VOSGLEntry PFNGLVERTEXATTRIB4NIVPROC glVertexAttrib4Niv;
    typedef void (*PFNGLVERTEXATTRIB4NSVPROC)(GLuint index, const GLshort* v);
    VOSGLEntry PFNGLVERTEXATTRIB4NSVPROC glVertexAttrib4Nsv;
    typedef void (*PFNGLVERTEXATTRIB4NUBPROC)(
        GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w
    );
    VOSGLEntry PFNGLVERTEXATTRIB4NUBPROC glVertexAttrib4Nub;
    typedef void (*PFNGLVERTEXATTRIB4NUBVPROC)(GLuint index, const GLubyte* v);
    VOSGLEntry PFNGLVERTEXATTRIB4NUBVPROC glVertexAttrib4Nubv;
    typedef void (*PFNGLVERTEXATTRIB4NUIVPROC)(GLuint index, const GLuint* v);
    VOSGLEntry PFNGLVERTEXATTRIB4NUIVPROC glVertexAttrib4Nuiv;
    typedef void (*PFNGLVERTEXATTRIB4NUSVPROC)(GLuint index, const GLushort* v);
    VOSGLEntry PFNGLVERTEXATTRIB4NUSVPROC glVertexAttrib4Nusv;
    typedef void (*PFNGLVERTEXATTRIB4BVPROC)(GLuint index, const GLbyte* v);
    VOSGLEntry PFNGLVERTEXATTRIB4BVPROC glVertexAttrib4bv;
    typedef void (*PFNGLVERTEXATTRIB4DPROC)(
        GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w
    );
    VOSGLEntry PFNGLVERTEXATTRIB4DPROC glVertexAttrib4d;
    typedef void (*PFNGLVERTEXATTRIB4DVPROC)(GLuint index, const GLdouble* v);
    VOSGLEntry PFNGLVERTEXATTRIB4DVPROC glVertexAttrib4dv;
    typedef void (*PFNGLVERTEXATTRIB4FPROC)(
        GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w
    );
    VOSGLEntry PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f;
    typedef void (*PFNGLVERTEXATTRIB4FVPROC)(GLuint index, const GLfloat* v);
    VOSGLEntry PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv;
    typedef void (*PFNGLVERTEXATTRIB4IVPROC)(GLuint index, const GLint* v);
    VOSGLEntry PFNGLVERTEXATTRIB4IVPROC glVertexAttrib4iv;
    typedef void (*PFNGLVERTEXATTRIB4SPROC)(
        GLuint index, GLshort x, GLshort y, GLshort z, GLshort w
    );
    VOSGLEntry PFNGLVERTEXATTRIB4SPROC glVertexAttrib4s;
    typedef void (*PFNGLVERTEXATTRIB4SVPROC)(GLuint index, const GLshort* v);
    VOSGLEntry PFNGLVERTEXATTRIB4SVPROC glVertexAttrib4sv;
    typedef void (*PFNGLVERTEXATTRIB4UBVPROC)(GLuint index, const GLubyte* v);
    VOSGLEntry PFNGLVERTEXATTRIB4UBVPROC glVertexAttrib4ubv;
    typedef void (*PFNGLVERTEXATTRIB4UIVPROC)(GLuint index, const GLuint* v);
    VOSGLEntry PFNGLVERTEXATTRIB4UIVPROC glVertexAttrib4uiv;
    typedef void (*PFNGLVERTEXATTRIB4USVPROC)(GLuint index, const GLushort* v);
    VOSGLEntry PFNGLVERTEXATTRIB4USVPROC glVertexAttrib4usv;
    typedef void (*PFNGLVERTEXATTRIBPOINTERPROC)(
        GLuint index, GLint size, GLenum type, GLboolean normalized,
        GLsizei stride, const void* pointer
    );
    VOSGLEntry PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
    typedef void (*PFNGLGETVERTEXATTRIBPOINTERVPROC)(
        GLuint index, GLenum pname, void** pointer
    );
    VOSGLEntry PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv;
    typedef void (*PFNGLGETVERTEXATTRIBDVPROC)(
        GLuint index, GLenum pname, GLdouble* params
    );
    VOSGLEntry PFNGLGETVERTEXATTRIBDVPROC glGetVertexAttribdv;
    typedef void (*PFNGLGETVERTEXATTRIBFVPROC)(
        GLuint index, GLenum pname, GLfloat* params
    );
    VOSGLEntry PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfv;
    typedef void (*PFNGLGETVERTEXATTRIBIVPROC)(
        GLuint index, GLenum pname, GLint* params
    );
    VOSGLEntry PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv;

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL buffers functions                                              //
    ////////////////////////////////////////////////////////////////////////////
    VOSGLApi VOSGLEntry void glSelectBuffer(GLsizei size, GLuint* buffer);
    VOSGLApi VOSGLEntry void glReadBuffer(GLenum mode);
    VOSGLApi VOSGLEntry void glFeedbackBuffer(
        GLsizei size, GLenum type, GLfloat* buffer
    );
    VOSGLApi VOSGLEntry void glReadPixels(
        GLint x, GLint y, GLsizei width, GLsizei height,
        GLenum format, GLenum type, void* pixels
    );
    VOSGLApi VOSGLEntry void glStencilFunc(GLenum func, GLint ref, GLuint mask);
    VOSGLApi VOSGLEntry void glStencilMask(GLuint mask);
    VOSGLApi VOSGLEntry void glStencilOp(
        GLenum fail, GLenum zfail, GLenum zpass
    );

    typedef void (*PFNGLBEGINQUERYPROC)(GLenum target, GLuint id);
    VOSGLEntry PFNGLBEGINQUERYPROC glBeginQuery;
    typedef void (*PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
    VOSGLEntry PFNGLBINDBUFFERPROC glBindBuffer;
    typedef void (*PFNGLBUFFERDATAPROC)(
        GLenum target, GLsizeiptr size, const void* data, GLenum usage
    );
    VOSGLEntry PFNGLBUFFERDATAPROC glBufferData;
    typedef void (*PFNGLBUFFERSUBDATAPROC)(
        GLenum target, GLintptr offset, GLsizeiptr size, const void* data
    );
    VOSGLEntry PFNGLBUFFERSUBDATAPROC glBufferSubData;
    typedef void (*PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint* buffers);
    VOSGLEntry PFNGLDELETEBUFFERSPROC glDeleteBuffers;
    typedef void (*PFNGLDELETEQUERIESPROC)(GLsizei n, const GLuint* ids);
    VOSGLEntry PFNGLDELETEQUERIESPROC glDeleteQueries;
    typedef void (*PFNGLENDQUERYPROC)(GLenum target);
    VOSGLEntry PFNGLENDQUERYPROC glEndQuery;
    typedef void (*PFNGLGENBUFFERSPROC)(GLsizei n, GLuint* buffers);
    VOSGLEntry PFNGLGENBUFFERSPROC glGenBuffers;
    typedef void (*PFNGLGENQUERIESPROC)(GLsizei n, GLuint* ids);
    VOSGLEntry PFNGLGENQUERIESPROC glGenQueries;
    typedef void (*PFNGLGETBUFFERPARAMETERIVPROC)(
        GLenum target, GLenum pname, GLint* params
    );
    VOSGLEntry PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv;
    typedef void (*PFNGLGETBUFFERPOINTERVPROC)(
        GLenum target, GLenum pname, void** params
    );
    VOSGLEntry PFNGLGETBUFFERPOINTERVPROC glGetBufferPointerv;
    typedef void (*PFNGLGETBUFFERSUBDATAPROC)(
        GLenum target, GLintptr offset, GLsizeiptr size, void* data
    );
    VOSGLEntry PFNGLGETBUFFERSUBDATAPROC glGetBufferSubData;
    typedef void (*PFNGLGETQUERYOBJECTIVPROC)(
        GLuint id, GLenum pname, GLint* params
    );
    VOSGLEntry PFNGLGETQUERYOBJECTIVPROC glGetQueryObjectiv;
    typedef void (*PFNGLGETQUERYOBJECTUIVPROC)(
        GLuint id, GLenum pname, GLuint* params
    );
    VOSGLEntry PFNGLGETQUERYOBJECTUIVPROC glGetQueryObjectuiv;
    typedef void (*PFNGLGETQUERYIVPROC)(
        GLenum target, GLenum pname, GLint* params
    );
    VOSGLEntry PFNGLGETQUERYIVPROC glGetQueryiv;
    typedef GLboolean (*PFNGLISBUFFERPROC)(GLuint buffer);
    VOSGLEntry PFNGLISBUFFERPROC glIsBuffer;
    typedef GLboolean (*PFNGLISQUERYPROC)(GLuint id);
    VOSGLEntry PFNGLISQUERYPROC glIsQuery;
    typedef void* (*PFNGLMAPBUFFERPROC)(GLenum target, GLenum access);
    VOSGLEntry PFNGLMAPBUFFERPROC glMapBuffer;
    typedef GLboolean (*PFNGLUNMAPBUFFERPROC)(GLenum target);
    VOSGLEntry PFNGLUNMAPBUFFERPROC glUnmapBuffer;

    typedef void (*PFNGLSTENCILFUNCSEPARATEPROC)(
        GLenum frontfunc, GLenum backfunc, GLint ref, GLuint mask
    );
    VOSGLEntry PFNGLSTENCILFUNCSEPARATEPROC glStencilFuncSeparate;
    typedef void (*PFNGLSTENCILMASKSEPARATEPROC)(GLenum face, GLuint mask);
    VOSGLEntry PFNGLSTENCILMASKSEPARATEPROC glStencilMaskSeparate;
    typedef void (*PFNGLSTENCILOPSEPARATEPROC)(
        GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass
    );
    VOSGLEntry PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate;

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL copy functions                                                 //
    ////////////////////////////////////////////////////////////////////////////
    VOSGLApi VOSGLEntry void glCopyPixels(
        GLint x, GLint y, GLsizei width, GLsizei height, GLenum type
    );
    VOSGLApi VOSGLEntry void glCopyTexImage1D(
        GLenum target, GLint level, GLenum internalFormat,
        GLint x, GLint y, GLsizei width, GLint border
    );
    VOSGLApi VOSGLEntry void glCopyTexImage2D(
        GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y,
        GLsizei width, GLsizei height, GLint border
    );
    VOSGLApi VOSGLEntry void glCopyTexSubImage1D(
        GLenum target, GLint level, GLint xoffset,
        GLint x, GLint y, GLsizei width
    );
    VOSGLApi VOSGLEntry void glCopyTexSubImage2D(
        GLenum target, GLint level, GLint xoffset, GLint yoffset,
        GLint x, GLint y, GLsizei width, GLsizei height
    );

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL lighting functions                                             //
    ////////////////////////////////////////////////////////////////////////////
    VOSGLApi VOSGLEntry void glLightModelf(GLenum pname, GLfloat param);
    VOSGLApi VOSGLEntry void glLightModelfv(
        GLenum pname, const GLfloat* params
    );
    VOSGLApi VOSGLEntry void glLightModeli(GLenum pname, GLint param);
    VOSGLApi VOSGLEntry void glLightModeliv(GLenum pname, const GLint* params);
    VOSGLApi VOSGLEntry void glLightf(
        GLenum light, GLenum pname, GLfloat param
    );
    VOSGLApi VOSGLEntry void glLightfv(
        GLenum light, GLenum pname, const GLfloat* params
    );
    VOSGLApi VOSGLEntry void glLighti(GLenum light, GLenum pname, GLint param);
    VOSGLApi VOSGLEntry void glLightiv(
        GLenum light, GLenum pname, const GLint* params
    );
    VOSGLApi VOSGLEntry void glGetLightfv(
        GLenum light, GLenum pname, GLfloat* params
    );
    VOSGLApi VOSGLEntry void glGetLightiv(
        GLenum light, GLenum pname, GLint* params
    );

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL fog functions                                                  //
    ////////////////////////////////////////////////////////////////////////////
    VOSGLApi VOSGLEntry void glFogf(GLenum pname, GLfloat param);
    VOSGLApi VOSGLEntry void glFogfv(GLenum pname, const GLfloat* params);
    VOSGLApi VOSGLEntry void glFogi(GLenum pname, GLint param);
    VOSGLApi VOSGLEntry void glFogiv(GLenum pname, const GLint* params);

    typedef void (*PFNGLFOGCOORDPOINTERPROC)(
        GLenum type, GLsizei stride, const void* pointer
    );
    VOSGLEntry PFNGLFOGCOORDPOINTERPROC glFogCoordPointer;
    typedef void (*PFNGLFOGCOORDDPROC)(GLdouble coord);
    VOSGLEntry PFNGLFOGCOORDDPROC glFogCoordd;
    typedef void (*PFNGLFOGCOORDDVPROC)(const GLdouble* coord);
    VOSGLEntry PFNGLFOGCOORDDVPROC glFogCoorddv;
    typedef void (*PFNGLFOGCOORDFPROC)(GLfloat coord);
    VOSGLEntry PFNGLFOGCOORDFPROC glFogCoordf;
    typedef void (*PFNGLFOGCOORDFVPROC)(const GLfloat* coord);
    VOSGLEntry PFNGLFOGCOORDFVPROC glFogCoordfv;

    ////////////////////////////////////////////////////////////////////////////
    //  OpenGL programs functions                                             //
    ////////////////////////////////////////////////////////////////////////////
    VOSGLApi VOSGLEntry void glShadeModel(GLenum mode);

    typedef void (*PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
    VOSGLEntry PFNGLATTACHSHADERPROC glAttachShader;
    typedef void (*PFNGLCOMPILESHADERPROC)(GLuint shader);
    VOSGLEntry PFNGLCOMPILESHADERPROC glCompileShader;
    typedef GLuint (*PFNGLCREATEPROGRAMPROC)();
    VOSGLEntry PFNGLCREATEPROGRAMPROC glCreateProgram;
    typedef GLuint (*PFNGLCREATESHADERPROC)(GLenum type);
    VOSGLEntry PFNGLCREATESHADERPROC glCreateShader;
    typedef void (*PFNGLDELETEPROGRAMPROC)(GLuint program);
    VOSGLEntry PFNGLDELETEPROGRAMPROC glDeleteProgram;
    typedef void (*PFNGLDELETESHADERPROC)(GLuint shader);
    VOSGLEntry PFNGLDELETESHADERPROC glDeleteShader;
    typedef void (*PFNGLDETACHSHADERPROC)(GLuint program, GLuint shader);
    VOSGLEntry PFNGLDETACHSHADERPROC glDetachShader;
    typedef void (*PFNGLBINDATTRIBLOCATIONPROC)(
        GLuint program, GLuint index, const GLchar* name
    );
    VOSGLEntry PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
    typedef void (*PFNGLGETACTIVEATTRIBPROC)(
        GLuint program, GLuint index, GLsizei maxLength, GLsizei* length,
        GLint* size, GLenum* type, GLchar* name
    );
    VOSGLEntry PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib;
    typedef void (*PFNGLGETACTIVEUNIFORMPROC)(
        GLuint program, GLuint index, GLsizei maxLength, GLsizei* length,
        GLint* size, GLenum* type, GLchar* name
    );
    VOSGLEntry PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform;
    typedef void (*PFNGLGETATTACHEDSHADERSPROC)(
        GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders
    );
    VOSGLEntry PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders;
    typedef GLint (*PFNGLGETATTRIBLOCATIONPROC)(
        GLuint program, const GLchar* name
    );
    VOSGLEntry PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
    typedef void (*PFNGLGETPROGRAMINFOLOGPROC)(
        GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog
    );
    VOSGLEntry PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
    typedef void (*PFNGLGETPROGRAMIVPROC)(
        GLuint program, GLenum pname, GLint* param
    );
    VOSGLEntry PFNGLGETPROGRAMIVPROC glGetProgramiv;
    typedef void (*PFNGLGETSHADERINFOLOGPROC)(
        GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog
    );
    VOSGLEntry PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
    typedef void (*PFNGLGETSHADERSOURCEPROC)(
        GLuint obj, GLsizei maxLength, GLsizei* length, GLchar* source
    );
    VOSGLEntry PFNGLGETSHADERSOURCEPROC glGetShaderSource;
    typedef void (*PFNGLGETSHADERIVPROC)(
        GLuint shader, GLenum pname, GLint* param
    );
    VOSGLEntry PFNGLGETSHADERIVPROC glGetShaderiv;
    typedef GLint (*PFNGLGETUNIFORMLOCATIONPROC)(
        GLuint program, const GLchar* name
    );
    VOSGLEntry PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
    typedef void (*PFNGLGETUNIFORMFVPROC)(
        GLuint program, GLint location, GLfloat* params
    );
    VOSGLEntry PFNGLGETUNIFORMFVPROC glGetUniformfv;
    typedef void (*PFNGLGETUNIFORMIVPROC)(
        GLuint program, GLint location, GLint* params
    );
    VOSGLEntry PFNGLGETUNIFORMIVPROC glGetUniformiv;
    typedef GLboolean (*PFNGLISPROGRAMPROC)(GLuint program);
    VOSGLEntry PFNGLISPROGRAMPROC glIsProgram;
    typedef GLboolean (*PFNGLISSHADERPROC)(GLuint shader);
    VOSGLEntry PFNGLISSHADERPROC glIsShader;
    typedef void (*PFNGLLINKPROGRAMPROC)(GLuint program);
    VOSGLEntry PFNGLLINKPROGRAMPROC glLinkProgram;
    typedef void (*PFNGLSHADERSOURCEPROC)(
        GLuint shader, GLsizei count,
        const GLchar* const* string, const GLint* length
    );
    VOSGLEntry PFNGLSHADERSOURCEPROC glShaderSource;
    typedef void (*PFNGLUSEPROGRAMPROC)(GLuint program);
    VOSGLEntry PFNGLUSEPROGRAMPROC glUseProgram;
    typedef void (*PFNGLVALIDATEPROGRAMPROC)(GLuint program);
    VOSGLEntry PFNGLVALIDATEPROGRAMPROC glValidateProgram;
    typedef void (*PFNGLUNIFORM1FPROC)(GLint location, GLfloat v0);
    VOSGLEntry PFNGLUNIFORM1FPROC glUniform1f;
    typedef void (*PFNGLUNIFORM1FVPROC)(
        GLint location, GLsizei count, const GLfloat* value
    );
    VOSGLEntry PFNGLUNIFORM1FVPROC glUniform1fv;
    typedef void (*PFNGLUNIFORM1IPROC)(GLint location, GLint v0);
    VOSGLEntry PFNGLUNIFORM1IPROC glUniform1i;
    typedef void (*PFNGLUNIFORM1IVPROC)(
        GLint location, GLsizei count, const GLint* value
    );
    VOSGLEntry PFNGLUNIFORM1IVPROC glUniform1iv;
    typedef void (*PFNGLUNIFORM2FPROC)(GLint location, GLfloat v0, GLfloat v1);
    VOSGLEntry PFNGLUNIFORM2FPROC glUniform2f;
    typedef void (*PFNGLUNIFORM2FVPROC)(
        GLint location, GLsizei count, const GLfloat* value
    );
    VOSGLEntry PFNGLUNIFORM2FVPROC glUniform2fv;
    typedef void (*PFNGLUNIFORM2IPROC)(GLint location, GLint v0, GLint v1);
    VOSGLEntry PFNGLUNIFORM2IPROC glUniform2i;
    typedef void (*PFNGLUNIFORM2IVPROC)(
        GLint location, GLsizei count, const GLint* value
    );
    VOSGLEntry PFNGLUNIFORM2IVPROC glUniform2iv;
    typedef void (*PFNGLUNIFORM3FPROC)(
        GLint location, GLfloat v0, GLfloat v1, GLfloat v2
    );
    VOSGLEntry PFNGLUNIFORM3FPROC glUniform3f;
    typedef void (*PFNGLUNIFORM3FVPROC)(
        GLint location, GLsizei count, const GLfloat* value
    );
    VOSGLEntry PFNGLUNIFORM3FVPROC glUniform3fv;
    typedef void (*PFNGLUNIFORM3IPROC)(
        GLint location, GLint v0, GLint v1, GLint v2
    );
    VOSGLEntry PFNGLUNIFORM3IPROC glUniform3i;
    typedef void (*PFNGLUNIFORM3IVPROC)(
        GLint location, GLsizei count, const GLint* value
    );
    VOSGLEntry PFNGLUNIFORM3IVPROC glUniform3iv;
    typedef void (*PFNGLUNIFORM4FPROC)(
        GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3
    );
    VOSGLEntry PFNGLUNIFORM4FPROC glUniform4f;
    typedef void (*PFNGLUNIFORM4FVPROC)(
        GLint location, GLsizei count, const GLfloat* value
    );
    VOSGLEntry PFNGLUNIFORM4FVPROC glUniform4fv;
    typedef void (*PFNGLUNIFORM4IPROC)(
        GLint location, GLint v0, GLint v1, GLint v2, GLint v3
    );
    VOSGLEntry PFNGLUNIFORM4IPROC glUniform4i;
    typedef void (*PFNGLUNIFORM4IVPROC)(
        GLint location, GLsizei count, const GLint* value
    );
    VOSGLEntry PFNGLUNIFORM4IVPROC glUniform4iv;
    typedef void (*PFNGLUNIFORMMATRIX2FVPROC)(
        GLint location, GLsizei count, GLboolean transpose, const GLfloat* value
    );
    VOSGLEntry PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv;
    typedef void (*PFNGLUNIFORMMATRIX3FVPROC)(
        GLint location, GLsizei count, GLboolean transpose, const GLfloat* value
    );
    VOSGLEntry PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
    typedef void (*PFNGLUNIFORMMATRIX4FVPROC)(
        GLint location, GLsizei count, GLboolean transpose, const GLfloat* value
    );
    VOSGLEntry PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;


    ////////////////////////////////////////////////////////////////////////////
    //  Init OpenGL                                                           //
    //  return : True if OpenGL is successfully loaded                        //
    ////////////////////////////////////////////////////////////////////////////
    bool InitOpenGL();

    ////////////////////////////////////////////////////////////////////////////
    //  Init OpenGL 1.2                                                       //
    //  return : True if OpenGL 1.2 is successfully loaded, false otherwise   //
    ////////////////////////////////////////////////////////////////////////////
    bool InitOpenGL_1_2();

    ////////////////////////////////////////////////////////////////////////////
    //  Init OpenGL 1.3                                                       //
    //  return : True if OpenGL 1.3 is successfully loaded, false otherwise   //
    ////////////////////////////////////////////////////////////////////////////
    bool InitOpenGL_1_3();

    ////////////////////////////////////////////////////////////////////////////
    //  Init OpenGL 1.4                                                       //
    //  return : True if OpenGL 1.4 is successfully loaded, false otherwise   //
    ////////////////////////////////////////////////////////////////////////////
    bool InitOpenGL_1_4();

    ////////////////////////////////////////////////////////////////////////////
    //  Init OpenGL 1.5                                                       //
    //  return : True if OpenGL 1.5 is successfully loaded, false otherwise   //
    ////////////////////////////////////////////////////////////////////////////
    bool InitOpenGL_1_5();

    ////////////////////////////////////////////////////////////////////////////
    //  Init OpenGL 2.0                                                       //
    //  return : True if OpenGL 2.0 is successfully loaded, false otherwise   //
    ////////////////////////////////////////////////////////////////////////////
    bool InitOpenGL_2_0();

    ////////////////////////////////////////////////////////////////////////////
    //  Init OpenGL 2.1                                                       //
    //  return : True if OpenGL 2.1 is successfully loaded, false otherwise   //
    ////////////////////////////////////////////////////////////////////////////
    bool InitOpenGL_2_1();


#endif // VOS_RENDERER_OPENGL_OPENGL_HEADER
