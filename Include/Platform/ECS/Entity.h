#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>
#include "Component.h"
#include "Utils/PtrUtils.h"
#include "Assertion.h"

namespace HC {
    class Entity {
    public:

        explicit Entity(const char* name) : name(name) { }
        virtual ~Entity() = default;

        void SetName(const std::string& name) {
            this->name = name;
        }

        std::string GetName() const{
            return name;
        }

        Entity* GetParent() const {
            return parent;
        }
        template <typename T>
        T* AddComponent() {
            auto type = T::StaticClass();
            auto component = PtrUtils::static_unique_pointer_cast<T,HCObject>(T::StaticClass()->CreateInstance());
            Assertion(component != nullptr, "Template type is not a component");
            component->RegisterEntity(this);
            component->Initialize();

            components[type] = std::move(component);

            return static_cast<T*>(components[type].get());
        }

        Component* AddComponent(HCClass* componentClass) {
            auto component = PtrUtils::static_unique_pointer_cast<Component,HCObject>(componentClass->CreateInstance());
            Assertion(component != nullptr, "Template type is not a component");
            component->RegisterEntity(this);
            component->Initialize();

            components[componentClass] = std::move(component);

            return components[componentClass].get();
        }

        template <typename T>
        T* GetComponent() const {
            auto it = components.find(T::StaticClass());
            if (it != components.end()) {
                return static_cast<T*>(it->second.get());
            }
            return nullptr;
        }

        template <typename T>
        bool HasComponent() const {
            return components.find(T::StaticClass()) != components.end();
        }

        void RemoveComponent(HCClass* componentClass) {
            auto it = components.find(componentClass);
            if (it != components.end()) {
                components.erase(it);
            }
        }

        template <typename T, typename Func>
        void ExecuteOnComponents(Func&& func) {
            std::vector<Component*> componentValues;
            for (auto& [type, component] : components) {
                componentValues.push_back(component.get());
            }

            for (auto& component : componentValues) {
                if (!component) {
                    return;
                }
                if (T* castedComponent = dynamic_cast<T*>(component)) {
                    func(castedComponent);
                }
            }
        }

        void ExecuteOnChildrens(std::function<void(Entity*, int depth)> func, bool includingSelf = true) {
            if (includingSelf) {
                func(this, 0);
            }

            for (auto& child : childrens) {
                func(child.get(), 1);
            }
        }

        void ExecuteOnChildrensRecursive(std::function<void(Entity*, int depth)> func, bool includingSelf = true) {
            ExecuteWorkerRecursive(func, this, 0, includingSelf);
        }

        void AddChild(std::unique_ptr<Entity> child) {
            child->parent = this;
            childrens.push_back(std::move(child));
        }

        bool RemoveChild(Entity* child) {
            for (auto it = childrens.begin(); it != childrens.end(); ++it) {
                if (it->get() == child) {
                    childrens.erase(it);
                    return true;
                }
            }

            for (auto& childEntity : childrens) {
                if (childEntity->RemoveChild(child)) {
                    return true;
                }
            }

            return false;
        }

    private:

        void ExecuteWorkerRecursive(std::function<void(Entity*, int)> func, Entity* entity, int depth, bool includingSelf) {
            if (includingSelf) {
                func(entity, depth);
            }

            for (auto& child : entity->childrens) {
                ExecuteWorkerRecursive(func, child.get(), depth + 1, true);
            }
        }




    private:
        Entity* parent = nullptr;
        std::map<HCClass*, std::unique_ptr<Component>> components;
        std::vector<std::unique_ptr<Entity>> childrens;
        std::string name;
    };
}
