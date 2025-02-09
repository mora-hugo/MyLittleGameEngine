#include "Viewport/Windows/Hierarchy.h"
#include "imgui.h"
#include "ECS/Entity.h"
#include "Components/TransformComponent.h"
#include "Scenes/SceneManager.h"
#include "Viewport/EditorStates/EntitySelector.h"

void HC::Editor::Window::Hierarchy::Draw() {
    ImGui::Begin(GetWindowName());

    if (ImGui::Button("+")) {
        CreateEntity(nullptr);
    }

    if (SceneManager::GetInstance()->GetCurrentScene()) {
        auto& entities = SceneManager::GetInstance()->GetCurrentScene()->GetEntities();
        int j = 0;

        for (int i = 0; i < entities.size(); i++) {
            auto& entity = *std::next(entities.begin(), i);

            entity->ExecuteOnChildrensRecursive([&](Entity* entity, int depth) {
                j++;

                if(depth != 0) {
                    ImGui::Indent(depth * 10.0f);
                }
                ImGui::PushID(j);

                bool isSelected = (EntitySelector::GetSelectedEntity() == entity);

                if (ImGui::Selectable(entity->GetName().c_str(), isSelected)) {
                    EntitySelector::SetSelectedEntity(entity);
                }

                if (ImGui::BeginPopupContextItem()) {
                    if (ImGui::MenuItem("Create Empty Child")) {
                        CreateEntity(entity);
                    }
                    ImGui::EndPopup();
                }

                ImGui::PopID();
                if(depth != 0) {
                    ImGui::Unindent(depth * 10.0f);
                }
            });
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

void HC::Editor::Window::Hierarchy::CreateEntity(HC::Entity *parent) {
    auto entity = std::make_unique<Entity>("New Entity");
    entity->AddComponent<TransformComponent>();
    if (parent) {
        parent->AddChild(std::move(entity));
    } else {
        SceneManager::GetInstance()->GetCurrentScene()->AddEntity(std::move(entity));
    }
}

