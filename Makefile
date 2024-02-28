################################################################################
##     _______                       ____________________________________     ##
##     \\ .   \            _________/ . . . . . . . . . . . . . . . .   /     ##
##      \\ .   \       ___/ . . . . .    ______________________________/      ##
##       \\ .   \   __/. . .   _________/     /    // .  __________/          ##
##        \\ .   \_//      ___/ .  _____     /    // .  /______               ##
##         \\ .   \/     _/ // .  /    \\    |    \\  .        \              ##
##          \\ .        /   || .  |    ||    |     \\______     \             ##
##           \\ .      /    || .  \____//    |  _________//     /             ##
##            \\ .    /     //  .            / // . . . .      /              ##
##             \\____/     //_______________/ //______________/               ##
##                                                                            ##
################################################################################
##   This is free and unencumbered software released into the public domain.  ##
##                                                                            ##
##   Anyone is free to copy, modify, publish, use, compile, sell, or          ##
##   distribute this software, either in source code form or as a compiled    ##
##   binary, for any purpose, commercial or non-commercial, and by any        ##
##   means.                                                                   ##
##                                                                            ##
##   In jurisdictions that recognize copyright laws, the author or authors    ##
##   of this software dedicate any and all copyright interest in the          ##
##   software to the public domain. We make this dedication for the benefit   ##
##   of the public at large and to the detriment of our heirs and             ##
##   successors. We intend this dedication to be an overt act of              ##
##   relinquishment in perpetuity of all present and future rights to this    ##
##   software under copyright law.                                            ##
##                                                                            ##
##   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,          ##
##   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF       ##
##   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   ##
##   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR        ##
##   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,    ##
##   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR    ##
##   OTHER DEALINGS IN THE SOFTWARE.                                          ##
##                                                                            ##
##   For more information, please refer to <https://unlicense.org>            ##
################################################################################
##    VOS : Virtual Operating System                                          ##
##     Makefile : Linux make compilation file                                 ##
################################################################################
CC=g++ -std=c++17 -O3 -fno-exceptions -fno-rtti \
	-fomit-frame-pointer -ffunction-sections \
	-fno-trapping-math -fno-math-errno -fno-signed-zeros
CFLAGS=-W -Wall
LDFLAGS=-pthread -lX11 -ldl

all: VOS

