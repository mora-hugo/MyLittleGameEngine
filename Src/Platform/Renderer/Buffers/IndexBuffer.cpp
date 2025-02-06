#include "Renderer/Buffers/IndexBuffer.h"

HC::IndexBuffer::IndexBuffer(const std::vector<unsigned int> &indices) : indexCount(indices.size()) {
    /* Generate the vertex buffer */
    glGenBuffers(1, &indexBufferId);

    /* Bind the vertex buffer */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);

    /* Copy the vertices to the buffer */
    /* CPU -> GPU */
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

HC::IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &indexBufferId);
}

void HC::IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
}

void HC::IndexBuffer::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint HC::IndexBuffer::GetId() const {
    return indexBufferId;
}

unsigned int HC::IndexBuffer::GetCount() const {
    return indexCount;
}
