#include "AttachableWindows/DefaultAttachableIMGUIWindows.h"
#include "imgui.h"
#include "Utils/Time.h"
#include "imgui_internal.h"
#include "Renderer/Renderer.h"
#include "Viewport.h"
#include "Scenes/SceneManager.h"
#include "App.h"
#include "Singleton.h"
#include "Components/RendererComponent.h"
#include "Components/CameraComponent.h"

void HC::DefaultAttachableIMGUIWindow::Draw() {
    static bool dockspaceOpen = true;
    static bool opt_fullscreen = true;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    if (FPSupdateCounter++ >= FPSupdateRate) {
        currentFPS = Time::GetFPS();
        FPSupdateCounter = 0;
    }
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

    // Créer le DockSpace et récupérer son ID
    ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

    static bool firstTime = true;

    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Layouts")) {
            if (ImGui::MenuItem("Reset")) {
                firstTime = true; // Force la reconstruction du DockSpace
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::End(); // Fin DockSpace

    // ----------------------
    // RESET du DockSpace
    // ----------------------
    if (firstTime) {
        firstTime = false;

        // Reset du layout
        ImGui::LoadIniSettingsFromMemory("");

        // Supprimer l'ancien DockSpace et recréer proprement
        ImGui::DockBuilderRemoveNode(dockspace_id);
        ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

        // Créer des DockIDs
        ImGuiID dock_main_id = dockspace_id;
        ImGuiID dock_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.2f, nullptr, &dock_main_id);
        ImGuiID dock_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.2f, nullptr, &dock_main_id);
        ImGuiID dock_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.2f, nullptr, &dock_main_id);

        // Assigner chaque fenêtre à un dock
        ImGui::DockBuilderDockWindow("Scene Hierarchy", dock_left);
        ImGui::DockBuilderDockWindow("Inspector", dock_right);
        ImGui::DockBuilderDockWindow("Console", dock_bottom);
        ImGui::DockBuilderDockWindow("Game Viewport", dock_main_id);

        ImGui::DockBuilderFinish(dockspace_id);
    }

    // ----------------------
    // Fenêtres de l'éditeur
    // ----------------------

    ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_FirstUseEver);
    ImGui::Begin("Scene Hierarchy");
    if(ImGui::Button("+")) {
        auto entitycreationTest = std::make_unique<Entity>("New Entity");
        SceneManager::GetInstance()->GetCurrentScene()->AddEntity(std::move(entitycreationTest));

    }
    if(SceneManager::GetInstance()->GetCurrentScene()) {
        for(auto& entity : SceneManager::GetInstance()->GetCurrentScene()->GetEntities()) {
            ImGui::Text(" - %s", entity->GetName().c_str());
        }
    }
    ImGui::End();

    ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_FirstUseEver);
    ImGui::Begin("Inspector");
    ImGui::Text("Propriétés de l’objet sélectionné...");
    ImGui::End();

    ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_FirstUseEver);
    ImGui::Begin("Console");
    ImGui::Text("Logs...");
    ImGui::End();

    ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_FirstUseEver);
    ImGui::Begin("Game Viewport");
    ImVec2 size = ImGui::GetContentRegionAvail();
    glm::vec2 pos = glm::vec2(ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y);

    if(Viewport::GetGameViewportSize() != glm::vec2(size.x, size.y) || bWindowStateDirty == true) {
        bWindowStateDirty = false;
        Viewport::SetGameViewportSize({size.x, size.y});
    }

    ImGui::Image((void*)(intptr_t)renderTextureId, size, ImVec2(0, 1), ImVec2(1, 0));
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    glm::vec2 textPos = pos + glm::vec2(10, 10);// 10 pixels de marge à gauche et en haut
    auto formatedText = "FPS: " + std::to_string(currentFPS);
    drawList->AddText(ImVec2(textPos.x, textPos.y), IM_COL32(255, 255, 255, 255), formatedText.c_str());
    ImGui::End();
}

HC::DefaultAttachableIMGUIWindow::DefaultAttachableIMGUIWindow(GLuint renderTexture) : renderTextureId(renderTexture) {
    App::GetInstance()->GetWindow()->OnWindowResize.AddListener(this, HC_BIND_MEMBER_FUNCTION_ARGS(&DefaultAttachableIMGUIWindow::OnWindowResize, this, 1));
}

void HC::DefaultAttachableIMGUIWindow::OnWindowResize(const glm::vec2 &size) {
    bWindowStateDirty = true;
}
