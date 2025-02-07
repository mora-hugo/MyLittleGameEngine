#pragma once

#include <memory>
#include <chrono>
#include "EditorLayer.h"
#include "Inputs/InputManager.h"

namespace HC {
    class BaseWindow;
    class GameLayer;
    class App : public Singleton<App> {
    public:
        App();
        ~App();
        int Run();
        float CalculateDeltaTime();

        [[nodiscard]] glm::vec2 GetWindowSize() const;

        [[nodiscard]] BaseWindow* GetWindow() const { return window.get(); }

    private:
        std::unique_ptr<BaseWindow> window;
#if HC_EDITOR == 0
        std::unique_ptr<EditorLayer> gameLayer;
#else
        std::unique_ptr<GameLayer> gameLayer;
#endif
        std::unique_ptr<InputManager> inputManager;

        /* Delta time */
        std::chrono::time_point<std::chrono::steady_clock> currentTime;
        std::chrono::time_point<std::chrono::steady_clock> previousTime;


        void CreateWindow(const glm::ivec2 &windowSize, const std::string &windowName);
    };
}