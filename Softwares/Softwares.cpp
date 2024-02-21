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
//     Softwares/Softwares.cpp : Softwares management                         //
////////////////////////////////////////////////////////////////////////////////
#include "Softwares.h"


////////////////////////////////////////////////////////////////////////////////
//  Softwares default constructor                                             //
////////////////////////////////////////////////////////////////////////////////
Softwares::Softwares()
{

}

////////////////////////////////////////////////////////////////////////////////
//  Softwares destructor                                                      //
////////////////////////////////////////////////////////////////////////////////
Softwares::~Softwares()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Init Softwares                                                            //
//  return : True if softwares are ready, false otherwise                     //
////////////////////////////////////////////////////////////////////////////////
bool Softwares::init()
{
    // Softwares are ready
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy softwares                                                         //
////////////////////////////////////////////////////////////////////////////////
void Softwares::destroy()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Compute softwares events                                                  //
////////////////////////////////////////////////////////////////////////////////
void Softwares::events(Event& event)
{
    // Process event
    switch (event.type)
    {
        // Key pressed
        case EVENT_KEYPRESSED:
            switch (event.key)
            {
                default:
                    break;
            }
            break;

        // Key released
        case EVENT_KEYRELEASED:
            switch (event.key)
            {
                case EVENT_KEY_ESCAPE:
                    break;

                default:
                    break;
            }
            break;

        // Mouse moved
        case EVENT_MOUSEMOVED:
            break;

        // Mouse button pressed
        case EVENT_MOUSEPRESSED:
            break;

        // Mouse button released
        case EVENT_MOUSERELEASED:
            break;

        // Mouse wheel
        case EVENT_MOUSEWHEEL:
            break;

        default:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Compute softwares logic                                                   //
////////////////////////////////////////////////////////////////////////////////
void Softwares::compute(float frametime)
{
    
}

////////////////////////////////////////////////////////////////////////////////
//  Render softwares                                                          //
////////////////////////////////////////////////////////////////////////////////
void Softwares::render()
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


    // Set default screen view
    GMainRenderer.bindDefaultView();

    // Bind default vertex buffer
    GRenderer.bindVertexBuffer(MESHES_DEFAULT);


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
