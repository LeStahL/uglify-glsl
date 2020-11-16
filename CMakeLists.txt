cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 20)

project(uglify-glsl)

add_subdirectory(thirdparty/glslang)

include_directories(thirdparty/glslang/glslang/Include)

set(UGLIFY_GLSL_SOURCES main.cpp)
add_executable(uglify-glsl ${UGLIFY_GLSL_SOURCES})
add_dependencies(uglify-glsl glslang)
