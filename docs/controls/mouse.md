# Mouse 🐭

[Supports motion](../getting-started/motion-controls.md): Yes

Control class: ``Mouse``

Control mapping class: ```MouseMapping```

## Example 🎉

### Mouse button press

````c++
MouseMapping mouseMapping;
Mouse mouse;
mouse.mapping = &mouseMapping;

mouseMapping.on(Event::ButtonPress, Input::MousePrimary, "shoot");
````

### Mouse movement

````c++
mouseMapping.onMove = [](MotionEvent motionEvent){
    if (motionEvent.surface == MotionSurface::Cursor) {
        std::cout << "Cursor was moved!" << std::endl;
    }
};
````

# See also 📋

- [All mouse-related inputs](../misc/enums-inputs.md)
- [MotionEvent](../misc/motion-event.md)
- [MotionSurface](../misc/motion-surface.md)
