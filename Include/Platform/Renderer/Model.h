#pragma once

#include "Renderer/Mesh.h"
#include <vector>
#include <memory>
namespace HC {
    class Model {
    public:
        Model();

        void Draw(std::shared_ptr<ShaderProgram> shader);

        void AddMesh(std::unique_ptr<Mesh> mesh) {
            meshes.push_back(std::move(mesh));
        }

    private:
        std::vector<std::unique_ptr<Mesh>> meshes;
    };
}