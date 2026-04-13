cmake_minimum_required(VERSION 3.16)
project(OpenGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "external/src/glad.c"
    "external/imgui/imgui.cpp"
    "external/imgui/imgui_draw.cpp"
    "external/imgui/imgui_tables.cpp"
    "external/imgui/imgui_widgets.cpp"
    "external/imgui/backends/imgui_impl_glfw.cpp"
    "external/imgui/backends/imgui_impl_opengl3.cpp"
)

add_executable(OpenGL ${SOURCES})

target_include_directories(OpenGL PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/external/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/backends 
    ${CMAKE_CURRENT_SOURCE_DIR}/external/stb
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_definitions(OpenGL PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)

target_link_libraries(OpenGL
    OpenGL::GL
    glfw
)
