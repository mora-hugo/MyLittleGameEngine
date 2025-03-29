#pragma once
#include "GLBuffer.h"

namespace HC {
    class UniformBuffer : public IGLBuffer {
    public:
        UniformBuffer(size_t bufferSize, GLuint bindingPointIndex);
        ~UniformBuffer() override;
        void SetData(const void* data, size_t size, size_t offset);
        void Bind() const override;

        void Unbind() const override;

        [[nodiscard]] GLuint GetId() const override;

    private:
        GLuint uniformBufferId;
    };
}
