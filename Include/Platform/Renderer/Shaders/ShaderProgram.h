#pragma once

#include "glad/glad.h"
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include "Shader.h"

namespace HC {
    class ShaderProgram {
    public:
        ShaderProgram(const Shader & vertexShader, const Shader& fragmentShader);
        ~ShaderProgram();

        void Bind() const;
        void Unbind() const;

        void SetUniformMatrix4fv(const std::string& name, const glm::mat4& matrix);
        void SetUniform3fv(const std::string& name, const glm::vec3& vector);
        void SetUniform1f(const std::string& name, float value);
        void SetUniform1i(const std::string& name, int value);

        bool IsBound() const;
        GLuint GetId() const;
    private:
        GLint GetUniformLocation(const std::string& name);
        GLuint CreateShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
        GLuint shaderProgram;
        std::unordered_map<std::string, GLint> m_UniformLocationCache;
    };
}