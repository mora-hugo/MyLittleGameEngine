#pragma once

#include "Window/AttachableIMGUIWindow.h"
#include "glad/glad.h"
#include "imgui.h"
#include "glm/vec2.hpp"
#include "Viewport/Windows/DockableEditorWindow.h"

namespace HC {


    class DefaultAttachableIMGUIWindow: public AttachableIMGUIWindow {
    public:
         explicit DefaultAttachableIMGUIWindow(GLuint renderTexture);
         ~DefaultAttachableIMGUIWindow() = default;
    public:

        void Draw() override;
        template<typename T>
        void AttachWindow() {
            auto window = std::make_unique<T>();
            window->Initialize(0);
            window->OnWindowClosed.AddListener(this, [this, window = window.get()]() {
                windows.erase(std::remove_if(windows.begin(), windows.end(), [window](const std::unique_ptr<Editor::Window::DockableEditorWindow>& windowPtr) {
                    return windowPtr.get() == window;
                }), windows.end());
            });
            windows.push_back(std::move(window));
        }


        Editor::Window::DockableEditorWindow& AttachWindow(HCClass* windowClass) {
            auto window= windowClass->CreateUniqueInstance<Editor::Window::DockableEditorWindow>();
            window->Initialize(0);
            window->OnWindowClosed.AddListener(this, [this, window = window.get()]() {
                windows.erase(std::remove_if(windows.begin(), windows.end(), [window](const std::unique_ptr<Editor::Window::DockableEditorWindow>& windowPtr) {
                    return windowPtr.get() == window;
                }), windows.end());
            });
            auto rawPtr = window.get();
            windows.push_back(std::move(window));
            return *rawPtr;
        }

        void DetachWindow(Editor::Window::DockableEditorWindow* window) {
            windows.erase(std::remove_if(windows.begin(), windows.end(), [window](const std::unique_ptr<Editor::Window::DockableEditorWindow>& windowPtr) {
                return windowPtr.get() == window;
            }), windows.end());
        }


    private:
        void SaveCurrentSceneToJson();
        void LoadSceneFromJson();
    private:
        glm::vec2 lastViewportSize;
        GLuint renderTextureId;

        std::unordered_map<ImGuiDir_, ImGuiID> dockIds;
        std::vector<std::unique_ptr<Editor::Window::DockableEditorWindow>> windows;
        void OnWindowResize(const glm::vec2& size);
    };
}