#include "AssetManager/StaticMeshAsset.h"
#include <Logger.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Renderer/Vertex.h>

HC::StaticMeshAsset::~StaticMeshAsset() = default;

void HC::StaticMeshAsset::Load() {
    Asset::Load();

    Assimp::Importer importer;
    auto fileData = GetAssetFile().ReadBytes();

    // Read file with appropriate post-processing flags
    const aiScene* scene = importer.ReadFile(GetAssetFile().path,
        aiProcess_Triangulate |
        aiProcess_GenNormals |
        aiProcess_FlipUVs |
        aiProcess_JoinIdenticalVertices

    );

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        Logger::LogError("ERROR::ASSIMP:: {}", importer.GetErrorString());
        return;
    }

    // Clear any existing data
    m_Vertices.clear();
    m_Indices.clear();

    // Process all meshes in the scene
    for(unsigned int i = 0; i < scene->mNumMeshes; i++) {
        const aiMesh* mesh = scene->mMeshes[i];
        const unsigned int vertexOffset = m_Vertices.size();

        // Process vertices
        for(unsigned int j = 0; j < mesh->mNumVertices; j++) {
            Vertex vertex;

            // Position
            vertex.position = {
                mesh->mVertices[j].x,
                mesh->mVertices[j].y,
                mesh->mVertices[j].z
            };

            // Normals
            if(mesh->HasNormals()) {
                vertex.normal = {
                    mesh->mNormals[j].x,
                    mesh->mNormals[j].y,
                    mesh->mNormals[j].z
                };
            }

            // Texture Coordinates (first set only)
            if(mesh->mTextureCoords[0]) {
                vertex.texCoord = {
                    mesh->mTextureCoords[0][j].x,
                    mesh->mTextureCoords[0][j].y
                };
            } else {
                vertex.texCoord = {0.0f, 0.0f};
            }

            m_Vertices.push_back(vertex);
        }

        // Process indices with correct offset
        for(unsigned int j = 0; j < mesh->mNumFaces; j++) {
            const aiFace& face = mesh->mFaces[j];
            for(unsigned int k = 0; k < face.mNumIndices; k++) {
                m_Indices.push_back(vertexOffset + face.mIndices[k]);
            }
        }
    }
}

std::vector<HC::Vertex> HC::StaticMeshAsset::GetVertices() {
    return m_Vertices;
}

std::vector<unsigned int> HC::StaticMeshAsset::GetIndices() {
    return m_Indices;
}