VOS: main.o \
	Vos.o \
	System/SysThread.o System/SysClock.o System/SysCPU.o \
	System/Lin/SysMessage.o System/Lin/SysDisplayMode.o \
	System/Lin/SysWindow.o System/Lin/SysVulkan.o \
	System/SysMouse.o System/SysSettings.o \
	Network/Lin/IPAddress4.o Network/Lin/IPAddress6.o \
	Network/Lin/TCPSocket.o Network/Lin/UDPSocket.o \
	Compress/ZLib.o \
	Images/BMPFile.o Images/PNGFile.o \
	Physics/Physics.o Physics/Collision2.o \
	Physics/BoundingCircle.o Physics/BoundingRect.o \
	Renderer/Vulkan/Vulkan.o Renderer/Vulkan/VulkanMemory.o \
	Renderer/Vulkan/VulkanQueue.o \
	Renderer/Vulkan/Swapchain.o Renderer/Vulkan/Backchain.o \
	Renderer/Vulkan/Uniformchain.o \
	Renderer/Vulkan/VulkanBuffer.o Renderer/Vulkan/VertexBuffer.o \
	Renderer/Vulkan/UniformBuffer.o \
	Renderer/Vulkan/GraphicsLayout.o Renderer/Vulkan/ComputeLayout.o \
	Renderer/Vulkan/Pipeline.o Renderer/Vulkan/ComputePipeline.o \
	Renderer/Vulkan/Shader.o \
	Renderer/Vulkan/Texture.o Renderer/Vulkan/TextureArray.o \
	Renderer/Vulkan/CubeMap.o \
	Renderer/View.o Renderer/Camera.o \
	Renderer/FreeFlyCam.o Renderer/OrbitalCam.o \
	Renderer/Sprite.o Renderer/ProcSprite.o \
	Renderer/Plane.o \
	Renderer/SkyBox.o Renderer/SkyProc.o \
	Renderer/StaticMesh.o \
	Renderer/HeightMapChunk.o Renderer/HeightFarChunk.o \
	Renderer/HeightMapStream.o Renderer/HeightFarStream.o \
	Renderer/SeaNearChunk.o Renderer/SeaFarChunk.o \
	Renderer/SeaNearStream.o Renderer/SeaFarStream.o \
	Renderer/WorldLight.o \
	Renderer/BackRenderer.o Renderer/Renderer.o \
	Renderer/Shapes/RectangleShape.o Renderer/Shapes/EllipseShape.o \
	Renderer/Shapes/CuboidShape.o \
	Renderer/GUI/GUICursor.o \
	Renderer/GUI/GUIPxText.o Renderer/GUI/GUIWindow.o \
	Renderer/GUI/GUIButton.o Renderer/GUI/GUIToggleButton.o \
	Renderer/GUI/GUIProgressBar.o \
	Resources/Resources.o Resources/TextureLoader.o Resources/MeshLoader.o \
	Resources/HeightMapLoader.o Resources/HeightFarLoader.o \
	Softwares/Softwares.o \
	Softwares/FirstPerson/FirstPerson.o Softwares/TopDown/TopDown.o

	$(CC) -o VOS \
	Vos.o \
	System/SysThread.o System/SysClock.o System/SysCPU.o \
	System/Lin/SysMessage.o System/Lin/SysDisplayMode.o \
	System/Lin/SysWindow.o System/Lin/SysVulkan.o \
	System/SysMouse.o System/SysSettings.o \
	Network/Lin/IPAddress4.o Network/Lin/IPAddress6.o \
	Network/Lin/TCPSocket.o Network/Lin/UDPSocket.o \
	Compress/ZLib.o \
	Images/BMPFile.o Images/PNGFile.o \
	Physics/Physics.o Physics/Collision2.o \
	Physics/BoundingCircle.o Physics/BoundingRect.o \
	Renderer/Vulkan/Vulkan.o Renderer/Vulkan/VulkanMemory.o \
	Renderer/Vulkan/VulkanQueue.o \
	Renderer/Vulkan/Swapchain.o Renderer/Vulkan/Backchain.o \
	Renderer/Vulkan/Uniformchain.o \
	Renderer/Vulkan/VulkanBuffer.o Renderer/Vulkan/VertexBuffer.o \
	Renderer/Vulkan/UniformBuffer.o \
	Renderer/Vulkan/GraphicsLayout.o Renderer/Vulkan/ComputeLayout.o \
	Renderer/Vulkan/Pipeline.o Renderer/Vulkan/ComputePipeline.o \
	Renderer/Vulkan/Shader.o \
	Renderer/Vulkan/Texture.o Renderer/Vulkan/TextureArray.o \
	Renderer/Vulkan/CubeMap.o \
	Renderer/View.o Renderer/Camera.o \
	Renderer/FreeFlyCam.o Renderer/OrbitalCam.o \
	Renderer/Sprite.o Renderer/ProcSprite.o \
	Renderer/Plane.o \
	Renderer/SkyBox.o Renderer/SkyProc.o \
	Renderer/StaticMesh.o \
	Renderer/HeightMapChunk.o Renderer/HeightFarChunk.o \
	Renderer/HeightMapStream.o Renderer/HeightFarStream.o \
	Renderer/SeaNearChunk.o Renderer/SeaFarChunk.o \
	Renderer/SeaNearStream.o Renderer/SeaFarStream.o \
	Renderer/WorldLight.o \
	Renderer/BackRenderer.o Renderer/Renderer.o \
	Renderer/Shapes/RectangleShape.o Renderer/Shapes/EllipseShape.o \
	Renderer/Shapes/CuboidShape.o \
	Renderer/GUI/GUICursor.o \
	Renderer/GUI/GUIPxText.o Renderer/GUI/GUIWindow.o \
	Renderer/GUI/GUIButton.o Renderer/GUI/GUIToggleButton.o \
	Renderer/GUI/GUIProgressBar.o \
	Resources/Resources.o Resources/TextureLoader.o Resources/MeshLoader.o \
	Resources/HeightMapLoader.o Resources/HeightFarLoader.o \
	Softwares/Softwares.o \
	Softwares/FirstPerson/FirstPerson.o Softwares/TopDown/TopDown.o \
	main.o $(LDFLAGS)


