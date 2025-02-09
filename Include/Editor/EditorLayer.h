#pragma once

#include <memory>
#include "GameLayer.h"
#include "Renderer/Buffers/FrameBuffer.h"
#include "Viewport/Viewport.h"

namespace HC {
    class EditorLayer : public GameLayer {
    public:
        EditorLayer();
        ~EditorLayer() override;

        void BeginPlay() override;
        void Update(float deltaTime) override;
        void Draw() override;
        void EndPlay() override;


        void DrawImGui_Internal();

    private:
        std::unique_ptr<FrameBuffer> frameBuffer;
        std::unique_ptr<Viewport> viewport;
    };
}