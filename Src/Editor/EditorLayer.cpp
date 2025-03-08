#include "EditorLayer.h"
#include "Interface.h"
#include "Window/IImGuiWindow.h"
#include "App.h"
#include "AttachableWindows/DefaultAttachableIMGUIWindows.h"
#include "Window/GLFWWindow.h"
#include "Renderer/Renderer.h"
#include "EditorCommands/EditorCommandManager.h"
#include "Logger.h"



HC::EditorLayer::EditorLayer() {

}

HC::EditorLayer::~EditorLayer() {

}

void HC::EditorLayer::DrawImGui_Internal() {
    auto* imGUIInterface = Interface::GetInterface<IImGUIWindow>(App::GetInstance()->GetWindow());
    if(!imGUIInterface) return;

    imGUIInterface->ImGUIFrameBegin();
    imGUIInterface->ImGUIRender();

}

void HC::EditorLayer::BeginPlay() {
    GameLayer::BeginPlay();
    frameBuffer = std::make_unique<FrameBuffer>(App::GetInstance()->GetWindow()->GetWindowSize());
    viewport = std::make_unique<Viewport>();
    auto* imGUIInterface = Interface::GetInterface<IImGUIWindow>(App::GetInstance()->GetWindow());
    if(imGUIInterface) {
        auto* glfwWindow = dynamic_cast<GLFWWindow*>(App::GetInstance()->GetWindow());
        if(glfwWindow) {
            imGUIInterface->AttachIMGUIWindow(std::make_shared<DefaultAttachableIMGUIWindow>(frameBuffer->GetRenderTextureId()));

        }
    }

    Logger::Init();
}


void HC::EditorLayer::Update(float deltaTime) {
    GameLayer::Update(deltaTime);
    while(Editor::EditorCommand* command = Editor::EditorCommandManager::DequeueCommand()) {
        command->Execute();
    }
}

void HC::EditorLayer::Draw() {
    Renderer::Clear();

    if (Viewport::GetGameViewportSize() != frameBuffer->GetSize() && Viewport::GetGameViewportSize().x > 0 && Viewport::GetGameViewportSize().y > 0) {
        frameBuffer->Resize(Viewport::GetGameViewportSize());

    }

    frameBuffer->Bind();

    GameLayer::Draw();
    frameBuffer->Unbind();
    DrawImGui_Internal();
}

void HC::EditorLayer::EndPlay() {
    GameLayer::EndPlay();
}
