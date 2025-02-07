#include <App.h>
#include <iostream>
#include "Window/GLFWWindow.h"
#include "ResourceManager.h"
#include "TestGameLayer.h"
#include <Inputs/Input.h>

int HC::App::Run() {
    previousTime = std::chrono::steady_clock::now();
    currentTime = std::chrono::steady_clock::now();

    gameLayer->BeginPlay();
    while (!window->ShouldClose()) {
        auto dt = CalculateDeltaTime();
        glfwPollEvents();
        inputManager->ProcessInput();
        gameLayer->Update(dt);

        gameLayer->Draw();

#if HC_EDITOR == 0
        gameLayer->DrawImGui_Internal();
#endif
        window->SwapBuffers();
    }
    gameLayer->EndPlay();
    return EXIT_SUCCESS;
}

HC::App::App() {
    auto Config = ResourceManager::GetInstance()->Load<ConfigResource>(RESOURCES_PATH"/Configs/Config.conf");
    glm::ivec2 windowSize {0};
    std::string windowName;
    Assertion(Config && Config->GetValue<int>("window_width", windowSize.x) && Config->GetValue<int>("window_height", windowSize.y) && Config->GetValue("window_name", windowName), "Failed to load window parameters from config");
    CreateWindow(windowSize, windowName);
#if HC_EDITOR == 0
    gameLayer = std::make_unique<EditorLayer>();
#else
    gameLayer = std::make_unique<GameLayer>();
#endif
    inputManager = std::make_unique<InputManager>(*GetWindow());
    Input::Initialize(inputManager.get());
}

void HC::App::CreateWindow(const glm::ivec2 &windowSize,
                           const std::string &windowName) {
    window = std::make_unique<GLFWWindow>(windowSize.x, windowSize.y, windowName);
}


HC::App::~App() {

}

float HC::App::CalculateDeltaTime() {
    float dt = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - previousTime).count();
    previousTime = currentTime;
    currentTime = std::chrono::steady_clock::now();
    return dt;
}

glm::vec2 HC::App::GetWindowSize() const {
    return window->GetWindowSize();
}




