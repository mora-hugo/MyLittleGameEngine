#include "Scenes/Scene.h"
#include "Components/RendererComponent.h"

HC::Scene::Scene(const char *sceneName) : name(sceneName) {

}

void HC::Scene::BeginPlay() {
    for(auto& entity : entities) {
        entity->ExecuteOnComponents<Component>([](Component* comp) {
            comp->BeginPlay();
        });
    }
}

void HC::Scene::Update(float deltaTime) {
    for(auto& entity : entities) {
        entity->ExecuteOnComponents<Component>([deltaTime](Component* component) {
            component->Update(deltaTime);
        });
    }
}

void HC::Scene::Draw() {
    for(auto& entity : entities) {
        entity->ExecuteOnComponents<RendererComponent>([](RendererComponent* comp) {
            comp->Draw();
        });
    }
}

void HC::Scene::EndPlay() {
    for(auto& entity : entities) {
        entity->ExecuteOnComponents<Component>([](Component* comp) {
            comp->EndPlay();
        });
    }
}

void HC::Scene::AddEntity(std::unique_ptr<Entity> entity) {
    entities.emplace(std::move(entity));
}

void HC::Scene::RemoveEntity(HC::Entity *entity) {
    entities.erase(std::ranges::find_if(entities.begin(), entities.end(), [entity](const std::unique_ptr<Entity>& e) {
        return e.get() == entity;
    }));
}

