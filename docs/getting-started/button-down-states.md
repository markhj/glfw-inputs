# Button down states 🔽

GLFW can not detect when a button is down, at least not to the extent
we usually want in games.

It can record when a button is held down, but it doesn't
immediately invoke (it uses the system setting typically with a few seconds delay, as seen in writing software, for
instance).

This is solved in **GLFW Inputs** for all types of controls (keyboard, mouse, joystick).

## Setting up 🔁

There's one small thing you need to do first, and that is calling the ``Manager::tick``
function. This has to be done for every loop iteration where inputs can be detected.

In an OpenGL or game application that would be in the render/game loop.

````c++
while (keepOpen) {
    // OpenGL stuff
    
    manager.tick();
    
    // OpenGL stuff
}
````

## Registering signals 🔉

Now, you simply use the ``Event::ButtonDown`` when setting up a signal.

````c++
keyboardMapping.on(Event::ButtonDown, Input::KeyA, "signal_name");
````
