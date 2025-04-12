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
//     System/SysMemory.h : System memory management                          //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_SYSTEM_SYSMEMORY_HEADER
#define VOS_SYSTEM_SYSMEMORY_HEADER

    #include "System.h"
    #include "SysMessage.h"

    #include <cstddef>
    #include <cstdlib>

    //#include <iostream>
    //#include <iomanip>


    ////////////////////////////////////////////////////////////////////////////
    //  SysMemory settings                                                    //
    ////////////////////////////////////////////////////////////////////////////
    const size_t SysMemoryDefaultAlignment = 0x100;


    ////////////////////////////////////////////////////////////////////////////
    //  System memory pool enumeration                                        //
    ////////////////////////////////////////////////////////////////////////////
    enum SysMemoryPool
    {
        SYSMEMORY_WINDOW = 0,
        SYSMEMORY_RENDERER = 1,
        SYSMEMORY_IMAGES = 2,
        SYSMEMORY_TEXTURES = 3,
        SYSMEMORY_MESHES = 4,

        SYSMEMORY_MATRICES = 5,
        SYSMEMORY_TILEMAPS = 6,
        SYSMEMORY_ISOMAPS = 7,
        SYSMEMORY_HEIGHTMAPS = 8,
        SYSMEMORY_HEIGHTFARS = 9,
        SYSMEMORY_SEANEARS = 10,
        SYSMEMORY_SEAFARS = 11,

        SYSMEMORY_POOLSCOUNT = 12
    };


    ////////////////////////////////////////////////////////////////////////////
    //  SysMemoryList structure                                               //
    ////////////////////////////////////////////////////////////////////////////
    struct SysMemoryList
    {
        SysMemoryPool pool;
        size_t size;
    };


    ////////////////////////////////////////////////////////////////////////////
    //  SysMemoryArray : Memory pools and sizes                               //
    ////////////////////////////////////////////////////////////////////////////
    const SysMemoryList SysMemoryArray[SYSMEMORY_POOLSCOUNT] =
    {
        SYSMEMORY_WINDOW, 0x1000,
        SYSMEMORY_RENDERER, 0x100000,
        SYSMEMORY_IMAGES, 0x1000000,
        SYSMEMORY_TEXTURES, 0x2000000,
        SYSMEMORY_MESHES, 0x800000,

        SYSMEMORY_MATRICES, 0x8000,
        SYSMEMORY_TILEMAPS, 0x1D000,
        SYSMEMORY_ISOMAPS, 0x1D000,
        SYSMEMORY_HEIGHTMAPS, 0xD0000,
        SYSMEMORY_HEIGHTFARS, 0xD0000,
        SYSMEMORY_SEANEARS, 0x32000,
        SYSMEMORY_SEAFARS, 0x32000
    };


    ////////////////////////////////////////////////////////////////////////////
    //  SysMemory class definition                                            //
    ////////////////////////////////////////////////////////////////////////////
    class SysMemory
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  SysMemory default constructor                                 //
            ////////////////////////////////////////////////////////////////////
            SysMemory();

            ////////////////////////////////////////////////////////////////////
            //  SysMemory destructor                                          //
            ////////////////////////////////////////////////////////////////////
            ~SysMemory();


            ////////////////////////////////////////////////////////////////////
            //  Init system memory                                            //
            //  return : True if system memory is ready                       //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Reset system memory pool                                      //
            ////////////////////////////////////////////////////////////////////
            void resetMemory(SysMemoryPool memoryPool)
            {
                m_offset[memoryPool] = 0;
            }

            ////////////////////////////////////////////////////////////////////
            //  Destroy system memory                                         //
            ////////////////////////////////////////////////////////////////////
            void destroySysMemory();


            ////////////////////////////////////////////////////////////////////
            //  Allocate memory                                               //
            ////////////////////////////////////////////////////////////////////
            template<typename T> T* alloc(size_t size, SysMemoryPool memoryPool,
                size_t alignment = SysMemoryDefaultAlignment)
            {
                // Check memory size
                if (size == 0) { return 0; }

                // Adjust memory size according to type
                size *= sizeof(T);

                // Adjust memory size according to alignment
                size_t sizeOffset = (size % alignment);
                if (sizeOffset != 0) { size += (alignment - sizeOffset); }

                // Adjust memory start offset according to alignment
                size_t offset = m_offset[memoryPool];
                size_t startOffset = (
                    (((size_t)m_memory[memoryPool]) + offset) % alignment
                );
                if (startOffset != 0) { offset += (alignment - startOffset); }

                // Check remaining memory in pool
                if ((offset + size) > SysMemoryArray[memoryPool].size)
                {
                    // Not enough remaining memory in pool
                    return 0;
                }

                // Get memory pointer
                T* data = (T*)(((size_t)m_memory[memoryPool]) + offset);

                // Update current memory offset
                m_offset[memoryPool] = (offset + size);

                // Update current memory usage
                if (m_offset[memoryPool] >= m_usage[memoryPool])
                {
                    m_usage[memoryPool] = m_offset[memoryPool];
                }

                // Return memory pointer
                return data;
            }


            ////////////////////////////////////////////////////////////////////
            //  Dump system memory usage                                      //
            ////////////////////////////////////////////////////////////////////
            /*void dumpMemory()
            {
                std::cout << "System memory dump\n";
                for (int i = 0; i < SYSMEMORY_POOLSCOUNT; ++i)
                {
                    std::cout << std::hex << m_usage[i] << " ( ";
                    std::cout << std::dec << (
                        (m_usage[i]*1.0)/(SysMemoryArray[i].size*1.0)
                    )*100.0;
                    std::cout << " % )\n";
                }
                std::cout << '\n';
            }*/


        private:
            ////////////////////////////////////////////////////////////////////
            //  SysMemory private copy constructor : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            SysMemory(const SysMemory&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  SysMemory private copy operator : Not copyable                //
            ////////////////////////////////////////////////////////////////////
            SysMemory& operator=(const SysMemory&) = delete;


        private:
            void*       m_memory[SYSMEMORY_POOLSCOUNT];     // Memory
            size_t      m_offset[SYSMEMORY_POOLSCOUNT];     // Offset
            size_t      m_usage[SYSMEMORY_POOLSCOUNT];      // Usage
    };


    ////////////////////////////////////////////////////////////////////////////
    //  SysMemory global instance                                             //
    ////////////////////////////////////////////////////////////////////////////
    extern SysMemory GSysMemory;


#endif // VOS_SYSTEM_SYSMEMORY_HEADER
