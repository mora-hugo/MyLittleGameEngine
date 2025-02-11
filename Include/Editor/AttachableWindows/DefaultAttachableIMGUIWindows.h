#pragma once

#include "Window/AttachableIMGUIWindow.h"
#include <string>
#include "glad/glad.h"
#include "imgui.h"
#include "glm/vec2.hpp"
#include "Viewport/Viewport.h"
#include "Renderer/Buffers/FrameBuffer.h"
#include "Viewport/Windows/DockableEditorWindow.h"

namespace HC {
    class DefaultAttachableIMGUIWindow: public AttachableIMGUIWindow {
    public:
         explicit DefaultAttachableIMGUIWindow(GLuint renderTexture);
    public:

        void Draw() override;

    private:
        void SaveCurrentSceneToJson();
        void LoadSceneFromJson();
    private:
        glm::vec2 lastViewportSize;
        GLuint renderTextureId;

        std::unordered_map<ImGuiDir_, ImGuiID> dockIds;
        std::vector<std::unique_ptr<Editor::Window::DockableEditorWindow>> windows;
        void OnWindowResize(const glm::vec2& size);
    };
}