#include "Viewport/Windows/Logs.h"
#include "imgui.h"
#include "Logger.h"

void HC::Editor::Window::Logs::Draw() {
    ImGui::Begin(GetWindowName());

    auto imguiSink = Logger::GetImGuiSink();
    if (imguiSink) {
        // Définir une zone de scrolling
        ImGui::BeginChild("LogScrollingRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

        // Vérifier si l'utilisateur est déjà en bas avant d'ajouter les nouvelles lignes
        float scrollY = ImGui::GetScrollY();
        float scrollMaxY = ImGui::GetScrollMaxY();
        bool isAtBottom = (scrollY >= scrollMaxY - 1.0f); // Tolérance pour éviter les flottants imprécis

        for (const auto& log : imguiSink->logs) {
            ImGui::TextUnformatted(log.c_str());
        }

        // Scroller en bas seulement si l'utilisateur n'a pas bougé manuellement
        if (isAtBottom) {
            ImGui::SetScrollHereY(1.0f);
        }

        ImGui::EndChild();
    }

    ImGui::End();
}


HC::Editor::Window::Logs::Logs() : DockableEditorWindow() {

}

void HC::Editor::Window::Logs::Initialize(ImGuiID dockId) {
    DockableEditorWindow::Initialize(dockId);
    SetWindowName("Console");
    SetDockDirection(ImGuiDir_Down);
    SetDockSize(0.2f);
}


