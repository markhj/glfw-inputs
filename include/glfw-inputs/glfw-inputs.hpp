#ifndef GLFW_INPUTS_TESTS_GLFW_INPUTS_HPP
#define GLFW_INPUTS_TESTS_GLFW_INPUTS_HPP

#include "include.hpp"
#include "enums.hpp"
#include <optional>
#include <map>
#include <functional>
#include <utility>
#include <regex>

/**
 * GLFW Inputs
 * Main header file
 *
 * @see https://github.com/markhj/glfw-inputs
 *      Repository on Github
 *
 * @see https://glfw-inputs.readthedocs.io/en/latest/
 *      Documentation
 */
namespace GLFW_Inputs {

    /**
     * Signal name regular expression
     * Used to verify applied signal names
     */
    const std::regex regexSignalName(R"(^[a-z]+(_[a-z]+){0,}$)");

    /**
     * Input Event
     *
     * Mostly used internally, as a streamlined way for GLFW-driven
     * callbacks to communicate seamlessly with the Manager and Control classes
     *
     * @see https://glfw-inputs.readthedocs.io/en/latest/misc/events/
     */
    struct InputEvent {
        Event event;
        Input input;
    };

    /**
     * Mapped Input Event
     *
     * Associates an input event with a signal
     * Used in ControlMapping classes
     *
     * @see https://glfw-inputs.readthedocs.io/en/latest/misc/events/
     */
    struct MappedInputEvent {
        InputEvent inputEvent;
        std::string signal;
    };

    /**
     * Mapped Device Event
     *
     * Associates a device event (such as a joystick being connected or disconnected)
     * with a signal. Used in ControlMapping classes.
     *
     * @see https://glfw-inputs.readthedocs.io/en/latest/misc/events/
     */
    struct MappedDeviceEvent {
        DeviceEvent deviceEvent;
        std::string signal;
    };

    /**
     * Position
     *
     * Used by MotionControl classes, and among other things
     * are part of the MotionEvent's position and relative properties
     *
     * @see https://glfw-inputs.readthedocs.io/en/latest/misc/position/
     */
    struct Position {
        double x, y;
        std::optional<double> z;
    };

    /**
     * Motion Event
     *
     * To be passed to library consumer callbacks with information
     * about the movements of various control surfaces such as cursor position,
     * mouse wheel and joystick axes
     *
     * @see https://glfw-inputs.readthedocs.io/en/latest/misc/motion-event/
     */
    struct MotionEvent {
        std::optional<Position> position, relative;
        MotionSurface surface;
    };

    /**
     * Messaging
     *
     * Used to streamline the processing of warnings and errors
     *
     * @see https://glfw-inputs.readthedocs.io/en/latest/misc/messaging/
     */
    class Messaging {
    public:
        static MessagingMethod warnings;
        static MessagingMethod errors;

    protected:

        /**
         * Submit a warning
         *
         * To be used internally by the library
         *
         * @param std::string message
         * @return void
         */
        static void warn(const std::string& message)
        {
            displayMessage(message, warnings);
        }

        /**
         * Submit an error
         *
         * To be used internally by the library
         *
         * @param std::string message
         * @return void
         */
        static void error(const std::string& message)
        {
            displayMessage(message, errors);
        }

        /**
         * General method to handle the display of a message
         *
         * @param const std::string& message
         * @param MessagingMethod method
         * @return void
         */
        static void displayMessage(const std::string& message, MessagingMethod method)
        {
            switch (method) {
                case MessagingMethod::Silent:
                    break;
                case MessagingMethod::StdCout:
                    std::cout << message << std::endl;
                    break;
                case MessagingMethod::StdCerr:
                    std::cerr << message << std::endl;
                    break;
                case MessagingMethod::Exception:
                    throw std::runtime_error(message);
            }
        }

    };

    /**
     * Control Mapping
     *
     * The base for mapping classes, which makes it possible to
     * specify and get events
     *
     * @see https://glfw-inputs.readthedocs.io/en/latest/controls/control-mapping/
     */
    class ControlMapping : public Messaging {
    public:

