#pragma once
#include <AssetManager/AssetOf.h>
#include "InspectorProperty.h"

namespace HC::Editor {
    class AssetOfProperty : public InspectorProperty {
    public:
        AssetOfProperty() = default;
        ~AssetOfProperty() = default;

        void Draw() override {
            auto *obj = property->GetPropertyPtr<HCObject>();
            auto *value = dynamic_cast<AssetOf *>(obj);
            if (!value)
                return;

            HCClass *hcClass = value->assetHCClass;
            auto selectedAsset = AssetManager::GetInstance()->GetAsset(value->assetUUID);

            if (!selectedAsset) {
                ImGui::Text("No asset selected");
            }

            if (hcClass) {
                auto assets = AssetManager::GetInstance()->GetAssetsUUIDByClass(hcClass);

                std::string preview = selectedAsset ? selectedAsset->GetAssetName() : "Select an asset";

                ImGui::PushID(property->propertyName);


                if (ImGui::BeginCombo("Assets", preview.c_str())) {
                    for (size_t i = 0; i < assets.size(); i++) {
                        auto assetUUID = assets[i];
                        auto asset = AssetManager::GetInstance()->GetAsset(assetUUID);
                        if (asset) {
                            bool isSelected = (assetUUID == value->assetUUID);
                            if (ImGui::Selectable(asset->GetAssetName().c_str(), isSelected)) {
                                value->assetUUID = assetUUID;
                                value->SetIsDirty(true);
                                InternalOnValueChanged.Invoke();
                            }

                            if (isSelected) {
                                ImGui::SetItemDefaultFocus();
                            }
                        }
                    }
                    ImGui::EndCombo();
                }
                ImGui::PopID();
            }
        }

        START_REFLECTION(AssetOfProperty, InspectorProperty)
        STOP_REFLECTION()

        INSPECTOR_PROPERTY_OF(AssetOf, AssetOfProperty)
    };
}
