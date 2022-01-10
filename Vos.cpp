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
m_texture(),
m_cursor(),
m_view(),
m_camera(),
m_procsprite(),
m_rect(),
m_oval(),
m_mouseX(0.0f),
m_mouseY(0.0f)
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

    // Load cursor texture
    if (!m_texture.updateTexture(m_renderer,
        CursorImageWidth, CursorImageHeight, CursorImage))
    {
        // Could not load cursor texture
        return false;
    }

    // Init cursor sprite
    if (!m_cursor.init(m_texture, 1.0f, 1.0f))
    {
        // Could not init test sprite
        return false;
    }


    // Init view
    if (!m_view.init(m_renderer))
    {
        // Could not init view
        return false;
    }

    // Init camera
    if (!m_camera.init(m_renderer))
    {
        // Could not init camera
        return false;
    }
    m_camera.setZ(1.0f);


    // Init procedural sprite
    if (!m_procsprite.init(m_renderer, 0, 0, 1.0f, 1.0f))
    {
        // Could not init procedural sprite
        return false;
    }

    // Init rect shape
    if (!m_rect.init(1.0f, 1.0f))
    {
        // Could not init rect shape
        return false;
    }

    // Init oval shape
    if (!m_oval.init(1.0f, 1.0f))
    {
        // Could not init oval shape
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
        float scale = m_renderer.getScale();
        float ratio = m_renderer.getRatio();

        // Get main window event
        Event event;
        while (m_window.getEvent(event))
        {
            // Process event
            switch (event.type)
            {
                // Close event
                case EVENT_CLOSED:
                    m_running = false;
                    break;

                // Key pressed
                case EVENT_KEYPRESSED:
                    switch (event.key)
                    {
                        case EVENT_KEY_UP:
                            break;

                        case EVENT_KEY_DOWN:
                            break;

                        case EVENT_KEY_LEFT:
                            break;

                        case EVENT_KEY_RIGHT:
                            break;

                        default:
                            break;
                    }
                    break;

                // Key released
                case EVENT_KEYRELEASED:
                    switch (event.key)
                    {
                        case EVENT_KEY_ESCAPE:
                            m_running = false;
                            break;

                        default:
                            break;
                    }
                    break;

                // Mouse moved
                case EVENT_MOUSEMOVED:
                    m_mouseX += event.mouse.x*scale*2.0f;
                    m_mouseY -= event.mouse.y*scale*2.0f;
                    if (m_mouseX <= -ratio) { m_mouseX = -ratio; }
                    if (m_mouseX >= ratio) { m_mouseX = ratio; }
                    if (m_mouseY <= -1.0f) { m_mouseY = -1.0f; }
                    if (m_mouseY >= 1.0f) { m_mouseY = 1.0f; }
                    break;

                default:
                    break;
            }
        }

        // Compute frame
        m_view.compute(m_renderer);
        m_camera.compute(m_renderer);

        // Render frame
        if (m_renderer.startFrame())
        {
            // Get renderer aspect ratio
            float cursorSize = 64.0f*scale;
            float cursorOffset = 2.0f*scale;

            // Set camera
            //m_renderer.setCamera(m_camera);

            m_renderer.setView(m_view);

            // Draw rectangle
            m_rect.setSize(1.0f, 1.0f);
            m_rect.setPosition(-0.5f, -0.5f);
            m_rect.render(m_renderer);

            // Draw ellipse
            /*m_oval.setSize(1.0f, 1.0f);
            m_oval.setPosition(-0.5f, -0.5f);
            m_oval.render(m_renderer);*/

            // Draw procedural sprite
            /*m_procsprite.setSize(1.0f, 1.0f);
            m_procsprite.setPosition(-0.5f, -0.5f);
            m_procsprite.render(m_renderer);*/

            // Set default screen view
            m_renderer.setDefaultView();

            // Draw cursor
            m_cursor.setSize(cursorSize, cursorSize);
            m_cursor.setPosition(
                m_mouseX-cursorOffset, m_mouseY-cursorSize+cursorOffset
            );
            m_cursor.render(m_renderer);

            // End rendering
            m_renderer.endFrame();
        }
    }

    // Wait for renderer device idle state
    if (m_renderer.waitDeviceIdle())
    {
        // Destroy procedural sprite
        m_procsprite.destroyProcSprite(m_renderer);

        // Destroy cursor texture
        m_texture.destroyTexture(m_renderer);
    }

    // Close VOS
    m_renderer.cleanup();
    m_window.close();
}
