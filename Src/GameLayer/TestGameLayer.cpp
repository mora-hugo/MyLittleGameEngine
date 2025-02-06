#include "TestGameLayer.h"
#include "Renderer/Shaders/ShaderProgram.h"
#include "Singleton.h"
#include "ResourceManager.h"
#include "Renderer/Shaders/ShadersResource.h"
#include "Inputs/Input.h"
#include "GLFW/glfw3.h"
#include "Renderer/Renderer.h"
#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
#include "Components/RendererComponent.h"

#include "App.h"
#include "Window/IImGuiWindow.h"
#include "Components/PlayerControllerComponent.h"
#include "Components/RotationComponent.h"
#include "Utils/ShaderUtils.h"
#include "AttachableWindows/SceneManagerWindow.h"
#include <iostream>

HC::TestGameLayer::TestGameLayer(App *app) : GameLayer(app) {

}

HC::TestGameLayer::~TestGameLayer() {

}

void HC::TestGameLayer::BeginPlay() {

    GameLayer::BeginPlay();

    Input::ListenKey(GLFW_KEY_UP);
    Input::ListenKey(GLFW_KEY_DOWN);
    Input::ListenKey(GLFW_KEY_LEFT);
    Input::ListenKey(GLFW_KEY_RIGHT);
    Input::GetKeyboardEventPressed().AddListener(this,
                                                HC_BIND_MEMBER_FUNCTION_ARGS(&TestGameLayer::InputKeyboardCallback,
                                                                             this, 1));


    Renderer::SetDepthBufferEnabled(true);
    Renderer::SetViewport(0,0, GetWindowSize().x, GetWindowSize().y);
    Renderer::SetClearColor({0.0f, 0.0f, 0.0f, 1.0f});

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

    auto scene = std::make_unique<Scene>("Scene 1");
    auto entity = std::make_unique<Entity>();
    entity->AddComponent<CameraComponent>(GetWindowSize(), GetApp()->GetWindow()->OnWindowResize);
    entity->AddComponent<TransformComponent>();
    entity->GetComponent<TransformComponent>()->SetPosition({0.0f, 0.0f, -3.0f});

    scene->AddEntity(std::move(entity));



    auto shaderProgram = ShaderUtils::LoadShader(RESOURCES_PATH"/Shaders/vertex.glsl",
                                                 RESOURCES_PATH"/Shaders/fragment.glsl");
    // ------------
    entity = std::make_unique<Entity>();
    entity->AddComponent<TransformComponent>();
    entity->GetComponent<TransformComponent>()->SetPosition({-1.0f, 0.0f, -3.0f});
    entity->AddComponent<RendererComponent>(vertices, indices, shaderProgram);
    entity->AddComponent<PlayerControllerComponent>(10.0f);

    scene->AddEntity(std::move(entity));

    // ------------
    entity = std::make_unique<Entity>();
    entity->AddComponent<TransformComponent>();
    entity->GetComponent<TransformComponent>()->SetPosition({1.0f, 0.0f, -3.0f});
    entity->AddComponent<RendererComponent>(vertices, indices, shaderProgram);
    entity->AddComponent<RotationComponent>(100.0f, glm::vec3(0.01f, 1.0f, 0.0f));

    scene->AddEntity(std::move(entity));

    SceneManager::GetInstance()->ChangeScene(std::move(scene));



    imguiWindow = std::make_shared<DefaultAttachableIMGUIWindow>("Default Window");

    auto* imGUIInterface = Interface::GetInterface<IImGUIWindow>(GetApp()->GetWindow());
    if(imGUIInterface) {
        imGUIInterface->AttachIMGUIWindow(imguiWindow);
        imGUIInterface->AttachIMGUIWindow(std::make_shared<SceneManagerWindow>());
    }
}

void HC::TestGameLayer::Update(float deltaTime) {
    Renderer::ResetMatrixDirtyFlags();
    GameLayer::Update(deltaTime);
    SceneManager::GetInstance()->Update(deltaTime);
}

void HC::TestGameLayer::Draw() {
    Renderer::Clear();
    SceneManager::GetInstance()->Draw();
}

void HC::TestGameLayer::EndPlay() {
    GameLayer::EndPlay();

}

void HC::TestGameLayer::InputKeyboardCallback(const HC::KeyboardInput &input) {
    if(input.key == GLFW_KEY_SPACE)  {
        if(lastScene == nullptr) {
            auto scene = std::make_unique<Scene>("Scene 2");
            lastScene = SceneManager::GetInstance()->ChangeScene(std::move(scene));
        }
        else {
            SceneManager::GetInstance()->ChangeScene(std::move(lastScene));
        }

    }
}
