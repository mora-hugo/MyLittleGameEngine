#pragma once

#include "IReflectable.h"
#include "Reflection/Property.h"
#include "nlohmann/json.hpp"
namespace HC {
class HCObject: public IReflectable {
public:
        virtual class HCClass * Class() = 0;
        [[nodiscard]] virtual nlohmann::json ToJson() const {
            nlohmann::json j;
            for (const auto& member : GetMembers()) { /* assume member.first is the property name */
                j[member.first] = member.second.ToJson();
            }
            return j;
        }

        /* Deserialize object from JSON by updating its properties */
        virtual void FromJson(const nlohmann::json& j) {
            for (auto& member : GetMutableMembers()) {
                if (j.contains(member.first))
                    member.second.FromJson(j.at(member.first));
            }
        }
    };
}