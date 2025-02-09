#include "Viewport/Windows/Hierarchy.h"
#include "imgui.h"
#include "ECS/Entity.h"
#include "Components/TransformComponent.h"
#include "Scenes/SceneManager.h"
#include "Viewport/EditorStates/EntitySelector.h"

void HC::Editor::Window::Hierarchy::Draw() {
    ImGui::Begin(GetWindowName());

    if (ImGui::Button("+")) {
        auto entitycreationTest = std::make_unique<Entity>("New Entity");
        entitycreationTest->AddComponent<TransformComponent>();
        SceneManager::GetInstance()->GetCurrentScene()->AddEntity(std::move(entitycreationTest));
    }

    if (SceneManager::GetInstance()->GetCurrentScene()) {
        auto& entities = SceneManager::GetInstance()->GetCurrentScene()->GetEntities();
        for (int i = 0; i < entities.size(); i++) {
            auto& entity = *std::next(entities.begin(), i);
            bool isSelected = (EntitySelector::GetSelectedEntity() == entity.get());

            ImGui::PushID(i + 1);
            if (ImGui::Selectable(entity->GetName().c_str(), isSelected)) {
                EntitySelector::SetSelectedEntity(entity.get());
            }
            ImGui::PopID();
        }
    }

    ImGui::End();
}

HC::Editor::Window::Hierarchy::Hierarchy() {

}

void HC::Editor::Window::Hierarchy::Initialize(ImGuiID dockId) {
    DockableEditorWindow::Initialize(dockId);
    SetWindowName("Scene Hierarchy");
    SetDockDirection(ImGuiDir_Left);
    SetDockSize(0.15f);
}

