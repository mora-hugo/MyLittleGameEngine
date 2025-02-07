#include "Components/PlayerControllerComponent.h"
#include "Components/TransformComponent.h"
#include "ECS/Entity.h"
#include "GLFW/glfw3.h"
#include "Utils/Time.h"
#include <iostream>

void HC::PlayerControllerComponent::Move(const glm::vec3 &direction, float amount) {
    auto transform = GetEntity()->GetComponent<TransformComponent>();
    if (transform) {
        transform->SetPosition(transform->GetPosition() + (direction * amount * moveSpeed));
    }
}

void HC::PlayerControllerComponent::Initialize(float speed) {
    Component::Initialize();
    moveSpeed = speed;
    BindEvents();

}

void HC::PlayerControllerComponent::BindEvents() {
    Input::GetKeyboardEventPressed().AddListener(this, HC_BIND_MEMBER_FUNCTION_ARGS(&PlayerControllerComponent::OnKeyPressed, this, 1));
    Input::GetKeyboardEventRepeat().AddListener(this, HC_BIND_MEMBER_FUNCTION_ARGS(&PlayerControllerComponent::OnKeyRepeat, this, 1));

}

void HC::PlayerControllerComponent::UnbindEvents() {
    //Input::GetKeyboardEventRepeat().RemoveListener(this);
    //Input::GetMouseEventRepeat().RemoveListener(this);
}

void HC::PlayerControllerComponent::OnKeyRepeat(const HC::KeyboardInput &keyboardInput) {
    switch (keyboardInput.key) {
        case GLFW_KEY_Z:
            Move(Time::GetSmoothDeltaTime() * glm::vec3{0.0f, 1.0f, 0});
            break;
        case GLFW_KEY_S:
            Move(Time::GetSmoothDeltaTime() * glm::vec3{0.0f, -1.0f, 0});
            break;
        case GLFW_KEY_LEFT:
            Move(Time::GetSmoothDeltaTime() * glm::vec3{1.0f, 0.0f, 0.0f});
            break;
        case GLFW_KEY_RIGHT:
            Move(Time::GetSmoothDeltaTime() * glm::vec3{-1.0f, 0.0f, 0.0f});
            break;
        case GLFW_KEY_UP:
            Move(Time::GetSmoothDeltaTime() * glm::vec3{0.0f, 0.0f, 1.0f});
            break;
        case GLFW_KEY_DOWN:
            Move(Time::GetSmoothDeltaTime() * glm::vec3{0.0f, 0.0f,-1.0f});
            break;
    }
}

HC::PlayerControllerComponent::~PlayerControllerComponent() {
    UnbindEvents();
}

void HC::PlayerControllerComponent::SetCursorHidden(bool bHidden) {
    if (bHidden) {
        glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
        glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

bool HC::PlayerControllerComponent::IsCursorHidden() const {
    return glfwGetInputMode(glfwGetCurrentContext(), GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
}

void HC::PlayerControllerComponent::OnKeyPressed(const HC::KeyboardInput &keyboardInput) {
    if(keyboardInput.key == GLFW_KEY_SPACE) {
        std::cout << "FPS : " << 1.0f / Time::GetDeltaTime() << std::endl;
    }
    if (keyboardInput.key == GLFW_KEY_F) {
        SetCursorHidden(!IsCursorHidden());
    }
    else if (keyboardInput.key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(glfwGetCurrentContext(), GLFW_TRUE);
    }
}


