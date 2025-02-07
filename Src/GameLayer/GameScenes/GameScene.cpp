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

    std::vector<Vertex> vertices = {
            // Face avant
            {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}}, // 0
            {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}}, // 1
            {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}}, // 2
            {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}}, // 3

            // Face arrière
            {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}}, // 4
            {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 1.0f}}, // 5
            {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}}, // 6
            {{-0.5f,  0.5f, -0.5f}, {0.5f, 0.5f, 0.5f}}  // 7
    };

    std::vector<unsigned int> indices = {
            // Face avant
            0, 1, 2,  2, 3, 0,

            // Face arrière
            4, 5, 6,  6, 7, 4,

            // Face gauche
            4, 0, 3,  3, 7, 4,

            // Face droite
            1, 5, 6,  6, 2, 1,

            // Face haut
            3, 2, 6,  6, 7, 3,

            // Face bas
            4, 5, 1,  1, 0, 4
    };

    auto shaderProgram = ShaderUtils::LoadShader(RESOURCES_PATH"/Shaders/vertex.glsl",
                                                 RESOURCES_PATH"/Shaders/fragment.glsl");

    auto entity = std::make_unique<Entity>("Camera");
    entity->AddComponent<CameraComponent>(App::GetInstance()->GetWindowSize(), App::GetInstance()->GetWindow()->OnWindowResize);
    entity->AddComponent<TransformComponent>();
    entity->GetComponent<TransformComponent>()->SetPosition({0.0f, 0.0f, -3.0f});
    entity->AddComponent<PlayerControllerComponent>(10.0f);


    AddEntity(std::move(entity));

    // ------------
    entity = std::make_unique<Entity>("First cube");
    entity->AddComponent<TransformComponent>();
    entity->GetComponent<TransformComponent>()->SetPosition({1.0f, 0.0f, -3.0f});
    entity->AddComponent<RendererComponent>(vertices, indices, shaderProgram);
    entity->AddComponent<RotationComponent>(100.0f, glm::vec3(0.01f, 1.0f, 0.0f));

    AddEntity(std::move(entity));
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
