#include "EditorLayer.h"
#include "Interface.h"
#include "Window/IImGuiWindow.h"
#include "Singleton.h"
#include "App.h"
#include "AttachableWindows/SceneManagerWindow.h"
#include "AttachableWindows/DefaultAttachableIMGUIWindows.h"

HC::EditorLayer::EditorLayer() {

}

HC::EditorLayer::~EditorLayer() {

}
#if HC_EDITOR == 0

void HC::EditorLayer::DrawImGui_Internal() {
    auto* imGUIInterface = Interface::GetInterface<IImGUIWindow>(App::GetInstance()->GetWindow());
    if(!imGUIInterface) return;

    imGUIInterface->ImGUIFrameBegin();
    imGUIInterface->ImGUIRender();

}
#endif

void HC::EditorLayer::BeginPlay() {
    GameLayer::BeginPlay();

    auto* imGUIInterface = Interface::GetInterface<IImGUIWindow>(App::GetInstance()->GetWindow());
    if(imGUIInterface) {
        imGUIInterface->AttachIMGUIWindow(std::make_shared<DefaultAttachableIMGUIWindow>("Stats"));
        imGUIInterface->AttachIMGUIWindow(std::make_shared<SceneManagerWindow>());

    }
}

void HC::EditorLayer::Update(float deltaTime) {
    GameLayer::Update(deltaTime);
}

void HC::EditorLayer::Draw() {
    GameLayer::Draw();
}

void HC::EditorLayer::EndPlay() {
    GameLayer::EndPlay();
}
