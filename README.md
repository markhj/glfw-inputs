![Project Image](https://res.cloudinary.com/drfztvfdh/image/upload/v1705746857/Github/glfw-inputs-github-banner_abv3r8.jpg)

**GLFW Inputs** is a library designed to streamline and abstract various control interfaces
for C++'s GLFW library, often used for OpenGL applications.

# Features 📢
The current version of **GLFW Inputs** sports the following headline features:

🎮 **Keyboard, mouse**, **joystick** and **gamepad** support

🔄 **Swappable key mappings** to easily manage purpose of controls, for instance
whether in-game or in main menu.

🔉 **Signal-based** event handling separates processing of the actual physical input from translation to an action.

🅰️ **Button states** for all controls to determine if a button is just pressed, held down or just released.

📐 **Abstracted** such that every control type have a completely streamlined and predictable usage

# Requirements 🌿
- C++ 17 or higher*
- GLFW3

*) _Due to use of ``std::optional`` versions prior to C++ 17 won't work_

# Documentation 📖
You can read about installation, usage and more on:
https://glfw-inputs.readthedocs.io/en/latest/

# Host documentation locally ✏️
To run host the documentation locally, you must have Python and Mkdocs already installed.

Then use:

````
python mkdocs serve
````

On some Windows machines, it will be necessary to run with:

````
python -m mkdocs serve
````

# Notes 📜
- Under the hood, some properties and methods are static. As long as you follow the manual, this can be ignored. This is due to how GLFW works. But in practice the classes can be used as instantiable objects.