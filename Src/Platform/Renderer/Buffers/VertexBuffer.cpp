#include "Renderer/Buffers/VertexBuffer.h"


HC::VertexBuffer::VertexBuffer(const std::vector<Vertex> &vertices) : vertexCount(vertices.size()) {

    /* Generate the vertex buffer */
    glGenBuffers(1, &vertexBufferId);

    /* Bind the vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);

    /* Copy the vertices to the buffer */
    /* CPU -> GPU */
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    /* Unbind the vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

HC::VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &vertexBufferId);
}

void HC::VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
}

void HC::VertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint HC::VertexBuffer::GetId() const {
    return vertexBufferId;
}

unsigned int HC::VertexBuffer::GetVertexCount() const {
    return vertexCount;
}
