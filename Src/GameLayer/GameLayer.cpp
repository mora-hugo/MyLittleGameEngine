
#include "GameLayer.h"
#include "App.h"

#include "Utils/Time.h"
#include "Renderer/Renderer.h"
#include "Scenes/SceneManager.h"
#include "AssetManager/AssetManager.h"
#include "AssetManager/ShaderAsset.h"
#include "GameScenes/GameScene.h"
#include "AssetManager/SceneAsset.h"


namespace HC {


    void GameLayer::BeginPlay() {
        Logger::Init();
        Renderer::SetDepthBufferEnabled(true);
        Renderer::SetViewport(0,0, GetWindowSize().x, GetWindowSize().y);
        Renderer::SetClearColor({0.0f, 0.0f, 0.0f, 1.0f});


        App::GetInstance()->LoadAllAssets();
        auto uuids = AssetManager::GetInstance()->GetAssetsUUIDByClass<SceneAsset>();
        if(uuids.empty()) {
            Logger::LogError("No scene found");
            return;
        }
        auto sceneAsset = AssetManager::GetInstance()->GetAsset<SceneAsset>(uuids[0]);

        SceneManager::GetInstance()->ChangeScene(std::move(std::make_unique<GameScene>(std::move(sceneAsset->GetRootEntity()))));
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
