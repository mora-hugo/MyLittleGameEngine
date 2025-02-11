#pragma once

#include <any>
#include <utility>
#include <vector>
#include <glm/glm.hpp>
#include <stdint.h>
#include <nlohmann/json.hpp>

namespace HC {

    struct Property {
        Property(const char *propertyName, std::any propertyValue) : propertyName(propertyName),
                                                                     propertyValue(std::move(propertyValue)) {}

        const char *propertyName;
        std::any propertyValue; // Properties are registered as ptr

        template<typename T>
        const T *GetConstPropertyPtr() const {
            return std::any_cast<T *>(propertyValue);
        }

        template<typename T>
        T *GetPropertyPtr() {
            return std::any_cast<T *>(propertyValue);
        }

        template<typename T>
        bool Is() const {
            return propertyValue.type() == typeid(T *);
        }

        [[nodiscard]] nlohmann::json ToJson() const {
            nlohmann::json j;
            j["propertyName"] = propertyName;
            if (propertyValue.type() == typeid(int *)) {
                int *value = std::any_cast<int *>(propertyValue);
                j["propertyValue"] = *value;
            } else if (propertyValue.type() == typeid(float *)) {
                float *value = std::any_cast<float *>(propertyValue);
                j["propertyValue"] = *value;
            } else if (propertyValue.type() == typeid(double *)) {
                double *value = std::any_cast<double *>(propertyValue);
                j["propertyValue"] = *value;
            } else if (propertyValue.type() == typeid(std::string *)) {
                std::string *value = std::any_cast<std::string *>(propertyValue);
                j["propertyValue"] = *value;
            } else if (propertyValue.type() == typeid(glm::vec2 *)) {
                glm::vec2 *value = std::any_cast<glm::vec2 *>(propertyValue);
                j["propertyValue"] = {value->x, value->y};
            } else if (propertyValue.type() == typeid(glm::vec3 *)) {
                glm::vec3 *value = std::any_cast<glm::vec3 *>(propertyValue);
                j["propertyValue"] = {value->x, value->y, value->z};
            } else if (propertyValue.type() == typeid(glm::vec4 *)) {
                glm::vec4 *value = std::any_cast<glm::vec4 *>(propertyValue);
                j["propertyValue"] = {value->x, value->y, value->z, value->w};
            } else {
                /* Fallback for unsupported types */
                j["propertyValue"] = nullptr;
            }
            return j;
        }

        void FromJson(const nlohmann::json &j) {
            if (propertyValue.type() == typeid(int *)) {
                int *value = std::any_cast<int *>(propertyValue);
                *value = j.at("propertyValue").get<int>();
            } else if (propertyValue.type() == typeid(float *)) {
                float *value = std::any_cast<float *>(propertyValue);
                *value = j.at("propertyValue").get<float>();
            } else if (propertyValue.type() == typeid(double *)) {
                double *value = std::any_cast<double *>(propertyValue);
                *value = j.at("propertyValue").get<double>();
            } else if (propertyValue.type() == typeid(std::string *)) {
                std::string *value = std::any_cast<std::string *>(propertyValue);
                *value = j.at("propertyValue").get<std::string>();
            } else if (propertyValue.type() == typeid(glm::vec2 *)) {
                glm::vec2 *value = std::any_cast<glm::vec2 *>(propertyValue);
                auto arr = j.at("propertyValue");
                value->x = arr[0].get<float>();
                value->y = arr[1].get<float>();
            } else if (propertyValue.type() == typeid(glm::vec3 *)) {
                glm::vec3 *value = std::any_cast<glm::vec3 *>(propertyValue);
                auto arr = j.at("propertyValue");
                value->x = arr[0].get<float>();
                value->y = arr[1].get<float>();
                value->z = arr[2].get<float>();
            } else if (propertyValue.type() == typeid(glm::vec4 *)) {
                glm::vec4 *value = std::any_cast<glm::vec4 *>(propertyValue);
                auto arr = j.at("propertyValue");
                value->x = arr[0].get<float>();
                value->y = arr[1].get<float>();
                value->z = arr[2].get<float>();
                value->w = arr[3].get<float>();
            } else {
                /* Fallback for unsupported types */
            }
        }


    };
}