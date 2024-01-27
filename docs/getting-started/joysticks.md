# Working with joysticks

In this chapter, we cover the basics of working with joysticks.
Look at the bottom to learn where you can explore the topic deeper.

## Joystick manager 🎮
First of all, it's important to recognize that multiple joysticks and gamepads can 
connected simultaneously. It's also possible they can be disconnected and reconnected
on-the-fly.

To help us with this, we have the ``JoystickManager`` class. With this, we can
at any time retrieve instances of all connected devices.

````c++
JoystickManager joystickManager;
std::vector<Joystick> joysticks = joystickManager.createJoystickInstances();
````

To learn more about managing multiple devices at once, please read the chapter: [Managing multiple joysticks](../controls/multiple-joysticks.md).

## Joystick name and ID
Especially when working with multiple joysticks, you will need to know the
assigned ID and the joystick name.

````c++
// The device ID (usually an integer between 1 and 16)
int id = joystick.getId();

// Getting the name
std::string name = joystick.getDeviceName();
````

## Interacting with joystick 🏄
### Buttons
You can listen for button presses on the joystick like this:

````c++
JoystickMapping joystickMapping;
joystickMapping.on(Event::ButtonDown, Input::JoystickButton1, "joystick_one")

Joystick joystick;
joystick.mapping = &joystickMapping;

// Assumed instantiation of Manager
std::vector<Joystick*> joystickReferences = { &joystick };
manager.addJoysticks(joystickReferences);
````

Note that "just pressed" and "just released" events are not recorded
for joysticks. We only listen for "button down" states.

> Note that mapping joysticks can be a bit tricky, because what "Button 1" means
> on one model isn't exactly the same on other models. Additionally, not all joysticks
> have the same number of buttons.
> 
> There are open source projects to assist with mapping, for instance by SDL.
> 
> Allowing your users/players to map their joystick might prove necessary for a good experience.

### Movement

You can track movement of the joystick with:

````c++
joystickMapping.onMove = [](MotionEvent motionEvent) {
    
};
````

You can explore which motion surfaces are available under the [MotionSurface chapter](../misc/motion-surface.md).

> Just like with button presses, there's no guaranteed consistency between
> different joystick models.
> 
> Allowing your users/players to map their joystick might prove necessary for a good experience.

### Connection status
You will often have use-cases where you need to know when a device has been disconnected
and/or re-connected.

For this, you can use:

````c++
joystickMapping.on(DeviceEvent::Disconnect, "joystick_disconnected");
joystickMapping.on(DeviceEvent::Connect, "joystick_connected");
````

You can check the current status of a joystick:

````c++
if (joystick.isConnected()) {
    // Connected
} else {
    // Disconnected
}
````