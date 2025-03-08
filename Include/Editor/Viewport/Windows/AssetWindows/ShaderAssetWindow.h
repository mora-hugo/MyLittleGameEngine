#pragma once

#include "Viewport/Windows/AssetWindows/AssetWindow.h"
#include "AssetManager/ShaderAsset.h"
namespace HC::Editor::Window {
    class ShaderAssetWindow : public AssetWindow {
    public:
    bool IsOpenAtStart() const override { return false; }
    void Initialize(ImGuiID dockId) override;
    void Draw() override;
    START_REFLECTION(ShaderAssetWindow, AssetWindow)
    STOP_REFLECTION()

    ASSET_WINDOW_OF(ShaderAsset)
    };
}