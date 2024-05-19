#cmakelists.txt
cmake_minimum_required(VERSION 3.25.2)
project(test VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIREDON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PROJECT_SOURCES
    main.h
    main.cpp
    pyramidFrame.h
    pyramidFrame.cpp
    pyramidCavans.h
    pyramidCavans.cpp
)

include_directories(
    "D:\\wxWidgets324\\include",
    "D:\\wxWidgets324\\lib\\gcc_dll",
    "D:\\wxWidgets324\\lib\\gcc_dll\\mswu"
)
    
link_directories("D:\\wxWidgets324\\lib\\gcc_dll")

add_executable(test ${PROJECT_SOURCES})
target_link_libraries(test wxbase32u)
target_link_libraries(test wxmsw32u_core)
target_link_libraries(test wxmsw32u_gl_gcc_custom)
target_link_libraries(test opengl32)
target_link_libraries(test glu32)
