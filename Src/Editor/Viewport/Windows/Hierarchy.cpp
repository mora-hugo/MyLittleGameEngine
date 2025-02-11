#include "Viewport/Windows/Hierarchy.h"
#include "imgui.h"
#include "ECS/Entity.h"
#include "Components/TransformComponent.h"
#include "Scenes/SceneManager.h"
#include "Viewport/EditorStates/EntitySelector.h"
#include "EditorCommands/EditorCommand.h"
#include "EditorCommands/EditorCommandManager.h"

void HC::Editor::Window::Hierarchy::Draw() {
    ImGui::Begin(GetWindowName());

    if (SceneManager::GetInstance()->GetCurrentScene()) {
        auto& rootEntity = SceneManager::GetInstance()->GetCurrentScene()->GetRootEntity();
        int j = 0;

        rootEntity->ExecuteOnChildrensRecursive([&](Entity* entity, int depth) {
            j++;

            if(depth != 0) {
                ImGui::Indent(depth * 10.0f);
            }
            ImGui::PushID(j);

            bool isSelected = (EntitySelector::GetSelectedEntity() == entity);

            if (ImGui::Selectable(entity->GetName().c_str(), isSelected)) {
                EntitySelector::SetSelectedEntity(entity);
            }
            if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
                ImGui::SetDragDropPayload("ENTITY_DRAG_DROP", &entity, sizeof(Entity*)); // Stocke le pointeur
                ImGui::Text("Move: %s", entity->GetName().c_str());
                ImGui::EndDragDropSource();
            }

            if (ImGui::BeginDragDropTarget()) {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ENTITY_DRAG_DROP")) {
                    Entity* droppedEntity = *(Entity**)payload->Data;

                    if (droppedEntity != entity && droppedEntity->GetParent() != entity) {
                        ImGui::SetTooltip("IsAncestor: %s", droppedEntity->IsAncestor(entity) ? "true" : "false");
                        if(!droppedEntity->IsAncestor(entity)) {
                            EditorCommandManager::EnqueueCommand(std::make_unique<ReparentEntityCommand>(droppedEntity, entity));
                        }

                    }
                }
                ImGui::EndDragDropTarget();
            }

            if (ImGui::BeginPopupContextItem()) {
                if (ImGui::MenuItem("Create Empty Child")) {
                    EditorCommandManager::EnqueueCommand(std::make_unique<AddEntityCommand>(entity));
                }

                if (ImGui::MenuItem("Delete")) {
                    EditorCommandManager::EnqueueCommand(std::make_unique<RemoveEntityCommand>(entity));
                }
                ImGui::EndPopup();
            }

            ImGui::PopID();
            if(depth != 0) {
                ImGui::Unindent(depth * 10.0f);
            }
        });
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


