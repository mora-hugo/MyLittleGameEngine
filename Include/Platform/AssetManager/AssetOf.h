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

        std::shared_ptr<Asset> cachedAsset;

        void OnDeserialized() override {
            isDirty = true;
        }

        bool IsDirty() {
            return isDirty;
        }

        void SetClean() {
            SetIsDirty(false);
        }

        void SetIsDirty(bool isDirty) {
            if (isDirty)
                cachedAsset = nullptr;
            this->isDirty = isDirty;

        }

        template<typename T>
        std::shared_ptr<T> GetAsset() {
            if (!IsAssetReferenced()) return nullptr;

            auto asset = AssetManager::GetInstance()->GetAsset<T>(assetUUID);
            cachedAsset = asset;
            return asset;
        }

        std::shared_ptr<Asset> GetAsset() {
            if (!IsAssetReferenced()) return nullptr;

            auto asset = AssetManager::GetInstance()->GetAsset(assetUUID);
            cachedAsset = asset;

            return asset;
        }

        void LoadAsset() {
            cachedAsset = AssetManager::GetInstance()->GetAsset(assetUUID);
        }

        bool IsAssetReferenced() {
            return assetUUID != 0;
        }
        bool IsAssetLoaded() {
            return IsAssetReferenced() && (cachedAsset || AssetManager::GetInstance()->IsAssetLoaded(assetUUID));
        }

    private:
        /* If the asset is dirty, it means that the asset has been modified and needs to be reloaded */
        bool isDirty = false;
        START_REFLECTION(AssetOf)
            ADD_MEMBER_PROPERTY(assetUUID)
            ADD_MEMBER_PROPERTY(assetHCClass)
        STOP_REFLECTION()

    };
}