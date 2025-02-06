#include "Renderer/Buffers/VertexArrayBuffer.h"
#include <iostream>
HC::VertexArrayBuffer::VertexArrayBuffer() {
    glGenVertexArrays(1, &vertexArrayBufferId);
}

HC::VertexArrayBuffer::~VertexArrayBuffer() {
    glDeleteVertexArrays(1, &vertexArrayBufferId);
}

void HC::VertexArrayBuffer::Bind() const {
    glBindVertexArray(vertexArrayBufferId);
}

void HC::VertexArrayBuffer::Unbind() const {
    glBindVertexArray(0);
}




GLuint HC::VertexArrayBuffer::GetId() const {
    return vertexArrayBufferId;
}

void HC::VertexArrayBuffer::SetLayout(const HC::VertexBufferLayout &layout) {
    const auto& elements = layout.GetElements();
    size_t stride = layout.GetStride();

    for (GLuint i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, stride, (const void*)element.offset);
    }
}
