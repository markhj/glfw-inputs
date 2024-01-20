# Basic usage 🚀

In this article, we assume that you have already created a GLFW window, and stored it in a variable of type ``GLFWwindow*``.

We will demonstrate how to implement a keyboard. As mentioned in the [Architecture chapter](../architecture/architecture.md),
it will be virtually identical to implement mouse or joystick.

## Inclusion and namespace 📂
Include **GLFW Inputs** with (assuming you [installed with CMake](installation-cmake.md)):

````c++
#include <glfw-inputs/glfw-inputs.hpp>
````

All **GLFW Inputs** parts are contained the namespace ``GLFW_Inputs``.
If it doesn't conflict with other names, you can optionally use:

````c++
using namespace GLFW_Inputs;
````

## Setting everything up 🏄
We start by initializing a manager, a keyboard, its mapping and connecting them.

````c++
// Replace with how you generate the GLFW window
GLFWwindow* = createGlfwWindow();

KeyboardMapping keyboardMapping;

Keyboard keyboard;
keyboard.mapping = &keyboardMapping;

Manager manager(window);
manager.setKeyboard(&keyboard);
````

This concludes the setup part, where we generate all required instances and connect it to
the GLFW window.

## Mapping 🔖
But to actually make this useful, we have to map some keys to signals.

Let's make two examples:

- Pressing "A" should print "Hello world" (signal name: ``greet``)
- Pressing "ESC" should exit the app

We start by defining this on the keyboard mapping:
````c++
keyboardMapping.on(Event::ButtonPress, Input::KeyA, "greet");
keyboardMapping.on(Event::ButtonPress, Input::KeyESC, "exit");
````

Now, to do something with these signals, we use ``Manager::listenFor`` method.

````c++
manager.listenFor("greet", []() {
    std::cout << "Hello world" << std::endl;    
});

// Assuming you have a variable called "keepOpen" which keeps
// the rendering loop running
manager.listenFor("exit", [&keepOpen]() {
    keepOpen = false;
});
````

Now, when you press A or ESC, you should see some action.

## Last notes 📌
Mouse and joystick are implemented in the exact same fashion.
You'll just need to replace with the appropriate classes and inputs.

See more under [Mouse](../controls/mouse.md) and [Joystick](../controls/joystick.md).

See also full documentation for keyboard under [Keyboard](../controls/keyboard.md).