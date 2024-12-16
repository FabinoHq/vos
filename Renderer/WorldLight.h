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
//     Renderer/WorldLight.h : World light management                         //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_WORLDLIGHT_HEADER
#define VOS_RENDERER_WORLDLIGHT_HEADER

    #include "../System/System.h"

    #include "Vulkan/Vulkan.h"
    #include "Vulkan/GraphicsLayout.h"
    #include "Vulkan/Swapchain.h"
    #include "Vulkan/UniformBuffer.h"

    #include "../Math/Math.h"
    #include "../Math/Vector3.h"
    #include "../Math/Vector4.h"


    ////////////////////////////////////////////////////////////////////////////
    //  WorldLightUniformData data structure                                  //
    ////////////////////////////////////////////////////////////////////////////
    struct WorldLightUniformData
    {
        float   color[4];       // Light color
        float   ambient[4];     // Ambient color
        float   position[3];    // Light position
        float   angle;          // Light angle
        float   direction[3];   // Light direction
        float   time;           // Day time
    };

    ////////////////////////////////////////////////////////////////////////////
    //  WorldLightUniformData data structure fixed size                       //
    ////////////////////////////////////////////////////////////////////////////
    const size_t WorldLightUniformDataSize = (sizeof(float)*16);

    ////////////////////////////////////////////////////////////////////////////
    //  WorldLight distance from camera                                       //
    ////////////////////////////////////////////////////////////////////////////
    const float WorldLightDistanceFromCamera = 100000.0f;


    ////////////////////////////////////////////////////////////////////////////
    //  WorldLight class definition                                           //
    ////////////////////////////////////////////////////////////////////////////
    class WorldLight
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  WorldLight default constructor                                //
            ////////////////////////////////////////////////////////////////////
            WorldLight();

            ////////////////////////////////////////////////////////////////////
            //  WorldLight destructor                                         //
            ////////////////////////////////////////////////////////////////////
            ~WorldLight();


            ////////////////////////////////////////////////////////////////////
            //  Init world light                                              //
            //  return : True if world light is successfully created          //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Destroy world light                                           //
            ////////////////////////////////////////////////////////////////////
            void destroyWorldLight();

            ////////////////////////////////////////////////////////////////////
            //  Compute world light                                           //
            //  return : True if world lights are successfully computed       //
            ////////////////////////////////////////////////////////////////////
            bool compute(const Vector3& cameraPosition);

            ////////////////////////////////////////////////////////////////////
            //  Bind world light                                              //
            ////////////////////////////////////////////////////////////////////
            inline void bind()
            {
                vkCmdBindDescriptorSets(
                    GSwapchain.commandBuffers[GSwapchain.current],
                    VK_PIPELINE_BIND_POINT_GRAPHICS, GGraphicsLayout.handle,
                    DESC_WORLDLIGHT, 1,
                    &descriptorSets[GSwapchain.current], 0, 0
                );
            }


        private:
            ////////////////////////////////////////////////////////////////////
            //  WorldLight private copy constructor : Not copyable            //
            ////////////////////////////////////////////////////////////////////
            WorldLight(const WorldLight&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  WorldLight private copy operator : Not copyable               //
            ////////////////////////////////////////////////////////////////////
            WorldLight& operator=(const WorldLight&) = delete;


        public:
            VkDescriptorSet     descriptorSets[RendererMaxSwapchainFrames];
            UniformBuffer       uniformBuffers[RendererMaxSwapchainFrames];
            Vector4             color;              // Light color
            Vector4             ambient;            // Ambient color
            Vector3             position;           // Light position
            Vector3             direction;          // Light direction
            Vector3             angles;             // Light angles
            float               time;               // Day time (-1.0 to 1.0)
    };


    ////////////////////////////////////////////////////////////////////////////
    //  WorldLight global instance                                            //
    ////////////////////////////////////////////////////////////////////////////
    extern WorldLight GWorldLight;


#endif // VOS_RENDERER_WORLDLIGHT_HEADER
