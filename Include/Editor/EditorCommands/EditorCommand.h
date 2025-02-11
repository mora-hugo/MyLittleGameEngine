#pragma once

#include "ECS/Entity.h"
#include "Components/TransformComponent.h"
#include "Viewport/EditorStates/EntitySelector.h"

namespace HC::Editor {
    struct EditorCommand {
        virtual void Execute() = 0;
        virtual void Undo() = 0;
    };

    struct AddEntityCommand : public EditorCommand {
        explicit AddEntityCommand(Entity * entityParent) : parent(entityParent) {}
        void Execute() override {
            if(!parent) return;

            auto entity = std::make_unique<Entity>("New Entity");
            entity->AddComponent<TransformComponent>();

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
}

