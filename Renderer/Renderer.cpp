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
//     Renderer/Renderer.cpp : Renderer management                            //
////////////////////////////////////////////////////////////////////////////////
#include "Renderer.h"


////////////////////////////////////////////////////////////////////////////////
//  Renderer default constructor                                              //
////////////////////////////////////////////////////////////////////////////////
Renderer::Renderer() :
m_sysWindow(0),
m_vulkanLibHandle(0),
m_vulkanInstance(0),
m_vulkanSurface(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  Renderer destructor                                                       //
////////////////////////////////////////////////////////////////////////////////
Renderer::~Renderer()
{
	// Destroy Vulkan instance
	DestroyVulkanInstance(m_vulkanInstance);

	// Free Vulkan functions
	FreeVulkanFunctions();

	// Free Vulkan library
	FreeVulkanLibrary(m_vulkanLibHandle);
}


////////////////////////////////////////////////////////////////////////////////
//  Init renderer                                                             //
//  return : True if the renderer is successfully loaded                      //
////////////////////////////////////////////////////////////////////////////////
bool Renderer::init(SysWindow* sysWindow)
{
	// Check SysWindow pointer
	if (!sysWindow)
	{
		// Invalid SysWindow pointer
		return false;
	}
	m_sysWindow = sysWindow;

	// Load Vulkan library
	if (!LoadVulkanLibrary(m_vulkanLibHandle))
	{
		// Could not load Vulkan library
		return false;
	}

	// Load Vulkan GetInstance function
	if (!LoadVulkanGetInstance(m_vulkanLibHandle))
	{
		// Could not load Vulkan GetInstance function
		return false;
	}

	// Load Vulkan global functions
	if (!LoadVulkanGlobalFunctions())
	{
		// Could not load Vulkan global functions
		return false;
	}

	// Create Vulkan instance
	if (!CreateVulkanInstance(m_vulkanInstance))
	{
		// Could not create Vulkan instance
		return false;
	}

	// Load Vulkan CreateSystemSurface
	if (!LoadVulkanCreateSystemSurface(m_vulkanInstance))
	{
		// Could not load Vulkan CreateSystemSurface function
		return false;
	}

	// Create Vulkan SystemSurface
	if (!CreateVulkanSystemSurface(
		m_vulkanInstance, *m_sysWindow, m_vulkanSurface))
	{
		// Could not create Vulkan SystemSurface
		return false;
	}

	// Load Vulkan instance functions
	if (!LoadVulkanInstanceFunctions(m_vulkanInstance))
	{
		// Could not load Vulkan instance functions
		return false;
	}

	// Select Vulkan device
	if (!SelectVulkanDevice(m_vulkanInstance))
	{
		// Could not select Vulkan device
		return false;
	}

	// Renderer successfully loaded
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Clear renderer frame                                                      //
////////////////////////////////////////////////////////////////////////////////
void Renderer::clear()
{

}
