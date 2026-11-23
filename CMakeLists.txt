cmake_minimum_required(VERSION 3.16)
project(Lab8 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(lab8 main.cpp Graph.cpp LinkedQueue.cpp)
if(MSVC)
    target_compile_options(lab8 PRIVATE /W4 /utf-8)
else()
    target_compile_options(lab8 PRIVATE -Wall -Wextra -Wpedantic)
endif()
