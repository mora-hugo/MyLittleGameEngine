#pragma once

#include "Viewport/Windows/DockableEditorWindow.h"

#define ASSET_WINDOW_OF(type) \
    static inline bool registered = (AssetWindow::RegisterAssetWindow(type::StaticClass(), StaticClass()), true); \
    std::shared_ptr<type> GetAsset() { \
         if(!asset->IsAssetLoaded()) asset->Load();                          \
    return std::dynamic_pointer_cast<type>(asset); \
    } \

namespace HC {
    class Asset;
    namespace Editor::Window {
    class AssetWindow : public HC::Editor::Window::DockableEditorWindow {
        bool IsOpenAtStart() const override { return false; }
    public:
        void Initialize(ImGuiID dockId) override;

        void SetAsset(std::shared_ptr<Asset> asset);

        void Draw() override;


        static HC::HCClass* GetWindowClassFromAssetClass(HCClass* assetClass) {
            if (windowClasses.contains(assetClass)) {
                return windowClasses[assetClass];
            }

            return nullptr;
        }

        static void RegisterAssetWindow(HCClass* assetClass, HCClass* windowClass) {
            windowClasses[assetClass] = windowClass;
        }
    protected:
        std::shared_ptr<Asset> asset;
    private:
        // <HCClass*, HCClass*> : <asset class, window class>
        static inline std::unordered_map<HCClass*, HCClass*> windowClasses;
    };

    }
}