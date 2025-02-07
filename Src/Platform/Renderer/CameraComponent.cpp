
#include <glm/gtc/matrix_transform.hpp>
#include "Components/CameraComponent.h"
#include "ECS/Entity.h"
#include "Components/TransformComponent.h"
#include "Renderer/Renderer.h"
#include "Singleton.h"
#include "App.h"





void HC::CameraComponent::Initialize() {
    windowSize = App::GetInstance()->GetWindow()->GetWindowSize();

    OnWindowResizePtr = std::make_unique<ReadOnlyEvent<glm::vec2>>(App::GetInstance()->GetWindow()->OnWindowResize);

    aspectRatio = windowSize.x / windowSize.y;
    BindEvents();
}

void HC::CameraComponent::Update(float deltaTime) {
    Component::Update(deltaTime);
    Renderer::SetProjectionMatrix(GetProjectionMatrix());
    Renderer::SetViewMatrix(GetViewMatrix());
}

glm::mat4 HC::CameraComponent::GetViewMatrix() const {
    return glm::translate(glm::mat4(1.0f), GetEntity()->GetComponent<TransformComponent>()->GetPosition()) * glm::rotate(glm::mat4(1.0f), glm::radians(GetEntity()->GetComponent<TransformComponent>()->GetRotation().x), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(GetEntity()->GetComponent<TransformComponent>()->GetRotation().y), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(GetEntity()->GetComponent<TransformComponent>()->GetRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::mat4 HC::CameraComponent::GetProjectionMatrix() const {
    return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

void HC::CameraComponent::OnWindowResizeEvent(const glm::vec2 &size) {
    aspectRatio = size.x / size.y;
    windowSize = size;
}

void HC::CameraComponent::BindEvents() {
    OnWindowResizePtr->AddListener(this, HC_BIND_MEMBER_FUNCTION_ARGS(&CameraComponent::OnWindowResizeEvent, this, 1));
}

void HC::CameraComponent::UnbindEvents() {

    OnWindowResizePtr->RemoveListener(this);

}

HC::CameraComponent::~CameraComponent() {
    UnbindEvents();
}