main.o: main.cpp
	$(CC) -o main.o -c main.cpp $(CFLAGS)

Vos.o: Vos.cpp
	$(CC) -o Vos.o -c Vos.cpp $(CFLAGS)


System/SysThread.o: System/SysThread.cpp
	$(CC) -o System/SysThread.o -c System/SysThread.cpp $(CFLAGS)

System/SysClock.o: System/SysClock.cpp
	$(CC) -o System/SysClock.o -c System/SysClock.cpp $(CFLAGS)

System/SysCPU.o: System/SysCPU.cpp
	$(CC) -o System/SysCPU.o -c System/SysCPU.cpp $(CFLAGS)

System/Lin/SysMessage.o: System/Lin/SysMessage.cpp
	$(CC) -o System/Lin/SysMessage.o -c System/Lin/SysMessage.cpp $(CFLAGS)

System/Lin/SysDisplayMode.o: System/Lin/SysDisplayMode.cpp
	$(CC) -o System/Lin/SysDisplayMode.o -c \
	System/Lin/SysDisplayMode.cpp $(CFLAGS)

System/Lin/SysWindow.o: System/Lin/SysWindow.cpp
	$(CC) -o System/Lin/SysWindow.o -c System/Lin/SysWindow.cpp $(CFLAGS)

System/Lin/SysVulkan.o: System/Lin/SysVulkan.cpp
	$(CC) -o System/Lin/SysVulkan.o -c System/Lin/SysVulkan.cpp $(CFLAGS)

System/SysMouse.o: System/SysMouse.cpp
	$(CC) -o System/SysMouse.o -c System/SysMouse.cpp $(CFLAGS)

System/SysSettings.o: System/SysSettings.cpp
	$(CC) -o System/SysSettings.o -c System/SysSettings.cpp $(CFLAGS)


Network/Lin/IPAddress4.o: Network/Lin/IPAddress4.cpp
	$(CC) -o Network/Lin/IPAddress4.o -c Network/Lin/IPAddress4.cpp $(CFLAGS)

Network/Lin/IPAddress6.o: Network/Lin/IPAddress6.cpp
	$(CC) -o Network/Lin/IPAddress6.o -c Network/Lin/IPAddress6.cpp $(CFLAGS)

Network/Lin/TCPSocket.o: Network/Lin/TCPSocket.cpp
	$(CC) -o Network/Lin/TCPSocket.o -c Network/Lin/TCPSocket.cpp $(CFLAGS)

Network/Lin/UDPSocket.o: Network/Lin/UDPSocket.cpp
	$(CC) -o Network/Lin/UDPSocket.o -c Network/Lin/UDPSocket.cpp $(CFLAGS)


Compress/ZLib.o: Compress/ZLib.cpp
	$(CC) -o Compress/ZLib.o -c Compress/ZLib.cpp $(CFLAGS)


Images/BMPFile.o: Images/BMPFile.cpp
	$(CC) -o Images/BMPFile.o -c Images/BMPFile.cpp $(CFLAGS)

Images/PNGFile.o: Images/PNGFile.cpp
	$(CC) -o Images/PNGFile.o -c Images/PNGFile.cpp $(CFLAGS)


Physics/Physics.o: Physics/Physics.cpp
	$(CC) -o Physics/Physics.o -c Physics/Physics.cpp $(CFLAGS)

Physics/Collision2.o: Physics/Collision2.cpp
	$(CC) -o Physics/Collision2.o -c Physics/Collision2.cpp $(CFLAGS)

Physics/BoundingCircle.o: Physics/BoundingCircle.cpp
	$(CC) -o Physics/BoundingCircle.o -c Physics/BoundingCircle.cpp $(CFLAGS)

Physics/BoundingRect.o: Physics/BoundingRect.cpp
	$(CC) -o Physics/BoundingRect.o -c Physics/BoundingRect.cpp $(CFLAGS)


Renderer/Vulkan/Vulkan.o: Renderer/Vulkan/Vulkan.cpp
	$(CC) -o Renderer/Vulkan/Vulkan.o -c Renderer/Vulkan/Vulkan.cpp $(CFLAGS)

