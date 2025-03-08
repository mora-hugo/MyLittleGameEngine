#pragma once

#include "IReflectable.h"
#include "nlohmann/json.hpp"
#include "Reflection/Property.h"
namespace HC {
class HCObject: public IReflectable {
public:
    //TODO
        virtual ~HCObject() = default;
        virtual class HCClass * Class() = 0;
        virtual nlohmann::json ToJson() const {
            nlohmann::json j;
            for (const auto& member : GetMembers()) { /* assume member.first is the property name */
                j[member.first] = member.second.ToJson();
            }
            return j;
        }

        virtual void FromJson(const nlohmann::json &j)  {
            for (auto& member : GetMutableMembers()) {
                if (j.contains(member.first))
                    member.second.FromJson(j.at(member.first));
            }
        }

        virtual void OnSerialized() {}
        virtual void OnDeserialized() {}

};
}