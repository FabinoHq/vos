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
//   For more information, please refer to <http://unlicense.org>             //
////////////////////////////////////////////////////////////////////////////////
//    VOS : Virtual Operating System                                          //
//     Renderer/OpenGL/OpenGL.cpp : OpenGL rendering management               //
////////////////////////////////////////////////////////////////////////////////
#include "OpenGL.h"


////////////////////////////////////////////////////////////////////////////////
//  VOS OpenGL version                                                        //
////////////////////////////////////////////////////////////////////////////////
int VOSOpenGLMajorVersion = 1;
int VOSOpenGLMinorVersion = 0;


////////////////////////////////////////////////////////////////////////////////
//  Init OpenGL functions pointers                                            //
////////////////////////////////////////////////////////////////////////////////
PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements = 0;
PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D = 0;
PFNGLTEXIMAGE3DPROC glTexImage3D = 0;
PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D = 0;


////////////////////////////////////////////////////////////////////////////////
//  Init OpenGL                                                               //
////////////////////////////////////////////////////////////////////////////////
void InitOpenGL()
{
    // Init OpenGL 1.1
    VOSOpenGLMajorVersion = 1;
    VOSOpenGLMinorVersion = 1;

    // Init OpenGL 1.2
    bool openGL_1_2 = true;
    glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC)VOSGLGetProcAddress(
        "glDrawRangeElements"
    );
    if (!glDrawRangeElements) openGL_1_2 = false;
    glCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC)VOSGLGetProcAddress(
        "glCopyTexSubImage3D"
    );
    if (!glCopyTexSubImage3D) openGL_1_2 = false;
    glTexImage3D = (PFNGLTEXIMAGE3DPROC)VOSGLGetProcAddress(
        "glTexImage3D"
    );
    if (!glTexImage3D) openGL_1_2 = false;
    glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC)VOSGLGetProcAddress(
        "glTexSubImage3D"
    );
    if (!glTexSubImage3D) openGL_1_2 = false;

    if (openGL_1_2)
    {
        // OpenGL 1.2 ready
        VOSOpenGLMajorVersion = 1;
        VOSOpenGLMinorVersion = 2;
    }
}
