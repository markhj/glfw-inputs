#ifndef GLFW_INPUTS_TESTS_GLFW_INPUTS_HPP
#define GLFW_INPUTS_TESTS_GLFW_INPUTS_HPP

#include "include.hpp"
#include "enums.hpp"
#include <optional>
#include <map>
#include <functional>
#include <utility>
#include <regex>

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
     */
    struct MappedInputEvent {
        InputEvent inputEvent;
        std::string signal;
    };

    /**
     * Position
     *
     * Used by MotionControl classes, and among other things
     * are part of the MotionEvent's position and relative properties
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
     */
    struct MotionEvent {
        std::optional<Position> position, relative;
        MotionSurface surface;
    };

    /**
     * Control Mapping
     *
     * The base for mapping classes, which makes it possible to
     * specify and get events
     */
    class ControlMapping {
    public:
        void on(Event event, Input input, std::string signal)
        {
            std::smatch matches;
            std::string target = signal;
            if (!std::regex_search(target, matches, regexSignalName)) {
                std::cout << "Signal name not compliant: " << signal << std::endl;
            }

            mappedInputEvents.push_back({
                .inputEvent = {
                    .event = event,
                    .input = input,
                },
                .signal = signal,
            });
        }

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

    protected:
        std::vector<MappedInputEvent> mappedInputEvents;

    };

    /**
     * Motion Control Mapping
     *
     * ControlMapping adapted for MotionControl classes
     */
    class MotionControlMapping : public ControlMapping {
    public:
        std::optional<std::function<void(MotionEvent motionEvent)>> onMove;

    };

    /**
     * Keyboard mapping
     */
    class KeyboardMapping : public ControlMapping {

    };

    /**
     * Mouse mapping
     */
    class MouseMapping : public MotionControlMapping {

    };

    /**
     * Control
     *
     * The base of the controls (keyboard, mouse, joystick)
     */
    class Control {
    public:
        virtual void handle(InputEvent inputEvent)
        {
            if (inputEvent.event == Event::ButtonPress) {
                buttonsDown[inputEvent.input] = true;
            } else if (inputEvent.event == Event::ButtonRelease) {
                buttonsDown[inputEvent.input] = false;
            }
        }

        std::vector<int> getButtonsDown()
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
     */
    class MotionControl : public Control {
    public:

        /**
         * Position changed
         *
         * Used when a control has a fixed position, such as the mouse cursor
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
     * Keyboard
     */
    class Keyboard : public Control {

    };

    /**
     * Mouse
     */
    class Mouse : public MotionControl {

    };

    /**
     * Manager
     *
     * The input manager class which first and foremost connects with GLFW,
     * but also handles all callbacks (i.e. communication with GLFW when inputs
     * are interacted with).
     *
     * Class is also responsible for listening for signals, and exposing the
     * option to receive those signals to the library consumer.
     */
    class Manager {
    public:
        explicit Manager(GLFWwindow *window) : window(window)
        {
            // Keyboard
            glfwSetKeyCallback(window, Manager::keyboardCallback);

            // Mouse
            glfwSetMouseButtonCallback(window, Manager::mouseButtonCallback);
            glfwSetCursorPosCallback(window, Manager::mouseMoveCallback);
            glfwSetScrollCallback(window, Manager::mouseWheelCallback);
        }

        /**
         * GLFW: Mouse/cursor movement callback
         */
        static void mouseMoveCallback(GLFWwindow *glfwWindow, double x, double y)
        {
            if (!mouse || !mouse->mapping.has_value()) {
                return;
            }

            mouse->positionChanged({
                .x = x,
                .y = y,
            }, MotionSurface::Cursor);
        }

        /**
         * GLFW: Mouse/scroll wheel callback
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
         */
        static void handleMappedInputEvent(std::optional<MappedInputEvent> mappedInputEvent)
        {
            if (!mappedInputEvent.has_value()) {
                return;
            }

            std::string signal = mappedInputEvent.value().signal;
            for (auto item : callbacks) {
                if (item.first == signal) {
                    item.second();
                    return;
                }
            }

            std::cout << "Leaked signal (not handled): " << signal << std::endl;
        }

        /**
         * Process tick
         *
         * Finds mapped input events for the specified control, in the cases
         * where a button is held down (Event::ButtonDown)
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
         */
        void processTick(MotionControl *control)
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

        void tick()
        {
            processTick(keyboard);
            processTick(mouse);
        }

        void setKeyboard(Keyboard *to)
        {
            keyboard = to;
        }

        void setMouse(Mouse *to)
        {
            mouse = to;
        }

        /**
         * Define what should happen when a signal is emitted
         *
         * The callback can be a lambda function, or a reference
         * to a function or class method
         */
        void listenFor(std::string signal, std::function<void()> callback)
        {
            callbacks[signal] = std::move(callback);
        }

    private:
        GLFWwindow *window;

        static std::map<std::string, std::function<void()>> callbacks;

        static Keyboard* keyboard;
        static Mouse* mouse;

    };

    // Initialization of static class properties
    std::map<std::string, std::function<void()>> Manager::callbacks = {};
    Keyboard* Manager::keyboard = nullptr;
    Mouse* Manager::mouse = nullptr;

}

#endif
