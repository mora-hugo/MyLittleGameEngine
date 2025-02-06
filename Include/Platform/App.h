#pragma once

#include <memory>
#include <chrono>
#include "Inputs/InputManager.h"

namespace HC {
    class BaseWindow;
    class GameLayer;
    class App {
    public:
        App();
        ~App();
        int Run();
        float CalculateDeltaTime();

        [[nodiscard]] glm::vec2 GetWindowSize() const;

        [[nodiscard]] BaseWindow* GetWindow() const { return window.get(); }

    private:
        std::unique_ptr<BaseWindow> window;
        std::unique_ptr<GameLayer> gameLayer;
        std::unique_ptr<InputManager> inputManager;

        /* Delta time */
        std::chrono::time_point<std::chrono::steady_clock> currentTime;
        std::chrono::time_point<std::chrono::steady_clock> previousTime;


        void CreateWindow(const glm::ivec2 &windowSize, const std::string &windowName);
    };
}