#include <iostream>

#include <GLFW/glfw3.h>
#include "glfw-inputs.hpp"

using namespace GLFW_Inputs;

int main()
{
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return 1;
    }

    GLFWwindow *window = glfwCreateWindow(800, 600, "GLFW inputs", nullptr, nullptr);

    Manager manager(window);

    KeyboardMapping keyboardMapping;
    keyboardMapping.on(Event::ButtonRelease, Input::KeyEsc, "exit");

    bool keepOpen = true;

    Keyboard keyboard;
    keyboard.mapping = &keyboardMapping;
    manager.setKeyboard(&keyboard);

    manager.listenFor("exit", [&](const ReceivedSignal& receivedSignal) {
        keepOpen = false;
    });

    while (keepOpen) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}