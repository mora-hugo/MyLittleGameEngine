#include "Viewport/Windows/AssetWindows/ShaderAssetWindow.h"
#include "AssetManager/Asset.h"

void HC::Editor::Window::ShaderAssetWindow::Initialize(ImGuiID dockId) {
    DockableEditorWindow::Initialize(dockId);
    SetWindowName("Shader Asset");
    SetDockDirection(ImGuiDir_None);
    SetDockSize(0.30f);
}

void HC::Editor::Window::ShaderAssetWindow::Draw() {
    BeginWindow(true);
    //ImGui::Text("Shader Asset : %s", asset->GetAssetName().c_str());
    ImGui::Text("Shader Asset");
    ImGui::End();
}
