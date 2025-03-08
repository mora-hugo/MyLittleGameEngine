#pragma once

#include <map>
namespace HC {
    class Property;
    class IReflectable {
    public:
        [[nodiscard]] virtual const std::map<const char*, Property>& GetMembers() const = 0;
        virtual std::map<const char*, Property>& GetMutableMembers() = 0;

        Property GetProperty(const char* propertyName);

    };
}