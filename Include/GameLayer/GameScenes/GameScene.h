#pragma once

#include "Scenes/Scene.h"
#include "Inputs/Inputs.h"


namespace HC {
    class GameScene : public Scene {

    public:
        GameScene(const char* name);
        GameScene(std::unique_ptr<Entity> rootEntity);
        ~GameScene() override;

        void BeginPlay() override;
        void Update(float deltaTime) override;
        void Draw() override;
        void EndPlay() override;

        void OnKeyPressed(const KeyboardInput &keyboardInput);
    };
}