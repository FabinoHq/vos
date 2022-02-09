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
##   For more information, please refer to <http://unlicense.org>             ##
################################################################################
##    VOS : Virtual Operating System                                          ##
##     Makefile : Linux make compilation file                                 ##
################################################################################
CC=g++ -std=c++17
CFLAGS=-W -Wall
LDFLAGS=-pthread -lX11 -ldl

all: VOS

VOS: main.o \
	Vos.o \
	System/SysSleep.o System/SysThread.o \
	System/SysMutex.o System/SysMutexLocker.o \
	System/SysClock.o System/SysMemory.o \
	System/Lin/SysMessage.o System/Lin/SysDisplayMode.o \
	System/Lin/SysWindow.o System/Lin/SysVulkan.o \
	Compress/ZLib.o \
	Images/BMPFile.o Images/PNGFile.o \
	Renderer/Vulkan/Vulkan.o Renderer/Vulkan/VulkanMemory.o \
	Renderer/Vulkan/VulkanQueue.o Renderer/Vulkan/Swapchain.o \
	Renderer/Vulkan/VulkanBuffer.o Renderer/Vulkan/VertexBuffer.o \
	Renderer/Vulkan/UniformBuffer.o Renderer/Vulkan/GraphicsLayout.o \
	Renderer/Pipeline.o Renderer/Shader.o \
	Renderer/Texture.o Renderer/CubeMap.o \
	Renderer/View.o Renderer/Camera.o Renderer/FreeFlyCam.o \
	Renderer/Sprite.o Renderer/ProcSprite.o \
	Renderer/Shapes/RectangleShape.o Renderer/Shapes/EllipseShape.o \
	Renderer/Shapes/CuboidShape.o \
	Renderer/GUI/GUIPxText.o Renderer/GUI/GUIWindow.o \
	Renderer/SkyBox.o \
	Renderer/StaticMesh.o Renderer/HeightMapChunk.o \
	Renderer/Renderer.o

	$(CC) -o VOS \
	Vos.o \
	System/SysSleep.o System/SysThread.o \
	System/SysMutex.o System/SysMutexLocker.o \
	System/SysClock.o System/SysMemory.o \
	System/Lin/SysMessage.o System/Lin/SysDisplayMode.o \
	System/Lin/SysWindow.o System/Lin/SysVulkan.o \
	Compress/ZLib.o \
	Images/BMPFile.o Images/PNGFile.o \
	Renderer/Vulkan/Vulkan.o Renderer/Vulkan/VulkanMemory.o \
	Renderer/Vulkan/VulkanQueue.o Renderer/Vulkan/Swapchain.o \
	Renderer/Vulkan/VulkanBuffer.o Renderer/Vulkan/VertexBuffer.o \
	Renderer/Vulkan/UniformBuffer.o Renderer/Vulkan/GraphicsLayout.o \
	Renderer/Pipeline.o Renderer/Shader.o \
	Renderer/CubeMap.o Renderer/Texture.o \
	Renderer/View.o Renderer/Camera.o Renderer/FreeFlyCam.o \
	Renderer/Sprite.o Renderer/ProcSprite.o \
	Renderer/Shapes/RectangleShape.o Renderer/Shapes/EllipseShape.o \
	Renderer/Shapes/CuboidShape.o \
	Renderer/GUI/GUIPxText.o Renderer/GUI/GUIWindow.o \
	Renderer/SkyBox.o \
	Renderer/StaticMesh.o Renderer/HeightMapChunk.o \
	Renderer/Renderer.o \
	main.o $(LDFLAGS)


main.o: main.cpp
	$(CC) -o main.o -c main.cpp $(CFLAGS)

Vos.o: Vos.cpp
	$(CC) -o Vos.o -c Vos.cpp $(CFLAGS)


System/SysSleep.o: System/SysSleep.cpp
	$(CC) -o System/SysSleep.o -c System/SysSleep.cpp $(CFLAGS)

System/SysThread.o: System/SysThread.cpp
	$(CC) -o System/SysThread.o -c System/SysThread.cpp $(CFLAGS)

System/SysMutex.o: System/SysMutex.cpp
	$(CC) -o System/SysMutex.o -c System/SysMutex.cpp $(CFLAGS)

System/SysMutexLocker.o: System/SysMutexLocker.cpp
	$(CC) -o System/SysMutexLocker.o -c System/SysMutexLocker.cpp $(CFLAGS)

System/SysClock.o: System/SysClock.cpp
	$(CC) -o System/SysClock.o -c System/SysClock.cpp $(CFLAGS)

System/SysMemory.o: System/SysMemory.cpp
	$(CC) -o System/SysMemory.o -c System/SysMemory.cpp $(CFLAGS)

System/Lin/SysMessage.o: System/Lin/SysMessage.cpp
	$(CC) -o System/Lin/SysMessage.o -c System/Lin/SysMessage.cpp $(CFLAGS)

System/Lin/SysDisplayMode.o: System/Lin/SysDisplayMode.cpp
	$(CC) -o System/Lin/SysDisplayMode.o -c \
	System/Lin/SysDisplayMode.cpp $(CFLAGS)

