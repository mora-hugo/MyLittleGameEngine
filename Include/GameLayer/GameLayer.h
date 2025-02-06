#pragma once
#include "glm/vec2.hpp"
namespace HC {
    class GameLayer {
    public:
        explicit GameLayer(class App* appContext);
        virtual ~GameLayer() = default;

        GameLayer(const GameLayer&) = delete;


        GameLayer& operator=(const GameLayer&) = delete;

        virtual void BeginPlay();
        virtual void Update(float deltaTime);
        virtual void Draw();
        virtual void EndPlay();

        [[nodiscard]] glm::vec2 GetWindowSize() const;
        [[nodiscard]] App* GetApp() const;

#if REMOVE_IMGUI == 0
        void DrawImGui_Internal();

#endif

    private:
        class App* app;


    };
};
