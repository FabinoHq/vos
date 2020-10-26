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
//     Renderer/Sprite.cpp : Sprite management                                //
////////////////////////////////////////////////////////////////////////////////
#include "Sprite.h"


////////////////////////////////////////////////////////////////////////////////
//  Sprite default constructor                                                //
////////////////////////////////////////////////////////////////////////////////
Sprite::Sprite() :
m_modelMatrix(),
m_texture(0),
m_position(0.0f, 0.0f),
m_size(1.0f, 1.0f),
m_angle(0.0f)
{
	for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
	{
		m_descriptorSets[i] = 0;
	}
	m_modelMatrix.setIdentity();
}

////////////////////////////////////////////////////////////////////////////////
//  Sprite destructor                                                         //
////////////////////////////////////////////////////////////////////////////////
Sprite::~Sprite()
{
	m_angle = 0.0f;
	m_size.reset();
	m_position.reset();
	m_texture = 0;
	m_modelMatrix.reset();
	for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
	{
		m_descriptorSets[i] = 0;
	}
}


////////////////////////////////////////////////////////////////////////////////
//  Init sprite                                                               //
//  return : True if the sprite is successfully created                       //
////////////////////////////////////////////////////////////////////////////////
bool Sprite::init(VkDevice vulkanDevice, VulkanPipeline& pipeline,
	Texture& texture, float width, float height)
{
	// Check Vulkan device
	if (!vulkanDevice)
	{
		// Invalid Vulkan device
		return false;
	}

	// Check pipeline handle
	if (!pipeline.handle)
	{
		// Invalid pipeline handle
		return false;
	}

	// Check texture handle
	if (!texture.handle)
	{
		// Invalid texture handle
		return false;
	}

	// Reset descriptor sets
	for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
	{
		m_descriptorSets[i] = 0;
	}

	// Set sprite texture pointer
	m_texture = &texture;

	// Create descriptor sets
	if (!createDescriptorSets(vulkanDevice, pipeline))
	{
		// Could not create descriptor sets
		return false;
	}

	// Reset sprite model matrix
	m_modelMatrix.setIdentity();

	// Reset sprite position
	m_position.reset();

	// Set sprite size
	m_size.set(width, height);

	// Reset sprite angle
	m_angle = 0.0f;

	// Sprite successfully created
	return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Create descriptor sets                                                    //
//  return : True if descriptor sets are successfully created                 //
////////////////////////////////////////////////////////////////////////////////
bool Sprite::createDescriptorSets(VkDevice vulkanDevice,
	VulkanPipeline& pipeline)
{
    // Create descriptor sets
    VkDescriptorSetAllocateInfo descriptorInfo;
    descriptorInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    descriptorInfo.pNext = 0;
    descriptorInfo.descriptorPool = pipeline.descPool;
    descriptorInfo.descriptorSetCount = RendererMaxSwapchainFrames;
    descriptorInfo.pSetLayouts = pipeline.descSetLayouts;

    if (vkAllocateDescriptorSets(
        vulkanDevice, &descriptorInfo, m_descriptorSets) != VK_SUCCESS)
    {
        // Could not allocate descriptor sets
        return false;
    }

    for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
    {
        // Update descriptor set
        VkDescriptorBufferInfo bufferInfo;
        bufferInfo.buffer = m_uniformBuffers[i].uniformBuffer.handle;
        bufferInfo.offset = 0;
        bufferInfo.range = m_uniformBuffers[i].uniformBuffer.size;

        VkDescriptorImageInfo imageInfo;
        imageInfo.sampler = m_texture->sampler;
        imageInfo.imageView = m_texture->view;
        imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

        VkWriteDescriptorSet descriptorWrites[2];

        descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[0].pNext = 0;
        descriptorWrites[0].dstSet = m_descriptorSets[i];
        descriptorWrites[0].dstBinding = 0;
        descriptorWrites[0].dstArrayElement = 0;
        descriptorWrites[0].descriptorCount = 1;
        descriptorWrites[0].descriptorType =
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrites[0].pImageInfo = 0;
        descriptorWrites[0].pBufferInfo = &bufferInfo;
        descriptorWrites[0].pTexelBufferView = 0;

        descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[1].pNext = 0;
        descriptorWrites[1].dstSet = m_descriptorSets[i];
        descriptorWrites[1].dstBinding = 1;
        descriptorWrites[1].dstArrayElement = 0;
        descriptorWrites[1].descriptorCount = 1;
        descriptorWrites[1].descriptorType =
            VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptorWrites[1].pImageInfo = &imageInfo;
        descriptorWrites[1].pBufferInfo = 0;
        descriptorWrites[1].pTexelBufferView = 0;

        vkUpdateDescriptorSets(vulkanDevice, 2, descriptorWrites, 0, 0);
    }

    // Descriptor sets successfully created
    return true;
}
