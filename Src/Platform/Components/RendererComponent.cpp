
#include "Components/RendererComponent.h"

#include <Scenes/SceneManager.h>

#include "Renderer/Shaders/ShadersResource.h"
#include "Renderer/Renderer.h"
#include "Components/CameraComponent.h"
#include "ECS/Entity.h"
#include "Utils/ShaderUtils.h"
#include "Utils/Time.h"


HC::RendererComponent::RendererComponent() : Component() {



}

void HC::RendererComponent::Draw() {

    /* check if shader is assigned */
    if(assetOf.IsDirty()) {

        if(!assetOf.IsAssetReferenced()) {
            return;
        }


        auto asset = assetOf.GetAsset<ShaderAsset>();;
        shaders = asset->GetShaderProgram();


        if(!shaders) {
            Logger::LogError("Shader not loaded");
            return;
        }
        InitializeShader();
    }

    if (textureAssetOf.IsAssetReferenced()) {
        textureAssetOf.GetAsset<TextureAsset>()->GetTexture().Bind();
    }

    if(!shaders) {
        return;
    }

    transformComponent = GetEntity()->GetComponent<TransformComponent>();
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

void HC::RendererComponent::InitializeData(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices) {


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

void HC::RendererComponent::Initialize() {

    // std::vector<Vertex> vertices = {
    //     // Face avant (+Z)
    //     {{-0.5f, -0.5f,  0.5f},  {1,0,0}, {0,0}, {0,0,1}},
    //     {{ 0.5f, -0.5f,  0.5f},  {1,0,0}, {1,0}, {0,0,1}},
    //     {{ 0.5f,  0.5f,  0.5f},  {1,0,0}, {1,1}, {0,0,1}},
    //     {{-0.5f,  0.5f,  0.5f},  {1,0,0}, {0,1}, {0,0,1}},
    //
    //     // Face arrière (-Z)
    //     {{ 0.5f, -0.5f, -0.5f},  {0,1,0}, {0,0}, {0,0,-1}},
    //     {{-0.5f, -0.5f, -0.5f},  {0,1,0}, {1,0}, {0,0,-1}},
    //     {{-0.5f,  0.5f, -0.5f},  {0,1,0}, {1,1}, {0,0,-1}},
    //     {{ 0.5f,  0.5f, -0.5f},  {0,1,0}, {0,1}, {0,0,-1}},
    //
    //     // Face gauche (-X)
    //     {{-0.5f, -0.5f, -0.5f},  {0,0,1}, {0,0}, {-1,0,0}},
    //     {{-0.5f, -0.5f,  0.5f},  {0,0,1}, {1,0}, {-1,0,0}},
    //     {{-0.5f,  0.5f,  0.5f},  {0,0,1}, {1,1}, {-1,0,0}},
    //     {{-0.5f,  0.5f, -0.5f},  {0,0,1}, {0,1}, {-1,0,0}},
    //
    //     // Face droite (+X)
    //     {{ 0.5f, -0.5f,  0.5f},  {1,1,0}, {0,0}, {1,0,0}},
    //     {{ 0.5f, -0.5f, -0.5f},  {1,1,0}, {1,0}, {1,0,0}},
    //     {{ 0.5f,  0.5f, -0.5f},  {1,0,1}, {1,1}, {1,0,0}},
    //     {{ 0.5f,  0.5f,  0.5f},  {1,0,1}, {0,1}, {1,0,0}},
    //
    //     // Face dessus (+Y)
    //     {{-0.5f,  0.5f,  0.5f},  {0,1,1},          {0,0}, {0,1,0}},
    //     {{ 0.5f,  0.5f,  0.5f},  {1,1,1},          {1,0}, {0,1,0}},
    //     {{ 0.5f,  0.5f, -0.5f},  {1,0.5f,0.5f},    {1,1}, {0,1,0}},
    //     {{-0.5f,  0.5f, -0.5f},  {0.5f,0.5f,0.5f}, {0,1}, {0,1,0}},
    //
    //     // Face dessous (-Y)
    //     {{-0.5f, -0.5f, -0.5f},  {0.5f,0,0.5f},    {0,0}, {0,-1,0}},
    //     {{ 0.5f, -0.5f, -0.5f},  {0,0.5f,0.5f},    {1,0}, {0,-1,0}},
    //     {{ 0.5f, -0.5f,  0.5f},  {0.5f,0.5f,0},    {1,1}, {0,-1,0}},
    //     {{-0.5f, -0.5f,  0.5f},  {0,0.5f,0.5f},    {0,1}, {0,-1,0}},
    // };
    //
    //
    //
    //
    // std::vector<uint32_t> indices = {
    //     /* Front face */
    //     0, 1, 2, 2, 3, 0,
    //     /* Back face */
    //     4, 5, 6, 6, 7, 4,
    //     /* Left face */
    //     8, 9, 10, 10, 11, 8,
    //     /* Right face */
    //     12, 13, 14, 14, 15, 12,
    //     /* Top face */
    //     16, 17, 18, 18, 19, 16,
    //     /* Bottom face */
    //     20, 21, 22, 22, 23, 20
    // };

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    const unsigned int X_SEGMENTS = 32;
    const unsigned int Y_SEGMENTS = 16;
    const float PI = 3.14159265359f;
    const float radius = 0.5f;

    for (unsigned int y = 0; y <= Y_SEGMENTS; ++y) {
        for (unsigned int x = 0; x <= X_SEGMENTS; ++x) {
            float xSegment = static_cast<float>(x) / static_cast<float>(X_SEGMENTS);
            float ySegment = static_cast<float>(y) / static_cast<float>(Y_SEGMENTS);
            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

            Vertex vertex;
            vertex.position = { xPos * radius, yPos * radius, zPos * radius };
            vertex.normal   = { xPos, yPos, zPos };
            vertex.texCoord = { xSegment, ySegment };
            vertex.color    = { 1.0f, 1.0f, 1.0f };
            vertices.push_back(vertex);
        }
    }

    for (unsigned int y = 0; y < Y_SEGMENTS; ++y) {
        for (unsigned int x = 0; x < X_SEGMENTS; ++x) {
            uint32_t first  = y * (X_SEGMENTS + 1) + x;
            uint32_t second = first + X_SEGMENTS + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }


    InitializeData(vertices, indices);
}

void HC::RendererComponent::InitializeShader() {
    shaders->Bind();

    shaders->SetUniformMatrix4fv(PROJECTION_MATRIX_LOCATION, Renderer::GetProjectionMatrix());
    shaders->SetUniformMatrix4fv(VIEW_MATRIX_LOCATION, Renderer::GetViewMatrix());

    shaders->Unbind();
}

void HC::RendererComponent::Update(float deltaTime) {
    Component::Update(deltaTime);
    if(shaders) {
        shaders->Bind();
        //shaders->SetUniform1f(TIME_MATRIX_LOCATION, Time::GetAppTime());
        shaders->Unbind();
    }

}
