#include "AttachableWindows/DefaultAttachableIMGUIWindows.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "Viewport/Viewport.h"
#include "Scenes/SceneManager.h"
#include "App.h"
#include "Viewport/Windows/EditorWindow.h"
#include "Utils/PtrUtils.h"
#include "Viewport/Windows/GameView.h"
#include "EditorCommands/EditorCommandManager.h"
#include "EditorCommands/EditorCommand.h"
#include "Viewport/Windows/SceneManagerWindow.h"
#include "Viewport/Windows/AssetManagerWindow.h"
#include "Viewport/Windows/SceneSettingsWindow.h"

void HC::DefaultAttachableIMGUIWindow::Draw() {
    static bool dockspaceOpen = true;
    static bool opt_fullscreen = true;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen) {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    ImGui::Begin("DockSpace", &dockspaceOpen, window_flags);

    if (opt_fullscreen) {
        ImGui::PopStyleVar(2);
    }

    ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

    static bool firstTime = true;

    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Save Scene")) {
                SaveCurrentSceneToJson();
            }
            if (ImGui::MenuItem("Load Scene")) {
                LoadSceneFromJson();
            }
            ImGui::EndMenu();
        }


        if(ImGui::BeginMenu("Windows")) {
            if(ImGui::MenuItem("Scenes")) {
                Editor::EditorCommandManager::EnqueueCommand(std::make_unique<Editor::TemplatedAttachWindowCommand<Editor::Window::SceneManagerWindow>>());
            }
            if (ImGui::MenuItem("Scene settings")) {
                Editor::EditorCommandManager::EnqueueCommand(std::make_unique<Editor::TemplatedAttachWindowCommand<Editor::Window::SceneSettingsWindow>>());
            }
            if(ImGui::MenuItem("Assets Viewer")) {
                Editor::EditorCommandManager::EnqueueCommand(std::make_unique<Editor::TemplatedAttachWindowCommand<Editor::Window::AssetManagerWindow>>());
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Layouts")) {
            if (ImGui::MenuItem("Reset")) {
                firstTime = true;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::End();

    if (firstTime) {
        windows.clear();
        dockIds.clear();
        firstTime = false;

        ImGui::LoadIniSettingsFromMemory("");

        ImGui::DockBuilderRemoveNode(dockspace_id);
        ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

        ImGuiID dock_main_id = dockspace_id;





        for (auto& window : HCClass::GetDerivedClasses(Editor::Window::DockableEditorWindow::StaticClass())) {
            auto dockableWindow = PtrUtils::static_unique_pointer_cast<Editor::Window::DockableEditorWindow>(
                    window->CreateUniqueInstance());
            if(!dockableWindow->IsOpenAtStart()) continue;

            if(dockableWindow->Class() == Editor::Window::GameView::StaticClass()) {
                auto gameView = PtrUtils::static_unique_pointer_cast<Editor::Window::GameView>(
                        window->CreateUniqueInstance());
                gameView->SetRenderTexture(renderTextureId);
                dockableWindow = std::move(gameView);
            }
            dockableWindow->Initialize(dockspace_id);
            windows.push_back(std::move(dockableWindow));

        }
        for (auto& window : windows) {
            ImGuiID dockDirId;
            if(window->GetDockDirection() == ImGuiDir_None) {
                dockDirId = dock_main_id;
            }
            else {
                if(dockIds.contains(window->GetDockDirection())) {
                    dockDirId = dockIds[window->GetDockDirection()];
                }
                else {
                    dockDirId = ImGui::DockBuilderSplitNode(dock_main_id, window->GetDockDirection(), 0.2f, nullptr, &dock_main_id);
                    dockIds[window->GetDockDirection()] = dockDirId;
                }
            }

            ImGui::DockBuilderDockWindow(window->GetWindowName(), dockDirId);
        }

        ImGui::DockBuilderFinish(dockspace_id);

    }

    for (auto& window : windows) {
        window->Draw();
    }



}

HC::DefaultAttachableIMGUIWindow::DefaultAttachableIMGUIWindow(GLuint renderTexture) : renderTextureId(renderTexture) {
    App::GetInstance()->GetWindow()->OnWindowResize.AddListener(this, HC_BIND_MEMBER_FUNCTION_ARGS(&DefaultAttachableIMGUIWindow::OnWindowResize, this, 1));
}

void HC::DefaultAttachableIMGUIWindow::OnWindowResize(const glm::vec2 &size) {
}

void HC::DefaultAttachableIMGUIWindow::SaveCurrentSceneToJson() {
    Editor::EditorCommandManager::EnqueueCommand(std::make_unique<Editor::SaveCurrentSceneCommand>(SceneManager::GetInstance()->GetCurrentScene()));
}

void HC::DefaultAttachableIMGUIWindow::LoadSceneFromJson() {
    Editor::EditorCommandManager::EnqueueCommand(std::make_unique<Editor::LoadSceneCommand>(SceneManager::GetInstance()->GetCurrentScene()));

}

