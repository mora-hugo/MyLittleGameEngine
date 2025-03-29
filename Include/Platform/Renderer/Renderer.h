#pragma once

#include <glm/vec4.hpp>

#include "Buffers/UniformBuffer.h"
#include "Renderer/Shaders/ShaderProgram.h"
#include "Renderer/Buffers/VertexArrayBuffer.h"
#include "Renderer/Buffers/IndexBuffer.h"
#include "Components/TransformComponent.h"
namespace HC {
    class Renderer {
    public:
        /* Initialize functions */
        static void SetClearColor(const glm::vec4& color);
        static void SetDepthBufferEnabled(bool bEnabled);
        static void SetViewport(int x, int y, int width, int height);
        /* Utils */
        static void Clear();
        static void Draw(const VertexArrayBuffer& vao, const IndexBuffer& ibo, ShaderProgram& shader);




        /* Matrix */
        static void SetViewMatrix(const glm::mat4& viewMatrix);
        static void SetProjectionMatrix(const glm::mat4& projectionMatrix);

        static bool IsProjectionMatrixDirty() { return bProjectionMatrixDirty; }
        static bool IsViewMatrixDirty() { return bViewMatrixDirty; }

        static void ResetMatrixDirtyFlags();


        static glm::mat4 GetProjectionMatrix() { return projectionMatrix; }
        static glm::mat4 GetViewMatrix() { return viewMatrix; }

        static bool UniformBufferExists(const std::string& bufferName);
        static UniformBuffer* GetUniformBuffer(const std::string& bufferName);
        static void CreateUniformBuffer(const std::string& bufferName, size_t bufferSize, GLuint bindingPointIndex);

    private:
        static inline std::unordered_map<std::string, std::unique_ptr<UniformBuffer>> uniformBuffers;

        static inline glm::mat4 projectionMatrix = glm::mat4(1.0f);
        static inline glm::mat4 viewMatrix = glm::mat4(1.0f);

        static inline bool bProjectionMatrixDirty = true;
        static inline bool bViewMatrixDirty = true;
    };
}
