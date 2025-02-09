#pragma once
#include "Viewport/Windows/DockableEditorWindow.h"

namespace HC::Editor::Window {
    class Hierarchy : public DockableEditorWindow {
    public:
        Hierarchy();
        ~Hierarchy() = default;

        void Initialize(ImGuiID dockId) override;
        void Draw() override;

        START_REFLECTION(Hierarchy, DockableEditorWindow)
        STOP_REFLECTION()
    };
}
