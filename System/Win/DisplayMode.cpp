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
//     Win/DisplayMode.cpp : DisplayMode management for Windows               //
////////////////////////////////////////////////////////////////////////////////
#include "DisplayMode.h"


////////////////////////////////////////////////////////////////////////////////
//  DisplayMode default constructor                                           //
////////////////////////////////////////////////////////////////////////////////
DisplayMode::DisplayMode() :
m_width(0),
m_height(0),
m_depth(0)
{
    
}

////////////////////////////////////////////////////////////////////////////////
//  DisplayMode destructor                                                    //
////////////////////////////////////////////////////////////////////////////////
DisplayMode::~DisplayMode()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Get current system desktop mode                                           //
//  return : True if the desktop mode is reached, false otherwise             //
////////////////////////////////////////////////////////////////////////////////
bool DisplayMode::getSystemMode()
{
    // Get system desktop configuration
    DEVMODE desktopMode = { 0 };
    desktopMode.dmSize = sizeof(desktopMode);
    desktopMode.dmDriverExtra = 0;
    if (EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &desktopMode))
    {
        // Check desktop mode validity
        if ((desktopMode.dmPelsWidth > 0) &&
            (desktopMode.dmPelsHeight > 0) &&
            (desktopMode.dmBitsPerPel > 0))
        {
            // Copy desktop mode
            m_width = desktopMode.dmPelsWidth;
            m_height = desktopMode.dmPelsHeight;
            m_depth = desktopMode.dmBitsPerPel;
            return true;
        }
    }
    return false;
}


////////////////////////////////////////////////////////////////////////////////
//  Get DisplayMode width in pixels                                           //
//  return : Display mode width                                               //
////////////////////////////////////////////////////////////////////////////////
int DisplayMode::getWidth() const
{
    return m_width;
}

////////////////////////////////////////////////////////////////////////////////
//  Get DisplayMode height in pixels                                          //
//  return : Display mode height                                              //
////////////////////////////////////////////////////////////////////////////////
int DisplayMode::getHeight() const
{
    return m_height;
}

////////////////////////////////////////////////////////////////////////////////
//  Get DisplayMode pixel depth in bits per pixel                             //
//  return : Display mode pixel depth                                         //
////////////////////////////////////////////////////////////////////////////////
int DisplayMode::getDepth() const
{
    return m_depth;
}
