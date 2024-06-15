# Architecture at a glance 🔬

**GLFW Inputs** was designed such that all controls work the same
from the library consumer's perspective. There's essentially no difference between how you implement
keyboard, mouse or joystick.

## Helicopter view 🚁

In every project utilizing **GLFW Inputs** there's a ``Manager`` instance. This is the class which
connects with the GLFW window, as well as handles key presses, mouse movements, etc.

The manager emits signals. To know _which_ signal to emit, each control is equipped with
a (swappable) mapping. A mapping, for instance a ``KeyboardMapping``, specifies how button actions or control motions
map to signals.

## An example 💡

Instance of ``Manager`` and ``Keyboard`` are created, and keyboard is connected to the manager.

Instance of ``KeyboardMapping`` is created, where the following is specified:

- Pressing A emits a signal called "hello"
- Releasing ESC emits a signal called "exit"

The ``Manager`` is then instructed to handle the signals accordingly. In this example that would be:

- Printing "Hello world" when the signal "hello" is received
- Exiting the application when the signal "exit" is received
