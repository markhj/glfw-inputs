include(CMakePackageConfigHelpers)

get_filename_component(GLFW_INPUTS_LIB_DIR "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)

add_library(glfw_inputs
        INTERFACE
        ${GLFW_INPUTS_LIB_DIR}/include/glfw-inputs/glfw-inputs.hpp
)

target_include_directories(glfw_inputs
        INTERFACE
        $<BUILD_INTERFACE:${GLFW_INPUTS_LIB_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

export(TARGETS glfw_inputs
        FILE ${CMAKE_CURRENT_BINARY_DIR}/glfw_inputsTargets.cmake)

install(
        FILES
        "${CMAKE_CURRENT_BINARY_DIR}/glfw_inputsConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/glfw_inputsConfigVersion.cmake"
        DESTINATION lib/cmake/glfw-inputs
)
