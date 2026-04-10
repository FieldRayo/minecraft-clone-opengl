cmake_minimum_required(VERSION 3.16)
project(OpenGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "external/src/glad.c"
)

add_executable(OpenGL ${SOURCES})

target_include_directories(OpenGL PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/external/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(OpenGL
    OpenGL::GL
    glfw
)
