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

PFNGLBEGINQUERYPROC glBeginQuery = 0;
PFNGLBINDBUFFERPROC glBindBuffer = 0;
PFNGLBUFFERDATAPROC glBufferData = 0;
PFNGLBUFFERSUBDATAPROC glBufferSubData = 0;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = 0;
PFNGLDELETEQUERIESPROC glDeleteQueries = 0;
PFNGLENDQUERYPROC glEndQuery = 0;
PFNGLGENBUFFERSPROC glGenBuffers = 0;
PFNGLGENQUERIESPROC glGenQueries = 0;
PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv = 0;
PFNGLGETBUFFERPOINTERVPROC glGetBufferPointerv = 0;
PFNGLGETBUFFERSUBDATAPROC glGetBufferSubData = 0;
PFNGLGETQUERYOBJECTIVPROC glGetQueryObjectiv = 0;
PFNGLGETQUERYOBJECTUIVPROC glGetQueryObjectuiv = 0;
PFNGLGETQUERYIVPROC glGetQueryiv = 0;
PFNGLISBUFFERPROC glIsBuffer = 0;
PFNGLISQUERYPROC glIsQuery = 0;
PFNGLMAPBUFFERPROC glMapBuffer = 0;
PFNGLUNMAPBUFFERPROC glUnmapBuffer = 0;

PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate = 0;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = 0;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = 0;
PFNGLDRAWBUFFERSPROC glDrawBuffers = 0;
PFNGLVERTEXATTRIB1DPROC glVertexAttrib1d = 0;
PFNGLVERTEXATTRIB1DVPROC glVertexAttrib1dv = 0;
PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f = 0;
PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv = 0;
PFNGLVERTEXATTRIB1SPROC glVertexAttrib1s = 0;
PFNGLVERTEXATTRIB1SVPROC glVertexAttrib1sv = 0;
PFNGLVERTEXATTRIB2DPROC glVertexAttrib2d = 0;
PFNGLVERTEXATTRIB2DVPROC glVertexAttrib2dv = 0;
PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f = 0;
PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv = 0;
PFNGLVERTEXATTRIB2SPROC glVertexAttrib2s = 0;
PFNGLVERTEXATTRIB2SVPROC glVertexAttrib2sv = 0;
PFNGLVERTEXATTRIB3DPROC glVertexAttrib3d = 0;
PFNGLVERTEXATTRIB3DVPROC glVertexAttrib3dv = 0;
PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f = 0;
PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv = 0;
PFNGLVERTEXATTRIB3SPROC glVertexAttrib3s = 0;
PFNGLVERTEXATTRIB3SVPROC glVertexAttrib3sv = 0;
PFNGLVERTEXATTRIB4NBVPROC glVertexAttrib4Nbv = 0;
PFNGLVERTEXATTRIB4NIVPROC glVertexAttrib4Niv = 0;
PFNGLVERTEXATTRIB4NSVPROC glVertexAttrib4Nsv = 0;
PFNGLVERTEXATTRIB4NUBPROC glVertexAttrib4Nub = 0;
PFNGLVERTEXATTRIB4NUBVPROC glVertexAttrib4Nubv = 0;
PFNGLVERTEXATTRIB4NUIVPROC glVertexAttrib4Nuiv = 0;
PFNGLVERTEXATTRIB4NUSVPROC glVertexAttrib4Nusv = 0;
PFNGLVERTEXATTRIB4BVPROC glVertexAttrib4bv = 0;
PFNGLVERTEXATTRIB4DPROC glVertexAttrib4d = 0;
PFNGLVERTEXATTRIB4DVPROC glVertexAttrib4dv = 0;
PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f = 0;
PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv = 0;
PFNGLVERTEXATTRIB4IVPROC glVertexAttrib4iv = 0;
PFNGLVERTEXATTRIB4SPROC glVertexAttrib4s = 0;
PFNGLVERTEXATTRIB4SVPROC glVertexAttrib4sv = 0;
PFNGLVERTEXATTRIB4UBVPROC glVertexAttrib4ubv = 0;
PFNGLVERTEXATTRIB4UIVPROC glVertexAttrib4uiv = 0;
PFNGLVERTEXATTRIB4USVPROC glVertexAttrib4usv = 0;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = 0;
PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv = 0;
PFNGLGETVERTEXATTRIBDVPROC glGetVertexAttribdv = 0;
PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfv = 0;
PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv = 0;
PFNGLSTENCILFUNCSEPARATEPROC glStencilFuncSeparate = 0;
PFNGLSTENCILMASKSEPARATEPROC glStencilMaskSeparate = 0;
PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate = 0;
PFNGLATTACHSHADERPROC glAttachShader = 0;
PFNGLCOMPILESHADERPROC glCompileShader = 0;
PFNGLCREATEPROGRAMPROC glCreateProgram = 0;
PFNGLCREATESHADERPROC glCreateShader = 0;
PFNGLDELETEPROGRAMPROC glDeleteProgram = 0;
PFNGLDELETESHADERPROC glDeleteShader = 0;
PFNGLDETACHSHADERPROC glDetachShader = 0;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = 0;
PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib = 0;
PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform = 0;
PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders = 0;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = 0;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = 0;
PFNGLGETPROGRAMIVPROC glGetProgramiv = 0;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = 0;
PFNGLGETSHADERSOURCEPROC glGetShaderSource = 0;
PFNGLGETSHADERIVPROC glGetShaderiv = 0;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = 0;
PFNGLGETUNIFORMFVPROC glGetUniformfv = 0;
PFNGLGETUNIFORMIVPROC glGetUniformiv = 0;
PFNGLISPROGRAMPROC glIsProgram = 0;
PFNGLISSHADERPROC glIsShader = 0;
PFNGLLINKPROGRAMPROC glLinkProgram = 0;
PFNGLSHADERSOURCEPROC glShaderSource = 0;
PFNGLUSEPROGRAMPROC glUseProgram = 0;
PFNGLVALIDATEPROGRAMPROC glValidateProgram = 0;
PFNGLUNIFORM1FPROC glUniform1f = 0;
PFNGLUNIFORM1FVPROC glUniform1fv = 0;
PFNGLUNIFORM1IPROC glUniform1i = 0;
PFNGLUNIFORM1IVPROC glUniform1iv = 0;
PFNGLUNIFORM2FPROC glUniform2f = 0;
PFNGLUNIFORM2FVPROC glUniform2fv = 0;
PFNGLUNIFORM2IPROC glUniform2i = 0;
PFNGLUNIFORM2IVPROC glUniform2iv = 0;
PFNGLUNIFORM3FPROC glUniform3f = 0;
PFNGLUNIFORM3FVPROC glUniform3fv = 0;
PFNGLUNIFORM3IPROC glUniform3i = 0;
PFNGLUNIFORM3IVPROC glUniform3iv = 0;
PFNGLUNIFORM4FPROC glUniform4f = 0;
PFNGLUNIFORM4FVPROC glUniform4fv = 0;
PFNGLUNIFORM4IPROC glUniform4i = 0;
PFNGLUNIFORM4IVPROC glUniform4iv = 0;
PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv = 0;
PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv = 0;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = 0;

PFNGLUNIFORMMATRIX2X3FVPROC glUniformMatrix2x3fv = 0;
PFNGLUNIFORMMATRIX2X4FVPROC glUniformMatrix2x4fv = 0;
PFNGLUNIFORMMATRIX3X2FVPROC glUniformMatrix3x2fv = 0;
PFNGLUNIFORMMATRIX3X4FVPROC glUniformMatrix3x4fv = 0;
PFNGLUNIFORMMATRIX4X2FVPROC glUniformMatrix4x2fv = 0;
PFNGLUNIFORMMATRIX4X3FVPROC glUniformMatrix4x3fv = 0;

