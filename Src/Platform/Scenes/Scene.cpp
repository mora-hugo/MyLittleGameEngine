#include "Scenes/Scene.h"
#include "Components/RendererComponent.h"

HC::Scene::Scene(const char *sceneName) : name(sceneName) {

}

void HC::Scene::BeginPlay() {
    for(auto& entity : entities) {
        entity->ExecuteOnChildrensRecursive([](Entity* entity, int depth) {
            entity->ExecuteOnComponents<Component>([](Component* comp) {
                comp->BeginPlay();
            });
        }, true);
    }
}

void HC::Scene::Update(float deltaTime) {
    for(auto& entity : entities) {
        entity->ExecuteOnChildrensRecursive([deltaTime](Entity* entity, int depth) {
            entity->ExecuteOnComponents<Component>([deltaTime](Component* comp) {
                comp->Update(deltaTime);
            });
        }, true);

    }
}

void HC::Scene::Draw() {
    for(auto& entity : entities) {
        entity->ExecuteOnChildrensRecursive([](Entity* entity, int depth) {
            entity->ExecuteOnComponents<RendererComponent>([](RendererComponent* renderer) {
                renderer->Draw();
            });
        }, true);
    }
}

void HC::Scene::EndPlay() {
    for(auto& entity : entities) {
        entity->ExecuteOnChildrensRecursive([](Entity* entity, int depth) {
            entity->ExecuteOnComponents<Component>([](Component* comp) {
                comp->EndPlay();
            });
        }, true);
    }
}

void HC::Scene::AddEntity(std::unique_ptr<Entity> entity) {
    entity->ExecuteOnComponents<Component>([](Component* comp) {
            comp->BeginPlay();
        });
    entities.emplace(std::move(entity));
}

void HC::Scene::RemoveEntity(HC::Entity *entity) {
    entities.erase(std::ranges::find_if(entities.begin(), entities.end(), [entity](const std::unique_ptr<Entity>& e) {
        return e.get() == entity;
    }));
}

