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
//     System/Win/SysVulkan.cpp : Vulkan management for Windows               //
////////////////////////////////////////////////////////////////////////////////
#include "SysVulkan.h"


////////////////////////////////////////////////////////////////////////////////
//  VulkanLib global instance                                                 //
////////////////////////////////////////////////////////////////////////////////
VulkanLibHandle GVulkanLib = 0;

////////////////////////////////////////////////////////////////////////////////
//  VulkanInstance global instance                                            //
////////////////////////////////////////////////////////////////////////////////
VkInstance GVulkanInstance = 0;


////////////////////////////////////////////////////////////////////////////////
//  Vulkan extensions for Windows                                             //
////////////////////////////////////////////////////////////////////////////////
const uint32_t VulkanExtensionsSize = 2;
const char* VulkanExtensions[] =
{
    "VK_KHR_surface", "VK_KHR_win32_surface"
};

////////////////////////////////////////////////////////////////////////////////
//  Vulkan device extensions for Windows                                      //
////////////////////////////////////////////////////////////////////////////////
const uint32_t VulkanDeviceExtensionsSize = 1;
const char* VulkanDeviceExtensions[] =
{
    "VK_KHR_swapchain"
};


////////////////////////////////////////////////////////////////////////////////
//  vkGetInstanceProcAddr function                                            //
////////////////////////////////////////////////////////////////////////////////
PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = 0;

////////////////////////////////////////////////////////////////////////////////
//  vkCreateWin32SurfaceKHR function                                          //
////////////////////////////////////////////////////////////////////////////////
PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR = 0;


////////////////////////////////////////////////////////////////////////////////
//  Vulkan library loader for Windows                                         //
//  return : True if Vulkan library is successfully loaded                    //
////////////////////////////////////////////////////////////////////////////////
bool LoadVulkanLibrary()
{
    // Load Vulkan library
    GVulkanLib = LoadLibrary(L"vulkan-1.dll");
    return GVulkanLib;
}

////////////////////////////////////////////////////////////////////////////////
//  Vulkan library unloader for Windows                                       //
////////////////////////////////////////////////////////////////////////////////
void FreeVulkanLibrary()
{
    if (GVulkanLib)
    {
        // Free Vulkan library
        FreeLibrary(GVulkanLib);
    }
    GVulkanLib = 0;
    vkCreateWin32SurfaceKHR = 0;
    vkGetInstanceProcAddr = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Load Vulkan GetInstance function                                          //
//  return : True if Vulkan GetInstance function is successfully loaded       //
////////////////////////////////////////////////////////////////////////////////
bool LoadVulkanGetInstance()
{
    // Load vkGetInstanceProcAddr
    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)GetProcAddress(
        GVulkanLib, "vkGetInstanceProcAddr"
    );
    return vkGetInstanceProcAddr;
}

////////////////////////////////////////////////////////////////////////////////
//  Load Vulkan CreateSystemSurface function                                  //
//  return : True if Vulkan CreateSystemSurface function is loaded            //
////////////////////////////////////////////////////////////////////////////////
bool LoadVulkanCreateSystemSurface()
{
    // Load vkCreateWin32SurfaceKHR
    vkCreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)
        vkGetInstanceProcAddr(GVulkanInstance, "vkCreateWin32SurfaceKHR"
    );
    return vkCreateWin32SurfaceKHR;
}


////////////////////////////////////////////////////////////////////////////////
//  Create Vulkan SystemSurface                                               //
//  return : True if Vulkan SystemSurface is successfully created             //
////////////////////////////////////////////////////////////////////////////////
bool CreateVulkanSystemSurface(VkSurfaceKHR& vulkanSurface)
{
    VkWin32SurfaceCreateInfoKHR surfaceInfo;
    surfaceInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    surfaceInfo.pNext = 0;
    surfaceInfo.flags = 0;
    surfaceInfo.hinstance = GSysWindow.getInstance();
    surfaceInfo.hwnd = GSysWindow.getHandle();

    if (vkCreateWin32SurfaceKHR(GVulkanInstance,
        &surfaceInfo, 0, &vulkanSurface) != VK_SUCCESS)
    {
        return false;
    }

    return true;
}
