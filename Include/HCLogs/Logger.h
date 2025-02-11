#pragma once
#include "ImGuiLogger.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <memory>

class Logger {
public:
    static void Init() {
        imgui_sink = std::make_shared<ImGuiSink>();

        logger = std::make_shared<spdlog::logger>("GameLogger", spdlog::sinks_init_list{imgui_sink});
        spdlog::set_default_logger(logger);

        spdlog::set_pattern("[%H:%M:%S] [%^%l%$] %v");
    }

    static std::shared_ptr<spdlog::logger> GetLogger() {
        return logger;
    }

    static std::shared_ptr<ImGuiSink> GetImGuiSink() {
        return imgui_sink;
    }

    template<typename... Args>
    static void LogInfo(fmt::format_string<Args...> fmt, Args&&... args) {
        spdlog::info(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void LogWarning(fmt::format_string<Args...> fmt, Args&&... args) {
        spdlog::warn(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void LogError(fmt::format_string<Args...> fmt, Args&&... args) {
        spdlog::error(fmt, std::forward<Args>(args)...);
    }

private:
    static inline std::shared_ptr<spdlog::logger> logger;
    static inline std::shared_ptr<ImGuiSink> imgui_sink;
};

