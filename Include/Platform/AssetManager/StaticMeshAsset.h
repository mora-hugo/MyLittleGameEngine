#pragma once
#include "Asset.h"
#include "assimp/scene.h"

namespace HC {
    struct Vertex;
    struct StaticMeshData {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
    };
}

namespace HC {
    class StaticMeshAsset : public Asset {
    public:
        StaticMeshAsset() = default;
        ~StaticMeshAsset();
        void Load() override;


    public:
        std::vector<unsigned int> GetIndices();
        std::vector<Vertex> GetVertices();

    private:

        START_REFLECTION(StaticMeshAsset, Asset)
        STOP_REFLECTION()

        ADD_ASSET_EXTENSION(obj)
        ADD_ASSET_EXTENSION(fbx)
    private:
        std::vector<Vertex> m_Vertices;
        std::vector<unsigned int> m_Indices;
        const aiScene *scene;
    };
}
