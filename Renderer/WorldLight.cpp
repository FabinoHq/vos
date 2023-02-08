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
//     Renderer/WorldLight.cpp : World light management                       //
////////////////////////////////////////////////////////////////////////////////
#include "WorldLight.h"


////////////////////////////////////////////////////////////////////////////////
//  WorldLight global instance                                                //
////////////////////////////////////////////////////////////////////////////////
WorldLight GWorldLight = WorldLight();


////////////////////////////////////////////////////////////////////////////////
//  WorldLight default constructor                                            //
////////////////////////////////////////////////////////////////////////////////
WorldLight::WorldLight() :
color(1.0f, 0.9f, 0.8f, 0.8f),
ambient(0.4f, 0.4f, 0.4f, 0.4f),
position(0.0f, 0.0f, 0.0f),
direction(0.0f, 0.0f, 0.0f),
angles(-1.0f, 1.5708f, 0.0f)
{
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        descriptorSets[i] = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  WorldLight destructor                                                     //
////////////////////////////////////////////////////////////////////////////////
WorldLight::~WorldLight()
{
    angles.reset();
    direction.reset();
    position.reset();
    ambient.reset();
    color.reset();
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        descriptorSets[i] = 0;
    }
}


////////////////////////////////////////////////////////////////////////////////
//  Init world light                                                          //
//  return : True if world light is successfully created                      //
////////////////////////////////////////////////////////////////////////////////
bool WorldLight::init()
{
    // Check WorldLightData size
    size_t worldLightUniformDataSize = sizeof(WorldLightUniformData);
    if (worldLightUniformDataSize != WorldLightUniformDataSize)
    {
        // Invalid WorldLightUniformData size
        return false;
    }

    // Copy world light data into world light uniform data
    WorldLightUniformData worldLightUniformData;
    memcpy(
        worldLightUniformData.color, color.vec, sizeof(color.vec)
    );
    memcpy(
        worldLightUniformData.ambient, ambient.vec, sizeof(ambient.vec)
    );
    memcpy(
        worldLightUniformData.position, position.vec, sizeof(position.vec)
    );
    worldLightUniformData.angleX = angles.vec[0];
    memcpy(
        worldLightUniformData.direction, direction.vec, sizeof(direction.vec)
    );
    worldLightUniformData.angleY = angles.vec[1];

    // Create world light uniform buffers
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        if (!uniformBuffers[i].createBuffer(sizeof(worldLightUniformData)))
        {
            // Could not create world light uniform buffer
            return false;
        }
    }

    // Create world light descriptor set
    VkDescriptorSetAllocateInfo descriptorInfo;
    descriptorInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    descriptorInfo.pNext = 0;
    descriptorInfo.descriptorPool = GGraphicsLayout.worldlightDescPool;
    descriptorInfo.descriptorSetCount = RendererMaxSwapchainFrames;
    descriptorInfo.pSetLayouts = &GGraphicsLayout.swapSetLayouts[
        DESC_WORLDLIGHT*RendererMaxSwapchainFrames
    ];

    if (vkAllocateDescriptorSets(GVulkanDevice,
        &descriptorInfo, descriptorSets) != VK_SUCCESS)
    {
        // Could not allocate matrices descriptor sets
        return false;
    }

    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        // Update descriptor sets
        VkDescriptorBufferInfo descBufferInfo;
        descBufferInfo.buffer = uniformBuffers[i].uniformBuffer.handle;
        descBufferInfo.offset = 0;
        descBufferInfo.range = uniformBuffers[i].uniformBuffer.size;

        // Update matrices descriptor sets
        VkWriteDescriptorSet descriptorWrites;

        descriptorWrites.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites.pNext = 0;
        descriptorWrites.dstSet = descriptorSets[i];
        descriptorWrites.dstBinding = 0;
        descriptorWrites.dstArrayElement = 0;
        descriptorWrites.descriptorCount = 1;
        descriptorWrites.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrites.pImageInfo = 0;
        descriptorWrites.pBufferInfo = &descBufferInfo;
        descriptorWrites.pTexelBufferView = 0;

        vkUpdateDescriptorSets(GVulkanDevice, 1, &descriptorWrites, 0, 0);
    }

    // World light sucessfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy world light                                                       //
////////////////////////////////////////////////////////////////////////////////
void WorldLight::destroyWorldLight()
{
    // Destroy uniform buffers and descriptor sets
    angles.reset();
    direction.reset();
    position.reset();
    ambient.reset();
    color.reset();
    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        uniformBuffers[i].destroyBuffer();
        descriptorSets[i] = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Compute world light                                                       //
//  return : True if world lights are successfully computed                   //
////////////////////////////////////////////////////////////////////////////////
bool WorldLight::compute(const Vector3& cameraPosition)
{
    // Compute world light position
    position.vec[0] = std::cos(angles.vec[0]);
    position.vec[0] *= std::sin(angles.vec[1]);
    position.vec[1] = std::sin(-angles.vec[0]);
    position.vec[2] = std::cos(angles.vec[0]);
    position.vec[2] *= std::cos(angles.vec[1]);
    position *= WorldLightDistanceFromCamera;
    position += cameraPosition;

    // Compute world light direction
    direction = (position-cameraPosition);
    direction.normalize();

    // Copy world light data into world light uniform data
    WorldLightUniformData worldLightUniformData;
    memcpy(
        worldLightUniformData.color, color.vec, sizeof(color.vec)
    );
    memcpy(
        worldLightUniformData.ambient, ambient.vec, sizeof(ambient.vec)
    );
    memcpy(
        worldLightUniformData.position, position.vec, sizeof(position.vec)
    );
    worldLightUniformData.angleX = angles.vec[0];
    memcpy(
        worldLightUniformData.direction, direction.vec, sizeof(direction.vec)
    );
    worldLightUniformData.angleY = angles.vec[1];

    // Update world light uniform buffer
    if (!uniformBuffers[GSwapchain.current].updateBufferVertex(
        &worldLightUniformData, sizeof(worldLightUniformData)))
    {
        // Could not update world light uniform buffer
        return false;
    }

    // View successfully computed
    return true;
}
