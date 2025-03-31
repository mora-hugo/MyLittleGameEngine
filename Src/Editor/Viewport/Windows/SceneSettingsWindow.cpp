#include "Viewport/Windows/SceneSettingsWindow.h"

#include <Renderer/Renderer.h>

void HC::Editor::Window::SceneSettingsWindow::Initialize(ImGuiID dockId) {
    DockableEditorWindow::Initialize(dockId);
    SetWindowName("Scene Settings");
    SetDockDirection(ImGuiDir_None);
    SetDockSize(0.3f);
}

void HC::Editor::Window::SceneSettingsWindow::SceneSettingsWindow::Draw() {
    BeginWindow(true);
        ImGui::SliderFloat("Ambient Intensity", &ambientIntensity, 0.0f, 1.0f);
        if (ambientIntensity!= lastAmbientIntensity) {
            lastAmbientIntensity = ambientIntensity;
            Renderer::GetUniformBuffer("Lights")->SetData(&ambientIntensity, sizeof(float), 0);
        }
    ImGui::End();
}
