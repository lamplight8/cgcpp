#cmakelists.txt
cmake_minimum_required(VERSION 3.25.2)
project(test VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIREDON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(
    "D:\\glfw-3.4.bin.WIN64\\include\\GLFW"
)

link_directories("D:\\glfw-3.4.bin.WIN64\\lib-mingw-w64")

set(PROJECT_SOURCES
    main.cpp
)

add_executable(test  ${PROJECT_SOURCES})

target_link_libraries(test glfw3)
target_link_libraries(test opengl32)