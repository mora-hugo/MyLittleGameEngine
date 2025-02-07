#pragma once

#include "Interface.h"
#include "Window/AttachableIMGUIWindow.h"
#include <memory>
class IImGUIWindow : public Interface {
public:
    ~IImGUIWindow() override = default;
    virtual void ImGUIFrameBegin() = 0;
    virtual void ImGUIRender() = 0;
    virtual void AttachIMGUIWindow(std::shared_ptr<AttachableIMGUIWindow> imguiWindow) = 0;
    virtual void DetachIMGUIWindow(std::shared_ptr<AttachableIMGUIWindow> imguiWindow) = 0;


protected:
    virtual void InitializeIMGUI() = 0;
};