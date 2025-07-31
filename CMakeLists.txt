cmake_minimum_required(VERSION 3.15)
project(ImGuiTextSelectExample)

# Set C++ standard and encoding (CMake doesn't directly handle encodings, but this ensures UTF-8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# Fetch dependencies (modern CMake approach)
include(FetchContent)

# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw)

# Dear ImGui
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.92.0
)
FetchContent_MakeAvailable(imgui)

# OpenGL (system library)
find_package(OpenGL REQUIRED)

# Configure ImGui with GLFW + OpenGL3 backend
set(IMGUI_DIR ${imgui_SOURCE_DIR})
file(GLOB IMGUI_SOURCES
    "${IMGUI_DIR}/*.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
)
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${glfw_SOURCE_DIR}/include
)
target_link_libraries(imgui PUBLIC glfw OpenGL::GL)

# Main executable
add_executable(example
    example/main.cpp
    textselect.cpp
)
target_include_directories(example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(example PRIVATE imgui)
