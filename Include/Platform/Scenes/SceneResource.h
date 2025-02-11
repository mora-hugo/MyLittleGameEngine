#pragma once
#include "ResourceManager.h"
#include "nlohmann/json.hpp"
#include "Assertion.h"
#include "ECS/Entity.h"
namespace HC {

    class SceneResource : public FileResource {
    public:
        SceneResource(const std::string& path) : FileResource(path) {}
        bool Load() override {
            bool bSuccess = FileResource::Load();
            if (!bSuccess) {
                //return true to create a new scene
                return true;
            }

            nlohmann::json j = nlohmann::json::parse(bytes);

            rootEntity = std::make_unique<Entity>();
            rootEntity->FromJson(j);
            return true;
        }

        bool Save() override {
            bytes.clear();
            //json as bytes
            nlohmann::json jsonData;
            jsonData = rawRootEntity->ToJson();

            std::string jsonString = jsonData.dump();
            bytes = std::vector<uint8_t>(jsonString.begin(), jsonString.end());
            return FileResource::Save();
        }
        std::unique_ptr<Entity> rootEntity;
        Entity* rawRootEntity;

    };


}