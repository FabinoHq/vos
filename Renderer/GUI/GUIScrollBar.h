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
//     Renderer/GUI/GUIScrollBar.h : GUI Scroll bar management                //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_GUI_GUISCROLLBAR_HEADER
#define VOS_RENDERER_GUI_GUISCROLLBAR_HEADER

    #include "../../System/System.h"

    #include "../Vulkan/Vulkan.h"
    #include "../Vulkan/Swapchain.h"
    #include "../Vulkan/GraphicsLayout.h"
    #include "../Vulkan/Texture.h"

    #include "../../Math/Math.h"
    #include "../../Math/Vector2.h"
    #include "../../Math/Vector4.h"
    #include "../../Math/Matrix4x4.h"
    #include "../../Math/Transform2.h"


    ////////////////////////////////////////////////////////////////////////////
    //  GUIScrollBar default settings                                         //
    ////////////////////////////////////////////////////////////////////////////
    const float GUIScrollBarDefaultIncrements = 0.1f;
    const float GUIScrollBarControlIncrements = 0.01f;
    const float GUIScrollBarMinScrollSize = 0.02f;
    const float GUIScrollBarMaxScrollSize = 1.0f;


    ////////////////////////////////////////////////////////////////////////////
    //  GUIScrollBar state enumeration                                        //
    ////////////////////////////////////////////////////////////////////////////
    enum GUIScrollBarState
    {
        GUISCROLLBAR_NONE = 0,
        GUISCROLLBAR_HOVER = 1,
        GUISCROLLBAR_PRESSED = 2,
        GUISCROLLBAR_PRESSEDHOVER = 3
    };


    ////////////////////////////////////////////////////////////////////////////
    //  GUIScrollBar class definition                                         //
    ////////////////////////////////////////////////////////////////////////////
    class GUIScrollBar : public Transform2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  GUIScrollBar default constructor                              //
            ////////////////////////////////////////////////////////////////////
            GUIScrollBar();

            ////////////////////////////////////////////////////////////////////
            //  GUIScrollBar virtual destructor                               //
            ////////////////////////////////////////////////////////////////////
            virtual ~GUIScrollBar();


        private:
            ////////////////////////////////////////////////////////////////////
            //  GUIScrollBar private copy constructor : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            GUIScrollBar(const GUIScrollBar&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  GUIScrollBar private copy operator : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            GUIScrollBar& operator=(const GUIScrollBar&) = delete;


        private:
            Texture*            m_texture;          // ScrollBar texture pointer
            Vector4             m_color;            // ScrollBar color
            float               m_uvFactor;         // Threepatch UV factor
            float               m_increments;       // ScrollBar increments
            float               m_ctrlIncrements;   // Control increments
            float               m_scrollSize;       // ScrollBar size
            float               m_value;            // ScrollBar value
            bool                m_vertical;         // ScrollBar vertical state
            bool                m_control;          // Control state
            bool                m_valueChanged;     // ScrollBar value changed
            bool                m_disabled;         // ScrollBar disabled state
            GUIScrollBarState   m_state;            // ScrollBar state
    };


#endif // VOS_RENDERER_GUI_GUISCROLLBAR_HEADER
