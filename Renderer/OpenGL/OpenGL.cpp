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
//  VOS OpenGL functions pointers                                             //
////////////////////////////////////////////////////////////////////////////////
PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements = 0;
PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D = 0;
PFNGLTEXIMAGE3DPROC glTexImage3D = 0;
PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D = 0;

PFNGLLOADTRANSPOSEMATRIXDPROC glLoadTransposeMatrixd = 0;
PFNGLLOADTRANSPOSEMATRIXFPROC glLoadTransposeMatrixf = 0;
PFNGLMULTTRANSPOSEMATRIXDPROC glMultTransposeMatrixd = 0;
PFNGLMULTTRANSPOSEMATRIXFPROC glMultTransposeMatrixf = 0;
PFNGLACTIVETEXTUREPROC glActiveTexture = 0;
PFNGLCLIENTACTIVETEXTUREPROC glClientActiveTexture = 0;
PFNGLCOMPRESSEDTEXIMAGE1DPROC glCompressedTexImage1D = 0;
PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D = 0;
PFNGLCOMPRESSEDTEXIMAGE3DPROC glCompressedTexImage3D = 0;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glCompressedTexSubImage1D = 0;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D = 0;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3D = 0;
PFNGLGETCOMPRESSEDTEXIMAGEPROC glGetCompressedTexImage = 0;
PFNGLMULTITEXCOORD1DPROC glMultiTexCoord1d = 0;
PFNGLMULTITEXCOORD1DVPROC glMultiTexCoord1dv = 0;
PFNGLMULTITEXCOORD1FPROC glMultiTexCoord1f = 0;
PFNGLMULTITEXCOORD1FVPROC glMultiTexCoord1fv = 0;
PFNGLMULTITEXCOORD1IPROC glMultiTexCoord1i = 0;
PFNGLMULTITEXCOORD1IVPROC glMultiTexCoord1iv = 0;
PFNGLMULTITEXCOORD1SPROC glMultiTexCoord1s = 0;
PFNGLMULTITEXCOORD1SVPROC glMultiTexCoord1sv = 0;
PFNGLMULTITEXCOORD2DPROC glMultiTexCoord2d = 0;
PFNGLMULTITEXCOORD2DVPROC glMultiTexCoord2dv = 0;
PFNGLMULTITEXCOORD2FPROC glMultiTexCoord2f = 0;
PFNGLMULTITEXCOORD2FVPROC glMultiTexCoord2fv = 0;
PFNGLMULTITEXCOORD2IPROC glMultiTexCoord2i = 0;
PFNGLMULTITEXCOORD2IVPROC glMultiTexCoord2iv = 0;
PFNGLMULTITEXCOORD2SPROC glMultiTexCoord2s = 0;
PFNGLMULTITEXCOORD2SVPROC glMultiTexCoord2sv = 0;
PFNGLMULTITEXCOORD3DPROC glMultiTexCoord3d = 0;
PFNGLMULTITEXCOORD3DVPROC glMultiTexCoord3dv = 0;
PFNGLMULTITEXCOORD3FPROC glMultiTexCoord3f = 0;
PFNGLMULTITEXCOORD3FVPROC glMultiTexCoord3fv = 0;
PFNGLMULTITEXCOORD3IPROC glMultiTexCoord3i = 0;
PFNGLMULTITEXCOORD3IVPROC glMultiTexCoord3iv = 0;
PFNGLMULTITEXCOORD3SPROC glMultiTexCoord3s = 0;
PFNGLMULTITEXCOORD3SVPROC glMultiTexCoord3sv = 0;
PFNGLMULTITEXCOORD4DPROC glMultiTexCoord4d = 0;
PFNGLMULTITEXCOORD4DVPROC glMultiTexCoord4dv = 0;
PFNGLMULTITEXCOORD4FPROC glMultiTexCoord4f = 0;
PFNGLMULTITEXCOORD4FVPROC glMultiTexCoord4fv = 0;
PFNGLMULTITEXCOORD4IPROC glMultiTexCoord4i = 0;
PFNGLMULTITEXCOORD4IVPROC glMultiTexCoord4iv = 0;
PFNGLMULTITEXCOORD4SPROC glMultiTexCoord4s = 0;
PFNGLMULTITEXCOORD4SVPROC glMultiTexCoord4sv = 0;
PFNGLSAMPLECOVERAGEPROC glSampleCoverage = 0;

