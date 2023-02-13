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
//     Renderer/Shaders/Sources/HeightMap.vert : Heightmap vertex shader      //
////////////////////////////////////////////////////////////////////////////////
#version 450
precision highp float;
precision highp int;

// WorldLight uniforms
layout(set = 0, binding = 0) uniform WorldLightUniforms
{
    vec4 color;
    vec4 ambient;
    vec3 position;
    float angle;
    vec3 direction;
    float time;
} worldlight;

// Camera uniforms
layout(set = 1, binding = 0) uniform CameraUniforms
{
    mat4 projview;
    mat4 view;
    vec3 position;
    float align;
} camera;

// Model matrix (push constant)
layout(push_constant) uniform ModelMatrix
{
    mat4 model;
} matrix;

// Input and output position and texture coordinates
layout(location = 0) in vec3 i_position;
layout(location = 1) in vec2 i_texCoords;
layout(location = 2) in vec3 i_normals;
layout(location = 0) out vec2 o_texCoords;
layout(location = 1) out vec3 o_normals;
layout(location = 2) out vec3 o_surfaceView;
layout(location = 3) out vec3 o_surfaceLight;
layout(location = 4) out vec2 o_distHeight;
out gl_PerVertex
{
    vec4 gl_Position;
};

// Main shader entry point
void main()
{
    // Compute vertex position
    vec4 vertexPos = (matrix.model*vec4(i_position, 1.0));
    o_texCoords = i_texCoords;
    o_normals = normalize(mat3(matrix.model)*i_normals);
    o_surfaceView = (camera.position - vertexPos.xyz);
    o_surfaceLight = (worldlight.position - vertexPos.xyz);
    o_distHeight.x = i_position.y;
    o_distHeight.y = length((camera.view*vertexPos).xyz);

    // Compute output vertex
    gl_Position = (camera.projview*vertexPos);
}
