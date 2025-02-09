#pragma once

#include "ECS/Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ECS/Entity.h"
namespace HC {
    class TransformComponent : public Component {
    public:
        TransformComponent() : Component() {}
        void Initialize() override {
        }

        void SetPosition(const glm::vec3 &newPosition) {
            position = newPosition;
        }

        void SetRotation(const glm::vec3 &newRotation) {
            rotation = newRotation;
            rotation.x = std::fmod(rotation.x, 360.0f);
            rotation.y = std::fmod(rotation.y, 360.0f);
            rotation.z = std::fmod(rotation.z, 360.0f);

        }

        void SetScale(const glm::vec3 &newScale) {
            scale = newScale;
        }

        [[nodiscard]] glm::vec3 GetWorldPosition() const {
            glm::vec3 worldPosition = GetPosition();
            auto parent = GetEntity()->GetParent();
            while (parent) {
                auto parentTransform = parent->GetComponent<TransformComponent>();
                if (parentTransform) {
                    worldPosition += parentTransform->GetPosition();
                }
                parent = parent->GetParent();
            }
            return worldPosition;
        }

        [[nodiscard]] const glm::vec3 &GetPosition() const {
            return position;
        }

        [[nodiscard]] const glm::vec3 &GetRotation() const {
            return rotation;
        }

        [[nodiscard]] const glm::vec3 &GetScale() const {
            return scale;
        }

    private:
        glm::vec3 position {0.0f};
        glm::vec3 rotation {0.0f};
        glm::vec3 scale {1.0f};

    public:
        [[nodiscard]] glm::mat4 GetModelMatrix() const {

            glm::mat4 modelMatrix = glm::mat4(1.0f);
            modelMatrix = glm::translate(modelMatrix, GetWorldPosition());
            modelMatrix = glm::rotate(modelMatrix, glm::radians(GetRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
            modelMatrix = glm::rotate(modelMatrix, glm::radians(GetRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
            modelMatrix = glm::rotate(modelMatrix, glm::radians(GetRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
            modelMatrix = glm::scale(modelMatrix, GetScale());
            return modelMatrix;
        }
        START_REFLECTION(TransformComponent, Component)
            ADD_MEMBER_PROPERTY(position)
            ADD_MEMBER_PROPERTY(rotation)
            ADD_MEMBER_PROPERTY(scale)
        STOP_REFLECTION()
    };

}
