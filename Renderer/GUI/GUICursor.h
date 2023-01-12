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
//     Renderer/GUI/GUICursor.h : GUI Cursor management                       //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_GUI_GUICURSOR_HEADER
#define VOS_RENDERER_GUI_GUICURSOR_HEADER

    #include "../../System/System.h"
    #include "../Vulkan/Texture.h"
    #include "../../Math/Math.h"
    #include "../../Math/Vector2.h"
    #include "../../Math/Vector4.h"
    #include "../../Math/Matrix4x4.h"
    #include "../../Math/Transform2.h"


    ////////////////////////////////////////////////////////////////////////////
    //  GUICursor offsets                                                     //
    ////////////////////////////////////////////////////////////////////////////
    const Vector2 GUICusorDefaultOffset = Vector2(2.0f, 2.0f);
    const Vector2 GUICusorNSCursorOffset = Vector2(10.0f, 24.0f);
    const Vector2 GUICusorEWCursorOffset = Vector2(24.0f, 10.0f);
    const Vector2 GUICusorNESWCursorOffset = Vector2(18.0f, 18.0f);
    const Vector2 GUICusorNWSECursorOffset = Vector2(18.0f, 18.0f);


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class declaration                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer;


    ////////////////////////////////////////////////////////////////////////////
    //  GUICursor class definition                                            //
    ////////////////////////////////////////////////////////////////////////////
    class GUICursor : public Transform2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  GUICursor default constructor                                 //
            ////////////////////////////////////////////////////////////////////
            GUICursor();

            ////////////////////////////////////////////////////////////////////
            //  GUICursor virtual destructor                                  //
            ////////////////////////////////////////////////////////////////////
            virtual ~GUICursor();


        private:
            ////////////////////////////////////////////////////////////////////
            //  GUICursor private copy constructor : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            GUICursor(const GUICursor&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  GUICursor private copy operator : Not copyable                //
            ////////////////////////////////////////////////////////////////////
            GUICursor& operator=(const GUICursor&) = delete;


        private:

    };


#endif // VOS_RENDERER_GUI_GUICURSOR_HEADER
