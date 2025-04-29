#pragma once
#include "Asset.h"
#include "assimp/scene.h"
#include "Renderer/Model.h"
#include <glm/glm.hpp>

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
        ~StaticMeshAsset() override;

        void Load() override;
        void Draw(std::shared_ptr<ShaderProgram> shader);

    protected:
        std::unique_ptr<Model> model;

    private:

        const aiScene* scene;
        void ProcessNode(aiNode* node, const aiScene* scene, const glm::mat4& parentTransform);
        std::unique_ptr<Mesh> ProcessMesh(const aiMesh* mesh, const aiScene* scene, const glm::mat4& transform);
        START_REFLECTION(StaticMeshAsset, Asset)
        STOP_REFLECTION()

        ADD_ASSET_EXTENSION(obj)
        ADD_ASSET_EXTENSION(fbx)
    };
}
