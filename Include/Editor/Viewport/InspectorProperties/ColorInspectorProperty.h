#pragma once

#include "Properties/Color.h"
#include "Viewport/InspectorProperties/InspectorProperty.h"

namespace HC::Editor{
    class ColorInspectorProperty : public InspectorProperty {
    public:
        ColorInspectorProperty() = default;
        ~ColorInspectorProperty() = default;

        void Draw() override {
            auto *obj = property->GetPropertyPtr<HCObject>();
            auto value = dynamic_cast<Color *>(obj);
            if (value) {
                ImGui::ColorEdit3("Color", glm::value_ptr(value->colorVec));
            }
        }

        START_REFLECTION(ColorInspectorProperty, InspectorProperty)
        STOP_REFLECTION()

        INSPECTOR_PROPERTY_OF(Color, ColorInspectorProperty)
    };
}


