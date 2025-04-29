#include "AssetManager/StaticMeshAsset.h"
#include <Logger.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <Renderer/Vertex.h>

HC::StaticMeshAsset::~StaticMeshAsset() = default;

void HC::StaticMeshAsset::Load() {
    Asset::Load();

    Assimp::Importer importer;
    scene = importer.ReadFile(
        GetAssetFile().path,
        aiProcess_Triangulate
        | aiProcess_GenSmoothNormals
        | aiProcess_FlipUVs
        | aiProcess_CalcTangentSpace
        | aiProcess_JoinIdenticalVertices
    );

    if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode) {
        Logger::LogError("ERROR::ASSIMP:: {}", importer.GetErrorString());
        return;
    }

    Logger::LogInfo("ASSIMP: '{}' loaded, meshes={}, materials={}",
                    GetAssetFile().path,
                    scene->mNumMeshes,
                    scene->mNumMaterials);

    model = std::make_unique<Model>();
    ProcessNode(scene->mRootNode, scene, glm::mat4(1.0f));
}

void HC::StaticMeshAsset::ProcessNode(aiNode* node, const aiScene* scene, const glm::mat4& parentTransform) {
    aiMatrix4x4 aiMat = node->mTransformation;
    glm::mat4 nodeMat = glm::transpose(glm::make_mat4(&aiMat.a1));
    glm::mat4 globalTransform = parentTransform * nodeMat;

    Logger::LogInfo("Processing node '{}' meshes={} children={}",
                    node->mName.C_Str(),
                    node->mNumMeshes,
                    node->mNumChildren);

    for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        auto meshPtr = ProcessMesh(mesh, scene, globalTransform);
        model->AddMesh(std::move(meshPtr));
    }

    for (unsigned int i = 0; i < node->mNumChildren; ++i) {
        ProcessNode(node->mChildren[i], scene, globalTransform);
    }
}

std::unique_ptr<HC::Mesh> HC::StaticMeshAsset::ProcessMesh(
    const aiMesh* mesh,
    const aiScene* /*scene*/,
    const glm::mat4& transform
) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    const char* name = mesh->mName.C_Str()[0] ? mesh->mName.C_Str() : "<no name>";
    Logger::LogInfo("Processing mesh '{}' vertices={} faces={}",
                    name,
                    mesh->mNumVertices,
                    mesh->mNumFaces);

    /* calculer la matrice normale = transpose(inverse(mat3(transform))) */
    glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(transform));

    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vtx;
        // position
        glm::vec4 p(mesh->mVertices[i].x,
                    mesh->mVertices[i].y,
                    mesh->mVertices[i].z,
                    1.0f);
        p = transform * p;
        vtx.position = glm::vec3(p);

        // normale
        if (mesh->HasNormals()) {
            glm::vec3 n(mesh->mNormals[i].x,
                        mesh->mNormals[i].y,
                        mesh->mNormals[i].z);
            vtx.normal = normalMatrix * n;
        }

        // UV
        if (mesh->HasTextureCoords(0)) {
            vtx.texCoord = {
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
            };
        } else {
            vtx.texCoord = glm::vec2(0.0f);
        }

        vertices.push_back(vtx);
    }

    // indices
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        const aiFace& face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }


    return std::make_unique<Mesh>(name, vertices, indices);
}

void HC::StaticMeshAsset::Draw(std::shared_ptr<ShaderProgram> shader) {
    if (!model) {
        Logger::LogError("StaticMeshAsset::Draw() called but model is null");
        return;
    }
    model->Draw(shader);
}
