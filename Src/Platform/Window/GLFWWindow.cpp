
#include "Window/GLFWWindow.h"
#include <stdexcept>
#include <iostream>
#include <glad/glad.h>

/* IMGUI */
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace HC {

    GLFWWindow::GLFWWindow(int width, int height, const std::string &windowName) : BaseWindow(width, height, windowName) {
        InitializeGLFW(width, height, windowName);
        SetCallbacks();
    }

    GLFWWindow::~GLFWWindow() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void GLFWWindow::InitializeGLFW(int width, int height, const std::string& windowName) {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
        if (window == nullptr) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }
        glfwMakeContextCurrent(window);
        if (!gladLoadGL()) {
            std::cerr << "OpenGL ERROR: Impossible to load opengl !" << std::endl;
        }

        //glfwSwapInterval(1);
        glfwSetWindowUserPointer(window, this);

    }

    void GLFWWindow::SetCallbacks() {
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetKeyCallback(window, key_callback);
        glfwSetMouseButtonCallback(window, mouse_callback);
        glfwSetCursorPosCallback(window, mouse_position_callback);
    }

    void GLFWWindow::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        auto *windowRef = reinterpret_cast<GLFWWindow *>(glfwGetWindowUserPointer(window));
        if(!windowRef) return;

        windowRef->SetWindowSize({width, height});
        windowRef->OnWindowResize.Invoke(windowRef->GetWindowSize());

        glViewport(0, 0, width, height);
    }
#if defined(HC_EDITOR)
    void GLFWWindow::InitializeIMGUI() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    void GLFWWindow::ImGUIFrameBegin() {
        if(!ImGui::GetCurrentContext()) {
            InitializeIMGUI();
        }
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void GLFWWindow::ImGUIRender() {

            for(auto& imguiWindow : imguiWindows) {
                imguiWindow->Draw();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    }
#endif

    void GLFWWindow::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        auto *vp_window = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        if(!vp_window) return;
        vp_window->OnWindowHandledKeyboardInput.Invoke(KeyboardInput(key, scancode, action));
    }

    void GLFWWindow::mouse_callback(GLFWwindow *window, int button, int action, int mods) {
        auto *vp_window = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        if(!vp_window) return;

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        glm::vec2 mousePos {mouseX, mouseY};
        vp_window->OnWindowHandledMouseInput.Invoke(MouseInput(button, action, mousePos));
    }

    void GLFWWindow::mouse_position_callback(GLFWwindow *window, double xpos, double ypos) {
        auto *vp_window = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        if(!vp_window) return;

        glm::vec2 mousePos {xpos, ypos};
        vp_window->OnWindowHandledMouseInput.Invoke(MouseInput(NO_KEY, MouseInput::MOUSE_MOVE_INT, mousePos));
    }

    const glm::vec2 GLFWWindow::GetMousePosition() const {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return {xpos, ypos};
    }

    int GLFWWindow::GetKey(int key) const {
        return glfwGetKey(window, key);
    }

    int GLFWWindow::GetMouseButton(int key) const {
        return glfwGetMouseButton(window, key);
    }

    bool GLFWWindow::ShouldClose() const {
        return glfwWindowShouldClose(window);
    }

    void GLFWWindow::SwapBuffers() const {
        glfwSwapBuffers(window);
    }
#if defined(HC_EDITOR)
    void GLFWWindow::AttachIMGUIWindow(std::shared_ptr<AttachableIMGUIWindow> imguiWindow) {
        imguiWindows.insert(imguiWindow);
    }

    void GLFWWindow::DetachIMGUIWindow(std::shared_ptr<AttachableIMGUIWindow> imguiWindow) {
        imguiWindows.erase(imguiWindow);
    }

    void GLFWWindow::PollEvents() {
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED)) {
            glfwWaitEvents();
        } else {
            glfwPollEvents();
        }
    }


#endif
} // HC