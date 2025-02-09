#pragma once

#include "Window/AttachableIMGUIWindow.h"
#include <string>
#include "glad/glad.h"
#include "imgui.h"
#include "glm/vec2.hpp"
#include "Viewport.h"
#include "Renderer/Buffers/FrameBuffer.h"

namespace HC {
    class DefaultAttachableIMGUIWindow: public AttachableIMGUIWindow {
    public:
         explicit DefaultAttachableIMGUIWindow(GLuint renderTexture);
    public:

        void Draw() override;

    private:
        void SaveCurrentSceneToJson(const std::string& path);
        void LoadSceneFromJson(const std::string& path);
    private:
        ImGuiID dock_main_id;
        ImGuiID dock_left;
        ImGuiID dock_right;
        ImGuiID dock_bottom;
        glm::vec2 lastViewportSize;

        GLuint renderTextureId;
        int currentFPS = 0;
        int FPSupdateCounter = 0;
        const int FPSupdateRate = 100;

        bool bWindowStateDirty = true;

        void OnWindowResize(const glm::vec2& size);
    };
}