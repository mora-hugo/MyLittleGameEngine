#include "Viewport/Windows/Logs.h"
#include "imgui.h"

void HC::Editor::Window::Logs::Draw() {
    ImGui::Begin(GetWindowName());
    ImGui::Text("Logs...");
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


