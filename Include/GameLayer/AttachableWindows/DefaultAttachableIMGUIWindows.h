#pragma once

#include "Window/AttachableIMGUIWindow.h"
#include <string>

namespace HC {
    class DefaultAttachableIMGUIWindow: public AttachableIMGUIWindow {
    public:
         explicit DefaultAttachableIMGUIWindow(const char* name);
    public:
        void Draw() override;

    private:
        std::string name;

    };
}