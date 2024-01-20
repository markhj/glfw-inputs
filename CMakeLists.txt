cmake_minimum_required(VERSION 3.26)

project(glfw_inputs_tests)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)

include_directories(include/glfw-inputs)

add_executable(tests
        tests/main.cpp
        include/glfw-inputs/glfw-inputs.hpp)

target_link_libraries(tests PRIVATE glfw)
