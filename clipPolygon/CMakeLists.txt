#cmakelists.txt
cmake_minimum_required(VERSION 3.25.2)
project(cgcpp VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIREDON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(
    "C:\\wxWidgets\\include",
    "C:\\wxWidgets\\lib\\gcc_dll",
    "C:\\wxWidgets\\lib\\gcc_dll\\mswu"
)
link_directories("C:\\wxWidgets\\lib\\gcc_dll")

set(PROJECT_SOURCES
    main.h
    main.cpp
    clipPolygon.h
    clipPolygon.cpp
    clipPolygonFrame.h
    clipPolygonFrame.cpp
)

add_executable(cgcpp  ${PROJECT_SOURCES})

target_link_libraries(cgcpp wxbase32u)
target_link_libraries(cgcpp wxmsw32u_core)