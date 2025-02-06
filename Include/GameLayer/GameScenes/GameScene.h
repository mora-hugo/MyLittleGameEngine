#pragma once

#include "Scenes/Scene.h"


namespace HC {
    class GameScene : public Scene {

    public:
        GameScene(const char* name);
        ~GameScene() override;

        void BeginPlay() override;
        void Update(float deltaTime) override;
        void Draw() override;
        void EndPlay() override;
    };
}