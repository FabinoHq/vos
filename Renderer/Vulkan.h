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
//     Renderer/Vulkan.h : Vulkan management                                  //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_VULKAN_HEADER
#define VOS_RENDERER_VULKAN_HEADER

    #include "../Vulkan.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Vulkan version                                                        //
    ////////////////////////////////////////////////////////////////////////////
    #define VK_MAKE_VERSION(major, minor, patch) \
        (((major) << 22) | ((minor) << 12) | (patch))
    #define VK_API_VERSION VK_MAKE_VERSION(1, 0, 0)

    ////////////////////////////////////////////////////////////////////////////
    //  Vulkan constants definitions                                          //
    ////////////////////////////////////////////////////////////////////////////
    #define VK_LOD_CLAMP_NONE                   1000.0f
    #define VK_REMAINING_MIP_LEVELS             (~0U)
    #define VK_REMAINING_ARRAY_LAYERS           (~0U)
    #define VK_WHOLE_SIZE                       (~0ULL)
    #define VK_ATTACHMENT_UNUSED                (~0U)
    #define VK_TRUE                             1
    #define VK_FALSE                            0
    #define VK_QUEUE_FAMILY_IGNORED             (~0U)
    #define VK_SUBPASS_EXTERNAL                 (~0U)
    #define VK_MAX_PHYSICAL_DEVICE_NAME_SIZE    256
    #define VK_UUID_SIZE                        16
    #define VK_MAX_MEMORY_TYPES                 32
    #define VK_MAX_MEMORY_HEAPS                 16
    #define VK_MAX_EXTENSION_NAME_SIZE          256
    #define VK_MAX_DESCRIPTION_SIZE             256


    ////////////////////////////////////////////////////////////////////////////
    //  Vulkan flags definitions                                              //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkFlags VkInstanceCreateFlags;

    // VkSampleCountFlags
    enum VkSampleCountFlagBits
    {
        VK_SAMPLE_COUNT_1_BIT = 0x00000001,
        VK_SAMPLE_COUNT_2_BIT = 0x00000002,
        VK_SAMPLE_COUNT_4_BIT = 0x00000004,
        VK_SAMPLE_COUNT_8_BIT = 0x00000008,
        VK_SAMPLE_COUNT_16_BIT = 0x00000010,
        VK_SAMPLE_COUNT_32_BIT = 0x00000020,
        VK_SAMPLE_COUNT_64_BIT = 0x00000040,
    };
    typedef VkFlags VkSampleCountFlags;

    // VkQueueFlags
    enum VkQueueFlagBits
    {
        VK_QUEUE_GRAPHICS_BIT = 0x00000001,
        VK_QUEUE_COMPUTE_BIT = 0x00000002,
        VK_QUEUE_TRANSFER_BIT = 0x00000004,
        VK_QUEUE_SPARSE_BINDING_BIT = 0x00000008,
    };
    typedef VkFlags VkQueueFlags;

    // VkMemoryHeapFlags
    enum VkMemoryHeapFlagBits
    {
        VK_MEMORY_HEAP_DEVICE_LOCAL_BIT = 0x00000001,
    };
    typedef VkFlags VkMemoryHeapFlags;
    typedef VkFlags VkDeviceCreateFlags;
    typedef VkFlags VkDeviceQueueCreateFlags;

    // VkMemoryPropertyFlags
    enum VkMemoryPropertyFlagBits
    {
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT = 0x00000001,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT = 0x00000002,
        VK_MEMORY_PROPERTY_HOST_COHERENT_BIT = 0x00000004,
        VK_MEMORY_PROPERTY_HOST_CACHED_BIT = 0x00000008,
        VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT = 0x00000010,
    };
    typedef VkFlags VkMemoryPropertyFlags;


    ////////////////////////////////////////////////////////////////////////////
    //  VkPhysicalDeviceType enum                                             //
    ////////////////////////////////////////////////////////////////////////////
    enum VkPhysicalDeviceType
    {
        VK_PHYSICAL_DEVICE_TYPE_OTHER = 0,
        VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU = 1,
        VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU = 2,
        VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU = 3,
        VK_PHYSICAL_DEVICE_TYPE_CPU = 4,
        VK_PHYSICAL_DEVICE_TYPE_BEGIN_RANGE = 0,
        VK_PHYSICAL_DEVICE_TYPE_END_RANGE = 4,
        VK_PHYSICAL_DEVICE_TYPE_RANGE_SIZE = 5,
        VK_PHYSICAL_DEVICE_TYPE_MAX_ENUM = 0x7FFFFFFF
    };


    ////////////////////////////////////////////////////////////////////////////
    //  VkApplicationInfo data structure                                      //
    ////////////////////////////////////////////////////////////////////////////
    struct VkApplicationInfo
    {
        VkStructureType     sType;
        const void*         pNext;
        const char*         pApplicationName;
        uint32_t            applicationVersion;
        const char*         pEngineName;
        uint32_t            engineVersion;
        uint32_t            apiVersion;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //  VkInstanceCreateInfo data structure                                   //
    ////////////////////////////////////////////////////////////////////////////
    struct VkInstanceCreateInfo
    {
        VkStructureType             sType;
        const void*                 pNext;
        VkInstanceCreateFlags       flags;
        const VkApplicationInfo*    pApplicationInfo;
        uint32_t                    enabledLayerCount;
        const char* const*          ppEnabledLayerNames;
        uint32_t                    enabledExtensionCount;
        const char* const*          ppEnabledExtensionNames;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkExtensionProperties data structure                                  //
    ////////////////////////////////////////////////////////////////////////////
    struct VkExtensionProperties
    {
        char        extensionName[VK_MAX_EXTENSION_NAME_SIZE];
        uint32_t    specVersion;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkPhysicalDeviceLimits data structure                                 //
    ////////////////////////////////////////////////////////////////////////////
    struct VkPhysicalDeviceLimits
    {
        uint32_t                maxImageDimension1D;
        uint32_t                maxImageDimension2D;
        uint32_t                maxImageDimension3D;
        uint32_t                maxImageDimensionCube;
        uint32_t                maxImageArrayLayers;
        uint32_t                maxTexelBufferElements;
        uint32_t                maxUniformBufferRange;
        uint32_t                maxStorageBufferRange;
        uint32_t                maxPushConstantsSize;
        uint32_t                maxMemoryAllocationCount;
        uint32_t                maxSamplerAllocationCount;
        VkDeviceSize            bufferImageGranularity;
        VkDeviceSize            sparseAddressSpaceSize;
        uint32_t                maxBoundDescriptorSets;
        uint32_t                maxPerStageDescriptorSamplers;
        uint32_t                maxPerStageDescriptorUniformBuffers;
        uint32_t                maxPerStageDescriptorStorageBuffers;
        uint32_t                maxPerStageDescriptorSampledImages;
        uint32_t                maxPerStageDescriptorStorageImages;
        uint32_t                maxPerStageDescriptorInputAttachments;
        uint32_t                maxPerStageResources;
        uint32_t                maxDescriptorSetSamplers;
        uint32_t                maxDescriptorSetUniformBuffers;
        uint32_t                maxDescriptorSetUniformBuffersDynamic;
        uint32_t                maxDescriptorSetStorageBuffers;
        uint32_t                maxDescriptorSetStorageBuffersDynamic;
        uint32_t                maxDescriptorSetSampledImages;
        uint32_t                maxDescriptorSetStorageImages;
        uint32_t                maxDescriptorSetInputAttachments;
        uint32_t                maxVertexInputAttributes;
        uint32_t                maxVertexInputBindings;
        uint32_t                maxVertexInputAttributeOffset;
        uint32_t                maxVertexInputBindingStride;
        uint32_t                maxVertexOutputComponents;
        uint32_t                maxTessellationGenerationLevel;
        uint32_t                maxTessellationPatchSize;
        uint32_t                maxTessellationControlPerVertexInputComponents;
        uint32_t                maxTessellationControlPerVertexOutputComponents;
        uint32_t                maxTessellationControlPerPatchOutputComponents;
        uint32_t                maxTessellationControlTotalOutputComponents;
        uint32_t                maxTessellationEvaluationInputComponents;
        uint32_t                maxTessellationEvaluationOutputComponents;
        uint32_t                maxGeometryShaderInvocations;
        uint32_t                maxGeometryInputComponents;
        uint32_t                maxGeometryOutputComponents;
        uint32_t                maxGeometryOutputVertices;
        uint32_t                maxGeometryTotalOutputComponents;
        uint32_t                maxFragmentInputComponents;
        uint32_t                maxFragmentOutputAttachments;
        uint32_t                maxFragmentDualSrcAttachments;
        uint32_t                maxFragmentCombinedOutputResources;
        uint32_t                maxComputeSharedMemorySize;
        uint32_t                maxComputeWorkGroupCount[3];
        uint32_t                maxComputeWorkGroupInvocations;
        uint32_t                maxComputeWorkGroupSize[3];
        uint32_t                subPixelPrecisionBits;
        uint32_t                subTexelPrecisionBits;
        uint32_t                mipmapPrecisionBits;
        uint32_t                maxDrawIndexedIndexValue;
        uint32_t                maxDrawIndirectCount;
        float                   maxSamplerLodBias;
        float                   maxSamplerAnisotropy;
        uint32_t                maxViewports;
        uint32_t                maxViewportDimensions[2];
        float                   viewportBoundsRange[2];
        uint32_t                viewportSubPixelBits;
        size_t                  minMemoryMapAlignment;
        VkDeviceSize            minTexelBufferOffsetAlignment;
        VkDeviceSize            minUniformBufferOffsetAlignment;
        VkDeviceSize            minStorageBufferOffsetAlignment;
        int32_t                 minTexelOffset;
        uint32_t                maxTexelOffset;
        int32_t                 minTexelGatherOffset;
        uint32_t                maxTexelGatherOffset;
        float                   minInterpolationOffset;
        float                   maxInterpolationOffset;
        uint32_t                subPixelInterpolationOffsetBits;
        uint32_t                maxFramebufferWidth;
        uint32_t                maxFramebufferHeight;
        uint32_t                maxFramebufferLayers;
        VkSampleCountFlags      framebufferColorSampleCounts;
        VkSampleCountFlags      framebufferDepthSampleCounts;
        VkSampleCountFlags      framebufferStencilSampleCounts;
        VkSampleCountFlags      framebufferNoAttachmentsSampleCounts;
        uint32_t                maxColorAttachments;
        VkSampleCountFlags      sampledImageColorSampleCounts;
        VkSampleCountFlags      sampledImageIntegerSampleCounts;
        VkSampleCountFlags      sampledImageDepthSampleCounts;
        VkSampleCountFlags      sampledImageStencilSampleCounts;
        VkSampleCountFlags      storageImageSampleCounts;
        uint32_t                maxSampleMaskWords;
        VkBool32                timestampComputeAndGraphics;
        float                   timestampPeriod;
        uint32_t                maxClipDistances;
        uint32_t                maxCullDistances;
        uint32_t                maxCombinedClipAndCullDistances;
        uint32_t                discreteQueuePriorities;
        float                   pointSizeRange[2];
        float                   lineWidthRange[2];
        float                   pointSizeGranularity;
        float                   lineWidthGranularity;
        VkBool32                strictLines;
        VkBool32                standardSampleLocations;
        VkDeviceSize            optimalBufferCopyOffsetAlignment;
        VkDeviceSize            optimalBufferCopyRowPitchAlignment;
        VkDeviceSize            nonCoherentAtomSize;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkPhysicalDeviceSparseProperties data structure                       //
    ////////////////////////////////////////////////////////////////////////////
    struct VkPhysicalDeviceSparseProperties
    {
        VkBool32    residencyStandard2DBlockShape;
        VkBool32    residencyStandard2DMultisampleBlockShape;
        VkBool32    residencyStandard3DBlockShape;
        VkBool32    residencyAlignedMipSize;
        VkBool32    residencyNonResidentStrict;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkPhysicalDeviceProperties data structure                             //
    ////////////////////////////////////////////////////////////////////////////
    struct VkPhysicalDeviceProperties
    {
        uint32_t                apiVersion;
        uint32_t                driverVersion;
        uint32_t                vendorID;
        uint32_t                deviceID;
        VkPhysicalDeviceType    deviceType;
        char                    deviceName[VK_MAX_PHYSICAL_DEVICE_NAME_SIZE];
        uint8_t                 pipelineCacheUUID[VK_UUID_SIZE];
        VkPhysicalDeviceLimits  limits;
        VkPhysicalDeviceSparseProperties    sparseProperties;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkPhysicalDeviceFeatures data structure                               //
    ////////////////////////////////////////////////////////////////////////////
    struct VkPhysicalDeviceFeatures
    {
        VkBool32    robustBufferAccess;
        VkBool32    fullDrawIndexUint32;
        VkBool32    imageCubeArray;
        VkBool32    independentBlend;
        VkBool32    geometryShader;
        VkBool32    tessellationShader;
        VkBool32    sampleRateShading;
        VkBool32    dualSrcBlend;
        VkBool32    logicOp;
        VkBool32    multiDrawIndirect;
        VkBool32    drawIndirectFirstInstance;
        VkBool32    depthClamp;
        VkBool32    depthBiasClamp;
        VkBool32    fillModeNonSolid;
        VkBool32    depthBounds;
        VkBool32    wideLines;
        VkBool32    largePoints;
        VkBool32    alphaToOne;
        VkBool32    multiViewport;
        VkBool32    samplerAnisotropy;
        VkBool32    textureCompressionETC2;
        VkBool32    textureCompressionASTC_LDR;
        VkBool32    textureCompressionBC;
        VkBool32    occlusionQueryPrecise;
        VkBool32    pipelineStatisticsQuery;
        VkBool32    vertexPipelineStoresAndAtomics;
        VkBool32    fragmentStoresAndAtomics;
        VkBool32    shaderTessellationAndGeometryPointSize;
        VkBool32    shaderImageGatherExtended;
        VkBool32    shaderStorageImageExtendedFormats;
        VkBool32    shaderStorageImageMultisample;
        VkBool32    shaderStorageImageReadWithoutFormat;
        VkBool32    shaderStorageImageWriteWithoutFormat;
        VkBool32    shaderUniformBufferArrayDynamicIndexing;
        VkBool32    shaderSampledImageArrayDynamicIndexing;
        VkBool32    shaderStorageBufferArrayDynamicIndexing;
        VkBool32    shaderStorageImageArrayDynamicIndexing;
        VkBool32    shaderClipDistance;
        VkBool32    shaderCullDistance;
        VkBool32    shaderFloat64;
        VkBool32    shaderInt64;
        VkBool32    shaderInt16;
        VkBool32    shaderResourceResidency;
        VkBool32    shaderResourceMinLod;
        VkBool32    sparseBinding;
        VkBool32    sparseResidencyBuffer;
        VkBool32    sparseResidencyImage2D;
        VkBool32    sparseResidencyImage3D;
        VkBool32    sparseResidency2Samples;
        VkBool32    sparseResidency4Samples;
        VkBool32    sparseResidency8Samples;
        VkBool32    sparseResidency16Samples;
        VkBool32    sparseResidencyAliased;
        VkBool32    variableMultisampleRate;
        VkBool32    inheritedQueries;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkExtent3D data structure                                             //
    ////////////////////////////////////////////////////////////////////////////
    struct VkExtent3D
    {
        uint32_t    width;
        uint32_t    height;
        uint32_t    depth;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkQueueFamilyProperties data structure                                //
    ////////////////////////////////////////////////////////////////////////////
    struct VkQueueFamilyProperties
    {
        VkQueueFlags    queueFlags;
        uint32_t        queueCount;
        uint32_t        timestampValidBits;
        VkExtent3D      minImageTransferGranularity;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkDeviceQueueCreateInfo data structure                                //
    ////////////////////////////////////////////////////////////////////////////
    struct VkDeviceQueueCreateInfo
    {
        VkStructureType             sType;
        const void*                 pNext;
        VkDeviceQueueCreateFlags    flags;
        uint32_t                    queueFamilyIndex;
        uint32_t                    queueCount;
        const float*                pQueuePriorities;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkDeviceCreateInfo data structure                                     //
    ////////////////////////////////////////////////////////////////////////////
    struct VkDeviceCreateInfo
    {
        VkStructureType                     sType;
        const void*                         pNext;
        VkDeviceCreateFlags                 flags;
        uint32_t                            queueCreateInfoCount;
        const VkDeviceQueueCreateInfo*      pQueueCreateInfos;
        uint32_t                            enabledLayerCount;
        const char* const*                  ppEnabledLayerNames;
        uint32_t                            enabledExtensionCount;
        const char* const*                  ppEnabledExtensionNames;
        const VkPhysicalDeviceFeatures*     pEnabledFeatures;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkMemoryType data structure                                           //
    ////////////////////////////////////////////////////////////////////////////
    struct VkMemoryType
    {
        VkMemoryPropertyFlags   propertyFlags;
        uint32_t                heapIndex;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkMemoryHeap data structure                                           //
    ////////////////////////////////////////////////////////////////////////////
    struct VkMemoryHeap
    {
        VkDeviceSize        size;
        VkMemoryHeapFlags   flags;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkPhysicalDeviceMemoryProperties data structure                       //
    ////////////////////////////////////////////////////////////////////////////
    struct VkPhysicalDeviceMemoryProperties
    {
        uint32_t        memoryTypeCount;
        VkMemoryType    memoryTypes[VK_MAX_MEMORY_TYPES];
        uint32_t        memoryHeapCount;
        VkMemoryHeap    memoryHeaps[VK_MAX_MEMORY_HEAPS];
    };


    ////////////////////////////////////////////////////////////////////////////
    //  vkCreateInstance function                                             //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkCreateInstance)(
        const VkInstanceCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator, VkInstance* pInstance
    );
    extern PFN_vkCreateInstance vkCreateInstance;

    ////////////////////////////////////////////////////////////////////////////
    //  vkEnumerateInstanceExtensionProperties function                       //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkEnumerateInstanceExtensionProperties)(
        const char* pLayerName, uint32_t* pPropertyCount,
        VkExtensionProperties* pProperties
    );
    extern PFN_vkEnumerateInstanceExtensionProperties
        vkEnumerateInstanceExtensionProperties;


    ////////////////////////////////////////////////////////////////////////////
    //  vkDestroyInstance function                                            //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkDestroyInstance)(
        VkInstance instance, const VkAllocationCallbacks* pAllocator
    );
    extern PFN_vkDestroyInstance vkDestroyInstance;

    ////////////////////////////////////////////////////////////////////////////
    //  vkEnumeratePhysicalDevices function                                   //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkEnumeratePhysicalDevices)(
        VkInstance instance, uint32_t* pPhysicalDeviceCount,
        VkPhysicalDevice* pPhysicalDevices
    );
    extern PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices;

    ////////////////////////////////////////////////////////////////////////////
    //  vkGetPhysicalDeviceProperties function                                //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkGetPhysicalDeviceProperties)(
        VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties
    );
    extern PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties;

    ////////////////////////////////////////////////////////////////////////////
    //  vkGetPhysicalDeviceFeatures function                                  //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkGetPhysicalDeviceFeatures)(
        VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* pFeatures
    );
    extern PFN_vkGetPhysicalDeviceFeatures vkGetPhysicalDeviceFeatures;

    ////////////////////////////////////////////////////////////////////////////
    //  vkGetPhysicalDeviceQueueFamilyProperties function                     //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkGetPhysicalDeviceQueueFamilyProperties)(
        VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount,
        VkQueueFamilyProperties* pQueueFamilyProperties
    );
    extern PFN_vkGetPhysicalDeviceQueueFamilyProperties
        vkGetPhysicalDeviceQueueFamilyProperties;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCreateDevice function                                               //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkCreateDevice)(
        VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator, VkDevice* pDevice
    );
    extern PFN_vkCreateDevice vkCreateDevice;

    ////////////////////////////////////////////////////////////////////////////
    //  vkGetDeviceProcAddr function                                          //
    ////////////////////////////////////////////////////////////////////////////
    typedef PFN_vkVoidFunction (VOSVK_PTR *PFN_vkGetDeviceProcAddr)(
        VkDevice device, const char* pName
    );
    extern PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr;

    ////////////////////////////////////////////////////////////////////////////
    //  vkEnumerateDeviceExtensionProperties function                         //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkEnumerateDeviceExtensionProperties)(
        VkPhysicalDevice physicalDevice, const char* pLayerName,
        uint32_t* pPropertyCount, VkExtensionProperties* pProperties
    );
    extern PFN_vkEnumerateDeviceExtensionProperties
        vkEnumerateDeviceExtensionProperties;

    ////////////////////////////////////////////////////////////////////////////
    //  vkGetPhysicalDeviceMemoryProperties function                          //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkGetPhysicalDeviceMemoryProperties)(
        VkPhysicalDevice physicalDevice,
        VkPhysicalDeviceMemoryProperties* pMemoryProperties
    );
    extern PFN_vkGetPhysicalDeviceMemoryProperties
        vkGetPhysicalDeviceMemoryProperties;


    ////////////////////////////////////////////////////////////////////////////
    //  Load Vulkan global functions                                          //
    //  return : True if Vulkan global functions are successfully loaded      //
    ////////////////////////////////////////////////////////////////////////////
    bool LoadVulkanGlobalFunctions();

    ////////////////////////////////////////////////////////////////////////////
    //  Create Vulkan instance                                                //
    //  return : True if Vulkan instance is successfully created              //
    ////////////////////////////////////////////////////////////////////////////
    bool CreateVulkanInstance(VkInstance& vulkanInstance);

    ////////////////////////////////////////////////////////////////////////////
    //  Load Vulkan instance functions                                        //
    //  return : True if Vulkan instance functions are successfully loaded    //
    ////////////////////////////////////////////////////////////////////////////
    bool LoadVulkanInstanceFunctions(VkInstance& vulkanInstance);

    ////////////////////////////////////////////////////////////////////////////
    //  Destroy Vulkan instance                                               //
    ////////////////////////////////////////////////////////////////////////////
    void DestroyVulkanInstance(VkInstance& vulkanInstance);

    ////////////////////////////////////////////////////////////////////////////
    //  Free Vulkan functions                                                 //
    ////////////////////////////////////////////////////////////////////////////
    void FreeVulkanFunctions();


#endif // VOS_RENDERER_VULKAN_HEADER
