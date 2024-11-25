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
//     Softwares/FirstPerson/FirstPerson.cpp : FirstPerson class management   //
////////////////////////////////////////////////////////////////////////////////
#include "FirstPerson.h"


////////////////////////////////////////////////////////////////////////////////
//  FirstPerson global instance                                               //
////////////////////////////////////////////////////////////////////////////////
FirstPerson GFirstPerson = FirstPerson();


////////////////////////////////////////////////////////////////////////////////
//  FirstPerson default constructor                                           //
////////////////////////////////////////////////////////////////////////////////
FirstPerson::FirstPerson() :
m_backRenderer(),
m_view(),
m_camera(),
m_freeflycam(),
m_farflycam(),
m_orbitalcam(),
m_skybox(),
m_skyproc(),
m_sprite(),
m_procSprite(),
m_rectangle(),
m_ellipse(),
m_cuboid(),
m_plane(),
m_cursor(),
m_pxText(),
m_staticMesh(),
m_heightMapStream(),
m_heightFarStream(),
m_seaNearStream(),
m_seaFarStream(),
m_spaceReleased(false)
{

}

////////////////////////////////////////////////////////////////////////////////
//  FirstPerson destructor                                                    //
////////////////////////////////////////////////////////////////////////////////
FirstPerson::~FirstPerson()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Init first person game                                                    //
//  return : True if first person game is ready, false otherwise              //
////////////////////////////////////////////////////////////////////////////////
bool FirstPerson::init()
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
    m_freeflycam.setY(550.0f);
    m_freeflycam.setNearPlane(CameraDefaultNearPlane);
    m_freeflycam.setFarPlane(CameraDefaultFarPlane);

    // Init freefly camera far
    if (!m_farflycam.init())
    {
        // Could not init freefly camera
        return false;
    }
    m_farflycam.setPosition(m_freeflycam.getPosition());
    m_farflycam.setNearPlane(CameraDistanceNearPlane);
    m_farflycam.setFarPlane(CameraDistanceFarPlane);


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
    if (!m_skybox.init(GResources.textures.cubemap(TEXTURE_CUBEMAPTEST)))
    {
        // Could not init skybox
        return false;
    }

    // Init procedural skybox
    if (!m_skyproc.init())
    {
        // Could not init procedural skybox
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

    // Init cuboid shape
    if (!m_cuboid.init())
    {
        // Could not init cuboid shape
        return false;
    }

    // Init plane billboard
    if (!m_plane.init(GResources.textures.high(TEXTURE_TEST), 1.0f, 1.0f))
    {
        // Could not init plane billboard
        return false;
    }
    m_plane.setBillboard(PLANE_BILLBOARD_SPHERICAL);
    m_plane.setTarget(m_freeflycam);


    // Init GUI cursor
    if (!m_cursor.init(GResources.textures.gui(TEXTURE_CURSOR), 64.0f))
    {
        // Could not init GUI cursor
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

    // Init heightfar stream
    if (!m_heightFarStream.init())
    {
        // Could not init heightfar stream
        return false;
    }

    // Init sea near stream
    if (!m_seaNearStream.init())
    {
        // Could not load sea near stream
        return false;
    }

    // Init sea far stream
    if (!m_seaFarStream.init())
    {
        // Could not load sea far stream
        return false;
    }

    // Load spawn heightmap chunks
    m_heightMapStream.reload(0, 0);
    m_heightFarStream.reload(0, 0);

    // Wait for spawn chunks to be loaded
    bool spawnLoaded = false;
    while (!spawnLoaded)
    {
        if (m_heightMapStream.isReady() && m_heightFarStream.isReady())
        {
            spawnLoaded = true;
        }
        else
        {
            // Release some CPU while loading
            SysSleep(ResourcesWaitSleepTime);
        }
    }

    // First person game is ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy first person game                                                 //
////////////////////////////////////////////////////////////////////////////////
void FirstPerson::destroy()
{
    // Destroy procedural sprite
    m_procSprite.destroyProcSprite();

    // Destroy procedural skybox
    m_skyproc.destroySkyProc();


    // Destroy orbital camera
    m_orbitalcam.destroyCamera();

    // Destroy freefly camera far
    m_farflycam.destroyCamera();

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
//  Compute first person game events                                          //
////////////////////////////////////////////////////////////////////////////////
void FirstPerson::events(SysEvent& event)
{
    // Process event
    switch (event.type)
    {
        // Key pressed
        case SYSEVENT_KEYPRESSED:
            switch (event.key)
            {
                case SYSEVENT_KEY_Z:
                    m_freeflycam.setForward(true);
                    break;

                case SYSEVENT_KEY_S:
                    m_freeflycam.setBackward(true);
                    break;

                case SYSEVENT_KEY_Q:
                    m_freeflycam.setLeftward(true);
                    break;

                case SYSEVENT_KEY_D:
                    m_freeflycam.setRightward(true);
                    break;

                case SYSEVENT_KEY_SPACE:
                    break;

                case SYSEVENT_KEY_LSHIFT:
                    m_freeflycam.setSpeed(300.0f);
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
                    m_freeflycam.setForward(false);
                    break;

                case SYSEVENT_KEY_S:
                    m_freeflycam.setBackward(false);
                    break;

                case SYSEVENT_KEY_Q:
                    m_freeflycam.setLeftward(false);
                    break;

                case SYSEVENT_KEY_D:
                    m_freeflycam.setRightward(false);
                    break;

                case SYSEVENT_KEY_SPACE:
                    m_spaceReleased = true;
                    break;

                case SYSEVENT_KEY_LSHIFT:
                    m_freeflycam.setSpeed(10.0f);
                    break;

                default:
                    break;
            }
            break;

        // Mouse moved
        case SYSEVENT_MOUSEMOVED:
        {
            // Compute mouse events
            m_freeflycam.mouseMove(GSysMouse.deltaX, GSysMouse.deltaY);
            //m_orbitalcam.mouseMove(GSysMouse.deltaX, GSysMouse.deltaY);
            break;
        }

        // Mouse button pressed
        case SYSEVENT_MOUSEPRESSED:
            if (event.mouse.button == SYSEVENT_MOUSE_LEFT)
            {
                //m_orbitalcam.mousePress();
            }
            break;

        // Mouse button released
        case SYSEVENT_MOUSERELEASED:
            if (event.mouse.button == SYSEVENT_MOUSE_LEFT)
            {
                //m_orbitalcam.mouseRelease();
            }
            break;

        // Mouse wheel
        case SYSEVENT_MOUSEWHEEL:
            //m_orbitalcam.mouseWheel(event.mouse.wheel);
            break;

        default:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Compute first person game logic                                           //
////////////////////////////////////////////////////////////////////////////////
void FirstPerson::compute(float frametime)
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


    // Start uniforms upload
    if (GUniformchain.startUpload())
    {
        // Compute world lights
        GWorldLight.time += frametime*0.01f;
        if (GWorldLight.time >= 1.0f)
        {
            GWorldLight.time -= 2.0f;
        }
        GWorldLight.compute(m_freeflycam.getPosition());

        // Compute views
        GRenderer.computeDefaultView();
        GMainRenderer.computeDefaultView();
        m_backRenderer.computeDefaultView();
        m_view.compute(GSwapchain.ratio);

        // Compute cameras
        m_camera.compute(GSwapchain.ratio);
        m_freeflycam.compute(GSwapchain.ratio, frametime);
        m_farflycam.compute(GSwapchain.ratio, m_freeflycam);
        m_orbitalcam.compute(GSwapchain.ratio, frametime);

        // End uniforms upload
        GUniformchain.endUpload();
    }

    // Update heightmap
    m_heightMapStream.update(
        Math::divide(m_freeflycam.getX(), HeightMapChunkXStride),
        Math::divide(m_freeflycam.getZ(), HeightMapChunkZStride)
    );

    // Update heightfar
    m_heightFarStream.update(
        Math::divide(m_freeflycam.getX(), HeightFarChunkXStride),
        Math::divide(m_freeflycam.getZ(), HeightFarChunkZStride)
    );

    // Rotate test static mesh
    m_staticMesh.rotateX(0.035f*frametime);
    m_staticMesh.rotateY(0.1f*frametime);
    m_staticMesh.rotateZ(0.075f*frametime);

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
//  Compute first person game physics (threaded)                              //
////////////////////////////////////////////////////////////////////////////////
void FirstPerson::physics(int64_t tick)
{

}

////////////////////////////////////////////////////////////////////////////////
//  Render first person game                                                  //
////////////////////////////////////////////////////////////////////////////////
void FirstPerson::render()
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

    // Bind world lights
    GWorldLight.bind();

    // Set freefly camera
    m_freeflycam.bind();

    // Set orbital camera
    //m_orbitalcam.bind();

    // Render skybox
    /*GRenderer.bindPipeline(RENDERER_PIPELINE_SKYBOX);
    GRenderer.bindVertexBuffer(MESHES_SKYBOX);
    m_skybox.setPosition(m_freeflycam.getPosition());
    //m_skybox.setPosition(m_orbitalcam.getPosition());
    m_skybox.bindCubeMap();
    m_skybox.render();*/

    // Render procedural skybox
    m_skyproc.bindPipeline();
    GRenderer.bindVertexBuffer(MESHES_SKYBOX);
    m_skyproc.setPosition(m_freeflycam.getPosition());
    //m_skyproc.setPosition(m_orbitalcam.getPosition());
    m_skyproc.render();

    // Render heightfar stream
    m_farflycam.bind();
    GRenderer.bindPipeline(RENDERER_PIPELINE_HEIGHTFAR);
    m_heightFarStream.render();

    // Render seafar stream
    GRenderer.bindPipeline(RENDERER_PIPELINE_SEAFAR);
    GRenderer.bindVertexBuffer(MESHES_SEAFAR);
    m_seaFarStream.render(
        m_heightFarStream.getChunkX(), m_heightFarStream.getChunkY()
    );


    // Clear depth buffer
    GMainRenderer.clearDepth();

    // Render heightmap stream
    m_freeflycam.bind();
    GRenderer.bindPipeline(RENDERER_PIPELINE_HEIGHTMAP);
    m_heightMapStream.render();

    // Render seanear stream
    GRenderer.bindPipeline(RENDERER_PIPELINE_SEANEAR);
    GRenderer.bindVertexBuffer(MESHES_SEANEAR);
    m_seaNearStream.render(
        m_heightMapStream.getChunkX(), m_heightMapStream.getChunkY()
    );

    // Render static mesh
    /*GRenderer.bindPipeline(RENDERER_PIPELINE_STATICMESH);
    m_staticMesh.bindVertexBuffer();
    m_staticMesh.bindTexture();
    m_staticMesh.setPosition(0.0f, 700.0f, 0.0f);
    m_staticMesh.setScale(10.0f);
    m_staticMesh.render();*/

    // Render cuboid shape
    /*GRenderer.bindPipeline(RENDERER_PIPELINE_STATICPROC);
    GRenderer.bindVertexBuffer(MESHES_CUBOID);
    m_cuboid.setScale(10.0f);
    m_cuboid.setPosition(0.0f, 700.0f, 0.0f);
    m_cuboid.render();*/

    // Render plane billboard
    GRenderer.bindPipeline(RENDERER_PIPELINE_STATICMESH);
    GRenderer.bindVertexBuffer(MESHES_PLANE);
    m_plane.bindTexture();
    m_plane.setPosition(0.0f, 700.0f, 0.0f);
    m_plane.setSize(10.0f, 10.0f, 1.0f);
    m_plane.render();


    // Set 2D view
    m_view.bind();

    // Bind default vertex buffer
    GRenderer.bindVertexBuffer(MESHES_DEFAULT);


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

    // Render pixel text (camera position)
    std::ostringstream camerastr;
    camerastr << "X : " << m_freeflycam.getX() <<
        " | Y : " << m_freeflycam.getY() <<
        " | Z : " << m_freeflycam.getZ();
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
    /*GRenderer.bindPipeline(RENDERER_PIPELINE_DEFAULT);
    m_cursor.setPosition(GSysMouse.mouseX, GSysMouse.mouseY);
    m_cursor.bindTexture();
    m_cursor.render();*/

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
