#cmakelists.txt
cmake_minimum_required(VERSION 3.25.2)
project(interaction VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIREDON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PROJECT_SOURCES
    main.h
    main.cpp
    interaction.h
    interaction.cpp
)

set(PROJECT_BINARY_DIR
    wxbase32u
    wxmsw32u_core
    wxmsw32u_gl_gcc_custom
    opengl32
    glu32
)
include_directories(
    "C:\\wxWidgets\\include",
    "C:\\wxWidgets\\lib\\gcc_dll",
    "C:\\wxWidgets\\lib\\gcc_dll\\mswu"
)

link_directories("C:\\wxWidgets\\lib\\gcc_dll")

add_executable(interaction ${PROJECT_SOURCES})

target_link_libraries(interaction ${PROJECT_BINARY_DIR})
