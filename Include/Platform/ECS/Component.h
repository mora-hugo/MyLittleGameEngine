#pragma once

#include <typeindex>
#include "Reflection/Class.h"
#include "Reflection/ReflexionMacro.h"
namespace HC {
    class Entity;

    class Component : public Class{
    public:
        virtual ~Component() = default;
        Component(const char* name) : Class(name) {}
        void Initialize() {}
        virtual void BeginPlay() {}
        virtual void EndPlay() {}
        [[nodiscard]] Entity* GetEntity() const { return entity; }
        virtual void Update(float deltaTime) {}

        void RegisterEntity(Entity* owner) { entity = owner; }


    private:
        Entity* entity = nullptr;
    };
}
