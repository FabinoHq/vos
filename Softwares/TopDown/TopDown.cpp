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
//     Softwares/TopDown/TopDown.cpp : TopDown class management               //
////////////////////////////////////////////////////////////////////////////////
#include "TopDown.h"


////////////////////////////////////////////////////////////////////////////////
//  TopDown default constructor                                               //
////////////////////////////////////////////////////////////////////////////////
TopDown::TopDown() :
m_backRenderer(),
m_view(),
m_sprite(),
m_procSprite(),
m_rectangle(),
m_ellipse(),
m_cursor(),
m_guiWindow(),
m_pxText(),
m_button(),
m_toggleButton(),
m_progressBar(),
m_boundingCircle(),
m_boundingCircle2(),
m_boundingRect(),
m_boundingRect2(),
m_collide(),
m_spaceReleased(false)
{

}

////////////////////////////////////////////////////////////////////////////////
//  TopDown destructor                                                        //
////////////////////////////////////////////////////////////////////////////////
TopDown::~TopDown()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Init top down game                                                        //
//  return : True if top down game is ready, false otherwise                  //
////////////////////////////////////////////////////////////////////////////////
bool TopDown::init()
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
    if (!m_sprite.init(GResources.textures.high(TEXTURE_TEST), 1.0f, 1.0f))
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

    // Init test button
    if (!m_button.init(
        GResources.textures.gui(TEXTURE_TESTBUTTON), 0.12f, 0.06f, false))
    {
        // Could not init test button
        return false;
    }

    // Init toggle button
    if (!m_toggleButton.init(
        GResources.textures.gui(TEXTURE_TOGGLEBUTTON), 0.06f, 0.06f, false))
    {
        // Could not init toggle button
        return false;
    }

    // Init progress bar
    if (!m_progressBar.init(
        GResources.textures.gui(TEXTURE_PROGRESSBAR), 0.5f, 0.06f, 15.0f))
    {
        // Could not init progress bar
        return false;
    }


    // Init bounding circle
    m_boundingCircle.setPosition(-20000000, 0);
    m_boundingCircle.setRadius(10000000);

    // Init bounding circle 2
    m_boundingCircle2.setPosition(20000000, 0);
    m_boundingCircle2.setRadius(8000000);

    // Init bounding rect
    m_boundingRect.setPosition(-20000000, 0);
    m_boundingRect.setSize(10000000, 7000000);

    // Init bounding rect2
    m_boundingRect2.setPosition(20000000, 0);
    m_boundingRect2.setSize(7500000, 6000000);


    // Top down game is ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy top down game                                                     //
////////////////////////////////////////////////////////////////////////////////
void TopDown::destroy()
{
    // Destroy procedural sprite
    m_procSprite.destroyProcSprite();

    // Destroy view
    m_view.destroyView();

    // Destroy back renderer
    m_backRenderer.destroyBackRenderer();
}


