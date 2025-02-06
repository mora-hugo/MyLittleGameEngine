#include "Renderer/Renderer.h"

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

void HC::Renderer::SetDepthBufferEnabled(bool bEnabled) {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void HC::Renderer::SetViewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
}
