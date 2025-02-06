#pragma once

#include <vector>
#include <glad/glad.h>
#include "Renderer/Vertex.h"
#include "Renderer/Buffers/GLBuffer.h"

namespace HC {
    class IndexBuffer : public IGLBuffer {
    public:
        explicit IndexBuffer(const std::vector<unsigned int> &indices);
        ~IndexBuffer();

        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer& operator=(const IndexBuffer&) = delete;

        void Bind() const override;
        void Unbind() const override;

        [[nodiscard]] GLuint GetId() const override;
        [[nodiscard]] unsigned int GetCount() const;
    private:
        GLuint indexBufferId;
        unsigned int indexCount;
    };
}