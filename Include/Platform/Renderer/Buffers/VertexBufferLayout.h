#pragma once

#include <vector>
#include <glad/glad.h>
#include "Renderer/LayoutElement.h"
#include <iostream>
namespace HC {
    class VertexBufferLayout {
    public:
        VertexBufferLayout() {}

        template<typename T>
        void Push(GLuint count);

        [[nodiscard]] const std::vector<LayoutElement>& GetElements() const { return m_Elements; }
        [[nodiscard]] GLsizei GetStride() const { return m_Stride; }

    private:
        std::vector<LayoutElement> m_Elements;
        size_t m_Stride = 0;
    };

    template<>
    inline void VertexBufferLayout::Push<float>(GLuint count) {
        GLsizei offset = m_Stride;
        m_Elements.push_back({ GL_FLOAT, count, GL_FALSE, offset });
        m_Stride += count * sizeof(float);
    }

    template<>
    inline void VertexBufferLayout::Push<unsigned int>(GLuint count) {
        GLsizei offset = m_Stride;
        m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE, offset });
        m_Stride += count * sizeof(GLuint);
    }

    template<>
    inline void VertexBufferLayout::Push<unsigned char>(GLuint count) {
        GLsizei offset = m_Stride;
        m_Elements.push_back({ GL_FLOAT, count, GL_FALSE, offset });
        m_Stride += count * sizeof(GLfloat);
    }
}