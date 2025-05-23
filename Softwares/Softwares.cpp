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
//     Softwares/Softwares.cpp : Softwares management                         //
////////////////////////////////////////////////////////////////////////////////
#include "Softwares.h"


////////////////////////////////////////////////////////////////////////////////
//  Softwares global instance                                                 //
////////////////////////////////////////////////////////////////////////////////
Softwares GSoftwares = Softwares();


////////////////////////////////////////////////////////////////////////////////
//  Softwares default constructor                                             //
////////////////////////////////////////////////////////////////////////////////
Softwares::Softwares()
{

}

////////////////////////////////////////////////////////////////////////////////
//  Softwares destructor                                                      //
////////////////////////////////////////////////////////////////////////////////
Softwares::~Softwares()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Init Softwares                                                            //
//  return : True if softwares are ready, false otherwise                     //
////////////////////////////////////////////////////////////////////////////////
bool Softwares::init()
{
    // Init top down game
    /*if (!GTopDown.init())
    {
        // Could not init top down game
        return false;
    }*/

    // Init isometric game
    if (!GIsometric.init())
    {
        // Could not init isometric game
        return false;
    }

    // Init first person game
    /*if (!GFirstPerson.init())
    {
        // Could not init first person game
        return false;
    }*/

    // Softwares are ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy softwares                                                         //
////////////////////////////////////////////////////////////////////////////////
void Softwares::destroy()
{
    // Destroy softwares
    //GTopDown.destroy();
    GIsometric.destroy();
    //GFirstPerson.destroy();
}


////////////////////////////////////////////////////////////////////////////////
//  Compute softwares events                                                  //
////////////////////////////////////////////////////////////////////////////////
void Softwares::events(SysEvent& event)
{
    // Dispatch events to softwares
    //GTopDown.events(event);
    GIsometric.events(event);
    //GFirstPerson.events(event);
}

////////////////////////////////////////////////////////////////////////////////
//  Precompute softwares physics (thread sync)                                //
////////////////////////////////////////////////////////////////////////////////
void Softwares::prephysics()
{
    // Precompute softwares physics
    //GTopDown.prephysics();
    GIsometric.prephysics();
    //GFirstPerson.prephysics();
}

////////////////////////////////////////////////////////////////////////////////
//  Compute softwares physics (threaded)                                      //
////////////////////////////////////////////////////////////////////////////////
void Softwares::physics()
{
    // Compute softwares physics
    //GTopDown.physics();
    GIsometric.physics();
    //GFirstPerson.physics();
}

////////////////////////////////////////////////////////////////////////////////
//  Precompute softwares renderer interpolations                              //
////////////////////////////////////////////////////////////////////////////////
void Softwares::precompute(float physicstime)
{
    // Precompute softwares
    //GTopDown.precompute(physicstime);
    GIsometric.precompute(physicstime);
    //GFirstPerson.precompute(physicstime);
}

////////////////////////////////////////////////////////////////////////////////
//  Compute softwares logic                                                   //
////////////////////////////////////////////////////////////////////////////////
void Softwares::compute(float frametime)
{
    // Compute softwares logic
    //GTopDown.compute(frametime);
    GIsometric.compute(frametime);
    //GFirstPerson.compute(frametime);
}

////////////////////////////////////////////////////////////////////////////////
//  Render softwares                                                          //
////////////////////////////////////////////////////////////////////////////////
void Softwares::render()
{
    // Render softwares
    //GTopDown.render();
    GIsometric.render();
    //GFirstPerson.render();
}
