#include <Inputs/Input.h>
#include <Event/ReadOnlyEvent.h>

bool HC::Input::IsKeyPressed(int key) {
    return inputManager->IsKeyPressed(key);
}
bool HC::Input::IsMouseButtonPressed(int button) {
    return inputManager->IsMouseKeyPressed(button);
}

glm::uvec2 HC::Input::GetMousePosition() {
    return inputManager->GetMousePosition();
}

void HC::Input::Initialize(InputManager* InputManager) {
    inputManager = InputManager;

    /* Create events */
    KeyboardEvent = std::make_unique<ReadOnlyEvent<KeyboardInput>>(inputManager->KeyboardEvent);
    KeyboardEventPressed = std::make_unique<ReadOnlyEvent<KeyboardInput>>(inputManager->KeyboardPressedEvent);
    KeyboardEventReleased = std::make_unique<ReadOnlyEvent<KeyboardInput>>(inputManager->KeyboardReleasedEvent);
    KeyboardEventRepeat = std::make_unique<ReadOnlyEvent<KeyboardInput>>(inputManager->KeyboardRepeatEvent);

    MouseEvent = std::make_unique<ReadOnlyEvent<MouseInput>>(inputManager->MouseEvent);
    MouseEventPressed = std::make_unique<ReadOnlyEvent<MouseInput>>(inputManager->MousePressedEvent);
    MouseEventReleased = std::make_unique<ReadOnlyEvent<MouseInput>>(inputManager->MouseReleasedEvent);
    MouseEventRepeat = std::make_unique<ReadOnlyEvent<MouseInput>>(inputManager->MouseRepeatEvent);

}

void HC::Input::ListenKey(int key) {
    inputManager->ListenKey(key);
}

void HC::Input::ListenMouseKey(int key) {
    inputManager->ListenMouseKey(key);
}

void HC::Input::StopListenKey(int key) {
    inputManager->StopListenKey(key);
}

void HC::Input::StopListenMouseKey(int key) {
    inputManager->StopListenMouseKey(key);
}

HC::ReadOnlyEvent<HC::KeyboardInput> &HC::Input::GetKeyboardEventPressed() {
    return *KeyboardEventPressed;
}

HC::ReadOnlyEvent<HC::KeyboardInput> &HC::Input::GetAllKeyboardEvent() {
    return *KeyboardEvent;
}

HC::ReadOnlyEvent<HC::KeyboardInput> &HC::Input::GetKeyboardEventReleased() {
    return *KeyboardEventReleased;
}

HC::ReadOnlyEvent<HC::MouseInput> &HC::Input::GetAllMouseEvent() {
    return *MouseEvent;
}

HC::ReadOnlyEvent<HC::MouseInput> &HC::Input::GetMouseEventPressed() {
    return *MouseEventPressed;
}

HC::ReadOnlyEvent<HC::MouseInput> &HC::Input::GetMouseEventReleased() {
    return *MouseEventReleased;
}

HC::ReadOnlyEvent<HC::KeyboardInput> &HC::Input::GetKeyboardEventRepeat() {
    return *KeyboardEventRepeat;
}

HC::ReadOnlyEvent<HC::MouseInput> &HC::Input::GetMouseEventRepeat() {
    return *MouseEventRepeat;
}