Renderer/Vulkan/VulkanMemory.o: Renderer/Vulkan/VulkanMemory.cpp
	$(CC) -o Renderer/Vulkan/VulkanMemory.o -c \
	Renderer/Vulkan/VulkanMemory.cpp $(CFLAGS)

Renderer/Vulkan/VulkanQueue.o: Renderer/Vulkan/VulkanQueue.cpp
	$(CC) -o Renderer/Vulkan/VulkanQueue.o -c \
	Renderer/Vulkan/VulkanQueue.cpp $(CFLAGS)

Renderer/Vulkan/Swapchain.o: Renderer/Vulkan/Swapchain.cpp
	$(CC) -o Renderer/Vulkan/Swapchain.o -c \
	Renderer/Vulkan/Swapchain.cpp $(CFLAGS)

Renderer/Vulkan/Backchain.o: Renderer/Vulkan/Backchain.cpp
	$(CC) -o Renderer/Vulkan/Backchain.o -c \
	Renderer/Vulkan/Backchain.cpp $(CFLAGS)

Renderer/Vulkan/Uniformchain.o: Renderer/Vulkan/Uniformchain.cpp
	$(CC) -o Renderer/Vulkan/Uniformchain.o -c \
	Renderer/Vulkan/Uniformchain.cpp $(CFLAGS)

Renderer/Vulkan/VulkanBuffer.o: Renderer/Vulkan/VulkanBuffer.cpp
	$(CC) -o Renderer/Vulkan/VulkanBuffer.o -c \
	Renderer/Vulkan/VulkanBuffer.cpp $(CFLAGS)

Renderer/Vulkan/VertexBuffer.o: Renderer/Vulkan/VertexBuffer.cpp
	$(CC) -o Renderer/Vulkan/VertexBuffer.o -c \
	Renderer/Vulkan/VertexBuffer.cpp $(CFLAGS)

Renderer/Vulkan/UniformBuffer.o: Renderer/Vulkan/UniformBuffer.cpp
	$(CC) -o Renderer/Vulkan/UniformBuffer.o -c \
	Renderer/Vulkan/UniformBuffer.cpp $(CFLAGS)

Renderer/Vulkan/GraphicsLayout.o: Renderer/Vulkan/GraphicsLayout.cpp
	$(CC) -o Renderer/Vulkan/GraphicsLayout.o -c \
	Renderer/Vulkan/GraphicsLayout.cpp $(CFLAGS)

Renderer/Vulkan/ComputeLayout.o: Renderer/Vulkan/ComputeLayout.cpp
	$(CC) -o Renderer/Vulkan/ComputeLayout.o -c \
	Renderer/Vulkan/ComputeLayout.cpp $(CFLAGS)

Renderer/Vulkan/Pipeline.o: Renderer/Vulkan/Pipeline.cpp
	$(CC) -o Renderer/Vulkan/Pipeline.o -c \
	Renderer/Vulkan/Pipeline.cpp $(CFLAGS)

Renderer/Vulkan/ComputePipeline.o: Renderer/Vulkan/ComputePipeline.cpp
	$(CC) -o Renderer/Vulkan/ComputePipeline.o -c \
	Renderer/Vulkan/ComputePipeline.cpp $(CFLAGS)

Renderer/Vulkan/Shader.o: Renderer/Vulkan/Shader.cpp
	$(CC) -o Renderer/Vulkan/Shader.o -c Renderer/Vulkan/Shader.cpp $(CFLAGS)

Renderer/Vulkan/Texture.o: Renderer/Vulkan/Texture.cpp
	$(CC) -o Renderer/Vulkan/Texture.o -c Renderer/Vulkan/Texture.cpp $(CFLAGS)

Renderer/Vulkan/TextureArray.o: Renderer/Vulkan/TextureArray.cpp
	$(CC) -o Renderer/Vulkan/TextureArray.o -c \
	Renderer/Vulkan/TextureArray.cpp $(CFLAGS)

Renderer/Vulkan/CubeMap.o: Renderer/Vulkan/CubeMap.cpp
	$(CC) -o Renderer/Vulkan/CubeMap.o -c Renderer/Vulkan/CubeMap.cpp $(CFLAGS)

Renderer/View.o: Renderer/View.cpp
	$(CC) -o Renderer/View.o -c Renderer/View.cpp $(CFLAGS)

