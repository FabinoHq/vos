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
//     Renderer/Shaders/ProgressBar.h : GUI ProgressBar shader                //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_SHADERS_PROGRESSBAR_HEADER
#define VOS_RENDERER_SHADERS_PROGRESSBAR_HEADER

    #include "../../System/System.h"

    #include <cstddef>
    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  Progress bar fragment shader                                          //
    ////////////////////////////////////////////////////////////////////////////
    const size_t ProgressBarFragmentShaderSize = 2396;
    const uint32_t ProgressBarFragmentShader[] =
    {
        0x07230203u, 0x00010000u, 0x00080000u, 0x00000065u,
        0x00000000u, 0x00020011u, 0x00000001u, 0x0006000Bu,
        0x00000001u, 0x4C534C47u, 0x6474732Eu, 0x3035342Eu,
        0x00000000u, 0x0003000Eu, 0x00000000u, 0x00000001u,
        0x0007000Fu, 0x00000004u, 0x00000004u, 0x6E69616Du,
        0x00000000u, 0x00000020u, 0x00000050u, 0x00030010u,
        0x00000004u, 0x00000007u, 0x00030003u, 0x00000002u,
        0x000001C2u, 0x00040005u, 0x00000004u, 0x6E69616Du,
        0x00000000u, 0x00050005u, 0x00000008u, 0x63746170u,
        0x7A695368u, 0x00000065u, 0x00050005u, 0x0000000Bu,
        0x736E6F43u, 0x746E6174u, 0x00000073u, 0x00050006u,
        0x0000000Bu, 0x00000000u, 0x6F6C6F63u, 0x00000072u,
        0x00050006u, 0x0000000Bu, 0x00000001u, 0x7366666Fu,
        0x00007465u, 0x00050006u, 0x0000000Bu, 0x00000002u,
        0x657A6973u, 0x00000000u, 0x00050006u, 0x0000000Bu,
        0x00000003u, 0x656D6974u, 0x00000000u, 0x00050005u,
        0x0000000Du, 0x736E6F63u, 0x746E6174u, 0x00000073u,
        0x00050005u, 0x0000001Eu, 0x63746170u, 0x6F6F4368u,
        0x00736472u, 0x00050005u, 0x00000020u, 0x65745F69u,
        0x6F6F4378u, 0x00736472u, 0x00040005u, 0x00000050u,
        0x6F635F6Fu, 0x00726F6Cu, 0x00050005u, 0x00000054u,
        0x53786574u, 0x6C706D61u, 0x00007265u, 0x00030047u,
        0x0000000Bu, 0x00000002u, 0x00050048u, 0x0000000Bu,
        0x00000000u, 0x00000023u, 0x00000040u, 0x00050048u,
        0x0000000Bu, 0x00000001u, 0x00000023u, 0x00000050u,
        0x00050048u, 0x0000000Bu, 0x00000002u, 0x00000023u,
        0x00000058u, 0x00050048u, 0x0000000Bu, 0x00000003u,
        0x00000023u, 0x00000060u, 0x00040047u, 0x00000020u,
        0x0000001Eu, 0x00000000u, 0x00040047u, 0x00000050u,
        0x0000001Eu, 0x00000000u, 0x00040047u, 0x00000054u,
        0x00000021u, 0x00000000u, 0x00040047u, 0x00000054u,
        0x00000022u, 0x00000002u, 0x00020013u, 0x00000002u,
        0x00030021u, 0x00000003u, 0x00000002u, 0x00030016u,
        0x00000006u, 0x00000020u, 0x00040020u, 0x00000007u,
        0x00000007u, 0x00000006u, 0x00040017u, 0x00000009u,
        0x00000006u, 0x00000004u, 0x00040017u, 0x0000000Au,
        0x00000006u, 0x00000002u, 0x0006001Eu, 0x0000000Bu,
        0x00000009u, 0x0000000Au, 0x0000000Au, 0x00000006u,
        0x00040020u, 0x0000000Cu, 0x00000009u, 0x0000000Bu,
        0x0004003Bu, 0x0000000Cu, 0x0000000Du, 0x00000009u,
        0x00040015u, 0x0000000Eu, 0x00000020u, 0x00000001u,
        0x0004002Bu, 0x0000000Eu, 0x0000000Fu, 0x00000002u,
        0x00040015u, 0x00000010u, 0x00000020u, 0x00000000u,
        0x0004002Bu, 0x00000010u, 0x00000011u, 0x00000000u,
        0x00040020u, 0x00000012u, 0x00000009u, 0x00000006u,
        0x0004002Bu, 0x0000000Eu, 0x00000015u, 0x00000003u,
        0x0004002Bu, 0x0000000Eu, 0x00000019u, 0x00000001u,
        0x00040020u, 0x0000001Fu, 0x00000001u, 0x0000000Au,
        0x0004003Bu, 0x0000001Fu, 0x00000020u, 0x00000001u,
        0x00040020u, 0x00000021u, 0x00000001u, 0x00000006u,
        0x0004002Bu, 0x00000006u, 0x00000027u, 0x3E800000u,
        0x00020014u, 0x00000028u, 0x0004002Bu, 0x00000006u,
        0x00000034u, 0x3F400000u, 0x0004002Bu, 0x00000006u,
        0x0000003Au, 0x3F000000u, 0x0004002Bu, 0x00000006u,
        0x0000004Au, 0x3F800000u, 0x00040020u, 0x0000004Fu,
        0x00000003u, 0x00000009u, 0x0004003Bu, 0x0000004Fu,
        0x00000050u, 0x00000003u, 0x00090019u, 0x00000051u,
        0x00000006u, 0x00000001u, 0x00000000u, 0x00000000u,
        0x00000000u, 0x00000001u, 0x00000000u, 0x0003001Bu,
        0x00000052u, 0x00000051u, 0x00040020u, 0x00000053u,
        0x00000000u, 0x00000052u, 0x0004003Bu, 0x00000053u,
        0x00000054u, 0x00000000u, 0x0004002Bu, 0x00000010u,
        0x00000057u, 0x00000001u, 0x0004002Bu, 0x0000000Eu,
        0x00000060u, 0x00000000u, 0x00040020u, 0x00000061u,
        0x00000009u, 0x00000009u, 0x00050036u, 0x00000002u,
        0x00000004u, 0x00000000u, 0x00000003u, 0x000200F8u,
        0x00000005u, 0x0004003Bu, 0x00000007u, 0x00000008u,
        0x00000007u, 0x0004003Bu, 0x00000007u, 0x0000001Eu,
        0x00000007u, 0x00060041u, 0x00000012u, 0x00000013u,
        0x0000000Du, 0x0000000Fu, 0x00000011u, 0x0004003Du,
        0x00000006u, 0x00000014u, 0x00000013u, 0x00050041u,
        0x00000012u, 0x00000016u, 0x0000000Du, 0x00000015u,
        0x0004003Du, 0x00000006u, 0x00000017u, 0x00000016u,
        0x00050085u, 0x00000006u, 0x00000018u, 0x00000014u,
        0x00000017u, 0x00060041u, 0x00000012u, 0x0000001Au,
        0x0000000Du, 0x00000019u, 0x00000011u, 0x0004003Du,
        0x00000006u, 0x0000001Bu, 0x0000001Au, 0x00050085u,
        0x00000006u, 0x0000001Cu, 0x00000018u, 0x0000001Bu,
        0x0006000Cu, 0x00000006u, 0x0000001Du, 0x00000001u,
        0x00000004u, 0x0000001Cu, 0x0003003Eu, 0x00000008u,
        0x0000001Du, 0x00050041u, 0x00000021u, 0x00000022u,
        0x00000020u, 0x00000011u, 0x0004003Du, 0x00000006u,
        0x00000023u, 0x00000022u, 0x0004003Du, 0x00000006u,
        0x00000024u, 0x00000008u, 0x00050085u, 0x00000006u,
        0x00000025u, 0x00000023u, 0x00000024u, 0x0003003Eu,
        0x0000001Eu, 0x00000025u, 0x0004003Du, 0x00000006u,
        0x00000026u, 0x0000001Eu, 0x000500BEu, 0x00000028u,
        0x00000029u, 0x00000026u, 0x00000027u, 0x000300F7u,
        0x0000002Bu, 0x00000000u, 0x000400FAu, 0x00000029u,
        0x0000002Au, 0x0000002Bu, 0x000200F8u, 0x0000002Au,
        0x0004003Du, 0x00000006u, 0x0000002Cu, 0x0000001Eu,
        0x0004003Du, 0x00000006u, 0x0000002Du, 0x00000008u,
        0x00050083u, 0x00000006u, 0x0000002Eu, 0x0000002Du,
        0x00000027u, 0x000500BEu, 0x00000028u, 0x0000002Fu,
        0x0000002Cu, 0x0000002Eu, 0x000300F7u, 0x00000031u,
        0x00000000u, 0x000400FAu, 0x0000002Fu, 0x00000030u,
        0x00000038u, 0x000200F8u, 0x00000030u, 0x0004003Du,
        0x00000006u, 0x00000032u, 0x00000008u, 0x00050083u,
        0x00000006u, 0x00000033u, 0x00000032u, 0x00000027u,
        0x00050083u, 0x00000006u, 0x00000035u, 0x00000033u,
        0x00000034u, 0x0004003Du, 0x00000006u, 0x00000036u,
        0x0000001Eu, 0x00050083u, 0x00000006u, 0x00000037u,
        0x00000036u, 0x00000035u, 0x0003003Eu, 0x0000001Eu,
        0x00000037u, 0x000200F9u, 0x00000031u, 0x000200F8u,
        0x00000038u, 0x0004003Du, 0x00000006u, 0x00000039u,
        0x0000001Eu, 0x0005008Du, 0x00000006u, 0x0000003Bu,
        0x00000039u, 0x0000003Au, 0x00050081u, 0x00000006u,
        0x0000003Cu, 0x00000027u, 0x0000003Bu, 0x0003003Eu,
        0x0000001Eu, 0x0000003Cu, 0x000200F9u, 0x00000031u,
        0x000200F8u, 0x00000031u, 0x000200F9u, 0x0000002Bu,
        0x000200F8u, 0x0000002Bu, 0x0004003Du, 0x00000006u,
        0x0000003Du, 0x00000008u, 0x000500BCu, 0x00000028u,
        0x0000003Eu, 0x0000003Du, 0x0000003Au, 0x000300F7u,
        0x00000040u, 0x00000000u, 0x000400FAu, 0x0000003Eu,
        0x0000003Fu, 0x00000040u, 0x000200F8u, 0x0000003Fu,
        0x00050041u, 0x00000021u, 0x00000041u, 0x00000020u,
        0x00000011u, 0x0004003Du, 0x00000006u, 0x00000042u,
        0x00000041u, 0x0004003Du, 0x00000006u, 0x00000043u,
        0x00000008u, 0x00050085u, 0x00000006u, 0x00000044u,
        0x00000042u, 0x00000043u, 0x0003003Eu, 0x0000001Eu,
        0x00000044u, 0x00050041u, 0x00000021u, 0x00000045u,
        0x00000020u, 0x00000011u, 0x0004003Du, 0x00000006u,
        0x00000046u, 0x00000045u, 0x000500BEu, 0x00000028u,
        0x00000047u, 0x00000046u, 0x0000003Au, 0x000300F7u,
        0x00000049u, 0x00000000u, 0x000400FAu, 0x00000047u,
        0x00000048u, 0x00000049u, 0x000200F8u, 0x00000048u,
        0x0004003Du, 0x00000006u, 0x0000004Bu, 0x00000008u,
        0x00050083u, 0x00000006u, 0x0000004Cu, 0x0000004Au,
        0x0000004Bu, 0x0004003Du, 0x00000006u, 0x0000004Du,
        0x0000001Eu, 0x00050081u, 0x00000006u, 0x0000004Eu,
        0x0000004Du, 0x0000004Cu, 0x0003003Eu, 0x0000001Eu,
        0x0000004Eu, 0x000200F9u, 0x00000049u, 0x000200F8u,
        0x00000049u, 0x000200F9u, 0x00000040u, 0x000200F8u,
        0x00000040u, 0x0004003Du, 0x00000052u, 0x00000055u,
        0x00000054u, 0x0004003Du, 0x00000006u, 0x00000056u,
        0x0000001Eu, 0x00050041u, 0x00000021u, 0x00000058u,
        0x00000020u, 0x00000057u, 0x0004003Du, 0x00000006u,
        0x00000059u, 0x00000058u, 0x00050085u, 0x00000006u,
        0x0000005Au, 0x00000059u, 0x0000003Au, 0x00060041u,
        0x00000012u, 0x0000005Bu, 0x0000000Du, 0x00000019u,
        0x00000057u, 0x0004003Du, 0x00000006u, 0x0000005Cu,
        0x0000005Bu, 0x00050081u, 0x00000006u, 0x0000005Du,
        0x0000005Au, 0x0000005Cu, 0x00050050u, 0x0000000Au,
        0x0000005Eu, 0x00000056u, 0x0000005Du, 0x00050057u,
        0x00000009u, 0x0000005Fu, 0x00000055u, 0x0000005Eu,
        0x00050041u, 0x00000061u, 0x00000062u, 0x0000000Du,
        0x00000060u, 0x0004003Du, 0x00000009u, 0x00000063u,
        0x00000062u, 0x00050085u, 0x00000009u, 0x00000064u,
        0x0000005Fu, 0x00000063u, 0x0003003Eu, 0x00000050u,
        0x00000064u, 0x000100FDu, 0x00010038u
    };


#endif // VOS_RENDERER_SHADERS_PROGRESSBAR_HEADER
