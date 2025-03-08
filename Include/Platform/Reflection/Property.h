#pragma once

#include <any>
#include <utility>
#include <vector>
#include <glm/glm.hpp>
#include <stdint.h>
#include <nlohmann/json.hpp>
#include <typeindex>


namespace HC {
    class HCObject;
    struct Property {
        Property(const char *propertyName, std::any propertyValue, const std::type_info& type) : propertyName(propertyName),
                                                                     propertyValue(std::move(propertyValue)), realType(type) {}


        const char *propertyName;
        std::any propertyValue; // Properties are registered as ptr
        const std::type_info& realType;

        [[nodiscard]] std::type_index GetRealTypeIndex() const {
            return (realType);
        }

        //TODO : HCObject can't be include (circular dependancy between HCObject and Property)
        template<typename T>
        const T *GetConstPropertyPtr() const {
            if constexpr(std::is_base_of<HCObject, T>::value) {
                auto val = std::any_cast<HCObject *>(propertyValue);
                return dynamic_cast<T *>(val);
            }

            return std::any_cast<T *>(propertyValue);
        }

        template<typename T>
        T *GetPropertyPtr() {
            if constexpr(std::is_base_of<HCObject, T>::value) {
                auto val = std::any_cast<HCObject *>(propertyValue);
                return dynamic_cast<T *>(val);
            }

            return std::any_cast<T *>(propertyValue);
        }

        template<typename T>
        bool Is() const {
            return propertyValue.type() == typeid(T *);
        }

        [[nodiscard]] nlohmann::json ToJson() const;

        void FromJson(const nlohmann::json &j);


    };
}