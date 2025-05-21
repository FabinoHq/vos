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
//     System/SysVkMemory.cpp : System Vulkan memory management               //
////////////////////////////////////////////////////////////////////////////////
#include "SysVkMemory.h"


////////////////////////////////////////////////////////////////////////////////
//  SysVkMemory global instance                                               //
////////////////////////////////////////////////////////////////////////////////
SysVkMemory GSysVkMemory = SysVkMemory();


////////////////////////////////////////////////////////////////////////////////
//  SysVkMemory default constructor                                           //
////////////////////////////////////////////////////////////////////////////////
SysVkMemory::SysVkMemory()
{
    // Reset vulkan memory arrays
    for (int i = 0; i < SYSVKMEMORY_POOLSCOUNT; ++i)
    {
        m_memory[i] = 0;
        m_offset[i] = 0;
        m_usage[i] = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  SysVkMemory destructor                                                    //
////////////////////////////////////////////////////////////////////////////////
SysVkMemory::~SysVkMemory()
{
    // Free vulkan memory arrays
    for (int i = 0; i < SYSVKMEMORY_POOLSCOUNT; ++i)
    {
        if (m_memory[i]) { std::free(m_memory[i]); }
        m_memory[i] = 0;
        m_offset[i] = 0;
        m_usage[i] = 0;
    }
}


////////////////////////////////////////////////////////////////////////////////
//  Init system vulkan memory                                                 //
//  return : True if system vulkan memory is ready                            //
////////////////////////////////////////////////////////////////////////////////
bool SysVkMemory::init()
{
    #if (SYSVKMEMORY_CUSTOM == 1)
        // Reset memory arrays
        for (int i = 0; i < SYSVKMEMORY_POOLSCOUNT; ++i)
        {
            m_memory[i] = 0;
            m_offset[i] = 0;
            m_usage[i] = 0;
        }

        // Allocate memory pools
        for (int i = 0; i < SYSVKMEMORY_POOLSCOUNT; ++i)
        {
            // Check memory pool size
            if (SysVkMemoryArray[i].size <= 0) { continue; }

            // Allocate system vulkan memory
            m_memory[i] = std::malloc(SysVkMemoryArray[i].size);
            if (!m_memory[i])
            {
                // Could not allocate system vulkan memory pool
                GSysMessage <<
                    "[0x1000] Could not allocate system vulkan memory pool\n";
                GSysMessage << "Please check your system memory";
                return false;
            }
        }
    #endif // SYSVKMEMORY_CUSTOM

    // System vulkan memory is ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy system vulkan memory                                              //
////////////////////////////////////////////////////////////////////////////////
void SysVkMemory::destroySysVkMemory()
{
    // Free memory arrays
    for (int i = 0; i < SYSVKMEMORY_POOLSCOUNT; ++i)
    {
        if (m_memory[i]) { std::free(m_memory[i]); }
        m_memory[i] = 0;
        m_offset[i] = 0;
        m_usage[i] = 0;
    }
}
