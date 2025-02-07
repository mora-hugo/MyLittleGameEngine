#pragma once

#include <memory>
#include <glm/vec3.hpp>
#include "GameLayer.h"
#include "Renderer/Buffers/VertexArrayBuffer.h"
#include "Renderer/Vertex.h"
#include "Renderer/Shaders/ShaderProgram.h"
#include "Inputs/Inputs.h"
#include "ECS/Entity.h"
#include "Scenes/SceneManager.h"
#include "Scenes/Scene.h"
#include "AttachableWindows/DefaultAttachableIMGUIWindows.h"


namespace HC {

    class TestGameLayer : public GameLayer {
    public:
        TestGameLayer();
        ~TestGameLayer() override;

        void BeginPlay() override;
        void Update(float deltaTime) override;
        void Draw() override;
        void EndPlay() override;

    private:
    private:
        void InputKeyboardCallback(const KeyboardInput& input);
    private:
        std::unique_ptr<Scene> lastScene;
        //std::shared_ptr<DefaultAttachableIMGUIWindow> imguiWindow;
    };
}