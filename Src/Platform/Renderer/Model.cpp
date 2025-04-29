#include "Renderer/Model.h"
#include "Logger.h"
HC::Model::Model() {
}


void HC::Model::Draw(std::shared_ptr<ShaderProgram> shader) {
    if (meshes.empty()) {
        Logger::LogWarning("No meshes to draw");
        return;
    }

    for (int i = 0; i < meshes.size(); i++) {
        meshes[i]->Draw(shader);
    }
}

