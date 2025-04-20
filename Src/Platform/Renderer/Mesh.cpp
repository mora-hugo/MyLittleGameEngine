#include "Renderer/Mesh.h"
#include "Renderer/Vertex.h"
#include "Renderer/Buffers/IndexBuffer.h"
#include "Renderer/Buffers/VertexArrayBuffer.h"
#include "Renderer/Buffers/VertexBuffer.h"
#include "Renderer/Renderer.h"
HC::Mesh::Mesh(const std::string& name, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) {
    this->name = name;

    vao = std::make_unique<VertexArrayBuffer>();
    vao->Bind();

    vbo = std::make_unique<VertexBuffer>(vertices);
    vbo->Bind();

    ibo = std::make_unique<IndexBuffer>(indices);
    ibo->Bind();

    HC::VertexBufferLayout layout;
    layout.Push<float>(3); // Position
    layout.Push<float>(3); // Color
    layout.Push<float>(2); // UV
    layout.Push<float>(3); // Normal

    vao->SetLayout(layout);
}

HC::Mesh::~Mesh() {
}

void HC::Mesh::Draw(std::shared_ptr<ShaderProgram> shaderProgram) const {
    Renderer::Draw(*vao, *ibo, *shaderProgram);
}
