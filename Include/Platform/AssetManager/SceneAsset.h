#pragma once

#include "AssetManager/Asset.h"
#include "FileSystem/File.h"

namespace HC {
    class SceneAsset : public Asset {
    public:
        SceneAsset() = default;
        ~SceneAsset() = default;

        void Load(const FileSystem::File &file) override {
            Asset::Load(file);
            sceneJson = nlohmann::json::parse(file.ReadBytes());
        }

        std::unique_ptr<Entity> GetRootEntity() {
            auto entity = std::make_unique<Entity>();
            entity->FromJson(sceneJson);
            return entity;
        }
        nlohmann::json sceneJson;


        START_REFLECTION(SceneAsset, Asset)
        STOP_REFLECTION()

        ADD_ASSET_EXTENSION(hcscene)
    };
}