cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 20)

project(uglify-glsl)

add_subdirectory(thirdparty/glslang)


set(UGLIFY_GLSL_SOURCES main.cpp)
add_executable(uglify-glsl ${UGLIFY_GLSL_SOURCES})
target_include_directories(uglify-glsl PUBLIC
    thirdparty/glslang/glslang/Include
    thirdparty/glslang/glslang/Public
)
add_dependencies(uglify-glsl glslang)