PFNGLBLENDCOLORPROC glBlendColor = 0;
PFNGLBLENDEQUATIONPROC glBlendEquation = 0;
PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate = 0;
PFNGLWINDOWPOS2DPROC glWindowPos2d = 0;
PFNGLWINDOWPOS2DVPROC glWindowPos2dv = 0;
PFNGLWINDOWPOS2FPROC glWindowPos2f = 0;
PFNGLWINDOWPOS2FVPROC glWindowPos2fv = 0;
PFNGLWINDOWPOS2IPROC glWindowPos2i = 0;
PFNGLWINDOWPOS2IVPROC glWindowPos2iv = 0;
PFNGLWINDOWPOS2SPROC glWindowPos2s = 0;
PFNGLWINDOWPOS2SVPROC glWindowPos2sv = 0;
PFNGLWINDOWPOS3DPROC glWindowPos3d = 0;
PFNGLWINDOWPOS3DVPROC glWindowPos3dv = 0;
PFNGLWINDOWPOS3FPROC glWindowPos3f = 0;
PFNGLWINDOWPOS3FVPROC glWindowPos3fv = 0;
PFNGLWINDOWPOS3IPROC glWindowPos3i = 0;
PFNGLWINDOWPOS3IVPROC glWindowPos3iv = 0;
PFNGLWINDOWPOS3SPROC glWindowPos3s = 0;
PFNGLWINDOWPOS3SVPROC glWindowPos3sv = 0;
PFNGLPOINTPARAMETERFPROC glPointParameterf = 0;
PFNGLPOINTPARAMETERFVPROC glPointParameterfv = 0;
PFNGLPOINTPARAMETERIPROC glPointParameteri = 0;
PFNGLPOINTPARAMETERIVPROC glPointParameteriv = 0;
PFNGLSECONDARYCOLOR3BPROC glSecondaryColor3b = 0;
PFNGLSECONDARYCOLOR3BVPROC glSecondaryColor3bv = 0;
PFNGLSECONDARYCOLOR3DPROC glSecondaryColor3d = 0;
PFNGLSECONDARYCOLOR3DVPROC glSecondaryColor3dv = 0;
PFNGLSECONDARYCOLOR3FPROC glSecondaryColor3f = 0;
PFNGLSECONDARYCOLOR3FVPROC glSecondaryColor3fv = 0;
PFNGLSECONDARYCOLOR3IPROC glSecondaryColor3i = 0;
PFNGLSECONDARYCOLOR3IVPROC glSecondaryColor3iv = 0;
PFNGLSECONDARYCOLOR3SPROC glSecondaryColor3s = 0;
PFNGLSECONDARYCOLOR3SVPROC glSecondaryColor3sv = 0;
PFNGLSECONDARYCOLOR3UBPROC glSecondaryColor3ub = 0;
PFNGLSECONDARYCOLOR3UBVPROC glSecondaryColor3ubv = 0;
PFNGLSECONDARYCOLOR3UIPROC glSecondaryColor3ui = 0;
PFNGLSECONDARYCOLOR3UIVPROC glSecondaryColor3uiv = 0;
PFNGLSECONDARYCOLOR3USPROC glSecondaryColor3us = 0;
PFNGLSECONDARYCOLOR3USVPROC glSecondaryColor3usv = 0;
PFNGLSECONDARYCOLORPOINTERPROC glSecondaryColorPointer = 0;
PFNGLMULTIDRAWARRAYSPROC glMultiDrawArrays = 0;
PFNGLMULTIDRAWELEMENTSPROC glMultiDrawElements = 0;
PFNGLFOGCOORDPOINTERPROC glFogCoordPointer = 0;
PFNGLFOGCOORDDPROC glFogCoordd = 0;
PFNGLFOGCOORDDVPROC glFogCoorddv = 0;
PFNGLFOGCOORDFPROC glFogCoordf = 0;
PFNGLFOGCOORDFVPROC glFogCoordfv = 0;


