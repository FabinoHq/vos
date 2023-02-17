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
//     Renderer/Shaders/Sources/SkyProc.frag : SkyProc fragment shader        //
////////////////////////////////////////////////////////////////////////////////
#version 450
precision highp float;
precision highp int;

// Pi constant
#define MATH_PI 3.1415926535897932384626433832795

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

// Input texture coordinates and output color
layout(location = 0) in vec3 i_texCoords;
layout(location = 0) out vec4 o_color;

// Main shader entry point
void main()
{
    // Normalize texture coords
    vec3 skycoords = normalize(i_texCoords);

    // Compute sun position
    float timeangle = (worldlight.time*MATH_PI);
    vec3 sunpos = normalize(vec3(
        -cos(timeangle)*0.4,
        sin(timeangle)*0.8,
        sin(timeangle)*0.3
    ));

    // Compute time weights
    float sunrise = exp(-(worldlight.time*worldlight.time)*256);
    float day = (sin(worldlight.time*MATH_PI)*0.5)+0.5;
    float sunset = (
        exp(-((worldlight.time-1.0)*(worldlight.time-1.0))*256)+
        exp(-((worldlight.time+1.0)*(worldlight.time+1.0))*256)
    );
    float night = (1.0-day);

    // Compute gradient colors
    vec3 bottomcolor = (
        vec3(0.02, 0.01, 0.08)*night + vec3(0.95, 0.7, 0.01)*sunrise +
        vec3(0.4, 0.75, 0.95)*day + vec3(0.78, 0.35, 0.3)*sunset
    );
    vec3 topcolor = (
        vec3(0.0, 0.0, 0.0)*night + vec3(0.3, 0.55, 0.62)*sunrise +
        vec3(0.04, 0.3, 0.75)*day + vec3(0.27, 0.15, 0.35)*sunset
    );

    // Compute skybox color
    vec3 fragOutput = mix(
        bottomcolor, topcolor,
        smoothstep(0.0, 1.0, (skycoords.y*0.5)+0.2)
    );

    // Compute sun color
    fragOutput += clamp(
        pow(1.0-(distance(skycoords, sunpos))*0.7, 8.0), 0.0, 1.0
    );

    // Compute output color
    o_color = vec4(fragOutput, 1.0);
}
