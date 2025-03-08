#pragma once


#include "Viewport/Windows/EditorWindow.h"
#include "Event/Event.h"
#include "imgui.h"
#include "imgui_internal.h"

namespace HC::Editor::Window {
    class DockableEditorWindow : public EditorWindow {
    public:
        [[nodiscard]] virtual bool IsOpenAtStart() const { return true; }
        DockableEditorWindow();
        ~DockableEditorWindow() override = default;

        virtual void Initialize(ImGuiID dockId);


        ImGuiDir_ GetDockDirection() const {
            return dock_direction;
        }

        float GetDockSize() const {
            return dock_size;
        }



        Event<> OnWindowClosed;


    protected:
        void SetDockDirection(ImGuiDir_ direction) {
            dock_direction = direction;
        }

        void SetDockSize(float size) {
            dock_size = size;
        }

        void BeginWindow(bool canBeClosed = true);

    private:
        ImGuiID dockId = 0;
        ImGuiDir_ dock_direction = ImGuiDir_None;
        float dock_size = 0.2f;

        START_REFLECTION(DockableEditorWindow, EditorWindow)
        STOP_REFLECTION()
    };
}