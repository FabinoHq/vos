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
//     Game.cpp : Main game class management                                  //
////////////////////////////////////////////////////////////////////////////////
#include "Game.h"


////////////////////////////////////////////////////////////////////////////////
//  Game default constructor                                                  //
////////////////////////////////////////////////////////////////////////////////
Game::Game() :
m_backRenderer(),
m_view(),
m_camera(),
m_freeflycam(),
m_orbitalcam(),
m_cubemap(),
m_skybox(),
m_sprite(),
m_procSprite(),
m_rectanle(),
m_ellipse(),
m_cuboid(),
m_cursor(),
m_guiWindow(),
m_pxText(),
m_staticMesh(),
m_heightMapStream(),
m_boundingCircle(),
m_boundingCircle2(),
m_collideCircle(),
m_mouseX(0.0f),
m_mouseY(0.0f),
m_spaceReleased(false)
{

}

////////////////////////////////////////////////////////////////////////////////
//  Game destructor                                                           //
////////////////////////////////////////////////////////////////////////////////
Game::~Game()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Init Game                                                                 //
//  return : True if game is ready, false otherwise                           //
////////////////////////////////////////////////////////////////////////////////
bool Game::init()
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

    // Init camera
    if (!m_camera.init())
    {
        // Could not init camera
        return false;
    }
    m_camera.setZ(1.0f);

    // Init freefly camera
    if (!m_freeflycam.init())
    {
        // Could not init freefly camera
        return false;
    }
    m_freeflycam.setZ(1.0f);
    m_freeflycam.setSpeed(10.0f);
    m_freeflycam.setY(300.0f);

    // Init orbital camera
    if (!m_orbitalcam.init())
    {
        // Could not init orbital camera
        return false;
    }
    m_orbitalcam.setZ(1.0f);
    m_orbitalcam.setTarget(0.0f, 0.0f, 0.0f);
    m_orbitalcam.setDistance(2.0f);
    m_orbitalcam.setSpeed(50.0f);


    // Init skybox
    if (!m_skybox.init(
        GResources.meshes.mesh(MESHES_SKYBOX),
        GResources.textures.cubemap(TEXTURE_CUBEMAPTEST)))
    {
        // Could not init skybox
        return false;
    }


    // Init sprite
    if (!m_sprite.init(GResources.textures.high(TEXTURE_TEST), 1.0f, 1.0f))
    {
        // Could not init sprite
        return false;
    }

    // Init procedural sprite
    if (!m_procSprite.init(0, 0, 1.0f, 1.0f))
    {
        // Could not init procedural sprite
        return false;
    }

    // Init rectangle shape
    if (!m_rectanle.init(1.0f, 1.0f))
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

    // Init cuboid shape
    if (!m_cuboid.init(GResources.meshes.mesh(MESHES_CUBOID)))
    {
        // Could not init cuboid shape
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


    // Init static mesh
    if (!m_staticMesh.init(
        GResources.meshes.mesh(MESHES_TEST),
        GResources.textures.high(TEXTURE_TEST)))
    {
        // Could not init static mesh
        return false;
    }

    // Init heightmap stream
    if (!m_heightMapStream.init())
    {
        // Could not init heightmap stream
        return false;
    }

    // Load spawn heightmap chunks
    m_heightMapStream.reload(0, 0);

    // Wait for heightmap spawn chunks
    bool heightmapLoaded = false;
    while (!heightmapLoaded)
    {
        if (m_heightMapStream.isReady())
        {
            heightmapLoaded = true;
        }
        else
        {
            // Release some CPU while loading
            SysSleep(ResourcesWaitSleepTime);
        }
    }


    // Init bounding circle
    m_boundingCircle.setPosition(-20000000, 0);
    m_boundingCircle.setRadius(10000000);

    // Init bounding circle 2
    m_boundingCircle2.setPosition(20000000, 0);
    m_boundingCircle2.setRadius(8000000);

    // Game is ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy game                                                              //
////////////////////////////////////////////////////////////////////////////////
void Game::destroy()
{
    // Destroy procedural sprite
    m_procSprite.destroyProcSprite();

    // Destroy cubemap
    m_cubemap.destroyCubeMap();


    // Destroy orbital camera
    m_orbitalcam.destroyCamera();

    // Destroy freefly camera
    m_freeflycam.destroyCamera();

    // Destroy camera
    m_camera.destroyCamera();

    // Destroy view
    m_view.destroyView();

    // Destroy back renderer
    m_backRenderer.destroyBackRenderer();
}


////////////////////////////////////////////////////////////////////////////////
//  Compute game events                                                       //
////////////////////////////////////////////////////////////////////////////////
void Game::events(Event& event)
{
    // Get renderer scale and ratio
    float scale = GSwapchain.getScale();
    float ratio = GSwapchain.getRatio();

    // Process event
    switch (event.type)
    {
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

                case EVENT_KEY_SPACE:
                    break;

                case EVENT_KEY_LSHIFT:
                    m_freeflycam.setSpeed(300.0f);
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

                case EVENT_KEY_SPACE:
                    m_spaceReleased = true;
                    break;

                case EVENT_KEY_LSHIFT:
                    m_freeflycam.setSpeed(10.0f);
                    break;

                case EVENT_KEY_R:
                    //m_boundingCircle2.setPosition(20000000, 0);
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
            /*m_orbitalcam.mouseMove(
                event.mouse.x*1.0f, event.mouse.y*1.0f
            );*/
            /*m_guiWindow.mouseMove(m_mouseX, m_mouseY);
            m_cursor.setCursor(
                GResources, m_guiWindow.updateCursor(m_mouseX, m_mouseY)
            );*/
            break;

        // Mouse button pressed
        case EVENT_MOUSEPRESSED:
            if (event.mouse.button == EVENT_MOUSE_LEFT)
            {
                //m_orbitalcam.mousePress();
                //m_guiWindow.mousePress(m_mouseX, m_mouseY);
            }
            break;

        // Mouse button released
        case EVENT_MOUSERELEASED:
            if (event.mouse.button == EVENT_MOUSE_LEFT)
            {
                //m_orbitalcam.mouseRelease();
                //m_guiWindow.mouseRelease(m_mouseX, m_mouseY);
            }
            break;

        // Mouse wheel
        case EVENT_MOUSEWHEEL:
            //m_orbitalcam.mouseWheel(event.mouse.wheel);
            break;

        default:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Compute game logic                                                        //
////////////////////////////////////////////////////////////////////////////////
void Game::compute(float frametime)
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

    // Compute frame
    m_view.compute(GSwapchain.ratio);
    m_camera.compute(GSwapchain.ratio);
    m_freeflycam.compute(GSwapchain.ratio, frametime);
    m_orbitalcam.compute(GSwapchain.ratio, frametime);

    // Update heightmap
    int32_t chunkX = static_cast<int32_t>(
        m_freeflycam.getX()/HeightMapChunkXStride
    );
    int32_t chunkY = static_cast<int32_t>(
        m_freeflycam.getZ()/HeightMapChunkZStride
    );
    m_heightMapStream.update(chunkX, chunkY);

    // Compute physics
    /*Vector2i collideOffset;
    collideOffset.vec[0] = static_cast<int64_t>(m_mouseX*100000000);
    collideOffset.vec[1] = static_cast<int64_t>(m_mouseY*100000000);
    collideOffset.vec[0] -= m_boundingCircle2.position.vec[0];
    collideOffset.vec[1] -= m_boundingCircle2.position.vec[1];
    m_collideCircle.reset();
    m_boundingCircle2.collideCircle(
        m_boundingCircle, collideOffset, m_collideCircle
    );

    // Space key released event
    if (m_spaceReleased)
    {
        m_boundingCircle2.position.vec[0] = m_collideCircle.position.vec[0];
        m_boundingCircle2.position.vec[1] = m_collideCircle.position.vec[1];
        m_spaceReleased = false;
    }*/
}

////////////////////////////////////////////////////////////////////////////////
//  Render game                                                               //
////////////////////////////////////////////////////////////////////////////////
void Game::render()
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
    if (m_backRenderer.startRenderPass())
    {
        // Set back renderer view
        m_backRenderer.setDefaultView();

        // Render sprite
        GRenderer.bindPipeline(RENDERER_PIPELINE_DEFAULT);
        GRenderer.bindDefaultVertexBuffer();
        m_sprite.bindTexture();
        m_sprite.render();

        // End back rendering
        m_backRenderer.endRenderPass();
    }

    // Start rendering
    GRenderer.startRenderPass();

    // Set freefly camera
    GRenderer.setCamera(m_freeflycam);

    // Set orbital camera
    //GRenderer.setCamera(m_orbitalcam);

    // Render skybox
    GRenderer.bindPipeline(RENDERER_PIPELINE_SKYBOX);
    m_skybox.setPosition(m_freeflycam.getPosition());
    //m_skybox.setPosition(m_orbitalcam.getPosition());
    m_skybox.bindVertexBuffer();
    m_skybox.bindCubeMap();
    m_skybox.render();

    // Render cuboid shape
    /*GRenderer.bindPipeline(RENDERER_PIPELINE_SHAPE);
    m_cuboid.bindVertexBuffer();
    m_cuboid.render();*/

    // Render static mesh
    /*GRenderer.bindPipeline(RENDERER_PIPELINE_STATICMESH);
    m_staticMesh.bindVertexBuffer();
    m_staticMesh.bindTexture();
    m_staticMesh.setPosition(0.0f, 0.9f, 0.0f);
    m_staticMesh.setPosition(
        m_freeflycam.getX()+2.0f,
        m_freeflycam.getY(),
        m_freeflycam.getZ()+2.0f
    );
    m_staticMesh.render();*/

    // Render heightmap stream
    GRenderer.bindPipeline(RENDERER_PIPELINE_HEIGHTMAP);
    m_heightMapStream.render();


    // Set 2D view
    /*GRenderer.setView(m_view);

    // Bind default vertex buffer
    GRenderer.bindDefaultVertexBuffer();


    // Render bounding circle
    GRenderer.bindPipeline(RENDERER_PIPELINE_ELLIPSE);
    float positionX =
        m_boundingCircle.position.vec[0]*PhysicsToRenderer;
    float positionY =
        m_boundingCircle.position.vec[1]*PhysicsToRenderer;
    float radius = m_boundingCircle.radius*PhysicsToRenderer;
    m_ellipse.setColor(0.0f, 0.8f, 0.2f, 0.8f);
    m_ellipse.setOrigin(radius, radius);
    m_ellipse.setPosition(positionX, positionY);
    m_ellipse.setSize(radius*2.05f, radius*2.05f);
    m_ellipse.setSmooth(0.025f);
    m_ellipse.render();

    // Render bounding circle 2
    positionX = m_boundingCircle2.position.vec[0]*PhysicsToRenderer;
    positionY = m_boundingCircle2.position.vec[1]*PhysicsToRenderer;
    radius = m_boundingCircle2.radius*PhysicsToRenderer;
    m_ellipse.setColor(0.0f, 0.2f, 0.8f, 0.8f);
    m_ellipse.setOrigin(radius, radius);
    m_ellipse.setPosition(positionX, positionY);
    m_ellipse.setSize(radius*2.04f, radius*2.04f);
    m_ellipse.setSmooth(0.022f);
    m_ellipse.render();

    // Render bounding circle 2 projection
    positionX = m_collideCircle.position.vec[0]*PhysicsToRenderer;
    positionY = m_collideCircle.position.vec[1]*PhysicsToRenderer;
    radius = m_boundingCircle2.radius*PhysicsToRenderer;
    m_ellipse.setColor(0.8f, 0.2f, 0.8f, 0.8f);
    if (m_collideCircle.collide)
    {
        m_ellipse.setColor(0.8f, 0.2f, 0.2f, 0.8f);
    }
    m_ellipse.setOrigin(radius, radius);
    m_ellipse.setPosition(positionX, positionY);
    m_ellipse.setSize(radius*2.07f, radius*2.07f);
    m_ellipse.setSmooth(0.028f);
    m_ellipse.render();*/


    // Set default screen view
    GRenderer.m_mainRenderer.setDefaultView();

    // Bind default vertex buffer
    GRenderer.bindDefaultVertexBuffer();

    // Render back rendered frame
    GRenderer.bindPipeline(RENDERER_PIPELINE_DEFAULT);
    m_backRenderer.bind();
    m_sprite.render();

    // Render sprite
    /*GRenderer.bindPipeline(RENDERER_PIPELINE_DEFAULT);
    m_sprite.bindTexture();
    m_sprite.render();*/

    // Render procedural sprite
    /*m_procSprite.bindPipeline();
    m_procSprite.render();*/

    // Render rectangle
    /*GRenderer.bindPipeline(RENDERER_PIPELINE_RECTANGLE);
    m_rectanle.render();*/

    // Render ellipse
    /*GRenderer.bindPipeline(RENDERER_PIPELINE_ELLIPSE);
    m_ellipse.render();*/

    // Render window
    /*GRenderer.bindPipeline(RENDERER_PIPELINE_NINEPATCH);
    m_guiWindow.bindTexture();
    m_guiWindow.render();*/

    // Render pixel text (framerate)
    GRenderer.bindPipeline(RENDERER_PIPELINE_PXTEXT);
    m_pxText.bindTexture();
    m_pxText.setPosition(-ratio, 1.0f-(m_pxText.getHeight()*0.7f));
    m_pxText.render();

    // Render pixel text (camera position)
    std::ostringstream camerastr;
    camerastr << "X : " << m_freeflycam.getX() <<
        " | Y : " << m_freeflycam.getY() <<
        " | Z : " << m_freeflycam.getZ();
    m_pxText.setText(camerastr.str());
    m_pxText.setPosition(-ratio, 0.96f-(m_pxText.getHeight()*0.7f));
    m_pxText.render();

    // Render cursor
    /*GRenderer.bindPipeline(RENDERER_PIPELINE_DEFAULT);
    m_cursor.setPosition(m_mouseX, m_mouseY);
    m_cursor.bindTexture();
    m_cursor.render();*/

    // End rendering
    GRenderer.endRenderPass();


    // Start final pass
    GRenderer.startFinalPass();

    // Render main compositing quad
    GRenderer.setDefaultView();
    GRenderer.bindPipeline(RENDERER_PIPELINE_COMPOSITING);
    GRenderer.bindDefaultVertexBuffer();
    GRenderer.m_mainRenderer.bind();
    GRenderer.m_mainSprite.setSize(
        (GSwapchain.ratio*2.0f)+RendererCompositingQuadOffset,
        2.0f+RendererCompositingQuadOffset
    );
    GRenderer.m_mainSprite.centerOrigin();
    GRenderer.m_mainSprite.setPosition(0.0f, 0.0f);
    GRenderer.m_mainSprite.render();

    // End final pass
    GRenderer.endFinalPass();


    // End frame rendering
    GRenderer.endFrame();
}
