# Managing multiple joysticks 🎮

Make sure you have covered the [introduction to joysticks](../getting-started/joysticks.md) before reading this.

## User ID 💁

When you with multiple joysticks or gamepads, you'll want to know which joystick was
used when a signal is fired.

To achieve this, you need to equip every joystick instance with a ``userId`` (or player ID).

For instance:

````c++
joystick.userId = 5;
````

Now, whenever an event is fired and you catch the [ReceivedSignal](../misc/received-signal.md) struct, you'll have a
reference
to the joystick instance, where you find the ``userId``.

````c++
manager.listenFor("joystick_button_x", [](ReceivedSignal signal) {
    if (!signal.device.has_value()) {
        return;
    }
    
    if (signal.device.value().userId == 1) {
        // Player 1 jumps
    } else if (signal.device.value().userId == 2) {
        // Player 2 jumps
    }
})
````

## Notes 📜

### Device ID retention

Instances retain their device ID through-out the application life-time.

If you have two joysticks connected which are correspondingly designated
IDs ``0`` and ``1``, and the first device, with ID ``0`` is disconnected,
the second will _still_ have ID of ``1``.

If the first joystick is re-connected, it will resume the ID of ``0``.
