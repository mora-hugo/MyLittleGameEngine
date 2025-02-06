#pragma once
#define NO_KEY -1
#include "glm/vec2.hpp"
namespace HC {

    enum class KeyboardAction {
        VP_KEY_PRESSED,
        VP_KEY_RELEASED,
        VP_KEY_REPEAT,
        VP_KEY_UNKNOWN
    };

    enum class MouseAction {
        VP_MOUSE_PRESSED,
        VP_MOUSE_RELEASED,
        VP_MOUSE_REPEAT,
        VP_MOUSE_MOVE,
        VP_MOUSE_UNKNOWN
    };


    struct KeyboardInput {
    public:
        KeyboardInput() = default;
        KeyboardInput(int key, int scancode, int action);
        KeyboardInput(const KeyboardInput&) = default;


    private:
        static KeyboardAction GetKeyboardActionFromInt(int action);

    public:
        int key = NO_KEY;
        int scan_code = NO_KEY;
        KeyboardAction action = KeyboardAction::VP_KEY_UNKNOWN;


    };


    struct MouseInput {
    public:
        MouseInput() = default;
        MouseInput(int key, int action, const glm::vec2& position);
        MouseInput(const MouseInput&) = default;
        MouseInput &operator=(const MouseInput&) = delete;

    private:
        static MouseAction GetMouseActionFromInt(int action);

    public:
        int key = NO_KEY;
        glm::vec2 position = glm::vec2(0.0f);
        const inline static int MOUSE_MOVE_INT = 3;


        MouseAction action = MouseAction::VP_MOUSE_UNKNOWN;


    };
}
