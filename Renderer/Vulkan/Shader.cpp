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
//     Renderer/Vulkan/Shader.cpp : Shader management                         //
////////////////////////////////////////////////////////////////////////////////
#include "Shader.h"
#include "../Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  Shader default constructor                                                //
////////////////////////////////////////////////////////////////////////////////
Shader::Shader() :
m_shader(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  Shader destructor                                                         //
////////////////////////////////////////////////////////////////////////////////
Shader::~Shader()
{
    m_shader = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Create Shader                                                             //
//  return : True if Shader is successfully created                           //
////////////////////////////////////////////////////////////////////////////////
bool Shader::createShader(Renderer& renderer,
    const uint32_t* source, const size_t size)
{
    // Check current shader
    if (m_shader)
    {
        // Destroy current shader
        destroyShader(renderer);
    }

    // Check shader source
    if (!source || (size <= 0))
    {
        // Invalid shader source
        return false;
    }

    // Create shader
    VkShaderModuleCreateInfo shaderInfo;
    shaderInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    shaderInfo.pNext = 0;
    shaderInfo.flags = 0;
    shaderInfo.codeSize = size;
    shaderInfo.pCode = source;

    if (vkCreateShaderModule(renderer.m_vulkanDevice,
        &shaderInfo, 0, &m_shader) != VK_SUCCESS)
    {
        // Could not create shader
        return false;
    }
    if (!m_shader)
    {
        // Invalid shader
        return false;
    }

    // Shader successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy Shader                                                            //
////////////////////////////////////////////////////////////////////////////////
void Shader::destroyShader(Renderer& renderer)
{
    // Check Vulkan device
    if (!renderer.m_vulkanDevice)
    {
        // Invalid Vulkan device
        return;
    }

    // Destroy shader
    if (m_shader)
    {
        vkDestroyShaderModule(renderer.m_vulkanDevice, m_shader, 0);
    }
    m_shader = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Check if the shader is valid                                              //
//  return : True if the shader is valid                                      //
////////////////////////////////////////////////////////////////////////////////
bool Shader::isValid()
{
    return m_shader;
}
