#pragma once

#include "Reflection/HCObject.h"
#include "Reflection/ReflexionMacro.h"
namespace HC::Editor::Window {
    class EditorWindow : public HCObject {
    public:
        EditorWindow() {}
        ~EditorWindow() = default;

    public:
        void SetWindowName(const char* name) { windowName = name; }

        const char* GetWindowName() const { return windowName; }
        virtual void Draw() = 0;
    private:
        const char* windowName;

        START_REFLECTION(EditorWindow)
        STOP_REFLECTION()
    };
}

