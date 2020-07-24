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
//     Renderer/Vulkan.cpp : Vulkan management                                //
////////////////////////////////////////////////////////////////////////////////
#include "Vulkan.h"


////////////////////////////////////////////////////////////////////////////////
//  Vulkan instance                                                           //
////////////////////////////////////////////////////////////////////////////////
VkInstance VulkanInstance = 0;

////////////////////////////////////////////////////////////////////////////////
//  vkCreateInstance function                                                 //
////////////////////////////////////////////////////////////////////////////////
PFN_vkCreateInstance vkCreateInstance = 0;

////////////////////////////////////////////////////////////////////////////////
//  vkEnumerateInstanceExtensionProperties function                           //
////////////////////////////////////////////////////////////////////////////////
PFN_vkEnumerateInstanceExtensionProperties
    vkEnumerateInstanceExtensionProperties = 0;


////////////////////////////////////////////////////////////////////////////////
//  Load Vulkan global functions                                              //
//  return : True if Vulkan global functions are successfully loaded          //
////////////////////////////////////////////////////////////////////////////////
bool LoadVulkanGlobalFunctions()
{
    // Load vkCreateInstance
    vkCreateInstance = (PFN_vkCreateInstance)vkGetInstanceProcAddr(
        0, "vkCreateInstance"
    );
    if (!vkCreateInstance)
    {
        // Could not load vkCreateInstance
        return false;
    }

    // Load vkEnumerateInstanceExtensionProperties
    vkEnumerateInstanceExtensionProperties =
        (PFN_vkEnumerateInstanceExtensionProperties)vkGetInstanceProcAddr(
        0, "vkEnumerateInstanceExtensionProperties"
    );
    if (!vkEnumerateInstanceExtensionProperties)
    {
        // Could not load vkEnumerateInstanceExtensionProperties
        return false;
    }

    // Vulkan global functions successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Create Vulkan instance                                                    //
//  return : True if Vulkan instance is successfully created                  //
////////////////////////////////////////////////////////////////////////////////
bool CreateVulkanInstance()
{
    // Enumerate Vulkan extension properties
    uint32_t extcount = 0;
    if (vkEnumerateInstanceExtensionProperties(0, &extcount, 0) != VK_SUCCESS)
    {
        // Could not enumerate Vulkan extension properties
        return false;
    }
    if (extcount == 0)
    {
        // No Vulkan extension properties
        return false;
    }

    // Get Vulkan extensions properties
    std::vector<VkExtensionProperties> extproperties(extcount);
    if (vkEnumerateInstanceExtensionProperties(
        0, &extcount, extproperties.data()) != VK_SUCCESS)
    {
        // Could not get Vulkan extensions properties
        return false;
    }

    // Check Vulkan extensions properties
    bool allExtFound = true;
    for (size_t i = 0; i < VulkanExtensions.size(); ++i)
    {
        bool extFound = false;
        for (size_t j = 0; j < extproperties.size(); ++j)
        {
            if (strcmp(VulkanExtensions[i],
                extproperties[j].extensionName) == 0)
            {
                extFound = true;
                break;
            }
        }
        if (!extFound)
        {
            allExtFound = false;
            break;
        }
    }
    if (!allExtFound)
    {
        // One or more extension is unavailable
        return false;
    }

    // VkApplication
    VkApplicationInfo appInfos;
    appInfos.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfos.pNext = 0;
    appInfos.pApplicationName = "VOS";
    appInfos.applicationVersion = 1;
    appInfos.pEngineName = "VOS";
    appInfos.engineVersion = 1;
    appInfos.apiVersion = VK_API_VERSION;

    // VkInstanceCreateInfo
    VkInstanceCreateInfo createInfos;
    createInfos.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfos.pNext = 0;
    createInfos.flags = 0;
    createInfos.pApplicationInfo = &appInfos;
    createInfos.enabledLayerCount = 0;
    createInfos.ppEnabledLayerNames = 0;
    createInfos.enabledExtensionCount = static_cast<uint32_t>(
        VulkanExtensions.size()
    );
    createInfos.ppEnabledExtensionNames = VulkanExtensions.data();

    // Create Vulkan instance
    VulkanInstance = 0;
    if (vkCreateInstance(&createInfos, 0, &VulkanInstance) != VK_SUCCESS)
    {
        // Could not create Vulkan instance
        return false;
    }

    // Vulkan instance successfully created
    return true;
}
