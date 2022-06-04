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
m_view(),
m_camera(),
m_freeflycam(),
m_orbitalcam(),
m_cubemap(),
m_skybox(),
m_procSprite(),
m_rectanle(),
m_ellipse(),
m_cuboid(),
m_pxFontTexture(),
m_pxText(),
m_windowTexture(),
m_guiWindow(),
m_testTexture(),
m_staticMesh(),
m_heightMapChunk(),
m_boundingCircle(),
m_boundingCircle2(),
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

    // Init orbital camera
    if (!m_orbitalcam.init(m_renderer))
    {
        // Could not init orbital camera
        return false;
    }
    m_orbitalcam.setZ(1.0f);
    m_orbitalcam.setTarget(0.0f, 0.0f, 0.0f);
    m_orbitalcam.setDistance(2.0f);
    m_orbitalcam.setSpeed(50.0f);


    // Load cubemap textures
    PNGFile cubeMapRight;
    if (!cubeMapRight.loadImage("Textures/testsprite.png"))
    {
        return false;
    }
    PNGFile cubeMapLeft;
    if (!cubeMapLeft.loadImage("Textures/testsprite.png"))
    {
        return false;
    }
    PNGFile cubeMapTop;
    if (!cubeMapTop.loadImage("Textures/testsprite.png"))
    {
        return false;
    }
    PNGFile cubeMapBottom;
    if (!cubeMapBottom.loadImage("Textures/testsprite.png"))
    {
        return false;
    }
    PNGFile cubeMapFront;
    if (!cubeMapFront.loadImage("Textures/testsprite.png"))
    {
        return false;
    }
    PNGFile cubeMapBack;
    if (!cubeMapBack.loadImage("Textures/testsprite.png"))
    {
        return false;
    }

    // Allocate cubemap data
    unsigned int cubemapWidth = cubeMapFront.getWidth();
    unsigned int cubemapHeight = cubeMapFront.getHeight();
    unsigned char* cubemapData = 0;
    try
    {
        cubemapData = new unsigned char[cubemapWidth*cubemapHeight*4*6];
    }
    catch (const std::bad_alloc&)
    {
        cubemapData = 0;
    }
    catch (...)
    {
        cubemapData = 0;
    }
    if (!cubemapData)
    {
        return false;
    }

    // Copy cubemap data
    memcpy(
        &cubemapData[cubemapWidth*cubemapHeight*4*0],
        cubeMapRight.getImage(), cubemapWidth*cubemapHeight*4
    );
    memcpy(
        &cubemapData[cubemapWidth*cubemapHeight*4*1],
        cubeMapLeft.getImage(), cubemapWidth*cubemapHeight*4
    );
    memcpy(
        &cubemapData[cubemapWidth*cubemapHeight*4*2],
        cubeMapTop.getImage(), cubemapWidth*cubemapHeight*4
    );
    memcpy(
        &cubemapData[cubemapWidth*cubemapHeight*4*3],
        cubeMapBottom.getImage(), cubemapWidth*cubemapHeight*4
    );
    memcpy(
        &cubemapData[cubemapWidth*cubemapHeight*4*4],
        cubeMapFront.getImage(), cubemapWidth*cubemapHeight*4
    );
    memcpy(
        &cubemapData[cubemapWidth*cubemapHeight*4*5],
        cubeMapBack.getImage(), cubemapWidth*cubemapHeight*4
    );

    // Cleanup cubemap textures
    cubeMapRight.destroyImage();
    cubeMapLeft.destroyImage();
    cubeMapTop.destroyImage();
    cubeMapBottom.destroyImage();
    cubeMapFront.destroyImage();
    cubeMapBack.destroyImage();

    // Create cubemap texture
    if (!m_cubemap.updateCubeMap(
        m_renderer, cubemapWidth, cubemapHeight, cubemapData, true))
    {
        // Could not load cubemap texture
        return false;
    }

    // Init skybox
    if (!m_skybox.init(m_renderer, m_cubemap))
    {
        // Could not init skybox
        return false;
    }


    // Init procedural sprite
    if (!m_procSprite.init(m_renderer, 0, 0, 1.0f, 1.0f))
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
    if (!m_cuboid.init(m_renderer, 1.0f, 1.0f, 1.0f))
    {
        // Could not init cuboid shape
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


    // Load window texture
    if (!m_windowTexture.updateTexture(m_renderer,
        WindowImageWidth, WindowImageHeight, WindowImage,
        true, false))
    {
        // Could not load window texture
        return false;
    }

    // Init GUI window
    if (!m_guiWindow.init(m_windowTexture, 1.0f, 1.0f, 3.75f))
    {
        // Could not init GUI window
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


    // Init bounding circle
    m_boundingCircle.setPosition(-200000000, 0);
    m_boundingCircle.setRadius(100000000);

    // Init bounding circle 2
    m_boundingCircle2.setPosition(200000000, 0);
    m_boundingCircle2.setRadius(100000000);


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

        // Space key released event
        bool spaceReleased = false;

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

                        case EVENT_KEY_SPACE:
                            spaceReleased = true;
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
                    m_orbitalcam.mouseMove(
                        event.mouse.x*1.0f, event.mouse.y*1.0f
                    );
                    //m_guiWindow.mouseMove(m_mouseX, m_mouseY);
                    //m_guiWindow.updateCursor(m_renderer, m_mouseX, m_mouseY);
                    break;

                // Mouse button pressed
                case EVENT_MOUSEPRESSED:
                    if (event.mouse.button == EVENT_MOUSE_LEFT)
                    {
                        m_orbitalcam.mousePress();
                        //m_guiWindow.mousePress(m_mouseX, m_mouseY);
                    }
                    break;

                // Mouse button released
                case EVENT_MOUSERELEASED:
                    if (event.mouse.button == EVENT_MOUSE_LEFT)
                    {
                        m_orbitalcam.mouseRelease();
                        //m_guiWindow.mouseRelease(m_mouseX, m_mouseY);
                    }
                    break;

                // Mouse wheel
                case EVENT_MOUSEWHEEL:
                    m_orbitalcam.mouseWheel(event.mouse.wheel);
                    break;

                default:
                    break;
            }
        }

        // Compute frame
        m_view.compute(m_renderer);
        m_camera.compute(m_renderer);
        m_freeflycam.compute(m_renderer, frametime);
        m_orbitalcam.compute(m_renderer, frametime);

        // Compute physics
        /*m_boundingCircle2.position.vec[0] =
            static_cast<int64_t>(m_mouseX*1000000000);
        m_boundingCircle2.position.vec[1] =
            static_cast<int64_t>(m_mouseY*1000000000);*/
        Vector2i collideOffset;
        collideOffset.vec[0] = static_cast<int64_t>(m_mouseX*1000000000);
        collideOffset.vec[1] = static_cast<int64_t>(m_mouseY*1000000000);
        collideOffset.vec[0] -= m_boundingCircle2.position.vec[0];
        collideOffset.vec[1] -= m_boundingCircle2.position.vec[1];
        Collision2 collideCircle;
        collideCircle.reset();
        m_boundingCircle2.collideCircle(
            m_boundingCircle, collideOffset, collideCircle
        );

        // Space key released event
        if (spaceReleased)
        {
            m_boundingCircle2.position.vec[0] = collideCircle.position.vec[0];
            m_boundingCircle2.position.vec[1] = collideCircle.position.vec[1];
            spaceReleased = false;
        }

        // Render frame
        if (m_renderer.startFrame())
        {
            // Set freefly camera
            //m_renderer.setCamera(m_freeflycam);

            // Set orbital camera
            m_renderer.setCamera(m_orbitalcam);

            // Render skybox
            /*m_renderer.bindSkyBoxPipeline();
            //m_skybox.setPosition(m_freeflycam.getPosition());
            m_skybox.setPosition(m_orbitalcam.getPosition());
            m_skybox.bindVertexBuffer(m_renderer);
            m_skybox.render(m_renderer);*/

            // Render cuboid shape
            /*m_renderer.bindShapePipeline();
            m_cuboid.bindVertexBuffer(m_renderer);
            m_cuboid.render(m_renderer);*/

            // Render static mesh
            /*m_renderer.bindStaticMeshPipeline();
            m_staticMesh.bindVertexBuffer(m_renderer);
            m_staticMesh.render(m_renderer);*/

            // Render heightmap chunk
            /*m_renderer.bindStaticMeshPipeline();
            m_heightMapChunk.bindVertexBuffer(m_renderer);
            m_heightMapChunk.render(m_renderer);*/


            // Set 2D view
            m_renderer.setView(m_view);

            // Render bounding circle
            m_renderer.bindEllipsePipeline();
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
            m_ellipse.render(m_renderer);

            // Render bounding circle 2
            positionX = m_boundingCircle2.position.vec[0]*PhysicsToRenderer;
            positionY = m_boundingCircle2.position.vec[1]*PhysicsToRenderer;
            radius = m_boundingCircle2.radius*PhysicsToRenderer;
            m_ellipse.setColor(0.0f, 0.2f, 0.8f, 0.8f);
            m_ellipse.setOrigin(radius, radius);
            m_ellipse.setPosition(positionX, positionY);
            m_ellipse.setSize(radius*2.05f, radius*2.05f);
            m_ellipse.setSmooth(0.025f);
            m_ellipse.render(m_renderer);

            // Render bounding circle 2 projection
            positionX = collideCircle.position.vec[0]*PhysicsToRenderer;
            positionY = collideCircle.position.vec[1]*PhysicsToRenderer;
            radius = m_boundingCircle2.radius*PhysicsToRenderer;
            m_ellipse.setColor(0.8f, 0.2f, 0.8f, 0.8f);
            if (collideCircle.collide)
            {
                m_ellipse.setColor(0.8f, 0.2f, 0.2f, 0.8f);
            }
            m_ellipse.setOrigin(radius, radius);
            m_ellipse.setPosition(positionX, positionY);
            m_ellipse.setSize(radius*2.05f, radius*2.05f);
            m_ellipse.setSmooth(0.025f);
            m_ellipse.render(m_renderer);


            // Set default screen view
            m_renderer.setDefaultView();

            // Bind default vertex buffer
            m_renderer.bindDefaultVertexBuffer();

            // Render rectangle
            /*m_renderer.bindRectanglePipeline();
            m_rectanle.render(m_renderer);*/

            // Render ellipse
            /*m_renderer.bindEllipsePipeline();
            m_ellipse.render(m_renderer);*/

            // Render procedural sprite
            /*m_procSprite.bindPipeline(m_renderer);
            m_procSprite.render(m_renderer);*/

            // Render window
            /*m_renderer.bindNinePatchPipeline();
            m_guiWindow.render(m_renderer);*/

            // Render pixel text (framerate)
            m_renderer.bindPxTextPipeline();
            m_pxText.setText(framestr.str());
            m_pxText.setPosition(-ratio, 1.0f-(m_pxText.getHeight()*0.7f));
            m_pxText.render(m_renderer);

            // Render cursor
            m_renderer.bindDefaultPipeline();
            m_renderer.renderCursor(m_mouseX, m_mouseY);

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

        // Destroy cuboid
        m_cuboid.destroyCuboid(m_renderer);

        // Destroy pixel font texture
        m_pxFontTexture.destroyTexture(m_renderer);

        // Destroy window texture
        m_windowTexture.destroyTexture(m_renderer);

        // Destroy test texture
        m_testTexture.destroyTexture(m_renderer);

        // Destroy procedural sprite
        m_procSprite.destroyProcSprite(m_renderer);

        // Destroy skybox
        m_skybox.destroySkyBox(m_renderer);

        // Destroy cubemap
        m_cubemap.destroyCubeMap(m_renderer);


        // Destroy orbital camera
        m_orbitalcam.destroyCamera(m_renderer);

        // Destroy freefly camera
        m_freeflycam.destroyCamera(m_renderer);

        // Destroy camera
        m_camera.destroyCamera(m_renderer);

        // Destroy view
        m_view.destroyView(m_renderer);
    }

    // Close VOS
    m_renderer.cleanup();
    m_window.close();
}
