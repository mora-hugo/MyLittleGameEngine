#pragma once

#include <memory>
#include "glm/glm.hpp"
#include "ECS/Component.h"
#include "Event/ReadOnlyEvent.h"

namespace HC {
    class CameraComponent : public Component {
    public:
        explicit CameraComponent();
        ~CameraComponent() override;
        void Initialize(const glm::vec2& defaultWindowSize, Event<glm::vec2> &onWindowResize);
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
        float zoom;
        glm::vec2 windowSize {0.0f, 0.0f};

    };
}