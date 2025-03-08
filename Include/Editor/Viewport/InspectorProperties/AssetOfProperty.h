#pragma once

#include "AssetManager/AssetOf.h"
#include "InspectorProperty.h"
#include "AssetManager/AssetManager.h"
#include "imgui.h"
#include "Viewport/InspectorProperties/InspectorProperty.h"

namespace HC::Editor {

    class AssetOfProperty : public InspectorProperty {
    public:
        AssetOfProperty() = default;
        ~AssetOfProperty() = default;

        void Draw() override {
            AssetOf *value = property->GetPropertyPtr<AssetOf>();
            if (value) {
                HCClass *hcClass = value->assetHCClass;
                auto selectedAsset = AssetManager::GetInstance()->GetLoadedAsset(value->assetUUID);
                if (selectedAsset) {
                    ImGui::Text("Current selected asset: %s", selectedAsset->Class()->GetClassName());
                } else {
                    ImGui::Text("No asset selected");
                }

                if (hcClass) {
                    auto assets = AssetManager::GetInstance()->GetLoadedAssetsUUIDByClass(hcClass);
                    for (auto assetUUID : assets) {
                        auto asset = AssetManager::GetInstance()->GetLoadedAsset(assetUUID);
                        if (asset) {
                            if (ImGui::Selectable(asset->Class()->GetClassName())) {
                                value->assetUUID = assetUUID;
                                InternalOnValueChanged.Invoke();
                            }
                        }
                    }
                }
            }
        }

        INSPECTOR_PROPERTY_OF(AssetOf, AssetOfProperty)
    };
}