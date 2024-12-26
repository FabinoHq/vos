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
//     Softwares/Isometric/Isometric.cpp : Isometric class management         //
////////////////////////////////////////////////////////////////////////////////
#include "Isometric.h"


////////////////////////////////////////////////////////////////////////////////
//  Isometric global instance                                                 //
////////////////////////////////////////////////////////////////////////////////
Isometric GIsometric = Isometric();


////////////////////////////////////////////////////////////////////////////////
//  Isometric default constructor                                             //
////////////////////////////////////////////////////////////////////////////////
Isometric::Isometric() :
m_backRenderer(),
m_view(),
m_sprite(),
m_procSprite(),
m_rectangle(),
m_ellipse(),
m_cursor(),
m_guiWindow(),
m_pxText(),
m_chunkWarp(false),
m_chunkX(0),
m_chunkY(0),
m_isomap(),
m_player(),
m_zoom(1.0f)
{

}

////////////////////////////////////////////////////////////////////////////////
//  Isometric destructor                                                      //
////////////////////////////////////////////////////////////////////////////////
Isometric::~Isometric()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Init isometric game                                                       //
//  return : True if isometric game is ready, false otherwise                 //
////////////////////////////////////////////////////////////////////////////////
bool Isometric::init()
{
    // Init back renderer
    if (!m_backRenderer.init(VULKAN_MEMORY_BACKRENDERER, 256, 256, false))
    {
        // Could not init back renderer
        return false;
    }

    // Init view
    if (!m_view.init())
    {
        // Could not init view
        return false;
    }


    // Init sprite
    if (!m_sprite.init(GResources.textures.high(TEXTURE_ISOTILE), 2.0f, 1.0f))
    {
        // Could not init sprite
        return false;
    }

    // Init procedural sprite
    if (!m_procSprite.init(1.0f, 1.0f))
    {
        // Could not init procedural sprite
        return false;
    }

    // Init rectangle shape
    if (!m_rectangle.init(1.0f, 1.0f))
    {
        // Could not init rectangle shape
        return false;
    }

    // Init ellipse shape
    if (!m_ellipse.init(1.0f, 1.0f))
    {
        // Could not init ellipse shape
        return false;
    }


    // Init GUI cursor
    if (!m_cursor.init(GResources.textures.gui(TEXTURE_CURSOR), 64.0f))
    {
        // Could not init GUI cursor
        return false;
    }

    // Init GUI window
    if (!m_guiWindow.init(
        GResources.textures.gui(TEXTURE_WINDOW), 1.0f, 1.0f, 3.75f))
    {
        // Could not init GUI window
        return false;
    }

    // Init test pixel text
    if (!m_pxText.init(GResources.textures.gui(TEXTURE_PIXELFONT), 0.04f))
    {
        // Could not init test pixel text
        return false;
    }
    m_pxText.setSmooth(0.2f);
    m_pxText.setText("FPS : 0");


    // Reset chunk X and Y
    m_chunkWarp = false;
    m_chunkX = 0;
    m_chunkY = 0;

    // Init matrix stream
    if (!GMatrixStream2.init())
    {
        // Could not init matrix stream
        return false;
    }

    // Init isomap stream
    if (!m_isomap.init())
    {
        // Could not init isomap stream
        return false;
    }

    // Load spawn matrix chunks
    while (!GMatrixStream2.reload(0, 0))
    {
        // Release some CPU
        SysSleep(ResourcesWaitSleepTime);
    }

    // Load spawn isomap chunks
    while (!m_isomap.reload(0, 0))
    {
        // Release some CPU
        SysSleep(ResourcesWaitSleepTime);
    }

    // Wait for spawn chunks to be loaded
    bool spawnLoaded = false;
    while (!spawnLoaded)
    {
        if (GMatrixStream2.isReady() && m_isomap.isReady())
        {
            spawnLoaded = true;
        }
        else
        {
            // Release some CPU while loading
            SysSleep(ResourcesWaitSleepTime);
        }
    }

    // Init player
    if (!m_player.init())
    {
        // Could not init player
        return false;
    }

    // Reset zoom
    m_zoom = 1.0f;


    // Isometric game is ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy isometric game                                                    //
////////////////////////////////////////////////////////////////////////////////
void Isometric::destroy()
{
    // Destroy procedural sprite
    m_procSprite.destroyProcSprite();

    // Destroy view
    m_view.destroyView();

    // Destroy back renderer
    m_backRenderer.destroyBackRenderer();
}


////////////////////////////////////////////////////////////////////////////////
//  Compute isometric game events                                             //
////////////////////////////////////////////////////////////////////////////////
void Isometric::events(SysEvent& event)
{
    // Process event
    switch (event.type)
    {
        // Key pressed
        case SYSEVENT_KEYPRESSED:
            switch (event.key)
            {
                case SYSEVENT_KEY_Z:
                    break;

                case SYSEVENT_KEY_S:
                    break;

                case SYSEVENT_KEY_Q:
                    break;

                case SYSEVENT_KEY_D:
                    break;

                case SYSEVENT_KEY_SPACE:
                    break;

                case SYSEVENT_KEY_LSHIFT:
                    break;

                default:
                    break;
            }
            break;

        // Key released
        case SYSEVENT_KEYRELEASED:
            switch (event.key)
            {
                case SYSEVENT_KEY_Z:
                    break;

                case SYSEVENT_KEY_S:
                    break;

                case SYSEVENT_KEY_Q:
                    break;

                case SYSEVENT_KEY_D:
                    break;

                case SYSEVENT_KEY_SPACE:
                    break;

                case SYSEVENT_KEY_LSHIFT:
                    break;

                default:
                    break;
            }
            break;

        // Mouse moved
        case SYSEVENT_MOUSEMOVED:
            break;

        // Mouse button pressed
        case SYSEVENT_MOUSEPRESSED:
            break;

        // Mouse button released
        case SYSEVENT_MOUSERELEASED:
            break;

        // Mouse wheel
        case SYSEVENT_MOUSEWHEEL:
            if (event.mouse.wheel < 0)
            {
                m_zoom = Math::max(0.2f, m_zoom-0.02f);
            }
            else if (event.mouse.wheel > 0)
            {
                m_zoom = Math::min(1.0f, m_zoom+0.02f);
            }
            break;

        default:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Precompute isometric game physics (thread sync)                           //
////////////////////////////////////////////////////////////////////////////////
void Isometric::prephysics()
{
    // Compute game warp
    Vector2i warpOffset = warp();

    // Precompute player physics
    m_player.prephysics(warpOffset);
}

////////////////////////////////////////////////////////////////////////////////
//  Compute isometric game warp                                               //
////////////////////////////////////////////////////////////////////////////////
Vector2i Isometric::warp()
{
    Vector2i warpOffset = Vector2i(0, 0);
    if (!m_chunkWarp && m_player.needWarp())
    {
        if (GMatrixStream2.isReady() && m_isomap.isReady())
        {
            if (m_player.topWarp())
            {
                // Top warp
                warpOffset.vec[1] = -MatrixChunk2XStride;
                ++m_chunkY;
            }
            else if (m_player.bottomWarp())
            {
                // Bottom warp
                warpOffset.vec[1] = MatrixChunk2XStride;
                --m_chunkY;
            }
            else if (m_player.leftWarp())
            {
                // Left warp
                warpOffset.vec[0] = MatrixChunk2YStride;
                --m_chunkX;
            }
            else if (m_player.rightWarp())
            {
                // Right warp
                warpOffset.vec[0] = -MatrixChunk2YStride;
                ++m_chunkX;
            }

            // Update matrix stream
            GMatrixStream2.update(m_chunkX, m_chunkY);
            m_chunkWarp = true;
        }
    }
    return warpOffset;
}

////////////////////////////////////////////////////////////////////////////////
//  Compute isometric game physics (threaded)                                 //
////////////////////////////////////////////////////////////////////////////////
void Isometric::physics()
{
    // Compute player physics
    m_player.physics();
}

////////////////////////////////////////////////////////////////////////////////
//  Precompute isometric game renderer interpolations                         //
////////////////////////////////////////////////////////////////////////////////
void Isometric::precompute(float physicstime)
{
    // Update isomap stream
    if (m_chunkWarp)
    {
        m_isomap.update(m_chunkX, m_chunkY);
        m_chunkWarp = false;
    }

    // Precompute player
    m_player.precompute(physicstime);
}

////////////////////////////////////////////////////////////////////////////////
//  Compute isometric game logic                                              //
////////////////////////////////////////////////////////////////////////////////
void Isometric::compute(float frametime)
{
    // Framerate
    static std::ostringstream framestr;
    static float frameavg = 0.0f;
    static float framecnt = 0.0f;

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
    m_pxText.setText(framestr.str());


    // Update view position
    //m_view.setSize(0.9f, 1.0f);
    //m_view.setPosition(m_player.getX()*0.9f, m_player.getY()+0.08f);
    m_view.setSize(m_zoom, m_zoom);
    m_view.setPosition(m_player.getX()*m_zoom, (m_player.getY()+0.08f)*m_zoom);


    // Start uniforms upload
    if (GUniformchain.startUpload())
    {
        // Compute views
        GRenderer.computeDefaultView();
        GMainRenderer.computeDefaultView();
        m_backRenderer.computeDefaultView();
        m_view.compute(GSwapchain.ratio);

        // End uniforms upload
        GUniformchain.endUpload();
    }


    /*// Memory dump
    static int memDump = 0;
    ++memDump;
    if (memDump >= 2000)
    {
        GVulkanMemory.dumpMemory();
        memDump = 0;
    }*/
}

////////////////////////////////////////////////////////////////////////////////
//  Render isometric game                                                     //
////////////////////////////////////////////////////////////////////////////////
void Isometric::render()
{
    // Start frame rendering
    if (!GRenderer.startFrame())
    {
        return;
    }

    // Get renderer scale and ratio
    //float scale = GSwapchain.getScale();
    float ratio = GSwapchain.getRatio();

    // Start rendering
    GRenderer.startRenderPass();

    // Set 2D view
    m_view.bind();

    // Bind default vertex buffer
    GRenderer.bindVertexBuffer(MESHES_DEFAULT);


    // Render isomap chunks
    GRenderer.bindPipeline(RENDERER_PIPELINE_DEFAULT);
    m_sprite.setColor(1.0f, 1.0f, 1.0f, 1.0f);
    m_sprite.setOrigin(0.0f, 0.0f);
    m_sprite.setSize(IsoMapElemWidth+0.00001f, IsoMapElemHeight+0.00001f);
    m_sprite.setAngle(0.0f);
    m_isomap.render(m_sprite);

    // Render player
    m_player.render();


    // Set default screen view
    GMainRenderer.bindDefaultView();

    // Bind default vertex buffer
    GRenderer.bindVertexBuffer(MESHES_DEFAULT);

    // Render pixel text (framerate)
    GRenderer.bindPipeline(RENDERER_PIPELINE_PXTEXT);
    m_pxText.bindTexture();
    m_pxText.setPosition(-ratio+0.01f, 1.0f-(m_pxText.getHeight()*0.7f));
    if (m_pxText.isPicking(GSysMouse.mouseX, GSysMouse.mouseY))
    {
        m_pxText.setColor(0.0f, 0.0f, 1.0f, 1.0f);
    }
    else
    {
        m_pxText.setColor(1.0f, 1.0f, 1.0f, 1.0f);
    }
    m_pxText.render();

    // Render pixel text (view position)
    std::ostringstream camerastr;
    camerastr << "X : " << m_player.getX() << " | Y : " << m_player.getY();
    m_pxText.setText(camerastr.str());
    m_pxText.setPosition(-ratio+0.01f, 0.96f-(m_pxText.getHeight()*0.7f));
    if (m_pxText.isPicking(GSysMouse.mouseX, GSysMouse.mouseY))
    {
        m_pxText.setColor(0.0f, 0.0f, 1.0f, 1.0f);
    }
    else
    {
        m_pxText.setColor(1.0f, 1.0f, 1.0f, 1.0f);
    }
    m_pxText.render();

    // Render pixel text (physics current ticks)
    std::ostringstream physicstr;
    physicstr << "Ticks : " << GPhysics.getTick();
    m_pxText.setText(physicstr.str());
    m_pxText.setPosition(-ratio+0.01f, 0.92f-(m_pxText.getHeight()*0.7f));
    if (m_pxText.isPicking(GSysMouse.mouseX, GSysMouse.mouseY))
    {
        m_pxText.setColor(0.0f, 0.0f, 1.0f, 1.0f);
    }
    else
    {
        m_pxText.setColor(1.0f, 1.0f, 1.0f, 1.0f);
    }
    m_pxText.render();

    // Render cursor
    GRenderer.bindPipeline(RENDERER_PIPELINE_DEFAULT);
    m_cursor.setPosition(GSysMouse.mouseX, GSysMouse.mouseY);
    m_cursor.bindTexture();
    m_cursor.render();

    // End rendering
    GRenderer.endRenderPass();


    // Start final pass
    GRenderer.startFinalPass();

    // Render main compositing quad
    GRenderer.bindDefaultView();
    GRenderer.bindPipeline(RENDERER_PIPELINE_COMPOSITING);
    GRenderer.bindVertexBuffer(MESHES_DEFAULT);
    GMainRenderer.bind();
    GRenderer.plane.setSize(
        (GSwapchain.ratio*2.0f)+RendererCompositingPlaneOffset,
        2.0f+RendererCompositingPlaneOffset
    );
    GRenderer.plane.setPosition(0.0f, 0.0f);
    GRenderer.plane.render();

    // End final pass
    GRenderer.endFinalPass();


    // End frame rendering
    GRenderer.endFrame();
}
