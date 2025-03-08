#pragma once

#include "glm/vec2.hpp"
#include "Reflection/HCClass.h"
#include <memory>
#include <AttachableWindows/DefaultAttachableIMGUIWindows.h>
#include <Event/Event.h>

namespace HC {
    class DefaultAttachableIMGUIWindow;

    class Viewport {
    public:

       static glm::vec2 GetGameViewportSize() { return gameViewportSize; }
       static glm::vec2 GetEditorViewportSize() { return { 0, 0 }; }

       static void SetGameViewportSize(const glm::vec2& size) {
           gameViewportSize = size;
           OnViewportResize.Invoke(size);
       }

       static void SetDefaultAttachableIMGUIWindow(std::shared_ptr<DefaultAttachableIMGUIWindow> window) {
           defaultAttachableIMGUIWindow = window;
       }

       template<typename T>
       static void AttachWindow() {
          if(defaultAttachableIMGUIWindow) {
            defaultAttachableIMGUIWindow->AttachWindow<T>();
          }
       }

        static Editor::Window::DockableEditorWindow& AttachWindow(HCClass* windowClass) {
            if(defaultAttachableIMGUIWindow) {
                return defaultAttachableIMGUIWindow->AttachWindow(windowClass);
            }
        }

        static void DetachWindow(Editor::Window::DockableEditorWindow* window) {
              defaultAttachableIMGUIWindow->DetachWindow(window);
        }


       static inline std::shared_ptr<DefaultAttachableIMGUIWindow> defaultAttachableIMGUIWindow;
    public:
       static inline Event<glm::vec2> OnViewportResize;
    private:

    static inline glm::vec2 gameViewportSize = { 0, 0 };
    };
}
