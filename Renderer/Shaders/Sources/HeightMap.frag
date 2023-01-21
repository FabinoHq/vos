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
//     Renderer/Shaders/Sources/HeightMap.frag : Heightmap fragment shader    //
////////////////////////////////////////////////////////////////////////////////
#version 450
precision highp float;
precision highp int;

// Texture sampler
layout(set = 1, binding = 0) uniform sampler2DArray texSampler;

// Color, position, offset, and time (push constant)
layout(push_constant) uniform Constants
{
	layout(offset = 64)
    vec4 color;
    vec2 offset;
    vec2 size;
    float time;
} constants;

// Distance fades
const float mixFadeDistance = 50.0;
const float alphaFadeDistance = 1200.0;

// Input texture coordinates and output color
layout(location = 0) in vec2 i_texCoords;
layout(location = 1) in vec3 i_normals;
layout(location = 2) in vec2 i_distHeight;
layout(location = 0) out vec4 o_color;
void main()
{
    // Heightmap texture layers
    float yHeight = ((i_distHeight.x-100.0)*0.004);
    float yLayer = clamp(floor(yHeight), 0.0, 3.0);
    float yLayer2 = clamp(ceil(yHeight-0.8), 0.0, 3.0);
    float mixLayers = clamp(((yHeight-0.8)-yLayer)*5.0, 0.0, 1.0);

    // Sample textures
    vec4 texColor = texture(texSampler, vec3(i_texCoords, yLayer));
    vec4 farColor = texture(texSampler, vec3((i_texCoords*0.125), yLayer));
    vec4 texColor2 = texture(texSampler, vec3(i_texCoords, yLayer2));
    vec4 farColor2 = texture(texSampler, vec3((i_texCoords*0.125), yLayer2));
    vec4 finalNear = mix(texColor, texColor2, mixLayers);
    vec4 finalFar = mix(farColor, farColor2, mixLayers);

    // Compute distance fades
    float distanceMix = clamp(
        (i_distHeight.y-mixFadeDistance)*0.005, 0.0, 1.0
    );
    float alphaFade = clamp(
        1.0-((i_distHeight.y-alphaFadeDistance)*0.01), 0.0, 1.0
    );

    // Compute output color
    vec4 fragOutput = mix(finalNear, finalFar, distanceMix);
    fragOutput.a *= alphaFade;
    o_color = (fragOutput*constants.color);
}
