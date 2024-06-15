# Control mappings 📔

The ``ControlMapping`` is the base class for specified mappings
for various control types such as keyboard and mouse.

See [Getting started](../getting-started/basic-usage.md) chapter to learn more about practical usage.

## Child classes

- ``KeyboardMapping``
- ``MouseMapping``
- ``JoystickMapping``

## Methods

````c++
void on(Event event, Input input, std::string signal)
void on(DeviceEvent deviceEvent, std::string signal)
std::optional<MappedInputEvent> getEvent(InputEvent inputEvent)
std::optional<MappedDeviceEvent> getEvent(DeviceEvent deviceEvent)
````