        /**
         * On (register an event)
         *
         * Specify on the mapping how a specific input event should
         * map to a given signal
         *
         * @see https://glfw-inputs.readthedocs.io/en/latest/getting-started/basic-usage/
         *      Guide on how to use the mapping feature
         *
         * @param Event event
         * @param Input input
         * @param std::string signal
         * @return void
         */
        void on(Event event, Input input, std::string signal)
        {
            std::smatch matches;
            std::string target = signal;
            if (!std::regex_search(target, matches, regexSignalName)) {
                error("Signal name not compliant: " + signal);
            }

            mappedInputEvents.push_back({
                .inputEvent = {
                    .event = event,
                    .input = input,
                },
                .signal = signal,
            });
        }

        /**
         * On (Device Event)
         *
         * For example when a joystick is connected or disconnected
         *
         * @param DeviceEvent deviceEvent
         * @param std::string signal
         * @return void
         */
        void on(DeviceEvent deviceEvent, std::string signal)
        {
            mappedDeviceEvents.push_back({
                .deviceEvent = deviceEvent,
                .signal = std::move(signal),
            });
        }

        /**
         * Get Event (InputEvent)
         *
         * Search the mapping for a MappedInputEvent which
         * matches the provided InputEvent.
         *
         * @param InputEvent inputEvent
         * @return std::optional<MappedInputEvent>
         */
        [[nodiscard]] std::optional<MappedInputEvent> getEvent(InputEvent inputEvent) const
        {
            for (MappedInputEvent mappedInputEvent : mappedInputEvents) {
                if (mappedInputEvent.inputEvent.event == inputEvent.event
                    && mappedInputEvent.inputEvent.input == inputEvent.input) {
                    return mappedInputEvent;
                }
            }
            return std::nullopt;
        }

        /**
         * Get Event (DeviceEvent)
         *
         * Search the provided callbacks for a MappedDeviceEvent
         * which matches the provided DeviceEvent
         *
         * @param DeviceEvent deviceEvent
         * @return std::optional<MappedDeviceEvent>
         */
        [[nodiscard]] std::optional<MappedDeviceEvent> getEvent(DeviceEvent deviceEvent) const
        {
            for (MappedDeviceEvent mappedDeviceEvent : mappedDeviceEvents) {
                if (mappedDeviceEvent.deviceEvent == deviceEvent) {
                    return mappedDeviceEvent;
                }
            }
            return std::nullopt;
        }

    protected:
        std::vector<MappedInputEvent> mappedInputEvents;

        std::vector<MappedDeviceEvent> mappedDeviceEvents;

    };

    /**
     * Motion Control Mapping
     *
     * ControlMapping adapted for MotionControl classes
     *
     * @see https://glfw-inputs.readthedocs.io/en/latest/controls/control-mapping/
     */
    class MotionControlMapping : public ControlMapping {
    public:

        /**
         * OnMove handler
         * Optionally used by control mappings to determine what should happen
         * when various control surfaces are moved
         */
        std::optional<std::function<void(MotionEvent motionEvent)>> onMove;

    };

    /**
     * Keyboard mapping
     *
     * @see https://glfw-inputs.readthedocs.io/en/latest/controls/keyboard/
     */
    class KeyboardMapping : public ControlMapping {

    };

    /**
     * Mouse mapping
     *
     * @see https://glfw-inputs.readthedocs.io/en/latest/controls/mouse/
     */
    class MouseMapping : public MotionControlMapping {

    };

    /**
     * Joystick mapping
     *
     * @see https://glfw-inputs.readthedocs.io/en/latest/controls/joystick/
     */
    class JoystickMapping : public MotionControlMapping {

    };

    /**
     * Control
     *
     * The base of the controls (keyboard, mouse, joystick)
     */
    class Control {
    public:

        /**
         * Handle input event
         *
         * Keeps track of the down-states of buttons
         *
         * @param InputEvent inputEvent
         * @return void
         */
        virtual void handle(InputEvent inputEvent)
        {
            if (inputEvent.event == Event::ButtonPress) {
                buttonsDown[inputEvent.input] = true;
            } else if (inputEvent.event == Event::ButtonRelease) {
                buttonsDown[inputEvent.input] = false;
            }
        }

        /**
         * Get buttons currently pressed down
         *
         * @see https://glfw-inputs.readthedocs.io/en/latest/getting-started/button-down-states/
         * @return std::vector<int>
         */
        [[nodiscard]] std::vector<int> getButtonsDown() const
        {
            std::vector<int> list;
            for (auto item : buttonsDown) {
                if (item.second) {
                    list.push_back(item.first);
                }
            }
            return list;
        }

