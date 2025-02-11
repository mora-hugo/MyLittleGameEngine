#pragma once
#include <spdlog/sinks/base_sink.h>
#include <imgui.h>
#include <vector>
#include <mutex>
#include <spdlog/fmt/chrono.h>

class ImGuiSink : public spdlog::sinks::base_sink<std::mutex> {
public:
    std::vector<std::string> logs;

protected:
    void sink_it_(const spdlog::details::log_msg& msg) override {
        fmt::memory_buffer formatted;
        fmt::format_to(
                std::back_inserter(formatted),
                "[{:%H:%M:%S}] [{}] {}\n",
                fmt::localtime(msg.time.time_since_epoch().count() / 1000000000),
                spdlog::level::to_string_view(msg.level),
                msg.payload
        );

        logs.emplace_back(std::string(formatted.data(), formatted.size()));

        if (logs.size() > 500) {
            logs.erase(logs.begin(), logs.begin() + 100);
        }
    }

    void flush_() override {}
};