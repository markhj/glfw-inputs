# Motion controls ⏩

"Motion controls" are controls which can "move". This includes
mouse and joystick, but not keyboard.

## Detecting movement 🏃

To detect movement, you basically just connect a function to the ``onMove``
property. Here's an example for the mouse:

````c++
mouseMapping.onMove = [](MotionEvent motionEvent) {
    // Do something here
};
````

## Type of movement 🚴

But there's a bit to unpack here, mainly about the [MotionEvent](../misc/motion-event.md).

At this point in time, you don't know _what_ moved. This is more relevant on joysticks than mice,
but still relevant nonetheless, because on a mouse both the cursor and the wheel can move.

To find out which part moved, you can look at the MotionEvent's ``surface`` property.

````c++
mouseMapping.onMove = [](MotionEvent motionEvent) {
    if (motionEvent.surface == MotionSurface::Cursor) {
        // Cursor moved
    } else if (MotionEvent.surface == MotionSurface::MouseWheel) {
        // Wheel was scrolled
    }
};
````

See more under [MotionSurface](../misc/motion-surface.md).

## Position and relative 📌

The ``MotionEvent`` is equipped with ``position`` and ``relative`` properties.

Start by noting that they are both ``std::optional``, and it's context-dependent
whether they have values or not.

The ``position`` provides the fixed and current absolute position. This is for example
the exact coordinates of the cursor (within the window).

The ``relative`` property describes how much movement has occurred since latest invocation.
For instance, if the cursor has moved 2 pixels since last frame in an OpenGL application.

The properties are sometimes omitted. For instance the mouse wheel doesn't have ``position``
because it has no fixed, absolute location. It just has "scroll up" and "scroll down".

See under [MotionSurface](../misc/motion-surface.md) which surfaces are available,
and which properties they have.
