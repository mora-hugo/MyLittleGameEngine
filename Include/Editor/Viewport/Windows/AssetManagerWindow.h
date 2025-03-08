#pragma once

#include "Viewport/Windows/DockableEditorWindow.h"
#include "AssetWindows/ShaderAssetWindow.h"
namespace HC::Editor::Window {
    class AssetManagerWindow : public DockableEditorWindow {
    public:
        AssetManagerWindow();
        virtual ~AssetManagerWindow() = default;

        void Initialize(ImGuiID dockId) override;
        void Draw() override;

        START_REFLECTION(DockableEditorWindow)
        STOP_REFLECTION()
    };
}