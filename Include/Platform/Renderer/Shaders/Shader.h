#pragma once
#include <glad/glad.h>
namespace HC {
    class Shader {
    public:
        explicit Shader(GLenum shaderType);
        ~Shader();

        void SetSource(const char *source);
        void Compile();

        void Delete() const;
        GLuint GetId() const;
    private:
        GLuint Id;
        GLenum ShaderType;
    };
}