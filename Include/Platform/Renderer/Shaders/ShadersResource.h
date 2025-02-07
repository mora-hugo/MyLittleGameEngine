#pragma once

#include <glad/glad.h>
#include "ResourceManager.h"
#include "Shader.h"

namespace HC {
    class ShaderResource : public FileResource {
    public:
        ShaderResource(const std::string& filepath, GLenum shaderType) : FileResource(filepath), shader(shaderType) {

        }

        bool Load() override {
            bool bSuccess = FileResource::Load();
            if (!bSuccess) {
                return false;
            }

            shader.SetSource(reinterpret_cast<const char*>(bytes.data()));
            shader.Compile();

            return bSuccess;

        }
    public:
        Shader& GetShader() { return shader; }
    private:
        Shader shader;

    };
}

