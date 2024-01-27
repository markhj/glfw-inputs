# ``ReceivedSignal``

``ReceivedSignal`` is a struct provided to the callbacks containing
relevant information.

## Properties
| Property   | Data type | Description                                                                                |
|------------| --- |--------------------------------------------------------------------------------------------|
| ``signal`` | ``std::string`` | Name of the fired signal                                                                   |
| ``device`` | ``std::optional<SupportsMultipleDevices*>`` | In some use-cases, a reference to the input device will be provided. For example joystick. |