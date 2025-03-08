#pragma once

#include <cstddef>
#include "Reflection/HCClass.h"
#include "AssetManager/AssetManager.h"
#include <type_traits>
namespace HC {
    class AssetOf : public HCObject{

    public:
        AssetOf() : assetUUID(0), assetHCClass(nullptr) {}
        AssetOf(HCClass* hcClass) : assetUUID(0), assetHCClass(hcClass) {}
    public:
        size_t assetUUID;
        HCClass* assetHCClass;
        /* If the asset is dirty, it means that the asset has been modified and needs to be reloaded */
        bool isDirty = false;

        void OnDeserialized() override {
            isDirty = true;
        }
        bool IsDirty() {
            return isDirty;
        }

        void SetClean() {
            isDirty = false;
        }

        template<typename T>
        std::shared_ptr<T> GetAsset() {
            if (!IsAssetLoaded()) return nullptr;

            return AssetManager::GetInstance()->GetLoadedAsset<T>(assetUUID);
        }

        std::shared_ptr<Asset> GetAsset() {
            if (!IsAssetLoaded()) return nullptr;

            return AssetManager::GetInstance()->GetLoadedAsset(assetUUID);
        }

        bool IsAssetLoaded() {
            return assetUUID != 0 && AssetManager::GetInstance()->IsAssetLoaded(assetUUID);
        }

        START_REFLECTION(AssetOf)
            ADD_MEMBER_PROPERTY(assetUUID)
            ADD_MEMBER_PROPERTY(assetHCClass)
        STOP_REFLECTION()

    };
}