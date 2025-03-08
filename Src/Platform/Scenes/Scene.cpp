#include "Scenes/Scene.h"
#include "Components/RendererComponent.h"

HC::Scene::Scene(const char *sceneName) : name(sceneName) {
    auto rootName = std::string("Root (") + sceneName + ")";
    rootEntity = std::make_unique<Entity>();
    rootEntity->AddComponent<TransformComponent>();
    rootEntity->SetName(rootName);
}

HC::Scene::Scene(std::unique_ptr<Entity> rootEntity) : name(rootEntity->GetName()) {
    rootEntity->AddComponent<TransformComponent>();
    this->rootEntity = std::move(rootEntity);
}

void HC::Scene::BeginPlay() {
    rootEntity->ExecuteOnChildrensRecursive([](Entity* entity, int depth) {
        entity->ExecuteOnComponents<Component>([](Component* comp) {
            comp->BeginPlay();
        });
    }, true);

    bSceneInitialized = true;
}

void HC::Scene::Update(float deltaTime) {
    if(!IsSceneInitialized()) return;
    rootEntity->ExecuteOnChildrensRecursive([deltaTime](Entity* entity, int depth) {
            entity->ExecuteOnComponents<Component>([deltaTime](Component* comp) {
                comp->Update(deltaTime);
            });
        }, true);

}

void HC::Scene::Draw() {
    if(!IsSceneInitialized()) return;
    rootEntity->ExecuteOnChildrensRecursive([](Entity* entity, int depth) {
            entity->ExecuteOnComponents<RendererComponent>([](RendererComponent* renderer) {
                renderer->Draw();
            });
        }, true);
}

void HC::Scene::EndPlay() {
        if(!IsSceneInitialized()) return;
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
    entity->Destroy();
}



