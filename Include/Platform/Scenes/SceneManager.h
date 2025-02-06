#pragma once

#include <unordered_map>
#include <memory>
#include "Scene.h"
#include "Assertion.h"
#include "Singleton.h"
namespace HC {
    class SceneManager : public Singleton<SceneManager> {
    public:
        SceneManager() = default;
        ~SceneManager() = default;

        /* Return last scene */
        std::unique_ptr<Scene> ChangeScene(std::unique_ptr<Scene> scene) {

            if(HasSceneLoaded()) {
                EndPlay();
            }

            auto lastScene = std::move(currentScene);
            currentScene = std::move(scene);

            BeginPlay();
            return lastScene;
        }

        Scene * GetCurrentScene() {
            return currentScene.get();
        }

        void Update(float deltaTime) {
            Assertion(currentScene != nullptr, "No scene to update");
            currentScene->Update(deltaTime);
        }

        void Draw() {
            Assertion(currentScene != nullptr, "No scene to draw");
            currentScene->Draw();
        }

        bool HasSceneLoaded() const {
            return currentScene != nullptr;
        }
    private:
        void BeginPlay() {
            Assertion(currentScene != nullptr, "No scene to play");
            currentScene->BeginPlay();
        }

        void EndPlay() {
            Assertion(currentScene != nullptr, "No scene to endplay");
            currentScene->EndPlay();
        }
    private:
        std::unique_ptr<Scene> currentScene;
    };
}