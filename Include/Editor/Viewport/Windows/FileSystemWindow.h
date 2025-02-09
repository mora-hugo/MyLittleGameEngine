#pragma once
#include "Viewport/Windows/DockableEditorWindow.h"

namespace HC::Editor::Window {
    class FileSystemWindow : public DockableEditorWindow {
    public:
        FileSystemWindow();
        ~FileSystemWindow() = default;
        void Initialize(ImGuiID dockId) override;
        void Draw() override;

        START_REFLECTION(FileSystemWindow, DockableEditorWindow)
        STOP_REFLECTION()
    };
}