#pragma once
#include <any>
#include <utility>

namespace HC {

    struct Property {
        Property(const char* propertyName, std::any propertyValue) : propertyName(propertyName), propertyValue(std::move(propertyValue)) {}

        const char* propertyName;
        std::any propertyValue; // Properties are registered as ptr

        template<typename T>
        const T* GetConstPropertyPtr() {
            return std::any_cast<T*>(propertyValue);
        }
        template<typename T>
        T* GetPropertyPtr() {
            return std::any_cast<T*>(propertyValue);
        }

        template<typename T>
        bool Is() const {
            return propertyValue.type() == typeid(T*);
        }


    };
}