#include "Reflection/Property.h"
#include "Reflection/HCClass.h"

nlohmann::json HC::Property::ToJson() const {
    nlohmann::json j;
    j["propertyName"] = propertyName;
    if (propertyValue.type() == typeid(size_t *)) {
        size_t *value = std::any_cast<size_t *>(propertyValue);
        j["propertyValue"] = *value;
    } else if (propertyValue.type() == typeid(int *)) {
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
    } else if (propertyValue.type() == typeid(HCClass **)) {
        HCClass **hcClass = std::any_cast<HCClass **>(propertyValue);
        j["propertyValue"] = (*hcClass)->GetClassName();
    } else if (propertyValue.type() == typeid(HCObject *)) {
        HCObject *obj = std::any_cast<HCObject *>(propertyValue);
        nlohmann::json objJson = nlohmann::json::object();
        for (const auto &member: obj->GetMembers()) {
            nlohmann::json memberJson = member.second.ToJson();
            objJson[memberJson["propertyName"].get<std::string>()] = memberJson["propertyValue"];
        }
        obj->OnSerialized();
        j["propertyValue"] = objJson;
    } else {
        j["propertyValue"] = nullptr;
    }
    return j;
}

void HC::Property::FromJson(const nlohmann::json &j) {
    if (propertyValue.type() == typeid(size_t *)) {
        size_t *value = std::any_cast<size_t *>(propertyValue);
        *value = j.at("propertyValue").get<size_t>();
    } else if (propertyValue.type() == typeid(int *)) {
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
    } else if (propertyValue.type() == typeid(HCClass **)) {
        HCClass **hcClass = std::any_cast<HCClass **>(propertyValue);
        *hcClass = HCClass::GetClassFromName(j.at("propertyValue").get<std::string>().c_str());
    } else if (propertyValue.type()  == typeid(HCObject *)) {
        HCObject *obj = std::any_cast<HCObject *>(propertyValue);
        const nlohmann::json &objJson = j.at("propertyValue");
        for (auto &member: obj->GetMutableMembers()) {
            std::string memberName = member.second.propertyName;
            if (objJson.contains(memberName)) {
                nlohmann::json memberJson;
                memberJson["propertyName"] = memberName;
                memberJson["propertyValue"] = objJson.at(memberName);

                member.second.FromJson(memberJson);
            }
        }
        obj->OnDeserialized();
    } else {


    }
}
