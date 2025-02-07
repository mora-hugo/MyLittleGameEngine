#pragma once

#include "ECS/Entity.h"
#include <unordered_set>
namespace HC {
    class Scene {
    public:
        Scene(const char* sceneName);
        virtual ~Scene() = default;

        virtual void BeginPlay();
        virtual void Update(float deltaTime);
        virtual void Draw();
        virtual void EndPlay();

        void AddEntity(std::unique_ptr<Entity> entity);
        void RemoveEntity(Entity* entity);

        std::unordered_set<std::unique_ptr<Entity>>& GetEntities() {
            return entities;
        }

        std::string GetName() const {
            return name;
        }

    private:
        std::unordered_set<std::unique_ptr<Entity>> entities;
        std::string name;
    };
}