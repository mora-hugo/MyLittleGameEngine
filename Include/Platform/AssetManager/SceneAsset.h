#pragma once

#include "AssetManager/Asset.h"
#include "FileSystem/File.h"

namespace HC {
    class SceneAsset : public Asset {
    public:
        SceneAsset() = default;
        ~SceneAsset() = default;

        void Load() override {
            sceneJson = nlohmann::json::parse(GetAssetFile().ReadBytes());
            Asset::Load();
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