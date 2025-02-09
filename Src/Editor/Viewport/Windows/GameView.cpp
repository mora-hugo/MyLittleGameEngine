#include "Viewport/Windows/GameView.h"
#include "imgui.h"
#include "Viewport/Viewport.h"
#include "Utils/Time.h"
HC::Editor::Window::GameView::GameView() : lastViewportSize(0.0f) {


}

void HC::Editor::Window::GameView::SetRenderTexture(GLuint renderTexture) {
    renderTextureId = renderTexture;
}

void HC::Editor::Window::GameView::Draw() {
    if(renderTextureId == 0) {
        return;
    }
    ImGui::Begin(GetWindowName());
    ImVec2 size = ImGui::GetContentRegionAvail();
    glm::vec2 pos = glm::vec2(ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y);

    if (Viewport::GetGameViewportSize() != glm::vec2(size.x, size.y)) {
        Viewport::SetGameViewportSize({size.x, size.y});
    }

    ImGui::Image((void*)(intptr_t)renderTextureId, size, ImVec2(0, 1), ImVec2(1, 0));
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    glm::vec2 textPos = pos + glm::vec2(10, 10);
    drawList->AddText(ImVec2(textPos.x, textPos.y), IM_COL32(255, 255, 255, 255), std::to_string(Time::GetFPS()).c_str());
    ImGui::End();

}

void HC::Editor::Window::GameView::Initialize(ImGuiID dockId) {
    DockableEditorWindow::Initialize(dockId);
    SetWindowName("Game Viewport");
    SetDockDirection(ImGuiDir_None);
}


