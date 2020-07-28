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
    #define VK_VERSION_MAJOR(version) ((uint32_t)(version) >> 22)
    #define VK_VERSION_MINOR(version) (((uint32_t)(version) >> 12) & 0x3FF)
    #define VK_VERSION_PATCH(version) ((uint32_t)(version) & 0xFFF)
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
    //  VkFormat enum                                                         //
    ////////////////////////////////////////////////////////////////////////////
    enum VkFormat
    {
        VK_FORMAT_UNDEFINED = 0,
        VK_FORMAT_R4G4_UNORM_PACK8 = 1,
        VK_FORMAT_R4G4B4A4_UNORM_PACK16 = 2,
        VK_FORMAT_B4G4R4A4_UNORM_PACK16 = 3,
        VK_FORMAT_R5G6B5_UNORM_PACK16 = 4,
        VK_FORMAT_B5G6R5_UNORM_PACK16 = 5,
        VK_FORMAT_R5G5B5A1_UNORM_PACK16 = 6,
        VK_FORMAT_B5G5R5A1_UNORM_PACK16 = 7,
        VK_FORMAT_A1R5G5B5_UNORM_PACK16 = 8,
        VK_FORMAT_R8_UNORM = 9,
        VK_FORMAT_R8_SNORM = 10,
        VK_FORMAT_R8_USCALED = 11,
        VK_FORMAT_R8_SSCALED = 12,
        VK_FORMAT_R8_UINT = 13,
        VK_FORMAT_R8_SINT = 14,
        VK_FORMAT_R8_SRGB = 15,
        VK_FORMAT_R8G8_UNORM = 16,
        VK_FORMAT_R8G8_SNORM = 17,
        VK_FORMAT_R8G8_USCALED = 18,
        VK_FORMAT_R8G8_SSCALED = 19,
        VK_FORMAT_R8G8_UINT = 20,
        VK_FORMAT_R8G8_SINT = 21,
        VK_FORMAT_R8G8_SRGB = 22,
        VK_FORMAT_R8G8B8_UNORM = 23,
        VK_FORMAT_R8G8B8_SNORM = 24,
        VK_FORMAT_R8G8B8_USCALED = 25,
        VK_FORMAT_R8G8B8_SSCALED = 26,
        VK_FORMAT_R8G8B8_UINT = 27,
        VK_FORMAT_R8G8B8_SINT = 28,
        VK_FORMAT_R8G8B8_SRGB = 29,
        VK_FORMAT_B8G8R8_UNORM = 30,
        VK_FORMAT_B8G8R8_SNORM = 31,
        VK_FORMAT_B8G8R8_USCALED = 32,
        VK_FORMAT_B8G8R8_SSCALED = 33,
        VK_FORMAT_B8G8R8_UINT = 34,
        VK_FORMAT_B8G8R8_SINT = 35,
        VK_FORMAT_B8G8R8_SRGB = 36,
        VK_FORMAT_R8G8B8A8_UNORM = 37,
        VK_FORMAT_R8G8B8A8_SNORM = 38,
        VK_FORMAT_R8G8B8A8_USCALED = 39,
        VK_FORMAT_R8G8B8A8_SSCALED = 40,
        VK_FORMAT_R8G8B8A8_UINT = 41,
        VK_FORMAT_R8G8B8A8_SINT = 42,
        VK_FORMAT_R8G8B8A8_SRGB = 43,
        VK_FORMAT_B8G8R8A8_UNORM = 44,
        VK_FORMAT_B8G8R8A8_SNORM = 45,
        VK_FORMAT_B8G8R8A8_USCALED = 46,
        VK_FORMAT_B8G8R8A8_SSCALED = 47,
        VK_FORMAT_B8G8R8A8_UINT = 48,
        VK_FORMAT_B8G8R8A8_SINT = 49,
        VK_FORMAT_B8G8R8A8_SRGB = 50,
        VK_FORMAT_A8B8G8R8_UNORM_PACK32 = 51,
        VK_FORMAT_A8B8G8R8_SNORM_PACK32 = 52,
        VK_FORMAT_A8B8G8R8_USCALED_PACK32 = 53,
        VK_FORMAT_A8B8G8R8_SSCALED_PACK32 = 54,
        VK_FORMAT_A8B8G8R8_UINT_PACK32 = 55,
        VK_FORMAT_A8B8G8R8_SINT_PACK32 = 56,
        VK_FORMAT_A8B8G8R8_SRGB_PACK32 = 57,
        VK_FORMAT_A2R10G10B10_UNORM_PACK32 = 58,
        VK_FORMAT_A2R10G10B10_SNORM_PACK32 = 59,
        VK_FORMAT_A2R10G10B10_USCALED_PACK32 = 60,
        VK_FORMAT_A2R10G10B10_SSCALED_PACK32 = 61,
        VK_FORMAT_A2R10G10B10_UINT_PACK32 = 62,
        VK_FORMAT_A2R10G10B10_SINT_PACK32 = 63,
        VK_FORMAT_A2B10G10R10_UNORM_PACK32 = 64,
        VK_FORMAT_A2B10G10R10_SNORM_PACK32 = 65,
        VK_FORMAT_A2B10G10R10_USCALED_PACK32 = 66,
        VK_FORMAT_A2B10G10R10_SSCALED_PACK32 = 67,
        VK_FORMAT_A2B10G10R10_UINT_PACK32 = 68,
        VK_FORMAT_A2B10G10R10_SINT_PACK32 = 69,
        VK_FORMAT_R16_UNORM = 70,
        VK_FORMAT_R16_SNORM = 71,
        VK_FORMAT_R16_USCALED = 72,
        VK_FORMAT_R16_SSCALED = 73,
        VK_FORMAT_R16_UINT = 74,
        VK_FORMAT_R16_SINT = 75,
        VK_FORMAT_R16_SFLOAT = 76,
        VK_FORMAT_R16G16_UNORM = 77,
        VK_FORMAT_R16G16_SNORM = 78,
        VK_FORMAT_R16G16_USCALED = 79,
        VK_FORMAT_R16G16_SSCALED = 80,
        VK_FORMAT_R16G16_UINT = 81,
        VK_FORMAT_R16G16_SINT = 82,
        VK_FORMAT_R16G16_SFLOAT = 83,
        VK_FORMAT_R16G16B16_UNORM = 84,
        VK_FORMAT_R16G16B16_SNORM = 85,
        VK_FORMAT_R16G16B16_USCALED = 86,
        VK_FORMAT_R16G16B16_SSCALED = 87,
        VK_FORMAT_R16G16B16_UINT = 88,
        VK_FORMAT_R16G16B16_SINT = 89,
        VK_FORMAT_R16G16B16_SFLOAT = 90,
        VK_FORMAT_R16G16B16A16_UNORM = 91,
        VK_FORMAT_R16G16B16A16_SNORM = 92,
        VK_FORMAT_R16G16B16A16_USCALED = 93,
        VK_FORMAT_R16G16B16A16_SSCALED = 94,
        VK_FORMAT_R16G16B16A16_UINT = 95,
        VK_FORMAT_R16G16B16A16_SINT = 96,
        VK_FORMAT_R16G16B16A16_SFLOAT = 97,
        VK_FORMAT_R32_UINT = 98,
        VK_FORMAT_R32_SINT = 99,
        VK_FORMAT_R32_SFLOAT = 100,
        VK_FORMAT_R32G32_UINT = 101,
        VK_FORMAT_R32G32_SINT = 102,
        VK_FORMAT_R32G32_SFLOAT = 103,
        VK_FORMAT_R32G32B32_UINT = 104,
        VK_FORMAT_R32G32B32_SINT = 105,
        VK_FORMAT_R32G32B32_SFLOAT = 106,
        VK_FORMAT_R32G32B32A32_UINT = 107,
        VK_FORMAT_R32G32B32A32_SINT = 108,
        VK_FORMAT_R32G32B32A32_SFLOAT = 109,
        VK_FORMAT_R64_UINT = 110,
        VK_FORMAT_R64_SINT = 111,
        VK_FORMAT_R64_SFLOAT = 112,
        VK_FORMAT_R64G64_UINT = 113,
        VK_FORMAT_R64G64_SINT = 114,
        VK_FORMAT_R64G64_SFLOAT = 115,
        VK_FORMAT_R64G64B64_UINT = 116,
        VK_FORMAT_R64G64B64_SINT = 117,
        VK_FORMAT_R64G64B64_SFLOAT = 118,
        VK_FORMAT_R64G64B64A64_UINT = 119,
        VK_FORMAT_R64G64B64A64_SINT = 120,
        VK_FORMAT_R64G64B64A64_SFLOAT = 121,
        VK_FORMAT_B10G11R11_UFLOAT_PACK32 = 122,
        VK_FORMAT_E5B9G9R9_UFLOAT_PACK32 = 123,
        VK_FORMAT_D16_UNORM = 124,
        VK_FORMAT_X8_D24_UNORM_PACK32 = 125,
        VK_FORMAT_D32_SFLOAT = 126,
        VK_FORMAT_S8_UINT = 127,
        VK_FORMAT_D16_UNORM_S8_UINT = 128,
        VK_FORMAT_D24_UNORM_S8_UINT = 129,
        VK_FORMAT_D32_SFLOAT_S8_UINT = 130,
        VK_FORMAT_BC1_RGB_UNORM_BLOCK = 131,
        VK_FORMAT_BC1_RGB_SRGB_BLOCK = 132,
        VK_FORMAT_BC1_RGBA_UNORM_BLOCK = 133,
        VK_FORMAT_BC1_RGBA_SRGB_BLOCK = 134,
        VK_FORMAT_BC2_UNORM_BLOCK = 135,
        VK_FORMAT_BC2_SRGB_BLOCK = 136,
        VK_FORMAT_BC3_UNORM_BLOCK = 137,
        VK_FORMAT_BC3_SRGB_BLOCK = 138,
        VK_FORMAT_BC4_UNORM_BLOCK = 139,
        VK_FORMAT_BC4_SNORM_BLOCK = 140,
        VK_FORMAT_BC5_UNORM_BLOCK = 141,
        VK_FORMAT_BC5_SNORM_BLOCK = 142,
        VK_FORMAT_BC6H_UFLOAT_BLOCK = 143,
        VK_FORMAT_BC6H_SFLOAT_BLOCK = 144,
        VK_FORMAT_BC7_UNORM_BLOCK = 145,
        VK_FORMAT_BC7_SRGB_BLOCK = 146,
        VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK = 147,
        VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK = 148,
        VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK = 149,
        VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK = 150,
        VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK = 151,
        VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK = 152,
        VK_FORMAT_EAC_R11_UNORM_BLOCK = 153,
        VK_FORMAT_EAC_R11_SNORM_BLOCK = 154,
        VK_FORMAT_EAC_R11G11_UNORM_BLOCK = 155,
        VK_FORMAT_EAC_R11G11_SNORM_BLOCK = 156,
        VK_FORMAT_ASTC_4x4_UNORM_BLOCK = 157,
        VK_FORMAT_ASTC_4x4_SRGB_BLOCK = 158,
        VK_FORMAT_ASTC_5x4_UNORM_BLOCK = 159,
        VK_FORMAT_ASTC_5x4_SRGB_BLOCK = 160,
        VK_FORMAT_ASTC_5x5_UNORM_BLOCK = 161,
        VK_FORMAT_ASTC_5x5_SRGB_BLOCK = 162,
        VK_FORMAT_ASTC_6x5_UNORM_BLOCK = 163,
        VK_FORMAT_ASTC_6x5_SRGB_BLOCK = 164,
        VK_FORMAT_ASTC_6x6_UNORM_BLOCK = 165,
        VK_FORMAT_ASTC_6x6_SRGB_BLOCK = 166,
        VK_FORMAT_ASTC_8x5_UNORM_BLOCK = 167,
        VK_FORMAT_ASTC_8x5_SRGB_BLOCK = 168,
        VK_FORMAT_ASTC_8x6_UNORM_BLOCK = 169,
        VK_FORMAT_ASTC_8x6_SRGB_BLOCK = 170,
        VK_FORMAT_ASTC_8x8_UNORM_BLOCK = 171,
        VK_FORMAT_ASTC_8x8_SRGB_BLOCK = 172,
        VK_FORMAT_ASTC_10x5_UNORM_BLOCK = 173,
        VK_FORMAT_ASTC_10x5_SRGB_BLOCK = 174,
        VK_FORMAT_ASTC_10x6_UNORM_BLOCK = 175,
        VK_FORMAT_ASTC_10x6_SRGB_BLOCK = 176,
        VK_FORMAT_ASTC_10x8_UNORM_BLOCK = 177,
        VK_FORMAT_ASTC_10x8_SRGB_BLOCK = 178,
        VK_FORMAT_ASTC_10x10_UNORM_BLOCK = 179,
        VK_FORMAT_ASTC_10x10_SRGB_BLOCK = 180,
        VK_FORMAT_ASTC_12x10_UNORM_BLOCK = 181,
        VK_FORMAT_ASTC_12x10_SRGB_BLOCK = 182,
        VK_FORMAT_ASTC_12x12_UNORM_BLOCK = 183,
        VK_FORMAT_ASTC_12x12_SRGB_BLOCK = 184,
        VK_FORMAT_BEGIN_RANGE = 0,
        VK_FORMAT_END_RANGE = 184,
        VK_FORMAT_RANGE_SIZE = 185,
        VK_FORMAT_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkColorSpaceKHR enum                                                  //
    ////////////////////////////////////////////////////////////////////////////
    enum VkColorSpaceKHR
    {
        VK_COLORSPACE_SRGB_NONLINEAR_KHR = 0,
        VK_COLORSPACE_BEGIN_RANGE = 0,
        VK_COLORSPACE_END_RANGE = 0,
        VK_COLORSPACE_RANGE_SIZE = 1,
        VK_COLORSPACE_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkPresentModeKHR enum                                                 //
    ////////////////////////////////////////////////////////////////////////////
    enum VkPresentModeKHR
    {
        VK_PRESENT_MODE_IMMEDIATE_KHR = 0,
        VK_PRESENT_MODE_MAILBOX_KHR = 1,
        VK_PRESENT_MODE_FIFO_KHR = 2,
        VK_PRESENT_MODE_FIFO_RELAXED_KHR = 3,
        VK_PRESENT_MODE_BEGIN_RANGE = 0,
        VK_PRESENT_MODE_END_RANGE = 3,
        VK_PRESENT_MODE_RANGE_SIZE = 4,
        VK_PRESENT_MODE_MAX_ENUM = 0x7FFFFFFF
    };


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

    // VkPipelineStageFlags
    enum VkPipelineStageFlagBits
    {
        VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT = 0x00000001,
        VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT = 0x00000002,
        VK_PIPELINE_STAGE_VERTEX_INPUT_BIT = 0x00000004,
        VK_PIPELINE_STAGE_VERTEX_SHADER_BIT = 0x00000008,
        VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT = 0x00000010,
        VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT = 0x00000020,
        VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT = 0x00000040,
        VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT = 0x00000080,
        VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT = 0x00000100,
        VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT = 0x00000200,
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT = 0x00000400,
        VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT = 0x00000800,
        VK_PIPELINE_STAGE_TRANSFER_BIT = 0x00001000,
        VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT = 0x00002000,
        VK_PIPELINE_STAGE_HOST_BIT = 0x00004000,
        VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT = 0x00008000,
        VK_PIPELINE_STAGE_ALL_COMMANDS_BIT = 0x00010000,
    };
    typedef VkFlags VkPipelineStageFlags;
    typedef VkFlags VkMemoryMapFlags;

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

    // VkImageUsageFlags
    enum VkImageUsageFlagBits
    {
        VK_IMAGE_USAGE_TRANSFER_SRC_BIT = 0x00000001,
        VK_IMAGE_USAGE_TRANSFER_DST_BIT = 0x00000002,
        VK_IMAGE_USAGE_SAMPLED_BIT = 0x00000004,
        VK_IMAGE_USAGE_STORAGE_BIT = 0x00000008,
        VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT = 0x00000010,
        VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT = 0x00000020,
        VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT = 0x00000040,
        VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT = 0x00000080,
    };
    typedef VkFlags VkImageUsageFlags;

    // VkSurfaceTransformFlagsKHR
    enum VkSurfaceTransformFlagBitsKHR
    {
        VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR = 0x00000001,
        VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR = 0x00000002,
        VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR = 0x00000004,
        VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR = 0x00000008,
        VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR = 0x00000010,
        VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR = 0x00000020,
        VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR = 0x00000040,
        VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR = 0x00000080,
        VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR = 0x00000100,
    };
    typedef VkFlags VkSurfaceTransformFlagsKHR;

    // VkCompositeAlphaFlagsKHR
    enum VkCompositeAlphaFlagBitsKHR
    {
        VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR = 0x00000001,
        VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR = 0x00000002,
        VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR = 0x00000004,
        VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR = 0x00000008,
    };
    typedef VkFlags VkCompositeAlphaFlagsKHR;


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
    //  VkViewport data structure                                             //
    ////////////////////////////////////////////////////////////////////////////
    struct VkViewport
    {
        float   x;
        float   y;
        float   width;
        float   height;
        float   minDepth;
        float   maxDepth;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkOffset2D data structure                                             //
    ////////////////////////////////////////////////////////////////////////////
    struct VkOffset2D
    {
        int32_t x;
        int32_t y;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkExtent2D data structure                                             //
    ////////////////////////////////////////////////////////////////////////////
    struct VkExtent2D
    {
        uint32_t    width;
        uint32_t    height;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkRect2D data structure                                               //
    ////////////////////////////////////////////////////////////////////////////
    struct VkRect2D
    {
        VkOffset2D  offset;
        VkExtent2D  extent;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkSurfaceCapabilitiesKHR data structure                               //
    ////////////////////////////////////////////////////////////////////////////
    struct VkSurfaceCapabilitiesKHR
    {
        uint32_t                        minImageCount;
        uint32_t                        maxImageCount;
        VkExtent2D                      currentExtent;
        VkExtent2D                      minImageExtent;
        VkExtent2D                      maxImageExtent;
        uint32_t                        maxImageArrayLayers;
        VkSurfaceTransformFlagsKHR      supportedTransforms;
        VkSurfaceTransformFlagBitsKHR   currentTransform;
        VkCompositeAlphaFlagsKHR        supportedCompositeAlpha;
        VkImageUsageFlags               supportedUsageFlags;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkSurfaceFormatKHR data structure                                     //
    ////////////////////////////////////////////////////////////////////////////
    struct VkSurfaceFormatKHR {
        VkFormat           format;
        VkColorSpaceKHR    colorSpace;
    };


    ////////////////////////////////////////////////////////////////////////////
    //  VkSubmitInfo data structure                                           //
    ////////////////////////////////////////////////////////////////////////////
    struct VkSubmitInfo
    {
        VkStructureType                 sType;
        const void*                     pNext;
        uint32_t                        waitSemaphoreCount;
        const VkSemaphore*              pWaitSemaphores;
        const VkPipelineStageFlags*     pWaitDstStageMask;
        uint32_t                        commandBufferCount;
        const VkCommandBuffer*          pCommandBuffers;
        uint32_t                        signalSemaphoreCount;
        const VkSemaphore*              pSignalSemaphores;
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
    //  vkDestroySurfaceKHR function                                          //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkDestroySurfaceKHR)(
        VkInstance instance, VkSurfaceKHR surface,
        const VkAllocationCallbacks* pAllocator
    );
    extern PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR;

    ////////////////////////////////////////////////////////////////////////////
    //  vkGetPhysicalDeviceSurfaceSupportKHR function                         //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkGetPhysicalDeviceSurfaceSupportKHR)(
        VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex,
        VkSurfaceKHR surface, VkBool32* pSupported
    );
    extern PFN_vkGetPhysicalDeviceSurfaceSupportKHR
        vkGetPhysicalDeviceSurfaceSupportKHR;

    ////////////////////////////////////////////////////////////////////////////
    //  vkGetPhysicalDeviceSurfaceCapabilitiesKHR function                    //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR)(
        VkPhysicalDevice physicalDevice, VkSurfaceKHR surface,
        VkSurfaceCapabilitiesKHR* pSurfaceCapabilities
    );
    extern PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR;

    ////////////////////////////////////////////////////////////////////////////
    //  vkGetPhysicalDeviceSurfaceFormatsKHR function                         //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkGetPhysicalDeviceSurfaceFormatsKHR)(
        VkPhysicalDevice physicalDevice, VkSurfaceKHR surface,
        uint32_t* pSurfaceFormatCount, VkSurfaceFormatKHR* pSurfaceFormats
    );
    extern PFN_vkGetPhysicalDeviceSurfaceFormatsKHR
        vkGetPhysicalDeviceSurfaceFormatsKHR;

    ////////////////////////////////////////////////////////////////////////////
    //  vkGetPhysicalDeviceSurfacePresentModesKHR function                    //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkGetPhysicalDeviceSurfacePresentModesKHR)(
        VkPhysicalDevice physicalDevice, VkSurfaceKHR surface,
        uint32_t* pPresentModeCount, VkPresentModeKHR* pPresentModes
    );
    extern PFN_vkGetPhysicalDeviceSurfacePresentModesKHR
        vkGetPhysicalDeviceSurfacePresentModesKHR;


    ////////////////////////////////////////////////////////////////////////////
    //  vkDestroyDevice function                                              //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkDestroyDevice)(
        VkDevice device, const VkAllocationCallbacks* pAllocator
    );
    extern PFN_vkDestroyDevice vkDestroyDevice;

    ////////////////////////////////////////////////////////////////////////////
    //  vkDeviceWaitIdle function                                             //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkDeviceWaitIdle)(VkDevice device);
    extern PFN_vkDeviceWaitIdle vkDeviceWaitIdle;

    ////////////////////////////////////////////////////////////////////////////
    //  vkGetDeviceQueue function                                             //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkGetDeviceQueue)(
        VkDevice device, uint32_t queueFamilyIndex,
        uint32_t queueIndex, VkQueue* pQueue
    );
    extern PFN_vkGetDeviceQueue vkGetDeviceQueue;

    ////////////////////////////////////////////////////////////////////////////
    //  vkQueueSubmit function                                                //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkQueueSubmit)(
        VkQueue queue, uint32_t submitCount,
        const VkSubmitInfo* pSubmits, VkFence fence
    );
    extern PFN_vkQueueSubmit vkQueueSubmit;

    ////////////////////////////////////////////////////////////////////////////
    //  vkQueueWaitIdle function                                              //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkQueueWaitIdle)(VkQueue queue);
    extern PFN_vkQueueWaitIdle vkQueueWaitIdle;


    ////////////////////////////////////////////////////////////////////////////
    //  Load Vulkan global functions                                          //
    //  return : True if Vulkan global functions are successfully loaded      //
    ////////////////////////////////////////////////////////////////////////////
    bool LoadVulkanGlobalFunctions();

    ////////////////////////////////////////////////////////////////////////////
    //  Load Vulkan instance functions                                        //
    //  return : True if Vulkan instance functions are successfully loaded    //
    ////////////////////////////////////////////////////////////////////////////
    bool LoadVulkanInstanceFunctions(VkInstance& vulkanInstance);

    ////////////////////////////////////////////////////////////////////////////
    //  Load Vulkan device functions                                          //
    //  return : True if Vulkan device functions are successfully loaded      //
    ////////////////////////////////////////////////////////////////////////////
    bool LoadVulkanDeviceFunctions(VkDevice& vulkanDevice);


    ////////////////////////////////////////////////////////////////////////////
    //  Free Vulkan functions                                                 //
    ////////////////////////////////////////////////////////////////////////////
    void FreeVulkanFunctions();


#endif // VOS_RENDERER_VULKAN_HEADER