PFNGLDISABLEIPROC glDisablei = 0;
PFNGLENABLEIPROC glEnablei = 0;
PFNGLISENABLEDIPROC glIsEnabledi = 0;
PFNGLGETBOOLEANI_VPROC glGetBooleani_v = 0;
PFNGLGETSTRINGIPROC glGetStringi = 0;
PFNGLCLAMPCOLORPROC glClampColor = 0;
PFNGLCOLORMASKIPROC glColorMaski = 0;
PFNGLTEXPARAMETERIIVPROC glTexParameterIiv = 0;
PFNGLTEXPARAMETERIUIVPROC glTexParameterIuiv = 0;
PFNGLGETTEXPARAMETERIIVPROC glGetTexParameterIiv = 0;
PFNGLGETTEXPARAMETERIUIVPROC glGetTexParameterIuiv = 0;
PFNGLCLEARBUFFERFIPROC glClearBufferfi = 0;
PFNGLCLEARBUFFERFVPROC glClearBufferfv = 0;
PFNGLCLEARBUFFERIVPROC glClearBufferiv = 0;
PFNGLCLEARBUFFERUIVPROC glClearBufferuiv = 0;
PFNGLBEGINCONDITIONALRENDERPROC glBeginConditionalRender = 0;
PFNGLBEGINTRANSFORMFEEDBACKPROC glBeginTransformFeedback = 0;
PFNGLBINDFRAGDATALOCATIONPROC glBindFragDataLocation = 0;
PFNGLENDCONDITIONALRENDERPROC glEndConditionalRender = 0;
PFNGLENDTRANSFORMFEEDBACKPROC glEndTransformFeedback = 0;
PFNGLGETFRAGDATALOCATIONPROC glGetFragDataLocation = 0;
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glGetTransformFeedbackVarying = 0;
PFNGLGETUNIFORMUIVPROC glGetUniformuiv = 0;
PFNGLGETVERTEXATTRIBIIVPROC glGetVertexAttribIiv = 0;
PFNGLGETVERTEXATTRIBIUIVPROC glGetVertexAttribIuiv = 0;
PFNGLTRANSFORMFEEDBACKVARYINGSPROC glTransformFeedbackVaryings = 0;
PFNGLUNIFORM1UIPROC glUniform1ui = 0;
PFNGLUNIFORM1UIVPROC glUniform1uiv = 0;
PFNGLUNIFORM2UIPROC glUniform2ui = 0;
PFNGLUNIFORM2UIVPROC glUniform2uiv = 0;
PFNGLUNIFORM3UIPROC glUniform3ui = 0;
PFNGLUNIFORM3UIVPROC glUniform3uiv = 0;
PFNGLUNIFORM4UIPROC glUniform4ui = 0;
PFNGLUNIFORM4UIVPROC glUniform4uiv = 0;
PFNGLVERTEXATTRIBI1IPROC glVertexAttribI1i = 0;
PFNGLVERTEXATTRIBI1IVPROC glVertexAttribI1iv = 0;
PFNGLVERTEXATTRIBI1UIPROC glVertexAttribI1ui = 0;
PFNGLVERTEXATTRIBI1UIVPROC glVertexAttribI1uiv = 0;
PFNGLVERTEXATTRIBI2IPROC glVertexAttribI2i = 0;
PFNGLVERTEXATTRIBI2IVPROC glVertexAttribI2iv = 0;
PFNGLVERTEXATTRIBI2UIPROC glVertexAttribI2ui = 0;
PFNGLVERTEXATTRIBI2UIVPROC glVertexAttribI2uiv = 0;
PFNGLVERTEXATTRIBI3IPROC glVertexAttribI3i = 0;
PFNGLVERTEXATTRIBI3IVPROC glVertexAttribI3iv = 0;
PFNGLVERTEXATTRIBI3UIPROC glVertexAttribI3ui = 0;
PFNGLVERTEXATTRIBI3UIVPROC glVertexAttribI3uiv = 0;
PFNGLVERTEXATTRIBI4BVPROC glVertexAttribI4bv = 0;
PFNGLVERTEXATTRIBI4IPROC glVertexAttribI4i = 0;
PFNGLVERTEXATTRIBI4IVPROC glVertexAttribI4iv = 0;
PFNGLVERTEXATTRIBI4SVPROC glVertexAttribI4sv = 0;
PFNGLVERTEXATTRIBI4UBVPROC glVertexAttribI4ubv = 0;
PFNGLVERTEXATTRIBI4UIPROC glVertexAttribI4ui = 0;
PFNGLVERTEXATTRIBI4UIVPROC glVertexAttribI4uiv = 0;
PFNGLVERTEXATTRIBI4USVPROC glVertexAttribI4usv = 0;
PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer = 0;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap = 0;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = 0;
PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer = 0;
PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer = 0;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus = 0;
PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers = 0;
PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers = 0;
PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer = 0;
PFNGLFRAMEBUFFERTEXTURE1DPROC glFramebufferTexture1D = 0;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D = 0;
PFNGLFRAMEBUFFERTEXTURE3DPROC glFramebufferTexture3D = 0;
PFNGLFRAMEBUFFERTEXTURELAYERPROC glFramebufferTextureLayer = 0;
PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = 0;
PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers = 0;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC
    glGetFramebufferAttachmentParameteriv = 0;
