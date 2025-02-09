#pragma once

#include "Viewport/InspectorProperties/InspectorProperty.h"
#include "imgui.h"
#include <glm/gtc/type_ptr.hpp>
namespace HC::Editor {
    class IntInspectorProperty : public InspectorProperty{
    public:
        IntInspectorProperty() : InspectorProperty() {

        }
        ~IntInspectorProperty() = default;

        void Draw() override {
            int* value = property.GetPropertyPtr<int>();
            if (value) {
                if(ImGui::DragInt(property.propertyName, value)) {
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
            float* value = property.GetPropertyPtr<float>();
            if (value) {
                if (ImGui::DragFloat(property.propertyName, value)) {
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
            glm::vec2* value = property.GetPropertyPtr<glm::vec2>();
            if (value) {
                if (ImGui::DragFloat2(property.propertyName, glm::value_ptr(*value))) {
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
            glm::vec3* value = property.GetPropertyPtr<glm::vec3>();
            if (value) {
                if (ImGui::DragFloat3(property.propertyName, glm::value_ptr(*value))) {
                    InternalOnValueChanged.Invoke();
                }
            }
        }

        START_REFLECTION(Vec3InspectorProperty, InspectorProperty)
        STOP_REFLECTION()

        INSPECTOR_PROPERTY_OF(glm::vec3, Vec3InspectorProperty)

    };
}