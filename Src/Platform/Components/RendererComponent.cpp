
#include "Components/RendererComponent.h"
#include "Renderer/Shaders/ShadersResource.h"
#include "Renderer/Renderer.h"
#include "Components/CameraComponent.h"
#include "ECS/Entity.h"
#include "Utils/ShaderUtils.h"


HC::RendererComponent::RendererComponent() : Component() {



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

void HC::RendererComponent::InitializeData(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, std::shared_ptr<ShaderProgram> shaderProgram) {

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

void HC::RendererComponent::Initialize() {
    std::vector<Vertex> vertices = {
            // Face avant
            {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}}, // 0
            {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}}, // 1
            {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}}, // 2
            {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}}, // 3

            // Face arrière
            {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}}, // 4
            {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 1.0f}}, // 5
            {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}}, // 6
            {{-0.5f,  0.5f, -0.5f}, {0.5f, 0.5f, 0.5f}}  // 7
    };

    std::vector<unsigned int> indices = {
            // Face avant
            0, 1, 2,  2, 3, 0,

            // Face arrière
            4, 5, 6,  6, 7, 4,

            // Face gauche
            4, 0, 3,  3, 7, 4,

            // Face droite
            1, 5, 6,  6, 2, 1,

            // Face haut
            3, 2, 6,  6, 7, 3,

            // Face bas
            4, 5, 1,  1, 0, 4
    };

    auto shaderProgram = ShaderUtils::LoadShader(RESOURCES_PATH"/Shaders/vertex.glsl",
                                                 RESOURCES_PATH"/Shaders/fragment.glsl");

    InitializeData(vertices, indices, shaderProgram);

    shaders->Bind();

    shaders->SetUniformMatrix4fv(PROJECTION_MATRIX_LOCATION, Renderer::GetProjectionMatrix());
    shaders->SetUniformMatrix4fv(VIEW_MATRIX_LOCATION, Renderer::GetViewMatrix());

    shaders->Unbind();
}
