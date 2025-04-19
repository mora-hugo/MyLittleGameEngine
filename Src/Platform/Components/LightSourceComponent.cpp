
#include "Components/LightSourceComponent.h"

#include <glm/gtc/type_ptr.hpp>
#include <Scenes/SceneManager.h>

#include "Renderer/Shaders/ShadersResource.h"
#include "Renderer/Renderer.h"
#include "Components/CameraComponent.h"
#include "ECS/Entity.h"
#include "Utils/ShaderUtils.h"
#include "Utils/Time.h"


HC::LightSourceComponent::LightSourceComponent() : Component() {



}

void HC::LightSourceComponent::Draw() {

    /* check if shader is assigned */
    if(lightShader.IsDirty()) {

        if(!lightShader.IsAssetReferenced()) {
            return;
        }

        shaders = lightShader.GetAsset<ShaderAsset>()->GetShaderProgram();
        if(!shaders) {
            Logger::LogError("Shader not loaded");
            return;
        }
        InitializeShader();
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
    //shaders->SetUniform3fv(LIGHT_SOURCE_COLOR_LOCATION, lightColor.colorVec);


    shaders->Unbind();

    Renderer::Draw(*vao, *ibo, *shaders);
}

HC::LightSourceComponent::~LightSourceComponent() {
    vao->Unbind();
    vbo->Unbind();
    ibo->Unbind();
}

void HC::LightSourceComponent::InitializeData(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices) {


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
    layout.Push<float>(3);
    vao->SetLayout(layout);

}

void HC::LightSourceComponent::Initialize() {
    uniformBuffer = Renderer::GetUniformBuffer("Lights");
    std::vector<Vertex> vertices = {
        // Face avant (+Z)
        {{-0.5f, -0.5f,  0.5f},  {1,0,0}, {0,0}, {0,0,1}},
        {{ 0.5f, -0.5f,  0.5f},  {1,0,0}, {1,0}, {0,0,1}},
        {{ 0.5f,  0.5f,  0.5f},  {1,0,0}, {1,1}, {0,0,1}},
        {{-0.5f,  0.5f,  0.5f},  {1,0,0}, {0,1}, {0,0,1}},

        // Face arrière (-Z)
        {{ 0.5f, -0.5f, -0.5f},  {0,1,0}, {0,0}, {0,0,-1}},
        {{-0.5f, -0.5f, -0.5f},  {0,1,0}, {1,0}, {0,0,-1}},
        {{-0.5f,  0.5f, -0.5f},  {0,1,0}, {1,1}, {0,0,-1}},
        {{ 0.5f,  0.5f, -0.5f},  {0,1,0}, {0,1}, {0,0,-1}},

        // Face gauche (-X)
        {{-0.5f, -0.5f, -0.5f},  {0,0,1}, {0,0}, {-1,0,0}},
        {{-0.5f, -0.5f,  0.5f},  {0,0,1}, {1,0}, {-1,0,0}},
        {{-0.5f,  0.5f,  0.5f},  {0,0,1}, {1,1}, {-1,0,0}},
        {{-0.5f,  0.5f, -0.5f},  {0,0,1}, {0,1}, {-1,0,0}},

        // Face droite (+X)
        {{ 0.5f, -0.5f,  0.5f},  {1,1,0}, {0,0}, {1,0,0}},
        {{ 0.5f, -0.5f, -0.5f},  {1,1,0}, {1,0}, {1,0,0}},
        {{ 0.5f,  0.5f, -0.5f},  {1,0,1}, {1,1}, {1,0,0}},
        {{ 0.5f,  0.5f,  0.5f},  {1,0,1}, {0,1}, {1,0,0}},

        // Face dessus (+Y)
        {{-0.5f,  0.5f,  0.5f},  {0,1,1},          {0,0}, {0,1,0}},
        {{ 0.5f,  0.5f,  0.5f},  {1,1,1},          {1,0}, {0,1,0}},
        {{ 0.5f,  0.5f, -0.5f},  {1,0.5f,0.5f},    {1,1}, {0,1,0}},
        {{-0.5f,  0.5f, -0.5f},  {0.5f,0.5f,0.5f}, {0,1}, {0,1,0}},

        // Face dessous (-Y)
        {{-0.5f, -0.5f, -0.5f},  {0.5f,0,0.5f},    {0,0}, {0,-1,0}},
        {{ 0.5f, -0.5f, -0.5f},  {0,0.5f,0.5f},    {1,0}, {0,-1,0}},
        {{ 0.5f, -0.5f,  0.5f},  {0.5f,0.5f,0},    {1,1}, {0,-1,0}},
        {{-0.5f, -0.5f,  0.5f},  {0,0.5f,0.5f},    {0,1}, {0,-1,0}},
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

void HC::LightSourceComponent::InitializeShader() {
    shaders->Bind();

    shaders->SetUniformMatrix4fv(PROJECTION_MATRIX_LOCATION, Renderer::GetProjectionMatrix());
    shaders->SetUniformMatrix4fv(VIEW_MATRIX_LOCATION, Renderer::GetViewMatrix());

    shaders->Unbind();
}

void HC::LightSourceComponent::Update(float deltaTime) {
    Component::Update(deltaTime);
    uniformBuffer->SetData(glm::value_ptr(GetEntity()->GetComponent<TransformComponent>()->GetWorldPosition()), sizeof(glm::vec3), 16);
    uniformBuffer->SetData(glm::value_ptr(lightColor.colorVec), sizeof(glm::vec3), 16 * 2);
}
