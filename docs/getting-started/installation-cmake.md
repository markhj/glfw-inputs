# Installation with CMake 🌿

**GLFW Inputs** is, out of the box, not a compiled library, but
a header-only source code library. It means it compiles together with your own application.

## Clone 🚦

To install **GLFW Inputs** and use it in your project, you must start
by cloning the repository.

````bash
git clone https://github.com/markhj/glfw-inputs
````

## Project-specific setup 🚧

For every project, you must specify an environment variable which
CMake can see, named ``glfw_inputs_DIR``. It should point to the location
where you put the repository you just cloned.

There are two steps to take in your CMakeLists.txt file.

The first is finding the package:

````cmake
find_package(glfw_inputs REQUIRED)
````

The second is linking it to your executable or library.

````cmake
add_executable(my_project PRIVATE glfw_inputs)
````
