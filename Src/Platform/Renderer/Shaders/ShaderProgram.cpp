
#include <glm/gtc/type_ptr.hpp>
#include "Renderer/Shaders/ShaderProgram.h"
#include "Renderer/Shaders/Shader.h"
#include "Assertion.h"


HC::ShaderProgram::ShaderProgram(const Shader & vertexShader, const Shader& fragmentShader) {

    shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);
}

HC::ShaderProgram::~ShaderProgram() {
    glDeleteProgram(shaderProgram);
}

void HC::ShaderProgram::Bind() const {
    glUseProgram(shaderProgram);
}

void HC::ShaderProgram::Unbind() const {
    glUseProgram(0);
}

/* Shaders need to be compiled */
GLuint HC::ShaderProgram::CreateShaderProgram(const Shader & vertexShader, const Shader& fragmentShader) {


    /* Create program and link shaders */
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShader.GetId());
    glAttachShader(programID, fragmentShader.GetId());
    glLinkProgram(programID);

    int success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(programID, 512, nullptr, infoLog);
        Assertion(false, "Program Link Error: " + std::string(infoLog));
    }

    vertexShader.Delete();
    fragmentShader.Delete();

    return programID;
}

void HC::ShaderProgram::SetUniformMatrix4fv(const std::string &name, const glm::mat4 &matrix) {
    Assertion(IsBound(), "Shader not bound");
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void HC::ShaderProgram::SetUniform3fv(const std::string &name, const glm::vec3 &vector) {
    Assertion(IsBound(), "Shader not bound");
    glUniform3fv(GetUniformLocation(name), 1, &vector[0]);
}

void HC::ShaderProgram::SetUniform1f(const std::string &name, float value) {
    Assertion(IsBound(), "Shader not bound");
    glUniform1f(GetUniformLocation(name), value);
}

void HC::ShaderProgram::SetUniform1i(const std::string &name, int value) {
    Assertion(IsBound(), "Shader not bound");
    glUniform1i(GetUniformLocation(name), value);
}

GLint HC::ShaderProgram::GetUniformLocation(const std::string& name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
        return m_UniformLocationCache[name];
    }

    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    Assertion(location != -1, "Uniform " + name + " not found in shader");

    m_UniformLocationCache[name] = location;
    return location;
}

GLuint HC::ShaderProgram::GetId() const {
    return shaderProgram;
}

bool HC::ShaderProgram::IsBound() const {
    GLint currentProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    return currentProgram == (GLint)shaderProgram;
}
