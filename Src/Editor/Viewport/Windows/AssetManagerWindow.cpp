#include "Viewport/Windows/AssetManagerWindow.h"
#include "AssetManager/AssetManager.h"

HC::Editor::Window::AssetManagerWindow::AssetManagerWindow() {
}

void HC::Editor::Window::AssetManagerWindow::Initialize(ImGuiID dockId) {
    DockableEditorWindow::Initialize(dockId);
    SetWindowName("Asset Manager");
    SetDockDirection(ImGuiDir_None);
    SetDockSize(0.30f);
}

void HC::Editor::Window::AssetManagerWindow::Draw() {
    BeginWindow();

    auto classes = HCClass::GetDerivedClasses(Asset::StaticClass());

    for (auto& clazz : classes) {
        auto uuids = AssetManager::GetInstance()->GetAssetsUUIDByClass(clazz);

        if (ImGui::TreeNode(clazz->GetClassName())) {
            for (auto uuid : uuids) {
                auto asset = AssetManager::GetInstance()->GetAsset<Asset>(uuid);

                if (ImGui::TreeNode(asset->GetAssetName().c_str())) {
                    ImGui::Text("UUID: %u", uuid);
                    ImGui::Text("Type: %s", clazz->GetClassName());

                    if (ImGui::Button("Ouvrir")) {
                    }

                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }
    }

    ImGui::End();
}
