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
//     Renderer/Vulkan/ComputeLayout.h : Compute layout management            //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_VULKAN_COMPUTELAYOUT_HEADER
#define VOS_RENDERER_VULKAN_COMPUTELAYOUT_HEADER

    #include "../../System/System.h"
    #include "../../System/SysVkMemory.h"
    #include "../../System/SysMessage.h"
    #include "Vulkan.h"
    #include "../../Math/Math.h"

    #include <cstddef>
    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  ComputeLayout class definition                                        //
    ////////////////////////////////////////////////////////////////////////////
    class ComputeLayout
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  ComputeLayout default constructor                             //
            ////////////////////////////////////////////////////////////////////
            ComputeLayout();

            ////////////////////////////////////////////////////////////////////
            //  ComputeLayout destructor                                      //
            ////////////////////////////////////////////////////////////////////
            ~ComputeLayout();


            ////////////////////////////////////////////////////////////////////
            //  Create compute pipeline layout                                //
            //  return : True if compute layout is successfully created       //
            ////////////////////////////////////////////////////////////////////
            bool createLayout();

            ////////////////////////////////////////////////////////////////////
            //  Create pipeline layout                                        //
            //  return : True if pipeline layout is successfully created      //
            ////////////////////////////////////////////////////////////////////
            bool createPipelineLayout();

            ////////////////////////////////////////////////////////////////////
            //  Destroy compute pipeline layout                               //
            ////////////////////////////////////////////////////////////////////
            void destroyLayout();


        private:
            ////////////////////////////////////////////////////////////////////
            //  ComputeLayout private copy constructor : Not copyable         //
            ////////////////////////////////////////////////////////////////////
            ComputeLayout(const ComputeLayout&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  ComputeLayout private copy operator : Not copyable            //
            ////////////////////////////////////////////////////////////////////
            ComputeLayout& operator=(const ComputeLayout&) = delete;


        public:
            VkPipelineLayout        handle;         // Pipeline layout handle
    };


    ////////////////////////////////////////////////////////////////////////////
    //  ComputeLayout global instance                                         //
    ////////////////////////////////////////////////////////////////////////////
    extern ComputeLayout GComputeLayout;


#endif // VOS_RENDERER_VULKAN_COMPUTELAYOUT_HEADER
