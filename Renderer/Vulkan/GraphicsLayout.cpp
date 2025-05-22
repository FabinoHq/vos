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
//     Renderer/Vulkan/GraphicsLayout.cpp : Graphics layout management        //
////////////////////////////////////////////////////////////////////////////////
#include "GraphicsLayout.h"


////////////////////////////////////////////////////////////////////////////////
//  GraphicsLayout global instance                                            //
////////////////////////////////////////////////////////////////////////////////
GraphicsLayout GGraphicsLayout = GraphicsLayout();


////////////////////////////////////////////////////////////////////////////////
//  GraphicsLayout default constructor                                        //
////////////////////////////////////////////////////////////////////////////////
GraphicsLayout::GraphicsLayout() :
handle(0),
worldlightDescPool(0),
uniformsDescPool(0),
texturesDescPool(0)
{
    for (uint32_t i = 0; i < DESC_SETS_COUNT; ++i)
    {
        descSetLayouts[i] = 0;
    }
    for (uint32_t i = 0; i < (RendererMaxSwapchainFrames*DESC_SETS_COUNT); ++i)
    {
        swapSetLayouts[i] = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  GraphicsLayout destructor                                                 //
////////////////////////////////////////////////////////////////////////////////
GraphicsLayout::~GraphicsLayout()
{
    texturesDescPool = 0;
    uniformsDescPool = 0;
    worldlightDescPool = 0;
    for (uint32_t i = 0; i < (RendererMaxSwapchainFrames*DESC_SETS_COUNT); ++i)
    {
        swapSetLayouts[i] = 0;
    }
    for (uint32_t i = 0; i < DESC_SETS_COUNT; ++i)
    {
        descSetLayouts[i] = 0;
    }
    handle = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Create graphics pipeline layout                                           //
//  return : True if graphics layout is successfully created                  //
////////////////////////////////////////////////////////////////////////////////
bool GraphicsLayout::createLayout()
{
    // Create world light uniforms descriptor pool
    VkDescriptorPoolSize worldlightPoolSize;
    worldlightPoolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    worldlightPoolSize.descriptorCount = RendererMaxSwapchainFrames;

    VkDescriptorPoolCreateInfo worldlightPoolInfo;
    worldlightPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    worldlightPoolInfo.pNext = 0;
    worldlightPoolInfo.flags = 0;
    worldlightPoolInfo.maxSets = RendererMaxSwapchainFrames;
    worldlightPoolInfo.poolSizeCount = 1;
    worldlightPoolInfo.pPoolSizes = &worldlightPoolSize;

    if (vkCreateDescriptorPool(GVulkanDevice, &worldlightPoolInfo,
        SYSVKMEMORY_DESCRIPTORPOOL_ALLOC, &worldlightDescPool) != VK_SUCCESS)
    {
        // Could not create world light uniforms descriptor pool
        GSysMessage << "[0x304C] Could not create worldlight desc pool\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }
    if (!worldlightDescPool)
    {
        // Invalid world light uniforms descriptor pool
        GSysMessage << "[0x304D] Invalid worldlight descriptor pool\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Create matrices uniforms descriptor pool
    VkDescriptorPoolSize uniformsPoolSize;
    uniformsPoolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uniformsPoolSize.descriptorCount =
        (RendererMaxUniformsDesc*RendererMaxSwapchainFrames);

    VkDescriptorPoolCreateInfo uniformsPoolInfo;
    uniformsPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    uniformsPoolInfo.pNext = 0;
    uniformsPoolInfo.flags = 0;
    uniformsPoolInfo.maxSets =
        (RendererMaxUniformsDesc*RendererMaxSwapchainFrames);
    uniformsPoolInfo.poolSizeCount = 1;
    uniformsPoolInfo.pPoolSizes = &uniformsPoolSize;

    if (vkCreateDescriptorPool(GVulkanDevice, &uniformsPoolInfo,
        SYSVKMEMORY_DESCRIPTORPOOL_ALLOC, &uniformsDescPool) != VK_SUCCESS)
    {
        // Could not create matrices uniforms descriptor pool
        GSysMessage << "[0x304C] Could not create uniforms desc pool\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }
    if (!uniformsDescPool)
    {
        // Invalid matrices uniforms descriptor pool
        GSysMessage << "[0x304D] Invalid uniforms descriptor pool\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Create textures descriptor pool
    VkDescriptorPoolSize texturesPoolSize;
    texturesPoolSize.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    texturesPoolSize.descriptorCount =
        (RendererMaxTexturesDesc*RendererMaxSwapchainFrames);

    VkDescriptorPoolCreateInfo texturesPoolInfo;
    texturesPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    texturesPoolInfo.pNext = 0;
    texturesPoolInfo.flags = 0;
    texturesPoolInfo.maxSets =
        (RendererMaxTexturesDesc*RendererMaxSwapchainFrames);
    texturesPoolInfo.poolSizeCount = 1;
    texturesPoolInfo.pPoolSizes = &texturesPoolSize;

    if (vkCreateDescriptorPool(GVulkanDevice, &texturesPoolInfo,
        SYSVKMEMORY_DESCRIPTORPOOL_ALLOC, &texturesDescPool) != VK_SUCCESS)
    {
        // Could not create textures descriptor pool
        GSysMessage << "[0x304E] Could not create textures desc pool\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }
    if (!texturesDescPool)
    {
        // Invalid textures descriptor pool
        GSysMessage << "[0x304F] Invalid textures descriptor pool\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Create descriptor set layouts
    if (!createDescriptorSetLayouts())
    {
        // Could not create descriptor set layouts
        GSysMessage << "[0x3050] Could not create descriptor layouts\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Create pipeline layout
    if (!createPipelineLayout())
    {
        // Could not create pipeline layout
        GSysMessage << "[0x3051] Could not create pipeline layout\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Graphics pipeline successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create descriptor set layouts                                             //
//  return : True if descriptor layout is successfully created                //
////////////////////////////////////////////////////////////////////////////////
bool GraphicsLayout::createDescriptorSetLayouts()
{
    // Descriptor sets bindings
    VkDescriptorSetLayoutBinding descriptorSetBindings[DESC_SETS_COUNT];

    descriptorSetBindings[DESC_WORLDLIGHT].binding = 0;
    descriptorSetBindings[DESC_WORLDLIGHT].descriptorType =
        VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorSetBindings[DESC_WORLDLIGHT].descriptorCount = 1;
    descriptorSetBindings[DESC_WORLDLIGHT].stageFlags =
        (VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT);
    descriptorSetBindings[DESC_WORLDLIGHT].pImmutableSamplers = 0;

    descriptorSetBindings[DESC_MATRICES].binding = 0;
    descriptorSetBindings[DESC_MATRICES].descriptorType =
        VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorSetBindings[DESC_MATRICES].descriptorCount = 1;
    descriptorSetBindings[DESC_MATRICES].stageFlags =
        VK_SHADER_STAGE_VERTEX_BIT;
    descriptorSetBindings[DESC_MATRICES].pImmutableSamplers = 0;

    descriptorSetBindings[DESC_TEXTURE].binding = 0;
    descriptorSetBindings[DESC_TEXTURE].descriptorType =
        VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptorSetBindings[DESC_TEXTURE].descriptorCount = 1;
    descriptorSetBindings[DESC_TEXTURE].stageFlags =
        VK_SHADER_STAGE_FRAGMENT_BIT;
    descriptorSetBindings[DESC_TEXTURE].pImmutableSamplers = 0;

    // Descriptor sets infos
    VkDescriptorSetLayoutCreateInfo descriptorSetInfo[DESC_SETS_COUNT];

    descriptorSetInfo[DESC_WORLDLIGHT].sType =
        VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    descriptorSetInfo[DESC_WORLDLIGHT].pNext = 0;
    descriptorSetInfo[DESC_WORLDLIGHT].flags = 0;
    descriptorSetInfo[DESC_WORLDLIGHT].bindingCount = 1;
    descriptorSetInfo[DESC_WORLDLIGHT].pBindings =
        &descriptorSetBindings[DESC_WORLDLIGHT];

    descriptorSetInfo[DESC_MATRICES].sType =
        VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    descriptorSetInfo[DESC_MATRICES].pNext = 0;
    descriptorSetInfo[DESC_MATRICES].flags = 0;
    descriptorSetInfo[DESC_MATRICES].bindingCount = 1;
    descriptorSetInfo[DESC_MATRICES].pBindings =
        &descriptorSetBindings[DESC_MATRICES];

    descriptorSetInfo[DESC_TEXTURE].sType =
        VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    descriptorSetInfo[DESC_TEXTURE].pNext = 0;
    descriptorSetInfo[DESC_TEXTURE].flags = 0;
    descriptorSetInfo[DESC_TEXTURE].bindingCount = 1;
    descriptorSetInfo[DESC_TEXTURE].pBindings =
        &descriptorSetBindings[DESC_TEXTURE];

    // Create descriptor sets layouts
    for (uint32_t i = 0; i < DESC_SETS_COUNT; ++i)
    {
        // Create descriptor set layout
        if (vkCreateDescriptorSetLayout(GVulkanDevice, &descriptorSetInfo[i],
            SYSVKMEMORY_DESCRIPTORSET_ALLOC, &descSetLayouts[i]) != VK_SUCCESS)
        {
            // Could not create descriptor set layout
            return false;
        }
        if (!descSetLayouts[i])
        {
            // Invalid descriptor set layout
            return false;
        }

        // Copy descriptor set layouts to match swapchain frames count
        for (uint32_t j = 0; j < RendererMaxSwapchainFrames; ++j)
        {
            swapSetLayouts[(i*RendererMaxSwapchainFrames)+j] =
                descSetLayouts[i];
        }
    }

    // Descriptor set layouts successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create pipeline layout                                                    //
//  return : True if pipeline layout is successfully created                  //
////////////////////////////////////////////////////////////////////////////////
bool GraphicsLayout::createPipelineLayout()
{
    // Check descriptor set layouts
    for (uint32_t i = 0; i < DESC_SETS_COUNT; ++i)
    {
        if (!descSetLayouts[i])
        {
            // Invalid descriptor set layout
            return false;
        }
    }

    // Check PushConstantMatrix size
    size_t pushConstantMatrixSize = sizeof(Matrix4x4::mat);
    if (pushConstantMatrixSize != PushConstantMatrixSize)
    {
        // Invalid PushConstantMatrix size
        return false;
    }

    // Check PushConstantData size
    size_t pushConstantDataSize = sizeof(PushConstantData);
    if (pushConstantDataSize != PushConstantDataSize)
    {
        // Invalid PushConstantData size
        return false;
    }

    // Set push constant range
    VkPushConstantRange pushConstantRange[PUSH_CONSTANT_COUNT];

    // Vertex push constant
    pushConstantRange[PUSH_CONSTANT_VERTEX].stageFlags =
        VK_SHADER_STAGE_VERTEX_BIT;
    pushConstantRange[PUSH_CONSTANT_VERTEX].offset = PushConstantMatrixOffset;
    pushConstantRange[PUSH_CONSTANT_VERTEX].size = PushConstantMatrixSize;

    // Fragment push constants
    pushConstantRange[PUSH_CONSTANT_FRAGMENT].stageFlags =
        VK_SHADER_STAGE_FRAGMENT_BIT;
    pushConstantRange[PUSH_CONSTANT_FRAGMENT].offset = PushConstantDataOffset;
    pushConstantRange[PUSH_CONSTANT_FRAGMENT].size = PushConstantDataSize;

    // Create pipeline layout
    VkPipelineLayoutCreateInfo pipelineInfo;
    pipelineInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineInfo.pNext = 0;
    pipelineInfo.flags = 0;
    pipelineInfo.setLayoutCount = DESC_SETS_COUNT;
    pipelineInfo.pSetLayouts = descSetLayouts;
    pipelineInfo.pushConstantRangeCount = PUSH_CONSTANT_COUNT;
    pipelineInfo.pPushConstantRanges = pushConstantRange;

    if (vkCreatePipelineLayout(GVulkanDevice, &pipelineInfo,
        SYSVKMEMORY_PIPELINE_ALLOC, &handle) != VK_SUCCESS)
    {
        // Could not create pipeline layout
        return false;
    }
    if (!handle)
    {
        // Invalid pipeline layout
        return false;
    }

    // Pipeline layout successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy graphics pipeline layout                                          //
////////////////////////////////////////////////////////////////////////////////
void GraphicsLayout::destroyLayout()
{
    // Check Vulkan device
    if (!GVulkanDevice)
    {
        // Invalid Vulkan device
        return;
    }

    // Destroy descriptor set layouts
    for (uint32_t i = 0; i < DESC_SETS_COUNT; ++i)
    {
        if (descSetLayouts[i])
        {
            vkDestroyDescriptorSetLayout(
                GVulkanDevice, descSetLayouts[i],
                SYSVKMEMORY_DESCRIPTORSET_ALLOC
            );
        }
        descSetLayouts[i] = 0;
    }

    // Destroy swapchain layouts
    for (uint32_t i = 0; i < (RendererMaxSwapchainFrames*DESC_SETS_COUNT); ++i)
    {
        swapSetLayouts[i] = 0;
    }

    // Destroy pipeline layout
    if (handle)
    {
        vkDestroyPipelineLayout(
            GVulkanDevice, handle, SYSVKMEMORY_PIPELINE_ALLOC
        );
    }
    handle = 0;

    // Destroy textures descriptor pool
    if (texturesDescPool)
    {
        vkDestroyDescriptorPool(
            GVulkanDevice, texturesDescPool, SYSVKMEMORY_DESCRIPTORPOOL_ALLOC
        );
    }
    texturesDescPool = 0;

    // Destroy uniforms descriptor pool
    if (uniformsDescPool)
    {
        vkDestroyDescriptorPool(
            GVulkanDevice, uniformsDescPool, SYSVKMEMORY_DESCRIPTORPOOL_ALLOC
        );
    }
    uniformsDescPool = 0;

    // Destroy worldlight descriptor pool
    if (worldlightDescPool)
    {
        vkDestroyDescriptorPool(
            GVulkanDevice, worldlightDescPool, SYSVKMEMORY_DESCRIPTORPOOL_ALLOC
        );
    }
    worldlightDescPool = 0;
}
