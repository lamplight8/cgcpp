#cmakelists.txt
cmake_minimum_required(VERSION 3.25.2)
project(test VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIREDON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(
    "D:\\wxWidgets\\include",
    "D:\\wxWidgets\\lib\\gcc_dll",
    "D:\\wxWidgets\\lib\\gcc_dll\\mswu"
)
link_directories("D:\\wxWidgets\\lib\\gcc_dll")

set(PROJECT_SOURCES
    main.h
    main.cpp
    house3dFrame.h
    house3dFrame.cpp
    rightPanel.h
    rightPanel.cpp
    object3d.h
    object3d.cpp
)

add_executable(test  ${PROJECT_SOURCES})

target_link_libraries(test wxbase32u)
target_link_libraries(test wxmsw32u_core)
#target_link_libraries(test wxmsw32u_core_gcc_custom)