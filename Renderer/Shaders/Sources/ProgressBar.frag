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
//     Renderer/Shaders/Sources/ProgressBar.frag : ProgressBar frag shader    //
////////////////////////////////////////////////////////////////////////////////
#version 450
precision highp float;
precision highp int;

// Texture sampler
layout(set = 2, binding = 0) uniform sampler2D texSampler;

// Color, offset, size, and time (push constant)
layout(push_constant) uniform Constants
{
	layout(offset = 64)
    vec4 color;
    vec2 offset;
    vec2 size;
    float time;
} constants;

// Input texture coordinates and output color
layout(location = 0) in vec2 i_texCoords;
layout(location = 0) out vec4 o_color;

// Main shader entry point
void main()
{
    // Compute threepatch UVs (constants.time is the UVs factor)
    float patchSize = abs(constants.size.x*constants.time*constants.offset.x);
    float patchCoords = i_texCoords.x*patchSize;
    if (patchCoords >= 0.25)
    {
        if (patchCoords >= (patchSize-0.25))
        {
            patchCoords -= (patchSize-0.25)-0.75;
        }
        else
        {
            patchCoords = 0.25+mod(patchCoords, 0.5);
        }
    }
    if (patchSize <= 0.5)
    {
        if (i_texCoords.x >= 0.5)
        {
            patchCoords = 0.5+
                ((1.0-(constants.time*constants.offset.x))*0.5)+
                (i_texCoords.x*patchSize);
        }
        else
        {
            patchCoords = (i_texCoords.x*patchSize);
        }
    }

    // Compute output color
    o_color = (texture(
        texSampler, vec2(patchCoords, (i_texCoords.y*0.5)+constants.offset.y)
    )*constants.color);
}
