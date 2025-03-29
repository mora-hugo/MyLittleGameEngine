#include "Renderer/Renderer.h"
#include "GLFW/glfw3.h"

void HC::Renderer::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void HC::Renderer::SetClearColor(const glm::vec4 &color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void HC::Renderer::Draw(const HC::VertexArrayBuffer &vao, const HC::IndexBuffer &ibo, HC::ShaderProgram &shader) {
    shader.Bind();
    vao.Bind();
    ibo.Bind();

    glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr);

    ibo.Unbind();
    vao.Unbind();
    shader.Unbind();
}

void HC::Renderer::SetViewMatrix(const glm::mat4 &newViewMatrix) {
    if (viewMatrix == newViewMatrix) return;

    viewMatrix = newViewMatrix;
    bViewMatrixDirty = true;
}

void HC::Renderer::SetProjectionMatrix(const glm::mat4 &newProjectionMatrix) {
    if (projectionMatrix == newProjectionMatrix) return;

    projectionMatrix = newProjectionMatrix;
    bProjectionMatrixDirty = true;
}

void HC::Renderer::ResetMatrixDirtyFlags() {
    bProjectionMatrixDirty = false;
    bViewMatrixDirty = false;
}


bool HC::Renderer::UniformBufferExists(const std::string &bufferName) {
    return uniformBuffers.find(bufferName) != uniformBuffers.end();
}

HC::UniformBuffer * HC::Renderer::GetUniformBuffer(const std::string &bufferName) {
    if (!UniformBufferExists(bufferName)) return nullptr;

    return uniformBuffers[bufferName].get();
}

void HC::Renderer::CreateUniformBuffer(const std::string &bufferName, size_t bufferSize, GLuint bindingPointIndex) {
    uniformBuffers[bufferName] = std::make_unique<UniformBuffer>(bufferSize, bindingPointIndex);
}

void HC::Renderer::SetDepthBufferEnabled(bool bEnabled) {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void HC::Renderer::SetViewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
}



