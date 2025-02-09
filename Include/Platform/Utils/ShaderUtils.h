#pragma once
#include <memory>
#include "Renderer/Shaders/ShaderProgram.h"
#include "Singleton.h"
#include "Renderer/Shaders/ShadersResource.h"


    namespace HC::ShaderUtils {

        std::shared_ptr<ShaderProgram> inline LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
            auto vertexShaderResource = ResourceManager::GetInstance()->Load<ShaderResource>(vertexShaderPath, GL_VERTEX_SHADER);
            auto fragmentShaderResource = ResourceManager::GetInstance()->Load<ShaderResource>(fragmentShaderPath, GL_FRAGMENT_SHADER);

            Assertion(vertexShaderResource != nullptr && fragmentShaderResource != nullptr, "Shader not loaded");

            //TODO
            auto shaderProgram = std::make_shared<ShaderProgram>(vertexShaderResource->GetShader(), fragmentShaderResource->GetShader());

            ResourceManager::GetInstance()->Unload(vertexShaderPath);
            ResourceManager::GetInstance()->Unload(fragmentShaderPath);

            return shaderProgram;
        }

    }
