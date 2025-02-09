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

        std::string &GetName() {
            return name;
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





    private:
        std::unordered_map<HCClass*, std::unique_ptr<Component>> components;

        std::string name;
    };
}
