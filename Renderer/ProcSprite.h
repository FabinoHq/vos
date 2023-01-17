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
//     Renderer/ProcSprite.h : Procedural sprite management                   //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_PROCSPRITE_HEADER
#define VOS_RENDERER_PROCSPRITE_HEADER

    #include "../System/System.h"
    #include "Vulkan/Vulkan.h"
    #include "Vulkan/Swapchain.h"
    #include "Vulkan/GraphicsLayout.h"
    #include "Vulkan/Pipeline.h"
    #include "../Math/Math.h"
    #include "../Math/Vector4.h"
    #include "../Math/Matrix4x4.h"
    #include "../Math/Transform2.h"
    #include "Shaders/Default.h"
    #include "Shaders/DefaultProc.h"

    #include <cstddef>
    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  ProcSprite class definition                                           //
    ////////////////////////////////////////////////////////////////////////////
    class ProcSprite : public Transform2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  ProcSprite default constructor                                //
            ////////////////////////////////////////////////////////////////////
            ProcSprite();

            ////////////////////////////////////////////////////////////////////
            //  ProcSprite virtual destructor                                 //
            ////////////////////////////////////////////////////////////////////
            virtual ~ProcSprite();


            ////////////////////////////////////////////////////////////////////
            //  Init procedural sprite                                        //
            //  return : True if the proc sprite is successfully created      //
            ////////////////////////////////////////////////////////////////////
            bool init(VkRenderPass& renderPass, const uint32_t* fragmentSource,
                const size_t fragmentSize, float width, float height);

            ////////////////////////////////////////////////////////////////////
            //  Destroy procedural sprite                                     //
            ////////////////////////////////////////////////////////////////////
            void destroyProcSprite();

            ////////////////////////////////////////////////////////////////////
            //  Set procedural sprite color                                   //
            ////////////////////////////////////////////////////////////////////
            void setColor(const Vector4& color);

            ////////////////////////////////////////////////////////////////////
            //  Set procedural sprite color                                   //
            ////////////////////////////////////////////////////////////////////
            void setColor(float red, float green, float blue, float alpha);

            ////////////////////////////////////////////////////////////////////
            //  Set procedural sprite red channel                             //
            ////////////////////////////////////////////////////////////////////
            void setRed(float red);

            ////////////////////////////////////////////////////////////////////
            //  Set procedural sprite green channel                           //
            ////////////////////////////////////////////////////////////////////
            void setGreen(float green);

            ////////////////////////////////////////////////////////////////////
            //  Set procedural sprite blue channel                            //
            ////////////////////////////////////////////////////////////////////
            void setBlue(float blue);

            ////////////////////////////////////////////////////////////////////
            //  Set procedural sprite alpha channel                           //
            ////////////////////////////////////////////////////////////////////
            void setAlpha(float alpha);


            ////////////////////////////////////////////////////////////////////
            //  Bind procedural sprite pipeline                               //
            ////////////////////////////////////////////////////////////////////
            void bindPipeline();

            ////////////////////////////////////////////////////////////////////
            //  Render procedural sprite                                      //
            ////////////////////////////////////////////////////////////////////
            void render();


        private:
            ////////////////////////////////////////////////////////////////////
            //  ProcSprite private copy constructor : Not copyable            //
            ////////////////////////////////////////////////////////////////////
            ProcSprite(const ProcSprite&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  ProcSprite private copy operator : Not copyable               //
            ////////////////////////////////////////////////////////////////////
            ProcSprite& operator=(const ProcSprite&) = delete;


        private:
            Pipeline            m_pipeline;         // ProcSprite pipeline
            Vector4             m_color;            // ProcSprite color
    };


#endif // VOS_RENDERER_PROCSPRITE_HEADER
