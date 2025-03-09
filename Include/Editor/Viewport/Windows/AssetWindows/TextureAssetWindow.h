#pragma once

#include "Viewport/Windows/AssetWindows/AssetWindow.h"
#include "AssetManager/TextureAsset.h"
namespace HC::Editor::Window {
    class TextureAssetWindow : public AssetWindow {
    public:
    void Initialize(ImGuiID dockId) override;
    void Draw() override;
    START_REFLECTION(TextureAssetWindow, AssetWindow)
    STOP_REFLECTION()

    ASSET_WINDOW_OF(TextureAsset)
    };
}