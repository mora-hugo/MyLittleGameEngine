#include "GameScenes/GameScene.h"
#include "Components/TransformComponent.h"
#include "Components/RendererComponent.h"
#include "Components/PlayerControllerComponent.h"
#include "Utils/ShaderUtils.h"
#include "Components/RotationComponent.h"
#include "Components/CameraComponent.h"
#include "App.h"
#include "GLFW/glfw3.h"

HC::GameScene::GameScene(const char* name) : Scene(name) {

}

HC::GameScene::~GameScene() {

}

void HC::GameScene::BeginPlay() {
    Scene::BeginPlay();

    Input::ListenKey(GLFW_KEY_Z);
    Input::ListenKey(GLFW_KEY_S);

    Input::ListenKey(GLFW_KEY_UP);
    Input::ListenKey(GLFW_KEY_DOWN);
    Input::ListenKey(GLFW_KEY_LEFT);
    Input::ListenKey(GLFW_KEY_RIGHT);



/*
    // ------------
    auto entity = std::make_unique<Entity>("First cube");
    entity->AddComponent<TransformComponent>();
    entity->GetComponent<TransformComponent>()->SetPosition({-1.0f, 0.0f, -3.0f});
    entity->AddComponent<RendererComponent>();
    entity->AddComponent<RotationComponent>();
    AddEntity(std::move(entity));

    entity = std::make_unique<Entity>("First cube2");
    entity->AddComponent<TransformComponent>();
    entity->GetComponent<TransformComponent>()->SetPosition({-1.5f, 0.0f, -3.0f});
    entity->AddComponent(RendererComponent::StaticClass());

    AddEntity(std::move(entity));
    */
}

void HC::GameScene::Update(float deltaTime) {
    Scene::Update(deltaTime);
}

void HC::GameScene::Draw() {
    Scene::Draw();
}

void HC::GameScene::EndPlay() {
    Scene::EndPlay();
}
