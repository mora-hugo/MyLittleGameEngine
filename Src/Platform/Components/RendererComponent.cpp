
#include "Components/RendererComponent.h"

#include <Scenes/SceneManager.h>

#include "Renderer/Shaders/ShadersResource.h"
#include "Renderer/Renderer.h"
#include "Components/CameraComponent.h"



HC::RendererComponent::RendererComponent() : Component() {
}

void HC::RendererComponent::Draw() {

    if (!staticMeshAssetOf.IsAssetReferenced() || !assetOf.IsAssetReferenced()) {
        return;
    }

    /* check if shader is assigned */
    if(assetOf.IsDirty()) {

        if(!assetOf.IsAssetReferenced()) {
            return;
        }

        if(!assetOf.GetAsset()) {
            Logger::LogError("Shader not loaded");
            return;
        }
        InitializeShader();
    }

    transformComponent = GetEntity()->GetComponent<TransformComponent>();

    auto shaders = assetOf.GetAsset<ShaderAsset>()->GetShaderProgram();
    shaders->Bind();

    if (Renderer::IsProjectionMatrixDirty()) {
        shaders->SetUniformMatrix4fv(PROJECTION_MATRIX_LOCATION, Renderer::GetProjectionMatrix());
    }

    if (Renderer::IsViewMatrixDirty()) {
        shaders->SetUniformMatrix4fv(VIEW_MATRIX_LOCATION, Renderer::GetViewMatrix());
    }

    shaders->SetUniformMatrix4fv(MODEL_MATRIX_LOCATION, transformComponent->GetModelMatrix());

    if (assetOfTexture.IsAssetLoaded()) {
        assetOfTexture.GetAsset<TextureAsset>()->GetTexture().Bind();
    }
    shaders->Unbind();




    staticMeshAssetOf.GetAsset<StaticMeshAsset>()->Draw(shaders);

    
}

HC::RendererComponent::~RendererComponent() {
}



void HC::RendererComponent::Initialize() {

}

void HC::RendererComponent::InitializeShader() {
    auto shaders = assetOf.GetAsset<ShaderAsset>()->GetShaderProgram();
    shaders->Bind();

    shaders->SetUniformMatrix4fv(PROJECTION_MATRIX_LOCATION, Renderer::GetProjectionMatrix());
    shaders->SetUniformMatrix4fv(VIEW_MATRIX_LOCATION, Renderer::GetViewMatrix());

    shaders->Unbind();
}

void HC::RendererComponent::Update(float deltaTime) {
    Component::Update(deltaTime);
    /*
    auto shaders = assetOf.GetAsset<ShaderAsset>()->GetShaderProgram();
    if(shaders) {
        shaders->Bind();
        //shaders->SetUniform1f(TIME_MATRIX_LOCATION, Time::GetAppTime());
        shaders->Unbind();
    }
    */

}
