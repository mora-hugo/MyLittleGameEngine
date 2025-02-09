#pragma once

#include <glm/glm.hpp>
#include "ECS/Component.h"
#include "ECS/Entity.h"
#include "TransformComponent.h"
#include <iostream>

namespace HC {
    class RotationComponent : public Component {
    public:
        RotationComponent() : Component() {}
        void Initialize() override {

        }

        void Update(float deltaTime) override{
            GetEntity()->GetComponent<TransformComponent>()->SetRotation(GetEntity()->GetComponent<TransformComponent>()->GetRotation() + (speed * deltaTime * rotationAxis));
        }

    private:
        float speed = 1.f;
        glm::vec3 rotationAxis = glm::vec3(0.0f);

        START_REFLECTION(RotationComponent, Component)
            ADD_MEMBER_PROPERTY(speed)
            ADD_MEMBER_PROPERTY(rotationAxis)
        STOP_REFLECTION()
    };
}