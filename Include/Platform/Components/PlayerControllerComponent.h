#pragma once

#include "ECS/Component.h"
#include "Inputs/Input.h"

#include <glm/glm.hpp>

namespace HC {
    class PlayerControllerComponent : public Component {
    public:
        PlayerControllerComponent() : Component() {}
        ~PlayerControllerComponent() override;

    public:
        void Initialize() override;

    protected:
        void Move(const glm::vec3 &direction, float amount = 1.0f);
        void BindEvents();
        void UnbindEvents();
        void SetCursorHidden(bool bHidden);
        [[nodiscard]] bool IsCursorHidden() const;
    private:
        void OnKeyRepeat(const KeyboardInput &keyboardInput);
        void OnKeyPressed(const KeyboardInput &keyboardInput);



    private:
        glm::vec2 lastMousePosition {0.0f, 0.0f};
        float moveSpeed = 1.0f;
        float mouseSensitivity = 001.f;

        START_REFLECTION(PlayerControllerComponent, Component)
            ADD_MEMBER_PROPERTY(moveSpeed)
            ADD_MEMBER_PROPERTY(mouseSensitivity)
        STOP_REFLECTION()
    };
         }
