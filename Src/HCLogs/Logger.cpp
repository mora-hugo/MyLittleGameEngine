#include "Logger.h"
#include <imgui.h>

void ShowLogWindow(bool* open) {
    ImGui::Begin("Console Log", open);

    auto imguiSink = Logger::GetImGuiSink();
    if (imguiSink) {
        for (const auto& log : imguiSink->logs) {
            ImGui::TextUnformatted(log.c_str());
        }
    }

    ImGui::End();
}
