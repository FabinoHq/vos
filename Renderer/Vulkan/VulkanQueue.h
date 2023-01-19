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
//     Renderer/Vulkan/VulkanQueue.h : Vulkan Queue management                //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_VULKAN_VULKANQUEUE_HEADER
#define VOS_RENDERER_VULKAN_VULKANQUEUE_HEADER

    #include "../../System/System.h"
    #include "../../System/SysMutex.h"
    #include "Vulkan.h"

    #include <cstdint>
    #include <vector>


    ////////////////////////////////////////////////////////////////////////////
    //  Vulkan queue pool enumeration                                         //
    ////////////////////////////////////////////////////////////////////////////
    enum VulkanQueuePool
    {
        VULKAN_QUEUE_RENDERER = 0,
        VULKAN_QUEUE_UNIFORMS = 1,

        VULKAN_QUEUE_TEXTURES = 2,
        VULKAN_QUEUE_MESHES = 3,
        VULKAN_QUEUE_HEIGHTMAPS = 4,

        VULKAN_QUEUE_QUEUESCOUNT = 5
    };


    ////////////////////////////////////////////////////////////////////////////
    //  VulkanDeviceQueues structure definition                               //
    ////////////////////////////////////////////////////////////////////////////
    struct VulkanDeviceQueues
    {
        SysMutex queueMutex[VULKAN_QUEUE_QUEUESCOUNT];
    };


    ////////////////////////////////////////////////////////////////////////////
    //  VulkanQueue class definition                                          //
    ////////////////////////////////////////////////////////////////////////////
    class VulkanQueue
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  VulkanQueue default constructor                               //
            ////////////////////////////////////////////////////////////////////
            VulkanQueue();

            ////////////////////////////////////////////////////////////////////
            //  VulkanQueue destructor                                        //
            ////////////////////////////////////////////////////////////////////
            ~VulkanQueue();


            ////////////////////////////////////////////////////////////////////
            //  Get Vulkan queue                                              //
            //  return : True if the Vulkan queue is successfully retrieved   //
            ////////////////////////////////////////////////////////////////////
            bool getVulkanQueue(VulkanQueuePool queuePool);


            ////////////////////////////////////////////////////////////////////
            //  Get Vulkan queue families availables for the device           //
            //  return : True if the device supports all queue families       //
            ////////////////////////////////////////////////////////////////////
            static bool getDeviceQueues(VkPhysicalDevice& physicalDevice);


        private:
            ////////////////////////////////////////////////////////////////////
            //  VulkanQueue private copy constructor : Not copyable           //
            ////////////////////////////////////////////////////////////////////
            VulkanQueue(const VulkanQueue&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  VulkanQueue private copy operator : Not copyable              //
            ////////////////////////////////////////////////////////////////////
            VulkanQueue& operator=(const VulkanQueue&) = delete;


        public:
            VkQueue     handle;     // Queue handle
            uint32_t    family;     // Queue family
            uint32_t    index;      // Queue index
            int         shared;     // Queue shared index
    };


    ////////////////////////////////////////////////////////////////////////////
    //  VulkanQueues global instance                                          //
    ////////////////////////////////////////////////////////////////////////////
    extern VulkanDeviceQueues GVulkanQueues;


#endif // VOS_RENDERER_VULKAN_VULKANQUEUE_HEADER