Renderer/Camera.o: Renderer/Camera.cpp
	$(CC) -o Renderer/Camera.o -c Renderer/Camera.cpp $(CFLAGS)

Renderer/FreeFlyCam.o: Renderer/FreeFlyCam.cpp
	$(CC) -o Renderer/FreeFlyCam.o -c Renderer/FreeFlyCam.cpp $(CFLAGS)

Renderer/OrbitalCam.o: Renderer/OrbitalCam.cpp
	$(CC) -o Renderer/OrbitalCam.o -c Renderer/OrbitalCam.cpp $(CFLAGS)

Renderer/Sprite.o: Renderer/Sprite.cpp
	$(CC) -o Renderer/Sprite.o -c Renderer/Sprite.cpp $(CFLAGS)

Renderer/ProcSprite.o: Renderer/ProcSprite.cpp
	$(CC) -o Renderer/ProcSprite.o -c Renderer/ProcSprite.cpp $(CFLAGS)

Renderer/Plane.o: Renderer/Plane.cpp
	$(CC) -o Renderer/Plane.o -c Renderer/Plane.cpp $(CFLAGS)

Renderer/SkyBox.o: Renderer/SkyBox.cpp
	$(CC) -o Renderer/SkyBox.o -c Renderer/SkyBox.cpp $(CFLAGS)

Renderer/SkyProc.o: Renderer/SkyProc.cpp
	$(CC) -o Renderer/SkyProc.o -c Renderer/SkyProc.cpp $(CFLAGS)

Renderer/StaticMesh.o: Renderer/StaticMesh.cpp
	$(CC) -o Renderer/StaticMesh.o -c Renderer/StaticMesh.cpp $(CFLAGS)

Renderer/HeightMapChunk.o: Renderer/HeightMapChunk.cpp
	$(CC) -o Renderer/HeightMapChunk.o -c Renderer/HeightMapChunk.cpp $(CFLAGS)

Renderer/HeightFarChunk.o: Renderer/HeightFarChunk.cpp
	$(CC) -o Renderer/HeightFarChunk.o -c Renderer/HeightFarChunk.cpp $(CFLAGS)

Renderer/HeightMapStream.o: Renderer/HeightMapStream.cpp
	$(CC) -o Renderer/HeightMapStream.o -c \
	Renderer/HeightMapStream.cpp $(CFLAGS)

Renderer/HeightFarStream.o: Renderer/HeightFarStream.cpp
	$(CC) -o Renderer/HeightFarStream.o -c \
	Renderer/HeightFarStream.cpp $(CFLAGS)

Renderer/SeaNearChunk.o: Renderer/SeaNearChunk.cpp
	$(CC) -o Renderer/SeaNearChunk.o -c Renderer/SeaNearChunk.cpp $(CFLAGS)

Renderer/SeaFarChunk.o: Renderer/SeaFarChunk.cpp
	$(CC) -o Renderer/SeaFarChunk.o -c Renderer/SeaFarChunk.cpp $(CFLAGS)

Renderer/SeaNearStream.o: Renderer/SeaNearStream.cpp
	$(CC) -o Renderer/SeaNearStream.o -c Renderer/SeaNearStream.cpp $(CFLAGS)

Renderer/SeaFarStream.o: Renderer/SeaFarStream.cpp
	$(CC) -o Renderer/SeaFarStream.o -c Renderer/SeaFarStream.cpp $(CFLAGS)


Renderer/WorldLight.o: Renderer/WorldLight.cpp
	$(CC) -o Renderer/WorldLight.o -c Renderer/WorldLight.cpp $(CFLAGS)


Renderer/BackRenderer.o: Renderer/BackRenderer.cpp
	$(CC) -o Renderer/BackRenderer.o -c Renderer/BackRenderer.cpp $(CFLAGS)

Renderer/Renderer.o: Renderer/Renderer.cpp
	$(CC) -o Renderer/Renderer.o -c Renderer/Renderer.cpp $(CFLAGS)


Renderer/Shapes/RectangleShape.o: Renderer/Shapes/RectangleShape.cpp
	$(CC) -o Renderer/Shapes/RectangleShape.o -c \
	Renderer/Shapes/RectangleShape.cpp $(CFLAGS)

