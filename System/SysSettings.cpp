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
//     System/SysSettings.cpp : System Settings management                    //
////////////////////////////////////////////////////////////////////////////////
#include "SysSettings.h"


////////////////////////////////////////////////////////////////////////////////
//  SysSettings global instance                                               //
////////////////////////////////////////////////////////////////////////////////
SysSettings GSysSettings = SysSettings();


////////////////////////////////////////////////////////////////////////////////
//  SysSettings default constructor                                           //
////////////////////////////////////////////////////////////////////////////////
SysSettings::SysSettings() :
m_maxAnisotropicFiltering(ANISOTROPIC_FILTERING_NONE),
m_maxMultiSampling(MULTI_SAMPLING_NONE),
m_anisotropicFiltering(ANISOTROPIC_FILTERING_NONE),
m_multiSampling(MULTI_SAMPLING_NONE)
{

}

////////////////////////////////////////////////////////////////////////////////
//  SysSettings destructor                                                    //
////////////////////////////////////////////////////////////////////////////////
SysSettings::~SysSettings()
{
    m_multiSampling = MULTI_SAMPLING_NONE;
    m_anisotropicFiltering = ANISOTROPIC_FILTERING_NONE;
    m_maxMultiSampling = MULTI_SAMPLING_NONE;
    m_maxAnisotropicFiltering = ANISOTROPIC_FILTERING_NONE;
}


////////////////////////////////////////////////////////////////////////////////
//  Load system settings                                                      //
//  return : True if system settings are successfully loaded                  //
////////////////////////////////////////////////////////////////////////////////
bool SysSettings::loadSettings()
{
    // Temp set settings
    m_anisotropicFiltering = ANISOTROPIC_FILTERING_8X;
    m_multiSampling = MULTI_SAMPLING_8X;

    // System settings successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Adjust system settings according to device properties                     //
////////////////////////////////////////////////////////////////////////////////
void SysSettings::adjustSettings(VkPhysicalDeviceProperties& deviceProperties,
    VkPhysicalDeviceFeatures& deviceFeatures)
{
    // Set max anistrotropy filtering
    m_maxAnisotropicFiltering = ANISOTROPIC_FILTERING_NONE;
    if (deviceProperties.limits.maxSamplerAnisotropy >= 2.0f)
    {
        m_maxAnisotropicFiltering = ANISOTROPIC_FILTERING_2X;
    }
    if (deviceProperties.limits.maxSamplerAnisotropy >= 4.0f)
    {
        m_maxAnisotropicFiltering = ANISOTROPIC_FILTERING_4X;
    }
    if (deviceProperties.limits.maxSamplerAnisotropy >= 8.0f)
    {
        m_maxAnisotropicFiltering = ANISOTROPIC_FILTERING_8X;
    }
    if (deviceProperties.limits.maxSamplerAnisotropy >= 16.0f)
    {
        m_maxAnisotropicFiltering = ANISOTROPIC_FILTERING_16X;
    }

    if (deviceFeatures.samplerAnisotropy != VK_TRUE)
    {
        m_maxAnisotropicFiltering = ANISOTROPIC_FILTERING_NONE;
    }

    // Set max multisampling
    VkSampleCountFlags multiSampleCount =
        (deviceProperties.limits.framebufferColorSampleCounts &
        deviceProperties.limits.framebufferDepthSampleCounts);

    m_maxMultiSampling = MULTI_SAMPLING_NONE;
    if (multiSampleCount & VK_SAMPLE_COUNT_2_BIT)
    {
        m_maxMultiSampling = MULTI_SAMPLING_2X;
    }
    if (multiSampleCount & VK_SAMPLE_COUNT_4_BIT)
    {
        m_maxMultiSampling = MULTI_SAMPLING_4X;
    }
    if (multiSampleCount & VK_SAMPLE_COUNT_8_BIT)
    {
        m_maxMultiSampling = MULTI_SAMPLING_8X;
    }

    if (deviceFeatures.shaderStorageImageMultisample != VK_TRUE)
    {
        m_maxMultiSampling = MULTI_SAMPLING_NONE;
    }


    // Adjust anistrotropy filtering
    if (m_anisotropicFiltering >= m_maxAnisotropicFiltering)
    {
        m_anisotropicFiltering = m_maxAnisotropicFiltering;
    }

    // Adjust multisampling
    if (m_multiSampling >= m_maxMultiSampling)
    {
        m_multiSampling = m_maxMultiSampling;
    }
}
