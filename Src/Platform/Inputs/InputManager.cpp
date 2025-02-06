#include "Inputs/InputManager.h"
#include "GLFW/glfw3.h"
#include <Event/IEvent.h>


void HC::InputManager::ListenKey(int key) {
    keysInUse.insert(key);
}

void HC::InputManager::ListenMouseKey(int key) {
    keysMouseInUse.insert(key);
}

void HC::InputManager::StopListenKey(int key) {
    keysInUse.erase(key);
}

void HC::InputManager::StopListenMouseKey(int key) {
    keysMouseInUse.erase(key);
}
const HC::KeyboardInput &HC::InputManager::UnqueueKeyboardInput() {
    const KeyboardInput& input = KeyboardInputs.front();
    KeyboardInputs.pop();
    return input;
}

const HC::MouseInput &HC::InputManager::UnqueueMouseInput() {
    const MouseInput& input = MouseInputs.front();
    MouseInputs.pop();
    return input;
}


bool HC::InputManager::IsKeyPressed(int key) {
    return window.GetKey(key) == GLFW_PRESS;
}

bool HC::InputManager::IsMouseKeyPressed(int key) {
    return window.GetMouseButton(key) == GLFW_PRESS;
}
void ez(HC::KeyboardInput input) {

}
void HC::InputManager::QueueMouseInput(MouseInput input) {
    MouseInputs.push(input);
}

void HC::InputManager::QueueKeyboardInput(KeyboardInput input) {
    KeyboardInputs.push(input);
}

void HC::InputManager::ProcessInput() {

    // Processing REPEATING keys (Input polling)
    //TODO - Handle only keys that the user is interested in

    for(int key : keysInUse) {
        if(window.GetKey(key) == GLFW_PRESS) {
            KeyboardInput input(key, NO_KEY, GLFW_REPEAT);
            KeyboardEvent.Invoke(input);
            KeyboardRepeatEvent.Invoke(input);
        }
    }
    for(int mouseKey : keysMouseInUse) {
        if(window.GetMouseButton(mouseKey) == GLFW_PRESS) {
            glm::dvec2 mousePos = window.GetMousePosition();
            MouseInput input(mouseKey, GLFW_REPEAT, mousePos);
            MouseEvent.Invoke(input);
            MouseRepeatEvent.Invoke(input);
        }
    }

    // Processing PRESSED AND RELEASED keys (From window callback)
    while(!KeyboardInputs.empty()) {
        const KeyboardInput& input = UnqueueKeyboardInput();
        KeyboardEvent.Invoke(input);

        if(input.action == KeyboardAction::VP_KEY_PRESSED) {
            KeyboardPressedEvent.Invoke(input);
        } else if(input.action == KeyboardAction::VP_KEY_RELEASED) {
            KeyboardReleasedEvent.Invoke(input);
        }

    }

    // Processing mouse inputs
    while(!MouseInputs.empty()) {
        const MouseInput& input = UnqueueMouseInput();
        MouseEvent.Invoke(input);

        if(input.action == MouseAction::VP_MOUSE_PRESSED) {
            MousePressedEvent.Invoke(input);
        } else if(input.action == MouseAction::VP_MOUSE_RELEASED) {
            MouseReleasedEvent.Invoke(input);
        }
    }

}

HC::InputManager::InputManager(HC::BaseWindow &context_window) : window(context_window) {
    context_window.OnWindowHandledMouseInput.AddListener(this,HC_BIND_MEMBER_FUNCTION_ARGS(&HC::InputManager::QueueMouseInput, this, 1));
    context_window.OnWindowHandledKeyboardInput.AddListener(this, HC_BIND_MEMBER_FUNCTION_ARGS(&HC::InputManager::QueueKeyboardInput, this, 1));
}

glm::uvec2 HC::InputManager::GetMousePosition() const {
    return window.GetMousePosition();
}


