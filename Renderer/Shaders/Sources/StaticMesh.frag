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
//     Renderer/Shaders/Sources/StaticMesh.frag : Static mesh fragment shader //
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
    float angleX;
    vec3 direction;
    float angleY;
} worldlight;

// Texture sampler
layout(set = 2, binding = 0) uniform sampler2D texSampler;

// Input texture coordinates and output color
layout(location = 0) in vec2 i_texCoords;
layout(location = 1) in vec3 i_normals;
layout(location = 2) in vec3 i_surfaceView;
layout(location = 3) in vec3 i_surfaceLight;
layout(location = 0) out vec4 o_color;

// Main shader entry point
void main()
{
    // Texture sampling
    vec4 fragOutput = texture(texSampler, i_texCoords);

    // Compute world light
    float dirLight = clamp(dot(i_normals, worldlight.direction), 0.0, 1.0);
    vec3 worldLight = (worldlight.color.rgb*worldlight.color.a*dirLight);
    vec3 ambientLight = (worldlight.ambient.rgb*worldlight.ambient.a);
    vec3 surfaceView = normalize(i_surfaceView);
    vec3 surfaceLight = normalize(i_surfaceLight);
    vec3 halfSurface = normalize(surfaceLight+surfaceView);
    float dotLight = clamp(dot(i_normals, surfaceLight), 0.0, 1.0);
    float specular = pow(clamp(dot(i_normals, halfSurface), 0.0001, 1.0), 16.0);
    vec3 pointLight = (worldlight.color.rgb*worldlight.color.a*dotLight);
    vec3 specLight = (worldlight.color.rgb*worldlight.color.a*specular);

    // Compute output color
    o_color = vec4(
        (fragOutput.xyz*ambientLight) +
        (fragOutput.xyz*worldLight) +
        (fragOutput.xyz*pointLight)*vec3(0.4) +
        (fragOutput.xyz*specLight)*vec3(0.35),
        fragOutput.a
    );
}
