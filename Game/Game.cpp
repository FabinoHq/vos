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
Game::Game(Renderer& renderer, Resources& resources) :
m_renderer(renderer),
m_resources(resources),
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
m_guiWindow(),
m_staticMesh(),
m_heightMapChunk(),
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


    // Init skybox
    if (!m_skybox.init(m_resources,
        m_resources.textures.cubemap(TEXTURE_CUBEMAPTEST)))
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
    if (!m_cuboid.init(m_resources))
    {
        // Could not init cuboid shape
        return false;
    }


    // Init GUI window
    if (!m_guiWindow.init(
        m_resources.textures.gui(TEXTURE_WINDOW), 1.0f, 1.0f, 3.75f))
    {
        // Could not init GUI window
        return false;
    }


    // Init static mesh
    if (!m_staticMesh.init(
        m_resources.meshes.mesh(MESHES_TEST),
        m_resources.textures.high(TEXTURE_TEST)))
    {
        // Could not init static mesh
        return false;
    }

    // Init heightmap chunk
    if (!m_heightMapChunk.init(
        m_resources.heightmaps.heightmap(HEIGHTMAP_DEFAULT),
        m_resources.textures.high(TEXTURE_TEST)))
    {
        // Could not init heightmap chunk
        return false;
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
    m_procSprite.destroyProcSprite(m_renderer);

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


////////////////////////////////////////////////////////////////////////////////
//  Compute game events                                                       //
////////////////////////////////////////////////////////////////////////////////
void Game::events(Event& event)
{
    // Renderer scale and ratio
    float scale = m_renderer.getScale();
    float ratio = m_renderer.getRatio();

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
                    m_freeflycam.setSpeed(50.0f);
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
                    m_freeflycam.setSpeed(5.0f);
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
            //m_guiWindow.mouseMove(m_mouseX, m_mouseY);
            //m_guiWindow.updateCursor(m_renderer, m_mouseX, m_mouseY);
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
    // Compute frame
    m_view.compute(m_renderer);
    m_camera.compute(m_renderer);
    m_freeflycam.compute(m_renderer, frametime);
    m_orbitalcam.compute(m_renderer, frametime);

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
    // Set freefly camera
    m_renderer.setCamera(m_freeflycam);

    // Set orbital camera
    //m_renderer.setCamera(m_orbitalcam);

    // Render skybox
    m_renderer.bindSkyBoxPipeline();
    m_skybox.setPosition(m_freeflycam.getPosition());
    //m_skybox.setPosition(m_orbitalcam.getPosition());
    m_skybox.bindVertexBuffer(m_renderer);
    m_skybox.render(m_renderer);

    // Render cuboid shape
    /*m_renderer.bindShapePipeline();
    m_cuboid.bindVertexBuffer(m_renderer);
    m_cuboid.render(m_renderer);*/

    // Render static mesh
    /*m_renderer.bindStaticMeshPipeline();
    m_staticMesh.bindVertexBuffer(m_renderer);
    m_staticMesh.render(m_renderer);*/

    // Render heightmap chunk
    m_renderer.bindStaticMeshPipeline();
    m_heightMapChunk.bindVertexBuffer(m_renderer);
    m_heightMapChunk.render(m_renderer);


    // Set 2D view
    m_renderer.setView(m_view);

    // Bind default vertex buffer
    m_renderer.bindDefaultVertexBuffer();


    // Render bounding circle
    /*m_renderer.bindEllipsePipeline();
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
    m_ellipse.setSize(radius*2.04f, radius*2.04f);
    m_ellipse.setSmooth(0.022f);
    m_ellipse.render(m_renderer);

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
    m_ellipse.render(m_renderer);*/


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
}
