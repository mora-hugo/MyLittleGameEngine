#include "Renderer/Shaders/Shader.h"
#include "Assertion.h"
HC::Shader::Shader(GLenum shaderType) {
    ShaderType = shaderType;
    Id = glCreateShader(shaderType);

}

HC::Shader::~Shader() {

}

void HC::Shader::SetSource(const char *source) {

    glShaderSource(Id, 1, &source, NULL);
}

void HC::Shader::Compile() {
    glCompileShader(Id);

    int success;
    glGetShaderiv(Id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(Id, 1024, nullptr, infoLog);
        std::cerr << "❌ Erreur compilation Shader (" << ShaderType << "): " << infoLog << std::endl;
    }


}

GLuint HC::Shader::GetId() const {
    return Id;
}

void HC::Shader::Delete() const {
    glDeleteShader(GetId());
}
