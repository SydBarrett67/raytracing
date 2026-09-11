cmake_minimum_required(VERSION 3.16)

project(raytracing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SDL
add_subdirectory(SDL EXCLUDE_FROM_ALL)

add_executable(raytracing
    src/main.cpp
    src/Renderer.cpp
    src/Camera.cpp
    src/Ray.cpp
    src/RayTracer.cpp
)

target_link_libraries(raytracing PRIVATE SDL3::SDL3)