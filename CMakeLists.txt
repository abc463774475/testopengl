cmake_minimum_required(VERSION 3.22)
project(test1)


set(VCPKG_DIR C:/Users/hxd/Desktop/vcpkg/vcpkg/installed/x64-windows)
set(CMAKE_CXX_STANDARD 23)

#include_directories(C:/Users/hxd/Desktop/vcpkg/vcpkg/installed/x64-windows/include)

include_directories(${VCPKG_DIR}/include)


link_directories(C:/Users/hxd/Desktop/vcpkg/vcpkg/installed/x64-windows/lib)

set(
    lib_totals
    glew32.lib
    OpenGL32.Lib
    glfw3dll.lib
    GlU32.Lib
    soil2.lib
)

add_executable(test1
        utils.cpp utils.h
        Sphere.cpp Sphere.h main.cpp Torus.cpp Torus.h)

target_link_libraries(test1
        ${lib_totals})