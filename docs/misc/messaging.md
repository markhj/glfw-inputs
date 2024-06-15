# Messaging 📢

With ``Messaging`` you can decide how you want to receive warnings and
errors prompted by **GLFW Inputs**.

An example, would be unhandled signals or invalid signal names.

## ``MessagingMethod``

This enum contains the various ways you can get messages.

| Value                          | Description                       |
|--------------------------------|-----------------------------------|
| ``MessagingMethod::Silent``    | Do nothing                        |
| ``MessagingMethod::StdCout``   | Log to console with ``std::cout`` |
| ``MessagingMethod::StdCerr``   | Log to console with ``std::cerr`` |
| ``MessagingMethod::Exception`` | Throw a runtime exception         |

## Changing behavior

You can modify the behavior of messages by setting ``Messaging::warnings``
and ``Messaging::errors`` to one of the enum values listed above.

For example:

````c++
Messaging::warnings = MessagingMethod::Silent;
````

## Default behavior

Under normal circumstances, warnings will be logged to the console
with ``std::cout`` and errors will be thrown as runtime exceptions.

## Example

````c++
KeyboardMapping keyboardMapping;
keyboardMapping.on(Event::ButtonPress, Input::KeyA, "invalid_SIGNAL_name!!!");
````

This will trigger a warning logged to the console.

This, on the other hand, will throw a runtime exception:

````c++
Messaging::warnings = MessagingMethod::Exception;

KeyboardMapping keyboardMapping;
keyboardMapping.on(Event::ButtonPress, Input::KeyA, "invalid_SIGNAL_name!!!");
````