PFNGLGETRENDERBUFFERPARAMETERIVPROC glGetRenderbufferParameteriv = 0;
PFNGLISFRAMEBUFFERPROC glIsFramebuffer = 0;
PFNGLISRENDERBUFFERPROC glIsRenderbuffer = 0;
PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage = 0;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glRenderbufferStorageMultisample = 0;
PFNGLFLUSHMAPPEDBUFFERRANGEPROC glFlushMappedBufferRange = 0;
PFNGLMAPBUFFERRANGEPROC glMapBufferRange = 0;
PFNGLBINDBUFFERBASEPROC glBindBufferBase = 0;
PFNGLBINDBUFFERRANGEPROC glBindBufferRange = 0;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glGetActiveUniformBlockName = 0;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC glGetActiveUniformBlockiv = 0;
PFNGLGETACTIVEUNIFORMNAMEPROC glGetActiveUniformName = 0;
PFNGLGETACTIVEUNIFORMSIVPROC glGetActiveUniformsiv = 0;
PFNGLGETINTEGERI_VPROC glGetIntegeri_v = 0;
PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex = 0;
PFNGLGETUNIFORMINDICESPROC glGetUniformIndices = 0;
PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBinding = 0;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = 0;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = 0;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = 0;
PFNGLISVERTEXARRAYPROC glIsVertexArray = 0;


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

    // Init OpenGL 1.5
    if (InitOpenGL_1_5())
    {
        // OpenGL 1.5 ready
        VOSOpenGLMajorVersion = 1;
        VOSOpenGLMinorVersion = 5;
    }
    else
    {
        // Could not init OpenGL 1.5
        return false;
    }

    // Init OpenGL 2.0
    if (InitOpenGL_2_0())
    {
        // OpenGL 2.0 ready
        VOSOpenGLMajorVersion = 2;
        VOSOpenGLMinorVersion = 0;
    }
    else
    {
        // Could not init OpenGL 2.0
        return false;
    }

    // Init OpenGL 2.1
    if (InitOpenGL_2_1())
    {
        // OpenGL 2.1 ready
        VOSOpenGLMajorVersion = 2;
        VOSOpenGLMinorVersion = 1;
    }
    else
    {
        // Could not init OpenGL 2.1
        return false;
    }

    // Init OpenGL 3.0
    if (InitOpenGL_3_0())
    {
        // OpenGL 3.0 ready
        VOSOpenGLMajorVersion = 3;
        VOSOpenGLMinorVersion = 0;
    }
    else
    {
        // Could not init OpenGL 3.0
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

////////////////////////////////////////////////////////////////////////////////
//  Init OpenGL 1.5                                                           //
//  return : True if OpenGL 1.5 is successfully loaded, false otherwise       //
////////////////////////////////////////////////////////////////////////////////
bool InitOpenGL_1_5()
{
    // Init OpenGL 1.5
    glBeginQuery =
        (PFNGLBEGINQUERYPROC)VOSGLGetProcAddress(
        "glBeginQuery"
    );
    if (!glBeginQuery) return false;
    glBindBuffer =
        (PFNGLBINDBUFFERPROC)VOSGLGetProcAddress(
        "glBindBuffer"
    );
    if (!glBindBuffer) return false;
    glBufferData =
        (PFNGLBUFFERDATAPROC)VOSGLGetProcAddress(
        "glBufferData"
    );
    if (!glBufferData) return false;
    glBufferSubData =
        (PFNGLBUFFERSUBDATAPROC)VOSGLGetProcAddress(
        "glBufferSubData"
    );
    if (!glBufferSubData) return false;
    glDeleteBuffers =
        (PFNGLDELETEBUFFERSPROC)VOSGLGetProcAddress(
        "glDeleteBuffers"
    );
    if (!glDeleteBuffers) return false;
    glDeleteQueries =
        (PFNGLDELETEQUERIESPROC)VOSGLGetProcAddress(
        "glDeleteQueries"
    );
    if (!glDeleteQueries) return false;
    glEndQuery =
        (PFNGLENDQUERYPROC)VOSGLGetProcAddress(
        "glEndQuery"
    );
    if (!glEndQuery) return false;
    glGenBuffers =
        (PFNGLGENBUFFERSPROC)VOSGLGetProcAddress(
        "glGenBuffers"
    );
    if (!glGenBuffers) return false;
    glGenQueries =
        (PFNGLGENQUERIESPROC)VOSGLGetProcAddress(
        "glGenQueries"
    );
    if (!glGenQueries) return false;
    glGetBufferParameteriv =
        (PFNGLGETBUFFERPARAMETERIVPROC)VOSGLGetProcAddress(
        "glGetBufferParameteriv"
    );
    if (!glGetBufferParameteriv) return false;
    glGetBufferPointerv =
        (PFNGLGETBUFFERPOINTERVPROC)VOSGLGetProcAddress(
        "glGetBufferPointerv"
    );
    if (!glGetBufferPointerv) return false;
    glGetBufferSubData =
        (PFNGLGETBUFFERSUBDATAPROC)VOSGLGetProcAddress(
        "glGetBufferSubData"
    );
    if (!glGetBufferSubData) return false;
    glGetQueryObjectiv =
        (PFNGLGETQUERYOBJECTIVPROC)VOSGLGetProcAddress(
        "glGetQueryObjectiv"
    );
    if (!glGetQueryObjectiv) return false;
    glGetQueryObjectuiv =
        (PFNGLGETQUERYOBJECTUIVPROC)VOSGLGetProcAddress(
        "glGetQueryObjectuiv"
    );
    if (!glGetQueryObjectuiv) return false;
    glGetQueryiv =
        (PFNGLGETQUERYIVPROC)VOSGLGetProcAddress(
        "glGetQueryiv"
    );
    if (!glGetQueryiv) return false;
    glIsBuffer =
        (PFNGLISBUFFERPROC)VOSGLGetProcAddress(
        "glIsBuffer"
    );
    if (!glIsBuffer) return false;
    glIsQuery =
        (PFNGLISQUERYPROC)VOSGLGetProcAddress(
        "glIsQuery"
    );
    if (!glIsQuery) return false;
    glMapBuffer =
        (PFNGLMAPBUFFERPROC)VOSGLGetProcAddress(
        "glMapBuffer"
    );
    if (!glMapBuffer) return false;
    glUnmapBuffer =
        (PFNGLUNMAPBUFFERPROC)VOSGLGetProcAddress(
        "glUnmapBuffer"
    );
    if (!glUnmapBuffer) return false;

    // OpenGL 1.5 successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Init OpenGL 2.0                                                           //
//  return : True if OpenGL 2.0 is successfully loaded, false otherwise       //
////////////////////////////////////////////////////////////////////////////////
bool InitOpenGL_2_0()
{
    // Init OpenGL 2.0
    glBlendEquationSeparate =
        (PFNGLBLENDEQUATIONSEPARATEPROC)VOSGLGetProcAddress(
        "glBlendEquationSeparate"
    );
    if (!glBlendEquationSeparate) return false;

    glEnableVertexAttribArray =
        (PFNGLENABLEVERTEXATTRIBARRAYPROC)VOSGLGetProcAddress(
        "glEnableVertexAttribArray"
    );
    if (!glEnableVertexAttribArray) return false;
    glDisableVertexAttribArray =
        (PFNGLDISABLEVERTEXATTRIBARRAYPROC)VOSGLGetProcAddress(
        "glDisableVertexAttribArray"
    );
    if (!glDisableVertexAttribArray) return false;
    glDrawBuffers =
        (PFNGLDRAWBUFFERSPROC)VOSGLGetProcAddress(
        "glDrawBuffers"
    );
    if (!glDrawBuffers) return false;
    glVertexAttrib1d =
        (PFNGLVERTEXATTRIB1DPROC)VOSGLGetProcAddress(
        "glVertexAttrib1d"
    );
    if (!glVertexAttrib1d) return false;
    glVertexAttrib1dv =
        (PFNGLVERTEXATTRIB1DVPROC)VOSGLGetProcAddress(
        "glVertexAttrib1dv"
    );
    if (!glVertexAttrib1dv) return false;
    glVertexAttrib1f =
        (PFNGLVERTEXATTRIB1FPROC)VOSGLGetProcAddress(
        "glVertexAttrib1f"
    );
    if (!glVertexAttrib1f) return false;
    glVertexAttrib1fv =
        (PFNGLVERTEXATTRIB1FVPROC)VOSGLGetProcAddress(
        "glVertexAttrib1fv"
    );
    if (!glVertexAttrib1fv) return false;
    glVertexAttrib1s =
        (PFNGLVERTEXATTRIB1SPROC)VOSGLGetProcAddress(
        "glVertexAttrib1s"
    );
    if (!glVertexAttrib1s) return false;
    glVertexAttrib1sv =
        (PFNGLVERTEXATTRIB1SVPROC)VOSGLGetProcAddress(
        "glVertexAttrib1sv"
    );
    if (!glVertexAttrib1sv) return false;
    glVertexAttrib2d =
        (PFNGLVERTEXATTRIB2DPROC)VOSGLGetProcAddress(
        "glVertexAttrib2d"
    );
    if (!glVertexAttrib2d) return false;
    glVertexAttrib2dv =
        (PFNGLVERTEXATTRIB2DVPROC)VOSGLGetProcAddress(
        "glVertexAttrib2dv"
    );
    if (!glVertexAttrib2dv) return false;
    glVertexAttrib2f =
        (PFNGLVERTEXATTRIB2FPROC)VOSGLGetProcAddress(
        "glVertexAttrib2f"
    );
    if (!glVertexAttrib2f) return false;
    glVertexAttrib2fv =
        (PFNGLVERTEXATTRIB2FVPROC)VOSGLGetProcAddress(
        "glVertexAttrib2fv"
    );
    if (!glVertexAttrib2fv) return false;
    glVertexAttrib2s =
        (PFNGLVERTEXATTRIB2SPROC)VOSGLGetProcAddress(
        "glVertexAttrib2s"
    );
    if (!glVertexAttrib2s) return false;
    glVertexAttrib2sv =
        (PFNGLVERTEXATTRIB2SVPROC)VOSGLGetProcAddress(
        "glVertexAttrib2sv"
    );
    if (!glVertexAttrib2sv) return false;
    glVertexAttrib3d =
        (PFNGLVERTEXATTRIB3DPROC)VOSGLGetProcAddress(
        "glVertexAttrib3d"
    );
    if (!glVertexAttrib3d) return false;
    glVertexAttrib3dv =
        (PFNGLVERTEXATTRIB3DVPROC)VOSGLGetProcAddress(
        "glVertexAttrib3dv"
    );
    if (!glVertexAttrib3dv) return false;
    glVertexAttrib3f =
        (PFNGLVERTEXATTRIB3FPROC)VOSGLGetProcAddress(
        "glVertexAttrib3f"
    );
    if (!glVertexAttrib3f) return false;
    glVertexAttrib3fv =
        (PFNGLVERTEXATTRIB3FVPROC)VOSGLGetProcAddress(
        "glVertexAttrib3fv"
    );
    if (!glVertexAttrib3fv) return false;
    glVertexAttrib3s =
        (PFNGLVERTEXATTRIB3SPROC)VOSGLGetProcAddress(
        "glVertexAttrib3s"
    );
    if (!glVertexAttrib3s) return false;
    glVertexAttrib3sv =
        (PFNGLVERTEXATTRIB3SVPROC)VOSGLGetProcAddress(
        "glVertexAttrib3sv"
    );
    if (!glVertexAttrib3sv) return false;
    glVertexAttrib4Nbv =
        (PFNGLVERTEXATTRIB4NBVPROC)VOSGLGetProcAddress(
        "glVertexAttrib4Nbv"
    );
    if (!glVertexAttrib4Nbv) return false;
    glVertexAttrib4Niv =
        (PFNGLVERTEXATTRIB4NIVPROC)VOSGLGetProcAddress(
        "glVertexAttrib4Niv"
    );
    if (!glVertexAttrib4Niv) return false;
    glVertexAttrib4Nsv =
        (PFNGLVERTEXATTRIB4NSVPROC)VOSGLGetProcAddress(
        "glVertexAttrib4Nsv"
    );
    if (!glVertexAttrib4Nsv) return false;
    glVertexAttrib4Nub =
        (PFNGLVERTEXATTRIB4NUBPROC)VOSGLGetProcAddress(
        "glVertexAttrib4Nub"
    );
    if (!glVertexAttrib4Nub) return false;
    glVertexAttrib4Nubv =
        (PFNGLVERTEXATTRIB4NUBVPROC)VOSGLGetProcAddress(
        "glVertexAttrib4Nubv"
    );
    if (!glVertexAttrib4Nubv) return false;
    glVertexAttrib4Nuiv =
        (PFNGLVERTEXATTRIB4NUIVPROC)VOSGLGetProcAddress(
        "glVertexAttrib4Nuiv"
    );
    if (!glVertexAttrib4Nuiv) return false;
    glVertexAttrib4Nusv =
        (PFNGLVERTEXATTRIB4NUSVPROC)VOSGLGetProcAddress(
        "glVertexAttrib4Nusv"
    );
    if (!glVertexAttrib4Nusv) return false;
    glVertexAttrib4bv =
        (PFNGLVERTEXATTRIB4BVPROC)VOSGLGetProcAddress(
        "glVertexAttrib4bv"
    );
    if (!glVertexAttrib4bv) return false;
    glVertexAttrib4d =
        (PFNGLVERTEXATTRIB4DPROC)VOSGLGetProcAddress(
        "glVertexAttrib4d"
    );
    if (!glVertexAttrib4d) return false;
    glVertexAttrib4dv =
        (PFNGLVERTEXATTRIB4DVPROC)VOSGLGetProcAddress(
        "glVertexAttrib4dv"
    );
    if (!glVertexAttrib4dv) return false;
    glVertexAttrib4f =
        (PFNGLVERTEXATTRIB4FPROC)VOSGLGetProcAddress(
        "glVertexAttrib4f"
    );
    if (!glVertexAttrib4f) return false;
    glVertexAttrib4fv =
        (PFNGLVERTEXATTRIB4FVPROC)VOSGLGetProcAddress(
        "glVertexAttrib4fv"
    );
    if (!glVertexAttrib4fv) return false;
    glVertexAttrib4iv =
        (PFNGLVERTEXATTRIB4IVPROC)VOSGLGetProcAddress(
        "glVertexAttrib4iv"
    );
    if (!glVertexAttrib4iv) return false;
    glVertexAttrib4s =
        (PFNGLVERTEXATTRIB4SPROC)VOSGLGetProcAddress(
        "glVertexAttrib4s"
    );
    if (!glVertexAttrib4s) return false;
    glVertexAttrib4sv =
        (PFNGLVERTEXATTRIB4SVPROC)VOSGLGetProcAddress(
        "glVertexAttrib4sv"
    );
    if (!glVertexAttrib4sv) return false;
    glVertexAttrib4ubv =
        (PFNGLVERTEXATTRIB4UBVPROC)VOSGLGetProcAddress(
        "glVertexAttrib4ubv"
    );
    if (!glVertexAttrib4ubv) return false;
    glVertexAttrib4uiv =
        (PFNGLVERTEXATTRIB4UIVPROC)VOSGLGetProcAddress(
        "glVertexAttrib4uiv"
    );
    if (!glVertexAttrib4uiv) return false;
    glVertexAttrib4usv =
        (PFNGLVERTEXATTRIB4USVPROC)VOSGLGetProcAddress(
        "glVertexAttrib4usv"
    );
    if (!glVertexAttrib4usv) return false;
    glVertexAttribPointer =
        (PFNGLVERTEXATTRIBPOINTERPROC)VOSGLGetProcAddress(
        "glVertexAttribPointer"
    );
    if (!glVertexAttribPointer) return false;
    glGetVertexAttribPointerv =
        (PFNGLGETVERTEXATTRIBPOINTERVPROC)VOSGLGetProcAddress(
        "glGetVertexAttribPointerv"
    );
    if (!glGetVertexAttribPointerv) return false;
    glGetVertexAttribdv =
        (PFNGLGETVERTEXATTRIBDVPROC)VOSGLGetProcAddress(
        "glGetVertexAttribdv"
    );
    if (!glGetVertexAttribdv) return false;
    glGetVertexAttribfv =
        (PFNGLGETVERTEXATTRIBFVPROC)VOSGLGetProcAddress(
        "glGetVertexAttribfv"
    );
    if (!glGetVertexAttribfv) return false;
    glGetVertexAttribiv =
        (PFNGLGETVERTEXATTRIBIVPROC)VOSGLGetProcAddress(
        "glGetVertexAttribiv"
    );
    if (!glGetVertexAttribiv) return false;

    glStencilFuncSeparate =
        (PFNGLSTENCILFUNCSEPARATEPROC)VOSGLGetProcAddress(
        "glStencilFuncSeparate"
    );
    if (!glStencilFuncSeparate) return false;
    glStencilMaskSeparate =
        (PFNGLSTENCILMASKSEPARATEPROC)VOSGLGetProcAddress(
        "glStencilMaskSeparate"
    );
    if (!glStencilMaskSeparate) return false;
    glStencilOpSeparate =
        (PFNGLSTENCILOPSEPARATEPROC)VOSGLGetProcAddress(
        "glStencilOpSeparate"
    );
    if (!glStencilOpSeparate) return false;

    glAttachShader =
        (PFNGLATTACHSHADERPROC)VOSGLGetProcAddress(
        "glAttachShader"
    );
    if (!glAttachShader) return false;
    glCompileShader =
        (PFNGLCOMPILESHADERPROC)VOSGLGetProcAddress(
        "glCompileShader"
    );
    if (!glCompileShader) return false;
    glCreateProgram =
        (PFNGLCREATEPROGRAMPROC)VOSGLGetProcAddress(
        "glCreateProgram"
    );
    if (!glCreateProgram) return false;
    glCreateShader =
        (PFNGLCREATESHADERPROC)VOSGLGetProcAddress(
        "glCreateShader"
    );
    if (!glCreateShader) return false;
    glDeleteProgram =
        (PFNGLDELETEPROGRAMPROC)VOSGLGetProcAddress(
        "glDeleteProgram"
    );
    if (!glDeleteProgram) return false;
    glDeleteShader =
        (PFNGLDELETESHADERPROC)VOSGLGetProcAddress(
        "glDeleteShader"
    );
    if (!glDeleteShader) return false;
    glDetachShader =
        (PFNGLDETACHSHADERPROC)VOSGLGetProcAddress(
        "glDetachShader"
    );
    if (!glDetachShader) return false;
    glBindAttribLocation =
        (PFNGLBINDATTRIBLOCATIONPROC)VOSGLGetProcAddress(
        "glBindAttribLocation"
    );
    if (!glBindAttribLocation) return false;
    glGetActiveAttrib =
        (PFNGLGETACTIVEATTRIBPROC)VOSGLGetProcAddress(
        "glGetActiveAttrib"
    );
    if (!glGetActiveAttrib) return false;
    glGetActiveUniform =
        (PFNGLGETACTIVEUNIFORMPROC)VOSGLGetProcAddress(
        "glGetActiveUniform"
    );
    if (!glGetActiveUniform) return false;
    glGetAttachedShaders =
        (PFNGLGETATTACHEDSHADERSPROC)VOSGLGetProcAddress(
        "glGetAttachedShaders"
    );
    if (!glGetAttachedShaders) return false;
    glGetAttribLocation =
        (PFNGLGETATTRIBLOCATIONPROC)VOSGLGetProcAddress(
        "glGetAttribLocation"
    );
    if (!glGetAttachedShaders) return false;
    glGetProgramInfoLog =
        (PFNGLGETPROGRAMINFOLOGPROC)VOSGLGetProcAddress(
        "glGetProgramInfoLog"
    );
    if (!glGetProgramInfoLog) return false;
    glGetProgramiv =
        (PFNGLGETPROGRAMIVPROC)VOSGLGetProcAddress(
        "glGetProgramiv"
    );
    if (!glGetProgramiv) return false;
    glGetShaderInfoLog =
        (PFNGLGETSHADERINFOLOGPROC)VOSGLGetProcAddress(
        "glGetShaderInfoLog"
    );
    if (!glGetShaderInfoLog) return false;
    glGetShaderSource =
        (PFNGLGETSHADERSOURCEPROC)VOSGLGetProcAddress(
        "glGetShaderSource"
    );
    if (!glGetShaderSource) return false;
    glGetShaderiv =
        (PFNGLGETSHADERIVPROC)VOSGLGetProcAddress(
        "glGetShaderiv"
    );
    if (!glGetShaderiv) return false;
    glGetUniformLocation =
        (PFNGLGETUNIFORMLOCATIONPROC)VOSGLGetProcAddress(
        "glGetUniformLocation"
    );
    if (!glGetUniformLocation) return false;
    glGetUniformfv =
        (PFNGLGETUNIFORMFVPROC)VOSGLGetProcAddress(
        "glGetUniformfv"
    );
    if (!glGetUniformfv) return false;
    glGetUniformiv =
        (PFNGLGETUNIFORMIVPROC)VOSGLGetProcAddress(
        "glGetUniformiv"
    );
    if (!glGetUniformiv) return false;
    glIsProgram =
        (PFNGLISPROGRAMPROC)VOSGLGetProcAddress(
        "glIsProgram"
    );
    if (!glIsProgram) return false;
    glIsShader =
        (PFNGLISSHADERPROC)VOSGLGetProcAddress(
        "glIsShader"
    );
    if (!glIsShader) return false;
    glLinkProgram =
        (PFNGLLINKPROGRAMPROC)VOSGLGetProcAddress(
        "glLinkProgram"
    );
    if (!glLinkProgram) return false;
    glShaderSource =
        (PFNGLSHADERSOURCEPROC)VOSGLGetProcAddress(
        "glShaderSource"
    );
    if (!glShaderSource) return false;
    glUseProgram =
        (PFNGLUSEPROGRAMPROC)VOSGLGetProcAddress(
        "glUseProgram"
    );
    if (!glUseProgram) return false;
    glValidateProgram =
        (PFNGLVALIDATEPROGRAMPROC)VOSGLGetProcAddress(
        "glValidateProgram"
    );
    if (!glValidateProgram) return false;
    glUniform1f =
        (PFNGLUNIFORM1FPROC)VOSGLGetProcAddress(
        "glUniform1f"
    );
    if (!glUniform1f) return false;
    glUniform1fv =
        (PFNGLUNIFORM1FVPROC)VOSGLGetProcAddress(
        "glUniform1fv"
    );
    if (!glUniform1fv) return false;
    glUniform1i =
        (PFNGLUNIFORM1IPROC)VOSGLGetProcAddress(
        "glUniform1i"
    );
    if (!glUniform1i) return false;
    glUniform1iv =
        (PFNGLUNIFORM1IVPROC)VOSGLGetProcAddress(
        "glUniform1iv"
    );
    if (!glUniform1iv) return false;
    glUniform2f =
        (PFNGLUNIFORM2FPROC)VOSGLGetProcAddress(
        "glUniform2f"
    );
    if (!glUniform2f) return false;
    glUniform2fv =
        (PFNGLUNIFORM2FVPROC)VOSGLGetProcAddress(
        "glUniform2fv"
    );
    if (!glUniform2fv) return false;
    glUniform2i =
        (PFNGLUNIFORM2IPROC)VOSGLGetProcAddress(
        "glUniform2i"
    );
    if (!glUniform2i) return false;
    glUniform2iv =
        (PFNGLUNIFORM2IVPROC)VOSGLGetProcAddress(
        "glUniform2iv"
    );
    if (!glUniform2iv) return false;
    glUniform3f =
        (PFNGLUNIFORM3FPROC)VOSGLGetProcAddress(
        "glUniform3f"
    );
    if (!glUniform3f) return false;
    glUniform3fv =
        (PFNGLUNIFORM3FVPROC)VOSGLGetProcAddress(
        "glUniform3fv"
    );
    if (!glUniform3fv) return false;
    glUniform3i =
        (PFNGLUNIFORM3IPROC)VOSGLGetProcAddress(
        "glUniform3i"
    );
    if (!glUniform3i) return false;
    glUniform3iv =
        (PFNGLUNIFORM3IVPROC)VOSGLGetProcAddress(
        "glUniform3iv"
    );
    if (!glUniform3iv) return false;
    glUniform4f =
        (PFNGLUNIFORM4FPROC)VOSGLGetProcAddress(
        "glUniform4f"
    );
    if (!glUniform4f) return false;
    glUniform4fv =
        (PFNGLUNIFORM4FVPROC)VOSGLGetProcAddress(
        "glUniform4fv"
    );
    if (!glUniform4fv) return false;
    glUniform4i =
        (PFNGLUNIFORM4IPROC)VOSGLGetProcAddress(
        "glUniform4i"
    );
    if (!glUniform4i) return false;
    glUniform4iv =
        (PFNGLUNIFORM4IVPROC)VOSGLGetProcAddress(
        "glUniform4iv"
    );
    if (!glUniform4iv) return false;
    glUniformMatrix2fv =
        (PFNGLUNIFORMMATRIX2FVPROC)VOSGLGetProcAddress(
        "glUniformMatrix2fv"
    );
    if (!glUniformMatrix2fv) return false;
    glUniformMatrix3fv =
        (PFNGLUNIFORMMATRIX3FVPROC)VOSGLGetProcAddress(
        "glUniformMatrix3fv"
    );
    if (!glUniformMatrix3fv) return false;
    glUniformMatrix4fv =
        (PFNGLUNIFORMMATRIX4FVPROC)VOSGLGetProcAddress(
        "glUniformMatrix4fv"
    );
    if (!glUniformMatrix4fv) return false;

    // OpenGL 2.0 successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Init OpenGL 2.1                                                           //
//  return : True if OpenGL 2.1 is successfully loaded, false otherwise       //
////////////////////////////////////////////////////////////////////////////////
bool InitOpenGL_2_1()
{
    // Init OpenGL 2.1
    glUniformMatrix2x3fv =
        (PFNGLUNIFORMMATRIX2X3FVPROC)VOSGLGetProcAddress(
        "glUniformMatrix2x3fv"
    );
    if (!glUniformMatrix2x3fv) return false;
    glUniformMatrix2x4fv =
        (PFNGLUNIFORMMATRIX2X4FVPROC)VOSGLGetProcAddress(
        "glUniformMatrix2x4fv"
    );
    if (!glUniformMatrix2x4fv) return false;
    glUniformMatrix3x2fv =
        (PFNGLUNIFORMMATRIX3X2FVPROC)VOSGLGetProcAddress(
        "glUniformMatrix3x2fv"
    );
    if (!glUniformMatrix3x2fv) return false;
    glUniformMatrix3x4fv =
        (PFNGLUNIFORMMATRIX3X4FVPROC)VOSGLGetProcAddress(
        "glUniformMatrix3x4fv"
    );
    if (!glUniformMatrix3x4fv) return false;
    glUniformMatrix4x2fv =
        (PFNGLUNIFORMMATRIX4X2FVPROC)VOSGLGetProcAddress(
        "glUniformMatrix4x2fv"
    );
    if (!glUniformMatrix4x2fv) return false;
    glUniformMatrix4x3fv =
        (PFNGLUNIFORMMATRIX4X3FVPROC)VOSGLGetProcAddress(
        "glUniformMatrix4x3fv"
    );
    if (!glUniformMatrix4x3fv) return false;

    // OpenGL 2.1 successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Init OpenGL 3.0                                                           //
//  return : True if OpenGL 3.0 is successfully loaded, false otherwise       //
////////////////////////////////////////////////////////////////////////////////
bool InitOpenGL_3_0()
{
    // Init OpenGL 3.0
    glDisablei =
        (PFNGLDISABLEIPROC)VOSGLGetProcAddress(
        "glDisablei"
    );
    if (!glDisablei) return false;
    glEnablei =
        (PFNGLENABLEIPROC)VOSGLGetProcAddress(
        "glEnablei"
    );
    if (!glEnablei) return false;
    glIsEnabledi =
        (PFNGLISENABLEDIPROC)VOSGLGetProcAddress(
        "glIsEnabledi"
    );
    if (!glIsEnabledi) return false;
    glGetBooleani_v =
        (PFNGLGETBOOLEANI_VPROC)VOSGLGetProcAddress(
        "glGetBooleani_v"
    );
    if (!glGetBooleani_v) return false;
    glGetStringi =
        (PFNGLGETSTRINGIPROC)VOSGLGetProcAddress(
        "glGetStringi"
    );
    if (!glGetStringi) return false;
    glClampColor =
        (PFNGLCLAMPCOLORPROC)VOSGLGetProcAddress(
        "glClampColor"
    );
    if (!glClampColor) return false;
    glColorMaski =
        (PFNGLCOLORMASKIPROC)VOSGLGetProcAddress(
        "glColorMaski"
    );
    if (!glColorMaski) return false;

    glTexParameterIiv =
        (PFNGLTEXPARAMETERIIVPROC)VOSGLGetProcAddress(
        "glTexParameterIiv"
    );
    if (!glTexParameterIiv) return false;
    glTexParameterIuiv =
        (PFNGLTEXPARAMETERIUIVPROC)VOSGLGetProcAddress(
        "glTexParameterIuiv"
    );
    if (!glTexParameterIuiv) return false;
    glGetTexParameterIiv =
        (PFNGLGETTEXPARAMETERIIVPROC)VOSGLGetProcAddress(
        "glGetTexParameterIiv"
    );
    if (!glGetTexParameterIiv) return false;
    glGetTexParameterIuiv =
        (PFNGLGETTEXPARAMETERIUIVPROC)VOSGLGetProcAddress(
        "glGetTexParameterIuiv"
    );
    if (!glGetTexParameterIuiv) return false;

    glClearBufferfi =
        (PFNGLCLEARBUFFERFIPROC)VOSGLGetProcAddress(
        "glClearBufferfi"
    );
    if (!glClearBufferfi) return false;
    glClearBufferfv =
        (PFNGLCLEARBUFFERFVPROC)VOSGLGetProcAddress(
        "glClearBufferfv"
    );
    if (!glClearBufferfv) return false;
    glClearBufferiv =
        (PFNGLCLEARBUFFERIVPROC)VOSGLGetProcAddress(
        "glClearBufferiv"
    );
    if (!glClearBufferiv) return false;
    glClearBufferuiv =
        (PFNGLCLEARBUFFERUIVPROC)VOSGLGetProcAddress(
        "glClearBufferuiv"
    );
    if (!glClearBufferuiv) return false;

    glBeginConditionalRender =
        (PFNGLBEGINCONDITIONALRENDERPROC)VOSGLGetProcAddress(
        "glBeginConditionalRender"
    );
    if (!glBeginConditionalRender) return false;
    glBeginTransformFeedback =
        (PFNGLBEGINTRANSFORMFEEDBACKPROC)VOSGLGetProcAddress(
        "glBeginTransformFeedback"
    );
    if (!glBeginTransformFeedback) return false;
    glBindFragDataLocation =
        (PFNGLBINDFRAGDATALOCATIONPROC)VOSGLGetProcAddress(
        "glBindFragDataLocation"
    );
    if (!glBindFragDataLocation) return false;
    glEndConditionalRender =
        (PFNGLENDCONDITIONALRENDERPROC)VOSGLGetProcAddress(
        "glEndConditionalRender"
    );
    if (!glEndConditionalRender) return false;
    glEndTransformFeedback =
        (PFNGLENDTRANSFORMFEEDBACKPROC)VOSGLGetProcAddress(
        "glEndTransformFeedback"
    );
    if (!glEndTransformFeedback) return false;
    glGetFragDataLocation =
        (PFNGLGETFRAGDATALOCATIONPROC)VOSGLGetProcAddress(
        "glGetFragDataLocation"
    );
    if (!glGetFragDataLocation) return false;
    glGetTransformFeedbackVarying =
        (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)VOSGLGetProcAddress(
        "glGetTransformFeedbackVarying"
    );
    if (!glGetTransformFeedbackVarying) return false;
    glGetUniformuiv =
        (PFNGLGETUNIFORMUIVPROC)VOSGLGetProcAddress(
        "glGetUniformuiv"
    );
    if (!glGetUniformuiv) return false;
    glGetVertexAttribIiv =
        (PFNGLGETVERTEXATTRIBIIVPROC)VOSGLGetProcAddress(
        "glGetVertexAttribIiv"
    );
    if (!glGetVertexAttribIiv) return false;
    glGetVertexAttribIuiv =
        (PFNGLGETVERTEXATTRIBIUIVPROC)VOSGLGetProcAddress(
        "glGetVertexAttribIuiv"
    );
    if (!glGetVertexAttribIuiv) return false;
    glTransformFeedbackVaryings =
        (PFNGLTRANSFORMFEEDBACKVARYINGSPROC)VOSGLGetProcAddress(
        "glTransformFeedbackVaryings"
    );
    if (!glTransformFeedbackVaryings) return false;
    glUniform1ui =
        (PFNGLUNIFORM1UIPROC)VOSGLGetProcAddress(
        "glUniform1ui"
    );
    if (!glUniform1ui) return false;
    glUniform1uiv =
        (PFNGLUNIFORM1UIVPROC)VOSGLGetProcAddress(
        "glUniform1uiv"
    );
    if (!glUniform1uiv) return false;
    glUniform2ui =
        (PFNGLUNIFORM2UIPROC)VOSGLGetProcAddress(
        "glUniform2ui"
    );
    if (!glUniform2ui) return false;
    glUniform2uiv =
        (PFNGLUNIFORM2UIVPROC)VOSGLGetProcAddress(
        "glUniform2uiv"
    );
    if (!glUniform2uiv) return false;
    glUniform3ui =
        (PFNGLUNIFORM3UIPROC)VOSGLGetProcAddress(
        "glUniform3ui"
    );
    if (!glUniform3ui) return false;
    glUniform3uiv =
        (PFNGLUNIFORM3UIVPROC)VOSGLGetProcAddress(
        "glUniform3uiv"
    );
    if (!glUniform3uiv) return false;
    glUniform4ui =
        (PFNGLUNIFORM4UIPROC)VOSGLGetProcAddress(
        "glUniform4ui"
    );
    if (!glUniform4ui) return false;
    glUniform4uiv =
        (PFNGLUNIFORM4UIVPROC)VOSGLGetProcAddress(
        "glUniform4uiv"
    );
    if (!glUniform4uiv) return false;
    glVertexAttribI1i =
        (PFNGLVERTEXATTRIBI1IPROC)VOSGLGetProcAddress(
        "glVertexAttribI1i"
    );
    if (!glVertexAttribI1i) return false;
    glVertexAttribI1iv =
        (PFNGLVERTEXATTRIBI1IVPROC)VOSGLGetProcAddress(
        "glVertexAttribI1iv"
    );
    if (!glVertexAttribI1iv) return false;
    glVertexAttribI1ui =
        (PFNGLVERTEXATTRIBI1UIPROC)VOSGLGetProcAddress(
        "glVertexAttribI1ui"
    );
    if (!glVertexAttribI1ui) return false;
    glVertexAttribI1uiv =
        (PFNGLVERTEXATTRIBI1UIVPROC)VOSGLGetProcAddress(
        "glVertexAttribI1uiv"
    );
    if (!glVertexAttribI1uiv) return false;
    glVertexAttribI2i =
        (PFNGLVERTEXATTRIBI2IPROC)VOSGLGetProcAddress(
        "glVertexAttribI2i"
    );
    if (!glVertexAttribI2i) return false;
    glVertexAttribI2iv =
        (PFNGLVERTEXATTRIBI2IVPROC)VOSGLGetProcAddress(
        "glVertexAttribI2iv"
    );
    if (!glVertexAttribI2iv) return false;
    glVertexAttribI2ui =
        (PFNGLVERTEXATTRIBI2UIPROC)VOSGLGetProcAddress(
        "glVertexAttribI2ui"
    );
    if (!glVertexAttribI2ui) return false;
    glVertexAttribI2uiv =
        (PFNGLVERTEXATTRIBI2UIVPROC)VOSGLGetProcAddress(
        "glVertexAttribI2uiv"
    );
    if (!glVertexAttribI2uiv) return false;
    glVertexAttribI3i =
        (PFNGLVERTEXATTRIBI3IPROC)VOSGLGetProcAddress(
        "glVertexAttribI3i"
    );
    if (!glVertexAttribI3i) return false;
    glVertexAttribI3iv =
        (PFNGLVERTEXATTRIBI3IVPROC)VOSGLGetProcAddress(
        "glVertexAttribI3iv"
    );
    if (!glVertexAttribI3iv) return false;
    glVertexAttribI3ui =
        (PFNGLVERTEXATTRIBI3UIPROC)VOSGLGetProcAddress(
        "glVertexAttribI3ui"
    );
    if (!glVertexAttribI3ui) return false;
    glVertexAttribI3uiv =
        (PFNGLVERTEXATTRIBI3UIVPROC)VOSGLGetProcAddress(
        "glVertexAttribI3uiv"
    );
    if (!glVertexAttribI3uiv) return false;
    glVertexAttribI4bv =
        (PFNGLVERTEXATTRIBI4BVPROC)VOSGLGetProcAddress(
        "glVertexAttribI4bv"
    );
    if (!glVertexAttribI4bv) return false;
    glVertexAttribI4i =
        (PFNGLVERTEXATTRIBI4IPROC)VOSGLGetProcAddress(
        "glVertexAttribI4i"
    );
    if (!glVertexAttribI4i) return false;
    glVertexAttribI4iv =
        (PFNGLVERTEXATTRIBI4IVPROC)VOSGLGetProcAddress(
        "glVertexAttribI4iv"
    );
    if (!glVertexAttribI4iv) return false;
    glVertexAttribI4sv =
        (PFNGLVERTEXATTRIBI4SVPROC)VOSGLGetProcAddress(
        "glVertexAttribI4sv"
    );
    if (!glVertexAttribI4sv) return false;
    glVertexAttribI4ubv =
        (PFNGLVERTEXATTRIBI4UBVPROC)VOSGLGetProcAddress(
        "glVertexAttribI4ubv"
    );
    if (!glVertexAttribI4ubv) return false;
    glVertexAttribI4ui =
        (PFNGLVERTEXATTRIBI4UIPROC)VOSGLGetProcAddress(
        "glVertexAttribI4ui"
    );
    if (!glVertexAttribI4ui) return false;
    glVertexAttribI4uiv =
        (PFNGLVERTEXATTRIBI4UIVPROC)VOSGLGetProcAddress(
        "glVertexAttribI4uiv"
    );
    if (!glVertexAttribI4uiv) return false;
    glVertexAttribI4usv =
        (PFNGLVERTEXATTRIBI4USVPROC)VOSGLGetProcAddress(
        "glVertexAttribI4usv"
    );
    if (!glVertexAttribI4usv) return false;
    glVertexAttribIPointer =
        (PFNGLVERTEXATTRIBIPOINTERPROC)VOSGLGetProcAddress(
        "glVertexAttribIPointer"
    );
    if (!glVertexAttribIPointer) return false;

    glGenerateMipmap =
        (PFNGLGENERATEMIPMAPPROC)VOSGLGetProcAddress(
        "glGenerateMipmap"
    );
    if (!glGenerateMipmap) return false;

    glBindFramebuffer =
        (PFNGLBINDFRAMEBUFFERPROC)VOSGLGetProcAddress(
        "glBindFramebuffer"
    );
    if (!glBindFramebuffer) return false;
    glBindRenderbuffer =
        (PFNGLBINDRENDERBUFFERPROC)VOSGLGetProcAddress(
        "glBindRenderbuffer"
    );
    if (!glBindRenderbuffer) return false;
    glBlitFramebuffer =
        (PFNGLBLITFRAMEBUFFERPROC)VOSGLGetProcAddress(
        "glBlitFramebuffer"
    );
    if (!glBlitFramebuffer) return false;
    glCheckFramebufferStatus =
        (PFNGLCHECKFRAMEBUFFERSTATUSPROC)VOSGLGetProcAddress(
        "glCheckFramebufferStatus"
    );
    if (!glCheckFramebufferStatus) return false;
    glDeleteFramebuffers =
        (PFNGLDELETEFRAMEBUFFERSPROC)VOSGLGetProcAddress(
        "glDeleteFramebuffers"
    );
    if (!glDeleteFramebuffers) return false;
    glDeleteRenderbuffers =
        (PFNGLDELETERENDERBUFFERSPROC)VOSGLGetProcAddress(
        "glDeleteRenderbuffers"
    );
    if (!glDeleteRenderbuffers) return false;
    glFramebufferRenderbuffer =
        (PFNGLFRAMEBUFFERRENDERBUFFERPROC)VOSGLGetProcAddress(
        "glFramebufferRenderbuffer"
    );
    if (!glFramebufferRenderbuffer) return false;
    glFramebufferTexture1D =
        (PFNGLFRAMEBUFFERTEXTURE1DPROC)VOSGLGetProcAddress(
        "glFramebufferTexture1D"
    );
    if (!glFramebufferTexture1D) return false;
    glFramebufferTexture2D =
        (PFNGLFRAMEBUFFERTEXTURE2DPROC)VOSGLGetProcAddress(
        "glFramebufferTexture2D"
    );
    if (!glFramebufferTexture2D) return false;
    glFramebufferTexture3D =
        (PFNGLFRAMEBUFFERTEXTURE3DPROC)VOSGLGetProcAddress(
        "glFramebufferTexture3D"
    );
    if (!glFramebufferTexture3D) return false;
    glFramebufferTextureLayer =
        (PFNGLFRAMEBUFFERTEXTURELAYERPROC)VOSGLGetProcAddress(
        "glFramebufferTextureLayer"
    );
    if (!glFramebufferTextureLayer) return false;
    glGenFramebuffers =
        (PFNGLGENFRAMEBUFFERSPROC)VOSGLGetProcAddress(
        "glGenFramebuffers"
    );
    if (!glGenFramebuffers) return false;
    glGenRenderbuffers =
        (PFNGLGENRENDERBUFFERSPROC)VOSGLGetProcAddress(
        "glGenRenderbuffers"
    );
    if (!glGenRenderbuffers) return false;
    glGetFramebufferAttachmentParameteriv =
        (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)VOSGLGetProcAddress(
        "glGetFramebufferAttachmentParameteriv"
    );
    if (!glGetFramebufferAttachmentParameteriv) return false;
    glGetRenderbufferParameteriv =
        (PFNGLGETRENDERBUFFERPARAMETERIVPROC)VOSGLGetProcAddress(
        "glGetRenderbufferParameteriv"
    );
    if (!glGetRenderbufferParameteriv) return false;
    glIsFramebuffer =
        (PFNGLISFRAMEBUFFERPROC)VOSGLGetProcAddress(
        "glIsFramebuffer"
    );
    if (!glIsFramebuffer) return false;
    glIsRenderbuffer =
        (PFNGLISRENDERBUFFERPROC)VOSGLGetProcAddress(
        "glIsRenderbuffer"
    );
    if (!glIsRenderbuffer) return false;
    glRenderbufferStorage =
        (PFNGLRENDERBUFFERSTORAGEPROC)VOSGLGetProcAddress(
        "glRenderbufferStorage"
    );
    if (!glRenderbufferStorage) return false;
    glRenderbufferStorageMultisample =
        (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)VOSGLGetProcAddress(
        "glRenderbufferStorageMultisample"
    );
    if (!glRenderbufferStorageMultisample) return false;

    glFlushMappedBufferRange =
        (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)VOSGLGetProcAddress(
        "glFlushMappedBufferRange"
    );
    if (!glFlushMappedBufferRange) return false;
    glMapBufferRange =
        (PFNGLMAPBUFFERRANGEPROC)VOSGLGetProcAddress(
        "glMapBufferRange"
    );
    if (!glMapBufferRange) return false;

    glBindBufferBase =
        (PFNGLBINDBUFFERBASEPROC)VOSGLGetProcAddress(
        "glBindBufferBase"
    );
    if (!glBindBufferBase) return false;
    glBindBufferRange =
        (PFNGLBINDBUFFERRANGEPROC)VOSGLGetProcAddress(
        "glBindBufferRange"
    );
    if (!glBindBufferRange) return false;

    glGetActiveUniformBlockName =
        (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)VOSGLGetProcAddress(
        "glGetActiveUniformBlockName"
    );
    if (!glGetActiveUniformBlockName) return false;
    glGetActiveUniformBlockiv =
        (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)VOSGLGetProcAddress(
        "glGetActiveUniformBlockiv"
    );
    if (!glGetActiveUniformBlockiv) return false;
    glGetActiveUniformName =
        (PFNGLGETACTIVEUNIFORMNAMEPROC)VOSGLGetProcAddress(
        "glGetActiveUniformName"
    );
    if (!glGetActiveUniformName) return false;
    glGetActiveUniformsiv =
        (PFNGLGETACTIVEUNIFORMSIVPROC)VOSGLGetProcAddress(
        "glGetActiveUniformsiv"
    );
    if (!glGetActiveUniformsiv) return false;
    glGetIntegeri_v =
        (PFNGLGETINTEGERI_VPROC)VOSGLGetProcAddress(
        "glGetIntegeri_v"
    );
    if (!glGetIntegeri_v) return false;
    glGetUniformBlockIndex =
        (PFNGLGETUNIFORMBLOCKINDEXPROC)VOSGLGetProcAddress(
        "glGetUniformBlockIndex"
    );
    if (!glGetUniformBlockIndex) return false;
    glGetUniformIndices =
        (PFNGLGETUNIFORMINDICESPROC)VOSGLGetProcAddress(
        "glGetUniformIndices"
    );
    if (!glGetUniformIndices) return false;
    glUniformBlockBinding =
        (PFNGLUNIFORMBLOCKBINDINGPROC)VOSGLGetProcAddress(
        "glUniformBlockBinding"
    );
    if (!glUniformBlockBinding) return false;

    glBindVertexArray =
        (PFNGLBINDVERTEXARRAYPROC)VOSGLGetProcAddress(
        "glBindVertexArray"
    );
    if (!glBindVertexArray) return false;
    glDeleteVertexArrays =
        (PFNGLDELETEVERTEXARRAYSPROC)VOSGLGetProcAddress(
        "glDeleteVertexArrays"
    );
    if (!glDeleteVertexArrays) return false;
    glGenVertexArrays =
        (PFNGLGENVERTEXARRAYSPROC)VOSGLGetProcAddress(
        "glGenVertexArrays"
    );
    if (!glGenVertexArrays) return false;
    glIsVertexArray =
        (PFNGLISVERTEXARRAYPROC)VOSGLGetProcAddress(
        "glIsVertexArray"
    );
    if (!glIsVertexArray) return false;

    // OpenGL 3.0 successfully loaded
    return true;
}
