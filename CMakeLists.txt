cmake_minimum_required(VERSION 3.20)
project(Pr02)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

file( GLOB MY_FILES *.cpp )
file( GLOB GLAD_FILES GLAD/src/*.c )

add_executable(${PROJECT_NAME} ${MY_FILES} ${GLAD_FILES}
        Renderer.cpp
        Renderer.h)

target_include_directories( ${PROJECT_NAME} PUBLIC GLAD/include )

target_link_libraries( ${PROJECT_NAME} OpenGL::GL glfw )