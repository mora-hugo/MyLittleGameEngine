#pragma once
#include "Viewport/Windows/DockableEditorWindow.h"

namespace HC::Editor::Window {
    class Logs : public DockableEditorWindow {
    public:
        Logs();
        ~Logs() = default;

        void Initialize(ImGuiID dockId) override;

        void Draw() override;

        START_REFLECTION(Logs, DockableEditorWindow)
        STOP_REFLECTION()
    };
}