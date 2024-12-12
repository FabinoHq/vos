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
//     Physics/Physics.cpp : Physics management                               //
////////////////////////////////////////////////////////////////////////////////
#include "Physics.h"
#include "../Softwares/Softwares.h"


////////////////////////////////////////////////////////////////////////////////
//  Physics global instance                                                   //
////////////////////////////////////////////////////////////////////////////////
Physics GPhysics = Physics();


////////////////////////////////////////////////////////////////////////////////
//  Physics default constructor                                               //
////////////////////////////////////////////////////////////////////////////////
Physics::Physics() :
m_state(PHYSICS_STATE_NONE),
m_stateMutex(),
m_clock(),
m_clockTime(0.0),
m_tick(0),
m_tickMutex(),
m_mutex()
{

}

////////////////////////////////////////////////////////////////////////////////
//  Physics virtual destructor                                                //
////////////////////////////////////////////////////////////////////////////////
Physics::~Physics()
{
    m_tick = 0;
    m_clockTime = 0.0;
    m_state = PHYSICS_STATE_NONE;
}


////////////////////////////////////////////////////////////////////////////////
//  Physics solver thread process                                             //
////////////////////////////////////////////////////////////////////////////////
void Physics::process()
{
    PhysicsState state = PHYSICS_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();

    switch (state)
    {
        case PHYSICS_STATE_NONE:
            // Boot to init state
            m_stateMutex.lock();
            m_state = PHYSICS_STATE_INIT;
            m_stateMutex.unlock();
            break;

        case PHYSICS_STATE_INIT:
            // Init physics solver
            if (init())
            {
                m_stateMutex.lock();
                m_state = PHYSICS_STATE_IDLE;
                m_stateMutex.unlock();
            }
            else
            {
                m_stateMutex.lock();
                m_state = PHYSICS_STATE_ERROR;
                m_stateMutex.unlock();
            }
            break;

        case PHYSICS_STATE_IDLE:
            // Physics solver in idle state
            SysSleep(PhysicsIdleSleepTime);
            break;

        case PHYSICS_STATE_RUN:
            // Physics solver running
            run();
            break;

        case PHYSICS_STATE_ERROR:
            // Physics solver error
            SysSleep(PhysicsErrorSleepTime);
            break;

        default:
            // Invalid state
            m_stateMutex.lock();
            m_state = PHYSICS_STATE_ERROR;
            m_stateMutex.unlock();
            break;
    }
}


////////////////////////////////////////////////////////////////////////////////
//  Init physics solver                                                       //
//  return : True if the physics solver is successfully loaded                //
////////////////////////////////////////////////////////////////////////////////
bool Physics::init()
{
    // Physics solver successfully loaded
    m_tickMutex.lock();
    m_tick = 0;
    m_tickMutex.unlock();
    m_clock.reset();
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Start physics precompute                                                  //
////////////////////////////////////////////////////////////////////////////////
float Physics::startPrecompute()
{
    // Get physics clock
    m_mutex.lock();
    m_clockTime += m_clock.getAndReset();

    // Wait for pending physics tick
    while (m_clockTime >= PhysicsTickTime)
    {
        m_mutex.unlock();
        SysSleep(PhysicsPrecomputeSleepTime);
        m_mutex.lock();
        m_clockTime += m_clock.getAndReset();
    }

    // Return physics time
    return (static_cast<float>(m_clockTime*PhysicsTickRate));
}

////////////////////////////////////////////////////////////////////////////////
//  End physics precompute                                                    //
////////////////////////////////////////////////////////////////////////////////
void Physics::endPrecompute()
{
    m_mutex.unlock();
}


////////////////////////////////////////////////////////////////////////////////
//  Get physics solver state                                                  //
//  return : Current physics solver state                                     //
////////////////////////////////////////////////////////////////////////////////
PhysicsState Physics::getState()
{
    PhysicsState state = PHYSICS_STATE_NONE;
    m_stateMutex.lock();
    state = m_state;
    m_stateMutex.unlock();
    return state;
}

////////////////////////////////////////////////////////////////////////////////
//  Launch physics solver                                                     //
////////////////////////////////////////////////////////////////////////////////
bool Physics::launch()
{
    bool launched = false;
    m_stateMutex.lock();
    if (m_state == PHYSICS_STATE_IDLE)
    {
        // Reset ticks counter
        m_tickMutex.lock();
        m_tick = 0;
        m_tickMutex.unlock();

        // Run physics solver
        m_state = PHYSICS_STATE_RUN;
        m_clock.reset();
        launched = true;
    }
    m_stateMutex.unlock();
    return launched;
}

////////////////////////////////////////////////////////////////////////////////
//  Get current physics solver tick                                           //
//  return : Current physics solver tick                                      //
////////////////////////////////////////////////////////////////////////////////
int64_t Physics::getTick()
{
    int64_t tick = 0;
    m_tickMutex.lock();
    tick = m_tick;
    m_tickMutex.unlock();
    return tick;
}


////////////////////////////////////////////////////////////////////////////////
//  Run physics solver                                                        //
////////////////////////////////////////////////////////////////////////////////
void Physics::run()
{
    // Compute physics clock
    m_mutex.lock();
    m_clockTime += m_clock.getAndReset();

    // Physics tick
    if (m_clockTime >= PhysicsTickTime)
    {
        // Reset physics clock time
        m_clockTime -= PhysicsTickTime;
        if (m_clockTime >= PhysicsTickTime)
        {
            // Physics solver is overloaded
            m_clockTime = 0.0;
        }

        // Compute physics tick
        m_tickMutex.lock();
        ++m_tick;
        m_tickMutex.unlock();

        // Sync physics with renderer
        GSoftwares.prephysics();
        m_mutex.unlock();

        // Sync inputs with physics
        GSysMouse.sync();
        GSysKeys.sync();

        // Compute softwares physics
        GSoftwares.physics();
    }
    else
    {
        m_mutex.unlock();
    }

    // Release some CPU
    SysSleep(PhysicsRunSleepTime);
}