Renderer/Shapes/EllipseShape.o: Renderer/Shapes/EllipseShape.cpp
	$(CC) -o Renderer/Shapes/EllipseShape.o -c \
	Renderer/Shapes/EllipseShape.cpp $(CFLAGS)

Renderer/Shapes/CuboidShape.o: Renderer/Shapes/CuboidShape.cpp
	$(CC) -o Renderer/Shapes/CuboidShape.o -c \
	Renderer/Shapes/CuboidShape.cpp $(CFLAGS)


Renderer/GUI/GUICursor.o: Renderer/GUI/GUICursor.cpp
	$(CC) -o Renderer/GUI/GUICursor.o -c Renderer/GUI/GUICursor.cpp $(CFLAGS)

Renderer/GUI/GUIPxText.o: Renderer/GUI/GUIPxText.cpp
	$(CC) -o Renderer/GUI/GUIPxText.o -c Renderer/GUI/GUIPxText.cpp $(CFLAGS)

Renderer/GUI/GUIWindow.o: Renderer/GUI/GUIWindow.cpp
	$(CC) -o Renderer/GUI/GUIWindow.o -c Renderer/GUI/GUIWindow.cpp $(CFLAGS)

Renderer/GUI/GUIButton.o: Renderer/GUI/GUIButton.cpp
	$(CC) -o Renderer/GUI/GUIButton.o -c Renderer/GUI/GUIButton.cpp $(CFLAGS)

Renderer/GUI/GUIToggleButton.o: Renderer/GUI/GUIToggleButton.cpp
	$(CC) -o Renderer/GUI/GUIToggleButton.o -c \
	Renderer/GUI/GUIToggleButton.cpp $(CFLAGS)

Renderer/GUI/GUIProgressBar.o: Renderer/GUI/GUIProgressBar.cpp
	$(CC) -o Renderer/GUI/GUIProgressBar.o -c \
	Renderer/GUI/GUIProgressBar.cpp $(CFLAGS)


Resources/Resources.o: Resources/Resources.cpp
	$(CC) -o Resources/Resources.o -c Resources/Resources.cpp $(CFLAGS)

Resources/TextureLoader.o: Resources/TextureLoader.cpp
	$(CC) -o Resources/TextureLoader.o -c Resources/TextureLoader.cpp $(CFLAGS)

Resources/MeshLoader.o: Resources/MeshLoader.cpp
	$(CC) -o Resources/MeshLoader.o -c Resources/MeshLoader.cpp $(CFLAGS)

Resources/HeightMapLoader.o: Resources/HeightMapLoader.cpp
	$(CC) -o Resources/HeightMapLoader.o -c \
	Resources/HeightMapLoader.cpp $(CFLAGS)

Resources/HeightFarLoader.o: Resources/HeightFarLoader.cpp
	$(CC) -o Resources/HeightFarLoader.o -c \
	Resources/HeightFarLoader.cpp $(CFLAGS)


Softwares/Softwares.o: Softwares/Softwares.cpp
	$(CC) -o Softwares/Softwares.o -c Softwares/Softwares.cpp $(CFLAGS)

Softwares/FirstPerson/FirstPerson.o: Softwares/FirstPerson/FirstPerson.cpp
	$(CC) -o Softwares/FirstPerson/FirstPerson.o -c \
	Softwares/FirstPerson/FirstPerson.cpp $(CFLAGS)

Softwares/TopDown/TopDown.o: Softwares/TopDown/TopDown.cpp
	$(CC) -o Softwares/TopDown/TopDown.o -c \
	Softwares/TopDown/TopDown.cpp $(CFLAGS)


clean:
	rm -rf *.o
	rm -rf System/*.o
	rm -rf System/Lin/*.o
	rm -rf Network/Lin/*.o
	rm -rf Compress/*.o
	rm -rf Images/*.o
	rm -rf Physics/*.o
	rm -rf Renderer/*.o
	rm -rf Renderer/Vulkan/*.o
	rm -rf Renderer/Shapes/*.o
	rm -rf Renderer/GUI/*.o
	rm -rf Resources/*.o
	rm -rf Softwares/*.o
	rm -rf Softwares/FirstPerson/*.o
	rm -rf Softwares/TopDown/*.o

mrproper: clean
	rm -rf VOS
