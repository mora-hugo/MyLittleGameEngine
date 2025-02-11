#pragma once

#include <memory>
#include "Singleton.h"
#include "ECS/Entity.h"
namespace HC {
    class EntitySelector {
    public:
        EntitySelector();
        ~EntitySelector();

        static Entity * GetSelectedEntity() { return selectedEntity; }
        static bool IsEntitySelected() { return selectedEntity != nullptr; }
        static void SetSelectedEntity(Entity * entity) { selectedEntity = entity; }

    private:

        static inline Entity * selectedEntity = nullptr;



    };
}