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
//     Softwares/Interface/Interface.cpp : Interface class management         //
////////////////////////////////////////////////////////////////////////////////
#include "Interface.h"


////////////////////////////////////////////////////////////////////////////////
//  Interface global instance                                                 //
////////////////////////////////////////////////////////////////////////////////
Interface GInterface = Interface();


////////////////////////////////////////////////////////////////////////////////
//  Interface default constructor                                             //
////////////////////////////////////////////////////////////////////////////////
Interface::Interface() :
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
m_progressBar()
{

}

////////////////////////////////////////////////////////////////////////////////
//  Interface destructor                                                       //
////////////////////////////////////////////////////////////////////////////////
Interface::~Interface()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Init interface                                                            //
//  return : True if interface is ready, false otherwise                      //
////////////////////////////////////////////////////////////////////////////////
bool Interface::init()
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
    if (!m_sprite.init(GResources.textures.high(TEXTURE_TILE), 1.0f, 1.0f))
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
        GResources.textures.gui(TEXTURE_TOGGLEBUTTON), 0.08f, 0.08f, false))
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


    // Interface is ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy interface                                                         //
////////////////////////////////////////////////////////////////////////////////
void Interface::destroy()
{
    // Destroy procedural sprite
    m_procSprite.destroyProcSprite();

    // Destroy view
    m_view.destroyView();

    // Destroy back renderer
    m_backRenderer.destroyBackRenderer();
}


////////////////////////////////////////////////////////////////////////////////
//  Compute interface events                                                  //
////////////////////////////////////////////////////////////////////////////////
void Interface::events(SysEvent& event)
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

                case SYSEVENT_KEY_R:
                    break;

                default:
                    break;
            }
            break;

        // Mouse moved
        case SYSEVENT_MOUSEMOVED:
        {
            // Compute mouse events
            m_guiWindow.mouseMove(GSysMouse.mouseX, GSysMouse.mouseY);
            m_button.mouseMove(GSysMouse.mouseX, GSysMouse.mouseY);
            m_toggleButton.mouseMove(GSysMouse.mouseX, GSysMouse.mouseY);

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
            #endif // VOS_POINTERLOCK*/
            break;
        }

        // Mouse button pressed
        case SYSEVENT_MOUSEPRESSED:
            if (event.mouse.button == SYSEVENT_MOUSE_LEFT)
            {
                m_guiWindow.mousePress(GSysMouse.mouseX, GSysMouse.mouseY);
                m_button.mousePress(GSysMouse.mouseX, GSysMouse.mouseY);
                m_toggleButton.mousePress(GSysMouse.mouseX, GSysMouse.mouseY);
            }
            break;

        // Mouse button released
        case SYSEVENT_MOUSERELEASED:
            if (event.mouse.button == SYSEVENT_MOUSE_LEFT)
            {
                m_guiWindow.mouseRelease(GSysMouse.mouseX, GSysMouse.mouseY);
                m_button.mouseRelease(GSysMouse.mouseX, GSysMouse.mouseY);
                if (m_toggleButton.mouseRelease(
                    GSysMouse.mouseX, GSysMouse.mouseY))
                {
                    m_toggleButton.toggle();
                }
            }
            break;

        // Mouse wheel
        case SYSEVENT_MOUSEWHEEL:
            break;

        default:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Compute interface logic                                                   //
////////////////////////////////////////////////////////////////////////////////
void Interface::compute(float frametime)
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

    // Compute button
    m_button.setPosition(m_guiWindow.getX(), m_guiWindow.getY()+0.2f);

    // Compute toggle button
    m_toggleButton.setPosition(m_guiWindow.getX(), m_guiWindow.getY());

    // Compute progress bar
    static float valAcc = 0.0f;
    valAcc += frametime*0.5f;
    if (valAcc >= Math::TwoPi)
    {
        valAcc -= Math::TwoPi;
    }
    m_progressBar.setValue((Math::sin(valAcc)*0.5f)+0.5f);
    if (m_progressBar.isPicking(GSysMouse.mouseX, GSysMouse.mouseY))
    {
        m_progressBar.setColor(0.0f, 0.0f, 1.0f, 1.0f);
    }
    else
    {
        m_progressBar.setColor(1.0f, 1.0f, 1.0f, 1.0f);
    }
    m_progressBar.setPosition(m_guiWindow.getX(), m_guiWindow.getY()-0.2f);


    // Update view position
    m_view.setPosition(0.0f, 0.0f);

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
//  Render interface                                                          //
////////////////////////////////////////////////////////////////////////////////
void Interface::render()
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
    GRenderer.bindPipeline(RENDERER_PIPELINE_NINEPATCH);
    m_guiWindow.bindTexture();
    m_guiWindow.render();

    // Render button
    GRenderer.bindPipeline(RENDERER_PIPELINE_BUTTON);
    m_button.bindTexture();
    m_button.render();

    // Render toggle button
    GRenderer.bindPipeline(RENDERER_PIPELINE_TOGGLEBUTTON);
    m_toggleButton.bindTexture();
    m_toggleButton.render();

    // Render progress bar
    GRenderer.bindPipeline(RENDERER_PIPELINE_PROGRESSBAR);
    m_progressBar.bindTexture();
    m_progressBar.render();

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
