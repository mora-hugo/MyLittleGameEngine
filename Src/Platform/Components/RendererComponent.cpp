
#include "Components/RendererComponent.h"
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



        shaders = assetOf.GetAsset<ShaderAsset>()->GetShaderProgram();
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
    layout.Push<float>(2);

    vao->SetLayout(layout);

}

void HC::RendererComponent::Initialize() {
    std::vector<Vertex> vertices = {
        // positions             // couleurs         // UV
        // Face avant
        {{-0.5f, -0.5f,  0.5f},  {1,0,0},            {0,0}},
        {{ 0.5f, -0.5f,  0.5f},  {1,0,0},            {1,0}},
        {{ 0.5f,  0.5f,  0.5f},  {1,0,0},            {1,1}},
        {{-0.5f,  0.5f,  0.5f},  {1,0,0},            {0,1}},

        // Face arrière
        {{ 0.5f, -0.5f, -0.5f},  {0,1,0},            {0,0}},
        {{-0.5f, -0.5f, -0.5f},  {0,1,0},            {1,0}},
        {{-0.5f,  0.5f, -0.5f},  {0,1,0},            {1,1}},
        {{ 0.5f,  0.5f, -0.5f},  {0,1,0},            {0,1}},

        // Face gauche
        {{-0.5f, -0.5f, -0.5f},  {0,0,1},            {0,0}},
        {{-0.5f, -0.5f,  0.5f},  {0,0,1},            {1,0}},
        {{-0.5f,  0.5f,  0.5f},  {0,0,1},            {1,1}},
        {{-0.5f,  0.5f, -0.5f},  {0,0,1},            {0,1}},

        // Face droite
        {{ 0.5f, -0.5f,  0.5f},  {1,1,0},            {0,0}},
        {{ 0.5f, -0.5f, -0.5f},  {1,1,0},            {1,0}},
        {{ 0.5f,  0.5f, -0.5f},  {1,0,1},            {1,1}},
        {{ 0.5f,  0.5f,  0.5f},  {1,0,1},            {0,1}},

        // Face dessus
        {{-0.5f,  0.5f,  0.5f},  {0,1,1},            {0,0}},
        {{ 0.5f,  0.5f,  0.5f},  {1,1,1},            {1,0}},
        {{ 0.5f,  0.5f, -0.5f},  {1,0.5,0.5},        {1,1}},
        {{-0.5f,  0.5f, -0.5f},  {0.5f,0.5f,0.5f},   {0,1}},

        // Face dessous
        {{-0.5f, -0.5f, -0.5f},  {0.5,0,0.5},        {0,0}},
        {{ 0.5f, -0.5f, -0.5f},  {0,0.5,0.5},        {1,0}},
        {{ 0.5f, -0.5f,  0.5f},  {0.5,0.5,0},        {1,1}},
        {{-0.5f, -0.5f,  0.5f},  {0,0.5,0.5},        {0,1}},
    };



    std::vector<uint32_t> indices = {
        /* Front face */
        0, 1, 2, 2, 3, 0,
        /* Back face */
        4, 5, 6, 6, 7, 4,
        /* Left face */
        8, 9, 10, 10, 11, 8,
        /* Right face */
        12, 13, 14, 14, 15, 12,
        /* Top face */
        16, 17, 18, 18, 19, 16,
        /* Bottom face */
        20, 21, 22, 22, 23, 20
    };


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
        shaders->SetUniform1f(TIME_MATRIX_LOCATION, Time::GetAppTime());
        shaders->Unbind();
    }
}
