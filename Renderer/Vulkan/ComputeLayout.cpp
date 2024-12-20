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
//     Renderer/Vulkan/ComputeLayout.cpp : Compute layout management          //
////////////////////////////////////////////////////////////////////////////////
#include "ComputeLayout.h"


////////////////////////////////////////////////////////////////////////////////
//  ComputeLayout global instance                                             //
////////////////////////////////////////////////////////////////////////////////
ComputeLayout GComputeLayout = ComputeLayout();


////////////////////////////////////////////////////////////////////////////////
//  ComputeLayout default constructor                                        //
////////////////////////////////////////////////////////////////////////////////
ComputeLayout::ComputeLayout() :
handle(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  ComputeLayout destructor                                                  //
////////////////////////////////////////////////////////////////////////////////
ComputeLayout::~ComputeLayout()
{
    handle = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Create compute pipeline layout                                            //
//  return : True if compute layout is successfully created                   //
////////////////////////////////////////////////////////////////////////////////
bool ComputeLayout::createLayout()
{
    // Create pipeline layout
    if (!createPipelineLayout())
    {
        // Could not create pipeline layout
        GSysMessage << "[0x3051] Could not create pipeline layout\n";
        GSysMessage << "Please update your graphics drivers";
        return false;
    }

    // Compute pipeline successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create pipeline layout                                                    //
//  return : True if pipeline layout is successfully created                  //
////////////////////////////////////////////////////////////////////////////////
bool ComputeLayout::createPipelineLayout()
{
    // Create pipeline layout
    VkPipelineLayoutCreateInfo pipelineInfo;
    pipelineInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineInfo.pNext = 0;
    pipelineInfo.flags = 0;
    pipelineInfo.setLayoutCount = 0;
    pipelineInfo.pSetLayouts = 0;
    pipelineInfo.pushConstantRangeCount = 0;
    pipelineInfo.pPushConstantRanges = 0;

    if (vkCreatePipelineLayout(GVulkanDevice,
        &pipelineInfo, 0, &handle) != VK_SUCCESS)
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
//  Destroy compute pipeline layout                                           //
////////////////////////////////////////////////////////////////////////////////
void ComputeLayout::destroyLayout()
{
    // Check Vulkan device
    if (!GVulkanDevice)
    {
        // Invalid Vulkan device
        return;
    }

    // Destroy pipeline layout
    if (handle)
    {
        vkDestroyPipelineLayout(GVulkanDevice, handle, 0);
    }
    handle = 0;
}
