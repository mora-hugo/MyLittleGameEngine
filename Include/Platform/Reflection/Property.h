#pragma once
#include <any>
#include <utility>
#include <vector>
#include <glm/glm.hpp>
#include <stdint.h>
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

        [[nodiscard]] std::vector<uint8_t> Serialized() const {
            /*
            if (propertyValue.type() == typeid(float*)) {
                return std::vector<uint8_t>(reinterpret_cast<uint8_t*>(std::any_cast<float*>(propertyValue)), reinterpret_cast<uint8_t*>(std::any_cast<float*>(propertyValue)) + sizeof(float));
            }
            else if (propertyValue.type() == typeid(int*)) {
                return std::vector<uint8_t>(reinterpret_cast<uint8_t*>(std::any_cast<int*>(propertyValue)), reinterpret_cast<uint8_t*>(std::any_cast<int*>(propertyValue)) + sizeof(int));
            }
            else if (propertyValue.type() == typeid(glm::vec2*)) {
                return std::vector<uint8_t>(reinterpret_cast<uint8_t*>(std::any_cast<glm::vec2*>(propertyValue)), reinterpret_cast<uint8_t*>(std::any_cast<glm::vec2*>(propertyValue)) + sizeof(glm::vec2));
            }
            else if (propertyValue.type() == typeid(glm::vec3*)) {
                return std::vector<uint8_t>(reinterpret_cast<uint8_t*>(std::any_cast<glm::vec3*>(propertyValue)), reinterpret_cast<uint8_t*>(std::any_cast<glm::vec3*>(propertyValue)) + sizeof(glm::vec3));
            }
            return {};
             */
        }

        void Deserialize(const std::vector<uint8_t>& data) {
            /*
            if (propertyValue.type() == typeid(float*)) {
                float* value = std::any_cast<float*>(propertyValue);
                *value = *reinterpret_cast<const float*>(data.data());
            }
            else if (propertyValue.type() == typeid(int*)) {
                int* value = std::any_cast<int*>(propertyValue);
                *value = *reinterpret_cast<const int*>(data.data());
            }
            else if (propertyValue.type() == typeid(glm::vec2*)) {
                glm::vec2* value = std::any_cast<glm::vec2*>(propertyValue);
                *value = *reinterpret_cast<const glm::vec2*>(data.data());
            }
            else if (propertyValue.type() == typeid(glm::vec3*)) {
                glm::vec3* value = std::any_cast<glm::vec3*>(propertyValue);
                *value = *reinterpret_cast<const glm::vec3*>(data.data());
            }
             */
        }





    };
}