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
//     Renderer/Shader.cpp : Shader management                                //
////////////////////////////////////////////////////////////////////////////////
#include "Shader.h"


////////////////////////////////////////////////////////////////////////////////
//  Shader default constructor                                                //
////////////////////////////////////////////////////////////////////////////////
Shader::Shader() :
vertexShader(0),
fragmentShader(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  Shader destructor                                                         //
////////////////////////////////////////////////////////////////////////////////
Shader::~Shader()
{
    fragmentShader = 0;
    vertexShader = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Create Shader                                                             //
//  return : True if Shader is successfully created                           //
////////////////////////////////////////////////////////////////////////////////
bool Shader::createShader(VkDevice& vulkanDevice,
    const uint32_t* vertexSource, const size_t vertexSize,
    const uint32_t* fragmentSource, const size_t fragmentSize)
{
    // Check Vulkan device
    if (!vulkanDevice)
    {
        // Invalid Vulkan device
        return false;
    }

    // Check shader sources
    if (!vertexSource || (vertexSize <= 0) ||
        !fragmentSource || (fragmentSize <= 0))
    {
        // Invalid shader sources
        return false;
    }

    // Check current shader
    if (vertexShader || fragmentShader)
    {
        destroyShader(vulkanDevice);
    }

    // Create vertex shader
    VkShaderModuleCreateInfo vertexShaderInfo;
    vertexShaderInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    vertexShaderInfo.pNext = 0;
    vertexShaderInfo.flags = 0;
    vertexShaderInfo.codeSize = vertexSize;
    vertexShaderInfo.pCode = vertexSource;

    if (vkCreateShaderModule(
        vulkanDevice, &vertexShaderInfo, 0, &vertexShader) != VK_SUCCESS)
    {
        // Could not create vertex shader
        return false;
    }
    if (!vertexShader)
    {
        // Invalid vertex shader
        return false;
    }

    // Create fragment shader
    VkShaderModuleCreateInfo fragmentShaderInfo;
    fragmentShaderInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    fragmentShaderInfo.pNext = 0;
    fragmentShaderInfo.flags = 0;
    fragmentShaderInfo.codeSize = fragmentSize;
    fragmentShaderInfo.pCode = fragmentSource;

    if (vkCreateShaderModule(
        vulkanDevice, &fragmentShaderInfo, 0, &fragmentShader) != VK_SUCCESS)
    {
        // Could not create fragment shader
        return false;
    }
    if (!fragmentShader)
    {
        // Invalid fragment shader
        return false;
    }

    // Shader successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy Shader                                                            //
////////////////////////////////////////////////////////////////////////////////
void Shader::destroyShader(VkDevice& vulkanDevice)
{
    // Destroy shader
    if (vkDestroyShaderModule)
    {
        if (fragmentShader)
        {
            vkDestroyShaderModule(vulkanDevice, fragmentShader, 0);
        }
        if (vertexShader)
        {
            vkDestroyShaderModule(vulkanDevice, vertexShader, 0);
        }
    }
    fragmentShader = 0;
    vertexShader = 0;
}
