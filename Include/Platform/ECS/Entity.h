#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>
#include "Component.h"

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

        template <typename T, typename... Args>
        T* AddComponent(Args&&... args) {
            auto type = std::type_index(typeid(T));
            auto component = std::make_unique<T>();
            component->RegisterEntity(this);
            component->Initialize(std::forward<Args>(args)...);

            components[type] = std::move(component);

            return static_cast<T*>(components[type].get());
        }

        template <typename T>
        T* GetComponent() const {
            auto type = std::type_index(typeid(T));
            auto it = components.find(type);
            if (it != components.end()) {
                return static_cast<T*>(it->second.get());
            }
            return nullptr;
        }

        template <typename T>
        bool HasComponent() const {
            return components.find(std::type_index(typeid(T))) != components.end();
        }

        template <typename T, typename Func>
        void ExecuteOnComponents(Func&& func) {
            for (auto& [type, component] : components) {
                if (T* castedComponent = dynamic_cast<T*>(component.get())) {
                    func(castedComponent);
                }
            }
        }





    private:
        std::unordered_map<std::type_index, std::unique_ptr<Component>> components;

        std::string name;
    };
}
