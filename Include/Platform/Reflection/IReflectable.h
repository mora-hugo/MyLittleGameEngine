#pragma once

#include <map>
#include "Property.h"

namespace HC {
    class IReflectable {
    public:
        virtual const std::map<const char*, Property>& GetMembers() const = 0;

        Property GetProperty(const char* propertyName) const {
            return GetMembers().at(propertyName);
        }

    };
}