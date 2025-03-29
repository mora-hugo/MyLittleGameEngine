#include "Renderer/Buffers/UniformBuffer.h"

HC::UniformBuffer::UniformBuffer(size_t bufferSize, GLuint bindingPointIndex) {
    glGenBuffers(1, &uniformBufferId);

    glBindBuffer(GL_UNIFORM_BUFFER, uniformBufferId);
    glBufferData(GL_UNIFORM_BUFFER, bufferSize, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPointIndex, uniformBufferId);
}

HC::UniformBuffer::~UniformBuffer() {
}

void HC::UniformBuffer::SetData(const void *data, size_t size, size_t offset) {
    Bind();
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    Unbind();
}

void HC::UniformBuffer::Bind() const {
    glBindBuffer(GL_UNIFORM_BUFFER, uniformBufferId);
}

void HC::UniformBuffer::Unbind() const {
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

GLuint HC::UniformBuffer::GetId() const {
    return uniformBufferId;
}
