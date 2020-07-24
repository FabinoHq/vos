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
//     Lin/SysVulkan.h : Vulkan management for Linux                          //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_LIN_SYSVULKAN_HEADER
#define VOS_LIN_SYSVULKAN_HEADER

    #include <dlfcn.h>
    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  Vulkan API for Linux                                                  //
    ////////////////////////////////////////////////////////////////////////////
    #define VOSVK_ATTR
    #define VOSVK_CALL
    #define VOSVK_PTR

    ////////////////////////////////////////////////////////////////////////////
    // Vulkan library handle for Linux                                        //
    ////////////////////////////////////////////////////////////////////////////
    typedef void* VulkanLibHandle;

    ////////////////////////////////////////////////////////////////////////////
    //  Vulkan instance type                                                  //
    ////////////////////////////////////////////////////////////////////////////
    typedef struct VkInstance_T* VkInstance;


    ////////////////////////////////////////////////////////////////////////////
    //  vkGetInstanceProcAddr function                                        //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkVoidFunction)(void);
    typedef PFN_vkVoidFunction (VOSVK_PTR *PFN_vkGetInstanceProcAddr)(
        VkInstance instance, const char* pName
    );
    extern PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;


    ////////////////////////////////////////////////////////////////////////////
    //  Vulkan library loader for Linux                                       //
    //  return : True if Vulkan library is successfully loaded                //
    ////////////////////////////////////////////////////////////////////////////
    bool LoadVulkanLibrary(VulkanLibHandle& vulkanLibHandle);

    ////////////////////////////////////////////////////////////////////////////
    //  Vulkan library unloader for Linux                                     //
    ////////////////////////////////////////////////////////////////////////////
    void FreeVulkanLibrary(VulkanLibHandle& vulkanLibHandle);


    ////////////////////////////////////////////////////////////////////////////
    //  Load Vulkan GetInstance function                                      //
    //  return : True if Vulkan GetInstance function is successfully loaded   //
    ////////////////////////////////////////////////////////////////////////////
    bool LoadVulkanGetInstance(VulkanLibHandle& vulkanLibHandle);


#endif // VOS_LIN_SYSVULKAN_HEADER
