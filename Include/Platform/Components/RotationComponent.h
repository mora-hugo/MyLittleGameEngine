#pragma once

#include <glm/glm.hpp>
#include "ECS/Component.h"
#include "ECS/Entity.h"
#include "TransformComponent.h"
#include <iostream>

namespace HC {
    class RotationComponent : public Component {
    private:
        static constexpr const char* ClassName = "RotationComponent";
    public:
        RotationComponent() : Component(ClassName) {}
        void Initialize(float newSpeed, const glm::vec3& newRotationAxis) {
            speed = newSpeed;
            rotationAxis = newRotationAxis;
        }

        void Update(float deltaTime) override{
            GetEntity()->GetComponent<TransformComponent>()->SetRotation(GetEntity()->GetComponent<TransformComponent>()->GetRotation() + (speed * deltaTime * rotationAxis));
        }

    private:
        float speed = 0.0f;
        glm::vec3 rotationAxis = glm::vec3(0.0f);

        START_REFLECTION()
            ADD_MEMBER_PROPERTY(speed)
        STOP_REFLECTION()
    };
}