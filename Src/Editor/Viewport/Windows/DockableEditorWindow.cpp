#include "Viewport/Windows/DockableEditorWindow.h"

#include <EditorCommands/EditorCommandManager.h>

HC::Editor::Window::DockableEditorWindow::DockableEditorWindow() {

}

void HC::Editor::Window::DockableEditorWindow::Initialize(ImGuiID mainDockId) {
    dockId = mainDockId;
}

void HC::Editor::Window::DockableEditorWindow::BeginWindow(bool canBeClosed) {
        bool open = true;
        if (canBeClosed)
            ImGui::Begin(GetWindowName(), &open);
        else
            ImGui::Begin(GetWindowName());

        if (canBeClosed && !open) {
            EditorCommandManager::EnqueueCommand(std::make_unique<DetachWindowCommand>(this));
        }
}
