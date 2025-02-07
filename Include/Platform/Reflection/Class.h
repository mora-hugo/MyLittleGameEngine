#pragma once
#include "Reflection/IReflectable.h"

namespace HC {
    class Class : public IReflectable {
    private:
        static constexpr const char* ClassName = nullptr;

    public:
        Class(const char* name) : name(name) { }

        const char* GetClassName() const {
            return name;
        }

        //get type

    private:
        const char* name;
    };
}