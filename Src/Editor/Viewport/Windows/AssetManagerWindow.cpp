#include "Viewport/Windows/AssetManagerWindow.h"
#include "AssetManager/AssetManager.h"
#include "Viewport/Windows/AssetWindows/AssetWindow.h"
#include "EditorCommands/EditorCommandManager.h"

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

    if (ImGui::Button("Refresh assets")) {
        App::GetInstance()->LoadAllAssets();
    }

    for (auto& clazz : classes) {
        auto uuids = AssetManager::GetInstance()->GetAssetsUUIDByClass(clazz);

        if (ImGui::TreeNode(clazz->GetClassName())) {
            for (auto uuid : uuids) {
                auto asset = AssetManager::GetInstance()->GetAsset<Asset>(uuid);

                if (ImGui::TreeNode(asset->GetAssetName().c_str())) {
                    ImGui::Text("UUID: %u", uuid);
                    ImGui::Text("Type: %s", clazz->GetClassName());

                    if (ImGui::Button("Edit")) {
                        auto windowClass = AssetWindow::GetWindowClassFromAssetClass(clazz);
                        if (windowClass) {
                            Editor::EditorCommandManager::EnqueueCommand(std::make_unique<Editor::AttachAssetWindowCommand>(windowClass, asset));
                        }
                    }

                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }
    }

    ImGui::End();
}
