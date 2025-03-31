#pragma once

#include <string>
#include <vector>
#include "Reflection/HCObject.h"
#include "Reflection/ReflexionMacro.h"
#include "FileSystem/File.h"

#define CONCAT(a, b) CONCAT_INNER(a, b)
#define CONCAT_INNER(a, b) a##b

#define ADD_ASSET_EXTENSION(extension) \
static inline bool CONCAT(registered_, __COUNTER__) = (RegisterExtension(#extension, StaticClass()), true);


namespace HC {

    class Asset : public HCObject {
    public:
        Asset() {}
        virtual ~Asset() = default;

        virtual void Load() {
            isAssetLoaded = true;
        };

        [[nodiscard]] bool IsAssetLoaded() {
            return isAssetLoaded;
        }

        void AssignFile(const FileSystem::File& file) {
            assetFile = std::move(std::make_unique<FileSystem::File>(file));
        }


        START_REFLECTION(Asset)
        STOP_REFLECTION()


        std::string GetAssetName() {
            return assetFile->GetName();
        }

        bool IsFileCompatible(const FileSystem::File& file) {
            if(assetsExtensions.find(file.GetExtension()) != assetsExtensions.end()) {
                return assetsExtensions[file.GetExtension()] == StaticClass();
            }
            return false;
        }

        static HCClass* GetAssetClassFromExtension(const std::string& extension) {
            if(assetsExtensions.find(extension) != assetsExtensions.end()) {
                return assetsExtensions[extension];
            }
            return nullptr;
        }

    protected:
        static void RegisterExtension(const char* extension, HCClass* assetClass) {
            assetsExtensions.insert({extension, assetClass});
        }

        FileSystem::File& GetAssetFile() {
            return *assetFile;
        }


    private:
        static inline std::unordered_map<std::string, HCClass*> assetsExtensions;
        std::unique_ptr<FileSystem::File> assetFile;
        bool isAssetLoaded = false;


    };
}