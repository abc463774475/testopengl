cmake_minimum_required(VERSION 3.22)
project(test1)

set(CMAKE_CXX_STANDARD 14)

add_executable(test1
        test1/test1.cpp test1/redcoll.cpp utils.cpp utils.h)
