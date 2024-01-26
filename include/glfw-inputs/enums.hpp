#ifndef GLFW_INPUTS_TESTS_ENUMS_HPP
#define GLFW_INPUTS_TESTS_ENUMS_HPP

#include "include.hpp"

namespace GLFW_Inputs {

    /**
     * Motion Surface
     *
     * Describes which control surface has been moved
     *
     * @see https://glfw-inputs.readthedocs.io/en/latest/misc/motion-surface/
     */
    enum class MotionSurface {
        MouseCursor,
        MouseWheel,

        JoystickAxesXY,
        JoystickRotationXY,
    };

    /**
     * Device Event
     */
    enum class DeviceEvent {
        Connected,
        Disconnected,
    };

    /**
     * Event
     *
     * Used to indicate the current state of a button.
     * ButtonPress and ButtonRelease should be thought of as "just pressed" and "just released"
     *
     * @see https://glfw-inputs.readthedocs.io/en/latest/misc/events/
     *      Primary documentation about events
     *
     * @see https://glfw-inputs.readthedocs.io/en/latest/getting-started/button-down-states/
     *      Documentation specifically about the ButtonDown state
     */
    enum class Event {
        ButtonPress,
        ButtonDown,
        ButtonRelease,
    };

    /**
     * Input
     *
     * List of keyboard, mouse and joystick button-based inputs
     *
     * @see https://glfw-inputs.readthedocs.io/en/latest/misc/enums-inputs/
     */
    enum Input {
        // Special keys
        KeyEsc = GLFW_KEY_ESCAPE,
        KeyCtrlLeft = GLFW_KEY_LEFT_CONTROL,
        KeyCtrlRight = GLFW_KEY_RIGHT_CONTROL,
        KeyAltLeft = GLFW_KEY_LEFT_ALT,
        KeyAltRight = GLFW_KEY_RIGHT_ALT,
        KeyShiftLeft = GLFW_KEY_LEFT_SHIFT,
        KeyShiftRight = GLFW_KEY_RIGHT_SHIFT,
        KeyCapsLock = GLFW_KEY_CAPS_LOCK,
        KeyTab = GLFW_KEY_TAB,
        KeyPrintScreen = GLFW_KEY_PRINT_SCREEN,
        KeyInsert = GLFW_KEY_INSERT,
        KeyNumLock = GLFW_KEY_NUM_LOCK,
        KeyScrollLock = GLFW_KEY_SCROLL_LOCK,
        KeyPause = GLFW_KEY_PAUSE,

        // Spacing and delete
        KeySpace = GLFW_KEY_SPACE,
        KeyBackspace = GLFW_KEY_BACKSPACE,
        KeyEnter = GLFW_KEY_ENTER,
        KeyDelete = GLFW_KEY_DELETE,

        // F-keys
        KeyF1 = GLFW_KEY_F1,
        KeyF2 = GLFW_KEY_F2,
        KeyF3 = GLFW_KEY_F3,
        KeyF4 = GLFW_KEY_F4,
        KeyF5 = GLFW_KEY_F5,
        KeyF6 = GLFW_KEY_F6,
        KeyF7 = GLFW_KEY_F7,
        KeyF8 = GLFW_KEY_F8,
        KeyF9 = GLFW_KEY_F9,
        KeyF10 = GLFW_KEY_F10,
        KeyF11 = GLFW_KEY_F11,
        KeyF12 = GLFW_KEY_F12,

        // Letters
        KeyA = GLFW_KEY_A,
        KeyB = GLFW_KEY_B,
        KeyC = GLFW_KEY_C,
        KeyD = GLFW_KEY_D,
        KeyE = GLFW_KEY_E,
        KeyF = GLFW_KEY_F,
        KeyG = GLFW_KEY_G,
        KeyH = GLFW_KEY_H,
        KeyI = GLFW_KEY_I,
        KeyJ = GLFW_KEY_J,
        KeyK = GLFW_KEY_K,
        KeyL = GLFW_KEY_L,
        KeyM = GLFW_KEY_M,
        KeyN = GLFW_KEY_N,
        KeyO = GLFW_KEY_O,
        KeyP = GLFW_KEY_P,
        KeyQ = GLFW_KEY_Q,
        KeyR = GLFW_KEY_R,
        KeyS = GLFW_KEY_S,
        KeyT = GLFW_KEY_T,
        KeyU = GLFW_KEY_U,
        KeyV = GLFW_KEY_V,
        KeyW = GLFW_KEY_W,
        KeyX = GLFW_KEY_X,
        KeyY = GLFW_KEY_Y,
        KeyZ = GLFW_KEY_Z,

