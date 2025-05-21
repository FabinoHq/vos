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
//     System/SysVkMemory.h : System Vulkan memory management                 //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_SYSTEM_SYSVKMEMORY_HEADER
#define VOS_SYSTEM_SYSVKMEMORY_HEADER

    #include "System.h"
    #include "SysMessage.h"

    #include <cstddef>
    #include <cstdlib>

    //#include <iostream>
    //#include <iomanip>


    ////////////////////////////////////////////////////////////////////////////
    //  SysVkMemory custom allocators usage (0 : default, 1 : custom)         //
    ////////////////////////////////////////////////////////////////////////////
    #define SYSVKMEMORY_CUSTOM 0

    ////////////////////////////////////////////////////////////////////////////
    //  SysVkMemory allocators                                                //
    ////////////////////////////////////////////////////////////////////////////
    #if (SYSVKMEMORY_CUSTOM == 1)

        #define SYSVKMEMORY_SAMPLER_ALLOC 0
        #define SYSVKMEMORY_SAMPLER_FREE 0

    #else

        #define SYSVKMEMORY_SAMPLER_ALLOC 0
        #define SYSVKMEMORY_SAMPLER_FREE 0

    #endif // SYSVKMEMORY_CUSTOM


    ////////////////////////////////////////////////////////////////////////////
    //  SysVkMemory settings                                                  //
    ////////////////////////////////////////////////////////////////////////////
    const size_t SysVkMemoryDefaultAlignment = 0x100;


    ////////////////////////////////////////////////////////////////////////////
    //  System vulkan memory pool enumeration                                 //
    ////////////////////////////////////////////////////////////////////////////
    enum SysVkMemoryPool
    {
        SYSVKMEMORY_SAMPLER = 0,

        SYSVKMEMORY_POOLSCOUNT = 1
    };


    ////////////////////////////////////////////////////////////////////////////
    //  SysVkMemoryList structure                                             //
    ////////////////////////////////////////////////////////////////////////////
    struct SysVkMemoryList
    {
        SysVkMemoryPool pool;
        size_t size;
    };


    ////////////////////////////////////////////////////////////////////////////
    //  SysVkMemoryArray : System vulkan memory pools and sizes               //
    ////////////////////////////////////////////////////////////////////////////
    const SysVkMemoryList SysVkMemoryArray[SYSVKMEMORY_POOLSCOUNT] =
    {

    };


    ////////////////////////////////////////////////////////////////////////////
    //  SysVkMemory class definition                                          //
    ////////////////////////////////////////////////////////////////////////////
    class SysVkMemory
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  SysVkMemory default constructor                               //
            ////////////////////////////////////////////////////////////////////
            SysVkMemory();

            ////////////////////////////////////////////////////////////////////
            //  SysVkMemory destructor                                        //
            ////////////////////////////////////////////////////////////////////
            ~SysVkMemory();


            ////////////////////////////////////////////////////////////////////
            //  Init system vulkan memory                                     //
            //  return : True if system vulkan memory is ready                //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Reset system vulkan memory pool                               //
            ////////////////////////////////////////////////////////////////////
            void resetMemory(SysVkMemoryPool memoryPool)
            {
                m_offset[memoryPool] = 0;
            }

            ////////////////////////////////////////////////////////////////////
            //  Destroy system vulkan memory                                  //
            ////////////////////////////////////////////////////////////////////
            void destroySysVkMemory();


            ////////////////////////////////////////////////////////////////////
            //  Dump system vulkan memory usage                               //
            ////////////////////////////////////////////////////////////////////
            /*void dumpMemory()
            {
                #if (SYSVKMEMORY_CUSTOM == 1)
                    std::cout << "System vulkan memory dump\n";
                    for (int i = 0; i < SYSVKMEMORY_POOLSCOUNT; ++i)
                    {
                        std::cout << std::hex << m_usage[i] << " ( ";
                        std::cout << std::dec << (
                            (m_usage[i]*1.0)/(SysVkMemoryArray[i].size*1.0)
                        )*100.0;
                        std::cout << " % )\n";
                    }
                    std::cout << '\n';
                #endif // SYSVKMEMORY_CUSTOM
            }*/


        private:
            ////////////////////////////////////////////////////////////////////
            //  SysVkMemory private copy constructor : Not copyable           //
            ////////////////////////////////////////////////////////////////////
            SysVkMemory(const SysVkMemory&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  SysVkMemory private copy operator : Not copyable              //
            ////////////////////////////////////////////////////////////////////
            SysVkMemory& operator=(const SysVkMemory&) = delete;


        private:
            void*       m_memory[SYSVKMEMORY_POOLSCOUNT];   // Memory
            size_t      m_offset[SYSVKMEMORY_POOLSCOUNT];   // Offset
            size_t      m_usage[SYSVKMEMORY_POOLSCOUNT];    // Usage
    };


    ////////////////////////////////////////////////////////////////////////////
    //  SysVkMemory global instance                                           //
    ////////////////////////////////////////////////////////////////////////////
    extern SysVkMemory GSysVkMemory;


#endif // VOS_SYSTEM_SYSVKMEMORY_HEADER
