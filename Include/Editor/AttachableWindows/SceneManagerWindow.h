#pragma once

#include "Window/AttachableIMGUIWindow.h"
#include <string>
namespace HC {
    class SceneManagerWindow: public AttachableIMGUIWindow {
    public:
        SceneManagerWindow();
        ~SceneManagerWindow() = default;
    public:
        void Draw() override;


    };
}
