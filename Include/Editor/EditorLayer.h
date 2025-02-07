#pragma once

#include "GameLayer.h"

namespace HC {
    class EditorLayer : public GameLayer {
    public:
        EditorLayer();
        ~EditorLayer() override;

        void BeginPlay() override;
        void Update(float deltaTime) override;
        void Draw() override;
        void EndPlay() override;


#if HC_EDITOR == 0
        void DrawImGui_Internal();
#endif
    };
}