        std::optional<ControlMapping *> mapping = std::nullopt;

    protected:
        std::map<int, bool> buttonsDown;

    };

    /**
     * Motion Control
     *
     * An extension of the Control class which includes motion surfaces
     * such as the mouse cursor, mouse wheel and joystick axes
     *
     * @see https://glfw-inputs.readthedocs.io/en/latest/getting-started/motion-controls/
     */
    class MotionControl : public Control {
    public:

        /**
         * Position changed
         *
         * Used when a control has a fixed position, such as the mouse cursor
         *
         * @param Position position
         * @param MotionSurface surface
         * @return void
         */
        void positionChanged(Position position, MotionSurface surface)
        {
            std::optional<Position> lastOnSurface = last[surface];

            if (lastOnSurface.has_value()) {
                relative[surface]->x = position.x - lastOnSurface.value().x;
                relative[surface]->y = position.y - lastOnSurface.value().y;
                if (lastOnSurface.value().z.has_value() && position.z.has_value()) {
                    relative[surface]->z = position.z.value() - lastOnSurface.value().z.value();
                }
            }

            last[surface] = position;

            if (mapping.has_value() && mapping.value()->onMove.has_value()) {
                mapping.value()->onMove.value()({
                    .position = lastOnSurface,
                    .relative = relative[surface],
                    .surface = surface,
                });
            }
        }

        /**
         * Relative changed
         *
         * Used when the position of the control isn't relevant, for instance
         * applicable for the mouse wheel
         *
         * @param Position relative
         * @param MotionSurface surface
         * @return void
         */
        void relativeChanged(Position relative, MotionSurface surface)
        {
            if (mapping.has_value() && mapping.value()->onMove.has_value()) {
                mapping.value()->onMove.value()({
                    .position = std::nullopt,
                    .relative = relative,
                    .surface = surface,
                });
            }
        }

        std::optional<MotionControlMapping *> mapping = std::nullopt;

    protected:
        std::map<MotionSurface, std::optional<Position>> last, relative;

    };

    /**
     * Supports Multiple Devices
     *
     * Trait for control types with support for multiple
     * devices at the same time such as joysticks and gamepads
     *
     * @see https://glfw-inputs.readthedocs.io/en/latest/misc/control-traits/
     */
    class SupportsMultipleDevices {
    public:

        /**
         * Constructor which takes the ID of the device
         *
         * @param int id
         */
        explicit SupportsMultipleDevices(int id) : deviceId(id) { }

        /**
         * Returns the (GLFW-assigned) ID of the device
         *
         * @return int
         */
        [[nodiscard]] int getId() const
        {
            return deviceId;
        }

        /**
         * User ID
         *
         * Optionally used to distinguish between users/players
         *
         * @see https://glfw-inputs.readthedocs.io/en/latest/controls/multiple-joysticks/
         */
        std::optional<unsigned int> userId = std::nullopt;

    protected:
        int deviceId;

    };

    /**
     * Supports Dynamic Connectivity
     *
     * Interface for control types which have dynamic support of devices
     * which can be connected and disconnected on-the-fly
     *
     * @see https://glfw-inputs.readthedocs.io/en/latest/misc/control-traits/
     */
    class SupportsDynamicConnectivity {

    };

    /**
     * Keyboard
     *
     * @see https://glfw-inputs.readthedocs.io/en/latest/controls/keyboard/
     */
    class Keyboard : public Control {

    };

    /**
     * Mouse
     *
     * @see https://glfw-inputs.readthedocs.io/en/latest/controls/mouse/
     */
    class Mouse : public MotionControl {

    };

