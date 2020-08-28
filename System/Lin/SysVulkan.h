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
//     System/Lin/SysVulkan.h : Vulkan management for Linux                   //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_SYSTEM_LIN_SYSVULKAN_HEADER
#define VOS_SYSTEM_LIN_SYSVULKAN_HEADER

    #include <dlfcn.h>
    #include <cstdint>
    #include <cstring>
    #include <vector>

    #include "../System.h"
    #include "../SysWindow.h"


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
    //  Vulkan extensions for Linux                                           //
    ////////////////////////////////////////////////////////////////////////////
    extern const uint32_t VulkanExtensionsSize;
    extern const char* VulkanExtensions[];

    ////////////////////////////////////////////////////////////////////////////
    //  Vulkan device extensions for Linux                                    //
    ////////////////////////////////////////////////////////////////////////////
    extern const uint32_t VulkanDeviceExtensionsSize;
    extern const char* VulkanDeviceExtensions[];


    ////////////////////////////////////////////////////////////////////////////
    //  Vulkan types definitions                                              //
    ////////////////////////////////////////////////////////////////////////////
    typedef uint32_t                    VkFlags;
    typedef uint32_t                    VkBool32;
    typedef uint64_t                    VkDeviceSize;
    typedef uint32_t                    VkSampleMask;

    typedef struct VkInstance_T*        VkInstance;
    typedef struct VkPhysicalDevice_T*  VkPhysicalDevice;
    typedef struct VkDevice_T*          VkDevice;
    typedef struct VkQueue_T*           VkQueue;
    typedef struct VkCommandBuffer_T*   VkCommandBuffer;

    typedef VkFlags                     VkXlibSurfaceCreateFlagsKHR;

    #ifdef VOS_64BITS
        typedef struct VkSurfaceKHR_T*              VkSurfaceKHR;
        typedef struct VkSwapchainKHR_T*            VkSwapchainKHR;
        typedef struct VkDeviceMemory_T*            VkDeviceMemory;
        typedef struct VkSemaphore_T*               VkSemaphore;
        typedef struct VkFence_T*                   VkFence;
        typedef struct VkBuffer_T*                  VkBuffer;
        typedef struct VkImage_T*                   VkImage;
        typedef struct VkEvent_T*                   VkEvent;
        typedef struct VkQueryPool_T*               VkQueryPool;
        typedef struct VkBufferView_T*              VkBufferView;
        typedef struct VkImageView_T*               VkImageView;
        typedef struct VkShaderModule_T*            VkShaderModule;
        typedef struct VkPipelineCache_T*           VkPipelineCache;
        typedef struct VkPipelineLayout_T*          VkPipelineLayout;
        typedef struct VkRenderPass_T*              VkRenderPass;
        typedef struct VkPipeline_T*                VkPipeline;
        typedef struct VkSampler_T*                 VkSampler;
        typedef struct VkDescriptorSetLayout_T*     VkDescriptorSetLayout;
        typedef struct VkDescriptorPool_T*          VkDescriptorPool;
        typedef struct VkDescriptorSet_T*           VkDescriptorSet;
        typedef struct VkFramebuffer_T*             VkFramebuffer;
        typedef struct VkCommandPool_T*             VkCommandPool;

        typedef struct VkSamplerYcbcrConversion_T*   VkSamplerYcbcrConversion;
        typedef struct VkDescriptorUpdateTemplate_T* VkDescriptorUpdateTemplate;
    #else
        typedef uint64_t                            VkSurfaceKHR;
        typedef uint64_t                            VkSwapchainKHR;
        typedef uint64_t                            VkDeviceMemory;
        typedef uint64_t                            VkSemaphore;
        typedef uint64_t                            VkFence;
        typedef uint64_t                            VkBuffer;
        typedef uint64_t                            VkImage;
        typedef uint64_t                            VkEvent;
        typedef uint64_t                            VkQueryPool;
        typedef uint64_t                            VkBufferView;
        typedef uint64_t                            VkImageView;
        typedef uint64_t                            VkShaderModule;
        typedef uint64_t                            VkPipelineCache;
        typedef uint64_t                            VkPipelineLayout;
        typedef uint64_t                            VkRenderPass;
        typedef uint64_t                            VkPipeline;
        typedef uint64_t                            VkSampler;
        typedef uint64_t                            VkDescriptorSetLayout;
        typedef uint64_t                            VkDescriptorPool;
        typedef uint64_t                            VkDescriptorSet;
        typedef uint64_t                            VkFramebuffer;
        typedef uint64_t                            VkCommandPool;

        typedef uint64_t                             VkSamplerYcbcrConversion;
        typedef uint64_t                             VkDescriptorUpdateTemplate;
    #endif


    ////////////////////////////////////////////////////////////////////////////
    //  VkResult enum                                                         //
    ////////////////////////////////////////////////////////////////////////////
    enum VkResult
    {
        VK_SUCCESS = 0,
        VK_NOT_READY = 1,
        VK_TIMEOUT = 2,
        VK_EVENT_SET = 3,
        VK_EVENT_RESET = 4,
        VK_INCOMPLETE = 5,
        VK_ERROR_OUT_OF_HOST_MEMORY = -1,
        VK_ERROR_OUT_OF_DEVICE_MEMORY = -2,
        VK_ERROR_INITIALIZATION_FAILED = -3,
        VK_ERROR_DEVICE_LOST = -4,
        VK_ERROR_MEMORY_MAP_FAILED = -5,
        VK_ERROR_LAYER_NOT_PRESENT = -6,
        VK_ERROR_EXTENSION_NOT_PRESENT = -7,
        VK_ERROR_FEATURE_NOT_PRESENT = -8,
        VK_ERROR_INCOMPATIBLE_DRIVER = -9,
        VK_ERROR_TOO_MANY_OBJECTS = -10,
        VK_ERROR_FORMAT_NOT_SUPPORTED = -11,
        VK_ERROR_FRAGMENTED_POOL = -12,
        VK_ERROR_OUT_OF_POOL_MEMORY = -1000069000,
        VK_ERROR_INVALID_EXTERNAL_HANDLE = -1000072003,
        VK_ERROR_SURFACE_LOST_KHR = -1000000000,
        VK_ERROR_NATIVE_WINDOW_IN_USE_KHR = -1000000001,
        VK_SUBOPTIMAL_KHR = 1000001003,
        VK_ERROR_OUT_OF_DATE_KHR = -1000001004,
        VK_ERROR_INCOMPATIBLE_DISPLAY_KHR = -1000003001,
        VK_ERROR_VALIDATION_FAILED_EXT = -1000011001,
        VK_ERROR_INVALID_SHADER_NV = -1000012000,
        VK_ERROR_FRAGMENTATION_EXT = -1000161000,
        VK_ERROR_NOT_PERMITTED_EXT = -1000174001,
        VK_ERROR_OUT_OF_POOL_MEMORY_KHR = -1000069000,
        VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR = -1000072003,
        VK_RESULT_BEGIN_RANGE = -12,
        VK_RESULT_END_RANGE = 5,
        VK_RESULT_RANGE_SIZE = 18,
        VK_RESULT_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkStructureType enum                                                  //
    ////////////////////////////////////////////////////////////////////////////
    enum VkStructureType
    {
        VK_STRUCTURE_TYPE_APPLICATION_INFO = 0,
        VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO = 1,
        VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO = 2,
        VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO = 3,
        VK_STRUCTURE_TYPE_SUBMIT_INFO = 4,
        VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO = 5,
        VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE = 6,
        VK_STRUCTURE_TYPE_BIND_SPARSE_INFO = 7,
        VK_STRUCTURE_TYPE_FENCE_CREATE_INFO = 8,
        VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO = 9,
        VK_STRUCTURE_TYPE_EVENT_CREATE_INFO = 10,
        VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO = 11,
        VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO = 12,
        VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO = 13,
        VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO = 14,
        VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO = 15,
        VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO = 16,
        VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO = 17,
        VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO = 18,
        VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO = 19,
        VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO = 20,
        VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO = 21,
        VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO = 22,
        VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO = 23,
        VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO = 24,
        VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO = 25,
        VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO = 26,
        VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO = 27,
        VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO = 28,
        VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO = 29,
        VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO = 30,
        VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO = 31,
        VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO = 32,
        VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO = 33,
        VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO = 34,
        VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET = 35,
        VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET = 36,
        VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO = 37,
        VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO = 38,
        VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO = 39,
        VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO = 40,
        VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO = 41,
        VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO = 42,
        VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO = 43,
        VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER = 44,
        VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER = 45,
        VK_STRUCTURE_TYPE_MEMORY_BARRIER = 46,
        VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO = 47,
        VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO = 48,
        VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR
            = 1000001000,
        VK_STRUCTURE_TYPE_PRESENT_INFO_KHR
            = 1000001001,
        VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_CAPABILITIES_KHR
            = 1000060007,
        VK_STRUCTURE_TYPE_IMAGE_SWAPCHAIN_CREATE_INFO_KHR
            = 1000060008,
        VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_SWAPCHAIN_INFO_KHR
            = 1000060009,
        VK_STRUCTURE_TYPE_ACQUIRE_NEXT_IMAGE_INFO_KHR
            = 1000060010,
        VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_INFO_KHR
            = 1000060011,
        VK_STRUCTURE_TYPE_DEVICE_GROUP_SWAPCHAIN_CREATE_INFO_KHR
            = 1000060012,
        VK_STRUCTURE_TYPE_DISPLAY_MODE_CREATE_INFO_KHR
            = 1000002000,
        VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR
            = 1000002001,
        VK_STRUCTURE_TYPE_DISPLAY_PRESENT_INFO_KHR
            = 1000003000,
        VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR
            = 1000004000,
        VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR
            = 1000005000,
        VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR
            = 1000006000,
        VK_STRUCTURE_TYPE_MIR_SURFACE_CREATE_INFO_KHR
            = 1000007000,
        VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR
            = 1000008000,
        VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR
            = 1000009000,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_PROPERTIES
            = 1000094000,
        VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO
            = 1000157000,
        VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO
            = 1000157001,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_16BIT_STORAGE_FEATURES
            = 1000083000,
        VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS
            = 1000127000,
        VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO
            = 1000127001,
        VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO
            = 1000060000,
        VK_STRUCTURE_TYPE_DEVICE_GROUP_RENDER_PASS_BEGIN_INFO
            = 1000060003,
        VK_STRUCTURE_TYPE_DEVICE_GROUP_COMMAND_BUFFER_BEGIN_INFO
            = 1000060004,
        VK_STRUCTURE_TYPE_DEVICE_GROUP_SUBMIT_INFO
            = 1000060005,
        VK_STRUCTURE_TYPE_DEVICE_GROUP_BIND_SPARSE_INFO
            = 1000060006,
        VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_DEVICE_GROUP_INFO
            = 1000060013,
        VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_DEVICE_GROUP_INFO
            = 1000060014,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GROUP_PROPERTIES
            = 1000070000,
        VK_STRUCTURE_TYPE_DEVICE_GROUP_DEVICE_CREATE_INFO
            = 1000070001,
        VK_STRUCTURE_TYPE_BUFFER_MEMORY_REQUIREMENTS_INFO_2
            = 1000146000,
        VK_STRUCTURE_TYPE_IMAGE_MEMORY_REQUIREMENTS_INFO_2
            = 1000146001,
        VK_STRUCTURE_TYPE_IMAGE_SPARSE_MEMORY_REQUIREMENTS_INFO_2
            = 1000146002,
        VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2
            = 1000146003,
        VK_STRUCTURE_TYPE_SPARSE_IMAGE_MEMORY_REQUIREMENTS_2
            = 1000146004,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2
            = 1000059000,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2
            = 1000059001,
        VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2
            = 1000059002,
        VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2
            = 1000059003,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2
            = 1000059004,
        VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2
            = 1000059005,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2
            = 1000059006,
        VK_STRUCTURE_TYPE_SPARSE_IMAGE_FORMAT_PROPERTIES_2
            = 1000059007,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SPARSE_IMAGE_FORMAT_INFO_2
            = 1000059008,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_POINT_CLIPPING_PROPERTIES
            = 1000117000,
        VK_STRUCTURE_TYPE_RENDER_PASS_INPUT_ATTACHMENT_ASPECT_CREATE_INFO
            = 1000117001,
        VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO
            = 1000117002,
        VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_DOMAIN_ORIGIN_STATE_CREATE_INFO
            = 1000117003,
        VK_STRUCTURE_TYPE_RENDER_PASS_MULTIVIEW_CREATE_INFO
            = 1000053000,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_FEATURES
            = 1000053001,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PROPERTIES
            = 1000053002,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VARIABLE_POINTER_FEATURES
            = 1000120000,
        VK_STRUCTURE_TYPE_PROTECTED_SUBMIT_INFO
            = 1000145000,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_FEATURES
            = 1000145001,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_PROPERTIES
            = 1000145002,
        VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2
            = 1000145003,
        VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO
            = 1000156000,
        VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_INFO
            = 1000156001,
        VK_STRUCTURE_TYPE_BIND_IMAGE_PLANE_MEMORY_INFO
            = 1000156002,
        VK_STRUCTURE_TYPE_IMAGE_PLANE_MEMORY_REQUIREMENTS_INFO
            = 1000156003,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_YCBCR_CONVERSION_FEATURES
            = 1000156004,
        VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_IMAGE_FORMAT_PROPERTIES
            = 1000156005,
        VK_STRUCTURE_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_CREATE_INFO
            = 1000085000,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO
            = 1000071000,
        VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES
            = 1000071001,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_BUFFER_INFO
            = 1000071002,
        VK_STRUCTURE_TYPE_EXTERNAL_BUFFER_PROPERTIES
            = 1000071003,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES
            = 1000071004,
        VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_BUFFER_CREATE_INFO
            = 1000072000,
        VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO
            = 1000072001,
        VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO
            = 1000072002,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_FENCE_INFO
            = 1000112000,
        VK_STRUCTURE_TYPE_EXTERNAL_FENCE_PROPERTIES
            = 1000112001,
        VK_STRUCTURE_TYPE_EXPORT_FENCE_CREATE_INFO
            = 1000113000,
        VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO
            = 1000077000,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_SEMAPHORE_INFO
            = 1000076000,
        VK_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_PROPERTIES
            = 1000076001,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_3_PROPERTIES
            = 1000168000,
        VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_SUPPORT
            = 1000168001,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DRAW_PARAMETER_FEATURES
            = 1000063000,
        VK_STRUCTURE_TYPE_BEGIN_RANGE = 0,
        VK_STRUCTURE_TYPE_END_RANGE = 48,
        VK_STRUCTURE_TYPE_RANGE_SIZE = 49,
        VK_STRUCTURE_TYPE_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkSystemAllocationScope enum                                          //
    ////////////////////////////////////////////////////////////////////////////
    enum VkSystemAllocationScope
    {
        VK_SYSTEM_ALLOCATION_SCOPE_COMMAND = 0,
        VK_SYSTEM_ALLOCATION_SCOPE_OBJECT = 1,
        VK_SYSTEM_ALLOCATION_SCOPE_CACHE = 2,
        VK_SYSTEM_ALLOCATION_SCOPE_DEVICE = 3,
        VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE = 4,
        VK_SYSTEM_ALLOCATION_SCOPE_BEGIN_RANGE = 0,
        VK_SYSTEM_ALLOCATION_SCOPE_END_RANGE = 4,
        VK_SYSTEM_ALLOCATION_SCOPE_RANGE_SIZE = 5,
        VK_SYSTEM_ALLOCATION_SCOPE_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkInternalAllocationType enum                                         //
    ////////////////////////////////////////////////////////////////////////////
    enum VkInternalAllocationType
    {
        VK_INTERNAL_ALLOCATION_TYPE_EXECUTABLE = 0,
        VK_INTERNAL_ALLOCATION_TYPE_BEGIN_RANGE = 0,
        VK_INTERNAL_ALLOCATION_TYPE_END_RANGE = 0,
        VK_INTERNAL_ALLOCATION_TYPE_RANGE_SIZE = 1,
        VK_INTERNAL_ALLOCATION_TYPE_MAX_ENUM = 0x7FFFFFFF
    };


    ////////////////////////////////////////////////////////////////////////////
    //  vkAllocationFunction definition                                       //
    ////////////////////////////////////////////////////////////////////////////
    typedef void* (VOSVK_PTR *PFN_vkAllocationFunction)(
        void* pUserData, size_t size, size_t alignment,
        VkSystemAllocationScope allocationScope
    );

    ////////////////////////////////////////////////////////////////////////////
    //  vkReallocationFunction definition                                     //
    ////////////////////////////////////////////////////////////////////////////
    typedef void* (VOSVK_PTR *PFN_vkReallocationFunction)(
        void* pUserData, void* pOriginal, size_t size, size_t alignment,
        VkSystemAllocationScope allocationScope
    );

    ////////////////////////////////////////////////////////////////////////////
    //  vkFreeFunction definition                                             //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkFreeFunction)(
        void* pUserData, void* pMemory
    );

    ////////////////////////////////////////////////////////////////////////////
    //  vkInternalAllocationNotification definition                           //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkInternalAllocationNotification)(
        void* pUserData, size_t size,
        VkInternalAllocationType allocationType,
        VkSystemAllocationScope allocationScope
    );

    ////////////////////////////////////////////////////////////////////////////
    //  vkInternalFreeNotification definition                                 //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkInternalFreeNotification)(
        void* pUserData, size_t size,
        VkInternalAllocationType allocationType,
        VkSystemAllocationScope allocationScope
    );


    ////////////////////////////////////////////////////////////////////////////
    //  VkAllocationCallbacks data structure                                  //
    ////////////////////////////////////////////////////////////////////////////
    struct VkAllocationCallbacks
    {
        void*                                   pUserData;
        PFN_vkAllocationFunction                pfnAllocation;
        PFN_vkReallocationFunction              pfnReallocation;
        PFN_vkFreeFunction                      pfnFree;
        PFN_vkInternalAllocationNotification    pfnInternalAllocation;
        PFN_vkInternalFreeNotification          pfnInternalFree;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkXlibSurfaceCreateInfoKHR data structure                             //
    ////////////////////////////////////////////////////////////////////////////
    struct VkXlibSurfaceCreateInfoKHR
    {
        VkStructureType                 sType;
        const void*                     pNext;
        VkXlibSurfaceCreateFlagsKHR     flags;
        Display*                        dpy;
        Window                          window;
    };


    ////////////////////////////////////////////////////////////////////////////
    //  vkGetInstanceProcAddr function                                        //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkVoidFunction)(void);
    typedef PFN_vkVoidFunction (VOSVK_PTR *PFN_vkGetInstanceProcAddr)(
        VkInstance instance, const char* pName
    );
    extern PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCreateXlibSurfaceKHR function                                       //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkCreateXlibSurfaceKHR)(
        VkInstance instance, const VkXlibSurfaceCreateInfoKHR* pCreateInfo,
        const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface
    );
    extern PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR;


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

    ////////////////////////////////////////////////////////////////////////////
    //  Load Vulkan CreateSystemSurface function                              //
    //  return : True if Vulkan CreateSystemSurface function is loaded        //
    ////////////////////////////////////////////////////////////////////////////
    bool LoadVulkanCreateSystemSurface(VkInstance& vulkanInstance);


    ////////////////////////////////////////////////////////////////////////////
    //  Create Vulkan SystemSurface                                           //
    //  return : True if Vulkan SystemSurface is successfully created         //
    ////////////////////////////////////////////////////////////////////////////
    bool CreateVulkanSystemSurface(
        VkInstance& vulkanInstance, SysWindow& sysWindow,
        VkSurfaceKHR& vulkanSurface
    );


#endif // VOS_SYSTEM_LIN_SYSVULKAN_HEADER
