# Install as part of project 🌿

You can, of course, also just copy the files contained in ``include/glfw-inputs``
from the repository and add them as-is in your project.

This has some benefits and some drawbacks, but mostly it can sometimes just be easier
than dealing with CMake's discovery.

## How to do it

Simply, copy the contents of the ``include/glfw-inputs`` (alternatively, the entire repository)
from https://github.com/markhj/glfw-inputs.

Include them in your ``CMakeLists.txt`` file with:

````cmake
include(path/to/glfw-inputs)
````

The files should now be discoverable from your project. You can
test it by trying out:

````c++
#include "glfw-inputs.hpp"
````

Depending on how you imported the project the path may differ.
