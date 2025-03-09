#pragma once

#include <Assertion.h>

#include "AssetManager/Asset.h"
#include "Renderer/Texture.h"

namespace HC {
    class TextureAsset : public Asset {
    public:
        void Load() override {
            Asset::Load();
            texture = std::make_unique<Texture>(GetAssetFile().ReadBytes());
        }

        [[nodiscard]] Texture& GetTexture() const {
            if (texture) {
                return *texture;
            }

            Assertion(false, "Texture is not loaded");
        }


        std::unique_ptr<Texture> texture;

        START_REFLECTION(TextureAsset, Asset)
        STOP_REFLECTION()

        ADD_ASSET_EXTENSION(jpg)
        ADD_ASSET_EXTENSION(png)
    };
}
