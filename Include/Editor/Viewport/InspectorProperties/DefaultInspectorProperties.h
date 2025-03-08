#pragma once

#include "Viewport/InspectorProperties/InspectorProperty.h"
#include "AssetManager/AssetOf.h"
#include "AssetManager/AssetManager.h"
#include "imgui.h"
#include <glm/gtc/type_ptr.hpp>
namespace HC::Editor {
    class IntInspectorProperty : public InspectorProperty{
    public:
        IntInspectorProperty() : InspectorProperty() {

        }
        ~IntInspectorProperty() = default;

        void Draw() override {
            int* value = property->GetPropertyPtr<int>();
            if (value) {
                if(ImGui::DragInt(property->propertyName, value)) {
                    InternalOnValueChanged.Invoke();
                }
            }
        }

        START_REFLECTION(IntInspectorProperty, InspectorProperty)
        STOP_REFLECTION()

        INSPECTOR_PROPERTY_OF(int, IntInspectorProperty)

    };

    class FloatInspectorProperty : public InspectorProperty {
    public:
        FloatInspectorProperty() : InspectorProperty() {
        }
        ~FloatInspectorProperty() = default;

        void Draw() override {
            float* value = property->GetPropertyPtr<float>();
            if (value) {
                if (ImGui::DragFloat(property->propertyName, value, 0.1f)) {
                    InternalOnValueChanged.Invoke();
                }
            }
        }

        START_REFLECTION(FloatInspectorProperty, InspectorProperty)
        STOP_REFLECTION()

        INSPECTOR_PROPERTY_OF(float, FloatInspectorProperty)

    };

    class Vec2InspectorProperty : public InspectorProperty {
    public:
        Vec2InspectorProperty() : InspectorProperty() {
        }
        ~Vec2InspectorProperty() = default;

        void Draw() override {
            glm::vec2* value = property->GetPropertyPtr<glm::vec2>();
            if (value) {
                if (ImGui::DragFloat2(property->propertyName, glm::value_ptr(*value), 0.1f)) {
                    InternalOnValueChanged.Invoke();
                }
            }
        }

        START_REFLECTION(Vec2InspectorProperty, InspectorProperty)
        STOP_REFLECTION()

        INSPECTOR_PROPERTY_OF(glm::vec2, Vec2InspectorProperty)

    };

    class Vec3InspectorProperty : public InspectorProperty {

    public:
        Vec3InspectorProperty() : InspectorProperty() {

        }
        ~Vec3InspectorProperty() = default;
        void Draw() override {
            glm::vec3* value = property->GetPropertyPtr<glm::vec3>();
            if (value) {
                if (ImGui::DragFloat3(property->propertyName, glm::value_ptr(*value), 0.1f)) {
                    InternalOnValueChanged.Invoke();
                }
            }
        }

        START_REFLECTION(Vec3InspectorProperty, InspectorProperty)
        STOP_REFLECTION()

        INSPECTOR_PROPERTY_OF(glm::vec3, Vec3InspectorProperty)

    };

    class AssetOfProperty : public InspectorProperty {
    public:
        AssetOfProperty() = default;
        ~AssetOfProperty() = default;

        void Draw() override {
            HCObject *obj = property->GetPropertyPtr<HCObject>();
            AssetOf *value = dynamic_cast<AssetOf *>(obj);
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

                    for (int i = 0; i < assets.size(); i++) {
                        auto assetUUID = assets[i];
                        auto asset = AssetManager::GetInstance()->GetLoadedAsset(assetUUID);
                        if (asset) {
                            ImGui::PushID(i);
                            if (ImGui::Selectable(asset->Class()->GetClassName())) {
                                value->assetUUID = assetUUID;
                                value->isDirty = true;
                                InternalOnValueChanged.Invoke();
                            }
                            ImGui::PopID();
                        }
                    }
                }
            }
        }

        START_REFLECTION(AssetOfProperty, InspectorProperty)
        STOP_REFLECTION()

        INSPECTOR_PROPERTY_OF(AssetOf, AssetOfProperty)

    };
}