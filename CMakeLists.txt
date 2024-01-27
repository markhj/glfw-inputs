cmake_minimum_required(VERSION 3.26)

project(glfw_inputs_samples)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)

include_directories(include/glfw-inputs)

add_executable(keyboard
        samples/keyboard.cpp
        include/glfw-inputs/glfw-inputs.hpp)

target_link_libraries(keyboard PRIVATE glfw)
