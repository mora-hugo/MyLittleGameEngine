#pragma once
#include "Asset.h"
#include "assimp/scene.h"
#include "Renderer/Model.h"

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

        void Draw(std::shared_ptr<ShaderProgram> shader);

    protected:
        std::unique_ptr<Model> model;

    private:
        void ProcessNode(aiNode* node, const aiScene* scene);
        std::unique_ptr<Mesh> ProcessMesh(const aiMesh* mesh, const aiScene* scene);
    private:

        START_REFLECTION(StaticMeshAsset, Asset)
        STOP_REFLECTION()

        ADD_ASSET_EXTENSION(obj)
        ADD_ASSET_EXTENSION(fbx)
    private:

        const aiScene *scene;
    };
}
