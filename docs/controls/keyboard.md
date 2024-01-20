# Keyboard 🅱️

[Supports motion](../getting-started/motion-controls.md): No

Control class: ``Keyboard``

Control mapping class: ```KeyboardMapping```

## Example 🎉
### Key press
````c++
KeyboardMapping keyboardMapping;
Keyboard keyboard;
keyboard.mapping = &keyboardMapping;

keyboardMapping.on(Event::ButtonPress, Input::KeyF1, "open_menu");
````

# See also 📋
All available inputs under [Inputs](../misc/enums-inputs.md)