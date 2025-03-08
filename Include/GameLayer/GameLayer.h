#pragma once
#include "glm/vec2.hpp"
namespace HC {
    class GameLayer {
    public:
        explicit GameLayer();
        virtual ~GameLayer() = default;

        GameLayer(const GameLayer&) = delete;


        GameLayer& operator=(const GameLayer&) = delete;

        virtual void BeginPlay();
        virtual void Update(float deltaTime);
        virtual void Draw();
        virtual void EndPlay();



        [[nodiscard]] glm::vec2 GetWindowSize() const;


    private:
        void LoadAllAssets();

    };
};
