#pragma once

#include <typeindex>
#include "Reflection/HCClass.h"
#include "Reflection/ReflexionMacro.h"

namespace HC {
    class Entity;
    class Component : public HCObject {

    public:
        Component() {}
        virtual ~Component();
        virtual void Initialize() = 0;
        virtual void BeginPlay() {}
        virtual void EndPlay() {}
        [[nodiscard]] Entity* GetEntity() const { return entity; }
        virtual void Draw() {}
        virtual void Update(float deltaTime) {}

        void RegisterEntity(Entity* owner) { entity = owner; }



    private:
        Entity* entity = nullptr;

        START_REFLECTION(Component)

        STOP_REFLECTION()
    };

}
