#pragma once

#include "ECS/Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace HC {
    class TransformComponent : public Component {
    public:
        void Initialize(const glm::vec3 &defaultPosition = glm::vec3{0.0f}, const glm::vec3 &defaultRotation = glm::vec3{0.0f}, const glm::vec3 &defaultScale = glm::vec3{0.0f}) {
            SetPosition(position);
            SetRotation(rotation);
            SetScale(scale);
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
            modelMatrix = glm::translate(modelMatrix, GetPosition());
            modelMatrix = glm::rotate(modelMatrix, glm::radians(GetRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
            modelMatrix = glm::rotate(modelMatrix, glm::radians(GetRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
            modelMatrix = glm::rotate(modelMatrix, glm::radians(GetRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
            modelMatrix = glm::scale(modelMatrix, GetScale());
            return modelMatrix;
        }
    };

}