        // Numbers
        Key0 = GLFW_KEY_0,
        Key1 = GLFW_KEY_1,
        Key2 = GLFW_KEY_2,
        Key3 = GLFW_KEY_3,
        Key4 = GLFW_KEY_4,
        Key5 = GLFW_KEY_5,
        Key6 = GLFW_KEY_6,
        Key7 = GLFW_KEY_7,
        Key8 = GLFW_KEY_8,
        Key9 = GLFW_KEY_9,

        // Punctuators
        KeyPeriod = GLFW_KEY_PERIOD,
        KeyComma = GLFW_KEY_COMMA,
        KeySemicolon = GLFW_KEY_SEMICOLON,

        // Arrows and navigation
        KeyUp = GLFW_KEY_UP,
        KeyDown = GLFW_KEY_DOWN,
        KeyLeft = GLFW_KEY_LEFT,
        KeyRight = GLFW_KEY_RIGHT,
        KeyHome = GLFW_KEY_HOME,
        KeyEnd = GLFW_KEY_END,
        KeyPageDown = GLFW_KEY_PAGE_DOWN,
        KeyPageUp = GLFW_KEY_PAGE_UP,

        // Special characters
        KeySlash = GLFW_KEY_SLASH,
        KeyEqual = GLFW_KEY_EQUAL,
        KeyDash = GLFW_KEY_MINUS,
        KeyGraveAccent = GLFW_KEY_GRAVE_ACCENT,
        KeyApostrophe = GLFW_KEY_APOSTROPHE,
        KeyBracketLeft = GLFW_KEY_LEFT_BRACKET,
        KeyBracketRight = GLFW_KEY_RIGHT_BRACKET,

        // Keypad
        KeyNumpad0 = GLFW_KEY_KP_0,
        KeyNumpad1 = GLFW_KEY_KP_1,
        KeyNumpad2 = GLFW_KEY_KP_2,
        KeyNumpad3 = GLFW_KEY_KP_3,
        KeyNumpad4 = GLFW_KEY_KP_4,
        KeyNumpad5 = GLFW_KEY_KP_5,
        KeyNumpad6 = GLFW_KEY_KP_6,
        KeyNumpad7 = GLFW_KEY_KP_7,
        KeyNumpad8 = GLFW_KEY_KP_8,
        KeyNumpad9 = GLFW_KEY_KP_9,
        KeyNumpadAdd = GLFW_KEY_KP_ADD,
        KeyNumpadSubtract = GLFW_KEY_KP_SUBTRACT,
        KeyNumpadMultiply = GLFW_KEY_KP_MULTIPLY,
        KeyNumpadDivide = GLFW_KEY_KP_DIVIDE,
        KeyNumpadDecimal = GLFW_KEY_KP_DECIMAL,
        KeyNumpadEqual = GLFW_KEY_KP_EQUAL,
        KeyNumpadEnter = GLFW_KEY_KP_ENTER,

        // The designations are GLFW_MOUSE_BUTTON with LEFT and RIGHT
        // in reality point to primary and secondary, not the buttons
        // which are physically left or right on the mouse. We choose
        // "primary" and "secondary" to reflect this
        MousePrimary = GLFW_MOUSE_BUTTON_LEFT,
        MouseSecondary = GLFW_MOUSE_BUTTON_RIGHT,

        MouseMiddle = GLFW_MOUSE_BUTTON_MIDDLE,

        // Numbered mouse buttons
        // Remember that these buttons aren't available on most mice
        MouseButton1 = GLFW_MOUSE_BUTTON_1,
        MouseButton2 = GLFW_MOUSE_BUTTON_2,
        MouseButton3 = GLFW_MOUSE_BUTTON_3,
        MouseButton4 = GLFW_MOUSE_BUTTON_4,
        MouseButton5 = GLFW_MOUSE_BUTTON_5,
        MouseButton6 = GLFW_MOUSE_BUTTON_6,
        MouseButton7 = GLFW_MOUSE_BUTTON_7,
        MouseButton8 = GLFW_MOUSE_BUTTON_8,

        // Joystick & Gamepad
        JoystickButton1 = GLFW_JOYSTICK_1,
        JoystickButton2 = GLFW_JOYSTICK_2,
        JoystickButton3 = GLFW_JOYSTICK_3,
        JoystickButton4 = GLFW_JOYSTICK_4,
        JoystickButton5 = GLFW_JOYSTICK_5,
        JoystickButton6 = GLFW_JOYSTICK_6,
        JoystickButton7 = GLFW_JOYSTICK_7,
        JoystickButton8 = GLFW_JOYSTICK_8,
        JoystickButton9 = GLFW_JOYSTICK_9,
        JoystickButton10 = GLFW_JOYSTICK_10,
        JoystickButton11 = GLFW_JOYSTICK_11,
        JoystickButton12 = GLFW_JOYSTICK_12,

    };
};

#endif
