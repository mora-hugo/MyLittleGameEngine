#pragma once

#include "ECS/Entity.h"
#include <unordered_set>
namespace HC {
    class Scene {
    public:
        explicit Scene(const char* sceneName);
        explicit Scene(std::unique_ptr<Entity> rootEntity);
        virtual ~Scene() = default;

        virtual void BeginPlay();
        virtual void Update(float deltaTime);
        virtual void Draw();
        virtual void EndPlay();

        void AddEntity(std::unique_ptr<Entity> entity);
        void RemoveEntity(Entity* entity);

        std::vector<std::unique_ptr<Entity>>& GetEntities() {
            return rootEntity->GetChildrens();
        }

        std::unique_ptr<Entity>& GetRootEntity() {
            return rootEntity;
        }

        std::string GetName() const {
            return name;
        }
    private:
        bool IsSceneInitialized() const {
            return bSceneInitialized;
        }
    private:
        std::unique_ptr<Entity> rootEntity;
        std::string name;

        bool bSceneInitialized = false;
    };
}