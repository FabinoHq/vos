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
//     main.cpp : Main program entry point                                    //
////////////////////////////////////////////////////////////////////////////////
#include "Vos.h"
#include <exception>


////////////////////////////////////////////////////////////////////////////////
//  Standard program entry point                                              //
//  param argc : Program arguments count                                      //
//  param argv : Program arguments vector                                     //
//  return : Main program return code                                         //
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    try
    {
        // Start VOS
        Vos vos;
        if (!vos.launch())
        {
            // VOS error occured
            SysMessage::box().display();
            return 1;
        }
    }
    catch (std::exception&)
    {
        // Standard exception occured
        SysMessage::box() << "[0x0001] Unknown error occured\n";
        SysMessage::box() << "Please restart the VOS program";
        SysMessage::box().display();
        return 1;
    }
    catch (...)
    {
        // Unknown exception occured
        SysMessage::box() << "[0x0002] Unknown error occured\n";
        SysMessage::box() << "Please restart the VOS program";
        SysMessage::box().display();
        return 1;
    }

    // Display system message if any
    SysMessage::box().display();

    // Program successfully executed
    return 0;
}
