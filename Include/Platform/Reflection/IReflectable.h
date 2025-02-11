#pragma once

#include <map>
#include "Property.h"

namespace HC {
    class IReflectable {
    public:
        virtual const std::map<const char*, Property>& GetMembers() const = 0;
        virtual std::map<const char*, Property>& GetMutableMembers() = 0;

        Property GetProperty(const char* propertyName) {
            return GetMembers().at(propertyName);
        }

    };
}