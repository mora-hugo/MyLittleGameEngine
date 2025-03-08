#include "Viewport/Windows/Inspector.h"
#include "imgui.h"

#include "Viewport/EditorStates/EntitySelector.h"
#include "Viewport/InspectorProperties/DefaultInspectorProperties.h"
#include "EditorCommands/EditorCommandManager.h"
#include "Scenes/SceneManager.h"

void HC::Editor::Window::Inspector::Draw() {
    ImGui::Begin(GetWindowName());

    if (EntitySelector::GetSelectedEntity()) {
        if(!EntitySelector::IsEntitySelected()) return;
        auto &rootEntity = SceneManager::GetInstance()->GetCurrentScene()->GetRootEntity();
        if (rootEntity.get() == EntitySelector::GetSelectedEntity()) {
            ImGui::End();
            return;
        }
        auto selectedEntity = EntitySelector::GetSelectedEntity();
        static char nameBuffer[256];

        std::strncpy(nameBuffer, selectedEntity->GetName().c_str(), sizeof(nameBuffer));
        nameBuffer[sizeof(nameBuffer) - 1] = '\0';

        if (ImGui::InputText("Entity Name", nameBuffer, sizeof(nameBuffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
            selectedEntity->SetName(nameBuffer);
        }
        selectedEntity->ExecuteOnComponents<Component>([&](Component* component) {
            ImGui::Separator();

            ImGui::Text("%s", component->Class()->GetClassName());

            ImGui::SameLine();
            std::string buttonLabel = "x##" + std::string(component->Class()->GetClassName());
            if (ImGui::Button(buttonLabel.c_str())) {
                EditorCommandManager::EnqueueCommand(std::make_unique<RemoveComponentCommand>(selectedEntity, component->Class()));
                return;
            }


            for (auto& member : component->GetMutableMembers()) {
                ImGui::Text("-- %s", member.first);

                auto inspectorClass = InspectorProperty::GetInspectorPropertyClass(member.second);
                if (inspectorClass) {
                    auto inspectorProperty = PtrUtils::static_unique_pointer_cast<InspectorProperty>(
                            inspectorClass->CreateUniqueInstance());
                    inspectorProperty->SetProperty(member.second);
                    inspectorProperty->Draw();
                } else {
                    ImGui::Text("Non-editable type");
                }
            }
        });
        ImGui::Separator();
        if (ImGui::BeginCombo("Add Component", "Select Component")) {
            for (auto& derivedClass : HCClass::GetDerivedClasses(Component::StaticClass())) {
                if (ImGui::Selectable(derivedClass->GetClassName())) {
                    EditorCommandManager::EnqueueCommand(std::make_unique<AddComponentCommand>(selectedEntity, derivedClass));
                }
            }
            ImGui::EndCombo();
        }

    } else {
        ImGui::Text("No entity selected.");
    }

    ImGui::End();
}

HC::Editor::Window::Inspector::Inspector() {

}

void HC::Editor::Window::Inspector::Initialize(ImGuiID dockId) {
    DockableEditorWindow::Initialize(dockId);
    SetWindowName("Inspector");
    SetDockDirection(ImGuiDir_Right);
    SetDockSize(0.30f);
}


