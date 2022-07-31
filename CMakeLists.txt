cmake_minimum_required(VERSION 3.22)
project(test1)


set(VCPKG_DIR C:/Users/hxd/Desktop/vcpkg/vcpkg/installed/x64-windows)
set(CMAKE_CXX_STANDARD 23)

#include_directories(C:/Users/hxd/Desktop/vcpkg/vcpkg/installed/x64-windows/include)

include_directories(${VCPKG_DIR}/include)


link_directories(“C:/Users/hxd/Desktop/vcpkg/vcpkg/installed/x64-windows/lib”)

#target_link_libraries(t2
#        glew32.lib
#        OpenGL32.Lib
#        glfw3dll.lib
#        GlU32.Lib
#        soil2.lib)
#link_libraries(glew32.lib OpenGL32.Lib glfw3dll.lib GlU32.Lib soil2.lib)




add_executable(test1
        utils.cpp utils.h
        C:/Users/hxd/Desktop/vcpkg/vcpkg/installed/x64-windows/lib/glew32.lib
        C:/Users/hxd/Desktop/vcpkg/vcpkg/installed/x64-windows/lib/OpenGL32.Lib
        C:/Users/hxd/Desktop/vcpkg/vcpkg/installed/x64-windows/lib/glfw3dll.lib
        C:/Users/hxd/Desktop/vcpkg/vcpkg/installed/x64-windows/lib/GlU32.Lib
        C:/Users/hxd/Desktop/vcpkg/vcpkg/installed/x64-windows/lib/soil2.lib Sphere.cpp Sphere.h main.cpp Torus.cpp Torus.h)
