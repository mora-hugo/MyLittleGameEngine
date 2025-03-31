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
#include "Properties/Color.h"


namespace HC {
    class UniformBuffer;
}

namespace HC {
    class LightSourceComponent : public Component {
    public:
        LightSourceComponent();
        void Initialize() override;
        ~LightSourceComponent() override;
        void Update(float deltaTime) override;
        void Draw() override;

    private:
        void InitializeData(const std::vector<Vertex>& vertices = {}, const std::vector<unsigned int>& indices = {});
        void InitializeShader();
        std::unique_ptr< HC::VertexBuffer> vbo;
        std::unique_ptr<HC::IndexBuffer> ibo;
        std::unique_ptr<HC::VertexArrayBuffer> vao;
        std::shared_ptr<HC::ShaderProgram> shaders;
        UniformBuffer* uniformBuffer;

        const TransformComponent* transformComponent;

        static constexpr const char* PROJECTION_MATRIX_LOCATION = "u_ProjectionMatrix";
        static constexpr const char* VIEW_MATRIX_LOCATION = "u_ViewMatrix";
        static constexpr const char* MODEL_MATRIX_LOCATION = "u_ModelMatrix";
        static constexpr const char* TIME_MATRIX_LOCATION = "u_Time";
        static constexpr const char* WORLD_POS_MATRIX_LOCATION = "u_WorldPos";

        static constexpr const char* LIGHT_COLOR_LOCATION = "objectColor";
        static constexpr const char* LIGHT_SOURCE_COLOR_LOCATION = "lightColor";


        AssetOf lightShader {ShaderAsset::StaticClass()};
        Color lightColor;

        START_REFLECTION(LightSourceComponent, Component)
            ADD_OBJECT_MEMBER_PROPERTY(lightShader)
                ADD_OBJECT_MEMBER_PROPERTY(lightColor)
        STOP_REFLECTION()
    };

}
