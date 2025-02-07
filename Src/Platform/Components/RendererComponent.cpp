
#include "Components/RendererComponent.h"
#include "Renderer/Shaders/ShadersResource.h"
#include "Renderer/Renderer.h"
#include "Components/CameraComponent.h"
#include "ECS/Entity.h"


HC::RendererComponent::RendererComponent() {



}

void HC::RendererComponent::Draw() {
    shaders->Bind();
    if (Renderer::IsProjectionMatrixDirty()) {
        shaders->SetUniformMatrix4fv(PROJECTION_MATRIX_LOCATION, Renderer::GetProjectionMatrix());
    }

    if (Renderer::IsViewMatrixDirty()) {
        shaders->SetUniformMatrix4fv(VIEW_MATRIX_LOCATION, Renderer::GetViewMatrix());
    }

    shaders->SetUniformMatrix4fv(MODEL_MATRIX_LOCATION, transformComponent->GetModelMatrix());

    shaders->Unbind();
    Renderer::Draw(*vao, *ibo, *shaders);
}

HC::RendererComponent::~RendererComponent() {
    vao->Unbind();
    vbo->Unbind();
    ibo->Unbind();
}

void HC::RendererComponent::Initialize(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, std::shared_ptr<ShaderProgram> shaderProgram) {

    transformComponent = GetEntity()->GetComponent<TransformComponent>();

    shaders = shaderProgram;

    vao = std::make_unique<VertexArrayBuffer>();
    vao->Bind();

    vbo = std::make_unique<VertexBuffer>(vertices);
    vbo->Bind();

    ibo = std::make_unique<IndexBuffer>(indices);
    ibo->Bind();

    HC::VertexBufferLayout layout;
    layout.Push<float>(3); // Position
    layout.Push<float>(3); // Color

    vao->SetLayout(layout);
}
