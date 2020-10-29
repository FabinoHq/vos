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
//     Vos.cpp : VOS Main class management                                    //
////////////////////////////////////////////////////////////////////////////////
#include "Vos.h"


////////////////////////////////////////////////////////////////////////////////
//  Vos default constructor                                                   //
////////////////////////////////////////////////////////////////////////////////
Vos::Vos() :
m_running(false),
m_window(),
m_renderer(),
m_cursor()
{

}

////////////////////////////////////////////////////////////////////////////////
//  Vos destructor                                                            //
////////////////////////////////////////////////////////////////////////////////
Vos::~Vos()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Launch VOS                                                                //
//  return : True if VOS successfully started, false otherwise                //
////////////////////////////////////////////////////////////////////////////////
bool Vos::launch()
{
    // Check system memory
    if (!SysMemoryCheck())
    {
        // Invalid system memory
        return false;
    }

    // Create VOS main window
    if (!m_window.create())
    {
        // Unable to create VOS main window
        return false;
    }

    // Init VOS renderer
    if (!m_renderer.init(&m_window))
    {
        // Unable to init VOS renderer
        return false;
    }

    // Init cursor sprite
    if (!m_cursor.init(m_renderer.m_texture, 1.0f, 1.0f))
    {
        // Could not init test sprite
        return false;
    }

    // Run VOS
    run();

    // VOS successfully terminated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Run VOS                                                                   //
////////////////////////////////////////////////////////////////////////////////
void Vos::run()
{
    // Run VOS
    m_running = true;
    while (m_running)
    {
        // Get main window event
        Event event;
        while (m_window.getEvent(event))
        {
            // Process event
            switch (event.type)
            {
                case EVENT_CLOSED:
                    m_running = false;
                    break;

                case EVENT_KEYRELEASED:
                    switch (event.key)
                    {
                        case EVENT_KEY_ESCAPE:
                            m_running = false;
                            break;
                            
                        default:
                            break;
                    }

                default:
                    break;
            }
        }

        // Render frame
        if (m_renderer.startFrame())
        {
            // Get renderer aspect ratio
            float ratio = m_renderer.getRatio();

            // Draw cursor
            m_cursor.setSize(ratio*2.0f, 2.0f);
            m_cursor.setPosition(-ratio, -1.0f);
            m_cursor.render(m_renderer);

            // End rendering
            m_renderer.endFrame();
        }
    }

    // Close VOS
    m_renderer.cleanup();
    m_window.close();
}
