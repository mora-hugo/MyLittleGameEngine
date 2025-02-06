#pragma once

#include <vector>
#include "Renderer/Vertex.h"
#include "glad/glad.h"
#include "GLBuffer.h"

namespace HC {
    class VertexBuffer : public IGLBuffer {
    public:
        explicit VertexBuffer(const std::vector<Vertex> &vertices);
        ~VertexBuffer();

        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator=(const VertexBuffer&) = delete;

        void Bind() const override;
        void Unbind() const override;

        [[nodiscard]] GLuint GetId() const override;
        [[nodiscard]] unsigned int GetVertexCount() const;

    private:
        GLuint vertexBufferId;
        unsigned int vertexCount;
    };
}