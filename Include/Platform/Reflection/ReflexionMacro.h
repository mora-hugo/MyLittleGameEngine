#pragma once

#include "Reflection/Property.h"
#include <map>
#define START_REFLECTION() \
    private: \
    std::map<const char*, Property> members {

#define ADD_MEMBER_PROPERTY(variable) \
    {#variable, Property(#variable, &(variable))},

#define STOP_REFLECTION() \
    };                    \
    [[nodiscard]] const std::map<const char*, Property>& GetMembers() const override { return members; }

