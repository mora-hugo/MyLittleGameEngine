#include "AttachableWindows/SceneManagerWindow.h"
#include "Scenes/SceneManager.h"
#include "imgui.h"


HC::SceneManagerWindow::SceneManagerWindow() {

}

void HC::SceneManagerWindow::Draw() {
    if(!SceneManager::GetInstance()->HasSceneLoaded()) return;

    auto* currentScene = SceneManager::GetInstance()->GetCurrentScene();
    ImGui::Begin("Scene Manager");
    ImGui::Text("Current Scene: %s", currentScene->GetName().c_str());

    auto scene = SceneManager::GetInstance()->GetCurrentScene();
    if(scene) {
        for(auto& entity : scene->GetEntities()) {
            ImGui::Text(entity->GetName().c_str());
            entity->ExecuteOnComponents<Component>([](Component* component) {
                ImGui::Text("- Component");
            });
        }
    }
    ImGui::End();
}