    /**
     * Joystick
     *
     * @see https://glfw-inputs.readthedocs.io/en/latest/controls/joystick/
     */
    class Joystick : public MotionControl,
            public SupportsMultipleDevices,
            public SupportsDynamicConnectivity {
    public:
        /**
         * Create Joystick instance
         *
         * @param int id The GLFW-assigned ID of the joystick/gamepad
         */
        explicit Joystick(int id) : SupportsMultipleDevices(id)
        {
            // We need to store device name immediately, because
            // it cannot be retrieved when disconnected, which is a typical
            // scenario where you need to know it
            deviceName = glfwGetJoystickName(getId());
        }

        /**
         * Returns true if the joystick associated with this connection
         * is connected
         *
         * @return bool
         */
        [[nodiscard]] bool isConnected() const
        {
            return glfwJoystickPresent(getId());
        }

        /**
         * Retrieve the device name (as stored upon creation of the joystick
         * instance)
         *
         * @return std::string
         */
        [[nodiscard]] std::string getDeviceName() const
        {
            return deviceName;
        }

    protected:
        std::string deviceName;

    };

    /**
     * Joystick Manager
     *
     * A class which assists with managing multiple joystick/gamepad
     * devices within the same application
     *
     * @see https://glfw-inputs.readthedocs.io/en/latest/controls/multiple-joysticks/
     */
    class JoystickManager {
    public:

        /**
         * Creates a vector of all currently connected joysticks/gamepads
         *
         * @return std::vector<Joystick>
         */
        [[nodiscard]] std::vector<Joystick> createJoystickInstances() const
        {
            std::vector<Joystick> list;
            for (int i = 0; i <= maxJoysticks - 1; i++) {
                if (glfwJoystickPresent(GLFW_JOYSTICK_1 + i)) {
                    list.emplace_back(GLFW_JOYSTICK_1 + i);
                }
            }
            return list;
        }

    private:
        /**
         * The maximum joysticks which can be handled with GLFW
         * This is based on the existence of the GLFW_JOYSTICK_16 constant
         */
        unsigned int maxJoysticks = 16;

    };

    /**
     * Received signal
     *
     * Struct used for callbacks
     *
     * @see https://glfw-inputs.readthedocs.io/en/latest/misc/received-signal/
     */
    struct ReceivedSignal {
        std::string signal;
        std::optional<SupportsMultipleDevices*> device;
    };

    /**
     * Input Manager
     *
     * The input manager class which first and foremost connects with GLFW,
     * but also handles all callbacks (i.e. communication with GLFW when inputs
     * are interacted with).
     *
     * Class is also responsible for listening for signals, and exposing the
     * option to receive those signals to the library consumer.
     *
     * @see https://glfw-inputs.readthedocs.io/en/latest/controls/input-manager/
     */
    class Manager : public Messaging {
    public:

        /**
         * Create a new instance of the input manager
         *
         * @param GLFWwindow* window
         */
        explicit Manager(GLFWwindow *window) : window(window)
        {
            // Keyboard
            glfwSetKeyCallback(window, Manager::keyboardCallback);

            // Mouse
            glfwSetMouseButtonCallback(window, Manager::mouseButtonCallback);
            glfwSetCursorPosCallback(window, Manager::mouseMoveCallback);
            glfwSetScrollCallback(window, Manager::mouseWheelCallback);

            // Joysticks and gamepads
            glfwSetJoystickCallback(Manager::joystickConnectionCallback);
        }

        /**
         * GLFW: Joystick callback
         *
         * This callback detects when joysticks are connected or
         * disconnected.
         *
         * @param int jid Joystick (device) ID
         * @param int event GLFW event ID
         * @return void
         */
        static void joystickConnectionCallback(int jid, int event)
        {
            std::optional<DeviceEvent> ev;
            if (event == GLFW_CONNECTED) {
                ev = DeviceEvent::Connected;
            } else if (event == GLFW_DISCONNECTED) {
                ev = DeviceEvent::Disconnected;
            }

            if (!ev.has_value()) {
                return;
            }

            for (Joystick* joystick : joysticks) {
                if (!joystick->mapping.has_value()) {
                    continue;
                }

                handleMappedDeviceEvent(joystick->mapping.value()->getEvent(ev.value()),
                                        joystick);
            }
        }

        /**
         * Handle mapped device events
         *
         * Helper method to find a specific signal and invoke its callback
         *
         * @param std::optional<MappedDeviceEvent> mappedDeviceEvent
         * @param Joystick* joystick
         * @return void
         */
        static void handleMappedDeviceEvent(std::optional<MappedDeviceEvent> mappedDeviceEvent, Joystick* joystick)
        {
            if (!mappedDeviceEvent.has_value()) {
                return;
            }

            std::string signal = mappedDeviceEvent.value().signal;
            for (auto item : callbacks) {
                if (item.first == signal) {
                    item.second({
                        .signal = signal,
                        .device = joystick,
                    });
                    return;
                }
            }

            warn("Leaked signal (not handled): " + signal);
        }

