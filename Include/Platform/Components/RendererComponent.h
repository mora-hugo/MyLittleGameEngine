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


namespace HC {
    class RendererComponent : public Component {
    public:
        RendererComponent();
        void Initialize() override;
        ~RendererComponent() override;
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

        AssetOf assetOf {ShaderAsset::StaticClass()};

        START_REFLECTION(RendererComponent, Component)
            ADD_OBJECT_MEMBER_PROPERTY(assetOf)
        STOP_REFLECTION()
    };

}