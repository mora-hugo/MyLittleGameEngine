#pragma once

#include <vector>
#include <memory>
#include "ECS/Component.h"
#include "Renderer/Vertex.h"
#include "Renderer/Buffers/VertexBuffer.h"
#include "Renderer/Buffers/IndexBuffer.h"
#include "Renderer/Buffers/VertexArrayBuffer.h"
#include "Renderer/Shaders/ShaderProgram.h"
#include "AssetManager/AssetOf.h"
#include "TransformComponent.h"
#include "AssetManager/ShaderAsset.h"
#include "AssetManager/TextureAsset.h"


namespace HC {
    class RendererComponent : public Component {
    public:
        RendererComponent();
        void Initialize() override;
        ~RendererComponent() override;
        void Update(float deltaTime) override;
        virtual void Draw();

    private:
        void InitializeData(const std::vector<Vertex>& vertices = {}, const std::vector<unsigned int>& indices = {});
        void InitializeShader();
        std::unique_ptr< HC::VertexBuffer> vbo;
        std::unique_ptr<HC::IndexBuffer> ibo;
        std::unique_ptr<HC::VertexArrayBuffer> vao;
        std::shared_ptr<HC::ShaderProgram> shaders;

        const TransformComponent* transformComponent;

        static constexpr const char* PROJECTION_MATRIX_LOCATION = "u_ProjectionMatrix";
        static constexpr const char* VIEW_MATRIX_LOCATION = "u_ViewMatrix";
        static constexpr const char* MODEL_MATRIX_LOCATION = "u_ModelMatrix";
        static constexpr const char* TIME_MATRIX_LOCATION = "u_Time";
        static constexpr const char* WORLD_POS_MATRIX_LOCATION = "u_WorldPos";

        AssetOf assetOf {ShaderAsset::StaticClass()};
        AssetOf textureAssetOf {TextureAsset::StaticClass()};

        START_REFLECTION(RendererComponent, Component)
            ADD_OBJECT_MEMBER_PROPERTY(assetOf)
            ADD_OBJECT_MEMBER_PROPERTY(textureAssetOf)
        STOP_REFLECTION()
    };

}