////////////////////////////////////////////////////////////////////////////////
//  Compute top down game events                                              //
////////////////////////////////////////////////////////////////////////////////
void TopDown::events(Event& event)
{
    // Process event
    switch (event.type)
    {
        // Key pressed
        case EVENT_KEYPRESSED:
            switch (event.key)
            {
                case EVENT_KEY_Z:
                    break;

                case EVENT_KEY_S:
                    break;

                case EVENT_KEY_Q:
                    break;

                case EVENT_KEY_D:
                    break;

                case EVENT_KEY_SPACE:
                    break;

                case EVENT_KEY_LSHIFT:
                    break;

                default:
                    break;
            }
            break;

        // Key released
        case EVENT_KEYRELEASED:
            switch (event.key)
            {
                case EVENT_KEY_Z:
                    break;

                case EVENT_KEY_S:
                    break;

                case EVENT_KEY_Q:
                    break;

                case EVENT_KEY_D:
                    break;

                case EVENT_KEY_SPACE:
                    m_spaceReleased = true;
                    break;

                case EVENT_KEY_LSHIFT:
                    break;

                case EVENT_KEY_R:
                    m_boundingCircle2.setPosition(20000000, 0);
                    m_boundingRect2.setPosition(20000000, 0);
                    break;

                default:
                    break;
            }
            break;

        // Mouse moved
        case EVENT_MOUSEMOVED:
        {
            // Compute mouse events
            //m_guiWindow.mouseMove(GSysMouse.mouseX, GSysMouse.mouseY);
            //m_button.mouseMove(GSysMouse.mouseX, GSysMouse.mouseY);
            //m_toggleButton.mouseMove(GSysMouse.mouseX, GSysMouse.mouseY);

            #if (VOS_POINTERLOCK == 1)
                // GUI cursor
                m_cursor.setCursor(
                    m_guiWindow.updateCursor(GSysMouse.mouseX, GSysMouse.mouseY)
                );
            #else
                // System cursor
                GSysWindow.setCursor(
                    m_guiWindow.updateCursor(GSysMouse.mouseX, GSysMouse.mouseY)
                );
            #endif // VOS_POINTERLOCK
            break;
        }

        // Mouse button pressed
        case EVENT_MOUSEPRESSED:
            if (event.mouse.button == EVENT_MOUSE_LEFT)
            {
                //m_guiWindow.mousePress(GSysMouse.mouseX, GSysMouse.mouseY);
                //m_button.mousePress(GSysMouse.mouseX, GSysMouse.mouseY);
                //m_toggleButton.mousePress(GSysMouse.mouseX, GSysMouse.mouseY);
            }
            break;

        // Mouse button released
        case EVENT_MOUSERELEASED:
            if (event.mouse.button == EVENT_MOUSE_LEFT)
            {
                //m_guiWindow.mouseRelease(GSysMouse.mouseX, GSysMouse.mouseY);
                //m_button.mouseRelease(GSysMouse.mouseX, GSysMouse.mouseY);
                /*if (m_toggleButton.mouseRelease(
                    GSysMouse.mouseX, GSysMouse.mouseY))
                {
                    m_toggleButton.toggle();
                }*/
            }
            break;

        // Mouse wheel
        case EVENT_MOUSEWHEEL:
            break;

        default:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Compute top down game logic                                               //
////////////////////////////////////////////////////////////////////////////////
void TopDown::compute(float frametime)
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

    /*static float valAcc = 0.0f;
    valAcc += frametime*0.5f;
    if (valAcc >= Math::TwoPi)
    {
        valAcc -= Math::TwoPi;
    }
    m_progressBar.setValue((std::sin(valAcc)*0.5f)+0.5f);

    if (m_progressBar.isPicking(GSysMouse.mouseX, GSysMouse.mouseY))
    {
        m_progressBar.setColor(0.0f, 0.0f, 1.0f, 1.0f);
    }
    else
    {
        m_progressBar.setColor(1.0f, 1.0f, 1.0f, 1.0f);
    }*/

    // Compute physics
    /*Vector2i collideOffset;
    collideOffset.vec[0] = static_cast<int64_t>(GSysMouse.mouseX*100000000);
    collideOffset.vec[1] = static_cast<int64_t>(GSysMouse.mouseY*100000000);
    collideOffset.vec[0] -= m_boundingCircle2.position.vec[0];
    collideOffset.vec[1] -= m_boundingCircle2.position.vec[1];
    m_collide.reset();
    m_boundingCircle2.collideCircle(
        m_boundingCircle, collideOffset, m_collide
    );

    // Space key released event
    if (m_spaceReleased)
    {
        m_boundingCircle2.position.vec[0] = m_collide.position.vec[0];
        m_boundingCircle2.position.vec[1] = m_collide.position.vec[1];
        m_spaceReleased = false;
    }*/

    // Compute physics
    Vector2i collideOffset;
    collideOffset.vec[0] = static_cast<int64_t>(GSysMouse.mouseX*100000000);
    collideOffset.vec[1] = static_cast<int64_t>(GSysMouse.mouseY*100000000);
    collideOffset.vec[0] -= m_boundingRect2.position.vec[0];
    collideOffset.vec[1] -= m_boundingRect2.position.vec[1];
    m_collide.reset();
    m_boundingRect2.collideRect(
        m_boundingRect, collideOffset, m_collide
    );

    // Space key released event
    if (m_spaceReleased)
    {
        m_boundingRect2.position.vec[0] = m_collide.position.vec[0];
        m_boundingRect2.position.vec[1] = m_collide.position.vec[1];
        m_spaceReleased = false;
    }
    

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
//  Render top down game                                                      //
////////////////////////////////////////////////////////////////////////////////
void TopDown::render()
{
    // Start frame rendering
    if (!GRenderer.startFrame())
    {
        return;
    }

    // Get renderer scale and ratio
    //float scale = GSwapchain.getScale();
    float ratio = GSwapchain.getRatio();

    // Back rendering
    /*if (m_backRenderer.startRenderPass())
    {
        // Set back renderer view
        m_backRenderer.bindDefaultView();

        // Render sprite
        GRenderer.bindPipeline(RENDERER_PIPELINE_DEFAULT);
        GRenderer.bindVertexBuffer(MESHES_DEFAULT);
        m_sprite.bindTexture();
        m_sprite.render();

        // End back rendering
        m_backRenderer.endRenderPass();
    }*/

    // Start rendering
    GRenderer.startRenderPass();

    // Set 2D view
    m_view.bind();

    // Bind default vertex buffer
    GRenderer.bindVertexBuffer(MESHES_DEFAULT);


    // Render bounding circle
    /*GRenderer.bindPipeline(RENDERER_PIPELINE_ELLIPSE);
    float positionX =
        m_boundingCircle.position.vec[0]*PhysicsToRenderer;
    float positionY =
        m_boundingCircle.position.vec[1]*PhysicsToRenderer;
    float radius = m_boundingCircle.radius*PhysicsToRenderer;
    m_ellipse.setColor(0.0f, 0.8f, 0.2f, 0.8f);
    m_ellipse.setOrigin(0.0f, 0.0f);
    m_ellipse.setPosition(positionX, positionY);
    m_ellipse.setSize(radius*2.05f, radius*2.05f);
    m_ellipse.setSmooth(0.025f);
    m_ellipse.render();

    // Render bounding circle 2
    positionX = m_boundingCircle2.position.vec[0]*PhysicsToRenderer;
    positionY = m_boundingCircle2.position.vec[1]*PhysicsToRenderer;
    radius = m_boundingCircle2.radius*PhysicsToRenderer;
    m_ellipse.setColor(0.0f, 0.2f, 0.8f, 0.8f);
    m_ellipse.setOrigin(0.0f, 0.0f);
    m_ellipse.setPosition(positionX, positionY);
    m_ellipse.setSize(radius*2.04f, radius*2.04f);
    m_ellipse.setSmooth(0.022f);
    m_ellipse.render();

    // Render bounding circle 2 projection
    positionX = m_collide.position.vec[0]*PhysicsToRenderer;
    positionY = m_collide.position.vec[1]*PhysicsToRenderer;
    radius = m_boundingCircle2.radius*PhysicsToRenderer;
    m_ellipse.setColor(0.8f, 0.2f, 0.8f, 0.8f);
    if (m_collide.collide)
    {
        m_ellipse.setColor(0.8f, 0.2f, 0.2f, 0.8f);
    }
    m_ellipse.setOrigin(0.0f, 0.0f);
    m_ellipse.setPosition(positionX, positionY);
    m_ellipse.setSize(radius*2.07f, radius*2.07f);
    m_ellipse.setSmooth(0.028f);
    m_ellipse.render();*/


    // Render bounding rect
    GRenderer.bindPipeline(RENDERER_PIPELINE_RECTANGLE);
    float positionX =
        m_boundingRect.position.vec[0]*PhysicsToRenderer;
    float positionY =
        m_boundingRect.position.vec[1]*PhysicsToRenderer;
    float width = m_boundingRect.size.vec[0]*PhysicsToRenderer;
    float height = m_boundingRect.size.vec[1]*PhysicsToRenderer;
    m_rectangle.setColor(0.0f, 0.8f, 0.2f, 0.8f);
    m_rectangle.setOrigin(0.0f, 0.0f);
    m_rectangle.setPosition(positionX, positionY);
    m_rectangle.setSize(width*2.05f, height*2.05f);
    m_rectangle.setSmooth(0.025f);
    m_rectangle.render();

    // Render bounding rect 2
    positionX = m_boundingRect2.position.vec[0]*PhysicsToRenderer;
    positionY = m_boundingRect2.position.vec[1]*PhysicsToRenderer;
    width = m_boundingRect2.size.vec[0]*PhysicsToRenderer;
    height = m_boundingRect2.size.vec[1]*PhysicsToRenderer;
    m_rectangle.setColor(0.0f, 0.2f, 0.8f, 0.8f);
    m_rectangle.setOrigin(0.0f, 0.0f);
    m_rectangle.setPosition(positionX, positionY);
    m_rectangle.setSize(width*2.04f, height*2.04f);
    m_rectangle.setSmooth(0.022f);
    m_rectangle.render();

    // Render bounding rect 2 projection
    positionX = m_collide.position.vec[0]*PhysicsToRenderer;
    positionY = m_collide.position.vec[1]*PhysicsToRenderer;
    width = m_boundingRect2.size.vec[0]*PhysicsToRenderer;
    height = m_boundingRect2.size.vec[1]*PhysicsToRenderer;
    m_rectangle.setColor(0.8f, 0.2f, 0.8f, 0.8f);
    if (m_collide.collide)
    {
        m_rectangle.setColor(0.8f, 0.2f, 0.2f, 0.8f);
    }
    m_rectangle.setOrigin(0.0f, 0.0f);
    m_rectangle.setPosition(positionX, positionY);
    m_rectangle.setSize(width*2.07f, height*2.07f);
    m_rectangle.setSmooth(0.028f);
    m_rectangle.render();


    // Set default screen view
    GMainRenderer.bindDefaultView();

    // Bind default vertex buffer
    GRenderer.bindVertexBuffer(MESHES_DEFAULT);

    // Render back rendered frame
    /*GRenderer.bindPipeline(RENDERER_PIPELINE_DEFAULT);
    m_backRenderer.bind();
    m_sprite.render();*/

    // Render sprite
    /*GRenderer.bindPipeline(RENDERER_PIPELINE_DEFAULT);
    m_sprite.bindTexture();
    m_sprite.render();*/

    // Render procedural sprite
    /*m_procSprite.bindPipeline();
    m_procSprite.render();*/

    // Render rectangle
    /*GRenderer.bindPipeline(RENDERER_PIPELINE_RECTANGLE);
    m_rectangle.render();*/

    // Render ellipse
    /*GRenderer.bindPipeline(RENDERER_PIPELINE_ELLIPSE);
    m_ellipse.render();*/

    // Render window
    /*GRenderer.bindPipeline(RENDERER_PIPELINE_NINEPATCH);
    m_guiWindow.bindTexture();
    if (m_guiWindow.isPicking(GSysMouse.mouseX, GSysMouse.mouseY))
    {
        m_guiWindow.setColor(0.0f, 0.0f, 1.0f, 1.0f);
    }
    else
    {
        m_guiWindow.setColor(1.0f, 1.0f, 1.0f, 1.0f);
    }
    m_guiWindow.render();*/

    // Render button
    /*GRenderer.bindPipeline(RENDERER_PIPELINE_BUTTON);
    m_button.bindTexture();
    m_button.render();*/

    // Render toggle button
    /*GRenderer.bindPipeline(RENDERER_PIPELINE_TOGGLEBUTTON);
    m_toggleButton.bindTexture();
    m_toggleButton.render();*/

    // Render progress bar
    /*GRenderer.bindPipeline(RENDERER_PIPELINE_PROGRESSBAR);
    m_progressBar.bindTexture();
    m_progressBar.render();*/

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
    camerastr << "X : " << m_view.getX() <<
        " | Y : " << m_view.getY();
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
