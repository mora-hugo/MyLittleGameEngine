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
            try {
                std::string jsonString(bytes.begin(), bytes.end());
                nlohmann::json jsonData = nlohmann::json::parse(jsonString);
                sceneName = jsonData["scene_name"];
                auto entitiesData = jsonData["entities"];
                for (auto& entityData : entitiesData) {
                    auto entity = std::make_unique<Entity>(entityData["name"].get<std::string>().c_str());

                    entities.push_back(std::move(entity));
                }


            }
            catch (nlohmann::json::parse_error& e) {
                Assertion(false, "Failed to parse scene file: " + std::string(e.what()));
            }
            return true;
        }

        bool Save() override {
            nlohmann::json jsonData;
            //clear the json data
            jsonData.clear();
            jsonData["scene_name"] = sceneName;
            nlohmann::json entitiesData;
            for (auto& entity : entities) {
                nlohmann::json entityData;
                entityData["name"] = entity->GetName().c_str();
                entitiesData.push_back(entityData);
            }
            jsonData["entities"] = entitiesData;
            std::string jsonString = jsonData.dump();

            bytes = std::vector<uint8_t>(jsonString.begin(), jsonString.end());
            return FileResource::Save();
        }
        std::string sceneName;
        std::vector<std::unique_ptr<Entity>> entities;

    };


}