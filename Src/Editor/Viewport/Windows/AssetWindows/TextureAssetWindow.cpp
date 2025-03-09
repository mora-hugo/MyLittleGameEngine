#include "Viewport/Windows/AssetWindows/TextureAssetWindow.h"

void HC::Editor::Window::TextureAssetWindow::Initialize(ImGuiID dockId) {
    AssetWindow::Initialize(dockId);
    SetWindowName("Texture Asset");
    SetDockDirection(ImGuiDir_None);
    SetDockSize(0.30f);
}

void HC::Editor::Window::TextureAssetWindow::Draw() {
    BeginWindow(true);
    ImGui::Text("Width: %d", GetAsset()->GetTexture().GetWidth());
    ImGui::Text("Height: %d", GetAsset()->GetTexture().GetHeight());
    ImGui::Image((void*)(intptr_t)GetAsset()->GetTexture().GetTextureID(), ImVec2(256, 256));
    ImGui::End();
}
