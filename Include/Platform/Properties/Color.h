#pragma once
#include <Reflection/HCObject.h>
#include <Reflection/ReflexionMacro.h>

namespace HC {
    class Color : public HCObject {
    public:
        Color() : colorVec(1.0f, 1.0f, 1.0f) {}
        ~Color() override = default;
        glm::vec3 colorVec;

        START_REFLECTION(Color)
            ADD_MEMBER_PROPERTY(colorVec)
        STOP_REFLECTION()
    };
}