System/Lin/SysWindow.o: System/Lin/SysWindow.cpp
	$(CC) -o System/Lin/SysWindow.o -c System/Lin/SysWindow.cpp $(CFLAGS)

System/Lin/SysVulkan.o: System/Lin/SysVulkan.cpp
	$(CC) -o System/Lin/SysVulkan.o -c System/Lin/SysVulkan.cpp $(CFLAGS)


Compress/ZLib.o: Compress/ZLib.cpp
	$(CC) -o Compress/ZLib.o -c Compress/ZLib.cpp $(CFLAGS)


Images/BMPFile.o: Images/BMPFile.cpp
	$(CC) -o Images/BMPFile.o -c Images/BMPFile.cpp $(CFLAGS)

Images/PNGFile.o: Images/PNGFile.cpp
	$(CC) -o Images/PNGFile.o -c Images/PNGFile.cpp $(CFLAGS)


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

Renderer/Pipeline.o: Renderer/Pipeline.cpp
	$(CC) -o Renderer/Pipeline.o -c Renderer/Pipeline.cpp $(CFLAGS)

Renderer/Shader.o: Renderer/Shader.cpp
	$(CC) -o Renderer/Shader.o -c Renderer/Shader.cpp $(CFLAGS)

Renderer/Texture.o: Renderer/Texture.cpp
	$(CC) -o Renderer/Texture.o -c Renderer/Texture.cpp $(CFLAGS)

Renderer/CubeMap.o: Renderer/CubeMap.cpp
	$(CC) -o Renderer/CubeMap.o -c Renderer/CubeMap.cpp $(CFLAGS)

Renderer/View.o: Renderer/View.cpp
	$(CC) -o Renderer/View.o -c Renderer/View.cpp $(CFLAGS)

Renderer/Camera.o: Renderer/Camera.cpp
	$(CC) -o Renderer/Camera.o -c Renderer/Camera.cpp $(CFLAGS)

Renderer/FreeFlyCam.o: Renderer/FreeFlyCam.cpp
	$(CC) -o Renderer/FreeFlyCam.o -c Renderer/FreeFlyCam.cpp $(CFLAGS)

Renderer/Sprite.o: Renderer/Sprite.cpp
	$(CC) -o Renderer/Sprite.o -c Renderer/Sprite.cpp $(CFLAGS)

Renderer/ProcSprite.o: Renderer/ProcSprite.cpp
	$(CC) -o Renderer/ProcSprite.o -c Renderer/ProcSprite.cpp $(CFLAGS)


Renderer/Shapes/RectangleShape.o: Renderer/Shapes/RectangleShape.cpp
	$(CC) -o Renderer/Shapes/RectangleShape.o -c \
	Renderer/Shapes/RectangleShape.cpp $(CFLAGS)

Renderer/Shapes/EllipseShape.o: Renderer/Shapes/EllipseShape.cpp
	$(CC) -o Renderer/Shapes/EllipseShape.o -c \
	Renderer/Shapes/EllipseShape.cpp $(CFLAGS)

Renderer/Shapes/CuboidShape.o: Renderer/Shapes/CuboidShape.cpp
	$(CC) -o Renderer/Shapes/CuboidShape.o -c \
	Renderer/Shapes/CuboidShape.cpp $(CFLAGS)


Renderer/GUI/GUIPxText.o: Renderer/GUI/GUIPxText.cpp
	$(CC) -o Renderer/GUI/GUIPxText.o -c Renderer/GUI/GUIPxText.cpp $(CFLAGS)

Renderer/GUI/GUIWindow.o: Renderer/GUI/GUIWindow.cpp
	$(CC) -o Renderer/GUI/GUIWindow.o -c Renderer/GUI/GUIWindow.cpp $(CFLAGS)


Renderer/SkyBox.o: Renderer/SkyBox.cpp
	$(CC) -o Renderer/SkyBox.o -c Renderer/SkyBox.cpp $(CFLAGS)

Renderer/StaticMesh.o: Renderer/StaticMesh.cpp
	$(CC) -o Renderer/StaticMesh.o -c Renderer/StaticMesh.cpp $(CFLAGS)

Renderer/HeightMapChunk.o: Renderer/HeightMapChunk.cpp
	$(CC) -o Renderer/HeightMapChunk.o -c Renderer/HeightMapChunk.cpp $(CFLAGS)


Renderer/Renderer.o: Renderer/Renderer.cpp
	$(CC) -o Renderer/Renderer.o -c Renderer/Renderer.cpp $(CFLAGS)


clean:
	rm -rf *.o
	rm -rf System/*.o
	rm -rf System/Lin/*.o
	rm -rf Compress/*.o
	rm -rf Images/*.o
	rm -rf Renderer/*.o
	rm -rf Renderer/Vulkan/*.o
	rm -rf Renderer/Shapes/*.o
	rm -rf Renderer/GUI/*.o

mrproper: clean
	rm -rf VOS
