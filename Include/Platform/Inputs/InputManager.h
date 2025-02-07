#pragma once
#include <queue>
#include <map>
#include <unordered_map>
#include <functional>
#include <string>
#include "glm/vec2.hpp"
#include "Singleton.h"
#include "Event/Event.h"
#include <set>
#include "Window/BaseWindow.h"





namespace HC {
    class InputManager {
    public:
        explicit InputManager(BaseWindow& context_window);

        InputManager(const InputManager&) = delete;
        InputManager& operator=(const InputManager&) = delete;




        //TODO : Better way to handle reapeat keys
        void ListenKey(int key);
        void ListenMouseKey(int key);
        void StopListenKey(int key);
        void StopListenMouseKey(int key);

        /* Keyboard */
        void QueueKeyboardInput(KeyboardInput input);

        /* Mouse */
        void QueueMouseInput(MouseInput);

        void ProcessInput();

        bool IsKeyPressed(int key);
        bool IsMouseKeyPressed(int key);

        glm::uvec2 GetMousePosition() const;

    private:

        const KeyboardInput& UnqueueKeyboardInput();
        const MouseInput& UnqueueMouseInput();

    public:

        Event<KeyboardInput> KeyboardEvent;
        Event<KeyboardInput> KeyboardPressedEvent;
        Event<KeyboardInput> KeyboardReleasedEvent;
        Event<KeyboardInput> KeyboardRepeatEvent;


        Event<MouseInput> MouseEvent;
        Event<MouseInput> MousePressedEvent;
        Event<MouseInput> MouseReleasedEvent;
        Event<MouseInput> MouseRepeatEvent;


    private:


        std::queue<KeyboardInput> KeyboardInputs;
        std::queue<MouseInput> MouseInputs;
        std::set<int> keysInUse;
        std::set<int> keysMouseInUse;


        const BaseWindow& window;
    };
}

