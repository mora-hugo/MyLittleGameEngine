#pragma once

#include "DockableEditorWindow.h"

namespace HC::Editor::Window {
    class SceneSettingsWindow : public DockableEditorWindow {
    public:
        void Initialize(ImGuiID dockId) override;
        void Draw() override;

    private:
        float ambientIntensity = 0.9f;
        float lastAmbientIntensity = 0;
    };
}