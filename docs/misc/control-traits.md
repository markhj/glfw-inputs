# Control traits

The traits listed below are applied to some ``Control`` types.

## ``SupportsMultipleDevices``
Some control types are commonly seen with 2+ units connected, this is true
for joysticks and gamepads, for instance.

This trait requires the child class to support ID-assignment to every connected device.

## ``SupportsDynamicConnectivity``
Indicates that the control should dynamically handle the device being
connected and/or disconnected on-the-fly.