        /**
         * GLFW: Mouse/cursor movement callback
         *
         * @param GLFWwindow* glfwWindow
         * @param double x
         * @param double y
         * @return void
         */
        static void mouseMoveCallback(GLFWwindow *glfwWindow, double x, double y)
        {
            if (!mouse || !mouse->mapping.has_value()) {
                return;
            }

            mouse->positionChanged({
                .x = x,
                .y = y,
            }, MotionSurface::MouseCursor);
        }

        /**
         * GLFW: Mouse/scroll wheel callback
         *
         * @param GLFWwindow* glfwWindow
         * @param double x
         * @param double y
         * @return void
         */
        static void mouseWheelCallback(GLFWwindow *glfwWindow, double x, double y)
        {
            if (!mouse || !mouse->mapping.has_value()) {
                return;
            }

            mouse->relativeChanged({
                .x = x,
                .y = y,
            }, MotionSurface::MouseWheel);
        }

        /**
         * GLFW: Mouse button callback
         *
         * Note: The handling code cannot be put into a helper method because the
         * differences between Control and MotionControl would be sliced, and it
         * would point to the incorrect mapping
         *
         * @param GLFWwindow* window
         * @param int button
         * @param int action
         * @param int mods
         * @return void
         */
        static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
        {
            if (!mouse || !mouse->mapping.has_value()) {
                return;
            }

            InputEvent inputEvent = {
                .event = action == 0 ? Event::ButtonRelease : Event::ButtonPress,
                .input = static_cast<Input>(button),
            };
            mouse->handle(inputEvent);
            handleMappedInputEvent(mouse->mapping.value()->getEvent(inputEvent));
        }

        /**
         * GLFW: Keyboard button press callback
         *
         * @param GLFWwindow* window
         * @param int key
         * @param int scancode
         * @param int action
         * @param int mods
         * @return void
         */
        static void keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
        {
            if (!keyboard || !keyboard->mapping.has_value() || action > 1) {
                return;
            }

            InputEvent inputEvent = {
                .event = action == 0 ? Event::ButtonRelease : Event::ButtonPress,
                .input = static_cast<Input>(key),
            };
            keyboard->handle(inputEvent);
            handleMappedInputEvent(keyboard->mapping.value()->getEvent(inputEvent));
        }

        /**
         * Handle mapped input events
         *
         * Helper method to find a specific signal and invoke its callback
         *
         * @param std::optional<MappedInputEvent> mappedInputEvent
         * @return void
         */
        static void handleMappedInputEvent(std::optional<MappedInputEvent> mappedInputEvent)
        {
            if (!mappedInputEvent.has_value()) {
                return;
            }

            std::string signal = mappedInputEvent.value().signal;
            for (auto item : callbacks) {
                if (item.first == signal) {
                    item.second({
                        .signal = signal,
                    });
                    return;
                }
            }

            warn("Leaked signal (not handled): " + signal);
        }

        /**
         * Process tick
         *
         * Finds mapped input events for the specified control, in the cases
         * where a button is held down (Event::ButtonDown)
         *
         * @param Control* control
         * @return void
         */
        void processTick(Control *control)
        {
            if (!control) {
                return;
            }
            for (auto input : control->getButtonsDown()) {
                handleMappedInputEvent(control->mapping.value()->getEvent({
                   .event = Event::ButtonDown,
                   .input = static_cast<Input>(input),
                }));
            }
        }

        /**
         * Process tick (MotionControl-specific)
         *
         * The same as processTick, but for MotionControl
         * Method is needed to avoid slicing of MotionControl properties
         *
         * @param MotionControl* control
         * @return void
         */
        void processTick(MotionControl *motionControl)
        {
            if (!motionControl) {
                return;
            }
            for (auto input : motionControl->getButtonsDown()) {
                handleMappedInputEvent(motionControl->mapping.value()->getEvent({
                    .event = Event::ButtonDown,
                    .input = static_cast<Input>(input),
                }));
            }
        }

