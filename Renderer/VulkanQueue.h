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
//     Renderer/VulkanQueue.h : Vulkan Queue management                       //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_VULKANQUEUE_HEADER
#define VOS_RENDERER_VULKANQUEUE_HEADER

    #include "Vulkan.h"


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
            //  Create Vulkan queue from index                                //
            //  return : True if the queue is successfully created            //
            ////////////////////////////////////////////////////////////////////
            bool createVulkanQueue(VkDevice& vulkanDevice);


            ////////////////////////////////////////////////////////////////////
            //  Get Vulkan queue families availables for the device           //
            //  return : True if the device supports all queue families       //
            ////////////////////////////////////////////////////////////////////
            static bool getDeviceQueues(VkSurfaceKHR& vulkanSurface,
                VkPhysicalDevice& physicalDevice, VulkanQueue& graphicsQueue,
                VulkanQueue& surfaceQueue, VulkanQueue& transferQueue);


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
            uint32_t    index;      // Queue index
    };


#endif // VOS_RENDERER_VULKANQUEUE_HEADER
