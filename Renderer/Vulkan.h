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

    #include "../System/SysVulkan.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Vulkan version                                                        //
    ////////////////////////////////////////////////////////////////////////////
    #define VK_MAKE_VERSION(major, minor, patch) \
        (((major) << 22) | ((minor) << 12) | (patch))
    #define VK_VERSION_MAJOR(version) ((uint32_t)(version) >> 22)
    #define VK_VERSION_MINOR(version) (((uint32_t)(version) >> 12) & 0x3FF)
    #define VK_VERSION_PATCH(version) ((uint32_t)(version) & 0xFFF)
    #define VK_API_VERSION VK_MAKE_VERSION(1, 1, 0)

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
    //  VkImageType enum                                                      //
    ////////////////////////////////////////////////////////////////////////////
    enum VkImageType
    {
        VK_IMAGE_TYPE_1D = 0,
        VK_IMAGE_TYPE_2D = 1,
        VK_IMAGE_TYPE_3D = 2,
        VK_IMAGE_TYPE_BEGIN_RANGE = 0,
        VK_IMAGE_TYPE_END_RANGE = 2,
        VK_IMAGE_TYPE_RANGE_SIZE = 3,
        VK_IMAGE_TYPE_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkImageTiling enum                                                    //
    ////////////////////////////////////////////////////////////////////////////
    enum VkImageTiling
    {
        VK_IMAGE_TILING_OPTIMAL = 0,
        VK_IMAGE_TILING_LINEAR = 1,
        VK_IMAGE_TILING_BEGIN_RANGE = 0,
        VK_IMAGE_TILING_END_RANGE = 1,
        VK_IMAGE_TILING_RANGE_SIZE = 2,
        VK_IMAGE_TILING_MAX_ENUM = 0x7FFFFFFF
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
    //  VkQueryType enum                                                      //
    ////////////////////////////////////////////////////////////////////////////
    enum VkQueryType
    {
        VK_QUERY_TYPE_OCCLUSION = 0,
        VK_QUERY_TYPE_PIPELINE_STATISTICS = 1,
        VK_QUERY_TYPE_TIMESTAMP = 2,
        VK_QUERY_TYPE_BEGIN_RANGE = 0,
        VK_QUERY_TYPE_END_RANGE = 2,
        VK_QUERY_TYPE_RANGE_SIZE = 3,
        VK_QUERY_TYPE_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkSharingMode enum                                                    //
    ////////////////////////////////////////////////////////////////////////////
    enum VkSharingMode
    {
        VK_SHARING_MODE_EXCLUSIVE = 0,
        VK_SHARING_MODE_CONCURRENT = 1,
        VK_SHARING_MODE_BEGIN_RANGE = 0,
        VK_SHARING_MODE_END_RANGE = 1,
        VK_SHARING_MODE_RANGE_SIZE = 2,
        VK_SHARING_MODE_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkImageLayout enum                                                    //
    ////////////////////////////////////////////////////////////////////////////
    enum VkImageLayout
    {
        VK_IMAGE_LAYOUT_UNDEFINED = 0,
        VK_IMAGE_LAYOUT_GENERAL = 1,
        VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL = 2,
        VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL = 3,
        VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL = 4,
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL = 5,
        VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL = 6,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL = 7,
        VK_IMAGE_LAYOUT_PREINITIALIZED = 8,
        VK_IMAGE_LAYOUT_PRESENT_SRC_KHR = 1000001002,
        VK_IMAGE_LAYOUT_BEGIN_RANGE = 0,
        VK_IMAGE_LAYOUT_END_RANGE = 8,
        VK_IMAGE_LAYOUT_RANGE_SIZE = 9,
        VK_IMAGE_LAYOUT_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkImageViewType enum                                                  //
    ////////////////////////////////////////////////////////////////////////////
    enum VkImageViewType
    {
        VK_IMAGE_VIEW_TYPE_1D = 0,
        VK_IMAGE_VIEW_TYPE_2D = 1,
        VK_IMAGE_VIEW_TYPE_3D = 2,
        VK_IMAGE_VIEW_TYPE_CUBE = 3,
        VK_IMAGE_VIEW_TYPE_1D_ARRAY = 4,
        VK_IMAGE_VIEW_TYPE_2D_ARRAY = 5,
        VK_IMAGE_VIEW_TYPE_CUBE_ARRAY = 6,
        VK_IMAGE_VIEW_TYPE_BEGIN_RANGE = 0,
        VK_IMAGE_VIEW_TYPE_END_RANGE = 6,
        VK_IMAGE_VIEW_TYPE_RANGE_SIZE = 7,
        VK_IMAGE_VIEW_TYPE_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkComponentSwizzle enum                                               //
    ////////////////////////////////////////////////////////////////////////////
    enum VkComponentSwizzle
    {
        VK_COMPONENT_SWIZZLE_IDENTITY = 0,
        VK_COMPONENT_SWIZZLE_ZERO = 1,
        VK_COMPONENT_SWIZZLE_ONE = 2,
        VK_COMPONENT_SWIZZLE_R = 3,
        VK_COMPONENT_SWIZZLE_G = 4,
        VK_COMPONENT_SWIZZLE_B = 5,
        VK_COMPONENT_SWIZZLE_A = 6,
        VK_COMPONENT_SWIZZLE_BEGIN_RANGE = 0,
        VK_COMPONENT_SWIZZLE_END_RANGE = 6,
        VK_COMPONENT_SWIZZLE_RANGE_SIZE = 7,
        VK_COMPONENT_SWIZZLE_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkVertexInputRate enum                                                //
    ////////////////////////////////////////////////////////////////////////////
    enum VkVertexInputRate
    {
        VK_VERTEX_INPUT_RATE_VERTEX = 0,
        VK_VERTEX_INPUT_RATE_INSTANCE = 1,
        VK_VERTEX_INPUT_RATE_BEGIN_RANGE = 0,
        VK_VERTEX_INPUT_RATE_END_RANGE = 1,
        VK_VERTEX_INPUT_RATE_RANGE_SIZE = 2,
        VK_VERTEX_INPUT_RATE_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkPrimitiveTopology enum                                              //
    ////////////////////////////////////////////////////////////////////////////
    enum VkPrimitiveTopology
    {
        VK_PRIMITIVE_TOPOLOGY_POINT_LIST = 0,
        VK_PRIMITIVE_TOPOLOGY_LINE_LIST = 1,
        VK_PRIMITIVE_TOPOLOGY_LINE_STRIP = 2,
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST = 3,
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP = 4,
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN = 5,
        VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY = 6,
        VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY = 7,
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY = 8,
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY = 9,
        VK_PRIMITIVE_TOPOLOGY_PATCH_LIST = 10,
        VK_PRIMITIVE_TOPOLOGY_BEGIN_RANGE = 0,
        VK_PRIMITIVE_TOPOLOGY_END_RANGE = 10,
        VK_PRIMITIVE_TOPOLOGY_RANGE_SIZE = 11,
        VK_PRIMITIVE_TOPOLOGY_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkPolygonMode enum                                                    //
    ////////////////////////////////////////////////////////////////////////////
    enum VkPolygonMode
    {
        VK_POLYGON_MODE_FILL = 0,
        VK_POLYGON_MODE_LINE = 1,
        VK_POLYGON_MODE_POINT = 2,
        VK_POLYGON_MODE_BEGIN_RANGE = 0,
        VK_POLYGON_MODE_END_RANGE = 2,
        VK_POLYGON_MODE_RANGE_SIZE = 3,
        VK_POLYGON_MODE_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkFrontFace enum                                                      //
    ////////////////////////////////////////////////////////////////////////////
    enum VkFrontFace
    {
        VK_FRONT_FACE_COUNTER_CLOCKWISE = 0,
        VK_FRONT_FACE_CLOCKWISE = 1,
        VK_FRONT_FACE_BEGIN_RANGE = 0,
        VK_FRONT_FACE_END_RANGE = 1,
        VK_FRONT_FACE_RANGE_SIZE = 2,
        VK_FRONT_FACE_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkCompareOp enum                                                      //
    ////////////////////////////////////////////////////////////////////////////
    enum VkCompareOp
    {
        VK_COMPARE_OP_NEVER = 0,
        VK_COMPARE_OP_LESS = 1,
        VK_COMPARE_OP_EQUAL = 2,
        VK_COMPARE_OP_LESS_OR_EQUAL = 3,
        VK_COMPARE_OP_GREATER = 4,
        VK_COMPARE_OP_NOT_EQUAL = 5,
        VK_COMPARE_OP_GREATER_OR_EQUAL = 6,
        VK_COMPARE_OP_ALWAYS = 7,
        VK_COMPARE_OP_BEGIN_RANGE = 0,
        VK_COMPARE_OP_END_RANGE = 7,
        VK_COMPARE_OP_RANGE_SIZE = 8,
        VK_COMPARE_OP_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkStencilOp enum                                                      //
    ////////////////////////////////////////////////////////////////////////////
    enum VkStencilOp
    {
        VK_STENCIL_OP_KEEP = 0,
        VK_STENCIL_OP_ZERO = 1,
        VK_STENCIL_OP_REPLACE = 2,
        VK_STENCIL_OP_INCREMENT_AND_CLAMP = 3,
        VK_STENCIL_OP_DECREMENT_AND_CLAMP = 4,
        VK_STENCIL_OP_INVERT = 5,
        VK_STENCIL_OP_INCREMENT_AND_WRAP = 6,
        VK_STENCIL_OP_DECREMENT_AND_WRAP = 7,
        VK_STENCIL_OP_BEGIN_RANGE = 0,
        VK_STENCIL_OP_END_RANGE = 7,
        VK_STENCIL_OP_RANGE_SIZE = 8,
        VK_STENCIL_OP_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkLogicOp enum                                                        //
    ////////////////////////////////////////////////////////////////////////////
    enum VkLogicOp
    {
        VK_LOGIC_OP_CLEAR = 0,
        VK_LOGIC_OP_AND = 1,
        VK_LOGIC_OP_AND_REVERSE = 2,
        VK_LOGIC_OP_COPY = 3,
        VK_LOGIC_OP_AND_INVERTED = 4,
        VK_LOGIC_OP_NO_OP = 5,
        VK_LOGIC_OP_XOR = 6,
        VK_LOGIC_OP_OR = 7,
        VK_LOGIC_OP_NOR = 8,
        VK_LOGIC_OP_EQUIVALENT = 9,
        VK_LOGIC_OP_INVERT = 10,
        VK_LOGIC_OP_OR_REVERSE = 11,
        VK_LOGIC_OP_COPY_INVERTED = 12,
        VK_LOGIC_OP_OR_INVERTED = 13,
        VK_LOGIC_OP_NAND = 14,
        VK_LOGIC_OP_SET = 15,
        VK_LOGIC_OP_BEGIN_RANGE = 0,
        VK_LOGIC_OP_END_RANGE = 15,
        VK_LOGIC_OP_RANGE_SIZE = 16,
        VK_LOGIC_OP_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkBlendFactor enum                                                    //
    ////////////////////////////////////////////////////////////////////////////
    enum VkBlendFactor
    {
        VK_BLEND_FACTOR_ZERO = 0,
        VK_BLEND_FACTOR_ONE = 1,
        VK_BLEND_FACTOR_SRC_COLOR = 2,
        VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR = 3,
        VK_BLEND_FACTOR_DST_COLOR = 4,
        VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR = 5,
        VK_BLEND_FACTOR_SRC_ALPHA = 6,
        VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA = 7,
        VK_BLEND_FACTOR_DST_ALPHA = 8,
        VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA = 9,
        VK_BLEND_FACTOR_CONSTANT_COLOR = 10,
        VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR = 11,
        VK_BLEND_FACTOR_CONSTANT_ALPHA = 12,
        VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA = 13,
        VK_BLEND_FACTOR_SRC_ALPHA_SATURATE = 14,
        VK_BLEND_FACTOR_SRC1_COLOR = 15,
        VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR = 16,
        VK_BLEND_FACTOR_SRC1_ALPHA = 17,
        VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA = 18,
        VK_BLEND_FACTOR_BEGIN_RANGE = 0,
        VK_BLEND_FACTOR_END_RANGE = 18,
        VK_BLEND_FACTOR_RANGE_SIZE = 19,
        VK_BLEND_FACTOR_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkBlendOp enum                                                        //
    ////////////////////////////////////////////////////////////////////////////
    enum VkBlendOp
    {
        VK_BLEND_OP_ADD = 0,
        VK_BLEND_OP_SUBTRACT = 1,
        VK_BLEND_OP_REVERSE_SUBTRACT = 2,
        VK_BLEND_OP_MIN = 3,
        VK_BLEND_OP_MAX = 4,
        VK_BLEND_OP_BEGIN_RANGE = 0,
        VK_BLEND_OP_END_RANGE = 4,
        VK_BLEND_OP_RANGE_SIZE = 5,
        VK_BLEND_OP_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkDynamicState enum                                                   //
    ////////////////////////////////////////////////////////////////////////////
    enum VkDynamicState
    {
        VK_DYNAMIC_STATE_VIEWPORT = 0,
        VK_DYNAMIC_STATE_SCISSOR = 1,
        VK_DYNAMIC_STATE_LINE_WIDTH = 2,
        VK_DYNAMIC_STATE_DEPTH_BIAS = 3,
        VK_DYNAMIC_STATE_BLEND_CONSTANTS = 4,
        VK_DYNAMIC_STATE_DEPTH_BOUNDS = 5,
        VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK = 6,
        VK_DYNAMIC_STATE_STENCIL_WRITE_MASK = 7,
        VK_DYNAMIC_STATE_STENCIL_REFERENCE = 8,
        VK_DYNAMIC_STATE_BEGIN_RANGE = 0,
        VK_DYNAMIC_STATE_END_RANGE = 8,
        VK_DYNAMIC_STATE_RANGE_SIZE = 9,
        VK_DYNAMIC_STATE_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkFilter enum                                                         //
    ////////////////////////////////////////////////////////////////////////////
    enum VkFilter
    {
        VK_FILTER_NEAREST = 0,
        VK_FILTER_LINEAR = 1,
        VK_FILTER_BEGIN_RANGE = 0,
        VK_FILTER_END_RANGE = 1,
        VK_FILTER_RANGE_SIZE = 2,
        VK_FILTER_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkSamplerMipmapMode enum                                              //
    ////////////////////////////////////////////////////////////////////////////
    enum VkSamplerMipmapMode
    {
        VK_SAMPLER_MIPMAP_MODE_NEAREST = 0,
        VK_SAMPLER_MIPMAP_MODE_LINEAR = 1,
        VK_SAMPLER_MIPMAP_MODE_BEGIN_RANGE = 0,
        VK_SAMPLER_MIPMAP_MODE_END_RANGE = 1,
        VK_SAMPLER_MIPMAP_MODE_RANGE_SIZE = 2,
        VK_SAMPLER_MIPMAP_MODE_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkSamplerAddressMode enum                                             //
    ////////////////////////////////////////////////////////////////////////////
    enum VkSamplerAddressMode
    {
        VK_SAMPLER_ADDRESS_MODE_REPEAT = 0,
        VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT = 1,
        VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE = 2,
        VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER = 3,
        VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE = 4,
        VK_SAMPLER_ADDRESS_MODE_BEGIN_RANGE = 0,
        VK_SAMPLER_ADDRESS_MODE_END_RANGE = 4,
        VK_SAMPLER_ADDRESS_MODE_RANGE_SIZE = 5,
        VK_SAMPLER_ADDRESS_MODE_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkBorderColor enum                                                    //
    ////////////////////////////////////////////////////////////////////////////
    enum VkBorderColor
    {
        VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK = 0,
        VK_BORDER_COLOR_INT_TRANSPARENT_BLACK = 1,
        VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK = 2,
        VK_BORDER_COLOR_INT_OPAQUE_BLACK = 3,
        VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE = 4,
        VK_BORDER_COLOR_INT_OPAQUE_WHITE = 5,
        VK_BORDER_COLOR_BEGIN_RANGE = 0,
        VK_BORDER_COLOR_END_RANGE = 5,
        VK_BORDER_COLOR_RANGE_SIZE = 6,
        VK_BORDER_COLOR_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkDescriptorType enum                                                 //
    ////////////////////////////////////////////////////////////////////////////
    enum VkDescriptorType
    {
        VK_DESCRIPTOR_TYPE_SAMPLER = 0,
        VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER = 1,
        VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE = 2,
        VK_DESCRIPTOR_TYPE_STORAGE_IMAGE = 3,
        VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER = 4,
        VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER = 5,
        VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER = 6,
        VK_DESCRIPTOR_TYPE_STORAGE_BUFFER = 7,
        VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC = 8,
        VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC = 9,
        VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT = 10,
        VK_DESCRIPTOR_TYPE_BEGIN_RANGE = 0,
        VK_DESCRIPTOR_TYPE_END_RANGE = 10,
        VK_DESCRIPTOR_TYPE_RANGE_SIZE = 11,
        VK_DESCRIPTOR_TYPE_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkAttachmentLoadOp enum                                               //
    ////////////////////////////////////////////////////////////////////////////
    enum VkAttachmentLoadOp
    {
        VK_ATTACHMENT_LOAD_OP_LOAD = 0,
        VK_ATTACHMENT_LOAD_OP_CLEAR = 1,
        VK_ATTACHMENT_LOAD_OP_DONT_CARE = 2,
        VK_ATTACHMENT_LOAD_OP_BEGIN_RANGE = 0,
        VK_ATTACHMENT_LOAD_OP_END_RANGE = 2,
        VK_ATTACHMENT_LOAD_OP_RANGE_SIZE = 3,
        VK_ATTACHMENT_LOAD_OP_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkAttachmentStoreOp enum                                              //
    ////////////////////////////////////////////////////////////////////////////
    enum VkAttachmentStoreOp
    {
        VK_ATTACHMENT_STORE_OP_STORE = 0,
        VK_ATTACHMENT_STORE_OP_DONT_CARE = 1,
        VK_ATTACHMENT_STORE_OP_BEGIN_RANGE = 0,
        VK_ATTACHMENT_STORE_OP_END_RANGE = 1,
        VK_ATTACHMENT_STORE_OP_RANGE_SIZE = 2,
        VK_ATTACHMENT_STORE_OP_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkPipelineBindPoint enum                                              //
    ////////////////////////////////////////////////////////////////////////////
    enum VkPipelineBindPoint
    {
        VK_PIPELINE_BIND_POINT_GRAPHICS = 0,
        VK_PIPELINE_BIND_POINT_COMPUTE = 1,
        VK_PIPELINE_BIND_POINT_BEGIN_RANGE = 0,
        VK_PIPELINE_BIND_POINT_END_RANGE = 1,
        VK_PIPELINE_BIND_POINT_RANGE_SIZE = 2,
        VK_PIPELINE_BIND_POINT_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkCommandBufferLevel enum                                             //
    ////////////////////////////////////////////////////////////////////////////
    enum VkCommandBufferLevel
    {
        VK_COMMAND_BUFFER_LEVEL_PRIMARY = 0,
        VK_COMMAND_BUFFER_LEVEL_SECONDARY = 1,
        VK_COMMAND_BUFFER_LEVEL_BEGIN_RANGE = 0,
        VK_COMMAND_BUFFER_LEVEL_END_RANGE = 1,
        VK_COMMAND_BUFFER_LEVEL_RANGE_SIZE = 2,
        VK_COMMAND_BUFFER_LEVEL_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkIndexType enum                                                      //
    ////////////////////////////////////////////////////////////////////////////
    enum VkIndexType
    {
        VK_INDEX_TYPE_UINT16 = 0,
        VK_INDEX_TYPE_UINT32 = 1,
        VK_INDEX_TYPE_BEGIN_RANGE = 0,
        VK_INDEX_TYPE_END_RANGE = 1,
        VK_INDEX_TYPE_RANGE_SIZE = 2,
        VK_INDEX_TYPE_MAX_ENUM = 0x7FFFFFFF
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkSubpassContents enum                                                //
    ////////////////////////////////////////////////////////////////////////////
    enum VkSubpassContents
    {
        VK_SUBPASS_CONTENTS_INLINE = 0,
        VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS = 1,
        VK_SUBPASS_CONTENTS_BEGIN_RANGE = 0,
        VK_SUBPASS_CONTENTS_END_RANGE = 1,
        VK_SUBPASS_CONTENTS_RANGE_SIZE = 2,
        VK_SUBPASS_CONTENTS_MAX_ENUM = 0x7FFFFFFF
    };


    ////////////////////////////////////////////////////////////////////////////
    //  Vulkan flags definitions                                              //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkFlags VkInstanceCreateFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkFormatFeatureFlags                                                  //
    ////////////////////////////////////////////////////////////////////////////
    enum VkFormatFeatureFlagBits
    {
        VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT = 0x00000001,
        VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT = 0x00000002,
        VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT = 0x00000004,
        VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT = 0x00000008,
        VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT = 0x00000010,
        VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT = 0x00000020,
        VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT = 0x00000040,
        VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT = 0x00000080,
        VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT = 0x00000100,
        VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT = 0x00000200,
        VK_FORMAT_FEATURE_BLIT_SRC_BIT = 0x00000400,
        VK_FORMAT_FEATURE_BLIT_DST_BIT = 0x00000800,
        VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT = 0x00001000
    };
    typedef VkFlags VkFormatFeatureFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkSampleCountFlags                                                    //
    ////////////////////////////////////////////////////////////////////////////
    enum VkSampleCountFlagBits
    {
        VK_SAMPLE_COUNT_1_BIT = 0x00000001,
        VK_SAMPLE_COUNT_2_BIT = 0x00000002,
        VK_SAMPLE_COUNT_4_BIT = 0x00000004,
        VK_SAMPLE_COUNT_8_BIT = 0x00000008,
        VK_SAMPLE_COUNT_16_BIT = 0x00000010,
        VK_SAMPLE_COUNT_32_BIT = 0x00000020,
        VK_SAMPLE_COUNT_64_BIT = 0x00000040
    };
    typedef VkFlags VkSampleCountFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkQueueFlags                                                          //
    ////////////////////////////////////////////////////////////////////////////
    enum VkQueueFlagBits
    {
        VK_QUEUE_GRAPHICS_BIT = 0x00000001,
        VK_QUEUE_COMPUTE_BIT = 0x00000002,
        VK_QUEUE_TRANSFER_BIT = 0x00000004,
        VK_QUEUE_SPARSE_BINDING_BIT = 0x00000008
    };
    typedef VkFlags VkQueueFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkMemoryHeapFlags                                                     //
    ////////////////////////////////////////////////////////////////////////////
    enum VkMemoryHeapFlagBits
    {
        VK_MEMORY_HEAP_DEVICE_LOCAL_BIT = 0x00000001
    };
    typedef VkFlags VkMemoryHeapFlags;
    typedef VkFlags VkDeviceCreateFlags;
    typedef VkFlags VkDeviceQueueCreateFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkPipelineStageFlags                                                  //
    ////////////////////////////////////////////////////////////////////////////
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
        VK_PIPELINE_STAGE_ALL_COMMANDS_BIT = 0x00010000
    };
    typedef VkFlags VkPipelineStageFlags;
    typedef VkFlags VkMemoryMapFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkMemoryPropertyFlags                                                 //
    ////////////////////////////////////////////////////////////////////////////
    enum VkMemoryPropertyFlagBits
    {
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT = 0x00000001,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT = 0x00000002,
        VK_MEMORY_PROPERTY_HOST_COHERENT_BIT = 0x00000004,
        VK_MEMORY_PROPERTY_HOST_CACHED_BIT = 0x00000008,
        VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT = 0x00000010
    };
    typedef VkFlags VkMemoryPropertyFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkImageUsageFlags                                                     //
    ////////////////////////////////////////////////////////////////////////////
    enum VkImageUsageFlagBits
    {
        VK_IMAGE_USAGE_TRANSFER_SRC_BIT = 0x00000001,
        VK_IMAGE_USAGE_TRANSFER_DST_BIT = 0x00000002,
        VK_IMAGE_USAGE_SAMPLED_BIT = 0x00000004,
        VK_IMAGE_USAGE_STORAGE_BIT = 0x00000008,
        VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT = 0x00000010,
        VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT = 0x00000020,
        VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT = 0x00000040,
        VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT = 0x00000080
    };
    typedef VkFlags VkImageUsageFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkImageCreateFlags                                                    //
    ////////////////////////////////////////////////////////////////////////////
    enum VkImageCreateFlagBits
    {
        VK_IMAGE_CREATE_SPARSE_BINDING_BIT = 0x00000001,
        VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT = 0x00000002,
        VK_IMAGE_CREATE_SPARSE_ALIASED_BIT = 0x00000004,
        VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT = 0x00000008,
        VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT = 0x00000010
    };
    typedef VkFlags VkImageCreateFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkImageAspectFlags                                                    //
    ////////////////////////////////////////////////////////////////////////////
    enum VkImageAspectFlagBits
    {
        VK_IMAGE_ASPECT_COLOR_BIT = 0x00000001,
        VK_IMAGE_ASPECT_DEPTH_BIT = 0x00000002,
        VK_IMAGE_ASPECT_STENCIL_BIT = 0x00000004,
        VK_IMAGE_ASPECT_METADATA_BIT = 0x00000008
    };
    typedef VkFlags VkImageAspectFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkSparseImageFormatFlags                                              //
    ////////////////////////////////////////////////////////////////////////////
    enum VkSparseImageFormatFlagBits
    {
        VK_SPARSE_IMAGE_FORMAT_SINGLE_MIPTAIL_BIT = 0x00000001,
        VK_SPARSE_IMAGE_FORMAT_ALIGNED_MIP_SIZE_BIT = 0x00000002,
        VK_SPARSE_IMAGE_FORMAT_NONSTANDARD_BLOCK_SIZE_BIT = 0x00000004
    };
    typedef VkFlags VkSparseImageFormatFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkSparseMemoryBindFlags                                               //
    ////////////////////////////////////////////////////////////////////////////
    enum VkSparseMemoryBindFlagBits
    {
        VK_SPARSE_MEMORY_BIND_METADATA_BIT = 0x00000001
    };
    typedef VkFlags VkSparseMemoryBindFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkSurfaceTransformFlagsKHR                                            //
    ////////////////////////////////////////////////////////////////////////////
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
        VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR = 0x00000100
    };
    typedef VkFlags VkSurfaceTransformFlagsKHR;

    ////////////////////////////////////////////////////////////////////////////
    //  VkCompositeAlphaFlagsKHR                                              //
    ////////////////////////////////////////////////////////////////////////////
    enum VkCompositeAlphaFlagBitsKHR
    {
        VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR = 0x00000001,
        VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR = 0x00000002,
        VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR = 0x00000004,
        VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR = 0x00000008
    };
    typedef VkFlags VkCompositeAlphaFlagsKHR;

    ////////////////////////////////////////////////////////////////////////////
    //  VkFenceCreateFlags                                                    //
    ////////////////////////////////////////////////////////////////////////////
    enum VkFenceCreateFlagBits
    {
        VK_FENCE_CREATE_SIGNALED_BIT = 0x00000001
    };
    typedef VkFlags VkFenceCreateFlags;
    typedef VkFlags VkSemaphoreCreateFlags;
    typedef VkFlags VkEventCreateFlags;
    typedef VkFlags VkQueryPoolCreateFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkQueryPipelineStatisticFlags                                         //
    ////////////////////////////////////////////////////////////////////////////
    enum VkQueryPipelineStatisticFlagBits {
    VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_VERTICES_BIT =
        0x00000001,
    VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_PRIMITIVES_BIT =
        0x00000002,
    VK_QUERY_PIPELINE_STATISTIC_VERTEX_SHADER_INVOCATIONS_BIT =
        0x00000004,
    VK_QUERY_PIPELINE_STATISTIC_GEOMETRY_SHADER_INVOCATIONS_BIT =
        0x00000008,
    VK_QUERY_PIPELINE_STATISTIC_GEOMETRY_SHADER_PRIMITIVES_BIT =
        0x00000010,
    VK_QUERY_PIPELINE_STATISTIC_CLIPPING_INVOCATIONS_BIT =
        0x00000020,
    VK_QUERY_PIPELINE_STATISTIC_CLIPPING_PRIMITIVES_BIT =
        0x00000040,
    VK_QUERY_PIPELINE_STATISTIC_FRAGMENT_SHADER_INVOCATIONS_BIT =
        0x00000080,
    VK_QUERY_PIPELINE_STATISTIC_TESSELLATION_CONTROL_SHADER_PATCHES_BIT =
        0x00000100,
    VK_QUERY_PIPELINE_STATISTIC_TESSELLATION_EVALUATION_SHADER_INVOCATIONS_BIT =
        0x00000200,
    VK_QUERY_PIPELINE_STATISTIC_COMPUTE_SHADER_INVOCATIONS_BIT =
        0x00000400
    };
    typedef VkFlags VkQueryPipelineStatisticFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkQueryResultFlags                                                    //
    ////////////////////////////////////////////////////////////////////////////
    enum VkQueryResultFlagBits {
        VK_QUERY_RESULT_64_BIT = 0x00000001,
        VK_QUERY_RESULT_WAIT_BIT = 0x00000002,
        VK_QUERY_RESULT_WITH_AVAILABILITY_BIT = 0x00000004,
        VK_QUERY_RESULT_PARTIAL_BIT = 0x00000008
    };
    typedef VkFlags VkQueryResultFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkBufferCreateFlags                                                   //
    ////////////////////////////////////////////////////////////////////////////
    enum VkBufferCreateFlagBits {
        VK_BUFFER_CREATE_SPARSE_BINDING_BIT = 0x00000001,
        VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT = 0x00000002,
        VK_BUFFER_CREATE_SPARSE_ALIASED_BIT = 0x00000004
    };
    typedef VkFlags VkBufferCreateFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkBufferUsageFlags                                                    //
    ////////////////////////////////////////////////////////////////////////////
    enum VkBufferUsageFlagBits
    {
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT = 0x00000001,
        VK_BUFFER_USAGE_TRANSFER_DST_BIT = 0x00000002,
        VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT = 0x00000004,
        VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT = 0x00000008,
        VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT = 0x00000010,
        VK_BUFFER_USAGE_STORAGE_BUFFER_BIT = 0x00000020,
        VK_BUFFER_USAGE_INDEX_BUFFER_BIT = 0x00000040,
        VK_BUFFER_USAGE_VERTEX_BUFFER_BIT = 0x00000080,
        VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT = 0x00000100
    };
    typedef VkFlags VkBufferUsageFlags;
    typedef VkFlags VkBufferViewCreateFlags;
    typedef VkFlags VkImageViewCreateFlags;
    typedef VkFlags VkShaderModuleCreateFlags;
    typedef VkFlags VkPipelineCacheCreateFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkPipelineCreateFlags                                                 //
    ////////////////////////////////////////////////////////////////////////////
    enum VkPipelineCreateFlagBits
    {
        VK_PIPELINE_CREATE_DISABLE_OPTIMIZATION_BIT = 0x00000001,
        VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT = 0x00000002,
        VK_PIPELINE_CREATE_DERIVATIVE_BIT = 0x00000004
    };
    typedef VkFlags VkPipelineCreateFlags;
    typedef VkFlags VkPipelineShaderStageCreateFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkShaderStageFlags                                                    //
    ////////////////////////////////////////////////////////////////////////////
    enum VkShaderStageFlagBits
    {
        VK_SHADER_STAGE_VERTEX_BIT = 0x00000001,
        VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT = 0x00000002,
        VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT = 0x00000004,
        VK_SHADER_STAGE_GEOMETRY_BIT = 0x00000008,
        VK_SHADER_STAGE_FRAGMENT_BIT = 0x00000010,
        VK_SHADER_STAGE_COMPUTE_BIT = 0x00000020,
        VK_SHADER_STAGE_ALL_GRAPHICS = 0x1F,
        VK_SHADER_STAGE_ALL = 0x7FFFFFFF
    };
    typedef VkFlags VkPipelineVertexInputStateCreateFlags;
    typedef VkFlags VkPipelineInputAssemblyStateCreateFlags;
    typedef VkFlags VkPipelineTessellationStateCreateFlags;
    typedef VkFlags VkPipelineViewportStateCreateFlags;
    typedef VkFlags VkPipelineRasterizationStateCreateFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkCullModeFlags                                                       //
    ////////////////////////////////////////////////////////////////////////////
    enum VkCullModeFlagBits
    {
        VK_CULL_MODE_NONE = 0,
        VK_CULL_MODE_FRONT_BIT = 0x00000001,
        VK_CULL_MODE_BACK_BIT = 0x00000002,
        VK_CULL_MODE_FRONT_AND_BACK = 0x3
    };
    typedef VkFlags VkCullModeFlags;
    typedef VkFlags VkPipelineMultisampleStateCreateFlags;
    typedef VkFlags VkPipelineDepthStencilStateCreateFlags;
    typedef VkFlags VkPipelineColorBlendStateCreateFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkColorComponentFlags                                                 //
    ////////////////////////////////////////////////////////////////////////////
    enum VkColorComponentFlagBits
    {
        VK_COLOR_COMPONENT_R_BIT = 0x00000001,
        VK_COLOR_COMPONENT_G_BIT = 0x00000002,
        VK_COLOR_COMPONENT_B_BIT = 0x00000004,
        VK_COLOR_COMPONENT_A_BIT = 0x00000008
    };
    typedef VkFlags VkColorComponentFlags;
    typedef VkFlags VkPipelineDynamicStateCreateFlags;
    typedef VkFlags VkPipelineLayoutCreateFlags;
    typedef VkFlags VkShaderStageFlags;
    typedef VkFlags VkSamplerCreateFlags;
    typedef VkFlags VkDescriptorSetLayoutCreateFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkDescriptorPoolCreateFlags                                           //
    ////////////////////////////////////////////////////////////////////////////
    enum VkDescriptorPoolCreateFlagBits
    {
        VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT = 0x00000001
    };
    typedef VkFlags VkDescriptorPoolCreateFlags;
    typedef VkFlags VkDescriptorPoolResetFlags;
    typedef VkFlags VkFramebufferCreateFlags;
    typedef VkFlags VkRenderPassCreateFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkAttachmentDescriptionFlags                                          //
    ////////////////////////////////////////////////////////////////////////////
    enum VkAttachmentDescriptionFlagBits
    {
        VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT = 0x00000001
    };
    typedef VkFlags VkAttachmentDescriptionFlags;
    typedef VkFlags VkSubpassDescriptionFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkAccessFlags                                                         //
    ////////////////////////////////////////////////////////////////////////////
    enum VkAccessFlagBits
    {
        VK_ACCESS_INDIRECT_COMMAND_READ_BIT = 0x00000001,
        VK_ACCESS_INDEX_READ_BIT = 0x00000002,
        VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT = 0x00000004,
        VK_ACCESS_UNIFORM_READ_BIT = 0x00000008,
        VK_ACCESS_INPUT_ATTACHMENT_READ_BIT = 0x00000010,
        VK_ACCESS_SHADER_READ_BIT = 0x00000020,
        VK_ACCESS_SHADER_WRITE_BIT = 0x00000040,
        VK_ACCESS_COLOR_ATTACHMENT_READ_BIT = 0x00000080,
        VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT = 0x00000100,
        VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT = 0x00000200,
        VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT = 0x00000400,
        VK_ACCESS_TRANSFER_READ_BIT = 0x00000800,
        VK_ACCESS_TRANSFER_WRITE_BIT = 0x00001000,
        VK_ACCESS_HOST_READ_BIT = 0x00002000,
        VK_ACCESS_HOST_WRITE_BIT = 0x00004000,
        VK_ACCESS_MEMORY_READ_BIT = 0x00008000,
        VK_ACCESS_MEMORY_WRITE_BIT = 0x00010000
    };
    typedef VkFlags VkAccessFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkDependencyFlags                                                     //
    ////////////////////////////////////////////////////////////////////////////
    enum VkDependencyFlagBits
    {
        VK_DEPENDENCY_BY_REGION_BIT = 0x00000001
    };
    typedef VkFlags VkDependencyFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkCommandPoolCreateFlags                                              //
    ////////////////////////////////////////////////////////////////////////////
    enum VkCommandPoolCreateFlagBits
    {
        VK_COMMAND_POOL_CREATE_TRANSIENT_BIT = 0x00000001,
        VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT = 0x00000002
    };
    typedef VkFlags VkCommandPoolCreateFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkCommandPoolResetFlags                                               //
    ////////////////////////////////////////////////////////////////////////////
    enum VkCommandPoolResetFlagBits
    {
        VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT = 0x00000001
    };
    typedef VkFlags VkCommandPoolResetFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkCommandBufferUsageFlags                                             //
    ////////////////////////////////////////////////////////////////////////////
    enum VkCommandBufferUsageFlagBits
    {
        VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT = 0x00000001,
        VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT = 0x00000002,
        VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT = 0x00000004
    };
    typedef VkFlags VkCommandBufferUsageFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkQueryControlFlags                                                   //
    ////////////////////////////////////////////////////////////////////////////
    enum VkQueryControlFlagBits
    {
        VK_QUERY_CONTROL_PRECISE_BIT = 0x00000001
    };
    typedef VkFlags VkQueryControlFlags;

    ////////////////////////////////////////////////////////////////////////////
    //  VkCommandBufferResetFlags                                             //
    ////////////////////////////////////////////////////////////////////////////
    enum VkCommandBufferResetFlagBits
    {
        VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT = 0x00000001
    };
    typedef VkFlags VkCommandBufferResetFlags;


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
    //  VkLayerProperties data structure                                      //
    ////////////////////////////////////////////////////////////////////////////
    struct VkLayerProperties
    {
        char        layerName[VK_MAX_EXTENSION_NAME_SIZE];
        uint32_t    specVersion;
        uint32_t    implementationVersion;
        char        description[VK_MAX_DESCRIPTION_SIZE];
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
    //  VkFormatProperties data structure                                     //
    ////////////////////////////////////////////////////////////////////////////
    struct VkFormatProperties
    {
        VkFormatFeatureFlags    linearTilingFeatures;
        VkFormatFeatureFlags    optimalTilingFeatures;
        VkFormatFeatureFlags    bufferFeatures;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkOffset3D data structure                                             //
    ////////////////////////////////////////////////////////////////////////////
    struct VkOffset3D
    {
        int32_t x;
        int32_t y;
        int32_t z;
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
    //  VkImageFormatProperties data structure                                //
    ////////////////////////////////////////////////////////////////////////////
    struct VkImageFormatProperties
    {
        VkExtent3D          maxExtent;
        uint32_t            maxMipLevels;
        uint32_t            maxArrayLayers;
        VkSampleCountFlags  sampleCounts;
        VkDeviceSize        maxResourceSize;
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
    //  VkSpecializationMapEntry data structure                               //
    ////////////////////////////////////////////////////////////////////////////
    struct VkSpecializationMapEntry
    {
        uint32_t    constantID;
        uint32_t    offset;
        size_t      size;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkSpecializationInfo data structure                                   //
    ////////////////////////////////////////////////////////////////////////////
    struct VkSpecializationInfo
    {
        uint32_t                            mapEntryCount;
        const VkSpecializationMapEntry*     pMapEntries;
        size_t                              dataSize;
        const void*                         pData;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkPipelineShaderStageCreateInfo data structure                        //
    ////////////////////////////////////////////////////////////////////////////
    struct VkPipelineShaderStageCreateInfo
    {
        VkStructureType                     sType;
        const void*                         pNext;
        VkPipelineShaderStageCreateFlags    flags;
        VkShaderStageFlagBits               stage;
        VkShaderModule                      module;
        const char*                         pName;
        const VkSpecializationInfo*         pSpecializationInfo;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkVertexInputBindingDescription data structure                        //
    ////////////////////////////////////////////////////////////////////////////
    struct VkVertexInputBindingDescription
    {
        uint32_t            binding;
        uint32_t            stride;
        VkVertexInputRate   inputRate;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkVertexInputAttributeDescription data structure                      //
    ////////////////////////////////////////////////////////////////////////////
    struct VkVertexInputAttributeDescription
    {
        uint32_t    location;
        uint32_t    binding;
        VkFormat    format;
        uint32_t    offset;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkPipelineVertexInputStateCreateInfo data structure                   //
    ////////////////////////////////////////////////////////////////////////////
    struct VkPipelineVertexInputStateCreateInfo
    {
        VkStructureType                         sType;
        const void*                             pNext;
        VkPipelineVertexInputStateCreateFlags   flags;
        uint32_t                                vertexBindingDescriptionCount;
        const VkVertexInputBindingDescription*  pVertexBindingDescriptions;
        uint32_t                                vertexAttributeDescriptionCount;
        const VkVertexInputAttributeDescription* pVertexAttributeDescriptions;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkPipelineInputAssemblyStateCreateInfo data structure                 //
    ////////////////////////////////////////////////////////////////////////////
    struct VkPipelineInputAssemblyStateCreateInfo
    {
        VkStructureType                             sType;
        const void*                                 pNext;
        VkPipelineInputAssemblyStateCreateFlags     flags;
        VkPrimitiveTopology                         topology;
        VkBool32                                    primitiveRestartEnable;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkPipelineTessellationStateCreateInfo data structure                  //
    ////////////////////////////////////////////////////////////////////////////
    struct VkPipelineTessellationStateCreateInfo
    {
        VkStructureType                         sType;
        const void*                             pNext;
        VkPipelineTessellationStateCreateFlags  flags;
        uint32_t                                patchControlPoints;
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
    //  VkPipelineViewportStateCreateInfo data structure                      //
    ////////////////////////////////////////////////////////////////////////////
    struct VkPipelineViewportStateCreateInfo
    {
        VkStructureType                     sType;
        const void*                         pNext;
        VkPipelineViewportStateCreateFlags  flags;
        uint32_t                            viewportCount;
        const VkViewport*                   pViewports;
        uint32_t                            scissorCount;
        const VkRect2D*                     pScissors;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkPipelineRasterizationStateCreateInfo data structure                 //
    ////////////////////////////////////////////////////////////////////////////
    struct VkPipelineRasterizationStateCreateInfo
    {
        VkStructureType                             sType;
        const void*                                 pNext;
        VkPipelineRasterizationStateCreateFlags     flags;
        VkBool32                                    depthClampEnable;
        VkBool32                                    rasterizerDiscardEnable;
        VkPolygonMode                               polygonMode;
        VkCullModeFlags                             cullMode;
        VkFrontFace                                 frontFace;
        VkBool32                                    depthBiasEnable;
        float                                       depthBiasConstantFactor;
        float                                       depthBiasClamp;
        float                                       depthBiasSlopeFactor;
        float                                       lineWidth;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkPipelineMultisampleStateCreateInfo data structure                   //
    ////////////////////////////////////////////////////////////////////////////
    struct VkPipelineMultisampleStateCreateInfo
    {
        VkStructureType                         sType;
        const void*                             pNext;
        VkPipelineMultisampleStateCreateFlags   flags;
        VkSampleCountFlagBits                   rasterizationSamples;
        VkBool32                                sampleShadingEnable;
        float                                   minSampleShading;
        const VkSampleMask*                     pSampleMask;
        VkBool32                                alphaToCoverageEnable;
        VkBool32                                alphaToOneEnable;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkStencilOpState data structure                                       //
    ////////////////////////////////////////////////////////////////////////////
    struct VkStencilOpState
    {
        VkStencilOp     failOp;
        VkStencilOp     passOp;
        VkStencilOp     depthFailOp;
        VkCompareOp     compareOp;
        uint32_t        compareMask;
        uint32_t        writeMask;
        uint32_t        reference;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkPipelineDepthStencilStateCreateInfo data structure                  //
    ////////////////////////////////////////////////////////////////////////////
    struct VkPipelineDepthStencilStateCreateInfo
    {
        VkStructureType                         sType;
        const void*                             pNext;
        VkPipelineDepthStencilStateCreateFlags  flags;
        VkBool32                                depthTestEnable;
        VkBool32                                depthWriteEnable;
        VkCompareOp                             depthCompareOp;
        VkBool32                                depthBoundsTestEnable;
        VkBool32                                stencilTestEnable;
        VkStencilOpState                        front;
        VkStencilOpState                        back;
        float                                   minDepthBounds;
        float                                   maxDepthBounds;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkPipelineColorBlendAttachmentState data structure                    //
    ////////////////////////////////////////////////////////////////////////////
    struct VkPipelineColorBlendAttachmentState
    {
        VkBool32                blendEnable;
        VkBlendFactor           srcColorBlendFactor;
        VkBlendFactor           dstColorBlendFactor;
        VkBlendOp               colorBlendOp;
        VkBlendFactor           srcAlphaBlendFactor;
        VkBlendFactor           dstAlphaBlendFactor;
        VkBlendOp               alphaBlendOp;
        VkColorComponentFlags   colorWriteMask;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkPipelineColorBlendStateCreateInfo data structure                    //
    ////////////////////////////////////////////////////////////////////////////
    struct VkPipelineColorBlendStateCreateInfo
    {
        VkStructureType                             sType;
        const void*                                 pNext;
        VkPipelineColorBlendStateCreateFlags        flags;
        VkBool32                                    logicOpEnable;
        VkLogicOp                                   logicOp;
        uint32_t                                    attachmentCount;
        const VkPipelineColorBlendAttachmentState*  pAttachments;
        float                                       blendConstants[4];
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkPipelineDynamicStateCreateInfo data structure                       //
    ////////////////////////////////////////////////////////////////////////////
    struct VkPipelineDynamicStateCreateInfo
    {
        VkStructureType                     sType;
        const void*                         pNext;
        VkPipelineDynamicStateCreateFlags   flags;
        uint32_t                            dynamicStateCount;
        const VkDynamicState*               pDynamicStates;
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
    //  VkSwapchainCreateInfoKHR data structure                               //
    ////////////////////////////////////////////////////////////////////////////
    struct VkSwapchainCreateInfoKHR
    {
        VkStructureType                 sType;
        const void*                     pNext;
        VkSwapchainCreateFlagsKHR       flags;
        VkSurfaceKHR                    surface;
        uint32_t                        minImageCount;
        VkFormat                        imageFormat;
        VkColorSpaceKHR                 imageColorSpace;
        VkExtent2D                      imageExtent;
        uint32_t                        imageArrayLayers;
        VkImageUsageFlags               imageUsage;
        VkSharingMode                   imageSharingMode;
        uint32_t                        queueFamilyIndexCount;
        const uint32_t*                 pQueueFamilyIndices;
        VkSurfaceTransformFlagBitsKHR   preTransform;
        VkCompositeAlphaFlagBitsKHR     compositeAlpha;
        VkPresentModeKHR                presentMode;
        VkBool32                        clipped;
        VkSwapchainKHR                  oldSwapchain;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkPresentInfoKHR data structure                                       //
    ////////////////////////////////////////////////////////////////////////////
    struct VkPresentInfoKHR
    {
        VkStructureType         sType;
        const void*             pNext;
        uint32_t                waitSemaphoreCount;
        const VkSemaphore*      pWaitSemaphores;
        uint32_t                swapchainCount;
        const VkSwapchainKHR*   pSwapchains;
        const uint32_t*         pImageIndices;
        VkResult*               pResults;
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
    //  VkMemoryAllocateInfo data structure                                   //
    ////////////////////////////////////////////////////////////////////////////
    struct VkMemoryAllocateInfo
    {
        VkStructureType     sType;
        const void*         pNext;
        VkDeviceSize        allocationSize;
        uint32_t            memoryTypeIndex;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkMappedMemoryRange data structure                                    //
    ////////////////////////////////////////////////////////////////////////////
    struct VkMappedMemoryRange
    {
        VkStructureType     sType;
        const void*         pNext;
        VkDeviceMemory      memory;
        VkDeviceSize        offset;
        VkDeviceSize        size;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkMemoryRequirements data structure                                   //
    ////////////////////////////////////////////////////////////////////////////
    struct VkMemoryRequirements
    {
        VkDeviceSize    size;
        VkDeviceSize    alignment;
        uint32_t        memoryTypeBits;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkSparseImageFormatProperties data structure                          //
    ////////////////////////////////////////////////////////////////////////////
    struct VkSparseImageFormatProperties
    {
        VkImageAspectFlags          aspectMask;
        VkExtent3D                  imageGranularity;
        VkSparseImageFormatFlags    flags;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkSparseImageMemoryRequirements data structure                        //
    ////////////////////////////////////////////////////////////////////////////
    struct VkSparseImageMemoryRequirements
    {
        VkSparseImageFormatProperties   formatProperties;
        uint32_t                        imageMipTailFirstLod;
        VkDeviceSize                    imageMipTailSize;
        VkDeviceSize                    imageMipTailOffset;
        VkDeviceSize                    imageMipTailStride;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkComponentMapping data structure                                     //
    ////////////////////////////////////////////////////////////////////////////
    struct VkComponentMapping
    {
        VkComponentSwizzle  r;
        VkComponentSwizzle  g;
        VkComponentSwizzle  b;
        VkComponentSwizzle  a;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkFramebufferCreateInfo data structure                                //
    ////////////////////////////////////////////////////////////////////////////
    struct VkFramebufferCreateInfo
    {
        VkStructureType             sType;
        const void*                 pNext;
        VkFramebufferCreateFlags    flags;
        VkRenderPass                renderPass;
        uint32_t                    attachmentCount;
        const VkImageView*          pAttachments;
        uint32_t                    width;
        uint32_t                    height;
        uint32_t                    layers;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkGraphicsPipelineCreateInfo data structure                           //
    ////////////////////////////////////////////////////////////////////////////
    struct VkGraphicsPipelineCreateInfo
    {
        VkStructureType                                 sType;
        const void*                                     pNext;
        VkPipelineCreateFlags                           flags;
        uint32_t                                        stageCount;
        const VkPipelineShaderStageCreateInfo*          pStages;
        const VkPipelineVertexInputStateCreateInfo*     pVertexInputState;
        const VkPipelineInputAssemblyStateCreateInfo*   pInputAssemblyState;
        const VkPipelineTessellationStateCreateInfo*    pTessellationState;
        const VkPipelineViewportStateCreateInfo*        pViewportState;
        const VkPipelineRasterizationStateCreateInfo*   pRasterizationState;
        const VkPipelineMultisampleStateCreateInfo*     pMultisampleState;
        const VkPipelineDepthStencilStateCreateInfo*    pDepthStencilState;
        const VkPipelineColorBlendStateCreateInfo*      pColorBlendState;
        const VkPipelineDynamicStateCreateInfo*         pDynamicState;
        VkPipelineLayout                                layout;
        VkRenderPass                                    renderPass;
        uint32_t                                        subpass;
        VkPipeline                                      basePipelineHandle;
        int32_t                                         basePipelineIndex;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkComputePipelineCreateInfo data structure                            //
    ////////////////////////////////////////////////////////////////////////////
    struct VkComputePipelineCreateInfo
    {
        VkStructureType                     sType;
        const void*                         pNext;
        VkPipelineCreateFlags               flags;
        VkPipelineShaderStageCreateInfo     stage;
        VkPipelineLayout                    layout;
        VkPipeline                          basePipelineHandle;
        int32_t                             basePipelineIndex;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkPushConstantRange data structure                                    //
    ////////////////////////////////////////////////////////////////////////////
    struct VkPushConstantRange
    {
        VkShaderStageFlags  stageFlags;
        uint32_t            offset;
        uint32_t            size;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkPipelineLayoutCreateInfo data structure                             //
    ////////////////////////////////////////////////////////////////////////////
    struct VkPipelineLayoutCreateInfo
    {
        VkStructureType                 sType;
        const void*                     pNext;
        VkPipelineLayoutCreateFlags     flags;
        uint32_t                        setLayoutCount;
        const VkDescriptorSetLayout*    pSetLayouts;
        uint32_t                        pushConstantRangeCount;
        const VkPushConstantRange*      pPushConstantRanges;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkSamplerCreateInfo data structure                                    //
    ////////////////////////////////////////////////////////////////////////////
    struct VkSamplerCreateInfo
    {
        VkStructureType         sType;
        const void*             pNext;
        VkSamplerCreateFlags    flags;
        VkFilter                magFilter;
        VkFilter                minFilter;
        VkSamplerMipmapMode     mipmapMode;
        VkSamplerAddressMode    addressModeU;
        VkSamplerAddressMode    addressModeV;
        VkSamplerAddressMode    addressModeW;
        float                   mipLodBias;
        VkBool32                anisotropyEnable;
        float                   maxAnisotropy;
        VkBool32                compareEnable;
        VkCompareOp             compareOp;
        float                   minLod;
        float                   maxLod;
        VkBorderColor           borderColor;
        VkBool32                unnormalizedCoordinates;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkDescriptorSetLayoutBinding data structure                           //
    ////////////////////////////////////////////////////////////////////////////
    struct VkDescriptorSetLayoutBinding
    {
        uint32_t            binding;
        VkDescriptorType    descriptorType;
        uint32_t            descriptorCount;
        VkShaderStageFlags  stageFlags;
        const VkSampler*    pImmutableSamplers;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkDescriptorSetLayoutCreateInfo data structure                        //
    ////////////////////////////////////////////////////////////////////////////
    struct VkDescriptorSetLayoutCreateInfo
    {
        VkStructureType                         sType;
        const void*                             pNext;
        VkDescriptorSetLayoutCreateFlags        flags;
        uint32_t                                bindingCount;
        const VkDescriptorSetLayoutBinding*     pBindings;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkDescriptorPoolSize data structure                                   //
    ////////////////////////////////////////////////////////////////////////////
    struct VkDescriptorPoolSize
    {
        VkDescriptorType    type;
        uint32_t            descriptorCount;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkDescriptorPoolCreateInfo data structure                             //
    ////////////////////////////////////////////////////////////////////////////
    struct VkDescriptorPoolCreateInfo
    {
        VkStructureType                 sType;
        const void*                     pNext;
        VkDescriptorPoolCreateFlags     flags;
        uint32_t                        maxSets;
        uint32_t                        poolSizeCount;
        const VkDescriptorPoolSize*     pPoolSizes;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkDescriptorSetAllocateInfo data structure                            //
    ////////////////////////////////////////////////////////////////////////////
    struct VkDescriptorSetAllocateInfo
    {
        VkStructureType                 sType;
        const void*                     pNext;
        VkDescriptorPool                descriptorPool;
        uint32_t                        descriptorSetCount;
        const VkDescriptorSetLayout*    pSetLayouts;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkDescriptorImageInfo data structure                                  //
    ////////////////////////////////////////////////////////////////////////////
    struct VkDescriptorImageInfo
    {
        VkSampler       sampler;
        VkImageView     imageView;
        VkImageLayout   imageLayout;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkDescriptorBufferInfo data structure                                 //
    ////////////////////////////////////////////////////////////////////////////
    struct VkDescriptorBufferInfo
    {
        VkBuffer        buffer;
        VkDeviceSize    offset;
        VkDeviceSize    range;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkWriteDescriptorSet data structure                                   //
    ////////////////////////////////////////////////////////////////////////////
    struct VkWriteDescriptorSet
    {
        VkStructureType                 sType;
        const void*                     pNext;
        VkDescriptorSet                 dstSet;
        uint32_t                        dstBinding;
        uint32_t                        dstArrayElement;
        uint32_t                        descriptorCount;
        VkDescriptorType                descriptorType;
        const VkDescriptorImageInfo*    pImageInfo;
        const VkDescriptorBufferInfo*   pBufferInfo;
        const VkBufferView*             pTexelBufferView;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkCopyDescriptorSet data structure                                    //
    ////////////////////////////////////////////////////////////////////////////
    struct VkCopyDescriptorSet
    {
        VkStructureType     sType;
        const void*         pNext;
        VkDescriptorSet     srcSet;
        uint32_t            srcBinding;
        uint32_t            srcArrayElement;
        VkDescriptorSet     dstSet;
        uint32_t            dstBinding;
        uint32_t            dstArrayElement;
        uint32_t            descriptorCount;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkSparseMemoryBind data structure                                     //
    ////////////////////////////////////////////////////////////////////////////
    struct VkSparseMemoryBind
    {
        VkDeviceSize                resourceOffset;
        VkDeviceSize                size;
        VkDeviceMemory              memory;
        VkDeviceSize                memoryOffset;
        VkSparseMemoryBindFlags     flags;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkSparseBufferMemoryBindInfo data structure                           //
    ////////////////////////////////////////////////////////////////////////////
    struct VkSparseBufferMemoryBindInfo
    {
        VkBuffer                    buffer;
        uint32_t                    bindCount;
        const VkSparseMemoryBind*   pBinds;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkSparseImageOpaqueMemoryBindInfo data structure                      //
    ////////////////////////////////////////////////////////////////////////////
    struct VkSparseImageOpaqueMemoryBindInfo
    {
        VkImage                     image;
        uint32_t                    bindCount;
        const VkSparseMemoryBind*   pBinds;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkImageSubresource data structure                                     //
    ////////////////////////////////////////////////////////////////////////////
    struct VkImageSubresource
    {
        VkImageAspectFlags  aspectMask;
        uint32_t            mipLevel;
        uint32_t            arrayLayer;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkSparseImageMemoryBind data structure                                //
    ////////////////////////////////////////////////////////////////////////////
    struct VkSparseImageMemoryBind
    {
        VkImageSubresource          subresource;
        VkOffset3D                  offset;
        VkExtent3D                  extent;
        VkDeviceMemory              memory;
        VkDeviceSize                memoryOffset;
        VkSparseMemoryBindFlags     flags;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkSparseImageMemoryBindInfo data structure                            //
    ////////////////////////////////////////////////////////////////////////////
    struct VkSparseImageMemoryBindInfo
    {
        VkImage                         image;
        uint32_t                        bindCount;
        const VkSparseImageMemoryBind*  pBinds;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkBindSparseInfo data structure                                       //
    ////////////////////////////////////////////////////////////////////////////
    struct VkBindSparseInfo
    {
        VkStructureType                             sType;
        const void*                                 pNext;
        uint32_t                                    waitSemaphoreCount;
        const VkSemaphore*                          pWaitSemaphores;
        uint32_t                                    bufferBindCount;
        const VkSparseBufferMemoryBindInfo*         pBufferBinds;
        uint32_t                                    imageOpaqueBindCount;
        const VkSparseImageOpaqueMemoryBindInfo*    pImageOpaqueBinds;
        uint32_t                                    imageBindCount;
        const VkSparseImageMemoryBindInfo*          pImageBinds;
        uint32_t                                    signalSemaphoreCount;
        const VkSemaphore*                          pSignalSemaphores;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkFenceCreateInfo data structure                                      //
    ////////////////////////////////////////////////////////////////////////////
    struct VkFenceCreateInfo
    {
        VkStructureType     sType;
        const void*         pNext;
        VkFenceCreateFlags  flags;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkSemaphoreCreateInfo data structure                                  //
    ////////////////////////////////////////////////////////////////////////////
    struct VkSemaphoreCreateInfo
    {
        VkStructureType         sType;
        const void*             pNext;
        VkSemaphoreCreateFlags  flags;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkEventCreateInfo data structure                                      //
    ////////////////////////////////////////////////////////////////////////////
    struct VkEventCreateInfo
    {
        VkStructureType     sType;
        const void*         pNext;
        VkEventCreateFlags  flags;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkBufferCreateInfo data structure                                     //
    ////////////////////////////////////////////////////////////////////////////
    struct VkBufferCreateInfo
    {
        VkStructureType         sType;
        const void*             pNext;
        VkBufferCreateFlags     flags;
        VkDeviceSize            size;
        VkBufferUsageFlags      usage;
        VkSharingMode           sharingMode;
        uint32_t                queueFamilyIndexCount;
        const uint32_t*         pQueueFamilyIndices;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkBufferViewCreateInfo data structure                                 //
    ////////////////////////////////////////////////////////////////////////////
    struct VkBufferViewCreateInfo
    {
        VkStructureType             sType;
        const void*                 pNext;
        VkBufferViewCreateFlags     flags;
        VkBuffer                    buffer;
        VkFormat                    format;
        VkDeviceSize                offset;
        VkDeviceSize                range;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkImageCreateInfo data structure                                      //
    ////////////////////////////////////////////////////////////////////////////
    struct VkImageCreateInfo
    {
        VkStructureType         sType;
        const void*             pNext;
        VkImageCreateFlags      flags;
        VkImageType             imageType;
        VkFormat                format;
        VkExtent3D              extent;
        uint32_t                mipLevels;
        uint32_t                arrayLayers;
        VkSampleCountFlagBits   samples;
        VkImageTiling           tiling;
        VkImageUsageFlags       usage;
        VkSharingMode           sharingMode;
        uint32_t                queueFamilyIndexCount;
        const uint32_t*         pQueueFamilyIndices;
        VkImageLayout           initialLayout;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkSubresourceLayout data structure                                    //
    ////////////////////////////////////////////////////////////////////////////
    struct VkSubresourceLayout
    {
        VkDeviceSize    offset;
        VkDeviceSize    size;
        VkDeviceSize    rowPitch;
        VkDeviceSize    arrayPitch;
        VkDeviceSize    depthPitch;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkAttachmentDescription data structure                                //
    ////////////////////////////////////////////////////////////////////////////
    struct VkAttachmentDescription
    {
        VkAttachmentDescriptionFlags    flags;
        VkFormat                        format;
        VkSampleCountFlagBits           samples;
        VkAttachmentLoadOp              loadOp;
        VkAttachmentStoreOp             storeOp;
        VkAttachmentLoadOp              stencilLoadOp;
        VkAttachmentStoreOp             stencilStoreOp;
        VkImageLayout                   initialLayout;
        VkImageLayout                   finalLayout;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkAttachmentReference data structure                                  //
    ////////////////////////////////////////////////////////////////////////////
    struct VkAttachmentReference
    {
        uint32_t        attachment;
        VkImageLayout   layout;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkSubpassDescription data structure                                   //
    ////////////////////////////////////////////////////////////////////////////
    struct VkSubpassDescription
    {
        VkSubpassDescriptionFlags       flags;
        VkPipelineBindPoint             pipelineBindPoint;
        uint32_t                        inputAttachmentCount;
        const VkAttachmentReference*    pInputAttachments;
        uint32_t                        colorAttachmentCount;
        const VkAttachmentReference*    pColorAttachments;
        const VkAttachmentReference*    pResolveAttachments;
        const VkAttachmentReference*    pDepthStencilAttachment;
        uint32_t                        preserveAttachmentCount;
        const uint32_t*                 pPreserveAttachments;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkSubpassDependency data structure                                    //
    ////////////////////////////////////////////////////////////////////////////
    struct VkSubpassDependency
    {
        uint32_t                srcSubpass;
        uint32_t                dstSubpass;
        VkPipelineStageFlags    srcStageMask;
        VkPipelineStageFlags    dstStageMask;
        VkAccessFlags           srcAccessMask;
        VkAccessFlags           dstAccessMask;
        VkDependencyFlags       dependencyFlags;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkRenderPassCreateInfo data structure                                 //
    ////////////////////////////////////////////////////////////////////////////
    struct VkRenderPassCreateInfo
    {
        VkStructureType                 sType;
        const void*                     pNext;
        VkRenderPassCreateFlags         flags;
        uint32_t                        attachmentCount;
        const VkAttachmentDescription*  pAttachments;
        uint32_t                        subpassCount;
        const VkSubpassDescription*     pSubpasses;
        uint32_t                        dependencyCount;
        const VkSubpassDependency*      pDependencies;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkImageSubresourceRange data structure                                //
    ////////////////////////////////////////////////////////////////////////////
    struct VkImageSubresourceRange
    {
        VkImageAspectFlags  aspectMask;
        uint32_t            baseMipLevel;
        uint32_t            levelCount;
        uint32_t            baseArrayLayer;
        uint32_t            layerCount;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkImageViewCreateInfo data structure                                  //
    ////////////////////////////////////////////////////////////////////////////
    struct VkImageViewCreateInfo
    {
        VkStructureType             sType;
        const void*                 pNext;
        VkImageViewCreateFlags      flags;
        VkImage                     image;
        VkImageViewType             viewType;
        VkFormat                    format;
        VkComponentMapping          components;
        VkImageSubresourceRange     subresourceRange;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkShaderModuleCreateInfo data structure                               //
    ////////////////////////////////////////////////////////////////////////////
    struct VkShaderModuleCreateInfo
    {
        VkStructureType             sType;
        const void*                 pNext;
        VkShaderModuleCreateFlags   flags;
        size_t                      codeSize;
        const uint32_t*             pCode;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkPipelineCacheCreateInfo data structure                              //
    ////////////////////////////////////////////////////////////////////////////
    struct VkPipelineCacheCreateInfo
    {
        VkStructureType             sType;
        const void*                 pNext;
        VkPipelineCacheCreateFlags  flags;
        size_t                      initialDataSize;
        const void*                 pInitialData;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkQueryPoolCreateInfo data structure                                  //
    ////////////////////////////////////////////////////////////////////////////
    struct VkQueryPoolCreateInfo
    {
        VkStructureType                 sType;
        const void*                     pNext;
        VkQueryPoolCreateFlags          flags;
        VkQueryType                     queryType;
        uint32_t                        queryCount;
        VkQueryPipelineStatisticFlags   pipelineStatistics;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkCommandPoolCreateInfo data structure                                //
    ////////////////////////////////////////////////////////////////////////////
    struct VkCommandPoolCreateInfo
    {
        VkStructureType             sType;
        const void*                 pNext;
        VkCommandPoolCreateFlags    flags;
        uint32_t                    queueFamilyIndex;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkCommandBufferAllocateInfo data structure                            //
    ////////////////////////////////////////////////////////////////////////////
    struct VkCommandBufferAllocateInfo
    {
        VkStructureType         sType;
        const void*             pNext;
        VkCommandPool           commandPool;
        VkCommandBufferLevel    level;
        uint32_t                commandBufferCount;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkCommandBufferInheritanceInfo data structure                         //
    ////////////////////////////////////////////////////////////////////////////
    struct VkCommandBufferInheritanceInfo
    {
        VkStructureType                 sType;
        const void*                     pNext;
        VkRenderPass                    renderPass;
        uint32_t                        subpass;
        VkFramebuffer                   framebuffer;
        VkBool32                        occlusionQueryEnable;
        VkQueryControlFlags             queryFlags;
        VkQueryPipelineStatisticFlags   pipelineStatistics;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkCommandBufferBeginInfo data structure                               //
    ////////////////////////////////////////////////////////////////////////////
    struct VkCommandBufferBeginInfo
    {
        VkStructureType                         sType;
        const void*                             pNext;
        VkCommandBufferUsageFlags               flags;
        const VkCommandBufferInheritanceInfo*   pInheritanceInfo;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkBufferCopy data structure                                           //
    ////////////////////////////////////////////////////////////////////////////
    struct VkBufferCopy
    {
        VkDeviceSize    srcOffset;
        VkDeviceSize    dstOffset;
        VkDeviceSize    size;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkImageSubresourceLayers data structure                               //
    ////////////////////////////////////////////////////////////////////////////
    struct VkImageSubresourceLayers
    {
        VkImageAspectFlags  aspectMask;
        uint32_t            mipLevel;
        uint32_t            baseArrayLayer;
        uint32_t            layerCount;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkBufferImageCopy data structure                                      //
    ////////////////////////////////////////////////////////////////////////////
    struct VkBufferImageCopy
    {
        VkDeviceSize                bufferOffset;
        uint32_t                    bufferRowLength;
        uint32_t                    bufferImageHeight;
        VkImageSubresourceLayers    imageSubresource;
        VkOffset3D                  imageOffset;
        VkExtent3D                  imageExtent;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkClearColorValue data structure                                      //
    ////////////////////////////////////////////////////////////////////////////
    union VkClearColorValue
    {
        float       float32[4];
        int32_t     int32[4];
        uint32_t    uint32[4];
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkClearDepthStencilValue data structure                               //
    ////////////////////////////////////////////////////////////////////////////
    struct VkClearDepthStencilValue
    {
        float       depth;
        uint32_t    stencil;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkClearValue data structure                                           //
    ////////////////////////////////////////////////////////////////////////////
    union VkClearValue
    {
        VkClearColorValue           color;
        VkClearDepthStencilValue    depthStencil;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkClearAttachment data structure                                      //
    ////////////////////////////////////////////////////////////////////////////
    struct VkClearAttachment
    {
        VkImageAspectFlags  aspectMask;
        uint32_t            colorAttachment;
        VkClearValue        clearValue;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkClearRect data structure                                            //
    ////////////////////////////////////////////////////////////////////////////
    struct VkClearRect
    {
        VkRect2D    rect;
        uint32_t    baseArrayLayer;
        uint32_t    layerCount;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkMemoryBarrier data structure                                        //
    ////////////////////////////////////////////////////////////////////////////
    struct VkMemoryBarrier
    {
        VkStructureType     sType;
        const void*         pNext;
        VkAccessFlags       srcAccessMask;
        VkAccessFlags       dstAccessMask;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkBufferMemoryBarrier data structure                                  //
    ////////////////////////////////////////////////////////////////////////////
    struct VkBufferMemoryBarrier
    {
        VkStructureType     sType;
        const void*         pNext;
        VkAccessFlags       srcAccessMask;
        VkAccessFlags       dstAccessMask;
        uint32_t            srcQueueFamilyIndex;
        uint32_t            dstQueueFamilyIndex;
        VkBuffer            buffer;
        VkDeviceSize        offset;
        VkDeviceSize        size;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkImageMemoryBarrier data structure                                   //
    ////////////////////////////////////////////////////////////////////////////
    struct VkImageMemoryBarrier
    {
        VkStructureType             sType;
        const void*                 pNext;
        VkAccessFlags               srcAccessMask;
        VkAccessFlags               dstAccessMask;
        VkImageLayout               oldLayout;
        VkImageLayout               newLayout;
        uint32_t                    srcQueueFamilyIndex;
        uint32_t                    dstQueueFamilyIndex;
        VkImage                     image;
        VkImageSubresourceRange     subresourceRange;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VkRenderPassBeginInfo data structure                                  //
    ////////////////////////////////////////////////////////////////////////////
    struct VkRenderPassBeginInfo
    {
        VkStructureType         sType;
        const void*             pNext;
        VkRenderPass            renderPass;
        VkFramebuffer           framebuffer;
        VkRect2D                renderArea;
        uint32_t                clearValueCount;
        const VkClearValue*     pClearValues;
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
    //  vkEnumerateInstanceLayerProperties function                           //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkEnumerateInstanceLayerProperties)(
        uint32_t* pPropertyCount, VkLayerProperties* pProperties
    );
    extern PFN_vkEnumerateInstanceLayerProperties
        vkEnumerateInstanceLayerProperties;


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
    //  vkGetPhysicalDeviceFormatProperties function                          //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkGetPhysicalDeviceFormatProperties)(
        VkPhysicalDevice physicalDevice, VkFormat format,
        VkFormatProperties* pFormatProperties
    );
    extern PFN_vkGetPhysicalDeviceFormatProperties
        vkGetPhysicalDeviceFormatProperties;

    ////////////////////////////////////////////////////////////////////////////
    //  vkGetPhysicalDeviceImageFormatProperties function                     //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkGetPhysicalDeviceImageFormatProperties)(
        VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type,
        VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags,
        VkImageFormatProperties* pImageFormatProperties
    );
    extern PFN_vkGetPhysicalDeviceImageFormatProperties
        vkGetPhysicalDeviceImageFormatProperties;

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
    //  vkEnumerateDeviceLayerProperties function                             //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkEnumerateDeviceLayerProperties)(
        VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount,
        VkLayerProperties* pProperties
    );
    extern PFN_vkEnumerateDeviceLayerProperties
        vkEnumerateDeviceLayerProperties;

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
    //  vkGetPhysicalDeviceSparseImageFormatProperties function               //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkGetPhysicalDeviceSparseImageFormatProperties)
        (VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type,
        VkSampleCountFlagBits samples, VkImageUsageFlags usage,
        VkImageTiling tiling, uint32_t* pPropertyCount,
        VkSparseImageFormatProperties* pProperties
    );
    extern PFN_vkGetPhysicalDeviceSparseImageFormatProperties
        vkGetPhysicalDeviceSparseImageFormatProperties;


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
    //  vkCreateSwapchainKHR function                                         //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkCreateSwapchainKHR)(
        VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo,
        const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain
    );
    extern PFN_vkCreateSwapchainKHR vkCreateSwapchainKHR;

    ////////////////////////////////////////////////////////////////////////////
    //  vkDestroySwapchainKHR function                                        //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkDestroySwapchainKHR)(
        VkDevice device, VkSwapchainKHR swapchain,
        const VkAllocationCallbacks* pAllocator
    );
    extern PFN_vkDestroySwapchainKHR vkDestroySwapchainKHR;

    ////////////////////////////////////////////////////////////////////////////
    //  vkGetSwapchainImagesKHR function                                      //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkGetSwapchainImagesKHR)(
        VkDevice device, VkSwapchainKHR swapchain,
        uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages
    );
    extern PFN_vkGetSwapchainImagesKHR vkGetSwapchainImagesKHR;

    ////////////////////////////////////////////////////////////////////////////
    //  vkAcquireNextImageKHR function                                        //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkAcquireNextImageKHR)(
        VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout,
        VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex
    );
    extern PFN_vkAcquireNextImageKHR vkAcquireNextImageKHR;

    ////////////////////////////////////////////////////////////////////////////
    //  vkQueuePresentKHR function                                            //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkQueuePresentKHR)(
        VkQueue queue, const VkPresentInfoKHR* pPresentInfo
    );
    extern PFN_vkQueuePresentKHR vkQueuePresentKHR;


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
    //  vkAllocateMemory function                                             //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkAllocateMemory)(
        VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo,
        const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory
    );
    extern PFN_vkAllocateMemory vkAllocateMemory;

    ////////////////////////////////////////////////////////////////////////////
    //  vkFreeMemory function                                                 //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkFreeMemory)(
        VkDevice device, VkDeviceMemory memory,
        const VkAllocationCallbacks* pAllocator
    );
    extern PFN_vkFreeMemory vkFreeMemory;

    ////////////////////////////////////////////////////////////////////////////
    //  vkMapMemory function                                                  //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkMapMemory)(
        VkDevice device, VkDeviceMemory memory, VkDeviceSize offset,
        VkDeviceSize size, VkMemoryMapFlags flags, void** ppData
    );
    extern PFN_vkMapMemory vkMapMemory;

    ////////////////////////////////////////////////////////////////////////////
    //  vkUnmapMemory function                                                //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkUnmapMemory)(
        VkDevice device, VkDeviceMemory memory
    );
    extern PFN_vkUnmapMemory vkUnmapMemory;

    ////////////////////////////////////////////////////////////////////////////
    //  vkFlushMappedMemoryRanges function                                    //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkFlushMappedMemoryRanges)(
        VkDevice device, uint32_t memoryRangeCount,
        const VkMappedMemoryRange* pMemoryRanges
    );
    extern PFN_vkFlushMappedMemoryRanges vkFlushMappedMemoryRanges;

    ////////////////////////////////////////////////////////////////////////////
    //  vkInvalidateMappedMemoryRanges function                               //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkInvalidateMappedMemoryRanges)(
        VkDevice device, uint32_t memoryRangeCount,
        const VkMappedMemoryRange* pMemoryRanges
    );
    extern PFN_vkInvalidateMappedMemoryRanges vkInvalidateMappedMemoryRanges;

    ////////////////////////////////////////////////////////////////////////////
    //  vkGetDeviceMemoryCommitment function                                  //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkGetDeviceMemoryCommitment)(
        VkDevice device, VkDeviceMemory memory,
        VkDeviceSize* pCommittedMemoryInBytes
    );
    extern PFN_vkGetDeviceMemoryCommitment vkGetDeviceMemoryCommitment;

    ////////////////////////////////////////////////////////////////////////////
    //  vkBindBufferMemory function                                           //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkBindBufferMemory)(
        VkDevice device, VkBuffer buffer,
        VkDeviceMemory memory, VkDeviceSize memoryOffset
    );
    extern PFN_vkBindBufferMemory vkBindBufferMemory;

    ////////////////////////////////////////////////////////////////////////////
    //  vkBindImageMemory function                                            //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkBindImageMemory)(
        VkDevice device, VkImage image,
        VkDeviceMemory memory, VkDeviceSize memoryOffset
    );
    extern PFN_vkBindImageMemory vkBindImageMemory;


    ////////////////////////////////////////////////////////////////////////////
    //  vkCreateRenderPass function                                           //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkCreateRenderPass)(
        VkDevice device, const VkRenderPassCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass
    );
    extern PFN_vkCreateRenderPass vkCreateRenderPass;

    ////////////////////////////////////////////////////////////////////////////
    //  vkDestroyRenderPass function                                          //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkDestroyRenderPass)(
        VkDevice device, VkRenderPass renderPass,
        const VkAllocationCallbacks* pAllocator
    );
    extern PFN_vkDestroyRenderPass vkDestroyRenderPass;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCreateFramebuffer function                                          //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkCreateFramebuffer)(
        VkDevice device, const VkFramebufferCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer
    );
    extern PFN_vkCreateFramebuffer vkCreateFramebuffer;

    ////////////////////////////////////////////////////////////////////////////
    //  vkDestroyFramebuffer function                                         //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkDestroyFramebuffer)(
        VkDevice device, VkFramebuffer framebuffer,
        const VkAllocationCallbacks* pAllocator
    );
    extern PFN_vkDestroyFramebuffer vkDestroyFramebuffer;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCreateImageView function                                            //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkCreateImageView)(
        VkDevice device, const VkImageViewCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator, VkImageView* pView
    );
    extern PFN_vkCreateImageView vkCreateImageView;

    ////////////////////////////////////////////////////////////////////////////
    //  vkDestroyImageView function                                           //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkDestroyImageView)(
        VkDevice device, VkImageView imageView,
        const VkAllocationCallbacks* pAllocator
    );
    extern PFN_vkDestroyImageView vkDestroyImageView;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCreateShaderModule function                                         //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkCreateShaderModule)(
        VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule
    );
    extern PFN_vkCreateShaderModule vkCreateShaderModule;

    ////////////////////////////////////////////////////////////////////////////
    //  vkDestroyShaderModule function                                        //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkDestroyShaderModule)(
        VkDevice device, VkShaderModule shaderModule,
        const VkAllocationCallbacks* pAllocator
    );
    extern PFN_vkDestroyShaderModule vkDestroyShaderModule;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCreatePipelineCache function                                        //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkCreatePipelineCache)(
        VkDevice device, const VkPipelineCacheCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache
    );
    extern PFN_vkCreatePipelineCache vkCreatePipelineCache;

    ////////////////////////////////////////////////////////////////////////////
    //  vkGetPipelineCacheData function                                       //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkGetPipelineCacheData)(
        VkDevice device, VkPipelineCache pipelineCache,
        size_t* pDataSize, void* pData
    );
    extern PFN_vkGetPipelineCacheData vkGetPipelineCacheData;

    ////////////////////////////////////////////////////////////////////////////
    //  vkMergePipelineCaches function                                        //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkMergePipelineCaches)(
        VkDevice device, VkPipelineCache dstCache,
        uint32_t srcCacheCount, const VkPipelineCache* pSrcCaches
    );
    extern PFN_vkMergePipelineCaches vkMergePipelineCaches;

    ////////////////////////////////////////////////////////////////////////////
    //  vkDestroyPipelineCache function                                       //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkDestroyPipelineCache)(
        VkDevice device, VkPipelineCache pipelineCache,
        const VkAllocationCallbacks* pAllocator
    );
    extern PFN_vkDestroyPipelineCache vkDestroyPipelineCache;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCreatePipelineLayout function                                       //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkCreatePipelineLayout)(
        VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkPipelineLayout* pPipelineLayout
    );
    extern PFN_vkCreatePipelineLayout vkCreatePipelineLayout;

    ////////////////////////////////////////////////////////////////////////////
    //  vkDestroyPipelineLayout function                                      //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkDestroyPipelineLayout)(
        VkDevice device, VkPipelineLayout pipelineLayout,
        const VkAllocationCallbacks* pAllocator
    );
    extern PFN_vkDestroyPipelineLayout vkDestroyPipelineLayout;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCreateSampler function                                              //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkCreateSampler)(
        VkDevice device, const VkSamplerCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator, VkSampler* pSampler
    );
    extern PFN_vkCreateSampler vkCreateSampler;

    ////////////////////////////////////////////////////////////////////////////
    //  vkDestroySampler function                                             //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkDestroySampler)(
        VkDevice device, VkSampler sampler,
        const VkAllocationCallbacks* pAllocator
    );
    extern PFN_vkDestroySampler vkDestroySampler;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCreateGraphicsPipelines function                                    //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkCreateGraphicsPipelines)(
        VkDevice device, VkPipelineCache pipelineCache,
        uint32_t createInfoCount,
        const VkGraphicsPipelineCreateInfo* pCreateInfos,
        const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines
    );
    extern PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCreateComputePipelines function                                     //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkCreateComputePipelines)(
        VkDevice device, VkPipelineCache pipelineCache,
        uint32_t createInfoCount,
        const VkComputePipelineCreateInfo* pCreateInfos,
        const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines
    );
    extern PFN_vkCreateComputePipelines vkCreateComputePipelines;

    ////////////////////////////////////////////////////////////////////////////
    //  vkDestroyPipeline function                                            //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkDestroyPipeline)(
        VkDevice device, VkPipeline pipeline,
        const VkAllocationCallbacks* pAllocator
    );
    extern PFN_vkDestroyPipeline vkDestroyPipeline;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCreateDescriptorSetLayout function                                  //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkCreateDescriptorSetLayout)(
        VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkDescriptorSetLayout* pSetLayout
    );
    extern PFN_vkCreateDescriptorSetLayout vkCreateDescriptorSetLayout;

    ////////////////////////////////////////////////////////////////////////////
    //  vkDestroyDescriptorSetLayout function                                 //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkDestroyDescriptorSetLayout)(
        VkDevice device, VkDescriptorSetLayout descriptorSetLayout,
        const VkAllocationCallbacks* pAllocator
    );
    extern PFN_vkDestroyDescriptorSetLayout vkDestroyDescriptorSetLayout;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCreateDescriptorPool function                                       //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkCreateDescriptorPool)(
        VkDevice device, const VkDescriptorPoolCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkDescriptorPool* pDescriptorPool
    );
    extern PFN_vkCreateDescriptorPool vkCreateDescriptorPool;

    ////////////////////////////////////////////////////////////////////////////
    //  vkDestroyDescriptorPool function                                      //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkDestroyDescriptorPool)(
        VkDevice device, VkDescriptorPool descriptorPool,
        const VkAllocationCallbacks* pAllocator
    );
    extern PFN_vkDestroyDescriptorPool vkDestroyDescriptorPool;

    ////////////////////////////////////////////////////////////////////////////
    //  vkResetDescriptorPool function                                        //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkResetDescriptorPool)(
        VkDevice device, VkDescriptorPool descriptorPool,
        VkDescriptorPoolResetFlags flags
    );
    extern PFN_vkResetDescriptorPool vkResetDescriptorPool;

    ////////////////////////////////////////////////////////////////////////////
    //  vkAllocateDescriptorSets function                                     //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkAllocateDescriptorSets)(
        VkDevice device, const VkDescriptorSetAllocateInfo* pAllocateInfo,
        VkDescriptorSet* pDescriptorSets
    );
    extern PFN_vkAllocateDescriptorSets vkAllocateDescriptorSets;

    ////////////////////////////////////////////////////////////////////////////
    //  vkFreeDescriptorSets function                                         //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkFreeDescriptorSets)(
        VkDevice device, VkDescriptorPool descriptorPool,
        uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets
    );
    extern PFN_vkFreeDescriptorSets vkFreeDescriptorSets;

    ////////////////////////////////////////////////////////////////////////////
    //  vkUpdateDescriptorSets function                                       //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkUpdateDescriptorSets)(
        VkDevice device, uint32_t descriptorWriteCount,
        const VkWriteDescriptorSet* pDescriptorWrites,
        uint32_t descriptorCopyCount,
        const VkCopyDescriptorSet* pDescriptorCopies
    );
    extern PFN_vkUpdateDescriptorSets vkUpdateDescriptorSets;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCreateBuffer function                                               //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkCreateBuffer)(
        VkDevice device, const VkBufferCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer
    );
    extern PFN_vkCreateBuffer vkCreateBuffer;

    ////////////////////////////////////////////////////////////////////////////
    //  vkDestroyBuffer function                                              //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkDestroyBuffer)(
        VkDevice device, VkBuffer buffer,
        const VkAllocationCallbacks* pAllocator
    );
    extern PFN_vkDestroyBuffer vkDestroyBuffer;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCreateBufferView function                                           //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkCreateBufferView)(
        VkDevice device, const VkBufferViewCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator, VkBufferView* pView
    );
    extern PFN_vkCreateBufferView vkCreateBufferView;

    ////////////////////////////////////////////////////////////////////////////
    //  vkDestroyBufferView function                                          //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkDestroyBufferView)(
        VkDevice device, VkBufferView bufferView,
        const VkAllocationCallbacks* pAllocator
    );
    extern PFN_vkDestroyBufferView vkDestroyBufferView;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCreateImage function                                                //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkCreateImage)(
        VkDevice device, const VkImageCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator, VkImage* pImage
    );
    extern PFN_vkCreateImage vkCreateImage;

    ////////////////////////////////////////////////////////////////////////////
    //  vkDestroyImage function                                               //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkDestroyImage)(
        VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator
    );
    extern PFN_vkDestroyImage vkDestroyImage;

    ////////////////////////////////////////////////////////////////////////////
    //  vkGetImageSubresourceLayout function                                  //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkGetImageSubresourceLayout)(
        VkDevice device, VkImage image, const VkImageSubresource* pSubresource,
        VkSubresourceLayout* pLayout
    );
    extern PFN_vkGetImageSubresourceLayout vkGetImageSubresourceLayout;

    ////////////////////////////////////////////////////////////////////////////
    //  vkGetBufferMemoryRequirements function                                //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkGetBufferMemoryRequirements)(
        VkDevice device, VkBuffer buffer,
        VkMemoryRequirements* pMemoryRequirements
    );
    extern PFN_vkGetBufferMemoryRequirements vkGetBufferMemoryRequirements;

    ////////////////////////////////////////////////////////////////////////////
    //  vkGetImageMemoryRequirements function                                 //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkGetImageMemoryRequirements)(
        VkDevice device, VkImage image,
        VkMemoryRequirements* pMemoryRequirements
    );
    extern PFN_vkGetImageMemoryRequirements vkGetImageMemoryRequirements;

    ////////////////////////////////////////////////////////////////////////////
    //  vkGetImageSparseMemoryRequirements function                           //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkGetImageSparseMemoryRequirements)(
        VkDevice device, VkImage image, uint32_t* pSparseMemoryRequirementCount,
        VkSparseImageMemoryRequirements* pSparseMemoryRequirements
    );
    extern PFN_vkGetImageSparseMemoryRequirements
        vkGetImageSparseMemoryRequirements;

    ////////////////////////////////////////////////////////////////////////////
    //  vkQueueBindSparse function                                            //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkQueueBindSparse)(
        VkQueue queue, uint32_t bindInfoCount,
        const VkBindSparseInfo* pBindInfo, VkFence fence
    );
    extern PFN_vkQueueBindSparse vkQueueBindSparse;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCreateFence function                                                //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkCreateFence)(
        VkDevice device, const VkFenceCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator, VkFence* pFence
    );
    extern PFN_vkCreateFence vkCreateFence;

    ////////////////////////////////////////////////////////////////////////////
    //  vkDestroyFence function                                               //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkDestroyFence)(
        VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator
    );
    extern PFN_vkDestroyFence vkDestroyFence;

    ////////////////////////////////////////////////////////////////////////////
    //  vkResetFences function                                                //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkResetFences)(
        VkDevice device, uint32_t fenceCount, const VkFence* pFences
    );
    extern PFN_vkResetFences vkResetFences;

    ////////////////////////////////////////////////////////////////////////////
    //  vkGetFenceStatus function                                             //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkGetFenceStatus)(
        VkDevice device, VkFence fence
    );
    extern PFN_vkGetFenceStatus vkGetFenceStatus;

    ////////////////////////////////////////////////////////////////////////////
    //  vkWaitForFences function                                              //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkWaitForFences)(
        VkDevice device, uint32_t fenceCount,
        const VkFence* pFences, VkBool32 waitAll, uint64_t timeout
    );
    extern PFN_vkWaitForFences vkWaitForFences;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCreateSemaphore function                                            //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkCreateSemaphore)(
        VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore
    );
    extern PFN_vkCreateSemaphore vkCreateSemaphore;

    ////////////////////////////////////////////////////////////////////////////
    //  vkDestroySemaphore function                                           //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkDestroySemaphore)(
        VkDevice device, VkSemaphore semaphore,
        const VkAllocationCallbacks* pAllocator
    );
    extern PFN_vkDestroySemaphore vkDestroySemaphore;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCreateEvent function                                                //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkCreateEvent)(
        VkDevice device, const VkEventCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator, VkEvent* pEvent
    );
    extern PFN_vkCreateEvent vkCreateEvent;

    ////////////////////////////////////////////////////////////////////////////
    //  vkDestroyEvent function                                               //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkDestroyEvent)(
        VkDevice device, VkEvent event, const VkAllocationCallbacks* pAllocator
    );
    extern PFN_vkDestroyEvent vkDestroyEvent;

    ////////////////////////////////////////////////////////////////////////////
    //  vkGetEventStatus function                                             //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkGetEventStatus)(
        VkDevice device, VkEvent event
    );
    extern PFN_vkGetEventStatus vkGetEventStatus;

    ////////////////////////////////////////////////////////////////////////////
    //  vkSetEvent function                                                   //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkSetEvent)(
        VkDevice device, VkEvent event
    );
    extern PFN_vkSetEvent vkSetEvent;

    ////////////////////////////////////////////////////////////////////////////
    //  vkResetEvent function                                                 //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkResetEvent)(
        VkDevice device, VkEvent event
    );
    extern PFN_vkResetEvent vkResetEvent;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCreateQueryPool function                                            //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkCreateQueryPool)(
        VkDevice device, const VkQueryPoolCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool
    );
    extern PFN_vkCreateQueryPool vkCreateQueryPool;

    ////////////////////////////////////////////////////////////////////////////
    //  vkDestroyQueryPool function                                           //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkDestroyQueryPool)(
        VkDevice device, VkQueryPool queryPool,
        const VkAllocationCallbacks* pAllocator
    );
    extern PFN_vkDestroyQueryPool vkDestroyQueryPool;

    ////////////////////////////////////////////////////////////////////////////
    //  vkGetQueryPoolResults function                                        //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkGetQueryPoolResults)(
        VkDevice device, VkQueryPool queryPool,
        uint32_t firstQuery, uint32_t queryCount, size_t dataSize,
        void* pData, VkDeviceSize stride, VkQueryResultFlags flags
    );
    extern PFN_vkGetQueryPoolResults vkGetQueryPoolResults;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCreateCommandPool function                                          //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkCreateCommandPool)(
        VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool
    );
    extern PFN_vkCreateCommandPool vkCreateCommandPool;

    ////////////////////////////////////////////////////////////////////////////
    //  vkDestroyCommandPool function                                         //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkDestroyCommandPool)(
        VkDevice device, VkCommandPool commandPool,
        const VkAllocationCallbacks* pAllocator
    );
    extern PFN_vkDestroyCommandPool vkDestroyCommandPool;

    ////////////////////////////////////////////////////////////////////////////
    //  vkResetCommandPool function                                           //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkResetCommandPool)(
        VkDevice device, VkCommandPool commandPool,
        VkCommandPoolResetFlags flags
    );
    extern PFN_vkResetCommandPool vkResetCommandPool;

    ////////////////////////////////////////////////////////////////////////////
    //  vkAllocateCommandBuffers function                                     //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkAllocateCommandBuffers)(
        VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo,
        VkCommandBuffer* pCommandBuffers
    );
    extern PFN_vkAllocateCommandBuffers vkAllocateCommandBuffers;

    ////////////////////////////////////////////////////////////////////////////
    //  vkFreeCommandBuffers function                                         //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkFreeCommandBuffers)(
        VkDevice device, VkCommandPool commandPool,
        uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers
    );
    extern PFN_vkFreeCommandBuffers vkFreeCommandBuffers;

    ////////////////////////////////////////////////////////////////////////////
    //  vkBeginCommandBuffer function                                         //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkBeginCommandBuffer)(
        VkCommandBuffer commandBuffer,
        const VkCommandBufferBeginInfo* pBeginInfo
    );
    extern PFN_vkBeginCommandBuffer vkBeginCommandBuffer;

    ////////////////////////////////////////////////////////////////////////////
    //  vkEndCommandBuffer function                                           //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkEndCommandBuffer)(
        VkCommandBuffer commandBuffer
    );
    extern PFN_vkEndCommandBuffer vkEndCommandBuffer;

    ////////////////////////////////////////////////////////////////////////////
    //  vkResetCommandBuffer function                                         //
    ////////////////////////////////////////////////////////////////////////////
    typedef VkResult (VOSVK_PTR *PFN_vkResetCommandBuffer)(
        VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags
    );
    extern PFN_vkResetCommandBuffer vkResetCommandBuffer;


    ////////////////////////////////////////////////////////////////////////////
    //  vkCmdBindPipeline function                                            //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkCmdBindPipeline)(
        VkCommandBuffer commandBuffer,
        VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline
    );
    extern PFN_vkCmdBindPipeline vkCmdBindPipeline;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCmdSetViewport function                                             //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkCmdSetViewport)(
        VkCommandBuffer commandBuffer, uint32_t firstViewport,
        uint32_t viewportCount, const VkViewport* pViewports
    );
    extern PFN_vkCmdSetViewport vkCmdSetViewport;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCmdSetScissor function                                              //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkCmdSetScissor)(
        VkCommandBuffer commandBuffer, uint32_t firstScissor,
        uint32_t scissorCount, const VkRect2D* pScissors
    );
    extern PFN_vkCmdSetScissor vkCmdSetScissor;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCmdBindDescriptorSets function                                      //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkCmdBindDescriptorSets)(
        VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint,
        VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount,
        const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount,
        const uint32_t* pDynamicOffsets
    );
    extern PFN_vkCmdBindDescriptorSets vkCmdBindDescriptorSets;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCmdBindIndexBuffer function                                         //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkCmdBindIndexBuffer)(
        VkCommandBuffer commandBuffer, VkBuffer buffer,
        VkDeviceSize offset, VkIndexType indexType
    );
    extern PFN_vkCmdBindIndexBuffer vkCmdBindIndexBuffer;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCmdBindVertexBuffers function                                       //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkCmdBindVertexBuffers)(
        VkCommandBuffer commandBuffer, uint32_t firstBinding,
        uint32_t bindingCount, const VkBuffer* pBuffers,
        const VkDeviceSize* pOffsets
    );
    extern PFN_vkCmdBindVertexBuffers vkCmdBindVertexBuffers;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCmdDraw function                                                    //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkCmdDraw)(
        VkCommandBuffer commandBuffer, uint32_t vertexCount,
        uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance
    );
    extern PFN_vkCmdDraw vkCmdDraw;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCmdDrawIndexed function                                             //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkCmdDrawIndexed)(
        VkCommandBuffer commandBuffer, uint32_t indexCount,
        uint32_t instanceCount, uint32_t firstIndex,
        int32_t vertexOffset, uint32_t firstInstance
    );
    extern PFN_vkCmdDrawIndexed vkCmdDrawIndexed;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCmdCopyBuffer function                                              //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkCmdCopyBuffer)(
        VkCommandBuffer commandBuffer, VkBuffer srcBuffer,
        VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions
    );
    extern PFN_vkCmdCopyBuffer vkCmdCopyBuffer;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCmdCopyBufferToImage function                                       //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkCmdCopyBufferToImage)(
        VkCommandBuffer commandBuffer, VkBuffer srcBuffer,
        VkImage dstImage, VkImageLayout dstImageLayout,
        uint32_t regionCount, const VkBufferImageCopy* pRegions
    );
    extern PFN_vkCmdCopyBufferToImage vkCmdCopyBufferToImage;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCmdCopyImageToBuffer function                                       //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkCmdCopyImageToBuffer)(
        VkCommandBuffer commandBuffer, VkImage srcImage,
        VkImageLayout srcImageLayout, VkBuffer dstBuffer,
        uint32_t regionCount, const VkBufferImageCopy* pRegions
    );
    extern PFN_vkCmdCopyImageToBuffer vkCmdCopyImageToBuffer;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCmdClearColorImage function                                         //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkCmdClearColorImage)(
        VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout,
        const VkClearColorValue* pColor, uint32_t rangeCount,
        const VkImageSubresourceRange* pRanges
    );
    extern PFN_vkCmdClearColorImage vkCmdClearColorImage;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCmdPipelineBarrier function                                         //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkCmdPipelineBarrier)(
        VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask,
        VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags,
        uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers,
        uint32_t bufferMemoryBarrierCount,
        const VkBufferMemoryBarrier* pBufferMemoryBarriers,
        uint32_t imageMemoryBarrierCount,
        const VkImageMemoryBarrier* pImageMemoryBarriers
    );
    extern PFN_vkCmdPipelineBarrier vkCmdPipelineBarrier;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCmdBeginRenderPass function                                         //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkCmdBeginRenderPass)(
        VkCommandBuffer commandBuffer,
        const VkRenderPassBeginInfo* pRenderPassBegin,
        VkSubpassContents contents
    );
    extern PFN_vkCmdBeginRenderPass vkCmdBeginRenderPass;

    ////////////////////////////////////////////////////////////////////////////
    //  vkCmdEndRenderPass function                                           //
    ////////////////////////////////////////////////////////////////////////////
    typedef void (VOSVK_PTR *PFN_vkCmdEndRenderPass)(
        VkCommandBuffer commandBuffer
    );
    extern PFN_vkCmdEndRenderPass vkCmdEndRenderPass;


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
