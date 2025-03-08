#pragma once
#include "Viewport/Windows/DockableEditorWindow.h"
#include "glad/glad.h"

namespace HC::Editor::Window {
    class GameView : public DockableEditorWindow {
    public:
        GameView();
        ~GameView() = default;

        void Initialize(ImGuiID dockId) override;

        void SetRenderTexture(GLuint renderTexture);

        void Draw() override;

        START_REFLECTION(GameView, DockableEditorWindow)
        STOP_REFLECTION()
    private:
        GLuint renderTextureId = 0;
        glm::vec2 lastViewportSize;
    };
}