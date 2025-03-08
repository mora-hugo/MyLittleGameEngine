#pragma once
#include "AssetManager/Asset.h"
#include "Renderer/Shaders/Shader.h"
#include "Renderer/Shaders/ShaderProgram.h"
#include <glad/glad.h>
#include "Logger.h"
#include <iostream>

namespace HC {

    class ShaderAsset : public Asset {
    public:
        ShaderAsset() = default;
        ~ShaderAsset() = default;
        void Load() override {
            Asset::Load();
            auto file = GetAssetFile().GetStream();
            if (!file.is_open()) {
                Logger::LogError("Failed to open file: {0}",  GetAssetFile().path);
                return;
            }

            std::stringstream vertexStream, fragmentStream;
            std::string line;
            enum class ShaderType { NONE, VERTEX, FRAGMENT } currentType = ShaderType::NONE;

            while (std::getline(file, line)) {
                if (line.find("/* ---- VERTEX SHADER ---- */") != std::string::npos) {
                    currentType = ShaderType::VERTEX;
                } else if (line.find("/* ---- FRAGMENT SHADER ---- */") != std::string::npos) {
                    currentType = ShaderType::FRAGMENT;
                } else {
                    if (currentType == ShaderType::VERTEX) vertexStream << line << '\n';
                    else if (currentType == ShaderType::FRAGMENT) fragmentStream << line << '\n';
                }
            }


            vertexShader = std::make_unique<Shader>(GL_VERTEX_SHADER);
            fragmentShader = std::make_unique<Shader>(GL_FRAGMENT_SHADER);

            vertexShader->SetSource(vertexStream.str().c_str());
            fragmentShader->SetSource(fragmentStream.str().c_str());

            vertexShader->Compile();
            fragmentShader->Compile();

            shaderProgram = std::make_shared<ShaderProgram>(*vertexShader, *fragmentShader);
        }

        std::shared_ptr<ShaderProgram> GetShaderProgram() {
            return shaderProgram;
        }
    private:
        std::shared_ptr<ShaderProgram> shaderProgram;
        std::unique_ptr<Shader> vertexShader;
        std::unique_ptr<Shader> fragmentShader;

    START_REFLECTION(ShaderAsset, Asset)
    STOP_REFLECTION()

    ADD_ASSET_EXTENSION(hcshader)


    };
}