#pragma once

#include "Viewport/Windows/DockableEditorWindow.h"
#include <string>
namespace HC::Editor::Window {
    class SceneManagerWindow: public DockableEditorWindow {
    public:
        SceneManagerWindow();
        ~SceneManagerWindow() = default;
        void Initialize(ImGuiID dockId) override;
    public:
        void Draw() override;


    };
}
