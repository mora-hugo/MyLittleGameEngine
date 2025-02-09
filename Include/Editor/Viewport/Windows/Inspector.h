#pragma once
#include "Viewport/Windows/DockableEditorWindow.h"

namespace HC::Editor::Window {
    class Inspector : public DockableEditorWindow {
    public:
        Inspector();
        ~Inspector() = default;

        void Initialize(ImGuiID dockId) override;
        void Draw() override;

        START_REFLECTION(Inspector, DockableEditorWindow)
        STOP_REFLECTION()
    };
}