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
m_clock(),
m_cursorTexture(),
m_cursor(),
m_view(),
m_camera(),
m_freeflycam(),
m_procSprite(),
m_rect(),
m_oval(),
m_pxFontTexture(),
m_pxText(),
m_testTexture(),
m_staticMesh(),
m_heightMapChunk(),
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
    if (!m_cursorTexture.updateTexture(m_renderer,
        CursorImageWidth, CursorImageHeight, CursorImage))
    {
        // Could not load cursor texture
        return false;
    }

    // Init cursor sprite
    if (!m_cursor.init(m_cursorTexture, 1.0f, 1.0f))
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

    // Init freefly camera
    if (!m_freeflycam.init(m_renderer))
    {
        // Could not init freefly camera
        return false;
    }
    m_freeflycam.setZ(1.0f);
    m_freeflycam.setSpeed(5.0f);


    // Init procedural sprite
    if (!m_procSprite.init(m_renderer, 0, 0, 1.0f, 1.0f))
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

    // Load pixel font texture
    if (!m_pxFontTexture.updateTexture(m_renderer,
        PxFontImageWidth, PxFontImageHeight, PxFontImage))
    {
        // Could not load pixel font texture
        return false;
    }

    // Init test pixel text
    if (!m_pxText.init(m_pxFontTexture, 2.0f, 1.0f))
    {
        // Could not init test pixel text
        return false;
    }


    // Load test texture
    PNGFile pngfile;
    if (!pngfile.loadImage("Textures/testsprite.png"))
    {
        return false;
    }
    if (!m_testTexture.updateTexture(m_renderer,
        pngfile.getWidth(), pngfile.getHeight(), pngfile.getImage(),
        false, true))
    {
        return false;
    }
    pngfile.destroyImage();

    // Init static mesh
    if (!m_staticMesh.loadVMSH(
        m_renderer, m_testTexture, "Models/testmodel.vmsh"))
    {
        // Could not init static mesh
        return false;
    }

    // Allocate heightmap data
    float* heightmap = 0;
    try
    {
        heightmap = new float[(HeightMapChunkWidth+3)*(HeightMapChunkHeight+3)];
    }
    catch (const std::bad_alloc&)
    {
        heightmap = 0;
    }
    catch (...)
    {
        heightmap = 0;
    }
    if (!heightmap)
    {
        // Could not allocate heightmap data
        return false;
    }

    // Generate heightmap data
    size_t heightmapIndex = 0;
    for (uint32_t j = 0; j <= (HeightMapChunkHeight+2); ++j)
    {
        for (uint32_t i = 0; i <= (HeightMapChunkWidth+2); ++i)
        {
            heightmapIndex = (j * (HeightMapChunkWidth+3)) + i;
            heightmap[heightmapIndex] = 0.0f;
        }
    }

    // Init heightmap chunk
    if (!m_heightMapChunk.generate(m_renderer, m_testTexture, heightmap))
    {
        // Could not init heightmap chunk
        return false;
    }

    // Cleanup heightmap data
    if (heightmap) { delete[] heightmap; }


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
    m_clock.reset();
    m_running = true;
    while (m_running)
    {
        float frametime = m_clock.getAndResetF();
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
                        case EVENT_KEY_Z:
                            m_freeflycam.setForward(true);
                            break;

                        case EVENT_KEY_S:
                            m_freeflycam.setBackward(true);
                            break;

                        case EVENT_KEY_Q:
                            m_freeflycam.setLeftward(true);
                            break;

                        case EVENT_KEY_D:
                            m_freeflycam.setRightward(true);
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

                        case EVENT_KEY_Z:
                            m_freeflycam.setForward(false);
                            break;

                        case EVENT_KEY_S:
                            m_freeflycam.setBackward(false);
                            break;

                        case EVENT_KEY_Q:
                            m_freeflycam.setLeftward(false);
                            break;

                        case EVENT_KEY_D:
                            m_freeflycam.setRightward(false);
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
                    m_freeflycam.mouseMove(
                        event.mouse.x*1.0f, event.mouse.y*1.0f
                    );
                    break;

                default:
                    break;
            }
        }

        // Compute frame
        m_view.compute(m_renderer);
        m_camera.compute(m_renderer);
        m_freeflycam.compute(m_renderer, frametime);

        // Render frame
        if (m_renderer.startFrame())
        {
            // Get renderer aspect ratio
            float cursorSize = 64.0f*scale;
            float cursorOffset = 2.0f*scale;

            // Set freefly camera
            m_renderer.setCamera(m_freeflycam);

            // Render static mesh
            /*m_renderer.bindStaticMeshPipeline();
            m_staticMesh.bindVertexBuffer(m_renderer);
            m_staticMesh.render(m_renderer);*/

            // Render heightmap chunk
            /*m_renderer.bindStaticMeshPipeline();
            m_heightMapChunk.bindVertexBuffer(m_renderer);
            m_heightMapChunk.render(m_renderer);*/


            // Set default screen view
            m_renderer.setDefaultView();

            // Bind default vertex buffer
            m_renderer.bindDefaultVertexBuffer();

            // Render rectangle
            /*m_renderer.bindRectPipeline();
            m_rect.render(m_renderer);*/

            // Render ellipse
            /*m_renderer.bindOvalPipeline();
            m_oval.render(m_renderer);*/

            // Render procedural sprite
            /*m_procSprite.bindPipeline(m_renderer);
            m_procSprite.render(m_renderer);*/

            // Render pixel text
            m_renderer.bindDefaultPipeline();
            m_pxText.render(m_renderer);

            // Draw cursor
            m_renderer.bindDefaultPipeline();
            m_cursor.setSize(cursorSize, cursorSize);
            m_cursor.setOrigin(0.0f, cursorSize);
            m_cursor.setPosition(
                m_mouseX-cursorOffset, m_mouseY+cursorOffset
            );
            m_cursor.render(m_renderer);

            // End rendering
            m_renderer.endFrame();
        }
    }

    // Wait for renderer device idle state
    if (m_renderer.waitDeviceIdle())
    {
        // Destroy heightmap chunk
        m_heightMapChunk.destroyHeightMapChunk(m_renderer);

        // Destroy static mesh
        m_staticMesh.destroyStaticMesh(m_renderer);

        // Destroy test texture
        m_testTexture.destroyTexture(m_renderer);

        // Destroy procedural sprite
        m_procSprite.destroyProcSprite(m_renderer);


        // Destroy freefly camera
        m_freeflycam.destroyCamera(m_renderer);

        // Destroy camera
        m_camera.destroyCamera(m_renderer);

        // Destroy view
        m_view.destroyView(m_renderer);

        // Destroy cursor texture
        m_cursorTexture.destroyTexture(m_renderer);
    }

    // Close VOS
    m_renderer.cleanup();
    m_window.close();
}
