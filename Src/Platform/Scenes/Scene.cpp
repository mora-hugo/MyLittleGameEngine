#include "Scenes/Scene.h"
#include "Components/RendererComponent.h"

HC::Scene::Scene(const char *sceneName) : name(sceneName) {
    rootEntity = std::make_unique<Entity>("Root");
}

void HC::Scene::BeginPlay() {
    rootEntity->ExecuteOnChildrensRecursive([](Entity* entity, int depth) {
        entity->ExecuteOnComponents<Component>([](Component* comp) {
            comp->BeginPlay();
        });
    }, true);
}

void HC::Scene::Update(float deltaTime) {
    rootEntity->ExecuteOnChildrensRecursive([deltaTime](Entity* entity, int depth) {
            entity->ExecuteOnComponents<Component>([deltaTime](Component* comp) {
                comp->Update(deltaTime);
            });
        }, true);

}

void HC::Scene::Draw() {
    rootEntity->ExecuteOnChildrensRecursive([](Entity* entity, int depth) {
            entity->ExecuteOnComponents<RendererComponent>([](RendererComponent* renderer) {
                renderer->Draw();
            });
        }, true);
}

void HC::Scene::EndPlay() {

        rootEntity->ExecuteOnChildrensRecursive([](Entity* entity, int depth) {
            entity->ExecuteOnComponents<Component>([](Component* comp) {
                comp->EndPlay();
            });
        }, true);
}

void HC::Scene::AddEntity(std::unique_ptr<Entity> entity) {
    entity->ExecuteOnComponents<Component>([](Component* comp) {
            comp->BeginPlay();
        });
    rootEntity->AddChild(std::move(entity));
}

void HC::Scene::RemoveEntity(HC::Entity *entity) {
    rootEntity->RemoveChild(entity);
}

