//
// Created by hugom on 31/03/2025.
//

#include "AssetManager/StaticMeshAsset.h"

#include <Logger.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

HC::StaticMeshAsset::~StaticMeshAsset() {
}

void HC::StaticMeshAsset::Load() {
    Asset::Load();
    Assimp::Importer importer;
    auto fileData = GetAssetFile().ReadBytes();
    const aiScene *scene = importer.ReadFileFromMemory(fileData.data(), fileData.size(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        Logger::LogError("ERROR::ASSIMP:: %s" ,importer.GetErrorString());
        return;
    }


}
