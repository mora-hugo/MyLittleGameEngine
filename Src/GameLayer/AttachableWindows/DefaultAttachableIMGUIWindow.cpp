#include "AttachableWindows/DefaultAttachableIMGUIWindows.h"
#include "imgui.h"
#include "Utils/Time.h"

void HC::DefaultAttachableIMGUIWindow::Draw() {
    ImGui::Begin(name.c_str());
    ImGui::Text("FPS : %f", 1/Time::GetSmoothDeltaTime());
    ImGui::End();
}

HC::DefaultAttachableIMGUIWindow::DefaultAttachableIMGUIWindow(const char* name) : name(name) {

}

