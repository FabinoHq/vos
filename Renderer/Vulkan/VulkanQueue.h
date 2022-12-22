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
    #include "Vulkan.h"

    #include <cstdint>
    #include <vector>


    ////////////////////////////////////////////////////////////////////////////
    //  VulkanDeviceQueues structure definition                               //
    ////////////////////////////////////////////////////////////////////////////
    struct VulkanDeviceQueues
    {
        uint32_t graphicsQueueFamily;
        uint32_t graphicsQueueIndex;
        uint32_t graphicsQueueMax;

        uint32_t surfaceQueueFamily;
        uint32_t surfaceQueueIndex;
        uint32_t surfaceQueueMax;

        uint32_t transferQueueFamily;
        uint32_t transferQueueIndex;
        uint32_t transferQueueMax;
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
            //  Create graphics queue                                         //
            //  return : True if the graphics queue is successfully created   //
            ////////////////////////////////////////////////////////////////////
            bool createGraphicsQueue(VkDevice& vulkanDevice,
                VulkanDeviceQueues& vulkanQueues);

            ////////////////////////////////////////////////////////////////////
            //  Create surface queue                                          //
            //  return : True if the surface queue is successfully created    //
            ////////////////////////////////////////////////////////////////////
            bool createSurfaceQueue(VkDevice& vulkanDevice,
                VulkanDeviceQueues& vulkanQueues);

            ////////////////////////////////////////////////////////////////////
            //  Create transfer queue                                         //
            //  return : True if the transfer queue is successfully created   //
            ////////////////////////////////////////////////////////////////////
            bool createTransferQueue(VkDevice& vulkanDevice,
                VulkanDeviceQueues& vulkanQueues);


            ////////////////////////////////////////////////////////////////////
            //  Get Vulkan queue families availables for the device           //
            //  return : True if the device supports all queue families       //
            ////////////////////////////////////////////////////////////////////
            static bool getDeviceQueues(VkSurfaceKHR& vulkanSurface,
                VkPhysicalDevice& physicalDevice,
                VulkanDeviceQueues& vulkanQueues);


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
    };


#endif // VOS_RENDERER_VULKAN_VULKANQUEUE_HEADER
