#pragma once

#include "ECS/Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "ECS/Entity.h"

namespace HC {
    class TransformComponent : public Component {
    public:
        TransformComponent() : Component(), lastEulerAngles(0.0f) {}

        void Initialize() override {}

        void SetPosition(const glm::vec3 &newPosition) {
            position = newPosition;
        }

        void SetRotation(const glm::vec3 &newRotation) {
            eulerAngles = glm::mod(newRotation, glm::vec3(360.0f)); // Garde les valeurs entre 0 et 360
            UpdateQuaternionFromEuler();
        }

        void SetScale(const glm::vec3 &newScale) {
            scale = newScale;
        }

        void Update(float deltaTime) override {
            if (glm::distance(eulerAngles, lastEulerAngles) > 0.001f) {
                UpdateQuaternionFromEuler();
                lastEulerAngles = eulerAngles;
            }

            ComputeWorldPosition();
            ComputeWorldRotation();
            ComputeWorldScale();
        }

        [[nodiscard]] glm::vec3 GetWorldPosition() const {
            return cachedWorldPosition;
        }

        [[nodiscard]] glm::vec3 GetWorldRotation() const {
            return glm::degrees(glm::eulerAngles(cachedWorldRotation)); // Convertit proprement
        }

        [[nodiscard]] glm::vec3 GetWorldScale() const {
            return cachedWorldScale;
        }

        [[nodiscard]] const glm::vec3 &GetPosition() const {
            return position;
        }

        [[nodiscard]] glm::vec3 GetRotation() const {
            return eulerAngles;
        }

        [[nodiscard]] const glm::vec3 &GetScale() const {
            return scale;
        }

    private:
        void ComputeWorldPosition() {
            cachedWorldPosition = GetPosition();
            auto parent = GetEntity()->GetParent();
            while (parent) {
                auto parentTransform = parent->GetComponent<TransformComponent>();
                if (parentTransform) {
                    cachedWorldPosition = parentTransform->cachedWorldRotation * cachedWorldPosition;
                    cachedWorldPosition += parentTransform->GetWorldPosition();
                }
                parent = parent->GetParent();
            }
        }

        void ComputeWorldRotation() {
            cachedWorldRotation = rotation;
            auto parent = GetEntity()->GetParent();
            while (parent) {
                auto parentTransform = parent->GetComponent<TransformComponent>();
                if (parentTransform) {
                    cachedWorldRotation = parentTransform->cachedWorldRotation * cachedWorldRotation;
                }
                parent = parent->GetParent();
            }
        }

        void ComputeWorldScale() {
            cachedWorldScale = GetScale();
            auto parent = GetEntity()->GetParent();
            while (parent) {
                auto parentTransform = parent->GetComponent<TransformComponent>();
                if (parentTransform) {
                    cachedWorldScale *= parentTransform->GetScale();
                }
                parent = parent->GetParent();
            }
        }

        void UpdateQuaternionFromEuler() {
            rotation = glm::quat(glm::radians(eulerAngles));
        }

    private:
        glm::vec3 position {0.0f};
        glm::vec3 eulerAngles {0.0f};
        glm::vec3 lastEulerAngles {0.0f};
        glm::vec3 scale {1.0f};

        glm::quat rotation {1, 0, 0, 0};
        glm::vec3 cachedWorldPosition;
        glm::quat cachedWorldRotation {1, 0, 0, 0};
        glm::vec3 cachedWorldScale;

    public:
        [[nodiscard]] glm::mat4 GetModelMatrix() const {
            glm::mat4 modelMatrix = glm::mat4(1.0f);
            modelMatrix = glm::translate(modelMatrix, GetWorldPosition());
            modelMatrix *= glm::toMat4(cachedWorldRotation);
            modelMatrix = glm::scale(modelMatrix, GetWorldScale());
            return modelMatrix;
        }

    START_REFLECTION(TransformComponent, Component)
                        ADD_MEMBER_PROPERTY(position)
                        ADD_MEMBER_PROPERTY(eulerAngles)
                        ADD_MEMBER_PROPERTY(scale)
        STOP_REFLECTION()
    };
}
