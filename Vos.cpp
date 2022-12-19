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
m_clock(),
m_resources(),
m_game(m_renderer, m_resources),
m_pxFontTexture(),
m_pxText(),
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
    // Check system CPU
    if (!SysCPUCheck())
    {
        // Invalid system CPU
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


    // Load pixel font texture
    if (!m_pxFontTexture.updateTexture(m_renderer,
        PxFontImageWidth, PxFontImageHeight, PxFontImage,
        true, false))
    {
        // Could not load pixel font texture
        return false;
    }

    // Init test pixel text
    if (!m_pxText.init(m_pxFontTexture, 0.04f))
    {
        // Could not init test pixel text
        return false;
    }
    m_pxText.setSmooth(0.2f);
    m_pxText.setText("FPS : 0");


    // Init game
    if (!m_game.init())
    {
        // Could not init game
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
    // Framerate
    const float maxFramerate = 300.0f;
    std::ostringstream framestr;
    framestr << "FPS : 0";
    float frameavg = 0.0f;
    float framecnt = 0.0f;

    // Run VOS
    m_clock.reset();
    m_running = true;
    while (m_running)
    {
        float frametime = m_clock.getAndResetF();
        float framelimit = frametime;
        float scale = m_renderer.getScale();
        float ratio = m_renderer.getRatio();

        // Framerate limiter
        if (framelimit <= (1.0f/maxFramerate))
        {
            // Release some CPU
            float remainingTime = ((1.0f/maxFramerate) - framelimit);
            if (remainingTime >= 0.01f)
            {
                SysSleep(0.001);
            }

            // Stall to match target framerate
            framelimit += m_clock.getElapsedTimeF();
            while (framelimit <= (1.0f/maxFramerate))
            {
                framelimit = (m_clock.getElapsedTimeF()-framelimit);
            }
        }

        // Framerate display
        frameavg += frametime;
        framecnt += 1.0f;
        if ((frameavg >= 0.5f) && (framecnt >= 1.0f))
        {
            framestr.clear();
            framestr.str("");
            framestr << "FPS : " << (1.0f/(frameavg/framecnt));
            frameavg = 0.0f;
            framecnt = 0.0f;
        }

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

            // Compute events
            m_game.events(event);
        }

        // Compute logic
        m_game.compute(frametime);

        // Render frame
        if (m_renderer.startFrame())
        {
            // Render game
            m_game.render();

            // Render pixel text (framerate)
            m_renderer.bindPxTextPipeline();
            m_pxText.setText(framestr.str());
            m_pxText.setPosition(-ratio, 1.0f-(m_pxText.getHeight()*0.7f));
            m_pxText.render(m_renderer);

            // Render cursor
            //m_renderer.bindDefaultPipeline();
            //m_renderer.renderCursor(m_mouseX, m_mouseY);

            // End rendering
            m_renderer.endFrame();
        }
    }

    // Wait for renderer device idle state
    if (m_renderer.waitDeviceIdle())
    {
        // Destroy game
        m_game.destroy();

        // Destroy pixel font texture
        m_pxFontTexture.destroyTexture(m_renderer);
    }

    // Close VOS
    m_renderer.cleanup();
    m_window.close();
}
