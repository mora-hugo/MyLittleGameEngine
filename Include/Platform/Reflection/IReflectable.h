#pragma once

#include <map>
#include "Property.h"

namespace HC {
    class IReflectable {
    public:
        virtual std::map<const char*, Property>& GetMembers() = 0;

        Property GetProperty(const char* propertyName) {
            return GetMembers().at(propertyName);
        }

    };
}