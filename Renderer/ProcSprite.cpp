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
//     Renderer/ProcSprite.cpp : Procedural sprite management                 //
////////////////////////////////////////////////////////////////////////////////
#include "ProcSprite.h"
#include "Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  ProcSprite default constructor                                            //
////////////////////////////////////////////////////////////////////////////////
ProcSprite::ProcSprite() :
Transform2(),
m_pipeline(),
m_color(1.0f, 1.0f, 1.0f, 1.0f)
{

}

////////////////////////////////////////////////////////////////////////////////
//  ProcSprite virtual destructor                                             //
////////////////////////////////////////////////////////////////////////////////
ProcSprite::~ProcSprite()
{
    m_color.reset();
}


////////////////////////////////////////////////////////////////////////////////
//  Init procedural sprite                                                    //
//  return : True if the proc sprite is successfully created                  //
////////////////////////////////////////////////////////////////////////////////
bool ProcSprite::init(Renderer& renderer, const uint32_t* fragmentSource,
    const size_t fragmentSize, float width, float height)
{
    bool shaderCreated = false;
    if (fragmentSource && (fragmentSize > 0))
    {
        // Create procedural sprite pipeline
        m_pipeline.createVertexShader(
            DefaultVertexShader, DefaultVertexShaderSize
        );
        m_pipeline.createFragmentShader(
            fragmentSource, fragmentSize
        );
        if (m_pipeline.createPipeline(renderer))
        {
            shaderCreated = true;
        }
    }

    if (!shaderCreated)
    {
        // Create default procedural sprite pipeline
        m_pipeline.createVertexShader(
            DefaultVertexShader, DefaultVertexShaderSize
        );
        m_pipeline.createFragmentShader(
            DefaultProcFragmentShader, DefaultProcFragmentShaderSize
        );
        if (!m_pipeline.createPipeline(renderer))
        {
            // Could not create default procedural sprite pipeline
            return false;
        }
    }

    // Reset procedural sprite transformations
    resetTransforms();

    // Set procedural sprite size
    setSize(width, height);

    // Center procedural sprite origin (anchor)
    centerOrigin();

    // Reset procedural sprite color
    m_color.set(1.0f, 1.0f, 1.0f, 1.0f);

    // Procedural sprite successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Destroy procedural sprite                                                 //
////////////////////////////////////////////////////////////////////////////////
void ProcSprite::destroyProcSprite()
{
    m_color.reset();
    m_pipeline.destroyPipeline();
    resetTransforms();
}

////////////////////////////////////////////////////////////////////////////////
//  Set procedural sprite color                                               //
////////////////////////////////////////////////////////////////////////////////
void ProcSprite::setColor(const Vector4& color)
{
    m_color.vec[0] = color.vec[0];
    m_color.vec[1] = color.vec[1];
    m_color.vec[2] = color.vec[2];
    m_color.vec[3] = color.vec[3];
}

////////////////////////////////////////////////////////////////////////////////
//  Set procedural sprite color                                               //
////////////////////////////////////////////////////////////////////////////////
void ProcSprite::setColor(float red, float green, float blue, float alpha)
{
    m_color.vec[0] = red;
    m_color.vec[1] = green;
    m_color.vec[2] = blue;
    m_color.vec[3] = alpha;
}

////////////////////////////////////////////////////////////////////////////////
//  Set procedural sprite red channel                                         //
////////////////////////////////////////////////////////////////////////////////
void ProcSprite::setRed(float red)
{
    m_color.vec[0] = red;
}

////////////////////////////////////////////////////////////////////////////////
//  Set procedural sprite green channel                                       //
////////////////////////////////////////////////////////////////////////////////
void ProcSprite::setGreen(float green)
{
    m_color.vec[1] = green;
}

////////////////////////////////////////////////////////////////////////////////
//  Set procedural sprite blue channel                                        //
////////////////////////////////////////////////////////////////////////////////
void ProcSprite::setBlue(float blue)
{
    m_color.vec[2] = blue;
}

////////////////////////////////////////////////////////////////////////////////
//  Set procedural sprite alpha channel                                       //
////////////////////////////////////////////////////////////////////////////////
void ProcSprite::setAlpha(float alpha)
{
    m_color.vec[3] = alpha;
}


////////////////////////////////////////////////////////////////////////////////
//  Bind procedural sprite pipeline                                           //
////////////////////////////////////////////////////////////////////////////////
void ProcSprite::bindPipeline(Renderer& renderer)
{
    // Bind procedural sprite shader
    m_pipeline.bind(renderer);
}

////////////////////////////////////////////////////////////////////////////////
//  Render procedural sprite                                                  //
////////////////////////////////////////////////////////////////////////////////
void ProcSprite::render(Renderer& renderer)
{
    // Compute sprite transformations
    computeTransforms();

    // Push model matrix into command buffer
    vkCmdPushConstants(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        renderer.m_layout.handle, VK_SHADER_STAGE_VERTEX_BIT,
        PushConstantMatrixOffset, PushConstantMatrixSize, m_matrix.mat
    );

    // Push constants into command buffer
    PushConstantData pushConstants;
    pushConstants.color[0] = m_color.vec[0];
    pushConstants.color[1] = m_color.vec[1];
    pushConstants.color[2] = m_color.vec[2];
    pushConstants.color[3] = m_color.vec[3];
    pushConstants.offset[0] = 0.0f;
    pushConstants.offset[1] = 0.0f;
    pushConstants.size[0] = 1.0f;
    pushConstants.size[1] = 1.0f;
    pushConstants.time = 0.0f;

    vkCmdPushConstants(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        renderer.m_layout.handle, VK_SHADER_STAGE_FRAGMENT_BIT,
        PushConstantDataOffset, PushConstantDataSize, &pushConstants
    );

    // Draw procedural sprite triangles
    vkCmdDrawIndexed(
        renderer.m_swapchain.commandBuffers[renderer.m_swapchain.current],
        6, 1, 0, 0, 0
    );
}
