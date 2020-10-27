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
//     Renderer/Sprite.h : Sprite management                                  //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_SPRITE_HEADER
#define VOS_RENDERER_SPRITE_HEADER

    #include "Vulkan.h"
    #include "Texture.h"
    #include "VulkanBuffer.h"
    #include "UniformBuffer.h"
    #include "GraphicsPipeline.h"
    #include "../Math/Math.h"
    #include "../Math/Matrix4x4.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Sprite class definition                                               //
    ////////////////////////////////////////////////////////////////////////////
    class Sprite
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Sprite default constructor                                    //
            ////////////////////////////////////////////////////////////////////
            Sprite();

            ////////////////////////////////////////////////////////////////////
            //  Sprite destructor                                             //
            ////////////////////////////////////////////////////////////////////
            ~Sprite();


            ////////////////////////////////////////////////////////////////////
            //  Init sprite                                                   //
            //  return : True if the sprite is successfully created           //
            ////////////////////////////////////////////////////////////////////
            bool init(VkDevice vulkanDevice, GraphicsPipeline& pipeline,
                UniformBuffer* uniformBuffers, Texture& texture,
                float width, float height);


        private:
            ////////////////////////////////////////////////////////////////////
            //  Sprite private copy constructor : Not copyable                //
            ////////////////////////////////////////////////////////////////////
            Sprite(const Sprite&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Sprite private copy operator : Not copyable                   //
            ////////////////////////////////////////////////////////////////////
            Sprite& operator=(const Sprite&) = delete;


            ////////////////////////////////////////////////////////////////////
            //  Create descriptor sets                                        //
            //  return : True if descriptor sets are successfully created     //
            ////////////////////////////////////////////////////////////////////
            bool createDescriptorSets(VkDevice vulkanDevice,
                GraphicsPipeline& pipeline, UniformBuffer* uniformBuffers);


        public:
            VkDescriptorSet     m_descriptorSets[RendererMaxSwapchainFrames];
            Matrix4x4           m_modelMatrix;      // Sprite model matrix
            Texture*            m_texture;          // Sprite texture pointer
            Vector2             m_position;         // Sprite position
            Vector2             m_size;             // Sprite size
            float               m_angle;            // Sprite angle
    };


#endif // VOS_RENDERER_SPRITE_HEADER
