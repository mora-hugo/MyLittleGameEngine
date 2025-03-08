#include "Viewport/Windows/SceneManagerWindow.h"
#include "Scenes/SceneManager.h"
#include "imgui.h"
#include "AssetManager/AssetManager.h"
#include "AssetManager/SceneAsset.h"

HC::Editor::Window::SceneManagerWindow::SceneManagerWindow() {
}

void HC::Editor::Window::SceneManagerWindow::Draw() {
    BeginWindow();
    auto uuids = AssetManager::GetInstance()->GetLoadedAssetsUUIDByClass<SceneAsset>();
    for (auto uuid : uuids) {
        auto sceneAsset = AssetManager::GetInstance()->GetLoadedAsset<SceneAsset>(uuid);
        if (ImGui::Button(sceneAsset->GetAssetName().c_str())) {
            SceneManager::GetInstance()->ChangeScene(std::make_unique<Scene>(sceneAsset->GetRootEntity()));
        }
    }
    ImGui::End();
}

void HC::Editor::Window::SceneManagerWindow::Initialize(ImGuiID dockId) {
    DockableEditorWindow::Initialize(dockId);
    SetWindowName("Scene Manager");

    SetDockDirection(ImGuiDir_None);
    SetDockSize(0.30f);
}
