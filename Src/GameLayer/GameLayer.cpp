
#include <iostream>
#include "GameLayer.h"
#include "App.h"
#include "Interface.h"
#include "Window/GLFWWindow.h"
#include "Utils/Time.h"
#include "Renderer/Renderer.h"
#include "AttachableWindows/SceneManagerWindow.h"
#include "Singleton.h"
#include "Scenes/SceneManager.h"
#include "GameScenes/GameScene.h"


namespace HC {


    void GameLayer::BeginPlay() {
        Renderer::SetDepthBufferEnabled(true);
        Renderer::SetViewport(0,0, GetWindowSize().x, GetWindowSize().y);
        Renderer::SetClearColor({0.0f, 0.0f, 0.0f, 1.0f});


        auto rootEntity = std::make_unique<Entity>();
        rootEntity->SetName("Premiere scene wouhou");
        SceneManager::GetInstance()->ChangeScene(std::move(std::make_unique<GameScene>(std::move(rootEntity))));
    }

    void GameLayer::Update(float deltaTime) {
        Renderer::ResetMatrixDirtyFlags();
        Time::SetDeltaTime(deltaTime);
        SceneManager::GetInstance()->Update(deltaTime);
        //TODO: Camera not removed bc matrix are reset before components update and for now
        // delete logic is made in the draw function
    }

    void GameLayer::EndPlay() {

    }

    void GameLayer::Draw() {
        Renderer::Clear();
        SceneManager::GetInstance()->Draw();
    }

    GameLayer::GameLayer() {

    }

    glm::vec2 GameLayer::GetWindowSize() const {
        return App::GetInstance()->GetWindowSize();
    }



}