////////////////////////////////////////////////////////////////////////////////
//  Init OpenGL                                                               //
//  return : True if OpenGL is successfully loaded                            //
////////////////////////////////////////////////////////////////////////////////
bool InitOpenGL()
{
    // Init OpenGL 1.1
    VOSOpenGLMajorVersion = 1;
    VOSOpenGLMinorVersion = 1;

    // Init OpenGL 1.2
    if (InitOpenGL_1_2())
    {
        // OpenGL 1.2 ready
        VOSOpenGLMajorVersion = 1;
        VOSOpenGLMinorVersion = 2;
    }
    else
    {
        // Could not init OpenGL 1.2
        return false;
    }

    // Init OpenGL 1.3
    if (InitOpenGL_1_3())
    {
        // OpenGL 1.3 ready
        VOSOpenGLMajorVersion = 1;
        VOSOpenGLMinorVersion = 3;
    }
    else
    {
        // Could not init OpenGL 1.3
        return false;
    }

    // Init OpenGL 1.4
    if (InitOpenGL_1_4())
    {
        // OpenGL 1.4 ready
        VOSOpenGLMajorVersion = 1;
        VOSOpenGLMinorVersion = 4;
    }
    else
    {
        // Could not init OpenGL 1.4
        return false;
    }

    // OpenGL successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Init OpenGL 1.2                                                           //
//  return : True if OpenGL 1.2 is successfully loaded, false otherwise       //
////////////////////////////////////////////////////////////////////////////////
bool InitOpenGL_1_2()
{
    // Init OpenGL 1.2
    glDrawRangeElements =
        (PFNGLDRAWRANGEELEMENTSPROC)VOSGLGetProcAddress(
        "glDrawRangeElements"
    );
    if (!glDrawRangeElements) return false;
    glCopyTexSubImage3D =
        (PFNGLCOPYTEXSUBIMAGE3DPROC)VOSGLGetProcAddress(
        "glCopyTexSubImage3D"
    );
    if (!glCopyTexSubImage3D) return false;
    glTexImage3D =
        (PFNGLTEXIMAGE3DPROC)VOSGLGetProcAddress(
        "glTexImage3D"
    );
    if (!glTexImage3D) return false;
    glTexSubImage3D =
        (PFNGLTEXSUBIMAGE3DPROC)VOSGLGetProcAddress(
        "glTexSubImage3D"
    );
    if (!glTexSubImage3D) return false;

    // OpenGL 1.2 successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Init OpenGL 1.3                                                           //
//  return : True if OpenGL 1.3 is successfully loaded, false otherwise       //
////////////////////////////////////////////////////////////////////////////////
bool InitOpenGL_1_3()
{
    // Init OpenGL 1.3
    glLoadTransposeMatrixd =
        (PFNGLLOADTRANSPOSEMATRIXDPROC)VOSGLGetProcAddress(
        "glLoadTransposeMatrixd"
    );
    if (!glLoadTransposeMatrixd) return false;
    glLoadTransposeMatrixf =
        (PFNGLLOADTRANSPOSEMATRIXFPROC)VOSGLGetProcAddress(
        "glLoadTransposeMatrixf"
    );
    if (!glLoadTransposeMatrixf) return false;
    glMultTransposeMatrixd =
        (PFNGLMULTTRANSPOSEMATRIXDPROC)VOSGLGetProcAddress(
        "glMultTransposeMatrixd"
    );
    if (!glMultTransposeMatrixd) return false;
    glMultTransposeMatrixf =
        (PFNGLMULTTRANSPOSEMATRIXFPROC)VOSGLGetProcAddress(
        "glMultTransposeMatrixf"
    );
    if (!glMultTransposeMatrixf) return false;

    glActiveTexture =
        (PFNGLACTIVETEXTUREPROC)VOSGLGetProcAddress(
        "glActiveTexture"
    );
    if (!glActiveTexture) return false;
    glClientActiveTexture =
        (PFNGLCLIENTACTIVETEXTUREPROC)VOSGLGetProcAddress(
        "glClientActiveTexture"
    );
    if (!glClientActiveTexture) return false;
    glCompressedTexImage1D =
        (PFNGLCOMPRESSEDTEXIMAGE1DPROC)VOSGLGetProcAddress(
        "glCompressedTexImage1D"
    );
    if (!glCompressedTexImage1D) return false;
    glCompressedTexImage2D =
        (PFNGLCOMPRESSEDTEXIMAGE2DPROC)VOSGLGetProcAddress(
        "glCompressedTexImage2D"
    );
    if (!glCompressedTexImage2D) return false;
    glCompressedTexImage3D =
        (PFNGLCOMPRESSEDTEXIMAGE3DPROC)VOSGLGetProcAddress(
        "glCompressedTexImage3D"
    );
    if (!glCompressedTexImage3D) return false;
    glCompressedTexSubImage1D =
        (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)VOSGLGetProcAddress(
        "glCompressedTexSubImage1D"
    );
    if (!glCompressedTexSubImage1D) return false;
    glCompressedTexSubImage2D =
        (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)VOSGLGetProcAddress(
        "glCompressedTexSubImage2D"
    );
    if (!glCompressedTexSubImage2D) return false;
    glCompressedTexSubImage3D =
        (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)VOSGLGetProcAddress(
        "glCompressedTexSubImage3D"
    );
    if (!glCompressedTexSubImage3D) return false;
    glGetCompressedTexImage =
        (PFNGLGETCOMPRESSEDTEXIMAGEPROC)VOSGLGetProcAddress(
        "glGetCompressedTexImage"
    );
    if (!glGetCompressedTexImage) return false;
    glMultiTexCoord1d =
        (PFNGLMULTITEXCOORD1DPROC)VOSGLGetProcAddress(
        "glMultiTexCoord1d"
    );
    if (!glMultiTexCoord1d) return false;
    glMultiTexCoord1dv =
        (PFNGLMULTITEXCOORD1DVPROC)VOSGLGetProcAddress(
        "glMultiTexCoord1dv"
    );
    if (!glMultiTexCoord1dv) return false;
    glMultiTexCoord1f =
        (PFNGLMULTITEXCOORD1FPROC)VOSGLGetProcAddress(
        "glMultiTexCoord1f"
    );
    if (!glMultiTexCoord1f) return false;
    glMultiTexCoord1fv =
        (PFNGLMULTITEXCOORD1FVPROC)VOSGLGetProcAddress(
        "glMultiTexCoord1fv"
    );
    if (!glMultiTexCoord1fv) return false;
    glMultiTexCoord1i =
        (PFNGLMULTITEXCOORD1IPROC)VOSGLGetProcAddress(
        "glMultiTexCoord1i"
    );
    if (!glMultiTexCoord1i) return false;
    glMultiTexCoord1iv =
        (PFNGLMULTITEXCOORD1IVPROC)VOSGLGetProcAddress(
        "glMultiTexCoord1iv"
    );
    if (!glMultiTexCoord1iv) return false;
    glMultiTexCoord1s =
        (PFNGLMULTITEXCOORD1SPROC)VOSGLGetProcAddress(
        "glMultiTexCoord1s"
    );
    if (!glMultiTexCoord1s) return false;
    glMultiTexCoord1sv =
        (PFNGLMULTITEXCOORD1SVPROC)VOSGLGetProcAddress(
        "glMultiTexCoord1sv"
    );
    if (!glMultiTexCoord1sv) return false;
    glMultiTexCoord2d =
        (PFNGLMULTITEXCOORD2DPROC)VOSGLGetProcAddress(
        "glMultiTexCoord2d"
    );
    if (!glMultiTexCoord2d) return false;
    glMultiTexCoord2dv =
        (PFNGLMULTITEXCOORD2DVPROC)VOSGLGetProcAddress(
        "glMultiTexCoord2dv"
    );
    if (!glMultiTexCoord2dv) return false;
    glMultiTexCoord2f =
        (PFNGLMULTITEXCOORD2FPROC)VOSGLGetProcAddress(
        "glMultiTexCoord2f"
    );
    if (!glMultiTexCoord2f) return false;
    glMultiTexCoord2fv =
        (PFNGLMULTITEXCOORD2FVPROC)VOSGLGetProcAddress(
        "glMultiTexCoord2fv"
    );
    if (!glMultiTexCoord2fv) return false;
    glMultiTexCoord2i =
        (PFNGLMULTITEXCOORD2IPROC)VOSGLGetProcAddress(
        "glMultiTexCoord2i"
    );
    if (!glMultiTexCoord2i) return false;
    glMultiTexCoord2iv =
        (PFNGLMULTITEXCOORD2IVPROC)VOSGLGetProcAddress(
        "glMultiTexCoord2iv"
    );
    if (!glMultiTexCoord2iv) return false;
    glMultiTexCoord2s =
        (PFNGLMULTITEXCOORD2SPROC)VOSGLGetProcAddress(
        "glMultiTexCoord2s"
    );
    if (!glMultiTexCoord2s) return false;
    glMultiTexCoord2sv =
        (PFNGLMULTITEXCOORD2SVPROC)VOSGLGetProcAddress(
        "glMultiTexCoord2sv"
    );
    if (!glMultiTexCoord2sv) return false;
    glMultiTexCoord3d =
        (PFNGLMULTITEXCOORD3DPROC)VOSGLGetProcAddress(
        "glMultiTexCoord3d"
    );
    if (!glMultiTexCoord3d) return false;
    glMultiTexCoord3dv =
        (PFNGLMULTITEXCOORD3DVPROC)VOSGLGetProcAddress(
        "glMultiTexCoord3dv"
    );
    if (!glMultiTexCoord3dv) return false;
    glMultiTexCoord3f =
        (PFNGLMULTITEXCOORD3FPROC)VOSGLGetProcAddress(
        "glMultiTexCoord3f"
    );
    if (!glMultiTexCoord3f) return false;
    glMultiTexCoord3fv =
        (PFNGLMULTITEXCOORD3FVPROC)VOSGLGetProcAddress(
        "glMultiTexCoord3fv"
    );
    if (!glMultiTexCoord3fv) return false;
    glMultiTexCoord3i =
        (PFNGLMULTITEXCOORD3IPROC)VOSGLGetProcAddress(
        "glMultiTexCoord3i"
    );
    if (!glMultiTexCoord3i) return false;
    glMultiTexCoord3iv =
        (PFNGLMULTITEXCOORD3IVPROC)VOSGLGetProcAddress(
        "glMultiTexCoord3iv"
    );
    if (!glMultiTexCoord3iv) return false;
    glMultiTexCoord3s =
        (PFNGLMULTITEXCOORD3SPROC)VOSGLGetProcAddress(
        "glMultiTexCoord3s"
    );
    if (!glMultiTexCoord3s) return false;
    glMultiTexCoord3sv =
        (PFNGLMULTITEXCOORD3SVPROC)VOSGLGetProcAddress(
        "glMultiTexCoord3sv"
    );
    if (!glMultiTexCoord3sv) return false;
    glMultiTexCoord4d =
        (PFNGLMULTITEXCOORD4DPROC)VOSGLGetProcAddress(
        "glMultiTexCoord4d"
    );
    if (!glMultiTexCoord4d) return false;
    glMultiTexCoord4dv =
        (PFNGLMULTITEXCOORD4DVPROC)VOSGLGetProcAddress(
        "glMultiTexCoord4dv"
    );
    if (!glMultiTexCoord4dv) return false;
    glMultiTexCoord4f =
        (PFNGLMULTITEXCOORD4FPROC)VOSGLGetProcAddress(
        "glMultiTexCoord4f"
    );
    if (!glMultiTexCoord4f) return false;
    glMultiTexCoord4fv =
        (PFNGLMULTITEXCOORD4FVPROC)VOSGLGetProcAddress(
        "glMultiTexCoord4fv"
    );
    if (!glMultiTexCoord4fv) return false;
    glMultiTexCoord4i =
        (PFNGLMULTITEXCOORD4IPROC)VOSGLGetProcAddress(
        "glMultiTexCoord4i"
    );
    if (!glMultiTexCoord4i) return false;
    glMultiTexCoord4iv =
        (PFNGLMULTITEXCOORD4IVPROC)VOSGLGetProcAddress(
        "glMultiTexCoord4iv"
    );
    if (!glMultiTexCoord4iv) return false;
    glMultiTexCoord4s =
        (PFNGLMULTITEXCOORD4SPROC)VOSGLGetProcAddress(
        "glMultiTexCoord4s"
    );
    if (!glMultiTexCoord4s) return false;
    glMultiTexCoord4sv =
        (PFNGLMULTITEXCOORD4SVPROC)VOSGLGetProcAddress(
        "glMultiTexCoord4sv"
    );
    if (!glMultiTexCoord4sv) return false;
    glSampleCoverage =
        (PFNGLSAMPLECOVERAGEPROC)VOSGLGetProcAddress(
        "glSampleCoverage"
    );
    if (!glSampleCoverage) return false;

    // OpenGL 1.3 successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Init OpenGL 1.4                                                           //
//  return : True if OpenGL 1.4 is successfully loaded, false otherwise       //
////////////////////////////////////////////////////////////////////////////////
bool InitOpenGL_1_4()
{
    // Init OpenGL 1.4
    glBlendColor =
        (PFNGLBLENDCOLORPROC)VOSGLGetProcAddress(
        "glBlendColor"
    );
    if (!glBlendColor) return false;
    glBlendEquation =
        (PFNGLBLENDEQUATIONPROC)VOSGLGetProcAddress(
        "glBlendEquation"
    );
    if (!glBlendEquation) return false;
    glBlendFuncSeparate =
        (PFNGLBLENDFUNCSEPARATEPROC)VOSGLGetProcAddress(
        "glBlendFuncSeparate"
    );
    if (!glBlendFuncSeparate) return false;

    glWindowPos2d =
        (PFNGLWINDOWPOS2DPROC)VOSGLGetProcAddress(
        "glWindowPos2d"
    );
    if (!glWindowPos2d) return false;
    glWindowPos2dv =
        (PFNGLWINDOWPOS2DVPROC)VOSGLGetProcAddress(
        "glWindowPos2dv"
    );
    if (!glWindowPos2dv) return false;
    glWindowPos2f =
        (PFNGLWINDOWPOS2FPROC)VOSGLGetProcAddress(
        "glWindowPos2f"
    );
    if (!glWindowPos2f) return false;
    glWindowPos2fv =
        (PFNGLWINDOWPOS2FVPROC)VOSGLGetProcAddress(
        "glWindowPos2fv"
    );
    if (!glWindowPos2fv) return false;
    glWindowPos2i =
        (PFNGLWINDOWPOS2IPROC)VOSGLGetProcAddress(
        "glWindowPos2i"
    );
    if (!glWindowPos2i) return false;
    glWindowPos2iv =
        (PFNGLWINDOWPOS2IVPROC)VOSGLGetProcAddress(
        "glWindowPos2iv"
    );
    if (!glWindowPos2iv) return false;
    glWindowPos2s =
        (PFNGLWINDOWPOS2SPROC)VOSGLGetProcAddress(
        "glWindowPos2s"
    );
    if (!glWindowPos2s) return false;
    glWindowPos2sv =
        (PFNGLWINDOWPOS2SVPROC)VOSGLGetProcAddress(
        "glWindowPos2sv"
    );
    if (!glWindowPos2sv) return false;
    glWindowPos3d =
        (PFNGLWINDOWPOS3DPROC)VOSGLGetProcAddress(
        "glWindowPos3d"
    );
    if (!glWindowPos3d) return false;
    glWindowPos3dv =
        (PFNGLWINDOWPOS3DVPROC)VOSGLGetProcAddress(
        "glWindowPos3dv"
    );
    if (!glWindowPos3dv) return false;
    glWindowPos3f =
        (PFNGLWINDOWPOS3FPROC)VOSGLGetProcAddress(
        "glWindowPos3f"
    );
    if (!glWindowPos3f) return false;
    glWindowPos3fv =
        (PFNGLWINDOWPOS3FVPROC)VOSGLGetProcAddress(
        "glWindowPos3fv"
    );
    if (!glWindowPos3fv) return false;
    glWindowPos3i =
        (PFNGLWINDOWPOS3IPROC)VOSGLGetProcAddress(
        "glWindowPos3i"
    );
    if (!glWindowPos3i) return false;
    glWindowPos3iv =
        (PFNGLWINDOWPOS3IVPROC)VOSGLGetProcAddress(
        "glWindowPos3iv"
    );
    if (!glWindowPos3iv) return false;
    glWindowPos3s =
        (PFNGLWINDOWPOS3SPROC)VOSGLGetProcAddress(
        "glWindowPos3s"
    );
    if (!glWindowPos3s) return false;
    glWindowPos3sv =
        (PFNGLWINDOWPOS3SVPROC)VOSGLGetProcAddress(
        "glWindowPos3sv"
    );
    if (!glWindowPos3sv) return false;

    glPointParameterf =
        (PFNGLPOINTPARAMETERFPROC)VOSGLGetProcAddress(
        "glPointParameterf"
    );
    if (!glPointParameterf) return false;
    glPointParameterfv =
        (PFNGLPOINTPARAMETERFVPROC)VOSGLGetProcAddress(
        "glPointParameterfv"
    );
    if (!glPointParameterfv) return false;
    glPointParameteri =
        (PFNGLPOINTPARAMETERIPROC)VOSGLGetProcAddress(
        "glPointParameteri"
    );
    if (!glPointParameteri) return false;
    glPointParameteriv =
        (PFNGLPOINTPARAMETERIVPROC)VOSGLGetProcAddress(
        "glPointParameteriv"
    );
    if (!glPointParameteriv) return false;

    glSecondaryColor3b =
        (PFNGLSECONDARYCOLOR3BPROC)VOSGLGetProcAddress(
        "glSecondaryColor3b"
    );
    if (!glSecondaryColor3b) return false;
    glSecondaryColor3bv =
        (PFNGLSECONDARYCOLOR3BVPROC)VOSGLGetProcAddress(
        "glSecondaryColor3bv"
    );
    if (!glSecondaryColor3bv) return false;
    glSecondaryColor3d =
        (PFNGLSECONDARYCOLOR3DPROC)VOSGLGetProcAddress(
        "glSecondaryColor3d"
    );
    if (!glSecondaryColor3d) return false;
    glSecondaryColor3dv =
        (PFNGLSECONDARYCOLOR3DVPROC)VOSGLGetProcAddress(
        "glSecondaryColor3dv"
    );
    if (!glSecondaryColor3dv) return false;
    glSecondaryColor3f =
        (PFNGLSECONDARYCOLOR3FPROC)VOSGLGetProcAddress(
        "glSecondaryColor3f"
    );
    if (!glSecondaryColor3f) return false;
    glSecondaryColor3fv =
        (PFNGLSECONDARYCOLOR3FVPROC)VOSGLGetProcAddress(
        "glSecondaryColor3fv"
    );
    if (!glSecondaryColor3fv) return false;
    glSecondaryColor3i =
        (PFNGLSECONDARYCOLOR3IPROC)VOSGLGetProcAddress(
        "glSecondaryColor3i"
    );
    if (!glSecondaryColor3i) return false;
    glSecondaryColor3iv =
        (PFNGLSECONDARYCOLOR3IVPROC)VOSGLGetProcAddress(
        "glSecondaryColor3iv"
    );
    if (!glSecondaryColor3iv) return false;
    glSecondaryColor3s =
        (PFNGLSECONDARYCOLOR3SPROC)VOSGLGetProcAddress(
        "glSecondaryColor3s"
    );
    if (!glSecondaryColor3s) return false;
    glSecondaryColor3sv =
        (PFNGLSECONDARYCOLOR3SVPROC)VOSGLGetProcAddress(
        "glSecondaryColor3sv"
    );
    if (!glSecondaryColor3sv) return false;
    glSecondaryColor3ub =
        (PFNGLSECONDARYCOLOR3UBPROC)VOSGLGetProcAddress(
        "glSecondaryColor3ub"
    );
    if (!glSecondaryColor3ub) return false;
    glSecondaryColor3ubv =
        (PFNGLSECONDARYCOLOR3UBVPROC)VOSGLGetProcAddress(
        "glSecondaryColor3ubv"
    );
    if (!glSecondaryColor3ubv) return false;
    glSecondaryColor3ui =
        (PFNGLSECONDARYCOLOR3UIPROC)VOSGLGetProcAddress(
        "glSecondaryColor3ui"
    );
    if (!glSecondaryColor3ui) return false;
    glSecondaryColor3uiv =
        (PFNGLSECONDARYCOLOR3UIVPROC)VOSGLGetProcAddress(
        "glSecondaryColor3uiv"
    );
    if (!glSecondaryColor3uiv) return false;
    glSecondaryColor3us =
        (PFNGLSECONDARYCOLOR3USPROC)VOSGLGetProcAddress(
        "glSecondaryColor3us"
    );
    if (!glSecondaryColor3us) return false;
    glSecondaryColor3usv =
        (PFNGLSECONDARYCOLOR3USVPROC)VOSGLGetProcAddress(
        "glSecondaryColor3usv"
    );
    if (!glSecondaryColor3usv) return false;
    glSecondaryColorPointer =
        (PFNGLSECONDARYCOLORPOINTERPROC)VOSGLGetProcAddress(
        "glSecondaryColorPointer"
    );
    if (!glSecondaryColorPointer) return false;

    glMultiDrawArrays =
        (PFNGLMULTIDRAWARRAYSPROC)VOSGLGetProcAddress(
        "glMultiDrawArrays"
    );
    if (!glMultiDrawArrays) return false;
    glMultiDrawElements =
        (PFNGLMULTIDRAWELEMENTSPROC)VOSGLGetProcAddress(
        "glMultiDrawElements"
    );
    if (!glMultiDrawElements) return false;

    glFogCoordPointer =
        (PFNGLFOGCOORDPOINTERPROC)VOSGLGetProcAddress(
        "glFogCoordPointer"
    );
    if (!glFogCoordPointer) return false;
    glFogCoordd =
        (PFNGLFOGCOORDDPROC)VOSGLGetProcAddress(
        "glFogCoordd"
    );
    if (!glFogCoordd) return false;
    glFogCoorddv =
        (PFNGLFOGCOORDDVPROC)VOSGLGetProcAddress(
        "glFogCoorddv"
    );
    if (!glFogCoorddv) return false;
    glFogCoordf =
        (PFNGLFOGCOORDFPROC)VOSGLGetProcAddress(
        "glFogCoordf"
    );
    if (!glFogCoordf) return false;
    glFogCoordfv =
        (PFNGLFOGCOORDFVPROC)VOSGLGetProcAddress(
        "glFogCoordfv"
    );
    if (!glFogCoordfv) return false;

    // OpenGL 1.4 successfully loaded
    return true;
}
