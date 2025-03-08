#pragma once

#include <utility>

#include "ECS/Entity.h"
#include "Components/TransformComponent.h"
#include "Viewport/EditorStates/EntitySelector.h"
#include "Singleton.h"
#include "Scenes/SceneResource.h"
#include "Scenes/SceneManager.h"
#include "GameScenes/GameScene.h"
#include "Window/IImGuiWindow.h"
#include "Interface.h"
#include "App.h"
#include "AttachableWindows/DefaultAttachableIMGUIWindows.h"
#include "Viewport/Windows/AssetWindows/AssetWindow.h"

namespace HC {
    class Asset;
    namespace Editor {
    struct EditorCommand {
        virtual void Execute() = 0;
        virtual void Undo() = 0;
    };

    struct AddEntityCommand : public EditorCommand {
        explicit AddEntityCommand(Entity * entityParent) : parent(entityParent) {}
        void Execute() override {
            if(!parent) return;

            auto entity = std::make_unique<Entity>();
            entity->SetName("New Entity");
            entity->AddComponent<TransformComponent>();
            EntitySelector::SetSelectedEntity(entity.get());

            parent->AddChild(std::move(entity));
        }
        void Undo() override {

        }

    private:
        Entity* parent;
    };


    struct RemoveEntityCommand : public EditorCommand {
        explicit RemoveEntityCommand(Entity * entityToRemove) : entity(entityToRemove) {}
        void Execute() override {
            if(!entity) return;
            entity->Destroy();
            EntitySelector::SetSelectedEntity(nullptr);
        }
        void Undo() override {
            if(!entity) return;
        }
    private:
        Entity* entity;
    };

    struct AddComponentCommand : public EditorCommand {
        explicit AddComponentCommand(Entity *entity, HCClass *ComponentToAdd) : entity(entity),
                                                                                component(ComponentToAdd) {}

        void Execute() override {
            if (!entity) return;
            entity->AddComponent(component);
        }

        void Undo() override {
            if (!entity) return;
            entity->RemoveComponent(component);
        }
    private:
        Entity *entity;
        HCClass *component;
    };

    struct RemoveComponentCommand : public EditorCommand {
        explicit RemoveComponentCommand(Entity *entity, HCClass *ComponentToRemove) : entity(entity),
                                                                                      component(ComponentToRemove) {}

        void Execute() override {
            if (!entity) return;
            entity->RemoveComponent(component);
        }

        void Undo() override {
            if (!entity) return;
            entity->AddComponent(component);
        }
    private:
        Entity *entity;
        HCClass *component;
    };

    struct ReparentEntityCommand : public EditorCommand {
        explicit ReparentEntityCommand(Entity *entity, Entity *newParent) : entity(entity), newParent(newParent) {}

        void Execute() override {
            if (!entity) return;
            if (!newParent) return;

            auto removedEntity = entity->GetParent()->RemoveChild(entity);
            newParent->AddChild(std::move(removedEntity));
        }

        void Undo() override {
            if (!entity) return;
            if (!newParent) return;

            auto removedEntity = newParent->RemoveChild(entity);
            entity->GetParent()->AddChild(std::move(removedEntity));
        }

    private:
        Entity *entity;
        Entity *newParent;
    };

    struct SaveCurrentSceneCommand : public EditorCommand {
        explicit SaveCurrentSceneCommand(Scene* scene) : scene(scene) {}

        void Execute() override {
            auto scene = SceneManager::GetInstance()->GetCurrentScene();
            auto sceneResource = ResourceManager::GetInstance()->Load<SceneResource>(RESOURCES_PATH"/Scenes/" + std::string(scene->GetName()) + ".hcscene");
            sceneResource->rawRootEntity = scene->GetRootEntity().get();
            sceneResource->Save();
            ResourceManager::GetInstance()->Unload(RESOURCES_PATH"/Scenes/" + std::string(scene->GetName()) + ".hcscene");

        }

        void Undo() override {

        }
    private:
        Scene* scene;
    };

    struct LoadSceneCommand : public EditorCommand {
        explicit LoadSceneCommand(Scene* scene) : scene(scene) {}

        void Execute() override {
            auto sceneResource = ResourceManager::GetInstance()->Load<SceneResource>(RESOURCES_PATH"/Scenes/" + std::string(scene->GetName()) + ".json");
            if(!sceneResource->rootEntity) return;
            EntitySelector::SetSelectedEntity(nullptr);
            auto loadedScene = SceneManager::GetInstance()->ChangeScene(std::make_unique<GameScene>(std::move(sceneResource->rootEntity)));

            ResourceManager::GetInstance()->Unload(RESOURCES_PATH"/Scenes/" + std::string(scene->GetName()) + ".hcscene");
        }

        void Undo() override {

        }

    private:
        Scene* scene;
    };

    struct DuplicateEntityCommand : public EditorCommand {
        explicit DuplicateEntityCommand(Entity* entity) : entity(entity) {}

        void Execute() override {
            if(!entity || !entity->GetParent()) return;

            auto newEntity = entity->Clone();
            EntitySelector::SetSelectedEntity(newEntity.get());
            entity->GetParent()->AddChild(std::move(newEntity));
        }

        void Undo() override {

        }

    private:
        Entity* entity;
    };

    template<typename T>
    struct TemplatedAttachWindowCommand : public EditorCommand {
        explicit TemplatedAttachWindowCommand()= default;
        ~TemplatedAttachWindowCommand() = default;

        void Execute() override {
            Viewport::AttachWindow<T>();
        }

        void Undo() override {

        }

    private:
    };

    struct AttachWindowCommand : public EditorCommand {
        explicit AttachWindowCommand(HCClass* windowClass) : windowClass(windowClass) {}
        ~AttachWindowCommand() = default;

        void Execute() override {
            Viewport::AttachWindow(windowClass);
        }

        void Undo() override {

        }

    protected:
        HCClass* windowClass;
    };

    struct AttachAssetWindowCommand : public AttachWindowCommand {
        explicit AttachAssetWindowCommand(HCClass* windowClass, std::shared_ptr<Asset> asset) : AttachWindowCommand(windowClass), asset(std::move(asset)) {}
        virtual ~AttachAssetWindowCommand() = default;

        void Execute() override {
            auto& windowRef = Viewport::AttachWindow(windowClass);
            auto assetWindow = dynamic_cast<Window::AssetWindow*>(&windowRef);
            if(assetWindow) {
                assetWindow->SetAsset(asset);
            }
        }

        void Undo() override {

        }

    private:
        std::shared_ptr<Asset> asset;
    };
    }
}

