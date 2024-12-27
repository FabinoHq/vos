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
//     System/SysMemory.cpp : System memory management                        //
////////////////////////////////////////////////////////////////////////////////
#include "SysMemory.h"


////////////////////////////////////////////////////////////////////////////////
//  SysMemory global instance                                                 //
////////////////////////////////////////////////////////////////////////////////
SysMemory GSysMemory = SysMemory();


////////////////////////////////////////////////////////////////////////////////
//  SysMemory default constructor                                             //
////////////////////////////////////////////////////////////////////////////////
SysMemory::SysMemory()
{
    // Reset memory arrays
    for (int i = 0; i < SYSMEMORY_POOLSCOUNT; ++i)
    {
        m_memory[i] = 0;
        m_offset[i] = 0;
        m_usage[i] = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  SysMemory destructor                                                      //
////////////////////////////////////////////////////////////////////////////////
SysMemory::~SysMemory()
{
    // Free memory arrays
    for (int i = 0; i < SYSMEMORY_POOLSCOUNT; ++i)
    {
        if (m_memory[i]) { std::free(m_memory[i]); }
        m_memory[i] = 0;
        m_offset[i] = 0;
        m_usage[i] = 0;
    }
}


////////////////////////////////////////////////////////////////////////////////
//  Init system memory                                                        //
//  return : True if system memory is ready                                   //
////////////////////////////////////////////////////////////////////////////////
bool SysMemory::init()
{
    // Reset memory arrays
    for (int i = 0; i < SYSMEMORY_POOLSCOUNT; ++i)
    {
        m_memory[i] = 0;
        m_offset[i] = 0;
        m_usage[i] = 0;
    }

    // Allocate memory pools
    for (int i = 0; i < SYSMEMORY_POOLSCOUNT; ++i)
    {
        // Check memory pool size
        if (SysMemoryArray[i].size <= 0) { continue; }

        // Allocate system memory
        m_memory[i] = std::malloc(SysMemoryArray[i].size);
        if (!m_memory[i])
        {
            // Could not allocate system memory pool
            GSysMessage << "[0x1000] Could not allocate system memory pool\n";
            GSysMessage << "Please check your system memory";
            return false;
        }
    }

    // System memory is ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy system memory                                                     //
////////////////////////////////////////////////////////////////////////////////
void SysMemory::destroySysMemory()
{
    // Free memory arrays
    for (int i = 0; i < SYSMEMORY_POOLSCOUNT; ++i)
    {
        if (m_memory[i]) { std::free(m_memory[i]); }
        m_memory[i] = 0;
        m_offset[i] = 0;
        m_usage[i] = 0;
    }
}
