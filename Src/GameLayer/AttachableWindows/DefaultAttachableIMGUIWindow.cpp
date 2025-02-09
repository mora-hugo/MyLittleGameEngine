#include "AttachableWindows/DefaultAttachableIMGUIWindows.h"
#include "imgui.h"
#include "Utils/Time.h"
#include "imgui_internal.h"
#include "Viewport.h"
#include "Scenes/SceneManager.h"
#include "App.h"
#include "Components/CameraComponent.h"
#include "glm/gtc/type_ptr.hpp"
#include "Scenes/SceneResource.h"
#include "Components/TransformComponent.h"


HC::Entity* selectedEntity = nullptr;

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

    ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

    static bool firstTime = true;

    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Save Scene")) {
                SaveCurrentSceneToJson(RESOURCES_PATH"/Scenes/Scene1.json");
            }
            if (ImGui::MenuItem("Load Scene")) {
                LoadSceneFromJson(RESOURCES_PATH"/Scenes/Scene1.json");
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
        firstTime = false;

        ImGui::LoadIniSettingsFromMemory("");

        ImGui::DockBuilderRemoveNode(dockspace_id);
        ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

        ImGuiID dock_main_id = dockspace_id;
        ImGuiID dock_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.2f, nullptr, &dock_main_id);
        ImGuiID dock_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.2f, nullptr, &dock_main_id);
        ImGuiID dock_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.2f, nullptr, &dock_main_id);

        ImGui::DockBuilderDockWindow("Scene Hierarchy", dock_left);
        ImGui::DockBuilderDockWindow("Inspector", dock_right);
        ImGui::DockBuilderDockWindow("Console", dock_bottom);
        ImGui::DockBuilderDockWindow("Game Viewport", dock_main_id);

        ImGui::DockBuilderFinish(dockspace_id);
    }

    ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_FirstUseEver);
    ImGui::Begin("Scene Hierarchy");

    if (ImGui::Button("+")) {
        auto entitycreationTest = std::make_unique<Entity>("New Entity");
        entitycreationTest->AddComponent<TransformComponent>();
        SceneManager::GetInstance()->GetCurrentScene()->AddEntity(std::move(entitycreationTest));
    }

    if (SceneManager::GetInstance()->GetCurrentScene()) {
        for (auto& entity : SceneManager::GetInstance()->GetCurrentScene()->GetEntities()) {
            bool isSelected = (selectedEntity == entity.get());

            if (ImGui::Selectable(entity->GetName().c_str(), isSelected)) {
                selectedEntity = entity.get();
            }
        }
    }

    ImGui::End();

    ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_FirstUseEver);
    ImGui::Begin("Inspector");

    if (selectedEntity) {
        static char nameBuffer[256];

        std::strncpy(nameBuffer, selectedEntity->GetName().c_str(), sizeof(nameBuffer));
        nameBuffer[sizeof(nameBuffer) - 1] = '\0';

        if (ImGui::InputText("Entity Name", nameBuffer, sizeof(nameBuffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
            selectedEntity->SetName(nameBuffer);
        }
        bool bComponentDeleted = false;
        selectedEntity->ExecuteOnComponents<Component>([&](Component* component) {
            ImGui::Separator();

            ImGui::Text("%s", component->Class()->GetClassName());

            ImGui::SameLine();
            std::string buttonLabel = "x##" + std::string(component->Class()->GetClassName());
            if (ImGui::Button(buttonLabel.c_str())) {
                selectedEntity->RemoveComponent(component->Class());
                bComponentDeleted = true;
                return;
            }


            ImGui::Text("Component: ");
            for (auto& member : component->GetMembers()) {
                ImGui::Text("-- %s", member.first);
                auto non_const_property = const_cast<Property&>(member.second);

                if (non_const_property.Is<float>()) {
                    float* value = non_const_property.GetPropertyPtr<float>();
                    if (value) {
                        ImGui::DragFloat(member.first, value, 0.1f);
                    }
                } else if (non_const_property.Is<int>()) {
                    int* value = non_const_property.GetPropertyPtr<int>();
                    if (value) {
                        ImGui::DragInt(member.first, value);
                    }
                }
                else if (non_const_property.Is<glm::vec2>()) {
                    glm::vec2* value = non_const_property.GetPropertyPtr<glm::vec2>();
                    if (value) {
                        ImGui::DragFloat2(member.first, glm::value_ptr(*value), 0.1f);
                    }
                }
                else if (member.second.Is<glm::vec3>()) {
                    glm::vec3* value = non_const_property.GetPropertyPtr<glm::vec3>();
                    if (value) {
                        ImGui::DragFloat3(member.first, glm::value_ptr(*value), 0.1f);
                    }
                }
                else {
                    ImGui::Text("Non-editable type");
                }
            }
        });

        if (ImGui::BeginCombo("Add Component", "Select Component")) {
            for (auto& derivedClass : HCClass::GetDerivedClasses(Component::StaticClass())) {
                if (ImGui::Selectable(derivedClass->GetClassName())) {
                    selectedEntity->AddComponent(derivedClass);
                }
            }
            ImGui::EndCombo();
        }

    } else {
        ImGui::Text("No entity selected.");
    }

    ImGui::End();

    ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_FirstUseEver);
    ImGui::Begin("Console");
    ImGui::Text("Logs...");
    ImGui::End();

    ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_FirstUseEver);
    ImGui::Begin("Game Viewport");
    ImVec2 size = ImGui::GetContentRegionAvail();
    glm::vec2 pos = glm::vec2(ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y);

    if (Viewport::GetGameViewportSize() != glm::vec2(size.x, size.y) || bWindowStateDirty == true) {
        bWindowStateDirty = false;
        Viewport::SetGameViewportSize({size.x, size.y});
    }

    ImGui::Image((void*)(intptr_t)renderTextureId, size, ImVec2(0, 1), ImVec2(1, 0));
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    glm::vec2 textPos = pos + glm::vec2(10, 10);
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

void HC::DefaultAttachableIMGUIWindow::SaveCurrentSceneToJson(const std::string &path) {
    auto currentScene = SceneManager::GetInstance()->GetCurrentScene();
    Assertion(currentScene != nullptr, "No scene is currently loaded.");


    auto json = ResourceManager::GetInstance()->Load<SceneResource>(path);
    json->sceneName = currentScene->GetName();
    for (auto& entity : currentScene->GetEntities()) {
        auto newEntity = std::make_unique<Entity>(entity->GetName().c_str());
        json->entities.push_back(std::move(newEntity));
    }
    json->Save();
}

void HC::DefaultAttachableIMGUIWindow::LoadSceneFromJson(const std::string &path) {
    auto json = ResourceManager::GetInstance()->Load<SceneResource>(path);
    Assertion(json != nullptr, "Failed to load scene from path:" + path);

    auto scene = std::make_unique<Scene>(json->sceneName.c_str());
    for (auto& entity : json->entities) {
        scene->AddEntity(std::move(entity));
    }
    SceneManager::GetInstance()->ChangeScene(std::move(scene));
}
