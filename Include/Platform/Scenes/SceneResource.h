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
                for (const auto& entityData : jsonData["entities"]) {
                    auto entity = new Entity(entityData["name"].get<std::string>().c_str());

                    // 🔥 3. Charger les composants de chaque entité
                    for (auto& componentData : entityData["components"]) {
                        std::string componentType = componentData["type"];
                        HCClass* componentClass = HCClass::GetClassFromName(componentType.c_str());

                        if (!componentClass) {
                            Assertion(false, "Component type '" + componentType + "' not found!");
                            continue;
                        }

                        // 🔥 4. Ajouter le composant à l'entité
                        Component* component = entity->AddComponent(componentClass);

                        // 🔥 5. Récupérer les variables du composant
                        for (auto& member : component->GetMembers()) {
                            if (componentData["variables"].contains(member.first)) {
                                member.second.Deserialize(componentData["variables"][member.first]);
                            }
                        }
                    }

                    // 🔥 6. Ajouter l'entité à la liste

                    // WARN : Ptr will be saved as unique ptr after
                    entities.push_back(entity);
                }


            }
            catch (nlohmann::json::parse_error& e) {
                Assertion(false, "Failed to parse scene file: " + std::string(e.what()));
            }
            return true;
        }

        bool Save() override {
            bytes.clear();
            nlohmann::json jsonData;
            //clear the json data
            jsonData.clear();
            jsonData["scene_name"] = sceneName;
            nlohmann::json entitiesData;
            for (auto& entity : entities) {
                nlohmann::json entityData;
                entityData["name"] = entity->GetName().c_str();
                entity->ExecuteOnComponents<Component>([&](Component* component) {
                    nlohmann::json componentData;
                    componentData["type"] = component->Class()->GetClassName();

                    {
                        nlohmann::json componentVariables;
                        for (auto& member : component->GetMembers()) {
                            componentVariables[member.first] = member.second.Serialized();
                        }
                        componentData["variables"] = componentVariables;
                    }

                    entityData["components"].push_back(componentData);
                });
                entitiesData.push_back(entityData);
            }
            jsonData["entities"] = entitiesData;
            std::string jsonString = jsonData.dump();

            bytes = std::vector<uint8_t>(jsonString.begin(), jsonString.end());
            return FileResource::Save();
        }
        std::string sceneName;
        std::vector<Entity*> entities;

    };


}