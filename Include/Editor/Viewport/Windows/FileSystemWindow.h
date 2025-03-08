#pragma once

#include "Viewport/Windows/DockableEditorWindow.h"
#include "FileSystem/FileSystem.h"
#include <vector>
#include <memory>

namespace HC::Editor::Window {
    class FileSystemWindow : public DockableEditorWindow {
    public:
        FileSystemWindow();
        ~FileSystemWindow() = default;

        void Initialize(ImGuiID dockId) override;
        void Draw() override;
        void RefreshContents();

    private:
        std::string currentPath;
        std::vector<std::unique_ptr<HC::FileSystem::FileDirectoryVariant>> cachedContents;

    START_REFLECTION(FileSystemWindow, DockableEditorWindow)
        STOP_REFLECTION()
    };
}
