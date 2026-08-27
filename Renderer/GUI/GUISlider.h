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
//     Renderer/GUI/GUISlider.h : GUI Slider management                       //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_GUI_GUISLIDER_HEADER
#define VOS_RENDERER_GUI_GUISLIDER_HEADER

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
    //  GUISlider default increments                                          //
    ////////////////////////////////////////////////////////////////////////////
    const float GUISliderDefaultIncrements = 0.02f;
    const float GUISliderControlIncrements = 0.002f;


    ////////////////////////////////////////////////////////////////////////////
    //  GUISlider state enumeration                                           //
    ////////////////////////////////////////////////////////////////////////////
    enum GUISliderState
    {
        GUISLIDER_NONE = 0,
        GUISLIDER_HOVER = 1,
        GUISLIDER_PRESSED = 2,
        GUISLIDER_PRESSEDHOVER = 3
    };


    ////////////////////////////////////////////////////////////////////////////
    //  GUISlider class definition                                            //
    ////////////////////////////////////////////////////////////////////////////
    class GUISlider : public Transform2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  GUISlider default constructor                                 //
            ////////////////////////////////////////////////////////////////////
            GUISlider();

            ////////////////////////////////////////////////////////////////////
            //  GUISlider virtual destructor                                  //
            ////////////////////////////////////////////////////////////////////
            virtual ~GUISlider();


        private:
            ////////////////////////////////////////////////////////////////////
            //  GUISlider private copy constructor : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            GUISlider(const GUISlider&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  GUISlider private copy operator : Not copyable                //
            ////////////////////////////////////////////////////////////////////
            GUISlider& operator=(const GUISlider&) = delete;


        private:
            Texture*            m_texture;          // Slider texture pointer
            Vector4             m_color;            // Slider color
            float               m_uvFactor;         // Threepatch UV factor
            float               m_increments;       // Slider increments
            float               m_ctrlIncrements;   // Slider control increments
            float               m_value;            // Slider value
            bool                m_vertical;         // Slider vertical state
            bool                m_control;          // Control state
            bool                m_valueChanged;     // Slider value changed
            bool                m_disabled;         // Slider disabled state
            GUISliderState      m_state;            // Slider state
    };


#endif // VOS_RENDERER_GUI_GUISLIDER_HEADER
