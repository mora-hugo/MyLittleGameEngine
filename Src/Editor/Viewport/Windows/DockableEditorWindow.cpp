#include "Viewport/Windows/DockableEditorWindow.h"

HC::Editor::Window::DockableEditorWindow::DockableEditorWindow() {

}

void HC::Editor::Window::DockableEditorWindow::Initialize(ImGuiID mainDockId) {
    dockId = mainDockId;
}

HC::Editor::Window::DockableEditorWindow::~DockableEditorWindow() {
    OnWindowClosed.ClearListeners();
}
