
#include <iostream>
#include "GameLayer.h"
#include "App.h"
#include "Interface.h"
#include "Window/GLFWWindow.h"
#include "Utils/Time.h"


namespace HC {


    void GameLayer::BeginPlay() {

    }

    void GameLayer::Update(float deltaTime) {
        Time::SetDeltaTime(deltaTime);
    }

    void GameLayer::EndPlay() {

    }

    void GameLayer::Draw() {
    }
#if REMOVE_IMGUI == 0

    void GameLayer::DrawImGui_Internal() {
        auto* imGUIInterface = Interface::GetInterface<IImGUIWindow>(app->GetWindow());
        if(!imGUIInterface) return;

        imGUIInterface->ImGUIFrameBegin();
        imGUIInterface->ImGUIRender();

    }
#endif  
    GameLayer::GameLayer(App* appContext) : app(appContext) {

    }

    glm::vec2 GameLayer::GetWindowSize() const {
        return app->GetWindowSize();
    }

    App *GameLayer::GetApp() const {
        return app;
    }


}
