#pragma once


#include <memory>
#include "Vertex.h"
#include <vector>
#include <string>

namespace HC {
    class VertexBuffer;
    class IndexBuffer;
    class VertexArrayBuffer;
    class ShaderProgram;

    class Mesh {
    public:
        Mesh(const std::string& name, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
        ~Mesh();

        std::string & GetName() { return name; }
        void Draw(std::shared_ptr<ShaderProgram> shaderProgram) const;
    private:
        std::string name;
        std::unique_ptr<HC::VertexBuffer> vbo;
        std::unique_ptr<HC::IndexBuffer> ibo;
        std::unique_ptr<HC::VertexArrayBuffer> vao;
    };
}

