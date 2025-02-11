#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <unordered_set>
#include "BaseWindow.h"
#include "IImGuiWindow.h"
#include "Utils/ShaderUtils.h"

namespace HC {
    class GLFWWindow : public BaseWindow
#if defined(HC_EDITOR)
            , public IImGUIWindow
#endif
                    {
    public:
        GLFWWindow(int width, int height, const std::string &windowName);
        ~GLFWWindow() override;


        GLFWWindow(const GLFWWindow&) = delete;
        GLFWWindow &operator=(const GLFWWindow&) = delete;

        [[nodiscard]] GLFWwindow * GetGLFWWindow() const { return window; }
        [[nodiscard]] const glm::vec2 GetMousePosition() const override;
        [[nodiscard]] int GetKey(int key) const override;
        [[nodiscard]] int GetMouseButton(int key) const override;
        [[nodiscard]] bool ShouldClose() const override;

        void SwapBuffers() const override;
        void PollEvents() override;

#if defined(HC_EDITOR)
        void ImGUIFrameBegin() override;
        void ImGUIRender()  override;
#endif


    private:
#if defined(HC_EDITOR)
        void InitializeIMGUI()  override;
        void AttachIMGUIWindow(std::shared_ptr<AttachableIMGUIWindow> imguiWindow) override;
        void DetachIMGUIWindow(std::shared_ptr<AttachableIMGUIWindow> imguiWindow) override;
#endif
        /* GLFW Callbacks */
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void mouse_callback(GLFWwindow *window, int button, int action, int mods);
        static void mouse_position_callback(GLFWwindow *window, double xpos, double ypos);

        void InitializeGLFW(int width, int height, const std::string &windowName);
        void SetCallbacks();



    private:
        GLFWwindow * window;
#if defined(HC_EDITOR)
        std::unordered_set<std::shared_ptr<AttachableIMGUIWindow>> imguiWindows;
#endif
    private:

    };

} // HC
