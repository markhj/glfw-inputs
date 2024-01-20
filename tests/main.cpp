#include <iostream>

#include <GLFW/glfw3.h>
#include "glfw-inputs.hpp"

int main()
{
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return 1;
    }

    GLFWwindow *window = glfwCreateWindow(800, 600, "GLFW inputs", nullptr, nullptr);

    GLFW_Inputs::Manager manager(window);

    bool keepOpen = true;

    int c = 0;

    while (keepOpen) {
        c++;
        if (c > 100) {
            keepOpen = false;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }



    return 0;
}