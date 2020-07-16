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
CC=g++
CFLAGS=-W -Wall
LDFLAGS=-std=c++11 -lX11

all: VOS

VOS: main.o \
    Vos.o \
    Lin/DisplayMode.o Lin/SysWindow.o \
    Renderer/Renderer.o
    
    $(CC) -o VOS \
    Vos.o \
    Lin/DisplayMode.o Lin/SysWindow.o \
    Renderer/Renderer.o \
    main.o $(LDFLAGS)

main.o: main.cpp
    $(CC) -o main.o -c main.cpp $(CFLAGS)

Vos.o: Vos.cpp
    $(CC) -o Vos.o -c Vos.cpp $(CFLAGS)

Lin/DisplayMode.o: Lin/DisplayMode.cpp
    $(CC) -o Lin/DisplayMode.o -c Lin/DisplayMode.cpp $(CFLAGS)

Lin/SysWindow.o: Lin/SysWindow.cpp
    $(CC) -o Lin/SysWindow.o -c Lin/SysWindow.cpp $(CFLAGS)

Renderer/Renderer.o: Renderer/Renderer.cpp
    $(CC) -o Renderer/Renderer.o -c Renderer/Renderer.cpp $(CFLAGS)

clean:
    rm -rf *.o
    rm -rf Lin/*.o
    rm -rf Renderer/*.o

mrproper: clean 
    rm -rf VOS

