#pragma once

#include <glad/glad.h>

#include "Renderer/Buffers/GLBuffer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

namespace HC {
    class VertexArrayBuffer : public IGLBuffer {
    public:
        VertexArrayBuffer();
        ~VertexArrayBuffer();

        void Bind() const override;
        void Unbind() const override;

        void SetLayout(const VertexBufferLayout& layout);

        [[nodiscard]] GLuint GetId() const override;

    private:
        GLuint vertexArrayBufferId;
    };
}