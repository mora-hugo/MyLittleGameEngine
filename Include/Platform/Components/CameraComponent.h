
#pragma once

#include <memory>
#include "glm/glm.hpp"
#include "ECS/Component.h"
#include "Event/ReadOnlyEvent.h"
#include "Reflection/ReflexionMacro.h"
#include "Reflection/IReflectable.h"
namespace HC {
    class CameraComponent : public Component {
    private:
    public:
        explicit CameraComponent() : Component() {}
        ~CameraComponent() override;
        void Initialize() override;
        void Update(float deltaTime) override;

        [[nodiscard]] glm::mat4 GetViewMatrix() const;
        [[nodiscard]] glm::mat4 GetProjectionMatrix() const;

        std::unique_ptr<ReadOnlyEvent<glm::vec2>> OnWindowResizePtr;

    private:
        void BindEvents();
        void UnbindEvents();
        void OnWindowResizeEvent(const glm::vec2 &size);

    private:
        float aspectRatio;
        float zoom = 0;
        float fov = 45.0f;
        float nearPlane = 0.1f;
        float farPlane = 100.0f;

        glm::vec2 windowSize {0.0f, 0.0f};

    START_REFLECTION(CameraComponent, Component)
         ADD_MEMBER_PROPERTY(aspectRatio)
         ADD_MEMBER_PROPERTY(zoom)
         ADD_MEMBER_PROPERTY(fov)
         ADD_MEMBER_PROPERTY(nearPlane)
         ADD_MEMBER_PROPERTY(farPlane)
    STOP_REFLECTION()

    public: \
    };
}