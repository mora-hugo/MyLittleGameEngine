#pragma once

#include <memory>
#include <string>
#include "glm/fwd.hpp"
#include "glm/detail/type_vec2.hpp"
#include "Event/Event.h"
#include "Inputs/Inputs.h"

namespace HC {
    class BaseWindow {
    public:

        BaseWindow(int width, int height, const std::string &windowName);
        ~BaseWindow() = default;

        BaseWindow(const BaseWindow&) = delete;
        virtual BaseWindow &operator=(const BaseWindow&) = delete;

        /* Getters */
        [[nodiscard]] inline const glm::uvec2 & GetWindowSize() const { return windowSize; }
        [[nodiscard]] inline const std::string & GetWindowName() const { return windowName; }
        [[nodiscard]] virtual const glm::vec2 GetMousePosition() const = 0;

        //TODO usage of glfw key for now everywhere
        virtual int GetKey(int key) const = 0;
        virtual int GetMouseButton(int key) const = 0;
        virtual bool ShouldClose() const = 0;
        virtual void SwapBuffers() const = 0;

    protected:
        void SetWindowSize(const glm::uvec2 &size) { windowSize = size; }
        void SetWindowName(const std::string &name) { windowName = name; }
    public:
        Event<KeyboardInput> OnWindowHandledKeyboardInput;
        Event<MouseInput> OnWindowHandledMouseInput;
        Event<glm::vec2> OnWindowResize;

    private:

        glm::uvec2 windowSize {0};
        std::string windowName;
    };
}
