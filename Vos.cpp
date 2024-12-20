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
m_clock(),
m_frameClock(),
m_clockTime(0.0)
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

    // Create VOS global window
    if (!GSysWindow.create())
    {
        // Unable to create VOS global window
        return false;
    }

    // Init system settings
    if (!GSysSettings.loadSettings())
    {
        // Unable to load system settings
        return false;
    }

    // Start physics solver thread
    GPhysics.start();

    // Init VOS renderer
    if (!GRenderer.init())
    {
        // Unable to init VOS renderer
        return false;
    }

    // Init VOS resources
    if (!GResources.init())
    {
        // Unable to init VOS resources
        return false;
    }

    // Preload resources
    if (!GResources.preload())
    {
        // Unable to preload resources
        return false;
    }

    // Start resources loading
    if (!GResources.startLoading())
    {
        // Unable to start resources loading
        return false;
    }


    // Wait for physics solver
    bool physicsReady = false;
    while (!physicsReady)
    {
        // Get physics solver states
        PhysicsState physicsState = GPhysics.getState();

        // Check physics solver state
        if (physicsState == PHYSICS_STATE_ERROR)
        {
            // Physics solver error
            return false;
        }

        // Check physics solver init state
        if (physicsState == PHYSICS_STATE_IDLE)
        {
            // Physics solver ready
            physicsReady = true;
        }
        else
        {
            // Release some CPU while loading
            SysSleep(PhysicsWaitSleepTime);
        }
    }


    // Wait for resources
    bool resourcesLoaded = false;
    while (!resourcesLoaded)
    {
        if (GResources.isLoadingDone())
        {
            resourcesLoaded = true;
        }
        else
        {
            // Release some CPU while loading
            SysSleep(ResourcesWaitSleepTime);
        }
    }


    // Init softwares
    if (!GSoftwares.init())
    {
        // Could not init softwares
        return false;
    }

    // Wait for renderer device idle state
    if (!GRenderer.waitDeviceIdle())
    {
        // Could not wait for renderer device idle state
        return false;
    }

    // Launch physics solver
    GPhysics.launch();

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
    // Reset clocks
    m_clock.reset();
    m_frameClock.reset();
    m_clockTime = 0.0;

    // Run VOS
    m_running = true;
    while (m_running)
    {
        // Update clock time
        m_clockTime += m_clock.getAndReset();

        // Check renderer tick
        if (m_clockTime < RendererTickTime)
        {
            // Release some CPU
            SysSleep(RendererRunSleepTime);
            continue;
        }

        // Reset renderer clock time
        m_clockTime -= RendererTickTime;
        if (m_clockTime >= RendererTickTime)
        {
            // Renderer is overloaded
            m_clockTime = 0.0;
        }

        // Get main window event
        SysEvent event;
        while (GSysWindow.getEvent(event))
        {
            // Process event
            switch (event.type)
            {
                // Close event
                case SYSEVENT_CLOSED:
                    m_running = false;
                    break;

                // Key pressed
                case SYSEVENT_KEYPRESSED:
                    GSysKeys.pressed(event.key);
                    break;

                // Key released
                case SYSEVENT_KEYRELEASED:
                    GSysKeys.released(event.key);
                    switch (event.key)
                    {
                        case SYSEVENT_KEY_ESCAPE:
                            m_running = false;
                            break;

                        default:
                            break;
                    }
                    break;

                // Mouse moved
                case SYSEVENT_MOUSEMOVED:
                    GSysMouse.move(event.mouse.x, event.mouse.y);
                    break;

                // Mouse button pressed
                case SYSEVENT_MOUSEPRESSED:
                    GSysMouse.pressed(event.mouse.button);
                    break;

                // Mouse button released
                case SYSEVENT_MOUSERELEASED:
                    GSysMouse.released(event.mouse.button);
                    break;

                // Mouse wheel
                case SYSEVENT_MOUSEWHEEL:
                    GSysMouse.mouseWheel(event.mouse.wheel);
                    break;

                default:
                    break;
            }

            // Compute events
            GSoftwares.events(event);
        }

        // Precompute
        float physicstime = GPhysics.startPrecompute();
        GSoftwares.precompute(physicstime);
        GPhysics.endPrecompute();

        // Compute logic
        GSoftwares.compute(m_frameClock.getAndResetF());

        // Render frame
        GSoftwares.render();
    }

    // Wait for renderer device idle state
    if (GRenderer.waitDeviceIdle())
    {
        // Stop physics solver thread
        GPhysics.stop();

        // Destroy softwares
        GSoftwares.destroy();

        // Destroy resources
        GResources.destroyResources();

        // Destroy renderer
        GRenderer.destroyRenderer();
    }

    // Close VOS
    GSysWindow.close();
}
