#pragma once

#include <unordered_map>
#include <memory>
#include <string>

#include "Asset.h"
#include "FileSystem/File.h"
#include "Singleton.h"

namespace HC {
    class AssetManager : public Singleton<AssetManager> {
    public:


        std::shared_ptr<Asset> LoadAsset(const FileSystem::File& file) {

            size_t hash = hasher(file.path);
            if (assets.find(hash) != assets.end()) {
                return assets[hash];
            }


            auto assetClass = Asset::GetAssetClassFromExtension(file.GetExtension());
            if (!assetClass) {
                return nullptr;
            }

            auto asset = assetClass->CreateSharedInstance<Asset>();


            asset->Load(file);
            assets[hash] = asset;
            assetsByClass[asset->Class()].push_back(hash);

            return asset;
        }

        template<typename T>
        std::shared_ptr<T> LoadAsset(const FileSystem::File& file) {
            static_assert(std::is_base_of<Asset, T>::value, "T must inherit from Asset");

            size_t hash = hasher(file.path);
            if (assets.find(hash) != assets.end()) {
                return std::dynamic_pointer_cast<T>(assets[hash]);
            }

            auto asset = std::make_shared<T>();
            if(!asset->IsFileCompatible(file)) {
                return nullptr;
            }

            asset->Load(file);
            assets[hash] = asset;
            assetsByClass[T::StaticClass()].push_back(hash);

            return asset;
        }

        template<typename T>
        std::shared_ptr<T> GetLoadedAsset(size_t assetUUID) {
            static_assert(std::is_base_of<Asset, T>::value, "T must inherit from Asset");

            if (assets.find(assetUUID) != assets.end()) {
                return std::dynamic_pointer_cast<T>(assets[assetUUID]);
            }

            return nullptr;
        }

        std::shared_ptr<Asset> GetLoadedAsset(size_t assetUUID) {

            if (assets.find(assetUUID) != assets.end()) {
                return assets[assetUUID];
            }

            return nullptr;
        }

        std::vector<size_t> GetLoadedAssetsUUIDByClass(HCClass* hcClass) {
            if (assetsByClass.find(hcClass) != assetsByClass.end()) {
                return assetsByClass[hcClass];
            }

            return {};
        }

        bool IsAssetLoaded(size_t assetUUID) {
            return assets.find(assetUUID) != assets.end();
        }
    private:
        std::unordered_map<size_t, std::shared_ptr<Asset>> assets;

        std::unordered_map<HCClass*, std::vector<size_t>> assetsByClass;

        std::hash<std::string> hasher;
    };
}