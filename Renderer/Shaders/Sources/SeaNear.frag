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
//     Renderer/Shaders/Sources/SeaNear.frag : SeaNear fragment shader        //
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

// Distance fades
const float alphaFadeNear = 1200.0;
const float alphaFadeDistance = 1200.0;

// Input texture coordinates and output color
layout(location = 0) in vec2 i_texCoords;
layout(location = 1) in vec3 i_normals;
layout(location = 2) in vec3 i_surfaceView;
layout(location = 3) in vec3 i_surfaceLight;
layout(location = 4) in float i_distance;
layout(location = 0) out vec4 o_color;

// Main shader entry point
void main()
{
    // Water color
    vec4 fragOutput = vec4(0.1, 0.3, 0.5, 1.0);

    // Compute distance fades
    float alphaFade = clamp(
        clamp(((i_distance+alphaFadeNear)*0.0005), 0.7, 1.0)*
        clamp(1.0-((i_distance-alphaFadeDistance)*0.002), 0.0, 1.0),
        0.0, 1.0
    );
    fragOutput.a *= alphaFade;

    // Compute output color
    o_color = fragOutput;
}
