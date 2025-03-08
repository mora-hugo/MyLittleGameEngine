#include "Viewport/Windows/AssetWindows/AssetWindow.h"


void HC::Editor::Window::AssetWindow::Initialize(ImGuiID dockId) {
    DockableEditorWindow::Initialize(dockId);
}

void HC::Editor::Window::AssetWindow::Draw() {

}

void HC::Editor::Window::AssetWindow::SetAsset(std::shared_ptr<Asset> asset) {
    this->asset = asset;
}
