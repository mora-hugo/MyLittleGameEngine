#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>
#include "Component.h"
#include "Utils/PtrUtils.h"
#include "Assertion.h"

namespace HC {
    class Entity : public HCObject {
    public:

        explicit Entity() { }
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
            auto component = PtrUtils::static_unique_pointer_cast<T,HCObject>(T::StaticClass()->CreateUniqueInstance());
            Assertion(component != nullptr, "Template type is not a component");
            component->RegisterEntity(this);
            component->Initialize();

            components[type] = std::move(component);

            return static_cast<T*>(components[type].get());
        }

        Component* AddComponent(HCClass* componentClass) {
            auto component = PtrUtils::static_unique_pointer_cast<Component,HCObject>(
                    componentClass->CreateUniqueInstance());
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


        template <typename T, typename Func>
        void ExecuteOnComponentsConst(const Func&& func) const{
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

        std::unique_ptr<Entity> RemoveChild(Entity* child) {
            for (auto it = childrens.begin(); it != childrens.end(); ++it) {
                if (it->get() == child) {
                    auto removedChild = std::move(*it);
                    childrens.erase(it);
                    return removedChild;
                }
            }
            return nullptr;
        }

        bool IsAncestor(Entity* potentialParent) {
            Entity* current = potentialParent;
            while (current) {
                if (current == this) {
                    return true;
                }
                current = current->GetParent();
            }
            return false;
        }

        bool HasChildren() {
            return !childrens.empty();
        }

        int GetChildrenCount() {
            return childrens.size();
        }

        void Destroy() {
            auto childrenToDestroy = std::move(childrens);
            childrens.clear();

            for (auto& child : childrenToDestroy) {
                child->Destroy();
            }

            components.clear();

            if (parent) {
                parent->RemoveChild(this);
            }
        }

        std::vector<std::unique_ptr<Entity>>& GetChildrens() {
            return childrens;
        }

        nlohmann::json ToJson() const override {
            nlohmann::json j;
            j["name"] = name;
            nlohmann::json componentsJson = nlohmann::json::array();
            for (const auto& [cls, component] : components) {
                nlohmann::json compJson;
                compJson["class"] = component->Class()->GetClassName();
                compJson["data"] = component->ToJson();
                componentsJson.push_back(compJson);
            }
            j["components"] = componentsJson;
            nlohmann::json childrenJson = nlohmann::json::array();
            for (const auto& child : childrens) {
                childrenJson.push_back(child->ToJson());
            }
            j["childrens"] = childrenJson;
            return j;
        }

        void FromJson(const nlohmann::json &j) override {
            name = j.at("name").get<std::string>();
            components.clear();
            for (const auto& compJson : j.at("components")) {
                std::string compClassName = compJson.at("class").get<std::string>();
                HCClass* compHCClass = HCClass::GetClassFromName(compClassName.c_str());
                Component* comp = AddComponent(compHCClass);
                comp->FromJson(compJson.at("data"));
            }
            childrens.clear();
            if (j.contains("childrens")) {
                for (const auto& childJson : j.at("childrens")) {
                    std::unique_ptr<Entity> child = std::make_unique<Entity>();
                    child->FromJson(childJson);
                    AddChild(std::move(child));
                }
            }
        }

        std::unique_ptr<Entity> Clone() {
            auto clone = std::make_unique<Entity>();
            auto json = ToJson();
            clone->FromJson(json);
            return clone;
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


    START_REFLECTION(Entity)
    STOP_REFLECTION()

    private:
        Entity* parent = nullptr;
        std::map<HCClass*, std::unique_ptr<Component>> components;
        std::vector<std::unique_ptr<Entity>> childrens;
        std::string name;
    };
}
