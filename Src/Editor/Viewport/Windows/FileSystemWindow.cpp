#include "Viewport/Windows/FileSystemWindow.h"
#include "App.h"
#include "Logger.h"
#include "imgui.h"
#include "AssetManager/AssetManager.h"
#include "AssetManager/ShaderAsset.h"

namespace HC::Editor::Window {

    FileSystemWindow::FileSystemWindow()
            : currentPath("Assets") {
        RefreshContents();
    }

    void FileSystemWindow::Initialize(ImGuiID dockId) {
        DockableEditorWindow::Initialize(dockId);
        SetWindowName("File System");
        SetDockDirection(ImGuiDir_Down);
        SetDockSize(0.2f);
    }

    void FileSystemWindow::Draw() {
        ImGui::Begin(GetWindowName());

        ImGui::Text("Current Directory: %s", currentPath.c_str());

        if (currentPath != "Assets") {
            if (ImGui::Button("< Back")) {
                size_t pos = currentPath.find_last_of("/\\");
                currentPath = (pos == std::string::npos) ? "Assets" : currentPath.substr(0, pos);
                RefreshContents();
            }
        }

        for (int i = 0; i < cachedContents.size(); i++) {
            auto entry = cachedContents[i].get();
            if (entry->IsDirectory()) {
                if (ImGui::Selectable(entry->GetDirectory().name.c_str(), false, ImGuiSelectableFlags_DontClosePopups)) {
                    currentPath += "/" + entry->GetDirectory().name;
                    RefreshContents();
                }
            } else {
                ImGui::Text(entry->GetFile().name.c_str());
            }
        }

        ImGui::End();
    }

    void FileSystemWindow::RefreshContents() {
        cachedContents.clear();

        auto directory = App::GetInstance()->GetFileSystem().GetDirectory(currentPath);
        if (!directory->Exists()) {
            Logger::LogError("Directory \"{0}\" does not exist", currentPath);
            return;
        }

        for (auto& entry : directory->GetContents()) {
            cachedContents.emplace_back(std::move(entry));

        }
    }
}
