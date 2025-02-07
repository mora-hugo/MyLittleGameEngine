#pragma once
#include <glm/vec2.hpp>
#include "Renderer/Buffers/GLBuffer.h"
#include "glad/glad.h"

namespace HC {
    class FrameBuffer : public IGLBuffer {
    public:
        explicit FrameBuffer(const glm::vec2& size);
        ~FrameBuffer();

        void Resize(const glm::vec2& size);
        void Bind() const override;
        void Unbind() const override;


        [[nodiscard]] unsigned int GetRenderTextureId() const { return colorAttachment; }
        [[nodiscard]] unsigned int GetRBO() const { return rbo; }
        [[nodiscard]] unsigned int GetId() const override { return framebuffer; }
        [[nodiscard]] const glm::vec2& GetSize() const { return framebufferSize; }

    private:
        void Destroy();
        void Create(const glm::vec2& size);
    private:
        GLuint framebuffer;
        GLuint colorAttachment;
        GLuint rbo;
        glm::vec2 framebufferSize;
    };
}