        /**
         * Tick
         *
         * Should be called on every iteration of render/game loop, in order
         * to handle button-down and joystick-related events
         *
         * @return void
         */
        void tick()
        {
            processTick(keyboard);
            processTick(mouse);

            processJoysticks();
        }

        /**
         * Process joysticks
         *
         * Iterates over the connected joysticks/gamepads, and
         * looks for button presses and movements on the axes
         *
         * The way button presses are detected on joysticks is different
         * from mouse and keyboard, in that joysticks don't have
         * a specific callback for it
         *
         * @return void
         */
        void processJoysticks()
        {
            for (Joystick* joystick : joysticks) {
                if (!joystick->isConnected()) {
                    continue;
                } else if (!joystick->mapping.has_value()) {
                    continue;
                }

                int bCount;
                const unsigned char *buttons = glfwGetJoystickButtons(joystick->getId(), &bCount);

                for (int i = 0; i <= bCount; i++) {
                    if (buttons[i] == GLFW_PRESS) {
                        handleMappedInputEvent(joystick->mapping.value()->getEvent({
                            .event = Event::ButtonDown,
                            .input = translateJoystickButton(i),
                        }));
                    }
                }

                // Look for movements along the different axes
                // The number of axes can vary between joysticks
                int countAxes;
                const float *axes = glfwGetJoystickAxes(joystick->getId(), &countAxes);
                if (axes) {
                    Position movement, rotation;
                    for (int a = 0; a < countAxes; a++) {
                        switch (a) {
                            case 0:
                                movement.x = axes[a];
                                break;
                            case 1:
                                movement.y = axes[a];
                                break;
                            case 2:
                                rotation.x = axes[a];
                                break;
                            case 3:
                                rotation.y = axes[a];
                                break;
                        }
                    }

                    joystick->positionChanged(movement, MotionSurface::JoystickAxesXY);
                    joystick->positionChanged(rotation, MotionSurface::JoystickRotationXY);
                }
            }
        }

        /**
         * Helper function to map a button index to the
         * corresponding enumerator value in Input
         *
         * @param int btn
         * @return Input
         */
        static Input translateJoystickButton(int btn) {
            std::vector<Input> joystickInputs = {
                    Input::JoystickButton1,
                    Input::JoystickButton2,
                    Input::JoystickButton3,
                    Input::JoystickButton4,
                    Input::JoystickButton5,
                    Input::JoystickButton6,
                    Input::JoystickButton7,
                    Input::JoystickButton8,
                    Input::JoystickButton9,
                    Input::JoystickButton10,
                    Input::JoystickButton11,
                    Input::JoystickButton12
            };
            return joystickInputs[btn];
        }

        /**
         * Set keyboard
         *
         * @param Keyboard* to
         * @return void
         */
        void setKeyboard(Keyboard *to)
        {
            keyboard = to;
        }

        /**
         * Set mouse
         *
         * @param Mouse* to
         * @return void
         */
        void setMouse(Mouse *to)
        {
            mouse = to;
        }

        /**
         * Set (list of) joysticks
         *
         * @param std::vector<Joystick*> to
         * @return void
         */
        void setJoysticks(const std::vector<Joystick*>& to)
        {
            joysticks = to;
        }

        /**
         * Define what should happen when a signal is emitted
         *
         * The callback can be a lambda function, or a reference
         * to a function or class method
         *
         * @param const std::string& signal
         * @param std::function<void(ReceivedSignal)> callback
         * @return void
         */
        void listenFor(const std::string& signal, std::function<void(ReceivedSignal)> callback)
        {
            callbacks[signal] = std::move(callback);
        }

    private:
        GLFWwindow *window;

        static std::map<std::string, std::function<void(ReceivedSignal)>> callbacks;

        static Keyboard* keyboard;
        static Mouse* mouse;
        static std::vector<Joystick*> joysticks;

    };

    // Initialization of static class properties
    std::map<std::string, std::function<void(ReceivedSignal)>> Manager::callbacks = {};
    Keyboard* Manager::keyboard = nullptr;
    Mouse* Manager::mouse = nullptr;
    std::vector<Joystick*> Manager::joysticks = {};

    MessagingMethod Messaging::warnings = MessagingMethod::StdCout;
    MessagingMethod Messaging::errors = MessagingMethod::Exception;

}

#endif
